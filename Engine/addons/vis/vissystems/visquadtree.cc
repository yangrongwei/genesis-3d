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
#include "vis/vissystems/visquadtree.h"
#include "threading/thread.h"
#include "jobs/jobdatadesc.h"
#include "jobs/jobuniformdesc.h"

namespace Vis
{
    __ImplementClass(Vis::VisQuadtree, 'VIQT', Vis::VisSystemBase);

using namespace Jobs;
using namespace Util;
using namespace Math;
using namespace Threading;

// job function declaration
#if __PS3__
extern "C" {
    extern const char _binary_jqjob_render_visquadtreejobfunc_ps3_bin_start[];
    extern const char _binary_jqjob_render_visquadtreejobfunc_ps3_bin_size[];
}
#else
extern void VisCellJobFunc(const JobFuncContext& ctx);
#endif
//------------------------------------------------------------------------------
/**
*/
VisQuadtree::VisQuadtree()
	: mNumCellsBuilt(0)
    , mQuadTreeDepth(0)
	, mNumEntity(0)
{
}

//------------------------------------------------------------------------------
/**
*/
VisQuadtree::~VisQuadtree()
{
}

//------------------------------------------------------------------------------
/**
*/
void
VisQuadtree::Open(IndexT orderIndex)
{    
    // this visibility system have to come first, before any other
    n_assert2(orderIndex == 0, "VisibilityQuadtree have to come first, before any other!");

    this->mQuadTree.Setup(this->mQuadTreeBox, this->mQuadTreeDepth);
    this->mNumCellsBuilt = 0;
    this->mRootCell = this->CreateQuadTreeCell(0, 0, 0, 0);

    VisSystemBase::Open(orderIndex);
}

//------------------------------------------------------------------------------
/**
*/
void
VisQuadtree::Close()
{           
    this->mRootCell->OnRemove();
    this->mRootCell = 0;
	mNumEntity = 0;
	mNumCellsBuilt = 0;
	mQuadTreeDepth = 0;
    VisSystemBase::Close();        
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuadtree::InsertVisEntity(const GPtr<VisEntity>& entityVis)
{
	VisCell* cell = entityVis->GetCell( OrderIndex() );
	if ( cell )
	{
		n_warning("VisibilityQuadtree::InsertvisEntity: repeat add entity\n");
		return;
	}

    cell = this->mRootCell->InsertEntity(entityVis);
	n_assert( cell );
	entityVis->SetCell( cell, OrderIndex() );
	++mNumEntity;
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuadtree::RemoveVisEntity(const GPtr<VisEntity>& entityVis)
{
	VisCell* cell = entityVis->GetCell( OrderIndex() );
	if ( !cell )
	{
		n_warning("VisibilityQuadtree::RemovevisEntity: not find\n");
		return;
	}

	cell->RemoveEntity(entityVis);
	entityVis->SetCell( NULL, OrderIndex() );
	--mNumEntity;
}
//------------------------------------------------------------------------
SizeT 
VisQuadtree::GetNumEntity()
{
	return mNumEntity;
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuadtree::UpdateVisEntity(const GPtr<VisEntity>& entityVis)
{       
	VisCell* oldCell = entityVis->GetCell( OrderIndex() );

	if ( !oldCell  )
	{
		n_warning("VisibilityQuadtree::UpdatevisEntity: not find\n");
		return;
	}

    VisCell* newCell = oldCell->FindEntityContainmentCell(entityVis);
    if (oldCell != newCell)
    {                                      
        oldCell->RemoveEntity(entityVis);
        newCell->AttachEntity(entityVis);

		entityVis->SetCell(newCell,OrderIndex() );
    }
}

//------------------------------------------------------------------------------
/**
*/
GPtr<VisCell> 
VisQuadtree::CreateQuadTreeCell(VisCell* parentCell, uchar curLevel, ushort curCol, ushort curRow)
{
    // create a new cell
    GPtr<VisCell> cell = VisCell::Create();
    int nodeIndex = this->mQuadTree.GetNodeIndex(curLevel, curCol, curRow);
    const QuadTree<CellInfo>::Node& node = this->mQuadTree.GetNodeByIndex(nodeIndex);
    cell->SetBoundingBox(node.GetBoundingBox());        
    this->mNumCellsBuilt++;

    // create child cells
    uchar childLevel = curLevel + 1;
    if (childLevel < this->mQuadTree.GetDepth())
    {        
        ushort i;
        for (i = 0; i < 4; i++)
        {
            ushort childCol = 2 * curCol + (i & 1);
            ushort childRow = 2 * curRow + ((i & 2) >> 1);
            GPtr<VisCell> childCell = this->CreateQuadTreeCell(cell, childLevel, childCol, childRow);
            cell->AttachChildCell(childCell);
        }        
    }
    return cell;
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuadtree::OnRenderDebug()
{
    // render boxes for cells
    float alpha = 0.2f / this->mQuadTreeDepth;
    float4 color(1, 1, 1, alpha);
    this->RenderCell(this->mRootCell, color);
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuadtree::RenderCell(const GPtr<VisCell>& cell, const Math::float4& color)
{
}

//------------------------------------------------------------------------------
/**
对一个系统的查询，生成一个job，不进行切片。只在一个线程中执行完毕
对VisibilityQuadtree的查询保证是只读的。
因为并行查询是没有异步，所以目前无需加锁。
*/
GPtr<Jobs::Job> 
VisQuadtree::CreateVisJob(const GPtr<ObserverContext>& observer, Util::Array<GPtr<VisEntity> >& outEntitiyArray )
{   
	n_assert( observer.isvalid() );

    // create new job           
    GPtr<Jobs::Job> visibilityJob = Jobs::Job::Create();

#ifdef __WIN32__
    // input data for job  
    // function
    JobFuncDesc jobFunction(VisCellJobFunc);        
    // uniform data     
    
	// JobUniformDesc传输 mRootCell的指针
	JobUniformDesc uniformData( mRootCell.get_unsafe(), sizeof(void*), 0 );

	// inputData用来传输observer的指针。
	// todo: 一个observer一个job，或许改成一个observer一个job Slice，会提高性能。需要实验
    JobDataDesc inputData(observer.get_unsafe(), sizeof(void*), sizeof(void*) );

    // outputData 用来传输查询结果的数组
    JobDataDesc outputData( &outEntitiyArray, sizeof(void*), sizeof(void*) );
    
	// setup job with data
    visibilityJob->Setup(uniformData, inputData, outputData, jobFunction);
#else
	mRootCell->QueryVisibleEntities(observer, outEntitiyArray);
#endif    

    return visibilityJob;
}
} // namespace Vis
