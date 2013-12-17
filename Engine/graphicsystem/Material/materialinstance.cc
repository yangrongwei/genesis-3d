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
#ifdef __OSX__
#include "string.h"
#include "math/matrix44.h"
#endif
#include "materialinstance.h"
#include "resource/resourcemanager.h"
namespace Graphic
{
	__ImplementClass(MaterialInstance,'MINS',Material)

		using namespace Resources;
	GPtr<MaterialInstance> MaterialInstance::NullMaterial(NULL);
	static uint sInstanceID = 1;//零位保留，表示空
	static const Util::String scUserDefTex="#UserDefTex";


	MaterialInstance::MaterialInstance() : m_dirty(false)
		, m_allLoaded(false)
		, m_isbuild(false)
		, m_materialID("")
	{
		m_sort = sInstanceID;
		m_InstanceID = sInstanceID;
		++sInstanceID;
		//empty
	}

	MaterialInstance::~MaterialInstance()
	{
		m_renderState = 0;
	}

	SizeT MaterialInstance::GetTextureParamCount() const
	{
		return m_texParams.Size();
	}

	const GPtr<Resources::TextureResInfo>& MaterialInstance::GetTextureResInfo(IndexT index) const
	{
		return m_texParams.ValueAtIndex(index);
	}

	const ShaderParamString& MaterialInstance::GetTextureParamName(IndexT index) const
	{
		n_assert(index >=0 && index < m_texParams.Size() );
		return m_texParams.KeyAtIndex(index);
	}

	IndexT MaterialInstance::GetTextureParamIndex(const ShaderParamString& paramName) const
	{
		return m_texParams.FindIndex( paramName );
	}

	void MaterialInstance::ClearTextureCache()
	{
		m_texParams.Clear();
	}

	bool MaterialInstance::ContainsTextureParam(const ShaderParamString& paramName) const
	{
		return m_texParams.Contains(paramName);
	}

	void MaterialInstance::SetTexture(const ShaderParamString& paramName, const RenderBase::TextureHandle& handle)
	{
		TexParamMap& texMap =  m_texParams;
		IndexT findtex = texMap.FindIndex( paramName );
		if (InvalidIndex == findtex)
		{					
			GPtr<Resources::TextureResInfo> tri = Resources::TextureResInfo::Create();
			tri->SetResID(scUserDefTex);
			tri->SetHandle(handle);
			texMap.Add( paramName, tri);
		}
		else
		{
			TexParamMap::key_value_pair_type& pair = m_texParams.KeyValuePairAtIndex(findtex);
			if (scUserDefTex != pair.Value()->GetResID().Value())
			{
				pair.Value() = Resources::TextureResInfo::Create();
				pair.Value()->SetResID(scUserDefTex);	
			}
			pair.Value()->SetHandle(handle);
		}
		AssignTextures();
	}

	void MaterialInstance::SetTexture(const ShaderParamString& paramName, const GPtr<Resources::TextureResInfo>& texRes)
	{
		if(!m_texParams.IsEmpty())
		{
			IndexT findtex = m_texParams.FindIndex( paramName );
			if ( findtex != InvalidIndex )
			{
				TexParamMap::key_value_pair_type& pair = m_texParams.KeyValuePairAtIndex(findtex);
				pair.Value() = texRes;
				if (texRes->GetHandle().IsValid())
				{
					AssignTextures();
				}
				else
				{
					m_dirty = true;	
				}
			}			
		}
	}

	void MaterialInstance::SetTexture(const ShaderParamString& paramName, const Resources::ResourceId& _texID, Resources::Priority priority /* = 1 */)
	{
		const Resources::ResourceId* texID = &_texID;
		if ( texID->IsValid() )
		{
			// - 这个参数由用户在脚本中设置，用于没有resid的情况。
			if ( *texID == scUserDefTex )
			{
				return;
			}
		}
		else
		{
			texID = &ResourceManager::DefaultTextureID;
			n_warning("RenderComponent::_AddTextureParam(): texID: %s is error,\n replace with DefaultTextureID: %s",_texID.AsString().AsCharPtr(),ResourceManager::DefaultTextureID.AsString().AsCharPtr());
		}



		if(!m_texParams.IsEmpty())
		{
			IndexT findtex = m_texParams.FindIndex( paramName );
			if ( findtex != InvalidIndex )
			{
				GPtr<Resources::TextureResInfo> tri = ResourceManager::Instance()->CreateTextureInfo(*texID,priority);					

				TexParamMap::key_value_pair_type& pair = m_texParams.KeyValuePairAtIndex(findtex);
				pair.Value() = tri;
				m_dirty = true;				
				return;
			}			
		}
		GPtr<TextureResInfo> tri = ResourceManager::Instance()->CreateTextureInfo(*texID,priority);
		m_texParams.Add( paramName, tri);	
		m_dirty = true;
	}

	void MaterialInstance::RemoveTexture(const ShaderParamString& paramName)
	{
		TexParamMap& texMap =  m_texParams;
		if(!texMap.IsEmpty())
		{
			IndexT findtex = texMap.FindIndex( paramName );
			if ( findtex != InvalidIndex )
			{
				texMap.EraseAtIndex(findtex);				
				m_dirty = true;
			}			
		}
	}

	ParamFindResult MaterialInstance::SetConstantParam(const ShaderParamString& paramName, const Math::matrix44& val)
	{
		MaterialParamMatrix* mp = NULL;
		ParamFindResult ret = findMatrix(paramName.AsString(), mp);
		if (ePFR_Succeed == ret)
		{
			mp->SetValue(val);
			_SetConstantParamOld(paramName, Util::String::FromMatrix44(val));
		}
		return ret;
	}

	ParamFindResult MaterialInstance::SetConstantParam(const ShaderParamString& paramName, const Math::float4& val)
	{
		MaterialParamVector* mp = NULL;
		ParamFindResult ret = findVector(paramName.AsString(), mp);
		if (ePFR_Succeed == ret)
		{
			mp->SetValue(val);
			_SetConstantParamOld(paramName, Util::String::FromFloat4(val));
		}
		return ret;
	}

	ParamFindResult MaterialInstance::SetConstantParam(const ShaderParamString& paramName, float val)
	{
		MaterialParamFloat* mp = NULL;
		ParamFindResult ret = findFloat(paramName.AsString(), mp);
		if (ePFR_Succeed == ret)
		{
			mp->SetValue(val);
			_SetConstantParamOld(paramName, Util::String::FromFloat(val));
		}
		return ret;
	}

	void MaterialInstance::RemoveConstantParam(const ShaderParamString& paramName)
	{
		ShaderConstantParamMap& scMap = m_scParams;
		IndexT findtex = scMap.FindIndex( paramName );
		if ( findtex != InvalidIndex )
		{
			scMap.EraseAtIndex(findtex);
		}
	}


	ParamFindResult MaterialInstance::_SetConstantParam(const ShaderParamString& paramName, Util::String val)
	{
		MaterialParam* mp = NULL;
		ParamFindResult ret = find(paramName.AsString(), mp);
		if (ePFR_Succeed == ret)
		{
			switch(mp->GetType())
			{
			case Graphic::eMaterialParamVector:
				{
					MaterialParamVector* mpv = static_cast<MaterialParamVector*>(mp);
					mpv->SetValue(val.AsFloat4());
					break;
				}
			case Graphic::eMaterialParamFloat:
				{
					MaterialParamFloat* mpf = static_cast<MaterialParamFloat*>(mp);
					mpf->SetValue(val.AsFloat());
					break;
				}
			case Graphic::eMaterialParamMatrix:
				{
					MaterialParamMatrix* mpm = static_cast<MaterialParamMatrix*>(mp);
					mpm->SetValue(val.AsMatrix44());
					break;
				}
			default:
				{
					return ePFR_TypeError;
				}
			}
			_SetConstantParamOld(paramName, val);

		}
		return ret;
	}
	void MaterialInstance::_SetConstantParamOld(const ShaderParamString& paramName, const Util::String& val)
	{
		//[zhongdaohuan]这是为了兼容旧代码。m_scParams暂时还不可以取消。
		IndexT findtex = m_scParams.FindIndex( paramName );
		if ( findtex != InvalidIndex )
		{
			Util::String& scParam = m_scParams.ValueAtIndex( findtex );
			if ( scParam != val )
			{
				scParam = val;
			}
		}
		else
		{
			Util::String scParam;
			scParam = val;
			m_scParams.Add( paramName, scParam);
		}
	}


	bool MaterialInstance::UpateState()
	{
		bool bAllTextureLoaded = true;

		// asyn load texture
		for ( IndexT iTex = 0; iTex < m_texParams.Size(); ++ iTex )
		{
			TextureResInfo* texParam = m_texParams.ValueAtIndex( iTex );
			n_assert( texParam->GetResID().IsValid() );

			if (!texParam->GetHandle().IsValid())
			{
				bAllTextureLoaded = false;
				break;
			}
		}
		if ( bAllTextureLoaded )
		{
			m_dirty = false; 
			m_allLoaded = true;
		}

		return bAllTextureLoaded;
	}

	void MaterialInstance::AssignTextures()
	{
		for (SizeT i = 0; i < GetTextureParamCount(); ++i)
		{

			const ShaderParamString& name = GetTextureParamName(i);
			MaterialParamTexture* mp = NULL;
			if (ePFR_Succeed == findTexture(name.AsString(), mp))
			{			
				const GPtr<TextureResInfo>& res = GetTextureResInfo(i);
				if (res->GetHandle().IsValid())
				{
					mp->SetHandle(res->GetHandle());
					mp->SetStringValue(res->GetResID().AsString());
				}
			}
		}
		m_dirty = false;
	}

	void MaterialInstance::AssignTexture(const Resources::ResourceId& texID)
	{
		for (SizeT i = 0; i < GetTextureParamCount(); ++i)
		{

			const ShaderParamString& name = GetTextureParamName(i);
			MaterialParamTexture* mp = NULL;
			if (ePFR_Succeed == findTexture(name.AsString(), mp))
			{			
				const GPtr<TextureResInfo>& res = GetTextureResInfo(i);
				if (res->GetHandle().IsValid() && texID == res->GetResID())
				{
					mp->SetHandle(res->GetHandle());
					mp->SetStringValue(res->GetResID().AsString());

					break;
				}

			}
		}
		m_dirty = true;
	}
	//------------------------------------------------------------------------
	void MaterialInstance::CopyFrom(GPtr<MaterialInstance>& rht)
	{
		// base class copy
		const GPtr<Material>& base = rht.upcast<Material>();
		Clone(base);

		//
		m_shaderID	 = rht->m_shaderID;
		//m_materialID = rht->m_materialID;
		m_dirty = true;
		m_allLoaded = false;
		m_isbuild = false;

		m_texParams.Clear();
		m_scParams.Clear();
		m_renderState = 0;

		// copy texParams
		m_texParams = rht->m_texParams;

		// copy scParams
		m_scParams = rht->m_scParams;

		m_renderState = rht->m_renderState;

	}
	//------------------------------------------------------------------------
	void MaterialInstance::CopyParamList(GPtr<MaterialInstance>& rht)
	{
		_CloneParamList(rht->GetParamList());
		m_texParams = rht->m_texParams;
		m_scParams = rht->m_scParams;
		m_texParams = rht->m_texParams;
		m_scParams = rht->m_scParams;

	}
	//------------------------------------------------------------------------
	void MaterialInstance::_AssignDefaultToInstance()
	{
		const Graphic::MaterialParamList& mpl = GetParamList();
		SizeT MaterialParamCount = mpl.Size();
		for (SizeT paramIndex = 0;paramIndex < MaterialParamCount; paramIndex++)
		{
			Graphic::MaterialParam * pMatParam = mpl[paramIndex];

			Util::String ustrKey	= pMatParam->GetName();
			Util::String ustrValue	= pMatParam->GetStringValue();
			if (pMatParam->IsConstType())
			{
				_SetConstantParam(ustrKey, ustrValue);

			}
			else if ( pMatParam->IsTexType() )
			{
				SetTexture(ustrKey, ustrValue,0);
			} 
			else
			{
				n_assert(0);
			}
		}


	}

}