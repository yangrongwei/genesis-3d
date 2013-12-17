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
#include "graphicfeature/components/cameracomponent.h"
#include "appframework/actor.h"
#include "appframework/component.h"
#include "graphicfeature/graphicsfeature.h"

#include "graphicfeature/graphicsfeatureprotocol.h"

#include "app/apputil/mouserayutil.h"
#include "appframework/actormanager.h"


namespace App
{
__ImplementClass(CameraComponent, 'CAMP', Component);

using namespace Math;
using namespace Graphic;

//------------------------------------------------------------------------------
/**
*/
CameraComponent::CameraComponent()
: m_bUseSkyBox(false)
, m_bAttached(false)
, m_bSkyBoxDirty(false)
, m_bInit(false)

{
	m_camera = Graphic::Camera::Create();
	m_camera->SetOwner(this);
	m_camera->SetCameraOrder(Graphic::eCO_Main);
}

//------------------------------------------------------------------------------
/**
*/
CameraComponent::~CameraComponent()
{
	m_camera = NULL;
}
//------------------------------------------------------------------------------
/**
*/
void
CameraComponent::SetupCallbacks()
{
	Super::SetupCallbacks();
	this->mActor->RegisterComponentCallback(this, BeginFrame);
	this->mActor->RegisterComponentCallback(this, OnFrame);
    this->mActor->RegisterComponentCallback(this, MoveAfter);
}

void CameraComponent::_OnBeginFrame()
{
	Super::_OnBeginFrame();
	if (m_bSkyBoxDirty)
	{
		DetachSkyBox();
		AttachSkyBox();
	}

}
//------------------------------------------------------------------------
void CameraComponent::_OnFrame()
{
	Super::_OnFrame();
}

void CameraComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
{
	//这个类只有编辑器会用到，所以不用统计。
	Super::GetReferenceResourceId(list);
}
//------------------------------------------------------------------------------
/**
*/
void
CameraComponent::OnActivate()
{
	Super::OnActivate();

	n_assert( m_camera.isvalid() );
	n_assert( GraphicsFeature::HasInstance() );
	n_assert( mActor );

	if ( mActor )
	{
		m_camera->SetTransform(  mActor->GetWorldTranslateNoScale()  );
		m_camera->OnTransformChanged();
	}
	AttachCamera();
#ifndef __SCRIPT_COMMIT__
	mActor->Check_OnRenderPostEffect_Bind();
#endif
}
//------------------------------------------------------------------------------
/**
*/
void
CameraComponent::OnDeactivate()
{
	DetachCamera();
#ifndef __SCRIPT_COMMIT__
	mActor->Check_OnRenderPostEffect_Unbind();
#endif
	Super::OnDeactivate();
}
//------------------------------------------------------------------------------
/**
*/
void 
CameraComponent::OnRenderSceneChanged()
{
	if (m_camera.isvalid())
	{
		m_camera->SetRenderScene(mActor->GetRenderScene());
	}
}

//------------------------------------------------------------------------------
/**
*/
void
CameraComponent::SetupAcceptedMessages()
{   
    Super::SetupAcceptedMessages();
}

//------------------------------------------------------------------------------
/**
*/
void
CameraComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
{
}
//------------------------------------------------------------------------
bool CameraComponent::GetProjParam( float* nearWidth , float* nearHeight , float* nearPlaneDis , float* farPlaneDis )
{
	*nearWidth  = m_camera->GetCameraSetting().GetNearWidth() ;
	*nearHeight = m_camera->GetCameraSetting().GetNearHeight() ;
	*nearPlaneDis = m_camera->GetCameraSetting().GetZNear() ;
	*farPlaneDis = m_camera->GetCameraSetting().GetZFar();

	return true ;
}
//------------------------------------------------------------------------
bool CameraComponent::SetProjParam( float nearW , float nearH , float nearDis , float farDis )
{

	Graphic::CameraSetting cs = m_camera->GetCameraSetting();
	
	float fovy = 2.0f * atan(nearH/(2.0f * nearDis));//

	cs.SetupPerspectiveFovRH( fovy , nearW / nearH , nearDis , farDis ) ;

	m_camera->SetCameraSetting( cs ) ;

	return true ;
}
//------------------------------------------------------------------------
bool CameraComponent::SetProj(float fovOrHeight, float zNear, float zFar, Graphic::Camera::ViewType vt)
{
	m_camera->SetProj(vt, fovOrHeight, zNear, zFar);
	return true ;
}

bool CameraComponent::SetProj(float fovOrHeight, float zNear, float zFar)
{
	return SetProj(fovOrHeight, zNear, zFar, m_camera->GetViewType());
}

void CameraComponent::SetZNear(float zNear)
{
	const CameraSetting& cs = m_camera->GetCameraSetting();
	Camera::ViewType vt = m_camera->GetViewType();
	switch (vt)
	{
	case Camera::VT_persp:
		{
			SetProj(cs.GetFov(), zNear, cs.GetZFar());
		}
		break;
	case Camera::VT_ortho:
		{
			SetProj(cs.GetNearHeight(), zNear, cs.GetZFar());
		}
		break;
	default:
		{
			n_error("No suport this Camera::ViewType: %d", (int)vt);//[zhongdaohuan]不允许有这种情况发生。
		}
		break;
	}
}

void CameraComponent::SetZFar(float zFar)
{
	const CameraSetting& cs = m_camera->GetCameraSetting();
	Camera::ViewType vt = m_camera->GetViewType();
	switch (vt)
	{
	case Camera::VT_persp:
		{
			SetProj(cs.GetFov(), cs.GetZNear(), zFar, vt);
		}
		break;
	case Camera::VT_ortho:
		{
			SetProj(cs.GetNearHeight(), cs.GetZNear(), zFar, vt);
		}
		break;
	default:
		{
			n_error("No suport this Camera::ViewType: %d", (int)vt);//[zhongdaohuan]不允许有这种情况发生。
		}
		break;
	}
}
//------------------------------------------------------------------------
void CameraComponent::_OnMoveAfter()
{
	if ( mActor )
	{
		m_camera->SetTransform( mActor->GetWorldTranslateNoScale() );
		m_camera->OnTransformChanged();		
	}

}
//------------------------------------------------------------------------
void CameraComponent::CopyFrom( const GPtr<Component>& pComponent )
{
	if( !pComponent.isvalid()  )
		return;
	if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
		return;

	GPtr<CameraComponent> pSource = pComponent.downcast<CameraComponent>();
	GPtr<Graphic::Camera> pSourceCamera = pSource->GetCameraObject();
	n_assert( pSource->m_camera.isvalid() );

	m_camera->CopyParam(pSourceCamera);
}

//------------------------------------------------------------------------
void CameraComponent::AttachCamera()
{
	if ( m_bAttached )
	{
		return;
	}

	if (eCO_PuppetMain != m_camera->GetCameraOrder())
	{
		const GPtr<GraphicSystem>& gs = GraphicsFeature::Instance()->GetGraphicSystem();
		n_assert( gs.isvalid() );
		if ( gs.isvalid() )
		{
			m_camera->SetRenderScene(mActor->GetRenderScene());
			m_camera->Setup();
			gs->AddCamera( m_camera );

			//if (m_camera->GetCameraOrder() == eCO_Main)
			//{
			//	GraphicsFeature::Instance()->AssignDefaultCamera( mActor );
			//}
		}
	}

	m_bAttached = true;

	AttachSkyBox();
}
//------------------------------------------------------------------------
void CameraComponent::DetachCamera()
{
	if ( !m_bAttached )
	{
		return;
	}

	const GPtr<GraphicSystem>& gs = GraphicsFeature::Instance()->GetGraphicSystem();
	n_assert( gs.isvalid() );
	if ( gs.isvalid() )
	{
		m_camera->Discard();
		gs->RemoveCamera( m_camera );	
		m_camera->SetRenderScene(NULL);
	}
	
	
	m_bAttached = false;

	DetachSkyBox();
}

void CameraComponent::SetCullMarkID(CullMarkID id)
{
	//m_cullMarkID = id;
	RenderLayer rl = RenderLayerConverter::Convert(id);
	if (m_camera.isvalid())
	{
		m_camera->SetCullMask(rl);
	}
}

void CameraComponent::AttachSkyBox()
{
}

void CameraComponent::DetachSkyBox()
{
	const GPtr<GraphicSystem>& gs = GraphicsFeature::Instance()->GetGraphicSystem();
	n_assert( gs.isvalid() );
}

bool CameraComponent::IsUseSkyBox(void)
{
	return m_bUseSkyBox;
}

void CameraComponent::SetUseSkyBox(bool useSkyBox)
{
}



	void CameraComponent::SetRenderCustom( bool custom )
	{
		if (m_camera.isvalid())
		{
			m_camera->SetUseCustomMaterial(custom);
		}
	}

	bool CameraComponent::IsRenderCustom()
	{
		if (m_camera.isvalid())
		{
			return m_camera->IsRenderCustom();
		}
		return false;
	}

	void CameraComponent::SetRenderNormal( bool normal )
	{
		if (m_camera.isvalid())
		{
			m_camera->SetRenderNormal(normal);
		}
	}

	bool CameraComponent::IsRenderNormal()
	{
		if (m_camera.isvalid())
		{
			return m_camera->IsRenderNormal();
		}
		return false;
	}

	void CameraComponent::SetRenderDepth( bool RenderDepth )
	{
		if (m_camera.isvalid())
		{
			m_camera->SetRenderDepth(RenderDepth);
		}
	}

	bool CameraComponent::IsRenderDepth()
	{
		if (m_camera.isvalid())
		{
			return m_camera->HasDepthMap();
		}
		return false;
	}

	void CameraComponent::SetRenderToTexture( const GPtr<Graphic::RenderToTexture>& rtt )
	{
		if (m_camera.isvalid())
		{
			return m_camera->SetRenderToTexture(rtt);
		}
	}

	void CameraComponent::SetPerspectiveFovRH( float fov, float aspect, float zNear, float zFar )
	{

		m_camera->SetPerspectiveFovRH(fov, aspect, zNear, zFar);
	}

	void CameraComponent::SetPerspectiveFovRHEx( float fov, float aspect, float zNear, float zFar,const Math::float4& clipPlane, bool reflection )
	{
		m_camera->SetPerspectiveFovRH(fov, aspect, zNear, zFar, clipPlane, reflection);
	}

	bool
		CameraComponent::IsAllResourceLoaded()
	{
		return true;
	}

	void
		CameraComponent::SetupAllResource()
	{
		return;
	}

}; // namespace GraphicsFeature
