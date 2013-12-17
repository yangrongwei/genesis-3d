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

#if WIN32

#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "RenderDeviceD3D9.h"
#include "VertexBufferD3D9.h"
#include "VertexLayoutD3D9.h"
#include "D3D9Types.h"

namespace D3D9
{
	__ImplementClass(VertexBufferD3D9,'VBD9',RenderBase::VertexBuffer)
	VertexBufferD3D9::VertexBufferD3D9(): m_d3d9VertexBuffer(NULL)
	{
	}

	VertexBufferD3D9::~VertexBufferD3D9()
	{
		Discard();
	}

	void VertexBufferD3D9::UpdateData(const RenderBase::DataStream& stream)
	{
		n_assert(stream.data);
		n_assert(vertexDataSize >= stream.sizeInByte);
		if (m_d3d9VertexBuffer)
		{
			void* dstPtr = 0;
			HRESULT hr = GetD3D9VertexBuffer()->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == GetUsage() ? D3DLOCK_DISCARD : 0);//D3DLOCK_NOSYSLOCKHasCpuBuffer()? D3DLOCK_DISCARD : 
			n_assert(SUCCEEDED(hr));
			n_assert(0 != dstPtr);
			Memory::CopyToGraphicsMemory(stream.data, dstPtr, stream.sizeInByte);
			hr = GetD3D9VertexBuffer()->Unlock();
			n_assert(SUCCEEDED(hr));
		}

	}

	/// on device lost
	void VertexBufferD3D9::OnDeviceLost()
	{
		if ( m_d3d9VertexBuffer )
		{
			m_d3d9VertexBuffer->Release();
			m_d3d9VertexBuffer = NULL;
		}
	}
	/// on device reset
	void VertexBufferD3D9::OnDeviceReset()
	{
		if (m_d3d9VertexBuffer)
		{
			return;
		}
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		// create a d3d9 vertex buffer object
		DWORD d3dVertexBufferSize = GetNumVertices() * GetVertexLayout()->GetVertexByteSize();
		D3DPOOL d3dPool     = D3D9Types::AsD3D9Pool(GetUsage());
		DWORD d3dUsage      = D3D9Types::AsD3D9Usage(GetUsage());

		IDirect3DVertexBuffer9* d3dVertexBuffer = 0;
		HRESULT hr = device->CreateVertexBuffer(d3dVertexBufferSize,        // Length
			d3dUsage,                   // Usage
			0,//D3DFVF_XYZ|D3DFVF_DIFFUSE,                          // FVF
			d3dPool,                    // Pool
			&d3dVertexBuffer,           // ppVertexBuffer
			NULL);                      // pSharedHandle
		n_assert(SUCCEEDED(hr));
		n_assert(0 != d3dVertexBuffer);
		void* dstPtr = 0;
		hr = d3dVertexBuffer->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == GetUsage() ? D3DLOCK_DISCARD : 0);
		n_assert(SUCCEEDED(hr));
		n_assert(0 != dstPtr);

		Memory::Clear(dstPtr, d3dVertexBufferSize);

		hr = d3dVertexBuffer->Unlock();

		_SetD3D9VertexBuffer(d3dVertexBuffer);
	}

	void VertexBufferD3D9::CreateVertexBuffer(const RenderBase::VertexBufferData* vbd, GPtr<VertexBufferD3D9>& out)
	{
		out = VertexBufferD3D9::Create();
		GPtr<VertexLayoutD3D9> layout = VertexLayoutD3D9::Create();
		layout->Setup(vbd->vertex.vertexComponents);
		layout->GenerateDeclarationD3D9();

		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		// create a d3d9 vertex buffer object
		DWORD d3dVertexBufferSize = vbd->vertexCount * layout->GetVertexByteSize();

		
		out->_SetVertexDataSize(d3dVertexBufferSize);
		out->_SetNumVertices(vbd->vertexCount);
		out->_SetUsage(vbd->usage);
		out->_SetD3d9VertexLayout(layout);

		D3DPOOL d3dPool     = D3D9Types::AsD3D9Pool(vbd->usage);
		DWORD d3dUsage      = D3D9Types::AsD3D9Usage(vbd->usage);


		IDirect3DVertexBuffer9* d3dVertexBuffer = 0;
		HRESULT hr = device->CreateVertexBuffer(d3dVertexBufferSize,        // Length
			d3dUsage,                   // Usage
			0,//D3DFVF_XYZ|D3DFVF_DIFFUSE,                          // FVF
			d3dPool,                    // Pool
			&d3dVertexBuffer,           // ppVertexBuffer
			NULL);                      // pSharedHandle
		n_assert(SUCCEEDED(hr));
		n_assert(0 != d3dVertexBuffer);
		out->_SetD3D9VertexBuffer(d3dVertexBuffer);

		// setup initial data if provided
		n_assert(vbd->vertexCount != 0);

		if (vbd->vertex.vertexComponentStreams.Size())
		{
			// copy vertex data to vertex buffer
			void* dstPtr = 0;
			hr = d3dVertexBuffer->Lock(0, 0, &dstPtr, RenderResource::UsageDynamic == out->GetUsage() ? D3DLOCK_DISCARD : 0);//D3DLOCK_NOSYSLOCKvb->HasCpuBuffer() ? D3DLOCK_DISCARD:
			n_assert(SUCCEEDED(hr));
			n_assert(0 != dstPtr);

			//Memory::Clear(dstPtr, d3dVertexBufferSize);
			DirectCopyVertexDataToGraphicBuffer(*vbd, dstPtr, layout->GetVertexByteSize());

			hr = d3dVertexBuffer->Unlock();
			n_assert(SUCCEEDED(hr));
		}

		PROFILER_ADDDEVICESTATEVAL(videoRam, d3dVertexBufferSize);
		PROFILER_ADDDEVICESTATEVAL(vboRam, d3dVertexBufferSize);
	}

	/// clear d3d resource
	void VertexBufferD3D9::Discard()
	{
		if ( m_d3d9VertexBuffer )
		{
			m_d3d9VertexBuffer->Release();
			m_d3d9VertexBuffer = NULL;
		}
		vertexLayout = NULL;
		PROFILER_ADDDEVICESTATEVAL(videoRam, -GetVertexDataSize());
		PROFILER_ADDDEVICESTATEVAL(vboRam, -GetVertexDataSize());
	}
}
#endif