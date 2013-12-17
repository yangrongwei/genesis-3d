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
#include "core/singleton.h"
#include "ALSystemFeature.h"
#include "addons/ALSystem/ALSystem.h"


namespace App
{
	__ImplementClass(App::ALSystemFeature, 'ALSF' , App::Feature);
	__ImplementThreadSingleton(App::ALSystemFeature);


	//------------------------------------------------------------------------------
	/**
	*/
	ALSystemFeature::ALSystemFeature()
	{
		__ConstructThreadSingleton;

		mFeatureName = "ALSystem";
		Init();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	ALSystemFeature::~ALSystemFeature()
	{
		__DestructThreadSingleton;
		CleanUp();
	}

	void ALSystemFeature::OnFrame()
	{
#if __OSX__ 
		if ( !mGameIAP.isvalid() )
		{
			return;
		}
		mGameIAP->onTick();
#endif
	}

	void ALSystemFeature::Init()
	{
		//now only ios implement
#if __OSX__ 
		NALSystem::ALSystemFactory::createALSystem();
		mGameIAP = App::GameIap::Create();
		mGameIAP->Init();
#endif
	}
	void ALSystemFeature::CleanUp()
	{
#if __OSX__ 
		NALSystem::ALSystemFactory::releaseALSystem();
		mGameIAP = 0;
#endif
	}


}