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
namespace App
{
	void ICallReg_ScriptGUI_Button();

	void ICall_setStateSelected(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		button->setStateSelected(c_iMonoBool_True == _value);
	}
	mono_bool ICall_getStateSelected(gconstpointer widget_ptr)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		return button->getStateSelected();
	}

	static void ICall_setModeImage(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		button->setModeImage(c_iMonoBool_True == _value);
	}

	static mono_bool ICall_getModeImage(gconstpointer widget_ptr)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		return button->getModeImage();
	}

	static void ICall_setImageResource(gconstpointer widget_ptr, MonoString* _name)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(_name, str);
		button->setImageResource(str);
	}

	static void ICall_setImageGroup(gconstpointer widget_ptr, MonoString* _name)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(_name, str);
		button->setImageGroup(str);
	}

	static void ICall_setImageName(gconstpointer widget_ptr, MonoString* _name)
	{
		MyGUI::Button* button = static_cast<MyGUI::Button*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(_name, str);
		button->setImageName(str);
	}


	void ICallReg_ScriptGUI_Button()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptGUI.Button::ICall_setStateSelected",				(void*)(&ICall_setStateSelected)}
			,{ "ScriptGUI.Button::ICall_getStateSelected",				(void*)(&ICall_getStateSelected)}

			,{ "ScriptGUI.Button::ICall_setModeImage",					(void*)(&ICall_setModeImage)}
			,{ "ScriptGUI.Button::ICall_getModeImage",					(void*)(&ICall_getModeImage)}
			,{ "ScriptGUI.Button::ICall_setImageResource",				(void*)(&ICall_setImageResource)}
			,{ "ScriptGUI.Button::ICall_setImageGroup",					(void*)(&ICall_setImageGroup)}
			,{ "ScriptGUI.Button::ICall_setImageName",					(void*)(&ICall_setImageName)}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}