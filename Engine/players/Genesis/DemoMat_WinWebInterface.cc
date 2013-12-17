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
#include "system/appentry.h"
#include "foundation/memory/memory.h"
#include "tools/GenesisLoader/GenesisLoader.h"
#include "simplegameapplication.h"

#include "appframework/app_fwd_decl.h"

#include "input/inputwindowsource.h"
#include "input/win32/win32inputwebwindowsource.h"

#include "app/graphicfeature/graphicsfeature.h"

using namespace Genesis;


static DemoPublishGameApplication* g_App = NULL;

//-------------------------------------------------------------------------------
char* GetCarmerPos( void )
{
	static char s_StrPos[64];
	App::TActorPtr pCamera = App::GraphicsFeature::Instance()->GetDefaultCameraActor();
	Math::vector pos = pCamera->GetPosition();

	memset( s_StrPos, 0, 64 );
	sprintf_s( s_StrPos, "%f %f %f", pos.x(), pos.y(), pos.z() );
	return s_StrPos;
}
//------------------------------------------------------------------------
bool WinWebInit(GenesisLoaderData* pData)
{
	g_App = n_new( DemoPublishGameApplication ) ;
	assert( NULL!= g_App) ;

	if( NULL==g_App )
	{
		return false;
	}

	g_App->SetCompanyName( "CYOU-INC.COM" );
	g_App->SetAppTitle( "Genesis Game" );

	g_App->SetWebVersion( true,pData->hWnd );
	g_App->SetEngineDir(pData->sEngineDir);
	g_App->SetResourceBaseDir( pData->sHomeDir );

	g_App->SetResDownloadUrl( pData->sResUrlBase );
	g_App->SetFileServicePath( pData->sFileServiceDir);
	if (pData->sResUrlBase[0] && pData->sFileServiceDir[0])
	{
		g_App->SetUseFileService(true);
	}

	//g_App->SetUseLocalRes( pData->bUseLocalRes );

	g_App->SetDebugScript( pData->bSupportSctiptDebug );
	g_App->SetGui( pData->bGui );


	RECT clientRect;
	::GetClientRect((HWND)pData->hWnd,&clientRect);
	uint height = clientRect.bottom - clientRect.top;
	uint width = clientRect.right - clientRect.left; 
	g_App->SetGameResolution(width, height);

	GPtr<Input::InputSource> input = NULL;
	//网页版分支
	if (pData->bWebVersion)
	{
		input = Win32Input::Win32InputWebWindowSource::Create();
		input.downcast<Win32Input::Win32InputWebWindowSource>()->SetWnd((HWND)pData->hWnd);
	}
	else
	{
		input = Input::InputWindowSource::Create();
		input.downcast<Input::InputWindowSource>()->SetWnd((HWND)pData->hWnd);
	}
	g_App->SetInput(input);

	g_App->SetLoaderData(*pData);
	g_App->Open();
	g_App->Start();

	Util::String fullScenePath = pData->sSceneName;

	IndexT index = fullScenePath.FindCharIndex(':');
	if (InvalidIndex == index)
	{
		//为了兼容旧有配置。如果SceneName不是asset:xxxx的形式默认认为在scene:目录下。
		fullScenePath = "asset:";
		fullScenePath += pData->sSceneName;
	}

	//fullScenePath += pData->sSceneName;
	//g_App->OpenScene( fullScenePath );
	g_App->OpenScene( fullScenePath );
	return true;
}
//------------------------------------------------------------------------
bool WinWebUpdate()
{
	if (g_App->IsQuit())
	{		
		return false;
	}
	g_App->Run();
	return true;
}
//------------------------------------------------------------------------
bool WinWebCleanup()
{
	if ( NULL!=g_App )
	{
		g_App->Exit();
		n_delete( g_App );
		g_App = NULL;
		DemoPublishGameApplication::ShutDown();
	}

	return true;	
}
//------------------------------------------------------------------------
LRESULT WinInputMsg( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( NULL!=g_App )
	{
		const GPtr<Input::InputSource>& pInputSource = g_App->GetInputSource();
		if ( pInputSource )
		{
			return pInputSource.downcast<Win32Input::Win32InputWebWindowSource>()->OnWinProc( hWnd, uMsg, wParam, lParam );
		}

	}
	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}