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
#include "DeferredLightingRenderPipeline.h"
#include "graphicsystem/Camera/RenderPipeline/RenderPipelineManager.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "GraphicSystem.h"


namespace Graphic
{


	__ImplementClass(DeferredLightingRenderPipeline,'DLRP',Core::RefCounted)

		DeferredLightingRenderPipeline::DeferredLightingRenderPipeline()
	{
		mLightPass = DeferredLightingPass::Create();
		mLightPass->Init();

		//empty
	}

	DeferredLightingRenderPipeline::~DeferredLightingRenderPipeline()
	{
		mLightPass = NULL;
	}

	void DeferredLightingRenderPipeline::Render(PipelineParamters& params)
	{
		setGlobalShaderParam(params);
		_RenderGBuffer(params);
		renderLightLitMap(params);
		_RenderLightMap(params);		
		renderCustomized(params);
		_RenderFinalScene(params);
		renderMain( params);
	}

	void DeferredLightingRenderPipeline::_RenderGBuffer(PipelineParamters& params)
	{
		GraphicRenderer::ResetCache();
		const GPtr<Camera>& camera = params.m_camera;
		const GPtr<RenderToTexture>& depthRT = camera->GetDepthMap();
		const GPtr<RenderToTexture>& normalRT = camera->GetDeferredNormalMap();
		const GPtr<RenderToTexture>& paramRT = camera->GetDeferredParamMap();

		n_assert(depthRT.isvalid());
		n_assert(normalRT.isvalid());
		n_assert(paramRT.isvalid());



		GraphicSystem* gs = GraphicSystem::Instance();
		if (gs)
		{
			gs->SetRenderTarget(normalRT, 0, RenderBase::RenderTarget::ClearAll);
			gs->SetRenderTarget(depthRT, 1, RenderBase::RenderTarget::ClearAll);
			gs->SetRenderTarget(paramRT, 2, RenderBase::RenderTarget::ClearAll);
			m_currentRT = normalRT;
		}

		renderRenderableList(params,RenderData::Opaque, eGBuffer, NULL);

		if (gs)
		{
			gs->SetRenderTarget(dummyhandle, 1, RenderBase::RenderTarget::ClearAll);
			gs->SetRenderTarget(dummyhandle, 2, RenderBase::RenderTarget::ClearAll);
		}

	}

	void DeferredLightingRenderPipeline::_RenderLightMap(PipelineParamters& params)
	{
		GraphicRenderer::ResetCache();
		mLightPass->RenderActiveLights(params);
		m_currentRT = params.m_camera->GetDeferredLightMap();
	}

	void DeferredLightingRenderPipeline::_RenderFinalScene(PipelineParamters& params)
	{
		const GPtr<Camera>& camera = params.m_camera;
		if(!camera->IsRenderNormal())
			return;
		GraphicRenderer::ResetCache();
		const GPtr<RenderToTexture>& rtt= camera->GetRenderToTexture();
		if (rtt.isvalid())
		{
			GraphicSystem::Instance()->SetRenderTarget(rtt->GetTargetHandle(),0,RenderBase::RenderTarget::ClearAll);
			m_currentRT = rtt;
		}
		else
		{
			GraphicSystem::Instance()->SetRenderTarget(dummyhandle,0,RenderBase::RenderTarget::ClearAll);
			m_currentRT = NULL;
		}
		renderRenderableList(params, RenderData::Background, eForward, NULL);//没有灯光的东西。在这里渲染。
		renderRenderableList(params, RenderData::Opaque, eDeferredLightPass, NULL);

		_RenderOtherObjs(params);
	}

	void DeferredLightingRenderPipeline::_RenderOtherObjs(PipelineParamters& params)
	{
		const GPtr<Camera>& camera = params.m_camera;
		if(!camera->IsRenderNormal())
			return;
		GraphicRenderer::ResetCache();
		setCommonLights(params);//设置共有的灯光，如平行光，阳光等
		renderRenderableListWidthLight(params, RenderData::Alpha, NULL);

		renderCustomObjs(params);
	}

}
