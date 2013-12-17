/****************************************************************************
Copyright (C) 2007 Radon Labs GmbH
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
#ifndef INDEXBUFFERD3D9_H_
#define INDEXBUFFERD3D9_H_
#include "base/IndexBuffer.h"
#include "base/BufferData.h"

namespace D3D9
{
	class IndexBufferD3D9 : public RenderBase::IndexBuffer
	{
		__DeclareSubClass(IndexBufferD3D9,RenderBase::IndexBuffer)
	public:
		/// constructor
		IndexBufferD3D9();
		/// destructor
		virtual ~IndexBufferD3D9();

		/// set d3d9 Index buffer pointer
		void SetD3D9IndexBuffer(IDirect3DIndexBuffer9* ptr);
		/// get pointer to d3d9 Index buffer object
		IDirect3DIndexBuffer9* GetD3D9IndexBuffer() const;
		/// on device lost
		virtual void OnDeviceLost();
		/// on device reset
		virtual void OnDeviceReset();
		/// clear d3d resource
		void Discard();

		void UpdateData(const RenderBase::DataStream& stream);

		static void CreateIndexBuffer(const RenderBase::IndexBufferData* ibd, GPtr<IndexBufferD3D9>& out);
	private:
		IDirect3DIndexBuffer9* m_d3d9IndexBuffer;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		IndexBufferD3D9::SetD3D9IndexBuffer(IDirect3DIndexBuffer9* ptr)
	{
		n_assert(0 != ptr);
		n_assert(0 == this->m_d3d9IndexBuffer);
		this->m_d3d9IndexBuffer = ptr;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DIndexBuffer9*
		IndexBufferD3D9::GetD3D9IndexBuffer() const
	{
		n_assert(0 != this->m_d3d9IndexBuffer);
		return this->m_d3d9IndexBuffer;
	}

}
#endif