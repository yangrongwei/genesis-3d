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
#include "scriptfeature/script_root_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/script_general_manager.h"

namespace App
{
	__ImplementClass( App::ScriptRootInstance, 'SRIN', Core::RefCounted );
	__ImplementImageSingleton( App::ScriptRootInstance );
	
	enum RootInstanceMethodIndex
	{
		RootInstanceMethodIndex_Begin = 0,
		RootInstanceMethodIndex_OnLoad = RootInstanceMethodIndex_Begin,
		RootInstanceMethodIndex_OnTick,
		RootInstanceMethodIndex_Exit,
		RootInstanceMethodIndex_OnStopped,
		RootInstanceMethodIndex_OnResumed,
		RootInstanceMethodIndex_Count,
	};

	
	static const char* gRootInstanceMethod[] = 
	{
		"*:Load()",
		"*:Tick()",
		"*:Exit()",
		"*:Stopped()",
		"*:Resumed()",
	};

	const Util::String& ScriptRootInstance::s_csRootClassName = "ScriptRoot";		

	const Util::String& ScriptRootInstance::s_csParentRootClassName = "RuntimeScriptRoot";		
	
	ScriptRootInstance::ScriptRootInstance()
		: m_ArrEntryMethods()
		, m_bInit( false )
		, m_pRootClass( NULL )
		, m_pRootObj( NULL )
		, m_uiRootRefID( c_iInvalidMonoRefID )
	{
		__ConstructImageSingleton
	}

	ScriptRootInstance::~ScriptRootInstance()
	{
		__DestructImageSingleton

		if ( c_iInvalidMonoRefID!=m_uiRootRefID )
		{
			mono_gchandle_free( m_uiRootRefID );
			m_uiRootRefID = c_iInvalidMonoRefID;
		}

		m_pRootClass  = NULL;
		m_pRootObj    = NULL;
		m_bInit       = false;
	}

	void ScriptRootInstance::CreateSingleton( void )
	{
		ScriptRootInstance::Create();
		ScriptRootInstance::Instance()->AddRef();
	}

	void ScriptRootInstance::DestorySingleton( void )
	{
		ScriptRootInstance::Instance()->Release();
	}

	void ScriptRootInstance::Init()
	{
		ScriptGeneralManager* manager = ScriptGeneralManager::Instance(); n_assert(manager);
		m_pRootClass = manager->GetMonoClassByName( s_csRootClassName, s_csScriptRuntimeNamespace, s_cpUserDefCSharpLibName );

		MonoClass* m_pParentRootClass = manager->GetMonoClassByName( s_csParentRootClassName, s_csScriptRuntimeNamespace, s_cpScriptRuntimeLibraryName );
		n_assert(m_pParentRootClass);

		if ( m_pRootClass==NULL )
		{
			n_warning("this app have no root class,maybe user don't need it.so root class's init will be canceled here");
			m_bInit = false;
			return;
		}

		mono_bool bParent = mono_class_is_subclass_of(m_pRootClass, m_pParentRootClass, true);

		if(!bParent)
		{
			n_warning("user don't inherit the script root in run time libery,but this will not cause any trouble at this moment");
			m_bInit = false;
			return;
		}

		MonoDomain* mono_domain = mono_domain_get();
		m_pRootObj  = mono_object_new( mono_domain, m_pRootClass );
		n_assert(NULL != m_pRootObj);
		mono_runtime_object_init(m_pRootObj);
		m_uiRootRefID = mono_gchandle_new ( m_pRootObj, 1 );
		n_assert(NULL != m_pRootObj);
		
		GetEntryMethods();
		m_bInit = true;
	}

	void ScriptRootInstance::OnLoad()
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[RootInstanceMethodIndex_OnLoad];
		if ( NULL==pMethod )
		{
			return; 
		}

		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, NULL );
	}

	void ScriptRootInstance::OnTick()
	{
			if( !m_bInit )
			{
				return;
			}
			
			MonoMethod* pMethod = m_ArrEntryMethods[RootInstanceMethodIndex_OnTick];
			if ( NULL==pMethod )
			{
					return;
			}
			Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, NULL );
	}

	void ScriptRootInstance::OnExit()
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[RootInstanceMethodIndex_Exit];
		if ( NULL==pMethod )
		{
			return; 
		}

		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, NULL );
	}

	void ScriptRootInstance::OnStopped()
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[RootInstanceMethodIndex_OnStopped];
		if ( NULL==pMethod )
		{
			return; 
		}

		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, NULL );
	}

	void ScriptRootInstance::OnResumed()
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[RootInstanceMethodIndex_OnResumed];
		if ( NULL==pMethod )
		{
			return; 
		}

		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, NULL );
	}

	void ScriptRootInstance::GetEntryMethods()
	{
		for (int i = RootInstanceMethodIndex_Begin; i < RootInstanceMethodIndex_Count; ++i)
		{
			MonoMethodDesc*	pDesc = NULL;
			MonoMethod*  pMethod = NULL;

			pDesc = mono_method_desc_new( gRootInstanceMethod[i], false ); n_assert( pDesc );
			pMethod	=  mono_method_desc_search_in_class( pDesc, m_pRootClass );
			mono_method_desc_free(pDesc);
			if( pMethod==NULL )
			{
				n_warning( "root class didn't implement this method,maybe user don't need it" );
			}
			m_ArrEntryMethods.Append(pMethod);
		}
	}
}

