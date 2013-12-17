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
#ifndef MATERIALINSTANCE_H_
#define MATERIALINSTANCE_H_
#include "graphicsystem/Material/Material.h"
#include "addons/resource/resource.h"
#include "addons/resource/imageres.h"
#include "rendersystem/base/RenderStateDesc.h"
#include "addons/serialization/serialize.h"
namespace Resources
{
	class TextureResInfo;
}

namespace Graphic
{

	typedef Util::StringAtom ShaderParamString;
	struct TextureParam
	{
		TextureParam()
		{
			texID.Clear();
			imageForLoad = NULL;
		}

		Resources::ResourceId texID;
		GPtr<Resources::ImageRes> imageForLoad;
		RenderBase::TextureHandle texHandle;
	};
	struct ShaderConstantParam
	{
		Util::String name;
		Util::String val;
	};

	typedef Util::Dictionary<ShaderParamString, GPtr<Resources::TextureResInfo> > TexParamMap;
	typedef Util::Dictionary<ShaderParamString,Util::String> ShaderConstantParamMap;
	class MaterialInstance : public Graphic::Material
	{
		__DeclareSubClass(MaterialInstance,Graphic::Material)
			__ScriptBind;
	public:
		MaterialInstance();
		virtual ~MaterialInstance();


		void SetTexture( const ShaderParamString& paramName, const RenderBase::TextureHandle& handle);

		void SetTexture( const ShaderParamString& paramName, const GPtr<Resources::TextureResInfo>& texRes);

		void SetTexture( const ShaderParamString& paramName, const Resources::ResourceId& _texID, Resources::Priority priority = 1);

		void RemoveTexture(const ShaderParamString& paramName);

		void CopyFrom(GPtr<MaterialInstance>& rht);
		void CopyParamList(GPtr<MaterialInstance>& rht);

		bool UpateState();

		void AssignTextures();
		void AssignTexture(const Resources::ResourceId& texID);
		//void AssignMatParams();

		void ClearTextureCache();

		void SetRenderState(GPtr<RenderBase::RenderStateDesc>& state);

		const GPtr<RenderBase::RenderStateDesc>& GetRenderState() const;

		const Resources::ResourceId& GetMaterialID()const ; 

		void SetMaterialID(const Resources::ResourceId& matID);

		//Use for material which has special render order(it's not the best way)
		uint GetSort() const;
		void SetSort(const uint insID);
		uint GetInstanceID() const;

		const Resources::ResourceId& GetShaderID()const ;

		bool IsBuild() const;

		bool IsAllLoaded() const;

		bool IsDirty() const;

		SizeT GetTextureParamCount() const;

		const GPtr<Resources::TextureResInfo>& GetTextureResInfo(IndexT index) const;

		const ShaderParamString& GetTextureParamName(IndexT index) const;

		IndexT GetTextureParamIndex(const ShaderParamString& paramName) const;

		bool ContainsTextureParam(const ShaderParamString& paramName) const;


		ParamFindResult SetConstantParam(const ShaderParamString& paramName, float val);

		ParamFindResult SetConstantParam(const ShaderParamString& paramName, const Math::float4& val);

		ParamFindResult SetConstantParam(const ShaderParamString& paramName, const Math::matrix44& val);

		SizeT GetConstantParamCount() const;

		const ShaderParamString& GetConstantParamName(IndexT index) const;

		const Util::String& GetConstantParamValue(IndexT index) const;

		IndexT GetConstantParamIndex(const ShaderParamString& paramName) const;

		bool ContainsConstantParam(const ShaderParamString& paramName) const;

		void ClearConstantParamCache();

		void RemoveConstantParam(const ShaderParamString& paramName);

		void _SetBuildState(bool value);//just for ResourceManager.
		void _SetShaderID(const Resources::ResourceId& id);//just for MaterialInstanceManager.
		ParamFindResult _SetConstantParam(const ShaderParamString& paramName, Util::String val);//just for serialization.
		//public:		



		static GPtr<MaterialInstance> NullMaterial;		
	protected:
		void _AssignDefaultToInstance();

	private:
		void _SetConstantParamOld(const ShaderParamString& paramName,const Util::String& val);//just for old code.
		ShaderConstantParamMap m_scParams;
		Resources::ResourceId m_shaderID;
		TexParamMap m_texParams;
		GPtr<RenderBase::RenderStateDesc> m_renderState;
		bool m_dirty;
		bool m_isbuild;
		bool m_allLoaded;
		uint m_sort;
		uint m_InstanceID;
		Resources::ResourceId m_materialID;			// from file path.
		friend class MaterialInstanceManager;

	};

	inline uint MaterialInstance::GetSort() const
	{
		return m_sort;
	}
	inline void MaterialInstance::SetSort(const uint insID)
	{
		m_sort = insID;
	}
	inline uint MaterialInstance::GetInstanceID() const
	{
		return m_InstanceID;
	}
	inline const Resources::ResourceId& MaterialInstance::GetMaterialID()const 
	{
		return m_materialID;
	}
	inline void MaterialInstance::SetMaterialID(const Resources::ResourceId& matID)
	{
		m_materialID = matID;
	}
	inline const Resources::ResourceId& MaterialInstance::GetShaderID() const
	{
		return m_shaderID;
	}
	inline bool MaterialInstance::IsBuild() const
	{
		return m_isbuild;
	}

	inline void MaterialInstance::_SetBuildState(bool value)
	{
		m_isbuild = value;
	}

	inline void MaterialInstance::_SetShaderID(const Resources::ResourceId& id)
	{
		m_shaderID = id;
	}

	inline bool MaterialInstance::IsAllLoaded() const
	{
		return m_allLoaded;
	}

	inline bool MaterialInstance::IsDirty() const
	{
		return m_dirty;
	}

	inline void MaterialInstance::SetRenderState(GPtr<RenderBase::RenderStateDesc>& state)
	{
		m_renderState = state;
	}

	inline const GPtr<RenderBase::RenderStateDesc>& MaterialInstance::GetRenderState() const
	{
		return m_renderState;
	}



	inline SizeT MaterialInstance::GetConstantParamCount() const
	{
		return m_scParams.Size();
	}
	inline const ShaderParamString& MaterialInstance::GetConstantParamName(IndexT index) const
	{
		n_assert(index >=0 && index < m_scParams.Size() );
		return m_scParams.KeyAtIndex(index);
	}

	inline const Util::String& MaterialInstance::GetConstantParamValue(IndexT index) const
	{
		n_assert(index >=0 && index < m_scParams.Size() );
		return m_scParams.ValueAtIndex(index);
	}

	inline IndexT MaterialInstance::GetConstantParamIndex(const ShaderParamString& paramName) const
	{
		return m_scParams.FindIndex( paramName );
	}

	inline bool MaterialInstance::ContainsConstantParam(const ShaderParamString& paramName) const
	{
		return m_scParams.Contains(paramName);
	}
	inline void MaterialInstance::ClearConstantParamCache()
	{
		m_scParams.Clear();
	}
}
#endif //MATERIALINSTANCE_H_
