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
#include "GlobalShaderParam.h"
#include "Camera/RenderPipeline/RenderPipeline.h"

namespace Graphic
{
	using namespace Math;

	__ImplementRootClass(GlobalMaterialParam,'GMGS')
		__ImplementImageSingleton(GlobalMaterialParam)
		GlobalMaterialParam::GlobalMaterialParam()
	{
		__ConstructImageSingleton;
		InitializeParamMap();
	}

	GlobalMaterialParam::~GlobalMaterialParam()
	{
		__DestructImageSingleton;
	}

	void GlobalMaterialParam::InitializeParamMap()
	{
		//matrix map
		m_globalShaderParams.SetSize( GlobalParamCount );

		//m_globalShaderParams[eGShaderMatMVP] = GlobalShaderParam(matrix44(),Util::String("g_ModelViewProj"));
		m_globalShaderParams[eGShaderMatV] = GlobalShaderParam(matrix44(),Util::String("g_View"));
		m_globalShaderParams[eGShaderMatInverseV] = GlobalShaderParam(matrix44(),Util::String("g_InverseView"));
		m_globalShaderParams[eGShaderMatM] = GlobalShaderParam(matrix44(),Util::String("g_Model"));
		m_globalShaderParams[eGShaderMatInverseTransposeM] = GlobalShaderParam(matrix44(),Util::String("g_InvTransModel"));
		m_globalShaderParams[eGShaderMatInverseM] = GlobalShaderParam(matrix44(),Util::String("g_InverseModel"));
		m_globalShaderParams[eGShaderMatP] = GlobalShaderParam(matrix44(),Util::String("g_Proj"));
		m_globalShaderParams[eGShaderMatInvVP] = GlobalShaderParam(matrix44(),Util::String("g_InvViewProj"));
		m_globalShaderParams[eGShaderMatLightV] = GlobalShaderParam(matrix44(),Util::String("g_LightView"));
		m_globalShaderParams[eGShaderMatProjector] = GlobalShaderParam(matrix44(),Util::String("g_Projector"));


		float4 row(0.f,0.f,0.f,0.f);
		for (SizeT i = 0; i < 4; ++i)
		{
			m_globalShaderParams[eGShaderMatLightP0 + i] = GlobalShaderParam(matrix44(row,row,row,row),Util::String("g_LightProj") + Util::String::FromInt(i));
		}

		//vector map
		m_globalShaderParams[eGShaderVecAmbientColor] = GlobalShaderParam(float4(0.5f,0.5f,0.5f,1.0f),Util::String("g_Ambient"));
		m_globalShaderParams[eGShaderVecCameraPos] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_CameraPos"));
		m_globalShaderParams[eGShaderVecCameraParam] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_CameraParam"));
		m_globalShaderParams[eGShaderVecScreenSize] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_ScreenSize"));
		m_globalShaderParams[eGShaderVecShadowMapSize] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_ShadowMapSize"));
		m_globalShaderParams[eGShaderVecSoftShadowParam] = GlobalShaderParam(float4(0.3f,1.0f,0.f,0.f),Util::String("g_SoftShadowParam"));
		m_globalShaderParams[eGShaderVecShadowColor] = GlobalShaderParam(float4(0.f,0.f,0.f,1.f),Util::String("g_ShadowColor"));
		m_globalShaderParams[eGShaderVecDebugCameraColor] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_DebugColor"));
		m_globalShaderParams[eGShaderVecFogColor] = GlobalShaderParam(float4(0.5f,0.5f,0.5f,0.0f),Util::String("g_FogColor"));
		m_globalShaderParams[eGShaderVecFogParam] = GlobalShaderParam(float4(0.0f,300.f,1.f,0.f),Util::String("g_FogParam"));
		m_globalShaderParams[eGShaderVecTime] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_Time"));

		for (SizeT i = 0; i < 4; ++i)
		{
			m_globalShaderParams[eGShaderVecLightDir0 + i * 4] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightDir") + Util::String::FromInt(i));
			m_globalShaderParams[eGShaderVecLightDiffuse0 + i * 4] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightDiffuse") + Util::String::FromInt(i));
			m_globalShaderParams[eGShaderVecLightPos0 + i * 4] = GlobalShaderParam(float4(0.f,0.f,0.f,-1.f),Util::String("g_LightPos") + Util::String::FromInt(i));
			m_globalShaderParams[eGShaderVecLightAttenuation0 + i * 4] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightAttenFactor") + Util::String::FromInt(i));
		}

		m_globalShaderParams[eGShaderVecLightCameraNear] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightCameraNear"));
		m_globalShaderParams[eGShaderVecLightCameraFar] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightCameraFar"));
		m_globalShaderParams[eGShaderVecLightCameraFrustumIntervalEnd] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_LightCameraFrustumIntervalEnd"));

		m_globalShaderParams[eGShaderBoolDefaultLight] = GlobalShaderParam(float4(1.f,0.f,0.f,0.f),Util::String("g_DefaultLight"));
		m_globalShaderParams[eGShaderParticleMeshColor] = GlobalShaderParam(float4(1.f,1.f,1.f,1.f),Util::String("g_ParticleMeshColor"));
		m_globalShaderParams[eGShaderMatLMTexParam] = GlobalShaderParam(float4(0.f,0.f,1.f,1.f),Util::String("g_LMTexParam"));
		m_globalShaderParams[eGShaderMatLMEnable] = GlobalShaderParam(float4(0.f,0.f,0.f,0.f),Util::String("g_UseLM"));
		m_globalShaderParams[eGShaderMatShadowReceive] = GlobalShaderParam(float4(1.f,1.f,1.f,1.f),Util::String("g_ShadowReceive"));

		// texture

		m_globalShaderParams[eGShaderTexMainBuffer] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_MainBuffer"));
		m_globalShaderParams[eGShaderTexDepthMap] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DepthMap"));
		m_globalShaderParams[eGShaderTexLightLitMap] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_LightLitMap"));
		m_globalShaderParams[eGShaderTexShadowMap0] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap0"));
		m_globalShaderParams[eGShaderTexShadowMap1] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap1"));
		m_globalShaderParams[eGShaderTexShadowMap2] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap2"));
		m_globalShaderParams[eGShaderTexShadowMap3] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap3"));
		m_globalShaderParams[eGShaderTexShadowMap4] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap4"));
		m_globalShaderParams[eGShaderTexShadowMap5] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap5"));
		m_globalShaderParams[eGShaderTexShadowMap6] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap6"));
		m_globalShaderParams[eGShaderTexShadowMap7] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ShadowMap7"));
		m_globalShaderParams[eGShaderTexSwapBuffer] =  GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_SwapBuffer"));
		m_globalShaderParams[eGShaderTexProjectorMap] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_ProjectorMap"));

		m_globalShaderParams[eGShaderTexDfNormalMap] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfNormalMap"));
		m_globalShaderParams[eGShaderTexDfDepthMap] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfDepthMap"));
		m_globalShaderParams[eGShaderTexDfParamMap] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfParamMap"));
		m_globalShaderParams[eGShaderTexDfLightMap0] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfAndSpecMap0"));
		m_globalShaderParams[eGShaderTexDfLightMap1] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfAndSpecMap1"));
		m_globalShaderParams[eGShaderTexDfLightMap2] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_DfAndSpecMap2"));

		// lightmap support 
		m_globalShaderParams[eGShaderTexLightmap] = GlobalShaderParam(RenderBase::TextureHandle(),Util::String("g_Lightmap"));

	}
	//------------------------------------------------------------------------
	void GlobalMaterialParam::SetMatrixParam(GlobalMatrixParamIndex index, const matrix44& mat)
	{
		n_assert(index >= eGShaderMatBegin && index < eGShaderMatEnd);
		m_globalShaderParams[index].m_value.SetMatrix44(mat);
	}

	void GlobalMaterialParam::GetMatrixParam(GlobalMatrixParamIndex index,Util::String& name, Math::matrix44& mat) const
	{
		n_assert(index >= eGShaderMatBegin && index < eGShaderMatEnd);

		name = m_globalShaderParams[index].m_name;
		mat = m_globalShaderParams[index].m_value.GetMatrix44();
	}

	void GlobalMaterialParam::SetVectorParam(GlobalVectorParamIndex index, const float4& vec)
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		m_globalShaderParams[index].m_value.SetFloat4(vec);
	}

	void GlobalMaterialParam::GetVectorParam(GlobalVectorParamIndex index,Util::String& name,Math::float4& vec) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		name = m_globalShaderParams[index].m_name;
		vec = m_globalShaderParams[index].m_value.GetFloat4();
	}

	void GlobalMaterialParam::SetVectorParam_X(GlobalVectorParamIndex index,float val)
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		m_globalShaderParams[index].m_value.SetFloat4_X(val);
	}

	void GlobalMaterialParam::GetVectorParam_X(GlobalVectorParamIndex index,Util::String& name,float& val) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		name = m_globalShaderParams[index].m_name;
		val = m_globalShaderParams[index].m_value.GetFloat4_X();
	}

	void GlobalMaterialParam::SetVectorParam_Y(GlobalVectorParamIndex index,float val)
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		m_globalShaderParams[index].m_value.SetFloat4_Y(val);
	}

	void GlobalMaterialParam::GetVectorParam_Y(GlobalVectorParamIndex index,Util::String& name,float& val) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		name = m_globalShaderParams[index].m_name;
		val = m_globalShaderParams[index].m_value.GetFloat4_Y();
	}

	void GlobalMaterialParam::SetVectorParam_Z(GlobalVectorParamIndex index,float val)
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		m_globalShaderParams[index].m_value.SetFloat4_Z(val);
	}

	void GlobalMaterialParam::GetVectorParam_Z(GlobalVectorParamIndex index,Util::String& name,float& val) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		name = m_globalShaderParams[index].m_name;
		val = m_globalShaderParams[index].m_value.GetFloat4_Z();
	}

	void GlobalMaterialParam::SetVectorParam_W(GlobalVectorParamIndex index,float val)
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		m_globalShaderParams[index].m_value.SetFloat4_W(val);
	}

	void GlobalMaterialParam::GetVectorParam_W(GlobalVectorParamIndex index,Util::String& name,float& val) const
	{
		n_assert(index >= eGShaderVecBegin && index < eGShaderVecEnd);

		name = m_globalShaderParams[index].m_name;
		val = m_globalShaderParams[index].m_value.GetFloat4_W();
	}

	void GlobalMaterialParam::SetTextureParam(GlobalTexParamIndex index, const Util::String& texName, RenderBase::TextureHandle texHandle)
	{
		n_assert( index >= eGShaderTexBegin && index < eGShaderTexEnd);

		if ( m_globalShaderParams[index].m_name == texName )
		{
			m_globalShaderParams[index].m_value.SetObject(texHandle.AsObject());
		}
		else
		{
			n_warning("GlobalMaterialParam::SetTextureParam: Invalid texName/n" );
		}
	}

	void GlobalMaterialParam::SetTextureParam(GlobalTexParamIndex index, RenderBase::TextureHandle texHandle)
	{
		n_assert( index >= eGShaderTexBegin && index < eGShaderTexEnd);

		m_globalShaderParams[index].m_value.SetObject(texHandle.AsObject());
	}

	void GlobalMaterialParam::GetTextureParam(GlobalTexParamIndex index,Util::String& name,RenderBase::TextureHandle& handle) const
	{
		n_assert( index >= eGShaderTexBegin && index < eGShaderTexEnd);

		name = m_globalShaderParams[index].m_name;
		handle = m_globalShaderParams[index].GetHandle();
	}

	void GlobalMaterialParam::ResetTextureCache()
	{
		for ( IndexT i = eGShaderTexBegin; i < eGShaderTexEnd; ++i )
		{
			m_globalShaderParams[i].m_value.SetObject(NULL);
		}
	}

	RenderBase::TextureHandle 
		GlobalMaterialParam::FindTextureParam(const Util::String& texName)
	{
		for ( IndexT index = eGShaderTexBegin; index < eGShaderTexEnd; ++index )
		{
			if ( m_globalShaderParams[index].m_name == texName )
			{
				return m_globalShaderParams[index].GetHandle();
			}
		}
		return RenderBase::TextureHandle();
	}

}