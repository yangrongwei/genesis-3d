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
#include "GenesisMaterial.h"
namespace GenesisMaterialMaker
{
	static uint sID_Index = 1;// 0 is remains which means null

	GenesisMaterial::GenesisMaterial()
	{
		//empty
	}

	GenesisMaterial::~GenesisMaterial()
	{
		//empty
	}

	void GenesisMaterial::Setup(const char* str)
	{
		m_GPUProgrampath = Util::String(str);		
	}

	RenderBase::GPUProgramHandle GenesisMaterial::CreateGPUProgram()
	{
		return m_material.CreateGPUProgram();	
	}

	GPtr<Graphic::Material> GenesisMaterial::CreateRealMaterial()
	{
		GPtr<Graphic::Material> mat;
		m_material.AssignDefaultMatParamBindings();
		m_material.MakeMaterial(mat);
		mat->SetName(m_name);

		// the shader would only be created once at the first time. materials with the same shader later
		// would use the clone of the first material. So that we can guarantee the copys have the same shader id
		mat->SetShaderInstanceID(sID_Index);
		++sID_Index;
		n_assert(0 != sID_Index); // assert the shaderInstance ID wouldn't overflow
		mat->_BuildBindingMap();
		// gles can catch the register's id at this time,so that we can set the state of texture.
		m_material._SetTextureSamplers();
		return mat;
	}


}
