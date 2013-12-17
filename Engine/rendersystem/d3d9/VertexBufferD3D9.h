/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef VERTEXBUFFERD3D9_H_
#define VERTEXBUFFERD3D9_H_

#include "base/VertexBuffer.h"
#include "base/BufferData.h"
#include "d3d9/VertexLayoutD3D9.h"

namespace D3D9
{
	class VertexBufferD3D9 : public RenderBase::VertexBuffer
	{
		__DeclareSubClass(VertexBufferD3D9,RenderBase::VertexBuffer)
	public:
		/// constructor
		VertexBufferD3D9();
		/// destructor
		virtual ~VertexBufferD3D9();

		/// clear d3d resource
		void Discard();

		/// get pointer to d3d9 vertex buffer object
		IDirect3DVertexBuffer9* GetD3D9VertexBuffer() const;
		/// on device lost
		virtual void OnDeviceLost();
		/// on device reset
		virtual void OnDeviceReset();

		void UpdateData(const RenderBase::DataStream& stream);

		static void CreateVertexBuffer(const RenderBase::VertexBufferData* vbd, GPtr<VertexBufferD3D9>& out);
	private:		
		/// set d3d9 vertex buffer pointer
		void _SetD3D9VertexBuffer(IDirect3DVertexBuffer9* ptr);
		void _SetD3d9VertexLayout(GPtr<VertexLayoutD3D9>& vertexLayout);
		IDirect3DVertexBuffer9* m_d3d9VertexBuffer;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		VertexBufferD3D9::_SetD3D9VertexBuffer(IDirect3DVertexBuffer9* ptr)
	{
		n_assert(0 != ptr);
		n_assert(0 == this->m_d3d9VertexBuffer);
		this->m_d3d9VertexBuffer = ptr;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DVertexBuffer9*
		VertexBufferD3D9::GetD3D9VertexBuffer() const
	{
		n_assert(0 != this->m_d3d9VertexBuffer);
		return this->m_d3d9VertexBuffer;
	}

	inline void
		VertexBufferD3D9::_SetD3d9VertexLayout(GPtr<VertexLayoutD3D9>& vertexLayout)
	{
		this->vertexLayout = vertexLayout;
	}

}

#endif//VERTEXBUFFER_H_