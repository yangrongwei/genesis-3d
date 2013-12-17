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
#include <Shlwapi.h>
//#include "json/include/reader.h"
#include "GenesisLoader.h"


#define PARAM_STRING_UTF8_CMD "-utf8"

#define PARAM_STRING_HWND_CMD   "--hwnd"
#define PARAM_STRING_HWND_CONFIG L"hwnd"

#define PARAM_STRING_GAMEDIR_CMD   "--gamedir"
#define PARAM_STRING_GAMEDIR_CONFIG L"gamedir"

#define PARAM_STRING_SYSDIR_CMD   "--sysdir"
#define PARAM_STRING_SHDDIR_CMD   "--shddir"

//#define PARAM_STRING_ASSETNAME_CMD   "--assetname"
//#define PARAM_STRING_ASSETNAME_CONFIG L"assetname"

#define PARAM_STRING_REMOTEPATH_CMD   "--remotepath"
#define PARAM_STRING_REMOTEPATH_CONFIG L"remotepath"

#define PARAM_STRING_SCENENAME_CMD   "--scenename"
#define PARAM_STRING_SCENENAME_CONFIG L"scenename"

#define PARAM_STRING_DEBUGSCRIPT_CMD   "--debugscript"
#define PARAM_STRING_DEBUGSCRIPT_CONFIG L"debugscript"

#define PARAM_STRING_NOGUI_CMD     "--nogui"
#define PARAM_STRING_GUI_CONFIG     L"gui"

#define PARAM_STRING_SCREENSIZE_CMD     "--screensize"
#define PARAM_STRING_SCREENWIDTH_CONFIG   L"screenwidth"
#define PARAM_STRING_SCREENHEIGHT_CONFIG  L"screenheight"

#define PARAM_STRING_FILESERVICEDIR_CMD    "--fspath"
#define PARAM_STRING_FILESERVICEDIR_CONFIG  L"fspath"

//#define PARAM_STRING_
//#define PARAM_STRING_
//#define PARAM_STRING_
//#define PARAM_STRING_




namespace Genesis
{
GenesisLoader* GenesisLoader::m_pInst = NULL;

//-------------------------------------------------------------------------
GenesisLoader::~GenesisLoader()
{
}
//------------------------------------------------------------------------

inline void _asi_to_u8(const char* src, char* dest)
{
	WCHAR Path[MAX_PATH] = {0};
	MultiByteToWideChar(CP_ACP, 0, src, -1, Path,MAX_PATH);

	WideCharToMultiByte(CP_UTF8, 0, Path, -1, dest, MAX_PATH, 0, 0);
}

inline void _asi_to_u16(const char* src, WCHAR* dest)
{
	MultiByteToWideChar(CP_ACP, 0, src, -1, dest, MAX_PATH);
}

inline void _u8_to_u16(const char* src, WCHAR* dest)
{
	MultiByteToWideChar(CP_UTF8, 0, src, -1, dest, MAX_PATH);
}

inline void _u16_to_u8(const WCHAR* src, char* dest)
{
	WideCharToMultiByte(CP_UTF8, 0, src, -1, dest, MAX_PATH, 0, 0);
}

inline void _str_cpy(char* dest, size_t sizeInByte, char* src)
{
	strcpy_s(dest, sizeInByte, src);
}

inline void _str_cpy_u8(char* dest, size_t sizeInByte, char* src, bool asi)
{
	if(asi)
	{
		char buffer[MAX_PATH];
		_asi_to_u8(src, buffer);
		_str_cpy(dest, sizeInByte, buffer);
	}
	else
	{
		strcpy_s(dest, sizeInByte, src);
	}
}

inline bool _check_num(char ch)
{
	return ('0' <= ch && ch <= '9');
}

const char* _get_value(const char* param, char* value)
{
	int index = 0;
	while('\0' != *param)
	{
		if (_check_num(*param))
		{
			value[index] = *param;
			++index;
		}
		else if (',' == *param)
		{
			++param;
			break;
		}
		++param;
	}
	value[index] = '\0';
	return param;
}

void _get_size(const char* param, int& width, int& height)
{
	char str_width[256] = {'\0'};
	char str_height[256] = {'\0'};
	param = _get_value(param, str_width);
	_get_value(param, str_height);
	if (str_width[0])
	{
		width = ::atoi(str_width);
	}
	if (str_height[0])
	{
		height = ::atoi(str_height);
	}
}

bool _string_cmp(const char* v1, const char* v2)
{
	//check if string: --%head%;
	return (0 == ::strcmp(v1, v2));
}

void _set_by_args(GenesisLoaderData& data, HWND& PluginWnd, int argc, char *argv[])
{
	n_assert(argc > 1);
	int i = 1;
	bool asi = true;
	if (_string_cmp(PARAM_STRING_UTF8_CMD, argv[i]))
	{
		asi = false;
		++i;
	}

	//获得启动参数
	for (;i<argc;i++)
	{
		//plugin window handle
		if (_string_cmp(PARAM_STRING_HWND_CMD,argv[i]))
		{
			i++;
			sscanf_s(argv[i], "%x", &PluginWnd);
		}
		//where is the executeble file
		else if (_string_cmp(PARAM_STRING_GAMEDIR_CMD,argv[i]))
		{
			i++;
			_str_cpy_u8(data.sHomeDir,_countof(data.sHomeDir), argv[i], asi);
		}
		else if (_string_cmp(PARAM_STRING_SYSDIR_CMD,argv[i]))
		{
			i++;
			_str_cpy_u8(data.sSystemDir,_countof(data.sSystemDir), argv[i], asi);
		}
		else if (_string_cmp(PARAM_STRING_SHDDIR_CMD,argv[i]))
		{
			i++;
			_str_cpy_u8(data.sShaderDir,_countof(data.sShaderDir), argv[i], asi);
		}
		//else if (_string_cmp(PARAM_STRING_ASSETNAME_CMD,argv[i]))
		//{
		//	i++;
		//	_str_cpy_u8(data.sAssetName,_countof(data.sAssetName), argv[i],asi);
		//}
		//game url base
		else if (_string_cmp(PARAM_STRING_REMOTEPATH_CMD,argv[i]))
		{
			i++;
			//if(_string_cmp(argv[i],"null")!=0)
			//{
			//	_str_cpy(data.sResUrlBase,_countof(data.sResUrlBase),argv[i]);
			//}
			_str_cpy(data.sResUrlBase,_countof(data.sResUrlBase),argv[i]);
		}
		//scenenname
		else if (_string_cmp(PARAM_STRING_SCENENAME_CMD,argv[i]))
		{
			i++;
			_str_cpy_u8(data.sSceneName,_countof(data.sSceneName), argv[i], asi);
		}
		// file service path
		else if(_string_cmp(PARAM_STRING_FILESERVICEDIR_CMD, argv[i]))
		{
			i++;
			_str_cpy_u8(data.sFileServiceDir, _countof(data.sFileServiceDir), argv[i], asi);
			data.bFileService = true;
		}
		//debug script // - SunHao TODO:move this command to other place later 2012-3-30
		else if (_string_cmp(PARAM_STRING_DEBUGSCRIPT_CMD,argv[i]))
		{
			i++;
			if ( _string_cmp("true",argv[i]))
			{
				data.bSupportSctiptDebug = true;
			}
			else
			{
				data.bSupportSctiptDebug = false;
			}
		}
		else if (_string_cmp(PARAM_STRING_NOGUI_CMD, argv[i]))
		{
			i++;
			data.bGui = false;
		}
		else if (_string_cmp(PARAM_STRING_SCREENSIZE_CMD, argv[i]))
		{
			i++;
			int width = 0;
			int height = 0;
			_get_size(argv[i], width, height);
			if (width > 0 && height > 0)
			{
				data.uGameWidth = width;
				data.uGameHeight = height;
			}
		}
	}
}

void _set_by_config(GenesisLoaderData& data)
{
	WCHAR lpPath[MAX_PATH] = {0};
	WCHAR gamedir[MAX_PATH] = {0};
	WCHAR assetname[MAX_PATH] = {0};
	WCHAR scenename[MAX_PATH] = {0};
	WCHAR remotepath[MAX_PATH] = {0};
	WCHAR fspath[MAX_PATH] = {0};

	WCHAR screenWidth[MAX_PATH] = {0};
	WCHAR screenHeight[MAX_PATH] = {0};

	INT gui = 1;
	INT width = 0;
	INT height = 0;

	_u8_to_u16(data.sEngineDir, lpPath);

	//_u16_to_u8(lpPath, data.sHomeDir);

	StrCatW(lpPath, L"\\Config.ini");
	const WCHAR dstr[] = L"";
	const WCHAR AppName[] = {L"Genesis"};
	const WCHAR OldAppName[] = {L"webjet"};// for old version.

	const WCHAR* pName = AppName;

	GetPrivateProfileString(pName, PARAM_STRING_GAMEDIR_CONFIG, dstr, gamedir , MAX_PATH, lpPath);
	if('\0' == gamedir[0])
	{	
		pName = OldAppName;
		GetPrivateProfileString(OldAppName, PARAM_STRING_GAMEDIR_CONFIG, dstr, gamedir , MAX_PATH, lpPath);
	}
	if ('\0' == gamedir[0])
	{
		return;
	}

	GetPrivateProfileString(pName, PARAM_STRING_SCENENAME_CONFIG, dstr, scenename ,MAX_PATH, lpPath);
	GetPrivateProfileString(pName, PARAM_STRING_REMOTEPATH_CONFIG, dstr, remotepath ,MAX_PATH, lpPath);
	GetPrivateProfileString(pName, PARAM_STRING_FILESERVICEDIR_CONFIG, dstr, fspath , MAX_PATH, lpPath);

	gui = GetPrivateProfileInt(pName, PARAM_STRING_GUI_CONFIG, 1, lpPath);
	width = GetPrivateProfileInt(pName, PARAM_STRING_SCREENWIDTH_CONFIG, 0, lpPath);
	height = GetPrivateProfileInt(pName, PARAM_STRING_SCREENHEIGHT_CONFIG, 0, lpPath);


	//if('\0' == gamedir[0])//exe根目录
	//{
	//	strcpy(data.sHomeDir, data.sEngineDir);
	//}
	//else 
	if(':' != gamedir[0 + 1])//相对路径拼接
	{
		_u8_to_u16(data.sEngineDir, lpPath);
		StrCatW(lpPath, L"\\");
		StrCatW(lpPath, gamedir);
		_u16_to_u8(lpPath, data.sHomeDir);
	}
	else //绝对路径
	{
		_u16_to_u8(gamedir, data.sHomeDir);
	}
	

	data.bGui = (1 == gui);
	if (width > 0 && height > 0)
	{
		data.uGameWidth = width;
		data.uGameHeight = height;
	}

	//_u16_to_u8(gamedir, data.sHomeDir); 

	//strcpy(data.sHomeDir,gamedir); 
	//_u16_to_u8(assetname, data.sAssetName); 

	_u16_to_u8(remotepath, data.sResUrlBase); 
	if ('\0' != fspath[0])
	{
		if(':' != fspath[0 + 1])//相对路径拼接
		{
			_u8_to_u16(data.sEngineDir, lpPath);
			StrCatW(lpPath, L"\\");
			StrCatW(lpPath, fspath);
			_u16_to_u8(lpPath, data.sFileServiceDir);
		}
		else
		{
			_u16_to_u8(fspath, data.sFileServiceDir);
		}
		
		data.bFileService = true;
	}
	

	_u16_to_u8(scenename, data.sSceneName); 

}

bool GenesisLoader::Init( int argc, char *argv[] )
{
	/*assert(pGameInst);
	m_pGameInst = pGameInst;*/
	
	GenesisLoaderData data;

	//获得exe目录

	WCHAR szPath[MAX_PATH] = {0};
	if (::GetModuleFileName(::GetModuleHandle(NULL), szPath, MAX_PATH))
	{
		_u16_to_u8(szPath, data.sEngineDir);
		for (int i=0;data.sEngineDir[i]!='\0';i++)
		{
			if(data.sEngineDir[i] == '#')
			{
				return false;
			}
		}
	}



	int i = 0;
	int end = 0;
	while(data.sEngineDir[i] != '\0')
	{
		if ('\\' == data.sEngineDir[i])
		{
			end = i;
		}
		++i;
	}
	data.sEngineDir[end] = '\0';

	
	if (argc > 1)
	{
		_set_by_args(data, mh_PluginWnd, argc, argv);
	}
	else
	{
		_set_by_config(data);
	}

	if (0 == data.sHomeDir[0])
	{
		return false;
	}

	//网页版本还是单机版本
	if (!mh_PluginWnd)
	{
		m_bLocalVersion = true;		
	}
	else
	{
		//取窗口尺寸
		RECT rect;
		GetClientRect(mh_PluginWnd,&rect);		
		data.uGameWidth = rect.right - rect.left;
		data.uGameHeight = rect.bottom -rect.top;

		m_bLocalVersion = false;
		data.bWebVersion = true;
	}
	////使用网络资源还是本地资源
	//if (!data.sResUrlBase[0])
	//{
	//	m_bLocalRes = true;
	//	//data.bUseLocalRes = true;
	//}
	//else
	//{
	//	m_bLocalRes = false;
	//	//data.bUseLocalRes = false;
	//}

	//创建窗口,赋值句柄
	data.hWnd = CreateLoaderWindow(mh_PluginWnd,data.uGameWidth,data.uGameHeight);
	if (m_bLocalVersion)
	{
		mh_PluginWnd = data.hWnd;
	}

	//CreateLoaderWindow(mh_PluginWnd,data.uGameWidth,data.uGameHeight);
	//data.hWnd =mh_PluginWnd;

	//初始化游戏应用实例
	WinWebInit(&data);

	return true;
}
//------------------------------------------------------------------------
 void GenesisLoader::Run()
{
	//Message Loop
	MSG msg;


	for (;;)
	{
		if(!IsWindowEnabled(this->mh_PluginWnd))break;			

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				WinWebCleanup();
				break;
			}
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}	
		else 
		{
			//限制帧数
			const float MAX_FPS = 70.f;
			//两次更新最小时间间隔，in milleseconds
			const float MIN_INTERVAL = 1000.f/MAX_FPS;
			static float fLastTick = (float)GetTickCount() - MIN_INTERVAL;
			float fCurrTick = (float)GetTickCount();
			
			//网页版限速
			if (!m_bLocalVersion)
			{
				//休息下一个间隔还剩的时间
				if (fCurrTick - fLastTick < MIN_INTERVAL)
				{
					Sleep(MIN_INTERVAL - (fCurrTick - fLastTick));
					continue;
				}
			}
			


			if (!WinWebUpdate())
			{
				break;
			}
			fLastTick = fCurrTick;
		
		}
	}
	
}
//------------------------------------------------------------------------
 bool GenesisLoader::End()
 {
	 WinWebCleanup();
	 return true;
 }
 //------------------------------------------------------------------------
 HWND GenesisLoader::CreateLoaderWindow( HWND parentWnd,unsigned int nWidth,unsigned int nHeight )
 {
	extern LRESULT CALLBACK  WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	const wchar_t* wndClassName = L"GameWindow";
	const wchar_t* wndTitle = L"GenesisGame";


	HINSTANCE hInst = ::GetModuleHandle(0);


	 WNDCLASSEX wcex;

	 wcex.cbSize = sizeof(WNDCLASSEX);

	 wcex.style			= CS_HREDRAW | CS_VREDRAW;
	 wcex.lpfnWndProc	= WndProc;
	 wcex.cbClsExtra	= 0;
	 wcex.cbWndExtra	= 0;
	 wcex.hInstance		= hInst;
	 wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	 wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	 wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	 wcex.lpszMenuName	= NULL;
	 wcex.lpszClassName	= wndClassName;
	 wcex.hIconSm		= NULL;

	RegisterClassEx(&wcex);
	
	HWND hWnd;
	DWORD dwStyle = 0;
	 // create window
	if (parentWnd)
	{
		dwStyle = WS_VISIBLE | WS_CHILD;

	}
	else
	{
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_VISIBLE;
	}

	RECT bounds;
	bounds.left = 0;
	bounds.top = 0;
	bounds.right = nWidth;
	bounds.bottom = nHeight;
	AdjustWindowRectEx(&bounds, dwStyle, FALSE, 0);

	int windowWidth = bounds.right - bounds.left;
	int windowHeight = bounds.bottom - bounds.top;


	hWnd = CreateWindow(wndClassName, 
		wndTitle,
		dwStyle,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		windowWidth,
		windowHeight,
		parentWnd, 
		NULL, 
		hInst, 
		NULL);

	assert(hWnd && "Create Window Failed");
	UpdateWindow(hWnd);

	return hWnd;
 }

	
}//end namespace

//------------------------------------------------------------------------

LRESULT CALLBACK  WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND parentWND = GetParent(hwnd);
	
	UINT eno;
		

	switch (message)
	{
	/*case WM_KILLFOCUS:
		{
			EnableWindow(hwnd,FALSE);
			break;
		}*/
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		{
			if(GetFocus()!=hwnd)
			{				
				SetForegroundWindow(hwnd);
	
				SetFocus(hwnd);  
			}
			break;
		}
	case WM_CREATE:
		return (0);

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);

		EndPaint (hwnd, &ps);
		return (0);
		break;

	case WM_DESTROY:
		PostQuitMessage (0); 
		return (0);

	case WM_MOUSEACTIVATE:
		{
			WinInputMsg(hwnd,message,wParam,lParam);
			return MA_ACTIVATE;
		
		}break;
	case WM_COPYDATA:
		{
			break;
		}
	default:
		{
			break;
		}
	
	}
	 //return ::DefWindowProc(hwnd, message, wParam, lParam);
	return WinInputMsg(hwnd,message,wParam,lParam);
}

void TestDashExc()
{
	//::OutputDebugString(_T("111111"));
	// 空指针:release和debug均(正常)
	//int* p = NULL;
	//*p = 1;
	// 除0:release模式(捕获不到,__try__except也捕获不到);debug模式(正常)
	/*int i= 0;
	i = 1/i;*/
	// n_assert:release模式(正常)
	//n_assert2(false, "test");
	// throw:release模式(正常);debug模式(正常)
	//throw("hello");
	// raise exception:release模式(加了outputstring语句正常，否则dump崩在set_invalid_param..)
	//::RaiseException(1,0,0,NULL);
	// crt invalid parm:release模式(正常)
	//printf(NULL);
	//::OutputDebugString(_T("2222"));
}

//------------------------------------------------------------------------
//入口点
int main(int argc, char *argv[])
{
	// - need it only when debugging 
	//MessageBoxA(NULL,"GenesisLoader","",MB_OK);

	using namespace Genesis;

	if(!GenesisLoader::Instance()->Init(argc,argv))
	{
		::MessageBoxA(NULL,"Error config.","Genesis Loader",MB_OK);
		return 0;
	}
	GenesisLoader::Instance()->Run();

	GenesisLoader::Instance()->End();

	
	return 0;
}