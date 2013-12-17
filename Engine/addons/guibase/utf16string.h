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
#ifndef __utf16_string_H__
#define __utf16_string_H__
#include "guibase/guibaseconfig.h"


namespace GuiBase
{
	class UTF16String
	{
	public:
		//UTF16String (char* str);
		UTF16String();
		UTF16String(const UTF16String &other);
		UTF16String(const UTF16* str);
		~UTF16String();
		SizeT StringLen() const;
		UTF16 operator [] (int index) const;
		void  operator += (const UTF16String& other);
		void  operator += (const UTF16* other);
		void  operator = (const UTF16String& other);
		static SizeT UTF16Length(const UTF16* ptr);
		static bool UTF16Cmp(const UTF16* lhs, const UTF16* rhs); 
		friend bool operator == (const UTF16String& lhs, const UTF16String& rhs);
		friend bool operator != (const UTF16String& lhs, const UTF16String& rhs);
	private:
		SizeT _wordSize() const;
		void _checkBuffer(SizeT len);
		UTF16* m_text;
		int m_buffer_len;
		int m_len;
		//void InitFromCharPointer(char* str);	

	};
	inline SizeT UTF16String::StringLen() const
	{
		return m_len;
	}
	inline SizeT UTF16String::_wordSize() const
	{
		return sizeof(UTF16);
	}
	inline UTF16 UTF16String::operator [] (int index) const
	{
		assert(index < m_len);
		return m_text[index];
	}
	inline bool UTF16String::UTF16Cmp(const UTF16* lhs, const UTF16* rhs)
	{
		UTF16* l = (UTF16*) lhs;
		UTF16* r = (UTF16*) rhs;
		do 
		{
			if (*l != *r)
			{
				return false;
			}
			++l;
			++r;
		} while (0 != *l);
		return true;
	}
	inline bool operator == (const UTF16String& lhs, const UTF16String& rhs)
	{
		if (lhs.m_len != rhs.m_len)
			return false;
		return (rhs.m_text == NULL) || UTF16String::UTF16Cmp(lhs.m_text, rhs.m_text);
	}

	inline bool operator != (const UTF16String& lhs, const UTF16String& rhs)
	{
		if (lhs.m_len != rhs.m_len)
			return true;
		return !UTF16String::UTF16Cmp(lhs.m_text, rhs.m_text);
	}

}

#endif //__utf16_string_H__
