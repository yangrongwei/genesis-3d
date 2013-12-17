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
#ifndef QUADRENDERABLE_H_
#define QUADRENDERABLE_H_

#include "Renderable.h"
#include "Camera/Camera.h"
#include "foundation/util/scriptbind.h"

namespace App
{
	class RenderComponent;
}
namespace RenderBase
{
	class VertexBuffer;
}

namespace Graphic
{

	class Camera;
	class QuadRenderable : public Core::RefCounted
	{
		__DeclareClass(QuadRenderable)
	public:

		QuadRenderable();
		virtual ~QuadRenderable();
		virtual void Setup(int width, int height);
		void Discard();
		const RenderBase::PrimitiveHandle& GetQuadHandle() const;

		SizeT GetWidth() const;

		SizeT GetHeight() const;

	private:
		RenderBase::PrimitiveHandle m_handle;
		SizeT m_Width;
		SizeT m_Height;
	};

	inline const RenderBase::PrimitiveHandle& QuadRenderable::GetQuadHandle() const
	{
		return m_handle;
	}

	inline SizeT QuadRenderable::GetWidth() const
	{
		return m_Width;
	}

	inline SizeT QuadRenderable::GetHeight() const
	{
		return m_Height;
	}
}

#endif