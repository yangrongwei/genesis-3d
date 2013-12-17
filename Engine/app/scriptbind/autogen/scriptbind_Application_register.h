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

namespace App
{ 
    static mono_bool ICall_Application_OpenScene(MonoString* sceneResID);

    static mono_bool ICall_Application_CloseScene(MonoString* sceneResID);

    static void ICall_Application_Quit( void );

    static  MonoObject* ICall_Application_GetCurrentScene( void );

	static  MonoString* ICall_Application_GetAssetPath( void );

	static MonoString* ICall_Application_GetAppDicOnMobile( void );

	static float ICall_Application_GetDPIHeight( void );

	static float ICall_Application_GetDPIWidth( void );

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_Application( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.Application::ICall_Application_OpenScene",                            (void*)&ICall_Application_OpenScene},
             { "ScriptRuntime.Application::ICall_Application_CloseScene",                           (void*)&ICall_Application_CloseScene},
             { "ScriptRuntime.Application::ICall_Application_Quit",                                 (void*)&ICall_Application_Quit},
             { "ScriptRuntime.Application::ICall_Application_GetCurrentScene",                      (void*)&ICall_Application_GetCurrentScene},
			 { "ScriptRuntime.Application::ICall_Application_GetAssetPath",							(void*)&ICall_Application_GetAssetPath},
			 { "ScriptRuntime.Application::ICall_Application_GetAppDicOnMobile",					(void*)&ICall_Application_GetAppDicOnMobile},
			 { "ScriptRuntime.Application::ICall_Application_GetDPIHeight",							(void*)&ICall_Application_GetDPIHeight},
			 { "ScriptRuntime.Application::ICall_Application_GetDPIWidth",							(void*)&ICall_Application_GetDPIWidth},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
