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
#include "scriptfeature/script_IAP_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/script_general_manager.h"

namespace App
{
	__ImplementClass( App::ScriptIAPInstance, 'SIAP', Core::RefCounted );
	__ImplementImageSingleton( App::ScriptIAPInstance );
	
	enum RootInstanceMethodIndex
	{
		IAPInstanceMethodIndex_Begin = 0,
		IAPInstanceMethodIndex_OnGetProductInfo = IAPInstanceMethodIndex_Begin,
		IAPInstanceMethodIndex_OnPurchaseSucc,
		IAPInstanceMethodIndex_OnPurchaseFailed,
		IAPInstanceMethodIndex_OnValidateFailed,
		IAPInstanceMethodIndex_Count
	};

		//函数的参数列表里不允许有任何空格存在，要不然，mono会找不到这个函数。
	static const char* gBaseIAPInstanceMethod[] = 
	{
		"*:OnSKGetProductInfo(String,String)",
		"*:OnSKPurchaseSucc(String,String,String)",
		"*:OnSKPruchaseFailed(String,String,RuntimeInAppPurchaseInstance/SKErrorType,String)",
		"*:OnSKValidateFailed(String)",
	};

	const Util::String& ScriptIAPInstance::s_csDerivedClassName = "InAppPurchaseInstance";		

	const Util::String& ScriptIAPInstance::s_csBaseClassName = "RuntimeInAppPurchaseInstance";		
	
	ScriptIAPInstance::ScriptIAPInstance()
		: m_ArrEntryMethods()
		, m_bInit( false )
		, m_pRootClass( NULL )
		, m_pRootObj( NULL )
		, m_uiRootRefID( c_iInvalidMonoRefID )
	{
		__ConstructImageSingleton
	}

	ScriptIAPInstance::~ScriptIAPInstance()
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

	void ScriptIAPInstance::CreateSingleton( void )
	{
		ScriptIAPInstance::Create();
		ScriptIAPInstance::Instance()->AddRef();
	}

	void ScriptIAPInstance::DestorySingleton( void )
	{
		ScriptIAPInstance::Instance()->Release();
	}

	void ScriptIAPInstance::Init()
	{
		ScriptGeneralManager* manager = ScriptGeneralManager::Instance(); n_assert(manager);
		m_pRootClass = manager->GetMonoClassByName( s_csDerivedClassName, s_csScriptRuntimeNamespace, s_cpUserDefCSharpLibName );

		MonoClass* m_pParentRootClass = manager->GetMonoClassByName( s_csBaseClassName, s_csScriptRuntimeNamespace, s_cpScriptRuntimeLibraryName );
		n_assert(m_pParentRootClass);

		if ( m_pRootClass==NULL )
		{
			n_warning("this app have no IAP Derived class!");
			m_bInit = false;
			return;
		}

		mono_bool bParent = mono_class_is_subclass_of(m_pRootClass, m_pParentRootClass, true);

		if(!bParent)
		{
			n_warning("user don't inherit the IAP base class  in run time libery!");
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

	void ScriptIAPInstance::onStoreKitGetProductPrice(Util::Dictionary<Util::String, Util::String> & idAndPrice)
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[IAPInstanceMethodIndex_OnGetProductInfo];
		if ( NULL==pMethod )
		{
			return; 
		}
		void* params[2] ;
		for ( IndexT idx = 0; idx < idAndPrice.Size();idx++ )
		{ 
			MonoString* monoStringID	 = Utility_CppStringToMonoString( idAndPrice.KeyAtIndex(idx).Get() );
			params[0]=monoStringID;
			MonoString* monoStringPrice  = Utility_CppStringToMonoString( idAndPrice.ValueAtIndex(idx).Get() );
			params[1]=monoStringPrice;
			Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, (void**)&params );
		}
		
	}

	void ScriptIAPInstance::onStoreKitPurchaseSucceed(const Util::String & productIdentifier, const Util::String & transactionIdentifier, const Util::String & transactionReceipt)
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[IAPInstanceMethodIndex_OnPurchaseSucc];
		if ( NULL==pMethod )
		{
			return; 
		}
		void* params[3] ;
		MonoString* monoStringPID	 = Utility_CppStringToMonoString( productIdentifier.Get() ); 
		params[0]=monoStringPID;
		MonoString* monoStringTID  = Utility_CppStringToMonoString( transactionIdentifier.Get() );
		params[1]=monoStringTID;
		MonoString* monoStringReceipt  = Utility_CppStringToMonoString(  transactionReceipt.Get());
		params[2]=monoStringReceipt;
		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, (void**)&params );		
	
	}

	void ScriptIAPInstance::onStoreKitPurchaseFailedWithError(const Util::String & productIdentifier, const Util::String & transactionIdentifier, NALSystem::ALSystem::SK_ERROR errorType, const Util::String & error)
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[IAPInstanceMethodIndex_OnPurchaseFailed];
		if ( NULL==pMethod )
		{
			return; 
		}
		void* params[4] ;
		MonoString* monoStringPID	 = Utility_CppStringToMonoString( productIdentifier.Get() ); 
		params[0]=monoStringPID;
		MonoString* monoStringTID  = Utility_CppStringToMonoString( transactionIdentifier.Get() );
		params[1]=monoStringTID;
		params[2]=&errorType;
		MonoString* monoStringError  = Utility_CppStringToMonoString(  error.Get());
		params[3]=monoStringError;
		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, (void**)&params );		
		
	}
	void ScriptIAPInstance::onStoreKitValidateProductIDFailed( const Util::String & invalidProductIdentifiers )
	{
		if( !m_bInit )
		{
			return;
		}

		MonoMethod* pMethod = m_ArrEntryMethods[IAPInstanceMethodIndex_OnValidateFailed];
		if ( NULL==pMethod )
		{
			return; 
		}
		void* params[1] ;
		MonoString* monoStringID	 = Utility_CppStringToMonoString( invalidProductIdentifiers.Get() );
		params[0]=monoStringID;
		Utility_MonoRuntimeInvoke( pMethod, m_pRootObj, (void**)&params );	
	}

	void ScriptIAPInstance::GetEntryMethods()
	{
		for (int i = IAPInstanceMethodIndex_Begin; i < IAPInstanceMethodIndex_Count; ++i)
		{
			MonoMethodDesc*	pDesc = NULL;
			MonoMethod*  pMethod = NULL;

			pDesc = mono_method_desc_new( gBaseIAPInstanceMethod[i], false ); n_assert( pDesc );
			pMethod	=  mono_method_desc_search_in_class( pDesc, m_pRootClass );
			mono_method_desc_free(pDesc);
			if( pMethod==NULL )
			{
				n_warning( "IAP derived class didn't implement this method!" );
			}
			m_ArrEntryMethods.Append(pMethod);
		}
	}

}

