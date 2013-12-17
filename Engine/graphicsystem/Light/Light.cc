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
#include "Light.h"
#include "GraphicSystem.h"
#include "materialmaker/parser/GenesisShaderParser.h"
namespace Graphic
{


	static const float S_C_ATTEN_REF = 3;
	static const float S_C_ATTEN_REF2 = 0.00001f;

	__ImplementClass(Light,'LTGS',GraphicObject)

		Light::Light() : m_lightType(eInvailidLightType),
		m_lightColor(0.5f,0.5f,0.5f,1.f),
		m_lightIntensity(1.f),
		m_constantAttenuation(1.f),
		m_linearAttenuation(0.8f),
		m_quadraticAttenuation(0.f),
		m_cosHalfOuterAngle(Math::n_cos(float(22.5*PI/180.0))),
		m_cosHalfInnerAngle(Math::n_cos(float(20.0f*PI/180.0))),
		m_invCosConeDifference(1.0f / (m_cosHalfInnerAngle - m_cosHalfOuterAngle)),
		m_spotExponent(1.0),
		m_falloff(1.0),
		m_range(10.f),
		m_enableShadow(false),
		m_bEnable(true),
		m_RealShadowmapSize(0),
		//m_owner(NULL),
		m_listener(NULL),
		m_renderScene(NULL),
		m_Lightmapping(eLM_Flexible),
		m_LightmapShadow(false)
	{
	}

	Light::~Light()
	{
		Discard();
		const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
		n_assert( gs.isvalid() );
		if ( gs.isvalid() && !m_dummyShadowRTs.IsEmpty())
		{
			for (SizeT i = 0; i < m_dummyShadowRTs.Size(); ++i )
			{
				m_dummyShadowRTs[i] = 0;
			}

		}
		m_dummyShadowRTs.Clear();
	}

	void Light::Discard()
	{
		DiscardShadow();
	}
	void Light::DiscardShadow()
	{
		for (SizeT i = 0; i < m_shadowMapCameras.Size(); ++i )
		{
			if (m_shadowMapCameras[i].isvalid())
			{
				m_shadowMapCameras[i]->Discard();
			}

		}
		m_shadowMapCameras.Clear();
	}

	void Light::Attach(RenderScene* rnsc)
	{
		Detach();
		n_assert(rnsc);
		m_renderScene = rnsc;
		rnsc->_AddLight(this);

		for (SizeT i = 0; i < m_shadowMapCameras.Size(); ++i )
		{
			if (m_shadowMapCameras[i].isvalid())
			{
				m_shadowMapCameras[i]->SetRenderScene(rnsc);
			}

		}
	}

	void Light::Detach()
	{
		if (m_renderScene)
		{
			m_renderScene->_RemoveLight(this);
		}
		for (SizeT i = 0; i < m_shadowMapCameras.Size(); ++i )
		{
			if (m_shadowMapCameras[i].isvalid())
			{
				m_shadowMapCameras[i]->SetRenderScene(NULL);
			}

		}
	}

	void Light::RenderShadowMapBegin()
	{
		if (m_listener)
		{
			m_listener->RenderShadowMapBegin(this);
		}
	}

	void Light::_SetupMainLightFrustum(GPtr<Camera>& cam)
	{
		n_assert(cam.isvalid())
			const Camera::ViewPort& vp = cam->GetViewport();
		CameraSetting cs =	cam->GetCameraSetting();
		cs.SetupOrthogonal(float(vp.width),float(vp.height),cs.GetZNear(),cs.GetZFar());
		cam->SetCameraSetting(cs);
		cam->GetRenderPipelineManager()->m_pipelineContext.m_renderDatas.SetUseFor(RenderDataCollection::Shadow);
		cam->SetCameraOrder(eCO_Shadow);
		cam->SetCullMask(eRLCameraRenderAll);
		cam->SetRenderSurface(true);
		cam->Setup();
		cam->SetTransform(m_transform);
		cam->OnTransformChanged();
	}

	void Light::SetTransform(const matrix44& trans)
	{
		Super::SetTransform(trans);
		for(ShadowMapCameraList::Iterator it = m_shadowMapCameras.Begin();it != m_shadowMapCameras.End(); ++it)
		{
			n_assert((*it).isvalid())
			{
				(*it)->SetTransform(this->GetTransform());
				(*it)->OnTransformChanged();
			}
		}		
	}

	float4 Light::GetLightDir() const//
	{
		float4 dir = m_transform.get_zaxis();
		dir = -float4::normalize(dir);//dir = dir.normalize(dir);
		return dir;
	}

	void Light::SetLightType(const LightType& ltype)
	{
		m_lightType = ltype;
		if (m_renderScene)
		{
			m_renderScene->_SortLights();
		}
	}

	/// set Lightmapping
	void Light::SetLightmapType (LightMapType mode)
	{
		m_Lightmapping = mode;
	}

	/// get Lightmapping
	const Light::LightMapType& Light::GetLightmapType() const
	{
		return m_Lightmapping;
	}
	///
	/// Set LightmapModeShadow
	void Light::SetLightmapModeShadow(bool bLightmapShadow)
	{
		m_LightmapShadow = bLightmapShadow;
	}
	/// Get LightmapModeShadow
	bool Light::GetLightmapModeShadow() const
	{
		return m_LightmapShadow;
	}

	void Light::SetEnableShadow(bool enable)
	{

		m_enableShadow = enable;
	}

	void Light::SetAttenuations(float constAtt, float linearAtt, float quadAtt)
	{
		m_constantAttenuation = constAtt;
		m_linearAttenuation = linearAtt;
		m_quadraticAttenuation = quadAtt;
	}

	void Light::CopyFrom(const Light& src)
	{
		m_lightType = src.m_lightType;
		m_lightColor = src.m_lightColor;
		m_lightIntensity = src.m_lightIntensity;
		m_range = src.m_range;
		m_cosHalfInnerAngle = src.m_cosHalfInnerAngle;
		m_cosHalfOuterAngle = src.m_cosHalfOuterAngle;
		m_invCosConeDifference = src.m_invCosConeDifference;
		m_spotExponent = src.m_spotExponent;
		m_falloff = src.m_falloff;
		m_transform = m_transform;
		m_Lightmapping = src.m_Lightmapping;
		m_LightmapShadow = src.m_LightmapShadow;
		m_enableShadow = src.m_enableShadow;
	}

	void Light::SetupSunlightShadow(int shadowMapSize, int splitCount)
	{
		n_assert(eSunLight == m_lightType)

		const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
		const RenderBase::DisplayMode& dm = gs->GetMainViewPortWindow()->GetDisplayMode();
		n_assert( gs.isvalid() );
		const RenderScene::Lights& lightList = m_renderScene->GetLights();
		if (0 == lightList.FindIndex(this))
		{
			n_assert( S_C_CASCADEDCAMERANUM < (eGShaderTexShadowMap7 - eGShaderTexShadowMap0 + 1) );
			GPtr<RenderToTexture> shadowMap = RenderToTexture::Create();
			shadowMap->Setup(shadowMapSize,shadowMapSize,RenderBase::PixelFormat::R32F, RenderBase::RenderTarget::ClearAll,
				Math::float4(1.f,1.f,1.f,1.f), true,RenderBase::AntiAliasQuality::None);

			GPtr<RenderToTexture> swapTexture = RenderToTexture::Create();
			swapTexture->Setup(shadowMapSize * splitCount,shadowMapSize,RenderBase::PixelFormat::R32F, RenderBase::RenderTarget::ClearAll,
				Math::float4(1.f,1.f,1.f,1.f), true,RenderBase::AntiAliasQuality::None);

			m_RealShadowmapSize = shadowMapSize;


			for (SizeT i = 0;i < splitCount ; ++i)
			{
				float aspect = float(dm.GetWidth())/float(dm.GetHeight());

				Material::GetGlobalMaterialParams()->SetTextureParam( (GlobalTexParamIndex)(i+eGShaderTexShadowMap0), 
					Util::String("g_ShadowMap") + Util::String::FromInt(i),
					swapTexture->GetTextureHandle());

				GPtr<Camera> shadowMapCamera = Camera::Create();
				_SetupMainLightFrustum(shadowMapCamera);
				shadowMapCamera->SetRenderToTexture(shadowMap);
				shadowMapCamera->SetSwapTexture(swapTexture);
				shadowMapCamera->SetRenderScene(m_renderScene);

				m_shadowMapCameras.Append(shadowMapCamera);
			}

			for (SizeT i = splitCount ; i < S_C_CASCADEDCAMERANUM; i++)
			{
				if ( i  >= (m_dummyShadowRTs.Size() + splitCount) )
				{
					GPtr<RenderToTexture> shadowMap = RenderToTexture::Create();
					shadowMap->Setup(1, 1, RenderBase::PixelFormat::R32F, RenderBase::RenderTarget::ClearAll,
						Math::float4(1.f,1.f,1.f,1.f), true,RenderBase::AntiAliasQuality::None);
					m_dummyShadowRTs.Append(shadowMap);
				}

				Material::GetGlobalMaterialParams()->SetTextureParam(
					(GlobalTexParamIndex)(i+eGShaderTexShadowMap0),
					Util::String("g_ShadowMap") + Util::String::FromInt(i),
					m_dummyShadowRTs[ i-splitCount ]->GetTextureHandle());
			}
		}			
	}

	void Light::ResetShadowMap(const SizeT nSplit)
	{
		

		SizeT nCount = m_shadowMapCameras.Size();

		for (IndexT i = 0; i < nCount; ++i)
		{
			for (IndexT iSplit = 0; iSplit < nSplit; ++iSplit)
			{
				Material::GetGlobalMaterialParams()->SetTextureParam( (GlobalTexParamIndex)(iSplit+eGShaderTexShadowMap0), 
					Util::String("g_ShadowMap") + Util::String::FromInt(iSplit),
					m_shadowMapCameras[i]->GetSwapTexture()->GetTextureHandle());
			}
			

			
		}
	}
}