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
#include "MojoShaderTool.h"
#include "mojoshader/mojoshader.h"

#include "ShaderTemplate/ShaderJoint.h"
#include "exception/exceptionbase.h"

namespace ShaderProgramCompiler
{
	__ImplementClass(MojoShaderTool,'MJTL',Core::RefCounted);
	__ImplementImageSingleton(MojoShaderTool);


static MojoShaderTool::InputModifier ConvertMojoInputModifier(const MOJOSHADER_astInputModifier modifier)
{
	MojoShaderTool::InputModifier im;
	switch (modifier)
	{
	case MOJOSHADER_AST_INPUTMOD_NONE:
		im = MojoShaderTool::INPUTMOD_NONE;
		break;

	case MOJOSHADER_AST_INPUTMOD_IN:
		im = MojoShaderTool::INPUTMOD_IN;
		break;

	case MOJOSHADER_AST_INPUTMOD_OUT:
		im = MojoShaderTool::INPUTMOD_OUT;
		break;

	case MOJOSHADER_AST_INPUTMOD_INOUT:
		im = MojoShaderTool::INPUTMOD_INOUT;
		break;

	case MOJOSHADER_AST_INPUTMOD_UNIFORM:
		im = MojoShaderTool::INPUTMOD_UNIFORM;
		break;
	}
	return im;
}

MojoShaderTool::MojoShaderTool()
{
	__ConstructImageSingleton;
}

MojoShaderTool::~MojoShaderTool()
{
	__DestructImageSingleton;
}

void MojoShaderTool::MojoJointParse(ShaderJoint* pJoint, const Util::String& source, const Util::String& customEntry)
{

	static MOJOSHADER_preprocessorDefine defined[7];
	defined[0].identifier = "fixed";
	defined[0].definition = "half";

	defined[1].identifier = "fixed2";
	defined[1].definition = "half2";

	defined[2].identifier = "fixed3";
	defined[2].definition = "half3";

	defined[3].identifier = "fixed4";
	defined[3].definition = "half4";

	defined[4].identifier = "fixed4x4";
	defined[4].definition = "half4x4";

	defined[5].identifier = "fixed3x3";
	defined[5].definition = "half3x3";

	defined[6].identifier = "fixed2x2";
	defined[6].definition = "half2x2";

	const MOJOSHADER_astData* pMojoData = MOJOSHADER_parseAst(MOJOSHADER_SRC_PROFILE_HLSL_PS_3_0, "", source.AsCharPtr(),
		                                  source.Length(), defined, 7, NULL, NULL, NULL, NULL, NULL);

	IndexT nError = pMojoData->error_count;
	if (nError > 0)
	{
		for (IndexT i = 0; i < nError; ++i)
		{

			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("Mojo Parse Error : %s, %d \n.", pMojoData->errors[i].error, pMojoData->errors[i].error_position),
				GET_FUNCTION_NAME()
				);
		}

		return;
	}


	//inputInfo contains the parmaters defined in the Shading Segment function(from left to right)
	Util::Array<MojoFuncInfo> inputInfo;

	bool bFunc = _MojoParseFunctionParam(pMojoData, customEntry, inputInfo);
	
	if (!bFunc)
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("The entry defined in the 'Compiler' does not match %s\n.", customEntry.AsCharPtr()),
			GET_FUNCTION_NAME()
			);
	}

	const MojoFuncInfo& input = inputInfo[0];

	//Validate Input paramter
	if (input.modifier != INPUTMOD_NONE && input.modifier != INPUTMOD_IN)
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Shading Segment must define 'in' modifier or left none!\n.", ""),
			GET_FUNCTION_NAME()
			);

		return;
	}

	pJoint->SetFunctionIOName(input.name, ShaderJoint::Input);
	pJoint->SetFunctionIOType(input.type, ShaderJoint::Input);

	Util::Array<MojoFuncInfo> inputParamInfo;
	_MojoParseParamType(pMojoData, input.type, inputParamInfo);

	for (IndexT i = 0; i < inputParamInfo.Size(); ++i)
	{
		ShaderJoint::FunctionParameter fp;
		fp.userTypeName = inputParamInfo[i].type;
		fp.identifier   = inputParamInfo[i].name;
		fp.semantic     = inputParamInfo[i].semantic;

		pJoint->AddFunctionParam(fp, ShaderJoint::Input);

	}

	const MojoFuncInfo& out = inputInfo[1];

	if (out.modifier != INPUTMOD_INOUT)
	{
		
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Shading Segment must define 'inout' before seconde paramter!\n.", ""),
			GET_FUNCTION_NAME()
			);
		
		return;
	}
	
	pJoint->SetFunctionIOName(out.name, ShaderJoint::OutPut);
	pJoint->SetFunctionIOType(out.type, ShaderJoint::OutPut);

	Util::Array<MojoFuncInfo> outputParamInfo;
	_MojoParseParamType(pMojoData, out.type, outputParamInfo);

	for (IndexT i = 0; i < outputParamInfo.Size(); ++i)
	{
		ShaderJoint::FunctionParameter fp;
		fp.userTypeName = outputParamInfo[i].type;
		fp.identifier   = outputParamInfo[i].name;
		fp.semantic     = outputParamInfo[i].semantic;

		pJoint->AddFunctionParam(fp, ShaderJoint::OutPut);
	}

	MOJOSHADER_freeAstData(pMojoData);
}
bool MojoShaderTool::_MojoParseFunctionParam(const MOJOSHADER_astData* pMojoData, const Util::String& customEntry, Util::Array<MojoFuncInfo>& funcInfos)
{
	const MOJOSHADER_astCompilationUnit *ast           = NULL;
	const MOJOSHADER_astCompilationUnitFunction *astfn = NULL;

	for (ast = &pMojoData->ast->compunit; ast != NULL; ast = ast->next)
	{
		if (ast->ast.type == MOJOSHADER_AST_COMPUNIT_FUNCTION)
		{
			astfn = (MOJOSHADER_astCompilationUnitFunction *) ast;

			const MOJOSHADER_astFunctionSignature* pFS = astfn->declaration;

			if (pFS->identifier == customEntry)
			{
				const MOJOSHADER_astFunctionParameters* pFP = pFS->params;

				while (pFP != NULL)
				{
					MojoFuncInfo info;
					info.type = pFP->datatype->user.name;
					info.name = pFP->identifier;
					info.modifier = ConvertMojoInputModifier(pFP->input_modifier);
					funcInfos.Append(info);

					pFP = pFP->next;
				}

				return true;
			}
			
		}
	}

	return false;
}

void MojoShaderTool::_MojoParseParamType(const MOJOSHADER_astData* pMojoData, const Util::String& typeName, Util::Array<MojoFuncInfo>& funcInfos)
{

	const MOJOSHADER_astCompilationUnit *ast           = NULL;
	const MOJOSHADER_astCompilationUnitStruct *astst   = NULL;

	for (ast = &pMojoData->ast->compunit; ast != NULL; ast = ast->next)
	{
		if (ast->ast.type == MOJOSHADER_AST_COMPUNIT_STRUCT)
		{
			astst = (MOJOSHADER_astCompilationUnitStruct *) ast;

			if (astst->struct_info->name == typeName)
			{
				const MOJOSHADER_astStructMembers* pSM = astst->struct_info->members;

				while (pSM != NULL)
				{
					MojoFuncInfo info;
					info.type     = pSM->datatype->user.name;
					info.name     = pSM->details->identifier;
					info.semantic = pSM->semantic;
					funcInfos.Append(info);

					pSM = pSM->next;
				}

				return;
			}
			
		}

	}
}

bool MojoShaderTool::MojoPreprocess(Util::String& source)
{
	const MOJOSHADER_preprocessData* pData = MOJOSHADER_preprocess("", source.AsCharPtr(), source.Length(), NULL, 0, NULL, NULL, NULL, NULL, NULL);

	SizeT nCount = pData->error_count;

	if (nCount > 0)
	{
		Util::String sError;
		for (IndexT i = 0; i < nCount; ++i)
		{
			sError += pData->errors[i].error;
			sError += "\n";
		}

		MOJOSHADER_freePreprocessData(pData);

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Preprocess shader Error: %s \n", sError.AsCharPtr()),
			GET_FUNCTION_NAME()
			);

		return false;
	}

	source = pData->output;
	return true;
}

}