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
#ifndef _SHADERJOINT_H_
#define _SHADERJOINT_H_

#include "core/refcounted.h"
#include "util/string.h"
#include "util/array.h"

namespace ShaderProgramCompiler
{
	class CommonShaderSetting;
	class ShadingTemplateSetting;

	class ShaderJoint
{
public:

	ShaderJoint();

	~ShaderJoint();
	
public:

	enum ParamType
	{
		Input = 0,
		OutPut,
	};

	enum PassType
	{
		Forward = 0,
		Depth,
		Shadow,

	};

	struct PassInfo
	{
		Util::String vertEntry;
		Util::String pixelEntry;
		Util::String source;
	};

	struct FunctionParameter
	{
		Util::String   userTypeName;
		Util::String   identifier;
		Util::String   semantic;
	};

	struct CustomFuncDesc
	{
		Util::Array<FunctionParameter>   funcInputParams;
		Util::Array<FunctionParameter>   funcOutputParams;

		Util::String paramInputType;
		Util::String paramInputName;
		
		Util::String paramOutputType;
		Util::String paramOutputName;
	};

public:

	void AddFunctionParam(const FunctionParameter& param, const ParamType& type );

	void SetFunctionIOType(const Util::String& name, const ParamType& type);

	void SetFunctionIOName(const Util::String& name, const ParamType& type);

	void Generate(CommonShaderSetting* pCommon, ShadingTemplateSetting* pSegment, const Util::String& renderState, const Util::String& source);

	const Util::Dictionary< PassType, PassInfo >& GetPassInfo() const;

	const Util::Dictionary< PassType, Util::String >& GetPassRenderState() const;

protected:

	void _GenerateForwardPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment);

	void _GenerateDepthPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const Util::String& renderState);

	void _GenerateShadowPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const Util::String& renderState);

	void _GenerateGBufferPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment);

	void _GenerateDefferdLightingPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment);

	void _GenerateFinalCode(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const PassType& passType, Util::String& code);

	void _CreateVsOutput(Util::String& code);

	void _CreateVsSegment(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const PassType& type, Util::String& code);

	void _CreatePsSegment(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const PassType& type, Util::String& code);

	void _ReGenRenderState(const ShadingTemplateSetting* pSegment, const Util::String& renderState, const PassType& type, Util::String& result);

private:

	CustomFuncDesc         m_CustomFunc;
	
	Util::String           m_sJointedSource;

	Util::Dictionary< PassType, PassInfo >     m_PassInfos;
	Util::Dictionary< PassType, Util::String > m_PassRenderState;

};

inline const Util::Dictionary< ShaderJoint::PassType, ShaderJoint::PassInfo >& ShaderJoint::GetPassInfo() const
{
	return m_PassInfos;
}

inline const Util::Dictionary< ShaderJoint::PassType, Util::String >& ShaderJoint::GetPassRenderState() const
{
	return m_PassRenderState;
}

	
inline void ShaderJoint::AddFunctionParam(const ShaderJoint::FunctionParameter& param, const ShaderJoint::ParamType& type )
{
	if (type == ShaderJoint::Input)
	{
		m_CustomFunc.funcInputParams.Append(param);
	}
	else if (type == ShaderJoint::OutPut)
	{
		m_CustomFunc.funcOutputParams.Append(param);
	}
	
}

inline void ShaderJoint::SetFunctionIOType(const Util::String& name, const ShaderJoint::ParamType& type)
{
	if (type == ShaderJoint::Input)
	{
		m_CustomFunc.paramInputType = name;
	}
	else if (type == ShaderJoint::OutPut)
	{
		m_CustomFunc.paramOutputType = name;
	}
}

inline void ShaderJoint::SetFunctionIOName(const Util::String& name, const ShaderJoint::ParamType& type)
{
	if (type == ShaderJoint::Input)
	{
		m_CustomFunc.paramInputName = name;
	}
	else if (type == ShaderJoint::OutPut)
	{
		m_CustomFunc.paramOutputName = name;
	}
}

}




#endif