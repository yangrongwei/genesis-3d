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
#ifndef __SCRIPT_UTILITY_H__
#define __SCRIPT_UTILITY_H__

#include "foundation/io/stream.h"
#include "foundation/io/ioserver.h"
#include "foundation/io/memorystream.h"
#include "foundation/io/iointerface.h"
#include "foundation/io/iointerfaceprotocol.h"

#include "foundation/util/string.h"
#include "foundation/util/guid.h"
#include "foundation/util/monoapi.h"
#include "foundation/core/rtti.h"
#include "app/scriptfeature/inc/script_fwd_decl.h"
#include "app/appframework/component.h"

// - define some mono function by macro
#define mono_array_addr(array,type,index) ((type*)(void*) mono_array_addr_with_size (array, sizeof (type), index))
#define mono_array_get(array,type,index) ( *(type*)mono_array_addr ((array), type, (index)) ) 
#define mono_array_set(array,type,index,value)	\
	do {	\
	type *__p = (type *) mono_array_addr ((array), type, (index));	\
	*__p = (value);	\
	} while (false)




namespace App
{

	class Actor;
	class ScriptComponent;
	
	// Mono Object has private data offset when get C# object. See Mono Source Code
	enum {
		MonoObjectMemoryOffset = 2 * sizeof(void*),
		MonoArrayMemoryOffset = 4 * sizeof(void*) 
	};

	struct bbox_script
	{
		Math::float3 Min;
		Math::float3 Max;
		inline void operator = (const Math::bbox& rhs)
		{
			Min.x() = rhs.pmin.x();
			Min.y() = rhs.pmin.y();
			Min.z() = rhs.pmin.z();

			Max.x() = rhs.pmax.x();
			Max.y() = rhs.pmax.y();
			Max.z() = rhs.pmax.z();
		}
		inline Math::bbox toBbox() const
		{
			return Math::bbox(Math::point(Min.x(), Min.y(), Min.z()), Math::point(Max.x(), Max.y(), Max.z()));
		}
	};


	// - name define
	static char* s_cpScriptFrameworkLibrary					  = "ScriptFrameworkLibrary.dll";
	static char* s_cpScriptRuntimeLibraryName				  = "ScriptRuntimeLibrary.dll";
	static char* s_cpScriptGUILibraryName					  = "ScriptGUILibrary.dll";			//[2012/5/15 zhongdaohuan]
	static char* s_cpUserDefCSharpLibName					  = "UserDefCSharp.dll";

	static const Util::String s_csScriptableClassName		  = "ScriptableClass";
	static const Util::String s_csScriptRuntimeNamespace	  = "ScriptRuntime";

	static const Util::String s_csScriptFrameworkLibraryName  = s_cpScriptFrameworkLibrary;
	static const Util::String s_csScriptRuntimeLibraryName    = s_cpScriptRuntimeLibraryName;
	static const Util::String s_csScriptGUILibraryName		  = s_cpScriptGUILibraryName;			//[2012/5/15 zhongdaohuan]
	static const Util::String s_csUserDefCSharpLibName		  = s_cpUserDefCSharpLibName;
	static const Util::String s_csScriptBinaryAssign		  = "script:";

	#ifdef __WIN32__
	static const Util::String s_csMonoDllAssign				  = "script:mono-2.0.dll";
	
	#elif defined(__ANDROID__)
	static const Util::String s_csMonoDllAssign				  = "";

    #elif defined(__OSX__)
    static const Util::String s_csMonoDllAssign               = "script:mono-2.0.dll";  
	#endif

	static const Util::String s_csFloat2ClassName		      = "Vector2";
	static const Util::String s_csFloat3ClassName		      = "Vector3";
	static const Util::String s_csFloat4ClassName		      = "Vector4";		
	static const Util::String s_csColorFClassName		      = "ColorF";		
	static const Util::String s_csColor32ClassName		      = "Color32";		
	static const Util::String s_csImagePathClassName		  = "ImagePath";		
	static const Util::String s_csAssetPathClassName		  = "AssetPath";		

	static const Util::String s_csExceptionConverterName      = "ExceptionConverter";
	static const Util::String s_csExceptionToStringMethodSig = "*:ExceptionToString(Exception,string&)";

	// - assemblies define 
	struct AssemblyNameAndPath
	{
		char* __pAssign;
		char* __pName;
	};

	static const AssemblyNameAndPath s_cAssemblies[] = {
		{ "script:",  s_cpScriptFrameworkLibrary },
        { "script:",  s_cpScriptRuntimeLibraryName },
		{ "script:",  s_cpScriptGUILibraryName },		
		{ "script:",  s_cpUserDefCSharpLibName },
	};

	/// - entry method names and index define
	enum EEntryMethodIndex
	{
		EEntryMethodIndex_OnLoad,
		EEntryMethodIndex_OnBeginFrame,
		EEntryMethodIndex_OnFrame,
		EEntryMethodIndex_OnEndFrame,
		EEntryMethodIndex_OnExit,
		EEntryMethodIndex_OnStopped,
		EEntryMethodIndex_OnResumed,
		EEntryMethodIndex_OnRenderPostEffect,
		EEntryMethodIndex_OnWillRenderObject,
		EEntryMethodIndex_Num,
	};

	struct EntryMethodNameAndIndex
	{
		char* __pName;
		uint8 __iIdx;
	};

	/// structure in front of a C# object
	struct DataOnHead
	{
		void*       __CppObjPtr;
	};

	struct InternalCallDetail
	{
		char* __pScriptFunName;
		void* __pCppFunPtr;
	};

	//函数的参数列表里不允许有任何空格存在，要不然，mono会找不到这个函数。
	static const EntryMethodNameAndIndex s_cEntryMethodNameAndIndex[] = {
		{ "*:OnLoad()", EEntryMethodIndex_OnLoad },
		{ "*:OnBeginFrame()", EEntryMethodIndex_OnBeginFrame },
		{ "*:OnFrame()", EEntryMethodIndex_OnFrame },
		{ "*:OnEndFrame()", EEntryMethodIndex_OnEndFrame },
		{ "*:OnExit()", EEntryMethodIndex_OnExit },
		{ "*:OnStopped()", EEntryMethodIndex_OnStopped },
		{ "*:OnResumed()", EEntryMethodIndex_OnResumed },
		{ "*:OnRenderPostEffect(CameraComponent,RenderToTexture,RenderToTexture)", EEntryMethodIndex_OnRenderPostEffect },
		{ "*:OnWillRenderObject(RenderComponent)", EEntryMethodIndex_OnWillRenderObject },
	};

	/// let the script system work
	bool StartupSciptSystem( const Util::String& monoDirPaths, 
							const Util::String& monoConfigsPath, 
							const Util::String& monoDllPath, 
							bool bEnableMonoDebugger );

	/// close script system
	bool ShutDownScriptSystem();

	/// load mono dll
	bool LoadMonoDll( const Util::String& monoDllPath );

	/// unload mono dll
	void UnloadMonoDll();

	Util::String GetLastError();

	/// replace '\' to '/',upper case to lower case
	void Utility_RegularPath( Util::String& inout);

	/// get file extension from a path
	Util::String Utility_ExtractExtension( const Util::String& sPath );

	/// change extension
	void Utility_ChangeExtension( Util::String& sPath, const Util::String& newEx );

	/// remove namespace
	void Utility_RemoveNameSpace( Util::String& inout );

	/// get class definition on the mono side 
	MonoClass* Utility_GetMonoClassByName( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName );

	/// get runtime mono class
	MonoClass* Utility_GetRuntimeMonoClass( const Util::String& sClassName );

	/// create a mono string
	MonoString* Utility_NewMonoString( const Util::String& string );

	/// create a dummy object to initialize a class
	MonoObject* Utility_GetDummyObject( void );

	/// create a monoObject from given mono class
	MonoObject* Utility_CreateMonoObj( MonoClass* pMonoClass );

	/// convert a MonoString to Cpp string
	Util::String Utility_MonoStringToCppString( MonoString* pMonoStr );

	/// convert a MonoString to Cpp string
	template<typename StringType>
	void Utility_MonoStringToCppString( MonoString* pMonoStr, StringType& buffer);

	/// convert a string to a MonoString
	MonoString* Utility_CppStringToMonoString( const char* pStr );

	MonoString* Utility_CppStringToMonoStringSafe( const char* pStr );

	/// get component's RTTI by name
	const Core::Rtti* Utility_GetComRttiByName( const Util::String& sName );

	/// add component by name 
	Component* AddComponentByName( Actor* pActor, const Util::String& sName );

	/// get component by name
	Component* GetComponentByName( Actor* pActor, const Util::String& sName );

	/// create a mono string array from a cpp string array
	MonoArray* Utility_CppStrArrToMonoStrArr( const Util::TStringArray& cppStrArr );

	MonoArray* Utility_CppByteArrToMonoByteArr( const Util::Array<ubyte>& cppStrArr );

	template<typename T>
	MonoArray* Utility_CppArrToMonoArr( const Util::Array<T>& cppStrArr );

	template<typename T>
	T* Utility_CreateCppArrFromMonoArr( MonoArray* monoarray );

	template<typename T>
	void Utility_FreeCppArr( T* cpparray );

	/// create a cpp string array from mono string array
	bool Utility_MonoStrArrToCppStrArr( MonoArray* pMonoStrArr, Util::TStringArray& cppStrArr );

	/// get a string from a class instance by given a field
	Util::String Utility_GetFieldStringValue( MonoObject* pMonoObj, MonoClassField* pClassField );

	Util::Guid Utility_MonoGuidToUtilGuid(MonoArray* guid_array);

	MonoArray* Utility_UtilGuidToMonoByteArray(const Util::Guid& guid);

	/// get all fields name from a script instance,it's slow
	Util::TStringArray Utility_GetAllEditableFieldNames( TScriptInstancePtr& pInstance );

	/// get editable field count
	int Utility_GetEditableFieldCount( TScriptInstancePtr& pInstance );

	/// get field by name
	MonoClassField* Utility_GetEditableField( TScriptInstancePtr& pInstance, const Util::String& sName );

	/// get field by index
	MonoClassField* Utility_GetEditableField( TScriptInstancePtr& pInstance, IndexT iIdx );

	/// get all fields of a script instance 
	TMonoClassFieldMap* Utility_GetFields( TScriptInstancePtr& pInstance );

	/// get field type, if null pointer is given,a invalid mono type(c_iInvalidMonoType) is return
	int Utility_GetFieldType( MonoClassField* pClassField );

	/// set a script instance's field value
	bool Utility_SetFieldValue( TScriptInstancePtr& pInstance, const Util::String& sName, int iType, void* val );

	/// set a imagepath instance's field value
	bool Utility_SetImagePathFieldValue( TScriptInstancePtr& pInstance, const Util::String& key, const Util::String& str, int iType);

	/// get a imagepath instance's field value
	Util::String Utility_GetFieldImagePathValue(MonoObject* pMonoObj, MonoClassField* pField);

	/// set a imagepath instance's field value
	bool Utility_SetAssetPathFieldValue( TScriptInstancePtr& pInstance, const Util::String& key, const Util::AssetPath& str, int iType);

	/// get a imagepath instance's field value
	Util::AssetPath Utility_GetFieldAssetPathValue(MonoObject* pMonoObj, MonoClassField* pField);


	/// set a script instance's field value
	bool Utility_SetFieldValue( GPtr<ScriptComponent>& com , int index, const Util::String& sName, int iType, void* val );

	/// set a script instance's field value
	bool Utility_SetFieldValue( GPtr<ScriptComponent>& com , const Util::String& sInstanceName, const Util::String& sName, int iType, void* val );

	/// get type's class name
	const char* Utility_GetTypeClassName(MonoType *type);

	/// get a feild's class name
	const char* Utility_GetTypeClassName(MonoClassField *type);

	/// create a child domain
	MonoDomain* Utility_CreateChildDomain();

	///  set it as current domain
	void Utility_SetChildDomain(MonoDomain* newDomain);

	/// unload a child domain ,never unload the root domain
	void Utility_UnloadChildDomain();

	/// call script root's load foo
	void Utility_ScriptRootLoad();

	/// call script root's Tick foo
	void Utility_ScriptRootTick();

	/// call script root's Stop foo
	void Utility_ScriptRootStop();

	/// call script root's Resume foo
	void Utility_ScriptRootResume();

	Math::float3 Utility_VectorToFloat3(const Math::vector& vec);

	Math::vector Utility_Float3ToVector(const Math::float3& f3);

	/// exception to string
	Util::String Utility_ExceptionToString(MonoObject* ecx);

	/// call mono method with exeception process
	MonoObject* Utility_MonoRuntimeInvoke(MonoMethod* method, void* obj, void** params);

	/// Create a script instance
	GPtr<ScriptInstance> Utility_CreateScriptInstance(const Util::String& className,const Util::String& nameSpaceName,const Util::String& assemblyName);

#ifdef __GENESIS_EDITOR__
	/// To check if this dll is a dot net's dll
	bool Utility_DetectDotNetDll(const char* pathName);
#endif
	
	// -- inline function define -------

	// translate from bool to MoonBool
	inline mono_bool Utility_MonoBool(bool b)
	{
		return b ? c_iMonoBool_True : c_iMonoBool_False;
	}

	// translate from MonoBool to bool
	inline bool Utility_MonoBool(mono_bool b)
	{
		return b == c_iMonoBool_True;
	}

	/// extract a stucture from a MonoObject
	inline DataOnHead* GetDataOnHead(MonoObject* wrapper)
	{
		return reinterpret_cast<DataOnHead*> (((char*)wrapper) + MonoObjectMemoryOffset);
	}

	//主要用于值类型的MonoObject解包。
	template<typename T>
	inline T& MonoObjectUnbox(MonoObject* obj)
	{
		return *((T*)(((char*) obj) + MonoObjectMemoryOffset));
	}

	template<typename T>
	inline T* GetMonoArrayBegin(MonoArray* array)
	{
		return (T*) (((char*) array) + MonoArrayMemoryOffset);
	}

	template<typename T>
	inline const T* GetMonoArrayBegin(const MonoArray* array)
	{
		return (T*) (((char*) array) + MonoArrayMemoryOffset);
	}

	template<typename T>
	inline T& GetMonoArrayElement (MonoArray* array, int i)
	{
		return *(GetMonoArrayBegin<T>(array) + i);
	}

	template<typename T>
	inline void SetMonoArrayElement (MonoArray* array, int i, const T& value)
	{
		T& elem = GetMonoArrayElement<T>(array,i);
		elem = value;
	}

	/// bind a cpp object with a script object
	inline void Utility_SetCppObjectPtr(MonoObject* wrapper, void* pCppObj )
	{
		GetDataOnHead(wrapper)->__CppObjPtr = pCppObj;
	}

	/// get cpp object pointer from a script object
	inline void* Utility_GetCppObjectPtr( MonoObject* wrapper )
	{
		return GetDataOnHead(wrapper)->__CppObjPtr;
	}

	/// if a script instance has editable fields
	inline bool Utility_HasEdiableFields( TScriptInstancePtr& pInstance )
	{
		int count = Utility_GetEditableFieldCount( pInstance );
		return count>0;
	}

	/// get field name 
	inline const char* Utility_GetFieldName( MonoClassField* pField )
	{
		if ( NULL!=pField )
		{
			return mono_field_get_name( pField );
		}

		return NULL;
	}

	inline Math::float3 Utility_VectorToFloat3(const Math::vector& vec)
	{
		return Math::float3(vec.x(), vec.y(), vec.z());
	}

	inline Math::vector Utility_Float3ToVector(const Math::float3& f3)
	{
		return Math::vector(f3.x(), f3.y(), f3.z());
	}

	//------------------------------------------------------------------------
	template<typename StringType>
	void Utility_MonoStringToCppString( MonoString* pMonoStr, StringType& buffer)
	{
		char* pStr = mono_string_to_utf8( pMonoStr );
		buffer = pStr;
		mono_free( pStr );
	}

	// -- template function define -------
	/// bind a mono object with a cpp object
	template<typename T>
	bool BindCppObjWithMonoObj( T* pCppObj, MonoObject* pMonoObj )
	{
		script_fatal_error( NULL!=pCppObj );
		script_fatal_error( NULL!=pMonoObj );

		// - this cpp obj must havn't bind before
		bool bBind = pCppObj->IsBindMonoObject();
		script_fatal_error( !bBind );

		// - bind this two object
		Utility_SetCppObjectPtr( pMonoObj, pCppObj );
		pCppObj->SetMonoObject( pMonoObj );

		// - add ref to this cpp object
		pCppObj->AddRef();
		
		return true;
	}

	/// bind a mono object with a cpp object
	template<typename T>
	bool ReleaseCppObjWithMonoObj( T* pCppObj, MonoObject* pMonoObj )
	{
		script_fatal_error( NULL!=pCppObj );
		script_fatal_error( NULL!=pMonoObj );

		// - unbind this two object
		Utility_SetCppObjectPtr( pMonoObj, NULL );

		// - release one ref of this cpp object,this foo is called in a mono's certain thread,
		// - it may be called at any time after the GC.
		pCppObj->Release();

		return true;
	}

	/// create a mono object from a cpp object
	template<typename T>
	MonoObject* CppObjectToScriptObj( T& rCppObj )
	{
		const Core::Rtti* pRtti = rCppObj.GetRtti(); 
		n_assert( NULL != pRtti );
		MonoObject* pMonoObj = rCppObj.GetMonoObject();
		if ( NULL == pMonoObj )
		{
			// - create a script object
			MonoClass* pMonoClass = NULL;

			while(NULL != pRtti)
			{
				pMonoClass = Utility_GetRuntimeMonoClass( pRtti->GetName() );
				if (pMonoClass)
				{
					pMonoObj = Utility_CreateMonoObj( pMonoClass );
					// - bind this two object
					BindCppObjWithMonoObj( &rCppObj, pMonoObj );	
					break;
				}
				pRtti = pRtti->GetParent();
			}
		}
		return pMonoObj;
	}

	/// create a mono object from a cpp pointer
	template<typename T>
	MonoObject* CppPointerToScriptObj( T* pCppObj )
	{
		if( NULL==pCppObj )
		{
			return NULL;
		}
		else
		{
			return CppObjectToScriptObj( *pCppObj );
		}
	}

	template<typename T>
	MonoArray* Utility_CppArrToMonoArr( const Util::Array<T>& cppArr )
	{
		if (cppArr.Size()==0)
		{
			return NULL;
		}
		MonoArray* pMonoArr		= NULL; 
		MonoClass* pMonoClass   = mono_object_get_class(CppObjectToScriptObj( *cppArr[0] ));
		MonoDomain* pDomain		= mono_domain_get();
		size_t size				= cppArr.Size();

		// - create a ubyte array
		pMonoArr = mono_array_new( pDomain, pMonoClass, size );
		if ( NULL==pMonoArr )
		{
			return NULL;
		}
		// - convert string into mono string and add them to a mono byte array
		for ( uint32 ii=0; ii<size; ii++ )
		{
			mono_array_set ( pMonoArr, MonoObject*, ii, CppObjectToScriptObj( *cppArr[ii] ) );
		}

		return pMonoArr;
	}

	/// - get a instance's field build in type value,for example:int float double etc
	template<typename T> 
	inline T Utility_GetFieldBuiltInTypeValue( MonoObject* pMonoObj, MonoClassField* pField )
	{
#ifdef _DEBUG
		n_assert( NULL!=pMonoObj );
		n_assert( NULL!=pField );
#endif
		T* value = reinterpret_cast<T*> ( reinterpret_cast<char*> (pMonoObj) + mono_field_get_offset(pField) );
		return *value;
	}

	/*
	* wrapper a mono object and associate with its cpp object,act like a pointer 
	*/
	template<typename T>
	class ScriptObjWrapper
	{
	public:
		ScriptObjWrapper( MonoObject* pMonoObj )
			: m_pMonoObj( pMonoObj )
			, m_pCppObj( NULL )
		{
			void* pObj = Utility_GetCppObjectPtr( pMonoObj );
			m_pCppObj  = static_cast<T*>( pObj );
			n_assert( NULL!=m_pCppObj );
		}

		T* GetCppObjPtr( void ) { return m_pCppObj; }
		T& operator * () const	{ return *m_pCppObj; }
		T* operator -> () const	{ return m_pCppObj;	}
		bool IsValid( void ) const	{ return m_pMonoObj!=NULL;}

		static T* Convert( MonoObject* pMonoObj )
		{
			if (NULL == pMonoObj)
			{
				return NULL;
			}
			return static_cast<T*>( Utility_GetCppObjectPtr( pMonoObj ) );
		}
	private:
		MonoObject* m_pMonoObj;
		T* m_pCppObj;
	};



}

template<typename T>
T* App::Utility_CreateCppArrFromMonoArr( MonoArray* monoarray )
{
	if ( NULL==monoarray )
	{
		return false;
	}

	size_t size			= mono_array_length( monoarray );
	T* cppArray = n_new_array(T,size);
	for ( uint32 ii=0; ii<size; ii++ )
	{
		cppArray[ii] = mono_array_get( monoarray, T, ii );
	}
}


template<typename T>
void App::Utility_FreeCppArr( T* cpparray )
{
	n_delete_array(cpparray);
}

#endif // - __SCRIPT_UTILITY_H__

