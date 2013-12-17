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
#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "MaterialTech.h"
#include "GlobalShaderParam.h"
#include "graphicsystem/base/RenderQueue.h"
namespace Graphic
{

	class RenderLayerConverter
	{
	public:
		static inline RenderLayer Convert(uint value)
		{
			return static_cast<RenderLayer>(value);
		}

		static inline uint Convert(RenderLayer value)
		{
			return static_cast<uint>(value);
		}
	};;

	enum ParamFindResult
	{		
		ePFR_Succeed = 0,
		ePFR_NotFound,
		ePFR_TypeError,

	};


	class Material : public Core::RefCounted
	{
		__DeclareSubClass(Material,Core::RefCounted)
	public:	
		Material();
		virtual ~Material();
		void SetName(const Util::String& name);
		const Util::String& GetName() const;
		void SetShaderInstanceID(uint id);
		uint GetShaderInstanceID() const;

		void AddTech(const GPtr<MaterialTech>& tech);
		const GPtr<MaterialTech>& GetTech(SizeT index = 0) const;
		const MaterialTechList& GetTechList() const;
		void AddParams(const MaterialParamList& param);
		const MaterialParamList& GetParamList() const;
		void SetRenderQueue(RenderQueue rqt);
		const RenderQueue& GetRenderQueue() const;
		void SetRenderLayer(RenderLayer rl);
		const RenderLayer& GetRenderLayer() const;
		virtual void Clone(const GPtr<Material>& from);
		virtual void Discard();



		IndexT GetRegisterIndex(const Util::String& name, ShaderCodeType area,  IndexT iPass) const ;

		ParamFindResult find(const Util::String& paramName, MaterialParam*& param);
		ParamFindResult findFloat(const Util::String& paramName, MaterialParamFloat*& param);
		ParamFindResult findVector(const Util::String& paramName, MaterialParamVector*& param);
		ParamFindResult findMatrix(const Util::String& paramName, MaterialParamMatrix*& param);
		ParamFindResult findTexture(const Util::String& paramName, MaterialParamTexture*& param);



		static GlobalMaterialParam* GetGlobalMaterialParams();
		static void RemoveGlobalMaterialParams();

		static GPtr<Material> s_defaultFallBackMat;

		// internal call.
		// used for build a binding map for shader parameter and gpu register.
		void _BuildBindingMap();
	protected:
		void _CloneParamList(const MaterialParamList& param);
	private:		
		void _CloneTechList(const MaterialTechList& from);
		void _DiscardMaterialParamList();

		static GPtr<GlobalMaterialParam> pGMP;
		Util::String m_name;
		MaterialParamList m_paramList;
		MaterialTechList m_techList;
		GPtr<MaterialTech> m_fallBackTech;
		RenderQueue m_renderQueue;
		RenderLayer m_renderLayer;
		uint m_shaderInstacneID;//使用相同shader文件的材质这个id都是一样的。
	};

	inline void Material::SetName(const Util::String& name)
	{
		m_name = name;
	}

	inline const Util::String& Material::GetName() const
	{
		return m_name;
	}

	inline void Material::SetShaderInstanceID(uint id)
	{
		m_shaderInstacneID = id;
	}

	inline uint Material::GetShaderInstanceID() const
	{
		return m_shaderInstacneID;
	}


	inline const MaterialParamList& Material::GetParamList() const
	{
		return m_paramList;
	}

	inline void Material::AddTech(const GPtr<MaterialTech>& tech)
	{
		m_techList.Append(tech);
	}

	inline const GPtr<MaterialTech>& Material::GetTech(SizeT index) const
	{
		return m_techList[index];
	}

	inline const MaterialTechList& Material::GetTechList() const
	{
		return m_techList;
	}

	inline void Material::SetRenderQueue(RenderQueue rqt)
	{
		m_renderQueue = rqt;
	}

	inline const RenderQueue& Material::GetRenderQueue() const
	{
		return m_renderQueue;
	}

	inline void Material::SetRenderLayer(RenderLayer rl)
	{
		m_renderLayer = rl;
	}

	inline const RenderLayer& Material::GetRenderLayer() const
	{
		return m_renderLayer;
	}

	inline GlobalMaterialParam* Material::GetGlobalMaterialParams()
	{
		if (!pGMP.isvalid())
		{
			pGMP = GlobalMaterialParam::Create();
		}

		return GlobalMaterialParam::Instance();
	}

	inline void Material::RemoveGlobalMaterialParams()
	{
		if (pGMP.isvalid())
		{
			pGMP = 0;
		}
		n_assert(!pGMP.isvalid())

			if (s_defaultFallBackMat.isvalid())
			{
				s_defaultFallBackMat = 0;
			}
			n_assert(!s_defaultFallBackMat.isvalid())
	}
}

#endif 