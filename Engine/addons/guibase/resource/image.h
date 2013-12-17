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
#ifndef __image_H__
#define __image_H__
#include "guibase/guibaseconfig.h"
#include "graphicsystem/GraphicSystem.h"
#include "rendersystem/base/RenderDeviceTypes.h"

namespace GuiBase
{
	class Image : public Core::RefCounted
	{
		__DeclareClass(Image);
	public:
		virtual ~Image();
		RenderBase::TextureHandle GetTextureHandle() const;
		void Destroy();
		void UpdateData(void* data, SizeT size);
		static GPtr<Image> LoadImage();
		static GPtr<Image> CreateImage(void* data, SizeT size, SizeT width, SizeT height, RenderBase::PixelFormat::Code format);


		friend class GPtr<Image>;
	private:	
		RenderBase::TextureHandle m_texHandle;
		bool m_shared;
		Util::String m_name;
		RenderBase::PixelFormat::Code m_format;
		SizeT m_width;
		SizeT m_height;
		Image();
		Image(const Image&);
	};

	inline RenderBase::TextureHandle Image::GetTextureHandle() const
	{
		return m_texHandle;
	}

}

#endif //__image_H__