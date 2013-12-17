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
#include "input/input_stdneb.h"
#include "input/inputsource.h"
#include "input/base/inputserverbase.h"

namespace Input
{
	__ImplementClass(Input::InputSource, 'INSR', Core::RefCounted);


	//------------------------------------------------------------------------
	InputSource::InputSource()
		:mIsOpen(false)
	{

	}
	//------------------------------------------------------------------------
	/// destructor
	InputSource::~InputSource()
	{
		n_assert( !mIsOpen );
	}
	//------------------------------------------------------------------------
	/// called when the input server Open
	void InputSource::Open(const GPtr<InputServerBase>& inputServer )
	{
		n_assert( !mIsOpen );
		mIsOpen = true;
		mInputServer = inputServer;
		n_assert( mInputServer );
	}
	//------------------------------------------------------------------------
	/// called whem the input server Close
	void InputSource::Close()
	{
		n_assert( mIsOpen );
		mIsOpen = false;
		mInputServer = NULL;
	}
	//------------------------------------------------------------------------
	/// called when the input server BeginFrame. Maybe Create InputEvent there
	void InputSource::BeginFrame()
	{
		n_assert( mIsOpen );
		// empty	
	}


	int InputSource::VirtualKeyToText(void* _virtualKey)
	{
#if __WIN32__

		static WCHAR deadKey = 0;

		BYTE keyState[256];
		HKL  layout = GetKeyboardLayout(0);
		if (GetKeyboardState(keyState) == 0)
			return 0;

		WCHAR buff[3] = { 0, 0, 0 };
		int ascii = ToUnicodeEx((UINT)_virtualKey, 0, keyState, buff, 3, 0, layout);
		if (ascii == 1 && deadKey != '\0' )
		{
			// A dead key is stored and we have just converted a character key
			// Combine the two into a single character
			WCHAR wcBuff[3] = { buff[0], deadKey, '\0' };
			WCHAR out[3];

			deadKey = '\0';
			if (FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuff, 3, (LPWSTR)out, 3))
				return out[0];
		}
		else if (ascii == 1)
		{
			// We have a single character
			deadKey = '\0';
			return buff[0];
		}
		else if (ascii == 2)
		{
			// Convert a non-combining diacritical mark into a combining diacritical mark
			// Combining versions range from 0x300 to 0x36F; only 5 (for French) have been mapped below
			// http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
			switch (buff[0])
			{
			case 0x5E: // Circumflex accent: §Ó
				deadKey = 0x302;
				break;
			case 0x60: // Grave accent: §Ñ
				deadKey = 0x300;
				break;
			case 0xA8: // Diaeresis: §î
				deadKey = 0x308;
				break;
			case 0xB4: // Acute accent: §Û
				deadKey = 0x301;
				break;
			case 0xB8: // Cedilla: §Ù
				deadKey = 0x327;
				break;
			default:
				deadKey = buff[0];
				break;
			}
		}
		return 0;

#endif
	}


}