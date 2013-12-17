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
#include "input/win32/win32inputhardwaresource.h"
#include "input/win32/win32inputserver.h"

namespace Win32Input
{
	__ImplementClass(Win32Input::Win32InputHardwareSource, 'WHIS', Input::InputSource );

	//------------------------------------------------------------------------
	Win32InputHardwareSource::Win32InputHardwareSource():
		mDi8(0),
		mDi8Mouse(0)
	{

	}
	//------------------------------------------------------------------------
	Win32InputHardwareSource::~Win32InputHardwareSource()
	{

	}
	//------------------------------------------------------------------------
	void
	Win32InputHardwareSource::Open(const GPtr<Input::InputServerBase>& inputServer)
	{
		_OpenDInputMouse();
		Super::Open(inputServer);
	}
	//------------------------------------------------------------------------
	// @ InputSource::Close()
	void 
	Win32InputHardwareSource::Close()
	{
		_CloseDInputMouse();
		Super::Close();
	}
	//------------------------------------------------------------------------
	void 
	Win32InputHardwareSource::BeginFrame()
	{
		Super::BeginFrame();
		_ReadDInputMouse();
	}
	//------------------------------------------------------------------------------
	/**    
		This intitialies a DirectInput mouse device in order to track
		raw mouse movement (WM mouse events stop at the screen borders).
	*/
	bool
	Win32InputHardwareSource::_OpenDInputMouse()
	{
		n_assert(0 == this->mDi8);
		n_assert(0 == this->mDi8Mouse);
		HRESULT hr;

		// create DirectInput interface
		hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&(this->mDi8), NULL);
		n_assert(SUCCEEDED(hr));
		n_assert(0 != this->mDi8);

		// create a DirectInput mouse device
		hr = this->mDi8->CreateDevice(GUID_SysMouse, &(this->mDi8Mouse), NULL);
		n_assert(SUCCEEDED(hr));
		n_assert(0 != this->mDi8Mouse);

		// tell DInput what we're interested in
		hr = this->mDi8Mouse->SetDataFormat(&c_dfDIMouse2);
		n_assert(SUCCEEDED(hr));

		// set the cooperative level of the device, we're friendly
		// note: use Win32's FindWindow() to find our top level window because 
		// the DisplayDevice may be running in a different thread
		HWND hWnd = FindWindowA(NEBULA3_WINDOW_CLASS, NULL);
		if (0 != hWnd)
		{
			hr = this->mDi8Mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NOWINKEY | DISCL_NONEXCLUSIVE);
			n_assert(SUCCEEDED(hr));
		}

		// set buffer size and relative axis mode on the mouse
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;

		dipdw.dwData = DInputMouseBufferSize;
		hr = this->mDi8Mouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
		n_assert(SUCCEEDED(hr));
		dipdw.dwData = DIPROPAXISMODE_REL;
		hr = this->mDi8Mouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
		n_assert(SUCCEEDED(hr));

		// aquire the mouse
		this->mDi8Mouse->Acquire();

		return true;
	}

	//------------------------------------------------------------------------------
	/**    
		Close the DirectInput mouse and DirectInput.
	*/
	void
	Win32InputHardwareSource::_CloseDInputMouse()
	{
		n_assert(0 != this->mDi8);
		n_assert(0 != this->mDi8Mouse);
		this->mDi8Mouse->Unacquire();
		this->mDi8Mouse->Release();
		this->mDi8Mouse = 0;
		this->mDi8->Release();
		this->mDi8 = 0;
	}

	//------------------------------------------------------------------------------
	/**    
		Read data from the DirectInput mouse (relative mouse movement
		since the last frame).
	*/
	void
	Win32InputHardwareSource::_ReadDInputMouse()
	{
		n_assert(0 != this->mDi8Mouse);
		DIDEVICEOBJECTDATA didod[DInputMouseBufferSize];
		HRESULT hr;
	    
		Math::float2 mouseMovement;
		mouseMovement.set(0.0f, 0.0f);

		// read buffered mouse data
		DWORD inOutNumElements = DInputMouseBufferSize;
		hr = this->mDi8Mouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), didod, &inOutNumElements, 0);
		if (DI_OK != hr)
		{
			hr = this->mDi8Mouse->Acquire();
		}
		else
		{
			IndexT i;
			for (i = 0; i < (SizeT)inOutNumElements; i++)
			{
				switch (didod[i].dwOfs)
				{
					case DIMOFS_X:
						mouseMovement.x() += float(int(didod[i].dwData)) * 0.1f;
						break;

					case DIMOFS_Y:
						mouseMovement.y() += float(int(didod[i].dwData)) * 0.1f;
						break;
				}
			}

			n_assert(mInputServer.isvalid() && mInputServer->GetRtti()->IsDerivedFrom( Win32InputServer::RTTI ) );
			GPtr<Win32InputServer> win32InputServer = mInputServer.downcast<Win32InputServer>();
			n_assert( win32InputServer.isvalid() );
			win32InputServer->SetMouseMovement( mouseMovement );
		}
	}


}

#endif