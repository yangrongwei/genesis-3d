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
#include "physXfeature/physicsCore/PhysicsMeshShape.h"

namespace App
{
	void ICallReg_ScriptRuntime_PhysicsMeshSphere( void );

	//------------------------------------------------------------------------
	static void ICall_PhysicsMeshShape_SetMeshID( MonoObject* pMonoObj,MonoString* meshID )
	{
		ScriptObjWrapper<PhysicsMeshShape> self( pMonoObj );

		Util::String str = Utility_MonoStringToCppString( meshID );
		self->SetMeshFileName( str );
	}

	static MonoString* ICall_PhysicsMeshShape_GetMeshID( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<PhysicsMeshShape> self( pMonoObj );
		return Utility_CppStringToMonoString(self->GetMeshFileName().AsCharPtr());
	}
}
#include "autogen/scriptbind_PhysicsMeshShape_register.h"
