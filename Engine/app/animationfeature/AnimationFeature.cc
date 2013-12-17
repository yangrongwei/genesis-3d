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
#include "profilesystem/ProfileSystem.h"
#include "AnimationFeature.h"
#include "animation/AnimationServer.h"
#include "basegamefeature/managers/timesource.h"

namespace App
{
	__ImplementClass(App::AnimationFeature, 'AFAP' , App::Feature);
	__ImplementImageSingleton(App::AnimationFeature);

	AnimationFeature::AnimationFeature()
	{
		__ConstructImageSingleton;

		mFeatureName = "Animation";
	}

	AnimationFeature::~AnimationFeature()
	{
		m_pAnimationServer = NULL;
		__DestructImageSingleton;
	}

	void AnimationFeature::OnActivate()
	{
		Feature::OnActivate();

		m_pAnimationServer = Animations::AnimationServer::Create();
	}

	void AnimationFeature::OnDeactivate()
	{
		Feature::OnDeactivate();
	}

	void AnimationFeature::OnFrame()
	{
		PROFILER_ADDDTICKBEGIN(animationsTime);
		m_pAnimationServer->UpdateAnimatons( (float)GameTime::Instance()->GetFrameTime() );
		PROFILER_ADDDTICKEND(animationsTime);
	}

	void AnimationFeature::OnStart()
	{
		m_pAnimationServer->OpenServer();
	}

	void AnimationFeature::OnStop()
	{
		m_pAnimationServer->StopServer();
	}

}