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
#include "stdneb.h"
#include "app/basegamefeature/managers/timesource.h"


namespace App
{
__ImplementClass(TimeSource, 'TTSC', Core::RefCounted);
__ImplementClass(GameTime,'GTSG',App::TimeSource);
__ImplementImageSingleton(GameTime);
using namespace Timing;

//------------------------------------------------------------------------
GameTime::GameTime()
{
	__ConstructImageSingleton;
}
GameTime::~GameTime()
{
	__DestructImageSingleton;
}
//------------------------------------------------------------------------------
/**
*/
TimeSource::TimeSource() :
    mFrameTime(0.001f),       
    mTime(0.0),                        
    mPauseCounter(0),         
    mTimeFactor(1.0f)         
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
TimeSource::~TimeSource()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
TimeSource::OnActivate()
{
    // empty
    this->mTime = 0.0;
    this->mPauseCounter = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
TimeSource::OnDeactivate()
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
    This method is called when the internal time should be updated. It will
    be called early in the frame by the TimeManager. Think of this method
    as the time source's OnFrame() method.
*/
void
TimeSource::UpdateTime(Time frameTime)
{
    this->mFrameTime = frameTime;

    if (!this->IsPaused())
    {
        this->mTime += frameTime * this->mTimeFactor;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
TimeSource::Reset()
{
    this->mTime = 0.0;
    this->mPauseCounter = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
TimeSource::Pause()
{
    this->mPauseCounter++;
}

//------------------------------------------------------------------------------
/**
*/
void
TimeSource::Continue()
{
    if (this->mPauseCounter > 0)
    {
        this->mPauseCounter--;
    }
}

} // namespace Timing




