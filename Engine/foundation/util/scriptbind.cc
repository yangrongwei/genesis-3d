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
#include "core/debug.h"
#include "util/scriptbind.h"

namespace Util
{
	#ifdef MONO_WEAKREF
	// - ScriptDetail implement --------------------------------------------------------------------------------------------------------------
	ScriptDetail::~ScriptDetail()
	{
		if ( c_iInvalidMonoRefID!=m_iMonoRefID )
		{
			m_iMonoRefID = c_iInvalidMonoRefID;
		}
	}
	
	void ScriptDetail::SetMonoObject( MonoObject* pObj )
	{
		if ( NULL!=pObj )
		{
			if ( m_iMonoRefID!=c_iInvalidMonoRefID )
			{
				mono_gchandle_free(m_iMonoRefID);
				m_iMonoRefID = c_iInvalidMonoRefID;
			}

			// - the second param should be 0, means this handle will not resurrection when invkoing finalisers.
			m_iMonoRefID = mono_gchandle_new_weakref ( pObj, 0 );
		}
		else
		{
			// - must be set before
			script_fatal_error("ScriptDetail::SetMonoObject,Deadly error!this prarm can't be null!\n");
		}
	}	

#else
	// - ScriptDetail implement --------------------------------------------------------------------------------------------------------------
	ScriptDetail::~ScriptDetail()
	{
		if ( c_iInvalidMonoRefID!=m_iMonoRefID )
		{
			n_assert( NULL!=m_pScriptObj );
			if (mono_gchandle_free)
			{
				mono_gchandle_free( m_iMonoRefID );
			}
			m_pScriptObj = NULL;
			m_iMonoRefID = c_iInvalidMonoRefID;
		}
	}

	void ScriptDetail::SetMonoObject( MonoObject* pObj )
	{
		if ( NULL!=pObj )
		{
			// - can't be set before
			n_assert( NULL==m_pScriptObj );
			n_assert( 0==m_iMonoRefID );

			// - tell mono don't delete this object unless free is call
			m_iMonoRefID = mono_gchandle_new ( pObj, 1 );
			m_pScriptObj = pObj;
		}
		else
		{
			// - must be set before
			n_assert( NULL!=m_pScriptObj );
			n_assert( 0!=m_iMonoRefID );

			// - release this obj on the manage world
			mono_gchandle_free( m_iMonoRefID );
			m_pScriptObj = NULL;
			m_iMonoRefID = 0;
		}
	}	
#endif

}