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
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
namespace App
{
	void ICallReg_ScriptRuntime_Debug( void );

	static void ICall_Debug_Printf( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		n_printf(str.AsCharPtr());
	}

	static void ICall_Debug_Error( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		n_error(str.AsCharPtr());
	}
	
	static void ICall_Debug_Dbgout( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		n_dbgout(str.AsCharPtr());
	}
	
	static void ICall_Debug_Warning( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		n_warning(str.AsCharPtr());
	}

	static void ICall_Debug_Confirm( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		n_confirm(str.AsCharPtr());
	}

	static void ICall_Debug_Assert( mono_bool exp )
	{
		n_assert(exp);
	}
	
	static void ICall_Debug_Barf(  MonoString* exp, MonoString* file,int line )
	{
		Util::String strExp = Utility_MonoStringToCppString( exp );
		Util::String strFile = Utility_MonoStringToCppString( file );
		n_barf( strExp.AsCharPtr(), strFile.AsCharPtr(), line );
	}

	void ICallReg_ScriptRuntime_Debug( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.Debug::ICall_Debug_Printf"			 , (void*)&ICall_Debug_Printf },
			{ "ScriptRuntime.Debug::ICall_Debug_Error"			 , (void*)&ICall_Debug_Error },
			{ "ScriptRuntime.Debug::ICall_Debug_Dbgout"			 , (void*)&ICall_Debug_Dbgout },
			{ "ScriptRuntime.Debug::ICall_Debug_Warning"		 , (void*)&ICall_Debug_Warning },
			{ "ScriptRuntime.Debug::ICall_Debug_Confirm"		 , (void*)&ICall_Debug_Confirm },
			{ "ScriptRuntime.Debug::ICall_Debug_Assert"			 , (void*)&ICall_Debug_Assert },
			{ "ScriptRuntime.Debug::ICall_Debug_Barf"			 , (void*)&ICall_Debug_Barf }
		};


		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}