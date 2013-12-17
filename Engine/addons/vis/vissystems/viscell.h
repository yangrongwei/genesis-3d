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
#ifndef __viscell_H__
#define __viscell_H__

#include "core/refcounted.h"
#include "math/bbox.h"
#include "vis/visentity.h"
#include "vis/observercontext.h"
#include "util/stl.h"

//------------------------------------------------------------------------------
namespace Vis
{

	class VisCell : public Core::RefCounted
	{
		__DeclareClass(VisCell);
	public:
		/// constructor
		VisCell();
		/// destructor
		virtual ~VisCell();

		/// called when attached to visibility system
		virtual void OnAttach();
		/// called when removed visibility system
		virtual void OnRemove();

		/// set the VisCell's world space bounding box
		void SetBoundingBox(const Math::bbox& box);
		/// get the VisCell's world space transform
		const Math::bbox& GetBoundingBox() const;

		/// add a child cell (only during setup phase)
		void AttachChildCell(const GPtr<VisCell>& cell);
		/// get pointer to parent cell (returns invalid pointer if this is root cell)
		const GPtr<VisCell>& GetParentCell() const;
		/// get current child cells
		const Util::Array<GPtr<VisCell> >& GetChildCells() const;

		/// insert an entity into the VisCell hierarchy, return found child cell
		VisCell* InsertEntity(const GPtr<VisEntity>& ent);
		/// attach a visibility entity to this VisCell
		void AttachEntity(const GPtr<VisEntity>& ent);
		/// remove a visibility entity from this VisCell
		void RemoveEntity(const GPtr<VisEntity>& ent);

		/// starting from this cell, find smallest containment cell in cell tree
		VisCell* FindEntityContainmentCell(const GPtr<VisEntity>& entity);

		// 得到该cell和childcell中所有entity的数量
		SizeT GetNumEntitiesInHierarchy(void) const; 

		/// recursively collect all visible entity
		void QueryVisibleEntities(const GPtr<ObserverContext>& observerContext, Util::Array<GPtr<VisEntity> >& visibilityEntities ) const;

	protected:

		/// create links between visible entities
		void RecurseCollectVisibleEntities(const GPtr<ObserverContext>& observerContext, Util::Array<GPtr<VisEntity> >& visibilityEntities,  Math::ClipStatus::Type clipStatus) const;

		void UpdateNumEntitiesInHierarchy(int num);

		GPtr<VisCell> mParentCell;
		Math::bbox mBoundingBox;
		Util::Array<GPtr<VisCell> > mChildCells;

		typedef Util::STL_list< GPtr<VisEntity> >::type EntityList;
		EntityList mEntities;
		
		SizeT mNumEntitiesInHierarchy;	//	in clude child cell. 
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	VisCell::SetBoundingBox(const Math::bbox& box)
	{
		this->mBoundingBox = box;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Math::bbox&
	VisCell::GetBoundingBox() const
	{
		return this->mBoundingBox;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const GPtr<VisCell>& 
	VisCell::GetParentCell() const
	{
		return this->mParentCell;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Util::Array<GPtr<VisCell> >& 
	VisCell::GetChildCells() const
	{
		return this->mChildCells;
	}

	//------------------------------------------------------------------------
	inline
	SizeT 
	VisCell::GetNumEntitiesInHierarchy(void) const
	{
		return mNumEntitiesInHierarchy;
	}
} // namespace InternalGraphics
//------------------------------------------------------------------------------





#endif // __viscell_H__

