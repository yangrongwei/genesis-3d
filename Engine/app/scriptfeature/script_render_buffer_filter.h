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
#ifndef _SCRIPT_RENDER_BUFFER_FILTER_H_
#define _SCRIPT_RENDER_BUFFER_FILTER_H_
#include "graphicsystem/base/ImageFilters.h"

namespace App
{
	class CameraComponent;
	class ScriptComponent;
	class ScriptRenderBufferFilter : public Graphic::ImageFilter
	{
	public:
		ScriptRenderBufferFilter();
		void Setup(CameraComponent* sender);
		static Graphic::ImageFilter::FilterIndexForSort ScriptIndexToSortIndex(int script_index);
		static int SortIndexToScriptIndex(Graphic::ImageFilter::FilterIndexForSort sort_index);
		virtual ~ScriptRenderBufferFilter();
		virtual bool RenderFilter(Graphic::RenderToTexture* source, Graphic::RenderToTexture* destination);
	private:
		CameraComponent* mSender;
	};
	inline Graphic::ImageFilter::FilterIndexForSort ScriptRenderBufferFilter::ScriptIndexToSortIndex(int script_index)
	{
		return TypeConvert<Graphic::ImageFilter::FilterIndexForSort>::Conver(
			Graphic::ImageFilter::FilterIndexForSort_ScriptBegin + script_index);
	}
	inline int ScriptRenderBufferFilter::SortIndexToScriptIndex(Graphic::ImageFilter::FilterIndexForSort sort_index)
	{
		return sort_index - Graphic::ImageFilter::FilterIndexForSort_ScriptBegin;
	}
}
#endif