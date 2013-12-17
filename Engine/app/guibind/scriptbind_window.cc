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
	void ICallReg_ScriptGUI_Window();

	static MyGUI::TextBox* ICall_getCaptionWidget(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		return window->getCaptionWidget();
	}


	static void ICall_setVisibleSmooth(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setVisibleSmooth(c_iMonoBool_True == _value);
	}


	static void ICall_destroySmooth(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->destroySmooth();
	}


	static void ICall_setAutoAlpha(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setAutoAlpha(c_iMonoBool_True == _value);
	}


	static mono_bool ICall_getAutoAlpha(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		return window->getAutoAlpha();
	}

	static void ICall_setMinSize(gconstpointer widget_ptr, MyGUI::IntSize& _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setMinSize(_value);
	}

	static void ICall_getMinSize(gconstpointer widget_ptr, MyGUI::IntSize& vlaue)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		vlaue = window->getMinSize();
	}

	static void ICall_setMaxSize(gconstpointer widget_ptr,  MyGUI::IntSize& _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setMaxSize(_value);
	}


	static void ICall_getMaxSize(gconstpointer widget_ptr, MyGUI::IntSize& vlaue)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		vlaue = window->getMaxSize();
	}


	static void ICall_setSnap(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setSnap(c_iMonoBool_True == _value);
	}


	static mono_bool ICall_getSnap(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		return window->getSnap();
	}


	static const MyGUI::IntCoord& ICall_getActionScale(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		return window->getActionScale();
	}


	static void ICall_setMovable(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		window->setMovable(c_iMonoBool_True == _value);
	}


	static mono_bool ICall_getMovable(gconstpointer widget_ptr)
	{
		MyGUI::Window* window = static_cast<MyGUI::Window*>(widget_ptr);
		return window->getMovable();
	}

	void ICallReg_ScriptGUI_Window()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			  { "ScriptGUI.Window::ICall_setVisibleSmooth",			(void*)&ICall_setVisibleSmooth}
			 ,{ "ScriptGUI.Window::ICall_getCaptionWidget",			(void*)&ICall_getCaptionWidget}
			 ,{ "ScriptGUI.Window::ICall_destroySmooth",			(void*)&ICall_destroySmooth}
			 ,{ "ScriptGUI.Window::ICall_setAutoAlpha",				(void*)&ICall_setAutoAlpha}
			 ,{ "ScriptGUI.Window::ICall_getAutoAlpha",				(void*)&ICall_getAutoAlpha}
			 ,{ "ScriptGUI.Window::ICall_setMinSize",				(void*)&ICall_setMinSize}
			 ,{ "ScriptGUI.Window::ICall_getMinSize",				(void*)&ICall_getMinSize}
			 ,{ "ScriptGUI.Window::ICall_setMaxSize",				(void*)&ICall_setMaxSize}
			 ,{ "ScriptGUI.Window::ICall_getMaxSize",				(void*)&ICall_getMaxSize}
			 ,{ "ScriptGUI.Window::ICall_setSnap",					(void*)&ICall_setSnap}
			 ,{ "ScriptGUI.Window::ICall_getSnap",					(void*)&ICall_getSnap}
			 ,{ "ScriptGUI.Window::ICall_getActionScale",			(void*)&ICall_getActionScale}
			 ,{ "ScriptGUI.Window::ICall_setMovable",				(void*)&ICall_setMovable}
			 ,{ "ScriptGUI.Window::ICall_getMovable",				(void*)&ICall_getMovable}

		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}