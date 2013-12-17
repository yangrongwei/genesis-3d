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
#ifndef __meshrendercomponent_H__
#define __meshrendercomponent_H__

#include "graphicfeature/components/rendercomponent.h"
#include "graphicsystem/Material/materialinstance.h"
#include "resource/resourcemanager.h"
//#include "addons/resource/meshres.h"
#include "graphicfeature/components/meshrenderobject.h"
#include "Lightmap/lightmapSetting.h"

namespace App
{
	class MeshRenderComponent: public App::RenderComponent
	{
		__DeclareSubClass(MeshRenderComponent, App::RenderComponent);
	public:
		MeshRenderComponent();
		virtual ~MeshRenderComponent();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		virtual void StandaloneRender(const GPtr<Graphic::Material>& customMat);

		virtual void UpdateRenderLayer();

		virtual void SetVisible(bool bVis);

		virtual void SetupAllResource();

		virtual bool IsAllResourceLoaded();

		const RenderBase::PrimitiveHandle& GetPrimitiveHandle() const;

		// get resource
		const GPtr<Resources::PrimitiveResInfo>& GetPrimtiveResInfo() const;

		const GPtr<Resources::MeshRes> GetMesh() const;

		void UpdateTransformMatrix();

		/// set meshid 
		void SetMeshID(const Resources::ResourceId& meshID, Resources::Priority priority = Resources::ResourcePriority::MeshDefault, 
			bool bUsedForResHotLoad = false);

		const Resources::ResourceId& GetMeshID() const;

		Resources::Priority GetPriority() const;

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		const Math::float4& GetLMTexParam() const;
		void  SetLMTexParam( const Math::float4& texParam );
		
		double GetLMScale() const;
		void SetLMScale(double lmscale);

		void SetLMIndex(int index);
		unsigned int  GetLMIndex() const;
		
		void SetLMDirty();
		
		bool IsUseLM() const;
		const RenderBase::TextureHandle& GetLMTextureHandle();
		const bool IsLMTextureHandleValid() const;

		void SetDrawDepth(bool bDraw);

		const bool IsDrawDepth() const;

		/// list all reference resource ids
		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		Math::bbox GetLocalBoundingBox();

	protected:
		typedef MeshRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> MeshRenderObjectPtr;

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		// @Component::_OnDestroy called only form Actor::Destroy
		virtual void OnDestroy();

		virtual void OnRenderSceneChanged();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

		/// @Component::_OnBeginFrame called after movement has happened. 
		virtual void _OnBeginFrame();

		virtual void _OnWillRenderObjectEvent_Change(bool bind);


		virtual void _LoadRenderData();


		virtual void _BuildRenderRes();

		virtual void _BuildRenderObject();

		void _SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable);


		virtual void _OnMeshDirty(bool bDeleteRenderObject = false);

		void _AttachRenderObject();

		void _DeattachRenderObject();


		virtual void _UpdateShadow();

		Graphic::MeshInfo mMeshInfo;
		MeshRenderObjectPtr mRenderObject;
		RenderBase::PrimitiveHandle mPrimitive;
		GPtr<Resources::PrimitiveResInfo> mPrimitiveResInfo;
		bool mMeshLoading;

		// lightmap Texture param
		Math::float4 mLMTexParam;
		unsigned int mLMIndex;
		bool  mLMDirty;
		double mLMScale;
		RenderBase::TextureHandle mLMHandle;

		bool m_bDrawDepth;

		bool m_bUsedForResHotLoad;
		Util::Dictionary<IndexT, Resources::ResourceId> mDeattachedMatList;
	};

	inline
		const GPtr<Resources::PrimitiveResInfo>& MeshRenderComponent::GetPrimtiveResInfo() const
	{
		return mPrimitiveResInfo;		 
	}
	inline
		const GPtr<Resources::MeshRes> MeshRenderComponent::GetMesh() const
	{
        if (!mPrimitiveResInfo || !mPrimitiveResInfo->GetRes().isvalid())
		{
			return NULL;
		}
		else
		{
			return mPrimitiveResInfo->GetRes().downcast<Resources::MeshRes>();
		}
	}
	
	inline
		const Resources::ResourceId& MeshRenderComponent::GetMeshID() const
	{
		return mMeshInfo.meshID;
	}

	inline
		Resources::Priority MeshRenderComponent::GetPriority() const
	{
		return mMeshInfo.priority;
	}

	inline
		const RenderBase::PrimitiveHandle& MeshRenderComponent::GetPrimitiveHandle() const
	{
		return mPrimitiveResInfo->GetHandle();
	}

	inline
		const bool MeshRenderComponent::IsDrawDepth() const
	{
		return m_bDrawDepth;
	}

	inline 
		const Math::float4& MeshRenderComponent::GetLMTexParam() const 
	{
		return mLMTexParam; 
	}

	inline 
		void  MeshRenderComponent::SetLMTexParam( const Math::float4& texParam )
	{
		if (texParam != mLMTexParam)
		{
			mLMTexParam = texParam;
			mLMDirty = true;
		}
	}

	inline 
	    double MeshRenderComponent::GetLMScale() const
	{
		return mLMScale;
	}

	inline 
		void MeshRenderComponent::SetLMScale(double lmscale)
	{
		mLMScale = lmscale;
	}

	inline 
		unsigned int  MeshRenderComponent::GetLMIndex() const 
	{ 
		return mLMIndex; 
	}

	inline 
		void MeshRenderComponent::SetLMIndex(int index)
	{
		if ( index != mLMIndex)
		{
			mLMIndex = index;
			mLMDirty = true;
		}
	}
	
	inline 
		void MeshRenderComponent::SetLMDirty()
	{
		mLMDirty = true;
	}

	inline
		const RenderBase::TextureHandle& MeshRenderComponent::GetLMTextureHandle()
	{
		if (mLMDirty)
		{
			if ( IsUseLM() )
			{
				mLMHandle = LightmapSetting::GetInstance().GetLightmapTexHandle( mLMIndex );
			}
			else
			{
				mLMHandle = RenderBase::TextureHandle();
			}

			mLMDirty = false;
		}

		return mLMHandle;
	}

	inline
		bool MeshRenderComponent::IsUseLM() const
	{ 
		return mLMIndex != 0xFFFF;
	}

	inline 
		const bool MeshRenderComponent::IsLMTextureHandleValid() const
	{
		if ( mLMDirty )
		{
			if ( IsUseLM() )
				return LightmapSetting::GetInstance().GetLightmapTexHandle( mLMIndex ).IsValid();
			else
				return false;
		}
		else
			return mLMHandle.IsValid();
	}
}



#endif // __meshrendercomponent_H__
