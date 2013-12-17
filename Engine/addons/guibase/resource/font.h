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
#ifndef __font_H__
#define __font_H__

#include "guibase/guibaseconfig.h"
#include "guibase/utf16string.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_BITMAP_H

namespace GuiBase
{

	class Font : public Core::RefCounted
	{
		__DeclareClass(Font);
	public:
		virtual ~Font();
		bool DrawChar(UTF16 word, SizeT size);
		FT_Face GetFace() const;
		const Util::String& GetURL() const;
		static GPtr<Font> LoadFont(const Util::String& url);
		static FT_Library GetFTLib();
		friend class GPtr<Font>;
	private:		
		bool _init(const Util::String& url);	
		FT_Face m_face;
		unsigned char* m_buffer;
		Util::String m_url;
		Font();
		Font(const Font&);
	};
	inline FT_Face Font::GetFace() const
	{
		return m_face;
	}

	inline const Util::String& Font::GetURL() const
	{
		return m_url;
	}

}

#endif //__font_H__