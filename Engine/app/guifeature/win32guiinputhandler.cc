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
#if __WIN32__
#include "input/input_stdneb.h"
#include "guiinputhandler.h"
#include "input/inputserver.h"

#include "gui.h"
#include "myguiplatforms/include/MyGUI_GenesisInput.h"

namespace Input
{
	__ImplementClass(Input::Win32GuiInputHandler, 'WGIH', Input::InputHandler);

	using namespace Input;
	//------------------------------------------------------------------------
	Win32GuiInputHandler::Win32GuiInputHandler()
	{

	}
	//------------------------------------------------------------------------
	Win32GuiInputHandler::~Win32GuiInputHandler()
	{

	}
	//------------------------------------------------------------------------
	bool Win32GuiInputHandler::OnEvent( const Input::InputEvent& inputEvent )
	{

		MyGUI::GenesisInputManager* gui_input = MyGUI::GenesisInputManager::getInstancePtr();
		if (!gui_input)
		{
			return false;
		}
		static int mouse_z = 0;

		static bool left_press = false;
		static bool right_press = false;
		static bool middle_press = false;

		bool ret = false;
		switch (inputEvent.GetType())
		{
			// reset input handler if another one begins to capture
		case InputEvent::BeginKeyboardCapture:
			if (!this->IsCapturing())
			{
				this->OnReset();
			}
			break;

		case InputEvent::KeyDown:
			{
				ret |= gui_input->injectKeyPress(App::GUIServer::KeyCodeWJtoMyGUI(inputEvent.GetKey()), inputEvent.GetChar());
			}
			break;

		case InputEvent::KeyUp:
			{
				//gui_input->injectKeyRelease(App::GUIServer::KeyCodeWJtoMyGUI(inputEvent.GetKey()));
				ret |= gui_input->injectKeyRelease(App::GUIServer::KeyCodeWJtoMyGUI(inputEvent.GetKey()));
			}
			break;

		case InputEvent::MouseMove:
			{
				const Math::float2& pos_n = inputEvent.GetNormMousePos();
				if ( pos_n.x() < 0.0f || pos_n.x() > 1.0f || pos_n.y() < 0.0f || pos_n.y() > 1.0f)
				{
					break;
				}
				ret |= gui_input->injectMouseMove(pos_n.x(), pos_n.y(), mouse_z);
			}
			break;
		case InputEvent::MouseButtonDown:
			{
				InputMouseButton::Code mouse = inputEvent.GetMouseButton();
				const Math::float2&  pos = inputEvent.GetNormMousePos();
				if (InputMouseButton::LeftButton == mouse)// && (!left_press))
				{
					left_press = true;
					ret |= gui_input->injectMousePress(pos.x(), pos.y(), MyGUI::MouseButton::Left);
				}
				else if (InputMouseButton::RightButton == mouse)// && (!right_press))
				{
					right_press = true;
					ret |= gui_input->injectMousePress(pos.x(), pos.y(), MyGUI::MouseButton::Right);
				}
				else if (InputMouseButton::MiddleButton == mouse)// && (!middle_press))
				{
					middle_press = true;
					ret |= gui_input->injectMousePress(pos.x(), pos.y(), MyGUI::MouseButton::Middle);
				}
			}
			break;
		case InputEvent::MouseButtonUp:
			{
				InputMouseButton::Code mouse = inputEvent.GetMouseButton();
				const Math::float2&  pos = inputEvent.GetNormMousePos();
				if (InputMouseButton::LeftButton == mouse)// && left_press)
				{
					left_press = false;//ret |= 
					gui_input->injectMouseRelease(pos.x(), pos.y(), MyGUI::MouseButton::Left);
				}
				else if (InputMouseButton::RightButton == mouse)// && right_press)
				{
					right_press = false;//ret |= 
					gui_input->injectMouseRelease(pos.x(), pos.y(), MyGUI::MouseButton::Right);
				}
				else if (InputMouseButton::MiddleButton == mouse)// && middle_press)
				{
					middle_press = false;//ret |= 
					gui_input->injectMouseRelease(pos.x(), pos.y(), MyGUI::MouseButton::Middle);
				}
			}
			break;
		case InputEvent::MouseWheelForward:
			{
				mouse_z += 120;
				const Math::float2&  pos = inputEvent.GetNormMousePos();
				ret |= gui_input->injectMouseMove(pos.x(), pos.y(), mouse_z);
			}
			break;
		case InputEvent::MouseWheelBackward:
			{
				mouse_z -= 120;
				const Math::float2&  pos = inputEvent.GetNormMousePos();
				ret |= gui_input->injectMouseMove(pos.x(), pos.y(), mouse_z);
			}
			break;
		case InputEvent::Character:
			{
				if (inputEvent.GetChar() > 255)//255, max 8bit
				{
					ret |= gui_input->injectKeyPress(MyGUI::KeyCode::None, (MyGUI::Char)inputEvent.GetChar());
				}
			}
			break;
		//case InputEvent::IMECharacter:
		//	{
		//		ret |= gui_input->injectKeyPress(MyGUI::KeyCode::None, (MyGUI::Char)inputEvent.GetChar());
		//		break;
		//	}
		case InputEvent::AppLoseFocus:
			{
				gui_input->resetMouseCaptureWidget();
			}
			break;
		default:
			break;
		}

		return !ret;
	}

}
#endif