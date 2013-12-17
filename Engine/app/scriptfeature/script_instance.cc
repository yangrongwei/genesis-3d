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
#include "foundation/util/array.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/script_general_manager.h"
#include "graphicfeature/components/rendercomponent.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicsystem/base/RenderToTexture.h"

namespace App
{

	// - ScriptInstance implement --------------------------------------------------------------------------
	__ImplementClass( App::ScriptInstance, 'SPIN', Core::RefCounted );
	//------------------------------------------------------------------------
	ScriptInstance::~ScriptInstance()
	{
		m_pMonoScript = NULL;
		m_pDicRegistedMessageHandler = NULL;
	}
	//------------------------------------------------------------------------
	bool ScriptInstance::Init( const TMonoScriptPtr& pMonoScript )
	{
		n_assert( NULL==m_pMonoScript );
		n_assert( NULL!=pMonoScript );
		m_pMonoScript = pMonoScript;

		// - get Methods from mono script
		m_pArrEntryMethods = pMonoScript->GetEntryMethods();
		m_pDicMethods  	   = pMonoScript->GetMethods(); 

		// - get registed message method
		m_pDicRegistedMessageHandler = pMonoScript->GetRegistedMessageHandlers();

		// - create a script instance on the mono side
		MonoClass* pMonoClass = pMonoScript->GetMonoClass();
		n_assert( NULL!=pMonoClass );
		MonoDomain* pMonoDomain = mono_domain_get();
		m_pMonoObj  = mono_object_new( pMonoDomain, pMonoClass ) ;
		n_assert( NULL!=m_pMonoObj );

		MonoMethod *method = NULL;
	
		method = mono_class_get_method_from_name (pMonoClass, ".ctor", 0);
	
		Utility_MonoRuntimeInvoke(method,m_pMonoObj,NULL);

		// - bind this two object
		BindCppObjWithMonoObj(this,m_pMonoObj);

		//- bind here is different ,because script instance's mono object can't be a managed object,it's mono object should not be
		//- collected by the garbage collector until script instance is destructed.

		//- so I called mono_gchandle_new here to add a reference to the mono object ,and pined it's position in memory, so the garbage collector
		//- can't destruct it or move it's position in mono's heaps until I call the function mono_gchandle_free(int).
		//- note:The same thing had already be done in class ScriptRootInstance.see To learn more,see the detail in file script_root_instance.
		m_Ref = mono_gchandle_new(m_pMonoObj,1);

		n_assert( NULL!=m_pMonoObj );

		// - has been init
		return true;
	}
	//------------------------------------------------------------------------
	void ScriptInstance::SetOwner( Actor* pOwner )
	{
		script_fatal_error(( NULL==m_pOwner )&&( NULL!=pOwner ));
		m_pOwner = pOwner;
	}
	//------------------------------------------------------------------------
	MonoObject* ScriptInstance::CallMethod( const char* methodName, void** params )
	{
		if ( !IsInit() )
		{
			return NULL ;
		}

		// - looks up methods
		n_assert( NULL!=m_pDicMethods );
		Util::String sMethodName = methodName ;
		IndexT idx = m_pDicMethods->FindIndex( sMethodName );
		if ( InvalidIndex==idx )
		{
			return NULL;
		}

		// - call method
		MonoMethod* pMethod = m_pDicMethods->ValueAtIndex( idx );
		return Utility_MonoRuntimeInvoke( pMethod, m_pMonoObj, params );
	}
	//------------------------------------------------------------------------	
	void ScriptInstance::OnBeginFrame( void )
	{
		invokeScript(EEntryMethodIndex_OnBeginFrame);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnFrame( void )
	{
		invokeScript(EEntryMethodIndex_OnFrame);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnEndFrame( void )
	{
		invokeScript(EEntryMethodIndex_OnEndFrame);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnLoad( void )
	{
		invokeScript(EEntryMethodIndex_OnLoad);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnExit( void )
	{
		invokeScript(EEntryMethodIndex_OnExit);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnStopped( void )
	{
		invokeScript(EEntryMethodIndex_OnStopped);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnResumed( void )
	{
		invokeScript(EEntryMethodIndex_OnResumed);
	}
	//------------------------------------------------------------------------
	void ScriptInstance::OnWillRenderObject( RenderComponent* renderComponent )
	{
		MonoObject* mo = CppObjectToScriptObj( *renderComponent );
		invokeScript(EEntryMethodIndex_OnWillRenderObject, (void**)&mo);
	}
	//------------------------------------------------------------------------
	bool ScriptInstance::OnRenderPostEffect(CameraComponent* camera, Graphic::RenderToTexture* source, Graphic::RenderToTexture* destination)
	{
		MonoObject* params[3];
		params[0] = CppObjectToScriptObj( *camera );
		params[1] = CppObjectToScriptObj( *source );
		params[2] = CppObjectToScriptObj( *destination );
		MonoObject* ret = invokeScript(EEntryMethodIndex_OnRenderPostEffect, (void**)&params);
		if (ret)
		{
			return MonoObjectUnbox<bool>(ret);
		}
		else
		{
			return false;
		}
		
	}
	//------------------------------------------------------------------------
	void ScriptInstance::HandleMessage( const TScriptMessagePtr& msg )
	{
		if ( !IsInit() )
		{
			return ;
		}

		Util::String name = msg->GetName();		

		IndexT idx = m_pDicRegistedMessageHandler->FindIndex( name );
		if ( InvalidIndex==idx )
		{
			return;
		}

		MonoMethod* pMethod = m_pDicRegistedMessageHandler->ValueAtIndex( idx );

		//const GPtr<Core::RefCounted>& pParam = msg->GetParam();
		
		void *args[1];
		args[0] = msg->GetMonoParam();

		Utility_MonoRuntimeInvoke( pMethod, m_pMonoObj, args );
	}

	void ScriptInstance::Discard()
	{
		if(m_pOwner!=NULL)
		{
			m_pOwner=NULL;
			//- I call mono_gchandle_free here to tell the garbage collector that I don't need this mono object any more
			//- and you can collect it at any time, so the garbage collector may collect it in the next call of gc.collect(int generation).
			//- But this mono object's generation may be a high number now,so it's OK if it is still alive after the next garbage collection call.
			if (ScriptGeneralManager::HasInstance())//- to check here because when we shut down the engine,script system is killed first,so we don't need to release here.
			{
				mono_gchandle_free(m_Ref);
			}
		}

	}
}

