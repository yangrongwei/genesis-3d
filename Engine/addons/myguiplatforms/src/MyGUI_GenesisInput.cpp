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
#include "stdneb.h"
#include "myguiengine/include/MyGUI_InputManager.h"
#include "MyGUI_GenesisInput.h"

namespace MyGUI
{
	GenesisInputManager* GenesisInputManager::sInstance = NULL;
	GenesisInputManager::GenesisInputManager()
		:mWidth(0)
		,mHeight(0)
	{
		assert(NULL == sInstance);
		sInstance = this;
	}

	GenesisInputManager::~GenesisInputManager()
	{
		assert(sInstance);
		sInstance = NULL;
	}

	GenesisInputManager* GenesisInputManager::getInstancePtr()
	{
		return sInstance;
	}

	GenesisInputManager& GenesisInputManager::getInstance()
	{
		return *sInstance;
	}

	bool GenesisInputManager::injectKeyPress(KeyCode _key, _Char _text /* = 0 */)
	{
		return InputManager::getInstancePtr()->injectKeyPress(_key, _text);
	}

	bool GenesisInputManager::injectKeyRelease(KeyCode _key)
	{
		return InputManager::getInstancePtr()->injectKeyRelease(_key);
	}

	bool GenesisInputManager::injectMouseMove(float _normalx, float _normaly, int _absz)
	{
		return InputManager::getInstancePtr()->injectMouseMove(int(_normalx * mWidth), int(_normaly * mHeight), _absz);
	}

	bool GenesisInputManager::injectMousePress(float _normalx, float _normaly, MouseButton _id)
	{
		return InputManager::getInstancePtr()->injectMousePress(int(_normalx * mWidth), int(_normaly * mHeight), _id);
	}

	bool GenesisInputManager::injectMouseRelease(float _normalx, float _normaly, MouseButton _id)
	{
		return InputManager::getInstancePtr()->injectMouseRelease(int(_normalx * mWidth), int(_normaly * mHeight), _id);
	}

	void GenesisInputManager::resetMouseCaptureWidget()
	{
		InputManager::getInstancePtr()->resetMouseCaptureWidget();
	}
}