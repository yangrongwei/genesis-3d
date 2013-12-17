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
#include "ForwardShadingRenderPipeline.h"
#include "graphicsystem/Camera/RenderPipeline/RenderPipelineManager.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "GraphicSystem.h"

namespace Graphic
{



	__ImplementClass(ForwardShadingRenderPipeline,'FSRP',Core::RefCounted)

		ForwardShadingRenderPipeline::ForwardShadingRenderPipeline()
	{
		//empty
	}

	ForwardShadingRenderPipeline::~ForwardShadingRenderPipeline()
	{
		m_currentRT = NULL;
	}

	void ForwardShadingRenderPipeline::Render(PipelineParamters& context)
	{
		setGlobalShaderParam(context);

		bool bCameraMain = (context.m_camera->GetCameraOrder()== eCO_Main);

		const Camera::DrawType& _mode = context.m_camera->GetDrawType();

		if ( _mode == Camera::DrawTextured )
		{
			if (bCameraMain)
			{
				GraphicSystem::Instance()->SetWireFrameMode(false);
				renderDepthMap(context);

#ifdef __WIN32__
				renderLightLitMap(context);
#endif
				_RenderNormal(context);
				renderSpecialPost(context);
				renderCustomObjs(context);
				renderMain(context);
			}
			else
			{
				renderCustomized(context);
			}
		}
	}

	//------------------------------------------------------------------------
	void ForwardShadingRenderPipeline::_RenderNormal(PipelineParamters& context)
	{
		const Camera* camera = context.m_camera;
		if(!camera->IsRenderNormal())
			return;
		GraphicRenderer::ResetCache();
#if __WIN32__
		GraphicSystem::Instance()->SetRenderTarget(camera->GetBackBuffer(),0,RenderBase::RenderTarget::ClearAll);
		m_currentRT = 0;
#endif
		const GPtr<RenderToTexture>& rtt= camera->GetRenderToTexture();
		if (rtt.isvalid())
		{
			GraphicSystem::Instance()->SetRenderTarget(rtt->GetTargetHandle(),0,RenderBase::RenderTarget::ClearAll);
			m_currentRT = rtt;
		}

		renderRenderableList(context, RenderData::Background, eForward, NULL);//没有灯光的东西。在这里渲染。

		setCommonLights(context);//设置共有的灯光，如平行光，阳光等

		renderRenderableListWidthLight(context, RenderData::Opaque, NULL);

		renderRenderableListWidthLight(context, RenderData::Alpha, NULL);
	}	
}
