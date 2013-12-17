/****************************************************************************
Copyright (c) 2010, Radon Labs GmbH
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
#include "osxfswrapper.h"
#include "core/sysfunc.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
namespace OSX
{
using namespace Util;
using namespace Core;
using namespace IO;
    
//------------------------------------------------------------------------------
/**
*/
OSXFSWrapper::Handle
OSXFSWrapper::OpenFile(const String& path, Stream::AccessMode accessMode, Stream::AccessPattern accessPattern)
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
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::CloseFile(Handle handle)
{
    if (handle != NULL)
	{
		fclose(handle);
	}
}
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::Write(Handle handle, const void* buf, Stream::Size numBytes)
{
    n_assert(0 != handle);
	n_assert(buf != 0);
	n_assert(numBytes > 0);
    
	fwrite(buf, numBytes, 1, handle);
}
    
//------------------------------------------------------------------------------
/**
*/
Stream::Size
OSXFSWrapper::Read(Handle handle, void* buf, Stream::Size numBytes)
{
    n_assert(0 != handle);
	n_assert(buf != 0);
	n_assert(numBytes > 0);
    
	fread(buf, numBytes, 1, handle);
    
	return numBytes;
}
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::Seek(Handle handle, Stream::Offset offset, Stream::SeekOrigin orig)
{
    n_assert(0 != handle);
    
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
    
	fseek(handle, offset, moveMethod);
}
    
//------------------------------------------------------------------------------
/**
*/
Stream::Position
OSXFSWrapper::Tell(Handle handle)
{
    n_assert(0 != handle);
	ftell(handle);
}
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::Flush(Handle handle)
{
    n_assert(0 != handle);
	fflush(handle);
}
    
//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::Eof(Handle handle)
{
    n_assert(0 != handle);
	IndexT pos = feof(handle);
    
	if (pos != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
    
//------------------------------------------------------------------------------
/**
*/
Stream::Size
OSXFSWrapper::GetFileSize(Handle handle)
{
    n_assert(0 != handle);
    
	SizeT fileSize;
    
	IndexT cur = ftell(handle);
	fseek(handle, 0, SEEK_END);
	fileSize = ftell(handle);
    
	fseek(handle, cur, SEEK_SET);
    
	return fileSize;
}
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::SetReadOnly(const String& path, bool readOnly)
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

//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::IsReadOnly(const String& path)
{
    n_assert(path.IsValid());
    
	struct stat attr;
	stat(path.AsCharPtr(), &attr);
    
	return (attr.st_mode & S_IRUSR);
}
    
//------------------------------------------------------------------------------
/**
 */
bool
OSXFSWrapper::DeleteFile(const String& path)
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
    
//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::DeleteDirectory(const String& path)
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
    
//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::FileExists(const String& path)
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
    
//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::DirectoryExists(const String& path)
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
    
//------------------------------------------------------------------------------
/**
*/
void
OSXFSWrapper::SetFileWriteTime(const String& path, FileTime fileTime)
{
    n_assert(path.IsValid());
    
	utime(path.AsCharPtr(), &fileTime.fileTime);
}
    
//------------------------------------------------------------------------------
/**
*/
FileTime
OSXFSWrapper::GetFileWriteTime(const String& path)
{
    n_assert(path.IsValid());
	FileTime fileTime;
    
	struct stat attr;
	stat(path.AsCharPtr(), &attr);
    
	fileTime.fileTime.modtime = attr.st_atime;
	fileTime.fileTime.actime  = attr.st_mtime;
    
	return fileTime;
}
    
//------------------------------------------------------------------------------
/**
*/
bool
OSXFSWrapper::CreateDirectory(const String& path)
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
//------------------------------------------------------------------------------
/**
*/
Array<String>
OSXFSWrapper::ListFiles(const String& path, const String& pattern)
{
    n_assert(path.IsValid());
	n_assert(pattern.IsValid());
    
	Array<String> result;
    
	List_Files(path.AsCharPtr(), false, result);
    
	return result;
}
    
//------------------------------------------------------------------------------
/**
 */
Array<String>
OSXFSWrapper::ListDirectories(const String& path, const String& pattern)
{
    n_assert(path.IsValid());
	n_assert(pattern.IsValid());
    
	Array<String> result;
    
	List_Files(path.AsCharPtr(), true, result);
    
	return result;
}
    
//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetUserDirectory()
{
    return "";
}
    
//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetAppDataDirectory()
{  
    return "";
}
    
//------------------------------------------------------------------------------
/**
 */
String 
OSXFSWrapper::GetProgramsDirectory()
{  
    n_error("OSXFSWrapper::GetProgramsDirectory(): NOT IMPLEMENTED!");
    return "";
}
    
//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetTempDirectory()
{
    return "";
}
    
//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetBinDirectory()
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
    
//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetHomeDirectory()
{
    char buffer[NEBULA3_MAXPATH];
	readlink("proc/self/exe", buffer, NEBULA3_MAXPATH);
    
	String pathToExe;
	pathToExe.SetCharPtr(buffer);
    
	String homePath = pathToExe.ExtractDirName();
	return String("file:///") + homePath;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
OSXFSWrapper::IsDeviceName(const Util::String& str)
{
    if (str == "OSX") return true;
    else return false;
}
    
//------------------------------------------------------------------------------
/**
 */
const char*
OSXFSWrapper::ConvertPath(const Util::String& str)
{
    const char* ptr = str.AsCharPtr();
    n_assert((ptr[0] == 'O') && (ptr[1] == 'S') && (ptr[2] == 'X') && (ptr[3] == ':'));
    return &(ptr[4]);
}

//------------------------------------------------------------------------------
/**
 */
String
OSXFSWrapper::GetEditorAssetDirectory()
{  
    n_error("OSXFSWrapper::GetEditorAssetDirectory(): NOT IMPLEMENTED!");
    return "";
}

} // namespace OSX