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

#ifndef __GLESTypes_H__
#define __GLESTypes_H__

#include "core/types.h"
#include "base/RenderDeviceTypes.h"
#include "base/RenderResource.h"
#include "base/VertexComponent.h"
#include "base/IndexBuffer.h"
#include "base/Texture.h"
#include "OpenGLES.h"
#include "util/string.h"

namespace GLES
{
	class GLESTypes
{
public:
	/// convert Engine pixel format to OpenGL Internal pixel format
	static GLenum AsGLESInternalPixelFormat(RenderBase::PixelFormat::Code p);
	static RenderBase::PixelFormat::Code AsGenesisPixelFormatFromInternal(GLenum f);

	/// convert Engine pixel format to OpenGL pixel format type
	static GLenum AsGLESPixelDataType(RenderBase::PixelFormat::Code p);

	/// convert Engine pixel format to OpenGL Origin pixel format
	static GLenum AsGLESOriginPixelFormat(RenderBase::PixelFormat::Code p);

	//convert Nebula3 resource usage/access flag pair into OpenGL usage flags
	static GLenum AsGLESUsage(RenderBase::RenderResource::Usage usage, RenderBase::RenderResource::Access access);

	static GLenum AsGLESUsage(RenderBase::BufferData::Usage usage);

	static GLenum IndexTypeAsGLESFormat(RenderBase::IndexBufferData::IndexType indexType);

	static GLenum AsGLESTextureType(RenderBase::Texture::Type t);
	static GLenum AsGLESTextureType(const Util::String& type);

	static GLenum AsGLESBasicType(RenderBase::VertexComponent::Format format);

	static GLenum AsGLESPrimitiveType(RenderBase::PrimitiveTopology::Code t);

	static GLuint AsGLESMultiSampleType(RenderBase::AntiAliasQuality::Code c);

	static Util::String AsGlesAttributeName(const RenderBase::VertexComponent::SemanticName& sem);

	/**
	*  mapping state                                                                    
	*/
	static GLenum AsGLESBlendFactor(RenderBase::BlendFactor factor);
	static GLenum AsGLESBlendOperation(RenderBase::BlendOperation blendop);
	static GLenum AsGLESCompareFunction(RenderBase::CompareFunction func);
	static GLenum AsGLESStencilOperation(RenderBase::StencilOperation so);
	static GLint  AsGLESSTextureAddress(RenderBase::TextureAddressMode mode);
};

}


#endif