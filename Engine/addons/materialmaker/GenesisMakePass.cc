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
#include "GenesisMakePass.h"
#include "graphicsystem/GraphicSystem.h"
#include "rendersystem/gles/GPUProgramGLES.h"
namespace GenesisMaterialMaker
{
	GenesisMakePass::GenesisMakePass()
		: m_bGles(false)
	{
		//empty
	}

	GenesisMakePass::~GenesisMakePass()
	{
		m_RenderObjectState = 0;
	}

	RenderBase::GPUProgramHandle GenesisMakePass::CreateGPUProgram()
	{
		GPtr<RenderBase::GPUProgram> program = RenderBase::GPUProgram::Create();

		for (SizeT i = 0; i < m_ShaderProgramList.Size(); ++i)
		{
			if (m_ShaderProgramList[i].GetDeviceType() == "D3D9")
			{
				if (m_ShaderProgramList[i].GetShaderType() == "vs")
				{
					program->SetVertexCode(m_ShaderProgramList[i].GetShaderCode());
				}
				else if (m_ShaderProgramList[i].GetShaderType() == "ps")
				{
					program->SetPixelCode(m_ShaderProgramList[i].GetShaderCode());
				}
			}
		}
		return Graphic::GraphicSystem::Instance()->CreateShaderProgram(program);
	}

	void GenesisMakePass::CreatePass(GPtr<Graphic::MaterialTech>& tech)
	{
		GPtr<RenderBase::GPUProgram> program = RenderBase::GPUProgram::Create();
		GPtr<Graphic::MaterialPass> pass = Graphic::MaterialPass::Create();
		for (SizeT i = 0; i < m_ShaderProgramList.Size(); ++i)
		{
			if (m_ShaderProgramList[i].GetDeviceType() == "D3D9")
			{
				if (m_ShaderProgramList[i].GetShaderType() == "vs")
				{
					program->SetVertexCode(m_ShaderProgramList[i].GetShaderCode());
					pass->AddShaderParamBinding(Graphic::SCT_VS,m_ShaderProgramList[i].GetParamList());
				}
				else if (m_ShaderProgramList[i].GetShaderType() == "ps")
				{
					program->SetPixelCode(m_ShaderProgramList[i].GetShaderCode());
					pass->AddShaderParamBinding(Graphic::SCT_PS,m_ShaderProgramList[i].GetParamList());
				}
			}
			else if (m_ShaderProgramList[i].GetDeviceType() == "OpenGL")
			{
				if (m_ShaderProgramList[i].GetShaderType() == "vs")
				{
					program->SetVertexCode(m_ShaderProgramList[i].GetShaderCode());
					pass->AddShaderParamBinding(Graphic::SCT_VS,m_ShaderProgramList[i].GetParamList());
				}
				else if (m_ShaderProgramList[i].GetShaderType() == "ps")
				{
					program->SetPixelCode(m_ShaderProgramList[i].GetShaderCode());
					pass->AddShaderParamBinding(Graphic::SCT_PS,m_ShaderProgramList[i].GetParamList());
				}
			}
			else if (m_ShaderProgramList[i].GetDeviceType() == "OpenGLES")
			{
				Util::String shaderCode;
				Util::String vsCode;
				Util::String psCode;
				Util::String s_vsStart("VertexBegin");
				Util::String s_vsEnd("VertexEnd");
				Util::String s_psStart("PixelBegin");
				Util::String s_psEnd("PixelEnd");
				if (m_ShaderProgramList[i].GetShaderType() == "vs")
				{
					shaderCode           = m_ShaderProgramList[i].GetShaderCode();
					IndexT vertexStart   = shaderCode.FindStringIndex(s_vsStart);
					IndexT vertexEnd     = shaderCode.FindStringIndex(s_vsEnd);
					IndexT fragmentStart = shaderCode.FindStringIndex(s_psStart);
					IndexT fragmentEnd   = shaderCode.FindStringIndex(s_psEnd);
					if (vertexStart != InvalidIndex && vertexEnd != InvalidIndex)
					{
						vsCode = shaderCode.ExtractRange(vertexStart + s_vsStart.Length(), vertexEnd - vertexStart - s_vsStart.Length());
						program->SetVertexCode(vsCode);
					}
					if (fragmentStart != InvalidIndex && fragmentEnd != InvalidIndex)
					{
						psCode = shaderCode.ExtractRange(fragmentStart + s_psStart.Length(), fragmentEnd - fragmentStart - s_psStart.Length());
						program->SetPixelCode(psCode);
					}

					m_bGles = true;
				}
			}

		}
		pass->SetRenderStateDesc(m_RenderObjectState);
		pass->SetName(m_name);

		RenderBase::GPUProgramHandle gpuHandle = Graphic::GraphicSystem::Instance()->CreateShaderProgram(program);
		pass->SetGPUProgramHandle(gpuHandle);

		if (m_bGles)
		{
			_InitOpenGLes(gpuHandle, pass);
		}


		tech->AddPass(pass);
	}

	void GenesisMakePass::_InitOpenGLes(RenderBase::GPUProgramHandle& gpuHandle, const GPtr<Graphic::MaterialPass>& pass)
	{
		using namespace RenderBase;
		using namespace GLES;
		using namespace Graphic;

		GPtr<RenderCommandType> rcType( (RenderCommandType*)gpuHandle.AsObject() );
		GPtr<GPUProgram> program = rcType.downcast<GPUProgram>();

		GPtr<GPUProgramGLES> glesProgram = program.downcast<GPUProgramGLES>();
		n_assert(glesProgram.isvalid());

		Graphic::ShaderParamList shaderParamsList;

		const Util::Array<Uniform>& activeUniforms = glesProgram->GetActiveUniforms();

		for (IndexT iUniform = 0; iUniform < activeUniforms.Size(); ++iUniform)
		{
			const Uniform& uni = activeUniforms[iUniform];

			Util::String paramName;

			for (IndexT iParam = 0; iParam < uni.size; ++iParam)
			{
				ShaderParam shaderParam;

				if (uni.size > 1)
				{
					if (!iParam)
					{
						paramName = uni.name.ExtractRange(0, uni.name.Length() - 3);
					}
					
					Util::String sNum;
					sNum.SetInt(iParam);
					Util::String name;
					name = paramName + sNum;
					shaderParam.SetName(name);
					shaderParam.SetRegister(uni.location + iParam);

				}
				else
				{
					shaderParam.SetName(uni.name);
					shaderParam.SetRegister(uni.location);
				}			

				switch (uni.type)
				{
				case GL_FLOAT:
				case GL_INT:
					shaderParam.SetParamType(eShaderParamFloat);
					break;

				case GL_FLOAT_VEC2:
				case GL_FLOAT_VEC3:
				case GL_FLOAT_VEC4:
				case GL_INT_VEC2:
				case GL_INT_VEC3:
				case GL_INT_VEC4:
					shaderParam.SetParamType(eShaderParamVector);
					break;

				case GL_FLOAT_MAT2:
				case GL_FLOAT_MAT3:
				case GL_FLOAT_MAT4:
					shaderParam.SetParamType(eShaderParamMatrix);
					break;

				case GL_SAMPLER_2D:
					shaderParam.SetParamType(eShaderParamTexture2D);
					break;

				case GL_SAMPLER_CUBE:
					shaderParam.SetParamType(eShaderParamTextureCUBE);
					break;
				}

				m_ShaderProgramList[0].AddParam(shaderParam);
			}
			
		}
		
		pass->AddShaderParamBinding(Graphic::SCT_VS, m_ShaderProgramList[0].GetParamList());
	}

	int GenesisMakePass::_FindRegister(const Util::String& name)
	{
		for (SizeT i = 0; i < m_ShaderProgramList.Size(); ++i)
		{
			const Graphic::ShaderParamList& spl = m_ShaderProgramList[i].GetParamList();
			for(SizeT spIndex = 0; spIndex < spl.Size(); ++spIndex )
			if(spl[spIndex].GetName() == name)
			{
				return spl[spIndex].GetRegister();
			}
		}
		return -1;
	}

	void GenesisMakePass::AssignTextureSamplerStates(const GenesisTextureSamplerStateList& sslist)
	{
		if (!m_RenderObjectState.isvalid())
			return;

		RenderBase::DeviceSamplerState rss = m_RenderObjectState->GetSamplerState();
		for (SizeT i = 0; i < sslist.Size(); ++i)
		{
			int reg = _FindRegister(sslist[i].m_name);
			if (reg != -1)
			{
				rss.m_textureIndexEnable[reg] = true;
				rss.m_addressU[reg] = sslist[i].m_tam;
				rss.m_addressV[reg] = sslist[i].m_tam;
				rss.m_addressW[reg] = sslist[i].m_tam;
				rss.m_Filter[reg] = sslist[i].m_tfo;
				rss.m_textureType[reg] = sslist[i].m_textureType;
			}
		}
		m_RenderObjectState->SetSamplerState(rss);
	}
}