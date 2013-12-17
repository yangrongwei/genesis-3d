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

#include "stdneb.h"
#include "GLESTypes.h"

namespace GLES
{
	using namespace RenderBase;

GLenum GLESTypes::AsGLESUsage(RenderBase::RenderResource::Usage usage, RenderBase::RenderResource::Access access)
{
	switch (usage)
	{
	case RenderResource::UsageImmutable:
		return GL_STATIC_DRAW;
	case RenderResource::UsageDynamic:
		return GL_DYNAMIC_DRAW;
		break;
	default:
		return GL_STATIC_DRAW;
	}
	
}

GLenum GLESTypes::AsGLESUsage(RenderBase::BufferData::Usage usage)
{
	switch (usage)
	{
	case BufferData::Static:
		return GL_STATIC_DRAW;

	case BufferData::Dynamic:
		return GL_DYNAMIC_DRAW;
	default:
		return GL_STATIC_DRAW;
	}
}

GLenum GLESTypes::IndexTypeAsGLESFormat(RenderBase::IndexBufferData::IndexType indexType)
{
	switch(indexType)
	{
	case RenderBase::IndexBufferData::Int16:
		return GL_UNSIGNED_SHORT;
	case RenderBase::IndexBufferData::Int32:
		return GL_UNSIGNED_INT;
	default:
		n_warning("GLESTypes::IndexTypeAsGLESFormat: Unknown Index Format");
		return GL_UNSIGNED_SHORT;
	}
}
GLenum GLESTypes::AsGLESInternalPixelFormat(RenderBase::PixelFormat::Code p)
{
	switch (p)
	{
	case PixelFormat::X8R8G8B8:
	case PixelFormat::A8R8G8B8:          return GL_RGBA;
	case PixelFormat::R8G8B8:			 return GL_RGB;
	case PixelFormat::A8:				 return GL_ALPHA;
	case PixelFormat::L8A8:				 return GL_LUMINANCE_ALPHA;
    case PixelFormat::ETC1_RGB8:
#ifdef __OSX__
            n_warning( "Unspported pixel format\n" );
            return GL_UNSIGNED_BYTE;
#else
            return GL_ETC1_RGB8_OES;
#endif
#ifdef GL_IMG_texture_compression_pvrtc
	case PixelFormat::PVRTC_RGB2:        return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
	case PixelFormat::PVRTC_RGBA2:       return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
	case PixelFormat::PVRTC_RGB4:        return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
	case PixelFormat::PVRTC_RGBA4:       return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
#else
	case PixelFormat::PVRTC_RGB2:       
	case PixelFormat::PVRTC_RGBA2:      
	case PixelFormat::PVRTC_RGB4:       
	case PixelFormat::PVRTC_RGBA4:
		n_warning(" GLESTypes::AsGLESPixelFormat: PVRTC texture is not supported on this GLES");
		return GL_RGBA;
#endif

	default:   
		n_warning(" GLESTypes::AsGLESPixelFormat: Unknown Pixel Format"); 
		return GL_RGBA;
	}
}

GLenum GLESTypes::AsGLESPixelDataType(RenderBase::PixelFormat::Code p)
{
	switch (p)
	{
	case PixelFormat::L8A8:
	case PixelFormat::A8:
	case PixelFormat::X8R8G8B8:
	case PixelFormat::A8R8G8B8:         
	case PixelFormat::R8G8B8:			return GL_UNSIGNED_BYTE;
    case PixelFormat::ETC1_RGB8:
#ifdef __OSX__
            n_warning( "Unspported pixel format\n" );
            return GL_UNSIGNED_BYTE;
#else
            return GL_ETC1_RGB8_OES;
#endif

#ifdef GL_IMG_texture_compression_pvrtc
	case PixelFormat::PVRTC_RGB2:        return GL_UNSIGNED_BYTE;
	case PixelFormat::PVRTC_RGBA2:       return GL_UNSIGNED_BYTE;
	case PixelFormat::PVRTC_RGB4:        return GL_UNSIGNED_BYTE;
	case PixelFormat::PVRTC_RGBA4:       return GL_UNSIGNED_BYTE;
#else
	case PixelFormat::PVRTC_RGB2:       
	case PixelFormat::PVRTC_RGBA2:      
	case PixelFormat::PVRTC_RGB4:       
	case PixelFormat::PVRTC_RGBA4:
		n_warning(" GLESTypes::AsGLESPixelFormat: PVRTC texture is not supported on this GLES");
		return GL_UNSIGNED_BYTE;
#endif


	default:
		n_warning(" GLESTypes::AsGLESPixelFormat: Unknown Pixel Format");
		return GL_UNSIGNED_BYTE;
	}
}

GLenum GLESTypes::AsGLESOriginPixelFormat(RenderBase::PixelFormat::Code p)
{
	switch (p)
	{
	case PixelFormat::X8R8G8B8:
	case PixelFormat::A8R8G8B8:         return GL_RGBA;
	case PixelFormat::R8G8B8:			return GL_RGB;
	case PixelFormat::A8:				return GL_ALPHA;
	case PixelFormat::L8A8:				return GL_LUMINANCE_ALPHA;
    case PixelFormat::ETC1_RGB8:
#ifdef __OSX__
            n_warning( "Unspported pixel format\n" );
            return GL_UNSIGNED_BYTE;
#else
            return GL_ETC1_RGB8_OES;
#endif
#ifdef GL_IMG_texture_compression_pvrtc
	case PixelFormat::PVRTC_RGB2:        return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
	case PixelFormat::PVRTC_RGBA2:       return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
	case PixelFormat::PVRTC_RGB4:        return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
	case PixelFormat::PVRTC_RGBA4:       return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
#else
	case PixelFormat::PVRTC_RGB2:       
	case PixelFormat::PVRTC_RGBA2:      
	case PixelFormat::PVRTC_RGB4:       
	case PixelFormat::PVRTC_RGBA4:
		n_warning(" GLESTypes::AsGLESPixelFormat: PVRTC texture is not supported on this GLES");
		return GL_RGBA;
#endif

	default:   
		n_warning(" GLESTypes::AsGLESPixelFormat: Unknown Pixel Format"); 
		return GL_RGBA;
	}

}

GLenum GLESTypes::AsGLESTextureType(RenderBase::Texture::Type t)
{
	switch(t)
	{
	case Texture::Texture2D:
		return GL_TEXTURE_2D;
	case Texture::TextureCube:
		return GL_TEXTURE_CUBE_MAP;
	default:
		n_warning("GLESTypes::AsGLESTextureType: Invalid Type\n");
		return GL_TEXTURE_2D;
	}
}

GLenum GLESTypes::AsGLESTextureType(const Util::String& type)
{
	if (type == "Texture2D")
	{
		return GL_TEXTURE_2D;
	}
	else if (type == "TextureCUBE")
	{
		return GL_TEXTURE_CUBE_MAP;
	}
	else
	{
		n_warning("GLESTypes::AsGLESTextureType: Invalid Type\n");
		return GL_TEXTURE_2D; 
	}
}

GLenum GLESTypes::AsGLESBasicType(RenderBase::VertexComponent::Format format)
{
	switch (format)
	{
	case VertexComponent::Float:
	case VertexComponent::Float2:
	case VertexComponent::Float3:
	case VertexComponent::Float4:
		return GL_FLOAT;
	case VertexComponent::Short2:
	case VertexComponent::Short4:
	case VertexComponent::Short2N:
	case VertexComponent::Short4N:
		return GL_SHORT;
	case VertexComponent::ColorBGRA:
	case VertexComponent::ColorRGBA:
	case VertexComponent::UByte4:
	case VertexComponent::UByte4N:
		return GL_UNSIGNED_BYTE;

	default:
		return 0;
	}
}

GLenum GLESTypes::AsGLESPrimitiveType(RenderBase::PrimitiveTopology::Code t)
{
	switch (t)
	{
	case PrimitiveTopology::PointList:
		return GL_POINTS;
	case PrimitiveTopology::LineList:
		return GL_LINES;
	case PrimitiveTopology::LineStrip:
		return GL_LINE_STRIP;
	case PrimitiveTopology::TriangleList:
		return GL_TRIANGLES;
	case PrimitiveTopology::TriangleStrip:
		return GL_TRIANGLE_STRIP;

	default:
		n_warning("GLTypes::AsGLPrimitiveType(): unsupported topology '%s'!", PrimitiveTopology::ToString(t).AsCharPtr());

		return GL_TRIANGLES;
	}
}

GLint GLESTypes::AsGLESSTextureAddress(RenderBase::TextureAddressMode mode)
{
	switch (mode)
	{
	case eTAMCLAMP:
		return GL_CLAMP_TO_EDGE;

	case eTAMWRAP:
		return GL_REPEAT;

	case eTAMMIRROR:
		return GL_MIRRORED_REPEAT;

	case eTAMBORDER:
		n_warning("GLES does not support GL_BORDER Address mode!");
		return GL_REPEAT;

	default:
		n_assert(false);
		return GL_REPEAT;
	}
}

GLenum GLESTypes::AsGLESBlendFactor(RenderBase::BlendFactor factor)
{
	switch (factor)
	{
	case eBFZERO:
		return GL_ZERO;

	case eBFONE:
		return GL_ONE;

	case eBFSRCALPHA:
		return GL_SRC_ALPHA;

	case eBFDSTALPHA:
		return GL_DST_ALPHA;

	case eBFINVSRCALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;

	case eBFINVDESTALPHA:
		return GL_ONE_MINUS_DST_ALPHA;

	case eBFSRCCOLOR:
		return GL_SRC_COLOR;

	case eBFDESTCOLOR:
		return GL_DST_COLOR;

	case eBFINVSRCCOLOR:
		return GL_ONE_MINUS_SRC_COLOR;

	case eBFINVDESTCOLOR:
		return GL_ONE_MINUS_DST_COLOR;

	case eBFSRCALPHASAT:
		return GL_SRC_ALPHA_SATURATE;

	default:
		n_assert(false);
		return GL_ZERO;
	}
}

GLenum GLESTypes::AsGLESBlendOperation(RenderBase::BlendOperation blendop)
{
	switch (blendop)
	{
	case eBOADD:
		return GL_FUNC_ADD;

	case eBOSUBSTRACT:
		return GL_FUNC_SUBTRACT;

	case eBOREVSUBTRACT:
		return GL_FUNC_REVERSE_SUBTRACT;

	case eBOMIN:
	case eBOMAX:
		n_warning("GLES does not support GL_MIN and GL_MAX!");
	
	default:
		return GL_FUNC_ADD;
	}
}

GLenum GLESTypes::AsGLESCompareFunction(RenderBase::CompareFunction func)
{
	switch (func)
	{
	case eCFNEVER:
		return GL_NEVER;

	case eCFALWAYS:
		return GL_ALWAYS;

	case eCFLESS:
		return GL_LESS;

	case eCFLESSEQUAL:
		return GL_LEQUAL;

	case eCFEQUAL:
		return GL_EQUAL;

	case eCFNOTEQUAL:
		return GL_NOTEQUAL;

	case eCFGREATEREQUAL:
		return GL_GEQUAL;

	case eCFGREATER:
		return GL_GREATER;

	default:
		return GL_NEVER;
	};
}

GLenum GLESTypes::AsGLESStencilOperation(RenderBase::StencilOperation so)
{
	switch (so)
	{
	case eSOKEEP:
		return GL_KEEP;

	case eSOZERO:
		return GL_ZERO;

	case eSOREPLACE:
		return GL_REPLACE;

	case eSOINCR:
		return GL_INCR;

	case eSODECR:
		return GL_DECR;

	case eSOINVERT:
		return GL_INVERT;

	case eSOINCRWRAP:
		return GL_INCR_WRAP;

	case eSODECRSAT:
		return GL_DECR_WRAP;

	default:
		return GL_KEEP;
	};
}

Util::String GLESTypes::AsGlesAttributeName(const RenderBase::VertexComponent::SemanticName& sem)
{
	switch (sem)
	{
	case VertexComponent::Position:
		return "gles_Vertex";
	case VertexComponent::TexCoord:
		return "gles_MultiTexCoord";
	case VertexComponent::Color:
		return "gles_Color";
	case VertexComponent::Normal:
		return "gles_Normal";
	case VertexComponent::Tangent:
		return "gles_TANGENT";
	case  VertexComponent::SkinWeights:
		return "xlat_attrib_blendweights";
	case VertexComponent::SkinJIndices:
		return "xlat_attrib_blendindices";

	default:
		n_error("No Matched GLES Attribute Name!");
		return "Error!";
	}
}

}