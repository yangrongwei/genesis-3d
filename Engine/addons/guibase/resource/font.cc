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
#include "font.h"
#include "io/ioserver.h"
#include "io/stream.h"
#include "io/filestream.h"
#include "io/memorystream.h"
#include "io/iointerfaceprotocol.h"
#include "io/iointerface.h"

static FT_Library  library = NULL;
static Util::Array<GuiBase::Font*> g_fontList;

FT_Library GetLib()
{
	if (NULL == library)
	{
		FT_Error error = FT_Init_FreeType( &library );
		if ( error )
		{
			assert(0);
		}
	}
	return library;
}

namespace GuiBase
{

	__ImplementClass(GuiBase::Font,'FONT', Core::RefCounted);
	Font::Font()
		: m_face(NULL)
	{

	}
	FT_Library Font::GetFTLib()
	{
		return GetLib();
	}
	GPtr<Font> Font::LoadFont(const Util::String& url)
	{
		for (int i = 0; i < g_fontList.Size(); ++i)
		{
			if (g_fontList[i]->m_url == url)
			{
				return GPtr<Font>(g_fontList[i]);

			}
		}
		GPtr<Font> font = Font::Create();
		if (font->_init(url))
		{
			g_fontList.Append(font.get());
			return font;
		}
		assert(0);
		return NULL;
	}
	Font::~Font()
	{
		for (int x = 0; x < g_fontList.Size(); ++x)
		{
			if (this == g_fontList[x])
			{
				g_fontList.EraseIndex(x);
				break;
			}
		}
		FT_Done_Face(m_face);
		n_delete_array(m_buffer);
	}
	bool Font::_init(const Util::String& url)
	{
		m_url = url;

		GPtr<IO::Stream> stream = IO::IoServer::Instance()->CreateFileStream(IO::URI(url));
		stream->Open();
		SizeT file_size = stream->GetSize();
		stream->Seek(0, IO::Stream::Begin);

		m_buffer = n_new_array(unsigned char, file_size);
		stream->Read(m_buffer, file_size);

		//FT_New_Memory_Face(GetLib(), buffer, file_size, 0, &m_face);
		if (FT_New_Memory_Face(GetLib(), m_buffer, file_size, 0, &m_face))
			//if (!FT_New_Face(GetLib(), url.Get(), 0, &m_face))
		{
			assert(0);
			return false;
		}

		FT_Matrix matrix;
		FT_Vector pen;
		pen.x = 0;
		pen.y = 0;

		//给它设置个旋转矩阵
		float angle = 0;//-20/180.* 3.14;
		matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
		matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
		matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
		matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
		FT_Set_Transform(m_face, &matrix, &pen);
		return true;
	}
	bool Font::DrawChar(UTF16 word, SizeT size)//, FT_Glyph& glyph)//, FT_Glyph_Metrics& metrices)
	{
		FT_Set_Pixel_Sizes(m_face, size, size);
		if (FT_Load_Glyph(m_face, FT_Get_Char_Index(m_face, word), FT_LOAD_RENDER) == 0)//
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
}