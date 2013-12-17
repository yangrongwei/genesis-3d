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
#pragma once

#include "core/refcounted.h"
#include "core/singleton.h"

namespace Animations
{
	class Animation;

	class AnimationServer : public Core::RefCounted
	{
		__DeclareClass(AnimationServer);
		__DeclareImageSingleton(AnimationServer);

	public:
		AnimationServer();
		~AnimationServer();

	public:
		void AttachAnimation(const GPtr<Animation>& animation);

		void DetachAnimaton(const GPtr<Animation>& animation);

		void UpdateAnimatons(float time);

		void UpdateAnimation(Animation* animation);

		float GetLocalTime() const;

		void OpenServer();

		void StopServer();

		bool IsStop();

	protected:
		float                  m_LocalTime;
		bool                   m_bStop;

		Util::Array< GPtr<Animation> > m_Animations;
	};

	inline float AnimationServer::GetLocalTime() const
	{
		return m_LocalTime;
	}

	inline void AnimationServer::OpenServer()
	{
		m_bStop = false;
	}

	inline void AnimationServer::StopServer()
	{
		m_bStop = true;
	}

	inline bool AnimationServer::IsStop()
	{
		return m_bStop;
	}

}