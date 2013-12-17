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
#ifndef __imageres_H__
#define __imageres_H__
#include "resource/resource.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "math/color.h"

namespace Resources
{
	class ImageRes;

	class ImageData: public Core::RefCounted
	{
		__DeclareClass(ImageData);
	public:
		ImageData();
		virtual ~ImageData();
		// setup data. if size <=0. the data 
		SizeT Size() const;
		const ubyte* Ptr(void) const;
		ubyte* Ptr(void);
		void SetData(ubyte* imageData, SizeT size);
	protected:
		void Setup(SizeT size);
		SizeT mSize;
		ubyte* mRaw;
	private:
		ImageData(const ImageData& );
		void operator=(const ImageData ); 
		friend class ImageRes;
		friend class ImageResLoader;
	};

	class ImageRes: public Resources::Resource
	{
		__DeclareSubClass(ImageRes, Resource);
	public:
		ImageRes();
		virtual ~ImageRes();

		/// if invalid, return 0
		SizeT GetWidth(void) const;

		/// if invalid, return 0
		SizeT GetHeight(void) const;

		/// if no mipmap, return 0. 
		SizeT GetMipMapLevel(void) const;

		/// Gets the depth of the image. usually 1 for 1D and 2D image. 
		SizeT GetDepth(void) const;

		/// the face of image. usually 6 for cubemap and 1 for a normal image
		SizeT GetNumFace(void) const;

		/// if invalid, return InvalidPixelFormat
		RenderBase::PixelFormat::Code GetPixelFormat(void) const;

		// return the image data.(no file header). if invalid, return NULL
		const GPtr<ImageData>& GetImageData() const;

		bool Validata(void) const;

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;

		// Calculate memory size base on mipmap, face, format etc.
		static SizeT S_CalculateSize(SizeT mipmaps, SizeT faces, SizeT width, SizeT height, SizeT depth, RenderBase::PixelFormat::Code format);

		///
		bool GetPixels(const int x, const int y, const int width, const int height, const int mipLevel, Math::ColorF *pixels) const;

		///
		bool GetPixels(const int mipLevel, Math::Color32 *pixels);

		///
		bool GetPixels(const int x, const int y, const int width, const int height, const int mipLevel, Math::Color32 *pixels);

		///
		bool SetPixels(const int x, const int y, const int width, const int height, const int miplevel, const Math::ColorF *pixels);

		///
		bool SetPixels(const int x, const int y, const int width, const int height, const int miplevel, const Math::Color32 *pixels);

		///
		Math::scalar GetAlphaValue(Math::scalar u, Math::scalar v);


		void SetWidth(SizeT width);
		void SetHeight(SizeT height);
		void SetMipMapLevel(SizeT mipMapLevel);
		void SetDepth(SizeT depth);
		void SetNumFace(SizeT numFace);
		void SetPixelFormat(RenderBase::PixelFormat::Code pixelFormat);
		void SetImageData(ubyte* imageData, SizeT size);
	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

		/**
		* _DecompressDDSTextureFormat		decomppress texture
		* @param:	all is so simple that no need note
		* @return:	bool	decompress is sucess or failed						
		* @see: 
		* @remark:  
		*/
		bool _DecompressDDSTextureFormat( const RenderBase::PixelFormat::Code srcFormat, const int srcWidth, const int srcHeight,
			const uint32* sourceData,  uint32* destData );



	protected:
		SizeT mWidth;
		SizeT mHeight;
		SizeT mDepth;
		SizeT mNumFace;
		SizeT mMipMapLevel;

		RenderBase::PixelFormat::Code mPixelFormat;
		GPtr<ImageData> mData;

		friend class ImageResLoader;
	};
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageData::Size() const
	{
		return mSize;
	}
	//------------------------------------------------------------------------
	inline
		const ubyte* 
		ImageData::Ptr(void) const
		//------------------------------------------------------------------------
	{
		return mRaw;
	}
	//------------------------------------------------------------------------
	inline
		ubyte* 
		ImageData::Ptr(void)
	{
		return mRaw;
	}
	//------------------------------------------------------------------------
	inline
		void
		ImageData::SetData(ubyte* raw, SizeT size)
	{
		this->mRaw = raw;
		this->mSize = size;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageRes::GetWidth(void) const
	{
		return mWidth;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageRes::GetHeight(void) const
	{
		return mHeight;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageRes::GetMipMapLevel(void) const
	{
		return mMipMapLevel;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageRes::GetDepth(void) const
	{
		return mDepth;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ImageRes::GetNumFace(void) const
	{
		return mNumFace;
	}
	//------------------------------------------------------------------------
	inline
		RenderBase::PixelFormat::Code
		ImageRes::GetPixelFormat(void) const
	{
		return mPixelFormat;
	}
	//------------------------------------------------------------------------
	inline
		const GPtr<ImageData>& 
		ImageRes::GetImageData() const
	{
		return mData;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ImageRes::Validata(void) const
	{
		if ( this->GetWidth() <= 0 || this->GetHeight() <= 0 || this->GetDepth() <= 0 
			||this->GetNumFace() <=0 || this->GetPixelFormat() == RenderBase::PixelFormat::InvalidPixelFormat
			|| this->GetMipMapLevel() < 0 || !this->GetImageData().isvalid() 
			|| this->GetImageData()->Size() <= 0 )
		{
			return false;
		}
		return true;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetWidth(SizeT width)
	{
		this->mWidth = width;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetHeight(SizeT height)
	{
		this->mHeight = height;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetMipMapLevel(SizeT mipMapLevel)
	{
		this->mMipMapLevel = mipMapLevel;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetDepth(SizeT depth)
	{
		this->mDepth = depth;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetNumFace(SizeT numFace)
	{
		this->mNumFace = numFace;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetPixelFormat(RenderBase::PixelFormat::Code pixelFormat)
	{
		this->mPixelFormat = pixelFormat;
	}
	//------------------------------------------------------------------------------
	inline void ImageRes::SetImageData(ubyte* imageData, SizeT size)
	{
		if(!(this->mData.isvalid()))
		{
			this->mData = ImageData::Create();
		}
		this->mData->SetData(imageData, size);
	}
}








#endif // __imageres_H__
