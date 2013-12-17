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
#ifndef __MONO_SCRIPT_MANAGER_H__
#define __MONO_SCRIPT_MANAGER_H__

#include "foundation/util/string.h"
#include "foundation/util/dictionary.h"
#include "foundation/core/refcounted.h"

#include "scriptfeature/inc/script_fwd_decl.h"

namespace App
{
	/*
	 * common index used in script system
	 */
	struct MonoCommonIndex
	{
		MonoCommonIndex()
			: __sClassName()
			, __sNamespace()
			, __sAssemblyName()
		{}

		MonoCommonIndex( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName )
			: __sClassName( sClassName )
			, __sNamespace( sNamespace )
			, __sAssemblyName( sAssemblyName )
		{}

		const Util::String& GetClassName( void )    { return __sClassName; }
		const Util::String& GetNameSpace( void )    { return __sNamespace; }
		const Util::String& GetAssemblyName( void ) { return __sAssemblyName; }

		bool operator<( const MonoCommonIndex& other ) const;
		bool operator>( const MonoCommonIndex& other )const;
		bool operator==( const MonoCommonIndex& other )const;
		bool operator!=( const MonoCommonIndex& other )const 	{ return !( this->operator==( other ) ); }
		const MonoCommonIndex& operator=( const MonoCommonIndex& in ) ;

		// - data
		Util::String	__sClassName ;
		Util::String	__sNamespace ;
		Util::String	__sAssemblyName;
	};

	// - to index mono script
	typedef MonoCommonIndex MonoScriptIndex;
	// - to index mono class
	typedef MonoCommonIndex MonoClassIndex;

	/*
	* define a manager to store all the mono scripts
	*/
	class MonoScriptManager : public Core::RefCounted
	{
		__DeclareSubClass( App::MonoScriptManager, Core::RefCounted );
	public:
		/// constructor
		MonoScriptManager() 
			: m_dicScripts()
		{}
		/// destructor
		virtual ~MonoScriptManager();
		/// add a mono script to the manager
		bool Add( const MonoScriptIndex& key, TMonoScriptPtr pMonoScript );
		/// find a mono script
		TMonoScriptPtr Find( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName );
		TMonoScriptPtr Find( const MonoScriptIndex& key );
		// - clear script dic
		void ClearScriptDic();
	private:
		// - private data
		Util::Dictionary<MonoScriptIndex, TMonoScriptPtr> m_dicScripts;		///< - record all the mono scripts 

	};
	inline void MonoScriptManager::ClearScriptDic()
	{
		m_dicScripts.Clear();
	}
}

#endif // - __MONO_SCRIPT_MANAGER_H__