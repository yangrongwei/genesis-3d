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
#ifndef __APPFWDDECL_H__
#define __APPFWDDECL_H__

#include "core/ptr.h"

namespace App
{
	// pointer define
	/*
	etc 
	typedef GPtr<StateHandler> TStateHandlerPtr
	T + ClassName + Ptr

	typedef GPtr<const StateHandler> TStateHandlerConstPtr
	T + ClassName + ConstPtr
	 */

	// forward declare
	class StateHandler;
	class Actor;
	class Component;

	// typedefs
	typedef GPtr<StateHandler> TStateHandlerPtr;
	typedef GPtr<Actor> TActorPtr;
	typedef GPtr<Component> TComponentPtr;

	enum ComponetsCommSign
	{
		eCCS_None = BIT_FLAG_NONE,
		eCCS_OnRenderPostEffect = BIT_FLAG(0),
		eCCS_OnWillRenderObject = BIT_FLAG(1),
		//eCCS_BoneAnimation = BIT_FLAG(2)
	};
}

#endif // __APPFWDDECL_H__
