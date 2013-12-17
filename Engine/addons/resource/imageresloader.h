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
#ifndef __imageresloader_H__
#define __imageresloader_H__
#include "resource/imageres.h"
#include "resource/resourceserver.h"
#include "core/singleton.h"

namespace Resources
{
	class ImageResCodecReg: public ResCodecReg
	{
		__DeclareSubClass(ImageResCodecReg, ResCodecReg);
		__DeclareImageSingleton(ImageResCodecReg);
	public:
		ImageResCodecReg();
		virtual ~ImageResCodecReg();
		/// ResCodecReg::Open
		virtual void Open(void);
		/// ResCodecReg::Close
		virtual void Close(void);

		IndexT FindType(const Util::String& strExt, int& ImageFiletype);
	protected:
		bool mIsOpen;
		Util::Dictionary<Util::String, int> mExtReg;
	};

	class ImageResLoader: public ResourceLoader
	{
		__DeclareSubClass(ImageResLoader, ResourceLoader);
	public:
		ImageResLoader(){ }
		virtual ~ImageResLoader(){ }

		/// @ResourceLoader::LoadResource
		virtual bool LoadResource(Resource* res );

	protected:
		bool LoadImage(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage);

		// Load DXT format image
		bool LoadDXT(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage);

		// Load PVRTC format image. IPhone
		bool LoadPVRTC(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage);

		// Load ETC format image. OpenGL ES
		bool LoadETC(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage);

		// Load common format image such as JPG, BMP, PNG.Compressed formats will be decompressed when loaded.
		bool LoadCommon(GPtr<IO::Stream>& stream, GPtr<ImageRes>& pImage);

		// for swap big bigEndian and LittleEndian 
		void FlipEndian(void * pData, size_t size, size_t count) const
		{
#if __WIN32__

#else
			// if special platform need swap	
			//for(unsigned int index = 0; index < count; index++)
			//{
			//	flipEndian((void *)((long)pData + (index * size)), size);
			//}
#endif

		}  

		void FlipEndian(void * pData, size_t size) const
		{
#if __WIN32__

#else
			// if special platform need swap	
			//char swapByte;
			//for(unsigned int byteIndex = 0; byteIndex < size/2; byteIndex++)
			//{
			//	swapByte = *(char *)((long)pData + byteIndex);
			//	*(char *)((long)pData + byteIndex) = *(char *)((long)pData + size - byteIndex - 1);
			//	*(char *)((long)pData + size - byteIndex - 1) = swapByte;
			//}
#endif
		}

	};
}






#endif // __imageresloader_H__
