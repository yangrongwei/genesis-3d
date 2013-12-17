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
#include "Package.h"
#include "FileData.h"
#include "FileFormat.h"
#include "io/filestream.h"
#include "io/zipfs/zipfilestream.h"
#include "io/fswrapper.h"


namespace Pack
{
static const char* data_ls_name = "home:data.ls";
static const char* data_bin_name = "home:data.bin";
using namespace IO;

	class file_table_reader : public FileTable
	{
	public:

		void init_file_map(GPtr<Stream>& stream, const PackageListHeader& header)
		{
			m_FileInfos.resize(header.fileBlocksCount);

			size_t table_size = _get_size(header.fileBlocksCount);
			m_HashTable.resize(table_size, _hash_elem());

			stream->Seek(header.fileBlocksBegin, Stream::Begin);
			stream->Read(&m_FileInfos[0], header.fileBlocksCount * sizeof(FileBlock));

			if(header.fileNamesBegin)
			{			
				m_NameCache.resize(header.fileBlocksCount);
				stream->Seek(header.fileNamesBegin, Stream::Begin);
				for(size_t i = 0; i < header.fileBlocksCount; ++i)
				{
					u8 size = 0;//路径文字个数不可能大于255.
					stream->Read(&size, sizeof(u8));
					m_NameCache[i].assign(size, 0);
					stream->Read((void*)m_NameCache[i].data(), size);
				}
			}

			for (size_t i = 0; i < header.fileBlocksCount; ++i)
			{
				const FileBlock& fb = m_FileInfos[i];
				int free_index = _get_free_pos(fb.hashName);
				m_HashTable[free_index].index = i;
			}
		} 

	private:
		size_t _get_size(size_t file_count)
		{
			size_t sizes[] = {	17,				37,				79,				163,				331,  
				673,			1361,			2729,			5471,				10949,        
				21911,			43853,			87719,			175447,				350899,
				701819,			1403641,		2807303,		5614657,			11229331,   
				22458671,		44917381,		89834777,		179669557,			359339171,  
				718678369,		1437356741,		2147483647 };


			size_t _count2 = file_count + file_count / 2;
			for (int i = 0; i < sizeof(sizes); ++i)
			{
				if (_count2 < sizes[i])
				{
					return sizes[i];
				}
			}
			return _count2;
		}

		int _get_free_pos(HashCode hash)
		{
			size_t hashStart = _GetBlockIndex(hash);
			size_t hashPos = hashStart;

			while (INVALID_INDEX != m_HashTable[hashPos].index)
			{
				hashPos = _GetBlockIndex(hashPos + 1);	
				n_assert(hashPos != hashStart);
			}
	
			return hashPos;
		}
	};

Package::Package()
	: m_pFileStream(NULL)
	, m_FileBeginPos(0)
	, m_Opened(false)
#if __ANDROID__
	,m_bInApk(false)
#endif
{

}

Package::~Package()
{
	if (m_pFileStream.isvalid())
	{
		m_pFileStream = NULL;
	}
}

#if __ANDROID__
bool Package::OpenInAPK(const char* APKName)
{
	m_bInApk = true;
	m_Opened = false;
	URI lsUri("assets/Data/data.ls");
	URI uri("assets/Data/data.bin");
	
	if (!FSWrapper::FileExists(APKName))
	{
		n_warning("no package.");
		return m_Opened;
	}
	n_warning("before ziparchive create");
	m_ZipArchive = ZipArchive::Create();

	URI apkuri(APKName);

	m_ZipArchive->Setup(apkuri);

	GPtr<ZipFileStream> lsStream = IO::ZipFileStream::Create();

	lsUri.SetScheme("zip");
	Util::String query;
	query.Append("file=");
	query.Append("assets/Data/data.ls");
	lsUri.SetQuery(query);

	uri.SetScheme("zip");
	Util::String query2;
	query2.Append("file=");
	query2.Append("assets/Data/data.bin");
	uri.SetQuery(query2);

	lsStream->SetURI(lsUri);

	lsStream->SetAccessMode(Stream::ReadAccess);
	n_warning("**** s i****");
	m_Opened = lsStream->Open(m_ZipArchive);
	if (!m_Opened)
	{

		return m_Opened;
	}
	PackageListHeader header;
	lsStream->Read(&header, sizeof(PackageListHeader));
	if (header.sign != PACKAGE_LS_SIGN)
	{

		lsStream->Close();
		m_Opened = false;
		return m_Opened;
	}
	if (header.version != CURRENT_LS_VERSION)
	{

		lsStream->Close();
		m_Opened = false;
		return m_Opened;
	}

	file_table_reader* reader = (file_table_reader*)&m_FileTable;

	GPtr<IO::Stream> stream =	lsStream.upcast<IO::Stream>();

	reader->init_file_map(stream, header);
	lsStream->Close();
	lsStream = NULL;
	stream = NULL;
	n_warning("**** s l****");
	m_pFileStream = IO::ZipFileStream::Create();
	m_pFileStream->SetURI(uri); 
	n_assert(m_pFileStream.isvalid());	

	m_pFileStream->SetAccessMode(Stream::ReadAccess);

	const GPtr<ZipFileStream>& _zipStream  = m_pFileStream.downcast<ZipFileStream>();

	m_Opened = _zipStream->Open(m_ZipArchive);
	n_warning("**** s i****");
	if (m_Opened)
	{
		PackageDataHeader dataHeader;

		m_pFileStream->Read(&dataHeader, sizeof(PackageDataHeader));
		if (dataHeader.sign != PACKAGE_DATA_SIGN)
		{
			m_pFileStream->Close();
			m_Opened = false;
			return m_Opened;
		}

		if (dataHeader.version != CURRENT_DATA_VERSION)
		{
			m_pFileStream->Close();
			m_Opened = false;
			return m_Opened;
		}
		m_FileBeginPos = dataHeader.filesBegin;
		m_DiskBlockCount = dataHeader.diskBlockCount;
		m_DiskBlockSize = dataHeader.diskBlockSize;
	}


	m_pFileStream->Close();
	n_warning("**** s l****");
	return m_Opened;

}
#endif

bool Package::Open()
{
	m_Opened = false;
	URI lsUri(data_ls_name);
	URI uri(data_bin_name);
	//uri.SetScheme("file");
	if ((!FSWrapper::FileExists(lsUri.GetHostAndLocalPath())) || (!FSWrapper::FileExists(uri.GetHostAndLocalPath())))
	{
		n_warning("no package.");
		return m_Opened;
	}

	GPtr<Stream> lsStream = IO::FileStream::Create();
	lsStream->SetURI(lsUri);

	lsStream->SetAccessMode(Stream::ReadAccess);
	m_Opened = lsStream->Open();
	if (!m_Opened)
	{
		return m_Opened;
	}
	PackageListHeader header;
	lsStream->Read(&header, sizeof(PackageListHeader));
	if (header.sign != PACKAGE_LS_SIGN)
	{
		n_warning("error package.");
		lsStream->Close();
		m_Opened = false;
		return m_Opened;
	}
	if (header.version != CURRENT_LS_VERSION)
	{
		n_warning("unknown version:%d", header.version);
		lsStream->Close();
		m_Opened = false;
		return m_Opened;
	}

	file_table_reader* reader = (file_table_reader*)&m_FileTable;
	reader->init_file_map(lsStream, header);

	m_pFileStream = IO::FileStream::Create();
	m_pFileStream->SetURI(uri);
	n_assert(m_pFileStream.isvalid());	

	m_pFileStream->SetAccessMode(Stream::ReadAccess);
	m_Opened = m_pFileStream->Open();
	if (m_Opened)
	{
		PackageDataHeader dataHeader;
		m_pFileStream->Read(&dataHeader, sizeof(PackageDataHeader));
		if (dataHeader.sign != PACKAGE_DATA_SIGN)
		{
			n_warning("error package data.");
			m_pFileStream->Close();
			m_Opened = false;
			return m_Opened;
		}

		if (dataHeader.version != CURRENT_DATA_VERSION)
		{
			n_warning("unknown data version:%d", header.version);
			m_pFileStream->Close();
			m_Opened = false;
			return m_Opened;
		}
		m_FileBeginPos = dataHeader.filesBegin;
		m_DiskBlockCount = dataHeader.diskBlockCount;
		m_DiskBlockSize = dataHeader.diskBlockSize;
	}
	return m_Opened;
	
}

void Package::Close()
{
	m_Opened = false;
	m_pFileStream = NULL;
	m_FileTable.Clear();
	m_DiskBlockCount = 0;
	m_DiskBlockSize = 0;
	m_FileBeginPos = 0;
	m_ZipArchive = NULL;

#if __ANDROID__
	m_bInApk = false;
#endif
}

bool Package::ReadFile(GPtr<Stream>& pStream, const char* fileName) const
{
#if __ANDROID__

	if( m_bInApk==true )
	{
		URI uri("assets/Data/data.bin");
		uri.SetScheme("zip");
		Util::String query2;
		query2.Append("file=");
		query2.Append("assets/Data/data.bin");
		uri.SetQuery(query2);
		m_pFileStream = IO::ZipFileStream::Create();
		m_pFileStream->SetURI(uri); 
		n_assert(m_pFileStream.isvalid());	
		n_warning("in read file");

		m_pFileStream->SetAccessMode(Stream::ReadAccess);

		const GPtr<ZipFileStream>& _zipStream  = m_pFileStream.downcast<ZipFileStream>();

		bool m_Opened = _zipStream->Open(m_ZipArchive);
		n_warning("after  open ");
		bool ret;
		if (m_Opened)
		{
			n_warning("open success");
			ret = _ReadFile(m_pFileStream, pStream, fileName);
		}
		else
		{
			n_warning("open failed");
		}

		m_pFileStream->Close();
		return ret;
	}
	else
	{
		return _ReadFile(m_pFileStream, pStream, fileName);
	}
#else
	return _ReadFile(m_pFileStream, pStream, fileName);
#endif
}

bool Package::ReadFileThreadSafe(GPtr<IO::Stream>& pStream, const char* fileName) const
{

	URI uri(data_bin_name);
	GPtr<IO::Stream> fileStream = IO::FileStream::Create();
	fileStream->SetURI(uri.GetHostAndLocalPath());
	n_assert(fileStream.isvalid());	

	fileStream->SetAccessMode(Stream::ReadAccess);

	if (fileStream->Open())
	{
		return _ReadFile(fileStream, pStream, fileName);
	}
	return false;
}

bool Package::_ReadFile(GPtr<IO::Stream>& srcStream, GPtr<IO::Stream>& pStream, const char* fileName) const
{
	const FileBlock* block = m_FileTable.GetFileBlock(fileName);

	if (block)
	{
		if (pStream->Open())
		{
			pStream->SetSize(block->fileSize);
			
			if (pStream->GetSize() == 0)
				return false;
			
			void* pMem = pStream->Map();

			n_assert(pMem != NULL);

			n_warning("zip seek");
			srcStream->Seek(m_FileBeginPos + m_DiskBlockSize * block->beginBlock, Stream::Begin);	
			n_warning("zip read");
			srcStream->Read(pMem, block->fileSize);

			pStream->Unmap();
			pStream->Close();
			return true;
		}
	} 
	else
	{
		n_warning("File does not exist in the package: %s\n", fileName);
	}
	return false;
}

bool Package::IsFileExit(const char* fileName) const
{
	const FileBlock* block = m_FileTable.GetFileBlock(fileName);
	return (NULL != block);
}

}
