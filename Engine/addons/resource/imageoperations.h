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
#ifndef __imageoperations_H__
#define __imageoperations_H__

#include "core/refcounted.h"
#include "util/string.h"
#include "math/color.h"
#include "resource/imageres.h"

namespace Resources
{

	class ImageOperations : public Core::RefCounted
	{
		__DeclareClass(ImageOperations)

	public:
		ImageOperations();
		~ImageOperations();
#if  __OSX__

#else
		static bool CreateTGAImageResAndSave(const Util::String &fileName, const int width, const int height, const Math::Color32 &defaultColor);

		static bool SaveTGAImage(const Util::String &imagePath, const GPtr<Resources::ImageRes> &res);

		static void SaveDDSCubeImage(uint32 height_ , uint32 width_ ,const Util::String& fileName , void* data, int size);

		static void HorizontalFlipImage( void* data,const int size,const int width,const int height);
#endif
	};

}



#endif //__imageoperations_H__
