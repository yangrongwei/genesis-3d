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

	void ICallReg_ScriptRuntime_XmlReader( void );

	static mono_bool ICall_XmlReader_Open( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		return (mono_bool)self->Open();
	}
    
	static MonoString* ICall_XmlReader_GetCurrentNodeName( MonoObject* pMonoObj )
	{
       ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
	   Util::String nodeName = self->GetCurrentNodeName( );
	   MonoString* mono= Utility_CppStringToMonoString(nodeName.AsCharPtr());
	   return mono;
    }

	static void ICall_XmlReader_SetToFirstChild( MonoObject* pMonoObj, MonoString* firstChild )
	{
       ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
	   Util::String firstChildName = Utility_MonoStringToCppString( firstChild );
	   self->SetToFirstChild( firstChildName );
    }

	static MonoString* ICall_XmlReader_GetString( MonoObject* pMonoObj, MonoString* tag )
	{
          ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		  Util::String tagName = Utility_MonoStringToCppString( tag );
		  const char* value =  self->GetString_forward( tagName.AsCharPtr() );
		  MonoString* mono= Utility_CppStringToMonoString( value );
		  return mono;
	}

	static int ICall_XmlReader_GetInt( MonoObject* pMonoObj, MonoString* tag )
	{
		ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		Util::String tagName = Utility_MonoStringToCppString( tag );
		const char* value =  self->GetString_forward( tagName.AsCharPtr() );
		Util::String sValue = value;
		return sValue.AsInt();
	}

	static mono_bool ICall_XmlReader_SetToNextChild( MonoObject* pMonoObj, MonoString* tag )
	{
          ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		  Util::String tagName = Utility_MonoStringToCppString( tag );
		  return (mono_bool)self->SetToNextChild( tagName );
	}

	static float ICall_XmlReader_GetFloat( MonoObject* pMonoObj, MonoString* tag )
	{
		ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		Util::String tagName = Utility_MonoStringToCppString( tag );
		const char* value =  self->GetString_forward( tagName.AsCharPtr() );
		Util::String sValue = value;
		return sValue.AsFloat();
	}

	static void ICall_XmlReader_GetFloat3( MonoObject* pMonoObj, MonoString* tag ,Math::float3& f3)
	{
		ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		Util::String tagName = Utility_MonoStringToCppString( tag );
		Util::String temp = self->GetString_forward( tagName.AsCharPtr() );
		n_assert( temp.IsValidFloat3() );
		f3 = temp.AsFloat3();

	}

	static void ICall_XmlReader_SetToNode( MonoObject* pMonoObj,MonoString* pMonoStr )
	{
		ScriptObjWrapper<IO::XmlReader> self( pMonoObj );
		Util::String path = Utility_MonoStringToCppString( pMonoStr );
		self->SetToNode(path);
	}

	static void ICall_XmlReader_BeginAttribute( MonoObject* pMonoObj )
	{
	
	}

	static void ICall_XmlReader_EndAttribute( MonoObject* pMonoObj )
	{
		
	}

	void ICallReg_ScriptRuntime_XmlReader( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_Open",			         (void*)&ICall_XmlReader_Open },
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_GetCurrentNodeName",     (void*)&ICall_XmlReader_GetCurrentNodeName},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_SetToFirstChild",        (void*)&ICall_XmlReader_SetToFirstChild},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_GetString",              (void*)&ICall_XmlReader_GetString },
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_GetInt",                 (void*)&ICall_XmlReader_GetInt},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_SetToNextChild",         (void*)&ICall_XmlReader_SetToNextChild},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_GetFloat",               (void*)&ICall_XmlReader_GetFloat},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_GetFloat3",              (void*)&ICall_XmlReader_GetFloat3},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_SetToNode",              (void*)&ICall_XmlReader_SetToNode},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_BeginAttribute",         (void*)&ICall_XmlReader_BeginAttribute},
			{ "ScriptRuntime.XmlReader::ICall_XmlReader_EndAttribute",           (void*)&ICall_XmlReader_EndAttribute}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}