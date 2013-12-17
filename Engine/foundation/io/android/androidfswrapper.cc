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

#ifdef __ANDROID__
#include "stdneb.h"
#include "androidfswrapper.h"
#include "core/sysfunc.h"
#include "util/android/androidstringconverter.h"

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

namespace Android
{
using namespace Util;
using namespace Core;
using namespace IO;

AndroidFSWrapper::Handle AndroidFSWrapper::OpenFile(const Util::String& path, IO::Stream::AccessMode accessMode, IO::Stream::AccessPattern accessPattern)
{

	 char* pMode;

	 switch (accessMode)
	 {
	 case Stream::ReadAccess:
		 pMode = "rb";
		 break;
	 case Stream::WriteAccess:
		 pMode = "wb";
		 break;
	 case Stream::ReadWriteAccess:
		 pMode = "r+b"; 
		 break;
	 case Stream::AppendAccess:
		 pMode = "a+b";
		 break;
	 }

	 Handle handle = fopen(path.AsCharPtr(), pMode);

	 if (handle != NULL)
	 {
		 return handle;
	 } 
	 else
	 {
		 char* pError = strerror(errno);
		 return NULL;
	 }
	
}

void AndroidFSWrapper::CloseFile(Handle h)
{
	if (h != NULL)
	{
		fclose(h);
	}
}

void AndroidFSWrapper::Write(Handle h, const void* buf, IO::Stream::Size numBytes)
{
	n_assert(0 != h);
	n_assert(buf != 0);
	n_assert(numBytes > 0);

	fwrite(buf, numBytes, 1, h);


}

Stream::Size AndroidFSWrapper::Read(Handle h, void* buf, IO::Stream::Size numBytes)
{
	n_assert(0 != h);
	n_assert(buf != 0);
	n_assert(numBytes > 0);

	fread(buf, numBytes, 1, h);

	return numBytes;
}

void AndroidFSWrapper::Seek(Handle h, IO::Stream::Offset offset, IO::Stream::SeekOrigin orig)
{
	n_assert(0 != h);

	SizeT moveMethod;
	switch (orig)
	{
	case Stream::Begin:
		moveMethod = SEEK_SET;
		break;
	case Stream::Current:
		moveMethod = SEEK_CUR;
		break;
	case Stream::End:
		moveMethod = SEEK_END;
		break;
	default:
		// can't happen
		moveMethod = SEEK_SET;
		break;
	}

	fseek(h, offset, moveMethod);
}

Stream::Position AndroidFSWrapper::Tell(Handle h)
{
	n_assert(0 != h);
	ftell(h);
}

void AndroidFSWrapper::Flush(Handle h)
{
	n_assert(0 != h);
	fflush(h);
}

bool AndroidFSWrapper::Eof(Handle h)
{
	n_assert(0 != h);
	IndexT pos = feof(h);

	if (pos != 0)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

Stream::Size AndroidFSWrapper::GetFileSize(Handle h)
{
	n_assert(0 != h);

	SizeT fileSize;

	IndexT cur = ftell(h);
	fseek(h, 0, SEEK_END);
	fileSize = ftell(h);

	fseek(h, cur, SEEK_SET);

	return fileSize;

}

void AndroidFSWrapper::SetReadOnly(const Util::String& path, bool readOnly)
{
	n_assert(path.IsValid());

	struct stat attr;
	stat(path.AsCharPtr(), &attr);

	if (readOnly)
	{
		attr.st_mode |= S_IRUSR;
	} 
	else
	{
		attr.st_mode &= ~S_IRUSR;
	}
	

	chmod(path.AsCharPtr(), attr.st_mode);
}

bool AndroidFSWrapper::IsReadOnly(const Util::String& path)
{
	n_assert(path.IsValid());

	struct stat attr;
	stat(path.AsCharPtr(), &attr);

	return (attr.st_mode & S_IRUSR);
}

bool AndroidFSWrapper::DeleteFile(const Util::String& path)
{
	n_assert(path.IsValid());

	IndexT ret = remove(path.AsCharPtr());

	if (ret == 0)
	{
		return true;
	}
	else if (ret == -1)
	{
		return false;
	}
}

bool AndroidFSWrapper::DeleteDirectory(const Util::String& path)
{
	n_assert(path.IsValid());

	IndexT ret = rmdir(path.AsCharPtr());

	if (ret == 0)
	{
		return true;
	}
	else if (ret == -1)
	{
		return false;
	}
}

bool AndroidFSWrapper::FileExists(const Util::String& path)
{
	n_assert(path.IsValid());

	IndexT ret = access(path.AsCharPtr(), 0);

	if (ret == 0)
	{
		return true;
	}
	else if (ret == -1)
	{
		return false;
	}
}

bool AndroidFSWrapper::DirectoryExists(const Util::String& path)
{
	n_assert(path.IsValid());

	IndexT ret = access(path.AsCharPtr(), 0);

	if (ret == 0)
	{
		return true;
	}
	else if (ret == -1)
	{
		return false;
	}
}

void AndroidFSWrapper::SetFileWriteTime(const Util::String& path, IO::FileTime fileTime)
{
	n_assert(path.IsValid());

	utime(path.AsCharPtr(), &fileTime.time);
}

FileTime AndroidFSWrapper::GetFileWriteTime(const Util::String& path)
{
	n_assert(path.IsValid());
	FileTime fileTime;

	struct stat attr;
	stat(path.AsCharPtr(), &attr);

	fileTime.time.modtime = attr.st_atime;
	fileTime.time.actime  = attr.st_mtime;

	return fileTime;
}

bool AndroidFSWrapper::CreateDirectory(const Util::String& path)
{
	n_assert(path.IsValid());
	IndexT ret = mkdir(path.AsCharPtr(), S_IRWXU);

	if (ret == 0)
	{
		return true;
	} 
	else if (ret == -1)
	{
		return false;
	}
}

static int IS_DIR(const char* path)
{
	struct stat st;
	lstat(path, &st);
	return S_ISDIR(st.st_mode);
}


static void ListFilesCore(const char *path, bool recursive, Array<String>& result)
{
	DIR *pdir;
	struct dirent *pdirent;
	char temp[256];
	pdir = opendir(path);
	if(pdir)
	{
		while(pdirent = readdir(pdir))
		{
			
			if(strcmp(pdirent->d_name, ".") == 0
				|| strcmp(pdirent->d_name, "..") == 0)
				continue;

			sprintf(temp, "%s/%s", path, pdirent->d_name);
			
			if(IS_DIR(temp) && recursive)
			{
				result.Append(temp);
				ListFilesCore(temp, recursive, result);
			}
			else
			{
				result.Append(temp);
			}
		}
	}

	closedir(pdir);

}

static void List_Files(const char *path, bool recursive, Array<String>& result)
{
	int len;
	char temp[256];

	len = strlen(path);
	strcpy(temp, path);
	if(temp[len - 1] == '/') 
	{
		temp[len -1] = '\0';
	}

	if(IS_DIR(temp))
	{
		ListFilesCore(temp, recursive, result);
	}
	
}

Array<String> AndroidFSWrapper::ListFiles(const Util::String& dirPath, const Util::String& pattern)
{
	n_assert(dirPath.IsValid());
	n_assert(pattern.IsValid());

	Array<String> result;

	List_Files(dirPath.AsCharPtr(), false, result);

	return result;


}

Array<String> AndroidFSWrapper::ListDirectories(const Util::String& dirPath, const Util::String& pattern)
{
	n_assert(dirPath.IsValid());
	n_assert(pattern.IsValid());

	Array<String> result;

	List_Files(dirPath.AsCharPtr(), true, result);

	return result;
}

String AndroidFSWrapper::GetUserDirectory()
{
	return "";
}

String AndroidFSWrapper::GetAppDataDirectory()
{
	return "";
}

String AndroidFSWrapper::GetProgramsDirectory()
{
	return "";
}

String AndroidFSWrapper::GetTempDirectory()
{
	return "";
}

String AndroidFSWrapper::GetBinDirectory()
{
	char buffer[NEBULA3_MAXPATH];
	readlink("proc/self/exe", buffer, NEBULA3_MAXPATH);

	String pathToExe;
	pathToExe.SetCharPtr(buffer);

	pathToExe.ConvertBackslashes();
	pathToExe = pathToExe.ExtractDirName();
	pathToExe.TrimRight("/");
	return String("file:///") + pathToExe;
}

String AndroidFSWrapper::GetHomeDirectory()
{
	char buffer[NEBULA3_MAXPATH];
	readlink("proc/self/exe", buffer, NEBULA3_MAXPATH);

	String pathToExe;
	pathToExe.SetCharPtr(buffer);

	String homePath = pathToExe.ExtractDirName();
	return String("file:///") + homePath;

}

bool AndroidFSWrapper::IsDeviceName(const Util::String& str)
{
	if (str == "ANDROID")
	{
		return true;
	} 
	else
	{
		return false;
	}
}

const char* AndroidFSWrapper::ConvertPath(const Util::String& str)
{
	const char* ptr = str.AsCharPtr();
	n_assert((ptr[0] == 'O') && (ptr[1] == 'S') && (ptr[2] == 'X') && (ptr[3] == ':'));
	return &(ptr[4]);
}

String AndroidFSWrapper::GetEditorAssetDirectory()
{
	return "";
}




}
#endif