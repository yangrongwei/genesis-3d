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
#include "resource/resinfo.h"
#include "resource/resourcemanager.h"
#include "resource/materialres.h"
#include "spritepackageres.h"
#include "sprite/spritepackage.h"

namespace Resources
{
	__ImplementClass( baseResInfo, 'baRI',Core::RefCounted);

	__ImplementClass( TextureResInfo, 'teRI',baseResInfo);

	__ImplementClass( PrimitiveResInfo, 'prRI',baseResInfo);

	__ImplementClass( MaterialResInfo, 'shRI',baseResInfo);

	__ImplementClass( SpritePackageResInfo, 'SPPP',baseResInfo);

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	bool baseResInfo::Compile()
	{
		if ( IsCompiled() )
		{
			return true;
		}

		if ( IsLoaded() )
		{
			OnCompile();
			SetNeedReCompile(false);
			return IsCompiled();
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	void PrimitiveResInfo::OnCompile()
	{
		const GPtr<MeshRes>& meshRes = resData.downcast<Resources::MeshRes>();
		n_assert(meshRes);
		RenderBase::PrimitiveHandle h = App::GraphicObjectManager::Instance()->CreatePrimitiveHandle(meshRes);
		SetHandle(h);


	}
	//------------------------------------------------------------------------
	void PrimitiveResInfo::Discard()
	{
		if ( primHandle.IsValid() )
		{
			App::GraphicObjectManager::Instance()->DiscardPrimitiveHandle(primHandle);
			primHandle = RenderBase::PrimitiveHandle();
		}

		Super::Discard();
	}
	//------------------------------------------------------------------------
	void PrimitiveResInfo::AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes)
	{
		if ( defaultRes )
		{
			GPtr<PrimitiveResInfo> priDefault = defaultRes.downcast<PrimitiveResInfo>();
			n_assert(priDefault);
			SetHandle( priDefault->GetHandle() );
			defaultRes->GetRes()->SetResourceId(Resources::ResourceManager::DefaultMeshID);	//default在Update的时候名字会改变。
		}
	}
	//------------------------------------------------------------------------
	void TextureResInfo::OnCompile()
	{
		const GPtr<ImageRes>& imageRes = resData.downcast<Resources::ImageRes>();
		n_assert(imageRes);
		RenderBase::TextureHandle h = App::GraphicObjectManager::Instance()->CreateTextureHandle(imageRes);
		SetHandle(h);

#ifndef __GENESIS_EDITOR__
		imageRes->UnLoad();
#endif

	}
	//------------------------------------------------------------------------
	void TextureResInfo::Discard()
	{
		if ( texHandle.IsValid() )
		{
			App::GraphicObjectManager::Instance()->DiscardTextureHandle(texHandle);
			texHandle = RenderBase::TextureHandle();
		}
		Super::Discard();
	}
	//------------------------------------------------------------------------
	void TextureResInfo::AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes)
	{
		if ( defaultRes )
		{
			GPtr<TextureResInfo> texDefault = defaultRes.downcast<TextureResInfo>();
			n_assert(texDefault);
			SetHandle( texDefault->GetHandle() );
		}
	}
	//------------------------------------------------------------------------
	void MaterialResInfo::OnCompile()
	{
		const GPtr<MaterialRes>& res = resData.downcast<Resources::MaterialRes>();
		n_assert(res);
		n_assert(res->GetMaterialInstance().isvalid());		
		SetHandle(res->GetMaterialInstance());
	}
	//------------------------------------------------------------------------
	void MaterialResInfo::AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes)
	{
		if ( defaultRes )
		{
			GPtr<MaterialResInfo> priDefault = defaultRes.downcast<MaterialResInfo>();
			n_assert(priDefault);
			SetHandle( priDefault->GetHandle() );
		}
	}
	//------------------------------------------------------------------------
	ResInfoContainer::ResInfoContainer()
	{
		m_resInfoType = NULL;
		m_resDataType = NULL;
	}
	//------------------------------------------------------------------------


	GPtr<Sprite::SpritePackage> SpritePackageResInfo::GetPackage() const
	{
		return GetRes().downcast<Resources::SpritePackageRes>()->GetSpritePackage();
	}
}