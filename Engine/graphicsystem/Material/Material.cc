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
#include "Material.h"

#include "memory/memory.h"

namespace Graphic
{
	GPtr<GlobalMaterialParam> Material::pGMP = 0;
	__ImplementClass(Material,'GMAT',Core::RefCounted)
		Material::Material() 
		:m_shaderInstacneID(0)
	{
		//empty
	}

	Material::~Material()
	{
		Discard();
	}

	void Material::Clone(const GPtr<Material>& from)
	{
		m_name = from->GetName();
		m_shaderInstacneID = from->GetShaderInstanceID();
		_CloneParamList(from->GetParamList());
		_CloneTechList(from->GetTechList());
		m_renderQueue = from->GetRenderQueue();
	}

	void Material::Discard()
	{
		for (SizeT i = 0; i < m_techList.Size(); ++i)
		{
			m_techList[i] = 0;
		}
		m_fallBackTech = 0;

		_DiscardMaterialParamList();
	}
	IndexT Material::GetRegisterIndex(const Util::String& name, ShaderCodeType area,  IndexT iPass) const
	{
		IndexT nSlot = -1;

		const MaterialTechList& techList = GetTechList();
		for (IndexT iTech = 0; iTech < techList.Size(); ++iTech)
		{
			const Util::Array< GPtr<Graphic::MaterialPass> >& passList = techList[iTech]->GetPassList();

			const GPtr<Graphic::ShaderParamBindingMap>& spMap = passList[iPass]->GetParamBindings();
			const Graphic::ShaderParamBindingList& spList    = spMap->GetShaderParamBindingList();
			ShaderParamList& bindList = spList[area];

			for (IndexT i = 0; i < bindList.Size(); ++i)
			{
				if (bindList[i].GetName() == name)
				{
					nSlot = bindList[i].GetRegister();
					return nSlot;
				}
			}
		}

		return nSlot;
	}
	//------------------------------------------------------------------------
	void 
		Material::_DiscardMaterialParamList()
	{
		if ( m_paramList.IsEmpty() )
		{
			return;
		}

		SizeT count = m_paramList.Size();
		for ( IndexT i = 0; i < count; ++i )
		{
			n_delete(m_paramList[i]);
		}
		m_paramList.Clear();
	}

	//------------------------------------------------------------------------
	/*
	这个函数只有从shader创建material模板的时候会调用。应该是clone。以免错误的删除内存
	*/
	void Material::AddParams(const MaterialParamList& param)
	{
		_CloneParamList(param);
		//m_paramList = param;
	}

	//------------------------------------------------------------------------
	void Material::_CloneParamList(const MaterialParamList& param)
	{
		_DiscardMaterialParamList();

		for (SizeT i = 0;i < param.Size();++i)
		{
			switch (param[i]->GetType())
			{
			case eMaterialParamFloat:
				{
					MaterialParamFloat* mpf = n_new( MaterialParamFloat );
					*mpf = *(static_cast<MaterialParamFloat*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamVector:
				{
					MaterialParamVector* mpf = n_new( MaterialParamVector );
					*mpf = *(static_cast<MaterialParamVector*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamMatrix:
				{
					MaterialParamMatrix* mpf = n_new( MaterialParamMatrix );
					*mpf = *(static_cast<MaterialParamMatrix*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamTexture1D:
				{
					MaterialParamTex1D* mpf = n_new( MaterialParamTex1D );
					*mpf = *(static_cast<MaterialParamTex1D*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamTexture2D:
				{
					MaterialParamTex2D* mpf = n_new( MaterialParamTex2D );
					*mpf = *(static_cast<MaterialParamTex2D*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamTexture3D:
				{
					MaterialParamTex3D* mpf = n_new( MaterialParamTex3D );
					*mpf = *(static_cast<MaterialParamTex3D*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			case eMaterialParamTextureCUBE:
				{
					MaterialParamTexCube* mpf = n_new( MaterialParamTexCube );
					*mpf = *(static_cast<MaterialParamTexCube*>(param[i]));
					m_paramList.Append(mpf);
				}
				break;
			default:
				n_error("TODO: MaterialInstance::CopyParams(): current material parameter is not implemented!\n");
				break;
			}

		}
	}

	void Material::_CloneTechList(const MaterialTechList& from)
	{
		m_techList.Clear();

		for (SizeT i = 0; i < from.Size(); ++i)
		{
			GPtr<MaterialTech> tech = MaterialTech::Create();
			tech->Clone(from[i]);
			m_techList.Append(tech);
		}
	}

	//------------------------------------------------------------------------
	// 构建shader参数和寄存器的绑定表。 外部不要调用
	void Material::_BuildBindingMap()
	{
		for( IndexT i = 0; i < m_techList.Size(); ++i )
		{
			m_techList[i]->_BuildBindingMap( this );
		}
	}

	template<typename MP_Type>
	inline ParamFindResult _find(MaterialParameterType type, const Util::String& paramName, MaterialParamList& list, MP_Type*& param)
	{
		MaterialParamList::Iterator begin = list.Begin();
		MaterialParamList::Iterator end = list.End();
		while(begin != end)
		{
			if ((*begin)->GetName() == paramName)
			{ 
				if((*begin)->GetType() == type)
				{
					param = static_cast<MP_Type*>(*begin);
					return ePFR_Succeed;
				}
				return ePFR_TypeError;
			}
			++begin;
		}
		return ePFR_NotFound;
	}
	ParamFindResult Material::find(const Util::String& paramName, MaterialParam*& param)
	{
		MaterialParamList::Iterator begin = m_paramList.Begin();
		MaterialParamList::Iterator end = m_paramList.End();
		while(begin != end)
		{
			if ((*begin)->GetName() == paramName)
			{ 
				param = (*begin);
				return ePFR_Succeed;

			}
			++begin;
		}
		return ePFR_NotFound;
	}

	ParamFindResult Material::findFloat(const Util::String& paramName, MaterialParamFloat*& param)
	{
		return _find(eMaterialParamFloat, paramName, m_paramList, param);
	}

	ParamFindResult Material::findVector(const Util::String& paramName, MaterialParamVector*& param)
	{
		return _find(eMaterialParamVector, paramName, m_paramList, param);
	}

	ParamFindResult Material::findMatrix(const Util::String& paramName, MaterialParamMatrix*& param)
	{
		return _find(eMaterialParamMatrix, paramName, m_paramList, param);
	}
	ParamFindResult Material::findTexture(const Util::String& paramName, MaterialParamTexture*& param)
	{
		MaterialParamList::Iterator begin = m_paramList.Begin();
		MaterialParamList::Iterator end = m_paramList.End();
		while(begin != end)
		{
			if ((*begin)->GetName() == paramName)
			{ 
				switch((*begin)->GetType())
				{
				case eMaterialParamTexture1D:
				case eMaterialParamTexture2D:
				case eMaterialParamTexture3D:
				case eMaterialParamTextureCUBE:
					{
						param = static_cast<MaterialParamTexture*>(*begin);					
						return ePFR_Succeed;
					}
				default:
					{
						break;
					}

				}
				return ePFR_TypeError;
			}
			++begin;
		}
		return ePFR_NotFound;
	}
}