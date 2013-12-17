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
#ifndef __PHYSX_COMMIT__
#include "stdneb.h"
#include "appframework/actor.h"
#include "PhysicsTerrian.h"
#include "PhysicsServer.h"
#include "PhysicsMaterial.h"
#include "PhysicsUtil.h"
#include "terrainfeature/components/TerrainRenderComponent.h"
#include "math/float3.h"
#include "PxShape.h"
#include "PxPhysics.h"
#include "PxRigidActor.h"
#include "PxHeightField.h"
#include "PxHeightFieldDesc.h"
#include "PxHeightFieldSample.h"
#include "PxHeightFieldGeometry.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
#define HOLE_MATERIAL_IDX 127

	__ImplementClass(App::PhysicsTerrain, 'PHTS', App::PhysicsShape);


	PhysicsTerrain::PhysicsTerrain()
		: m_bPhysicsTerrainLod(false),
		m_pHeightField(NULL)
	{
		m_ShapeType = TERRAINSHAPE;
	}

	PhysicsTerrain::~PhysicsTerrain()
	{
		OnDestory();
	}

	void PhysicsTerrain::OnDestory()
	{
		if (m_pHeightField != NULL)
		{
			m_pHeightField->release();
			m_pHeightField = NULL;
		}
	}

	bool PhysicsTerrain::CreatePhysicsTerrain(GPtr<PhysicsBodyComponent> component)
	{
		GPtr<Component> comObject = component->GetActor()->FindComponent( TerrainRenderComponent::RTTI );
		if (!comObject.isvalid())
		{
			n_warning("You must create a terrain before attaching a physics terrain! \n");
			return false;
		}

		GPtr<TerrainRenderComponent> pTerrainCom = comObject.downcast<TerrainRenderComponent>();
		n_assert(pTerrainCom.isvalid());

		SizeT terrainSize = pTerrainCom->GetTerrainDataSource()->GetHeightMapSize();

		const Math::float3& terrainScale = pTerrainCom->GetTerrainDataSource()->GetTerrainRatio();

		uint terrainRow = static_cast<uint>(terrainSize);
		uint terrainCol = static_cast<uint>(terrainSize);
		PxHeightFieldDesc heightFieldDesc;
		heightFieldDesc.nbRows		        = terrainRow;
		heightFieldDesc.nbColumns           = terrainCol;

		heightFieldDesc.samples.data   = n_new_array(uint, terrainRow * terrainCol);
		heightFieldDesc.samples.stride = sizeof(uint);

		uchar* pCurrentByte = (uchar*)heightFieldDesc.samples.data;
		n_assert(pCurrentByte);

		for (IndexT iRow = 0; iRow < terrainSize; ++iRow)
		{
			for (IndexT iCol = 0; iCol < terrainSize; ++iCol)
			{
				PxHeightFieldSample* pCurrentSample = (PxHeightFieldSample*)pCurrentByte;
				n_assert(pCurrentSample);

				pCurrentSample->height         = (ushort)pTerrainCom->GetTerrainDataSource()->GetLocalYByUnit(iRow, iCol);

				//if the area is not a hole ,these values should not be the same as the holeMaterial
// 				if ( pTerrainCom->IsHole(iRow,iCol) )
// 				{
// 					pCurrentSample->materialIndex0 = HOLE_MATERIAL_IDX;
// 					pCurrentSample->materialIndex1 = HOLE_MATERIAL_IDX;
// 				} 
// 				else
// 				{
// 					pCurrentSample->materialIndex0 = 0;
// 					pCurrentSample->materialIndex1 = 0;
// 				}


				pCurrentSample->setTessFlag();

				pCurrentByte += heightFieldDesc.samples.stride;
			}
		}

		m_pHeightField = PhysicsServer::Instance()->GetPhysics()->createHeightField(heightFieldDesc);

		n_delete_array(heightFieldDesc.samples.data);

		m_pGeometry = new PxHeightFieldGeometry(m_pHeightField,PxMeshGeometryFlags(),terrainScale.y(),terrainScale.x(),terrainScale.z());
		n_assert(m_pGeometry)
			return true;
	}

	bool PhysicsTerrain::CopyFrom( const GPtr<PhysicsShape>& pShape )
	{
		if ( pShape.isvalid() && pShape->GetType() == m_ShapeType)
		{
			Super::CopyFrom(pShape);
		}
		return false;
	}

	bool PhysicsTerrain::IsGeometryValid()
	{
		return IsValid() && ((PxHeightFieldGeometry*)m_pGeometry)->isValid();
	}

}
#endif
