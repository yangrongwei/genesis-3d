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

#ifndef __SCRIPT_BIND_H__
#define __SCRIPT_BIND_H__



#include "util/monotypes.h"
#include "core/types.h"
#include "util/monoapi.h"

// - macros 

// - fatal error macro
#define script_fatal_error(exp) { if (!(exp)) n_barf(#exp,__FILE__,__LINE__); }

// - bind
#define __ScriptBind \
public:\
	void SetMonoObject( MonoObject* pObj )  { this->m_ScriptDetail.SetMonoObject( pObj );  }\
	MonoObject* GetMonoObject( void )       { return this->m_ScriptDetail.GetMonoObject(); }\
	bool IsBindMonoObject( void )			{ return this->m_ScriptDetail.IsBindMonoObject(); }\
private:\
	Util::ScriptDetail m_ScriptDetail;\

#define MONO_WEAKREF

namespace Util
{
#ifdef MONO_WEAKREF
		/*
	* just make a smart pointer of script object
	*/
	class ScriptDetail
	{
	public:
		/// constructor
		ScriptDetail()
			: m_iMonoRefID( c_iInvalidMonoRefID )
			//, m_pScriptObj( NULL )
		{}
		/// destructor
		~ScriptDetail();
		/// set m_pScriptObj
		void SetMonoObject( MonoObject* pObj );
		/// Get m_pScriptObj
		MonoObject* GetMonoObject( void );
		/// to see if this cpp object is binding a mono object
		bool IsBindMonoObject( void );
	private:
		// - do not allow copy
		ScriptDetail( const ScriptDetail& );
		ScriptDetail& operator=( const ScriptDetail& );
		// - private data 
	 	uint32 m_iMonoRefID;
	};

	// - inline function implement ---
	//------------------------------------------------------------------------
	inline MonoObject* ScriptDetail::GetMonoObject( void ) 
	{
		return mono_gchandle_get_target(m_iMonoRefID);
	}
	inline bool ScriptDetail::IsBindMonoObject( void ) 
	{
		return (NULL!=mono_gchandle_get_target(m_iMonoRefID)); 
	}
#else
		/*
	* just make a smart pointer of script object
	*/
	class ScriptDetail
	{
	public:
		/// constructor
		ScriptDetail()
			: m_iMonoRefID( c_iInvalidMonoRefID )
			, m_pScriptObj( NULL )
		{}
		/// destructor
		~ScriptDetail();
		/// set m_pScriptObj
		void SetMonoObject( MonoObject* pObj );
		/// Get m_pScriptObj
		MonoObject* GetMonoObject( void );
		/// to see if this cpp object is binding a mono object
		bool IsBindMonoObject( void );
	private:
		// - do not allow copy
		ScriptDetail( const ScriptDetail& );
		ScriptDetail& operator=( const ScriptDetail& );
		// - private data 
		uint32 m_iMonoRefID;
		MonoObject* m_pScriptObj;
	};

	// - inline function implement ---
	//------------------------------------------------------------------------
	inline MonoObject* ScriptDetail::GetMonoObject( void ) 
	{
		return m_pScriptObj;
	}
	//------------------------------------------------------------------------
	inline bool ScriptDetail::IsBindMonoObject( void ) 
	{
		return (NULL!=m_pScriptObj); 
	}
#endif


}

#endif // - __SCRIPT_BIND_H__