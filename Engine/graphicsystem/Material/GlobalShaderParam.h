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
#ifndef GLOBALSHADERPARAM_H_
#define GLOBALSHADERPARAM_H_
#include "util/fixedarray.h"
#include "util/variant.h"

#include "MaterialParam.h"
namespace Graphic
{
	enum GlobalMatrixParamIndex {
		eGShaderMatBegin = 0,

		eGShaderMatCommonBegin = eGShaderMatBegin,
		eGShaderMatV = eGShaderMatCommonBegin,		//0,	g_View
		eGShaderMatInverseV,						//		g_InverseView
		eGShaderMatP,								//		g_Proj
		eGShaderMatInvVP,							//		g_InvViewProj
		eGShaderMatLightV,							//		g_LightView
		eGShaderMatLightP0,							//		g_LightProj[0]
		eGShaderMatLightP1,							//		g_LightProj[1]
		eGShaderMatLightP2,							//		g_LightProj[2]
		eGShaderMatLightP3,							//		g_LightProj[3]
		eGShaderMatCommonEnd,

		eGShaderMatCustomBegin = eGShaderMatCommonEnd,
		//eGShaderMatMVP = eGShaderMatCustomBegin,	//		g_ModelViewProj
		eGShaderMatM = eGShaderMatCustomBegin,		//		g_Model
		eGShaderMatInverseTransposeM,				//		g_InvTransModel
		eGShaderMatInverseM,						//		g_InverseModel
		eGShaderMatProjector,						//		g_Projector
		eGShaderMatCustomEnd,

		eGShaderMatEnd = eGShaderMatCustomEnd,		

		eGShaderMatCount = eGShaderMatEnd - eGShaderMatBegin,
		eGShaderMatCommenCount = eGShaderMatCommonEnd - eGShaderMatCommonBegin,
		eGShaderMatCustomCount = eGShaderMatCustomEnd - eGShaderMatCustomBegin,
	};

	enum GlobalVectorParamIndex {
		eGShaderVecBegin = eGShaderMatEnd,

		eGShaderVecCommonBegin = eGShaderVecBegin,
		eGShaderVecAmbientColor = eGShaderVecCommonBegin,	//		g_Ambient
		eGShaderVecCameraPos,								//		g_CameraPos
		eGShaderVecCameraParam,								//		g_CameraParam
		eGShaderVecScreenSize,								//		g_ScreenSize
		eGShaderVecShadowMapSize,							//		g_ShadowMapSize
		eGShaderVecSoftShadowParam,							//      g_SoftShadowParam
		eGShaderVecShadowColor,								//		g_ShadowColor
		eGShaderVecDebugCameraColor,						//		g_DebugColor
		eGShaderVecFogColor,								//		g_FogColor
		eGShaderVecFogParam,								//		g_FogParam
		eGShaderVecTime,									//		g_Time
		eGShaderVecCommonEnd,

		eGShaderVecCustomBegin = eGShaderVecCommonEnd,
		eGShaderVecLightDir0 = eGShaderVecCustomBegin,		//		g_LightDir[0]
		eGShaderVecLightDiffuse0,							//		g_LightDiffuse[0]
		eGShaderVecLightPos0,								//		g_LightPos[0]
		eGShaderVecLightAttenuation0,						//		g_LightAttenFactor[0]

		eGShaderVecLightDir1,								//		g_LightDir[1]
		eGShaderVecLightDiffuse1,							//		g_LightDiffuse[1]
		eGShaderVecLightPos1,								//		g_LightPos[1]
		eGShaderVecLightAttenuation1,						//		g_LightAttenFactor[1]

		eGShaderVecLightDir2,								//		g_LightDir[2]
		eGShaderVecLightDiffuse2,							//		g_LightDiffuse[2]
		eGShaderVecLightPos2,								//		g_LightPos[2]
		eGShaderVecLightAttenuation2,						//		g_LightAttenFactor[2]

		eGShaderVecLightDir3,								//		g_LightDir[3]
		eGShaderVecLightDiffuse3,							//		g_LightDiffuse[3]
		eGShaderVecLightPos3,								//		g_LightPos[3]
		eGShaderVecLightAttenuation3,						//		g_LightAttenFactor[3]

		eGShaderVecLightCameraNear,							//		g_LightCameraNear
		eGShaderVecLightCameraFar,							//		g_LightCameraFar
		eGShaderVecLightCameraFrustumIntervalEnd,			//		g_LightCameraFrustumIntervalEnd

		eGShaderBoolDefaultLight,                           //      g_DefaultLight
		eGShaderParticleMeshColor,                          //      g_ParticleMeshColor
		eGShaderMatLMTexParam,                              //      g_LMTexParam
		eGShaderMatLMEnable,								//      g_UseLM
		eGShaderMatShadowReceive,                           //      g_ShadowReceive


		eGShaderVecCustomEnd,

		eGShaderVecEnd = eGShaderVecCustomEnd,

		eGShaderVecCount = eGShaderVecEnd - eGShaderVecBegin,
		eGShaderVecCommonCount = eGShaderVecCommonEnd - eGShaderVecCommonBegin,
		eGShaderVecCustomCount = eGShaderVecCustomEnd - eGShaderVecCustomBegin,
	};

	enum GlobalTexParamIndex{
		eGShaderTexBegin = eGShaderVecEnd,
		eGShaderTexMainBuffer = eGShaderTexBegin,	//		g_MainBuffer
		eGShaderTexDepthMap,						//		g_DepthMap
		eGShaderTexLightLitMap,						//		g_LightLitMap

		eGShaderTexShadowMap0,						//		g_ShadowMap0
		eGShaderTexShadowMap1,						//		g_ShadowMap1
		eGShaderTexShadowMap2,						//		g_ShadowMap2
		eGShaderTexShadowMap3,						//		g_ShadowMap3

		eGShaderTexShadowMap4,						
		eGShaderTexShadowMap5,						
		eGShaderTexShadowMap6,						
		eGShaderTexShadowMap7,						
		eGShaderTexSwapBuffer,						//		g_SwapBuffer	
		eGShaderTexProjectorMap,					//		g_ProjectorMap


		eGShaderTexDfNormalMap,						//		g_DfNormalMap
		eGShaderTexDfDepthMap,						//		g_DfDepthMap
		eGShaderTexDfParamMap,						//		g_DfParamMap
		eGShaderTexDfLightMap0,						//		g_DfAndSpecMap0 used for deferred lighting.
		eGShaderTexDfLightMap1,						//		g_DfAndSpecMap1 used for deferred lighting.
		eGShaderTexDfLightMap2,						//		g_DfAndSpecMap2 used for deferred lighting.
		eGShaderTexLightmap,						//      g_Lightmap used for lightmapping
		eGShaderTexEnd,

		eGShaderTexCount = eGShaderTexEnd - eGShaderTexBegin
	};

	enum GlobalParm
	{
		GlobalParamCount = eGShaderTexEnd,
	};

	struct GlobalShaderParam
	{
		Util::String m_name;

		Util::Variant m_value;

		GlobalShaderParam(){
		}

		GlobalShaderParam(const Math::matrix44& value,const Util::String& name) 
			: m_value(value)
			, m_name(name){
		}

		GlobalShaderParam(const Math::float4& value,const Util::String& name) 
			: m_value(value)
			, m_name(name)
		{
		};

		GlobalShaderParam(RenderBase::TextureHandle value,const Util::String& name) 
			: m_value(value.AsObject())
			, m_name(name)
		{
		};

		void SetValue(const Math::matrix44& val){
			m_value.SetMatrix44(val);
		};

		void SetValue(const Math::float4& val){
			m_value.SetFloat4(val);
		};

		void SetValue(RenderBase::TextureHandle val){
			m_value.SetObject(val.AsObject());
		};
		RenderBase::TextureHandle GetHandle() const
		{

#ifdef _DEBUG
			RenderBase::RenderCommandType* temp = dynamic_cast<RenderBase::RenderCommandType*>(m_value.GetObject());
			if (NULL == temp)
			{
				n_error("Type Error: value of m_value is not the RenderBase::RenderCommandType");
			}
			return RenderBase::TextureHandle(temp);
#else
			return RenderBase::TextureHandle(static_cast<RenderBase::RenderCommandType*>(m_value.GetObject()));
#endif // _DEBUG

		}
	};

	typedef Util::FixedArray<GlobalShaderParam> GlobalShaderParamMap;

	class GlobalMaterialParam : public Core::RefCounted
	{
		__DeclareClass(GlobalMaterialParam)
			__DeclareImageSingleton(GlobalMaterialParam);
	public:
		GlobalMaterialParam();
		~GlobalMaterialParam();

		void InitializeParamMap();

		const GlobalShaderParamMap& GetGlobalShaderParamMap(void) const;

		void SetMatrixParam(GlobalMatrixParamIndex index,const Math::matrix44& mat);
		const Math::matrix44& GetMatrixParam( GlobalMatrixParamIndex index ) const;   
		const Util::String& GetMatrixParamName(GlobalMatrixParamIndex index) const;
		void GetMatrixParam(GlobalMatrixParamIndex index,Util::String& name,Math::matrix44& mat) const;

		void SetVectorParam(GlobalVectorParamIndex index, const Math::float4& vec);
		Math::float4 GetVectorParam( GlobalVectorParamIndex index ) const;   
		const Util::String& GetVectorParamName(GlobalVectorParamIndex index) const;
		void GetVectorParam(GlobalVectorParamIndex index,Util::String& name,Math::float4& vec) const;

		void SetVectorParam_X(GlobalVectorParamIndex index,float val);
		void GetVectorParam_X(GlobalVectorParamIndex index,Util::String& name,float& val) const;

		void SetVectorParam_Y(GlobalVectorParamIndex index,float val);
		void GetVectorParam_Y(GlobalVectorParamIndex index,Util::String& name,float& val) const;

		void SetVectorParam_Z(GlobalVectorParamIndex index,float val);
		void GetVectorParam_Z(GlobalVectorParamIndex index,Util::String& name,float& val) const;

		void SetVectorParam_W(GlobalVectorParamIndex index,float val);
		void GetVectorParam_W(GlobalVectorParamIndex index,Util::String& name,float& val) const;


		void SetTextureParam(GlobalTexParamIndex index, const Util::String& texName, RenderBase::TextureHandle texHandle);
		void SetTextureParam(GlobalTexParamIndex index, RenderBase::TextureHandle texHandle);
		RenderBase::TextureHandle GetTextureParam( GlobalTexParamIndex index ) const; 
		const Util::String& GetTextureParamName(GlobalTexParamIndex index) const;
		void GetTextureParam(GlobalTexParamIndex index,Util::String& name,RenderBase::TextureHandle& handle) const;
		RenderBase::TextureHandle FindTextureParam(const Util::String& texName);

		bool CheckTextureParamBind(GlobalTexParamIndex index, const Util::String& texName);

		void ResetTextureCache();
	protected:
		GlobalShaderParamMap m_globalShaderParams;
	};

	//------------------------------------------------------------------------
	inline
		const GlobalShaderParamMap& 
		GlobalMaterialParam::GetGlobalShaderParamMap(void) const
	{
		return m_globalShaderParams;
	}
	//------------------------------------------------------------------------
	inline
		const Math::matrix44& 
		GlobalMaterialParam::GetMatrixParam( GlobalMatrixParamIndex index ) const
	{
		n_assert(index >= eGShaderMatBegin && index < eGShaderMatEnd);
		return m_globalShaderParams[index].m_value.GetMatrix44();
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		GlobalMaterialParam::GetMatrixParamName(GlobalMatrixParamIndex index) const
	{
		n_assert(index >= eGShaderMatBegin && index < eGShaderMatEnd);
		return m_globalShaderParams[index].m_name;
	}
	//------------------------------------------------------------------------
	inline
		Math::float4 
		GlobalMaterialParam::GetVectorParam( GlobalVectorParamIndex index ) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);
		return m_globalShaderParams[index].m_value.GetFloat4();
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		GlobalMaterialParam::GetVectorParamName(GlobalVectorParamIndex index) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);
		return m_globalShaderParams[index].m_name;
	}
	//------------------------------------------------------------------------
	inline
		RenderBase::TextureHandle 
		GlobalMaterialParam::GetTextureParam( GlobalTexParamIndex index ) const
	{
		n_assert( index >= eGShaderTexBegin && index < eGShaderTexEnd);
		return static_cast<RenderBase::RenderCommandType*>(m_globalShaderParams[index].m_value.GetObject());
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		GlobalMaterialParam::GetTextureParamName(GlobalTexParamIndex index) const
	{
		n_assert( index >= eGShaderTexBegin && index < eGShaderTexEnd);
		return m_globalShaderParams[index].m_name;
	}
	//------------------------------------------------------------------------
	inline
		bool
		GlobalMaterialParam::CheckTextureParamBind(GlobalTexParamIndex index, const Util::String& texName)
	{
		return m_globalShaderParams[index].m_name == texName;
	}
}
#endif//GLOBALSHADERPARAM_H_