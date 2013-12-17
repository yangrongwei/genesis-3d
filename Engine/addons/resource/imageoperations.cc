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
#include "resource/resource_stdneb.h"
#include "imageoperations.h"
#include "foundation/io/stream.h" 
#include "foundation/io/ioserver.h" 


// must define FREEIMAGE_LIB when use FreeImage as static lib
#define FREEIMAGE_LIB
// use free image to load image
#include <FreeImage/FreeImage.h>

// freeimage 3.9.1~3.11.0 interoperability fix
#ifndef FREEIMAGE_COLORORDER
// we have freeimage 3.9.1, define these symbols in such way as 3.9.1 really work (do not use 3.11.0 definition, as color order was changed between these two versions on Apple systems)
#define FREEIMAGE_COLORORDER_BGR	0
#define FREEIMAGE_COLORORDER_RGB	1
#if defined(FREEIMAGE_BIGENDIAN)
#define FREEIMAGE_COLORORDER FREEIMAGE_COLORORDER_RGB
#else
#define FREEIMAGE_COLORORDER FREEIMAGE_COLORORDER_BGR
#endif
#endif

#ifndef __WIN32__

//#error	//	@todo in iphone

// Color order is actually RGB on iPhone
//#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
//#define FREEIMAGE_COLORORDER FREEIMAGE_COLORORDER_RGB
//#endif

#endif

namespace Resources
{

	using namespace Math;

	__ImplementClass(ImageOperations, 'IMOP', Core::RefCounted)

#define FOURCC(c0, c1, c2, c3) (c0 | (c1 << 8) | (c2 << 16) | (c3 << 24))
		typedef uint uint32;	//	static_assert sizeof(uint)==4  later
	typedef ushort uint16;  //  static_assert sizeof(uint16)==2  later
	typedef ubyte uint8;  //  static_assert sizeof(uint16)==1  later

#include "addons/resource/DDS_Header.h"

	ImageOperations::ImageOperations()
	{
	}
	//------------------------------------------------------------------------------

	ImageOperations::~ImageOperations()
	{}
#if  __OSX__

#else
	//------------------------------------------------------------------------
	// Save dib to disk file to use native IO via memory stream instead of FreeImage IO
	bool SaveToFile(FREE_IMAGE_FORMAT fif, FIBITMAP *dib, const IO::URI& uri)
	{
		n_assert(dib);
		bool ret = false;
		FIMEMORY* hMem = FreeImage_OpenMemory();
		if( FreeImage_SaveToMemory(fif,dib,hMem) )
		{
			//	Note: After FreeImage_SaveToMemory hMem points at the end of memory stream
#if NEBULA3_DEBUG
			long filememSize = FreeImage_TellMemory(hMem);	// address of hMem equals the size of the file
#endif
			FreeImage_SeekMemory(hMem,0,SEEK_SET);	
			IO::IoServer* ioServer = IO::IoServer::Instance();
			n_assert(ioServer);
			GPtr<IO::Stream> stream = ioServer->CreateFileStream(uri);
			if ( stream )
			{
				stream->SetAccessMode(IO::Stream::WriteAccess);
				if ( stream->Open() )
				{
					const int BufSize = 1024;
					char buf[BufSize];
					unsigned readCount = 0; 
#if NEBULA3_DEBUG
					long writeSize  = 0; 
#endif
					do 
					{
						readCount = FreeImage_ReadMemory(buf, 1, BufSize, hMem);
						n_assert(readCount<=BufSize);
						if ( readCount > 0 )
						{
							stream->Write(buf,readCount);
#if NEBULA3_DEBUG
							writeSize += readCount;
#endif
						}
					} 
					while ( readCount == BufSize );

#if NEBULA3_DEBUG
					n_assert(writeSize==filememSize);
#endif

					stream->Close();
					ret = true;
				}
			}
		}

		FreeImage_CloseMemory(hMem);
		return ret;
	}
#endif
#if  __OSX__

#else
	//------------------------------------------------------------------------
	bool ImageOperations::CreateTGAImageResAndSave(const Util::String &fileName, const int width, const int height, const Color32 &defaultColor)
	{
		FIBITMAP *dib = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		if (!dib)
		{
			n_warning("Create tga image res error.");
			return false;
		}

		RGBQUAD rgbBkColor;
		rgbBkColor.rgbRed = defaultColor.r;
		rgbBkColor.rgbGreen = defaultColor.g;
		rgbBkColor.rgbBlue = defaultColor.b;
		rgbBkColor.rgbReserved = defaultColor.a;

		//FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);	//for test
		FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(dib);	
		switch(color_type)
		{
		case FIC_RGBALPHA:
			{
				//TODO(KouYan): To optimize, assign a value at a time
				for (int y=0; y<height; y++)
				{
					for (int x=0; x<width; x++)
					{
						FreeImage_SetPixelColor(dib, x, y, &rgbBkColor);
					}
				}
				break;
			}
		default:
			{
				n_warning("CreateTGAImageResAndSave():do not support color type.");
				return false;
			}
		}

		bool ret = SaveToFile(FIF_TARGA, dib, fileName);
		FreeImage_Unload(dib);

		return ret;
	}
	//------------------------------------------------------------------------------
	bool ImageOperations::SaveTGAImage(const Util::String &imagePath, const GPtr<Resources::ImageRes> &res)
	{
		n_assert(imagePath.IsValid());

		const SizeT width = res->GetWidth();
		const SizeT height = res->GetHeight();

		FIBITMAP *dib = FreeImage_Allocate(width, height, 32);
		if (!dib)
		{
			n_warning("Create tga image res error.");
			return false;
		}

		RGBQUAD rgbBkColor;
		Math::ColorF tmpBuf;

		FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(dib);	
		switch(color_type)
		{
		case FIC_RGBALPHA:
			{
				//TODO(KouYan): To optimize, assign a value at a time
				for (int y=0; y<height; y++)
				{
					for (int x=0; x<width; x++)
					{
						res->GetPixels(x, y, 1, 1, 0, &tmpBuf);
						rgbBkColor.rgbRed = n_scalartoByte(tmpBuf.r);
						rgbBkColor.rgbGreen = n_scalartoByte(tmpBuf.g);
						rgbBkColor.rgbBlue = n_scalartoByte(tmpBuf.b);
						rgbBkColor.rgbReserved = n_scalartoByte(tmpBuf.a);
						FreeImage_SetPixelColor(dib, x, y, &rgbBkColor);
					}
				}
				break;
			}
		default:
			{
				n_warning("CreateTGAImageResAndSave():do not support color type.");
				return false;
			}
		}
		FreeImage_FlipVertical(dib);
		bool ret = SaveToFile(FIF_TARGA, dib, imagePath);
		FreeImage_Unload(dib);

		/*FIMEMORY* fiMem = FreeImage_OpenMemory( data, static_cast<DWORD>(size) );
		FIBITMAP* fiBitmap = FreeImage_LoadFromMemory( (FREE_IMAGE_FORMAT)fileType, fiMem );

		if (fiMem && fiBitmap)
		{
		ret = FreeImage_Save((FREE_IMAGE_FORMAT)fileType, fiBitmap, imagePath.AsCharPtr(), 0);
		FreeImage_Unload(fiBitmap);
		FreeImage_CloseMemory(fiMem);
		}*/

		return ret;
	}
	//------------------------------------------------------------------------------
	void ImageOperations::SaveDDSCubeImage(uint32 height_ , uint32 width_ ,const Util::String& fileName , void* data, int size)
	{
		DDSHeader ddsh;
		unsigned int headerSize = sizeof(DDSHeader);

		const uint value = 0x00;
		Memory::Fill(&ddsh,headerSize,value);

		ddsh.size = headerSize;
		ddsh.flags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
		ddsh.height = height_;
		ddsh.width = width_;

		ddsh.flags |= DDSD_PITCH;

		ddsh.sizeOrPitch = ((width_ * 4 * 8 + 31) & -32) >> 3;

		ddsh.pixelFormat.size = sizeof(DDSPixelFormat);

		ddsh.pixelFormat.flags = DDPF_RGBA;
		ddsh.pixelFormat.rgbBits = 32;
		ddsh.pixelFormat.redMask = 0x00ff0000;
		ddsh.pixelFormat.greenMask = 0x0000ff00;
		ddsh.pixelFormat.blueMask = 0x000000ff;


		ddsh.pixelFormat.flags |= DDPF_ALPHAPIXELS;
		ddsh.pixelFormat.alphaMask = 0xff000000;


		ddsh.caps.caps1 = DDSCAPS_TEXTURE;
		ddsh.caps.caps1 |= DDSCAPS_COMPLEX;
		ddsh.caps.caps2  =  DDSCAPS2_CUBEMAP |
			DDSCAPS2_CUBEMAP_POSITIVEX|
			DDSCAPS2_CUBEMAP_NEGATIVEX|
			DDSCAPS2_CUBEMAP_POSITIVEY|
			DDSCAPS2_CUBEMAP_NEGATIVEY|
			DDSCAPS2_CUBEMAP_POSITIVEZ|
			DDSCAPS2_CUBEMAP_NEGATIVEZ;


		const char* DDSName = "DDS ";

		IO::URI tmpUri; 
		tmpUri.Set(fileName.AsCharPtr()); 
		GPtr<IO::Stream> srcStream = IO::IoServer::Instance()->CreateFileStream(tmpUri); 
		srcStream->SetAccessMode(IO::Stream::WriteAccess); 

		if (srcStream->Open())
		{
			srcStream->Write(DDSName,4);
			srcStream->Write(&ddsh,sizeof(DDSHeader));
			srcStream->Write(data,size);

			srcStream->Close();
		}
	}

	void ImageOperations::HorizontalFlipImage( void* data,const int size ,const int width,const int height)
	{

		FIBITMAP *dib = FreeImage_Allocate(width, height, 32);
		if (!dib)
		{
			n_warning("Create tga image res error.");
			return ;
		}

		FREE_IMAGE_COLOR_TYPE color_type = FreeImage_GetColorType(dib);	
		switch(color_type)
		{
		case FIC_RGBALPHA:
			{

				BYTE* src = FreeImage_GetBits(dib);
				Memory::CopyToGraphicsMemory(data,src,size);
				break;
			}
		default:
			{
				n_warning("HorizontalFlipImage():do not support color type.");
				FreeImage_Unload(dib);
				return ;
			}
		}
		FreeImage_FlipHorizontal(dib);

		BYTE* src = FreeImage_GetBits(dib);

		Memory::CopyToGraphicsMemory(src,data,size);

		FreeImage_Unload(dib);

	}
#endif
}
