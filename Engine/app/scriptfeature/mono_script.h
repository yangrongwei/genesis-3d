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
#ifndef __MONO_SCRIPT_H__
#define __MONO_SCRIPT_H__

#include "foundation/core/refcounted.h"
#include "foundation/util/string.h"
#include "scriptfeature/inc/script_fwd_decl.h"
#include "appframework/app_fwd_decl.h"

namespace App
{
	/*
	* Presents a C# class.Act like a data template
	*/ 
	class MonoScript : public Core::RefCounted
	{
		/// for memory manage
		__DeclareSubClass( App::MonoScript, Core::RefCounted );
	public :	
		/// constructor
		MonoScript();
		/// destructor
		virtual ~MonoScript();

		/// init this class with a script class
		bool Init( MonoClass* pMonoClass, const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName, bool mem );
		/// to see if this mono script has been initialized
		bool IsValid();
		/// get class name
		const Util::String& ClassName();
		/// get namespace
		const Util::String& Namespace();
		/// get assembly name
		const Util::String& AssemblyName();
		/// get mono class
		MonoClass* GetMonoClass();
		/// get entry methods
		TMonoMethodArray* GetEntryMethods( void ); 
		/// get methods
		TMonoMethodMap* GetMethods( void );
		/// get fields
		TMonoClassFieldMap* GetFileds( void );
		/// get message handler 
		ScriptMessageHandlerMap* GetRegistedMessageHandlers(void);

		/// Create mono class instance ( regard as a MonoObject ) from a specified name.
		static TScriptInstancePtr CreateInstance( TMonoScriptPtr& pScript, Actor* pOwner );
		/// Create mono class instance and don't set the owner
		static TScriptInstancePtr CreateInstance( TMonoScriptPtr& pScript );
		/// Get mono method by name
		static MonoMethod* GetMethodByName( const Util::String& sig ,MonoClass* pMonoClass );
	private:
		/// recursively get entry methods,terminate at @pTimlParentClass class
		void GetEntryMethods( MonoClass* pMonoClass, MonoClass* pTimlParentClass );
		void GetMessageHandlerMethods( MonoClass* pMonoClass );
		void GetClassFields( MonoClass* pMonoClass );
		MonoMethod* GetMethodBySignature( const Util::String& sig ,MonoClass* pMonoClass );

		// - private data
		bool				m_bInit;			///< - indicate weather this mono script has been init by a mono class
		Util::String		m_sNamespace ;		///< - namespace of mono class which initialized this class
		Util::String		m_sClassName ;		///< - class name of mono class which initialized this class
		Util::String		m_sAssemblyName;	///< - name of a assembly which contains the mono class
		MonoClass*			m_pMonoClass;		///< - mono class which this class stands for
		TMonoMethodMap	    m_dicMethods;		///< - record all the methods of a mono class
		TMonoMethodArray	m_arrEntryMethods;	///< - record methods which would be call by the C++ side
		TMonoClassFieldMap        m_mapFileds;  ///< - fields of this class
		ScriptMessageHandlerMap   m_dicRegistedMessageHandler;  ///< - recored registered message handler
	};

	// - implement of inline function
	//------------------------------------------------------------------------
	inline bool MonoScript::IsValid() 
	{
		return m_bInit;
	}
	//------------------------------------------------------------------------
	inline const Util::String& MonoScript::ClassName() 
	{
		return m_sClassName;
	}
	//------------------------------------------------------------------------
	inline const Util::String& MonoScript::Namespace()
	{ 
		return m_sNamespace;
	}
	//------------------------------------------------------------------------
	inline const Util::String& MonoScript::AssemblyName()
	{ 
		return m_sAssemblyName;
	}
	//------------------------------------------------------------------------
	inline MonoClass* MonoScript::GetMonoClass()
	{
		return m_pMonoClass;
	}
	//------------------------------------------------------------------------
	inline TMonoMethodArray* MonoScript::GetEntryMethods( void )
	{
		return &m_arrEntryMethods; 
	} 
	//------------------------------------------------------------------------
	inline TMonoMethodMap* MonoScript::GetMethods( void )	
	{ 
		return &m_dicMethods;
	}
	//------------------------------------------------------------------------
	inline TMonoClassFieldMap* MonoScript::GetFileds( void )
	{ 
		return &m_mapFileds;
	}
	//------------------------------------------------------------------------
	inline ScriptMessageHandlerMap* MonoScript::GetRegistedMessageHandlers(void) 
	{ 
		return &m_dicRegistedMessageHandler;
	}

}

#endif // - __MONO_SCRIPT_H__

