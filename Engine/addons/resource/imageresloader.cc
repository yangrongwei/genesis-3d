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
#include "resource/resource_stdneb.h"
#include "resource/imageresloader.h"
#include "rendersystem/config/RenderDeviceConfig.h"
#include "ETC_Header.h"

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

/*
From Google£¬The DevIL And FreeImage All Are Not ThreadSafe¡£
We Use FreeImage From OgreDependencies_MSVC_20101231 As Static Lib. 
If Only Use ResourceServer::LoadResource, We Had Only One Thread when Decode The Image. It's¡¡Thread Safe
If Use ResourceServer::LoadResource And Image::Load In Two Thread .  It's Dangerous !!!!!!!!!!!!!!!!!!

*/
namespace Resources
{
	__ImplementClass(Resources::ImageResCodecReg,'IRCR', Resources::ResCodecReg);
	__ImplementClass(Resources::ImageResLoader,'IRLD', Resources::ResourceLoader);
	__ImplementImageSingleton(Resources::ImageResCodecReg);

#define FOURCC(c0, c1, c2, c3) (c0 | (c1 << 8) | (c2 << 16) | (c3 << 24))

	typedef uint uint32;	//	static_assert sizeof(uint)==4  later
	typedef ushort uint16;  //  static_assert sizeof(uint16)==2  later
	typedef ubyte uint8;  //  static_assert sizeof(uint16)==1  later


#include "PVRTC_Header.h"
#include "DDS_Header.h"


	//------------------------------------------------------------------------
	void FreeImageLoadErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
	{
		// Callback method as required by FreeImage to report problems
#if __OSX__

#else
		const char* typeName = FreeImage_GetFormatFromFIF(fif);


		if (typeName)
		{
			n_warning("FreeImage error: %s when loading format %s\n" , message, typeName);
		}
		else
		{
			n_warning("FreeImage error: %s \n", message);
		}
#endif
	}

	//------------------------------------------------------------------------
	ImageResCodecReg::ImageResCodecReg() 
		: mIsOpen(false)
	{
		__ConstructImageSingleton;
	}
	//------------------------------------------------------------------------
	ImageResCodecReg::~ImageResCodecReg()
	{
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	void 
		ImageResCodecReg::Open(void)
	{
		if ( mIsOpen )
		{
			return;
		}

		n_static_assert( sizeof(uint32) == 4 );
		n_static_assert( sizeof(uint16) == 2 );
		n_static_assert( sizeof(uint8) == 1 );

#if __OSX__

#else
		FreeImage_Initialise(false);

		n_printf("FreeImage version: %s  Info: %s \n", FreeImage_GetVersion(), FreeImage_GetCopyrightMessage());
		n_printf("FreeImage Supported formats:  \n");

		for (int iType = 0; iType < FreeImage_GetFIFCount(); ++iType)
		{
			// Skip DDS codec since FreeImage does not have the option 
			// to keep DXT data compressed, we'll use our own codec
			if ((FREE_IMAGE_FORMAT)iType == FIF_DDS)
				continue;

			Util::String exts(FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)iType));

			Util::Array<Util::String> strArray;
			exts.Tokenize(",", strArray);
			// Pull off individual formats (separated by comma by FI)
			for (IndexT index = 0 ; index < strArray.Size(); ++index )
			{
				// FreeImage 3.13 lists many formats twice: once under their own codec and
				// once under the "RAW" codec, which is listed last. Avoid letting the RAW override
				// the dedicated codec!

				Util::String strType = strArray[index];
				strType.ToUpper();
				n_printf( " %s", strType.AsCharPtr() );

				if ( InvalidIndex == mExtReg.FindIndex( strType ) )
				{
					mExtReg.Add(strType,  iType );
				}
			} 
		}
		n_printf("\n");

		// Set error handler
		FreeImage_SetOutputMessage(FreeImageLoadErrorHandler);
#endif
		mIsOpen = true;
	}
	//------------------------------------------------------------------------
	void 
		ImageResCodecReg::Close(void)
	{
		if ( mIsOpen )
		{
#if __OSX__

#else
			FreeImage_DeInitialise();
#endif
		}
		mIsOpen = false;
	}
	//------------------------------------------------------------------------
	IndexT 
		ImageResCodecReg::FindType(const Util::String& strExt, int& ImageFiletype)
	{
		IndexT findIndex = mExtReg.FindIndex( strExt );
		if ( findIndex != InvalidIndex )
		{
			ImageFiletype = mExtReg.ValueAtIndex( findIndex );
		}
		return findIndex;
	}
	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &ImageRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<ImageRes> pImageRes = pRes.downcast<ImageRes>();
		n_assert(pImageRes);

		if ( !mStream.isvalid() )
		{
			return false;
		}

		if ( mStream->GetSize() <= 0 )
		{
			return false;
		}

		// Image does not support streaming for now. In order to reload correctly, unload existing data first.
		pImageRes->UnLoadImpl();

		bool NeedClose = false;
		if ( !mStream->IsOpen() )
		{
			if ( !mStream->Open() )
			{
				return false;
			}
			NeedClose = true;
		}

		// load data
		if ( !LoadImage(mStream, pImageRes) )
		{
			if ( NeedClose )
			{
				mStream->Close();
			}
			return false;
		}

		if ( NeedClose )
		{
			mStream->Close();
		}

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadImage(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage)
	{
		n_assert( mStream.isvalid() && pImage.isvalid() );

		// check if dds
		if ( stream->GetSize() >= 4 )
		{
			//Read first byte to identify format
			uint32 magic;
			stream->Read(&magic,sizeof(uint32) );
			FlipEndian(&magic, sizeof(uint32), 1);

			if ( DDS_MAGIC == magic )
			{
				stream->Seek(0, IO::Stream::Begin );
				return LoadDXT(stream, pImage );
			}

			// prepare check other
			stream->Seek(0, IO::Stream::Begin );
		}

		// check if PVRTC
		if ( stream->GetSize() >= sizeof(PVRTCTexHeader) )
		{
			// PVRTCTexHeader header;

			uint32 magic;
			stream->Read(&magic,sizeof(uint32) );
			FlipEndian(&magic, sizeof(uint32), 1);

			const uint32 PVRTEX3_IDENT			= 0x03525650;	// 'P''V''R'3

			if (PVRTEX3_IDENT== magic)
			{
				stream->Seek(0, IO::Stream::Begin );
				return LoadPVRTC(stream, pImage );
			}

			// prepare check other
			stream->Seek(0, IO::Stream::Begin );
		}

		if ( stream->GetSize() >= sizeof(ETCHeader) )
		{
			static const char* ETC_MAGIC = "PKM ";
			char magicNum[5];
			magicNum[4] = '\0';
			stream->Read(&magicNum, 4);

			if (!strcmp(ETC_MAGIC, magicNum))
			{
				stream->Seek(0, IO::Stream::Begin );
				return LoadETC(stream, pImage);
			}

			stream->Seek(0, IO::Stream::Begin);
		}

		// check if ETC
		// not impl now

		// use FreeImage
		return LoadCommon(stream, pImage );

	}

	//------------------------------------------------------------------------
	RenderBase::PixelFormat::Code DXT_convertFourCCFormat(uint32 fourcc)
	{
		// convert dxt pixel format
		switch(fourcc)
		{
		case FOURCC('D','X','T','1'):
			return RenderBase::PixelFormat::DXT1;
		case FOURCC('D','X','T','2'):
			return RenderBase::PixelFormat::DXT2;
		case FOURCC('D','X','T','3'):
			return RenderBase::PixelFormat::DXT3;
		case FOURCC('D','X','T','4'):
			return RenderBase::PixelFormat::DXT4;
		case FOURCC('D','X','T','5'):
			return RenderBase::PixelFormat::DXT5;
		case D3DFMT_R16F:
			return RenderBase::PixelFormat::R16F;
		case D3DFMT_G16R16F:
			return RenderBase::PixelFormat::G16R16F;
		case D3DFMT_A16B16G16R16F:
			return RenderBase::PixelFormat::A16B16G16R16F;
		case D3DFMT_R32F:
			return RenderBase::PixelFormat::R32F;
		case D3DFMT_G32R32F:
			return RenderBase::PixelFormat::G32R32F;
		case D3DFMT_A32B32G32R32F:
			return RenderBase::PixelFormat::A32B32G32R32F;
			// We could support 3Dc here, but only ATI cards support it, not nVidia
		default:
			return RenderBase::PixelFormat::InvalidPixelFormat;
		};
	}

	//------------------------------------------------------------------------
	RenderBase::PixelFormat::Code DXT_convertPixelFormat(uint32 rgbBits, uint32 rMask, 
		uint32 gMask, uint32 bMask, uint32 aMask)
	{
		// General search through pixel formats
		for (IndexT i = 0; i < RenderBase::PixelFormat::NumPixelFormats; ++i)
		{
			RenderBase::PixelFormat::Code pf = static_cast<RenderBase::PixelFormat::Code>(i);

			SizeT numBits = RenderBase::PixelFormat::GetNumElemBytes(pf) * 8;
			if (numBits == rgbBits)
			{
				uint32 testMasks[4];
				RenderBase::PixelFormat::GetBitMasks(pf, testMasks);
				int testBits[4];
				RenderBase::PixelFormat::GetBitDepths(pf, testBits);
				if (testMasks[0] == rMask && testMasks[1] == gMask &&
					testMasks[2] == bMask && 
					// for alpha, deal with 'X8' formats by checking bit counts
					(testMasks[3] == aMask || (aMask == 0 && testBits[3] == 0)))
				{
					return pf;
				}
			}

		}

		return RenderBase::PixelFormat::InvalidPixelFormat;
	}
	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadDXT(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage)
	{
		uint32 magic;
		stream->Read(&magic,sizeof(uint32) );
		FlipEndian(&magic, sizeof(uint32), 1);
		if ( DDS_MAGIC != magic )
		{
			return false;
		}

		// Read header in full
		DDSHeader header;
		stream->Read(&header, sizeof(DDSHeader));

		// Endian flip if required, all 32-bit values
		FlipEndian(&header, 4, sizeof(DDSHeader) / 4);

		// Check some sizes
		if (header.size != DDS_HEADER_SIZE)
		{
			n_warning(" ImageResLoader::LoadDXT DDS header size mismatch!\n");
			return false;
		}
		if (header.pixelFormat.size != DDS_PIXELFORMAT_SIZE)
		{
			n_warning(" ImageResLoader::LoadDXT DDS header size mismatch!\n");
		}


		pImage->mDepth = 1; // (deal with volume later)
		pImage->mWidth = header.width;
		pImage->mHeight = header.height;

		pImage->mNumFace = 1; // assume one face until we know otherwise
		pImage->mDepth = 1;  // assume one depth until we know otherwise

		if (header.caps.caps1 & DDSCAPS_MIPMAP)
		{
			pImage->mMipMapLevel = static_cast<ushort>(header.mipMapCount - 1);
		}
		else
		{
			pImage->mMipMapLevel = 0;
		}

		bool decompressDXT = false;

		// Figure out basic image type
		if (header.caps.caps2 & DDSCAPS2_CUBEMAP)
		{
			pImage->mNumFace = 6;	//	cube map
		}
		else if (header.caps.caps2 & DDSCAPS2_VOLUME)
		{
			pImage->mDepth = header.depth;	//	3d texture
		}

		// Pixel format
		RenderBase::PixelFormat::Code sourceFormat = RenderBase::PixelFormat::InvalidPixelFormat;

		if (header.pixelFormat.flags & DDPF_FOURCC)
		{
			sourceFormat = DXT_convertFourCCFormat(header.pixelFormat.fourCC);
		}
		else
		{
			sourceFormat = DXT_convertPixelFormat(header.pixelFormat.rgbBits, 
				header.pixelFormat.redMask, header.pixelFormat.greenMask, 
				header.pixelFormat.blueMask, 
				header.pixelFormat.flags & DDPF_ALPHAPIXELS ? 
				header.pixelFormat.alphaMask : 0);
		}

		if ( sourceFormat == RenderBase::PixelFormat::InvalidPixelFormat)
		{
			n_warning( "ImageResLoader::LoadDXT Cannot determine pixel format\n");
			return false;
		}

		pImage->mPixelFormat = sourceFormat;


		// Calculate total size from number of mipmaps, faces and size
		SizeT dataSize = ImageRes::S_CalculateSize(pImage->mMipMapLevel, pImage->mNumFace, 
			pImage->mWidth, pImage->mHeight, pImage->mDepth, pImage->mPixelFormat);

		if ( dataSize == 0 )
		{
			return false;
		}

		GPtr<ImageData> pData = ImageData::Create();
		pData->Setup( dataSize );

		pImage->mData = pData;

		// Now deal with the data
		ubyte* destPtr = pData->Ptr();
		n_assert(destPtr);

		// all mips for a face, then each face
		for(IndexT i = 0; i < pImage->mNumFace; ++i)
		{   
			SizeT width = pImage->mWidth;
			SizeT height = pImage->mHeight;
			SizeT depth = pImage->mDepth;

			for(IndexT mip = 0; mip <= pImage->mMipMapLevel; ++mip)
			{
				SizeT dstPitch = width * RenderBase::PixelFormat::GetNumElemBytes(pImage->mPixelFormat);

				if (RenderBase::PixelFormat::IsCompressed(sourceFormat))
				{
					// load directly
					// DDS format lies! sizeOrPitch is not always set for DXT!!
					size_t dxtSize = RenderBase::PixelFormat::GetMemorySize(width, height, depth, pImage->mPixelFormat);

					stream->Read(destPtr, dxtSize);
					destPtr += dxtSize;
				}
				else
				{
					// Final data - trim incoming pitch
					SizeT srcPitch;
					if (header.flags & DDSD_PITCH)
					{
						srcPitch = header.sizeOrPitch / Math::n_max( 1, mip * 2 );
					}
					else
					{
						// assume same as final pitch
						srcPitch = dstPitch;
					}

					n_assert (dstPitch <= srcPitch);

					long srcAdvance = srcPitch - dstPitch;

					for (IndexT z = 0; z < depth; ++z)
					{
						for (IndexT y = 0; y < height; ++y)
						{
							stream->Read(destPtr, dstPitch);
							if (srcAdvance > 0)
							{
								stream->Seek(srcAdvance, IO::Stream::Current);
							}

							destPtr = destPtr + dstPitch;
						}
					}

				}


				/// Next mip
				if(width!=1) width /= 2;
				if(height!=1) height /= 2;
				if(depth!=1) depth /= 2;
			}

		}

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadPVRTC(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage)
	{
		n_assert( stream->GetSize() >= sizeof(New_PVRTCTexHeader) );

		New_PVRTCTexHeader header;
		uint64 formatFlags = 0 ;

		size_t numFaces = 1; // Assume one face until we know otherwise

		// Read the PVRTC header
		stream->Read(&header, sizeof(New_PVRTCTexHeader));

		// Get format flags
		formatFlags = header.u64PixelFormat;

		FlipEndian((void *)formatFlags, sizeof(uint64));

		if (formatFlags == ePVRTPF_PVRTCI_2bpp_RGBA || formatFlags == ePVRTPF_PVRTCI_4bpp_RGBA)
		{
			if (formatFlags == ePVRTPF_PVRTCI_4bpp_RGBA)
			{
				pImage->mPixelFormat =  RenderBase::PixelFormat::PVRTC_RGBA4 ;
			}
			else if (formatFlags == ePVRTPF_PVRTCI_2bpp_RGBA)
			{
				pImage->mPixelFormat =  RenderBase::PixelFormat::PVRTC_RGBA2 ;
			}

			pImage->mDepth = 1;
			pImage->mWidth = header.u32Width;
			pImage->mHeight = header.u32Height;
			pImage->mMipMapLevel = static_cast<ushort>(header.u32MIPMapCount)-1;
			pImage->mNumFace = numFaces;
		}

		// Calculate total size from number of mipmaps, faces and size
		SizeT dataSize = ImageRes::S_CalculateSize(pImage->mMipMapLevel, pImage->mNumFace, 
			pImage->mWidth, pImage->mHeight, pImage->mDepth, pImage->mPixelFormat);

		if ( dataSize == 0 )
		{
			return false;
		}

		GPtr<ImageData> pData = ImageData::Create();
		pData->Setup( dataSize );
		pImage->mData = pData;

		// Now deal with the data
		ubyte *destPtr = pData->Ptr();
		stream->Read(destPtr, dataSize);

		return true;

	}
	//------------------------------------------------------------------------
	class AutoMemory
	{
	public:
		AutoMemory(GPtr<IO::Stream>& stream, ubyte** data) 
			: mStream( stream )
			, mNewData(NULL)
			, mMap(false)
		{
			SizeT streamSize = mStream->GetSize();
			n_assert(streamSize > 0 );

			if ( mStream->CanBeMapped() && !mStream->IsMapped() )
			{
				(*data) = (ubyte*)stream->Map();
				mMap = true;
			}
			else
			{
				mNewData = n_new_array(ubyte, streamSize);
				(*data) = mNewData;
				mMap = false;
			}
		}
		~AutoMemory()
		{
			if ( mMap )
			{
				mStream->Unmap();
			}
			else
			{
				n_delete_array(mNewData);
			}
		}


		bool mMap;
		GPtr<IO::Stream>& mStream;
		ubyte* mNewData;
	};
	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadCommon(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage)
	{
		n_assert( stream.isvalid() && pImage.isvalid() );
		SizeT streamSize = stream->GetSize();
		if ( streamSize <= 0 )
		{
			return false;
		}	

		FreeImage_SetOutputMessage(FreeImageLoadErrorHandler);

		Util::String resName = pImage->GetResourceId().AsString();
		Util::String fileExt = resName.GetFileExtension();
		fileExt.ToUpper();

		ubyte* pStreamData = NULL;
		AutoMemory autoMem( stream, &pStreamData );
		n_assert( pStreamData != NULL );

		// To identify image format, analysis with FreeImage stream first, then try ImageResCodecReg
		int fileType = FIF_UNKNOWN;
		FIMEMORY* fiMem = FreeImage_OpenMemory( pStreamData, static_cast<DWORD>(streamSize) );
		if( !fiMem )
		{
			n_warning( "mageResLoader::LoadCommon Can Not Open image Memory\n");
			return false;
		}

		fileType = FreeImage_GetFileTypeFromMemory(fiMem);

		if ( fileType == FIF_UNKNOWN )
		{
			if ( ImageResCodecReg::HasInstance()  )
			{
				ImageResCodecReg::Instance()->FindType(fileExt, fileType);
			}
		}

		if ( fileType == FIF_UNKNOWN )
		{
			n_warning( "mageResLoader::LoadCommon Can Not Get image Type\n");
			return false;
		}


		FIBITMAP* fiBitmap = FreeImage_LoadFromMemory( (FREE_IMAGE_FORMAT)fileType, fiMem );
		if (!fiBitmap)
		{
			n_warning( "mageResLoader::LoadCommon Error decoding image\n");
			return false;
		}

		pImage->mDepth = 1; // only 2D formats handled by this codec
		pImage->mWidth = FreeImage_GetWidth(fiBitmap);
		pImage->mHeight = FreeImage_GetHeight(fiBitmap);
		pImage->mMipMapLevel = 0; // no mipmaps in non-DDS 

		// Must derive format first, this may perform conversions
		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(fiBitmap);
		FREE_IMAGE_COLOR_TYPE colourType = FreeImage_GetColorType(fiBitmap);
		unsigned bpp = FreeImage_GetBPP(fiBitmap);

		switch(imageType)
		{
		case FIT_UNKNOWN:
		case FIT_COMPLEX:
		case FIT_UINT32:
		case FIT_INT32:
		case FIT_DOUBLE:
			n_warning(" ImageResLoader::LoadCommon: Unknown or unsupported image format\n");
			return false;
		case FIT_BITMAP:
			// Standard image type
			// Perform any colour conversions for greyscale
			if (colourType == FIC_MINISWHITE || colourType == FIC_MINISBLACK)
			{
				FIBITMAP* newBitmap = FreeImage_ConvertToGreyscale(fiBitmap);
				// free old bitmap and replace
				FreeImage_Unload(fiBitmap);
				fiBitmap = newBitmap;
				// get new formats
				bpp = FreeImage_GetBPP(fiBitmap);
				colourType = FreeImage_GetColorType(fiBitmap);
			}
			// Perform any colour conversions for RGB
			else if (bpp < 8 || colourType == FIC_PALETTE || colourType == FIC_CMYK)
			{
				FIBITMAP* newBitmap = FreeImage_ConvertTo32Bits(fiBitmap);
				// free old bitmap and replace
				FreeImage_Unload(fiBitmap);
				fiBitmap = newBitmap;
				// get new formats
				bpp = FreeImage_GetBPP(fiBitmap);
				colourType = FreeImage_GetColorType(fiBitmap);
			}
			else if ( bpp == 24 )
			{
				// most graphics chip does not support 24bit but 32bit
				FIBITMAP* newBitmap = FreeImage_ConvertTo32Bits(fiBitmap);
				// free old bitmap and replace
				FreeImage_Unload(fiBitmap);
				fiBitmap = newBitmap;
				// get new formats
				bpp = FreeImage_GetBPP(fiBitmap);
				colourType = FreeImage_GetColorType(fiBitmap);
			}

			// by this stage, 8-bit is greyscale, 16/24/32 bit are RGB[A]
			switch(bpp)
			{
			case 8:
				pImage->mPixelFormat = RenderBase::PixelFormat::L8;
				break;
			case 16:
				// Determine 555 or 565 from green mask
				// cannot be 16-bit greyscale since that's FIT_UINT16
				if(FreeImage_GetGreenMask(fiBitmap) == FI16_565_GREEN_MASK)
				{
					pImage->mPixelFormat = RenderBase::PixelFormat::R5G6B5;
				}
				else
				{
					// FreeImage doesn't support 4444 format so must be 1555
					pImage->mPixelFormat = RenderBase::PixelFormat::A1R5G5B5;
				}
				break;
			case 24:
				// FreeImage differs per platform
				//     little endian: BGR[A]
				//     for big endian:  RGB[A]
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				// big endian. RGB in memory, RGB in native
				pImage->mPixelFormat = RenderBase::PixelFormat::R8G8B8;
#else
				// little endian. BGR in memory, RGB in native
				pImage->mPixelFormat = RenderBase::PixelFormat::R8G8B8;
#endif
				break;
			case 32:
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				// big endian. RGBA in memory, RGBA in native
				pImage->mPixelFormat = RenderBase::PixelFormat::R8G8B8A8;
#else
				// little endian. BGRA in memory, ARGB in native
				pImage->mPixelFormat = RenderBase::PixelFormat::A8R8G8B8;
#endif
				break;


			};
			break;
		case FIT_UINT16:
		case FIT_INT16:
			// 16-bit greyscale
			pImage->mPixelFormat = RenderBase::PixelFormat::L16;
			break;
		case FIT_FLOAT:
			// Single-component floating point data
			pImage->mPixelFormat = RenderBase::PixelFormat::R32F;
			break;
			// not support now
			//case FIT_RGB16:
			//	pImage->mPixelFormat = PF_SHORT_RGB;
			//	break;
			//case FIT_RGBA16:
			//	pImage->mPixelFormat = PF_SHORT_RGBA;
			//	break;
		case FIT_RGBF:
			{
				//Convert to 8bit format
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				//  big endian. RGBA in memory, RGBA in native
				pImage->mPixelFormat = RenderBase::PixelFormat::R8G8B8A8;
#else
				// little endian. BGRA in memory, ARGB in native
				pImage->mPixelFormat = RenderBase::PixelFormat::A8R8G8B8;
#endif
			}
			//	pImage->mPixelFormat = PF_FLOAT32_RGB;
			break;
			//case FIT_RGBAF:
			//	pImage->mPixelFormat = PF_FLOAT32_RGBA;
			//	break;
		default:
			n_warning(" ImageResLoader::LoadCommon: Unknown or unsupported image format\n");
			return false;
		};

		unsigned char* srcData = FreeImage_GetBits(fiBitmap);
		unsigned srcPitch = FreeImage_GetPitch(fiBitmap);

		uint texSize = FreeImage_GetDIBSize(fiBitmap);

		// Final data - invert image and trim pitch at the same time
		SizeT dstPitch = pImage->mWidth * RenderBase::PixelFormat::GetNumElemBytes(pImage->mPixelFormat);
		SizeT dataSize = dstPitch * pImage->mHeight;

		if ( dataSize == 0 || pImage->mHeight < 1 || pImage->mWidth < 1)
		{
			return false;
		}

		GPtr<ImageData> pData = ImageData::Create();
		pData->Setup( dataSize );
		pImage->mData = pData;

		ubyte* pSrc;
		ubyte* pDst = pData->Ptr();

		if ( imageType == FIT_RGBF)
		{
			const float maxColorComponent = 6.0f;
			const float overMaxColorComponent = 1.0f / maxColorComponent;
			const float minColorComponent = 2.0f * 1e-6f;
			ubyte * bits = pDst;

			pSrc = srcData;

			// encoding Float Texture with RGBM
			// reference from network www.gamedev.net
			for ( IndexT y = 0; y < pImage->mHeight; y++ )
			{
				FIRGBF* srcPixel = (FIRGBF*)(pSrc + (pImage->mHeight - y - 1) * srcPitch);
				ubyte * destPixel = bits;

				for ( int x = 0; x < pImage->mWidth; x++ )
				{
					float redComponent = srcPixel[x].red;
					float greenComponent = srcPixel[x].green;
					float blueComponent = srcPixel[x].blue;

					float maxComponent = Math::n_max( Math::n_max(redComponent, greenComponent), Math::n_max(blueComponent, minColorComponent));
					float alphaComponent = ((int)(maxComponent * overMaxColorComponent * 255.0f) + 0.5f) * 1.0f / 255.0f;

#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
					destPixel[0] = (ubyte)(Math::n_min(alphaComponent , 1.0f) * 255.0f + 0.5f);
					destPixel[1] = (ubyte)(Math::n_min(redComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f + 0.5f);
					destPixel[2] = (ubyte)(Math::n_min(greenComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f + 0.5f);
					destPixel[3] = (ubyte)(Math::n_min(blueComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f + 0.5f);
#else
					destPixel[3] = (ubyte)(Math::n_min(alphaComponent, 1.0f) * 255.0f);
					destPixel[2] = (ubyte)(Math::n_min(redComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f);
					destPixel[1] = (ubyte)(Math::n_min(greenComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f);
					destPixel[0] = (ubyte)(Math::n_min(blueComponent * overMaxColorComponent / alphaComponent, 1.0f) * 255.0f);
#endif
					destPixel += 4;
				}
				bits += dstPitch;
			}
		}
		else
		{
#if RENDERDEVICE_OPENGLES
			SizeT nPixel = RenderBase::PixelFormat::GetNumElemBytes(pImage->mPixelFormat);
			for (IndexT i = 0; i < pImage->mWidth * pImage->mHeight * nPixel; i += nPixel)
			{
				uchar temp   = srcData[i];
				srcData[i]   = srcData[i+2];
				srcData[i+2] = temp;
			}
#endif


			for (IndexT y = 0; y < pImage->mHeight; ++y)
			{
				pSrc = srcData + (pImage->mHeight - y - 1) * srcPitch;
				memcpy(pDst, pSrc, dstPitch);
				pDst += dstPitch;
			}
		}

		FreeImage_Unload(fiBitmap);
		FreeImage_CloseMemory(fiMem);
		return true;
	}

	//------------------------------------------------------------------------
	bool 
		ImageResLoader::LoadETC(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage)
	{
		ubyte* pStreamData = NULL;
		AutoMemory autoMem( stream, &pStreamData );

		ETCHeader loadedETCHeader = ETCHeader(pStreamData);
		uint width  = loadedETCHeader.getWidth();
		uint height = loadedETCHeader.getHeight();

		uint texSize = (loadedETCHeader.getPaddedWidth() * loadedETCHeader.getPaddedHeight()) >> 1;

		ubyte* pRaw = n_new_array(ubyte, texSize);
		memcpy(pRaw, pStreamData + 16, texSize);

		GPtr<ImageData> pData = ImageData::Create();

		pData->SetData(pRaw, texSize);


		pImage->mData = pData;
		pImage->SetWidth(width);
		pImage->SetHeight(height);
		pImage->SetMipMapLevel(0);
		pImage->SetDepth(1);
		pImage->SetPixelFormat(RenderBase::PixelFormat::ETC1_RGB8);

		return true;

	}





}
