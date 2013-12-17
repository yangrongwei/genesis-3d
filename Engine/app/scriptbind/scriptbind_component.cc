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
#include "scriptfeature/inc/script_utility.h"
#include "appframework/component.h"
namespace App
{
	void ICallReg_ScriptRuntime_Component( void );
	//-----------------------------------------------------------------------
	static MonoObject* ICall_Component_GetOwner( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Component> self( pMonoObj );
		Actor* pActor = self->GetActor();
		
		if( NULL==pActor )
		{
			return NULL;
		}
		return CppObjectToScriptObj<Actor>( *pActor );
	}
	//-----------------------------------------------------------------------
	// - all component's ref of the script will be released here
	static void ICall_Component_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Component> self( pMonoObj );
		Component* pComponent = self.GetCppObjPtr();
		n_assert( NULL!=pComponent );

		ReleaseCppObjWithMonoObj<Component>( pComponent, pMonoObj );
	}
	//-----------------------------------------------------------------------
	static mono_bool ICall_Component_Active( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Component> self( pMonoObj );
		return self->IsActive();
	}
	//-----------------------------------------------------------------------
}

#include "autogen/scriptbind_Component_register.h"
