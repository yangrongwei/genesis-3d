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
#if __WIN32__

#include "stdneb.h"
#include "io/FileService/fileservicesystem.h"
#include "io/archfs/archive.h"
#include "io/assignregistry.h"
#include "util/stringatom.h"


#define MAX_CHAR_LENGTH 512
#define ENGIN_ID_PREFIX "__eg__"

namespace IO
{
	bool ConvertStrFromU8ToU16( const Util::String& src , wchar_t* dst , int dstBfLen )
	{
		int srcLen = src.Length() ;
		if( srcLen > dstBfLen )
		{
			n_error( "Wide char buffer is too short." ) ;
			return false ;
		}

		::MultiByteToWideChar( CP_UTF8 , 0 , src.Get() , - 1 , dst , dstBfLen ) ;
		return true ;
	}
	//------------------------------------------------------------------------------
	bool ConvertToRelativePath(const IO::URI& resID, Util::String& relative)
	{
		IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
		Util::String projPath = pAssignRegistry->GetAssign("project");
		projPath.ConvertBackslashes();
		Util::String resFileName = pAssignRegistry->ResolveAssigns(resID).LocalPath();
		IndexT projIndex = resFileName.FindStringIndex(projPath);
		if (projIndex == InvalidIndex)
		{
			return false;
		}
		relative = resFileName.ExtractRange(projPath.Length()+1, resFileName.Length()- projPath.Length()-1);
		return true;
	};

	//------------------------------------------------------------------------------
	FileService::FsHandle DownloadByFileService(const Util::String& resID)
	{
		return FileService::AccessResFromDisk(resID.AsCharPtr());
	};
}


namespace IO
{
__ImplementClass(IO::FileServiceSystem, 'FSSS', Core::RefCounted);
__ImplementImageSingleton(IO::FileServiceSystem);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
FileServiceSystem::FileServiceSystem() :
    isValid(false)
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
FileServiceSystem::~FileServiceSystem()
{
    if (this->IsValid())
    {
        // make sure that derived method is called
        this->Discard();
    }    
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
    Setup the archive file system. Subclasses may register their
    archive stream classes with the SchemeRegistry here.
*/
void
FileServiceSystem::Setup()
{
    n_assert(!this->IsValid());
    this->isValid = true;
	//Util::String fileserviceDIR = GetFileServiceDirectory();

	IndexT index = cacheDir.BackwardFindChar('\\', 1);
	if (InvalidIndex == index)
	{
		index = cacheDir.BackwardFindChar('/', 1);
	}
	n_assert(InvalidIndex != index);

	Util::String id = ENGIN_ID_PREFIX;
	id += &(cacheDir[index + 1]);


	wchar_t wfileserviceDIR[MAX_CHAR_LENGTH] = {0};
	wchar_t wcacheDIR[MAX_CHAR_LENGTH] = {0};
	wchar_t wserverAddress[MAX_CHAR_LENGTH] = {0};
	wchar_t wid[MAX_CHAR_LENGTH] = {0};
	ConvertStrFromU8ToU16(fileServiceDir,wfileserviceDIR, MAX_CHAR_LENGTH);
	ConvertStrFromU8ToU16(serverAddress,wserverAddress, MAX_CHAR_LENGTH);
	ConvertStrFromU8ToU16(cacheDir, wcacheDIR, MAX_CHAR_LENGTH);
	ConvertStrFromU8ToU16(id, wid, MAX_CHAR_LENGTH);

	this->isValid = FileService::InitFileService(wid, wfileserviceDIR, wcacheDIR, wserverAddress);

	if (!isValid)
	{		
		n_warning("\nfile service init false.");
		n_warning("\nid: ");
		n_warning(id.AsCharPtr());
		n_warning("\nfs dir: ");
		n_warning(fileServiceDir.AsCharPtr());
		n_warning("\nserver address: ");
		n_warning(serverAddress.AsCharPtr());
		n_warning("\ncache dir: ");
		n_warning(cacheDir.AsCharPtr());
	}
}

//------------------------------------------------------------------------------
/**
    Discard the archive file system.
*/
void
FileServiceSystem::Discard()
{
    n_assert(this->IsValid());

	FileService::CloseFileService();
    this->isValid = false;
}

//------------------------------------------------------------------------------
/**
    download file,return true if file is ready 
*/
FileService::FsHandle
FileServiceSystem::DownloadFile(const URI& uri, int& error)
{
	error = 0;
	Util::String resID;
	if(ConvertToRelativePath(uri, resID))
	{
		return DownloadByFileService(resID);
	}
	error = 1;
	return 0;
}
FileService::EAccessState
FileServiceSystem::FileAccessState(const FileService::FsHandle& hdl)
{
	return FileService::IsCanAccess(hdl);
}

} // namespace IO
#endif