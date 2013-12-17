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
#include "MaterialPass.h"
#include "foundation/math/scalar.h"
#include "foundation/util/stl.h"
#include "graphicsystem/Material/Material.h"

namespace Graphic
{



	struct MatParamBindingSort : public std::binary_function<MatParamBinding&, MatParamBinding&, std::size_t>
	{
		bool operator() (const MatParamBinding& lhs, const MatParamBinding& rhs) const
		{
			return lhs.bindIndex < rhs.bindIndex;
		}
	};
	__ImplementClass(MaterialPass,'GRMP',Core::RefCounted);
	__ImplementClass(ShaderParamBindingMap,'SPBM', Core::RefCounted);
	//------------------------------------------------------------------------
	ShaderParamBindingMap::ShaderParamBindingMap()
	{
		m_ShaderBindingList.SetSize( SCT_COUNT );
		m_GlobalBinding.SetSize( SCT_COUNT );
		m_LocalBinding.SetSize( SCT_COUNT );
		m_GlobaBingdingInfos.SetSize(SCT_COUNT);
	}

	inline void _set_info(MatParamBindings& global_sct, IndexT& index, int& end_, int enum_)
	{
		while(index < global_sct.Size() && global_sct[index].bindIndex < enum_)
		{
			++index;
		}
		end_ = index;//Math::n_min(index, global_sct.Size());
	}

	void ShaderParamBindingMap::Setup()
	{
		for ( IndexT sct = SCT_VS; sct < SCT_COUNT; ++sct )
		{
			MatParamBindings& global_sct = m_GlobalBinding[sct];
			GlobalBindingInfo& info = m_GlobaBingdingInfos[sct];
			Util::CustomSortArray<MatParamBinding, MatParamBindingSort>(global_sct);

			IndexT index = 0;
			_set_info(global_sct, index, info.MatCommonEnd, eGShaderMatCommonEnd);
			_set_info(global_sct, index, info.MatCustomEnd, eGShaderMatCustomEnd);
			_set_info(global_sct, index, info.VecCommonEnd, eGShaderVecCommonEnd);
			_set_info(global_sct, index, info.VecCustomEnd, eGShaderVecCustomEnd);

		}
	}

	//------------------------------------------------------------------------
	ShaderParamBindingMap::~ShaderParamBindingMap()
	{

	}
	//------------------------------------------------------------------------
	MaterialPass::MaterialPass()
	{
		memset( m_bGlobalParamUsage, 0, sizeof(m_bGlobalParamUsage) );
		m_ShaderParamBindingMap = ShaderParamBindingMap::Create();
		//empty
	}
	MaterialPass::~MaterialPass()
	{
		m_renderStateObject = 0;
	}

	void MaterialPass::Clone(const GPtr<MaterialPass>& from)
	{
		m_GPUProgramHandle = from->GetGPUProgramHandle();
		m_ShaderParamBindingMap = from->m_ShaderParamBindingMap;
		m_name = from->m_name;
		//copy renderstate
		if (from->GetRenderStateObject().isvalid())
		{
			m_renderStateObject = RenderBase::RenderStateDesc::Create();
			m_renderStateObject->Setup();
			m_renderStateObject->SetBlendState(from->GetRenderStateObject()->GetBlendState());
			m_renderStateObject->SetDepthAndStencilState(from->GetRenderStateObject()->GetDepthAndStencilState());
			m_renderStateObject->SetSamplerState(from->GetRenderStateObject()->GetSamplerState());
			m_renderStateObject->SetRasterizerState(from->GetRenderStateObject()->GetRasterizerState());
		}
		Memory::Copy(from->m_bGlobalParamUsage, m_bGlobalParamUsage, GlobalParamCount);
	}

	//------------------------------------------------------------------------
	void MaterialPass::_BuildBindingMap(Material* mat)
	{
		n_assert(mat);
		n_assert(m_ShaderParamBindingMap);

		ShaderParamBindingList& shaderBindingList = m_ShaderParamBindingMap->m_ShaderBindingList;
		BindingMap& globalBinding = m_ShaderParamBindingMap->m_GlobalBinding;
		BindingMap& localBinding = m_ShaderParamBindingMap->m_LocalBinding;

		GlobalMaterialParam* g_GlobalMaterialParam = Material::GetGlobalMaterialParams();
		const GlobalShaderParamMap& globalShaderParamMap = g_GlobalMaterialParam->GetGlobalShaderParamMap();

		const MaterialParamList& localMatParamList = mat->GetParamList();

		for ( IndexT sct = SCT_VS; sct < SCT_COUNT; ++sct )
		{
			ShaderParamList& rigisterList = shaderBindingList[sct];
			MatParamBindings& global_sct = globalBinding[sct];
			MatParamBindings& local_sct = localBinding[sct];

			// 构造一个名字和寄存器位置的查询表
			Util::Dictionary<Util::String, int> RegQuery;
			for ( IndexT iReg = 0; iReg < rigisterList.Size(); ++iReg )
			{
				ShaderParam& sp = rigisterList[iReg];
				RegQuery.Add( sp.GetName(), sp.GetRegister() );
			}

			// 首先绑定全局表
			for ( IndexT globalindex = 0; globalindex < globalShaderParamMap.Size(); ++globalindex)
			{
				GlobalShaderParam& globalSP = globalShaderParamMap[globalindex];
				IndexT findIndex = RegQuery.FindIndex( globalSP.m_name );
				if ( findIndex != InvalidIndex )
				{
					MatParamBinding binding;
					binding.Regiter = RegQuery.ValueAtIndex(findIndex);
					binding.bindIndex = globalindex;
					global_sct.Append( binding );
					m_bGlobalParamUsage[globalindex] = 1;
				}
			}

			// 绑定本地表
			for ( IndexT localIndex = 0; localIndex < localMatParamList.Size(); ++localIndex )
			{
				MaterialParam* matParam = localMatParamList[localIndex];
				n_assert(matParam);
				IndexT findIndex = RegQuery.FindIndex( matParam->GetName() );

				if ( findIndex != InvalidIndex )
				{
					MatParamBinding binding;
					binding.Regiter = RegQuery.ValueAtIndex(findIndex);
					binding.bindIndex = localIndex;
					local_sct.Append( binding );
				}
			}

		}
		m_ShaderParamBindingMap->Setup();
	}


}