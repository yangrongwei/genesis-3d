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
#include "appframework/component.h"
#include "graphicfeature/components/lightcomponent.h"

namespace App
{
	class LightComponentSerialization
	{
	public:
		LightComponentSerialization( const LightComponent* pComponent )
			:mObject(pComponent)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(pReader);
				return;
			}
			else if ( 3 == ver )
			{
				Load_3(pReader);
				return;
			}
			else if ( 4 == ver )
			{
				Load_4(pReader);
				return;
			}
			else if ( 5 == ver )
			{
				Load_5(pReader);
				return;
			}
			else if( 6 == ver )
			{
				Load_6(pReader);
				return;
			}
			else if(7 == ver)
			{
				Load_7(pReader);
				return;
			}
			else if(8 == ver)
			{
				Load_8(pReader);
				return;
			}
			n_error(" SceneSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Load_3( AppReader* pReader );
		void Load_4( AppReader* pReader );
		void Load_5( AppReader* pReader );
		void Load_6( AppReader* pReader );
		void Load_7( AppReader* pReader);
		void Load_8( AppReader* pReader);

		void Save( AppWriter* pWriter );
	protected:
		const LightComponent* mObject;

	};

	const char* s_LightType = "LightType";
	const char* s_LightColor = "LightColor";
	const char* s_OppositeColor = "OppositeColor";
	const char* s_LightIntensity = "LightIntensity";
	const char* s_LightRange = "LightRange";
	const char* s_LightAmbientColor = "LightAmbientColor";
	//const char* s_CastShadow = "CastShadow";
	const char* s_ConeAngle = "LightConeAngle";
	const char* s_ConstantAttenuation = "ConstantAttenuation";
	const char* s_LinearAttenuation = "LinearAttenuation";
	const char* s_QuadraticAttenuation = "QuadraticAttenuation";
	const char* s_CostCutOff = "CostCutOff";
	const char* s_Exponent = "Exponent";
	const char* s_DepthBias = "DepthBias";
	const char* s_SceneMax = "SceneMax";
	const char* s_Shadow = "EnableShadow";

	const char* s_ShadowLightStrength = "ShadowStrength";
	const char* s_ShadowDistanceL = "ShadowDistance";
	const char* s_ShadowMapQuality = "ShadowMapQuality";
	const char* s_ShadowSplitCount = "ShadowSplitCount";
	const char* s_ShadowProjection = "ShadowProjection";
	const char* s_ShadowSplitDistances0 = "ShadowSplitDistance0";
	const char* s_ShadowSplitDistances1 = "ShadowSplitDistance1";
	const char* s_ShadowSplitDistances2 = "ShadowSplitDistance2";
	const char* s_ShadowSplitDistances3 = "ShadowSplitDistance3";
	const char* s_LightMaping = "LightMaping";
	const char* s_LightEnable = "LightEnable";
	const char* s_Falloff = "Falloff";
	const char* s_CosHalfOuterAngle = "CosHalfOuterAngle";
	const char* s_CosHalfInnerAngle = "CosHalfInnerAngle";

	//------------------------------------------------------------------------
	void LightComponentSerialization::Load_1(AppReader* pSerialize)
	{
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			int type;
			pSerialize->SerializeInt( s_LightType, type );

			uint hex;
			pSerialize->SerializeUInt(s_LightColor, hex);
			Math::Color32 c32(hex);

			float Intensity;
			pSerialize->SerializeFloat(s_LightIntensity, Intensity);

			float ConstantAttenuation;
			pSerialize->SerializeFloat(s_ConstantAttenuation, ConstantAttenuation);

			float LinearAttenuation;
			pSerialize->SerializeFloat(s_LinearAttenuation, LinearAttenuation);

			float QuadraticAttenuation;
			pSerialize->SerializeFloat(s_QuadraticAttenuation, QuadraticAttenuation);

			float CostCutOff;
			pSerialize->SerializeFloat(s_CostCutOff, CostCutOff);

			float Exponen;
			pSerialize->SerializeFloat(s_Exponent, Exponen);

			float DepthBias;
			pSerialize->SerializeFloat(s_DepthBias, DepthBias);

			float SceneMax;
			pSerialize->SerializeFloat(s_SceneMax, SceneMax);

			pLC->SetLightType( (Graphic::Light::LightType)type );
			pLC->SetLightColor( c32 );
			pLC->SetLightIntensity( Intensity );
			pLC->SetConstantAttenuation(ConstantAttenuation);
			pLC->SetLinearAttenuation(LinearAttenuation);
			pLC->SetQuadraticAttenuation(QuadraticAttenuation);
			pLC->SetCosCutOff(CostCutOff);
			pLC->SetSpotExponent(Exponen);
			pLC->SetDepthBias(DepthBias);
			pLC->SetSceneMax(SceneMax);

			//pLC->UpdateLightShape();
		}
	}

	//------------------------------------------------------------------------
	void LightComponentSerialization::Load_2(AppReader* pSerialize)
	{
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			int type;
			pSerialize->SerializeInt( s_LightType, type );

			uint hex;
			pSerialize->SerializeUInt(s_LightColor, hex);
			Math::Color32 c32(hex);

			float Intensity;
			pSerialize->SerializeFloat(s_LightIntensity, Intensity);

			float ConstantAttenuation;
			pSerialize->SerializeFloat(s_ConstantAttenuation, ConstantAttenuation);

			float LinearAttenuation;
			pSerialize->SerializeFloat(s_LinearAttenuation, LinearAttenuation);

			float QuadraticAttenuation;
			pSerialize->SerializeFloat(s_QuadraticAttenuation, QuadraticAttenuation);

			float CostCutOff;
			pSerialize->SerializeFloat(s_CostCutOff, CostCutOff);

			float Exponen;
			pSerialize->SerializeFloat(s_Exponent, Exponen);

			float DepthBias;
			pSerialize->SerializeFloat(s_DepthBias, DepthBias);

			float SceneMax;
			pSerialize->SerializeFloat(s_SceneMax, SceneMax);

			bool EnableShadow;
			pSerialize->SerializeBool(s_Shadow,EnableShadow);

			pLC->SetLightType( (Graphic::Light::LightType)type );
			pLC->SetLightColor( c32 );
			pLC->SetLightIntensity( Intensity );
			//pLC->SetConstantAttenuation(ConstantAttenuation);
			//pLC->SetLinearAttenuation(LinearAttenuation);
			//pLC->SetQuadraticAttenuation(QuadraticAttenuation);

			pLC->SetAttenuations(ConstantAttenuation, LinearAttenuation, QuadraticAttenuation);


			pLC->SetCosCutOff(CostCutOff);
			pLC->SetSpotExponent(Exponen);
			pLC->SetDepthBias(DepthBias);
			pLC->SetSceneMax(SceneMax);
			pLC->SetEnableShadow(EnableShadow);
			//pLC->UpdateLightShape();
		}
	}
	//------------------------------------------------------------------------
	void LightComponentSerialization::Load_3( AppReader* pSerialize )
	{
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			int type;
			pSerialize->SerializeInt( s_LightType, type );

			uint hex;
			pSerialize->SerializeUInt(s_LightColor, hex);
			Math::Color32 c32(hex);

			float Intensity;
			pSerialize->SerializeFloat(s_LightIntensity, Intensity);

			float LightRange;
			pSerialize->SerializeFloat(s_LightRange, LightRange);

			float ConstantAttenuation;
			pSerialize->SerializeFloat(s_ConstantAttenuation, ConstantAttenuation);

			float LinearAttenuation;
			pSerialize->SerializeFloat(s_LinearAttenuation, LinearAttenuation);

			float QuadraticAttenuation;
			pSerialize->SerializeFloat(s_QuadraticAttenuation, QuadraticAttenuation);

			float CostCutOff;
			pSerialize->SerializeFloat(s_CostCutOff, CostCutOff);

			float Exponen;
			pSerialize->SerializeFloat(s_Exponent, Exponen);

			float DepthBias;
			pSerialize->SerializeFloat(s_DepthBias, DepthBias);

			float SceneMax;
			pSerialize->SerializeFloat(s_SceneMax, SceneMax);

			bool EnableShadow;
			pSerialize->SerializeBool(s_Shadow,EnableShadow);


			pLC->SetLightType( (Graphic::Light::LightType)type );
			pLC->SetLightColor( c32 );
			pLC->SetLightIntensity( Intensity );
			pLC->SetLightRange( LightRange );
			//pLC->SetConstantAttenuation(ConstantAttenuation);
			//pLC->SetLinearAttenuation(LinearAttenuation);
			//pLC->SetQuadraticAttenuation(QuadraticAttenuation);

			pLC->SetAttenuations(ConstantAttenuation, LinearAttenuation, QuadraticAttenuation);


			pLC->SetCosCutOff(CostCutOff);
			pLC->SetSpotExponent(Exponen);
			pLC->SetDepthBias(DepthBias);
			pLC->SetSceneMax(SceneMax);
			pLC->SetEnableShadow(EnableShadow);
			//pLC->UpdateLightShape();
		}
	}
	//------------------------------------------------------------------------

	void LightComponentSerialization::Load_4( AppReader* pReader )
	{
		Load_3( pReader );
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			float shadowDistance;
			int shadowMapQuality; //LightComponent::SHADOWMAPQUALITY
			int shadowSplitCounts;
			int shadowProjection;

			float firstSplitDistance,sencondSplitDistance,thirdSplitDistance;

			pReader->SerializeFloat( s_ShadowDistanceL, shadowDistance );
			pReader->SerializeInt( s_ShadowMapQuality, shadowMapQuality );
			pReader->SerializeInt( s_ShadowSplitCount, shadowSplitCounts );
			pReader->SerializeInt( s_ShadowProjection, shadowProjection );

			pLC->SetShadowDistance( shadowDistance );
			pLC->SetShadowMapQuality(LightComponent::ShadowMapQuality(shadowMapQuality));
			pLC->SetShadowSplitCount(LightComponent::ShadowMapSplitCount(shadowSplitCounts));
			pLC->SetShadowProjType(LightComponent::ShadowMapProjType(shadowProjection));

			
			pReader->SerializeFloat( s_ShadowSplitDistances0, firstSplitDistance);
			pLC->SetShadowSplitDistances(LightComponent::eTwoCountsSplit, firstSplitDistance);

			pReader->SerializeFloat( s_ShadowSplitDistances1, firstSplitDistance);
			pReader->SerializeFloat( s_ShadowSplitDistances2, sencondSplitDistance);
			pReader->SerializeFloat( s_ShadowSplitDistances3, thirdSplitDistance);
			pLC->SetShadowSplitDistances(LightComponent::eFourCountsSplit, firstSplitDistance, sencondSplitDistance, thirdSplitDistance);
			
		}
		
	}
	//------------------------------------------------------------------------

	void LightComponentSerialization::Load_5( AppReader* pReader)
	{
		Load_4( pReader );
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			int lightMaping;
			pReader->SerializeInt( s_LightMaping, lightMaping );
			pLC->SetLightmapType((Graphic::Light::LightMapType)lightMaping);
		}
	}

	void LightComponentSerialization::Load_6( AppReader* pReader)
	{
		Load_5( pReader );
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			float shadowStrength;
			pReader->SerializeFloat( s_ShadowLightStrength, shadowStrength );
			pLC->SetShadowStrength( shadowStrength );
		}
		
	}
	void LightComponentSerialization::Load_7( AppReader* pReader)
	{
		Load_6( pReader );
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			bool enable;
			pReader->SerializeBool( s_LightEnable, enable );
			pLC->SetEnabled(enable);
		}

	}

	void LightComponentSerialization::Load_8( AppReader* pReader)
	{
		Load_7( pReader );
		LightComponent* pLC = const_cast<LightComponent*>( mObject );
		{
			float temp;

			pReader->SerializeFloat( s_Falloff, temp );
			pLC->SetFalloff( temp );

			pReader->SerializeFloat( s_CosHalfOuterAngle, temp );
			pLC->SetCosHalfOuterAngle( temp );

			pReader->SerializeFloat( s_CosHalfInnerAngle, temp );
			pLC->SetCosHalfInnerAngle( temp );
		}

	}
	//------------------------------------------------------------------------
	void LightComponentSerialization::Save(AppWriter* pSerialize)
	{
		LightComponent* pLC = const_cast<LightComponent*>( mObject );

		//private data
		{
			pSerialize->SerializeInt( s_LightType, (int)(pLC->GetLightType()) );
			pSerialize->SerializeUInt( s_LightColor, pLC->GetLightColor().ToUInt() );
			pSerialize->SerializeFloat( s_LightIntensity, pLC->GetLightIntensity() );
			pSerialize->SerializeFloat( s_LightRange, pLC->GetLightRange() );
			pSerialize->SerializeFloat(s_ConstantAttenuation, pLC->GetConstantAttenuation());
			pSerialize->SerializeFloat(s_LinearAttenuation, pLC->GetLinearAttenuation());
			pSerialize->SerializeFloat(s_QuadraticAttenuation, pLC->GetQuadraticAttenuation());
			pSerialize->SerializeFloat(s_CostCutOff, pLC->GetCosCutOff());
			pSerialize->SerializeFloat(s_Exponent, pLC->GetSpotExponent());
			pSerialize->SerializeFloat(s_DepthBias, pLC->GetDepthBias());
			pSerialize->SerializeFloat(s_SceneMax, pLC->GetSceneMax());
			pSerialize->SerializeBool(s_Shadow,pLC->IsShadowEnable());

			pSerialize->SerializeFloat( s_ShadowDistanceL, pLC->GetShadowDistance() );
			pSerialize->SerializeInt( s_ShadowMapQuality, (int)pLC->GetshadowMapQuality() );
			pSerialize->SerializeInt( s_ShadowSplitCount, (int)pLC->GetShadowSplitCount() );
			pSerialize->SerializeInt( s_ShadowProjection, (int)pLC->GetShadowProjType() );

			float firstSplitDistance,sencondSplitDistance,thirdSplitDistance;

			pLC->GetShadowSplitDistances(LightComponent::eTwoCountsSplit, firstSplitDistance, sencondSplitDistance, thirdSplitDistance);
			pSerialize->SerializeFloat( s_ShadowSplitDistances0, firstSplitDistance);

			pLC->GetShadowSplitDistances(LightComponent::eFourCountsSplit, firstSplitDistance, sencondSplitDistance, thirdSplitDistance);
			pSerialize->SerializeFloat( s_ShadowSplitDistances1, firstSplitDistance);
			pSerialize->SerializeFloat( s_ShadowSplitDistances2, sencondSplitDistance);
			pSerialize->SerializeFloat( s_ShadowSplitDistances3, thirdSplitDistance);

			pSerialize->SerializeInt(s_LightMaping,(int)pLC->GetLightmapType());
			pSerialize->SerializeFloat( s_ShadowLightStrength,  pLC->GetShadowStrength() );
			pSerialize->SerializeBool(s_LightEnable,pLC->IsEnabled());

			pSerialize->SerializeFloat(s_Falloff, pLC->GetFalloff() );
			pSerialize->SerializeFloat(s_CosHalfOuterAngle, pLC->GetCosHalfOuterAngle());
			pSerialize->SerializeFloat(s_CosHalfInnerAngle, pLC->GetCosHalfInnerAngle());
		}
		return;
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version LightComponent::GetVersion() const
	{
		return 8;	//	当前版本号是8
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void LightComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		LightComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void LightComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		LightComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

}


