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
#include "foundation/util/stringconvert.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/mono_icall_registration.h"
#include "scriptfeature/script_general_manager.h"
#include "appframework/app_fwd_decl.h"

#include "app/scriptfeature/script_message_regist.h"
#include "app/scriptfeature/inc/script_message.h"
#include "app/scriptfeature/inc/script_instance.h"
#include "app/scriptfeature/mono_script.h"
#include "util/assetpath.h"

// - for RTTI
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicfeature/components/skinnedmeshrendercomponent.h"
#include "graphicfeature/components/projectorcomponent.h"
#include "graphicfeature/components/skeletoncomponent.h"
#include "graphicfeature/components/spriterendercomponent.h"
#include "graphicfeature/components/animationcomponent.h"
#include "particlefeature/components/particlerendercomponent.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicfeature/components/lightcomponent.h"
#include "scriptfeature/inc/script_component.h"
#include "scriptfeature/editable_field_value.h"
#include "scriptfeature/script_root_instance.h"
#include <stdexcept>

#ifndef __SOUND_COMMIT__
#include "physXfeature/PhysicsBodyComponent.h"
#include "soundfeature/components/SoundSourceComponent.h"
#include "soundfeature/components/SoundEchoFilterComponent.h"
#include "soundfeature/components/SoundLowPassFilterComponent.h"
#include "soundfeature/components/SoundReverbFilterComponent.h"
#endif

#ifdef __WIN32__
#include "WinBase.h" // - for LoadLibrary and GetProcAddress
static HMODULE s_monoDllHandle = NULL;
#elif defined(__ANDROID__)
#include "dlfcn.h" // - for dlopen and dlsym
static void* s_monoSOHandle;
#endif

#define MONO_API_TYPE(ret, fun, params)	typedef ret (*_fp_mono_##fun) params;
#define MONO_API_DECL(ret,fun, params)	_fp_mono_##fun fun = NULL;
#define GET_MONO_API(ret, fun, params)	fun = (_fp_mono_##fun) GetProcAddress(hMonoModule, #fun); if( NULL==fun ) { n_assert(false && "can't find " #fun " in mono dll"); }
#define GET_MONO_API_ANDROID(ret, fun, params)	fun = (_fp_mono_##fun) dlsym(hMonoModule, #fun); if( NULL==fun ) { n_assert(false && "can't find " #fun " in mono so"); }
#define RESET_MONO_API(ret,fun,params)	fun = NULL;

// - make a typedef for each function pointer
#ifndef __OSX__
ALL_MONO_API(MONO_API_TYPE)
ALL_MONO_API(MONO_API_DECL)
#endif

#ifdef __OSX__
#include "RegisterMonoModules.h"
#endif


//------------------------------------------------------------------------------
namespace App
{
	static Util::String g_LastError = "";

	bool StartupSciptSystem( const Util::String& monoDirPaths,
                            const Util::String& monoConfigsPath,
                            const Util::String& monoDllPath,
                            bool bEnableMonoDebugger )
	{
        //setenv(<#const char *#>, <#const char *#>, <#int#>)
#ifdef __OSX__
        RegisterMonoModules();
#endif        
		bool bLoadDll = LoadMonoDll( monoDllPath );
		n_assert( bLoadDll );
		// - set mono dll search path
		mono_set_assemblies_path( monoDirPaths.AsCharPtr() );

        
		if ( bEnableMonoDebugger )
		{
			static const char* options[] =
			{
				//"--soft-breakpoints"  // action in higher version mono
				"--debugger-agent=transport=dt_socket,address=127.0.0.1:52013,server=n",
			};
			mono_jit_parse_options( sizeof(options)/sizeof(char*), (char**)options );
			mono_debug_init( 1 ); // 1 stands for MONO_DEBUG_FORMAT_MONO, for more detail see the mono source code mono-debug.g
            
			n_dbgout( "Script system is in debug state!" );
		}
		// - init mono
		MonoDomain* pDomain = mono_jit_init_version ( "MainMonoDomain", "v2.0.50727" );
		script_fatal_error( NULL!=pDomain );

		if ( bEnableMonoDebugger )
		{
			// - The mono soft debugger needs this
			mono_thread_set_main( mono_thread_current() );
		}

		// - register internal call functions
		RegisterInternalCalls();

		// - init message generator
		ScriptMessageCreator::CreateSingleton();
        
		// - register all messages
		Reg_ScriptRuntime_Message();
		// - init script general manager
		ScriptGeneralManager::CreateSingleton();
		
		// - create a child domain,and run in this child domain
#ifndef __OSX__
        MonoDomain* domain = Utility_CreateChildDomain();
		script_fatal_error( NULL!=domain );
		Utility_SetChildDomain( domain );
#endif
        
		// - load runtime library
		ScriptGeneralManager::Instance()->LoadAssemblies( bEnableMonoDebugger );
        
		// - setup script global instance
		ScriptRootInstance::CreateSingleton();
		ScriptRootInstance::Instance()->Init();
		return true;
	}
	//------------------------------------------------------------------------
	bool ShutDownScriptSystem()
	{
		// - execute script root exit method
		ScriptRootInstance::Instance()->OnExit();
        
		// - release singletons
		ScriptMessageCreator::DestorySingleton();
		ScriptGeneralManager::DestorySingleton();
		ScriptRootInstance::DestorySingleton();
		
		// - unload child domain first
		Utility_UnloadChildDomain();
		// - make sure that there's only a root domain now
		n_assert(mono_domain_get()==mono_get_root_domain());
		mono_jit_cleanup( mono_domain_get() );
		// - unload mono dll
		UnloadMonoDll();

#if defined(__WIN32__)  && (!defined(__GENESIS_EDITOR__))// hack __WIN32__版退出崩溃的问题。// && defined(_DEBUG)
		HMODULE module_handle = GetModuleHandleW(L"mscoree.dll");
		if (module_handle)
		{
			while(::FreeLibrary (module_handle));
		}
#endif
		return true;
	}
	//------------------------------------------------------------------------
	Util::String GetLastError()
	{
		return g_LastError;
	}
	//------------------------------------------------------------------------
	bool LoadMonoDll( const Util::String& monoDllPath )
	{
#ifdef __WIN32__
		// - dynamic load mono dll
		char16_t path[512] = {0};
		Util::StringConvert::UTF8ToWide(monoDllPath.AsCharPtr(), path, 512);
		HMODULE hMonoModule = LoadLibraryW( (wchar_t*)path );
		if (!hMonoModule)
		{
			g_LastError = monoDllPath + " not found!";
			throw(0);
		}

		n_printf("\n mono dll path: %s\n",monoDllPath.AsCharPtr());
		n_assert( NULL!=hMonoModule );
		
		// - save this handle
		s_monoDllHandle = hMonoModule;
        
		// - assign value to the function pointer which we define before

        ALL_MONO_API(GET_MONO_API)
        
#elif defined(__ANDROID__)
        // - dynamic load mono dll
        const char* loadInfo = NULL;
       
        void* hMonoModule = dlopen( (char*)monoDllPath.AsCharPtr() ,RTLD_LAZY);
        n_printf("\n monodllpath: %s\n",monoDllPath.AsCharPtr());
        loadInfo = dlerror();
        if(NULL != loadInfo)
            n_printf("\n load_error: %s\n",loadInfo);
        else
            n_printf("\n load_successful\n");
        
        n_printf("\n monodllpath: %s\n",monoDllPath.AsCharPtr());
        n_assert( NULL!=hMonoModule );
        
        // - save this handle
        s_monoSOHandle = hMonoModule;
        
        // - assign value to the function pointer which we define before
        ALL_MONO_API(GET_MONO_API_ANDROID)
#endif
		return true;
	}
	//------------------------------------------------------------------------
	void UnloadMonoDll()
	{
#ifndef __OSX__
        ALL_MONO_API(RESET_MONO_API)
#endif
        
#ifdef __WIN32__
		if( s_monoDllHandle )
		{
			::FreeLibrary( s_monoDllHandle );
			s_monoDllHandle = NULL;
		}
#elif defined(__ANDROID__)
		if(s_monoSOHandle){
			dlclose(s_monoSOHandle);
			s_monoSOHandle = NULL;
		}
#endif
	}
	//------------------------------------------------------------------------
	void Utility_RegularPath( Util::String& inout )
	{
		int len = inout.Length();
		int dis = 'a' - 'A' ;
		for( int i=0; i<len; i++ )
		{
			char ch = inout[i];
			if( ch=='\\' )
			{
				inout[i] ='/';
			}
            
			if ( ch>='A' &&
				ch<='Z' )
			{
				inout[i] = ch + dis;
			}
		}
	}
	//------------------------------------------------------------------------
	Util::String Utility_ExtractExtension( const Util::String& sPath )
	{
		int p = sPath.BackwardFindChar(  '.' );
        
		if ( InvalidIndex==p )
		{
			return Util::String( "No Extension" );
		}
		else if ( p<sPath.Length()-1 )
		{
			return sPath.ExtractToEnd( p+1 );
		}
		else //( p==sPath.Size )
		{
			return Util::String( "No Extension" );
		}
	}
	//------------------------------------------------------------------------
	void Utility_ChangeExtension( Util::String& sPath, const Util::String& newEx )
	{
		int p = sPath.BackwardFindChar(  '.' );
		if ( InvalidIndex==p )
		{
			sPath.Append( "." + newEx );
		}
		else if ( p<sPath.Length()-1 )
		{
			sPath.TerminateAtIndex( p );
			sPath.Append( "." + newEx );
		}
		else //( p==sPath.Size )
		{
			sPath.Append( newEx );
		}
	}
	//------------------------------------------------------------------------
	void Utility_RemoveNameSpace( Util::String& inout )
	{
		IndexT idx = inout.BackwardFindChar( ':' );
		if ( idx>=1 &&
			':'==inout[idx-1] && // - make sure there is "::"
			idx+1!=inout.Length() ) // - make sure it is not the last one
		{
			inout.SetCharPtr( &inout[idx+1] );
		}
	}
	//------------------------------------------------------------------------
	MonoClass* Utility_GetMonoClassByName( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName )
	{
		return App::ScriptGeneralManager::Instance()->GetMonoClassByName( sClassName, sNamespace, sAssemblyName );
	}
	//------------------------------------------------------------------------
	MonoClass* Utility_GetRuntimeMonoClass( const Util::String& sClassName )
	{
		Util::String sTempClassName = sClassName;
		Utility_RemoveNameSpace( sTempClassName );
		return Utility_GetMonoClassByName( sTempClassName, s_csScriptRuntimeNamespace, s_csScriptRuntimeLibraryName );
	}
	//------------------------------------------------------------------------
	MonoString* Utility_NewMonoString( const Util::String& string )
	{
		MonoString* monoStr = mono_string_new_wrapper( string.AsCharPtr() );
		n_assert( NULL!=monoStr );
        
		return monoStr;
	}
	//------------------------------------------------------------------------
	MonoObject* Utility_GetDummyObject( void )
	{
		static MonoObject* pDummyObj = NULL;
		if ( NULL==pDummyObj )
		{
			MonoClass* pMonoClass = Utility_GetRuntimeMonoClass( "DummyClass__" );
			n_assert( NULL!=pMonoClass );
            
			MonoDomain* pMonoDomain = mono_domain_get();
			pDummyObj  = mono_object_new( pMonoDomain, pMonoClass ) ;
			n_assert( NULL!=pDummyObj );
            
			mono_runtime_object_init( pDummyObj );
		}
        
		return pDummyObj;
	}
	//------------------------------------------------------------------------
	MonoObject* Utility_CreateMonoObj( MonoClass* pMonoClass )
	{
		n_assert( NULL!=pMonoClass );
        
		MonoObject* pMonoObj = NULL;
		MonoDomain* pMonoDomain = mono_domain_get();
		pMonoObj  = mono_object_new( pMonoDomain, pMonoClass ) ;
        
		n_assert( NULL!=pMonoObj );
		MonoMethodDesc* pDesc = mono_method_desc_new( ":.ctor(DummyClass__)", c_iMonoBool_False );
		MonoMethod *pConstructor = NULL;
		pConstructor = mono_method_desc_search_in_class( pDesc, pMonoClass );
		n_assert( NULL!=pConstructor && "No specify constructor!" );
		mono_method_desc_free(pDesc);
        
		MonoObject* pDummyObj = Utility_GetDummyObject();
		void* params[1] ;
		params[0] = &pDummyObj;
		if ( mono_class_is_valuetype(pMonoClass) )
		{
			MonoObject* pUnboxObj = pMonoObj;
			pUnboxObj = (MonoObject*)mono_object_unbox ( pUnboxObj );
            
			Utility_MonoRuntimeInvoke ( pConstructor, pUnboxObj, params );
		}
		else
		{
			Utility_MonoRuntimeInvoke ( pConstructor, pMonoObj, params );
		}
        
		return pMonoObj;
	}
	//------------------------------------------------------------------------
	// 尽量改用 void Utility_MonoStringToCppString( MonoString* pMonoStr, Util::String& buffer)
	// 特别是字符对象很长的时候，以减少 Util::String 临时对象的拷贝复制。
	Util::String Utility_MonoStringToCppString( MonoString* pMonoStr )
	{
		char* pStr = mono_string_to_utf8( pMonoStr );
		Util::String cppString( pStr );
		mono_free( pStr );
        
		return cppString;
	}
	//------------------------------------------------------------------------
	/// convert a string to a MonoString
	MonoString* Utility_CppStringToMonoString( const char* pStr )
	{
		MonoString* monoString = mono_string_new_wrapper( pStr );
		n_assert( NULL!=monoString );
		return monoString;
	}

	MonoString* Utility_CppStringToMonoStringSafe( const char* pStr )
	{
		MonoString* mono= Utility_CppStringToMonoString( pStr );
		if (mono != NULL)
		{
			return mono;
		}
		else
		{
			mono = Utility_CppStringToMonoString("");
			return mono;
		}
	}
	//------------------------------------------------------------------------
	Util::Guid Utility_MonoGuidToUtilGuid(MonoArray* guid_array)
	{
		n_assert(mono_array_length(guid_array) == sizeof(Util::Guid));
		unsigned char* ptr = GetMonoArrayBegin<unsigned char>(guid_array);
		return Util::Guid::FromBinary(ptr, sizeof(Util::Guid));
	}
	//------------------------------------------------------------------------
	MonoArray* Utility_UtilGuidToMonoByteArray(const Util::Guid& guid )
	{
		Util::Array<ubyte> byteArr;
		const ubyte* buffer;
		guid.AsBinary(buffer);
		int length = sizeof(Util::Guid);
        
		for (int ii=0;ii<length;ii++)
		{
			byteArr.Append(buffer[ii]);
		}
		return Utility_CppByteArrToMonoByteArr(byteArr);
	}
	//------------------------------------------------------------------------
	const Core::Rtti* Utility_GetComRttiByName( const Util::String& sName )
	{
		// - SunHao TODO:string compare is a bit expense,do we have better way to do this? 2012/04/23
		if ( sName=="Render" ||
			sName=="RenderComponent" )
		{
			return &( RenderComponent::RTTI );
		}
		else if ( sName=="MeshRender" ||
                 sName=="MeshRenderComponent" )
		{
			return &( MeshRenderComponent::RTTI );
		}
		else if ( sName=="SkinnedMeshRender" ||
                 sName=="SkinnedMeshRenderComponent" )
		{
			return &( SkinnedMeshRenderComponent::RTTI );
		}
		else if ( sName=="ProjectorRender" ||
			sName=="ProjectorRenderComponent")
		{
			return &( ProjectorRenderComponent::RTTI);
		}
		else if ( sName=="Skeleton" ||
                 sName=="SkeletonComponent" )
		{
			return &( SkeletonComponent::RTTI );
		}
		else if ( sName=="ParticleRender" ||
                 sName=="ParticleRenderComponent" )
		{
			return &( ParticleRenderComponent::RTTI );
		}
		else if ( sName=="SpriteRender" ||
			sName=="SpriteRenderComponent" )
		{
			return &( SpriteRenderComponent::RTTI );
		}
		else if ( sName=="Animation" ||
                 sName=="AnimationComponent" )
		{
			return &( AnimationComponent::RTTI );
		}
		else if ( sName=="Light" ||
                 sName=="LightComponent" )
		{
			return &( LightComponent::RTTI );
		}
		else if ( sName=="Script" ||
                 sName=="ScriptComponent")
		{
			return &( ScriptComponent::RTTI );
		}
		else if ( sName=="Camera" ||
                 sName=="CameraComponent")
		{
			return &( CameraComponent::RTTI );
		}
#ifndef __SOUND_COMMIT__
		else if ( sName=="SoundSource" ||
                 sName=="SoundSourceComponent")
		{
			return &( SoundSource::RTTI );
		}
		else if ( sName=="SoundEchoFilter" ||
                 sName=="SoundEchoFilterComponent")
		{
			return &( SoundEchoFilterComponent::RTTI );
		}
		else if ( sName=="SoundReverbFilter" ||
                 sName=="SoundReverbFilterComponent")
		{
			return &( SoundReverbFilterComponent::RTTI );
		}
		else if ( sName=="SoundLowPassFilter" ||
                 sName=="SoundLowPassFilterComponent")
		{
			return &( SoundLowPassFilterComponent::RTTI );
		}
#endif
#ifndef __PHYSX_COMMIT__
		else if ( sName=="PhysicsBody" ||
                 sName=="PhysicsBodyComponent")
		{
			return &( PhysicsBodyComponent::RTTI );
		}
#endif
		else
		{
			n_printf( "Error component type happen! Passing error component's name when getting component." );
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	Component* AddComponentByName( Actor* pActor, const Util::String& sName )
	{
		// - find the component's RTTI
		const Core::Rtti* pRtti  = Utility_GetComRttiByName( sName );
		if ( NULL==pRtti )
		{
			return NULL;
		}
        
		// - to see if this component is already exist
		const TComponentPtr& pCurrCom = pActor->FindComponentExactly( *pRtti );
		if ( NULL!=pCurrCom )
		{
			return pCurrCom.get();
		}
        
		Core::RefCounted* pObj = Core::Factory::Instance()->Create( pRtti->GetFourCC() );
		n_assert( NULL!=pObj );
		GPtr<Component> pCom = static_cast<Component*>( pObj );
        
		pActor->AttachComponent( pCom );
		return pCom.get();
	}
	//------------------------------------------------------------------------
	Component* GetComponentByName( Actor* pActor, const Util::String& sName )
	{
		const Core::Rtti* pRtti  = Utility_GetComRttiByName( sName );
		if ( NULL==pRtti )
		{
			return NULL;
		}
        
		GPtr<Component> pCom = pActor->FindComponentExactly( *pRtti );
		if ( NULL==pCom )
		{
			return NULL;
		}
        
		return pCom.get();
	}
	//------------------------------------------------------------------------
	MonoArray* Utility_CppStrArrToMonoStrArr( const Util::TStringArray& cppStrArr )
	{
		if ( cppStrArr.IsEmpty() )
		{
			return NULL;
		}
        
		MonoArray* pMonoArr		= NULL;
		MonoString* pMonoString = NULL;
		MonoClass* pMonoClass   = mono_get_string_class();
		MonoDomain* pDomain		= mono_domain_get();
		size_t size				= cppStrArr.Size();
        
		// - create a byte array
		pMonoArr = mono_array_new( pDomain, pMonoClass, size );
		if ( NULL==pMonoArr )
		{
			return NULL;
		}
        
		// - convert string into mono string and add them to a mono string array
		for ( uint32 ii=0; ii<size; ii++ )
		{
			pMonoString = Utility_NewMonoString ( cppStrArr[ii] );
			mono_array_set ( pMonoArr, MonoString*, ii, pMonoString );
		}
        
		return pMonoArr;
	}
	//-----------------------------------------------------------------------
	MonoArray* Utility_CppByteArrToMonoByteArr( const Util::Array<ubyte>& cppByteArr )
	{
		if ( cppByteArr.IsEmpty() )
		{
			return NULL;
		}
        
		MonoArray* pMonoArr		= NULL;
		MonoClass* pMonoClass   = mono_get_byte_class();
		MonoDomain* pDomain		= mono_domain_get();
		size_t size				= cppByteArr.Size();
        
		// - create a ubyte array
		pMonoArr = mono_array_new( pDomain, pMonoClass, size );
		if ( NULL==pMonoArr )
		{
			return NULL;
		}
		// - convert string into mono string and add them to a mono byte array
		for ( uint32 ii=0; ii<size; ii++ )
		{
			mono_array_set ( pMonoArr, ubyte, ii, cppByteArr[ii] );
		}
        
		return pMonoArr;
	}
	//------------------------------------------------------------------------
	bool Utility_MonoStrArrToCppStrArr( MonoArray* pMonoStrArr, Util::TStringArray& cppStrArr )
	{
		if ( NULL==pMonoStrArr )
		{
			return false;
		}
        
		MonoString* pStr	= NULL;
		size_t size			= mono_array_length( pMonoStrArr );
        
		for ( uint32 ii=0; ii<size; ii++ )
		{
			pStr = mono_array_get( pMonoStrArr, MonoString*, ii );
			Util::String str = Utility_MonoStringToCppString( pStr );
			cppStrArr.Append( str );
		}
        
		return true;
	}
	//------------------------------------------------------------------------
	Util::String Utility_GetFieldStringValue( MonoObject* pMonoObj, MonoClassField* pClassField )
	{
		if ( NULL==pClassField ||
			NULL==pMonoObj )
		{
			static Util::String s_sEmpty;
			return s_sEmpty;
		}
        
		MonoString *strval = NULL;
		mono_field_get_value( pMonoObj, pClassField, &strval );
        
		return Utility_MonoStringToCppString( strval );
	}
	//------------------------------------------------------------------------
	Util::TStringArray Utility_GetAllEditableFieldNames( TScriptInstancePtr& pInstance )
	{
		TMonoClassFieldMap* pFields   = Utility_GetFields( pInstance ); 
		n_assert( NULL!=pFields );
		int size					  = pFields->Size();
        
		Util::TStringArray arr( size, 0 );
		for ( int ii=0; ii<size; ii++ )
		{
			arr.Append( pFields->KeyAtIndex(ii) );
		}
        
		return arr;
	}
	//------------------------------------------------------------------------
	int Utility_GetEditableFieldCount( TScriptInstancePtr& pInstance )
	{
		TMonoClassFieldMap* pFields = Utility_GetFields( pInstance ); 
		n_assert( NULL!=pFields );
		return pFields->Size();
	}
	//------------------------------------------------------------------------
	MonoClassField* Utility_GetEditableField( TScriptInstancePtr& pInstance, const Util::String& sName )
	{
		if ( (NULL==pInstance) ||
			!(pInstance.isvalid()) )
		{
			return NULL;
		}
        
		TMonoClassFieldMap* pFields = Utility_GetFields( pInstance );
		IndexT idx					= pFields->FindIndex( sName );
		if ( InvalidIndex==idx )
		{
			return NULL;
		}
        
		return pFields->ValueAtIndex( idx );
	}
	//------------------------------------------------------------------------
	MonoClassField* Utility_GetEditableField( TScriptInstancePtr& pInstance, IndexT iIdx )
	{
		if ( (NULL==pInstance) ||
			!(pInstance.isvalid()) )
		{
			return NULL;
		}
        
		TMonoClassFieldMap* pFields = Utility_GetFields( pInstance );
		if ( iIdx<0 ||
			(iIdx>pFields->Size()) )
		{
			return NULL;
		}
        
		return pFields->ValueAtIndex( iIdx );
	}
	//------------------------------------------------------------------------
	TMonoClassFieldMap* Utility_GetFields( TScriptInstancePtr& pInstance )
	{
		MonoScript* pMonoScript		  = pInstance->GetMonoScript(); 
		n_assert( NULL!=pMonoScript );
		TMonoClassFieldMap* pFields   = pMonoScript->GetFileds();   
		n_assert( NULL!=pFields );
        
		return pFields;
	}
	//------------------------------------------------------------------------
	int Utility_GetFieldType( MonoClassField* pClassField )
	{
		// - if null pointer, return a invalid type
		if ( NULL==pClassField )
		{
			n_assert( false && "Utility_GetFieldType, null pointer!" );
			return c_iInvalidMonoType;
		}
        
		MonoType* pFieldMonoType = mono_field_get_type( pClassField );
		int iFieldType			 = mono_type_get_type( pFieldMonoType );
		
		return iFieldType;
	}
	//------------------------------------------------------------------------
	bool Utility_SetFieldValue( TScriptInstancePtr& pInstance, const Util::String& sName, int iType, void* val )
	{
		if ( (NULL==val) ||
			(NULL==pInstance) ||
			!(pInstance.isvalid()) )
		{
			return false;
		}
        
		MonoObject* pMonoInstance   = pInstance->GetMonoInstance();
        
		// - check if it's a valid field
		MonoClassField* pClassField = Utility_GetEditableField( pInstance, sName );
		if ( NULL==pClassField )
		{
			return false;
		}
        
		// - check if the type is match
		int iFieldType = Utility_GetFieldType( pClassField );
		if ( iFieldType!=iType )
		{
			return false;
		}
        
		mono_field_set_value( pMonoInstance, pClassField, val );
		
		return true;
	}
	//------------------------------------------------------------------------    
	bool Utility_SetImagePathFieldValue( TScriptInstancePtr& pInstance, const Util::String& key, const Util::String& str, int iType)
	{
		MonoString* value = Utility_CppStringToMonoString(str.AsCharPtr());

		if ( (NULL == value) || (NULL==pInstance) || !(pInstance.isvalid()) )
			return false;
		
		MonoObject* pMonoObj = pInstance->GetMonoInstance();
		MonoClassField* pClassField = Utility_GetEditableField( pInstance, key);
		if ( NULL == pClassField )
			return false;

		// - check if the type is match, for the reason that user may change their script when editor offline
		int iFieldType = Utility_GetFieldType( pClassField );
		if ( iFieldType != iType )
			return false;
		
		MonoObject* pMemMonoObj = Utility_GetFieldBuiltInTypeValue<MonoObject*>( pMonoObj, pClassField );
		if ( pMemMonoObj == NULL )
			return false;
		
		MonoScript* pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( "ImagePath", "ScriptRuntime", "ScriptRuntimeLibrary.dll", true);
		TMonoClassFieldMap* maps = pMonoScript->GetFileds();
		for ( int i = 0; i < maps->Size(); ++i)
		{
			MonoClassField* pMemClassField =  maps->ValueAtIndex(i);
			mono_field_set_value( pMemMonoObj, pMemClassField, value);
		}
		return true;
	}
	//------------------------------------------------------------------------
	Util::String Utility_GetFieldImagePathValue( MonoObject* pMonoObj, MonoClassField* pField )
	{
		MonoObject* pMemMonoObj = Utility_GetFieldBuiltInTypeValue<MonoObject*>( pMonoObj, pField);
		if ( pMemMonoObj == NULL || pField == NULL )
			return "";

		MonoScript* pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( "ImagePath", "ScriptRuntime", "ScriptRuntimeLibrary.dll", true);
		TMonoClassFieldMap* maps = pMonoScript->GetFileds();
		Util::String value;
		for ( int i = 0; i < maps->Size(); ++i)
		{
			MonoClassField* pMemClassField =  maps->ValueAtIndex(i);
			value = Utility_GetFieldStringValue( pMemMonoObj, pMemClassField);
		}
		return value;
	}
	//------------------------------------------------------------------------
	bool Utility_SetAssetPathFieldValue( TScriptInstancePtr& pInstance, const Util::String& key, const Util::AssetPath& assetPath, int iType )
	{
		MonoString* valueStr = Utility_CppStringToMonoString(assetPath.path.AsCharPtr());
		int32			type = assetPath.type;

		if ( (NULL==pInstance) || !(pInstance.isvalid()) )
			return false;

		MonoObject* pMonoObj = pInstance->GetMonoInstance();
		MonoClassField* pClassField = Utility_GetEditableField( pInstance, key);
		if ( NULL == pClassField )
			return false;

		// - check if the type is match, for the reason that user may change their script when editor offline
		int iFieldType = Utility_GetFieldType( pClassField );
		if ( iFieldType != iType )
			return false;

		MonoObject* pMemMonoObj = Utility_GetFieldBuiltInTypeValue<MonoObject*>( pMonoObj, pClassField );
		if ( pMemMonoObj == NULL )
			return false;

		MonoScript* pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( "AssetPath", "ScriptRuntime", "ScriptRuntimeLibrary.dll", true);
		TMonoClassFieldMap* maps = pMonoScript->GetFileds();
		for ( int i = 0; i < maps->Size(); ++i)
		{
			MonoClassField* pMemClassField =  maps->ValueAtIndex(i);
			int memType = Utility_GetFieldType( pMemClassField);
			if ( memType == (int)MONO_TYPE_STRING )
				mono_field_set_value( pMemMonoObj, pMemClassField, valueStr);
			else if( memType == (int)MONO_TYPE_I4 )
				mono_field_set_value( pMemMonoObj, pMemClassField, &type);
		}

		return true;
	}
	//------------------------------------------------------------------------
	Util::AssetPath Utility_GetFieldAssetPathValue( MonoObject* pMonoObj, MonoClassField* pField )
	{
		Util::AssetPath assetPath;
		MonoObject* pMemMonoObj = Utility_GetFieldBuiltInTypeValue<MonoObject*>( pMonoObj, pField);
		if ( pMemMonoObj == NULL || pField == NULL )
			return assetPath;

		MonoScript* pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( "AssetPath", "ScriptRuntime", "ScriptRuntimeLibrary.dll", true);
		TMonoClassFieldMap* maps = pMonoScript->GetFileds();
		Util::String value;
		for ( int i = 0; i < maps->Size(); ++i)
		{
			MonoClassField* pMemClassField =  maps->ValueAtIndex(i);
			int memType = Utility_GetFieldType( pMemClassField);
			if ( memType == (int)MONO_TYPE_STRING )
			{
				Util::String str = Utility_GetFieldStringValue( pMemMonoObj, pMemClassField);
				assetPath.path = str;
			}
			else if( memType == (int)MONO_TYPE_I4 )
			{
				int32 type = Utility_GetFieldBuiltInTypeValue<int32>( pMemMonoObj, pMemClassField);
				assetPath.type = type;
			}
		}
		return assetPath;
	}
	//------------------------------------------------------------------------
	bool Utility_SetFieldValue( GPtr<ScriptComponent>& com , int index, const Util::String& sName, int iType, void* val )
	{
		GPtr<App::ScriptInstance> pScriptInstance = com->GetScriptInstance( index );
		EditableFeilValue& feildValue = com->GetEditableFeildValue();
        
		// string type need special pricess;
		if ( iType==MONO_TYPE_STRING )
		{
			MonoString* monostring = Utility_CppStringToMonoString( static_cast<Util::String*>(val)->AsCharPtr() );
			if ( !App::Utility_SetFieldValue( pScriptInstance, sName, iType, monostring ) )
			{
				return false;
			}
			feildValue.SetString(index,sName,*static_cast<Util::String*>(val));
			return true;
		}
        
		//other types;
		switch(iType)
		{
            case MONO_TYPE_I4:
			{
				App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
				feildValue.SetInt( index, sName, *static_cast<int*>(val) );
				break;
			}
            case MONO_TYPE_R4:
			{
				App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
				feildValue.SetFloat( index, sName, *static_cast<float*>(val) );
				break;
			}
            case MONO_TYPE_VALUETYPE:
			{
				MonoClassField* pClassField = Utility_GetEditableField( pScriptInstance, sName );
				Util::String className = Utility_GetTypeClassName( pClassField );
				if( className==s_csFloat2ClassName )
				{
					App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
					feildValue.SetFloat2( index, sName, *static_cast<Math::float2*>(val) );
				}
				else if( className==s_csFloat3ClassName )
				{
					App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
					feildValue.SetFloat3( index, sName, *static_cast<Math::float3*>(val) );
				}
				else if ( className==s_csFloat4ClassName )
				{
					App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
					feildValue.SetFloat4( index, sName, *static_cast<Math::float4*>(val));
				}
				else if( className == s_csColor32ClassName )
				{
					App::Utility_SetFieldValue( pScriptInstance, sName, iType, val);
					feildValue.SetColor32( index, sName, *static_cast<Math::Color32*>(val));
				}
				break;
			}
			case MONO_TYPE_CLASS:
			{
				MonoClassField* pClassField = Utility_GetEditableField( pScriptInstance, sName );
				Util::String className = Utility_GetTypeClassName( pClassField );
				if( className == s_csImagePathClassName )
				{
					Util::String* str = static_cast<Util::String*>(val);
					App::Utility_SetImagePathFieldValue( pScriptInstance, sName, *str, iType);
					feildValue.SetImagePath( index, sName, *str);
				}
				else if ( className == s_csAssetPathClassName )
				{
					Util::AssetPath* assetPath = static_cast<Util::AssetPath*>(val);
					App::Utility_SetAssetPathFieldValue( pScriptInstance, sName, *assetPath, iType);
					feildValue.SetAssetPath( index, sName, *assetPath);
				}
				break;
			}
			return true;
		} // switch(iType) end
		return false;
	}
	//------------------------------------------------------------------------    
	bool Utility_SetFieldValue( GPtr<ScriptComponent>& com , const Util::String& sInstanceName, const Util::String& sName, int iType, void* val)
	{
		int idx =  com->GetClassNames().FindIndex( sInstanceName );
		return Utility_SetFieldValue( com, idx, sName, iType, val );
	}
	//------------------------------------------------------------------------
	MonoDomain* Utility_CreateChildDomain()
	{
		MonoDomain* newDomain = mono_domain_create_appdomain("Genesis Child Domain", NULL); 
		n_assert( newDomain!=NULL );
		MonoDomain* old_domain = mono_domain_get(); 
		n_assert( old_domain!=NULL );
		MonoDomain* rootDomaain = mono_get_root_domain(); 
		n_assert( rootDomaain!=NULL );
		if(rootDomaain != old_domain)
		{
			n_error("already have a child domain\n");
		}
		return newDomain;
		
	}
	void Utility_SetChildDomain(MonoDomain* newDomain)
	{
		if (newDomain)
		{
			if (!mono_domain_set (newDomain, false))
			{
				n_error("Utility_SetChildDomain: mono_domain_set failed\n");
				return;
			}

			if(mono_domain_get() == mono_get_root_domain())
			{
				n_error("Utility_SetChildDomain: root domain\n");
			}

			return;
		}

		n_error("Utility_SetChildDomain: newDomain is null\n");
	}
	//----------------------------------------------------------------------
	const char* Utility_GetTypeClassName(MonoType *type)
	{
		MonoClass* pClass =  mono_type_get_class(type);
        
		return mono_class_get_name(pClass);
	}
    
	//-----------------------------------------------------------------------
	const char* Utility_GetTypeClassName(MonoClassField *pClassField)
	{
		MonoType* pFieldMonoType = mono_field_get_type( pClassField );
        
		return Utility_GetTypeClassName(pFieldMonoType);
	}
	
	void Utility_UnloadChildDomain()
	{
		MonoDomain* domain = mono_domain_get();
		if (domain)
		{
			MonoDomain* rootDomain = mono_get_root_domain();
			if (domain != rootDomain)
			{
				//-we can't unload the domain that is running now,so we set the root domain as active domain
				mono_domain_set(rootDomain, false);
				mono_domain_unload(domain);
			}
		}
		mono_gc_collect(mono_gc_max_generation());
	}
    
	//--------------------------------------------------------------------------
	void Utility_ScriptRootLoad()
	{
		ScriptRootInstance::Instance()->OnLoad();
	}
	//--------------------------------------------------------------------------
	void Utility_ScriptRootTick()
	{
		ScriptRootInstance::Instance()->OnTick();
	}
	//--------------------------------------------------------------------------
	void Utility_ScriptRootStop()
	{
		if(ScriptRootInstance::HasInstance())
		{
			ScriptRootInstance::Instance()->OnStopped();
		}
	}
	//--------------------------------------------------------------------------
	void Utility_ScriptRootResume()
	{
		if(ScriptRootInstance::HasInstance())
		{
			ScriptRootInstance::Instance()->OnResumed();
		}
	}
	//--------------------------------------------------------------------------
    
	Util::String Utility_ExceptionToString( MonoObject* ecx )
	{
		MonoMethodDesc*	pDesc = NULL;
		MonoMethod*  pMethod = NULL;
		MonoClass*   pExcClass = NULL;
        
		ScriptGeneralManager* manager = ScriptGeneralManager::Instance(); 
		n_assert(manager);
		MonoString* monoStringMessage = NULL;
        
		pExcClass = manager->GetMonoClassByName( s_csExceptionConverterName, s_csScriptRuntimeNamespace, s_cpScriptRuntimeLibraryName );
		n_assert(pExcClass);
        
		pDesc = mono_method_desc_new( s_csExceptionToStringMethodSig.AsCharPtr(), false );
		n_assert(pDesc);
		pMethod = mono_method_desc_search_in_class( pDesc, pExcClass ); 
		n_assert(pMethod);
		mono_method_desc_free(pDesc);
        
		void* args[] = { ecx, &monoStringMessage };
        
		MonoObject* tempException = NULL;
		mono_runtime_invoke( pMethod, NULL, args, &tempException );
		if( tempException )
		{
			const char* exceptionClassName = mono_class_get_name(mono_object_get_class( tempException ) );
            
			Util::String errorString;
			errorString.Append("This exception string can't output because there is another exception of class '");
			errorString.Append( exceptionClassName );
			errorString.Append("' is thrown in the process\n");
			
			n_error( errorString.AsCharPtr() );
			return NULL;
		}
		return Utility_MonoStringToCppString(monoStringMessage);
	}
	//--------------------------------------------------------------------------
    
	MonoObject* Utility_MonoRuntimeInvoke( MonoMethod* method, void* obj, void** params )
	{
		MonoObject* exc = NULL;
		MonoObject* ret = NULL;
		ret = mono_runtime_invoke( method, obj, params , &exc );
		if ( exc!=NULL )
		{
			Util::String error = Utility_ExceptionToString( exc );
			n_warning( error.AsCharPtr() );
		}
		return ret;
	}
	//--------------------------------------------------------------------------
    
	GPtr<ScriptInstance> Utility_CreateScriptInstance( const Util::String& className,const Util::String& nameSpaceName,const Util::String& assemblyName )
	{

		TMonoScriptPtr pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( className,nameSpaceName,assemblyName );
        
		if ( !(pMonoScript.isvalid()) ||
			!(pMonoScript->IsValid()) )
		{
#ifdef __GENESIS_EDITOR__
			return NULL; 
#endif
			script_fatal_error( false && "Utility_CreateScriptInstance,Can't find monoScript!" );
		}
        
		TScriptInstancePtr _pScriptInstance;
		_pScriptInstance = MonoScript::CreateInstance( pMonoScript );
		return _pScriptInstance;
	}
	//--------------------------------------------------------------------------
    
#ifdef __GENESIS_EDITOR__
	bool Utility_DetectDotNetDll(const char* pathName )
	{
		if( mono_image_open_from_data_full==NULL )
		{
			return false;
		}
		// - load the assemblies to memory 
		GPtr<IO::Stream> srcStream = IO::IoServer::Instance()->ReadFileFromDisk( pathName ); 
		srcStream->SetAccessMode( IO::Stream::ReadAccess ); 
        
		void* dllData = NULL;
		int	  dataSize = 0;
        
		if ( !srcStream->Open() )
		{
			n_warning("dll open failed,it may be locked by other process,or not existed\n");
			return false;
		}
		dllData = srcStream->Map(); 
		n_assert( dllData!=NULL );
		dataSize = srcStream->GetSize();
        
		int status = 0;
		MonoImage* pImage = NULL;
		pImage = mono_image_open_from_data_full ( dllData, dataSize, true, &status, false); 
		// - if this is not a dot net's dll,mono_image_open_from_data_full() function will return a null value
        
		if (pImage == NULL)
		{
			return false;
		}
		else
		{
			// release the dll
			mono_image_close(pImage);
			return true;
		}
		srcStream->Close();
	}
#endif
}

