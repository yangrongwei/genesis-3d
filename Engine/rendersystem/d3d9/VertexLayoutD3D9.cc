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
#include "VertexLayoutD3D9.h"
#include "RenderDeviceD3D9.h"
#include "D3D9Types.h"
#include "rendersystem/base/BufferData.h"
namespace D3D9
{
	using namespace RenderBase;
	__ImplementClass(VertexLayoutD3D9,'IDD9',RenderBase::VertexLayout)
		VertexLayoutD3D9::VertexLayoutD3D9():d3d9VertexDeclaration(NULL)
	{

	}

	VertexLayoutD3D9::~VertexLayoutD3D9()
	{
		if ( d3d9VertexDeclaration )
		{
			d3d9VertexDeclaration->Release();
			d3d9VertexDeclaration = NULL;
		}
	}

	void VertexLayoutD3D9::GenerateDeclarationD3D9()
	{
		n_assert(GetVertexComponents().Size() > 0);

		components = GetVertexComponents();
		// create a D3D9 vertex declaration object
		const SizeT maxElements = 32;
		n_assert(this->components.Size() < maxElements);
		D3DVERTEXELEMENT9 decl[maxElements] = { 0 };
		IndexT curOffset[RenderBase::MaxNumVertexStreams] = { 0 };
		IndexT compIndex;
		for (compIndex = 0; compIndex < this->components.Size(); compIndex++)
		{
			const VertexComponent& component = this->components[compIndex];
			WORD streamIndex = (WORD) component.GetStreamIndex();
			n_assert(streamIndex < RenderBase::MaxNumVertexStreams);
			decl[compIndex].Stream = streamIndex;
			decl[compIndex].Offset = (WORD) curOffset[streamIndex];
			decl[compIndex].Type   = D3D9Types::AsD3D9VertexDeclarationType(component.GetFormat());
			decl[compIndex].Method = D3DDECLMETHOD_DEFAULT;
			decl[compIndex].Usage  = (BYTE) D3D9Types::AsD3D9VertexDeclarationUsage(component.GetSemanticName());
			decl[compIndex].UsageIndex = (BYTE) component.GetSemanticIndex();
			curOffset[streamIndex] += component.GetByteSize();
		}
		decl[compIndex].Stream = 0xff;
		decl[compIndex].Type = (WORD) D3DDECLTYPE_UNUSED;

		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		IDirect3DVertexDeclaration9* d3d9VertexDeclaration;
		HRESULT hr = device->CreateVertexDeclaration(decl, &d3d9VertexDeclaration);
		n_assert(SUCCEEDED(hr));
		n_assert(0 != d3d9VertexDeclaration);
		SetD3D9VertexDeclaration(d3d9VertexDeclaration);
	}
}
#endif