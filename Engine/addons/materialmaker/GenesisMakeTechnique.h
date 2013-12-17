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
#ifndef GENESISMAKETECHNIQUE_H_
#define GENESISMAKETECHNIQUE_H_

#include "GenesisMakePass.h"
namespace GenesisMaterialMaker
{
	typedef Util::Array<GenesisMakePass> GenesisPassList;
	class GenesisMakeTechnique
	{
	public:
		GenesisMakeTechnique();
		virtual ~GenesisMakeTechnique();
		void AddPass(const GenesisMakePass& pass);
		void AssignSamplerStates(const GenesisTextureSamplerStateList& sslist);
		RenderBase::GPUProgramHandle CreateGPUProgram();
		void CreateTech(GPtr<Graphic::MaterialTech>& tech);
		void SetName(const Util::String& name);
		const Util::String& GetName() const;
		void SetIsMatTemplate(Util::String bTemplate);
		const bool IsMatTemplate() const ;
	private:
		GenesisPassList m_matPassList;
		Util::String m_techName;
		bool m_bMatTemplate;
	};

	inline void GenesisMakeTechnique::AddPass(const GenesisMakePass& pass)
	{
		m_matPassList.Append(pass);
	}

	inline void GenesisMakeTechnique::SetName(const Util::String& name)
	{
		m_techName = name;
	}
	
	inline const Util::String& GenesisMakeTechnique::GetName() const
	{
		return m_techName;
	}

	inline void GenesisMakeTechnique::SetIsMatTemplate(Util::String bTemplate)
	{
		bTemplate.ToUpper();
		if (bTemplate == "TRUE")
		{
			m_bMatTemplate = true;
		}
		else
		{
			m_bMatTemplate = false;
		}
	}

	inline const bool GenesisMakeTechnique::IsMatTemplate() const
	{
		return m_bMatTemplate;
	}
}
#endif //GENESISMAKETECHNIQUE_H_