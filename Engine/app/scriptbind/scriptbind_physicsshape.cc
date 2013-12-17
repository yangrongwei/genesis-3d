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
#include "scriptfeature/inc/script_utility.h"
#include "physXfeature/physicsCore/PhysicsShape.h"

namespace App
{
	void ICallReg_ScriptRuntime_PhysicsShape( void );

	static void ICall_PhysicsShape_SetDensity( MonoObject* pMonoObj, Math::scalar density )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		self->SetDensity(density);
	}

	static Math::scalar ICall_PhysicsShape_GetDensity( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		return self->GetDensity();
	}

	static void ICall_PhysicsShape_SetCenterPos( MonoObject* pMonoObj, Math::float3& pos )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		self->SetCenter(pos);
	}

	static void ICall_PhysicsShape_GetCenterPos( MonoObject* pMonoObj, Math::float3& pos )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		pos = self->GetLocalCenter();
	}

	static void ICall_PhysicsShape_SetRotation( MonoObject* pMonoObj, Math::quaternion& rotation )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		self->SetRotation(rotation);
	}

	static void ICall_PhysicsShape_GetRotation( MonoObject* pMonoObj, Math::quaternion& rotation )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		rotation = self->GetLocalRotation();
	}

	static void ICall_PhysicsShape_SetMaterialID( MonoObject* pMonoObj,MonoString* matID )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
		Util::String smatID = Utility_MonoStringToCppString( matID );
		self->SetMaterialID(smatID);
	}

	static MonoString* ICall_PhysicsShape_GetMaterialID( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<PhysicsShape> self( pMonoObj ); 
		return Utility_CppStringToMonoString(self->GetMaterialID().AsCharPtr());   
	}

	static void ICall_PhysicsShape_SetUserData( MonoObject* pMonoObj, void* obj)
	{
 		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
 		self->SetUserData(obj);
	}

	static void* ICall_PhysicsShape_GetUserData( MonoObject* pMonoObj )
	{
 		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
 		return self->GetUserData();
	}

	static void ICall_PhysicsShape_SetGroup( MonoObject* pMonoObj, int group)
	{
 		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
 		self->SetGroup(group);
	}

	static int ICall_PhysicsShape_GetGroup( MonoObject* pMonoObj )
	{
 		ScriptObjWrapper<PhysicsShape> self( pMonoObj );
 		return self->GetGroup();
	}
}
#include "autogen/scriptbind_PhysicsShape_register.h"
	
