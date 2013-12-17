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
#ifndef MATERIALTECH_H_
#define MATERIALTECH_H_

#include "MaterialPass.h"
namespace Graphic
{
	class MaterialPass;
	class Material;

	class MaterialTech : public Core::RefCounted
	{
		__DeclareSubClass(MaterialTech,Core::RefCounted)
	public:
		MaterialTech();
		virtual	~MaterialTech();
		void AddPass(const GPtr<MaterialPass>& pass);
		const GPtr<MaterialPass>& GetDefaultPass() const;
		const Util::Array< GPtr<MaterialPass> >& GetPassList() const;
		virtual void Clone(const GPtr<MaterialTech>& from);
		bool IsTemplateTech();
		void SetTemplateTech(bool bSurface);
		// internal call.
		// used for build a binding map for shader parameter and gpu register.
		void _BuildBindingMap(Material* mat);

	private:
		Util::Array< GPtr<MaterialPass> > m_passList;
		bool m_bSurfaceTech;

	};

	typedef Util::Array< GPtr<MaterialTech> > MaterialTechList;

	inline void MaterialTech::AddPass(const GPtr<MaterialPass>& pass)
	{
		m_passList.Append(pass);
	}

	inline const GPtr<MaterialPass>& MaterialTech::GetDefaultPass() const
	{
		return m_passList[0];
	}

	inline const Util::Array< GPtr<MaterialPass> >& MaterialTech::GetPassList() const
	{
		return m_passList;
	}

	inline bool MaterialTech::IsTemplateTech()
	{
		return m_bSurfaceTech;
	}

	inline void MaterialTech::SetTemplateTech(bool bSurface)
	{
		m_bSurfaceTech = bSurface;
	}
}
#endif//MATERIALTECH_H_