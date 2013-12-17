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
#ifndef __visquadtree_H__
#define __visquadtree_H__


#include "vis/vissystems/vissystembase.h"
#include "vis/vissystems/viscell.h"
#include "util/quadtree.h"
#include "jobs/job.h"

//------------------------------------------------------------------------------
namespace Vis
{    
	class VisQuadtree : public VisSystemBase
	{
		__DeclareClass(VisQuadtree);
	public:      
		struct CellInfo 
		{
			SizeT numEntitiesInHierarchy;
			IndexT entityInfoStartIndex;
			IndexT numEntitiesInCell;
		};

		struct EntityInfo
		{
			Math::bbox entityBox;        
			VisEntity* entityPtr;
		};

		/// constructor
		VisQuadtree();
		/// destructor
		virtual ~VisQuadtree();

		/// set quad tree depth and boudning box
		void SetQuadTreeSettings(uchar depth, const Math::bbox& worldBBox);
		/// open the graphics server
		virtual void Open(IndexT orderIndex);
		/// close the graphics server
		virtual void Close(void);

		/// @VisibilitySystemBase::InsertVisEntity insert entity visibility
		virtual void InsertVisEntity(const GPtr<VisEntity>& entityVis);
		/// @VisibilitySystemBase::RemoveVisEntity remove entity visibility
		virtual void RemoveVisEntity(const GPtr<VisEntity>& entityVis);
		/// @VisibilitySystemBase::UpdateVisEntity update entity visibility
		virtual void UpdateVisEntity(const GPtr<VisEntity>& entityVis);
		/// @VisibilitySystemBase::GetNumEntity get the num of entity in visibility system
		virtual SizeT GetNumEntity();

		/// @VisibilitySystemBase::CreateVisibilityJob attach visibility job to port
		virtual GPtr<Jobs::Job> CreateVisJob( const GPtr<ObserverContext>& observer, Util::Array<GPtr<VisEntity> >& outEntitiyArray );
		/// @VisibilitySystemBase::OnRenderDebug render debug visualizations
		virtual void OnRenderDebug(void);

	private:
		/// create a quad tree and its children, recursively
		GPtr<VisCell> CreateQuadTreeCell(VisCell* parentCell, uchar curLevel, ushort curCol, ushort curRow);
		/// render quadtree cell
		void RenderCell(const GPtr<VisCell>& cell, const Math::float4& color);

		int mNumCellsBuilt;
		uchar mQuadTreeDepth;
		Math::bbox mQuadTreeBox;
		GPtr<VisCell> mRootCell;	
		SizeT mNumEntity;

		Util::QuadTree<CellInfo> mQuadTree; //	Nebula3里面用来做双缓冲的。现在不需要双缓冲，暂时继续用来辅助树的构造。以后再优化
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	VisQuadtree::SetQuadTreeSettings(uchar depth, const Math::bbox& worldBox)
	{
		this->mQuadTreeDepth = depth;
		this->mQuadTreeBox = worldBox;
	}
} // namespace Vis
//------------------------------------------------------------------------------





#endif // __visquadtree_H__

