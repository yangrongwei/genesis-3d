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
#ifndef __PhysicsServer_H__
#define __PhysicsServer_H__

#include "app/appframework/app_fwd_decl.h"
#include "app/appframework/actor.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/array.h"
#include "PhysicsDeclaration.h"

using namespace physx;
using namespace physx::debugger::comm;
using namespace pxtask;

namespace App
{
	class EngineErrorCallback;
	class EngineMemAllocator;
	class EngineSimulationCallback;
	class PhysicsBodyComponent;
	class EngineProfileEventNameProvider;
	class EnginePVDConnectHandler;
	class PhysicsEntity;
	class UserReportPair;

	class PhysicsServer : public Core::RefCounted
	{
		__DeclareClass(PhysicsServer);
		__DeclareImageSingleton(PhysicsServer);

	public:

		PhysicsServer();

		virtual ~PhysicsServer();

	public://process logic

		void InitPhysXSDK();

		void InitScene();

		void Update(const Math::scalar& time);

	public://PVD
		void togglePvdConnection(bool isConnect);
		void createPvdConnection();
		void registPvdConnectHander();
		void unregistPvdConnectHander();
		void enablePvdVisualDebug();
		void disablePvdVisualDebug();

	public://getter and setter
		PxPhysics*	  GetPhysics();
		PxScene*      GetPhysXScene();

		PxControllerManager* GetControllerManager() const;

		PxCooking* GetCookingInterface() const;

		uint GetCollisionMask(IndexT layer) const;

		bool GetCollisionFlag(IndexT layer1,IndexT layer2 );//return true: ignore, false:not ignore

		void SetCollisionFlag(IndexT layer1,IndexT layer2,bool ignore );

		void EnablePhysicsSimulate();

		void DisablePhysicsSimulate();

		void AttachPhysicsEntity(GPtr<PhysicsEntity> pEntity);

		void DettachPhysicsEntity(GPtr<PhysicsEntity> pEntity);

		void UpdatePhysicsEntity(float time);

		Util::Array<uint> GetAllCollisionMask(); 

		void SetAllCollisionMaskMatrix( Util::Array<uint>& array );

		bool IsPhysicsOpen() const;

		void DisableMoveAfter();

		void EnableMoveAfter();

		bool IsMoveAfterEnabled() const;

		void SetGravity(const Math::float3& gravity);

		const Math::float3& GetGravity() const;

		void SetSleepThreshold(float velocity);

		const float GetSleepThreshold() const;

		void SetMaxAngularVelocity(float velocity);

		const float GetMaxAngularVelocity() const;

		void SetDefaultMaterial(Util::String mat);

		const Util::String GetDefaultMaterial() const;
		PxMaterial*		GetDefaultPxMaterial() { n_assert(m_pMaterial) return m_pMaterial; }

	private://basic feature
		PxFoundation*		  m_pFoundation;
		PxProfileZone*		  m_pProfileZone;
		PxProfileZoneManager* m_pProfileZoneMgr;
		PxControllerManager*  m_pControllerMgr;
		PxPhysics*			  m_pPhysics;
		PxCooking*			  m_pCooking;
		CudaContextManager*	  m_pCudaContextMgr;

	private://optional feature
		PxDefaultCpuDispatcher*mCpuDispatcher;

	private://user define
		EngineErrorCallback*  m_pErrorCallback;
		EngineMemAllocator*	  m_pMemAllocator;
		EngineSimulationCallback* m_pSimulaReport;
		EnginePVDConnectHandler* m_pPvdConnHandler;
		EngineProfileEventNameProvider* m_pProfileNameProvider;
	private://Scene build
		PxScene*			  m_pScene;
		PxMaterial*			  m_pMaterial;

	private://configurations
		bool                  m_bEnablePhys;
		bool                  m_bEnableOnMoveAfter;
		bool				  m_bRecordMemoryAllocations;

		Util::Array<GPtr<PhysicsEntity> > m_EntitySet;

		Math::float3     m_Gravity;
		float            m_SleepThreshold;
		float            m_MaxAngularVelocity;
		Util::String     m_DefaultMaterial;
	};

	inline PxPhysics* PhysicsServer::GetPhysics()
	{
		n_assert(m_pPhysics != NULL);
		return m_pPhysics;
	}

	inline PxScene* PhysicsServer::GetPhysXScene()
	{
		n_assert(m_pScene != NULL);
		return m_pScene;
	}

	inline PxCooking* PhysicsServer::GetCookingInterface() const
	{
		n_assert(m_pCooking != NULL);
		return m_pCooking;
	}

	inline PxControllerManager* PhysicsServer::GetControllerManager() const
	{
		n_assert(m_pControllerMgr);
		return m_pControllerMgr;
	}

	inline void PhysicsServer::EnablePhysicsSimulate()
	{
		m_bEnablePhys = true;
	}

	inline void PhysicsServer::DisablePhysicsSimulate()
	{
		m_bEnablePhys = false;
	}

	inline bool PhysicsServer::IsPhysicsOpen() const
	{
		return m_bEnablePhys;
	}

	inline bool PhysicsServer::IsMoveAfterEnabled() const
	{
		return m_bEnableOnMoveAfter;
	}


	inline void PhysicsServer::DisableMoveAfter()
	{
		m_bEnableOnMoveAfter = false;
	}

	inline void PhysicsServer::EnableMoveAfter()
	{
		m_bEnableOnMoveAfter = true;
	}

}

#endif
