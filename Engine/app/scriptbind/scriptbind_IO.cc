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
#include "io/memorystream.h"
#include "io/xmlreader.h"
#include "io/xmlwriter.h"
#include "io/iointerfaceprotocol.h"
#include "io/iointerface.h"
#include "io/textreader.h"
#include "util/string.h"
#include "app/basegamefeature/managers/sceneschedulemanager.h"

namespace App
{

	void ICallReg_ScriptRuntime_IO( void );

	static MonoObject* ICall_IO_GetXmlReader( MonoString* sFilePath )
	{
		GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		n_assert( pStream );

		GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
		n_assert( readStreamMsg );

		Util::String filePath = Utility_MonoStringToCppString( sFilePath );
		readStreamMsg->SetFileName( Util::StringAtom(filePath) );
		readStreamMsg->SetStream( pStream );

		IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

		if ( !readStreamMsg->GetResult() )
		{
			n_error( "BuildingDataSet::BuildingDataSet, can not open %s", filePath.AsCharPtr() );
		}

		// - parser data
		GPtr<IO::XmlReader> reader = IO::XmlReader::Create();
		reader->SetStream( pStream );
		n_assert( NULL!=reader );
		
		return CppObjectToScriptObj( *reader );
	}


	static MonoObject* ICall_IO_GetXmlWriter( MonoString* sFilePath )
	{
		GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		n_assert( pStream );
		Util::String filePath = Utility_MonoStringToCppString( sFilePath );
		pStream->SetURI( filePath );
		GPtr<IO::XmlWriter> mXmlWriter = IO::XmlWriter::Create();
		mXmlWriter->SetStream( pStream );
		bool bOK = mXmlWriter->Open();
		n_assert( bOK );

		// root
		bOK = mXmlWriter->BeginNode( "AppXMLFileTag" );

		// first object is file header
		bOK = mXmlWriter->BeginNode( "AppXMLFileHeaderTag" );
		n_assert(bOK);
		mXmlWriter->SetInt( "AppXMLFileVersionTag", 1 );
		mXmlWriter->EndNode();
		
		return CppObjectToScriptObj( *mXmlWriter );
	}


	static void ICall_IO_CloseWriteFile(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<IO::XmlWriter> pWriter( pMonoObj );
			
		pWriter->EndNode();	//end root
		pWriter->Close();

		const GPtr<IO::Stream> pStream = pWriter->GetStream();
		n_assert( pStream );

		// 发出存储文件的消息
		GPtr<IO::WriteStream> writeStreamMsg = IO::WriteStream::Create();
		n_assert( writeStreamMsg );

		writeStreamMsg->SetURI( pStream->GetURI() );
		writeStreamMsg->SetStream( pStream );

		IO::IoInterface::Instance()->SendWait( writeStreamMsg.upcast<Messaging::Message>() );

		if ( !writeStreamMsg->GetResult() )
		{
			n_assert2(false, "SerializationManager::CloseWriteFile write file error" );
			n_warning("SerializationManager::CloseWriteFile write file error" );
		}
	}

	static void ICall_IO_SaveScene( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		App::SceneScheduleManager* pSceneSchedule = App::SceneScheduleManager::Instance();
		pSceneSchedule->SaveScene( str );
	}

	static MonoArray* ICall_IO_ReadAllLines( MonoString* pMonoString )
	{
		Util::String str = Utility_MonoStringToCppString( pMonoString );
		MonoArray* lines = NULL;
		MonoString* line = NULL;

		//GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		//n_assert( pStream );
		//GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
		//n_assert( readStreamMsg );
		//readStreamMsg->SetURI( str );
		//readStreamMsg->SetStream( pStream );
		//IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

		//if ( !readStreamMsg->GetResult() )
		//{
		//	n_warning( "ScriptGeneralManager::LoadAssemblies: can not open %s", str.AsCharPtr() );
		//}

		GPtr<IO::Stream> stream = IO::IoServer::Instance()->ReadFile( str.AsCharPtr() );
		GPtr<IO::TextReader> textReader = IO::TextReader::Create();
		textReader->SetStream( stream );
		if ( textReader->Open() )
		{
			Util::TStringArray text = textReader->ReadAllLines();
			lines = Utility_CppStrArrToMonoStrArr( text );
		}

		// - release reader
		textReader->Close();
		textReader = NULL;

		return lines;
	}
	

	void ICallReg_ScriptRuntime_IO( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.IO::ICall_IO_GetXmlReader",			 (void*)&ICall_IO_GetXmlReader },
			{ "ScriptRuntime.IO::ICall_IO_GetXmlWriter",			 (void*)&ICall_IO_GetXmlWriter },
			{ "ScriptRuntime.IO::ICall_IO_CloseWriteFile",			 (void*)&ICall_IO_CloseWriteFile },
			{ "ScriptRuntime.IO::ICall_IO_SaveScene",			     (void*)&ICall_IO_SaveScene },
			{ "ScriptRuntime.IO::ICall_IO_ReadAllLines",			 (void*)&ICall_IO_ReadAllLines }
			
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}