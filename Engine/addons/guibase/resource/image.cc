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
#include "image.h"
#include "io/memorystream.h"
#include "GraphicSystem.h"

namespace GuiBase
{
	__ImplementClass(GuiBase::Image,'GBIG', Core::RefCounted);

	Image::Image()
		: m_texHandle(NULL)
		, m_shared(false)
	{

	}

	Image::~Image()
	{		
		Destroy();
	}

	void Image::Destroy()
	{
		if (m_texHandle.IsValid())
		{
			Graphic::GraphicSystem::Instance()->RemoveTexture(m_texHandle);
		}
		m_texHandle = NULL;
	}

	void Image::UpdateData(void* data, SizeT size)
	{
		GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
		tex->Setup();

		// set type
		RenderBase::Texture::Type texType = RenderBase::Texture::Texture2D;
		tex->SetType( texType );
		tex->SetWidth( m_width );
		tex->SetHeight( m_height );
		tex->SetDepth( 1 );
		tex->SetNumMipLevels( 1 );
		tex->SetPixelFormat( m_format );

		// dummy
		tex->SetSkippedMips( 0 );
		tex->SetUnitIndex( 0 );

		//tex->SetTexturePath();

		GPtr<IO::MemoryStream> memStream = IO::MemoryStream::Create();
		memStream->SetAccessMode( IO::Stream::WriteAccess );
		if( memStream->Open() )
		{
			memStream->Write( data, size );
			tex->SetStream( memStream.upcast<IO::Stream>() );
			memStream->Close();
			memStream->SetAccessMode( IO::Stream::ReadAccess );
			Graphic::GraphicSystem::Instance()->UpdateTexture(m_texHandle, tex);
		}
	}

	GPtr<Image> Image::CreateImage(void* data, SizeT size, SizeT width, SizeT height, RenderBase::PixelFormat::Code format)
	{	
		GPtr<Image> image = Image::Create();
		image->m_format = format;
		image->m_width = width;
		image->m_height = height;
		GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
		tex->Setup();

		// set type
		RenderBase::Texture::Type texType = RenderBase::Texture::Texture2D;


		tex->SetType( texType );

		tex->SetWidth( width );
		tex->SetHeight( height );
		tex->SetDepth( 1);
		tex->SetNumMipLevels( 1 );
		tex->SetPixelFormat( format );

		// dummy
		tex->SetSkippedMips( 0 );
		tex->SetUnitIndex( 0 );

		//tex->SetTexturePath();

		GPtr<IO::MemoryStream> memStream = IO::MemoryStream::Create();
		memStream->SetAccessMode( IO::Stream::WriteAccess );
		if( memStream->Open() )
		{
			memStream->Write( data, size );
			tex->SetStream( memStream.upcast<IO::Stream>() );
			memStream->Close();
			memStream->SetAccessMode( IO::Stream::ReadAccess );
			image->m_texHandle = Graphic::GraphicSystem::Instance()->CreateTexture(tex);
		}
		else
		{
			image->m_texHandle = NULL;
		}
		return image;
	}

	GPtr<Image> Image::LoadImage()
	{
		return NULL;
	}
}