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
#ifndef _SHADERCOMPILERSETTING_H_
#define _SHADERCOMPILERSETTING_H_


#include "util/string.h"
#include "util/array.h"
#include "util/dictionary.h"


namespace ShaderProgramCompiler
{

	class CommonShaderSetting 
{
	
public:

		CommonShaderSetting();

		~CommonShaderSetting();

public:

	enum ShaderModel 
	{
		ShaderModel11 = 0,
		ShaderModel20,
		ShaderModel30,	
	};

	enum ShaderType
	{
		Vertex = 0,
		Pixel,
		Template,
	};

	enum GPUSDK
	{
		GPUSDKD3D9 = 0,
		GPUSDKIOPENGLES,
	};
	
public:
	
		void     AddEntry(const ShaderType& type, const Util::String& entryName);

		void     SetEntryName(const ShaderType& type, const Util::String& entryName);

		bool     HasEntry(const ShaderType& type) const;

		bool     HasEntry() const;

		const Util::String& GetEntryName(const ShaderType& type) const;

		void     SetShaderModel(const ShaderModel& sm);

		const  ShaderModel GetShaderModel() const;

		void     SetShaderType(const ShaderType& st);

		const ShaderType  GetShaderType() const;

		void SetGpuSDK(const GPUSDK& sdk);

		const GPUSDK GetGpuSDK() const;

		static Util::String  GpuSdkAsString(const GPUSDK& sdk);

private:


		Util::Dictionary<ShaderType, Util::String> m_ShaderEntry;
		ShaderModel                                m_ShaderModel;
		ShaderType                                 m_ShaderType;
		GPUSDK                                     m_SDK;

};

inline void CommonShaderSetting::SetGpuSDK(const CommonShaderSetting::GPUSDK& sdk)
{
	m_SDK = sdk;
}

inline const CommonShaderSetting::GPUSDK CommonShaderSetting::GetGpuSDK() const
{
	return m_SDK;
}

inline Util::String CommonShaderSetting::GpuSdkAsString(const CommonShaderSetting::GPUSDK& sdk)
{
		Util::String sValue;
		switch (sdk)
		{
		case CommonShaderSetting::GPUSDKD3D9 :
			sValue = "D3D9";
			break;
		case CommonShaderSetting::GPUSDKIOPENGLES :
			sValue = "OpenGLES";
			break;
		default:
			n_warning("UnSupported GPU SDK!\n");
		}

		return sValue;
}

inline void CommonShaderSetting::AddEntry(const ShaderType& type, const Util::String& entryName)
{
	IndexT res = m_ShaderEntry.FindIndex(type);

	if (res == InvalidIndex)
	{
		m_ShaderEntry.Add(type, entryName);
	}
}

inline bool CommonShaderSetting::HasEntry(const ShaderType& type) const
{
	IndexT res = m_ShaderEntry.FindIndex(type);

	if (res != InvalidIndex)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

inline bool CommonShaderSetting::HasEntry() const
{
	bool bEmpty = m_ShaderEntry.IsEmpty();

	if (bEmpty)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline const Util::String& CommonShaderSetting::GetEntryName(const CommonShaderSetting::ShaderType& type) const
{
	return m_ShaderEntry[type];
}

inline void CommonShaderSetting::SetEntryName(const CommonShaderSetting::ShaderType& type, const Util::String& entryName)
{
	m_ShaderEntry[type] = entryName;
}

inline void CommonShaderSetting::SetShaderModel(const ShaderModel& sm)
{
	m_ShaderModel = sm;
}

inline const CommonShaderSetting::ShaderModel CommonShaderSetting::GetShaderModel() const
{
	return m_ShaderModel;
}

inline void CommonShaderSetting::SetShaderType(const CommonShaderSetting::ShaderType& st)
{
	m_ShaderType = st;
}

inline const CommonShaderSetting::ShaderType CommonShaderSetting::GetShaderType() const
{
	return m_ShaderType;
}

class ShadingTemplateSetting 
{
	
public:

	ShadingTemplateSetting();

	 ~ShadingTemplateSetting();

public:


	enum ShadingBuiltInOption
	{
		LightMap = 0,
		VertexLight,
		Light,
		Fog,
	};

public:

	void CreateFinalShadingOptions();

	bool HasShadingOption(const ShadingBuiltInOption& option) const;

	Util::Dictionary<ShadingBuiltInOption, bool>& GetShadingOptions();

	void SetLightingType(const Util::String& type);

	const Util::String& GetLightingType() const;

	void SetColorModifier(const Util::String& cm);

	const Util::String& GetColorModifier() const;

	void SetAlphaTestValue(const Util::String& value);

	const Util::String& GetAlphaTestValue() const;

	void SetCastShadow(bool value);

	const bool IsCastShadow() const;

	void SetGenShadow(bool value);

	const bool IsGenShadow() const;

	void SetEnableFog(bool value);

	const bool IsEnableFog() const;

	void SetEnableLightMap(bool value);

	const bool IsEnableLightMap() const;

	void SetLightMapUsetFirstUV(bool value);

	const bool IsLightMapUseFirstUV() const;

	void SetEnableVertexLight(bool value);

	const bool IsEnableVertexLight() const;

	void SetEnableLighting(bool value);

	const bool IsEnableLighting() const;

	void SetAlphaBlend(bool value);

	const bool IsEnalbeAlphaBlend() const;

	void SetAlphaTest(bool value);

	const bool IsEnalbeAlphaTest() const;

protected:


private:
	
	Util::String m_lightingType;
	Util::String m_finalColorModifier;
	Util::String m_alphaTestVariable;	
	bool		 m_bCastShadow;
	bool         m_bGenShadow;
	bool         m_bEnableFog;
	bool         m_bEnableLightMap;
	bool         m_blightMapUseFirstUV;
	bool         m_bVertexLight;
	bool         m_bUseLight;
	bool         m_bAlphaBlend;
	bool         m_bAlphaTest;

	Util::Dictionary<ShadingBuiltInOption, bool> m_shadingOptions;

};

inline void ShadingTemplateSetting::CreateFinalShadingOptions()
{
	m_shadingOptions.Add(LightMap, m_bEnableLightMap);
	m_shadingOptions.Add(VertexLight, m_bVertexLight);
	m_shadingOptions.Add(Light, m_bUseLight);
	m_shadingOptions.Add(Fog, m_bEnableFog);
}

inline bool ShadingTemplateSetting::HasShadingOption(const ShadingTemplateSetting::ShadingBuiltInOption& option) const
{
	IndexT res = m_shadingOptions.FindIndex(option);

	if (res != InvalidIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline void ShadingTemplateSetting::SetLightingType(const Util::String& type)
{
	m_lightingType = type;
}

inline const Util::String& ShadingTemplateSetting::GetLightingType() const
{
	return m_lightingType;
}

inline void ShadingTemplateSetting::SetColorModifier(const Util::String& cm)
{
	m_finalColorModifier = cm;
}

inline const Util::String& ShadingTemplateSetting::GetColorModifier() const
{
	return m_finalColorModifier;
}

inline void ShadingTemplateSetting::SetAlphaTestValue(const Util::String& value)
{
	m_alphaTestVariable = value;
}

inline const Util::String& ShadingTemplateSetting::GetAlphaTestValue() const
{
	return m_alphaTestVariable;
}

inline void ShadingTemplateSetting::SetCastShadow(bool value)
{
	m_bCastShadow = value;
}

inline const bool ShadingTemplateSetting::IsCastShadow() const
{
	return m_bCastShadow;
}

inline void ShadingTemplateSetting::SetGenShadow(bool value)
{
	m_bGenShadow = value;
}

inline const bool ShadingTemplateSetting::IsGenShadow() const
{
	return m_bGenShadow;
}

inline void ShadingTemplateSetting::SetEnableFog(bool value)
{
	m_bEnableFog = value;
}

inline const bool ShadingTemplateSetting::IsEnableFog() const
{
	return m_bEnableFog;
}

inline void ShadingTemplateSetting::SetEnableLightMap(bool value)
{
	m_bEnableLightMap = value;
}

inline const bool ShadingTemplateSetting::IsEnableLightMap() const
{
	return m_bEnableLightMap;
}

inline void ShadingTemplateSetting::SetLightMapUsetFirstUV(bool value)
{
	m_blightMapUseFirstUV = value;
}

inline const bool ShadingTemplateSetting::IsLightMapUseFirstUV() const
{
	return m_blightMapUseFirstUV;
}

inline void ShadingTemplateSetting::SetEnableVertexLight(bool value)
{
	m_bVertexLight = value;
}

inline const bool ShadingTemplateSetting::IsEnableVertexLight() const
{
	return m_bVertexLight;
}

inline void ShadingTemplateSetting::SetEnableLighting(bool value)
{
	m_bUseLight = value;
}

inline const bool ShadingTemplateSetting::IsEnableLighting() const
{
	return m_bUseLight;
}

inline void ShadingTemplateSetting::SetAlphaBlend(bool value)
{
	m_bAlphaBlend = value;
}

inline const bool ShadingTemplateSetting::IsEnalbeAlphaBlend() const
{
	return m_bAlphaBlend;
}

inline void ShadingTemplateSetting::SetAlphaTest(bool value)
{
	m_bAlphaTest = value;
}

inline const bool ShadingTemplateSetting::IsEnalbeAlphaTest() const
{
	return m_bAlphaTest;
}

}



#endif