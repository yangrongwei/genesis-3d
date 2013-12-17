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
#ifndef __androidinputserver_H__
#define __androidinputserver_H__

#include "core/singleton.h"
#include "input/base/inputserverbase.h"
#include "math/float2.h"
#include "util/dictionary.h"

namespace AndroidInput
{
	class AndroidInputServer : public Input::InputServerBase
	{
		__DeclareClass(AndroidInputServer);
	public:
		/// constructor
		AndroidInputServer();
		/// destructor
		virtual ~AndroidInputServer();

	public:

		virtual void Open();

		virtual void Close();

		void SetTouchMovement(const Math::float2& movement, const IndexT id);

		const Math::float2& GetTouchMovement(const IndexT id) const;

		const GPtr<Input::InputTouchScreen>& GetDefaultTouchScreen() const;
	protected:

		Util::Dictionary<IndexT, Math::float2> m_TouchMovement;

		GPtr<Input::InputTouchScreen> defaultTouchScreen;

	};

	inline void AndroidInputServer::SetTouchMovement(const Math::float2& movement, const IndexT id)
	{
		IndexT ret = m_TouchMovement.FindIndex(id);

		if (ret != InvalidIndex)
		{
			m_TouchMovement[id] = movement;
		} 
		else
		{
			m_TouchMovement.Add(id, movement);
		}
	}

	inline const Math::float2& AndroidInputServer::GetTouchMovement(const IndexT id) const
	{
		IndexT ret = m_TouchMovement.FindIndex(id);

		if (ret != InvalidIndex)
		{
			return m_TouchMovement.ValueAtIndex(ret);
		} 
		else
		{
			n_error(" AndroidInputServer::GetTouchMovement : Invalid Id !!! ");
		}
	}

	inline const GPtr<Input::InputTouchScreen>& AndroidInputServer::GetDefaultTouchScreen() const
	{
		return defaultTouchScreen;
	}

}

#endif