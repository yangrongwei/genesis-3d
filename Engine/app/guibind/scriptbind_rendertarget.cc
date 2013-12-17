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
#include "scriptfeature/inc/script_utility.h"
#include "guifeature/guiutility.h"
#include "graphicsystem/base/RenderToTexture.h"
#include "myguiplatforms/include/MyGUI_GenesisRTTexture.h"
namespace App
{
	using namespace MyGUI;
	void ICallReg_ScriptGUI_RenderTarget();

	
	static IRenderTarget* ICall_createFromScriptRuntimeRenderToTexture(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<Graphic::RenderToTexture> rtt( pMonoObj );
		GPtr<Graphic::RenderToTexture> tmpRTex = GPtr<Graphic::RenderToTexture>(rtt.GetCppObjPtr());
		IRenderTarget* target = new GenesisRTTexture(tmpRTex);
		return target;
	}
	static void ICall_release(gconstpointer rt_ptr)
	{
		MyGUI::IRenderTarget* rt = static_cast<MyGUI::IRenderTarget*>(rt_ptr);
		delete rt;
	}
	void ICallReg_ScriptGUI_RenderTarget()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptGUI.RenderTarget::ICall_createFromScriptRuntimeRenderToTexture",							(void*)&ICall_createFromScriptRuntimeRenderToTexture}
			,{ "ScriptGUI.RenderTarget::ICall_release",															(void*)&ICall_release}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}