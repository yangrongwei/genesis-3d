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
#include "appframework/actor.h"
#include "app/basegamefeature/managers/timesource.h"
#include "foundation/math/matrix44.h"
#include "foundation/math/float2.h"
#include "foundation/math/float3.h"
#include "foundation/meshbuilder/parallelogrambuilder.h"
#include "sprite/spriteimage.h"
#include "sprite/spritepackage.h"
#include "sprite/spritemesh.h"
#include "spritebaserendercomponent.h"
#include "spriterenderobject.h"

namespace App
{
	using namespace Math;
	__ImplementClass(App::SpriteBaseRenderComponent, 'SBRC', App::RenderComponent)

		SpriteBaseRenderComponent::SpriteBaseRenderComponent()
	{

	}

	SpriteBaseRenderComponent::~SpriteBaseRenderComponent()
	{

	}

	void SpriteBaseRenderComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, MoveAfter);
		Super::SetupCallbacks();
	}

	void SpriteBaseRenderComponent::UpdateRenderLayer()
	{
		if (mRenderObject.isvalid())
		{
			mRenderObject->SetLayerID(mActor->GetLayerID());
		}
	}

	void SpriteBaseRenderComponent::OnActivate()
	{		
		if (!mRenderObject)
		{
			_BuildSimpleRenderObject();	
		}
		mRenderObject->SetTransform(mActor->GetWorldTransform());
		if (mVisible)
		{
			_AttachRenderObject();
		}


		Super::OnActivate();
	}

	void SpriteBaseRenderComponent::OnDeactivate()
	{
		if (IsActive())
		{
			_DeattachRenderObject();
		}
		Super::OnDeactivate();		
	}

	void SpriteBaseRenderComponent::OnDestroy()
	{
		if (IsActive())
		{
			_DeattachRenderObject();
		}
		mRenderableResUnitList.Clear();

		mSpriteInfo.Destroy();

		Super::OnDestroy();
	}
	void SpriteBaseRenderComponent::_OnMoveAfter()
	{
		n_assert(mActor)

		if (mRenderObject.isvalid())
		{
			mRenderObject->SetTransform(mActor->GetWorldTransform());
		}
	}

	void SpriteBaseRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		if ( IsActive() )
		{
			return;
		}
		const GPtr<SpriteBaseRenderComponent> rh = pComponent.downcast<SpriteBaseRenderComponent>();
		//mSpriteInfo.CopyFrom(rh->mSpriteInfo);
		Setup(rh->GetPackageID());
	}

	void SpriteBaseRenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		mSpriteInfo.GetReferenceResourceId(list);
		/// Do not get super's ReferenceResourceIds;
	}

	void SpriteBaseRenderComponent::Setup(const Resources::ResourceId& packId)
	{
		mSpriteInfo.Set(packId);
	}

	void SpriteBaseRenderComponent::SetVisible(bool bVis)
	{
		Super::SetVisible(bVis);
		if (IsActive())
		{
			if (mVisible)
			{
				_AttachRenderObject();
			}
			else
			{
				_DeattachRenderObject();
			}
		}
	}


	void SpriteBaseRenderComponent::_AttachRenderObject()
	{
		if (mRenderObject)
		{
			n_assert(mActor);
			mRenderObject->Attach(mActor->GetRenderScene());
		}
	}

	void SpriteBaseRenderComponent::_DeattachRenderObject()
	{
		if (mRenderObject)
		{
			n_assert(mActor);
			mRenderObject->Detach();
			//mRenderableResUnitList.Clear();
		}
	}

	void SpriteBaseRenderComponent::OnRenderSceneChanged()
	{
		if (mRenderObject.isvalid() && mRenderObject->Attached())
		{
			mRenderObject->Attach(mActor->GetRenderScene());
		}
	}

	void  SpriteBaseRenderComponent::_SetMaterial()
	{
		mRenderableResUnitList[0].SetResInfo(mSpriteInfo.GetMaterial());
	}

	void SpriteBaseRenderComponent::_BuildSimpleRenderObject()
	{	
		n_assert(NULL == mRenderObject);
		mRenderObject = RenderObjectType::Create();
		mRenderObject->SetOwner(this);
		mRenderObject->SetBoundingBox(mSpriteInfo.GetBoundingBox());
	}

	void SpriteBaseRenderComponent::_UpdateBoundingBox()
	{
		n_assert(NULL != mRenderObject);
		mRenderObject->SetBoundingBox(mSpriteInfo.GetBoundingBox());
		if (mActor)
		{
			mActor->_UpdateLocalBBox();
		}
	}

	bool SpriteBaseRenderComponent::_BuildSimpleRenderable()
	{
		if (mSpriteInfo.GetPrimitiveHandle().IsValid())
		{
			mRenderableResUnitList.Clear();
			mRenderableResUnitList.Append(Graphic::RenderbleResUnit());
			_SetMaterial();
			mRenderableResUnitList[0].ResetRenderable<RenderObjectType::RenderableType>();
			return true;
		};
		return false;
	}

	void SpriteBaseRenderComponent::_SetImage(const GPtr<Sprite::SpriteImage>& texture)
	{
		n_assert(texture.isvalid());
		if (0 == mRenderableResUnitList.Size())
		{
			if (!_BuildSimpleRenderable())
			{
				return;
			}
		}
#ifdef __SPRITE_CHECK__
		if (mSpriteInfo.CheckMaterial())
		{
			_SetMaterial();
		}
#endif
		mRenderableResUnitList[0].GetRenderableFast<RenderObjectType::RenderableType>()->SetImage(texture);
		
	}
	void SpriteBaseRenderComponent::_ClearRenderable()
	{
		mRenderableResUnitList.Clear();
	}

	const RenderBase::PrimitiveHandle& SpriteBaseRenderComponent::_getHandle() const
	{
		return mSpriteInfo.GetPrimitiveHandle();
	}

	Resources::ResourceId SpriteBaseRenderComponent::GetPackageID() const
	{
		return mSpriteInfo.GetPackID();
	}

	void SpriteBaseRenderComponent::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy /* = false */ )
	{
		///empty.
	}

	void SpriteBaseRenderComponent::SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave /* = true */ )
	{
		///empty.
	}

	void SpriteBaseRenderComponent::ModifyMaterialShaderID(IndexT iSubMesh, const Resources::ResourceId& shaderID)
	{
		///empty.
	}

	Math::bbox SpriteBaseRenderComponent::GetLocalBoundingBox()
	{
		return mSpriteInfo.GetBoundingBox();
	}

	bool SpriteBaseRenderComponent::Intersect( const Math::Ray& worldRay, Math::scalar& fout, Math::scalar fTolerance /*= N_TINY*/ )
	{
		if (GetActor())
		{
			const GPtr<Resources::SpritePackageResInfo> spri = mSpriteInfo.GetPackageResInfo();
			if (spri)
			{
				GPtr<Sprite::SpritePackage> sp = spri->GetPackage();
				if (sp && sp->GetMesh())
				{
					Math::matrix44 invMat = Math::matrix44::inverse(GetActor()->GetWorldTransform());
					Math::Ray localRay = worldRay.Tramsform( invMat );
					return sp->GetMesh()->Intersect(localRay, fout, fTolerance);
				}
			}
		}
		return false;
	}


}