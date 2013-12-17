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
#ifndef __visEntity_H__
#define __visEntity_H__


#include "core/refcounted.h"
#include "math/bbox.h"

//------------------------------------------------------------------------------
namespace Graphic
{
	class GraphicObject;
}
namespace Vis
{   
	class VisServer;
	class VisSystemBase;
	class VisCell;

	class VisEntity : public Core::RefCounted
	{
		__DeclareClass(VisEntity);
	public:
		

		static const int MAX_VIS_SYSTEM_COUNT;

		typedef Graphic::GraphicObject UserData;
		/// constructor
		VisEntity();
		/// destructor
		virtual ~VisEntity();   

		/// setup
		void Setup(const Math::bbox& box,  UserData* userData ); 

		/// update bounding box
		void UpdateBoundingBox(const Math::bbox& box);

		/// get GfxEntity	
		UserData* GetUserData(); 

		/// get BoundingBox	
		const Math::bbox& GetBoundingBox() const;  


		//void Setup(const Math::bbox& box,  void* userData ); 
		const void* GetCustomUserData() const;

		//Get the cell which contain this VisEntity
		VisCell* GetCell(IndexT orderIndex) const;

		//Set the cell which contain this VisEntity
		void SetCell(VisCell* cell, IndexT orderIndex);

	private:  
		friend class VisServer;

		UserData* mUserData;
		void* mCustomUserData;
		Math::bbox mBoundingBox;

		typedef Util::FixedArray< VisCell* > CellArray;
		CellArray mCells;	
	};

	//--------------------------------------------------------------------------------
	/** 
	*/
	inline const void* VisEntity::GetCustomUserData() const
	{
		return this->mCustomUserData;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	VisEntity::UserData* 
	VisEntity::GetUserData()
	{
		return this->mUserData;        
	}        

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Math::bbox& 
	VisEntity::GetBoundingBox() const
	{
		return this->mBoundingBox;        
	}
	//------------------------------------------------------------------------
	//Get the cell which contain this VisEntity
	inline 
	VisCell* 
	VisEntity::GetCell(IndexT orderIndex) const
	{
		return mCells[orderIndex];
	}

	//Set the cell which contain this VisEntity
	inline 
	void 
	VisEntity::SetCell(VisCell* cell,IndexT orderIndex)
	{
		mCells[orderIndex] = cell;
	}

} // namespace Vis
//------------------------------------------------------------------------------





#endif // __visEntity_H__



