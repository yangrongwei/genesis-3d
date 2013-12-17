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
#pragma once
#ifndef GENESISMAKEPASS_H_
#define GENESISMAKEPASS_H_

#include "GenesisMakeGPUProgram.h"
#include "graphicsystem/Material/Material.h"
namespace GenesisMaterialMaker
{
	struct GenesisTextureSamplerState
	{
		Util::String m_name;
		Util::String m_textureType;
		RenderBase::TextureAddressMode m_tam;
		RenderBase::TextureFilter m_tfo;
	};

	typedef Util::Array<GenesisTextureSamplerState> GenesisTextureSamplerStateList;
	typedef Util::Array<GenesisMakeGPUProgram> GenesisGPUProgramList;

	class GenesisMakePass
	{
	public:
		GenesisMakePass();
		virtual ~GenesisMakePass();

		void SetName(const Util::String& name);
		void AddShaderProgram(const GenesisMakeGPUProgram& program);
		void SetRenderStateDesc(const GPtr<RenderBase::RenderStateDesc>& rso);
		void AssignTextureSamplerStates(const GenesisTextureSamplerStateList& sslist);
		int _FindRegister(const Util::String& name);
		RenderBase::GPUProgramHandle CreateGPUProgram();
		void CreatePass(GPtr<Graphic::MaterialTech>& tech);

	protected:
		void _InitOpenGLes(RenderBase::GPUProgramHandle& gpuHandle, const GPtr<Graphic::MaterialPass>& pass);
	private:
		Util::String m_name;
		GenesisGPUProgramList m_ShaderProgramList;
		GPtr<RenderBase::RenderStateDesc> m_RenderObjectState;

		bool m_bGles;
	};

	inline void GenesisMakePass::SetName(const Util::String& name)
	{
		m_name = name;
	}

	inline void GenesisMakePass::AddShaderProgram(const GenesisMakeGPUProgram& program)
	{
		m_ShaderProgramList.Append(program);
	}

	inline void GenesisMakePass::SetRenderStateDesc(const GPtr<RenderBase::RenderStateDesc>& rsd)
	{
		m_RenderObjectState = rsd;
	}

}
#endif //GENESISMAKEPASS_H_