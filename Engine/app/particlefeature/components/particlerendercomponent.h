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
#ifndef __particlerendercomponent_H__
#define __particlerendercomponent_H__

#include "graphicfeature/components/rendercomponent.h"
#include "particlefeature/components/particlerenderobject.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "particles/particlesystem.h"
#include "resource/meshres.h"

namespace App
{
	class ParticleRenderComponent: public RenderComponent
	{
		__DeclareSubClass(ParticleRenderComponent, RenderComponent );
	public:
		ParticleRenderComponent();
		virtual ~ParticleRenderComponent();

		/// setup callbacks for this Component, call by Actor in OnActivate()
		virtual void SetupCallbacks(void);

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		virtual void UpdateRenderLayer();

		virtual void SetVisible(bool bVis);

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		void GetTargetInfo(ushort&   partType ,  Util::Array<Math::matrix44>& mMats, Util::Array<Math::float4>& mColors);

		void CalculateBBox(Math::bbox& box, const Util::Array<Math::matrix44>& matlist) ;

		bool IsSetTransParam() const ;

		/// delete shader iD
		void RemoveShader( IndexT iSubMesh );

		const GPtr<Particles::ParticleSystem>& GetParticleSystem(void) const;

		/// Init Method
		void InitParticleSystem();
		/// Do not use this Method. except use a temp ParticleSystem 
		void SetParticleSystem( const GPtr<Particles::ParticleSystem>& parSys);

		/// set meshid 
		void SetMeshID(const Resources::ResourceId& meshID, Resources::Priority priority = Resources::ResourcePriority::MeshDefault );

		/// get meshid 
		const Resources::ResourceId& GetMeshID(void) const;

		/// set meshid 
		void SetTemplateID(const Resources::ResourceId& templateID);

		/// get meshid 
		const Resources::ResourceId& GetTemplateID(void) const;

		/// get meshloadpriority
		const int GetMeshLoadPriority(void) const;

		/// set emitter meshid 
		void SetEmitMeshRes(const Resources::ResourceId& meshID, int techIdx = 0, int emitIdx = 0 );

		/// get emitter meshid 
		const Resources::ResourceId& GetEmitMeshID(void) const;

		/// 
		const GPtr<Resources::MeshRes> GetMesh() const;

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		struct RenderData
		{
			ushort	mPartType;
			ushort	mSubmeshIndex;
			ushort	mTargetIndex;
			RenderBase::PrimitiveHandle mPrimitiveHandle;
		};
		const RenderData* GetRenderData( IndexT index) const ;

		void OnParticleDataChange();

		void NeedUpdate();
	protected:		
		typedef ParticleRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> ParticleRenderObjectPtr;

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		// @Component::_OnDestroy called only form Actor::Destroy
		virtual void OnDestroy();

		virtual void OnRenderSceneChanged();

		virtual void _OnBeginFrame();

		virtual void _OnFrame();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

		void BuildRenderData(void);

		void DiscardRenderData(void);

		void UpdateRenderData(void);

		bool CheckMeshChanged(void);

		void OnParticleSystemChange();

		void SetRenderShapeEnable(bool enable);

		void _SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable);

		void _UpdateRenderable(IndexT index, SizeT activeVertexCount, SizeT activeIndexCount, RenderObjectType::RenderableType* renderable);

		void LoadEmitterMesh(void);

		void _AttachRenderObject();

		void _DeattachRenderObject();

		void _updateTarget(Graphic::Camera* camera);
	protected:		

		Util::Array<RenderData>					mRenderDates;

		GPtr<Resources::PrimitiveResInfo>		mPrimitiveResInfo;

		GPtr<Resources::PrimitiveResInfo>		mEmitMeshRes;

		friend class ParticleRenderer;

		GPtr<Particles::ParticleSystem>			mParticleSystem;

		Graphic::MeshInfo						mMeshInfo;
		ParticleRenderObjectPtr					mRenderObject;
		IndexT									mSelectTech;

		Resources::ResourceId					mTemplateName;

		bool									mShowSimpleShape;		

		bool									mIsBuild;
		bool									mIsAttached;
		bool									mIsTrans;
	};
	//------------------------------------------------------------------------
	inline
		const ParticleRenderComponent::RenderData* 
		ParticleRenderComponent::GetRenderData( IndexT index) const 
	{
		if ( index >= 0 && index < mRenderDates.Size() )
		{
			return &( mRenderDates[index] );
		}
		else
		{
			return NULL;
		}
	}
	//-------------------------------------------------------------------------
	inline bool ParticleRenderComponent::IsSetTransParam() const
	{
		return mIsTrans;
	}
	//------------------------------------------------------------------------
	inline
		const GPtr<Particles::ParticleSystem>&
		ParticleRenderComponent::GetParticleSystem(void) const
	{
		return mParticleSystem;
	}
	//------------------------------------------------------------------------
	inline
		const Resources::ResourceId& 
		ParticleRenderComponent::GetMeshID( void ) const
	{
		return mMeshInfo.meshID;
	}

	//------------------------------------------------------------------------
	inline
		const int 
		ParticleRenderComponent::GetMeshLoadPriority(void) const
	{
		return mMeshInfo.priority;
	}
	//------------------------------------------------------------------------
	inline
		const Resources::ResourceId& 
		ParticleRenderComponent::GetEmitMeshID( void ) const
	{
		return mEmitMeshRes->GetResID();
	}
	//------------------------------------------------------------------------
	inline void ParticleRenderComponent::NeedUpdate()
	{
		mParticleSystem->_NeedUpdate();
	}
}

#endif // __particlerendercomponent_H__
