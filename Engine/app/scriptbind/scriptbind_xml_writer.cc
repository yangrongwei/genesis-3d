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
#include "scriptfeature/inc/script_utility.h"
#include "io/xmlreader.h"
#include "addons/serialization/xmserialize.h"

namespace App
{

	void ICallReg_ScriptRuntime_XmlWriter( void );

	static mono_bool ICall_XmlWriter_Open( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		return (mono_bool)self->Open();
	}

	static void ICall_XmlWriter_Close( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		self->Close();
	}


	static mono_bool ICall_XmlWriter_BeginNode( MonoObject* pMonoObj ,MonoString* pMonoStr)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		Util::String tagName = Utility_MonoStringToCppString( pMonoStr );
		return (mono_bool)self->BeginNode(tagName);
	}
	
	static void ICall_XmlWriter_EndNode( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		self->EndNode();
	}

	static void ICall_XmlWriter_WriteContent(MonoObject* pMonoObj,MonoString* pMonoStr)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		Util::String content = Utility_MonoStringToCppString( pMonoStr );
		self->WriteContent(content);
	}

	static void ICall_XmlWriter_WriteComment(MonoObject* pMonoObj,MonoString* pMonoStr)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		Util::String comment = Utility_MonoStringToCppString( pMonoStr );
		self->WriteComment(comment);
	}

	static void ICall_XmlWriter_SetString(MonoObject* pMonoObj,MonoString* pMonoTag,MonoString* pMonoStr)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		Util::String str = Utility_MonoStringToCppString( pMonoStr );
		Util::String tag = Utility_MonoStringToCppString( pMonoTag );
		self->SetString(tag,str);
	}

	static void ICall_XmlWriter_SetInt(MonoObject* pMonoObj,MonoString* pMonoTag,int index)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		
		Util::String tag = Utility_MonoStringToCppString( pMonoTag );
		self->SetInt(tag,index);
	}

	static void ICall_XmlWriter_SetFloat(MonoObject* pMonoObj,MonoString* pMonoTag,float index)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );

		Util::String tag = Utility_MonoStringToCppString( pMonoTag );
		self->SetFloat(tag,index);
	}

	static void ICall_XmlWriter_SetFloat3(MonoObject* pMonoObj,MonoString* pMonoTag,Math::float3& f3)
	{
		ScriptObjWrapper<IO::XmlWriter> self( pMonoObj );
		Util::String tag = Utility_MonoStringToCppString( pMonoTag );
		Util::String temp;
		temp.SetFloat3( f3 );
		self->SetString( tag, temp );		
	}

	
	void ICallReg_ScriptRuntime_XmlWriter( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_Open",			         (void*)&ICall_XmlWriter_Open },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_Close",			         (void*)&ICall_XmlWriter_Close },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_BeginNode",			     (void*)&ICall_XmlWriter_BeginNode },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_EndNode",			     (void*)&ICall_XmlWriter_EndNode },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_WriteContent",			 (void*)&ICall_XmlWriter_WriteContent },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_WriteComment",			 (void*)&ICall_XmlWriter_WriteComment },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_SetString",			     (void*)&ICall_XmlWriter_SetString },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_SetInt",			     (void*)&ICall_XmlWriter_SetInt },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_SetFloat",			     (void*)&ICall_XmlWriter_SetFloat },
			{ "ScriptRuntime.XmlWriter::ICall_XmlWriter_SetFloat3",			     (void*)&ICall_XmlWriter_SetFloat3 }		
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}