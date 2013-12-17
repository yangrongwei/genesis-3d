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
#include "graphicfeature/components/lightcomponent.h"
#include "graphicfeature/components/cameracomponent.h"
#include "core/factory.h"
#include "appframework/actor.h"
#include "graphicfeature/graphicsfeature.h"
#include "math/polar.h"
#include "apputil/shadowmaputil.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "foundation/util/guid.h"
#include "app/apputil/mouserayutil.h"
#include "graphicfeature/components/meshrendercomponent.h"
#include "app/apputil/manuresutil.h"
#include "addons/resource/meshres.h"




namespace App
{

__ImplementClass(LightComponent, 'LIPR', Component);


using namespace Messaging;
using namespace Graphic;
using namespace Math;
using namespace Util;

//------------------------------------------------------------------------
LightComponent::LightComponent() 
	:m_lightDirty(false)
	,m_bQualityChange(false)
	,m_sceneMax(2500.f)
	,m_depthBias(3.0f)
	,m_ShadowStrength(1.0f)
	,m_ShadowDistance(100.0f)
	,m_shadowMapQuality(eMiddle)
	,m_shadowSplitCount(eFourCountsSplit)//eFourSplit)//
	,m_shadowProjection(eBoxShadow)
	,m_CacheShadowState(false)
{
	// init shadow split distance
	m_splitPercentages[eFourCountsSplit][0] = 0.0f;
	m_splitPercentages[eFourCountsSplit][1] = 0.1f;
	m_splitPercentages[eFourCountsSplit][2] = 3.0f / 15.0f;
	m_splitPercentages[eFourCountsSplit][3] = 7.0f / 15.0f;
	m_splitPercentages[eFourCountsSplit][4] = 1.0f;

	m_splitPercentages[eTwoCountsSplit][0] = 0.0f;
	m_splitPercentages[eTwoCountsSplit][1] = 1.0f / 3.0f;
	m_splitPercentages[eTwoCountsSplit][2] = 1.0f;
	m_splitPercentages[eTwoCountsSplit][3] = 1.0f;
	m_splitPercentages[eTwoCountsSplit][4] = 1.0f;

	m_splitPercentages[eOneCountsSplit][0] = 0.0f;
	m_splitPercentages[eOneCountsSplit][1] = 1.0f;
	m_splitPercentages[eOneCountsSplit][2] = 1.0f;
	m_splitPercentages[eOneCountsSplit][3] = 1.0f;
	m_splitPercentages[eOneCountsSplit][4] = 1.0f;
	

	m_light = Graphic::Light::Create();
	//m_light->SetOwner(this);
	m_light->SetListener(this);

}
//------------------------------------------------------------------------
LightComponent::~LightComponent()
{

	m_light->Discard();
	m_light = NULL;
}
//------------------------------------------------------------------------------
/**
*/
void
LightComponent::SetupCallbacks()
{
    this->mActor->RegisterComponentCallback(this, MoveAfter);
	this->mActor->RegisterComponentCallback(this, EndFrame);
	this->mActor->RegisterComponentCallback(this, OnFrame);
	mActor->RegisterComponentCallback(this, BeginFrame);
	Super::SetupCallbacks();
}

//------------------------------------------------------------------------------
/**
*/
void
LightComponent::OnActivate()
{
    Super::OnActivate();

	n_assert( m_light.isvalid() );
	n_assert( GraphicsFeature::HasInstance() );
	n_assert( mActor );

	Graphic::RenderScene* renderScene = NULL;
	if ( mActor )
	{
		renderScene = mActor->GetRenderScene();
		m_light->SetTransform( mActor->GetWorldTranslateNoScale() );
	}	
	if ( renderScene && Graphic::Light::eInvailidLightType != m_light->GetLightType())
	{
		m_light->Attach(renderScene);
	}

}

//------------------------------------------------------------------------------
/**
*/
void
LightComponent::OnDeactivate()
{
	m_light->Detach();
	
    Super::OnDeactivate();
}
//------------------------------------------------------------------------------
/**
*/
void 
LightComponent::OnRenderSceneChanged()
{
	if (m_light.isvalid())
	{
		m_light->Attach(mActor->GetRenderScene());
	}
}

//------------------------------------------------------------------------------
/**
*/
void
LightComponent::SetupAcceptedMessages()
{
    Super::SetupAcceptedMessages();
}

//------------------------------------------------------------------------------
/**
*/
void
LightComponent::HandleMessage(const GPtr<Message>& msg)
{
}

void LightComponent::_OnBeginFrame()
{
	Super::_OnBeginFrame();

	
}
//------------------------------------------------------------------------
void LightComponent::_OnFrame()
{
	Super::_OnFrame();

	m_light->ResetShadowMap(m_shadowSplitCount);
}
void LightComponent::_OnEndFrame()
{
	Super::_OnEndFrame();
	n_assert(m_light.isvalid());

	if (m_lightDirty)
	{
		if (Graphic::Light::eSunLight == m_light->GetLightType())
		{
			if (m_light->IsEnableShadow())
			{
				int shadowMapSize = GetShaowMapSize( m_shadowMapQuality );
				m_light->DiscardShadow();
				m_light->SetupSunlightShadow( shadowMapSize, (int)m_shadowSplitCount );
			}
			else
			{
				m_light->DiscardShadow();
			}

		}
		m_lightDirty = false;
	}
}

void
LightComponent::RenderShadowMapBegin(Graphic::Light* sender)
{
	if (Graphic::Light::eSunLight == m_light->GetLightType() 
		&& m_light->IsEnabled() 
		&& m_light->IsEnableShadow() 
		&& 0 < m_light->GetShadowMapCameraList().Size())
	{
		_SetupGlobalLightFrustum();
	}	
}

//////////////////////////////////////////////////////////////////////////
void 
LightComponent::_SetupGlobalLightFrustum_NoCascade()
{
	float4 sceneAABBMin( 100000.f,100000.f,100000.f,1.f );
	float4 sceneAABBMax( -100000.f,-100000.f,-100000.f,1.f );

	float4 halfVector( 0.5f,0.5f,0.5f,0.5f );
	sceneAABBMin = float4(-m_sceneMax,-m_sceneMax,-m_sceneMax,1.f);
	sceneAABBMax = float4(m_sceneMax,m_sceneMax,m_sceneMax,1.f);

	float4 vSceneCenter = sceneAABBMin + sceneAABBMax;
	vSceneCenter  *= halfVector;
	float4 vSceneExtents = sceneAABBMax - sceneAABBMin;
	vSceneExtents *= halfVector;

	const Light::ShadowMapCameraList& smcList = m_light->GetShadowMapCameraList();

	const Math::matrix44& lightCameraView = smcList[0]->GetViewTransform();

	const Camera* mainCamera = GraphicSystem::Instance()->GetRenderingCamera();
	n_assert( mainCamera);

	const Math::matrix44& mainCameraProj = mainCamera->GetProjTransform();
	const Math::matrix44& mainCameraView = mainCamera->GetViewTransform();
	Math::matrix44 inverseMainCameraView = matrix44::inverse( mainCameraView );

	float4 vSceneAABBPointsLightSpace[8];
	AppUtil::ShadowMapUtil::CalculateAABBPoints( vSceneAABBPointsLightSpace, vSceneCenter, vSceneExtents );
	for( int index =0; index < 8; ++index )
	{
		vSceneAABBPointsLightSpace[index] = matrix44::transform( lightCameraView, vSceneAABBPointsLightSpace[index] );
	}

	float fFrustumIntervalBegin, fFrustumIntervalEnd;
	float shadowDistance = mainCamera->GetCameraSetting().GetZFar();
	shadowDistance = Math::n_min(shadowDistance, m_ShadowDistance);
	float fCameraNearFarRange = shadowDistance - mainCamera->GetCameraSetting().GetZNear();
	float4 vWorldUnitsPerTexel = float4(0.f,0.f,0.f,0.f);
	float4 vLightCameraOrthographicMin;  // light space frustrum aabb
	float4 vLightCameraOrthographicMax;
	
	float splitDistances[eMaxSplitCounts+1];

	int shadowMapWidth = m_light->GetRealShadowMapSize();
	int shadowSplitCount = m_light->GetRealSplitCount();

	for (int i = 0; i <= (int)(shadowSplitCount); ++i )
	{
		splitDistances[i] = m_splitPercentages[shadowSplitCount][i] * fCameraNearFarRange;
	}

	for( int i = (int)(shadowSplitCount + 1); i < eMaxSplitCounts+1; ++i )
	{
		splitDistances[i] = splitDistances[i-1] * 1.1f;
	}

	for( SizeT iCascadeIndex = 0; iCascadeIndex < shadowSplitCount; ++iCascadeIndex )
	{
		fFrustumIntervalBegin = splitDistances[iCascadeIndex];
		fFrustumIntervalEnd   = splitDistances[iCascadeIndex+1];

		float4 vFrustumPoints[8];

		// This function takes the began and end intervals along with the projection matrix and returns the 8
		// points that repreresent the cascade Interval
		AppUtil::ShadowMapUtil::CreateFrustumPointsFromCascadeInterval( fFrustumIntervalBegin, fFrustumIntervalEnd, 
			mainCameraProj, vFrustumPoints );

		float4 sphereCenter;
		float  radius;
		bool   isEnableSphereBound = (m_shadowProjection == eSphereShadow);

		if ( isEnableSphereBound )
		{
			//compute the sphere center and radius
			AppUtil::ShadowMapUtil::CalculateCloseSphereFromFrustum(vFrustumPoints, sphereCenter, radius);
			// Transform the sphere center from camera view space to world space
			sphereCenter = matrix44::transform( inverseMainCameraView, sphereCenter );
			// Compute the bound in world space
			vFrustumPoints[0] = sphereCenter + float4( radius,  radius, -radius, 0.0f);
			vFrustumPoints[1] = sphereCenter + float4( radius, -radius, -radius, 0.0f);
			vFrustumPoints[2] = sphereCenter + float4(-radius,  radius, -radius, 0.0f);
			vFrustumPoints[3] = sphereCenter + float4(-radius, -radius, -radius, 0.0f);

			vFrustumPoints[4] = sphereCenter + float4( radius,  radius,  radius, 0.0f);
			vFrustumPoints[5] = sphereCenter + float4( radius, -radius,  radius, 0.0f);
			vFrustumPoints[6] = sphereCenter + float4(-radius,  radius,  radius, 0.0f);
			vFrustumPoints[7] = sphereCenter + float4(-radius, -radius,  radius, 0.0f);
		}

		vLightCameraOrthographicMin = AppUtil::S_C_FLOAT4MAX;
		vLightCameraOrthographicMax = AppUtil::S_C_FLOAT4MIN;

		float4 vTempTranslatedCornerPoint;
		// This next section of code calculates the min and max values for the orthographic projection.
		for( int icpIndex=0; icpIndex < 8; ++icpIndex )
		{
			if (!isEnableSphereBound)
			{
				// Transform the frustum from camera view space to world space.
				vFrustumPoints[icpIndex] = matrix44::transform( inverseMainCameraView, vFrustumPoints[icpIndex] );
			}
			// Transform the point from world space to Light Camera Space.
			vTempTranslatedCornerPoint = matrix44::transform( lightCameraView, vFrustumPoints[icpIndex] );

			// Find the closest point.
			vLightCameraOrthographicMin = float4::minimize( vTempTranslatedCornerPoint, vLightCameraOrthographicMin );
			vLightCameraOrthographicMax = float4::maximize( vTempTranslatedCornerPoint, vLightCameraOrthographicMax );
		}

		float4 vLightSpaceSceneAABBminValue = AppUtil::S_C_FLOAT4MAX;  // world space scene aabb 
		float4 vLightSpaceSceneAABBmaxValue = AppUtil::S_C_FLOAT4MIN;       

		// We calculate the min and max vectors of the scene in light space. The min and max "Z" values of the  
		// light space AABB can be used for the near and far plane. This is easier than intersecting the scene with the AABB
		// and in some cases provides similar results.
		for(int index=0; index< 8; ++index) 
		{
			vLightSpaceSceneAABBminValue = float4::minimize( vSceneAABBPointsLightSpace[index], vLightSpaceSceneAABBminValue );
			vLightSpaceSceneAABBmaxValue = float4::maximize( vSceneAABBPointsLightSpace[index], vLightSpaceSceneAABBmaxValue );
		}

		float4 vBoundSize = vLightCameraOrthographicMax - vLightCameraOrthographicMin;
		float4 vBoundCenter = ( vLightCameraOrthographicMax + vLightCameraOrthographicMin ) * 0.5f;
		float4 vHalfSize = vBoundSize * 0.5f;
		
		float4 vPosLightSpace = vBoundCenter;

		double projectX = (double)(vPosLightSpace.x());
		double projectY = (double)(vPosLightSpace.y());
		
		double texelSizeX = ((double)(vBoundSize.x())) / shadowMapWidth;
		double texelSizeY = ((double)(vBoundSize.y())) / shadowMapWidth;

		float modProjectX = float( fmod( projectX, texelSizeX ) );
		float modProjectY = float( fmod( projectY, texelSizeY ) );
		vPosLightSpace.x() -= modProjectX;
		vPosLightSpace.y() -= modProjectY;

		float4 vCorrectPosLightSpace = vPosLightSpace;

		vLightCameraOrthographicMin.set_x( vCorrectPosLightSpace.x() - vHalfSize.x() );
		vLightCameraOrthographicMin.set_y( vCorrectPosLightSpace.y() - vHalfSize.y() );
		vLightCameraOrthographicMax.set_x( vCorrectPosLightSpace.x() + vHalfSize.x() );
		vLightCameraOrthographicMax.set_y( vCorrectPosLightSpace.y() + vHalfSize.y() );

		// The min and max z values are the near and far planes.
		float fFarPlane = -vLightCameraOrthographicMin.z();
		float fNearPlane = -vLightSpaceSceneAABBmaxValue.z();

	    Graphic::CameraSetting cs = smcList[iCascadeIndex]->GetCameraSetting();

		cs.SetupOffCenterOrthogonal(vLightCameraOrthographicMin.x(),vLightCameraOrthographicMax.x(),
			vLightCameraOrthographicMin.y(),vLightCameraOrthographicMax.y(),fNearPlane,fFarPlane);

		smcList[iCascadeIndex]->SetCameraSetting(cs);
		
	}

	GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
	pGMP->SetVectorParam(eGShaderVecLightCameraFrustumIntervalEnd,float4(splitDistances[1],splitDistances[2],splitDistances[3],splitDistances[4]));
	Math::scalar fSize = Math::scalar( smcList.Size() );
	const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();

	pGMP->SetVectorParam(eGShaderVecShadowMapSize,float4((float)shadowMapWidth,(float)shadowMapWidth,m_depthBias,fSize));//width,height,bias,cascade levels
	// set shadow color and strength
	// shadow.w = shadow strength
	pGMP->SetVectorParam(eGShaderVecShadowColor,float4(m_ShadowColor.x(), m_ShadowColor.y(), m_ShadowColor.z(),m_ShadowStrength));
}

void
LightComponent::SetLightPos(const Math::float3& pos)
{
	Math::matrix44 world = m_light->GetTransform();
	world.set_position(float4(pos.x(), pos.y(), pos.z(), 1.0f));
	m_light->SetTransform(world);
}

void
LightComponent::SetLightDir(const Math::float3& dir)
{
	Math::matrix44 world = m_light->GetTransform();
	world.set_zaxis(float4(-dir.x(), -dir.y(), -dir.z(), 0.0f));
	m_light->SetTransform(world);
}
//------------------------------------------------------------------------
void 
LightComponent::_SetupGlobalLightFrustum()
{
	_SetupGlobalLightFrustum_NoCascade();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
void 
LightComponent::SetLightType(Graphic::Light::LightType ltype)
{
	m_light->SetLightType(ltype);
}

//------------------------------------------------------------------------
void
LightComponent::SetEnableShadow(bool enable /* = true */)
{
	if (!m_light->IsEnabled())
	{
		m_CacheShadowState = enable;
		return;
	}

	m_lightDirty = (m_light->IsEnableShadow() != enable);
	m_light->SetEnableShadow(enable);

	//if (!enable)
	//{	
	//	GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
	//	pGMP->SetVectorParam(eGShaderVecShadowMapSize,float4(1,1,m_depthBias,0));//width,height,bias,cascade levels
	//}
}

//------------------------------------------------------------------------

void
LightComponent::SetShadowMapQuality(ShadowMapQuality quality)
{
	if (quality != m_shadowMapQuality && quality < eQualityCounts)
	{
		m_lightDirty = true;
		m_shadowMapQuality = quality;
	}
}
//------------------------------------------------------------------------
LightComponent::ShadowMapQuality LightComponent::GetshadowMapQuality()
{
	return m_shadowMapQuality;
}

//------------------------------------------------------------------------

int 
LightComponent::GetShaowMapSize(ShadowMapQuality quality)
{
	return 512 * (1 << (int)quality);
}
//------------------------------------------------------------------------
void
LightComponent::SetShadowSplitCount(ShadowMapSplitCount splitCount)
{
	if (splitCount != m_shadowSplitCount)
	{
		m_lightDirty = true;
		m_shadowSplitCount = splitCount;		
	}
}
//------------------------------------------------------------------------

LightComponent::ShadowMapSplitCount LightComponent::GetShadowSplitCount( )
{
	return m_shadowSplitCount;
}
//------------------------------------------------------------------------

void 
LightComponent::SetShadowSplitDistances(ShadowMapSplitCount splitCount,float firstDistance, float secondDistance, float thirdDistance)
{
	m_splitPercentages[splitCount][1] = firstDistance;
	m_splitPercentages[splitCount][2] = secondDistance;
	m_splitPercentages[splitCount][3] = thirdDistance;
}
//------------------------------------------------------------------------
void 
LightComponent::GetShadowSplitDistances(ShadowMapSplitCount splitCount,float & outFirstDistance, float & outSecondDistance, float& outThirdDistance)
{
	outFirstDistance = m_splitPercentages[splitCount][1];
	outSecondDistance = m_splitPercentages[splitCount][2];
	outThirdDistance = m_splitPercentages[splitCount][3];
}
//------------------------------------------------------------------------
void 
LightComponent::SetShadowProjType(ShadowMapProjType shadowProjection)
{
	m_shadowProjection = shadowProjection;
}
//------------------------------------------------------------------------
LightComponent::ShadowMapProjType 
	LightComponent::GetShadowProjType()
{
	return m_shadowProjection;
}
//------------------------------------------------------------------------
void 
LightComponent::_OnMoveAfter()
{
	if ( mActor )
	{
		m_light->SetTransform( mActor->GetWorldTranslateNoScale() );
	}
}

//------------------------------------------------------------------------
// copy from other component
void LightComponent::CopyFrom( const GPtr<Component>& pComponent )
{
	if( !pComponent.isvalid()  )
		return;
	if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
		return;

	GPtr<LightComponent> pSource = pComponent.downcast<LightComponent>();
	n_assert( pSource->m_light.isvalid() );

	m_light->CopyFrom(*(pSource->m_light));


	//GPtr<Light> pSourceLight = pSource->m_light;
	//GPtr<Light> pDestLight = m_light;
	//pDestLight->SetLightType( pSourceLight->GetLightType() );
	//pDestLight->SetLightColor( pSourceLight->GetLightColor() );
	//pDestLight->SetLightIntensity( pSourceLight->GetLightIntensity() );
	//pDestLight->SetLightRange( pSourceLight->GetLightRange() );
	//pDestLight->SetConstantAttenuation( pSourceLight->GetConstantAttenuation() );
	//pDestLight->SetLinearAttenuation( pSourceLight->GetLinearAttenuation() );
	//pDestLight->SetQuadraticAttenuation( pSourceLight->GetQuadraticAttenuation() );
	//pDestLight->SetCosCutOff( pSourceLight->GetCosCutOff() );
	//pDestLight->SetExponent( pSourceLight->GetExponent() );

	//pDestLight->SetTransform( pSourceLight->GetTransform() );
}

bool
	LightComponent::IsAllResourceLoaded()
{
	return true;
}

void
	LightComponent::SetupAllResource()
{
	return;
}

void LightComponent::SetShadowMapHandle()
{

}

} // namespace App


