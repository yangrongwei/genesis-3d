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
#include "guifeature/guievent.h"
#include "guifeature/gui.h"

#include "scriptfeature/script_general_manager.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_fwd_decl.h"
namespace App
{
	const int GuiEvent::ParamCount = 2;
	const Util::String& GuiEvent::EventMethodName = "onEvent";
	const Util::String& GuiEvent::EventClassName = "Event";						//ui全局的类名
	const Util::String& GuiEvent::EventNamespace = "ScriptGUI";					//所在的名字空间


	GuiEvent::GuiEvent()
		:m_method(NULL)
	{

	}
	GuiEvent::~GuiEvent()
	{

	}
	void GuiEvent::Init()
	{
		ScriptGeneralManager* manager = ScriptGeneralManager::Instance();
		if (manager)
		{
			MonoClass* mono_class = manager->GetMonoClassByName(EventClassName, EventNamespace, s_csScriptGUILibraryName);

			n_assert(NULL != mono_class);	
			m_method = mono_class_get_method_from_name( mono_class, EventMethodName.AsCharPtr(), ParamCount);
				
		}
	}
	void GuiEvent::OnEvent(MyGUI::Widget* widget, EventArg* arg)
	{
		static void* params[ParamCount] = {0};
		
		MonoObject** sender = widget->getUserData<MonoObject*>(false);
		params[0] = (void*)(*sender);
		params[1] = (void*)(&arg);
		if (m_method)
		{
			Utility_MonoRuntimeInvoke( m_method, NULL, (void**)&params );	
		}

	}

}