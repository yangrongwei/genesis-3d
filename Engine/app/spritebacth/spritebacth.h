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
#ifndef __sprite_bacth_H__
#define __sprite_bacth_H__


#include "spriterenderable.h"
namespace App
{
	class SpriteBatch : public Core::RefCounted
	{
		__DeclareClass(SpriteBatch);
	public:

		enum SpriteState
		{
			SS_Running,
			SS_Stop,
		};

		SpriteBatch();
		virtual ~SpriteBatch();
		void Render(const GPtr<SpriteRenderInfo>& renderable, const RenderBase::TextureHandle& text_handle);
		void Begin();
		void End();
		void SetShaderName(const Util::String& name);
	private:

		void _loadShader();
		void _checkShader();
		Util::String m_shaderName;
		GPtr<Graphic::Material> m_shader;
		RenderBase::GPUProgramHandle m_shaderHandle;
		SpriteState m_state;

		IndexT m_RegisterScreen;

	};
	inline void SpriteBatch::_checkShader()
	{
		if (NULL == m_shader)
		{
			_loadShader();
		}
	}

	inline void SpriteBatch::SetShaderName(const Util::String& name)
	{
		m_shaderName = name;
	}
}




#endif	//__sprite_bacth_H__