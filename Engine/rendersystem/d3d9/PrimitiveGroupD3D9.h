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

#ifndef PRIMITIVEGROUPD3D9_H_
#define PRIMITIVEGROUPD3D9_H_

#include "VertexBufferD3D9.h"
#include "IndexBufferD3D9.h"
#include "base/PrimitiveGroup.h"
#include "RenderDeviceD3D9.h"
namespace D3D9
{
class PrimitiveGroupD3D9 : public PrimitiveGroup
{
	__DeclareSubClass(PrimitiveGroupD3D9,PrimitiveGroup)
public:
	// constructor
	PrimitiveGroupD3D9();
	// destructor
	virtual ~PrimitiveGroupD3D9();

	/// discard
	virtual void Discard();

	void DiscardVertexBuffer();

	void DiscardIndexBuffer();

	void LoadBuffers(const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd);
	/// on device lost
	virtual void OnDeviceLost();

	/// on device reset
	virtual void OnDeviceReset();

	/// get VertexBuffer
	const VertexBufferD3D9* GetVertexBuffer() const;
	/// get IndexBuffer
	const IndexBufferD3D9* GetIndexBuffer() const;

	bool IsDefaultPool();
};

	//------------------------------------------------------------------------------
	/**
	*/
	inline const VertexBufferD3D9*
		PrimitiveGroupD3D9::GetVertexBuffer() const
	{
		return static_cast<VertexBufferD3D9*>(this->m_vertexBuffer.get_unsafe());
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const IndexBufferD3D9*
		PrimitiveGroupD3D9::GetIndexBuffer() const
	{
		return static_cast<IndexBufferD3D9*>(this->m_indexBuffer.get_unsafe());
	}
	inline void PrimitiveGroupD3D9::DiscardVertexBuffer()
	{
		m_vertexBuffer = NULL;
	}

	inline void PrimitiveGroupD3D9::DiscardIndexBuffer()
	{
		m_indexBuffer = NULL;
	}
}

#endif //PRIMITIVEGROUPD3D9_H_