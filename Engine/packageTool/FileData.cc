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
#include "io/filestream.h"
#include "packageTool/FileData.h"
#include "io/ioserver.h"

namespace Pack
{
	__ImplementClass(FileData, 'FIDA', Core::RefCounted);

FileData::FileData()
	: m_pFileStream(NULL)
{

}

FileData::~FileData()
{
	if (m_pFileStream.isvalid())
	{
		m_pFileStream = NULL;
	}

}

void FileData::Open()
{
	//if (m_pFileStream.isvalid())
	//{
	//	return;
	//}

	//URI uri(m_FilePath);
	//uri.SetScheme("file");
	//
	//
	//m_pFileStream   = IoServer::Instance()->CreateStream(uri);

	//n_assert(m_pFileStream.isvalid());

	//if (!m_pFileStream->Open())
	//{
	//	n_error( "Can not open this file: %s \n", m_FilePath.AsCharPtr() );
	//}
	
	
}

SizeT FileData::GetSize() const
{
	return m_pFileStream->GetSize();
}

void* FileData::GetMemory() const
{
	return m_pFileStream->Map();
}

void FileData::ReleaseMemory() const
{
	m_pFileStream->Unmap();
}

}