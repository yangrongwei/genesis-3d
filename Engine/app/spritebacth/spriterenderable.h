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
#ifndef __sprite_render_buffer_H__
#define __sprite_render_buffer_H__



#include "sprite.h"

namespace App
{

	// ---------------------------------------
	// ----- 1 --- 2 -----
	// ----- |  /  | ----- rect
	// ----- 3 ___ 4 -----
	// ---------------------------------------



	

	class SpriteRenderInfo : public Core::RefCounted//: public Graphic::Renderable //
	{
		//__DeclareSubClass(SpriteRenderable, Graphic::Renderable);
		__DeclareClass(SpriteRenderInfo);
	public:
		virtual ~SpriteRenderInfo();
		SpriteRenderInfo();
		int GetRectCount() const;
		void InitBuffer(SizeT count, const RectF rect[], const RectF rect_uv[], const ColorF& color = ColorOne);// = ColorF(0.0f, 0.0f, 0.0f, 0.0f));
		void UpdateBuffer(SizeT count, const RectF rect[], const RectF rect_uv[], const ColorF& color = ColorOne);// = ColorF(0.0f, 0.0f, 0.0f, 0.0f));
		void SetRectInScreen(const RectF& rect, SizeT index);
		void SetRectInTexture(const RectF& rect_uv, SizeT index);
		void SetColor(const ColorF& color);
		void SetScreenOffset(const float2& offset);
		float2 GetScreenOffset() const;
		//void Flush();
		const RenderBase::PrimitiveHandle& GetPrimHandle() const;

		static const ColorF ColorWhite;		
		static const ColorF ColorBlack;
		static const ColorF ColorRed;
		static const ColorF ColorGreen;
		static const ColorF ColorBlue;
		static const ColorF ColorOne;
		static const ColorF ColorZero;
	private:
		
		struct _vertex_info
		{
			float x,y,u,v;		//screen x,y. texture u,v.
			ColorF color;		
		};
		void _release();
		void _setVertexInfo(_vertex_info* info_ptr, const RectF& rect, const RectF& rect_uv, const ColorF& color);
		
		RenderBase::PrimitiveHandle		m_primHandle;
		SizeT m_rectCount;
		float2 m_screenOffset;

		static const SizeT s_verticsOneRect; 
		static const SizeT s_indicesOneRect;
	};

	inline void SpriteRenderInfo::SetScreenOffset(const float2& offset)
	{
		m_screenOffset.x() = ceil(offset.x());
		m_screenOffset.y() = ceil(offset.y());
	}

	inline float2 SpriteRenderInfo::GetScreenOffset() const
	{
		return m_screenOffset;
	}
	inline int SpriteRenderInfo::GetRectCount() const
	{
		return m_rectCount;
	}
	inline const RenderBase::PrimitiveHandle& SpriteRenderInfo::GetPrimHandle() const 
	{
		return m_primHandle;
	}
}




#endif	//__sprite_render_buffer_H__