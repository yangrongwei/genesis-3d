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
#include "spritebacth.h"
#include "materialmaker/parser/GenesisShaderParser.h"

#include "statictext.h"
//#include "debugboard.h"


using namespace Graphic;
namespace App
{
	__ImplementClass(App::SpriteBatch,'SPBA', Core::RefCounted);

	SpriteBatch::SpriteBatch()
		:m_shader(NULL)
		,m_shaderHandle(NULL)
		,m_state(SS_Stop)
	{

	}
	SpriteBatch::~SpriteBatch()
	{
		m_shader = NULL;
		m_shaderHandle = NULL;
		
	}
	void SpriteBatch::Begin()
	{
		assert(SS_Stop == m_state);
		m_state = SS_Running;
		_checkShader();
		GraphicSystem* gs = GraphicSystem::Instance();
		gs->SetShaderProgram(m_shaderHandle);
		gs->SetRenderState(m_shader->GetTech()->GetDefaultPass()->GetRenderStateObject());
	}
	void SpriteBatch::End()
	{
		assert(SS_Running == m_state);
		m_state = SS_Stop;
	}
	void SpriteBatch::Render(const GPtr<SpriteRenderInfo>& renderable, const RenderBase::TextureHandle& text_handle)
	{
		assert(SS_Running == m_state);		
		GraphicSystem* gs = GraphicSystem::Instance();

		gs->SetTexture(0,text_handle);

		const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();
		float2 offset = renderable->GetScreenOffset();
		float4 screen((float)dm.GetWidth(), (float)dm.GetHeight(), (float)offset.x(), (float)offset.y());

		gs->SetVertexShaderConstantVectorF(m_RegisterScreen, &screen, 1);

		gs->DrawPrimitive(renderable->GetPrimHandle());
		
	}

	void SpriteBatch::_loadShader()
	{

		m_shader = GenesisMaterialMaker::MakeFromShader(m_shaderName); 

		m_shaderHandle = m_shader->GetTech(0)->GetDefaultPass()->GetGPUProgramHandle();
		assert(NULL != m_shader);
		assert(NULL != m_shaderHandle);

		m_RegisterScreen = m_shader->GetRegisterIndex("gScreen", Graphic::SCT_VS, 0);

		GPtr<RenderBase::RenderStateDesc>& rso = m_shader->GetTech()->GetDefaultPass()->GetRenderStateObject();
		RenderBase::DeviceDepthAndStencilState state;
		state = rso->GetDepthAndStencilState();
		state.m_stencilTwoEnable = false;
		state.m_depthEnable = false;
		state.m_depthWriteMask = false;
		rso->SetDepthAndStencilState(state);
	}
}

