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
#ifndef __static_text_H__
#define __static_text_H__

#include "sprite.h"
#include "spritebacth.h"
#include "drawunit.h"
#include "guibase/resource/font.h"
#include "guibase/resource/image.h"

namespace App
{
	class StaticText : public DrawUnit
	{
		__DeclareSubClass(StaticText, DrawUnit);
	public:
		StaticText();
		virtual ~StaticText();
		void SetCharSize(SizeT size);
		void SetFont(const Util::String& font_name);
		void SetText(const UTF16String& text);
		void SetTextColor(const ColorF& color);

		void SetVisible( bool show);
		bool GetVisible() const;

		const UTF16String& GetText() const;
		float GetTextWidth() const;
		void Flush(bool force = false);
		virtual void Render(SpriteBatch& batch);

		static void AddTail(GPtr<StaticText>& front, GPtr<StaticText>& follow);
	private:
		typedef Math::rectangle<int> RectInt;

		struct CharInfo
		{
			float width;
			float height;
			float advance;
			float bearingX;
			float bearingY;
			CharInfo(
				float _width = 0.0f,
				float _height = 0.0f,
				float _advance = 0.0f,
				float _bearingX = 0.0f,
				float _bearingY = 0.0f)								
				:width(_width)
				,height(_height)
				,advance(_advance)
				,bearingX(_bearingX)
				,bearingY(_bearingY)
			{

			}

		};
		struct GlyphInfo
		{
		public:
			//RectInt rect_int;
			CharInfo charInfo;
			RectF uvRect;
			GlyphInfo(
				const CharInfo& _charInfo = CharInfo(),
				const RectF& _uvRect = RectF())
				:charInfo(_charInfo)
				,uvRect(_uvRect)
			{
			}
			
		};
		class ImageData		//8bit alpha texture.
		{
		public:
			ImageData();
			virtual ~ImageData();
			
			void Reset(SizeT width, SizeT height);
			void ClearInfo();
			bool SetData(UTF16 key, const uint8* data, const FT_GlyphSlot glyph, GlyphInfo& info);//const FT_Glyph_Metrics& metrices			
			//bool SetData(UTF16 key, const void* data, SizeT width, SizeT height, RectInt& rect_int);
			RectF ToUVF(const RectInt& rect_int) const;
			bool FindWord(UTF16 key, GlyphInfo& word_info);

			inline SizeT GetWidth() const
			{
				return m_width;
			}
			inline SizeT GetHeight() const
			{
				return m_height;
			}
			inline void* GetPtr()
			{
				return (void*)m_buffer;
			}
			inline SizeT GetSize()
			{
				return m_width * m_height;
			}
		private:
			typedef unsigned char BufferType;		
			typedef Util::Dictionary<UTF16, GlyphInfo> WordInfoTable; //u,v bounding box.
			void _release();
			BufferType* m_buffer;
			SizeT m_width;
			SizeT m_height;
			SizeT m_nextU;
			SizeT m_nextV;
			SizeT m_lineHeight;//
			SizeT m_bufferLen;
			WordInfoTable m_charInfoTable;
		};

		struct TextPair
		{
		public:
			GPtr<Image> m_image;
			GPtr<SpriteRenderInfo> m_renderable;
			ImageData m_imageData;
			TextPair()
				: m_renderable(NULL)
				, m_image(NULL)
			{
			}
			~TextPair()
			{
				m_renderable = NULL;
				m_image = NULL;
			}
			static const TextPair EmptyInstance;
		};
		void _resetImageBuffer();
		void _flush(TextPair& tp, const RectF rect[], const RectF rect_uv[], int begin_index, int count);
		SizeT		m_charSize;
		UTF16String m_text;
		ColorF		m_textColor;
		GPtr<Font>	m_font;
		float		m_textWidth;	//pixe.

		typedef Util::Array<TextPair> TextPairArr;
		TextPairArr m_textPairs;

		bool		m_needRebuild;
		bool		m_sizeChange;
		bool		m_bShow;        
		static const UTF16 s_blankChar; 

	}; 
	inline float StaticText::GetTextWidth() const
	{
		return m_textWidth;
	}
	inline const UTF16String& StaticText::GetText() const
	{
		return m_text;
	}

	inline void StaticText::SetVisible( bool show)
	{
		m_bShow = show;
	}

	inline bool StaticText::GetVisible( void) const 
	{
		return m_bShow;
	}
}

#endif	//__static_text_H__


