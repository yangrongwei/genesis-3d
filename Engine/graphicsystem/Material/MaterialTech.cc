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
#include "MaterialTech.h"

namespace Graphic
{
	__ImplementClass(MaterialTech,'GRMT',Core::RefCounted)
		MaterialTech::MaterialTech()
	{
		//empty
	}

	MaterialTech::~MaterialTech()
	{
		m_passList.Clear();
	}

	void MaterialTech::Clone(const GPtr<MaterialTech>& from)
	{
		m_passList.Clear();
		m_bSurfaceTech = from->m_bSurfaceTech;
		const Util::Array< GPtr<MaterialPass> >& passList = from->GetPassList();
		for (SizeT i = 0; i < passList.Size(); ++i)
		{
			GPtr<MaterialPass> pass = MaterialPass::Create();
			m_passList.Append(pass); 
			m_passList[i]->Clone(passList[i]);
		}		
	}

	// 构建shader参数和寄存器的绑定表。 外部不要调用。 只有在第一次读取后，有shader调用在模板上
	void MaterialTech::_BuildBindingMap(Material* mat)
	{
		for (SizeT i = 0; i < m_passList.Size(); ++i)
		{
			m_passList[i]->_BuildBindingMap(mat);
		}	
	}
}