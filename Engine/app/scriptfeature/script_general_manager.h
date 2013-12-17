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
#ifndef __SCRIPT_GENERAL_MANAGER_H__
#define __SCRIPT_GENERAL_MANAGER_H__

#include "foundation/util/string.h"
#include "foundation/util/array.h"
#include "foundation/util/dictionary.h"
#include "foundation/core/refcounted.h"
#include "foundation/core/singleton.h"
#include "foundation/core/scopedptr.h"

#include "scriptfeature/inc/script_fwd_decl.h"

namespace App
{
	/*
	*  manager the whole script system
	*/
	class ScriptGeneralManager: public Core::RefCounted
	{
		typedef ScopedPtr<MonoScriptManager> TMonoScriptMngrPtr;
		/// RTTI and memory manager
		__DeclareSubClass( App::ScriptGeneralManager, Core::RefCounted );
		/// this is a singleton class
		__DeclareImageSingleton( App::ScriptGeneralManager );
	public:
		/// destructor
		virtual ~ScriptGeneralManager();
		/// create a mono script
		TMonoScriptPtr GetMonoScript( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName , bool mem = false);
		/// get mono class define from embedding mono by name
		MonoClass* GetMonoClassByName( const Util::String& sClassName, const Util::String& sNamespace, const Util::String& sAssemblyName );
		// - static functions
		/// create singleton 
		static void CreateSingleton( void );
		/// destroy singleton 
		static void DestorySingleton( void );

		/// load base and user define script library
		void LoadAssemblies( bool needDebug );

		/// Check Dll load state
		bool IsDllLoaded( const Util::String& sDllName );
		
	private:
		/// constructor
		ScriptGeneralManager();
		
		// - private data
		Util::Dictionary<Util::String, MonoImage*> m_dicImages;	///< - assembly name and image
		TMonoScriptMngrPtr	m_pMonoScriptManager;				///< - pointer to a mono script manager
	};
}

#endif // - __SCRIPT_GENERAL_MANAGER_H__