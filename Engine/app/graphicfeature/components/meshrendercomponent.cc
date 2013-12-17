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
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicfeature/components/apprenderable.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "resource/meshres.h"
#include "resource/resourceserver.h"
#include "appframework/actor.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"

namespace App
{
	using namespace Resources;
	using namespace Graphic;
	using namespace RenderBase;

	__ImplementClass(App::MeshRenderComponent, 'MRCT', App::RenderComponent );

	//------------------------------------------------------------------------
	MeshRenderComponent::MeshRenderComponent()
		: mRenderObject()
		, mMeshLoading(false)
		, mLMTexParam(1.0f,1.0f,0.0f,0.0f)
		, mLMIndex (0xFFFF)
		, mLMDirty (true)
		, mLMScale(1.0)
		, m_bDrawDepth (true)
		, m_bUsedForResHotLoad(false)
	{
		mResourcePrior = 1;
		mMeshInfo.dirty = false;
	}
	//------------------------------------------------------------------------
	MeshRenderComponent::~MeshRenderComponent()
	{
		mPrimitiveResInfo = NULL;
		OnDestroy();
		n_assert( mRenderableResUnitList.IsEmpty() );

	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::OnActivate()
	{
		Super::OnActivate();
		if (mMeshInfo.dirty)
		{
			_LoadRenderData();
		}
		else
		{
			if (!mMeshLoading && mVisible)
			{
				_AttachRenderObject();
			}
		}

		n_assert( mActor );
		if( mActor  )
		{
			if (mRenderObject.isvalid())
			{
				mRenderObject->SetTransform(mActor->GetWorldTransform());
			}
		}
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::OnDeactivate()
	{
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}
		// deActive material
		Super::OnDeactivate();
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::OnDestroy()
	{
		//n_assert( !mRenderableAttached );
		if ( mPrimitive.IsValid() )
		{
			mPrimitive = RenderBase::PrimitiveHandle();
		}

		if ( mLMHandle.IsValid() )
		{
			mLMHandle = RenderBase::TextureHandle();
		}
		//mRenderableResUnitList.Clear();

		Super::OnDestroy();
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, MoveAfter);
		mActor->RegisterComponentCallback(this, BeginFrame);
		Super::SetupCallbacks();
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		 Super::HandleMessage(msg);//[zhongdaohuan]消息机制干掉了。
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::StandaloneRender(const GPtr<Graphic::Material>& customMat)
	{
		Graphic::RenderableResUnitArray::Iterator begin = mRenderableResUnitList.Begin();
		Graphic::RenderableResUnitArray::Iterator end = mRenderableResUnitList.End();
		Graphic::GraphicRenderer::ResetCache();
		while(begin != end)
		{
			Renderable* rdbl = begin->GetRenderable();
			if (rdbl)
			{
				GraphicRenderer::BeforeRender(rdbl, eCustomized, customMat.get_unsafe());
				mRenderObject->Render(rdbl, eCustomized, customMat.get_unsafe());
			}

			++begin;
		}
	}

	void MeshRenderComponent::SetMeshID(const Resources::ResourceId& meshID, Resources::Priority priority /* = 1 */, bool bUsedForResHotLoad )
	{
		if (mActor && mActor->PriorityDefinition())
		{
			priority = mActor->GetPriority();
		}
		mMeshLoading = true;
		mMeshInfo.meshID = meshID;
		mMeshInfo.priority = priority;
		mMeshInfo.dirty = true;
		m_bUsedForResHotLoad = bUsedForResHotLoad;
		if(Resources::ResourcePriority::Synchronization == priority)
		{
			_OnMeshDirty( bUsedForResHotLoad );
		}
	}


	void MeshRenderComponent::UpdateRenderLayer()
	{
		if (mRenderObject.isvalid())
		{
			mRenderObject->SetLayerID(mActor->GetLayerID());
		}
	}
	 
	void MeshRenderComponent::SetVisible(bool bVis)
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
	void MeshRenderComponent::_AttachRenderObject()
	{
		if (mRenderObject.isvalid())
		{
			n_assert(mActor);
			mRenderObject->Attach(mActor->GetRenderScene());
		}

	}

	void MeshRenderComponent::_DeattachRenderObject()
	{
		if (mRenderObject.isvalid())
		{
			n_assert(mActor);
			mRenderObject->Detach();
		}
	}

	void MeshRenderComponent::OnRenderSceneChanged()
	{
		if (mRenderObject.isvalid() && mRenderObject->Attached())
		{
			mRenderObject->Attach(mActor->GetRenderScene());
		}
	}

	void MeshRenderComponent::_OnMeshDirty(bool bDeleteRenderObject)
	{
		if (bDeleteRenderObject || (IsActive() && mVisible) )
		{
			_DeattachRenderObject();
		}
		_LoadRenderData();
	}

	//------------------------------------------------------------------------
	void MeshRenderComponent::_OnBeginFrame()
	{
		Super::_OnBeginFrame();

		// 更新阴影的状态
		_UpdateShadow();

		if (mMeshLoading)
		{	
			if (mMeshInfo.dirty)
			{
				_OnMeshDirty();
			}
			if (mPrimitiveResInfo.isvalid() && mPrimitiveResInfo->GetHandle().IsValid())//检测mesh是否已加载。
			{	 
				mActor->_UpdateLocalBBox();
				//mActor->SetLocalBoundingBox(mPrimitiveResInfo->GetRes().downcast<Resources::MeshRes>()->GetBoundingBox());
				_BuildRenderRes();
				if ( IsActive() && mVisible)
				{
					_AttachRenderObject();
				}
				mPrimitive = mPrimitiveResInfo->GetHandle();
				mMeshLoading = false;
#ifndef __SCRIPT_COMMIT__
				mActor->Check_OnWillRenderObject_Bind();
#endif
			}

			//异步加载后，需要更新那些在脚本初始化了的物体的包围盒
			_OnMoveAfter();
		}


	}
	void MeshRenderComponent::_OnWillRenderObjectEvent_Change(bool bind)
	{
		if (mRenderObject.isvalid())
		{
			mRenderObject->SetNeedCullCallBack(bind);
		}
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::_OnMoveAfter()
	{
		if( mActor  )
		{
			if (mRenderObject.isvalid())
			{
				mRenderObject->SetTransform(mActor->GetWorldTransform());
			}

		}
	}
	//------------------------------------------------------------------------
	void 
	MeshRenderComponent::_LoadRenderData()
	{
		n_assert( mMeshInfo.dirty );
		n_assert( mMeshInfo.meshID.IsValid() );
		n_assert( mMeshInfo.meshID.Value() != "" );
		//if( mActor)
		//{
		//	Resources::Priority actorLoadOrder = mActor->GetPriority();
		//	if (actorLoadOrder >= 0)
		//	{
		//		mMeshInfo.priority = actorLoadOrder;
		//	}
		//}
		
		mPrimitiveResInfo = ResourceManager::Instance()->CreatePrimitiveInfo(mMeshInfo.meshID, mMeshInfo.priority);
		mMeshInfo.dirty = false;
		mMeshLoading = true;
	}

	//------------------------------------------------------------------------
	void MeshRenderComponent::_SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable)
	{
		SubMesh* subMesh = meshRes->GetSubMesh(index);
		n_assert(subMesh);
		renderable->SetRenderInfo(
			subMesh->firstVertex, 
			subMesh->numVertex,
			subMesh->FirstIndex,
			subMesh->numIndex);
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::_BuildRenderObject()
	{
		//生成新的RenderObject
		if (!mRenderObject.isvalid())
		{
			const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();
			mRenderObject = RenderObjectType::Create();
			mRenderObject->SetOwner(this);		
		}
	}
	//------------------------------------------------------------------------
	void MeshRenderComponent::_BuildRenderRes()
	{
		n_assert( mActor );
		n_assert( mMeshLoading );
		const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();

		_BuildRenderObject();


		mRenderObject->SetTransform(mActor->GetWorldTransform());
		mRenderObject->SetBoundingBox(meshRes->GetBoundingBox());

		UpdateRenderLayer();

		// 生成新的renderable
		int sub_count = meshRes->GetSubMeshCount();
		int mat_count = mRenderableResUnitList.Size();
//		int count = n_min(sub_count, mat_count);

		if(m_bUsedForResHotLoad)
		{
			//热加载时，如果材质数量大于1，需要把多出来的材质记录下来，在恢复的时候重新载入

			// 填充材质列表
			for ( IndexT index = mat_count; index < sub_count; ++index )
			{
				IndexT foundindex = mDeattachedMatList.FindIndex(index);
				if(foundindex != InvalidIndex)
				{
					SetMaterialID(index, mDeattachedMatList[index], false);
				}
				else
				{
					SetMaterialID(index,"sys:meshRenderDefault.material", false);
				}
			}

			mDeattachedMatList.Clear();

			// 删除不在使用的材质
			for (int i = mat_count - 1 ; i >= sub_count; --i)
			{
				mDeattachedMatList.Add(i,GetMaterialID(i));
				mRenderableResUnitList.EraseIndex(i);
			}
		}
		else
		{
			mDeattachedMatList.Clear();

			// 填充材质列表
			for ( IndexT index = mat_count; index < sub_count; ++index )
			{
				SetMaterialID(index,"sys:meshRenderDefault.material", false);
			}

			// 删除不在使用的材质
			for (int i = mat_count - 1 ; i >= sub_count; --i)
			{
				mRenderableResUnitList.EraseIndex(i);
			}
		}

		for ( IndexT index = 0; index < sub_count; ++index )
		{
			RenderObjectType::RenderableType* renderable = mRenderableResUnitList[index].ResetRenderable<RenderObjectType::RenderableType>();
			_SetRenderable(meshRes, index, renderable);

			if (!m_bDrawDepth)
			{
				Graphic::Renderable::Mark mark = renderable->GetMark();
				mark = (Graphic::Renderable::Mark)(mark & ~Graphic::Renderable::GenDepth);
				renderable->SetMark(mark);
			}
		}
		
	}	

	//------------------------------------------------------------------------
	void MeshRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		if ( IsActive() )
		{
			OnDeactivate();
		}

		//n_assert( !mRenderableAttached );
		if ( mPrimitive.IsValid() )
		{
			mPrimitive = RenderBase::PrimitiveHandle();
		}
		mRenderableResUnitList.Clear();

		GPtr<MeshRenderComponent> pSource = pComponent.downcast<MeshRenderComponent>();
		if ( pSource->GetMeshID().IsValid() )
		{
			SetMeshID(pSource->GetMeshID());
			SetDrawDepth(pSource->IsDrawDepth());
		    Super::CopyFrom(pComponent);
		}
		else
		{
			mMeshLoading = false;
			mMeshInfo.dirty = false;
		}

		SetLMTexParam( pSource->GetLMTexParam() );
		SetLMIndex( pSource->GetLMIndex() );
		SetLMScale( pSource->GetLMScale() );
		SetLMDirty();
	}

	void MeshRenderComponent::SetupAllResource()
	{
		if (mActor->PriorityUndefinition())
			return;
		Super::SetupAllResource();
		SetMeshID(GetMeshID(),mActor->GetPriority());
	}

	bool MeshRenderComponent::IsAllResourceLoaded()
	{
		if (Super::IsAllResourceLoaded())
		{
			return !mMeshLoading;
		}
		else
		{
			return false;
		}
		
	}

	//-------------------------------------------------------------------------
	void MeshRenderComponent::UpdateTransformMatrix()
	{
		//[zhongdaohuan][render_obj] 开发renderobject分支的时候，需要重写这里的逻辑。
		//if ( !mActor || !mSimpleShape.isvalid())
		//{
		//	return;
		//}


		//const Math::bbox& localBB = mActor->GetLocalBoundingBox();
		//Math::vector vScale(localBB.pmax.x() - localBB.pmin.x(), localBB.pmax.y() - localBB.pmin.y(), localBB.pmax.z() - localBB.pmin.z());
		//vScale *= mActor->GetWorldScale();

		//const Math::quaternion quat = mActor->GetWorldRotation();	

		////translate
		//const Math::bbox& bbLocal = mActor->GetLocalBoundingBox();
		//Math::float4 translate = bbLocal.center();	
		//translate = mActor->GetWorldRotation() * (mActor->GetWorldScale() * translate);
		//
		//translate += mActor->GetWorldPosition();
		//
		//Math::matrix44 mat44 = Math::matrix44::transformation(
		//	vScale,
		//	quat,
		//	translate);

		//mSimpleShape->SetTransform(mat44);	

	}


	//------------------------------------------------------------------------------
	void MeshRenderComponent::_UpdateShadow()
	{

		bool isReceiveShadow = this->GetReceiveShadow();
		bool isCastShadow = this->GetCastShadow();

		if ( mRenderObject.isvalid() )
		{
			mRenderObject->SetReceiveShadow( isReceiveShadow );
			mRenderObject->SetCastShadow( isCastShadow );
		}
	}

	void MeshRenderComponent::SetDrawDepth(bool bDraw)
	{
		m_bDrawDepth = bDraw;


		if (!m_bDrawDepth)
		{
			for (IndexT i = 0; i < mRenderableResUnitList.Size(); ++i)
			{
				Graphic::Renderable* pRenderable = mRenderableResUnitList[i].GetRenderable();

				if (pRenderable != NULL)
				{
					Graphic::Renderable::Mark mark = pRenderable->GetMark();
					mark = (Graphic::Renderable::Mark)(mark & ~Graphic::Renderable::GenDepth);
					pRenderable->SetMark(mark);
				}

			}
		}

	}
	//------------------------------------------------------------------------------
	void MeshRenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		if( IsLMTextureHandleValid() )
		{
			LightmapName name;
			LightmapSetting::GetInstance().GetLightmap( mLMIndex, name);

			if ( name.IsValid() )
				list.Append(Resources::ReferenceResource(name, Resources::RR_Unknown));
		}
		list.Append(Resources::ReferenceResource(mMeshInfo.meshID, Resources::RR_Unknown));
		Super::GetReferenceResourceId(list);
	}

	Math::bbox MeshRenderComponent::GetLocalBoundingBox()
	{
		if (mPrimitiveResInfo.isvalid() && mPrimitiveResInfo->GetHandle().IsValid())
		{	 
			return mPrimitiveResInfo->GetRes().downcast<Resources::MeshRes>()->GetBoundingBox();
		}
		return Math::bbox(Math::point(0,0,0), Math::point(0,0,0));
	}

}


