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
#ifndef __actor_H__
#define __actor_H__

#include "app/appframework/app_fwd_decl.h"
#include "core/refcounted.h"
#include "core/ptr.h"
#include "foundation/messaging/message.h"
#include "messaging/dispatcher.h"
#include "app/appframework/component.h"
#include "util/dictionary.h"
#include "util/guid.h"
#include "debug/debugtimer.h"
#include "app/appframework/serialization.h"
#include "math/matrix44.h"
#include "math/vector.h"
#include "math/quaternion.h"
#include "math/bbox.h"
#ifndef __SCRIPT_COMMIT__
#include "foundation/util/scriptbind.h"
#include "app/scriptfeature/inc/script_message.h"
#include "app/scriptfeature/inc/script_utility.h"
#endif
#include "addons/resource/resourcemanager.h"
#include "addons/resource/resourcepriority.h"
#include "addons/resource/templateresloader.h"
#include "addons/resource/templateressaver.h"

//------------------------------------------------------------------------------
namespace Graphic
{
	class RenderScene;
}

namespace App
{
	class Actor;
	class ActorManager;
	class ScriptComponent;
	class RenderComponent;
	class PhysicsEntity;
	class SkinnedMeshRenderComponent;
	class SkeletonComponent;
	class AnimationComponent;

	enum SysLayerID
	{
		eSL_Defualt = 0,//RenderLayer::eRLDefault
		eSL_Debug = 31,//RenderLayer::eRLDebug
	};

	

	typedef uint LayerID;

	typedef uint TagID;

	class ActorSerializationArgs : public Serialization::SerializationArgs
	{
	public:
		inline ActorSerializationArgs(Actor* parent)
		{
			this->parent = parent;
		}
		Actor* parent;
	};

	// Modified From Nebula3's Entity(Actor) and Property(Component).  MayBe It's Good for Radon Labs. 
	// But I think It's too Difficult to Understand Nebula3's Design for Newer. For Example:  Property in DB Storage , So Many Thread, So Many Details Hidden in Addon... 
	// Actor:     Manage RelationShip And Component. TODO:  Add TinyActor For Object With No Game Logic.
	// Addons:     I Hope There are only Libs Which Can Be Replace By Other Libs Or ReUse By Other Engine. Idealism, But Can Be More Easier. 
	// Component:  First:  Make Addons-Lib's Function Corresponded With Actor-Component Model 
	//             Second: Corresponded With Other Components With Message. 
	class Actor : public Core::RefCounted, App::ISerialization
	{
		__DeclareClass(Actor);
		__ScriptBind
	public:
		/// an Id type, used to identify entities
		typedef unsigned int FastId;

		const static GPtr<Actor> NullActor;
		
		/// destructor.  but use Actor::destory
		virtual ~Actor();

		virtual Graphic::RenderScene* GetRenderScene() const;

		//--------------------------------basic----------------------------------------
		void SetName(const Util::String& name);

		const Util::String& GetName(void) const;

		/// get the Actor's category
		const Util::StringAtom& GetTemplateName() const;
		//  store activeState for templatedActors
		void SetTmpActiveState(bool tmpActiveState);
		// get activeState for templatedActors
		bool GetTmpActiveState();
		// set activeState for templatedActors 
		void SetActiveStateForTemplate();

		bool IsLinkTemplate(void) const;

		void SetLinkTemplate(bool bLink);

		LayerID GetLayerID(void) const;

		void SetLayerID(LayerID id);

		uint GetCullMark() const;

		TagID GetTagID(void) const;

		void SetTagID(TagID);

		/// get unique id of Actor
		FastId GetFastId() const;

		/// if the actor is active
		bool IsActive() const;//bool checkParent = true

		/// if the actor is active
		bool IsDestory() const;

		// active the actor and it's component. add in active actor list in ActorManger
		// if includeChild is true, all child actor will be active too
		void Active(bool forceActiveControlofChild = false);

		// Deactive the actor and it's component. remove from active actor list in ActorManger
		// if includeChild is true, all child actor will be deactive
		void Deactive(bool forceActiveControlofChild = false);

		bool GetActiveControl() const;

		/// actor's it's component and all child actor
		/// obsolete fuction. the same as Deactive(true).
		void Destory(bool forceChild = false);

		//--------------------------------Parent----------------------------------------	
		// return parent. May be Null
		Actor* GetParent(void) const;

		// set parent. will remove from old parent 
		void SetParent( Actor* parent );

		void SetParent( const GPtr<Actor>& parent );

		// return child count. May be 0
		SizeT GetChildCount(void) const;

		// return child by index
		const GPtr<Actor>& GetChild(IndexT i) const;

		// find actor by FastID
		const GPtr<Actor>& FindChild(FastId id) const;

		const GPtr<Actor>& FindChildByTag(App::TagID id) const;

		void FindChildrenByTag(const App::TagID tagID,Util::Array< GPtr<Actor> >& actors) const;

		const GPtr<Actor>& FindChild(const Util::Guid& guid) const;

		const GPtr<Actor>& FindChild(const Util::String& name) const;

		// find child actor index in child list
		IndexT FindChildIndex(FastId id) const;

		// add child. If childActor Has Parent, Failed, Need Remove Form Other Parent First. Please Use SetParent
		void AddChild(GPtr<Actor>& childActor );

		// Remove Child By Ptr or Index. if Null or Not Exist, Failed. After Removed, the Index of other Child Actor May Change
		void RemoveChild( const GPtr<Actor>& childActor );
		void RemoveChild( IndexT i );

		// remove all child 
		void RemoveAllChild(void);

		//----------------------------Transform ----------------------------------------

		void SetPosition(const Math::vector& pos);

		void SetRotation(const Math::quaternion& rot);

		void SetScale(const Math::vector& scale);

		const Math::vector& GetPosition(void) const;

		const Math::quaternion& GetRotation(void) const;

		const Math::vector& GetScale(void) const;



		/** move around z axis(radian).
		*/
		void Roll(Math::scalar angle );

		/** move around x axis(radian).
		*/
		void Pitch(Math::scalar angle );

		/** move around y axis(radian).
		*/
		void Yaw(Math::scalar angle );

		// roll first, then pitch, then yaw.radian.
		void Rotate(Math::scalar roll , Math::scalar pitch , Math::scalar yaw  );

		void SetTransform(const Math::vector& pos,  const Math::quaternion& rot, const Math::vector& scale);

		void SetTransform( const Math::matrix44& m );

		void SetWorldTransform( const Math::matrix44& m );

		const Math::matrix44& GetTransform(void) const;

		const Util::Guid& GetGUID() const;

		void SetWorldPosition(const Math::vector& pos);

		void SetWorldRotation(const Math::quaternion& rot);

		void SetWorldScale(const Math::vector& scale);

		const Math::quaternion& GetWorldRotation(void) const;

		const Math::vector& GetWorldPosition(void) const; 

		const Math::vector& GetWorldScale(void) const;

		const Math::matrix44& GetWorldTransform(void) const;

		const Math::matrix44 GetWorldTranslateRotation(void) const;

		// remove the scales of all parent actors
		const Math::matrix44 GetWorldTranslateNoScale(void) const;
		const Math::quaternion GetWorldRotationNoScale(void) const;

		//-------------------------------boundingbox-----------------------------------------

		// get world boundingbox. Just The Actor, No child actor 
		const Math::bbox& GetWorldBoundingBox(void) const;

		// get world boundingbox. Include the Actor and it's child actor. Slow !!!!!!! 
		Math::bbox GetWorldBoundingBoxWithChild(void) const;

		// get local boundingbox. default  is [-0.5,-0.5,-0.5]~[0.5,0.5,0.5]
		const Math::bbox& GetLocalBoundingBox(void)  const;

		// set Local boundingbox.
		void SetLocalBoundingBox(const Math::bbox& bb);

		//-------------------------------component-----------------------------------------

		/// return true if any Component accepts/processes message
		bool AcceptsMessage(const Messaging::Id& msgId) const;

		/// send a synchronous message to the Actor
		void SendSync(const GPtr<Messaging::Message>& msg);

		/// throw a message to the script
		template<typename T>
		void ThrowMessageToScript(const Util::String& name,T& pair);

		/// find Component by RTTI (performs IsA() check), returns invalid pointer if not exists, slow!
		const GPtr<Component>& FindComponent(const Core::Rtti& rtti) const;

		template<typename T>
		GPtr<T> FindComponent() const;
		
		/// find Component by RTTI (perform RTTI's operator == check),returns invalid pointer if not exists,
		/// now only used in script sys to get the exactly component in order to show correct debug imformation.  
		const GPtr<Component>& FindComponentExactly(const Core::Rtti& rtti) const;

		/// find Components by RTTI (performs IsA() check), returns empty size if not exists, slow!
		const Util::Array< GPtr<Component> > FindComponents(const Core::Rtti& rtti) const;

		/// attach a Component to the Actor
		void AttachComponent(const GPtr<Component>& prop);

		/// remove a Component from the Actor
		void RemoveComponent(const GPtr<Component>& prop);

		/// destroy a Component from the Actor
		void DestroyComponent(const GPtr<Component>& prop);

		const bool IsAllResourcePrepared() const;

	    void SaveTerrainFile(void) const;

		//----------------------------- callbacks -------------------------------------------

		/// register a Component callback, called by ComponentSetupCallback() method
		void RegisterComponentCallback(const GPtr<Component>& prop, Component::CallbackType callback);

		/// called at the beginning of the frame
		void OnBeginFrame();

		/// called before movement
		void OnMoveBefore();

		/// called after movement
		void OnMoveAfter();

		/// called before rendering
		void OnFrame();

		/// called at the ending of the frame
		void OnEndFrame();

		/// debug rendering called before rendering 
		void OnRenderDebug();

		//----------------------------------ISerialization--------------------------------------

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const ;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args ) ;

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const ;

		// copy from source Actor. after copy, all old components and the child actor in this actor will destroy
		// if includeSelfProperty is false, only the components and  child actor will copy
		// if includePrivateProperty is true, the actor's property( like transform, layerID,...) , components and child actor will copy
		// if needRecurVFL is false, the actor's visible,frozen,lock states will affect its children. 
		// after copy, the actor is deactive. should manu active if need
		virtual void CopyFrom( const GPtr<Actor>& pSource, bool includePrivateProperty , bool isTemplate = false , bool needRecurVFL = true);

		//virtual void CopyFromTemplateRes(Resources::ResourceId resID);'

		//resource loading priority: if -1,use component's setup
		void SetPriority( const Resources::Priority priority );

		Resources::Priority GetPriority() const;

		bool PriorityDefinition() const;

		bool PriorityUndefinition() const;
		//----------------------------------- between components -----------------------------
#ifndef __SCRIPT_COMMIT__
		void Check_OnRenderPostEffect_Bind();
		void Check_OnRenderPostEffect_Unbind(); 

		void Check_OnWillRenderObject_Bind();
		void Check_OnWillRenderObject_Unbind();
#endif
		static void Check_Skeleton(SkeletonComponent* skeleton);
		static void Check_Animation(AnimationComponent* animation);
		static void Check_Skin(SkinnedMeshRenderComponent* skin);

		void OpenComponentsCommSign(ComponetsCommSign sign);
		void CloseComponentsCommSign(ComponetsCommSign sign);
		bool IsComponentsCommSignOpen(ComponetsCommSign sign);

		void _UpdateLocalBBox();
	protected:
		typedef Util::Array<TActorPtr> Children;
		// recompute world transform if need
		void _UpdateWolrdTransform() const;
		void _UpdateLocalTransform() const;
		

		void _CheckActive();

		void _CheckDeactive();

		void _Active(bool forceActiveControlofChild = false);

		void _Deactive(bool forceActiveControlofChild = false);

		void _OnRenderSceneChanged();

		void _OnActorParentChanged();

		/// set Actor category
		void SetTemplateName(const Util::StringAtom& tepName);

		/// cleanup the Actor Components, called from OnDeactivate()
		void _CleanupAllComponents();

		/// call OnActivate() on all Components
		void _ActivateAllComponents();

		/// call OnDeactivate() on all Components
		void _DeactivateAllComponents();

		void _ActiveComponent( const GPtr<Component>& pComponent );

		void _DeactiveComponent( const GPtr<Component>& pComponent );

		void _SetParentImpl(Actor* p);

		void _DirtyWorldTransform();

		/// called when attached to world. Just called by ActorManger
		void OnActivate();

		/// called when removed from world. Just called by ActorManger
		void OnDeactivate();

#ifdef __GENESIS_EDITOR__
	public:
		void SetQueryMask(uint mask);
		uint GetQueryMask() const;

		const Math::vector& GetEulerRotation() const;
		void SetEulerRotation(const Math::vector & rot);

		void SetFrozen( bool bFrozen , bool needRecursive = true );
		void SetLocked( bool bLocked , bool needRecursive = true );
		bool GetFrozen() { return mFrozen; }
		bool GetLocked() { return mLocked; }
		//only called after copy,pSource is the actor used for copyfrom source
		void SetLockedActorTransformRecursive(const GPtr<App::Actor>& pSource);

	protected:
		void SetLockedActorLocalTransform( const Actor *parent );

		Math::vector	mEulerAngle;
		uint	mQueryMask;

		bool    mFrozen;
		bool    mLocked;
#endif
	public:
		enum EditorFlag
		{	
			RenderLightMap = 1,
		};
		void SetEditorFlag(EditorFlag flags);
		EditorFlag GetEditorFlag() const;
		bool CheckEditorFlag (EditorFlag flags);

		void SetVisible( bool bVisible , bool needRecursive = true);
		bool GetVisible() const;

		//return true if this actor is a child of one actor that has a animation component
		bool IsChildOfAnimationActor();

	protected:// date
		uint    mEditorFlag;

		FastId mFastId;
		static FastId s_fastIdCounter;

		Util::Guid mGuid;

		Util::String mName;
		bool mActivated;
		//when true, actor will be actived when it is parent is been actived.
		bool mActiveControl;

		bool mTmpActiveState;

		Util::StringAtom mTemplateName;
		bool mIsLinkTemplate;

		LayerID mLayerID;
		TagID mTagID;
		//flag config of components.
		//used for bit flag.see, enum ComponetsCommSign
		TagID mComponentsCommSign;

		//local transform and bound
		Math::quaternion mLocalRotation;
		Math::vector mLocalPosition;
		Math::vector mLocalScale;

		Math::bbox   mLocalBB;

		// cache transform and bound
		mutable Math::matrix44 mLocaTrans;
		mutable bool mDirtyLocaTrans;


		mutable Math::quaternion mWorldRotation;
		mutable Math::vector mWorldPosition;
		mutable Math::vector mWorldScale;
		mutable Math::matrix44 mWorldTrans;
		mutable bool mDirtyWorldTrans;

		mutable Math::bbox mWorldBB;
		mutable bool mDirtyWorldBB;

		GPtr<Messaging::Dispatcher> mDispatcher;
		Util::Array<GPtr<Component> > mComponents;
		Util::FixedArray<Util::Array<GPtr<Component> > > mCallbackComponents;

		Actor* mParent;
		Children mChildren;
		
		bool mVisible;
		Resources::Priority mPriority;

		//GPtr<Resources::TemplateResInfo> mTemplateResInfo;

		friend class ActorManager;
		friend class ActorSerialization;
		friend class Scene;

#if NEBULA3_ENABLE_PROFILING
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentActivateDebugTimer;
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentDeactivateDebugTimer;
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentOnBeginFrameDebugTimer;
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentOnMoveBeforeDebugTimer;
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentOnMoveAfterDebugTimer;
		Util::Dictionary<Util::String, GPtr<Debug::DebugTimer> > mComponentOnRenderDebugTimer;

		void _AttachComponentTimer( const Core::Rtti* pRtti );
		void _RemoveComponentTimer( const Core::Rtti* pRtti );
		void _ResetComponentTimer();
#endif

		/// constructor. but use Actor::Create()
		Actor();
	private:


		//internal call.
		/// actor's it's component and all child actor.
		void _Destory(bool forceShutDown = false);

	};

	//------------------------------------------------------------------------
	inline 
		void 
		Actor::SetName(const Util::String& name)
	{
		mName = name;
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		Actor::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Actor::SetTemplateName(const Util::StringAtom& tepName)
	{
		if (tepName.IsValid())
		{
			Util::String str = tepName.AsString();
			str.ToLower();
			if (str == "empty")
			{
				this->mTemplateName = "";
				return;
			}
		}

		this->mTemplateName = tepName;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Util::StringAtom&
		Actor::GetTemplateName() const
	{
		return this->mTemplateName;
	}
	//------------------------------------------------------------------------
	inline 
		bool 
		Actor::IsLinkTemplate(void) const
	{
		return mIsLinkTemplate;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::SetLinkTemplate(bool bLink)
	{
		mIsLinkTemplate = bLink;
	}
	//------------------------------------------------------------------------
	inline
		LayerID 
		Actor::GetLayerID(void) const
	{
		return mLayerID;
	}
	//------------------------------------------------------------------------
	inline
		uint 
		Actor::GetCullMark(void) const
	{
		return 1 << mLayerID;
	}
	//------------------------------------------------------------------------
	inline 
		TagID 
		Actor::GetTagID(void) const
	{
		return mTagID;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		Actor::SetTagID(TagID id)
	{
		mTagID = id;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline bool
		Actor::IsActive() const//bool checkParent/* = true*/
	{
		return mActivated;
		//if (checkParent)
		//{
		//	return mActivated && IsParentActive(true);
		//}
		//else
		//{
		//	return mActivated;
		//}
	}
	//------------------------------------------------------------------------------
	inline bool
		Actor::GetActiveControl() const
	{
		return mActiveControl;
	}

	//------------------------------------------------------------------------------
	inline void
		Actor::SetTmpActiveState(bool tmpActiveState)
	{
		mTmpActiveState = tmpActiveState;
	}

	inline bool
		Actor::GetTmpActiveState()
	{
		return mTmpActiveState;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline uint
		Actor::GetFastId() const
	{
		return this->mFastId;
	}


	//------------------------------------------------------------------------------
	/**
	*/
	inline 
		const Math::vector&
		Actor::GetPosition() const
	{
		return this->mLocalPosition;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
		const Util::Guid& 
		Actor::GetGUID() const
	{
		return this->mGuid;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
		const Math::quaternion&
		Actor::GetRotation() const
	{
		return this->mLocalRotation;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
		const Math::vector&
		Actor::GetScale() const
	{
		return this->mLocalScale;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline bool
		Actor::AcceptsMessage(const Messaging::Id& msgId) const
	{
		return this->mDispatcher->AcceptsMessage(msgId);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Actor::SendSync(const GPtr<Messaging::Message>& msg)
	{
		this->mDispatcher->HandleMessage(msg);
	}
	//------------------------------------------------------------------------
	inline
		const Math::bbox& 
		Actor::GetLocalBoundingBox(void) const
	{
		return mLocalBB;
	}
	//------------------------------------------------------------------------
	inline
		Actor* 
		Actor::GetParent(void) const
	{
		return mParent;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		Actor::GetChildCount(void) const
	{
		return mChildren.Size();
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::Roll(Math::scalar angle )
	{
		Rotate(angle, 0, 0);
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::Pitch(Math::scalar angle )
	{
		Rotate(0, angle, 0);
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::Yaw(Math::scalar angle )
	{
		Rotate(0, 0, angle);
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::Rotate(Math::scalar roll , Math::scalar pitch , Math::scalar yaw  )
	{
		Math::quaternion q = Math::quaternion::rotationyawpitchroll(yaw, pitch, roll);
		SetRotation(q);
	}
	//------------------------------------------------------------------------
	inline
		void
		Actor::OpenComponentsCommSign(ComponetsCommSign sign)
	{
		mComponentsCommSign |= sign;
	}
	//------------------------------------------------------------------------
	inline
		void
		Actor::CloseComponentsCommSign(ComponetsCommSign sign)
	{
		mComponentsCommSign &= (~sign);
	}	
	//------------------------------------------------------------------------
	inline
		bool
		Actor::IsComponentsCommSignOpen(ComponetsCommSign sign)
	{
		return (mComponentsCommSign & sign) != 0;
	}
	//------------------------------------------------------------------------
#ifdef __GENESIS_EDITOR__
	//------------------------------------------------------------------------
	inline
		void 
		Actor::SetQueryMask(uint mask)
	{
		if (mask > 31 || mask < 0)
		{
			n_assert(0);
			return;
		}
		mQueryMask = mask;
	}
	//------------------------------------------------------------------------
	inline
		uint 
		Actor::GetQueryMask() const
	{
		return mQueryMask;
	}
	//------------------------------------------------------------------------
	inline
		const Math::vector& 
		Actor::GetEulerRotation() const
	{
		return mEulerAngle;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Actor::SetEulerRotation(const Math::vector & rot)
	{
		mEulerAngle = rot;
	}
	//------------------------------------------------------------------------	
#endif

	inline bool 
		Actor::CheckEditorFlag (EditorFlag flags)
	{
		return (mEditorFlag & (uint)flags) != 0;
	}
	//------------------------------------------------------------------------
	inline App::Actor::EditorFlag Actor::GetEditorFlag () const
	{
		return (EditorFlag)mEditorFlag;
	}
	//------------------------------------------------------------------------
	inline void Actor::SetEditorFlag (EditorFlag flags)
	{
		mEditorFlag = (uint)flags;
	}

	inline Resources::Priority Actor::GetPriority() const
	{
		return mPriority;
	}

	inline bool Actor::PriorityDefinition() const
	{
		return (Resources::ResourcePriority::Undefinition != mPriority);
	}

	inline bool Actor::PriorityUndefinition() const
	{
		return (Resources::ResourcePriority::Undefinition == mPriority);
	}

	template<typename T>
	GPtr<T> Actor::FindComponent() const
	{
		const GPtr<Component>& obj = this->FindComponent( T::RTTI );
		if ( obj )
		{
			return obj.downcast<T>();
		}
		else
		{
			return GPtr<T>(0);
		}
	}
#ifndef __SCRIPT_COMMIT__
	//-------------------------------------------------------------------------
	template<typename T>
	void Actor::ThrowMessageToScript( const Util::String& name,T& pair )
	{
		TScriptMessagePtr msg = ScriptMessageCreator::Instance()->CreateMessage(name,pair);
		SendSync( msg.upcast<Messaging::Message>() );
	}
#endif

} // namespace Game
//------------------------------------------------------------------------------






#endif // __actor_H__

