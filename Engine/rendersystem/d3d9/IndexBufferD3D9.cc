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

#if WIN32


#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "IndexBufferD3D9.h"
#include "RenderDeviceD3D9.h"
#include "D3D9Types.h"
namespace D3D9
{
	__ImplementClass(IndexBufferD3D9,'IBD9',RenderBase::IndexBuffer)
	IndexBufferD3D9::IndexBufferD3D9():m_d3d9IndexBuffer(NULL)
	{

	}

	IndexBufferD3D9::~IndexBufferD3D9()
	{
		Discard();
	}

	void IndexBufferD3D9::UpdateData(const RenderBase::DataStream& stream)
	{
		n_assert(stream.data);
		n_assert(indexDataSize >= stream.sizeInByte);
		if (m_d3d9IndexBuffer)
		{
			void* dstPtr = 0;
			HRESULT hr = GetD3D9IndexBuffer()->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == GetUsage() ? D3DLOCK_DISCARD : 0);//D3DLOCK_NOSYSLOCKHasCpuBuffer()? D3DLOCK_DISCARD : 
			n_assert(SUCCEEDED(hr));
			n_assert(0 != dstPtr);
			Memory::CopyToGraphicsMemory(stream.data, dstPtr, stream.sizeInByte);
			hr = GetD3D9IndexBuffer()->Unlock();
			n_assert(SUCCEEDED(hr));
		}
	}

	void IndexBufferD3D9::CreateIndexBuffer(const RenderBase::IndexBufferData* ibd, GPtr<IndexBufferD3D9>& out)
	{
		out = IndexBufferD3D9::Create();

		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		// create a d3d9 index buffer object
		DWORD d3dIndexBufferSize = IndexBufferData::SizeOf(ibd->indexType) * ibd->indexCount;
		
		out->_SetIndexDataSize(d3dIndexBufferSize);
		out->_SetNumIndices(ibd->indexCount);
		out->_SetIndexType(ibd->indexType);
		out->_SetUsage(ibd->usage);

		D3DPOOL d3dPool     = D3D9Types::AsD3D9Pool(ibd->usage);
		DWORD d3dUsage      = D3D9Types::AsD3D9Usage(ibd->usage);

		D3DFORMAT d3dFormat = D3D9Types::IndexTypeAsD3D9Format(ibd->indexType);
		IDirect3DIndexBuffer9* d3dIndexBuffer = 0;
		HRESULT hr = device->CreateIndexBuffer(d3dIndexBufferSize,     // Length,
			d3dUsage,                // Usage
			d3dFormat,               // Format
			d3dPool,                 // Pool
			&d3dIndexBuffer,         // ppIndexBuffer
			NULL);                   // pSharedHandle
		n_assert(SUCCEEDED(hr));
		n_assert(0 != d3dIndexBuffer);
		out->SetD3D9IndexBuffer(d3dIndexBuffer);

		// setup initial data if provided
		if (NULL != ibd->stream)
		{
			// copy data to d3d9 index buffer
			void* dstPtr = 0;
			hr = d3dIndexBuffer->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == out->GetUsage() ? D3DLOCK_DISCARD : 0);
			n_assert(SUCCEEDED(hr));
			n_assert(0 != dstPtr);
			Memory::CopyToGraphicsMemory(ibd->stream, dstPtr, d3dIndexBufferSize);
			hr = d3dIndexBuffer->Unlock();
			n_assert(SUCCEEDED(hr));		

		}
		PROFILER_ADDDEVICESTATEVAL(videoRam, d3dIndexBufferSize);
		PROFILER_ADDDEVICESTATEVAL(vboRam, d3dIndexBufferSize);
	}

	void IndexBufferD3D9::Discard()
	{
		if ( m_d3d9IndexBuffer )
		{
			m_d3d9IndexBuffer->Release();
			m_d3d9IndexBuffer = NULL;
		}
		PROFILER_ADDDEVICESTATEVAL(videoRam, -GetIndexDataSize());
		PROFILER_ADDDEVICESTATEVAL(vboRam, -GetIndexDataSize());
	}

	/// on device lost
	void IndexBufferD3D9::OnDeviceLost()
	{
		Discard();
	}
	/// on device reset
	void IndexBufferD3D9::OnDeviceReset()
	{
		n_assert(NULL == m_d3d9IndexBuffer);
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		DWORD d3dIndexBufferSize = GetIndexDataSize();
		D3DPOOL d3dPool     = D3D9Types::AsD3D9Pool(GetUsage());
		DWORD d3dUsage      = D3D9Types::AsD3D9Usage(GetUsage());
		D3DFORMAT d3dFormat = D3D9Types::IndexTypeAsD3D9Format(GetIndexType());
		IDirect3DIndexBuffer9* d3dIndexBuffer = 0;
		HRESULT hr = device->CreateIndexBuffer(d3dIndexBufferSize,     // Length,
			d3dUsage,                // Usage
			d3dFormat,               // Format
			d3dPool,                 // Pool
			&d3dIndexBuffer,         // ppIndexBuffer
			NULL);                   // pSharedHandle
		n_assert(SUCCEEDED(hr));
		n_assert(0 != d3dIndexBuffer);		
		void* dstPtr = 0;
		hr = d3dIndexBuffer->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == GetUsage() ? D3DLOCK_DISCARD : 0);
		n_assert(SUCCEEDED(hr));
		n_assert(0 != dstPtr);
		Memory::Clear(dstPtr, d3dIndexBufferSize);
		d3dIndexBuffer->Unlock();
		SetD3D9IndexBuffer(d3dIndexBuffer);

	}
}
#endif