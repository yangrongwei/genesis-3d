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
#include "guifeature/scriptgui.h"
#include "graphicsystem/GraphicSystem.h"
namespace App
{
	void ICallReg_ScriptGUI_GUI( void );
	
	static gconstpointer ICall_loadLayout(gconstpointer parent, MonoString* file_name)
	{
		std::string str;
		GuiUtility::MonoStringToStdString(file_name, str);

		MyGUI::Widget* widget = ScriptGui::loadLayout(static_cast<MyGUI::Widget*>(parent), str);
		return static_cast<gconstpointer>(widget);
	}
	static void ICall_destroyWidget(gconstpointer ptr)
	{
		ScriptGui::destroyWidget(static_cast<MyGUI::Widget*>(ptr));
	}
	static gconstpointer ICall_findWidget(gconstpointer parent, MonoString* widget_name)
	{
		n_assert(NULL != parent);
		MyGUI::Widget* parent_widget = static_cast<MyGUI::Widget*>(parent);
		std::string str;
		GuiUtility::MonoStringToStdString(widget_name, str);

		MyGUI::Widget* ret = ScriptGui::findWidget(parent_widget, str);
		return static_cast<gconstpointer>(ret);
	}

	static void ICall_getScreenSize(MyGUI::IntSize& value)
	{
		value = ScriptGui::getScreenSize();
	}

	mono_bool ICall_tickEvent(mono_bool start)
	{
		return (mono_bool)GUIServer::Instance()->StartTick(1 == start);
	} 

	void ICall_setResolution(const MyGUI::IntSize& size)
	{
		ScriptGui::setResolution(size);
	}

	void ICall_getResolution(MyGUI::IntSize& size)
	{
		size = ScriptGui::getResolution();
	}

	mono_bool ICall_autoResolutionWidth()
	{
		return ScriptGui::autoResolutionWidth() ? c_iMonoBool_True : c_iMonoBool_False;
	}

	mono_bool ICall_autoResolutionHeight()
	{
		return ScriptGui::autoResolutionHeight() ? c_iMonoBool_True : c_iMonoBool_False;
	}


	void ICallReg_ScriptGUI_GUI()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = 
			{{ "ScriptGUI.GUI::ICall_loadLayout",					(void*)&ICall_loadLayout}
			,{ "ScriptGUI.GUI::ICall_destroyWidget",				(void*)&ICall_destroyWidget}
			,{ "ScriptGUI.GUI::ICall_findWidget",					(void*)&ICall_findWidget}
			,{ "ScriptGUI.GUI::ICall_getScreenSize",				(void*)&ICall_getScreenSize}
			,{ "ScriptGUI.GUI::ICall_setResolution",				(void*)&ICall_setResolution}
			,{ "ScriptGUI.GUI::ICall_getResolution",				(void*)&ICall_getResolution}
			,{ "ScriptGUI.GUI::ICall_autoResolutionWidth",			(void*)&ICall_autoResolutionWidth}
			,{ "ScriptGUI.GUI::ICall_autoResolutionHeight",			(void*)&ICall_autoResolutionHeight}

			,{ "ScriptGUI.GUIRoot::ICall_tickEvent",				(void*)&ICall_tickEvent}
			};
	
		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}