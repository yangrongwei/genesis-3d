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

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

//#include "RenderResource.h"
#include "VertexComponent.h"
#include "VertexLayout.h"
#include "BufferData.h"

namespace RenderBase
{
	class VertexBuffer : public Core::RefCounted
	{
		__DeclareSubClass(VertexBuffer,Core::RefCounted)
	public:
		
		/// destructor
		virtual ~VertexBuffer();

		/// get the vertex layout
		const GPtr<VertexLayout>& GetVertexLayout() const;

		/// get number of vertices in the buffer
		SizeT GetNumVertices() const;
		///
		SizeT GetVertexDataSize() const;

		BufferData::Usage GetUsage() const;

		///// get the vertex layout
		//void _SetVertexLayout(const GPtr<VertexLayout>& vl);

		/// get number of vertices in the buffer
		void _SetNumVertices(SizeT num);
		///
		void _SetVertexDataSize(SizeT size);

		void _SetUsage(BufferData::Usage usage);

		/// on device lost
		virtual void OnDeviceLost();
		/// on device reset
		virtual void OnDeviceReset();

	protected:
		/// constructor
		VertexBuffer();
		BufferData::Usage usage;
		SizeT numVertices;
		SizeT vertexDataSize;
		GPtr<VertexLayout> vertexLayout;
	};

	inline const GPtr<VertexLayout>&
		VertexBuffer::GetVertexLayout() const
	{
		return this->vertexLayout;
	}

	inline SizeT
		VertexBuffer::GetNumVertices() const
	{
		return this->numVertices;
	}

	inline SizeT
		VertexBuffer::GetVertexDataSize() const
	{
		return this->vertexDataSize;
	}

	inline BufferData::Usage
		VertexBuffer::GetUsage() const
	{
		return this->usage;
	}

	inline void
		VertexBuffer::_SetNumVertices(SizeT num)
	{
		this->numVertices = num;
	}

	inline void VertexBuffer::_SetVertexDataSize(SizeT size)
	{
		this->vertexDataSize = size;
	}

	inline void VertexBuffer::_SetUsage(BufferData::Usage usage)
	{
		this->usage = usage;
	}
}

#endif