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
#include "resource/imageres.h"
#include "util/algorithm.h"
#include "DXTextureDecompress.h"

namespace Resources
{
	using namespace Math;

	__ImplementClass(Resources::ImageData, 'IMGD', Core::RefCounted);
	__ImplementClass(Resources::ImageRes, 'IMGR', Resources::Resource);
	//------------------------------------------------------------------------
	ImageData::ImageData()
		: mSize(0)
		, mRaw(NULL)
	{

	}
	//------------------------------------------------------------------------
	ImageData::~ImageData()
	{
		if ( mRaw )
		{
			n_delete_array(mRaw);
			mRaw = NULL;
		}
		mSize = 0;
	}
	//------------------------------------------------------------------------
	void ImageData::Setup(SizeT size)
	{
		if ( size <= 0 )
		{
			mSize = 0;
			if ( mRaw )
			{
				n_delete_array(mRaw);
				mRaw = NULL;
			}
		}
		else if ( mSize != size )
		{
			if ( mRaw )
			{
				n_delete_array(mRaw);
				mRaw = NULL;
			}

			mSize = size;
			mRaw = n_new_array(ubyte,mSize);
		}
		else	//	mSize = size
		{
			n_assert(mRaw);
		}
	}
	//------------------------------------------------------------------------
	ImageRes::ImageRes()
		: mWidth(0)
		, mHeight(0)
		, mMipMapLevel(0)
		, mDepth(0)
		, mNumFace(1)
		, mPixelFormat(RenderBase::PixelFormat::InvalidPixelFormat)
	{

	}
	//------------------------------------------------------------------------
	ImageRes::~ImageRes()
	{
	}
	//------------------------------------------------------------------------
	SizeT 
		ImageRes::CalculateRuntimeSize(void) const
	{
		SizeT size = 24;//sizeof(mWidth) +sizeof(mHeight)+ sizeof(mDepth)+ sizeof(mNumFace)+ sizeof(mMipMapLevel)+ sizeof(mPixelFormat);

		if ( mData.isvalid() )
		{
			size += sizeof(ImageData);
			size += mData->Size();
		}
		return size += Super::CalculateRuntimeSize();
	}
	//------------------------------------------------------------------------
	bool 
		ImageRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{
		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<ImageRes> tempImage = tempRes.downcast<ImageRes>();
			n_assert(tempImage.isvalid());

			Util::Swap(mWidth , tempImage->mWidth);
			Util::Swap(mHeight, tempImage->mHeight);
			Util::Swap(mDepth, tempImage->mDepth);
			Util::Swap(mNumFace, tempImage->mNumFace);
			Util::Swap(mMipMapLevel, tempImage->mMipMapLevel);
			Util::Swap(mPixelFormat, tempImage->mPixelFormat);
			Util::Swap(mData,  tempImage->mData);

			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------
	void 
		ImageRes::UnLoadImpl(void)
	{
		mData = NULL;
	}
	//------------------------------------------------------------------------
	SizeT ImageRes::S_CalculateSize(SizeT mipmaps, SizeT faces, SizeT width, SizeT height, SizeT depth, RenderBase::PixelFormat::Code format)
	{
		SizeT size = 0;
		for(SizeT mip=0; mip <= mipmaps; ++mip)
		{
			size += RenderBase::PixelFormat::GetMemorySize(width, height, depth, format)*faces; 
			if(width!=1) width /= 2;
			if(height!=1) height /= 2;
			if(depth!=1) depth /= 2;
		}
		return size;
	}

	//------------------------------------------------------------------------------
	bool ImageRes::GetPixels(const int baseX, const int baseY, const int width, const int height, const int mipLevel, Math::ColorF *pixels) const
	{
		n_assert(mData.isvalid());

		ubyte* pDst = NULL;
		const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
		const SizeT dstPitch = mWidth * elemBytes;

		if (mipLevel == 0)
		{
			if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat)
			{
				for (int y=0; y<height; ++y)
				{
					pDst = mData->Ptr() + (baseY+y) * dstPitch + baseX * elemBytes;
					for (int x=0; x<width; ++x)
					{
						pixels->b = n_scalarfromByte(pDst[0]);
						pixels->g = n_scalarfromByte(pDst[1]);
						pixels->r = n_scalarfromByte(pDst[2]);
						pixels->a = n_scalarfromByte(pDst[3]);

						pDst += 4;
						pixels++;
					}
				}
			}
			else
			{
				n_warning("GetPixels(): PixelFormat do not support.");
			}
		}
		else
		{}

		return true;
	}

	//------------------------------------------------------------------------------
	bool ImageRes::GetPixels(const int mipLevel, Math::Color32 *pixels)
	{
		n_assert(mData.isvalid());

		const int height = GetHeight();
		const int width = GetWidth();

		if ( !RenderBase::PixelFormat::IsCompressed(mPixelFormat) )
		{// not compress

			if (mipLevel == 0)
			{
				ubyte* pDst = NULL;
				const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
				const SizeT dstPitch = mWidth * elemBytes;
				if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat)
				{
					for (int y=0; y<height; ++y)
					{
						pDst = mData->Ptr() + y * dstPitch;
						for (int x=0; x<width; ++x)
						{
							pixels->b = (pDst[0]);
							pixels->g = (pDst[1]);
							pixels->r = (pDst[2]);
							pixels->a = (pDst[3]);

							pDst += 4;
							pixels++;
						}
					}
				}
				else
				{
					n_warning("GetPixels(): PixelFormat do not support.");
				}
			}
			else
			{}
		} 
		else
		{
			
			if ( mPixelFormat == RenderBase::PixelFormat::DXT1 ||
				 mPixelFormat == RenderBase::PixelFormat::DXT2 ||
				 mPixelFormat == RenderBase::PixelFormat::DXT3 ||
				 mPixelFormat == RenderBase::PixelFormat::DXT4 ||
				 mPixelFormat == RenderBase::PixelFormat::DXT5 )
			{
				if ( !mData.isvalid() || !mData->Ptr())
				{
					n_assert(0);
					return false;
				}

				// dds format min mipmapsize is 4
				const int minMipmapSize = 4; 
				int mipmapW = width >> mipLevel;
				int mipmapH = height >> mipLevel;

				// calcualte mipmap offset
				SizeT totalOffset = 0;
				if (width >= 1 &&  height >= 1)
				{
					for (int i=0;i < mipLevel;i++)
					{
						totalOffset += RenderBase::PixelFormat::GetMemorySize (Math::n_max (width >> i, 1), Math::n_max (height >> i, 1),1, mPixelFormat);
					}
				}
				
				//
				ubyte* data = mData->Ptr() +  totalOffset;
				
				if (mipmapW % minMipmapSize == 0 && mipmapH % minMipmapSize == 0)
				{
					_DecompressDDSTextureFormat( mPixelFormat, mipmapW, mipmapH, reinterpret_cast<const uint32*>(data), reinterpret_cast<uint32*>(pixels) );
					return true;
				}
				else
				{
					// target mipmap width or height size not be multipled 4,but dds format must be 4x4 block.
					int nMultiped16 = ( (mipmapW + 3)/4 ) * ( (mipmapH + 3)/4 ) * 16;
					uint32* tmpColorBuf = n_new_array(uint32,nMultiped16);
					_DecompressDDSTextureFormat( mPixelFormat, mipmapW, mipmapH, reinterpret_cast<const uint32*>(data), tmpColorBuf);
					memcpy(reinterpret_cast<uint32*>(pixels),tmpColorBuf,sizeof(uint32)*mipmapW*mipmapH);

					n_delete_array(tmpColorBuf);
					return true;
				}
			} 
			else
			{
				n_assert2(0,"can't decompress as not supported other compressed format!");
				return false;
			}
		}



		return true;
	}

	bool ImageRes::GetPixels( const int baseX, const int baseY, const int width, const int height, const int mipLevel, Math::Color32 *pixels )
	{
		n_assert(mData.isvalid());

		ubyte* pDst = NULL;
		const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
		const SizeT dstPitch = mWidth * elemBytes;

		if (mipLevel == 0)
		{
			if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat)
			{
				for (int y=0; y<height; ++y)
				{
					pDst = mData->Ptr() + (baseY+y) * dstPitch + baseX * elemBytes;
					for (int x=0; x<width; ++x)
					{
						pixels->b = (pDst[0]);
						pixels->g = (pDst[1]);
						pixels->r = (pDst[2]);
						pixels->a = (pDst[3]);

						pDst += 4;
						pixels++;
					}
				}
			}
			else
			{
				n_warning("GetPixels(): PixelFormat do not support.");
			}
		}
		else
		{}	

		return true;
	}

	//------------------------------------------------------------------------
	bool ImageRes::_DecompressDDSTextureFormat( const RenderBase::PixelFormat::Code srcFormat, const int srcWidth, const int srcHeight, 
		const uint32* sourceData, uint32* destData )
	{
		n_assert(srcWidth%4 == 0 && srcHeight%4 == 0);

		int flags(1);
		switch( srcFormat )
		{
		case RenderBase::PixelFormat::DXT1:
			flags = squish::kDxt1;
			break;
		case RenderBase::PixelFormat::DXT3:
			flags = squish::kDxt3;
			break;
		case RenderBase::PixelFormat::DXT5:
			flags = squish::kDxt5;
			break;
		default:
			{
				n_assert2(0,"now not support other dds compress format!");
				return false;
			}
			break;
		}
		DXTextureDecompress::DecompressImage(destData,srcWidth,srcHeight,sourceData,flags);
		return true;
	}



	//------------------------------------------------------------------------------
	bool ImageRes::SetPixels(const int baseX, const int baseY, const int width, const int height, const int miplevel, const Math::ColorF *pixels)
	{
		n_assert(mData.isvalid());

		ubyte* pDst = NULL;
		const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
		const SizeT dstPitch = mWidth * elemBytes;

		if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat) 
		{
			for (int y=0; y<height; ++y)
			{
				pDst = mData->Ptr() + (baseY+y) * dstPitch + baseX * 4;
				for (int x=0; x<width; ++x)
				{
					pDst[0] = n_scalartoByte(pixels->b);
					pDst[1] = n_scalartoByte(pixels->g);
					pDst[2] = n_scalartoByte(pixels->r);
					pDst[3] = n_scalartoByte(pixels->a);

					pDst += 4;
					pixels++;
				}
			}
		}
		else
		{
			n_warning("SetPixels(): PixelFormat do not support.");
		}

		return true;
	}

	//------------------------------------------------------------------------------
	bool ImageRes::SetPixels(const int baseX, const int baseY, const int width, const int height, const int miplevel, const Math::Color32 *pixels)
	{
		n_assert(mData.isvalid());

		ubyte* pDst = NULL;
		const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
		const SizeT dstPitch = mWidth * elemBytes;

		if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat) 
		{
			for (int y=0; y<height; ++y)
			{
				pDst = mData->Ptr() + (baseY+y) * dstPitch + baseX * 4;
				for (int x=0; x<width; ++x)
				{
					pDst[0] = pixels->b;
					pDst[1] = pixels->g;
					pDst[2] = pixels->r;
					pDst[3] = pixels->a;

					pDst += 4;
					pixels++;
				}
			}
		}
		else
		{
			n_warning("SetPixels(): PixelFormat do not support.");
		}

		return true;
	}
	//------------------------------------------------------------------------------

	Math::scalar ImageRes::GetAlphaValue(Math::scalar u, Math::scalar v)
	{
		n_assert(mData.isvalid());

		ubyte* pDst = NULL;
		const SizeT elemBytes = RenderBase::PixelFormat::GetNumElemBytes(mPixelFormat);
		const SizeT dstPitch = mWidth * elemBytes;
		const int height = GetHeight();
		const int width = GetWidth();


		IndexT x = Math::n_fchop(u * width);;
		IndexT y = Math::n_fchop(v * height);

		if (x >= width || y >= height)
		{
			x %= width;
			y %= height;
		}

		if (RenderBase::PixelFormat::A8R8G8B8 == mPixelFormat)
		{
			pDst = mData->Ptr() + y * dstPitch + x * elemBytes;
		}	
		else
		{
			n_warning("GetPixels(): PixelFormat do not support.");

		}

		if (pDst == NULL)
		{
			return 0.0f;
		}

		return pDst[3] / 255.0f;

	}
}
