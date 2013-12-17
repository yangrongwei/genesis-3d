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

#include "scriptfeature/mono_script_manager.h"
#include "mono_script.h"

namespace App
{
	// - MonoScriptIndex implement -----------------------------------------------------------------------------
	bool MonoCommonIndex::operator<( const MonoCommonIndex& other ) const
	{
		if ( this->__sClassName<other.__sClassName )
		{
			return true;
		}
		else if ( this->__sClassName>other.__sClassName )
		{
			return false;
		}
		else if ( this->__sNamespace<other.__sNamespace )
		{
			return true;
		}
		else if ( this->__sNamespace>other.__sNamespace )
		{
			return false;
		}
		else
		{
			return this->__sAssemblyName<other.__sAssemblyName;
		}
	}

	bool MonoCommonIndex::operator>( const MonoCommonIndex& other )const
	{
		if ( this->__sClassName>other.__sClassName )
		{
			return true;
		}
		else if ( this->__sClassName<other.__sClassName )
		{
			return false;
		}
		else if ( this->__sNamespace>other.__sNamespace )
		{
			return true;
		}
		else if ( this->__sNamespace<other.__sNamespace )
		{
			return false;
		}
		else
		{
			return this->__sAssemblyName>other.__sAssemblyName;
		}
	}


	bool MonoCommonIndex::operator==( const MonoCommonIndex& other )const
	{
		if ( this->__sClassName==other.__sClassName &&
			this->__sNamespace==other.__sNamespace  && 
			this->__sAssemblyName==other.__sAssemblyName )
		{
			return true;
		}

		return false;
	}

	const MonoCommonIndex& MonoCommonIndex::operator=(const MonoCommonIndex& in)
	{
		__sClassName    = in.__sClassName ;
		__sNamespace    = in.__sNamespace ;
		__sAssemblyName = in.__sAssemblyName;

		return *this ;
	}
	
	// - MonoScriptManager implement --------------------------------------------------------------------------------
	__ImplementClass( App::MonoScriptManager, 'MNSM', Core::RefCounted );

	MonoScriptManager::~MonoScriptManager()
	{
		m_dicScripts.Clear();
	}

	bool MonoScriptManager::Add( const MonoScriptIndex& key, TMonoScriptPtr pMonoScript )
	{
		bool bContain = m_dicScripts.Contains( key );
		if ( bContain )
		{
			return false;
		}

		m_dicScripts.Add( key, pMonoScript );

		return true;
	}

	TMonoScriptPtr MonoScriptManager::Find( const Util::String &sClassName,
										const Util::String &sNamespace,
										const Util::String &sAssemblyName )
	{
		MonoScriptIndex key( sClassName, sNamespace, sAssemblyName );
		return Find( key );
	}

	TMonoScriptPtr MonoScriptManager::Find( const MonoScriptIndex& key )
	{
		IndexT idx = m_dicScripts.FindIndex( key );
		if ( InvalidIndex==idx )
		{
			return TMonoScriptPtr( NULL );
		}

		return m_dicScripts.ValueAtIndex( idx );
	}
}