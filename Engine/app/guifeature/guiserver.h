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
#ifndef __guiserver_H__
#define __guiserver_H__

#include "addons/myguiengine/include/MyGUI_Gui.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/string.h"
#include "input/base/inputkeyboardbase.h"
#include "input/base/inputmousebase.h"
#include "guiroot.h"
#include "guievent.h"
#include "foundation/delegates/delegatetype.h"


#define GUI_ROOT_CONFIG "gui_core.xml"
namespace MyGUI
{
	class GenesisPlatform;
}

namespace App
{
	//typedef MyGUI::delegates::CMultiDelegate1<void*> EventHandle_BeforeDrawVoid;

	typedef Delegates::delegates::CMultiDelegate1<void*> EventHandle_BeforeDrawVoid;

	class GUIServer : public Core::RefCounted
	{
		__DeclareClass(GUIServer);
		__DeclareImageSingleton(GUIServer);
	public:
		virtual ~GUIServer();
		void SetCoreFile(const char* core);
		void SetEngineDir(const Util::String& dir);
		void SetCoreFile(const Util::String& core = GUI_ROOT_CONFIG);
		bool Open();
		bool IsOpen();
		void Close();
		void OnWindowResized();
		void OnDeviceReseted();

		MyGUI::Gui* GetGui() const;	
		GuiEvent& GetGuiEvent();

		void InitGuiRootScript();
		bool StartTick(bool start);

		bool GetVisible();
		void SetVisible(bool visible);

		EventHandle_BeforeDrawVoid eventBeforeDrawUI;

		static MyGUI::KeyCode KeyCodeWJtoMyGUI(Input::InputKey::Code key);

	private:
		MyGUI::GenesisPlatform* GetPlatform() const;
		void _initMyGUI();
		void _initScript();
		static void _beforeDraw();
		static void _drawUI();

		MyGUI::Gui* m_gui;
		MyGUI::GenesisPlatform* m_platform;
		bool  m_visible;

		Util::String m_coreFile;			
		Util::String m_engineDir;			
		GuiRoot	m_guiRoot;					//reference of a c# object.
		GuiEvent m_guiEvent;				//used for event between c++ and c#.

		GUIServer();

	};
	inline MyGUI::Gui* GUIServer::GetGui() const
	{
		return m_gui;
	}
	inline MyGUI::GenesisPlatform* GUIServer::GetPlatform() const
	{
		return m_platform;
	}
	inline GuiEvent& GUIServer::GetGuiEvent()
	{
		return m_guiEvent;
	}
	inline bool GUIServer::GetVisible()
	{
		return m_visible;
	}
	inline void GUIServer::SetVisible(bool visible)
	{
		m_visible = visible;
	}
}

#endif //__guiserver_H__