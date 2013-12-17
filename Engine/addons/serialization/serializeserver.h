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
#ifndef __serializeserver_H__
#define __serializeserver_H__
#include "serialization/serialize.h"
#include "core/singleton.h"

namespace Serialization
{

enum FileType
{
	// - should not change the assign value if you don't understand what they are used for.
	FT_XML     = 1,
	FT_BXML    = 2,
	FT_BINARY  = 3,
	FT_DEFAULT = 4,
	FT_AUTO	   = 5, //auto idenfiy only used by tools
	FT_NUM,
};
static const  uint  s_ciXmlBinaryTag = 0xFF0000FF;
static const  char* s_ciXmlTag		 = "<?xml";

/*
   M2 version
 1. allow serialization multi files at once.
 2. when writing an file ,the sequences of writing are according to the call of CloseWriteFile
*/

class SerializationServer: public Core::RefCounted
{
	__DeclareClass(SerializationServer);
	__DeclareImageSingleton(SerializationServer);
public:
	static FileType SDefaultType;
	SerializationServer();
	virtual ~SerializationServer();

	static FileType GetDefaultType( void )
	{
		return SDefaultType;
	}

	GPtr<SerializeReader> OpenReadFile( const Util::String& filePath, FileType aft = FT_DEFAULT );
	GPtr<SerializeReader> OpenReadFile( const IO::TStreamPtr& pFileStream, FileType aft = FT_DEFAULT );

	GPtr<SerializeWriter> OpenWriteFile( const Util::String& filePath, FileType aft = FT_DEFAULT );
	GPtr<SerializeWriter> OpenWriteFile( const IO::TStreamPtr& pFileStream, FileType aft = FT_DEFAULT );

	bool CloseReadFile( const GPtr<SerializeReader>& pReader );
	bool CloseWriteFile( const GPtr<SerializeWriter>& pWriter );
private:
	GPtr<SerializeReader> _CreateReaderByFT(FileType aft,const IO::TStreamPtr& pFileStream);


protected:

};

//------------------------------------------------------------------------

//------------------------------------------------------------------------


}
#endif // __serializeserver_H__
