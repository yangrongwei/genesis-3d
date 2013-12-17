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
#if WIN32


#include "input/input_stdneb.h"
#include "input/win32/win32inputwebwindowsource.h"
#include "input/inputserver.h"

namespace Win32Input
{
	using namespace Input;

	__ImplementClass(Win32Input::Win32InputWebWindowSource, 'WWWI', Input::InputSource );

	//------------------------------------------------------------------------
	Win32InputWebWindowSource::Win32InputWebWindowSource()
		:mWnd(0)
	{
		mMousePostion.set(0.0, 0.0);
	}
	//------------------------------------------------------------------------
	Win32InputWebWindowSource::~Win32InputWebWindowSource()
	{

	}
	//------------------------------------------------------------------------
	// @ InputSource::Open()
	void Win32InputWebWindowSource::Open(const GPtr<Input::InputServerBase>& inputServer)
	{
		Super::Open(inputServer);
	}
	//------------------------------------------------------------------------
	// @ InputSource::Close()
	void Win32InputWebWindowSource::Close()
	{
		mWnd = 0;
		Super::Close();
	}
	void Win32InputWebWindowSource::BeginFrame(void)
	{
		n_assert(mInputServer.isvalid());
		SizeT count = mInputEventList.Size();
		for ( IndexT i = 0; i < count; ++i )
		{
			mInputServer->PutEvent( mInputEventList[i] );
		}
		mInputEventList.Clear();

	}
	//------------------------------------------------------------------------
	LRESULT Win32InputWebWindowSource::OnWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		InputEvent inputEvent;

		switch (uMsg)
		{
		case WM_NCCALCSIZE:
			break;

		case WM_ERASEBKGND:
			// prevent Windows from erasing the background
			return 1;

		case WM_SIZE:
			{
				// inform input server about focus change
				if ((SIZE_MAXHIDE == wParam) || (SIZE_MINIMIZED == wParam))
				{
					inputEvent.SetType(InputEvent::AppLoseFocus);
					mInputEventList.Append( inputEvent );
					//XInputEnable(false);
					ReleaseCapture();
				}
				else
				{
					inputEvent.SetType(InputEvent::AppObtainFocus);
					mInputEventList.Append(inputEvent);
					//XInputEnable(true);
					ReleaseCapture();
				}

				// manually change window size in child mode
				//if (mWin32Device->parentWindow)
				//{
				//	WORD newWidth = LOWORD(lParam);
				//	WORD newHeight = HIWORD(lParam);
				//	MoveWindow(hWnd, 0, 0, newWidth, newHeight, TRUE);
				//}
			}
			break;

		case WM_SETCURSOR:
			break;

		case WM_PAINT:
			break;

		case WM_SETFOCUS:
			inputEvent.SetType(InputEvent::AppObtainFocus);
			mInputEventList.Append(inputEvent);
			//XInputEnable(true);
			ReleaseCapture();
			return 0;
			break;

		case WM_KILLFOCUS:
			inputEvent.SetType(InputEvent::AppLoseFocus);
			mInputEventList.Append(inputEvent);
			//XInputEnable(false);
			ReleaseCapture();
			return 0;
			break;

		case WM_CLOSE:
			mInputServer->SetQuitRequested(true);
			break;

		case WM_COMMAND:
			//if (LOWORD(wParam) == Win32DisplayDevice::AccelToggleFullscreen)
			//{
			//	mWin32Device->NotifyEventHandlers(DisplayEvent(DisplayEvent::ToggleFullscreenWindowed));
			//}
			break;

		case WM_KEYDOWN:
			{
				Input::InputKey::Code keyCode = TranslateKeyCode(wParam);
				if (Input::InputKey::InvalidKey != keyCode)
				{
					//inputEvent.SetType(InputEvent::KeyDown);
					//inputEvent.SetKey(keyCode);
					//mInputEventList.Append(inputEvent);
					SetKeyDown(mInputEventList, inputEvent, keyCode, (void*)&wParam);
					return 0;
				}
			}
			break;

		case WM_KEYUP:
			{
				Input::InputKey::Code keyCode = TranslateKeyCode(wParam);
				if (Input::InputKey::InvalidKey != keyCode)
				{
				//	inputEvent.SetType(InputEvent::KeyUp);
				//	inputEvent.SetKey(keyCode);
				//	mInputEventList.Append(inputEvent);
					SetKeyUp(mInputEventList, inputEvent,  keyCode);
					return 0;
				}
			}
			break;

		case WM_CHAR:
			{
				Input::Char chr = (Input::Char) wParam;
				//inputEvent.SetType(InputEvent::Character);
				//inputEvent.SetChar(chr);
				//mInputEventList.Append(inputEvent);
				SetChar(mInputEventList, inputEvent, chr);
				return 0;
			}
			break;

		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			if(OnMouseButton(uMsg, lParam))
			{
				return 0;
			}			
			break;

		case WM_MOUSEMOVE:
			if(OnMouseMove(lParam))
			{
				return 0;
			}			
			break;

		case WM_MOUSEWHEEL:
			if (OnMouseWheel(wParam))
			{
				return 0;
			}				
			break;
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	//------------------------------------------------------------------------
	bool
	Win32InputWebWindowSource::OnMouseButton(UINT uMsg, LPARAM lParam)
	{
		Math::float2 absMousePos = ComputeAbsMousePos(lParam);
		Math::float2 normMousePos = ComputeNormMousePos(absMousePos);

		InputEvent inputEvent;
		inputEvent.SetAbsMousePos( absMousePos );
		inputEvent.SetNormMousePos( normMousePos );

		//mouseMove(absMousePos);

		switch (uMsg)
		{
		case WM_LBUTTONDBLCLK:
			inputEvent.SetType(InputEvent::MouseButtonDoubleClick);
			inputEvent.SetMouseButton(Input::InputMouseButton::LeftButton);
			mInputEventList.Append(inputEvent);
			return true;
			break;

		case WM_RBUTTONDBLCLK:
			inputEvent.SetType(InputEvent::MouseButtonDoubleClick);
			inputEvent.SetMouseButton(Input::InputMouseButton::RightButton);
			mInputEventList.Append(inputEvent);
			return true;
			break;

		case WM_MBUTTONDBLCLK:
			inputEvent.SetType(InputEvent::MouseButtonDoubleClick);
			inputEvent.SetMouseButton(Input::InputMouseButton::MiddleButton);
			mInputEventList.Append(inputEvent);
			return true;
			break;

		case WM_LBUTTONDOWN:
			inputEvent.SetType(InputEvent::MouseButtonDown);
			inputEvent.SetMouseButton(Input::InputMouseButton::LeftButton);
			mInputEventList.Append(inputEvent);	
			if ( mWnd )
			{
				SetCapture( mWnd );
			}
			return true;
			break;

		case WM_RBUTTONDOWN:
			inputEvent.SetType(InputEvent::MouseButtonDown);
			inputEvent.SetMouseButton(Input::InputMouseButton::RightButton);
			mInputEventList.Append(inputEvent);
			if ( mWnd )
			{
				SetCapture( mWnd );
			}
			return true;
			break;

		case WM_MBUTTONDOWN:
			inputEvent.SetType(InputEvent::MouseButtonDown);
			inputEvent.SetMouseButton(Input::InputMouseButton::MiddleButton);
			mInputEventList.Append(inputEvent);

			if ( mWnd )
			{
				SetCapture( mWnd );
			}
			return true;
			break;

		case WM_LBUTTONUP:
			inputEvent.SetType(InputEvent::MouseButtonUp);
			inputEvent.SetMouseButton(Input::InputMouseButton::LeftButton);
			mInputEventList.Append(inputEvent);
			ReleaseCapture();
			return true;
			break;

		case WM_RBUTTONUP:
			inputEvent.SetType(InputEvent::MouseButtonUp);
			inputEvent.SetMouseButton(Input::InputMouseButton::RightButton);
			mInputEventList.Append(inputEvent);
			ReleaseCapture();
			return true;
			break;

		case WM_MBUTTONUP:
			inputEvent.SetType(InputEvent::MouseButtonUp);
			inputEvent.SetMouseButton(Input::InputMouseButton::MiddleButton);
			mInputEventList.Append(inputEvent);
			ReleaseCapture();
			return true;
			break;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
	Win32InputWebWindowSource::OnMouseMove(LPARAM lParam)
	{
		Math::float2 absMousePos = this->ComputeAbsMousePos(lParam);
		Math::float2 normMousePos = this->ComputeNormMousePos(absMousePos);

		InputEvent inputEvent;
		inputEvent.SetType(InputEvent::MouseMove);
		inputEvent.SetAbsMousePos( absMousePos );
		inputEvent.SetNormMousePos( normMousePos );
		mInputEventList.Append(inputEvent);

		mouseMove(absMousePos);

		return true;
	}
	//------------------------------------------------------------------------
	void
	Win32InputWebWindowSource::mouseMove(const Math::float2& absMousePos)
	{
		Math::float2 mousemove = absMousePos - mMousePostion; 

		mMousePostion = absMousePos;

		n_assert(mInputServer.isvalid() && mInputServer->GetRtti()->IsDerivedFrom( Win32InputServer::RTTI ) );
		GPtr<Win32InputServer> win32InputServer = mInputServer.downcast<Win32InputServer>();
		n_assert( win32InputServer.isvalid() );

		win32InputServer->SetMouseMovement( mousemove );
	}
	//------------------------------------------------------------------------
	bool 
	Win32InputWebWindowSource::OnMouseWheel(WPARAM wParam)
	{
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (zDelta > 0)
		{
			InputEvent inputEvent;
			inputEvent.SetType(InputEvent::MouseWheelForward);
			mInputEventList.Append(inputEvent);
		}
		else
		{
			InputEvent inputEvent;
			inputEvent.SetType(InputEvent::MouseWheelBackward);
			mInputEventList.Append(inputEvent);
		}

		return true;
	}
	//------------------------------------------------------------------------------
	/**    
	*/
	Math::float2
	Win32InputWebWindowSource::ComputeAbsMousePos(LPARAM lParam) const
	{
		return Math::float2( float(short(LOWORD(lParam))), float(short(HIWORD(lParam))) );
	}

	//------------------------------------------------------------------------------
	/**    
	*/
	Math::float2
	Win32InputWebWindowSource::ComputeNormMousePos(const Math::float2& absMousePos) const
	{
		Math::float2 normMousePos;
		RECT clientRect = { 0 };

		if ((0 != mWnd ) && GetClientRect( mWnd, &clientRect))
		{
			LONG w = Math::n_max(clientRect.right - clientRect.left, (LONG)1);
			LONG h = Math::n_max(clientRect.bottom - clientRect.top, (LONG)1);
			normMousePos.set(absMousePos.x() / float(w), absMousePos.y() / float(h));
		}

		return normMousePos;
	}
	//------------------------------------------------------------------------------
	/**
		Helper method which translates a Win32 virtual key code into a Nebula
		key code.
	*/
	Input::InputKey::Code
	Win32InputWebWindowSource::TranslateKeyCode(WPARAM wParam) const
	{
		switch (wParam)
		{
			case VK_BACK:                   return Input::InputKey::Back;
			case VK_TAB:                    return Input::InputKey::Tab;
			case VK_CLEAR:                  return Input::InputKey::Clear;
			case VK_RETURN:                 return Input::InputKey::Return;
			case VK_SHIFT:                  return Input::InputKey::Shift;
			case VK_CONTROL:                return Input::InputKey::Control;
			case VK_MENU:                   return Input::InputKey::Menu;
			case VK_PAUSE:                  return Input::InputKey::Pause;
			case VK_CAPITAL:                return Input::InputKey::Capital;
			case VK_ESCAPE:                 return Input::InputKey::Escape;
			case VK_CONVERT:                return Input::InputKey::Convert;
			case VK_NONCONVERT:             return Input::InputKey::NonConvert;
			case VK_ACCEPT:                 return Input::InputKey::Accept;
			case VK_MODECHANGE:             return Input::InputKey::ModeChange;
			case VK_SPACE:                  return Input::InputKey::Space;
			case VK_PRIOR:                  return Input::InputKey::Prior;
			case VK_NEXT:                   return Input::InputKey::Next;
			case VK_END:                    return Input::InputKey::End;
			case VK_HOME:                   return Input::InputKey::Home;
			case VK_LEFT:                   return Input::InputKey::Left;
			case VK_RIGHT:                  return Input::InputKey::Right;
			case VK_UP:                     return Input::InputKey::Up;
			case VK_DOWN:                   return Input::InputKey::Down;
			case VK_SELECT:                 return Input::InputKey::Select;
			case VK_PRINT:                  return Input::InputKey::Print;
			case VK_EXECUTE:                return Input::InputKey::Execute;
			case VK_SNAPSHOT:               return Input::InputKey::Snapshot;
			case VK_INSERT:                 return Input::InputKey::Insert;
			case VK_DELETE:                 return Input::InputKey::Delete;
			case VK_HELP:                   return Input::InputKey::Help;
			case VK_LWIN:                   return Input::InputKey::LeftWindows;
			case VK_RWIN:                   return Input::InputKey::RightWindows;
			case VK_APPS:                   return Input::InputKey::Apps;
			case VK_SLEEP:                  return Input::InputKey::Sleep;
			case VK_NUMPAD0:                return Input::InputKey::NumPad0;
			case VK_NUMPAD1:                return Input::InputKey::NumPad1;
			case VK_NUMPAD2:                return Input::InputKey::NumPad2;
			case VK_NUMPAD3:                return Input::InputKey::NumPad3;
			case VK_NUMPAD4:                return Input::InputKey::NumPad4;
			case VK_NUMPAD5:                return Input::InputKey::NumPad5;
			case VK_NUMPAD6:                return Input::InputKey::NumPad6;
			case VK_NUMPAD7:                return Input::InputKey::NumPad7;
			case VK_NUMPAD8:                return Input::InputKey::NumPad8;
			case VK_NUMPAD9:                return Input::InputKey::NumPad9;
			case VK_MULTIPLY:               return Input::InputKey::Multiply;
			case VK_ADD:                    return Input::InputKey::Add;
			case VK_SEPARATOR:              return Input::InputKey::Separator;
			case VK_DECIMAL:                return Input::InputKey::Decimal;
			case VK_DIVIDE:                 return Input::InputKey::Divide;
			case VK_F1:                     return Input::InputKey::F1;
			case VK_F2:                     return Input::InputKey::F2;
			case VK_F3:                     return Input::InputKey::F3;
			case VK_F4:                     return Input::InputKey::F4;
			case VK_F5:                     return Input::InputKey::F5;
			case VK_F6:                     return Input::InputKey::F6;
			case VK_F7:                     return Input::InputKey::F7;
			case VK_F8:                     return Input::InputKey::F8;
			case VK_F9:                     return Input::InputKey::F9;
			case VK_F10:                    return Input::InputKey::F10;
			case VK_F11:                    return Input::InputKey::F11;
			case VK_F12:                    return Input::InputKey::F12;
			case VK_F13:                    return Input::InputKey::F13;
			case VK_F14:                    return Input::InputKey::F14;
			case VK_F15:                    return Input::InputKey::F15;
			case VK_F16:                    return Input::InputKey::F16;
			case VK_F17:                    return Input::InputKey::F17;
			case VK_F18:                    return Input::InputKey::F18;
			case VK_F19:                    return Input::InputKey::F19;
			case VK_F20:                    return Input::InputKey::F20;
			case VK_F21:                    return Input::InputKey::F21;
			case VK_F22:                    return Input::InputKey::F22;
			case VK_F23:                    return Input::InputKey::F23;
			case VK_F24:                    return Input::InputKey::F24;
			case VK_NUMLOCK:                return Input::InputKey::NumLock;
			case VK_SCROLL:                 return Input::InputKey::Scroll;
			case VK_LSHIFT:                 return Input::InputKey::LeftShift;
			case VK_RSHIFT:                 return Input::InputKey::RightShift;
			case VK_LCONTROL:               return Input::InputKey::LeftControl;
			case VK_RCONTROL:               return Input::InputKey::RightControl;
			case VK_LMENU:                  return Input::InputKey::LeftMenu;
			case VK_RMENU:                  return Input::InputKey::RightMenu;
			case VK_BROWSER_BACK:           return Input::InputKey::BrowserBack;
			case VK_BROWSER_FORWARD:        return Input::InputKey::BrowserForward;
			case VK_BROWSER_REFRESH:        return Input::InputKey::BrowserRefresh;
			case VK_BROWSER_STOP:           return Input::InputKey::BrowserStop;
			case VK_BROWSER_SEARCH:         return Input::InputKey::BrowserSearch;
			case VK_BROWSER_FAVORITES:      return Input::InputKey::BrowserFavorites;
			case VK_BROWSER_HOME:           return Input::InputKey::BrowserHome;
			case VK_VOLUME_MUTE:            return Input::InputKey::VolumeMute;
			case VK_VOLUME_DOWN:            return Input::InputKey::VolumeDown;
			case VK_VOLUME_UP:              return Input::InputKey::VolumeUp;
			case VK_MEDIA_NEXT_TRACK:       return Input::InputKey::MediaNextTrack;
			case VK_MEDIA_PREV_TRACK:       return Input::InputKey::MediaPrevTrack;
			case VK_MEDIA_STOP:             return Input::InputKey::MediaStop;
			case VK_MEDIA_PLAY_PAUSE:       return Input::InputKey::MediaPlayPause;
			case VK_LAUNCH_MAIL:            return Input::InputKey::LaunchMail;
			case VK_LAUNCH_MEDIA_SELECT:    return Input::InputKey::LaunchMediaSelect;
			case VK_LAUNCH_APP1:            return Input::InputKey::LaunchApp1;
			case VK_LAUNCH_APP2:            return Input::InputKey::LaunchApp2;
			case '0':                       return Input::InputKey::Key0;
			case '1':                       return Input::InputKey::Key1;
			case '2':                       return Input::InputKey::Key2;
			case '3':                       return Input::InputKey::Key3;
			case '4':                       return Input::InputKey::Key4;
			case '5':                       return Input::InputKey::Key5;
			case '6':                       return Input::InputKey::Key6;
			case '7':                       return Input::InputKey::Key7;
			case '8':                       return Input::InputKey::Key8;
			case '9':                       return Input::InputKey::Key9;
			case 'A':                       return Input::InputKey::A;
			case 'B':                       return Input::InputKey::B;
			case 'C':                       return Input::InputKey::C;
			case 'D':                       return Input::InputKey::D;
			case 'E':                       return Input::InputKey::E;
			case 'F':                       return Input::InputKey::F;
			case 'G':                       return Input::InputKey::G;
			case 'H':                       return Input::InputKey::H;
			case 'I':                       return Input::InputKey::I;
			case 'J':                       return Input::InputKey::J;
			case 'K':                       return Input::InputKey::K;
			case 'L':                       return Input::InputKey::L;
			case 'M':                       return Input::InputKey::M;
			case 'N':                       return Input::InputKey::N;
			case 'O':                       return Input::InputKey::O;
			case 'P':                       return Input::InputKey::P;
			case 'Q':                       return Input::InputKey::Q;
			case 'R':                       return Input::InputKey::R;
			case 'S':                       return Input::InputKey::S;
			case 'T':                       return Input::InputKey::T;
			case 'U':                       return Input::InputKey::U;
			case 'V':                       return Input::InputKey::V;
			case 'W':                       return Input::InputKey::W;
			case 'X':                       return Input::InputKey::X;
			case 'Y':                       return Input::InputKey::Y;
			case 'Z':                       return Input::InputKey::Z;
			default:                        return Input::InputKey::InvalidKey;
		}
	}


}

#endif