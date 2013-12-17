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
#include "ShaderJoint.h"
#include "shadercompiler/Utility/ShaderCompilerUtil.h"
#include "shadercompiler/ShaderCompilerSetting.h"
#include "shadercompiler/Compilers/MojoShaderTool.h"

namespace ShaderProgramCompiler
{


ShaderJoint::ShaderJoint()
{
	
}

ShaderJoint::~ShaderJoint()
{

}

void ShaderJoint::Generate(CommonShaderSetting* pCommon, ShadingTemplateSetting* pSegment, const Util::String& renderState, const Util::String& source)
{

	m_sJointedSource += source;

	pSegment->CreateFinalShadingOptions();

	IndexT firstStructIndex = m_sJointedSource.FindStringIndex("struct",0);

	Util::String templateOutPutStr = "\n struct TEMPLATE_OUT\n ";
	templateOutPutStr += "{\n";
	templateOutPutStr += "\tfloat3 Emission;\n";
	templateOutPutStr += "\tfloat4 Diffuse;\n";
	templateOutPutStr += "\tfloat3 Normal;\n";
	templateOutPutStr += "\tfloat  Alpha;\n";
	templateOutPutStr += "\tfloat4 Specular;\n";
	templateOutPutStr += "\tfloat  Shininess;\n";

	if (pSegment->IsEnableLightMap())
	{
		templateOutPutStr += "\tfloat2 LightmapUV;\n";
	}

	if (pSegment->IsEnableVertexLight())
	{
		templateOutPutStr += "\tfloat3 VertexLightDiffuse;\n";
		templateOutPutStr += "\tfloat3 VertexLightSpecular;\n";
	}

	templateOutPutStr += "};\n";

	if (firstStructIndex == InvalidIndex)
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Shading Segment must define a struct INPUT!\n", ""),
			GET_FUNCTION_NAME()
			);
		return;
	}

	m_sJointedSource = m_sJointedSource.InsertRange(firstStructIndex-1, templateOutPutStr);

	if (pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		Util::String vsOutPutStr = "\n struct VS_OUTPUT\n ";
		vsOutPutStr += "{\n";
		vsOutPutStr += "  float4 Position : POSITION;\n";
		vsOutPutStr += "  float2 Uv     : TEXCOORD0;\n";
		vsOutPutStr += "  float3 Normal : TEXCOORD1;\n";
		vsOutPutStr += "  float4 Tangent   : TEXCOORD2;\n";
		vsOutPutStr += "  float3 ViewDir	  : TEXCOORD3;\n";
		vsOutPutStr += "  float4 ClipSpacePos : TEXCOORD4;\n";
		vsOutPutStr += "  float3 CameraSpacePos : TEXCOORD5;\n";
		vsOutPutStr += "  float4 Color : TEXCOORD6;\n";
		vsOutPutStr += "  float4 ExternUvs : TEXCOORD7;\n";
		vsOutPutStr += "};\n";

		m_sJointedSource = m_sJointedSource.InsertRange(firstStructIndex-1, vsOutPutStr);

	}

	MojoShaderTool::Instance()->MojoJointParse(this, m_sJointedSource, pCommon->GetEntryName(CommonShaderSetting::Template));

	_GenerateForwardPass(pCommon, pSegment);

	_GenerateDepthPass(pCommon, pSegment, renderState);

#if RENDERDEVICE_D3D9
	_GenerateShadowPass(pCommon, pSegment, renderState);
#endif

	

}

void ShaderJoint::_GenerateForwardPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment)
{
	Util::String vsSeg;

	Util::String code = m_sJointedSource;

	if (!pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		_CreateVsOutput(vsSeg);
		vsSeg += "};\n";

		code += vsSeg;
		_CreateVsSegment(pCommon, pSegment, Forward, code);
		code += "  return o;\n";
		code += "}\n";
	}
	

	_CreatePsSegment(pCommon, pSegment, Forward, code);

	code += "float4 diffuse = float4(0.0,0.0,0.0,0.0);\n";
	code += "float4 specular = float4(0.0,0.0,0.0,0.0);\n";

	code += "float2 hPos = IN.ClipSpacePos.xy/IN.ClipSpacePos.w;\n";
	code += "float percentLit = 1.0f;\n";

	if (pSegment->IsCastShadow() && !pSegment->IsEnalbeAlphaBlend())
	{
		code += "float lit = tex2D(g_LightLitMap,getUVfromscreenspace(hPos)).r;\n";
		code += "if ( g_ShadowReceive.x > 0.0f && g_ShadowMapSize.w > 0.0f)\n";
		code += "percentLit = lit;\n";
	}

	Util::String tmpStr = pSegment->GetLightingType();

	if (pSegment->IsEnableLighting())
	{
		if(tmpStr == "default")
		{
			if (pSegment->IsEnableVertexLight())
			{
				code += "float4 color =  float4(o.VertexLightDiffuse, 1.0f) * o.Diffuse +  float4(o.VertexLightSpecular, 1.0f) * o.Specular;\n";
			} 
			else
			{
				code += "LightingBlinnPhong(o.Normal,IN.ViewDir,o.Shininess,diffuse,specular,percentLit);\n";
				code += "float4 color =  diffuse * o.Diffuse + specular * o.Specular;\n";
			}

		}
		else
		{
			if (!pSegment->IsEnableVertexLight())
			{
				code += "float4 color = float4(0,0,0,0);\n";
				code += "color = " + pSegment->GetLightingType() + "( o , IN.ViewDir, percentLit );\n";
			}
			else
			{
				code += "float4 color =  float4(o.VertexLightDiffuse, 1.0f) * o.Diffuse +  float4(o.VertexLightSpecular, 1.0f) * o.Specular;\n";
			}

		}
	}
	else
	{
		code += "LightingBlinnPhong(o.Normal,IN.ViewDir,o.Shininess,diffuse,specular,percentLit);\n";
		code += "float4 color =  diffuse * o.Diffuse + specular * o.Specular;\n";
	}

	// lightmap support
	if (pSegment->IsEnableLightMap())
	{
		// xy for scale, zw for offset
		code += "o.LightmapUV = o.LightmapUV * g_LMTexParam.xy + g_LMTexParam.zw;\n";
		code += "float4 lightmapColor = tex2D(g_Lightmap, o.LightmapUV);\n";
		code += "if (g_UseLM.r > 0.0)\n";
		code += "{\n";
		code += "color.xyz += o.Diffuse.xyz * DecodeLightmap(lightmapColor)*g_UseLM.r*percentLit;\n";
		code += "}\n";
	}

	// add emission
	code += "color.xyz += o.Emission.rgb;\n";

	if (pSegment->IsEnableFog())
	{
		code += "if(g_FogColor.a > 0){\n";
		code += "color = ComputeHeightFog (IN.CameraSpacePos,IN.ViewDir,color);\n";

		code += "}\n";
	}

	code += "color.a = o.Alpha;\n";
	code += "return color;\n";
	code += "}\n";

	_GenerateFinalCode(pCommon, pSegment, Forward, code);
}

void ShaderJoint::_GenerateDepthPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const Util::String& renderState)
{
	Util::String result;
	_ReGenRenderState(pSegment, renderState, Depth, result);

	m_PassRenderState.Add(Depth, result);

	Util::String vsSeg;

	Util::String code = m_sJointedSource;

	if (!pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		_CreateVsOutput(vsSeg);
		vsSeg += "};\n";

		code += vsSeg;
		_CreateVsSegment(pCommon, pSegment, Depth, code);
		code += "  return o;\n";
		code += "}\n";
	}

	_CreatePsSegment(pCommon, pSegment, Depth, code);

	if (pSegment->IsEnalbeAlphaBlend())
	{
		code += "  clip(-1);\n";
	}

	code += "  float4 color = -IN.CameraSpacePos.z / g_CameraParam.y;\n";//g_CameraPos.w
	code += "  color.b = 0.5f;\n";
	code += "  color.a = 1.0f;\n";
	code += "#ifdef GLES \n";
	code += "color = packFloatToVec4i(color.r);\n";
	code += "#endif \n";
	code += "  return color;\n";
	code += "}\n";

	_GenerateFinalCode(pCommon, pSegment, Depth, code);
}

void ShaderJoint::_GenerateShadowPass(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const Util::String& renderState)
{
	Util::String result;
	_ReGenRenderState(pSegment, renderState, Shadow, result);

	m_PassRenderState.Add(Shadow, result);

	Util::String vsSeg;

	Util::String code = m_sJointedSource;

	if (!pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		_CreateVsOutput(vsSeg);
		vsSeg += "};\n";

		code += vsSeg;
		_CreateVsSegment(pCommon, pSegment, Shadow, code);
		code += "  return o;\n";
		code += "}\n";
	}

	_CreatePsSegment(pCommon, pSegment, Shadow, code);

	if (pSegment->IsEnalbeAlphaBlend() || !pSegment->IsGenShadow())
	{
		code += "  clip(-1);\n";
	}

	code += "  float2 color;\n";
	code += "  color.r = (-IN.CameraSpacePos.z - g_CameraParam.x) / (g_CameraParam.y - g_CameraParam.x); \n";//g_CameraPos.w
	//depth bias
	code += "  float bias = g_ShadowMapSize.z * max(abs(ddx(color.r)), abs(ddy(color.r)));";
	code += "  color.r += bias;"; 
	//
	code += "  color.g = color.r*color.r;\n";
	code += "  return float4(color,0.0,1.0);\n";
	code += "}\n";

	_GenerateFinalCode(pCommon, pSegment, Shadow, code);
}

void ShaderJoint::_CreateVsOutput(Util::String& code)
{
	code += "struct VS_OUTPUT {\n";
	code += "  float4 Position : POSITION;\n";
	code += "  float2 Uv     : TEXCOORD0;\n";
	code += "  float3 Normal : TEXCOORD1;\n";
	code += "  float4 Tangent   : TEXCOORD2;\n";
	code += "  float3 ViewDir	  : TEXCOORD3;\n";
	code += "  float4 ClipSpacePos : TEXCOORD4;\n";
	code += "  float3 CameraSpacePos : TEXCOORD5;\n";
	code += "  float4 Color : TEXCOORD6;\n";
	code += "  float4 ExternUvs : TEXCOORD7;\n";
}

void ShaderJoint::_CreateVsSegment(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const ShaderJoint::PassType& type, Util::String& code)
{
	
	code += "VS_OUTPUT vsMain (VS_INPUT v) {\n";
	code += "  VS_OUTPUT o;\n";
	code += "float4 worldpos =  mul( g_Model ,float4(v.vertex,1.0f) );\n"; 
	code += "float4 viewpos = mul( g_View ,worldpos );\n"; 
	code += "o.CameraSpacePos = viewpos.xyz;\n";
	code += "o.Position = mul( g_Proj ,viewpos );\n";
	code += "o.Normal = v.normal;\n";
	code += "o.ViewDir = g_CameraPos.xyz - worldpos.xyz;\n";
	code += "o.Uv = v.texcoord;\n";
	code += "o.ClipSpacePos = o.Position;\n";
	code += "o.Color = v.color;\n";

	if (pSegment->IsEnableLightMap())
	{
		if (pSegment->IsLightMapUseFirstUV())
		{
			code += "o.ExternUvs.xy = v.texcoord.xy;\n";
		} 
		else
		{
			code += "o.ExternUvs.xy = v.texcoord1.xy;\n";
		}
	}

	if (pSegment->IsEnableLighting())
	{
		if (pSegment->IsEnableVertexLight() && type == Forward)
		{
			code += "float4 diffuse = float4(0.0,0.0,0.0,0.0);\n";
			code += "float4 specular = float4(0.0,0.0,0.0,0.0);\n";
			code += "float3 normal = normalize(mul(g_InvTransModel, float4(v.normal, 1.0f)).xyz);\n";
			code += "LightingBlinnPhong(normal, o.ViewDir, 1.0f, diffuse, specular, 1.0f);";
			code += "o.Tangent.xyz = diffuse.xyz;\n";
			code += "o.Normal.xyz = specular.xyz;\n";
		} 
		else
		{
			code += "o.Tangent = v.tangent;\n";
		}
	} 
	else
	{
		code += "o.Tangent = v.tangent;\n";
	}
}

void ShaderJoint::_CreatePsSegment(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const ShaderJoint::PassType& type, Util::String& code)
{
	if (pSegment->IsEnalbeAlphaTest())
	{
		code += "float " + pSegment->GetAlphaTestValue() + ";\n";
	}

	SizeT nCount = m_CustomFunc.funcInputParams.Size();

	for (IndexT i = 0; i < nCount; ++i)
	{
		if (ShaderUtil::HaveStringAtEnd(m_CustomFunc.funcInputParams[i].identifier, "_UV"))
		{
			Util::String texOffestScale;
			texOffestScale.Clear();
			texOffestScale.Format("float4 %s_OffsetScale;\n", m_CustomFunc.funcInputParams[i].identifier.AsCharPtr());
			code += texOffestScale;
		}
	}

	code += "float4 psMain (VS_OUTPUT IN) : COLOR {\n";

	code += "  INPUT templateParam;\n";

	code += "  " + m_CustomFunc.paramOutputType + " o;\n";

	{
		Util::String tmp;
		for (IndexT i = 0; i < nCount; ++i)
		{
			const FunctionParameter& fp    = m_CustomFunc.funcInputParams[i];
			const Util::String& identifier = fp.identifier;

			if (ShaderUtil::HaveStringAtEnd(identifier, "_UV"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.Uv * %s_OffsetScale.zw + %s_OffsetScale.xy;\n", identifier.AsCharPtr(),
					identifier.AsCharPtr(), identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_UV2"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.ExternUvs.xy;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_UV3"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.ExternUvs.zw;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_Normal"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.Normal;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_Tangent"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.Tangent;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_Color"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.Color;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_CameraSpacePos"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.CameraSpacePos;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_ClipSpacePos"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.ClipSpacePos;\n", identifier.AsCharPtr());
				code += tmp;
			}
			else if (ShaderUtil::HaveStringAtEnd(identifier, "_ViewDir"))
			{
				tmp.Clear();
				tmp.Format("templateParam.%s = IN.ViewDir;\n", identifier.AsCharPtr());
				code += tmp;
			}
		}

		code += "o.Emission.rgb = float3(0.0f,0.0f,0.0f);";

		if (pSegment->IsEnableVertexLight())
		{
			code += "o.VertexLightDiffuse  = IN.Tangent.xyz;\n";
			code += "o.VertexLightSpecular = IN.Normal.xyz;\n";
		}

		code += pCommon->GetEntryName(CommonShaderSetting::Template) + "(templateParam, o);\n";

		if (pSegment->IsEnableLightMap())
		{
			code += "o.LightmapUV = IN.ExternUvs.xy;\n";
		}
	}

	if (pSegment->IsEnalbeAlphaTest())
	{
		code += "  clip (o.Alpha - " + pSegment->GetAlphaTestValue() + ");\n";
		code += "  o.Alpha = 1.0f;\n";
	}
}

void ShaderJoint::_GenerateFinalCode(const CommonShaderSetting* pCommon, const ShadingTemplateSetting* pSegment, const ShaderJoint::PassType& passType, Util::String& code)
{
	Util::String vsCode;

	if (!pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		vsCode += "struct VS_INPUT\n";
		vsCode += "{\n";
		vsCode += "\tfloat3 vertex : POSITION;\n";
		vsCode += "\tfloat3 normal : NORMAL;\n";
		vsCode += "\tfloat2 texcoord : TEXCOORD0;\n";
		// support lightmap
		if (pSegment->IsEnableLightMap() && !pSegment->IsLightMapUseFirstUV())
		{
			vsCode += "\tfloat2 texcoord1 : TEXCOORD1;\n";
		}
		vsCode += "\tfloat4 tangent :  TANGENT;\n";
		vsCode += "\tfloat4 color :  COLOR0;\n";
		vsCode += "};\n";
	}

	code = vsCode + code;

	Util::String vertEntry, pixelEntry;
	if (!pCommon->HasEntry(CommonShaderSetting::Vertex))
	{
		vertEntry = "vsMain";
	}

	pixelEntry = "psMain";

	ShaderJoint::PassInfo info;
	info.vertEntry  = vertEntry;
	info.pixelEntry = pixelEntry;
	info.source     = code;

	m_PassInfos.Add(passType, info);
}

void ShaderJoint::_ReGenRenderState(const ShadingTemplateSetting* pSegment, const Util::String& renderState, const ShaderJoint::PassType& type, Util::String& result)
{
	Util::String passTypeName;
	Util::String passRenderState;
	Util::String matType = "true";

	if (type == ShaderJoint::Depth)
	{
		passTypeName = "DepthPass";
		passRenderState += "cullMode \"Back\"\n";
		passRenderState += "ZTest On\n";
		passRenderState += "ZWrite On\n";
		passRenderState += "blendMode Off\n";
		passRenderState += "alphatest Off\n";
	}
	else if (type == ShaderJoint::Shadow)
	{
		Util::String cullMode;

		IndexT pos = renderState.FindStringIndex("cullMode");

		if (pos == InvalidIndex)
		{
			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("No cullmode defined in the RenderState!\n.", ""),
				GET_FUNCTION_NAME()
				);
		}

		IndexT nCR = renderState.FindCharIndex('\n', pos);

		cullMode = renderState.ExtractRange(pos, nCR - pos + 1);
		
		passTypeName = "ShadowMap";
		passRenderState += cullMode;
		passRenderState += "\n";

		if (pSegment->IsGenShadow())
		{
			passRenderState += "ZTest On\n";
			passRenderState += "ZWrite On\n";
			passRenderState += "ColorMask \"RGBA\"\n";
		}
		else
		{
			passRenderState += "ZTest Off\n";
			passRenderState += "ZWrite Off\n";
			passRenderState += "ColorMask \"A\"\n";
		}

		passRenderState += "blendMode Off\n";
		passRenderState += "alphatest Off\n";
	}

	result += "}\n";
	result += "MaterialType \"" + matType + "\"\n";
	result += "Pass\t \"" + passTypeName +"\"\t {\n";
	result += "RenderState\n{\n";
	result += passRenderState;
	result += "\t}\n";
}

}