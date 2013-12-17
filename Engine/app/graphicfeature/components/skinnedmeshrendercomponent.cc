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
#include "graphicfeature/components/skinnedmeshrendercomponent.h"
#include "graphicfeature/components/skeletoncomponent.h"
#include "graphicfeature/components/animationcomponent.h"
#include "graphicfeature/graphicsfeatureprotocol.h"

#include "animation/AnimationServer.h"

#include "graphicfeature/graphicsfeature.h"
#include "rendersystem/RenderSystem.h"
#include "graphicsystem/GraphicSystem.h"
#include "foundation/math/float3.h"

#include "util/stl.h"

#include "graphicsystem/GraphicObjectManager.h"

#define MaxSupportedBones 60

namespace App
{
	__ImplementClass(App::SkinnedMeshRenderComponent, 'SMRC', App::MeshRenderComponent)

		using namespace Animations;
	using namespace Resources;
	using namespace RenderBase;
	using namespace Graphic;
	const Math::matrix44 SkinnedMeshRenderComponent::m_IndentityMatrix;

	SkinnedMeshRenderComponent::SkinnedMeshRenderComponent()
		: m_bHasRecorded(false)
		, m_bReserveFinalTrans(false)
		, m_pVertexDataPtr(NULL)
		, m_SkeletonCom(NULL)
		, m_AniamtionCom(NULL)
		, m_UpdateState(US_Lack)
	{
		mResourcePrior = 1;
	}

	SkinnedMeshRenderComponent::~SkinnedMeshRenderComponent()
	{
		_Destroy();
	}

	void SkinnedMeshRenderComponent::OnActivate()
	{
		Super::OnActivate();
		if (mPrimitiveResInfo.isvalid() && mPrimitiveResInfo->GetHandle().IsValid())//check mesh loaded
		{
			mMeshLoading = true;
			_BuildRenderRes();

		}
		Actor::Check_Skin(this);
	}

	void SkinnedMeshRenderComponent::OnDeactivate()
	{
		Super::OnDeactivate();
		_Destroy();
	}

	void SkinnedMeshRenderComponent::_Destroy()
	{
		if (m_pVertexDataPtr != NULL)
		{
			n_delete_array(m_pVertexDataPtr);
			m_pVertexDataPtr = NULL;
		}
		m_VertsRecord.Clear();
	}


	void SkinnedMeshRenderComponent::SetupCallbacks()
	{	
		mActor->RegisterComponentCallback(this, OnFrame);
		Super::SetupCallbacks();
	}

	void SkinnedMeshRenderComponent::_ResetSkinnedMatrices()
	{
		for ( IndexT index = 0; index < mRenderableResUnitList.Size(); ++index )
		{
			RenderObjectType::RenderableType* smr = mRenderableResUnitList[index].GetRenderableFast<RenderObjectType::RenderableType>();
			if (smr)
			{
				SizeT size = smr->GetAffectedBonesCount();
				if (size > MaxSupportedBones)
				{
					size = MaxSupportedBones;
				}
				else if (!size)
				{
					smr->SetHWSkinning(false);
				}
				smr->ResetFinalMatrix(size);
			}
		}
	}

	void SkinnedMeshRenderComponent::_Update()
	{
		if (!mMeshLoading)
		{
#ifdef __GENESIS_EDITOR__
			if (_BuildToRootXForms())
			{
				_Skinning();
			}
			else if(!m_AniamtionCom->IsAnyAnimationPaused() && !m_AniamtionCom->IsAnyAnimationPlaying())
			{
				if (_BuildDefaultToRootXFroms())
				{
					_Skinning();

				}else
				{
					_ResetSkinnedMatrices();
				}
			}
			else
			{
				_ResetSkinnedMatrices();
			}
#else 
			if (_BuildToRootXForms())
			{
				_Skinning();
			}
			else
			{
				_ResetSkinnedMatrices();
			}
#endif 
		}
	}
	void SkinnedMeshRenderComponent::_ForceUpdate()
	{
		if (m_AniamtionCom && 1 == m_AniamtionCom->GetClientCount())
		{
			m_AniamtionCom->ForceUpdate();
		}
		_Update();
	}

	void SkinnedMeshRenderComponent::_NeedUpdate()
	{

		switch(m_UpdateState)
		{
		case US_HadUpdated:
			{
				m_UpdateState = US_Update;
			}
			break;
		case US_Stop:
			{
				_ForceUpdate();
				if (m_AniamtionCom)
				{
					m_AniamtionCom->ClientAdd();
				}
				m_UpdateState = US_Update;
			}
			break;
		case US_Update:
			break;
		default:
			m_UpdateState = US_Lack;
			break;
		}

	}

	void SkinnedMeshRenderComponent::_OnFrame()
	{
		switch(m_UpdateState)
		{
		case US_Update://Need update
			{
				_Update();
				m_UpdateState = US_HadUpdated;
			}
			break;
		case US_HadUpdated://Has updated, no need update
			{
				if (m_AniamtionCom)
				{
					m_AniamtionCom->ClientSub();
				}
				m_UpdateState = US_Stop;
			}
			break;
		default:
			break;
		}
	}

	void SkinnedMeshRenderComponent::_CheckState()
	{
		if (NULL == m_SkeletonCom || NULL == m_AniamtionCom)
		{
			m_UpdateState = US_Lack;
		}
		else
		{
			if (US_Lack == m_UpdateState)
			{
				m_UpdateState = US_Stop;
			}
		}
	}

	void SkinnedMeshRenderComponent::SetSkeleton(SkeletonComponent* skeleton)
	{
		m_SkeletonCom = skeleton;
		_CheckState();
	}



	void SkinnedMeshRenderComponent::SetAnimation(AnimationComponent* animation)
	{
		if (US_Update == m_UpdateState || US_HadUpdated == m_UpdateState)
		{
			if (m_AniamtionCom)
			{
				m_AniamtionCom->ClientSub();
			}
			if (animation)
			{
				animation->ClientAdd();
			}
		}

		m_AniamtionCom = animation;
		_CheckState();
	}

	void SkinnedMeshRenderComponent::_BuildRenderObject()
	{
		//build new RenderObject
		if (!mRenderObject.isvalid())
		{
			const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();
			GPtr<RenderObjectType> skin = RenderObjectType::Create();
			mRenderObject = skin.downcast<Super::RenderObjectType>();
			mRenderObject->SetOwner(this);
		}
	}

	void SkinnedMeshRenderComponent::_SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable)
	{
		const Util::Array<uchar>& bonesArray = meshRes->GetAffectedBonesIndex(index);
		renderable->SetAffectedBones(bonesArray);
		renderable->UpdateRegIndexOfAffected();
		SizeT size = bonesArray.Size();
		if (size > MaxSupportedBones)
		{
			size = MaxSupportedBones;
		}
		renderable->ResetFinalMatrix(size);
		Super::_SetRenderable(meshRes, index, renderable);
	}

	void SkinnedMeshRenderComponent::_BuildRenderRes()
	{
		n_assert( mActor );
		n_assert( mMeshLoading );
		_Destroy();
		const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();

		_BuildRenderObject();

		mRenderObject->SetTransform(mActor->GetWorldTransform());
		mRenderObject->SetBoundingBox(meshRes->GetBoundingBox());
		UpdateRenderLayer();


		// splited subMesh should use correct material
		Util::Array<uint>& submeshUsedMaterial = meshRes->GetSubmeshUsedMaterial();
		if ( submeshUsedMaterial.Size() > 0 )
		{
			n_assert( submeshUsedMaterial.Size() == mRenderableResUnitList.Size() );

			int curCount(0);
			Graphic::RenderableResUnitArray tempRenderableResUnit;
			for( IndexT idx = 0; idx < submeshUsedMaterial.Size(); ++idx)
			{
				curCount	 = submeshUsedMaterial[idx];
				for ( int i = 0; i < curCount; i++ )
				{				
					tempRenderableResUnit.Append(Graphic::RenderbleResUnit() );
					RenderbleResUnit& renderableUnit = tempRenderableResUnit.Back();
					renderableUnit.SetResInfo(mRenderableResUnitList[idx].GetResInfo());				
				}
			}
			mRenderableResUnitList.Swap(tempRenderableResUnit);
		}


		int sub_count = meshRes->GetSubMeshCount();
		int mat_count = mRenderableResUnitList.Size();	


		if(m_bUsedForResHotLoad)
		{
			//when hot load, if material count more than 1, should record other materials, and load when file reload

			// add to material list
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

			// delete materials not used
			for (int i = mat_count - 1 ; i >= sub_count; --i)
			{
				mDeattachedMatList.Add(i,GetMaterialID(i));
				mRenderableResUnitList.EraseIndex(i);
			}
		}
		else
		{
			mDeattachedMatList.Clear();

			// add to material list
			for ( IndexT index = mat_count; index < sub_count; ++index )
			{
				SetMaterialID(index,"sys:meshRenderDefault.material", false);
			}

			// delete materials not used
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

	void SkinnedMeshRenderComponent::_BuildOriginalVertices(const GPtr<Resources::MeshRes> &mesh)
	{
		n_assert(mesh.isvalid());

		// must has vertex and index
		if ( mesh->GetIndexCount() == 0 
			|| mesh->GetVertexCount() == 0 
			|| mesh->GetTopologyType() == RenderBase::PrimitiveTopology::InvalidPrimitiveTopology )
		{
			n_error("error:SkinnedMeshRenderComponent::_BuildPrimitive(const GPtr<Resources::MeshRes> &mesh): must have vertex and index!");
			return;
		}

		//// @todo: add check which vertex prams are¡¡current hardware or shader can use

		// copy vertex data
		Graphic::GraphicSystem* gs = Graphic::GraphicSystem::Instance();
		RenderBase::VertexComponents vcs;
		gs->GetVertexComponents(mPrimitive, vcs);


		m_pVertexDataPtr = _BuildOriginalVertices( mesh, vcs, m_nVerticeCount, m_VertexDataSize);
		if ( m_pVertexDataPtr == NULL )
		{
			n_error("error:SkinnedMeshRenderComponent::_BuildPrimitive(const GPtr<Resources::MeshRes> &mesh): m_pVertexDataPtr is NULL!");
			return;
		}
		RenderBase::VERTEX_DESC desc;
		gs->GetVertexDesc(mPrimitive, desc);
		Graphic::VertexBufferData2 vbd2;
		vbd2.Setup(m_nVerticeCount, m_VertexDataSize / m_nVerticeCount, RenderBase::BufferData::Dynamic, mesh->GetTopologyType(), true);
		vbd2.SetVertices(m_pVertexDataPtr, m_nVerticeCount);

		gs->ChangePrimitiveHandle(mPrimitive, &vbd2, NULL);

		m_VertsRecord.Reserve(m_nVerticeCount);

	}

	bool SkinnedMeshRenderComponent::_BuildVertexComponent(const GPtr<Resources::MeshRes>& mesh, Util::Array<RenderBase::VertexComponent>& verDeclare)
	{
		n_assert(mesh);

		if( mesh->GetVertexData<PositionData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Position,0, VertexComponent::Float3) );
		}

		if ( mesh->GetVertexData<NormalData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Normal,0, VertexComponent::Float3) );
		}

		if ( mesh->GetVertexData<ColorData>() )
		{
			//if ( RenderSystem::Instance()->GetRendererType() == eRendererD3D9 )
			if(true)
			{
				verDeclare.Append( VertexComponent(VertexComponent::Color,0, VertexComponent::ColorBGRA) );
			}
			else
			{
				n_error(" should decide device use bgra or rgba");
			}
		}

		const SizeT deviceSupportTexCount = 8;	// should defined by render system
		for ( IndexT iTex = 0; iTex < deviceSupportTexCount; ++iTex )
		{
			if ( mesh->GetVertexData<TexCoordData>(iTex) )
			{
				verDeclare.Append( VertexComponent(VertexComponent::TexCoord, iTex, VertexComponent::Float2) );
			}
			else
			{
				break;
			}
		}

		if( mesh->GetVertexData<TangentData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Tangent,0, VertexComponent::Float4) );
		}

		if ( mesh->GetVertexData<BiNormalData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Binormal,0, VertexComponent::Float4) );
		}

		if ( mesh->GetVertexData<BoneInfoData>() )
		{
			// SkinJIndices and SkinWeights must exist in same time, and copy at same time lately
			verDeclare.Append( VertexComponent(VertexComponent::SkinJIndices,0, VertexComponent::Short4) );
			verDeclare.Append( VertexComponent(VertexComponent::SkinWeights,0, VertexComponent::Float4) );
		}

		return !verDeclare.IsEmpty();
	}

	template<typename T, SizeT elemSize >
	void StripeCopy( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			Memory::Copy( from, to, elemSize );
			++from;
			to += toElemsSize;
		}
	}

	template<typename T , SizeT elemSize >
	void StripeSwapCopyColor( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );	// color is 4 byte

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			*((int*)to) = ((Color32*)from)->HexARGB();

			++from;
			to += toElemsSize;
		}
	}

	uchar* SkinnedMeshRenderComponent::_BuildOriginalVertices(const GPtr<Resources::MeshRes>& mesh, const Util::Array<VertexComponent> &verDeclare, SizeT& numVertices, SizeT& vertexDataSize)
	{
		n_assert( mesh.isvalid() );
		numVertices = mesh->GetVertexCount();
		n_assert( numVertices > 0 );
		n_assert( !verDeclare.IsEmpty() );
		// each vertex's size
		SizeT VertexSize = 0;
		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			VertexSize += verDeclare[index].GetByteSize();
		}
		n_assert( VertexSize > 0 );

		vertexDataSize = VertexSize * numVertices;
		uchar* vertexDataPtr = new uchar[vertexDataSize];
		n_assert( vertexDataPtr );

		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			_AnalysisVBOComponent(mesh, verDeclare[index], VertexSize);
		}

		n_assert( vertexDataPtr );
		GraphicObjectManager::CopyVBOData(mesh, verDeclare, VertexSize, numVertices, vertexDataPtr);

		return vertexDataPtr;
	}

	void SkinnedMeshRenderComponent::_AnalysisVBOComponent(const GPtr<MeshRes> &mesh, const VertexComponent &vcdef, SizeT VertexSize)
	{
		switch( vcdef.GetSemanticName() )
		{
		case VertexComponent::Position:
			{
				//PositionData::Elem* elem = mesh->GetVertexData<PositionData>();
				n_assert( vcdef.GetByteSize() == 12 );
				//StripeCopy<PositionData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

				m_VertexPosSize       = VertexSize;
				m_VertexPosByteOffset = vcdef.GetByteOffset();
			}
			break;
		case VertexComponent::Normal:
			{
				//NormalData::Elem* elem = mesh->GetVertexData<NormalData>();
				n_assert( vcdef.GetByteSize() == 12 );
				//StripeCopy<NormalData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

				m_VertexNormalSize       = VertexSize;
				m_VertexNormalByteOffset = vcdef.GetByteOffset();
			}
			break;
		case VertexComponent::Tangent:
			{
				TangentData::Elem* elem = mesh->GetVertexData<TangentData>();
				n_assert( vcdef.GetByteSize() == 16 );
				//StripeCopy<TangentData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Binormal:
			{
				BiNormalData::Elem* elem = mesh->GetVertexData<BiNormalData>();
				n_assert( vcdef.GetByteSize() == 16 );
				//StripeCopy<BiNormalData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::TexCoord:
			{
				//TexCoordData::Elem* elem = mesh->GetVertexData<TexCoordData>( vcdef.GetSemanticIndex() );
				//n_assert( vcdef.GetByteSize() == 8 );
				//StripeCopy<TexCoordData::Elem,8>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Color:
			{
				//ColorData::Elem* elem = mesh->GetVertexData<ColorData>( vcdef.GetSemanticIndex() );

				//n_assert( vcdef.GetByteSize() == 4 );
				//if ( vcdef.GetFormat() == VertexComponent::ColorRGBA )
				//{
				//	StripeCopy<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				//}
				//else if(  vcdef.GetFormat() == VertexComponent::ColorBGRA )
				//{
				//	StripeSwapCopyColor<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				//	//StripeCopy<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				//}
				//else
				//{
				//	n_assert(" GraphicObjectManager|copyVBOComponent: unknown color format" );
				//}

			}
			break;
		case VertexComponent::SkinJIndices:
			{
				//BoneInfoData::Elem* elem = mesh->GetVertexData<BoneInfoData>( vcdef.GetSemanticIndex() );

				//// when has SkinJIndices, must has SkinWeights, copy them at same time
				//n_assert( vcdef.GetByteSize() == 8 );
				//StripeCopy<BoneInfoData::Elem,24>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

				m_BoneInfoIndex = vcdef.GetSemanticIndex();
			}
			break;
		case VertexComponent::SkinWeights:
			{
				//n_assert( vcdef.GetByteSize() == 16 );
			}
			break;
		default:
			n_error("GraphicObjectManager|copyVBOComponent: invalid VertexComponent::SemanticName\n");
		}
		return;
	}

	bool SkinnedMeshRenderComponent::_BuildDefaultToRootXFroms()
	{
		if (AnimationServer::Instance()->IsStop() || !m_SkeletonCom || !m_AniamtionCom)
		{
			return false;
		}

		GPtr<Actor> actorParent = mActor->GetParent();
		if(actorParent.isvalid())
		{
			GPtr<Component> com = actorParent->FindComponent(AnimationComponent::RTTI);
			if(com.isvalid())
			{
				GPtr<AnimationComponent> animCom = com.downcast<AnimationComponent>();
				if(m_AniamtionCom != animCom)
					return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		const GPtr<SkeletonRes>& skeletonRes = m_SkeletonCom->GetSkeleton();

		if (skeletonRes.isvalid() && (skeletonRes->GetState() == Resource::Loaded))
		{
			if(skeletonRes->GetSkelID() != this->GetMesh()->GetMeshID())
			{
				return false;
			}

			if (! m_AniamtionCom->HasGotSkelTree() && !skeletonRes->IsSkelTreeEmpty())
			{
				m_AniamtionCom->SetSkelTree(skeletonRes->GetSkelTree());
				m_AniamtionCom->SetSkelTree(skeletonRes->GetSkelTreeArray());

				m_AniamtionCom->SetGetSkelTree(true);
			}

			if ( ! m_AniamtionCom->HasBuildDefaultToRootX() )
			{
				bool ret = m_AniamtionCom->BuildDefaultToRootX();		
				m_DefaultFinalTrans.Clear();
				if (!ret)
				{
					return false;
				}
			}

			if(!m_DefaultFinalTrans.IsEmpty())
			{
				m_FinalTrans = m_DefaultFinalTrans;
				return true;
			}

			m_FinalTrans.Clear();
			m_DefaultFinalTrans.Clear();

			const SizeT bonesCount = skeletonRes->GetBonesCount();

			const SkelBoneContainer& SkelBones = skeletonRes->GetSkelBones();

			m_DefaultFinalTrans.Reserve(bonesCount);



			//The hole skel's every bone's ToRootX matrix array, find from default ToRootX
			const Util::Dictionary<Util::String, Math::matrix44>& ToRootX = m_AniamtionCom->GetDefaultToRootX();
			Util::Array<IndexT> unusedBoneIndex;

			for (IndexT iBone = 0; iBone < bonesCount; ++iBone)
			{
				if(iBone >= ToRootX.Size())
				{
					unusedBoneIndex.Append(iBone);
					continue;
				}

				IndexT nodeIndex = ToRootX.FindIndex(SkelBones[iBone].boneName.AsString());
				if(nodeIndex == InvalidIndex)
				{
					unusedBoneIndex.Append(iBone);
					continue;
				}
				Math::matrix44 final = Math::matrix44::multiply(ToRootX.ValueAtIndex(nodeIndex), SkelBones[iBone].inverseBindingMatrix );


				Math::matrix44 transformMat = mActor->GetTransform();
				transformMat = Math::matrix44::inverse(transformMat);

				final = Math::matrix44::multiply(transformMat, final);

				m_DefaultFinalTrans.Add(iBone, final);
			}

			//remainder bones use identity matrix
			int remainBonesCount = unusedBoneIndex.Size();
			for(int index = 0; index < remainBonesCount; ++index)
			{
				IndexT iBone = unusedBoneIndex[index];
				m_DefaultFinalTrans.Add(iBone, Math::matrix44::identity());
			}

			m_FinalTrans = m_DefaultFinalTrans;
			return true;

		}
		return false;
	}

	bool SkinnedMeshRenderComponent::_BuildToRootXForms()
	{
		if (AnimationServer::Instance()->IsStop())
		{
			return false;
		}

		if(!m_SkeletonCom)
		{
			return false;
		}
		if(!m_AniamtionCom)
		{
			return false;
		}

		GPtr<Actor> actorParent = mActor->GetParent();
		if(actorParent.isvalid())
		{
			GPtr<Component> com = actorParent->FindComponent(AnimationComponent::RTTI);
			if(com.isvalid())
			{
				GPtr<AnimationComponent> animCom = com.downcast<AnimationComponent>();
				if(m_AniamtionCom != animCom)
				{
					Actor::Check_Skin(this);
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		const GPtr<SkeletonRes>& skeletonRes = m_SkeletonCom->GetSkeleton();

		if (!m_AniamtionCom->IsUpdate() && m_AniamtionCom->IsToParentXEmpty())
		{
			m_LostedSkelton = NULL;
			return false;
		}


		const bool bIsAllLoaded  = m_AniamtionCom->IsAllLoaded();
		const bool bHasAnyErrors = m_AniamtionCom->HasAnyErrors();

		if (bHasAnyErrors)
		{
			return false;
		}

		if (skeletonRes.isvalid() && (skeletonRes->GetState() == Resource::Loaded) && bIsAllLoaded )
		{
			if(skeletonRes->GetSkelID() != this->GetMesh()->GetMeshID())
			{
				if(m_LostedSkelton != skeletonRes->GetSkelID())
				{
					m_LostedSkelton = skeletonRes->GetSkelID();
					n_warning("This mesh %s dosen't fit the skelton %s .",this->GetMesh()->GetMeshID().AsCharPtr(), m_SkeletonCom->GetSkeleton()->GetSkelID().AsCharPtr());
				}

				return false;
			}

			if (! m_AniamtionCom->IsUpdate() && !m_AniamtionCom->IsToParentXEmpty() && !m_FinalTrans.IsEmpty())
			{
				return true;
			}

			m_FinalTrans.Clear();

			const SizeT bonesCount = skeletonRes->GetBonesCount();

			const SkelBoneContainer& SkelBones = skeletonRes->GetSkelBones();

			Util::Dictionary<IndexT, IndexT> usedBoneIndex;
			bool ret = m_AniamtionCom->GetUsedBoneIndex(mActor, usedBoneIndex);
			if(!ret)
			{
				return false;
			}

			Util::Array<IndexT> unusedBoneIndex;
			ret = m_AniamtionCom->GetUnusedBoneIndex(mActor,unusedBoneIndex);
			if(!ret)
			{
				return false;
			}

			if (usedBoneIndex.IsEmpty())
			{
				return false;
			}

			m_FinalTrans.Reserve(bonesCount);


			if ( ! m_AniamtionCom->HasBuildToParentTrans() )
			{
				n_warning("No Available AnimationState! \n");

				return false;
			}

			if ( ! m_AniamtionCom->HasBuildToRootX() )
			{
				m_AniamtionCom->SetBuildToRootX(true);

				bool ret = m_AniamtionCom->BuildToRootX();			

				if (!ret)
				{
					return false;
				}
			}

			//The hole skel's every bone's ToRootX matrix array
			const Util::Array<Math::matrix44>& ToRootX = m_AniamtionCom->GetToRootXTrans();

			for (IndexT iBone = 0; iBone < usedBoneIndex.Size(); ++iBone)
			{
				const IndexT& nodeIndex = usedBoneIndex.KeyAtIndex(iBone);
				const IndexT& boneIndex = usedBoneIndex.ValueAtIndex(iBone);

				if(nodeIndex >= ToRootX.Size() || boneIndex >= SkelBones.Size())
				{
					m_FinalTrans.Clear();
					return false;
				}
				Math::matrix44 final = Math::matrix44::multiply(ToRootX[nodeIndex], SkelBones[boneIndex].inverseBindingMatrix );


				Math::matrix44 transformMat = mActor->GetTransform();
				transformMat = Math::matrix44::inverse(transformMat);

				final = Math::matrix44::multiply(transformMat, final);

				m_FinalTrans.Add(boneIndex, final);
			}

			for (IndexT iRemain = 0; iRemain < unusedBoneIndex.Size(); ++iRemain)
			{
				const IndexT& remainBoneIndex = unusedBoneIndex[iRemain];
				m_FinalTrans.Add(remainBoneIndex, Math::matrix44::identity());
			}

			//if used and unused skel count not same as totel count, this anim is not correct
			if(bonesCount != m_FinalTrans.Size())
			{
				m_FinalTrans.Clear();
				return false;
			}
			else
				return true;

		}
		m_FinalTrans.Clear();
		return false;
	}

	void SkinnedMeshRenderComponent::_Skinning()
	{
		const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();

		n_assert(meshRes.isvalid())
		{
			bool bSWSkinning = false;


			for ( IndexT index = 0; index < mRenderableResUnitList.Size(); ++index )
			{
				RenderObjectType::RenderableType* smr = mRenderableResUnitList[index].GetRenderableFast<RenderObjectType::RenderableType>();

				SizeT nBones = smr->GetAffectedBonesCount();

				//Hardware Skinning
				if (nBones <= MaxSupportedBones)
				{
					smr->SetHWSkinning(true);

					const Util::Array<uchar>& bonesIndex = smr->GetAffectedBonesIndex();

					smr->Reserve(bonesIndex.Size());

					SizeT nBones = bonesIndex.Size();

#if RENDERDEVICE_OPENGLES
					if (nBones == 1)
					{
						IndexT index = (IndexT)bonesIndex[0];
						smr->SetFinalMatrix(0, m_FinalTrans[index]);
					}
					else
#endif
					{
						for (IndexT iBone = 0; iBone < nBones; ++iBone)
						{
							IndexT index = (IndexT)bonesIndex[iBone];

#if RENDERDEVICE_OPENGLES					
							smr->SetFinalMatrix(iBone, Math::matrix44::transpose(m_FinalTrans[index]));
#else
							smr->SetFinalMatrix(iBone, m_FinalTrans[index]);
#endif
						}


					}

				} 
				//Software Skinning
				else
				{
					// TODO
					n_warning("Not Support Software Skinning Now. /n");
				}

			}

		}
	}

	void SkinnedMeshRenderComponent::_OnMoveAfter()
	{
		Super::_OnMoveAfter();
	}

	void SkinnedMeshRenderComponent::CopyFrom(const GPtr<Component> &pComponent)
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		Super::CopyFrom(pComponent);
	}

}
