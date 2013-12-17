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
#include "scriptfeature/inc/script_component.h"
#include "scriptfeature/inc/script_utility.h"
#include "foundation/core/rtti.h"
#include "appframework/gameapplication.h"
#include "appframework/scene.h"


using namespace Util;

namespace App
{
	void ICallReg_ScriptRuntime_Application( void );


	static mono_bool ICall_Application_OpenScene(MonoString* sceneResID)
	{
		String scence_name;
		Utility_MonoStringToCppString(sceneResID, scence_name);
		return Utility_MonoBool(GameApplication::Instance()->OpenScene(scence_name) );

	}

	static mono_bool ICall_Application_CloseScene(MonoString* sceneResID)
	{
		String scence_name;
		Utility_MonoStringToCppString(sceneResID, scence_name);

		return Utility_MonoBool( 
			GameApplication::Instance()->CloseScene(scence_name) );
	}

	static void ICall_Application_Quit()
	{
		return GameApplication::Instance()->Quit();		
	}

	static MonoObject* ICall_Application_GetCurrentScene()
	{		
		const GPtr<Scene>& pScene = GameApplication::Instance()->GetCurrentScene();
		if ( pScene.isvalid() )
		{
			return CppObjectToScriptObj<Scene>( *pScene );
		}
		else
		{
			return NULL;
		}
	}

	static MonoString* ICall_Application_GetAssetPath( void )
	{
		Util::String path = GameApplication::Instance()->GetResourceBaseDir();
		return Utility_NewMonoString( path );
	}

	static MonoString* ICall_Application_GetAppDicOnMobile( void )
	{
#if __ANDROID__||__OSX__	
		Util::String path = GameApplication::Instance()->GetAppDicOnMobile();
		return Utility_NewMonoString( path );
#else
		n_warning("No Implementaion\n");
		return NULL;
#endif
	}

	static float ICall_Application_GetDPIHeight( void )
	{
#if __ANDROID__
		return GameApplication::Instance()->GetDPIHeight();
#else
		return 0;
#endif
	}

	static float ICall_Application_GetDPIWidth( void )
	{
#if __ANDROID__
		return GameApplication::Instance()->GetDPIWidth();
#else
		return 0;
#endif
	}
}

#include "autogen/scriptbind_Application_register.h"