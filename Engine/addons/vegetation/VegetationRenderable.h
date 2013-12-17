/****************************************************************************
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

#ifndef _VEGETATIONRENDERABLE_H_
#define _VEGETATIONRENDERABLE_H_
#include "graphicsystem/Renderable/Renderable.h"
#include "foundation/core/types.h"
namespace Vegetation
{
	class VegetationRenderable : public Graphic::Renderable
	{
	public:
		VegetationRenderable();
		virtual ~VegetationRenderable();
		void Set(IndexT matIndex , 
			IndexT firstVertex = 0,
			SizeT numVertex = 0,
			IndexT FirstIndex = 0,
			SizeT numIndex = 0 );

		IndexT GetFirstVertix() const;
		IndexT GetFirstIndex() const;
		SizeT GetNumVertex() const;
		SizeT GetNumIndex() const;
	protected:
		IndexT	mMatIndex;
		IndexT	mFirstVertex;
		SizeT	mNumVertex;
		IndexT	mFirstIndex;
		SizeT	mNumIndex;

	};

	inline IndexT VegetationRenderable::GetFirstVertix() const
	{
		return mFirstVertex;
	}
	inline IndexT VegetationRenderable::GetFirstIndex() const
	{
		return mFirstIndex;
	}
	inline SizeT VegetationRenderable::GetNumVertex() const
	{
		return mNumVertex;
	}

	inline SizeT VegetationRenderable::GetNumIndex() const
	{
		return mNumIndex;
	}
}


#endif //_VEGETATIONRENDERABLE_H_