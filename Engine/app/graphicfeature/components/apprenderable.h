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
#ifndef _APPRENDERABLET_H_
#define _APPRENDERABLET_H_
#include "foundation/core/types.h"
#include "graphicsystem/Renderable/Renderable.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "graphicsystem/base/RenderBase.h"

namespace Graphic
{
	class Material;
}

namespace App
{

	class AppSimpleRenderable : public Graphic::Renderable
	{
	public:
		AppSimpleRenderable();
		~AppSimpleRenderable();
		void RenderForward(Graphic::RenderPassType surType, const RenderBase::PrimitiveHandle& primHandle, const Graphic::Material* custom) const;
	protected:
	};


	class AppRenderable : public Graphic::Renderable
	{
	public:
		AppRenderable();
		virtual ~AppRenderable();
		void SetRenderInfo(IndexT firstVertex, SizeT numVertex, IndexT firstIndex, SizeT numIndex);

		void RenderForward(Graphic::RenderPassType surType, const RenderBase::PrimitiveHandle& primHandle, const Graphic::Material* customed) const;

		IndexT GetFirstVertix() const;
		IndexT GetFirstIndex() const;
		SizeT GetNumVertex() const;
		SizeT GetNumIndex() const;
	protected:
		IndexT mFirstVertex;
		SizeT  mNumVertex;
		IndexT mFirstIndex;
		SizeT  mNumIndex;
	};

	inline IndexT AppRenderable::GetFirstVertix() const
	{
		return mFirstVertex;
	}
	inline IndexT AppRenderable::GetFirstIndex() const
	{
		return mFirstIndex;
	}
	inline SizeT AppRenderable::GetNumVertex() const
	{
		return mNumVertex;
	}

	inline SizeT AppRenderable::GetNumIndex() const
	{
		return mNumIndex;
	}
}

#endif //_APPRENDERABLET_H_