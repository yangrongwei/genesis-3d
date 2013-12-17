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
#include "simpleskycomponent.h"
#include "appframework/actor.h"
#include "resource/meshres.h"

namespace App
{
	__ImplementClass(App::SimpleSkyComponent, 'SKRC', App::MeshRenderComponent );

SimpleSkyComponent::SimpleSkyComponent():
	    m_skyTex0(NULL),
		m_skyTex1(NULL),
		m_skyTex2(NULL),
		m_skyTex3(NULL),
		m_skyTex4(NULL),
		m_skyTex5(NULL)
{

}

SimpleSkyComponent::~SimpleSkyComponent()
{

}

void SimpleSkyComponent::SetupCallbacks()
{
	mActor->RegisterComponentCallback(this, BeginFrame);
	Super::SetupCallbacks();
}

void SimpleSkyComponent::OnActivate()
{
	Super::OnActivate();
	Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent += Delegates::newDelegate(this, &SimpleSkyComponent::updateScale);
}

void SimpleSkyComponent::_BuildRenderObject()
{
	Super::_BuildRenderObject();
}

void SimpleSkyComponent::_BuildRenderRes()
{
	Super::_BuildRenderRes();
	mRenderObject->SetTransform(mActor->GetWorldTransform());
	Math::bbox bb;
	bb.pmin = Math::point(-Math::N_INFINITY, -Math::N_INFINITY, -Math::N_INFINITY);
	bb.pmax = Math::point(Math::N_INFINITY, Math::N_INFINITY, Math::N_INFINITY);
	mRenderObject->SetBoundingBox(bb);
	mRenderObject->SetProjected(false);	
}

void SimpleSkyComponent::OnDeactivate()
{
	Super::OnDeactivate();
	Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent -= Delegates::newDelegate(this, &SimpleSkyComponent::updateScale);
}

void SimpleSkyComponent::OnDestroy()
{
	Super::OnDestroy();
}

void SimpleSkyComponent::_OnMoveAfter()
{
	Super::_OnMoveAfter();	
}

void SimpleSkyComponent::_OnBeginFrame()
{
	Super::_OnBeginFrame();

	GPtr<Graphic::Camera> pMainCam = Graphic::GraphicSystem::Instance()->GetCameraByType(Graphic::eCO_Main);
//	mActor->SetPosition(pMainCam->GetTransform().get_position());
}

void SimpleSkyComponent::_UpdateRenderQueue()
{
//[zhongdaohuan][render_obj]¡Ÿ ±…æµÙ µœ÷
}

void SimpleSkyComponent::CopyFrom(const GPtr<Component> &pComponent)
{
	if( !pComponent.isvalid()  )
		return;
	if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
		return;

	Super::CopyFrom(pComponent);
}

void SimpleSkyComponent::updateScale( Graphic::Camera* camera )
{
	float nh =camera->GetCameraSetting().GetNearHeight();
	float nw = camera->GetCameraSetting().GetNearWidth();
	float nz =  camera->GetCameraSetting().GetZNear();



	float scale = Math::n_max(nh,nw);
	scale = Math::n_max(nz,scale)/75;
	mActor->SetScale(Math::vector(scale,scale,scale));
	
}

//-----------------------------------------------------------------
void SimpleSkyComponent:: SetSkyTexByNum( int num, Util::String& tex )
{
	switch(num)
	{
	case 0:
		m_skyTex0 = tex;
		SetTexture(0, "_diffuseMap", m_skyTex0);//, 0);//
		break;
	case 1:
		m_skyTex1 = tex;
		SetTexture(1, "_diffuseMap", m_skyTex1);//, 0);
		break;
	case 2:
		m_skyTex2 = tex;
		SetTexture(2, "_diffuseMap", m_skyTex2);//, 0);
		break;
	case 3:
		m_skyTex3 = tex;
		SetTexture(3, "_diffuseMap", m_skyTex3);//, 0);
		break;
	case 4:
		m_skyTex4 = tex;
		SetTexture(4, "_diffuseMap", m_skyTex4);//, 0);
		break;
	case 5:
		m_skyTex5 = tex;
		SetTexture(5, "_diffuseMap", m_skyTex5);//, 0);
		break;
	default:
		break;
	}
}
const Util::String SimpleSkyComponent::GetSkyTexByNum( int num )
{
	Util::String temp;
	switch(num)
	{
	case 0:
		temp = m_skyTex0;
		break;
	case 1:
		temp = m_skyTex1;
		break;
	case 2:
		temp = m_skyTex2;
		break;
	case 3:
		temp = m_skyTex3;
		break;
	case 4:
		temp = m_skyTex4;
		break;
	case 5:
		temp = m_skyTex5;
		break;
	default:
		temp = NULL;
		break;
	}
	return temp;
}
//------------------------------------------------------------------------------
void SimpleSkyComponent::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy/* = false*/  )
{
	//skybox's setmaterial should be null
	return;
}
//------------------------------------------------------------------------------
void SimpleSkyComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
{

	list.Append(Resources::ReferenceResource(mMeshInfo.meshID, Resources::RR_Unknown));

	list.Append(Resources::ReferenceResource(m_skyTex0, Resources::RR_Texture));
	list.Append(Resources::ReferenceResource(m_skyTex1, Resources::RR_Texture));
	list.Append(Resources::ReferenceResource(m_skyTex2, Resources::RR_Texture));
	list.Append(Resources::ReferenceResource(m_skyTex3, Resources::RR_Texture));
	list.Append(Resources::ReferenceResource(m_skyTex4, Resources::RR_Texture));
	list.Append(Resources::ReferenceResource(m_skyTex5, Resources::RR_Texture));
	
}
}
