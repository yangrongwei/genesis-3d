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
#ifndef _GENESISLOADERDATA_H_
#define _GENESISLOADERDATA_H_


#ifdef WIN32


#include <Windows.h>

class GenesisLoaderData
{
public:
	GenesisLoaderData()
	{
		hWnd = NULL;
		SecureZeroMemory(sHomeDir, sizeof(sHomeDir));
		SecureZeroMemory(sSystemDir, sizeof(sSystemDir));
		SecureZeroMemory(sShaderDir, sizeof(sShaderDir));
		//SecureZeroMemory(sAssetName, sizeof(sAssetName));
		SecureZeroMemory(sResUrlBase, sizeof(sResUrlBase));
		SecureZeroMemory(sSceneName, sizeof(sSceneName));
		SecureZeroMemory(sFileServiceDir, sizeof(sFileServiceDir));
		SecureZeroMemory(sEngineDir, sizeof(sEngineDir));
		//bUseLocalRes		= false;
		bSupportSctiptDebug = false;
		uGameWidth			= 1024;
		uGameHeight			= 768;
		bGui				= true;	
		bFileService		= false;
	}

public:
	//窗口句柄
	HWND hWnd;
	//各游戏的资源文件夹名称
	char sHomeDir[MAX_PATH];
	// System资源目录
	char sSystemDir[MAX_PATH];
	// Shader资源目录
	char sShaderDir[MAX_PATH];
	//场景文件名称
	char sSceneName[MAX_PATH];
	//资源基础URL下载
	char sResUrlBase[MAX_PATH];
	//file service所在的目录
	char sFileServiceDir[MAX_PATH];
	//引擎所在目录
	char sEngineDir[MAX_PATH];

	//游戏分辨率
	unsigned int uGameWidth;
	unsigned int uGameHeight;

	//是否支持脚本调试
	bool bSupportSctiptDebug;
	////是否只使用本地资源
	//bool bUseLocalRes;
	//是否是网页版本
	bool bWebVersion;
	//是否加载GUI系统。
	bool bGui;
	//是否使用file service
	bool bFileService;
	
};
#endif // _GENESISLOADERDATA_H_

#endif