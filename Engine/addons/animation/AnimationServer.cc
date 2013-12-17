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

#include "animation/animation_stdneb.h"
#include "animation/AnimationServer.h"
#include "animation/Animation.h"

namespace Animations
{
	__ImplementClass(Animations::AnimationServer, 'ANSR', Core::RefCounted);

	__ImplementImageSingleton(Animations::AnimationServer);

	AnimationServer::AnimationServer()
		: m_LocalTime(0.0),
		m_bStop(false)
	{
		__ConstructImageSingleton;

		m_Animations.Clear();
	}

	AnimationServer::~AnimationServer()
	{
		__DestructImageSingleton;

		m_Animations.Clear();
	}

	void AnimationServer::AttachAnimation(const GPtr<Animation> &animation)
	{
		IndexT index = m_Animations.FindIndex(animation);

		if (index == InvalidIndex)
		{
			m_Animations.Append(animation);
		}
		else
			n_error("This animation has already existed!");
	}

	void AnimationServer::DetachAnimaton(const GPtr<Animation> &animation)
	{
		IndexT index = m_Animations.FindIndex(animation);

		if (index != InvalidIndex)
		{
			m_Animations.EraseIndex(index);
		}
		else
			n_error("The animation do not exist, can not be detached!");
	}

	void AnimationServer::UpdateAnimatons(float time)
	{
		if(m_Animations.IsEmpty())
			return;

		if (m_bStop)
		{
			m_LocalTime = 0.0f;
			return;
		}

		SizeT count = m_Animations.Size();

		for (IndexT i = 0; i<count; ++i)
		{
			m_Animations[i]->UpdateAnimation(time);

		}

		m_LocalTime += time;
	}

}