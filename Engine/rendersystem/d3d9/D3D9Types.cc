/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
#include "D3D9Types.h"
#include "RenderDeviceD3D9.h"
namespace D3D9
{
	using namespace RenderBase;

	//------------------------------------------------------------------------------
	/**
	*/
	D3DFORMAT
		D3D9Types::AsD3D9PixelFormat(PixelFormat::Code p)
	{
		switch (p)
		{
		case PixelFormat::X8R8G8B8:         return D3DFMT_X8R8G8B8;        
		case PixelFormat::A8R8G8B8:         return D3DFMT_A8R8G8B8;
		case PixelFormat::R5G6B5:           return D3DFMT_R5G6B5;
		case PixelFormat::A1R5G5B5:         return D3DFMT_A1R5G5B5;
		case PixelFormat::A4R4G4B4:         return D3DFMT_A4R4G4B4;
		case PixelFormat::DXT1:             return D3DFMT_DXT1;
		case PixelFormat::DXT3:             return D3DFMT_DXT3;
		case PixelFormat::DXT5:             return D3DFMT_DXT5;
		case PixelFormat::R16F:             return D3DFMT_R16F;
		case PixelFormat::G16R16F:          return D3DFMT_G16R16F;
		case PixelFormat::A16B16G16R16F:    return D3DFMT_A16B16G16R16F;
		case PixelFormat::R32F:             return D3DFMT_R32F;
		case PixelFormat::G32R32F:          return D3DFMT_G32R32F;
		case PixelFormat::A32B32G32R32F:    return D3DFMT_A32B32G32R32F;
		case PixelFormat::A8:               return D3DFMT_A8;
		case PixelFormat::L8:				return D3DFMT_L8; 
		case PixelFormat::L8A8:				return D3DFMT_A8L8; //[2012/4/12 zhongdaohuan] mygui 用到的格式
		case PixelFormat::G16R16:           return D3DFMT_G16R16;
		case PixelFormat::D24X8:            return D3DFMT_D24X8;
		case PixelFormat::D24S8:            return D3DFMT_D24S8;

		case PixelFormat::R8G8B8:           return D3DFMT_R8G8B8;

		default:                            return D3DFMT_UNKNOWN;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	PixelFormat::Code
		D3D9Types::AsGenesisPixelFormat(D3DFORMAT f)
	{
		switch (f)
		{
		case D3DFMT_X8R8G8B8:           return PixelFormat::X8R8G8B8;
		case D3DFMT_A8R8G8B8:           return PixelFormat::A8R8G8B8;
		case D3DFMT_R5G6B5:             return PixelFormat::R5G6B5;
		case D3DFMT_A1R5G5B5:           return PixelFormat::A1R5G5B5;
		case D3DFMT_A4R4G4B4:           return PixelFormat::A4R4G4B4;
		case D3DFMT_DXT1:               return PixelFormat::DXT1;
		case D3DFMT_DXT3:               return PixelFormat::DXT3;
		case D3DFMT_DXT5:               return PixelFormat::DXT5;
		case D3DFMT_R16F:               return PixelFormat::R16F;
		case D3DFMT_G16R16F:            return PixelFormat::G16R16F;
		case D3DFMT_A16B16G16R16F:      return PixelFormat::A16B16G16R16F;
		case D3DFMT_R32F:               return PixelFormat::R32F;
		case D3DFMT_G32R32F:            return PixelFormat::G32R32F;
		case D3DFMT_A32B32G32R32F:      return PixelFormat::A32B32G32R32F;
		case D3DFMT_A8:                 return PixelFormat::A8;
		case D3DFMT_G16R16:             return PixelFormat::G16R16;
		case D3DFMT_D24X8:              return PixelFormat::D24X8;
		case D3DFMT_D24S8:              return PixelFormat::D24S8;
		case D3DFMT_A8L8:				return PixelFormat::L8A8; //[2012/4/12 zhongdaohuan] mygui 用到的格式
		case D3DFMT_R8G8B8:             return PixelFormat::R8G8B8;

		default:                        return PixelFormat::InvalidPixelFormat;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DDECLTYPE
		D3D9Types::AsD3D9VertexDeclarationType(VertexComponent::Format f)
	{
		switch (f)
		{
		case VertexComponent::Float:    return D3DDECLTYPE_FLOAT1;
		case VertexComponent::Float2:   return D3DDECLTYPE_FLOAT2;
		case VertexComponent::Float3:   return D3DDECLTYPE_FLOAT3;
		case VertexComponent::Float4:   return D3DDECLTYPE_FLOAT4;
		case VertexComponent::UByte4:   return D3DDECLTYPE_UBYTE4;
		case VertexComponent::Short2:   return D3DDECLTYPE_SHORT2;
		case VertexComponent::Short4:   return D3DDECLTYPE_SHORT4;
		case VertexComponent::UByte4N:  return D3DDECLTYPE_UBYTE4N;
		case VertexComponent::Short2N:  return D3DDECLTYPE_SHORT2N;
		case VertexComponent::Short4N:  return D3DDECLTYPE_SHORT4N;
		case VertexComponent::ColorBGRA:	return D3DDECLTYPE_D3DCOLOR;
		default:                        
			n_error("D3D9Types::AsDirect3DVertexDeclarationType(): invalid input parameter!");
			return D3DDECLTYPE_UNUSED;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DDECLUSAGE
		D3D9Types::AsD3D9VertexDeclarationUsage(VertexComponent::SemanticName n)
	{
		switch (n)
		{
		case VertexComponent::Position:     return D3DDECLUSAGE_POSITION;
		case VertexComponent::Normal:       return D3DDECLUSAGE_NORMAL;
		case VertexComponent::Tangent:      return D3DDECLUSAGE_TANGENT;
		case VertexComponent::Binormal:     return D3DDECLUSAGE_BINORMAL;
		case VertexComponent::TexCoord:     return D3DDECLUSAGE_TEXCOORD;
		case VertexComponent::SkinWeights:  return D3DDECLUSAGE_BLENDWEIGHT;
		case VertexComponent::SkinJIndices: return D3DDECLUSAGE_BLENDINDICES;
		case VertexComponent::Color:        return D3DDECLUSAGE_COLOR;
		default:
			n_error("D3D9Types::AsDirect3DVertexDeclarationUsage(): invalid input parameter!");
			return D3DDECLUSAGE_POSITION;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DPRIMITIVETYPE
		D3D9Types::AsD3D9PrimitiveType(PrimitiveTopology::Code t)
	{
		switch (t)
		{
		case PrimitiveTopology::PointList:      return D3DPT_POINTLIST;
		case PrimitiveTopology::LineList:       return D3DPT_LINELIST;
		case PrimitiveTopology::LineStrip:      return D3DPT_LINESTRIP;
		case PrimitiveTopology::TriangleList:   return D3DPT_TRIANGLELIST;
		case PrimitiveTopology::TriangleStrip:  return D3DPT_TRIANGLESTRIP;
#if __XBOX360__
		case PrimitiveTopology::RectList:       return D3DPT_RECTLIST;
		case PrimitiveTopology::QuadList:       return D3DPT_QUADLIST;
#endif
		default:
			n_error("D3D9Types::AsDirect3DPrimitiveType(): unsupported topology '%s'!",
				PrimitiveTopology::ToString(t).AsCharPtr());
			return D3DPT_TRIANGLELIST;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DMULTISAMPLE_TYPE
		D3D9Types::AsD3D9MultiSampleType(AntiAliasQuality::Code c)
	{
		switch (c)
		{
		case AntiAliasQuality::None:    
			return D3DMULTISAMPLE_NONE;
		case AntiAliasQuality::Low:     
			return D3DMULTISAMPLE_2_SAMPLES;

#if __WIN32__
		case AntiAliasQuality::Medium:
			return D3DMULTISAMPLE_4_SAMPLES;    
		case AntiAliasQuality::High:    
			return D3DMULTISAMPLE_8_SAMPLES;    
#else   // xbox 360 only supports up to 4xAA
		case AntiAliasQuality::Medium:      
		case AntiAliasQuality::High:    
			return D3DMULTISAMPLE_4_SAMPLES;
#endif

		default:
			n_error("D3D9Types::AsD3D9MultiSampleType(): unsupported AntiAliasQuality!");
			return D3DMULTISAMPLE_NONE;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DXIMAGE_FILEFORMAT
		D3D9Types::AsD3DXImageFileFormat(ImageFileFormat::Code c)
	{
		switch (c)
		{
		case ImageFileFormat::BMP:  return D3DXIFF_BMP;
		case ImageFileFormat::JPG:  return D3DXIFF_JPG;
		case ImageFileFormat::PNG:  return D3DXIFF_PNG;
		case ImageFileFormat::DDS:  return D3DXIFF_DDS;
		default:
			n_error("D3D9Types::AsD3DXImageFileFormat(): unsupported ImageFileFormat!");
			return D3DXIFF_BMP;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	D3DPOOL
		D3D9Types::AsD3D9Pool(RenderResource::Usage usage, RenderResource::Access access)
	{
#if __WIN32__
		switch (usage)
		{
		case RenderResource::UsageImmutable:
			n_assert(RenderResource::AccessNone == access);
			return D3DPOOL_MANAGED;

		case RenderResource::UsageDynamic:
			n_assert(RenderResource::AccessWrite == access);
			return D3DPOOL_DEFAULT;

		case RenderResource::UsageCpu:
			return D3DPOOL_SYSTEMMEM;

		default:
			n_error("D3D9Util::AsD3D9Pool(): invalid usage parameter!");
			return D3DPOOL_SYSTEMMEM;
		}
#elif __XBOX360__
		// the pool flag is ignored on the Xbox360, so just return "something"
		switch (usage)
		{
		case UsageImmutable:
			n_assert(AccessNone == access);
			return D3DPOOL_SYSTEMMEM;

		case UsageDynamic:
			n_assert(AccessWrite == access);
			return D3DPOOL_SYSTEMMEM;

		case UsageCpu:
			return D3DPOOL_SYSTEMMEM;

		default:
			n_error("D3D9Util::AsD3D9Pool(): invalid usage parameter!");
			return D3DPOOL_SYSTEMMEM;
		}
#else
#error "D3D9Util::AsD3D9Pool: Unsupported platform!"
#endif
	}

	//------------------------------------------------------------------------------
	/**
	*/
	DWORD
		D3D9Types::AsD3D9Usage(RenderResource::Usage usage, RenderResource::Access access)
	{
#if __WIN32__
		switch (usage)
		{
		case RenderResource::UsageImmutable:
			n_assert( RenderResource::AccessNone == access);
			return D3DUSAGE_WRITEONLY;

		case RenderResource::UsageDynamic:
			n_assert(RenderResource::AccessWrite == access);
			return D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;

		case RenderResource::UsageCpu:
			return D3DUSAGE_DYNAMIC;

		default:
			n_error("D3D9Util::AsD3D9Usage(): invalid usage parameter!");
			return D3DPOOL_SYSTEMMEM;
		}
#elif __XBOX360__
		// only CPU access is relevant on the 360
		switch (usage)
		{
		case UsageImmutable:
			n_assert(AccessNone == access);
			return 0;

		case UsageDynamic:
			n_assert(AccessWrite == access);
			return 0;

		case UsageCpu:
			return D3DUSAGE_CPU_CACHED_MEMORY;

		default:
			n_error("D3D9Util::AsD3D9Usage(): invalid usage parameter!");
			return 0;
		}
#else
#error "D3D9Util::AsD3D9Usage: Unsupported platform!"
#endif
	}
	//------------------------------------------------------------------------------
	/**
	*/
	D3DPOOL
		D3D9Types::AsD3D9Pool(BufferData::Usage usage)
	{
		switch (usage)
		{
		case BufferData::Static:
			return D3DPOOL_MANAGED;

		case BufferData::Dynamic:
			return D3DPOOL_DEFAULT;
		default:
			n_error("D3D9Util::AsD3D9Usage(): invalid usage parameter!");
			return D3DPOOL_SYSTEMMEM;
		}
	}
	//------------------------------------------------------------------------------
	/**
	*/
	DWORD
		D3D9Types::AsD3D9Usage(BufferData::Usage usage)
	{
		switch (usage)
		{
		case BufferData::Static:
			return D3DUSAGE_WRITEONLY;

		case BufferData::Dynamic:
			return D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
		default:
			n_error("D3D9Util::AsD3D9Usage(): invalid usage parameter!");
			return D3DPOOL_SYSTEMMEM;
		}
	}
	//------------------------------------------------------------------------------
	/**
	*/
	D3DFORMAT
		D3D9Types::IndexTypeAsD3D9Format(IndexBufferData::IndexType indexType)
	{
		return (IndexBufferData::Int16 == indexType) ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
	}

	DWORD D3D9Types::AsD3D9ColorMask(unsigned int mask)
	{
		unsigned int ret = 0;
		if (mask & eCOLORMASKRED)
		{
			ret |= D3DCOLORWRITEENABLE_RED;
		}
		if (mask & eCOLORMASKGREEN)
		{
			ret |= D3DCOLORWRITEENABLE_GREEN;
		}
		if (mask & eCOLORMASKBLUE)
		{
			ret |= D3DCOLORWRITEENABLE_BLUE;
		}
		if (mask & eCOLORMASKALPHA)
		{
			ret |= D3DCOLORWRITEENABLE_ALPHA;
		}
		return ret;
	}

	D3DBLENDOP D3D9Types::AsD3D9BlendOperation(BlendOperation blendop)
	{
		switch (blendop)
		{
		case eBOADD:
			return D3DBLENDOP_ADD;

		case eBOSUBSTRACT:
			return D3DBLENDOP_SUBTRACT;

		case eBOREVSUBTRACT:
			return D3DBLENDOP_REVSUBTRACT;

		case eBOMIN:
			return D3DBLENDOP_MIN;

		case eBOMAX:
			return D3DBLENDOP_MAX;

		default:
			n_assert(false);
			return D3DBLENDOP_ADD;
		}

	}

	D3DBLEND D3D9Types::AsD3D9BlendFactor(BlendFactor factor)
	{
		switch (factor)
		{
		case eBFZERO:
			return D3DBLEND_ZERO;
		case eBFONE:
			return D3DBLEND_ONE;
		case eBFSRCCOLOR:
			return D3DBLEND_SRCCOLOR;
		case eBFINVSRCCOLOR:
			return D3DBLEND_INVSRCCOLOR;
		case eBFSRCALPHA:
			return D3DBLEND_SRCALPHA;
		case eBFINVSRCALPHA:
			return D3DBLEND_INVSRCALPHA;
		case eBFDSTALPHA:
			return D3DBLEND_DESTALPHA;
		case eBFINVDESTALPHA:
			return D3DBLEND_INVDESTALPHA;
		case eBFDESTCOLOR:
			return D3DBLEND_DESTCOLOR;
		case eBFINVDESTCOLOR:
			return D3DBLEND_INVDESTCOLOR;
		case eBFSRCALPHASAT:
			return D3DBLEND_SRCALPHASAT;

		default:
			n_assert(false);
			return D3DBLEND_ZERO;
		}
	}

	D3DCMPFUNC D3D9Types::AsD3D9CompareFunction(CompareFunction func)
	{
		switch (func)
		{
		case eCFNEVER:
			return D3DCMP_NEVER;
		case eCFLESS:
			return D3DCMP_LESS;
		case eCFEQUAL:
			return D3DCMP_EQUAL;
		case eCFLESSEQUAL:
			return D3DCMP_LESSEQUAL;
		case eCFGREATER:
			return D3DCMP_GREATER;
		case eCFNOTEQUAL:
			return D3DCMP_NOTEQUAL;
		case eCFGREATEREQUAL:
			return D3DCMP_GREATEREQUAL;
		case eCFALWAYS:
			return D3DCMP_ALWAYS;

		default:
			n_assert(false);
			return D3DCMP_NEVER;
		};
	}

	D3DSTENCILOP D3D9Types::AsD3D9StencilOperation(StencilOperation so)
	{
		switch (so)
		{
		case eSOKEEP:
			return D3DSTENCILOP_KEEP;
		case eSOZERO:
			return D3DSTENCILOP_ZERO;
		case eSOREPLACE:
			return D3DSTENCILOP_REPLACE;
		case eSOINCRWRAP:
			return D3DSTENCILOP_INCRSAT;
		case eSODECRSAT:
			return D3DSTENCILOP_DECRSAT;
		case eSOINVERT:
			return D3DSTENCILOP_INVERT;
		case eSOINCR:
			return D3DSTENCILOP_INCR;
		case eSODECR:
			return D3DSTENCILOP_DECR;
		default:
			n_assert(false);
			return D3DSTENCILOP_KEEP;
		};
	}

	D3DCULL D3D9Types::AsD3D9CullMode(CullMode mode)
	{
		switch (mode)
		{
		case eCMNONE:
			return D3DCULL_NONE;

		case eCMFRONT:
			return D3DCULL_CCW;

		case eCMBACK:
			return D3DCULL_CW;

		default:
			n_assert(false);
			return D3DCULL_NONE;
		}

	}

	D3DFILLMODE D3D9Types::AsD3D9FillMode(FillMode mode)
	{
		switch (mode)
		{
		case eFMPOINT:
			return D3DFILL_POINT;

		case eFMWIREFRAME:
			return D3DFILL_WIREFRAME;

		case eFMSOLID:
			return D3DFILL_SOLID;

		default:
			n_assert(false);
			return D3DFILL_SOLID;
		}
	}

	D3DTEXTUREADDRESS D3D9Types::AsD3D9TextureAddress(TextureAddressMode mode)
	{
		switch (mode)
		{
		case eTAMCLAMP:
			return D3DTADDRESS_CLAMP;

		case eTAMWRAP:
			return D3DTADDRESS_WRAP;

		case eTAMMIRROR:
			return D3DTADDRESS_MIRROR;

		case eTAMBORDER:
			return D3DTADDRESS_BORDER;

		default:
			n_assert(false);
			return D3DTADDRESS_CLAMP;
		}
	}

	HRESULT	D3D9Types::AsD3D9TextureFilter(int texUnit,TextureFilter filter)
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		n_assert(device != NULL);
		HRESULT hr = S_OK;
		switch (filter)
		{
		case eTFPOINT:
			hr = device->SetSamplerState(texUnit,D3DSAMP_MINFILTER,D3DTEXF_POINT);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MAGFILTER,D3DTEXF_POINT);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MIPFILTER,D3DTEXF_POINT);
			n_assert(SUCCEEDED(hr));
			return hr;

		case eTFLINEAR:
			hr = device->SetSamplerState(texUnit,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
			n_assert(SUCCEEDED(hr));
			return hr;

		case eTFANISOTROPIC:
			hr = device->SetSamplerState(texUnit,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);
			n_assert(SUCCEEDED(hr));
			hr = device->SetSamplerState(texUnit,D3DSAMP_MIPFILTER,D3DTEXF_ANISOTROPIC);
			n_assert(SUCCEEDED(hr));
			return hr;

		default:
			n_error("SetSamplerState Error : must have a valid filter!");
			hr = S_FALSE;
			return hr;
		}
	}

} // namespace D3D9

#endif