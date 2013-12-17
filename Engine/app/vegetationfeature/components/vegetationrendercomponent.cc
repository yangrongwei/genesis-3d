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
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "graphicfeature/graphicsfeature.h"
#include "resource/resourceserver.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "vegetationfeature/components/vegetationrendercomponent.h"
#include "resource/meshres.h"
#include "vegetation/VegetationServer.h"
#include "vegetation/VegetationObejct.h"
#include "vegetation/GrassInstanceMap.h"
#include "app/basegamefeature/managers/timesource.h"

#include "apputil/intersectutil.h"
#include "apputil/manuresutil.h"
#include "math/intersection.h"
#include "math/ray.h"

namespace App
{
	using namespace Resources;
	using namespace Vegetation;
	using namespace RenderBase;
	using namespace Graphic;

	__ImplementClass(App::VegetationRenderComponent, 'VERC', App::Component);

	const Resources::ResourceId DefalutShaderID("shd:Common_Diffuse.shader");
	//------------------------------------------------------------------------
	VegetationRenderComponent::VegetationRenderComponent()
		:mVisible(true)
	{

	}
	//------------------------------------------------------------------------
	VegetationRenderComponent::~VegetationRenderComponent()
	{

	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::SetupCallbacks(void)
	{
		mActor->RegisterComponentCallback(this, BeginFrame );
		mActor->RegisterComponentCallback(this, OnFrame );
		mActor->RegisterComponentCallback(this, MoveBefore );
		mActor->RegisterComponentCallback(this, MoveAfter );

		Super::SetupCallbacks();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		n_assert(msg);

		Super::HandleMessage(msg);
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::SetShaderId(GPtr<Vegetation::VegetationObject>& pVegeObj, IndexT iSubMesh , const Resources::ResourceId& shaderID)
	{
		if ( iSubMesh < 0 || !shaderID.IsValid() )
		{
			return;
		}

		if ( iSubMesh >= pVegeObj->GetShaderCount() )
		{
			while( iSubMesh >= pVegeObj->GetShaderCount() )
			{
				pVegeObj->SetShaderID(iSubMesh, shaderID);	

			}
		}
		else
		{
			const GPtr<Graphic::MaterialInstance>& pmat = pVegeObj->GetMaterial(iSubMesh);

			if ( pmat->GetShaderID() != shaderID)
			{
				pVegeObj->SetShaderID(iSubMesh,shaderID);
			} 
		}	

	}

	//------------------------------------------------------------------------
	void VegetationRenderComponent::OnActivate()
	{
		if(mVisible)
		{
			BuildRenderData();
			AttachRenderObjects();
		}

		Super::OnActivate();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::OnDeactivate()
	{
		if(mVisible)
		{
			DeattachRenderObjects();
			DiscardRenderData();
		}

		Super::OnDeactivate();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::OnDestroy()
	{
		Super::OnDestroy();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::SetVisible(bool bVisible)
	{
		mVisible = bVisible;
		if (IsActive())
		{
			if (mVisible)
			{
				BuildRenderData();
				AttachRenderObjects();
			}
			else
			{
				DeattachRenderObjects();
				DiscardRenderData();
			}
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_OnBeginFrame()
	{
		//TODO : mRenderDates[i].UpdateBushMesh();
		for (int i = 0; i<mRenderDates.Size();i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];

			if ( !pVegObj.isvalid() )
			{
				continue;
			}

			if(!CreateInstanceMap(pVegObj))
				continue;

			n_assert( GraphicsFeature::Instance() );

			_LoadBrushRes(pVegObj);
			_LoadBrushMaterials(pVegObj);



			if(mVisible)
			{
				_BuildRenderData(pVegObj);//if build , return
				_AttachRenderObject(pVegObj);
			}

		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_OnFrame()
	{
		for (int i = 0; i<mRenderDates.Size();i++)
		{
			Vegetation::VegetationObjectPtr pVegObj = mRenderDates[i];

			if ( !pVegObj->mIsAllTexLoaded)
			{
				return;
			}
			else
			{				
				Timing::Time fTick = App::GameTime::Instance()->GetFrameTime();
				static float time = 0.0f;
				time += (float)fTick;
				SizeT count = pVegObj->GetMaterialCount();
				for (IndexT index = 0; index < count; ++index)
				{

					if ( pVegObj->GetRenderType() == Vegetation::eRT_DetailMesh )
						break;

					pVegObj->SetShaderConstantParam(index, "uTime", time);
				}

			}

			_UpdateRenderData(pVegObj);
		}

		//TODO : renderable update
		//UpdateRenderData();
	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::_OnMoveBefore()
	{
		//Math::float4 pos = mActor->GetPosition();
		const Math::matrix44& invMatrix = Math::matrix44::inverse(mActor->GetWorldTransform());
		for (int i = 0; i< mRenderDates.Size(); i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];			

			if (pVegObj.isvalid())
			{
				pVegObj->SetWorldMatrix(invMatrix);
			}

		}
	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::_OnMoveAfter()
	{
		//Math::matrix44 tempMatrix = mActor->GetWorldTransform();
		//TODO : setobject offset Matrix
		for (int i = 0; i< mRenderDates.Size(); i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];			

			if (pVegObj.isvalid())
			{
				pVegObj->SetWorldMatrix(mActor->GetWorldTransform());

				//recalculate all vegobject bbox for bug2264
				ReCalcBBox(pVegObj);
			}

		}



	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::BuildRenderData( void )
	{
		//TODO : foreach object
		for (int i = 0; i< mRenderDates.Size(); i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];			

			//pVegObj->Active();
			if ( !pVegObj->GetPrimHandle().IsValid())
			{
				_BuildRenderData(pVegObj);
			}
		}

	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_BuildRenderData(  GPtr<VegetationObject>& pVegObj  )
	{
		if ( pVegObj->mIsBuildRenderable  )
			return;

		const VegeInstanceMapPtr& pVegInstMap =  pVegObj->GetInstanceMap();

		if ( !pVegInstMap.isvalid() || pVegInstMap->GetInstanceCount()<1 )
			return;	

		pVegInstMap->SetParentVegeObject(pVegObj);
		pVegInstMap->Active();

		VegetationObject::RenderObjectPtr& renderObject = pVegObj->GetRenderObject();
		if (!renderObject.isvalid())
		{
			renderObject = VegetationObject::RenderObjectType::Create();
		}
		renderObject->SetOwner(pVegObj.get(), mActor? mActor->GetLayerID() : 0);

		Graphic::RenderableResUnitArray& resArray = pVegObj->GetResUnits();
		Vegetation::RenderType etype = pVegObj->GetRenderType();
		if( etype == Vegetation::eRT_Grass )
		{
			VegetationObject::RenderObjectType::RenderableType* renderable = resArray[0].ResetRenderable<VegetationObject::RenderObjectType::RenderableType>();

			pVegObj->mRenderQueueDirty = true;
			renderable->Set(0 ,0, Vegetation::g_VertexCount, 0 ,Vegetation::g_IndexCount);
			//-START
			Math::bbox worldBB = Math::bbox();
			//worldBB.transform(mActor->GetWorldTransform());
			_CalculateBBox( worldBB, pVegInstMap);
			renderObject->SetBoundingBox( worldBB );
			//-END
			pVegInstMap->BuildPrimitive();
			pVegObj->mIsBuildRenderable  = true;	

		}
		else
		{
			const Resources::PrimitiveResInfo* meshInfo = pVegObj->GetMeshInfo();
			if ( !meshInfo )
				return;

			const GPtr<Resources::Resource>& _resourceinfo= meshInfo->GetRes();
			if ( !_resourceinfo.isvalid())
			{
				return;
			}
			const GPtr<MeshRes>& meshRes = _resourceinfo.downcast<MeshRes>();
			if ( meshRes.isvalid() && meshRes->GetState() == Resource::Loaded )
			{	
				Math::bbox worldBB = meshRes->GetBoundingBox();
				_CalculateBBox( worldBB, pVegInstMap);
				renderObject->SetBoundingBox( worldBB );
				bool bAllRenderableSet = true;
				for ( IndexT subIndex = 0; subIndex < meshRes->GetSubMeshCount(); ++subIndex )
				{

					if ( pVegObj->GetShaderCount() > subIndex)	
					{
						SubMesh* subMesh = meshRes->GetSubMesh(subIndex);
						n_assert(subMesh);

						VegetationObject::RenderObjectType::RenderableType* renderable = resArray[subIndex].ResetRenderable<VegetationObject::RenderObjectType::RenderableType>();

						pVegObj->mRenderQueueDirty = true;
						renderable->Set(subIndex , 
							subMesh->firstVertex, 
							subMesh->numVertex,
							subMesh->FirstIndex,
							subMesh->numIndex);	
					}
					else
					{
						bAllRenderableSet = false;

					}
				}

				//pVegObj->SetPrimHandle(NULL);	// fix bug4031
				if ( pVegInstMap->BuildPrimitive()  )
				{
					if (bAllRenderableSet)		
						pVegObj->mIsBuildRenderable  = true;
				}		

			}
			else
			{
				//TODO : reload meshres
				pVegObj->mIsBuildRenderable  = false;	
				pVegObj->mMeshDirty = true;
			}
		}

	}


	//------------------------------------------------------------------------
	void VegetationRenderComponent::UpdateRenderData(void)
	{
		//TODO : foreach object


		for ( IndexT index = 0; index < mRenderDates.Size(); ++index )
		{

			Vegetation::VegetationObjectPtr pVegObj = mRenderDates[index];
			_UpdateRenderData(pVegObj);
		}


	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::_UpdateRenderData(  GPtr<Vegetation::VegetationObject>&  pVegObj)
	{

		if ( !pVegObj->mIsAttached || !pVegObj->mIsBuildRenderable)
		{
			Graphic::RenderableResUnitArray& resArray = pVegObj->GetResUnits();
			SizeT rndcount = resArray.Size();
			for (IndexT rndIndex = 0; rndIndex < rndcount; ++rndIndex)
			{
				VegetationObject::RenderObjectType::RenderableType* vrptr = resArray[rndIndex].GetRenderableFast<VegetationObject::RenderObjectType::RenderableType>();
				if ( vrptr )
				{
					vrptr->Set(pVegObj,rndIndex);
				}
			}
		}
		else
		{
			Vegetation::RenderType etype = pVegObj->GetRenderType();
			//GPtr<RenderBase::PrimitiveGroup>& pPG = pVegObj->GetPrimGroup();
			RenderBase::PrimitiveHandle& pPH = pVegObj->GetPrimHandle();

			if( etype == Vegetation::eRT_Grass && pPH.IsValid())// && pPG.isvalid())
			{
			}
			else
			{
				const Resources::PrimitiveResInfo* meshInfo = pVegObj->GetMeshInfo();
				const GPtr<MeshRes>& meshres = meshInfo->GetRes().downcast<MeshRes>();

				if ( meshres.isvalid() && meshres->GetState() == Resource::Loaded && meshInfo->GetHandle().IsValid() )
				{			
					Graphic::RenderableResUnitArray& resArray = pVegObj->GetResUnits();
					int count = resArray.Size();
					for (SizeT sub = 0; sub < count; ++sub)
					{
						if (sub	>= meshres->GetSubMeshCount())
							continue;

						SubMesh* subMesh = meshres->GetSubMesh( sub );
						VegetationObject::RenderObjectType::RenderableType* renderable = resArray[sub].GetRenderableFast<VegetationObject::RenderObjectType::RenderableType>();

						if ( NULL == renderable)
						{
							pVegObj->mIsBuildRenderable  = false;	
							return;
						}

						renderable->Set(sub ,
							subMesh->firstVertex, subMesh->numVertex,
							subMesh->FirstIndex, subMesh->numIndex);
					}	

				}
			}
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::DiscardRenderData(void)
	{

		for (int nObj = 0; nObj < mRenderDates.Size(); ++nObj)
		{
			_DiscardRenderData(mRenderDates[nObj]);
		}		
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_DiscardRenderData(  GPtr<VegetationObject>& pvegeobj  )
	{
		pvegeobj->mIsBuildRenderable = false;

		if ( pvegeobj->GetPrimHandle().IsValid() )
		{
			//GraphicSystem::Instance()->RemovePrimitive(pvegeobj->GetPrimHandle());
			App::GraphicObjectManager::Instance()->DiscardPrimitiveHandle(pvegeobj->GetPrimHandle());
			pvegeobj->SetPrimHandle(NULL );
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_CleanRenderData()
	{
		for (int nObj = 0; nObj < mRenderDates.Size(); ++nObj)
		{
			GPtr<VegetationObject>& pvegeobj = mRenderDates[nObj];
			for ( IndexT iMat = 0 ; iMat < pvegeobj->GetShaderCount(); ++iMat )
			{
				GPtr<Graphic::MaterialInstance> mat = pvegeobj->GetMaterial(iMat);
				if ( mat.isvalid() )
				{
					pvegeobj->RemoveShader(iMat);
					mat = 0;
				}
			}
		}	
		mRenderDates.Clear();
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::AttachRenderObjects(void)
	{

		for (int nObj = 0; nObj < mRenderDates.Size(); ++nObj)
		{
			_AttachRenderObject(mRenderDates[nObj]);
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_AttachRenderObject( GPtr<VegetationObject>& pvegeobj )
	{
		if ( !pvegeobj->mIsBuildRenderable )
		{
			pvegeobj->mIsAttached  = false;
			return;
		}
		if ( pvegeobj->mIsAttached )
		{
			return;
		}
		pvegeobj->mIsAttached = true;

		VegetationObject::RenderObjectPtr& renderObject = pvegeobj->GetRenderObject();

		if (renderObject.isvalid())
		{
			renderObject->Attach(mActor->GetRenderScene());
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::DeattachRenderObjects(void)
	{
		//TODO : foreach object

		for (int nObj = 0; nObj < mRenderDates.Size(); ++nObj)
		{
			_DeattachRenderObject(mRenderDates[nObj]);
		}
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::_DeattachRenderObject( GPtr<VegetationObject>& pvegeobj )
	{
		if ( !pvegeobj->mIsAttached )
		{
			return;
		}
		pvegeobj->mIsAttached = false;
		VegetationObject::RenderObjectPtr& renderObject = pvegeobj->GetRenderObject();
		if (renderObject.isvalid())
		{
			renderObject->Detach();
		}
	}

	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::OnRenderSceneChanged()
	{
		for (int i = 0; i<mRenderDates.Size();i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];
			if (pVegObj->GetRenderObject() && pVegObj->GetRenderObject()->Attached())
			{
				pVegObj->GetRenderObject()->Attach(mActor->GetRenderScene());
			}
		}
	}

	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::AddVegetationObject(const GPtr<Vegetation::VegetationObject>& obj)
	{
		mRenderDates.Append(obj);

		CreateInstanceMap(obj);
	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::InsetVegetationObject(IndexT nIdx, const GPtr<Vegetation::VegetationObject>& obj)
	{
		mRenderDates.Insert(nIdx, obj);

		CreateInstanceMap(obj);
	}
	//------------------------------------------------------------------------
	GPtr<Vegetation::VegetationObject>& VegetationRenderComponent::CreateVegetationObject(Vegetation::RenderType etype, const Resources::ResourceId& meshID)
	{
		//TODO : append a vegetationObject to component's mRenderDates
		GPtr<Vegetation::VegetationObject> vegeobj = Vegetation::VegetationObject::Create();
		vegeobj->SetRenderType(etype);
		if ( meshID.IsValid() )
		{
			vegeobj->SetMeshID(meshID);
		}
		mRenderDates.Append(vegeobj);

		CreateInstanceMap(vegeobj);

		return mRenderDates.Back();
	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::RemoveVegetationObject(IndexT nIdx)
	{
		if (mRenderDates.Size() <= nIdx)
		{
			return;
		}
		_DeattachRenderObject(mRenderDates[nIdx]);
		mRenderDates[nIdx]->ClearRenderables();
		mRenderDates[nIdx]->DeActive();
		mRenderDates[nIdx] = NULL;
		mRenderDates.EraseIndex(nIdx);
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::UpdateRenderLayer()
	{
		for (int i = 0; i<mRenderDates.Size();i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];
			VegetationObject::RenderObjectPtr& obj = pVegObj->GetRenderObject();
			if (obj.isvalid())
			{
				obj->SetLayerID(mActor->GetLayerID());
			}
		}
	}
	//------------------------------------------------------------------------
	bool VegetationRenderComponent::_LoadBrushRes(GPtr<Vegetation::VegetationObject>& pVegeObj)
	{
		//TODO:
		bool bRet = false;

		if ( !pVegeObj.isvalid())
		{
			return false;
		}

		// while grass , no Meshres
		// or else  meshres has been loaded, return true
		if ( pVegeObj->GetRenderType() == eRT_Grass )
		{
			bRet =  true;
		}
		else
		{
			//VegetationBrushPtr& pVegeBrush = pVegeObj->GetBrush();
			//if ( !pVegeBrush.isvalid())
			//	return false;

			//const Resources::ResourceId& tResID = pVegeBrush->GetMeshID();
			if ( pVegeObj->mMeshDirty) 
			{	
				const Resources::PrimitiveResInfo* pInfo = pVegeObj->GetMeshInfo(); 
				if( pInfo && pInfo->GetRes().isvalid())
				{
					const GPtr<Resources::MeshRes>& tMeshres = pInfo->GetRes().downcast<Resources::MeshRes>();
					if ( tMeshres )
					{
						bRet = true;
						pVegeObj->mMeshDirty = false;
					}
				}
			}			
		}	

		return bRet;

	}
	//------------------------------------------------------------------------
	bool VegetationRenderComponent::_LoadBrushMaterials(GPtr<Vegetation::VegetationObject>& pVegeObj)
	{
		bool bRet = true;

		//VegetationBrushPtr& pVegeBrush = pVegeObj->GetBrush();

		if ( !pVegeObj.isvalid())
		{
			return false;
		}

		if (pVegeObj->mIsAllTexLoaded)
		{
			return bRet;
		}

		if (pVegeObj->mMatDirty)
		{
			bool hasMatDirty = false;
			//pVegeBrush->SetTexAllLoad(true);
			pVegeObj->mIsAllTexLoaded = true;
			for ( IndexT iMat = 0; iMat < pVegeObj->GetShaderCount(); ++iMat )
			{
				const GPtr<Graphic::MaterialInstance>& mat = pVegeObj->GetMaterial(iMat);
				if (!pVegeObj->mCanCreateMaterial)
				{
					//pVegeBrush->SetCanCreateMat(true);
					pVegeObj->mCanCreateMaterial = true;
					//error
					SetShaderId(pVegeObj, iMat,mat->GetShaderID());
					//pVegeObj->SetShaderId(iMat,mat->m_shaderID);
					if (iMat < pVegeObj->GetShaderCount() -1)
					{
						pVegeObj->mCanCreateMaterial = false;
					}

				}
				if ( !mat->IsAllLoaded() )
				{
					//pVegeBrush->SetTexAllLoad(false);
					pVegeObj->mIsAllTexLoaded = false;
				}

				hasMatDirty |= mat->IsDirty();
			}

			bRet ^= hasMatDirty;
			pVegeObj->mMatDirty = hasMatDirty;
			//pVegeBrush->SetMatDirty(hasMatDirty);
			//mRenderQueueDirty = true;
		}

		return bRet;
	}
	void VegetationRenderComponent::SetMeshID(GPtr<Vegetation::VegetationObject>& pVegeObj, const Resources::ResourceId& meshID )
	{
		pVegeObj->SetMeshID(meshID);
		pVegeObj->mMeshDirty = true;

	}
	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::SetMeshID(IndexT idx, const Resources::ResourceId& meshID)
	{
	}
	//--------------------------------------------------------------------------------
	IndexT VegetationRenderComponent::IntersectInstance(const Actor* camerActor, const Math::float2& mousepos, IndexT nIdx, Math::scalar& fout)
	{
		IndexT retIdx = -1;

		Math::Ray worldray;
		bool bcompute = AppUtil::IntersectUtil::ComputeDefaultWorldMouseRay( camerActor, mousepos, worldray );
		//if ( GetWorldRay(mousepos, worldray))
		if(bcompute)
		{		
			if ( nIdx >= mRenderDates.Size())
			{
				return retIdx;
			}
			const GPtr<VegetationObject>& vegeobj = mRenderDates[nIdx];
			if ( !vegeobj.isvalid())
			{
				return retIdx;
			}
			const GPtr<VegeInstanceMap>& instMap = vegeobj->GetInstanceMap();

			if (instMap.isvalid())
			{

				Math::vector objscale =  vegeobj->GetScale();
				Math::quaternion objrot =  vegeobj->GetRotation();


				if (  vegeobj->GetRenderType() == eRT_Grass  )
				{

					SizeT nInstCount = instMap->GetInstanceCount();
					for (IndexT i = 0; i < nInstCount; ++i)
					{
						INSTANCEDATA_POS* tmpInst = instMap->GetInstance(i);

						Math::float4 _pos(tmpInst->pos.x(),tmpInst->pos.y(), tmpInst->pos.z(), 1);				
						// while in the visual range , draw a single Tree 						

						Math::quaternion _quat = Math::quaternion::rotationyawpitchroll( tmpInst->rotate.y() * N_PI / 180.0f , tmpInst->rotate.x()* N_PI / 180.0f, tmpInst->rotate.z()* N_PI / 180.0f);
						_quat = Math::quaternion::multiply(_quat,objrot);
						Math::float4 _scale = Math::float4(tmpInst->scale.x() * objscale.x(), tmpInst->scale.y()* objscale.y(), tmpInst->scale.z()* objscale.z(), 0);
						Math::matrix44 _mat = Math::matrix44::transformation( _scale, _quat, _pos );

						Math::matrix44 invWorldM = Math::matrix44::inverse( _mat );
						Math::Ray localray = worldray.Tramsform(invWorldM);

						const PrimitiveTopology::Code type = PrimitiveTopology::TriangleList;
						const VEGE_VERTEX_INSTANCE* instanceVertex = &vegeobj->GetVertices()[0];//pg->GetVertexBuffer()->GetPtr<VEGE_VERTEX_INSTANCE>();
						const Resources::Index16Container::value_type* indicies32 =  (const Resources::Index16Container::value_type*)&vegeobj->GetIndices()[0];//pg->GetIndexBuffer()->GetPtr<Resources::Index16Container::value_type>();
						//scalar interPoint = N_INFINITY;

						Math::scalar tempOut;
						for (IndexT nIdx = 0; nIdx < 2; ++nIdx)
						{
							Resources::Index16Container::value_type index0 = indicies32[i*6 + nIdx*3];
							Resources::Index16Container::value_type index1 = indicies32[i*6 + nIdx*3 + 1];
							Resources::Index16Container::value_type index2 = indicies32[i*6 + nIdx*3 + 2];

							if ( Math::Intersection::Intersect(localray, instanceVertex[index0].pos, instanceVertex[index1].pos, instanceVertex[index2].pos, tempOut ) )
							{
								//interPoint = n_min( interPoint, fout );
								if ( fout > tempOut)
								{
									fout = tempOut;
									retIdx = i;
								}
							}	
						}
					}

				}
				else
				{

					//const GPtr<VegetationBrush>& vegebrush = vegeobj->GetBrush();
					const GPtr<Resources::MeshRes>& mesh = vegeobj->GetMeshInfo()->GetRes().downcast<Resources::MeshRes>();

					SizeT nInstCount = instMap->GetInstanceCount();
					for (IndexT i = 0; i	< nInstCount; ++i)
					{
						INSTANCEDATA_POS* tmpInst = instMap->GetInstance(i);

						Math::float4 _pos(tmpInst->pos.x(),tmpInst->pos.y(), tmpInst->pos.z(), 1);				
						// while in the visual range , draw a single Tree 						

						//Math::float3 tscale = tmpInst->scale * objscale;
						//Math::float4 _scale(tscale.x(), tscale.y(), tscale.z(), 0);	
						//Math::vector _axis(0, tmpInst->rotate.x(),0 );
						//Math::quaternion _quat = Math::quaternion::rotationaxis(_axis, (tmpInst->rotate.y() + objrot) * 5 * N_PI);
						//Math::matrix44 _mat = Math::matrix44::transformation( _scale, _quat, _pos );

						Math::quaternion _quat = Math::quaternion::rotationyawpitchroll( tmpInst->rotate.y()* N_PI / 180.0f, tmpInst->rotate.x()* N_PI / 180.0f, tmpInst->rotate.z()* N_PI / 180.0f);
						_quat = Math::quaternion::multiply(_quat,objrot);
						Math::float4 _scale = Math::float4(tmpInst->scale.x()* objscale.x(), tmpInst->scale.y()* objscale.y(), tmpInst->scale.z()* objscale.z(), 0);
						Math::matrix44 _mat = Math::matrix44::transformation( _scale, _quat, _pos );

						matrix44 invWorldM = Math::matrix44::inverse( _mat );
						Math::Ray localray = worldray.Tramsform(invWorldM);

						if ( AppUtil::IntersectUtil::IntersectMesh(localray, mesh, fout) )
						{
							return i;
						}
					}
				}
			}

		}
		return retIdx;
	}

	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::NotifiedTerrainChanged(const STR_TERRAINBLOCK& terrblock,const Math::scalar& scaleX,const Math::scalar& scaleZ)
	{
		//TODO : get whether there were some vegetations, and then 
		SizeT vegetcount = mRenderDates.Size();				
		for (IndexT nCurVeget = 0; nCurVeget < vegetcount; ++nCurVeget)
		{
			GPtr<VegeInstanceMap>& instMap = mRenderDates[nCurVeget]->GetInstanceMap();
			if ( !instMap.isvalid())
				continue;

			float flposx = terrblock.xmin /terrblock.heimapX * terrblock.terrainWidth;
			float flposz = terrblock.ymin /terrblock.heimapY * terrblock.terrainHeight;

			float frposx = (terrblock.xmin + terrblock.width) /terrblock.heimapX * terrblock.terrainWidth;
			float frposz = (terrblock.ymin + terrblock.height) /terrblock.heimapY * terrblock.terrainHeight;

			//float fWidthTileX = terrblock.terrainWidth / terrblock.heimapX;
			//float fWidthTileY = terrblock.terrainHeight / terrblock.heimapY;


			const Math::vector& actorPos = mActor->GetWorldPosition();
			SizeT instCount = instMap->GetInstanceCount();
			for ( IndexT nCurInst = 0; nCurInst < instCount; ++nCurInst)
			{
				INSTANCEDATA_POS* curInst = instMap->GetInstance(nCurInst);

				// transform from world coordinate to terrain actor(curInst is world pos)
				Math::float3 posAtCoornidateActor;
				posAtCoornidateActor.set(curInst->pos.x() - actorPos.x(), curInst->pos.y() - actorPos.y(), curInst->pos.z() - actorPos.z());

				bool bReplace = (posAtCoornidateActor.x() > flposx) && (posAtCoornidateActor.x() < frposx);
				//bReplace &= (posAtCoornidateActor.z() > leftupPos.y()) && (posAtCoornidateActor.z() < rightdownPos.y());

				if (!bReplace)
					continue;

				bReplace = (posAtCoornidateActor.z() > flposz) && (posAtCoornidateActor.z() < frposz);

				if ( bReplace )
				{
					//TODO : if there be , get y-value via (x,z)-value from terrain's data
					GPtr<Component> com ;
					GPtr<TerrainRenderComponent> TerrCom;


					com = mActor->FindComponent( TerrainRenderComponent::RTTI );
					if ( com.isvalid() )
					{
						TerrCom = com.downcast<TerrainRenderComponent>();

						if (TerrCom)
						{
							//float fTerrainHeight = pTVView->GetTerrainHeight(actorID, xmin+x, ymin+y); 

							//int xtile = (int)(posAtCoornidateActor.x() / terrblock.terrainWidth * terrblock.heimapX );
							//int ytile = (int)(posAtCoornidateActor.z() / terrblock.terrainHeight * terrblock.heimapY );

							//float insty = TerrCom->GetTerrainData()->GetHeightMap()->GetHeight(xtile, ytile);
							float insty = TerrCom->GetWorldYAtActorCoord(posAtCoornidateActor.x() , posAtCoornidateActor.z());

							//transform to world coordinate
							insty += actorPos.y();

							//TODO : set Instance date (replace)
							Math::scalar fXAtActorCoor = posAtCoornidateActor.x() * scaleX;
							Math::scalar fZAtActorCoor = posAtCoornidateActor.z() * scaleZ;
							fXAtActorCoor += actorPos.x();
							fZAtActorCoor += actorPos.z();

							curInst->pos = Math::float3(fXAtActorCoor, insty,fZAtActorCoor);
						}
					}


				}

			}

		}
	}

	//------------------------------------------------------------------------
	void VegetationRenderComponent::NotifiedTerrainHole( const STR_TERRAINBLOCK& terrblock)
	{
		//TODO : get whether there were some vegetations, and then 
		SizeT vegetcount = mRenderDates.Size();				
		for (IndexT nCurVeget = 0; nCurVeget < vegetcount; ++nCurVeget)
		{
			GPtr<VegeInstanceMap>& instMap = mRenderDates[nCurVeget]->GetInstanceMap();
			if ( !instMap.isvalid())
				continue;

			float flposx = terrblock.xmin /terrblock.heimapX * terrblock.terrainWidth;
			float flposz = terrblock.ymin /terrblock.heimapY * terrblock.terrainHeight;

			float frposx = (terrblock.xmin + terrblock.width) /terrblock.heimapX * terrblock.terrainWidth;
			float frposz = (terrblock.ymin + terrblock.height) /terrblock.heimapY * terrblock.terrainHeight;

			//float fWidthTileX = terrblock.terrainWidth / terrblock.heimapX;
			//float fWidthTileY = terrblock.terrainHeight / terrblock.heimapY;


			SizeT instCount = instMap->GetInstanceCount();
			for ( IndexT nCurInst = instCount - 1; nCurInst >= 0; --nCurInst)
			{
				INSTANCEDATA_POS* curInst = instMap->GetInstance(nCurInst);

				bool bReplace = (curInst->pos.x() > flposx) && (curInst->pos.x() < frposx);
				//bReplace &= (curInst->pos.z() > leftupPos.y()) && (curInst->pos.z() < rightdownPos.y());

				if (!bReplace)
					continue;

				bReplace = (curInst->pos.z() > flposz) && (curInst->pos.z() < frposz);

				if ( bReplace )
				{
					//TODO : if there be , get y-value via (x,z)-value from terrain's data
					GPtr<Component> com ;
					GPtr<TerrainRenderComponent> TerrCom;


					com = mActor->FindComponent( TerrainRenderComponent::RTTI );
					if ( com.isvalid() )
					{
						TerrCom = com.downcast<TerrainRenderComponent>();

						if (TerrCom)
						{
							mRenderDates[nCurVeget]->RemoveInstance(nCurInst);
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	void VegetationRenderComponent::_CalculateBBox(Math::bbox& box, const GPtr<VegeInstanceMap>& instmap) 
	{
		n_assert(instmap.isvalid());

		scalar minX = Math::N_INFINITY;
		scalar minY = Math::N_INFINITY;
		scalar minZ = Math::N_INFINITY;

		scalar maxX = -Math::N_INFINITY;
		scalar maxY = -Math::N_INFINITY;
		scalar maxZ = -Math::N_INFINITY;

		SizeT PosIndex = 0;
		while (PosIndex < instmap->GetInstanceCount())
		{
			Math::float3 curPos = instmap->GetInstance(PosIndex)->pos;
			Math::float3 curScal = instmap->GetInstance(PosIndex)->scale;

			/*if(curPos.x() < minX)
			minX = curPos.x();
			else if(curPos.x() > maxX)
			maxX = curPos.x();*/
			Math::scalar curMaxX =  curPos.x() + box.pmax.x() * curScal.x();
			if(curPos.x() < minX)
				minX = curPos.x();
			else if(curMaxX > maxX)
				maxX = curMaxX;

			Math::scalar curMaxY =  curPos.y() + box.pmax.y() * curScal.y();
			if(curPos.y() < minY)
				minY = curPos.y();
			else if(curMaxY > maxY)
				maxY = curMaxY;

			/*	if(curPos.z() < minZ)
			minZ = curPos.z();
			else if(curPos.z() > maxZ)
			maxZ = curPos.z();*/
			Math::scalar curMaxZ =  curPos.z() + box.pmax.z() * curScal.z();
			if(curPos.z() < minZ)
				minZ = curPos.z();
			else if(curMaxZ > maxZ)
				maxZ = curMaxZ;


			PosIndex++;
		}
		box.pmin = Math::point(minX,minY,minZ);
		box.pmax = Math::point(maxX,maxY,maxZ);
	}

	//------------------------------------------------------------------------
	void VegetationRenderComponent::ReCalcBBox(const GPtr<Vegetation::VegetationObject>& pVegObj)
	{
		GPtr<VegeInstanceMap>& pVegInstMap = pVegObj->GetInstanceMap();
		if (!pVegInstMap)
		{
			return;
		}		
		VegetationObject::RenderObjectPtr& renderObject = pVegObj->GetRenderObject();
		if (!renderObject.isvalid())
		{
			return;
		}
		Vegetation::RenderType etype = pVegObj->GetRenderType();
		if( etype == Vegetation::eRT_Grass )
		{

			if (!renderObject.isvalid())
				return;

			pVegObj->mRenderQueueDirty = true;
			Math::bbox worldBB = Math::bbox();
			_CalculateBBox( worldBB, pVegInstMap);
			renderObject->SetBoundingBox( worldBB );
		}
		else
		{
			const Resources::PrimitiveResInfo* meshInfo = pVegObj->GetMeshInfo();
			if ( !meshInfo )
				return;

			const GPtr<Resources::Resource>& _resourceinfo= meshInfo->GetRes();
			if ( !_resourceinfo.isvalid())
			{
				return;
			}
			const GPtr<MeshRes>& meshRes = _resourceinfo.downcast<MeshRes>();
			if ( meshRes.isvalid() && meshRes->GetState() == Resource::Loaded )
			{	
				//TODO : Instance Map trav
				// build new renderable
				bool bAllRenderableSet = true;
				Math::bbox worldBB = meshRes->GetBoundingBox();
				//worldBB.transform(mActor->GetWorldTransform());
				_CalculateBBox( worldBB, pVegInstMap);
				renderObject->SetBoundingBox( worldBB );
			}
		}
	}

	//------------------------------------------------------------------------
	void VegetationRenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		for (int i = 0; i< mRenderDates.Size(); i++)
		{
			Vegetation::VegetationObjectPtr& pVegObj = mRenderDates[i];			

			if (pVegObj.isvalid())
			{
				pVegObj->GetReferenceResourceId(list);
			}
		}
		Super::GetReferenceResourceId(list);
	}

	bool VegetationRenderComponent::CreateInstanceMap( const GPtr<Vegetation::VegetationObject>& obj )
	{
		Vegetation::VegeInstanceMapPtr& pInstMap = obj->GetInstanceMap();
		if ( !pInstMap.isvalid() )
		{
			const Util::String& tplpath = obj->GetInstanceFilePath();
			if ( tplpath.IsEmpty() )
				return false;				

			if( VegetationServer::Instance()->OpenTemplateFile( tplpath ) )				
				pInstMap = VegetationServer::Instance()->CreateFromTemplate( tplpath );				

			if ( !pInstMap.isvalid() )
				pInstMap = obj->CreateInstanceMap();

			obj->SetInstanceMap(pInstMap);
		}

		return true;
	}

}
