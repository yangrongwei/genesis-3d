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
#include "foundation/util/dictionary.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/script_general_manager.h"
#include "scriptfeature/inc/script_message.h"

namespace App
{
	// -  MonoScript implement ------------------------------------------------------------------------------
	__ImplementClass( App::MonoScript, 'MNSP', Core::RefCounted );

	MonoScript::MonoScript()
		: m_bInit( false )
		, m_sNamespace()
		, m_sClassName()
		, m_sAssemblyName()
		, m_pMonoClass( NULL )
		, m_dicMethods()
		, m_arrEntryMethods( EEntryMethodIndex_Num, EEntryMethodIndex_Num )
		, m_dicRegistedMessageHandler()
	{
		m_arrEntryMethods.Resize( EEntryMethodIndex_Num, NULL );
	}
	//------------------------------------------------------------------------
	MonoScript::~MonoScript()
	{
		m_dicRegistedMessageHandler.Clear();
		m_mapFileds.Clear();
	}
	//------------------------------------------------------------------------
	bool MonoScript::Init( MonoClass* pMonoClass, 
						const Util::String& sClassName, 
						const Util::String& sNamespace, 
						const Util::String& sAssemblyName,
						const bool mem)
	{
		// - can't be initlized before
		n_assert( NULL==m_pMonoClass );

		// - pMonoClass may be NULL
		if ( NULL==pMonoClass )
		{
			return false;
		}

		// - can't be init before
		if ( IsValid() )
		{
			return false;
		}

		// - check if this class is derived from scriptable class
		MonoClass* pScriptableClass = ScriptGeneralManager::Instance()->GetMonoClassByName( s_csScriptableClassName, s_csScriptRuntimeNamespace, s_csScriptRuntimeLibraryName );
		n_assert( NULL!=pScriptableClass );

		if (!mem)
		{
			mono_bool bParentRight = mono_class_is_subclass_of( pMonoClass, pScriptableClass, true );
			if ( !bParentRight )
			{
				return false;
			}
		}


		m_sClassName	= sClassName;
		m_sNamespace	= sNamespace;
		m_sAssemblyName = sAssemblyName; 
		
		// - get methods from this class,and terminal at ScriptableClass
		m_pMonoClass = pMonoClass;
		GetEntryMethods( pMonoClass, pScriptableClass );

		// - get message handler,if it has
		GetMessageHandlerMethods( pMonoClass );

		// - get fields which need to reflect to editor
		GetClassFields( pMonoClass );
	
		// - set init true
		m_bInit = true;

		return true;
	}
	//------------------------------------------------------------------------
	TScriptInstancePtr MonoScript::CreateInstance( TMonoScriptPtr& pScript, Actor* pOwner )
	{
		TScriptInstancePtr pScriptInstance = CreateInstance( pScript );
		if ( NULL!=pScriptInstance )
		{
			pScriptInstance->SetOwner( pOwner );
		}

		return pScriptInstance;
	}
	//------------------------------------------------------------------------
	TScriptInstancePtr MonoScript::CreateInstance( TMonoScriptPtr& pScript )
	{
		TScriptInstancePtr pScriptInstance = ScriptInstance::Create();
		n_assert( NULL!=pScriptInstance );

		if ( pScript.isvalid() &&
			pScript->IsValid() )
		{
			pScriptInstance->Init( pScript.get() );
		}

		return pScriptInstance;
	}
	//---------------------------------------------------------------------------
	MonoMethod* MonoScript::GetMethodByName( const Util::String& name ,MonoClass* pMonoClass )
	{
		MonoMethod* pMethod = NULL;

		MonoMethodDesc*	pDesc = mono_method_desc_new( name.AsCharPtr(), false );

		pMethod	=  mono_method_desc_search_in_class( pDesc, pMonoClass );
		mono_method_desc_free(pDesc);

		if ( NULL==pMethod )
		{

			MonoClass* pParnet = mono_class_get_parent( pMonoClass );

			if ( NULL!=pParnet )
			{
				pMethod  = GetMethodByName( name, pParnet );
			}

		}

		return pMethod; 	
	}
	//------------------------------------------------------------------------
	void MonoScript::GetEntryMethods( MonoClass* pMonoClass, MonoClass* pTimlParentClass )
	{
		// - get methods from this class
		SizeT size = sizeof(s_cEntryMethodNameAndIndex)/sizeof(EntryMethodNameAndIndex);
		for ( IndexT idx=0; idx<size; idx++ )
		{
			MonoMethodDesc*	pDesc = NULL;
			MonoMethod*  pMethod = NULL;

			pDesc = mono_method_desc_new( s_cEntryMethodNameAndIndex[idx].__pName, false ); n_assert(pDesc);
			pMethod	=  mono_method_desc_search_in_class( pDesc, pMonoClass ); // - no null ptr assert here , because if it's null ,we will look for it in the parent class
			mono_method_desc_free(pDesc);
			// - save this method with specified index
			// - check if child class already has this method,thus override can be support
			if ( NULL==m_arrEntryMethods[s_cEntryMethodNameAndIndex[idx].__iIdx] )
			{
				m_arrEntryMethods[s_cEntryMethodNameAndIndex[idx].__iIdx] = pMethod;
			}
		}

		// - get methods from parent class if don't reach specified parent class
		MonoClass* pParnet = mono_class_get_parent( pMonoClass );
		if ( NULL!=pParnet &&
			pParnet!=pTimlParentClass ) 
		{
			GetEntryMethods( pParnet, pTimlParentClass );
		}
	}
	//------------------------------------------------------------------------
	void MonoScript::GetMessageHandlerMethods( MonoClass* pMonoClass )
	{
		for ( int ii=0; ii<ScriptMessageCreator::Instance()->GetMessageCount(); ii++ )
		{
			Util::String name = ScriptMessageCreator::Instance()->GetNameByIndex( ii );
			Util::String sig  = ScriptMessageCreator::Instance()->GetSigByName( name );
			
			MonoMethod* pMethod = GetMethodBySignature( sig, pMonoClass );
			if( NULL==pMethod )
			{
				continue;
			}

			m_dicRegistedMessageHandler.Add( name, pMethod );
		}
	}
	//------------------------------------------------------------------------
	MonoMethod* MonoScript::GetMethodBySignature( const Util::String& sig, MonoClass* pMonoClass )
	{
		MonoMethod* pMethod = NULL;

		MonoMethodDesc*	pDesc = mono_method_desc_new( sig.AsCharPtr(), false );
		
		pMethod	=  mono_method_desc_search_in_class( pDesc, pMonoClass );
		mono_method_desc_free(pDesc);

		if ( NULL==pMethod )
		{

			MonoClass* pParnet = mono_class_get_parent( pMonoClass );

			if ( NULL!=pParnet )
			{
				pMethod  = GetMethodBySignature( sig, pParnet );
			}

		}

		return pMethod; 	
	}
	//------------------------------------------------------------------------
	void MonoScript::GetClassFields( MonoClass* pMonoClass )
	{
		gpointer iter = NULL;
		MonoClassField* field = NULL;
		field = mono_class_get_fields( pMonoClass, &iter );
		while ( NULL!=field ) 
		{
			MonoType* monoType  = mono_field_get_type( field );
			int type			= mono_type_get_type( monoType );
			
			int flags = mono_field_get_flags (field);

			if ( (flags&FIELD_ATTRIBUTE_STATIC)||((flags&FIELD_ATTRIBUTE_PUBLIC)==0) )	
			{
				field = mono_class_get_fields( pMonoClass, &iter );
				continue;
			}

			switch ( type )
			{
			case MONO_TYPE_I4:
			case MONO_TYPE_R4:
			case MONO_TYPE_STRING:
				{
					const char* name = Utility_GetFieldName( field );
					Util::String sFiledName( name );
					
					m_mapFileds.Add( sFiledName, field );
				}
				break;
			case MONO_TYPE_VALUETYPE:
				{
					Util::String feildClassName;
					feildClassName = Utility_GetTypeClassName(monoType);
					if( feildClassName == s_csFloat2ClassName ||
						feildClassName == s_csFloat3ClassName ||
						feildClassName == s_csFloat4ClassName ||
						feildClassName == s_csColor32ClassName
						)
					{
						const char* name = Utility_GetFieldName( field );
						Util::String sFiledName( name );
						m_mapFileds.Add( sFiledName, field );
					}
				}
				break;
			case MONO_TYPE_CLASS:
				{
					Util::String feildClassName;
					feildClassName = Utility_GetTypeClassName(monoType);
					if ( feildClassName == s_csAssetPathClassName ||
						feildClassName == s_csImagePathClassName)
					{
						const char* name = Utility_GetFieldName( field);
						Util::String sFiledName(name);
						m_mapFileds.Add( sFiledName, field);
					}
				}
				break;
			default:
				break;
			}	

			field = mono_class_get_fields( pMonoClass, &iter );
		}
	}
}

