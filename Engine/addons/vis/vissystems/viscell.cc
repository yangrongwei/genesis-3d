/****************************************************************************
Copyright (c) 2010,Radon Labs GmbH
Copyright (c) 2011-2013,WebJet Business Division,CYOU

http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "stdneb.h"
#include "vis/vissystems/viscell.h"

namespace Vis
{
__ImplementClass(Vis::VisCell, 'VICL', Core::RefCounted);

using namespace Math;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
VisCell::VisCell()
	:mNumEntitiesInHierarchy(0)
{
}

//------------------------------------------------------------------------------
/**
*/
VisCell::~VisCell()
{
    // make sure we've been properly cleaned up
    n_assert(!this->mParentCell.isvalid());
    n_assert(this->mChildCells.IsEmpty());
    n_assert(this->mEntities.empty());
}

//------------------------------------------------------------------------------
/**
*/
void
VisCell::OnAttach()
{
    n_assert(this->mEntities.empty());

	mNumEntitiesInHierarchy = 0;
    // recurse into child cells
    IndexT i;
    for (i = 0; i < this->mChildCells.Size(); i++)
    {
        this->mChildCells[i]->OnAttach();
    }
}

//------------------------------------------------------------------------------
/**
*/
void
VisCell::OnRemove()
{

    // first recurse to child cells
    IndexT i;
    for (i = 0; i < this->mChildCells.Size(); i++)
    {
        this->mChildCells[i]->OnRemove();
    }

	mNumEntitiesInHierarchy = 0;

    // cleanup
    this->mParentCell = 0;
    this->mChildCells.Clear();
    this->mEntities.clear();
}

//------------------------------------------------------------------------------
/**
    NOTE: the cell hierarchy may only be built during the setup phase while
    the cell hierarchy haven't been added to the stage yet.
*/
void
VisCell::AttachChildCell(const GPtr<VisCell>& cell)
{
    n_assert(cell.isvalid())
    n_assert(!cell->GetParentCell().isvalid()); 

    cell->mParentCell = this;
    this->mChildCells.Append(cell);
}

//------------------------------------------------------------------------------
/**
    Attach an context to this VisCell. This will happen when a visEntity
    moves through the world, leaving and entering cells as necessary.
*/
void
VisCell::AttachEntity(const GPtr<VisEntity>& ent)
{
    n_assert(ent.isvalid());

    this->mEntities.push_back(ent);

	UpdateNumEntitiesInHierarchy(+1);
}

//------------------------------------------------------------------------------
/**
*/
void
VisCell::RemoveEntity(const GPtr<VisEntity>& ent)
{
    n_assert(ent.isvalid());

	this->mEntities.remove(ent );

	UpdateNumEntitiesInHierarchy(-1);
}

//------------------------------------------------------------------------------
/**
    Starting from this cell, try to find the smallest cell which completely
    contains the given entity:

    - starting from initial cell:
        - if the entity does not fit into the cell, move up the
          tree until the first cell is found which the entity completely fits into
        - if the entity fits into a cell, check each child cell if the 
          entity fits completely into the cell

    The entity will not be attached! If the entity does not fit into the 
    root cell, the root cell will be returned, not 0.
    
    @param  entity      pointer of entity to find new cell for
    @return             cell which completely encloses the entity (the root cell is an exception)
*/
VisCell*
VisCell::FindEntityContainmentCell(const GPtr<VisEntity>& entity)
{
    // get global bounding box of entity
    const bbox& entityBox = entity->GetBoundingBox();

    // find the first upward cell which completely contains the entity,
    // stop at tree root
    GPtr<VisCell> curCell = this;
    while ( (curCell->GetParentCell().isvalid()) && (!curCell->GetBoundingBox().contains(entityBox)) )
    {
        curCell = curCell->GetParentCell();
    } 

    // find smallest downward cell which completely contains the entity
    IndexT cellIndex;
    SizeT numCells;
    do
    {
        const Array<GPtr<VisCell> >& curChildren = curCell->GetChildCells();
        numCells = curChildren.Size();
        for (cellIndex = 0; cellIndex < numCells; cellIndex++)
        {
            const GPtr<VisCell>& childCell = curChildren[cellIndex];
            if (childCell->GetBoundingBox().contains(entityBox))
            {
                curCell = childCell;
                break;
            }
        }
        // check for loop fallthrough: this means that the current cell either has
        // no children, or that none of the children completely contains the entity
    }
    while (cellIndex != numCells);

    return curCell.get_unsafe();
}

//------------------------------------------------------------------------------
/**
    Insert a dynamic graphics entity into the cell tree. The entity
    will correctly be inserted into the smallest enclosing cell in the tree.
    The cell may not be currently attached to a cell, the refcount of the
    entity will be incremented.

    @param  entity      pointer to a graphics entity
*/
VisCell* 
VisCell::InsertEntity(const GPtr<VisEntity>& entity)
{
	VisCell* cell = this->FindEntityContainmentCell(entity);
    cell->AttachEntity(entity);

    return cell;
}

//------------------------------------------------------------------------------
/**
    Recursively update visibility links. This method is called by the
    top level method CollectVisibleContexts(). 
    
    NOTE: This is the core visibility detection method and must be FAST.
*/
void 
VisCell::RecurseCollectVisibleEntities(const GPtr<ObserverContext>& observerContext, 
											  Util::Array<GPtr<VisEntity> >& visibilityEntities,  
											  Math::ClipStatus::Type clipStatus) const
{
    n_assert(observerContext.isvalid());

    // break immediately if no context of wanted type in this cell or below
    if (this->mNumEntitiesInHierarchy == 0)
    {
        return;
    }

	// if clip status unknown or clipped, get clip status of this cell against observer context
	if ((ClipStatus::Invalid == clipStatus) || (ClipStatus::Clipped == clipStatus))
	{
		const bbox& cellBox = this->GetBoundingBox();
		clipStatus = observerContext->ComputeClipStatus(cellBox);
	}

	/// BUGFIX: Cell的包围盒是固定的，没有根据包含的Entity大小而扩展，因为不能包含的Entity都移到了上一级。
	///        但对于根节点，其包围盒等于初始化时候裁剪树的大小。对于裁剪树范围外的Entity，可能会被错误裁剪
	if ( mParentCell )
	{
		// proceed depending on clip status of cell against observer context
		if (ClipStatus::Outside == clipStatus)
		{
			// cell isn't visible by observer context
			return;
		}
		else if (ClipStatus::Inside == clipStatus)
		{
			EntityList::const_iterator itor = this->mEntities.begin();
			EntityList::const_iterator end = this->mEntities.end();
			while( itor != end )
			{
				visibilityEntities.Append( *itor );
				++itor;
			}
		}
		else
		{
			EntityList::const_iterator itor = this->mEntities.begin();
			EntityList::const_iterator end = this->mEntities.end();
			while( itor != end )
			{
				if ( observerContext->ComputeClipStatus( (*itor)->GetBoundingBox() ) != ClipStatus::Outside )
				{    
					visibilityEntities.Append(*itor);
				}  
			
				++itor;
			}
		}
	}
	else
	{
		// 直接裁剪所有的Entity
		EntityList::const_iterator itor = this->mEntities.begin();
		EntityList::const_iterator end = this->mEntities.end();
		while( itor != end )
		{
			if ( observerContext->ComputeClipStatus( (*itor)->GetBoundingBox() ) != ClipStatus::Outside )
			{    
				visibilityEntities.Append(*itor);
			}  

			++itor;
		}
	}


    // recurse into child cells (if this cell is fully or partially visible)
    IndexT childIndex;
    SizeT numChildren = this->mChildCells.Size();
    for (childIndex = 0; childIndex < numChildren; ++childIndex)
    {
        this->mChildCells[childIndex]->RecurseCollectVisibleEntities(observerContext, visibilityEntities, clipStatus);
    }
}

//------------------------------------------------------------------------------
/**
    Frontend method for updating visibility links. This method
    simply calls RecurseCollectVisibleContexts() which recurses into child
    cells if necessary.
*/
void 
VisCell::QueryVisibleEntities(const GPtr<ObserverContext>& observerContext, Util::Array<GPtr<VisEntity> >& visibilityEntities  ) const
{
    this->RecurseCollectVisibleEntities(observerContext, visibilityEntities, ClipStatus::Invalid);
}

//------------------------------------------------------------------------------
/**
    Update the number of entities in hierarchy. Must be called when
    entities are added or removed from this cell.
*/
void
VisCell::UpdateNumEntitiesInHierarchy( int num)
{
    this->mNumEntitiesInHierarchy += num;
    n_assert(this->mNumEntitiesInHierarchy >= 0);

    VisCell* p = this->mParentCell.get_unsafe();

    if (p) 
	{
		do
		{
			p->mNumEntitiesInHierarchy += num;
			n_assert(p->mNumEntitiesInHierarchy >= 0);
		}
		while (0 != (p = p->mParentCell.get_unsafe()));
	}

}

} // namespace Vis
