/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#ifndef __MYGUI_GENESIS_INPUT_H__
#define __MYGUI_GENESIS_INPUT_H__
#include "myguiengine/include/MyGUI_KeyCode.h"
#include "myguiengine/include/MyGUI_MouseButton.h"

namespace MyGUI
{

	class GenesisInputManager
	{
	public:
		typedef unsigned int _Char;
		GenesisInputManager();
		~GenesisInputManager();
		static GenesisInputManager& getInstance();
		static GenesisInputManager* getInstancePtr();

		bool injectMouseMove(float _normalx, float _normaly, int _absz);

		bool injectMousePress(float _normalx, float _normaly, MouseButton _id);

		bool injectMouseRelease(float _normalx, float _normaly, MouseButton _id);

		bool injectKeyPress(KeyCode _key, _Char _text = 0);

		bool injectKeyRelease(KeyCode _key);

		void resetMouseCaptureWidget();

		void _setScreenSize(float width, float height);
	private:
		float mWidth;
		float mHeight;

		static GenesisInputManager* sInstance;

	};

	inline void GenesisInputManager::_setScreenSize(float width, float height)
	{
		mWidth = width;
		mHeight = height;
	}
}

#endif //__MYGUI_GENESIS_INPUT_H__
