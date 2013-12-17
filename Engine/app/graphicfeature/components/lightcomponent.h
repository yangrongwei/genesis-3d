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
#ifndef __LIAHGTCOMPONENT_H__
#define __LIAHGTCOMPONENT_H__
#include "appframework/component.h"
#include "graphicsystem/Light/Light.h"
#include "util/variant.h"
#include "math/color.h"
#include "math/float3.h"
#include "math/matrix44.h"
//------------------------------------------------------------------------------
namespace App
{

typedef TypeConvert<Graphic::Light::LightType> LightTypeConvert;

class LightComponent : public App::Component, public Graphic::LightListener
{
	__DeclareSubClass(LightComponent, Component);
public:

	enum ShadowMapQuality
	{
		eLow = 0,
		eMiddle,
		eHigh,
		eQualityCounts,
	};
	
	enum ShadowMapSplitCount
	{
		eOneCountsSplit = 1,
		eTwoCountsSplit = 2,
		eFourCountsSplit = 4,
		eMaxSplitCounts = 4,
	};

	enum ShadowMapProjType
	{
		eBoxShadow = 0,
		eSphereShadow,
	};

	

	LightComponent();
	virtual ~LightComponent();

	/// set light enabled
	void SetEnabled( bool bEnable);

	/// get light enabled
	bool IsEnabled();

    /// override to register accepted messages
    virtual void SetupAcceptedMessages();
    /// handle a single message
    virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

	/// get light color
	Math::Color32 GetLightColor() const;
	/// set light color by Math::Color32
	void SetLightColor(const Math::Color32& c);
	/// set light color by r¡¢g¡¢b¡¢a
	void SetLightColor(ubyte inR, ubyte inG, ubyte inB, ubyte inA);

	/// set shadow color 
	void SetShadowColor(const Math::Color32& color);
	/// get shadow color
	Math::Color32 GetShadowColor() const;
	/// set shadow strength
	void SetShadowStrength(float shadowStrength);
	/// get shadow strength
	float GetShadowStrength() const;

	/// set shadow distance
	void SetShadowDistance(float shadowDistance);
	/// get shadow distance
	float GetShadowDistance() const;

	Math::float4 GetLightColorF() const;
	void SetLightColorF(const Math::float4& color);

	/// get light intensity
	float GetLightIntensity() const;
	/// set light intensity
	void SetLightIntensity(float f);

	/// get light type
	Graphic::Light::LightType GetLightType(void) const;
	/// set light type
	void SetLightType(Graphic::Light::LightType ltype);

	/// set Lightmapping
	void SetLightmapType (Graphic::Light::LightMapType mode);
	/// get Lightmapping
	Graphic::Light::LightMapType GetLightmapType() const;

	/// Set LightmapModeShadow
	void SetLightmapModeShadow(bool bLightmapShadow);
	/// Get LightmapModeShadow
	bool GetLightmapModeShadow() const;
	/// get light dir
	Math::float3 GetLightDir() const;

	/// set light dir
	void SetLightDir(const Math::float3& dir);

	/// get light pos
	Math::float3 GetLightPos() const;

	/// set light pos
	void SetLightPos(const Math::float3& pos);

	/// set constant attenuation(spot,point)
	void SetConstantAttenuation(const float& ca);
	/// get constant attenuation(spot,point)
	const float& GetConstantAttenuation() const;

	/// set linear attenuation(spot,point)
	void SetLinearAttenuation(const float& la);
	/// get linear attenuation(spot,point)
	const float& GetLinearAttenuation() const;

	/// set quadratic attenuation(spot,point)
	void SetQuadraticAttenuation(const float& qa);
	/// get quadratic attenuation(spot,point)
	const float& GetQuadraticAttenuation() const;

	/// set light range
	void  SetLightRange(const float& range);
	const float& GetLightRange() const;

	void SetAttenuations(float constAtt, float linearAtt, float quadAtt);

	/// set quadratic attenuation(spot)
	void SetCosCutOff(const float& cco);
	/// get quadratic attenuation(spot)
	const float& GetCosCutOff() const;
	/// set cos half of the outerAngle
	void SetCosHalfOuterAngle(const float& cosHalfOuterAngle);
	/// get cos half of the outerAngle
	const float& GetCosHalfOuterAngle() const;

	/// set cos half of the innerAngle
	void SetCosHalfInnerAngle(const float& cosHalfInnerAngle);
	/// get cos half of the innerAngle
	const float& GetCosHalfInnerAngle() const;

	/// set exponent(spot)
	void SetSpotExponent(const float& expo);
	/// get exponent(spot)
	const float& GetSpotExponent() const;

	/// set falloff
	void SetFalloff(const float& falloff);
	/// get falloff
	const float& GetFalloff() const;

	/// set exponent(directional with shadow)
	void SetDepthBias(const float& bias);
	/// get exponent(directional with shadow)
	const float& GetDepthBias() const;

	/// set scene AABB(directional with shadow)
	void SetSceneMax(const float& sm);
	/// get scene AABB(directional with shadow)
	const float& GetSceneMax() const;

	/// enable shadow(sunlight)
	void SetEnableShadow(bool enable = true);

	/// set shadow map quality
	void SetShadowMapQuality(ShadowMapQuality quality = eMiddle);
	
	/// get shadow map quality
	LightComponent::ShadowMapQuality GetshadowMapQuality();
	
	/// set shadow map splitCount
	void SetShadowSplitCount(ShadowMapSplitCount splitCount);
	
	/// get shadow map splitCount
	LightComponent::ShadowMapSplitCount GetShadowSplitCount( );

	/// set shadow every split distance
	void SetShadowSplitDistances(ShadowMapSplitCount splitCount,float firstDistance = 1.0f, float secondDistance = 1.0f, float thirdDistance = 1.0f);
	/// get shadow every split distance
	void GetShadowSplitDistances(ShadowMapSplitCount splitCount,float & outFirstDistance, float & outSecondDistance, float& outThirdDistance);
	/// set shadow projection type
	void SetShadowProjType(ShadowMapProjType shadowProjection);
	/// get shadow projection type
	ShadowMapProjType GetShadowProjType();

	/// is shadow enabled(sunlight)
	const bool IsShadowEnable() const;

	/// @Component::_SetupGlobalLightFrustum called when the light type is Directional. 
	virtual void _SetupGlobalLightFrustum();

	virtual void _SetupGlobalLightFrustum_NoCascade();
	//virtual void _SetupGlobalLightFrustumEx();

	/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
	virtual void SetupCallbacks();

	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	virtual Version GetVersion() const;

	// @ISerialization::Load 
	virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

	// @ISerialization::Save
	virtual void Save( AppWriter* pWriter ) const;

	// copy from other component
	virtual void CopyFrom( const GPtr<Component>& pComponent );

	virtual void SetupAllResource();
	virtual bool IsAllResourceLoaded();
protected:
	/// called from Actor::ActivateComponents()
	virtual void OnActivate();
	/// called from Actor::DeactivateComponents()
	virtual void OnDeactivate();

	virtual void OnRenderSceneChanged();

	/// @Component::_OnBeginFrame called after movement has happened. 
	virtual void _OnBeginFrame();

	/// called before rendering happens
	virtual void _OnFrame();

	/// @Component::_OnEndFrame called after movement has happened. 
	virtual void _OnEndFrame();

	/// @Component::Component called after movement has happened. 
	/// this will change the light postion and dir when Actor change
	virtual void _OnMoveAfter();
	

private:

	virtual void RenderShadowMapBegin(Graphic::Light* sender);

	GPtr<Graphic::Light> m_light;
	float m_sceneMax;
	// directional light special
	bool m_lightDirty; 
	bool m_bQualityChange;
	float m_depthBias;
	ShadowMapQuality m_shadowMapQuality;
	ShadowMapSplitCount m_shadowSplitCount;
	ShadowMapProjType m_shadowProjection;
	friend class LightComponentSerialization;
	
	bool m_CacheShadowState;
	Math::float4 m_ShadowColor;
	float m_ShadowStrength;
	float m_ShadowDistance;
	float m_splitPercentages[eMaxSplitCounts+1][eMaxSplitCounts+1];

	


private:
	/// get shadow map size by shadowmapQuality
	int GetShaowMapSize(ShadowMapQuality quality);

	void SetShadowMapHandle();

};

//------------------------------------------------------------------------
inline
void 
LightComponent::SetEnabled( bool bEnable)
{
	if (m_light->IsEnabled() != bEnable)
	{
		if (bEnable)
		{
			m_light->SetEnabled( true );
			this->SetEnableShadow( m_CacheShadowState );
		}
		else
		{
			m_CacheShadowState = m_light->IsEnableShadow();
			this->SetEnableShadow( false );
			m_light->SetEnabled( false );
		}
	}
	
}
inline
bool 
LightComponent::IsEnabled()
{
	return m_light->IsEnabled();
}
//------------------------------------------------------------------------
inline
Math::float4
LightComponent::GetLightColorF() const
{
	return m_light->GetLightColor( false );
}
//------------------------------------------------------------------------
inline
void
LightComponent::SetLightColorF(const Math::float4& color)
{
	m_light->SetLightColor(color);
}
//------------------------------------------------------------------------
inline
Math::Color32 
LightComponent::GetLightColor() const
{
	return Math::Color32( Math::n_scalartoByte( m_light->GetLightColor( false ).x() ),
		           Math::n_scalartoByte( m_light->GetLightColor( false ).y() ),
				   Math::n_scalartoByte( m_light->GetLightColor( false ).z() ),
				   Math::n_scalartoByte( m_light->GetLightColor( false ).w() )
					); 
}
//------------------------------------------------------------------------
inline
void 
LightComponent::SetLightColor(const Math::Color32& color)
{
	Math::ColorF cf(color);
	Math::float4 lcolor( cf.r, cf.g,cf.b,cf.a);
	m_light->SetLightColor(lcolor);
}
//------------------------------------------------------------------------
inline
void 
LightComponent::SetLightColor(ubyte inR, ubyte inG, ubyte inB, ubyte inA)
{
	Math::Color32 color(inR, inG, inB, inA);
	Math::ColorF cf(color);
	m_light->SetLightColor(Math::float4(cf.r, cf.g,cf.b,cf.a));
}
//------------------------------------------------------------------------
inline
void
LightComponent::SetShadowColor(const Math::Color32& color)
{
	Math::ColorF cf(color);
	m_ShadowColor.set(color[0],color[1],color[2],color[3]);
}
//------------------------------------------------------------------------
inline
Math::Color32 
LightComponent::GetShadowColor() const
{
	return Math::Color32( Math::n_scalartoByte( m_ShadowColor.x() ),
		Math::n_scalartoByte( m_ShadowColor.y() ),
		Math::n_scalartoByte( m_ShadowColor.z() ),
		Math::n_scalartoByte( m_ShadowColor.w() )
		); 
}

//------------------------------------------------------------------------
inline
void
LightComponent::SetShadowStrength(float shadowStrength)
{
	m_ShadowStrength = shadowStrength;
}
//------------------------------------------------------------------------
inline
float 
LightComponent::GetShadowStrength() const
{
	return m_ShadowStrength;
}

//------------------------------------------------------------------------
inline
void
LightComponent::SetShadowDistance(float shadowDistance)
{
	m_ShadowDistance = shadowDistance;
}
//------------------------------------------------------------------------
inline
float 
LightComponent::GetShadowDistance() const
{
	return m_ShadowDistance;
}
//------------------------------------------------------------------------
inline
float 
LightComponent::GetLightIntensity() const
{
	return m_light->GetLightIntensity();
}
//------------------------------------------------------------------------
inline
void 
LightComponent::SetLightIntensity(float f)
{
	m_light->SetLightIntensity(f);
}
//------------------------------------------------------------------------
inline
Graphic::Light::LightType 
LightComponent::GetLightType(void) const
{
	return m_light->GetLightType();
}
//------------------------------------------------------------------------
inline
Math::float3
LightComponent::GetLightDir() const
{
	Math::float4 f4 = m_light->GetLightDir();
	return Math::float3(f4.x(), f4.y(),f4.z());
}
//------------------------------------------------------------------------
inline
Math::float3
LightComponent::GetLightPos() const
{
	Math::float4 f4 = m_light->GetLightPos();
	return Math::float3(f4.x(), f4.y(),f4.z());
}

inline void
LightComponent::SetConstantAttenuation(const float& ca)
{
	m_light->SetConstantAttenuation(ca);
}

inline const float&
LightComponent::GetConstantAttenuation() const
{
	return m_light->GetConstantAttenuation();
}

inline void
LightComponent::SetLinearAttenuation(const float& la)
{
	m_light->SetLinearAttenuation(la);
}

inline const float&
LightComponent::GetLinearAttenuation() const
{
	return m_light->GetLinearAttenuation();
}

inline void
LightComponent::SetQuadraticAttenuation(const float& qa)
{
	m_light->SetQuadraticAttenuation(qa);
}

inline const float&
LightComponent::GetQuadraticAttenuation() const
{
	return m_light->GetQuadraticAttenuation();
}
inline void  
LightComponent::SetLightRange(const float& range)
{
	m_light->SetLightRange( range );
}

inline const float&
LightComponent::GetLightRange() const
{
	return m_light->GetLightRange();
}

inline void
LightComponent::SetCosCutOff(const float& cco)
{
	m_light->SetCosHalfOuterAngle(cco);
}
inline void
LightComponent::SetAttenuations(float constAtt, float linearAtt, float quadAtt)
{
	m_light->SetAttenuations(constAtt, linearAtt, quadAtt);
}

inline const float&
LightComponent::GetCosCutOff() const
{
	return m_light->GetCosHalfOuterAngle();
}

inline void
	LightComponent::SetCosHalfOuterAngle(const float& cosHalfOuterAngle)
{
	m_light->SetCosHalfOuterAngle(cosHalfOuterAngle);
}

inline const float&
	LightComponent::GetCosHalfOuterAngle() const
{
	return m_light->GetCosHalfOuterAngle();	
}

inline void
	LightComponent::SetCosHalfInnerAngle(const float& cosHalfInnerAngle)
{
	m_light->SetCosHalfInnerAngle(cosHalfInnerAngle);
}

inline const float&
	LightComponent::GetCosHalfInnerAngle() const
{
	return m_light->GetCosHalfInnerAngle();
}

inline void
LightComponent::SetSpotExponent(const float& expo)
{
	m_light->SetExponent(expo);
}

inline const float&
LightComponent::GetSpotExponent() const
{
	return m_light->GetExponent();	
}

inline void 
	LightComponent::SetFalloff(const float& falloff)
{
	m_light->SetFalloff(falloff);
}

inline const float& 
	LightComponent::GetFalloff() const
{
	return m_light->GetFalloff();
}

inline void
LightComponent::SetDepthBias(const float& bias)
{
	m_depthBias = bias;
}

inline const float&
LightComponent::GetDepthBias() const
{
	return m_depthBias;	
}

inline void 
LightComponent::SetSceneMax(const float& sm)
{
	m_sceneMax = sm;
}

inline const float&
LightComponent::GetSceneMax() const
{
	return m_sceneMax;	
}

inline const bool
LightComponent::IsShadowEnable() const
{
	bool bShadowEnabled = false;

	if (!m_light->IsEnabled())
	{
		bShadowEnabled = m_CacheShadowState;
	}
	else
	{
		bShadowEnabled = m_light->IsEnableShadow();
	}

	return bShadowEnabled;
}

/// set Lightmapping
inline void 
	LightComponent::SetLightmapType (Graphic::Light::LightMapType mode)
{
	m_light->SetLightmapType( mode );
}
/// get Lightmapping
inline Graphic::Light::LightMapType
	LightComponent::GetLightmapType() const
{
	return m_light->GetLightmapType();
}

/// Set LightmapModeShadow
inline void 
	LightComponent::SetLightmapModeShadow(bool bLightmapShadow)
{
	m_light->SetLightmapModeShadow(bLightmapShadow);
}
/// Get LightmapModeShadow
inline bool 
	LightComponent::GetLightmapModeShadow() const
{
	return m_light->GetLightmapModeShadow();
}

}; // namespace GraphicsFeature
//------------------------------------------------------------------------------

#endif //__LIAHGTCOMPONENT_H__
