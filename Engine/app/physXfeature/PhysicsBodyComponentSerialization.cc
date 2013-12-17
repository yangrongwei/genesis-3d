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
#include "physXfeature/PhysicsBodyComponent.h"
#include "physicsCore/PhysicsDynamic.h"
namespace App
{
	class PhysicsBodyComponentSerialization
	{
	public:
		PhysicsBodyComponentSerialization( const PhysicsBodyComponent* pComponent );

	public:
		void Load( Version ver, AppReader* pReader );
		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Load_3( AppReader* pReader );
		void Load_4( AppReader* pReader );
		void Save( AppWriter* pWriter );

	protected:
		const PhysicsBodyComponent* m_Object;

	};

#define DEFINE_SERIAL_ITEM_NAME(name) static const char* s_##name = #name
	DEFINE_SERIAL_ITEM_NAME(Mass);
	DEFINE_SERIAL_ITEM_NAME(LinearDamping);
	DEFINE_SERIAL_ITEM_NAME(AngularDamping);
	DEFINE_SERIAL_ITEM_NAME(LinearVelocity);
	DEFINE_SERIAL_ITEM_NAME(AngularVelocity);
	DEFINE_SERIAL_ITEM_NAME(MaxAngularVelocity);
	DEFINE_SERIAL_ITEM_NAME(UseGravity);
	DEFINE_SERIAL_ITEM_NAME(Kinematic);
	DEFINE_SERIAL_ITEM_NAME(Dynamic);
	DEFINE_SERIAL_ITEM_NAME(CDMode);
	DEFINE_SERIAL_ITEM_NAME(XPosFreeze);
	DEFINE_SERIAL_ITEM_NAME(YPosFreeze);
	DEFINE_SERIAL_ITEM_NAME(ZPosFreeze);
	DEFINE_SERIAL_ITEM_NAME(XRotFreeze);
	DEFINE_SERIAL_ITEM_NAME(YRotFreeze);
	DEFINE_SERIAL_ITEM_NAME(ZRotFreeze);

	DEFINE_SERIAL_ITEM_NAME(ConstForce);
	DEFINE_SERIAL_ITEM_NAME(LocalConstForce);
	DEFINE_SERIAL_ITEM_NAME(ConstTorque);
	DEFINE_SERIAL_ITEM_NAME(LocalConstTorque);
	DEFINE_SERIAL_ITEM_NAME(ConstLinearVel);
	DEFINE_SERIAL_ITEM_NAME(ConstAngularVel);

	DEFINE_SERIAL_ITEM_NAME(Position);
	DEFINE_SERIAL_ITEM_NAME(Rotation);

	//------------------------------------------------------------------------
	PhysicsBodyComponentSerialization::PhysicsBodyComponentSerialization(const PhysicsBodyComponent* pComponent)
		: m_Object(pComponent)
	{

	}

	//------------------------------------------------------------------------
	inline void PhysicsBodyComponentSerialization::Load( Version ver, AppReader* pReader )
	{
		if ( 1 == ver )
		{
			Load_1(pReader);

		}
		else if ( 2 == ver )
		{
			Load_2(pReader);

		}
		else if ( 3 == ver )
		{
			Load_3(pReader);

		}
		else if ( 4 == ver )
		{
			Load_4(pReader);
		}
		else
		{
			n_error(" PhysicsBodyComponentSerialization::Load unknonw version " );
		}

	}

	//------------------------------------------------------------------------
	void PhysicsBodyComponentSerialization::Load_1(AppReader* pReader)
	{
		PhysicsBodyComponent* pComponent = const_cast<PhysicsBodyComponent*>(m_Object);
		GPtr<PhysicsEntity> pEntity = pComponent->GetEntity();
		if ( !pEntity.isvalid() )
		{
			return;
		}

		bool _bUseGrav, _bKinematic;
		Math::scalar _linearDamping, _angularDamping, tempScalar;
		Math::float3 _linearVel, _angularVel;
		unsigned int tempUint;

		pReader->SerializeFloat(s_Mass,tempScalar);
		pReader->SerializeFloat(s_LinearDamping,_linearDamping);
		pReader->SerializeFloat(s_AngularDamping,_angularDamping);

		pReader->SerializeFloat3(s_LinearVelocity,_linearVel);
		pReader->SerializeFloat3(s_AngularVelocity,_angularVel);

		pReader->SerializeBool(s_UseGravity,_bUseGrav);
		pReader->SerializeBool(s_Kinematic,_bKinematic);

		if ( pEntity->GetType() == PHYSICSDYNAMIC )
		{
			GPtr<PhysicsDynamic> _pDynamic = pEntity.downcast<PhysicsDynamic>();
			_pDynamic->SetLinearDamping(_linearDamping);
			_pDynamic->SetAngularDamping(_angularDamping);
			_pDynamic->SetLinearVelocity(_linearVel);
			_pDynamic->SetAngularVelocity(_angularVel);
			_pDynamic->SetUseGravity(_bUseGrav);
			_pDynamic->SetKinematic(_bKinematic);
		}

		pReader->SerializeBool(s_Dynamic,_bUseGrav);

		pReader->SerializeUInt(s_CDMode,tempUint);
	}
	//------------------------------------------------------------------------
	void PhysicsBodyComponentSerialization::Load_2( AppReader* pReader )
	{
		Load_1(pReader);
		PhysicsBodyComponent* pComponent = const_cast<PhysicsBodyComponent*>(m_Object);
		GPtr<PhysicsEntity> pEntity = pComponent->GetEntity();
		if ( !pEntity.isvalid() )
		{
			return;
		}


		bool XPosF = false;
		bool YPosF = false;
		bool ZPosF = false;

		bool XRotF = false;
		bool YRotF = false;
		bool ZRotF = false;

		Math::float4 constForce;
		Math::float4 localConstForce;
		Math::float4 constTorque;
		Math::float4 localConstTorque;

		pReader->SerializeBool(s_XPosFreeze ,XPosF);
		pReader->SerializeBool(s_YPosFreeze ,YPosF);
		pReader->SerializeBool(s_ZPosFreeze ,ZPosF);

		pReader->SerializeBool(s_XRotFreeze ,XRotF);
		pReader->SerializeBool(s_YRotFreeze ,YRotF);
		pReader->SerializeBool(s_ZRotFreeze ,ZRotF);

		pReader->SerializeFloat4(s_ConstForce,constForce);
		pReader->SerializeFloat4(s_LocalConstForce,localConstForce);
		pReader->SerializeFloat4(s_ConstTorque,constTorque);
		pReader->SerializeFloat4(s_LocalConstTorque,localConstTorque);

		if ( pEntity->GetType() == PHYSICSDYNAMIC )
		{
			GPtr<PhysicsDynamic> _pDynamic = pEntity.downcast<PhysicsDynamic>();

			_pDynamic->SetConstantForce(Math::float3(constForce.x(),constForce.y(),constForce.z()));
			_pDynamic->SetConstantTorques(Math::float3(constTorque.x(),constTorque.y(),constTorque.z()));
		}
	}
	//------------------------------------------------------------------------
	void PhysicsBodyComponentSerialization::Load_3( AppReader* pReader )
	{
		Load_2(pReader);
		PhysicsBodyComponent* pComponent = const_cast<PhysicsBodyComponent*>(m_Object);

		Math::vector pos;
		Math::quaternion qua;
		pReader->SerializeFloat4(s_Position,pos);
		pReader->SerializeQuaternion(s_Rotation,qua);
	}
	void PhysicsBodyComponentSerialization::Load_4( AppReader* pReader )
	{
		PhysicsBodyComponent* pComponent = const_cast<PhysicsBodyComponent*>(m_Object);

		bool _bUseGrav, _bKinematic, _bDynamic;
		Math::scalar _linearDamping, _angularDamping, tempScalar;
		Math::float3 _linearVel, _angularVel;

		pReader->SerializeFloat(s_Mass,tempScalar);
		pReader->SerializeFloat(s_LinearDamping,_linearDamping);
		pReader->SerializeFloat(s_AngularDamping,_angularDamping);

		pReader->SerializeFloat3(s_LinearVelocity,_linearVel);
		pReader->SerializeFloat3(s_AngularVelocity,_angularVel);

		pReader->SerializeBool(s_UseGravity,_bUseGrav);
		pReader->SerializeBool(s_Kinematic,_bKinematic);
		pReader->SerializeBool(s_Dynamic,_bDynamic);

		Math::float4 constForce;
		Math::float4 constTorque;
		Math::float4 constLinearVel;
		Math::float4 constAngularVel;

		pReader->SerializeFloat4(s_ConstForce,constForce);
		pReader->SerializeFloat4(s_ConstTorque,constTorque);
		pReader->SerializeFloat4(s_ConstLinearVel,constLinearVel);
		pReader->SerializeFloat4(s_ConstAngularVel,constAngularVel);

		GPtr<PhysicsEntity> pEntity = pComponent->GetEntity();
		if ( !pEntity.isvalid() )
		{
			if (_bDynamic)
			{
				pEntity = pComponent->CreateEntity(PHYSICSDYNAMIC);
			}
			else
			{
				pEntity = pComponent->CreateEntity(PHYSICSSTATIC);
			}
		}
		if ( pEntity->GetType() == PHYSICSDYNAMIC )
		{
			GPtr<PhysicsDynamic> _pDynamic = pEntity.downcast<PhysicsDynamic>();
			_pDynamic->SetLinearDamping(_linearDamping);
			_pDynamic->SetAngularDamping(_angularDamping);
			_pDynamic->SetLinearVelocity(_linearVel);
			_pDynamic->SetAngularVelocity(_angularVel);
			_pDynamic->SetUseGravity(_bUseGrav);
			_pDynamic->SetKinematic(_bKinematic);

			_pDynamic->SetConstantForce(Math::float3(constForce.x(),constForce.y(),constForce.z()));
			_pDynamic->SetConstantTorques(Math::float3(constTorque.x(),constTorque.y(),constTorque.z()));
			_pDynamic->SetConstantVelocity(Math::float3(constLinearVel.x(),constLinearVel.y(),constLinearVel.z()));
			_pDynamic->SetConstantAngularVel(Math::float3(constAngularVel.x(),constAngularVel.y(),constAngularVel.z()));
		}


		Math::vector pos;
		Math::quaternion qua;
		pReader->SerializeFloat4(s_Position,pos);
		pReader->SerializeQuaternion(s_Rotation,qua);
	}
	//------------------------------------------------------------------------
	void PhysicsBodyComponentSerialization::Save(AppWriter* pSerialize)
	{
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version PhysicsBodyComponent::GetVersion() const
	{
		return 7;
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void PhysicsBodyComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		if ( ver < 5 )
		{
			PhysicsBodyComponentSerialization Serialize(this);
			Serialize.Load( ver, pReader );
		} 
		else
		{
			// 
			uint _type = PHYSICSNONE;
			pReader->SerializeUInt("Type", _type);
			GPtr<PhysicsEntity> _entity = CreateEntity((PhysicsType)_type);
			if ( _entity.isvalid() )
			{
				_entity->Load(ver,pReader);
			}
		}
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void PhysicsBodyComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		if ( m_pPhysXActor.isvalid() )
		{
			pWriter->SerializeUInt("Type", m_pPhysXActor->GetType());
			m_pPhysXActor->Save(pWriter);
		}
		else
		{
			pWriter->SerializeUInt("Type", PHYSICSNONE);
		}
	}

}

#endif //__PHYSX_COMMIT__