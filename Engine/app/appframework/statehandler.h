/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
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
#ifndef __statehandler_H__
#define __statehandler_H__

#include "core/refcounted.h"
#include "app/application.h"

//------------------------------------------------------------------------------
namespace App
{
	class StateHandler : public Core::RefCounted
	{
		__DeclareClass(StateHandler);
	public:
		/// constructor
		StateHandler();
		/// destructor
		virtual ~StateHandler();

		/// set state name
		void SetName(const Util::String& n);
		/// get state name
		const Util::String& GetName() const;
		/// called when attached to application object
		virtual void OnAttachToApplication();
		/// called when removed from the application object
		virtual void OnRemoveFromApplication();
		/// called when the state represented by this state handler is entered
		virtual void OnStateEnter(const Util::String& prevState);
		/// called when the state represented by this state handler is left
		virtual void OnStateLeave(const Util::String& nextState);
		/// called each frame as long as state is current, return new state
		virtual Util::String OnFrame();
		/// called after Db is opened, and before entities are loaded
		virtual void OnLoadBefore();
		/// called after entities are loaded
		virtual void OnLoadAfter();

	protected:
		Util::String mStateName;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		StateHandler::SetName(const Util::String& n)
	{
		this->mStateName = n;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Util::String&
		StateHandler::GetName() const
	{
		return this->mStateName;
	}

};
//------------------------------------------------------------------------------





#endif // __statehandler_H__

