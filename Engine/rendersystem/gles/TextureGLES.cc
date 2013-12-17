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
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif
#include "TextureGLES.h"
#include "GLESTypes.h"
#include "math/color.h"
#include "util/algorithm.h"
namespace GLES
{
	using namespace RenderBase;
	__ImplementClass(TextureGLES,'TTGE',RenderBase::Texture);

TextureGLES::TextureGLES()
: m_textureGLES(0),
  m_bMipMap(false),
  m_bAttachedFBO(false),
  m_CurrentAddresingModeU(-1),
  m_CurrentAddresingModeV(-1),
  m_CurrentTexFilterOp(-1)
{

}

TextureGLES::~TextureGLES()
{
	_DeleteTextureObject();
}

void TextureGLES::Unload()
{
	_DeleteTextureObject();
}

void TextureGLES::_DeleteTextureObject()
{
	if (m_bAttachedFBO)
	{
		return;
	}

	if (m_textureGLES)
	{
		GLenum t = GLESTypes::AsGLESTextureType( GetType() );
		GLESImpl::Instance()->ActiveTextureObject(t, 0);
		glDeleteTextures(1, &m_textureGLES);
		m_textureGLES = 0;

		PROFILER_ADDDEVICESTATEVAL(videoRam, -memorySize);
		PROFILER_ADDDEVICESTATEVAL(texRam, -memorySize );
		PROFILER_ADDDEVICESTATEVAL(textureNum, -1);		
		memorySize = 0;
	}
}

void TextureGLES::_CreateTextureObject()
{
	if ( !m_textureGLES )
	{
		glGenTextures(1,&m_textureGLES);
		n_assert(m_textureGLES);
		n_assert( !glIsTexture(m_textureGLES) );
		memorySize = PixelFormat::GetMemorySize(GetWidth(), GetHeight(), GetDepth(), GetPixelFormat());
		PROFILER_ADDDEVICESTATEVAL(videoRam, memorySize);
		PROFILER_ADDDEVICESTATEVAL(texRam, memorySize );
		PROFILER_ADDDEVICESTATEVAL(textureNum, 1);
	}
	GLESImpl::Instance()->CheckError();
}

void TextureGLES::Setup(const GPtr<RenderBase::Texture>& srcTex)
{
	Super::Setup();
	/// set texture resouce path
	SetTexturePath(srcTex->GetTexturePath());
	/// set texture stream
	SetStream(srcTex->GetStream());
	/// set texture unit index
	SetUnitIndex(srcTex->GetUnitIndex());
	/// set attri
    SetSize( srcTex->GetStream()->GetSize() );
	SetType( srcTex->GetType() );
	SetWidth( srcTex->GetWidth() );
	SetHeight( srcTex->GetHeight() );
	SetDepth( srcTex->GetDepth() );
	SetNumMipLevels( srcTex->GetNumMipLevels() );
	SetPixelFormat( srcTex->GetPixelFormat() );
	SetSkippedMips( srcTex->GetSkippedMips() );
}

bool TextureGLES::LoadBuffers()
{
	GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( GetPixelFormat() );
	GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( GetPixelFormat() );
	GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( GetPixelFormat() );

	bool bDXT = false;

	if (GetPixelFormat() == PixelFormat::DXT1 || GetPixelFormat() == PixelFormat::DXT3 || GetPixelFormat() == PixelFormat::DXT5)
	{
		bDXT = true;
	}

	if( GetType() == InvalidType
		|| deviceInternalFormat == 0 
		|| deviceOriginFormat == 0
		|| ( deviceTypeFormat == 0 && !bDXT )
		)
	{

		bool bOK =  _LoadNormErrorBuffer();
		n_assert(bOK);
		return false;
	}

	if ( !m_stream.isvalid() )
	{
		n_warning("TextureGL::LoadBuffers: Invalid String. Use error texture\n");
		bool bOK =  _LoadNormErrorBuffer();
		n_assert(bOK);
		return false;
	}

	GPtr<IO::Stream> stream = m_stream;
	stream->SetAccessMode(IO::Stream::ReadAccess);
	stream->GetAccessMode();
	
	if (stream->Open())
	{
		bool bCreateOK = false;

		if ( GetType() == Texture2D )
		{			
			ubyte* srcData = (ubyte*)stream->Map();
			uint srcDataSize = stream->GetSize();

			bCreateOK = _LoadNormBuffer(srcData, srcDataSize);

			if ( !bCreateOK )
			{
				_LoadNormErrorBuffer();
			}

		}
		else if ( GetType() == Texture3D )
		{
			n_assert( GetDepth() > 1 );
			n_warning("TextureGLES::LoadBuffers: Not Support 3D tex Now");

			bCreateOK = false;
		}
		else if ( GetType() == TextureCube )
		{
			n_assert( GetDepth() == 1 );

			ubyte* srcData = (ubyte*)stream->Map();
			uint srcDataSize = stream->GetSize();

			bCreateOK = _LoadCubeBuffer(srcData, srcDataSize);
			if ( !bCreateOK )
			{
				_LoadCubeErrorBuffer();
			}
			bCreateOK = false;
		}
		else
		{
			n_error("TextureGLES::LoadBuffers: Invalid tex type");
			bCreateOK = false;
		}

		stream->Close();
		return bCreateOK;
	}

	bool bOK = _LoadNormErrorBuffer();
	n_assert(bOK);
	return false;

}

inline void MoveCursorToNextMipMap (PixelFormat::Code format, ubyte*& srcData, SizeT& texWidth, SizeT& texHeight, SizeT texDepth = 1 )
{
	srcData += PixelFormat::GetMemorySize(texWidth, texHeight, texDepth, format);
	texWidth =  Math::n_max( texWidth / 2, 1 );
	texHeight = Math::n_max( texHeight / 2, 1 );
}

bool TextureGLES::_LoadNormBuffer(ubyte* srcData, SizeT size )
{
	if( GetDepth() != 1 || GetWidth() <= 0 || GetHeight() <= 0 )
	{
		return false;
	}

	if( !Util::IsPowerTwo( GetHeight() ) || !Util::IsPowerTwo( GetWidth() ) )
	{
        n_assert("not pow of tow\n");
		return false;
	}

	if( GetPixelFormat() == PixelFormat::InvalidPixelFormat )
	{
		return false;
	}

	_CreateTextureObject();
	n_assert(m_textureGLES);
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D, m_textureGLES);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	SizeT texWidth = GetWidth();
	SizeT texHeight = GetHeight();
	SizeT texMipMap = GetNumMipLevels();

	PixelFormat::Code format    = GetPixelFormat();
	GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( format );

	bool isCompress = PixelFormat::IsCompressed( format );
	
	for (int level = 0; level < texMipMap; ++level)
	{
		if (isCompress) 
		{
			SizeT _size = PixelFormat::GetMemorySize(texWidth, texHeight, GetDepth(), format);
			glCompressedTexImage2D(GL_TEXTURE_2D, level, deviceInternalFormat, texWidth, texHeight, 0, _size, srcData);

			//PROFILER_ADDDEVICESTATEVAL(videoRam, _size);
			//PROFILER_ADDDEVICESTATEVAL(texRam, _size);
            
		} 
		else
		{
			
			GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( format );
			GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( format );

			n_assert( deviceInternalFormat != 0 );
			glTexImage2D (GL_TEXTURE_2D, level, deviceInternalFormat, texWidth, texHeight, 0, deviceOriginFormat, deviceTypeFormat, srcData);
			//int texSize = PixelFormat::GetMemorySize( texWidth, texHeight, depth, pixelFormat );

			//PROFILER_ADDDEVICESTATEVAL(videoRam, texSize);
			//PROFILER_ADDDEVICESTATEVAL(texRam, texSize);
		}

		GLESImpl::Instance()->CheckError();

		if (texMipMap > 1)
		{
			MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
		}
		

		TexInfo info;
		info.width  = texWidth;
		info.height = texHeight;
		m_TextureMipmapInfo.Add(level, info);
	}

	if ( texMipMap < 2 && !m_bAttachedFBO && !isCompress )
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		GLESImpl::Instance()->CheckError();
	}
	m_bMipMap = m_bAttachedFBO ? false : true;
	return true;
}

bool TextureGLES::_LoadNormErrorBuffer()
{
	_CreateTextureObject();
	GLESImpl::Instance()->CheckError();
	n_assert(m_textureGLES);
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D, m_textureGLES);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	SizeT texWidth = 1;
	SizeT texHeight = 1;
	SizeT texMipMap = 1;

	PixelFormat::Code format    = PixelFormat::A8R8G8B8;
	GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( format );
	GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( format );
	GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( format );

	SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);
	n_assert(levelPixelSize==4);

	Math::Color32 texColor(255,255,255,0);
	

	glTexImage2D (GL_TEXTURE_2D, 0, deviceInternalFormat, texWidth, texHeight, 0, deviceOriginFormat, deviceTypeFormat, texColor.Ptr() );
	GLESImpl::Instance()->CheckError();

	return true;
}

bool TextureGLES::_LoadCubeBuffer(ubyte* srcCube, SizeT size)
{
	if( GetDepth() != 1 || GetWidth() <= 0 || GetHeight() <= 0 )
	{
		return false;
	}

	if( !Util::IsPowerTwo( GetHeight() ) || !Util::IsPowerTwo( GetWidth() ) )
	{
		return false;
	}

	if( GetPixelFormat() == PixelFormat::InvalidPixelFormat )
	{
		return false;
	}

	if ( GetWidth() != GetHeight() )
	{
		return false;
	}


	_CreateTextureObject();
	GLESImpl::Instance()->CheckError();
	n_assert(m_textureGLES);
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_CUBE_MAP,m_textureGLES);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	SizeT cubeTexWidth  = GetWidth();
	SizeT cubeTexHeight = GetHeight();
	SizeT cubeTexMipMap = GetNumMipLevels();

	PixelFormat::Code format    = GetPixelFormat();
	GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( format );
	GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( format );
	GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( format );

	n_assert( deviceInternalFormat != 0 );

	bool isCompress = PixelFormat::IsCompressed( format );

	SizeT faceSize = 0;
	{
		SizeT cubeEdgeSize = cubeTexWidth;
		for( int level = 0; level < cubeTexMipMap; ++level )
		{
			faceSize += PixelFormat::GetMemorySize(cubeEdgeSize, cubeEdgeSize, 1, format);
			cubeEdgeSize =  Math::n_max( cubeEdgeSize / 2, 1 );
		}
	}

	for ( int face=0; face<6; ++face )
	{
		ubyte* faceData = srcCube + face*faceSize;
		SizeT texWidth  = cubeTexWidth;
		SizeT texHeight = cubeTexHeight;

		for (int level = 0; level < cubeTexMipMap; ++level)
		{
			// copy pixel
			SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);

			if (isCompress)
			{
				n_error("TextureGLES::_LoadCubeBuffer: Compress Cube Texture Not Support Now\n");
			} 
			else
			{
				glTexImage2D (face + GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, deviceInternalFormat, texWidth, texHeight, 0, deviceOriginFormat, deviceTypeFormat, faceData);
				GLESImpl::Instance()->CheckError();
			}

			MoveCursorToNextMipMap(format, faceData, texWidth, texHeight );
		}
	}

	if (cubeTexMipMap < 2 && !m_bAttachedFBO)
	{
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		m_bMipMap = true;
		GLESImpl::Instance()->CheckError();
	}

	return true;
}

bool TextureGLES::_LoadCubeErrorBuffer()
{
	_CreateTextureObject();
	GLESImpl::Instance()->CheckError();
	n_assert(m_textureGLES);
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_CUBE_MAP,m_textureGLES);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	SizeT cubeTexWidth  = 1;
	SizeT cubeTexHeight = 1;
	SizeT cubeTexMipMap = 1;

	PixelFormat::Code format    = PixelFormat::A8R8G8B8;
	GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( format );
	GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( format );
	GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( format );

	n_assert( deviceInternalFormat != 0 );

	SizeT faceDataSize = PixelFormat::GetMemorySize(cubeTexWidth, cubeTexHeight, 1, format);
	n_assert(faceDataSize==4);

	Math::Color32 texColor(255,255,255,255);

	for ( int face=0; face<6; ++face )
	{
		glTexImage2D (face+GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, deviceInternalFormat, cubeTexWidth, cubeTexHeight, 0, deviceOriginFormat, deviceTypeFormat, texColor.Ptr() );
		GLESImpl::Instance()->CheckError();
	}

	return true;
}

void TextureGLES::UpdateTexture(UpdateFunction texUpdateFunc, void* tag)
{
	MapInfo mapInfo;
	Util::Array<ubyte> mem;
    mem.Resize( GetSize(), 0 );
	for(SizeT mipLevel = 0; mipLevel < GetNumMipLevels(); mipLevel++ )
	{;

		if (GetType() == Texture2D)
		{
			TexInfo& info = m_TextureMipmapInfo[mipLevel];
			PixelFormat::Code format = GetPixelFormat();
			ubyte* srcData = &mem[0];
			if (!mipLevel)
			{
				mapInfo.data = srcData;
			} 
			else
			{
				for (IndexT i = 0; i < mipLevel; ++i)
				{
					MoveCursorToNextMipMap(format, srcData, info.width, info.height);
				}
				mapInfo.data = srcData;
			}
		}

		texUpdateFunc(mapInfo,GetWidth(),GetHeight(),GetDepth(),GetPixelFormat(),mipLevel, tag);

		if (this->type == Texture2D)
		{

			GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D,m_textureGLES);

			PixelFormat::Code format  = GetPixelFormat();
			GLenum deviceOriginFormat = GLESTypes::AsGLESOriginPixelFormat( format );
			GLenum deviceTypeFormat   = GLESTypes::AsGLESPixelDataType( format );

			glTexSubImage2D(GL_TEXTURE_2D, mipLevel, 0, 0, 
				this->width, this->height, 
				deviceOriginFormat,
				deviceTypeFormat,
				mapInfo.data);

			GLESImpl::Instance()->CheckError();
		}
		//Unmap(i);
	}
}

bool TextureGLES::Map(IndexT mipLevel, MapType mapType, MapInfo& outMapInfo)
{
	m_stream->SetAccessMode(IO::Stream::ReadAccess);

	TexInfo& info = m_TextureMipmapInfo[mipLevel];
	PixelFormat::Code format = GetPixelFormat();

	if (m_stream->Open())
	{
		if (GetType() == Texture2D)
		{
			ubyte* srcData = (ubyte*)m_stream->Map();

			if (!mipLevel)
			{
				outMapInfo.data = srcData;
				return true;	
			} 
			else
			{
				for (IndexT i = 0; i < mipLevel; ++i)
				{
					MoveCursorToNextMipMap(format, srcData, info.width, info.height );
				}

				outMapInfo.data = srcData;
				return true;
			}
		}
	}
	return false;
}

void TextureGLES::Unmap(IndexT mipLevel)
{
	m_stream->Unmap();
	if (this->type == Texture2D)
	{
		GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D,m_textureGLES);

		PixelFormat::Code format  = GetPixelFormat();
		GLenum deviceOriginFormat = GLESTypes::AsGLESOriginPixelFormat( format );
		GLenum deviceTypeFormat   = GLESTypes::AsGLESPixelDataType( format );

		glTexSubImage2D(GL_TEXTURE_2D, mipLevel, 0, 0, 
			this->width, this->height, 
			deviceOriginFormat,
			deviceTypeFormat,
			m_stream->Map());
			m_stream->Unmap();
		GLESImpl::Instance()->CheckError();
	}
	m_stream->Close();
}

bool TextureGLES::MapCubeFace(CubeFace face, IndexT mipLevel, MapType mapType, MapInfo& outMapInfo)
{
	return true;
}

void TextureGLES::UnmapCubeFace(CubeFace face, IndexT mipLevel)
{

}

void TextureGLES::OnDeviceLost()
{
	m_textureGLES = 0;
	m_bMipMap = false;

	m_CurrentAddresingModeU = -1;
	m_CurrentAddresingModeV = -1;
	m_CurrentTexFilterOp    = -1;
}

void TextureGLES::OnDeviceReset()
{

}

}

