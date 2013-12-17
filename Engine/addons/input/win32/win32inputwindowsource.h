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
#ifndef __win32inputwindowsource_H__
#define __win32inputwindowsource_H__

#include "input/inputsource.h"
#include "input/inputevent.h"


namespace Win32Input
{
	class Win32InputWindowSource: public Input::InputSource
	{
		__DeclareSubClass(Win32InputWindowSource, Input::InputSource );
	public:
		Win32InputWindowSource();
		virtual ~Win32InputWindowSource();

		// @ InputSource::Open()
		virtual void Open(const GPtr<Input::InputServerBase>& inputServer);

		// @ InputSource::Close()
		virtual void Close();

		/// called when the input server BeginFrame. Maybe Create InputEvent there
		virtual void BeginFrame(void);

		LRESULT OnWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

		void OnMouseButton(UINT uMsg, LPARAM lParam);

		void OnMouseMove(LPARAM lParam);

		void OnMouseWheel(WPARAM wParam);

		/// compute absolute mouse position from lParam
		Math::float2 ComputeAbsMousePos(LPARAM lParam) const;

		/// compute normalized mouse position from absolute mouse pos
		Math::float2 ComputeNormMousePos(const Math::float2& absMousePos) const;

		/// translate a Windows virtual key code into a Nebula3 key code
		Input::InputKey::Code TranslateKeyCode(WPARAM wParam) const;

		void SetWnd( HWND hWnd );

		HWND GetWnd(void) const;

	protected:
		Util::Array< Input::InputEvent > mInputEventList;

		Math::float2 mMousePostion;

		HWND mWnd;
	};
	//------------------------------------------------------------------------
	inline
	void 
	Win32InputWindowSource::SetWnd( HWND hWnd )
	{
		mWnd = hWnd;
	}

	//------------------------------------------------------------------------
	inline
	HWND 
	Win32InputWindowSource::GetWnd(void) const
	{
		return mWnd;
	}
}












#endif // __win32inputwindowsource_H__

