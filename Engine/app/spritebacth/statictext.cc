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
#include "statictext.h"

static const SizeT g_defaultWordSize = 24;

static const SizeT g_defaultTextSize = 256;
static const int g_glyphSpacing = 1;
namespace App
{

	const StaticText::TextPair StaticText::TextPair::EmptyInstance;
	const UTF16 StaticText::s_blankChar = (UTF16)' ';
	StaticText::ImageData::ImageData()
		: m_buffer(NULL)
		, m_width(0)
		, m_height(0)
		, m_nextU(0)
		, m_nextV(0)
		, m_lineHeight(0)
		, m_bufferLen(0)
	{

	}
	StaticText::ImageData::~ImageData()
	{
		_release();
	}
	void StaticText::ImageData::_release()
	{
		if (m_buffer)
		{
			n_delete_array(m_buffer);
		}
		m_buffer = NULL;
		m_bufferLen = 0;
		m_width = 0;
		m_height = 0;
	}

	void StaticText::ImageData::ClearInfo()
	{
		memset(m_buffer, 0, m_bufferLen * sizeof(BufferType));
		m_charInfoTable.Clear();
		m_nextU = 0;
		m_nextV = 0;
		m_lineHeight = 0;
	}

	void StaticText::ImageData::Reset(SizeT width, SizeT height)
	{
		SizeT len = width * height;
		if (len > m_bufferLen)
		{
			if (m_buffer)
			{
				n_delete_array(m_buffer);
			}
			m_buffer = n_new_array(BufferType, len);
			m_bufferLen = len;
		}
		memset(m_buffer, 0, len * sizeof(BufferType));
		m_width = width;
		m_height = height;
		m_charInfoTable.Clear();

	}
	bool StaticText::ImageData::FindWord(UTF16 key, GlyphInfo& word_info)
	{
		if (m_charInfoTable.Contains(key))
		{
			word_info = m_charInfoTable[key];
			return true;
		}
		else
		{
			return false;
		}
	}
	RectF StaticText::ImageData::ToUVF(const RectInt& rect_int) const
	{
		RectF uv;
		uv.top = ((float)rect_int.top) / ((float) m_height);
		uv.left = ((float)rect_int.left) / ((float) m_width);		
		uv.right = ((float)rect_int.right) / ((float) m_width);
		uv.bottom = ((float)rect_int.bottom) / ((float) m_height);
		return uv;
	}
	bool StaticText::ImageData::SetData(UTF16 key, const uint8* data, const FT_GlyphSlot glyph, GlyphInfo& info)
	{		

		if (m_nextU + glyph->bitmap.width > m_width)//下一行
		{
			m_nextU = 0;
			m_nextV += m_lineHeight;
			m_lineHeight = 0;
			if (glyph->bitmap.width > m_width)
			{
				return false;
			}
		}
		if (m_lineHeight < glyph->bitmap.rows + g_glyphSpacing)
		{
			m_lineHeight = glyph->bitmap.rows + g_glyphSpacing;
		}
		if (m_nextV + m_lineHeight > m_height)
		{
			return false;
		}
		//RectInt rect_int;
		//info.rect_int.top = m_nextV;
		//info.rect_int.left = m_nextU;
		//info.rect_int.right = m_nextU + width;// - 1;
		//info.rect_int.bottom = m_nextV + height;// - 1;

		info.charInfo.width = glyph->metrics.width / 64.0f;
		info.charInfo.height = glyph->metrics.height / 64.0f;
		info.charInfo.advance = glyph->advance.x / 64.0f;
		info.charInfo.bearingX = glyph->metrics.horiBearingX / 64.0f;
		info.charInfo.bearingY = glyph->metrics.horiBearingY / 64.0f;

		//info.metrices = metrices;

		info.uvRect.top = ((float)m_nextV) / ((float) m_height);
		info.uvRect.left = ((float)m_nextU) / ((float) m_width);		
		info.uvRect.right = ((float)(m_nextU + info.charInfo.width)) / ((float) m_width);
		info.uvRect.bottom = ((float)(m_nextV + info.charInfo.height)) / ((float) m_height);


		m_charInfoTable.Add(key, info);

		SizeT dest_addr  = (SizeT)m_buffer + (m_nextU + m_nextV * m_width);//(info.rect_int.left + info.rect_int.top * m_width);
		SizeT src_addr = (SizeT)data;
		SizeT end = src_addr + glyph->bitmap.width * glyph->bitmap.rows;
		while(src_addr < end)
		{
			Memory::Copy((void*)src_addr, (void*)dest_addr, glyph->bitmap.width);
			dest_addr += m_width;
			src_addr += glyph->bitmap.width;
		}

		m_nextU += (glyph->bitmap.width + g_glyphSpacing);//一位的间隔
		return true;
	}

	__ImplementClass(App::StaticText,'STTE', App::DrawUnit);
	StaticText::StaticText()
		: m_charSize(g_defaultWordSize)
		, m_textColor(SpriteRenderInfo::ColorWhite)
		, m_font(NULL)
		, m_textWidth(0)
		, m_needRebuild(true)
		, m_sizeChange(true)
		, m_bShow(true)
	{

	}
	StaticText::~StaticText()
	{
		m_font = NULL;
		//m_renderable = NULL;

	}
	void StaticText::SetCharSize(SizeT size)
	{
		m_sizeChange |= (m_charSize != size);
		m_charSize = size;
		m_needRebuild = true;
	}
	void StaticText::SetFont(const Util::String& font_name)
	{
		m_needRebuild = true;
		m_font = Font::LoadFont(font_name);
	}
	void StaticText::SetText(const UTF16String& text)
	{
		if (text != m_text)
		{		
			m_text = text;
			m_needRebuild = true;
		}
	}
	void StaticText::SetTextColor(const ColorF& color)
	{
		m_textColor = color;
		m_needRebuild = true;
	}

	static void _min_tex_size(int char_size, int char_count, int& width, int& height)
	{
		width = 64;
		height = 64;

		while(true)
		{
			int row = width / (char_size + g_glyphSpacing);
			int col = height / (char_size + g_glyphSpacing);
			if (row * col >= char_count)
			{
				return;
			}
			if (width <= height)
			{
				width <<= 1;
			}
			else
			{
				height <<= 1;
			}
		}
	}

	static int _code_count(const GuiBase::UTF16String& str)
	{
		Util::Array<GuiBase::UTF16> cache;
		for (int i = 0; i < str.StringLen(); ++i)
		{
			if (InvalidIndex == cache.FindIndex(str[i]))
			{
				cache.Append(str[i]);
			}
		}
		return cache.Size();
	}


	void StaticText::Flush(bool force)
	{
		if (!(m_needRebuild || force))
		{
			return;
		}

		if (m_sizeChange)
		{
			m_textPairs.Clear();
			m_sizeChange = false;
		}

		SizeT char_count = m_text.StringLen();
		if (0 == char_count)
		{
			m_textPairs.Clear();
			return;
		}

		m_textWidth = 0;
		int pairCount = 1;
		if (m_textPairs.Size() == 0)
		{
			m_textPairs.Append(TextPair::EmptyInstance);
		}

		TextPair* tp = &m_textPairs.Back();
		
		if (char_count)
		{
			RectF* rect = n_new_array(RectF, char_count);
			RectF* rect_uv = n_new_array(RectF, char_count);
			memset(rect, 0, char_count);
			memset(rect_uv, 0, char_count);
			int tex_width = 0;
			int tex_height = 0;
			int code_count = _code_count(m_text);
			_min_tex_size(m_charSize, code_count, tex_width, tex_height);

			if (tp->m_imageData.GetWidth() < tex_width || tp->m_imageData.GetHeight() < tex_height || (tp->m_imageData.GetWidth() * tp->m_imageData.GetHeight() / 2 > tex_width * tex_height))
			{
				//实际纹理空间和需求相比较，过大或是不足，都应该重置缓冲。
				tp->m_imageData.Reset(tex_width, tex_height);
				if (tp->m_image.isvalid())
				{
					tp->m_image->Destroy();
					tp->m_image = NULL;
				}
			}
			else
			{
				tp->m_imageData.ClearInfo();
			}

			int count = 0;		
			float offset_x = 0;
			float offset_y = 0;

			GlyphInfo char_info;
			FT_Bitmap ft_bitmap;
			FT_Bitmap_New(&ft_bitmap);

			for (int i = 0; i < char_count; ++i)
			{
				UTF16 ch = m_text[i];		
				if (!tp->m_imageData.FindWord(ch, char_info))
				{						
					uint8* glyphBuffer = NULL;
					m_font->DrawChar(ch, m_charSize);
					if (m_font->GetFace()->glyph->bitmap.buffer != NULL)
					{
						switch (m_font->GetFace()->glyph->bitmap.pixel_mode)
						{
						case FT_PIXEL_MODE_GRAY:
							glyphBuffer = m_font->GetFace()->glyph->bitmap.buffer;
							break;

						case FT_PIXEL_MODE_MONO:
							// Convert the monochrome bitmap to 8-bit before rendering it.
							if (FT_Bitmap_Convert(Font::GetFTLib(), &m_font->GetFace()->glyph->bitmap, &ft_bitmap, 1) == 0)
							{
								// Go through the bitmap and convert all of the nonzero values to 0xFF (white).
								for (uint8* p = ft_bitmap.buffer, * endP = p + ft_bitmap.width * ft_bitmap.rows; p != endP; ++p)
									*p ^= -*p ^ *p;

								glyphBuffer = ft_bitmap.buffer;
							}
							break;
						}
					}
					while(!tp->m_imageData.SetData(ch, glyphBuffer, m_font->GetFace()->glyph, char_info))
					{
						//位置已满
						n_assert(m_font->GetFace()->glyph->bitmap.width <= tp->m_imageData.GetWidth());
						n_assert(m_font->GetFace()->glyph->bitmap.rows <= tp->m_imageData.GetHeight());
						_flush(*tp, rect, rect_uv, i - count, count);
						count = 0;
						++pairCount;
						m_textPairs.Append(TextPair::EmptyInstance);
						tp = &m_textPairs.Back();
						tp->m_imageData.Reset((tex_width > 64) ? tex_width / 2 : 64  , (tex_height > 64) ? tex_height / 2 : 64);
					}
					//FT_Done_Glyph(glyph);
				}

				rect_uv[i] = char_info.uvRect;
				RectF& curr_rect = rect[i];
				curr_rect.left = offset_x + char_info.charInfo.bearingX;
				curr_rect.top = offset_y - char_info.charInfo.bearingY;
				curr_rect.right = curr_rect.left + char_info.charInfo.width;
				curr_rect.bottom = curr_rect.top + char_info.charInfo.height;

				offset_x += char_info.charInfo.advance;
				m_textWidth += char_info.charInfo.advance;			

				++count;
			}
			_flush(*tp, rect, rect_uv, char_count - count, count);
			n_delete_array(rect);
			n_delete_array(rect_uv);

			FT_Bitmap_Done(Font::GetFTLib(), &ft_bitmap);
		}

		while (m_textPairs.Size() > pairCount)
		{
			m_textPairs.EraseIndex(m_textPairs.Size() - 1);
		}

		m_needRebuild = false;
	}
	void StaticText::Render(SpriteBatch& batch)
	{
		if (m_textPairs.Size())
		{
			TextPairArr::Iterator begin = m_textPairs.Begin();
			TextPairArr::Iterator end = m_textPairs.End();
			while(begin < end)
			{
				if (begin->m_renderable)
				{
					begin->m_renderable->SetScreenOffset(m_position);				
					batch.Render(begin->m_renderable, begin->m_image->GetTextureHandle());
				}

				++begin;
			}
		}
	}



	void StaticText::AddTail(GPtr<StaticText>& front, GPtr<StaticText>& follow)
	{
		PointF pf = front->GetPosition();
		pf.x() += front->GetTextWidth();
		follow->SetPosition(pf);
	}
	void StaticText::_flush(TextPair& tp, const RectF rect[], const RectF rect_uv[], int begin_index, int count)
	{
		if (NULL == tp.m_renderable)
		{
			tp.m_renderable = SpriteRenderInfo::Create();
			tp.m_renderable->InitBuffer(count, rect + begin_index, rect_uv + begin_index, m_textColor);
		}
		else
		{
			if (tp.m_renderable->GetRectCount() != count)
			{
				tp.m_renderable->InitBuffer(count, rect + begin_index, rect_uv + begin_index, m_textColor);
			}
			else
			{
				tp.m_renderable->UpdateBuffer(count, rect + begin_index, rect_uv + begin_index, m_textColor);
			}
		}
		tp.m_renderable->SetScreenOffset(m_position);
		if (tp.m_image.isvalid())
		{
			tp.m_image->UpdateData(tp.m_imageData.GetPtr(), tp.m_imageData.GetSize());
		}
		else
		{
			tp.m_image = Image::CreateImage(tp.m_imageData.GetPtr(), tp.m_imageData.GetSize(), tp.m_imageData.GetWidth(), tp.m_imageData.GetHeight(), RenderBase::PixelFormat::A8);
		}
	}
	void StaticText::_resetImageBuffer()
	{

	}
}
