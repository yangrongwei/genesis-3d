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
#include "GraphicSystem.h"
#include "PhysicsServer.h"
#include "PhysicsUtil.h"
#include "appframework/actor.h"
#include "PxControllerManager.h"
#include "PxCudaContextManager.h"
#include "PvdConnectionManager.h"
#include "PxPhysicsAPI.h"
#include "physXfeature/PhysicsBodyComponent.h"
#include "appframework/component_force_compile.cc"

#if __WIN32__
#include "foundation/memory/win360/win360memory.h"
#endif

#define MaxLayers 32
#define	PVD_HOST	"127.0.0.1"

namespace App
{
	__ImplementClass(PhysicsServer, 'PXSR', Core::RefCounted);
	__ImplementImageSingleton(PhysicsServer);


	class EngineErrorCallback : public PxErrorCallback
	{
	public:

		virtual void reportError(PxErrorCode::Enum code, const char *message, const char* file, int line)
		{
			switch(code)
			{
			case PxErrorCode::eDEBUG_WARNING:
				n_warning("PhysX DEBUG WARNING: %s \n File: %s \n Line: %d \n", message, file, line);
				break;
			case PxErrorCode::eINVALID_PARAMETER:
				n_error("PhysX Error:Invalid Parameter, %s \n File: %s \n Line: %d \n", message, file, line);
				break;
			case PxErrorCode::eINVALID_OPERATION:
				n_error("PhysX Error:Invalid Operation, %s \n File: %s \n Line: %d \n", message, file, line);
				break;
			case PxErrorCode::eOUT_OF_MEMORY:
				n_error("PhysX Error:Out of Memory, %s \n File: %s \n Line: %d \n", message, file, line);
				break;
			case PxErrorCode::eABORT:
				n_error("PhysX Error:Abort, %s \n File: %s \n Line: %d \n", message, file, line);
				break;
			case PxErrorCode::ePERF_WARNING:
#ifdef _DEBUG
				n_warning("PhysX Warning:Perfmance Warning, %s \n File: %s \n Line: %d \n", message, file, line);
				break;
#endif
			default:
				break;
			}
		}
	};

	class EngineMemAllocator : public PxAllocatorCallback
	{
	public:

		virtual void* allocate(size_t size, const char*typeName, const char* filename, int line) 
		{
			return Memory::Alloc(Memory::PhysicsHeap, size);
		}

		virtual void deallocate(void* pMemory)
		{
			Memory::Free(Memory::PhysicsHeap, pMemory);
		}
	};

	class EngineSimulationCallback : public PxSimulationEventCallback
	{
	public:

		virtual void onContact(const PxContactPairHeader& pairHeader,const PxContactPair*pair,PxU32 nbPairs);
		virtual void onTrigger(PxTriggerPair*pairs,PxU32 count);
		virtual void onConstraintBreak(PxConstraintInfo*constraints,PxU32 count){}
		virtual void onWake(PxActor**actors,PxU32 count){}
		virtual void onSleep(PxActor**actors,PxU32 count){}
	};

	class EngineProfileEventNameProvider : public physx::PxProfileNameProvider
	{
	public:
		virtual physx::PxProfileNames getProfileNames() const;
	};

#define DEFINE_EVENT( name ) PxProfileEventName( #name, PxProfileEventId( name, true ) ),
	static PxProfileEventName gEventNames[] = {
		DEFINE_EVENT(0)
	};
#undef DEFINE_EVENT
	static PxU32 gEventNamesCount = 1;
	static PxProfileNames gPxProfileNames(gEventNamesCount,gEventNames);
	PxProfileNames EngineProfileEventNameProvider::getProfileNames() const
	{
		return gPxProfileNames;
	}

	class EnginePVDConnectHandler : public physx::debugger::comm::PvdConnectionHandler
	{
	public:
		void onPvdSendClassDescriptions( PvdConnection& connection ) {}
		void onPvdConnected( PvdConnection& connection ) {}
		void onPvdDisconnected( PvdConnection& connection ) {}
	};

	void EngineSimulationCallback::onContact(const PxContactPairHeader& pairHeader,const PxContactPair*pair,PxU32 nbPairs)
	{
		for(PxU32 i = 0;i < nbPairs; i++)
		{
			const PxContactPair& cp = pair[i];
			if(cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				if (!pairHeader.actors[0]|| !pairHeader.actors[1] || !pairHeader.actors[0]->userData || !pairHeader.actors[1]->userData)
				{
					return;
				}

				Component* first = (Component*)pairHeader.actors[0]->userData;
				Component* second = (Component*)pairHeader.actors[1]->userData;

				GPtr<UserReportPair> pairs = UserReportPair::Create(first, second);

				if (cp.flags & PxContactPairFlag::eACTOR_PAIR_HAS_FIRST_TOUCH)
				{
					if(first != NULL)
						first->SendMessageToScript<UserReportPair>("OnCollisionEnter", *pairs.get_unsafe());
					if(second != NULL)
						second->SendMessageToScript<UserReportPair>("OnCollisionEnter", *pairs.get_unsafe());			
				}
			}
		}
	}

	void EngineSimulationCallback::onTrigger(PxTriggerPair*pairs,PxU32 count)
	{
		for(PxU32 i = 0;i < count; i++)
		{
			if ( pairs->triggerShape == NULL || pairs->otherShape == NULL )
				continue;
			if( pairs[i].flags & (PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::eDELETED_SHAPE_OTHER))
				continue;
			Component* first = (Component*)pairs[i].triggerShape->getActor().userData;
			Component* second = (Component*)pairs[i].otherShape->getActor().userData;

			GPtr<UserReportPair> pair = UserReportPair::Create(first, second);

			if (pairs[i].status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				if(first != NULL)
					first->SendMessageToScript<UserReportPair>("OnTriggerEnter",*pair.get_unsafe());
				if(second != NULL)
					second->SendMessageToScript<UserReportPair>("OnTriggerEnter", *pair.get_unsafe());
			}
			else if (pairs[i].status == PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
			{
				if(first != NULL)
					first->SendMessageToScript<UserReportPair>("OnTriggerStay", *pair.get_unsafe());
				if(second != NULL)
					second->SendMessageToScript<UserReportPair>("OnTriggerStay", *pair.get_unsafe());
			}
			else if (pairs[i].status == PxPairFlag::eNOTIFY_TOUCH_LOST)
			{
				if(first != NULL)
					first->SendMessageToScript<UserReportPair>("OnTriggerLeave", *pair.get_unsafe());
				if(second != NULL)	
					second->SendMessageToScript<UserReportPair>("OnTriggerLeave", *pair.get_unsafe());
			}
			break;
		}
	}

	static Util::Array<uint> m_LayerCollisionFlag;
	static PxFilterFlags ContactFilter(PxFilterObjectAttributes attributes0,
		PxFilterData filterData0, 
		PxFilterObjectAttributes attributes1,
		PxFilterData filterData1,
		PxPairFlags& pairFlags,
		const void* constantBlock,
		PxU32 constantBlockSize)
	{
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_PERSISTS;
			return PxFilterFlag::eDEFAULT;
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;

		// The mark in the word3 is the group of the shape
		if (filterData0.word3 & PhysicsFlag::eSL_CCD_FLAG || filterData1.word3 & PhysicsFlag::eSL_CCD_FLAG)
		{
			pairFlags |= PxPairFlag::eSWEPT_INTEGRATION_LINEAR;
		}

		PxU32 ShapeGroup0 = filterData0.word0 & 31;
		PxU32 ShapeGroup1 = filterData1.word0 & 31;

		if ((m_LayerCollisionFlag[ShapeGroup0] & (1 << ShapeGroup1)) == 0)
			return PxFilterFlag::eSUPPRESS;
		else
		{
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			return PxFilterFlag::eDEFAULT;
		}
	}

	PhysicsServer::PhysicsServer()
		: m_pPhysics(NULL),
		m_pFoundation(NULL),
		m_pScene(NULL),
		m_pCooking(NULL),
		m_pMaterial(NULL),
		m_DefaultMaterial(""),
		m_pCudaContextMgr(NULL),
		m_pControllerMgr(NULL),
		m_pProfileZoneMgr(NULL),
		m_pProfileZone(NULL),
		m_pErrorCallback(NULL),
		m_pMemAllocator(NULL),
		m_pSimulaReport(NULL),
		mCpuDispatcher(NULL),
		m_bEnablePhys(false),
#ifdef __GENESIS_EDITOR__
		m_bEnableOnMoveAfter(true),
#else
		m_bEnableOnMoveAfter(false),
#endif
		m_Gravity(Math::float3(0.0f, -9.81f, 0.0f)),
		m_SleepThreshold(0.5f),
		m_MaxAngularVelocity(7.0f),
		m_bRecordMemoryAllocations(true)
	{
		__ConstructImageSingleton;

		m_pErrorCallback  = n_new(EngineErrorCallback);
		m_pMemAllocator   = n_new(EngineMemAllocator);
		m_pSimulaReport = n_new(EngineSimulationCallback);
		m_pPvdConnHandler = n_new(EnginePVDConnectHandler);
		m_pProfileNameProvider = n_new(EngineProfileEventNameProvider);

		m_LayerCollisionFlag.Resize(32,0xffffffff);
	}

	PhysicsServer::~PhysicsServer()
	{
		__DestructImageSingleton;
		if (m_pScene != NULL)
		{
			m_pScene->release();
			m_pScene = NULL;
		}

		if ( mCpuDispatcher != NULL )
		{
			mCpuDispatcher->release();
			mCpuDispatcher = NULL;
		}

		if (m_pCooking != NULL)
		{
			m_pCooking->release();
			m_pCooking = NULL;

		}

		if (m_pControllerMgr != NULL)
		{
			m_pControllerMgr->release();
			m_pControllerMgr = NULL;
		}

#ifdef PX_WINDOWS
		if ( m_pCudaContextMgr != NULL )
		{
			m_pCudaContextMgr->release();
			m_pCudaContextMgr = NULL;
		}
#endif

		if (m_pPhysics != NULL)
		{
			m_pPhysics->release();
			m_pPhysics = NULL;
		}

		if (m_pErrorCallback != NULL)
		{
			n_delete(m_pErrorCallback);
			m_pErrorCallback = NULL;
		}

		if (m_pMemAllocator != NULL)
		{
			n_delete(m_pMemAllocator);
			m_pMemAllocator = NULL;
		}

		if (m_pSimulaReport != NULL)
		{
			n_delete(m_pSimulaReport);
			m_pSimulaReport = NULL;
		}

		if (m_pPvdConnHandler != NULL)
		{
			n_delete(m_pPvdConnHandler);
			m_pPvdConnHandler = NULL;
		}

		if (m_pProfileNameProvider != NULL)
		{
			n_delete(m_pProfileNameProvider);
			m_pProfileNameProvider = NULL;
		}
	}

	void PhysicsServer::InitPhysXSDK()
	{
		m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,*m_pMemAllocator,*m_pErrorCallback);
		if(!m_pFoundation)
			n_error("PxCreateFoundation failed!");
		m_pProfileZoneMgr = &PxProfileZoneManager::createProfileZoneManager(m_pFoundation);
		if(!m_pProfileZoneMgr)
			n_error("PxProfileZoneManager::createProfileZoneManager failed!");
		m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale(), m_bRecordMemoryAllocations, m_pProfileZoneMgr);
		if(!m_pPhysics)
			n_error("PxCreatePhysics failed!");

		if(m_pProfileZone == NULL)
			m_pProfileZone = &PxProfileZone::createProfileZone(m_pFoundation, "EngineProfileZone", *m_pProfileNameProvider);
		m_pProfileZoneMgr->addProfileZone(*m_pProfileZone);

		if(!PxInitExtensions(*m_pPhysics))
			n_error("PxInitExtensions failed!");

		m_pCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pFoundation, PxCookingParams());
		if(!m_pCooking)
			n_error("PxCreateCooking failed!");

		m_pControllerMgr = PxCreateControllerManager(*m_pFoundation);
		if(!m_pControllerMgr)
			n_error("Create Controllere Manager Error!");

#ifdef PX_WINDOWS
		if ( m_pProfileZoneMgr != NULL )
		{
			pxtask::CudaContextManagerDesc _CudaDesc;
			m_pCudaContextMgr = pxtask::createCudaContextManager(*m_pFoundation, _CudaDesc, m_pProfileZoneMgr);
			if( m_pCudaContextMgr )
			{
				if( !m_pCudaContextMgr->contextIsValid() )
				{
					m_pCudaContextMgr->release();
					m_pCudaContextMgr = NULL;
				}
			}
		}
#endif

		togglePvdConnection(true);
	}

	void PhysicsServer::InitScene()
	{
		n_assert(NULL == m_pScene);

		PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());
		sceneDesc.gravity = PxVec3(m_Gravity.x(), m_Gravity.y(), m_Gravity.z());

		if(!sceneDesc.cpuDispatcher)
		{
			mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			if(!mCpuDispatcher)
				n_error("PxDefaultCpuDispatcherCreate failed!");
			sceneDesc.cpuDispatcher	= mCpuDispatcher;
		}

		if(!sceneDesc.filterShader)
			sceneDesc.filterShader	= &PxDefaultSimulationFilterShader;

#ifdef PX_WINDOWS
		if(!sceneDesc.gpuDispatcher && m_pCudaContextMgr)
		{
			sceneDesc.gpuDispatcher = m_pCudaContextMgr->getGpuDispatcher();
		}
#endif

#ifdef PX_PS3
		if(!sceneDesc.spuDispatcher)
		{
			mSpuDispatcher = PxDefaultSpuDispatcherCreate(PxGetPS3Extension().getSimulationTaskSet(),
				PxGetPS3Extension().getQueryTaskSet());
			if(!mSpuDispatcher)
				n_error("PxDefaultSpuDispatcherCreate failed!");
			sceneDesc.spuDispatcher = mSpuDispatcher;
		}
#endif

		sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
		sceneDesc.filterShader = ContactFilter;
		sceneDesc.simulationEventCallback = m_pSimulaReport;

		m_pScene = m_pPhysics->createScene(sceneDesc);
		if(!m_pScene)
			n_error("createScene failed!");

		PxSceneFlags flag = m_pScene->getFlags();

		m_pScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 0.0f);
		m_pScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES,	1.0f);

		m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.1f);
		if(!m_pMaterial)
			n_error("createMaterial failed!");

	}


	void PhysicsServer::Update(const Math::scalar& time)
	{
		if (!m_bEnablePhys)
		{
			return;
		}

#if _DEBUG
		//g_KeepTrackOfVRD.UpdateCamera();
#endif

		if (m_pScene != NULL && time < 1.0f)
		{
			m_pScene->simulate(time);

			m_pScene->fetchResults(true);

			UpdatePhysicsEntity(time);
		}
	}


	void PhysicsServer::togglePvdConnection(bool isConnect)
	{
		if(!m_pPhysics->getPvdConnectionManager()) 
			return;
		if(isConnect && m_pPhysics->getPvdConnectionManager()->isConnected())
			return;
		if(!isConnect && !m_pPhysics->getPvdConnectionManager()->isConnected())
			return;
		if (m_pPhysics->getPvdConnectionManager()->isConnected())
			m_pPhysics->getPvdConnectionManager()->disconnect();
		else
			createPvdConnection();
	}

	void PhysicsServer::createPvdConnection()
	{
		if(m_pPhysics->getPvdConnectionManager() == NULL)
			return;

		PxVisualDebuggerConnectionFlags theConnectionFlags( PxVisualDebuggerExt::getAllConnectionFlags() );

		PVD::PvdConnection* theConnection = PxVisualDebuggerExt::createConnection(m_pPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10, theConnectionFlags );
	}

	void PhysicsServer::registPvdConnectHander()
	{
		if(m_pPhysics->getPvdConnectionManager())
			m_pPhysics->getPvdConnectionManager()->addHandler(*m_pPvdConnHandler);
	}

	void PhysicsServer::unregistPvdConnectHander()
	{
		if(m_pPhysics->getPvdConnectionManager())
			m_pPhysics->getPvdConnectionManager()->removeHandler(*m_pPvdConnHandler);

	}
	void PhysicsServer::enablePvdVisualDebug()
	{
		togglePvdConnection(true);
	}
	void PhysicsServer::disablePvdVisualDebug()
	{
		togglePvdConnection(false);
	}

	uint PhysicsServer::GetCollisionMask(IndexT layer) const
	{
		n_assert(layer >= 0 && layer < m_LayerCollisionFlag.Size());
		return m_LayerCollisionFlag[layer];
	}

	Util::Array<uint> PhysicsServer::GetAllCollisionMask()
	{
		return m_LayerCollisionFlag;
	}

	void PhysicsServer::SetAllCollisionMaskMatrix( Util::Array<uint>& arr )
	{
		m_LayerCollisionFlag = arr;
	}

	bool PhysicsServer::GetCollisionFlag(IndexT layer1,IndexT layer2 )
	{	
		// true: ignore, false:not ignore
		if ( layer1 >= MaxLayers || layer2 >= MaxLayers )
		{
			n_assert(0);
			return true;
		}
		return (m_LayerCollisionFlag[layer1] & (1<<layer2))== 0? true : false;
	}

	void PhysicsServer::SetCollisionFlag(IndexT layer1,IndexT layer2,bool ignore )
	{
		if ( layer1 >= MaxLayers || layer2 >= MaxLayers )
		{
			n_assert(0);
			return;
		}

		if (ignore)
		{
			m_LayerCollisionFlag[layer1] &= ~(1<<layer2);
			m_LayerCollisionFlag[layer2] &= ~(1<<layer1);
		}
		else
		{
			m_LayerCollisionFlag[layer1] |= 1<<layer2;
			m_LayerCollisionFlag[layer2] |= 1<<layer1;
		}

	}

	void PhysicsServer::SetGravity(const Math::float3& gravity)
	{
		m_Gravity = gravity;
		if (m_pScene != NULL)
		{
			m_pScene->setGravity((const PxVec3&)gravity);
		}
	}

	const Math::float3& PhysicsServer::GetGravity() const
	{
		return m_Gravity;
	}

	void PhysicsServer::SetSleepThreshold(float velocity)
	{
		m_SleepThreshold = velocity;
		if (m_pScene != NULL)
		{
			int nb = m_pScene->getNbActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
			if(nb <= 0)
				return;
			PxRigidDynamic**actors = new PxRigidDynamic*[nb];
			m_pScene->getActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC,(PxActor**)actors,nb);
			for(int i=0;i<nb;i++)
			{
				actors[i]->setSleepThreshold(velocity);
			}
			delete []actors;
		}
	}

	const float PhysicsServer::GetSleepThreshold() const
	{
		return m_SleepThreshold;
	}

	void PhysicsServer::SetMaxAngularVelocity(float velocity)
	{
		m_MaxAngularVelocity = velocity;
		if (m_pScene != NULL)
		{
			int nb = m_pScene->getNbActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
			if(nb <= 0)
				return;
			PxRigidDynamic**actors = new PxRigidDynamic*[nb];
			m_pScene->getActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC,(PxActor**)actors,nb);
			for(int i=0;i<nb;i++)
			{
				actors[i]->setMaxAngularVelocity(velocity);
			}
			delete []actors;
		}
	}

	const float PhysicsServer::GetMaxAngularVelocity() const
	{
		return m_MaxAngularVelocity;
	}

	void PhysicsServer::SetDefaultMaterial(Util::String mat)
	{
		this->m_DefaultMaterial = mat;
	}

	const Util::String PhysicsServer::GetDefaultMaterial() const
	{
		return m_DefaultMaterial;
	}

	void PhysicsServer::UpdatePhysicsEntity(float time)
	{
		for ( int i=0; i<m_EntitySet.Size(); ++i )
		{
			m_EntitySet[i]->Tick(time);
		}
	}


	void PhysicsServer::AttachPhysicsEntity( GPtr<PhysicsEntity> pEntity )
	{
		if ( pEntity.isvalid() )
		{
			m_EntitySet.Append(pEntity);
		}
	}

	void PhysicsServer::DettachPhysicsEntity( GPtr<PhysicsEntity> pEntity )
	{
		IndexT index = m_EntitySet.FindIndex(pEntity);
		if ( index!=InvalidIndex )
		{
			m_EntitySet.EraseIndex(index);
		}
	}
}
#endif
