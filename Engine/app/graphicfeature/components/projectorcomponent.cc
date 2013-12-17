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
#ifndef __PROJECTOR_COMMIT__

#include "stdneb.h"
#include "projectorcomponent.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "graphicfeature/graphicsfeature.h"
#include "rendersystem/RenderSystem.h"
#if __ANDROID__
#define ICE_NO_DLL
#include "extlibs/OPCODEA/Opcode.h"
#elif __OSX__
#include "Opcode.h"
#elif __WIN32__
#include "extlibs/OPCODE/Opcode.h"
#endif
#include "graphicsystem/Projector/CollisionModelServer.h"

#include "app/graphicfeature/components/skinnedmeshrendercomponent.h"
#include "app/graphicfeature/components/projectorcomponent.h"
#include "app/graphicfeature/components/projectorrenderobject.h"
#include "resource/meshres.h"
#include "app/terrainfeature/components/TerrainRenderObject.h"

namespace App
{
using namespace Resources;

const char* DefaultMaterial = "sys:projector.material";

__ImplementClass(App::ProjectorRenderComponent, 'PCOM', App::RenderComponent);

ProjectorRenderComponent::ProjectorRenderComponent()
	: mProjector(NULL),
	mIsNeedUpdate(false),
	mVertexLimit(4*1024),
	mPrimitive(NULL),
	mTerrainPrimitive(NULL)
#ifdef __GENESIS_EDITOR__	//	edtior use
	,mIsBrushHelper(false)
#endif
{
	mProjector = Graphic::Projector::Create();
	mAabb.begin_extend();	
}
//--------------------------------------------------------------------------------
ProjectorRenderComponent::~ProjectorRenderComponent()
{
	if (mProjector.isvalid())
	{
		mProjector = NULL;
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::SetupCallbacks()
{
	mActor->RegisterComponentCallback(this, BeginFrame);
	mActor->RegisterComponentCallback(this, OnFrame);
	mActor->RegisterComponentCallback(this, MoveAfter);
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::SetupAcceptedMessages()
{
	Super::SetupAcceptedMessages();
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
{
	Super::HandleMessage(msg);
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::OnActivate()
{
	Super::OnActivate();

	if ( mActor )
	{
		mProjector->SetTransform( mActor->GetWorldTranslateRotation() );
	}

	if ( IsActive() )
	{
		_BuildRenderObject();
		_AttachRenderObject();
	}

}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::OnDeactivate()
{
	Super::OnDeactivate();

	if ( !IsActive())
	{
		_DeattachRenderObject();
	}
	if ( mPrimitive.IsValid() )
	{
		Graphic::GraphicSystem::Instance()->RemovePrimitive(mPrimitive);
		mPrimitive = RenderBase::PrimitiveHandle();
	}

	if (mTerrainPrimitive)
	{
		Graphic::GraphicSystem::Instance()->RemovePrimitive(mTerrainPrimitive);
		mTerrainPrimitive = RenderBase::PrimitiveHandle();
	}
}

void ProjectorRenderComponent::UpdateRenderLayer()
{
	if (mProjectorRenderObject.isvalid())
	{
		mProjectorRenderObject->SetLayerID(mActor->GetLayerID());
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_OnBeginFrame()
{
	Super::_OnBeginFrame();
}

//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_OnFrame()
{
	Super::_OnFrame();
	if (mProjector.isvalid() && mIsNeedUpdate && m_bAllTexLoaded)
	{
		_UpdateProjector();

		_BuildMeshInfo();

		_BuildRenderable();
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_UpdateProjector()
{
	// Rebuild mesh vertex container
	mVertexs.Clear(false);

	// Rebuild terrain vertex & indices container
	mTerrainVertexs.Clear(false);
	mTerrainIndices.Clear(false);

	// Update shader param & retrieve render objects
	mProjector->_UpdateProjector();


	// Collision dealing
	Math::matrix44 viewProjMatrix = Math::matrix44::zero();
	Graphic::CollisionModelServer* collisionModelServer = Graphic::CollisionModelServer::Instance();

	// TODO: Optimize usage of the following variables
	Opcode::PlanesCollider planesCollider;
	Opcode::PlanesCache planesCache;
	IceMaths::Plane clipPlanes[6];

	const Util::Array<GPtr<Graphic::RenderObject> >& renderObjs = mProjector->GetRenderObjs();

	for (int i = 0; i < renderObjs.Size(); ++i)
	{
		// check ignore layer
		if ( (1 << renderObjs[i]->GetLayerID() & mProjector->GetIgnoreLayers()) || !renderObjs[i]->GetProjected())
		{
			continue;
		}

		if ( renderObjs[i] && renderObjs[i]->GetRtti()->IsDerivedFrom(MeshRenderObject::RTTI)
			&& !renderObjs[i]->GetRtti()->IsDerivedFrom(SkinnedRenderObject::RTTI)
#ifdef __GENESIS_EDITOR__
			&& !mIsBrushHelper
#endif			
			)
		{
			GPtr<Graphic::RenderObject > renderObj = renderObjs[i];

			// skip the subRenderObject such as axis_X etc
			if ( renderObj->GetLayerID() == eSL_Debug )
				continue;

			GPtr<MeshRenderObject> meshRenderObj = renderObj.downcast<MeshRenderObject>();
			n_assert(meshRenderObj);

			// Get world matrix
			const Math::matrix44& worldMatrix = meshRenderObj->GetTransform();

			// Compute world-view-projection matrix
			if ( viewProjMatrix == Math::matrix44::zero() )
			{
				viewProjMatrix = Math::matrix44::multiply(
					mProjector->_CalcProjMatrix(),Math::matrix44::inverse(mProjector->GetTransform()));
			}
			Math::matrix44 worldViewProjMatrix = Math::matrix44::multiply(viewProjMatrix,worldMatrix);		

			// Get the collision mode
			Util::StringAtom mesh = meshRenderObj->GetMeshName();
			const GPtr<Graphic::CollisionModel>& collisionModel = collisionModelServer->GetCollisionModel( mesh.AsString() );

			// Setup clip planes in model space, NB: Opcode use negative side as inside
			// formula overturn : \\10.6.34.129\linuxsir\ÄÚÑµÎÄµµ\ÒýÇæ\Graphics\Math\plane_extraction.pdf
			clipPlanes[FRUSTUM_PLANE_LEFT].Set(
				- worldViewProjMatrix[0][0] - worldViewProjMatrix[3][0],
				- worldViewProjMatrix[0][1] - worldViewProjMatrix[3][1],
				- worldViewProjMatrix[0][2] - worldViewProjMatrix[3][2],
				- worldViewProjMatrix[0][3] - worldViewProjMatrix[3][3]);
			clipPlanes[FRUSTUM_PLANE_RIGHT].Set(
				+ worldViewProjMatrix[0][0] - worldViewProjMatrix[3][0],
				+ worldViewProjMatrix[0][1] - worldViewProjMatrix[3][1],
				+ worldViewProjMatrix[0][2] - worldViewProjMatrix[3][2],
				+ worldViewProjMatrix[0][3] - worldViewProjMatrix[3][3]);
			clipPlanes[FRUSTUM_PLANE_BOTTOM].Set(
				- worldViewProjMatrix[1][0] - worldViewProjMatrix[3][0],
				- worldViewProjMatrix[1][1] - worldViewProjMatrix[3][1],
				- worldViewProjMatrix[1][2] - worldViewProjMatrix[3][2],
				- worldViewProjMatrix[1][3] - worldViewProjMatrix[3][3]);
			clipPlanes[FRUSTUM_PLANE_TOP].Set(
				+ worldViewProjMatrix[1][0] - worldViewProjMatrix[3][0],
				+ worldViewProjMatrix[1][1] - worldViewProjMatrix[3][1],
				+ worldViewProjMatrix[1][2] - worldViewProjMatrix[3][2],
				+ worldViewProjMatrix[1][3] - worldViewProjMatrix[3][3]);
			clipPlanes[FRUSTUM_PLANE_NEAR].Set(
				- worldViewProjMatrix[2][0] - worldViewProjMatrix[3][0],
				- worldViewProjMatrix[2][1] - worldViewProjMatrix[3][1],
				- worldViewProjMatrix[2][2] - worldViewProjMatrix[3][2],
				- worldViewProjMatrix[2][3] - worldViewProjMatrix[3][3]);
			clipPlanes[FRUSTUM_PLANE_FAR].Set(
				+ worldViewProjMatrix[2][0] - worldViewProjMatrix[3][0],
				+ worldViewProjMatrix[2][1] - worldViewProjMatrix[3][1],
				+ worldViewProjMatrix[2][2] - worldViewProjMatrix[3][2],
				+ worldViewProjMatrix[2][3] - worldViewProjMatrix[3][3]);

			if (!planesCollider.Collide( planesCache, clipPlanes, 6, collisionModel->GetOpCodeModel(), NULL))
				continue;

			const uint* triangles = planesCollider.GetTouchedPrimitives();
			const uint numTriangles = planesCollider.GetNbTouchedPrimitives();

			if (!triangles || !numTriangles)
				continue;

			// Get the view vector base on projection type
			Math::float4 vv;
			Math::matrix44 eyeToModel = Math::matrix44::inverse(Math::matrix44::multiply( Math::matrix44::inverse(mProjector->GetTransform()), worldMatrix));

			if ( mProjector->GetViewType() == Graphic::Projector::VT_Persp )
			{
				// Use view position as view vector
				vv[0] = eyeToModel[0][3];
				vv[1] = eyeToModel[1][3];
				vv[2] = eyeToModel[2][3];
				vv[3] = eyeToModel[3][3];
			}
			else
			{
				// Use view direction as view vector
				vv[0] = eyeToModel[0][2];
				vv[1] = eyeToModel[1][2];
				vv[2] = eyeToModel[2][2];
				vv[3] = eyeToModel[3][2];
			}

			const Util::Array<Math::float4>& faceNormals = collisionModel->GetFaceNormals();
			const Util::Array<Math::float3>& vertices = collisionModel->GetVertices();
			const Util::Array<uint>& indices = collisionModel->GetIndices();
			SizeT vertexStart = mVertexs.Size();
			SizeT vertexCount = 0;
			SizeT cullCount = 0;


			// Reserve memory avoid allocate overhead
			mVertexs.Reserve(vertexStart + numTriangles*3);

			for (uint i = 0; i < numTriangles; ++i)
			{
				uint triangleIndex = triangles[i];
				Math::float4 faceNormal = Math::float4::normalize(faceNormals[triangleIndex]);
				faceNormal.set_w(0.0f);
				// check the triangle is projector facing
				if ( ! Math::n_fequal(Math::float4::dot4(faceNormal,vv), 0.0f, 0.001f) )
				{
					Math::float3 tempPos;
					Math::float4 result;
					// transform vertex from model space to world space
					for (int i = 0; i < 3; ++i,++vertexCount)
					{
						int index = triangleIndex*3 + i;

						tempPos = vertices[indices[index]];
						result = Math::matrix44::transform(worldMatrix,Math::float4(tempPos.x(),tempPos.y(),tempPos.z(),1.0f));

						tempPos.x() = result.x();
						tempPos.y() = result.y();
						tempPos.z() = result.z();

						mVertexs.Append(tempPos);

						_UpdateBoundingBox(tempPos);
						
					}
				}
			}

			// Check vertex limit
			n_assert(vertexStart <= mVertexLimit);
			if ( mVertexLimit <= vertexStart )
				break;	// Just for safely

			// check overrun
			bool overrun = vertexStart +  vertexCount > mVertexLimit;
			if (overrun)
			{
				// discard overrun vertices
				vertexCount = (mVertexLimit - vertexStart)/ 3 * 3;
				mVertexs.Resize(vertexStart + vertexCount,Math::float3(0.0, 0.0, 0.0));
			}

			// No more process because vertices overrun
			if (overrun)
				break;

		} 
		else if ( renderObjs[i]->GetRtti()->IsDerivedFrom(TerrainRenderObject::RTTI))
		{
			GPtr<TerrainRenderObject> terrainRenderObject = renderObjs[i].downcast<TerrainRenderObject>();
			n_assert(terrainRenderObject.isvalid());


			// catch indices
			Resources::Index16Container::value_type* pIndices = terrainRenderObject->GetTerrainNodeIndexData();
			SizeT indicesCount = terrainRenderObject->GetTerrainNodeIndexDataCount();
			SizeT positionCount = mTerrainVertexs.Size();
			for (int i = 0 ; i < indicesCount; ++i)
			{
				mTerrainIndices.Append(pIndices[i] + positionCount);
			}

			// catch position
			const Resources::PositionData::Elem* pLocalPosition = terrainRenderObject->GetTerrainNodePosData();
			SizeT positionsCount = terrainRenderObject->GetTerrainNodePosCount();
			for ( int i = 0; i < positionsCount; ++i)
			{
				const Math::float3 worldPostion = pLocalPosition[i].transformPoint(terrainRenderObject->GetTransform());
				mTerrainVertexs.Append(worldPostion);
				_UpdateBoundingBox(worldPostion);
			}

		} // end handling each render object

	} // end foreach render object
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_UpdateBoundingBox( const Math::float3 &pos)
{
	mAabb.extend(Math::float4(pos.x(),pos.y(),pos.z(),1.0f));
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::SetProjectorTrans(const Math::matrix44& trans)
{
	if (mProjector.isvalid())
	{		
		mProjector->SetTransform(trans);
	}
}

//--------------------------------------------------------------------------------
Math::scalar ProjectorRenderComponent::GetAlphaValue(Math::scalar u, Math::scalar v)
{
	if (GetMaterial(0).isvalid())
	{
		GPtr<Resources::Resource> pRes = GetMaterial(0)->GetTextureResInfo(0)->GetRes();
		n_assert(pRes.isvalid());
		GPtr<Resources::ImageRes> pImageRes = pRes.downcast<Resources::ImageRes>();
		Math::scalar alpha = pImageRes->GetAlphaValue(u, v);

		return alpha;
	}
	else
	{
		return 0.0f;
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::ActiveProjector(bool enable)
{
	EnableProjectorUpdate(enable);
}

//--------------------------------------------------------------------------------
const bool ProjectorRenderComponent::IsProjectorEnabled() const
{
	return mIsNeedUpdate;
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_BuildRenderable()
{
	n_assert( mActor );

	_BuildRenderObject();

	// Generate and fill renderable
	if ( mProjectorRenderObject.isvalid() && mPrimitive.IsValid() )
	{
		// Mesh
		mRenderableResUnitList[0].ResetRenderable<AppRenderable>();
		AppRenderable* renderable = mRenderableResUnitList[0].GetRenderableFast<AppRenderable>();
		renderable->SetRenderInfo( 0, mVertexs.Size(), 0, 0);
	}

	if (mProjectorRenderObject.isvalid() && mTerrainPrimitive.IsValid() )
	{
		// Terrain
		mRenderableResUnitList[1].ResetRenderable<AppRenderable>();
		AppRenderable* renderable = mRenderableResUnitList[1].GetRenderableFast<AppRenderable>();
		renderable->SetRenderInfo( 0, mTerrainVertexs.Size(), 0, mTerrainIndices.Size());
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_BuildRenderObject()
{
	// Generate new render object
	if ( !mProjectorRenderObject.isvalid() )
	{
		mProjectorRenderObject = ProjectorRenderObject::Create();
		mProjectorRenderObject->SetOwner(this);
		mProjectorRenderObject->SetTransform(Math::matrix44::identity());
	}
	mProjectorRenderObject->SetBoundingBox(mAabb);

	mAabb.begin_extend();
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::OnRenderSceneChanged()
{
	if (mProjectorRenderObject.isvalid() && mProjectorRenderObject->Attached())
	{
		mProjectorRenderObject->Attach(mActor->GetRenderScene());
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_AttachRenderObject()
{
	if (mProjectorRenderObject.isvalid())
	{
		n_assert(mActor);
		Graphic::RenderScene* rs = mActor->GetRenderScene();
		mProjector->SetRenderScene(rs);
		mProjectorRenderObject->Attach(rs);
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_DeattachRenderObject()
{
	if ( mProjectorRenderObject.isvalid() )
	{
		mProjector->SetRenderScene(NULL);
		mProjectorRenderObject->Detach();
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_BuildMeshInfo()
{
	using namespace RenderBase;

	// Mesh Use
	if ( mVertexs.Size() )
	{	
		Graphic::VertexBufferData2 vbd2;
		vbd2.GetVertexComponents().Append(
			RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));	// layout

		vbd2.Setup(mVertexs.Size(), sizeof(Math::float3), RenderBase::BufferData::Static, PrimitiveTopology::TriangleList, true);
		vbd2.SetVertices(&mVertexs[0], mVertexs.Size());
		if (mPrimitive.IsValid())
		{
			Graphic::GraphicSystem::Instance()->ChangePrimitiveHandle(mPrimitive, &vbd2, NULL);
		}
		else
		{
			mPrimitive = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, NULL);
		}
	}
	else
	{
		// No points found
		Graphic::GraphicSystem::Instance()->RemovePrimitive(mPrimitive);
		mPrimitive = RenderBase::PrimitiveHandle();
	}

	// Terrain use
	if ( mTerrainVertexs.Size() && mTerrainIndices.Size() )
	{	
		Graphic::VertexBufferData2 vbd2;
		vbd2.GetVertexComponents().Append(
			RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));	// layout

		vbd2.Setup(mTerrainVertexs.Size(), sizeof(Math::float3), RenderBase::BufferData::Static, PrimitiveTopology::TriangleList, true);
		vbd2.SetVertices(&mTerrainVertexs[0], mTerrainVertexs.Size());


		Graphic::IndexBufferData2 ibd2;
		ibd2.Setup(mTerrainIndices.Size(), RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
		ibd2.SetIndices(&mTerrainIndices[0], mTerrainIndices.Size());

		if (mTerrainPrimitive.IsValid())
		{
			Graphic::GraphicSystem::Instance()->ChangePrimitiveHandle(mTerrainPrimitive, &vbd2, &ibd2);
		}
		else
		{
			mTerrainPrimitive = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		}
	}
	else
	{
		// No terrain found
		Graphic::GraphicSystem::Instance()->RemovePrimitive(mTerrainPrimitive);
		mTerrainPrimitive = NULL;
	}
}
//--------------------------------------------------------------------------------
const RenderBase::PrimitiveHandle& ProjectorRenderComponent::GetPrimitiveHandleByRenderable( const Graphic::Renderable* renderable ) const
{
	if ( renderable == mRenderableResUnitList[0].GetRenderableFast<AppRenderable>() )
	{
		return mPrimitive;
	}
	else
	{
		return mTerrainPrimitive;
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::EnableProjectorUpdate(bool bEnable)
{
	mIsNeedUpdate = bEnable;
	
	if (bEnable)
	{
		_AttachRenderObject();
	}
	else
	{
		_DeattachRenderObject();
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::_OnMoveAfter()
{
	if ( mActor )
	{
		mProjector->SetTransform( mActor->GetWorldTranslateRotation() );
	}
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
{
	if( !pComponent.isvalid()  )
		return;
	if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
		return;

	GPtr<ProjectorRenderComponent> pSource = pComponent.downcast<ProjectorRenderComponent>();
	// copy component data
	mIsNeedUpdate = pSource->mIsNeedUpdate;
	SetMaterialID(0, pSource->GetMaterialID(0), false);

	// copy projector data
	GPtr<Graphic::Projector> pSourceProjector = pSource->GetProJector();
	n_assert( pSource->mProjector.isvalid() );
	mProjector->CopyParam(pSourceProjector);
}
//--------------------------------------------------------------------------------
#ifdef __GENESIS_EDITOR__	//	edtior use
bool ProjectorRenderComponent::GetBrushState() const
{
	return mIsBrushHelper;
}
//--------------------------------------------------------------------------------
void ProjectorRenderComponent::SetBrushState( const bool b )
{
	mIsBrushHelper = b;
}

#endif
//--------------------------------------------------------------------------------

}
#endif // __PROJECTOR_COMMIT__