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
#ifndef GENESISMATERIAL_H_
#define GENESISMATERIAL_H_
#include "util/string.h"
#include "util/array.h"
#include "GenesisMakeGPUProgram.h"
#include "GenesisMakeMaterial.h"
namespace GenesisMaterialMaker
{
	
	class GenesisMaterial
	{
	public:
			GenesisMaterial();
		~GenesisMaterial();
	void Setup(const char* str);
	void SetName(const Util::String& name);
	void AddMaterial(const GenesisMakeMaterial& mat);
	RenderBase::GPUProgramHandle CreateGPUProgram();
	GPtr<Graphic::Material> CreateRealMaterial();

	public:
	Util::String m_GPUProgrampath;
	GenesisMakeMaterial m_material;
	Util::String m_name;
	};

	inline void GenesisMaterial::AddMaterial(const GenesisMakeMaterial& mat)
	{
		m_material = mat;
	}

	inline void GenesisMaterial::SetName(const Util::String& name)
	{
		m_name = name;
	}
}
#endif//GENESISMATERIAL_H_