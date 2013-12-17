
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
#include "guiserver.h"
#include "graphicsystem/GraphicSystem.h"
#include "addons/myguiplatforms/include/MyGUI_GenesisPlatform.h"
#include "guifeature/gui.h"
#include "guiroot.h"

#include "foundation/io/ioserver.h"
namespace App
{
	__ImplementClass(App::GUIServer, 'GUIS', Core::RefCounted);

	__ImplementImageSingleton(App::GUIServer);

	using namespace MyGUI;

	Util::String g_uiPath = "asset:UIMedia/";


	GUIServer::GUIServer()
		:m_gui(NULL)
		,m_platform(NULL)
		,m_visible(true)
	{
		__ConstructImageSingleton;
	}

	GUIServer::~GUIServer()
	{
		Close();
		__DestructImageSingleton;
	}

	bool GUIServer::IsOpen()
	{
		return (NULL != m_platform) && (NULL != m_gui);
	}

	void GUIServer::SetCoreFile(const char* core)
	{
		m_coreFile = core;
	}

	void GUIServer::SetEngineDir(const Util::String& dir)
	{
		m_engineDir = dir;
	}

	bool GUIServer::Open()
	{
		Util::String core_file = g_uiPath + m_coreFile;
		if(IO::IoServer::Instance()->FileExists(Util::StringAtom(core_file)))
		{
			_initMyGUI();
			_initScript();
			return true;
		}
		return false;

	}

	void GUIServer::Close()
	{
		if (m_gui)
		{
			m_gui->shutdown();
			n_delete(m_gui);
			m_gui = NULL;
		}

		if (m_platform)
		{
			m_platform->shutdown();
			n_delete(m_platform);
			m_platform = NULL;
		}
		Graphic::GraphicSystem::Instance()->SetUIDrawCallBack(NULL);
	}

	void GUIServer::OnWindowResized()
	{
		n_assert(IsOpen());
		m_platform->getRenderManagerPtr()->windowResized();
		m_guiRoot.WinSizeChange();
	}

	void GUIServer::OnDeviceReseted()
	{
		n_assert(IsOpen());
		m_platform->getRenderManagerPtr()->deviceReseted();
	}

	void GUIServer::InitGuiRootScript()
	{
		m_guiRoot.InitGuiScript();
	}

	bool GUIServer::StartTick(bool start)
	{
		//也可以注册到，MyGUI::Gui::getInstance().eventFrameStart
		//不过那个计时器是独立的和我们的引擎的计时器无关。
		if (start)
		{
			eventBeforeDrawUI += Delegates::newDelegate(&m_guiRoot, &GuiRoot::Tick);
		}
		else
		{
			eventBeforeDrawUI -= Delegates::newDelegate(&m_guiRoot, &GuiRoot::Tick);
		}
		return true;
	}

	MyGUI::KeyCode GUIServer::KeyCodeWJtoMyGUI(Input::InputKey::Code key)
	{
		// the input type match below , some of them are commented
		// because we can't match the same in mygui, If anyone needed, recommented is OK
		MyGUI::KeyCode mygui_key = MyGUI::KeyCode::None;
		switch (key)
		{
		case Input::InputKey::Back: mygui_key = MyGUI::KeyCode::Backspace; break;
		case Input::InputKey::Tab: mygui_key = MyGUI::KeyCode::Tab; break;
			//case Input::InputKey::Clear: mygui_key = MyGUI::KeyCode::clear; break;
		case Input::InputKey::Return: mygui_key = MyGUI::KeyCode::Return; break;
		case Input::InputKey::Shift: mygui_key = MyGUI::KeyCode::LeftShift; break;//??????????????
		case Input::InputKey::Control: mygui_key = MyGUI::KeyCode::LeftControl; break;//??????????????
			//case Input::InputKey::Menu: mygui_key = MyGUI::KeyCode::AppMenu; break;//??????????????
		case Input::InputKey::Pause: mygui_key = MyGUI::KeyCode::Pause; break;
		case Input::InputKey::Capital: mygui_key = MyGUI::KeyCode::Capital; break;
		case Input::InputKey::Escape: mygui_key = MyGUI::KeyCode::Escape; break;
		case Input::InputKey::Convert: mygui_key = MyGUI::KeyCode::Convert; break;
		case Input::InputKey::NonConvert: mygui_key = MyGUI::KeyCode::NoConvert; break;
			//case Input::InputKey::Accept: mygui_key = MyGUI::KeyCode::acce; break;
			//case Input::InputKey::ModeChange: mygui_key = MyGUI::KeyCode::; break;
		case Input::InputKey::Space: mygui_key = MyGUI::KeyCode::Space; break;
			//case Input::InputKey::Prior: mygui_key = MyGUI::KeyCode::; break;
		case Input::InputKey::Next: mygui_key = MyGUI::KeyCode::NextTrack; break;
		case Input::InputKey::End: mygui_key = MyGUI::KeyCode::End; break;
		case Input::InputKey::Home: mygui_key = MyGUI::KeyCode::Home; break;
		case Input::InputKey::Left: mygui_key = MyGUI::KeyCode::ArrowLeft; break;
		case Input::InputKey::Right: mygui_key = MyGUI::KeyCode::ArrowRight; break;
		case Input::InputKey::Up: mygui_key = MyGUI::KeyCode::ArrowUp; break;
		case Input::InputKey::Down: mygui_key = MyGUI::KeyCode::ArrowDown; break;
			//case Input::InputKey::Select: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::Print: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::Execute: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::Snapshot: mygui_key = MyGUI::KeyCode:; break;
		case Input::InputKey::Insert: mygui_key = MyGUI::KeyCode::Insert; break;
		case Input::InputKey::Delete: mygui_key = MyGUI::KeyCode::Delete; break;
			//case Input::InputKey::Help: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::LeftWindows: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::RightWindows: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::Apps: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::Sleep: mygui_key = MyGUI::KeyCode:; break;
		case Input::InputKey::NumPad0: mygui_key = MyGUI::KeyCode::Numpad0; break;
		case Input::InputKey::NumPad1: mygui_key = MyGUI::KeyCode::Numpad1; break;
		case Input::InputKey::NumPad2: mygui_key = MyGUI::KeyCode::Numpad2; break;
		case Input::InputKey::NumPad3: mygui_key = MyGUI::KeyCode::Numpad3; break;
		case Input::InputKey::NumPad4: mygui_key = MyGUI::KeyCode::Numpad4; break;
		case Input::InputKey::NumPad5: mygui_key = MyGUI::KeyCode::Numpad5; break;
		case Input::InputKey::NumPad6: mygui_key = MyGUI::KeyCode::Numpad6; break;
		case Input::InputKey::NumPad7: mygui_key = MyGUI::KeyCode::Numpad7; break;
		case Input::InputKey::NumPad8: mygui_key = MyGUI::KeyCode::Numpad8; break;
		case Input::InputKey::NumPad9: mygui_key = MyGUI::KeyCode::Numpad9; break;
		case Input::InputKey::Multiply: mygui_key = MyGUI::KeyCode::Multiply; break;
		case Input::InputKey::Add: mygui_key = MyGUI::KeyCode::Add; break;
		case Input::InputKey::Subtract: mygui_key = MyGUI::KeyCode::Subtract; break;
			//case Input::InputKey::Separator: mygui_key = MyGUI::KeyCode::separator; break;
		case Input::InputKey::Decimal: mygui_key = MyGUI::KeyCode::Decimal; break;
		case Input::InputKey::Divide: mygui_key = MyGUI::KeyCode::Divide; break;
		case Input::InputKey::F1: mygui_key = MyGUI::KeyCode::F1; break;
		case Input::InputKey::F2: mygui_key = MyGUI::KeyCode::F2; break;
		case Input::InputKey::F3: mygui_key = MyGUI::KeyCode::F3; break;
		case Input::InputKey::F4: mygui_key = MyGUI::KeyCode::F4; break;
		case Input::InputKey::F5: mygui_key = MyGUI::KeyCode::F5; break;
		case Input::InputKey::F6: mygui_key = MyGUI::KeyCode::F6; break;
		case Input::InputKey::F7: mygui_key = MyGUI::KeyCode::F7; break;
		case Input::InputKey::F8: mygui_key = MyGUI::KeyCode::F8; break;
		case Input::InputKey::F9: mygui_key = MyGUI::KeyCode::F9; break;
		case Input::InputKey::F10: mygui_key = MyGUI::KeyCode::F10; break;
		case Input::InputKey::F11: mygui_key = MyGUI::KeyCode::F11; break;
		case Input::InputKey::F12: mygui_key = MyGUI::KeyCode::F12; break;
		case Input::InputKey::F13: mygui_key = MyGUI::KeyCode::F13; break;
		case Input::InputKey::F14: mygui_key = MyGUI::KeyCode::F14; break;
		case Input::InputKey::F15: mygui_key = MyGUI::KeyCode::F15; break;
			//case Input::InputKey::F16: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F17: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F18: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F19: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F20: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F21: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F22: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F23: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::F24: mygui_key = MyGUI::KeyCode:; break;
		case Input::InputKey::NumLock: mygui_key = MyGUI::KeyCode::NumLock; break;
			//case Input::InputKey::Scroll: mygui_key = MyGUI::KeyCode::Scroll; break;
		case Input::InputKey::Semicolon: mygui_key = MyGUI::KeyCode::Semicolon; break;
		case Input::InputKey::Slash: mygui_key = MyGUI::KeyCode::Slash; break;
			//case Input::InputKey::Tilde: mygui_key = MyGUI::KeyCode::tild; break;
		case Input::InputKey::LeftBracket: mygui_key = MyGUI::KeyCode::LeftBracket; break;
		case Input::InputKey::RightBracket: mygui_key = MyGUI::KeyCode::RightBracket; break;
		case Input::InputKey::BackSlash: mygui_key = MyGUI::KeyCode::Backslash; break;
			//case Input::InputKey::Quote: mygui_key = MyGUI::KeyCode::; break;
		case Input::InputKey::Comma: mygui_key = MyGUI::KeyCode::Comma; break;
			//case Input::InputKey::Underbar: mygui_key = MyGUI::KeyCode::; break;
		case Input::InputKey::Period: mygui_key = MyGUI::KeyCode::Period; break;
			//case Input::InputKey::Equality: mygui_key = MyGUI::KeyCode::equal; break;
		case Input::InputKey::LeftShift: mygui_key = MyGUI::KeyCode::LeftShift; break;
		case Input::InputKey::RightShift: mygui_key = MyGUI::KeyCode::RightShift; break;
		case Input::InputKey::LeftControl: mygui_key = MyGUI::KeyCode::LeftControl; break;
		case Input::InputKey::RightControl: mygui_key = MyGUI::KeyCode::RightControl; break;
			//case Input::InputKey::LeftMenu: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::RightMenu: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserBack: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::BrowserForward: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserRefresh: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserStop: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserSearch: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserFavorites: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::BrowserHome: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::VolumeMute: mygui_key = MyGUI::KeyCode::; break;
		case Input::InputKey::VolumeDown: mygui_key = MyGUI::KeyCode::VolumeDown; break;
		case Input::InputKey::VolumeUp: mygui_key = MyGUI::KeyCode::VolumeUp; break;
			//case Input::InputKey::MediaNextTrack: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::MediaPrevTrack: mygui_key = MyGUI::KeyCode:; break;
		case Input::InputKey::MediaStop: mygui_key = MyGUI::KeyCode::MediaStop; break;
		case Input::InputKey::MediaPlayPause: mygui_key = MyGUI::KeyCode::PlayPause; break;//??????????????
			//case Input::InputKey::LaunchMail: mygui_key = MyGUI::KeyCode::; break;
			//case Input::InputKey::LaunchMediaSelect: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::LaunchApp1: mygui_key = MyGUI::KeyCode:; break;
			//case Input::InputKey::LaunchApp2: mygui_key = MyGUI::KeyCode:; break;
		case Input::InputKey::Key0: mygui_key = MyGUI::KeyCode::Zero; break;
		case Input::InputKey::Key1: mygui_key = MyGUI::KeyCode::One; break;
		case Input::InputKey::Key2: mygui_key = MyGUI::KeyCode::Two; break;
		case Input::InputKey::Key3: mygui_key = MyGUI::KeyCode::Three; break;
		case Input::InputKey::Key4: mygui_key = MyGUI::KeyCode::Four; break;
		case Input::InputKey::Key5: mygui_key = MyGUI::KeyCode::Five; break;
		case Input::InputKey::Key6: mygui_key = MyGUI::KeyCode::Six; break;
		case Input::InputKey::Key7: mygui_key = MyGUI::KeyCode::Seven; break;
		case Input::InputKey::Key8: mygui_key = MyGUI::KeyCode::Eight; break;
		case Input::InputKey::Key9: mygui_key = MyGUI::KeyCode::Nine; break;
		case Input::InputKey::A: mygui_key = MyGUI::KeyCode::A; break;
		case Input::InputKey::B: mygui_key = MyGUI::KeyCode::B; break;
		case Input::InputKey::C: mygui_key = MyGUI::KeyCode::C; break;
		case Input::InputKey::D: mygui_key = MyGUI::KeyCode::D; break;
		case Input::InputKey::E: mygui_key = MyGUI::KeyCode::E; break;
		case Input::InputKey::F: mygui_key = MyGUI::KeyCode::F; break;
		case Input::InputKey::G: mygui_key = MyGUI::KeyCode::G; break;
		case Input::InputKey::H: mygui_key = MyGUI::KeyCode::H; break;
		case Input::InputKey::I: mygui_key = MyGUI::KeyCode::I; break;
		case Input::InputKey::J: mygui_key = MyGUI::KeyCode::J; break;
		case Input::InputKey::K: mygui_key = MyGUI::KeyCode::K; break;
		case Input::InputKey::L: mygui_key = MyGUI::KeyCode::L; break;
		case Input::InputKey::M: mygui_key = MyGUI::KeyCode::M; break;
		case Input::InputKey::N: mygui_key = MyGUI::KeyCode::N; break;
		case Input::InputKey::O: mygui_key = MyGUI::KeyCode::O; break;
		case Input::InputKey::P: mygui_key = MyGUI::KeyCode::P; break;
		case Input::InputKey::Q: mygui_key = MyGUI::KeyCode::Q; break;
		case Input::InputKey::R: mygui_key = MyGUI::KeyCode::R; break;
		case Input::InputKey::S: mygui_key = MyGUI::KeyCode::S; break;
		case Input::InputKey::T: mygui_key = MyGUI::KeyCode::T; break;
		case Input::InputKey::U: mygui_key = MyGUI::KeyCode::U; break;
		case Input::InputKey::V: mygui_key = MyGUI::KeyCode::V; break;
		case Input::InputKey::W: mygui_key = MyGUI::KeyCode::W; break;
		case Input::InputKey::X: mygui_key = MyGUI::KeyCode::X; break;
		case Input::InputKey::Y: mygui_key = MyGUI::KeyCode::Y; break;
		case Input::InputKey::Z: mygui_key = MyGUI::KeyCode::Z; break;

		default: mygui_key = MyGUI::KeyCode::None; break;
		}		

		return mygui_key;
	}			
	

	void GUIServer::_initMyGUI()
	{
		n_assert(NULL == m_platform);
		n_assert(NULL == m_gui);
		m_platform = n_new(GenesisPlatform);
		GenesisTexture::SetResourcePath(g_uiPath);
		GenesisRenderManager::SetResourcePath(g_uiPath);
		GenesisDataManager::getInstance().SetResourcePath(g_uiPath);
		std::string uilog;
#ifdef __WIN32__
		if (m_engineDir.Length())
		{
			uilog = m_engineDir.AsCharPtr();
			uilog += "\\gui.log";
		}
#endif
		m_platform->initialise("General", uilog);		

		m_gui = n_new(Gui);
		m_gui->initialise(m_coreFile.AsCharPtr());
		Graphic::GraphicSystem::Instance()->SetUIDrawCallBack(_drawUI);
		Graphic::GraphicSystem::Instance()->SetUIBeforeDrawCallBack(_beforeDraw);
		MyGUI::PointerManager::getInstance().setVisible(false);
	}
	void GUIServer::_initScript()
	{
		m_guiRoot.Init();
		m_guiEvent.Init();
	}

	void GUIServer::_drawUI()
	{			 
		if (Instance()->GetVisible())
		{
			Instance()->GetPlatform()->getRenderManagerPtr()->renderGUI();
		}
	}
	void GUIServer::_beforeDraw()
	{
		if (HasInstance())
		{
			Instance()->eventBeforeDrawUI((void*)Instance());
		}

	}
}