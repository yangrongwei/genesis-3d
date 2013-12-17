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
#include "serialization/serializeserver.h"
#include "io/iointerface.h"
#include "io/memorystream.h"
#include "io/iointerfaceprotocol.h"
#include "serialization/xmserialize.h"
#include "serialization/binaryserialize.h"

namespace Serialization
{
	__ImplementClass(Serialization::SerializationServer, 'GSLM', Core::RefCounted);
	__ImplementImageSingleton(Serialization::SerializationServer);

	FileType SerializationServer::SDefaultType = FT_BINARY;
	//------------------------------------------------------------------------
	SerializationServer::SerializationServer()
	{
		__ConstructImageSingleton;
	}
	//------------------------------------------------------------------------
	SerializationServer::~SerializationServer()
	{
		__DestructImageSingleton;
	}
	//--------------------------------------------------------------------------------
	GPtr<SerializeReader> 
		SerializationServer::OpenReadFile( const IO::TStreamPtr& pFileStream, FileType aft /*= FT_DEFAULT*/ )
	{
		// 根据文件类型创建reader
		GPtr<SerializeReader> pReader(NULL);
		if ( aft == FT_DEFAULT )
		{
			aft = SerializationServer::SDefaultType;
			
		}
		pReader = _CreateReaderByFT(aft,pFileStream);

		if ( pReader )
		{
			pReader->SetStream( pFileStream );
			pReader->BeginFileSerialize();
			pReader->SetOpen(true);
		}

		return pReader;

	}
	//------------------------------------------------------------------------
	GPtr<SerializeReader> 
	SerializationServer::_CreateReaderByFT(FileType aft,const IO::TStreamPtr& pFileStream)
	{
		//n_assert(aft != FT_DEFAULT);
//#ifdef __GENESIS_EDITOR__
#define __AUTO_IDENTIFY__
//#endif

#ifdef __AUTO_IDENTIFY__
		aft = FT_AUTO;
#endif

		GPtr<SerializeReader> pReader(NULL);
		if ( aft == FT_XML )
		{
			pReader = Serialization::SerializeXmlReader::Create();
		}
		else if ( aft == FT_BINARY )
		{
			pReader = Serialization::SerializeBinaryReader::Create();
		}
		else if (aft == FT_AUTO)
		{
			//char* pXml			= const_cast<char*>(s_ciXmlTag);
			uint* pXmlBinary	= const_cast<uint*>(&s_ciXmlBinaryTag);
			if ( pFileStream->IsHeader(pXmlBinary,sizeof(s_ciXmlBinaryTag)) )
			{
				pReader = Serialization::SerializeBinaryReader::Create();
			}
			else
			{
				pReader = Serialization::SerializeXmlReader::Create();
			}

		}
		else if ( aft == FT_BXML )
		{
			n_error(" SerializationServer::OpenReadFile: not support AFT_BXML now ");
		}
		else 
		{
			n_error(" SerializationServer::OpenReadFile: not support this FileType now! ");
		}
		return pReader;
	}
	//------------------------------------------------------------------------
	GPtr<SerializeReader> 
	SerializationServer::OpenReadFile( const Util::String& filePath, FileType aft /*= FT_AUTO*/ )
	{
		// 创建内存流，发出消息，将硬盘数据IO到内存中
		GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		n_assert( pStream );
		GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
		n_assert( readStreamMsg );

		readStreamMsg->SetFileName( filePath );
		readStreamMsg->SetStream( pStream );

		IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

		if ( !readStreamMsg->GetResult() )
		{
			n_warning( "SerializationServer::OpenReadFile: can not open %s!Maybe the size of file is 0.",
						filePath.AsCharPtr() );
			return NULL;
		}

		GPtr<SerializeReader> pReader = OpenReadFile(pStream, aft);
		if ( !pReader )
		{
			n_warning( "SerializationServer::OpenReadFile: can not read %s!Maybe the file format is wrong.",
						filePath.AsCharPtr() );
			return NULL;
		}

		return pReader;
	}
	//------------------------------------------------------------------------
	bool 
	SerializationServer::CloseReadFile( const GPtr<SerializeReader>& pReader )
	{
		if ( !pReader || !pReader->IsOpen() )
			return false;

		pReader->EndFileSerialize();
		pReader->SetOpen(false);
		return true;
	}
	//--------------------------------------------------------------------------------
	GPtr<SerializeWriter> SerializationServer::OpenWriteFile( const IO::TStreamPtr& pFileStream, FileType aft )
	{
		// 根据文件类型创建writer
		GPtr<SerializeWriter> pWriter = NULL;

		if ( aft == FT_DEFAULT )
		{
			aft = SerializationServer::SDefaultType;
		}

		if ( aft == FT_BXML )
		{
			n_error(" SerializationManager::OpenWriteFile: not support AFT_BXML now ");
		}
		else if ( aft == FT_XML )
		{
			pWriter = Serialization::SerializeXmlWriter::Create();
		}
		else if ( aft == FT_BINARY )
		{
			pWriter = Serialization::SerializeBinaryWriter::Create();
		}
		else
		{
			pWriter = Serialization::SerializeXmlWriter::Create();
		}

		if ( pWriter )
		{
			pWriter->SetStream( pFileStream );
			pWriter->BeginFileSerialize();
			pWriter->SetOpen(true);
		}

		return pWriter;
	}
	//------------------------------------------------------------------------
	GPtr<SerializeWriter> 
	SerializationServer::OpenWriteFile( const Util::String& filePath, FileType aft /*= AFT_DEFAULT*/ )
	{
		// 创建内存流
		GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		n_assert( pStream );
		pStream->SetURI( filePath );

		return OpenWriteFile(pStream, aft);

	}
	//------------------------------------------------------------------------
	bool 
	SerializationServer::CloseWriteFile( const GPtr<SerializeWriter>& pWriter )
	{
		if( !pWriter || !pWriter->IsOpen())
			return false;

		pWriter->EndFileSerialize();
		pWriter->SetOpen(false);

		const GPtr<IO::Stream> pStream = pWriter->GetStream();
		if ( !pStream )
		{
			n_warning("SerializationManager::CloseWriteFile Error: Can Not Get Steam" );
			return false;
		}

		// 发出存储文件的消息
		GPtr<IO::WriteStream> writeStreamMsg = IO::WriteStream::Create();
		n_assert( writeStreamMsg );

		writeStreamMsg->SetURI( pStream->GetURI() );
		writeStreamMsg->SetStream( pStream );

		IO::IoInterface::Instance()->SendWait( writeStreamMsg.upcast<Messaging::Message>() );

		if ( !writeStreamMsg->GetResult() )
		{
			n_warning("SerializationManager::CloseWriteFile write file error" );
			return false;
		}
		
		return true;
	}
}
