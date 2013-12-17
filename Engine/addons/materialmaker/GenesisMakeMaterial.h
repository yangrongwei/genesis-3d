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
#ifndef GENESISMAKEMATERIAL_H_
#define GENESISMAKEMATERIAL_H_
#include "GenesisMakeTechnique.h"
#include "graphicsystem/Material/MaterialParam.h"
 namespace GenesisMaterialMaker
 {
	 class GenesisMakeMaterial
	 {
	 public:
		 GenesisMakeMaterial();
		 virtual ~GenesisMakeMaterial();

		 void AddTechnique(const GenesisMakeTechnique& tech);
		 void AddMatParam(Graphic::MaterialParam* matParam);
		 void SetRenderQueue(Graphic::RenderQueue rqt);
		 const Util::String GetMatParamValueByName(const Util::String& name)const;
		 RenderBase::GPUProgramHandle CreateGPUProgram();
		 void MakeMaterial(GPtr<Graphic::Material>& mat);
		 void AssignDefaultMatParamBindings();
		 void _SetTextureSamplers();
		 void AddTextureSampler(const Util::String& name, RenderBase::TextureAddressMode tam = RenderBase::eTAMWRAP, RenderBase::TextureFilter tfo = RenderBase::eTFPOINT);
	 private:
		 Util::Array<GenesisMakeTechnique> m_TechniqueList;
		 Graphic::MaterialParamList m_matParamList;
		 Graphic::RenderQueue m_renderQueue;
		 GenesisTextureSamplerStateList m_TexSamplerStateList;
		 Util::Dictionary<Util::String, Graphic::MaterialParameterType> m_SampleTypeMap;
	 };

	 inline void GenesisMakeMaterial::AddTechnique(const GenesisMakeTechnique& tech)
	 {
		 m_TechniqueList.Append(tech);
	 }

	 inline void GenesisMakeMaterial::AddMatParam(Graphic::MaterialParam* mat)
	 {
		 m_matParamList.Append(mat);

		 if (mat->GetType() >= Graphic::eMaterialParamTexture1D && mat->GetType() <= Graphic::eMaterialParamTextureCUBE)
		 {
			 m_SampleTypeMap.Add(mat->GetName(), mat->GetType());
		 }
	 }

	 inline void GenesisMakeMaterial::SetRenderQueue(Graphic::RenderQueue rqt)
	 {
		 m_renderQueue = rqt;
	 }

	 inline void GenesisMakeMaterial::AddTextureSampler(const Util::String& name, RenderBase::TextureAddressMode tam /* = eTAMWRAP */, RenderBase::TextureFilter tfo /* = eTFPOINT */)
	 {
		 GenesisTextureSamplerState tss;
		 tss.m_name = name;
		 tss.m_tam = tam;
		 tss.m_tfo = tfo;

		 IndexT found = m_SampleTypeMap.FindIndex(name);
		 if (found != InvalidIndex)
		 {
			 Graphic::MaterialParameterType matType;
			 matType = m_SampleTypeMap.ValueAtIndex(found);

			 switch (matType)
			 {
			 case Graphic::eMaterialParamTexture1D :
				 tss.m_textureType = "Texture1D";
				 break;
			 case Graphic::eMaterialParamTexture2D:
				 tss.m_textureType = "Texture2D";
				 break;
			 case Graphic::eMaterialParamTexture3D:
				 tss.m_textureType = "Texture3D";
				 break;
			 case Graphic::eMaterialParamTextureCUBE:
				 tss.m_textureType = "TextureCUBE";
				 break;
			 }
		 }
		 else
		 {
			 tss.m_textureType = "Texture2D";
		 }

		 m_TexSamplerStateList.Append(tss);
	 }

 }
#endif //GENESISMAKEMATERIAL_H_