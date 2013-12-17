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
#include "PxMaterial.h"
#include "PhysicsServer.h"
#include "PxPhysics.h"
#include "PxMaterialFlags.h"
#include "PhysicsMaterial.h"
#include "PhysicsUtil.h"

using namespace physx;
namespace App
{
	__ImplementClass(PhysicsMaterial, 'PXMA', Core::RefCounted);

	PhysicsMaterial::PhysicsMaterial()
		: m_fStaticFriction(0.3f),
		m_fDynamicFriction(0.3f),
		m_fRestitution(0.0f),
		m_eRestitutionCombine((CombineMode)PxCombineMode::eAVERAGE),
		m_eFrictionComine((CombineMode)PxCombineMode::eAVERAGE),
		m_pPhysXMaterial(NULL),
		m_bCreateFromFile(true),
		m_sPhyXMatID("asset:Physics/Default.pmat")
	{

	}

	PhysicsMaterial::~PhysicsMaterial()
	{
		OnDestory();
	}

	PhysicsMaterial* PhysicsMaterial::Create(Math::scalar staticFriction, Math::scalar dynamicFriction, Math::scalar restitution,
		CombineMode frictionCombine /*= AVERAGE*/, CombineMode restitutionCombine /*= AVERAGE*/)
	{
		PhysicsMaterial* pMat = PhysicsMaterial::Create();
		pMat->SetStaticFriction(staticFriction);
		pMat->SetDynamicFriction(dynamicFriction);
		pMat->SetRestitution(restitution);
		pMat->SetFrictionCombineMode(frictionCombine);
		pMat->SetRestitutionCombineMode(restitutionCombine);
		pMat->SetLoadFromFile(false);
		pMat->OnCreate();
		return pMat;
	}

	PhysicsMaterial* PhysicsMaterial::Create(Util::String& materialFile)
	{
		PhysicsMaterial* pMat = PhysicsMaterial::Create();
		pMat->SetMatFile(materialFile);
		pMat->SetLoadFromFile(true);
		pMat->OnCreate();
		return pMat;
	}

	bool PhysicsMaterial::OnCreate()
	{
		OnDestory();
		GPtr<Resources::PhysXMaterialResInfo> pMatInfo;
		if(m_bCreateFromFile)
		{
			pMatInfo  = Resources::ResourceManager::Instance()->CreatePhysXMaterialResInfo(m_sPhyXMatID, Resources::ResourcePriority::Synchronization);
			if ( !pMatInfo.isvalid() )
			{
				n_error("create physics material failed!");
				return false;
			}
			if ( pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetMat()==NULL )
			{
				m_fStaticFriction = pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetStaticFriction();
				m_fDynamicFriction = pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetDynamicFriction();
				m_fRestitution = pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetRestitution();
				m_eFrictionComine = (CombineMode)pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetFrictionCombine();
				m_eRestitutionCombine = (CombineMode)pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetRestitutionCombine();
			}
			else
			{
				PhysicsMaterial*pMat = pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->GetMat();
				m_fStaticFriction = pMat->GetStaticFriction();
				m_fDynamicFriction = pMat->GetDynamicFriction();
				m_fRestitution = pMat->GetRestitution();
				m_eFrictionComine = (CombineMode)pMat->GetFrictionCombineMode();
				m_eRestitutionCombine = (CombineMode)pMat->GetRestitutionCombineMode();
			}
		}
		PxPhysics* pSDK = PhysicsServer::Instance()->GetPhysics();
		n_assert(pSDK);
		m_pPhysXMaterial = pSDK->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fRestitution);
		if(!m_pPhysXMaterial)
		{
			return false;
		}
		m_pPhysXMaterial->setFrictionCombineMode((physx::PxCombineMode::Enum)m_eFrictionComine);
		m_pPhysXMaterial->setRestitutionCombineMode((physx::PxCombineMode::Enum)m_eRestitutionCombine);
		if(pMatInfo.isvalid())
		{
			pMatInfo->GetRes().downcast<Resources::PhysXMaterialRes>()->SetMat(this);
		}
		return true;
	}

	bool PhysicsMaterial::OnDestory()
	{
		if (m_pPhysXMaterial != NULL)
		{
			m_pPhysXMaterial->release();
			m_pPhysXMaterial = NULL;
		}
		return true;
	}

	void PhysicsMaterial::SetMaterial(PxMaterial* pMaterial)
	{
		if(m_pPhysXMaterial)
		{
			m_pPhysXMaterial->release();
		}
		m_pPhysXMaterial = pMaterial;
	}

	void PhysicsMaterial::SetStaticFriction(Math::scalar friction)
	{
		if (friction < 0.0f)
		{
			friction = 0.0f;
		}
		m_fStaticFriction = friction;
		if (m_pPhysXMaterial)
		{		
			m_pPhysXMaterial->setStaticFriction(friction);
		}
	}

	void PhysicsMaterial::SetDynamicFriction(Math::scalar friction)
	{
		if (friction < 0.0f)
		{
			friction = 0.0f;
		}
		m_fDynamicFriction = friction;
		if (m_pPhysXMaterial)
		{
			m_pPhysXMaterial->setDynamicFriction(friction);
		} 
	}

	void PhysicsMaterial::SetRestitution(Math::scalar bounce)
	{
		bounce = Math::n_clamp(bounce, 0.0f, 1.0f);
		m_fRestitution = bounce;
		if (m_pPhysXMaterial)
		{
			m_pPhysXMaterial->setRestitution(bounce);
		} 
	}

	void PhysicsMaterial::SetFrictionCombineMode(CombineMode combineMode)
	{
		if(combineMode > 4 && combineMode != 0x7fffffff)
			return;
		m_eFrictionComine = combineMode;
		if (m_pPhysXMaterial)
		{
			m_pPhysXMaterial->setFrictionCombineMode((physx::PxCombineMode::Enum)combineMode);
		}
	}

	void PhysicsMaterial::SetRestitutionCombineMode(CombineMode bounceMode)
	{
		if(bounceMode > 4 && bounceMode != 0x7fffffff)
			return;
		m_eRestitutionCombine = bounceMode;
		if (m_pPhysXMaterial)
		{
			m_pPhysXMaterial->setRestitutionCombineMode((physx::PxCombineMode::Enum)bounceMode);
		} 
	}

	void PhysicsMaterial::SetFlag( MaterialFlag flag, bool )
	{
		//physx::PxMaterialFlag::Enum
	}

	bool PhysicsMaterial::GetFlag(MaterialFlag flag) const
	{
		return false;
	}

}
#endif


