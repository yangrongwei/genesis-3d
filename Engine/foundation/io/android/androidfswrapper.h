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

#ifndef __ANDROIDFSWRAPPER_H__
#define __ANDROIDFSWRAPPER_H__

#include "util/string.h"
#include "util/array.h"
#include "io/stream.h"
#include "io/filetime.h"

namespace Android
{
	class AndroidFSWrapper
{
public:

	typedef FILE* Handle; 

	/// open a file
	static Handle OpenFile(const Util::String& path, IO::Stream::AccessMode accessMode, IO::Stream::AccessPattern accessPattern);
	/// close a file
	static void CloseFile(Handle h);
	/// write to a file
	static void Write(Handle h, const void* buf, IO::Stream::Size numBytes);
	/// read from a file
	static IO::Stream::Size Read(Handle h, void* buf, IO::Stream::Size numBytes);
	/// seek in a file
	static void Seek(Handle h, IO::Stream::Offset offset, IO::Stream::SeekOrigin orig);
	/// get position in file
	static IO::Stream::Position Tell(Handle h);
	/// flush a file
	static void Flush(Handle h);
	/// return true if at end-of-file
	static bool Eof(Handle h);
	/// get size of a file in bytes
	static IO::Stream::Size GetFileSize(Handle h);
	/// set read-only status of a file
	static void SetReadOnly(const Util::String& path, bool readOnly);
	/// get read-only status of a file
	static bool IsReadOnly(const Util::String& path);
	/// delete a file
	static bool DeleteFile(const Util::String& path);
	/// delete an empty directory
	static bool DeleteDirectory(const Util::String& path);
	/// return true if a file exists
	static bool FileExists(const Util::String& path);
	/// return true if a directory exists
	static bool DirectoryExists(const Util::String& path);
	/// set the write-access time stamp of a file
	static void SetFileWriteTime(const Util::String& path, IO::FileTime fileTime);
	/// get the last write-access time stamp of a file
	static IO::FileTime GetFileWriteTime(const Util::String& path);
	/// create a directory
	static bool CreateDirectory(const Util::String& path);
	/// list all files in a directory
	static Util::Array<Util::String> ListFiles(const Util::String& dirPath, const Util::String& pattern);
	/// list all subdirectories in a directory
	static Util::Array<Util::String> ListDirectories(const Util::String& dirPath, const Util::String& pattern);
	/// get path to the current user's home directory (for user: standard assign)
	static Util::String GetUserDirectory();
	/// get path to the current user's appdata directory (for appdata: standard assign)
	static Util::String GetAppDataDirectory();
	/// get path to the current user's temp directory (for temp: standard assign)
	static Util::String GetTempDirectory();
	/// get path to the current application directory (for home: standard assign)
	static Util::String GetHomeDirectory();
	/// get path to the current bin directory (for bin: standard assign)
	static Util::String GetBinDirectory();
	/// get path to the "c:/program files" directory
	static Util::String GetProgramsDirectory();
	/// return true when the string is a device name (e.g. "C:")
	static bool IsDeviceName(const Util::String& str);
	/// skips the OSX: at the start of the path
	static const char* ConvertPath(const Util::String& str);
	/// get path to the editor asset directory (for editor: standard assign)
	static Util::String GetEditorAssetDirectory();
};
}


#endif