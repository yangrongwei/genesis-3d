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

#pragma once
#ifndef D3D9TYPES_H_
#define D3D9TYPES_H_
#include "core/types.h"
#include "base/RenderDeviceTypes.h"
#include "base/RenderResource.h"
#include "base/VertexComponent.h"
//#include "base/IndexBuffer.h"
#include "base/BufferData.h"


//------------------------------------------------------------------------------
namespace D3D9
{

	using namespace RenderBase;
	class D3D9Types
	{
	public:
		/// convert Nebula pixel format to D3D9 pixel format
		static D3DFORMAT AsD3D9PixelFormat(PixelFormat::Code p);
		/// convert Direct3D to Nebula pixel format
		static PixelFormat::Code AsGenesisPixelFormat(D3DFORMAT f);
		/// convert vertex component type to D3D9 declaration type
		static D3DDECLTYPE AsD3D9VertexDeclarationType(VertexComponent::Format f);
		/// convert vertex component semantic name as D3D9 declaration usage
		static D3DDECLUSAGE AsD3D9VertexDeclarationUsage(VertexComponent::SemanticName n);
		/// convert primitive topology to D3D
		static D3DPRIMITIVETYPE AsD3D9PrimitiveType(PrimitiveTopology::Code t);
		/// convert antialias quality to D3D multisample type
		static D3DMULTISAMPLE_TYPE AsD3D9MultiSampleType(AntiAliasQuality::Code c);
		/// convert image file format to D3DX file format
		static D3DXIMAGE_FILEFORMAT AsD3DXImageFileFormat(ImageFileFormat::Code c);
		/// convert resource usage/access flag pair into D3D9 pool
		static D3DPOOL AsD3D9Pool(RenderResource::Usage usage, RenderResource::Access access);
		/// convert resource usage/access flag pair into D3D9 usage flags
		static DWORD AsD3D9Usage(RenderResource::Usage usage, RenderResource::Access access);

		static D3DPOOL AsD3D9Pool(BufferData::Usage usage);
		static DWORD AsD3D9Usage(BufferData::Usage usage);
		/// convert index type to D3DFORMAT
		static D3DFORMAT IndexTypeAsD3D9Format(IndexBufferData::IndexType indexType);

		static DWORD AsD3D9ColorMask(unsigned int mask);


		static D3DBLEND AsD3D9BlendFactor(BlendFactor factor);
		static D3DBLENDOP AsD3D9BlendOperation(BlendOperation blendop);
		static D3DSTENCILOP AsD3D9StencilOperation(StencilOperation so);
		static D3DCMPFUNC AsD3D9CompareFunction(CompareFunction func);
		static D3DCULL AsD3D9CullMode(CullMode mode);
		static D3DFILLMODE AsD3D9FillMode(FillMode mode);
		static D3DTEXTUREADDRESS AsD3D9TextureAddress(TextureAddressMode mode);
		static HRESULT	AsD3D9TextureFilter(int texUnit,TextureFilter filter);
	};

} // namespace D3D9
//------------------------------------------------------------------------------
#endif