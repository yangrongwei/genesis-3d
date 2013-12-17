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
#ifndef MATERIALPASS_H_
#define MATERIALPASS_H_

#include "core/refcounted.h"
#include "ShaderParam.h"
#include "rendersystem/base/RenderStateDesc.h"
#include "graphicsystem/Material/GlobalShaderParam.h"
#include "graphicsystem/base/RenderBase.h"

namespace Graphic
{
	class MaterialPass;
	class Material;

	enum ShaderCodeType
	{
		SCT_VS = 0,
		SCT_PS,
		SCT_COUNT
	};

	typedef Util::FixedArray<ShaderParamList> ShaderParamBindingList;
	struct MatParamBinding
	{
		int Regiter;	//	index of gpu register.
		int bindIndex;	//	bind index. in global parameters means global index, in local parameters, means local index.
	};
	typedef Util::Array<MatParamBinding> MatParamBindings;
	typedef Util::FixedArray<MatParamBindings> BindingMap;

	struct GlobalBindingInfo
	{
		union{
			int MatCommonEnd;
			int MatCustomBegin;
		};
		union{
			int MatCustomEnd;
			int VecCommonBegin;
		};
		union{
			int VecCommonEnd;
			int VecCustomBegin;
		};
		union
		{
			int VecCustomEnd;
			int TexBegin;
		};

	};
	typedef Util::FixedArray<GlobalBindingInfo> GlobalBindingInfoMap;

	// binding map ,between shader register and material parameters index.
	class ShaderParamBindingMap: public Core::RefCounted
	{
		__DeclareClass(ShaderParamBindingMap);
	public:
		ShaderParamBindingMap();
		virtual ~ShaderParamBindingMap();

		const MatParamBindings& GetLocalBinding( ShaderCodeType t){
			n_assert( t >= SCT_VS && t < SCT_COUNT);
			return m_LocalBinding[t];
		}
		const MatParamBindings& GetGlobalBinding(ShaderCodeType t ){
			n_assert( t >= SCT_VS && t < SCT_COUNT);
			return m_GlobalBinding[t];
		}
		const GlobalBindingInfo& GetGlobalBindingInfo(ShaderCodeType t){
			n_assert( t >= SCT_VS && t < SCT_COUNT);
			return m_GlobaBingdingInfos[t];
		}
		const ShaderParamList& GetShaderParamList(ShaderCodeType t){
			n_assert( t >= SCT_VS && t < SCT_COUNT);
			return m_ShaderBindingList[t];
		}

		const ShaderParamBindingList& GetShaderParamBindingList(){
			return m_ShaderBindingList;
		}
		void Setup();

	protected:


		ShaderParamBindingList m_ShaderBindingList;	// all register index, type and name of pass
		BindingMap m_GlobalBinding;	//	used for global parameters.
		BindingMap m_LocalBinding;	//	used for local parameters.
		GlobalBindingInfoMap m_GlobaBingdingInfos;
		friend class MaterialPass;
	};


	class MaterialPass : public Core::RefCounted
	{
		__DeclareSubClass(MaterialPass,Core::RefCounted)
	public:
		MaterialPass();
		virtual	~MaterialPass();

		void SetGPUProgramHandle(RenderBase::GPUProgramHandle handle);
		const RenderBase::GPUProgramHandle& GetGPUProgramHandle() const;
		void SetRenderStateDesc(const GPtr<RenderBase::RenderStateDesc>& rso);
		GPtr<RenderBase::RenderStateDesc>& GetRenderStateObject();
		void SetName(const Util::String& name);
		const Util::String& GetName() const;

		void AddShaderParamBinding(ShaderCodeType t, const ShaderParamList& value);
		const GPtr<ShaderParamBindingMap>& GetParamBindings();


		void Clone(const GPtr<MaterialPass>& from);

		bool isGlobalParamUsed( const int& inedx );

		// internal call.
		// used for build a binding map for shader parameter and gpu register.
		void _BuildBindingMap(Material* mat);

	private:
		bool m_bGlobalParamUsage[GlobalParamCount];
		GPtr<RenderBase::RenderStateDesc> m_renderStateObject;
		RenderBase::GPUProgramHandle m_GPUProgramHandle;
		GPtr<ShaderParamBindingMap> m_ShaderParamBindingMap;
		Util::String m_name;
	};

	inline void MaterialPass::SetGPUProgramHandle(RenderBase::GPUProgramHandle handle)
	{
		m_GPUProgramHandle = handle;
	}

	inline const RenderBase::GPUProgramHandle& MaterialPass::GetGPUProgramHandle() const
	{
		return m_GPUProgramHandle;
	}

	inline void MaterialPass::AddShaderParamBinding(ShaderCodeType t, const ShaderParamList& value)
	{
		n_assert( t >= SCT_VS && t < SCT_COUNT );
		n_assert( m_ShaderParamBindingMap );
		m_ShaderParamBindingMap->m_ShaderBindingList[t] = value;
	}

	inline void MaterialPass::SetRenderStateDesc(const GPtr<RenderBase::RenderStateDesc>& rso)
	{
		m_renderStateObject = rso;
	}

	inline GPtr<RenderBase::RenderStateDesc>& MaterialPass::GetRenderStateObject()
	{
		return m_renderStateObject;
	}

	inline 
		const GPtr<ShaderParamBindingMap>& 
		MaterialPass::GetParamBindings()
	{
		return m_ShaderParamBindingMap;
	}

	inline
		void MaterialPass::SetName(const Util::String& name)
	{
		m_name = name;
	}

	inline
		const Util::String& MaterialPass::GetName() const
	{
		return m_name;
	}
	inline
		bool MaterialPass::isGlobalParamUsed( const int& index )
	{
		n_assert( index >=0 && index < GlobalParamCount );
		return m_bGlobalParamUsage[index];
	}
}
#endif//MATERIALPASS_H_