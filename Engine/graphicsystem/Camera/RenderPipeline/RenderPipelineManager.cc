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
#include "graphicsystem/Vision/RenderScene.h"
#include "RenderPipelineManager.h"
#include "GraphicSystem.h"
#include "graphicsystem/Camera/RenderPipeline/DeferredLightingRenderPipeline.h"
#include "graphicsystem/Renderable/RenderObject.h"

namespace Graphic
{

	__ImplementClass(RenderPipelineManager,'RPMA',Core::RefCounted)

		RenderPipelineManager::RenderPipelineManager()
	{
		m_pipelineContext.m_renderPipelineManager = this;
		m_forwardPipeline = ForwardShadingRenderPipeline::Create();
	}

	RenderPipelineManager::~RenderPipelineManager()
	{
		//empty
	}

	void RenderPipelineManager::PreRender(Camera* camera)
	{
		m_pipelineContext.m_camera = camera;
		if(camera->UseViewport())
		{
			const Camera::ViewPort& vp = camera->GetViewport();
			GraphicSystem::Instance()->SetViewPort(vp);
		}
	}

	void RenderPipelineManager::AfterRender()
	{
		if (m_pipelineContext.m_camera->UseViewport() && m_pipelineContext.m_camera->GetCameraOrder() != eCO_Main)
		{
			GPtr<Camera> mainCam = GraphicSystem::Instance()->GetCameraByType(eCO_Main);
			n_assert(mainCam.isvalid());
			GraphicSystem::Instance()->SetViewPort(mainCam->GetViewport());
		}

		m_pipelineContext.m_camera = 0;
	}

	void RenderPipelineManager::Open()
	{

	}

	void RenderPipelineManager::Close()
	{
		m_pipelineContext.m_camera = 0;
		m_pipelineContext.m_renderPipelineManager = 0;
		m_forwardPipeline = 0;
		m_customPipeline = 0;
	}
	void RenderPipelineManager::SetupDeferred()
	{
		m_deferredPipeline = DeferredLightingRenderPipeline::Create();
	}

	void RenderPipelineManager::SetCustomPipeline(const GPtr<RenderPipeline>& customPipeline)
	{
		this->m_customPipeline = customPipeline;
	}

	void RenderPipelineManager::OnRenderPipeline(Camera* camera)
	{
		GPtr<RenderPipelineManager>& renderpipemanager = camera->GetRenderPipelineManager();
		renderpipemanager->PreRender(camera);

		renderpipemanager->m_pipelineContext.m_renderDatas.SetUseFor(RenderDataCollection::Normal);
		AssignVisibleNodes(renderpipemanager->m_pipelineContext);

		if(camera->GetUseCallBack())
		{
			RenderCallBacks::Iterator begin = renderpipemanager->m_pipelineContext.m_callBacks.Begin();
			RenderCallBacks::Iterator end = renderpipemanager->m_pipelineContext.m_callBacks.End();
			while(begin != end)
			{
				(*begin)->OnWillRenderObject(camera);
				++begin;
			}	
		}

		AssignEffectiveLight(renderpipemanager->m_pipelineContext);
		AssignRenderDatas(renderpipemanager->m_pipelineContext);
		renderPipeline(renderpipemanager);

		renderpipemanager->AfterRender();
	}

	void RenderPipelineManager::renderPipeline(GPtr<RenderPipelineManager>& renderpipemanager)
	{
		Camera::RenderMode rm = renderpipemanager->m_pipelineContext.m_camera->GetRenderMode();

		switch (rm)
		{
		case Camera::ForwardMode:
			{
				renderpipemanager->m_forwardPipeline->Render(renderpipemanager->m_pipelineContext);
			}
			break;
		case Camera::DeferredMode:
			{
				renderpipemanager->m_deferredPipeline->Render(renderpipemanager->m_pipelineContext);
			}
			break;
		case Camera::CustomedMode:
			{
				// custom pipeline rendering
				n_assert(renderpipemanager->m_customPipeline.isvalid());
				renderpipemanager->m_customPipeline->Render(renderpipemanager->m_pipelineContext);
			}
			break;
		default:
			{
				n_error("error Camera::RenderMode !");
			}
			break;
		}
	}


	void RenderPipelineManager::AssignVisibleNodes(PipelineParamters& params)
	{
		Camera* camera = params.m_camera;
		params.m_callBacks.Clear();
		params.m_visibleNodes.Clear();

		GPtr<Vis::VisQuery> pVisQuery = camera->Cull();
		n_assert( pVisQuery.isvalid() );

		bool mainCamera = eCO_Main == camera->GetCameraOrder();
		const Util::Array<GPtr<Vis::VisEntity> >& viEnityList = pVisQuery->GetQueryResult();

		Math::float4 camPos = camera->GetTransform().get_position();
		Math::float4 camDir = -camera->GetTransform().get_zaxis();

		for (IndexT i = 0; i < viEnityList.Size(); ++i)
		{
			const GPtr<Vis::VisEntity>& visEnt = viEnityList[i];
			n_assert( visEnt.isvalid() );
			Graphic::GraphicObject* obj = visEnt->GetUserData();
			n_assert( obj && obj->GetRtti()->IsDerivedFrom( RenderObject::RTTI ) );

			RenderObject* renderObj = static_cast<RenderObject*>(obj);

			uint mark = renderObj->GetRenderCullMark() & (uint)camera->GetCullMask();

			if (mark)
			{
				if (mainCamera && renderObj->GetNeedCullCallBack())
				{
					params.m_callBacks.Append(renderObj);
				}
				Math::float4 renderablePos = renderObj->GetTransform().get_position();
				Math::float4 camToObj = renderablePos - camPos;
				VisibleNode& node = params.m_visibleNodes.PushBack();
				node.object = renderObj;
				node.distance = Math::float4::dot3(camDir,camToObj);
			}

		}
		if (mainCamera)
		{
			const Util::Array<RenderObject*>& notCullList = camera->GetRenderScene()->GetNotCullRenderObjects();
			Util::Array<RenderObject*>::Iterator it = notCullList.Begin();
			Util::Array<RenderObject*>::Iterator end = notCullList.End();
			while(it != end)
			{
				uint mark = (*it)->GetRenderCullMark() & (uint)camera->GetCullMask();
				if (mark)
				{
					VisibleNode& node = params.m_visibleNodes.PushBack();
					node.object = *it;
					node.distance = 0;
				}
				++it;
			}
		}
		const Util::Array<RenderObject*>& notCullList = camera->GetNotCullRenderObjects();
		Util::Array<RenderObject*>::Iterator it = notCullList.Begin();
		Util::Array<RenderObject*>::Iterator end = notCullList.End();
		while(it != end)
		{
			uint mark = (*it)->GetRenderCullMark() & (uint)camera->GetCullMask();
			if (mark)
			{
				VisibleNode& node = params.m_visibleNodes.PushBack();
				node.object = *it;
				node.distance = 0;
			}
			++it;
		}



	}

	void RenderPipelineManager::AssignRenderDatas(PipelineParamters& params)
	{
		RenderDataManager* renderDatas = &params.m_renderDatas;
		renderDatas->Reset(eCO_Main == params.m_camera->GetCameraOrder() );
		VisibleNodeCollection::Iterator it = params.m_visibleNodes.Begin();
		VisibleNodeCollection::Iterator end = params.m_visibleNodes.End();
		while(it != end)
		{
			renderDatas->SetCurrentNode(it);
			it->object->AddToCollection(renderDatas);
			++it;
		}
		renderDatas->Sort();
	}

	void RenderPipelineManager::AssignEffectiveLight(PipelineParamters& params)
	{
		params.m_activeLights.CameraCull(params.m_camera);

		if (params.m_camera->HasLightLitMap() && params.m_camera->HasDepthMap())
		{
			const ActiveLightInfo* sun_light = params.m_activeLights.FindSunLight();
			if (sun_light && sun_light->light->IsEnableShadow())
			{
				renderShadowMap(sun_light);
				return;
			}
		}
		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
		pGMP->SetVectorParam(eGShaderVecShadowMapSize, Math::float4(0.0f, 0.0f, 0.0f, 0.0f));
	}
	void RenderPipelineManager::renderShadowMap(const ActiveLightInfo* aLight)
	{
		RenderLayer cullmark = GraphicSystem::Instance()->GetRenderingCamera()->GetCullMask();
		aLight->light->RenderShadowMapBegin();
		const Light::ShadowMapCameraList& list = aLight->light->GetShadowMapCameraList();
		for (int i = 0; i < list.Size(); ++i)
		{
			GPtr<Camera> camera = list[i];
			camera->SetCullMask(cullmark);
			GPtr<RenderPipelineManager>& mgr = camera->GetRenderPipelineManager();
			mgr->m_pipelineContext.m_camera = camera.get();
			mgr->m_pipelineContext.m_renderDatas.SetUseFor(RenderDataCollection::Shadow);
			AssignVisibleNodes(mgr->m_pipelineContext);
			AssignRenderDatas(mgr->m_pipelineContext);
			renderPipeline(mgr);
			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
			n_assert(NULL != pGMP);
			const Math::float4& shadowMapParam = pGMP->GetVectorParam(Graphic::eGShaderVecShadowMapSize);
			Math::float4 srcRect(0,0,shadowMapParam.x(),shadowMapParam.y());
			Math::float4 desRect = srcRect;
			desRect.x() = shadowMapParam.x() * i;
			desRect.z() = desRect.x() + shadowMapParam.x();
			GraphicSystem::Instance()->CopyRenderTarget(camera->GetRenderToTexture()->GetTargetHandle(),srcRect,camera->GetSwapTexture()->GetTargetHandle(),desRect);
			mgr->m_pipelineContext.m_camera = NULL;
		}
	}
}
