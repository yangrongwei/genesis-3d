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
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "base/GraphicObject.h"
#include "math/quaternion.h"
#include "Camera/Camera.h"
#include "graphicsystem/Vision/RenderScene.h"

namespace Graphic
{
	using namespace Math;
	class Camera;
	class RenderToTexture;
	class Light;

	class LightListener
	{
	public:
		virtual ~LightListener(){};
		virtual void RenderShadowMapBegin(Light* sender) = 0;
	};

	class Light : public GraphicObject
	{
		__DeclareSubClass(Light,GraphicObject)
	public:
		enum LightType
		{
			eInvailidLightType = -1,
			eSunLight,
			eDirectionalLight,
			ePointLight,
			eSpotLight,			

			eLightTypeCount
		};

		enum LightMapType
		{
			eLM_NoBaked, // 
			eLM_Flexible, // 
			eLM_JustForBaked //
		};

		typedef GPtr<Camera> ShadowMapCamera;
		typedef Util::Array<ShadowMapCamera> ShadowMapCameraList;
		Light();
		virtual ~Light();

		void RenderShadowMapBegin();

		void SetupSunlightShadow(int shadowMapSize = 1024, int splitCount = 4);

		void DiscardShadow();

		void _SetupMainLightFrustum(GPtr<Camera>& cam);

		void Discard();

		virtual void SetTransform(const matrix44& trans);

		float4 GetLightDir() const;

		float4 GetLightPos() const;

		void SetEnabled( bool bEnable);
		bool IsEnabled();

		void SetLightColor(const float4& color);
		const float4& GetLightColor(bool bCheckLightState = true) const;

		void SetLightIntensity(const float& intensity);
		const float& GetLightIntensity() const;

		void SetLightType(const LightType& ltype);
		const LightType& GetLightType() const;

		/// set Lightmapping
		void SetLightmapType (LightMapType mode);
		/// get Lightmapping
		const Light::LightMapType& GetLightmapType() const;

		/// Set LightmapModeShadow
		void SetLightmapModeShadow(bool bLightmapShadow);
		/// Get LightmapModeShadow
		bool GetLightmapModeShadow() const;

		void SetLightRange(const float& range);
		const float& GetLightRange() const;
		//		void UpdateLightRange();

		void SetConstantAttenuation(const float& ca);
		const float& GetConstantAttenuation() const;

		void SetLinearAttenuation(const float& la);
		const float& GetLinearAttenuation() const;

		void SetFalloff(const float& falloff);
		const float& GetFalloff() const;

		void SetQuadraticAttenuation(const float& qa);
		const float& GetQuadraticAttenuation() const;

		void SetAttenuations(float constAtt, float linearAtt, float quadAtt);

		void SetCosHalfOuterAngle(const float& cosHalfOuterAngle);
		const float& GetCosHalfOuterAngle() const;

		void SetCosHalfInnerAngle(const float& cosHalfInnerAngle);
		const float& GetCosHalfInnerAngle() const;

		const float& GetInvCosConeDifference() const;

		void SetExponent(const float& expo);
		const float& GetExponent() const;

		const ShadowMapCameraList& GetShadowMapCameraList() const;
		// check the state of light
		void SetEnableShadow(bool enable);
		const bool IsEnableShadow() const;
		const SizeT GetRealSplitCount() const;
		const int GetRealShadowMapSize() const;

		void CopyFrom(const Light& src);

		void SetOwner(void* owner);

		void* GetOwner() const;

		void SetListener(LightListener* listener);
		LightListener* GetListener() const;

		void Attach(RenderScene* resc);
		void Detach();
		bool Attached() const;

		RenderScene* GetRenderScene() const;

		void ResetShadowMap(const SizeT nSplit);

	protected:		

		//void* m_owner;
		LightListener* m_listener;
		RenderScene* m_renderScene;
		ShadowMapCameraList m_shadowMapCameras;
		Util::Array<GPtr<RenderToTexture> > m_dummyShadowRTs;

		float4 m_lightColor;
		float m_lightIntensity;

		//spot/point light spec start
		float m_range;
		float m_constantAttenuation;
		float m_linearAttenuation;
		float m_quadraticAttenuation;
		//spot light spec
		float m_cosHalfOuterAngle;
		float m_cosHalfInnerAngle;
		float m_invCosConeDifference;
		float m_spotExponent;
		//spot/point light spec end

		// Falloff
		float m_falloff;

		LightType m_lightType;
		//used for shadowmap
		bool m_enableShadow;
		int m_RealShadowmapSize;

		//used for lightmap
		LightMapType m_Lightmapping;
		bool m_LightmapShadow;
		bool m_bEnable;

		static const SizeT S_C_CASCADEDCAMERANUM = 4;
	};		
	inline const SizeT Light::GetRealSplitCount() const
	{
		return m_shadowMapCameras.Size();
	}

	inline const int Light::GetRealShadowMapSize() const
	{
		return m_RealShadowmapSize;
	}

	inline float4
		Light::GetLightPos() const
	{
		return m_transform.get_position();
	}

	inline void 
		Light::SetEnabled( bool bEnable)
	{
		m_bEnable = bEnable;
	}

	inline bool 
		Light::IsEnabled( )
	{
		return m_bEnable;
	}

	inline void
		Light::SetLightColor(const float4& color)
	{
		m_lightColor = color;
	}

	inline const float4&
		Light::GetLightColor(bool bCheckLightState) const
	{
		if (bCheckLightState && (!m_bEnable) )
		{
			static Math::float4 blackColor(0.0f, 0.0f, 0.0f, 1.0f);

			return blackColor;
		}
		else
		{
			return m_lightColor;
		}
	}

	inline void
		Light::SetLightIntensity(const float& intensity)
	{
		m_lightIntensity = intensity;
	}

	inline const float&
		Light::GetLightIntensity() const
	{
		return m_lightIntensity;
	}

	inline const Light::LightType& 
		Light::GetLightType() const
	{
		return m_lightType;
	}

	inline void 
		Light::SetLightRange(const float& range)
	{
		m_range = range;
	}

	inline const float& 
		Light::GetLightRange() const
	{
		return m_range;
	}

	inline void
		Light::SetConstantAttenuation(const float& ca)
	{
		m_constantAttenuation = ca;
	}

	inline const float&
		Light::GetConstantAttenuation() const
	{
		return m_constantAttenuation;	
	}

	inline void
		Light::SetLinearAttenuation(const float& la)
	{
		m_linearAttenuation = la;
	}

	inline const float&
		Light::GetLinearAttenuation() const
	{
		return m_linearAttenuation;	
	}

	inline void
		Light::SetQuadraticAttenuation(const float& qa)
	{
		m_quadraticAttenuation = qa;
	}

	inline const float&
		Light::GetQuadraticAttenuation() const
	{
		return m_quadraticAttenuation;	
	}

	inline void
		Light::SetCosHalfOuterAngle(const float& cosHalfOuterAngle)
	{
		m_cosHalfOuterAngle = cosHalfOuterAngle;
		m_invCosConeDifference = 1.0f / (m_cosHalfInnerAngle - m_cosHalfOuterAngle);
	}

	inline const float&
		Light::GetCosHalfOuterAngle() const
	{
		return m_cosHalfOuterAngle;	
	}

	inline void
		Light::SetCosHalfInnerAngle(const float& cosHalfInnerAngle)
	{
		m_cosHalfInnerAngle = cosHalfInnerAngle;
		m_invCosConeDifference = 1.0f / (m_cosHalfInnerAngle - m_cosHalfOuterAngle);
	}

	inline const float&
		Light::GetCosHalfInnerAngle() const
	{
		return m_cosHalfInnerAngle;
	}

	inline const float&
		Light::GetInvCosConeDifference() const
	{
		return m_invCosConeDifference;
	}

	inline void
		Light::SetExponent(const float& expo)
	{
		m_spotExponent = expo;
	}

	inline const float&
		Light::GetExponent() const
	{
		return m_spotExponent;	
	}

	inline void
		Light::SetFalloff(const float& falloff)
	{
		m_falloff = falloff;
	}

	inline const float& 
		Light::GetFalloff() const
	{
		return m_falloff;
	}

	inline const Util::Array< GPtr<Camera> >& 
		Light::GetShadowMapCameraList() const
	{
		return m_shadowMapCameras;
	}

	inline const bool 
		Light::IsEnableShadow() const
	{
		return m_enableShadow;
	}
	inline RenderScene*
		Light::GetRenderScene() const
	{
		return m_renderScene;
	}

	inline void 
		Light::SetListener(LightListener* listener)
	{
		m_listener = listener;
	}
	inline LightListener*
		Light::GetListener() const
	{
		return m_listener;
	}

	inline bool 
		Light::Attached() const
	{
		return (m_renderScene != NULL);
	}
}
#endif//_LIGHT_H_