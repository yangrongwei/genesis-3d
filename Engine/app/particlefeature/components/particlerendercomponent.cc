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
#include "particlefeature/components/particlerenderobject.h"
#include "particlefeature/components/particlerendercomponent.h"
#include "particlefeature/particlefeatureprotocol.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "particles/particletarget.h"
#include "particles/targets/particleEntityTarget.h"
#include "particles/particleserver.h"
#include "serialization/serializeserver.h"
#include "graphicfeature/graphicsfeature.h"
#include "basegamefeature/managers/timemanager.h"
#include "basegamefeature/managers/timesource.h"
#include "graphicfeature/components/skinnedmeshrendercomponent.h"

#include "particles/affectors/particleLinearForceAffector.h"
#include "particles/affectors/particleTextureRotatorAffector.h"
#include "particles/affectors/particleGravityAffector.h"
#include "particles/affectors/particleVortexAffector.h"
#include "particles/affectors/particleLimitAffector.h"
#include "particles/affectors/particleColorAffector.h"
#include "particles/affectors/particleMovementAffector.h"
#include "particles/affectors/particleTextureAnimatorAffector.h"

#include "particles/emitters/particleSphereSurfaceEmitter.h"
#include "particles/emitters/particleModelEmitter.h"
#include "particles/emitters/particleBoxEmitter.h"
#include "particles/emitters/particleConeEmitter.h"
#include "particles/targets/particlebillboardtarget.h"
#include "particles/targets/particleDecalTarget.h"

#include "graphicfeature/components/skinnedmeshrendercomponent.h"

namespace App
{
	using namespace Resources;
	using namespace Particles;
	using namespace RenderBase;
	using namespace Graphic;

	__ImplementClass(App::ParticleRenderComponent, 'APRC', App::RenderComponent);

	//------------------------------------------------------------------------
	ParticleRenderComponent::ParticleRenderComponent()
		: mIsBuild(false)
		, mIsAttached(false)
		, mIsTrans(false)
		, mPrimitiveResInfo(NULL)
		, mEmitMeshRes(NULL)
		, mShowSimpleShape(false)
		, mSelectTech(0)
		, mTemplateName("sys:Mesh.template")
	{
		mMeshInfo.dirty = false;
		mMeshInfo.meshID = "sys:box.mesh";
		mMeshInfo.priority = Resources::ResourcePriority::Synchronization;
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::InitParticleSystem()
	{
		GPtr<ParticleSystem> ParSystem = ParticleSystem::Create();
		{
			GPtr<SphereSurfaceEmitter> emitter = SphereSurfaceEmitter::Create();
			emitter->getMinMaxCurve(Emitter_SphereRadius)->SetScalar(0.1f);
			ParSystem->SetEmitter( emitter.get() );

			GPtr<ParticleAffector> pAffector = ParticleAffector::Create();
			ParSystem->AddAffector( pAffector.get() ); 

			GPtr<ParticleBillBoardTarget> target = ParticleBillBoardTarget::Create();
			target->SetBillBoardType(ParticleBillBoardTarget::Billboard_Camera);
			ParSystem->SetTarget( target.get() );
		}
		ParSystem->SetName(Util::String("system_14"));
		this->SetParticleSystem(ParSystem);

		//create Matrails
		this->SetMaterialID(0, "sys:Default_Particle.material");
	}
	//------------------------------------------------------------------------
	ParticleRenderComponent::~ParticleRenderComponent()
	{
		mPrimitiveResInfo = NULL;
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::SetupCallbacks(void)
	{
		mActor->RegisterComponentCallback(this, BeginFrame );
		mActor->RegisterComponentCallback(this, OnFrame );
		mActor->RegisterComponentCallback(this, MoveAfter);
		Super::SetupCallbacks();
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
	}

	//------------------------------------------------------------------------
	void ParticleRenderComponent::SetRenderShapeEnable(bool enable)
	{

		//[zhongdaohuan][render_obj

	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::OnActivate()
	{
		if ( mParticleSystem.isvalid() )
		{
			mParticleSystem->Active();

			if ( NULL!=mActor )
			{
				mParticleSystem->SetWorldMatrix( mActor->GetWorldTransform() );
			}
		}

		n_assert( mRenderDates.Size() == 0 ); 

		LoadEmitterMesh();
		BuildRenderData();

		Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent += Delegates::newDelegate(this, &ParticleRenderComponent::_updateTarget);
		Super::OnActivate();
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::OnDeactivate()
	{
		if ( mParticleSystem.isvalid() )
		{
			mParticleSystem->DeActive();
		}

		_DeattachRenderObject();
		DiscardRenderData();
		Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent -= Delegates::newDelegate(this, &ParticleRenderComponent::_updateTarget);
		Super::OnDeactivate();
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::OnDestroy()
	{
		if ( mParticleSystem.isvalid() && mParticleSystem->IsActive() )
		{
			mParticleSystem->DeActive();
		}
		mParticleSystem = NULL;


		_DeattachRenderObject();
		DiscardRenderData();
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::_OnMoveAfter()
	{
		if ( !mActor || !mParticleSystem.isvalid() )
			return;

		if ( !mActor || !mParticleSystem.isvalid() )
			return;

		//const Math::vector& wolrdPos = mActor->GetWorldPosition();
		const Math::matrix44& worldMat = mActor->GetWorldTransform();
		mParticleSystem->SetWorldMatrix(worldMat);

		if (mRenderObject.isvalid())
		{
			mRenderObject->SetTransform(worldMat);
		}

		//if (mSimpleShape.isvalid())
		//{
		//	mSimpleShape->SetTransform(worldMat);
		//}



	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::_OnBeginFrame()
	{
		if ( !mParticleSystem.isvalid() )
			return;

		if ( mMeshInfo.dirty)
		{
			if (CheckMeshChanged() )
			{
				mIsBuild = false;
				mIsAttached = false;
				mMeshInfo.dirty = false;
				_DeattachRenderObject();
			}
		}

		//const GPtr<Actor>& pCamera = GraphicsFeature::Instance()->GetDefaultCameraActor();
		//	if ( pCamera.isvalid() )
		//	mParticleSystem->SetCameraMatrix( pCamera->GetWorldTransform() );

		LoadEmitterMesh();
		BuildRenderData();

		Super::_OnBeginFrame();

	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::OnParticleDataChange()
	{
		_DeattachRenderObject();
		DiscardRenderData();
		BuildRenderData();
	}
	//------------------------------------------------------------------------
	bool ParticleRenderComponent::CheckMeshChanged(void)
	{
		if(mPrimitiveResInfo&& mPrimitiveResInfo->GetHandle().IsValid())
			return true;

		return false;
	}
	//--------------------------------------------------------------------------------
	const GPtr<Resources::MeshRes> ParticleRenderComponent::GetMesh() const
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
	//--------------------------------------------------------------------------------
	void ParticleRenderComponent::LoadEmitterMesh(void)
	{
		const GPtr<ParticleSystem>& parSystem = GetParticleSystem();
		if ( !parSystem.isvalid() )
			return;		


		// load modelEmitter 's meshres
		if ( !parSystem->IsLoadEmitterMesh())
		{
			const GPtr<Particles::ParticleEmitter>& pEmit = parSystem->GetEmitter();
			if(	pEmit.isvalid() && pEmit->IsA( Particles::ModelEmitter::RTTI ) )
			{
				const GPtr<Particles::ModelEmitter>& pModelEmit = pEmit.downcast<Particles::ModelEmitter>();		

				const Resources::ResourceId& meshId= pModelEmit->GetMeshName();
				if("" == meshId.AsString())
					return;
				if ( !mEmitMeshRes || mEmitMeshRes->GetResID() != meshId)
				{
					mEmitMeshRes = Resources::ResourceManager::Instance()->CreatePrimitiveInfo(meshId, Resources::ResourcePriority::MeshDefault);
				}

				if ( mEmitMeshRes->GetHandle().IsValid() )
				{													
					pModelEmit->SetMeshRes(mEmitMeshRes->GetRes());			
				}
			}
		}
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::BuildRenderData(void)
	{
		if ( mIsBuild )
			return;

		mRenderDates.Clear();
		n_assert( mRenderDates.Size() == 0 );

		const GPtr<ParticleSystem>& parSystem = GetParticleSystem();
		if ( !parSystem.isvalid() )
			return;

		const GPtr<Particles::ParticleTarget>& pTarget = parSystem->GetTarget();
		if( !pTarget.isvalid() )
			return;


		if ( pTarget->GetTargetType() == ParticleTarget::Mesh )
		{
			ResourceId& resId = mMeshInfo.meshID;
			Resources::Priority priority = mMeshInfo.priority;
			if ( !mPrimitiveResInfo.isvalid() || mPrimitiveResInfo->GetResID() != resId )
			{
				mPrimitiveResInfo = Resources::ResourceManager::Instance()->CreatePrimitiveInfo( resId, priority);
				return;
			}

			if ( !mPrimitiveResInfo->GetHandle().IsValid() )
				return;

			const GPtr<Resources::Resource>& resource = mPrimitiveResInfo->GetRes();

			if ( resource.isvalid() && resource->GetState() == Resource::Loaded )
			{
				const GPtr<Resources::MeshRes>& meshResource = resource.downcast<Resources::MeshRes>();
				n_assert( meshResource.isvalid() );

				SizeT subMeshCount = meshResource->GetSubMeshCount();
				while ( mRenderableResUnitList.Size() < subMeshCount )
				{
					mRenderableResUnitList.Append(RenderbleResUnit());
					mRenderableResUnitList.Back().CopyFrom( mRenderableResUnitList[0]);
				}

				Math::bbox box;
				box.begin_extend();
				SizeT curMat = 0;
				for ( IndexT subIndex = 0 ; subIndex < subMeshCount; ++subIndex)
				{
					mRenderDates.Append( RenderData());
					RenderData& renderData = mRenderDates.Back();

					renderData.mPartType		= (ushort)ParticleTarget::Mesh;
					renderData.mPrimitiveHandle = mPrimitiveResInfo->GetHandle();
					renderData.mSubmeshIndex	= subIndex;
					renderData.mTargetIndex		= 0;

					const SubMesh* subMesh = meshResource->GetSubMesh(subIndex);
					RenderObjectType::RenderableType* renderable = mRenderableResUnitList[curMat].ResetRenderable<RenderObjectType::RenderableType>();
					_SetRenderable( meshResource, curMat, renderable);

					box.extend( subMesh->box );
					++curMat;
				}
			}
			else
			{
				_DeattachRenderObject();
				return;
			}
		}	
		else
		{
			// just rebuild pool
			int quota = parSystem->GetParticleQuota();
			parSystem->_resetPool( quota );

			mRenderDates.Append( RenderData() );
			RenderData& renderData = mRenderDates[0];
			//renderData.mPrimitiveGroup = PrimitiveGroup::Create();
			renderData.mTargetIndex = 0;
			renderData.mPartType = pTarget->GetTargetType();
			//pTarget->SetPrimitiveGroup( renderData.mPrimitiveGroup );
			pTarget->SetNeedPrimitive(true);

			RenderObjectType::RenderableType* renderable = mRenderableResUnitList[0].ResetRenderable<RenderObjectType::RenderableType>();
			_SetRenderable(NULL, 0, renderable);
		}

		//New RenderObject
		if( !mRenderObject.isvalid() )
		{
			mRenderObject = RenderObjectType::Create();
		}
		mRenderObject->SetOwner(this);
		mRenderObject->SetTransform(mActor->GetWorldTransform());
		_AttachRenderObject();
		mIsBuild = true;
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::DiscardRenderData(void)
	{
		//if ( !mIsBuild )
		//{
		//	n_assert( mRenderDates.IsEmpty() ); 
		//	return;
		//}

		mIsBuild = false;

		SizeT count = mRenderDates.Size();
		for ( IndexT index = 0; index < mRenderDates.Size(); ++index )
		{
			RenderData& renderData = mRenderDates[index];

			if ( renderData.mPrimitiveHandle.IsValid() )
			{
				//GraphicSystem::Instance()->RemovePrimitive( renderData.mPrimitiveHandle );				
				//GraphicObjectManager::Instance()->DiscardPrimitiveHandle( renderData.mPrimitiveHandle );
				const ParticleTargetPtr& target = mParticleSystem->GetTarget();
				if(target.isvalid())
					target->SetDirtyPrim(true);
				renderData.mPrimitiveHandle =  RenderBase::PrimitiveHandle();
			}
		}
		mRenderDates.Clear();
	}

	void ParticleRenderComponent::UpdateRenderLayer()
	{
		if (mRenderObject.isvalid())
		{
			mRenderObject->SetLayerID(mActor->GetLayerID());
		}
	}

	void ParticleRenderComponent::SetVisible(bool bVis)
	{
		mVisible = bVis;
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

	void ParticleRenderComponent::OnRenderSceneChanged()
	{
		if (mRenderObject.isvalid() && mRenderObject->Attached())
		{
			mRenderObject->Attach(mActor->GetRenderScene());
		}
	}

	void ParticleRenderComponent::_AttachRenderObject()
	{
		if(!mVisible)
			return;
		if (mRenderObject.isvalid())
		{
			n_assert(mActor);
			mRenderObject->Attach(mActor->GetRenderScene());
		}

	}

	void ParticleRenderComponent::_DeattachRenderObject()
	{
		if (mRenderObject.isvalid())
		{
			n_assert(mActor);
			mRenderObject->Detach();
		}

	}
	void ParticleRenderComponent::_updateTarget( Graphic::Camera* camera )
	{
		if(mIsBuild)
		{
			mParticleSystem->SetCameraMatrix( camera->GetTransform());
			mParticleSystem->_postProcessParticles();
			UpdateRenderData();	
		}
	}
	void ParticleRenderComponent::_SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable)
	{
		if (meshRes.isvalid())
		{
			SubMesh* subMesh = meshRes->GetSubMesh(index);
			n_assert(subMesh);

			renderable->SetParticleRenderInfo(index, 
				subMesh->firstVertex, 
				subMesh->numVertex,
				subMesh->FirstIndex,
				subMesh->numIndex);
		}
		else
		{
			RenderData& renderdata = mRenderDates[index];
			if ( renderdata.mPrimitiveHandle.IsValid())
			{
				const ParticleTargetPtr& target = mParticleSystem->GetTarget();
				renderable->SetParticleRenderInfo(index,
					0, target->GetActiveVertexCount(), 
					0, target->GetActiveIndexCount());
			}
			else
			{
				renderable->SetParticleRenderInfo(index, 0, 0, 0, 0);
			}
		}
	}
	void 
		ParticleRenderComponent::_UpdateRenderable(IndexT index, SizeT activeVertexCount, SizeT activeIndexCount, RenderObjectType::RenderableType* renderable)
	{
		renderable->SetParticleRenderInfo(index,
			0, activeVertexCount, 
			0, activeIndexCount);
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::UpdateRenderData(void)
	{
		Math::bbox box;	
		for ( IndexT index = 0; index < mRenderDates.Size(); ++index )
		{
			RenderData& renderData = mRenderDates[index];
			RenderObjectType::RenderableType* renderable = mRenderableResUnitList[index].GetRenderableFast<RenderObjectType::RenderableType>();

			if ( renderData.mPartType == ParticleTarget::Mesh )
			{	
				const GPtr<ParticleSystem>& parSystem = GetParticleSystem();
				if ( !parSystem.isvalid() )
					return;

				const ParticleTargetPtr& target = parSystem->GetTarget();
				const GPtr<ParticleEntityTarget>& entityTarget = target.downcast<ParticleEntityTarget>();

				if ( !entityTarget->IsNeedToRender() )
					return;

				GPtr<MeshRes> meshres = mPrimitiveResInfo->GetRes().downcast<MeshRes>();

				if ( meshres.isvalid() && meshres->GetState() == Resource::Loaded )
				{	
					SizeT vertexCount = meshres->GetVertexCount();
					ColorData colorData;
					Math::Color32 color(255,255,255,255);

					ColorData::Elem* elem = meshres->GetVertexData<ColorData>();

					if ( elem == NULL )
					{
						colorData.Fill(0, vertexCount, color );
						if( !meshres->SetVertexData<ColorData>(&colorData[0], vertexCount ) )
							return;
					}

					if ( !renderData.mPrimitiveHandle.IsValid() )
						renderData.mPrimitiveHandle = mPrimitiveResInfo->GetHandle();
					else 
						GraphicObjectManager::Instance()->UpdataPrimitiveHandle(meshres);

					if( renderData.mSubmeshIndex >= meshres->GetSubMeshCount())
						continue;

					_SetRenderable(meshres, index, renderable);

					Math::bbox particleBox = mParticleSystem->GetBoundingBox();
					box.extend(particleBox);
				}

			}// end: if ( renderData.mPartType == ParticleTarget::Mesh )
			else
			{
				const ParticleTargetPtr& target = mParticleSystem->GetTarget();
				if (target.isvalid())
				{
					if (target->IsDirtyPrim())
					{
						renderData.mPrimitiveHandle = mParticleSystem->GetTarget()->GetPrimitiveHandle();
						target->SetDirtyPrim(false);
					}
					_UpdateRenderable(index, target->GetActiveVertexCount(), target->GetActiveIndexCount(), renderable);
				}
				else
				{
					_UpdateRenderable(index, 0, 0, renderable);
				}

				Math::bbox particleBox = mParticleSystem->GetBoundingBox();
				box.extend(particleBox);

			}//end: if ( renderData.mPartType != ParticleTarget::Mesh )

		}//end: for ( IndexT index = 0; index < mRenderDates.Size(); ++index )
		box.end_extend();
		mRenderObject->SetBoundingBox(box);
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::_OnFrame()
	{

	}

	//------------------------------------------------------------------------
	void ParticleRenderComponent::GetTargetInfo(ushort& partType,Util::Array<Math::matrix44>& mMats, Util::Array<Math::float4>& mColors)
	{
		const GPtr<ParticleSystem>& parSystem = GetParticleSystem();
		if ( !parSystem.isvalid() )
			return ;

		const GPtr<Particles::ParticleTarget>& pTarget = parSystem->GetTarget();
		if( !pTarget.isvalid() )
			return ;

		partType = pTarget->GetTargetType();

		if ( partType == ParticleTarget::Mesh )
		{
			GPtr<Particles::ParticleEntityTarget> entityTar = pTarget.downcast<ParticleEntityTarget>();

			mMats.AppendArray( entityTar->GetMatrixList());
			mColors.AppendArray( entityTar->GetColorList());
		}
		else if ( partType == ParticleTarget::Decal )
		{
			GPtr<Particles::ParticleDecalTarget> decalTar = pTarget.downcast<ParticleDecalTarget>();

			mMats.Append( decalTar->GetDecalRotation());
			mColors.Append( Math::float4(1.0f,1.0f,1.0f,1.0f));
		}
		else
		{
			mMats.Append( Math::matrix44::identity());
			mColors.Append( Math::float4(1.0f,1.0f,1.0f,1.0f));
		}
	}

	//------------------------------------------------------------------------
	void ParticleRenderComponent::CalculateBBox(Math::bbox& box,const Util::Array<Math::matrix44>& matlist) 
	{
		SizeT PosIndex = 0;
		while (PosIndex < matlist.Size())
		{
			Math::float4 curPos = matlist[PosIndex].get_position();
			box.extend(curPos);
			PosIndex++;
		}
	}
	//--------------------------------------------------------------------------------
	void ParticleRenderComponent::RemoveShader( IndexT iSubMesh )
	{
		if ( iSubMesh < 0  )
		{
			return;
		}

		//whether need to determine the render type is entity target
		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			// delete the renderable from graphic system
			mRenderableResUnitList.EraseIndex(iSubMesh);
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::SetParticleSystem( const GPtr<Particles::ParticleSystem>& parSystem )
	{
		if ( mParticleSystem == parSystem )
		{
			return;
		}

		if ( mParticleSystem.isvalid()  )
		{
			if ( mParticleSystem->IsActive() )
			{
				mParticleSystem->DeActive();
			}
		}

		mParticleSystem = parSystem;

		if ( mParticleSystem.isvalid() )
		{
			if ( IsActive() )
			{
				mParticleSystem->Active();
			}
		}

		OnParticleSystemChange();
	}
	//--------------------------------------------------------------------------------
	void ParticleRenderComponent::SetEmitMeshRes(const Resources::ResourceId& meshID, int techIdx , int emitIdx  )
	{

		const GPtr<ParticleSystem>& parSystem = GetParticleSystem();
		if ( !parSystem.isvalid() )
			return;		

		const GPtr<Particles::ParticleEmitter>& pEmit = parSystem->GetEmitter();

		if(	pEmit.isvalid() && pEmit->IsA( Particles::ModelEmitter::RTTI ) )
		{
			const GPtr<Particles::ModelEmitter>& pModelEmit = pEmit.downcast<Particles::ModelEmitter>();
			pModelEmit->SetMeshName(meshID.AsString());
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleRenderComponent::OnParticleSystemChange()
	{
		if ( mActor )
		{
			GPtr<ParticleComponentChangeMsg> msg = ParticleComponentChangeMsg::Create();
			mActor->SendSync( msg.upcast<Messaging::Message>() );
		}
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		GPtr<ParticleRenderComponent> pSource = pComponent.downcast<ParticleRenderComponent>();	

		SetMeshID(pSource->GetMeshID(), pSource->GetMeshLoadPriority());
		mTemplateName =  pSource->GetTemplateID();

		ParticleSystemPtr newPartSystem = ParticleSystem::Create();
		newPartSystem->CopyFrom(pSource->GetParticleSystem());
		SetParticleSystem(newPartSystem);	

		Super::CopyFrom( pComponent );
	}
	//------------------------------------------------------------------------------
	void ParticleRenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		if (mEmitMeshRes.isvalid())
		{
			list.Append(ReferenceResource(mEmitMeshRes->GetResID(), Resources::RR_Unknown));
		}

		list.Append(ReferenceResource(mTemplateName, Resources::RR_Unknown));
		Super::GetReferenceResourceId(list);
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::SetMeshID(const Resources::ResourceId& meshID, Resources::Priority priority )
	{
		if( mMeshInfo.meshID != meshID )
		{
			if (mActor && mActor->PriorityDefinition())
			{
				priority = mActor->GetPriority();
			}
			mMeshInfo.meshID = meshID;
			mMeshInfo.priority = priority;
			mMeshInfo.dirty = true;
		}
	}
	//------------------------------------------------------------------------
	void ParticleRenderComponent::SetTemplateID( const Resources::ResourceId& templateID )
	{
		mTemplateName = templateID;
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& ParticleRenderComponent::GetTemplateID( void ) const
	{
		return mTemplateName;
	}

}
