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
#include "utf16string.h"

GuiBase::UTF16 g_defaulText[1] = {0};

namespace GuiBase
{

	UTF16String::UTF16String()
		: m_text(g_defaulText)
		, m_len(0)
		, m_buffer_len(0)
	{
	}

	UTF16String::UTF16String (const UTF16* str) 
		: m_text(g_defaulText)
		, m_buffer_len(0)
	{
		m_len = UTF16Length(str);
		_checkBuffer(m_len + 1);
		Memory::Copy(str, m_text, m_len * _wordSize());
		m_text[m_len] = NULL;
	}

	UTF16String::UTF16String (const UTF16String &other) 
		: m_text(g_defaulText)
		, m_buffer_len(0)
	{
		m_len = other.m_len;
		_checkBuffer(m_len + 1);
		Memory::Copy(other.m_text, m_text, m_len * _wordSize());
		m_text[m_len] = NULL;
	}
	void UTF16String::operator = (const UTF16String& other)
	{
		m_text = g_defaulText;
		m_buffer_len = 0;
		m_len = other.m_len;

		_checkBuffer(m_len + 1);
		Memory::Copy(other.m_text, m_text, m_len * _wordSize());
		m_text[m_len] = NULL;
	}
	void UTF16String::operator += (const UTF16String& other)
	{
		SizeT len = m_len + other.m_len;
		if (len + 1 > m_buffer_len)
		{
			UTF16* old_text = m_text;
			m_buffer_len = len * 2 + 1;
			m_text = n_new_array(UTF16, m_buffer_len);
			Memory::Copy(old_text, m_text, m_len);
			n_delete_array(old_text);
		}
		Memory::Copy(other.m_text, m_text + m_len, other.m_len * _wordSize());
		m_len = len;
		m_text[len] = NULL;	
	}
	void UTF16String::operator += (const UTF16* other)
	{
		SizeT other_len = UTF16Length(other);
		SizeT len = m_len + other_len;
		if (len + 1 > m_buffer_len)
		{
			UTF16* old_text = m_text;
			m_buffer_len = len * 2 + 1;
			m_text = n_new_array(UTF16, m_buffer_len);
			Memory::Copy(old_text, m_text, m_len);
			n_delete_array(old_text);
		}
		Memory::Copy(other, m_text + m_len, other_len * _wordSize());
		m_len = len;
		m_text[len] = NULL;	
	}

	UTF16String::~UTF16String () 
	{
		if (m_text)
		{
			n_delete_array(m_text);
		}

	}

	SizeT UTF16String::UTF16Length(const UTF16* ptr)
	{
		UTF16* temp = (UTF16*)ptr;
		n_assert( temp != NULL);
		while(0 != *temp)
		{
			++temp;
		}
		return (temp - ptr);// / sizeof(UTF16);
	}


	void UTF16String::_checkBuffer(SizeT len)
	{
		if (len > m_buffer_len)
		{
			m_buffer_len = len * 2 + 1;
			if (m_text && m_text != g_defaulText)
			{
				n_delete_array(m_text);
			}
			m_text = n_new_array(UTF16, m_buffer_len);			
		}
	}

}
