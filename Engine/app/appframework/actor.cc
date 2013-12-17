/****************************************************************************
Copyright (c) 2002, Radon Labs GmbH
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
#include "math/transform44.h"
#include "core/factory.h"
#include "app/application.h"
#include "debug/debugserver.h"
#include "appframework/actormanager.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "terrainfeature/components/TerrainRenderComponent.h"
#include "vegetationfeature/components/vegetationrendercomponent.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicfeature/components/animationcomponent.h"
#include "graphicfeature/components/skeletoncomponent.h"
#include "graphicfeature/components/skinnedmeshrendercomponent.h"
#include "scriptfeature/inc/script_component.h"
#include "graphicfeature/components/rendercomponent.h"
#include "graphicfeature/components/spriterendercomponent.h"
#ifndef __PHYSX_COMMIT__
#include "physXfeature/PhysicsBodyComponent.h"
#endif


namespace App
{
__ImplementClass(App::Actor, 'GACT', Core::RefCounted);

uint Actor::s_fastIdCounter = 0;

const GPtr<Actor> Actor::NullActor;
//------------------------------------------------------------------------------
/**
*/
Actor::Actor() :
    mFastId(++s_fastIdCounter),
	mName("NoName"),
    mActivated(false),
	mActiveControl(false),
	mTemplateName(""),
	mIsLinkTemplate(false),
	mLayerID(eSL_Defualt),
	mTagID(1),
	mDirtyLocaTrans(false),
	mDirtyWorldBB(false),
	mDirtyWorldTrans(false),
	mLocalPosition(0,0,0),
	mWorldPosition(0,0,0),
	mLocalScale(1,1,1),
	mWorldScale(1,1,1),
	mLocalRotation(0,0,0,1),
	mWorldRotation(0,0,0,1),
	mParent(NULL),
	mComponentsCommSign(eCCS_None),
	mVisible(true),
#ifdef __GENESIS_EDITOR__
	mQueryMask(0),
	mFrozen(false),
	mLocked(false),
#endif
	mEditorFlag(0), 
	mPriority(ResourcePriority::Undefinition)
{
	mGuid.Generate();
	mLocalBB.set(Math::point(0,0,0), Math::point(0,0,0));
	this->mCallbackComponents.SetSize(Component::NumCallbackTypes);
    this->mDispatcher = Messaging::Dispatcher::Create();
	ActorManager::Instance()->_AddAllCreatedManager(this);
}

//------------------------------------------------------------------------------
/**
*/
Actor::~Actor()
{
    n_assert(!this->mActivated);
	n_assert(mComponents.Size()==0);
    this->mDispatcher = 0;
}

//------------------------------------------------------------------------------
Graphic::RenderScene*
Actor::GetRenderScene() const
{
	if (mParent)
	{
		return mParent->GetRenderScene();
	}
	else
	{
		return SceneScheduleManager::Instance()->_GetMainRenderScene();
	}
}

//------------------------------------------------------------------------------
bool
Actor::IsDestory() const
{
	return ( GetRefCount() == ActorManager::ActorDeadRefCount ) && !IsActive();
}
//------------------------------------------------------------------------
void 
Actor::_Destory(bool forceShutDown )
{
	/// 系统关闭时的快速销毁流程
	if ( forceShutDown )
	{
		/// 系统
		_CleanupAllComponents();
		mParent = NULL;
		mChildren.Clear();
		mActivated = false;
		return;
	}

	/// 正常消耗流程

	if ( !IsDestory() )
	{
		return;
	}

	// 仅仅需要断开和孩子节点的联系即可。 孩子节点可以被删除的时候，被自动被垃圾搜集器回收
	SizeT count = mChildren.Size();
	for ( IndexT i = 0; i < count; ++i )
	{
		GPtr<Actor>& child = mChildren[i];
		n_assert( child.isvalid() );
		child->_SetParentImpl( NULL );
	}
	mChildren.Clear();

	// 清除所有的Component
	_CleanupAllComponents();
}
//------------------------------------------------------------------------
void Actor::SetLayerID(LayerID id)
{
	n_assert(id < 32);
	n_assert(0 <= id);
	mLayerID = id;
	IndexT i;
	for (i = 0; i < this->mComponents.Size(); ++i)
	{
		mComponents[i]->UpdateRenderLayer();
	}
}

void 
Actor::SetTransform( const Math::matrix44& m )
{
	_UpdateLocalTransform();
	if ( mLocaTrans != m )
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		mLocaTrans = m;

		Math::float4 pos,scale;
		Math::quaternion rot;
		mLocaTrans.decompose(scale,rot,pos);

		mLocalPosition = Math::vector(pos);
		mLocalRotation = rot;
		mLocalScale = scale;

		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}
	}

	mDirtyLocaTrans = false;
}
//------------------------------------------------------------------------
void
Actor::SetWorldTransform( const Math::matrix44& m )
{
	if ( mWorldTrans == m )
	{
		return;
	}

	if ( IsActive() )
	{
		OnMoveBefore();
	}

	mWorldTrans = m;
	mWorldTrans.decompose(mWorldScale, mWorldRotation, mWorldPosition);
	if (mParent)
	{
		Math::matrix44 pw = mParent->GetWorldTransform();
		Math::matrix44 inversepw = Math::matrix44::inverse(pw);
		mLocaTrans = Math::matrix44::multiply( inversepw ,mWorldTrans );
		mLocaTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
		mLocaTrans.decompose(mLocalScale,mLocalRotation, mLocalPosition);
	}
	else
	{
		// Root node, no parent
		mLocaTrans = mWorldTrans;
		mLocalRotation = mWorldRotation;
		mLocalPosition = mWorldPosition;
		mLocalScale = mWorldScale;
	}

	/*将当前actor和所有子actor的world transform标记为dirty，
	这样会根据mLocalScale,mLocalRotation, mLocalPosition重新计算world transform*/
	_DirtyWorldTransform();

	/*由于的上面的if语句中已经计算了当前actor的world transform，
	而且当前actor的mLocalScale,mLocalRotation, mLocalPosition由于是
	对非仿射矩阵执行decompose操作，存在误差，如果再根据这三个值重新计算
	当前actor的world transform也会出现误差，所以要把mDirtyWorldTrans
	设置为false，这样就不会重新计算当前actor的world transform*/
	mDirtyWorldTrans = false;

	if ( IsActive() )
	{
		OnMoveAfter();
	}
}
//------------------------------------------------------------------------
void 
Actor::SetTransform(const Math::vector& pos,  const Math::quaternion& rot, const Math::vector& scale)
{
	//if ( mLocalPosition != pos ||  this->mLocalRotation != rot ||  this->mLocalScale != scale )
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		this->mLocalPosition = pos;
		this->mLocalRotation = rot;
		this->mLocalScale = scale;

		mDirtyLocaTrans = true;
		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}
	}
}
//------------------------------------------------------------------------------
/**
*/ 
void
Actor::SetPosition(const Math::vector& pos)
{
	if ( mLocalPosition != pos )
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		this->mLocalPosition = pos;

		mDirtyLocaTrans = true;
		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}
	}
}
//------------------------------------------------------------------------------
/**
*/ 
void
Actor::SetRotation(const Math::quaternion& rot)
{
	if ( this->mLocalRotation != rot )
	{		
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		this->mLocalRotation = rot;

		mDirtyLocaTrans = true;
		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}
	}
}
//------------------------------------------------------------------------------
/**
*/
void
Actor::SetScale(const Math::vector& scale)
{
	if ( this->mLocalScale != scale )
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		this->mLocalScale = scale;

		mDirtyLocaTrans = true;
		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}

	}
}
//------------------------------------------------------------------------
const Math::matrix44& 
Actor::GetTransform() const
{
	_UpdateLocalTransform();
	return mLocaTrans;
}
/**
	设置Actor的世界空间坐标,更新其子Actor的变换矩阵与AABB更新标志
	并更新其在父空间的坐标(mLocalPosition)
*/
void
Actor::SetWorldPosition(const Math::vector& pos)
{
	if (mWorldPosition != pos)
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		mWorldPosition = pos;
		mWorldTrans = Math::matrix44::transformation(mWorldScale, mWorldRotation, mWorldPosition);
 		if ( NULL != mParent )
 		{
			const Math::matrix44& pw =  mParent->GetWorldTransform();
			Math::matrix44 inversepw = Math::matrix44::inverse(pw);
			mLocaTrans = Math::matrix44::multiply( inversepw ,mWorldTrans  ); 
			mLocaTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
			mLocaTrans.decompose(mLocalScale,mLocalRotation, mLocalPosition);
		}
		else
		{
			// 如果没有父节点，相对父空间位置即相对于世界空间的位置
			mLocaTrans = mWorldTrans;
			mLocalPosition = mWorldPosition;
		}

		/*将当前actor和所有子actor的world transform标记为dirty，
		这样会根据mLocalScale,mLocalRotation, mLocalPosition重新计算world transform*/
		_DirtyWorldTransform();

		/*由于的上面的if语句中已经计算了当前actor的world transform，
		而且当前actor的mLocalScale,mLocalRotation, mLocalPosition由于是
		对非仿射矩阵执行decompose操作，存在误差，如果再根据这三个值重新计算
		当前actor的world transform也会出现误差，所以要把mDirtyWorldTrans
		设置为false，这样就不会重新计算当前actor的world transform*/
		mDirtyWorldTrans = false;

		if ( IsActive() )
		{
			OnMoveAfter();
		}

		// dirty child
		SizeT numActor = mChildren.Size();
		for ( IndexT i = 0; i < numActor; ++i )
		{
			mChildren[i]->_DirtyWorldTransform();
		}

		mDirtyWorldBB = true;
	}
}
//------------------------------------------------------------------------
void
Actor::SetWorldRotation(const Math::quaternion& rot)
{
	if (mWorldRotation != rot)
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		mWorldRotation = rot;
		mWorldTrans = Math::matrix44::transformation(mWorldScale, mWorldRotation, mWorldPosition);
		if ( NULL != mParent )
		{
			const Math::matrix44& pw =  mParent->GetWorldTransform();
			Math::matrix44 inversepw = Math::matrix44::inverse(pw);
			mLocaTrans = Math::matrix44::multiply( inversepw ,mWorldTrans  );
			mLocaTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
			mLocaTrans.decompose(mLocalScale,mLocalRotation, mLocalPosition);
		}
		else
		{
			// 如果没有父节点，相对父空间旋转即相对于世界空间的旋转
			mLocaTrans = mWorldTrans;
			mLocalRotation = mWorldRotation;
		}

		/*将当前actor和所有子actor的world transform标记为dirty，
		这样会根据mLocalScale,mLocalRotation, mLocalPosition重新计算world transform*/
		_DirtyWorldTransform();

		/*由于的上面的if语句中已经计算了当前actor的world transform，
		而且当前actor的mLocalScale,mLocalRotation, mLocalPosition由于是
		对非仿射矩阵执行decompose操作，存在误差，如果再根据这三个值重新计算
		当前actor的world transform也会出现误差，所以要把mDirtyWorldTrans
		设置为false，这样就不会重新计算当前actor的world transform*/
		mDirtyWorldTrans = false;

		if ( IsActive() )
		{
			OnMoveAfter();
		}

		// dirty child
		SizeT numActor = mChildren.Size();
		for ( IndexT i = 0; i < numActor; ++i )
		{
			mChildren[i]->_DirtyWorldTransform();
		}

		mDirtyWorldBB = true;
	}
}
//------------------------------------------------------------------------
void 
Actor::SetWorldScale(const Math::vector& scale)
{
	if (mWorldScale != scale)
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}

		mWorldScale = scale;
		mWorldTrans = Math::matrix44::transformation(mWorldScale, mWorldRotation, mWorldPosition);
		if ( NULL != mParent )
		{
			const Math::matrix44& pw =  mParent->GetWorldTransform();
			Math::matrix44 inversepw = Math::matrix44::inverse(pw);
			mLocaTrans = Math::matrix44::multiply( inversepw ,mWorldTrans );
			mLocaTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
			mLocaTrans.decompose(mLocalScale,mLocalRotation, mLocalPosition);
		}
		else
		{
			// 如果没有父节点，相对父空间缩放即相对于世界空間的缩放
			mLocaTrans = mWorldTrans;
			mLocalScale = mWorldScale;

		}

		/*将当前actor和所有子actor的world transform标记为dirty，
		这样会根据mLocalScale,mLocalRotation, mLocalPosition重新计算world transform*/
		_DirtyWorldTransform();

		/*由于的上面的if语句中已经计算了当前actor的world transform，
		而且当前actor的mLocalScale,mLocalRotation, mLocalPosition由于是
		对非仿射矩阵执行decompose操作，存在误差，如果再根据这三个值重新计算
		当前actor的world transform也会出现误差，所以要把mDirtyWorldTrans
		设置为false，这样就不会重新计算当前actor的world transform*/
		mDirtyWorldTrans = false;

		if ( IsActive() )
		{
			OnMoveAfter();
		}

		// dirty child
		SizeT numActor = mChildren.Size();
		for ( IndexT i = 0; i < numActor; ++i )
		{
			mChildren[i]->_DirtyWorldTransform();
		}

		mDirtyWorldBB = true;
	}
}
//------------------------------------------------------------------------
const Math::quaternion& 
Actor::GetWorldRotation(void) const
{
	_UpdateWolrdTransform();
	return mWorldRotation;
}
//------------------------------------------------------------------------
const Math::vector& 
Actor::GetWorldPosition(void) const
{
	_UpdateWolrdTransform();
	return mWorldPosition;
}
//------------------------------------------------------------------------
const Math::vector& 
Actor::GetWorldScale(void) const
{
	_UpdateWolrdTransform();

	//非常HACK的方式临时解决现有ACTOR导致的scale为NAN的问题
	if (Math::n_isNaN(mWorldScale.x()))
	{
		mWorldScale.x() = 0.0f;
	}

	if (Math::n_isNaN(mWorldScale.y()))
	{
		mWorldScale.y() = 0.0f;
	}

	if (Math::n_isNaN(mWorldScale.z()))
	{
		mWorldScale.z() = 0.0f;
	}

	return mWorldScale;
}
//------------------------------------------------------------------------
const Math::matrix44& 
Actor::GetWorldTransform(void) const
{
	_UpdateWolrdTransform();
	return mWorldTrans;
}
//------------------------------------------------------------------------
const Math::matrix44 
	Actor::GetWorldTranslateRotation(void) const
{
	_UpdateWolrdTransform();
	Math::quaternion rotQuat = GetWorldRotation();
	Math::vector vScale(1.f,1.f,1.f);
	Math::vector vPos = GetWorldPosition();

	const Math::matrix44 mat44 = Math::matrix44::transformation(vScale,rotQuat,vPos);
	return mat44;
}
//------------------------------------------------------------------------
const Math::matrix44 
	Actor::GetWorldTranslateNoScale(void) const
{
	_UpdateWolrdTransform();
	Actor* parent = mParent;
	Math::quaternion sumRotation;
	Math::quaternion parentRotation;

	sumRotation = mLocalRotation;

	while(parent)
	{
		parentRotation = parent->GetRotation();
		sumRotation = Math::quaternion::multiply(parentRotation,sumRotation);
		parent = parent->mParent;
	}

	Math::vector vScale(1.f,1.f,1.f);
	Math::vector vPos = GetWorldPosition();
	const Math::matrix44 mat44 = Math::matrix44::transformation(vScale,sumRotation,vPos);
	return mat44;
}
//------------------------------------------------------------------------
const Math::quaternion 
	Actor::GetWorldRotationNoScale(void) const
{
	_UpdateWolrdTransform();
	Actor* parent = mParent;
	Math::quaternion sumRotation;
	Math::quaternion parentRotation;

	sumRotation = mLocalRotation;

	while(parent)
	{
		parentRotation = parent->GetRotation();
		sumRotation = Math::quaternion::multiply(parentRotation,sumRotation);
		parent = parent->mParent;
	}

	return sumRotation;
}
//------------------------------------------------------------------------
const Math::bbox& 
Actor::GetWorldBoundingBox(void) const
{
	if ( mDirtyWorldBB )
	{
		mWorldBB = mLocalBB;
		const Math::matrix44& m = GetWorldTransform();
		mWorldBB.transform(m);
		mDirtyWorldBB = false;
	}
	return mWorldBB;
}
//------------------------------------------------------------------------
Math::bbox 
Actor::GetWorldBoundingBoxWithChild(void) const
{
	Math::bbox bb;
	bb.begin_extend();
	bb.extend( GetWorldBoundingBox() );
	for ( IndexT i = 0; i < mChildren.Size(); ++i )
	{
		bb.extend( mChildren[i]->GetWorldBoundingBoxWithChild() );
	}
	bb.end_extend();
	return bb;
}
//------------------------------------------------------------------------
/** 
	Local BB 变化的时候，暂时不向其他component发出消息。
	1、如果是其他component的数据变化导致localBB变化，其他componet应该会发出专门的消息
	2、如果是外部设置的，暂时想不出有哪个组件需要响应
*/
void 
Actor::SetLocalBoundingBox(const Math::bbox& bb)
{
	mLocalBB = bb;
	mDirtyWorldBB = true;
}
#ifndef __SCRIPT_COMMIT__
//------------------------------------------------------------------------------
void
Actor::Check_OnRenderPostEffect_Bind()
{
	if (IsComponentsCommSignOpen(eCCS_OnRenderPostEffect))
	{
		const GPtr<ScriptComponent>& sc = FindComponent<ScriptComponent>();
		const GPtr<CameraComponent>& cc = FindComponent<CameraComponent>();
		if (sc->IsActive() && cc.isvalid() && cc->IsActive())
		{
			sc->BindOnRenderPostEffect(cc);
		}
	}
}
//------------------------------------------------------------------------------
void
Actor::Check_OnRenderPostEffect_Unbind()
{
	if (IsComponentsCommSignOpen(eCCS_OnRenderPostEffect))
	{
		const GPtr<ScriptComponent>& sc = FindComponent<ScriptComponent>();
		const GPtr<CameraComponent>& cc = FindComponent<CameraComponent>();
		if (sc.isvalid() && cc.isvalid())
		{
			sc->UnbindOnRenderPostEffect(cc);
		}
	}
}
//------------------------------------------------------------------------------
void
Actor::Check_OnWillRenderObject_Bind()
{
	if (IsComponentsCommSignOpen(eCCS_OnWillRenderObject))
	{
		const GPtr<ScriptComponent>& sc = FindComponent<ScriptComponent>();
		const GPtr<RenderComponent>& rc = FindComponent<RenderComponent>();
		if (sc->IsActive() && rc.isvalid() && rc->IsAllResourceLoaded())
		{
			sc->BindOnWillRenderObject(rc);
		}

	}
}

//------------------------------------------------------------------------------
void
Actor::Check_OnWillRenderObject_Unbind()
{
	if (IsComponentsCommSignOpen(eCCS_OnWillRenderObject))
	{
		const GPtr<RenderComponent>& rc = FindComponent<RenderComponent>();
		if (rc.isvalid())
		{
			rc->OnWillRenderObjectEvent_Unbind();
		}
	}
}
#endif
void
Actor::Check_Animation(AnimationComponent* animation)
{
	n_assert(animation->GetActor());
	Children::Iterator it = animation->GetActor()->mChildren.Begin();
	Children::Iterator end = animation->GetActor()->mChildren.End();
	while(it != end)
	{
		for (int i = 0; i < (*it)->mComponents.Size(); ++i)
		{
			GPtr<Component>& com = (*it)->mComponents[i];
			if (com->IsA(SkinnedMeshRenderComponent::RTTI))
			{
				com.downcast<SkinnedMeshRenderComponent>()->SetAnimation(animation);
			}
		}
		++it;
	}
}
void
Actor::Check_Skeleton(SkeletonComponent* skeleton)
{
	n_assert(skeleton->GetActor());
	GPtr<SkinnedMeshRenderComponent> skin = skeleton->GetActor()->FindComponent<SkinnedMeshRenderComponent>();
	if (skin.isvalid())
	{
		skin->SetSkeleton(skeleton);
	}
}
void
Actor::Check_Skin(SkinnedMeshRenderComponent* skin)
{
	if (skin->GetActor() && skin->GetActor()->GetParent())
	{
		GPtr<SkeletonComponent> skeleton = skin->GetActor()->FindComponent<SkeletonComponent>();
		GPtr<AnimationComponent> animation = skin->GetActor()->GetParent()->FindComponent<AnimationComponent>();

		if (skeleton.isvalid())
		{
			skin->SetSkeleton(skeleton.get_unsafe());
		}

		skin->SetAnimation(animation.get_unsafe());
	}
	
	
}
//------------------------------------------------------------------------------
void
Actor::_CleanupAllComponents()
{
    while (this->mComponents.Size() > 0)
    {
        this->RemoveComponent(this->mComponents.Back());
    }
}
//------------------------------------------------------------------------------
void
Actor::_ActivateAllComponents()
{
    IndexT i;
    SizeT num = this->mComponents.Size();
    for (i = 0; i < num; ++i)
    {
        const GPtr<Component>& pComponent = this->mComponents[i];
		n_assert (!pComponent->IsActive());
		_ActiveComponent( pComponent );
    }
}
//------------------------------------------------------------------------------
void
Actor::_DeactivateAllComponents()
{
    IndexT i;
    for (i = 0; i < Component::NumCallbackTypes; ++i)
    {
        this->mCallbackComponents[i].Clear();
    }

    for (i = 0; i < this->mComponents.Size(); ++i)
    {
		n_assert(mComponents[i]->IsActive());

        //n_assert(this->mComponents[i]->IsActive());

#if NEBULA3_ENABLE_PROFILING
		Util::String timerName(this->mComponents[i]->GetRtti()->GetName() + ".OnDeactivate");
		this->mComponentDeactivateDebugTimer[timerName]->StartAccum();        
#endif

        this->mDispatcher->RemovePort(this->mComponents[i].upcast<Messaging::Port>());
        this->mComponents[i]->OnDeactivate();

#if NEBULA3_ENABLE_PROFILING
		this->mComponentDeactivateDebugTimer[timerName]->StopAccum();
		_RemoveComponentTimer( this->mComponents[i]->GetRtti() );
#endif

    }
}
//------------------------------------------------------------------------
void 
Actor::_ActiveComponent( const GPtr<Component>& pComponent )
{
	n_assert( !pComponent->IsActive() );

#if NEBULA3_ENABLE_PROFILING
	_AttachComponentTimer( pComponent->GetRtti() );
	Util::String timerName(pComponent->GetRtti()->GetName() + ".OnActivate");
	this->mComponentActivateDebugTimer[timerName]->StartAccum();        
#endif

	 pComponent->SetupAcceptedMessages();
	 pComponent->SetupCallbacks();
	 mDispatcher->AttachPort(pComponent.upcast<Messaging::Port>());
	 pComponent->OnActivate();      

#if NEBULA3_ENABLE_PROFILING
	this->mComponentActivateDebugTimer[timerName]->StopAccum();
#endif

}
//------------------------------------------------------------------------
void 
Actor::_DeactiveComponent( const GPtr<Component>& pComponent )
{
#if NEBULA3_ENABLE_PROFILING
	Util::String timerName(pComponent->GetRtti()->GetName() + ".OnDeactivate");
	this->mComponentDeactivateDebugTimer[timerName]->StartAccum();        
#endif

	SizeT numCallBack = mCallbackComponents.Size();
	for ( IndexT indexCallBack = 0; indexCallBack < numCallBack; ++indexCallBack )
	{
		Util::Array< GPtr<Component> > & arrayList = mCallbackComponents[indexCallBack];
		IndexT findIndex = arrayList.FindIndex( pComponent );
		if ( InvalidIndex != findIndex)
		{
			arrayList.EraseIndex( findIndex );
		}
	}

	if (mDispatcher->HasPort(pComponent.upcast<Messaging::Port>()))
	{
		this->mDispatcher->RemovePort( pComponent.upcast<Messaging::Port>() );
	}
	
	if (pComponent->IsActive())
	{
		pComponent->OnDeactivate();
	}

#if NEBULA3_ENABLE_PROFILING
	this->mComponentDeactivateDebugTimer[timerName]->StopAccum();
	_RemoveComponentTimer( pComponent->GetRtti() );
#endif

}
//------------------------------------------------------------------------
void 
Actor::Active(bool forceActiveControlofChild)
{
	mActiveControl = true;
	if (NULL == mParent || mParent->IsActive())
	{
		if (!IsActive())
		{
			_Active(forceActiveControlofChild);
		}
	}

}


//------------------------------------------------------------------------
void 
Actor::Deactive(bool forceActiveControlofChild )
{
	mActiveControl = false;
	if (IsActive())
	{
		_Deactive(forceActiveControlofChild);
	}
}
//------------------------------------------------------------------------
void 
Actor::Destory(bool forceChild /* = false */)
{
	Deactive(true);
}
//------------------------------------------------------------------------
void
Actor::_Active(bool forceActiveControlofChild)
{
	n_assert( ActorManager::Instance() );
	GPtr<Actor> pActor(this);
	ActorManager::Instance()->ActiveActor( pActor, false );
	for (int i = 0; i < mChildren.Size(); ++i)
	{
		if (forceActiveControlofChild)
		{
			mChildren[i]->Active(forceActiveControlofChild);
		}
		else
		{
			mChildren[i]->_CheckActive();
		}
		
	}
}
//------------------------------------------------------------------------
void
Actor::_Deactive(bool forceActiveControlofChild)
{
	n_assert( ActorManager::Instance() );
	GPtr<Actor> pActor(this);
	ActorManager::Instance()->DeactiveActor( pActor, false );
	for (int i = 0; i < mChildren.Size(); ++i)
	{
		if (forceActiveControlofChild)
		{
			mChildren[i]->Deactive();
		}
		else
		{
			mChildren[i]->_CheckDeactive();
		}
	}
}

//------------------------------------------------------------------------
void
Actor::_CheckActive()
{
	if (mActiveControl && !IsActive())
	{
		_Active();
	}
}
//------------------------------------------------------------------------
void
Actor::_CheckDeactive()
{
	if (IsActive())
	{
		_Deactive();
	}
}

//------------------------------------------------------------------------------
void
Actor::OnActivate()
{
	n_assert(!this->mActivated);
	this->mActivated = true;
	// activate all Components
	this->_ActivateAllComponents();
}
//------------------------------------------------------------------------------
void
Actor::OnDeactivate()
{
	 n_assert(this->mActivated);
    this->mActivated = false;

	// cleanup Components
	this->_DeactivateAllComponents();
}
//------------------------------------------------------------------------------
/**
*/
const GPtr<Component>& 
Actor::FindComponentExactly( const Core::Rtti& rtti ) const
{
	IndexT i;
	for (i = 0; i < this->mComponents.Size(); ++i)
	{
		if (this->mComponents[i]->GetRtti() == &rtti)
		{
			return this->mComponents[i];
		}
	}
	// fallthrough: not found, return invalid ptr
	return Component::NullComplonent;
}

//------------------------------------------------------------------------------
/**
*/
const GPtr<Component>&
Actor::FindComponent(const Core::Rtti& rtti) const
{
    IndexT i;
    for (i = 0; i < this->mComponents.Size(); ++i)
    {
        if (this->mComponents[i]->IsA(rtti))
        {
            return this->mComponents[i];
        }
    }
    // fallthrough: not found, return invalid ptr
	return Component::NullComplonent;
}

//------------------------------------------------------------------------------
/**
*/
const Util::Array<GPtr<Component> >
Actor::FindComponents(const Core::Rtti& rtti) const
{
	Util::Array<GPtr<Component> > components;
	components.Clear();
	IndexT i;
	for (i = 0; i < this->mComponents.Size(); ++i)
	{
		if (this->mComponents[i]->IsA(rtti))
		{
			components.Append(mComponents[i]);
		}
	}
	// fallthrough: not found, return invalid ptr
	return components;
}
//------------------------------------------------------------------------------
void
Actor::AttachComponent(const GPtr<Component>& prop)
{
    n_assert(0 != prop);

    this->mComponents.Append(prop);
	prop->_SetActor(this);
	prop->SetupAllResource();
	if ( IsActive())
	{
		_ActiveComponent( prop );
	}

	_UpdateLocalBBox();
}

//------------------------------------------------------------------------------
void
Actor::RemoveComponent(const GPtr<Component>& prop)
{
    n_assert( prop.isvalid() );
    IndexT propIndex = this->mComponents.FindIndex(prop);
    if (InvalidIndex != propIndex)
    {
		_DeactiveComponent( prop );

        // delete Component
        n_assert( !mComponents[propIndex]->IsActive() );
		
		this->mComponents[propIndex]->_ClearActor();
        this->mComponents.EraseIndex(propIndex);

		_UpdateLocalBBox();
    }
    else
    {
        n_warning("Actor::RemoveComponent: Compon '%s' does not exist on Actor!", prop->GetClassName().AsCharPtr());
    }
}


void Actor::_UpdateLocalBBox()
{
	Math::bbox b(Math::point(0,0,0), Math::point(0,0,0));

	GPtr<Component> com = NULL;
	for (int i = 0; i < this->mComponents.Size(); ++i)
	{
		com = mComponents[i];
		if (com->IsA(MeshRenderComponent::RTTI))
		{
			GPtr<MeshRenderComponent> mrc = com.downcast<MeshRenderComponent>();
			GPtr<Resources::PrimitiveResInfo> resinfo = mrc->GetPrimtiveResInfo();
			if (resinfo)
			{
				GPtr<Resources::MeshRes> meshRes = resinfo->GetRes().downcast<Resources::MeshRes>();
				if (meshRes)
				{
					b.extend(meshRes->GetBoundingBox());
				}
			}
		}
		else if (com->IsA(TerrainRenderComponent::RTTI))
		{
			GPtr<TerrainRenderComponent> trc = com.downcast<TerrainRenderComponent>();
			TerrainNode* rootNode = trc->GetRootNode();
			if (rootNode)
			{
				b.extend(rootNode->GetLocalBoundingBox());
			}
		}
		else if (com->IsA(SpriteRenderComponent::RTTI))
		{
			GPtr<SpriteRenderComponent> src = com.downcast<SpriteRenderComponent>();
			b.extend(src->GetLocalBoundingBox());
		}
	}

	SetLocalBoundingBox(b);
}

//------------------------------------------------------------------------------
void
Actor::DestroyComponent(const GPtr<Component>& prop)
{
    n_assert( prop.isvalid() );
    IndexT propIndex = this->mComponents.FindIndex(prop);
    if (InvalidIndex != propIndex)
    {
		_DeactiveComponent( prop );

        // delete Component
        n_assert( !mComponents[propIndex]->IsActive() );
		
		this->mComponents[propIndex]->_ClearActor();
		this->mComponents[propIndex]->OnDestroy();
        this->mComponents.EraseIndex(propIndex);
    }
    else
    {
        n_error("Actor::RemoveComponent: Compon '%s' does not exist on Actor!", prop->GetClassName().AsCharPtr());
    }
}

//------------------------------------------------------------------------------
const bool
Actor::IsAllResourcePrepared() const
{
	const Util::Array<GPtr<Component> >& props = mComponents;
	IndexT i;
	bool allResLoaded = true;
	SizeT num = props.Size();
	for (i = 0; i < num; ++i)
	{
		allResLoaded &= props[i]->IsAllResourceLoaded();
	}
	return allResLoaded;
}
//------------------------------------------------------------------------------
void
Actor::OnBeginFrame()
{    
    n_assert(this->IsActive());

    // call Components that have registered for the BeginFrame callback
	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::BeginFrame];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {

    #if NEBULA3_ENABLE_PROFILING
        Util::String timerName = props[i]->GetRtti()->GetName() + ".OnBeginFrame";
        this->mComponentOnBeginFrameDebugTimer[timerName]->StartAccum();        
    #endif

        props[i]->_OnBeginFrame();   

    #if NEBULA3_ENABLE_PROFILING
        this->mComponentOnBeginFrameDebugTimer[timerName]->StopAccum();        
    #endif

    }
}
//------------------------------------------------------------------------------
void
Actor::OnMoveBefore()
{
    //n_assert(this->IsActive());

	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::MoveBefore];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {
    #if NEBULA3_ENABLE_PROFILING
		Util::String timerName = props[i]->GetRtti()->GetName() + ".OnMoveBefore";
        this->mComponentOnMoveBeforeDebugTimer[timerName]->StartAccum();
    #endif

        props[i]->_OnMoveBefore();        

    #if NEBULA3_ENABLE_PROFILING
        this->mComponentOnMoveBeforeDebugTimer[timerName]->StopAccum();
    #endif
    }

	SizeT numActor = mChildren.Size();
	for ( IndexT i = 0; i < numActor; ++i )
	{
		mChildren[i]->OnMoveBefore();
	}
}
//------------------------------------------------------------------------------
void
Actor::OnMoveAfter()
{
    //n_assert(this->IsActive());

	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::MoveAfter];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {
#if NEBULA3_ENABLE_PROFILING
		Util::String timerName = props[i]->GetRtti()->GetName() + ".OnMoveAfter";
		this->mComponentOnMoveAfterDebugTimer[timerName]->StartAccum();
#endif

        props[i]->_OnMoveAfter();        

#if NEBULA3_ENABLE_PROFILING
		this->mComponentOnMoveAfterDebugTimer[timerName]->StopAccum();
#endif
    }

	SizeT numActor = mChildren.Size();
	for ( IndexT i = 0; i < numActor; ++i )
	{
		mChildren[i]->OnMoveAfter();
	}
}
//------------------------------------------------------------------------------
void 
Actor::OnFrame()
{
    n_assert(this->IsActive());

	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::OnFrame];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {
#if NEBULA3_ENABLE_PROFILING
		Util::String timerName = props[i]->GetRtti()->GetName() + ".OnRender";
		this->mComponentOnRenderDebugTimer[timerName]->StartAccum();
#endif

        props[i]->_OnFrame();        

#if NEBULA3_ENABLE_PROFILING
		this->mComponentOnRenderDebugTimer[timerName]->StopAccum();
#endif
    }

#if NEBULA3_ENABLE_PROFILING
	_ResetComponentTimer();
#endif



}
//------------------------------------------------------------------------------
void 
Actor::OnEndFrame()
{
    n_assert(this->IsActive());

	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::EndFrame];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {
        props[i]->_OnEndFrame();   
	}
}
//------------------------------------------------------------------------------
void 
Actor::OnRenderDebug()
{
    n_assert(this->IsActive());

	const Util::Array<GPtr<Component> >& props = this->mCallbackComponents[Component::RenderDebug];
    IndexT i;
    SizeT num = props.Size();
    for (i = 0; i < num; ++i)
    {
        props[i]->_OnRenderDebug();
    }
}
//------------------------------------------------------------------------------
void
Actor::RegisterComponentCallback(const GPtr<Component>& prop, Component::CallbackType callbackType)
{
    n_assert(0 != prop);
    
    // ignore double entries, this could happen if the method
    // is called from several Component subclasses
    if (InvalidIndex == this->mCallbackComponents[callbackType].FindIndex(prop))
    {
        this->mCallbackComponents[callbackType].Append(prop);
    }
}
//------------------------------------------------------------------------
void Actor::SetActiveStateForTemplate()
{
	SizeT count = this->GetChildCount();
	bool bActive;

	bActive = this->GetTmpActiveState();

	if (bActive)
	{
		this->Active( false );
	}
	else
	{
		this->Deactive( false );
	}

	for ( IndexT i = 0; i < count; ++i)
	{
		const GPtr<Actor>& pChild = this->GetChild(i);

		pChild->SetActiveStateForTemplate();
	}

}
//------------------------------------------------------------------------
void Actor::CopyFrom( const GPtr<Actor>& pSource, bool includePrivateProperty, bool isTemplate , bool needRecurVFL )
{
//#ifdef _DEBUG
//	mCopyedActor = 1;
//#endif
	if ( !pSource.isvalid() )
	{
		return;
	}

	if ( this == pSource.get() )
	{
		return;
	}

	Deactive(true);
	
	// clear all child actor
	// destroy child
	{

		SizeT count = mChildren.Size();
		for ( IndexT i = 0; i < count; ++i )
		{
			n_assert( mChildren[i].isvalid() );
			mChildren[i]->_Destory();
		}
		mChildren.Clear();
	}

	// clear all Components
	_CleanupAllComponents();

	// copy actor
	{
		SizeT count = pSource->GetChildCount();
//#ifdef _DEBUG
//		mCopyedActor += count;
//#endif
		for ( IndexT i = 0; i < count; ++i)
		{
			const GPtr<Actor>& pSourceChild = pSource->GetChild(i);
			n_assert( pSourceChild.isvalid() );
			GPtr<RefCounted> pObj = pSourceChild->GetRtti()->Create();
			GPtr<Actor> pDestChild = pObj.downcast<Actor>();
			n_assert( pDestChild.isvalid() );
			pDestChild->CopyFrom( pSourceChild, true , isTemplate , needRecurVFL);	//	Dest Child is just Create, Copy All from Source Child
			pDestChild->SetParent( this );
//#ifdef _DEBUG
//			mCopyedActor += pDestChild->CopyedActor();
//#endif
		}
	}
	
	// copy component
	{
		SizeT count = pSource->mComponents.Size();
		for ( IndexT i = 0; i < count; ++i )
		{
			GPtr<Component> pSourceCom = pSource->mComponents[i];
			n_assert( pSourceCom.isvalid() );
			GPtr<RefCounted> pObj = pSourceCom->GetRtti()->Create();
			GPtr<Component> pDestCom = pObj.downcast<Component>();
			n_assert( pDestCom.isvalid() );
			pDestCom->CopyFrom( pSourceCom );
			AttachComponent( pDestCom );
		}
	}
	//更新 新加入的Component的显示属性
	SetVisible(pSource->GetVisible(), needRecurVFL);
#ifdef __GENESIS_EDITOR__
	SetFrozen(pSource->GetFrozen(), needRecurVFL);
	SetLocked(pSource->GetLocked(), needRecurVFL);
#endif
	SetLocalBoundingBox(pSource->GetLocalBoundingBox());
	SetTemplateName( pSource->GetTemplateName() );

	if ( includePrivateProperty )
	{
		// copy actor property, just serialization's property need copy
		//SetVisible(pSource->GetVisible());

		if (  pSource->GetActiveControl() )
			Active();
		else
			Deactive();

		SetName( pSource->GetName() );
		SetLinkTemplate( pSource->IsLinkTemplate() );
		SetLayerID( pSource->GetLayerID() );
		SetTagID( pSource->GetTagID() );
		SetTransform( pSource->GetPosition(), pSource->GetRotation(), pSource->GetScale() );
		// for templatedActors
		SetTmpActiveState( pSource->IsActive() );
#ifdef __GENESIS_EDITOR__
		SetQueryMask(pSource->GetQueryMask());		
#endif
		SetEditorFlag( pSource->GetEditorFlag() );
	}

	if (isTemplate)
	{
		SetLayerID( pSource->GetLayerID() );
		SetTagID( pSource->GetTagID() );
		SetTransform( this->GetPosition(), this->GetRotation(), this->GetScale() );
		SetTmpActiveState( pSource->IsActive() );
#ifdef __GENESIS_EDITOR__
		SetQueryMask(pSource->GetQueryMask());
#endif
		SetEditorFlag( pSource->GetEditorFlag() );
	}

}

//------------------------------------------------------------------------
void 
Actor::SetPriority( const Resources::Priority priority )
{
	mPriority = (Resources::ResourcePriority::Undefinition > mPriority) ? Resources::ResourcePriority::Undefinition : priority;
}

//------------------------------------------------------------------------

//------------------------------------------------------------------------
void 
Actor::SetParent( Actor* parent )
{
	if ( GetParent() == parent || this ==  parent)
	{
		return;
	}

#if NEBULA3_DEBUG	// check if loop link
	if ( parent )
	{
		Actor* checkParent = parent->GetParent();
		while( checkParent )
		{
			if ( this == checkParent )
			{
				n_error( "Actor::SetParent loop link" );
				return;
			}
			checkParent = checkParent->GetParent();
		}
	}
#endif
	const Graphic::RenderScene* old_rs = GetRenderScene();

	// 从老的Parent中移除
	Actor* oldParent = GetParent();
	if ( oldParent )
	{
		IndexT findIndex = oldParent->FindChildIndex( this->GetFastId() ); 
		n_assert( findIndex != InvalidIndex );
		oldParent->mChildren.EraseIndex( findIndex );
	}

	// 加入到新的parent中
	bool parentActive = true;
	if ( parent )
	{
		parent->mChildren.Append(TActorPtr(this));
		_SetParentImpl( parent );
		parentActive = parent->IsActive();
	}
	else
	{
		_SetParentImpl( parent );
		parentActive = true;
	}

	if (parentActive)
	{
		_CheckActive();
	}
	else
	{
		_CheckDeactive();
	}

	const Graphic::RenderScene* curr_rs = GetRenderScene();

	if (IsActive() && old_rs != curr_rs)
	{
		_OnRenderSceneChanged();
	}

}
//------------------------------------------------------------------------
void
Actor::_OnRenderSceneChanged()
{
	IndexT i;
	SizeT num = mComponents.Size();
	for (i = 0; i < num; ++i)
	{
		mComponents[i]->OnRenderSceneChanged();   
	}
}
//------------------------------------------------------------------------
void
Actor::_OnActorParentChanged()
{
	IndexT i;
	SizeT num = mComponents.Size();
	for (i = 0; i < num; ++i)
	{
		mComponents[i]->OnActorParentChanged();   
	}
}

//------------------------------------------------------------------------
void
Actor::SetParent( const GPtr<Actor>& actor )
{
	SetParent( actor.get_unsafe() );
}
//------------------------------------------------------------------------
const GPtr<Actor>& 
Actor::GetChild(IndexT i) const
{
	if ( i >= 0 && i < mChildren.Size() )
	{
		return mChildren[i];
	}
	return Actor::NullActor;
}
//------------------------------------------------------------------------
IndexT 
Actor::FindChildIndex(FastId id) const
{
	// @todo may be need optimize, eg. Binary Search
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		if ( mChildren[index]->GetFastId() == id )
		{
			return index;
		}
	}
	return InvalidIndex;
}
//------------------------------------------------------------------------
const GPtr<Actor>& 
Actor::FindChild(FastId id) const
{
	IndexT findIndex = FindChildIndex(id);
	return GetChild( findIndex );
}

//------------------------------------------------------------------------
const GPtr<Actor>&
Actor::FindChildByTag(App::TagID id) const
{
	// @todo may be need optimize, eg. Binary Search
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		if ( mChildren[index]->GetTagID() == id )
		{
			return mChildren[index];
		}
	}
	return NullActor;
}
//------------------------------------------------------------------------
void Actor::FindChildrenByTag(const App::TagID id,Util::Array< GPtr<Actor> >& actors) const
{
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		if ( mChildren[index]->GetTagID() == id )
		{
			actors.Append(mChildren[index]);
		}
	}
}
const GPtr<Actor>& 
	Actor::FindChild(const Util::String& name) const
{
	// @todo may be need optimize, eg. Binary Search
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		if ( mChildren[index]->GetName() == name )
		{
			return mChildren[index];
		}
	}
	return NullActor;
}

//------------------------------------------------------------------------
const GPtr<Actor>& 
Actor::FindChild(const Util::Guid& guid) const
{
	// @todo may be need optimize, eg. Binary Search
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		if ( mChildren[index]->GetGUID() == guid )
		{
			return mChildren[index];
		}
	}
	return NullActor;
}

//------------------------------------------------------------------------
void 
Actor::AddChild(GPtr<Actor>& childActor )
{
	if ( childActor.isvalid() )
	{
		childActor->SetParent( this );
	}
}
//------------------------------------------------------------------------
void 
Actor::RemoveChild( const GPtr<Actor>& childActor )
{
	if ( childActor.isvalid() )
	{
		IndexT findIndex = FindChildIndex( childActor->GetFastId() );
		RemoveChild( findIndex );
	}
}
//------------------------------------------------------------------------
void 
Actor::RemoveChild( IndexT i )
{
	if ( i >=0 && i < mChildren.Size() )
	{
		GPtr<Actor>& child = mChildren[i];
		n_assert( child.isvalid() );
		child->_SetParentImpl( NULL );
		if (GetRenderScene() != NULL && child->IsActive())
		{
			child->_OnRenderSceneChanged();
		}
		child->_CheckActive();
		mChildren.EraseIndex( i );
	}
}
//------------------------------------------------------------------------
void
Actor::RemoveAllChild()
{
	SizeT count = mChildren.Size();
	for ( IndexT i = 0; i < count; ++i)
	{
		GPtr<Actor>& pChild = mChildren[i];
		n_assert( pChild.isvalid() );
		pChild->_SetParentImpl( NULL );
		if (GetRenderScene() != NULL && pChild->IsActive())
		{
			pChild->_OnRenderSceneChanged();
		}
		pChild->_CheckActive();
	}
	mChildren.Clear();
}

//------------------------------------------------------------------------
void 
Actor::_SetParentImpl(Actor* p)
{
	if ( mParent != p )
	{
		if ( IsActive() )
		{
			OnMoveBefore();
		}
		mParent = p;
		_DirtyWorldTransform();

		if ( IsActive() )
		{
			OnMoveAfter();
		}
		_OnActorParentChanged();
	}
}
//------------------------------------------------------------------------
/**
	设置Actor下面挂载的孩子的变换矩阵&包围盒更新标志
*/
void 
Actor::_DirtyWorldTransform()
{
	mDirtyWorldTrans = true;
	mDirtyWorldBB = true;	//	world matrix change， world bounding box need change too

	// dirty child
	GPtr<Actor> children;

#ifdef __GENESIS_EDITOR__
	bool bLocked = false;
#endif

	SizeT numActor = mChildren.Size();
	for ( IndexT i = 0; i < numActor; ++i )
	{
		children = mChildren[i];

#ifdef __GENESIS_EDITOR__
		/*子actor处于锁定状态时，其世界坐标不应该跟着父actor的变换而变换，
		但其局部坐标发生了变化，所以要更新局部坐标*/
		bLocked = children->GetLocked();
		if ( bLocked )
		{
			const Actor *parent = children->GetParent();
			children->SetLockedActorLocalTransform(parent);
			continue;
		}
#endif

		children->_DirtyWorldTransform();
	}
}
//------------------------------------------------------------------------
void Actor::_UpdateLocalTransform() const
{
	if ( mDirtyLocaTrans )
	{
		mLocaTrans = Math::matrix44::transformation(
			mLocalScale,
			mLocalRotation,
			mLocalPosition);

		mDirtyLocaTrans = false;
	}
}

void 
Actor::_UpdateWolrdTransform() const
 {
	if ( mDirtyWorldTrans )
	{
		// 重新计算
		if (mParent)
		{
			const Math::matrix44& pw =  mParent->GetWorldTransform();
			Math::matrix44 own = Math::matrix44::transformation(mLocalScale, mLocalRotation, mLocalPosition);
			mWorldTrans = Math::matrix44::multiply(pw,own);
			mWorldTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
			mWorldTrans.decompose(mWorldScale,mWorldRotation, mWorldPosition);

			//Math::quaternion ParentRotation = mParent->GetWorldRotation();
			//Math::vector ParentScale = mParent->GetWorldScale();
			//Math::vector ParentPosition = mParent->GetWorldPosition();

			//mWorldRotation = Math::quaternion::multiply( ParentRotation, mLocalRotation );
			//mWorldPosition = ParentRotation * ( mLocalPosition * ParentScale ) + ParentPosition;
			//mWorldScale = ParentScale * mLocalScale;
		}
		else
		{
			// Root node, no parent
			mWorldRotation = mLocalRotation;
			mWorldPosition = mLocalPosition;
			mWorldScale = mLocalScale;

			mWorldTrans = Math::matrix44::transformation(
				mWorldScale,
				mWorldRotation,
				mWorldPosition);
		}

		//mWorldTrans = Math::matrix44::transformation(
		//	mWorldScale,
		//	mWorldRotation,
		//	mWorldPosition);

		mDirtyWorldTrans = false;
	}
}

//------------------------------------------------------------------------------
void 
Actor::SaveTerrainFile(void) const
{
    GPtr<Component> com = FindComponent( TerrainRenderComponent::RTTI );
    if ( com.isvalid() )
    {
	    GPtr<TerrainRenderComponent> terrainR = com.downcast<TerrainRenderComponent>();
	    if (terrainR)
	    {
            terrainR->SaveTerrainFile();
	    }
    }

    return;
}
//------------------------------------------------------------------------------
#ifdef __GENESIS_EDITOR__
void Actor::SetLocked(bool bLocked , bool needRecursive/* = true*/)
{
	mLocked = bLocked;
	if (needRecursive)
	{
		SizeT count = mChildren.Size();
		for ( IndexT index = 0; index < count; ++index )
		{
			mChildren[index]->SetLocked(bLocked);
		}
	}	
}
//------------------------------------------------------------------------------
void Actor::SetLockedActorTransformRecursive(const GPtr<App::Actor>& pSource)
{
	n_assert(pSource);
	SetTransform(pSource->GetPosition(),pSource->GetRotation(),pSource->GetScale());
	SizeT count = mChildren.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		mChildren[index]->SetLockedActorTransformRecursive(pSource->GetChild(index));
	}
}
//------------------------------------------------------------------------------
void Actor::SetFrozen(bool bFrozen , bool needRecursive/* = true*/)
{
	mFrozen = bFrozen;
	if (needRecursive)
	{
		SizeT count = mChildren.Size();
		for ( IndexT index = 0; index < count; ++index )
		{
			mChildren[index]->SetFrozen(bFrozen);
		}
	}
}
#endif
//------------------------------------------------------------------------------
void Actor::SetVisible( bool bVisible , bool needRecursive /*= true*/ )
{
	mVisible = bVisible;

	if ( NULL != FindComponent<RenderComponent>() )
	{
		Util::Array< GPtr<Component> > coms = FindComponents(RenderComponent::RTTI);
		SizeT count = coms.Size();
		for ( SizeT i = 0; i < count; i++ )
		{
			GPtr<RenderComponent> renderCom = coms[i].downcast<RenderComponent>();
			n_assert(renderCom.isvalid());

			renderCom->SetVisible(bVisible);
		}
	}

	if ( NULL != FindComponent<VegetationRenderComponent>() )
	{
		Util::Array< GPtr<Component> > coms = FindComponents(VegetationRenderComponent::RTTI);
		SizeT count = coms.Size();
		for ( SizeT i = 0; i < count; i++ )
		{
			GPtr<VegetationRenderComponent> vegeRenderCom = coms[i].downcast<VegetationRenderComponent>();
			if ( !vegeRenderCom.isvalid() )
			{
				continue;
			}
			vegeRenderCom->SetVisible(bVisible);
		}
	}
	if (needRecursive)
	{
		SizeT count = mChildren.Size();
		for ( IndexT index = 0; index < count; ++index )
		{
			mChildren[index]->SetVisible(bVisible);
		}
	}	
	//暂未处理其它component对显示隐藏属性的响应，如相机、灯光、声音、粒子
	return;
}
//------------------------------------------------------------------------------
bool Actor::GetVisible() const
{
	return mVisible;
}
//------------------------------------------------------------------------------
bool Actor::IsChildOfAnimationActor()
{
	if ( mParent != NULL )
	{
		if ( NULL != mParent->FindComponent<AnimationComponent>() )
			return true;
		return mParent->IsChildOfAnimationActor();
	}
	else
	{
		if ( NULL != FindComponent<AnimationComponent>() )
		  return true;
	}
	return false;
}
//------------------------------------------------------------------------
/*设置锁定actor的局部坐标时是不需要调_DirtyWorldTransform()函数的，因为
锁定物体的局部坐标是因为父物体位置改变造成的，其本身的空间方位根本没有发生变化。*/
#ifdef __GENESIS_EDITOR__
void Actor::SetLockedActorLocalTransform( const Actor *parent )
{

	if ( parent )
	{
		const Math::matrix44 &parentWT = parent->GetWorldTransform();
		Math::matrix44 inversepw = Math::matrix44::inverse(parentWT);
		const Math::matrix44 &worldTransform = GetWorldTransform();
		mLocaTrans = Math::matrix44::multiply( inversepw , worldTransform );
		mLocaTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
		mLocaTrans.decompose( mLocalScale, mLocalRotation, mLocalPosition );
		return;
	} 
	else
	{
		mLocalPosition = mWorldPosition;
		mLocalRotation = mWorldRotation;
		mLocalScale = mWorldScale;
		mLocaTrans = mWorldTrans;
	}
}
#endif
//------------------------------------------------------------------------------
#if NEBULA3_ENABLE_PROFILING
//------------------------------------------------------------------------
void Actor::_AttachComponentTimer( const Core::Rtti* pRtti )
{
	// create timer for activation
	{
		Util::String timerName(pRtti->GetName() + ".OnActivate");
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentActivateDebugTimer.Add(timerName, debugtimer);    
	}


	// create timer for deactivation
	{
		Util::String timerName(pRtti->GetName() + ".OnDeactivate");
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentDeactivateDebugTimer.Add(timerName, debugtimer);    
	}


	// create timer for on begin frame
	{
		Util::String timerName = pRtti->GetName() + ".OnBeginFrame";
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentOnBeginFrameDebugTimer.Add(timerName, debugtimer);  
	}


	// create timer for on move before
	{
		Util::String timerName = pRtti->GetName() + ".OnMoveBefore";
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentOnMoveBeforeDebugTimer.Add(timerName, debugtimer);  
	}


	// create timer for on begin frame
	{
		Util::String timerName = pRtti->GetName() + ".OnMoveAfter";
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentOnMoveAfterDebugTimer.Add(timerName, debugtimer);  
	}
	

	// create timer for on start
	{
		Util::String timerName = pRtti->GetName() + ".OnRender";
		GPtr<Debug::DebugTimer> debugtimer = Debug::DebugServer::Instance()->GetDebugTimerByName(timerName);
		if (!debugtimer.isvalid())
		{
			debugtimer = Debug::DebugTimer::Create();
			debugtimer->Setup(timerName);
		}
		this->mComponentOnRenderDebugTimer.Add(timerName, debugtimer);  
	}

}
//------------------------------------------------------------------------
void Actor::_RemoveComponentTimer( const Core::Rtti* pRtti )
{
	// remove active timer ptr
	{
		Util::String timerName(pRtti->GetName() + ".OnActivate");
		if (this->mComponentActivateDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentActivateDebugTimer[timerName]->Discard();
		}
		this->mComponentActivateDebugTimer[timerName] = 0;
	}


	// remove deactive timer ptr
	{
		Util::String timerName(pRtti->GetName() + ".OnDeactivate");
		if (this->mComponentDeactivateDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentDeactivateDebugTimer[timerName]->Discard();
		}
		this->mComponentDeactivateDebugTimer[timerName] = 0;
	}


	// remove begin frame timer ptr
	{
		Util::String timerName = pRtti->GetName() + ".OnBeginFrame";
		if (this->mComponentOnBeginFrameDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentOnBeginFrameDebugTimer[timerName]->Discard();
		}
		this->mComponentOnBeginFrameDebugTimer[timerName] = 0;	
	}


	// remove move before timer ptr
	{
		Util::String timerName = pRtti->GetName() + ".OnMoveBefore";
		if (this->mComponentOnMoveBeforeDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentOnMoveBeforeDebugTimer[timerName]->Discard();
		}
		this->mComponentOnMoveBeforeDebugTimer[timerName] = 0;
	}


	// remove move after timer ptr
	{
		Util::String timerName = pRtti->GetName() + ".OnMoveAfter";
		if (this->mComponentOnMoveAfterDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentOnMoveAfterDebugTimer[timerName]->Discard();
		}
		this->mComponentOnMoveAfterDebugTimer[timerName] = 0;
	}


	// remove render timer ptr
	{
		Util::String timerName = pRtti->GetName() + ".OnRender";
		if (this->mComponentOnRenderDebugTimer[timerName]->GetRefCount() == 2)
		{
			this->mComponentOnRenderDebugTimer[timerName]->Discard();
		}
		this->mComponentOnRenderDebugTimer[timerName] = 0;
	}


}
//------------------------------------------------------------------------
void Actor::_ResetComponentTimer()
{
	IndexT idx;

	for (idx = 0; idx < this->mComponentActivateDebugTimer.Size(); ++idx)
	{
		this->mComponentActivateDebugTimer.ValueAtIndex(idx)->ResetAccum();
	} 

	for (idx = 0; idx < this->mComponentDeactivateDebugTimer.Size(); ++idx)
	{
		this->mComponentDeactivateDebugTimer.ValueAtIndex(idx)->ResetAccum();
	} 

	for (idx = 0; idx < this->mComponentOnBeginFrameDebugTimer.Size(); ++idx)
	{
		this->mComponentOnBeginFrameDebugTimer.ValueAtIndex(idx)->ResetAccum();
	}

	for (idx = 0; idx < this->mComponentOnMoveBeforeDebugTimer.Size(); ++idx)
	{
		this->mComponentOnMoveBeforeDebugTimer.ValueAtIndex(idx)->ResetAccum();
	} 

	for (idx = 0; idx < this->mComponentOnMoveAfterDebugTimer.Size(); ++idx)
	{
		this->mComponentOnMoveAfterDebugTimer.ValueAtIndex(idx)->ResetAccum();
	} 

	for (idx = 0; idx < this->mComponentOnRenderDebugTimer.Size(); ++idx)
	{
		this->mComponentOnRenderDebugTimer.ValueAtIndex(idx)->ResetAccum();
	} 
}
#endif

} // namespace App