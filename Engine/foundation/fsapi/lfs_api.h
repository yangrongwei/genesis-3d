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



#ifndef __LFS_API_H__
#define __LFS_API_H__

namespace FileService
{
	typedef long long FsHandle;

	enum EPriorLvl
	{
		EPriorLvl_Highest	= 0,
		EPriorLvl_High		= 1,
		EPriorLvl_Normal	= 2,  
		EPriorLvl_Low		= 3,
		EPriorLvl_LvlNum	= 4,
	};

	enum EAccessState
	{
		EAccessState_Invalid = -1,
		EAccessState_OK = 0,
		EAccessState_Error,
		EAccessState_Downloading,
		EAccessState_Num,
	};

	bool InitFileService( const wchar_t* id, const wchar_t* file_service_path, const wchar_t* disk_cache, const wchar_t* server_address );

	//************************************
	// - request init FileService and create FileService process if needed
	// - Returns: bool 
	// - Parameter: const wchar_t* id
	// - Parameter:	const wchar_t* disk_cache
	// - Parameter: const wchar_t* server_address
	//************************************
	void CloseFileService( void );

	//************************************
	// - request the FileService to download a file to the disk
	// - Returns: FsHandle				handle of this download request
	// - Parameter: wchar_t* pFilePath  relative path of this file.eg, texture/white.dds
	// - Parameter:	EPriorLv eLvl       Prior of the request
	//************************************
	FsHandle AccessResFromDisk( const wchar_t* pRelativePath, EPriorLvl eLvl=EPriorLvl_High );


		//************************************
	// - request the FileService to download a file to the disk
	// - Returns: FsHandle				handle of this download request
	// - Parameter: char* pFilePath  relative path of this file.eg, texture/white.dds
	// - Parameter:	EPriorLv eLvl       Prior of the request
	//************************************
	FsHandle AccessResFromDisk( const char* pRelativePath, EPriorLvl eLvl=EPriorLvl_High );

	//************************************
	// - query if a request of specify handle is completed
	// - Returns: bool					true if the request is completed,false stands for not or invalid handle
	// - Parameter: FsHandle hdl		hdl of a download request, shall be return by AccessResFromFileSystem(char*) or AccessResFromDisk(char*)
	//************************************
	EAccessState IsCanAccess( FsHandle hdl );

	//************************************
	// - release a FsHandle
	// - Returns: void 
	// - Parameter: FsHandle hdl
	//************************************
	void ReleaseFileHandle( FsHandle hdl );

	////************************************ 
	//// - get file's stream by a handle
	//// - Returns: RawStream				return file's stream if this file can be access,return zero rawStream if not  
	//// - Parameter: FsHandle hdl		hdl of a download request, shall be return by AccessResFromFileSystem(char*) or AccessResFromDisk(char*)
	////************************************ 
	//RawStream GetFileStream( FsHandle hdl );

	////************************************ 
	//// - free memory record in RawStream
	//// - Returns: void
	//// - Parameter: RawStream stream	RawStream return by GetFileStream()
	////************************************ 
	//void DropRawSteam( RawStream& stream );
}

#endif // - __LFS_API_H__