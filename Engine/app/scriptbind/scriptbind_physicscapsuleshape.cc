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
#include "physXfeature/physicsCore/PhysicsCapsuleShape.h"

namespace App
{
	void ICallReg_ScriptRuntime_PhysicsCapsuleShape( void );

	//------------------------------------------------------------------------
	static void ICall_PhysicsCapsuleShape_SetRadius( MonoObject* pMonoObj,float radius )
	{
		ScriptObjWrapper<PhysicsCapsuleShape> self( pMonoObj );
		self->SetRadius(radius);
	}

	static float ICall_PhysicsCapsuleShape_GetRadius( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsCapsuleShape> self( pMonoObj );
		return self->GetRadius();
	}

	static void ICall_PhysicsCapsuleShape_SetHeight( MonoObject* pMonoObj,float height )
	{
		ScriptObjWrapper<PhysicsCapsuleShape> self( pMonoObj );
		self->SetHeight(height);
	}

	static float ICall_PhysicsCapsuleShape_GetHeight( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsCapsuleShape> self( pMonoObj );
		return self->GetHeight();
	}
}

#include "autogen/scriptbind_PhysicsCapsuleShape_register.h"
