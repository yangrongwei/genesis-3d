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
#include "app/basegamefeature/managers/timemanager.h"
#include "math/scalar.h"
#include "timing/time.h"



namespace App
{
__ImplementClass(TimeManager, 'TIMA', App::Manager);
__ImplementImageSingleton(TimeManager);

using namespace Timing;
using namespace Math;

//------------------------------------------------------------------------------
/**
*/
TimeManager::TimeManager() :                                           
    mLastRealTime(0)  
	, mFrameIndex(0)
{                                              
    __ConstructImageSingleton;                     
}

//------------------------------------------------------------------------------
/**
*/
TimeManager::~TimeManager()
{
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
    Activate the time manager. This will create all the standard time
    sources for Mangalore.
*/
void
TimeManager::OnActivate()
{
    // get current global time
	this->mTimer.Start();

    mLastRealTime = this->mTimer.GetTime();

    // create standard time sources...
    Manager::OnActivate();
}

//------------------------------------------------------------------------------
/**
    Deactivate the time manager. 
*/
void
TimeManager::OnDeactivate()
{
    // cleanup time sources...
    while (this->mTimeSourceArray.Size() > 0)
    {
        this->RemoveTimeSource(this->mTimeSourceArray[0]);
    }        
	this->mTimer.Stop();

    Manager::OnDeactivate();
}

//------------------------------------------------------------------------------
/**
    Attach a time source to the time manager. This will invoke
    OnActivate() on the time source.
*/
void
TimeManager::AttachTimeSource(const GPtr<TimeSource>& timeSource)
{
    n_assert(timeSource);
    n_assert(!this->mTimeSourceArray.Find(timeSource));
    timeSource->OnActivate();
    this->mTimeSourceArray.Append(timeSource);
}

//------------------------------------------------------------------------------
/**
    Remove a time source from the time manager. This will invoke OnDeactivate()
    on the time source.
*/
void
TimeManager::RemoveTimeSource(const GPtr<TimeSource>& timeSource)
{
    n_assert(timeSource);
    IndexT index = this->mTimeSourceArray.FindIndex(timeSource);
    n_assert(InvalidIndex != index);
    this->mTimeSourceArray[index]->OnDeactivate();
    this->mTimeSourceArray.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
    Returns number of time sources attached to the time manager.
*/
int
TimeManager::GetNumTimeSources() const
{
    return this->mTimeSourceArray.Size();
}

//------------------------------------------------------------------------------
/**
    Gets pointer to time source object by index.
*/
const GPtr<TimeSource>& 
TimeManager::GetTimeSourceByIndex(int index) const
{
    return this->mTimeSourceArray[index];
}

//------------------------------------------------------------------------------
/**
    Get pointer to time source object by class name, returns 0 if not found.
*/
GPtr<TimeSource> 
TimeManager::GetTimeSourceByClassName(const Util::String& n) const
{
    n_assert(n.IsValid());
    IndexT i;
    for (i = 0; i < this->mTimeSourceArray.Size(); i++)
    {
        if (this->mTimeSourceArray[i]->GetClassName() == n)
        {
            return this->mTimeSourceArray[i];
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
/**
    Reset all time sources. This is usually called at the beginning
    of an application state.
*/
void
TimeManager::ResetAll()
{
    IndexT i;
    for (i = 0; i < this->mTimeSourceArray.Size(); i++)
    {
        this->mTimeSourceArray[i]->Reset();
    }
}

//------------------------------------------------------------------------------
/**
    Pause all time sources. NOTE: there's an independent pause counter inside each
    time source, a pause just increments the counter, a continue decrements
    it, when the pause counter is != 0 it means, pause is activated.
*/
void
TimeManager::PauseAll()
{
    IndexT i;
    for (i = 0; i < this->mTimeSourceArray.Size(); i++)
    {
        this->mTimeSourceArray[i]->Pause();
    }
}

//------------------------------------------------------------------------------
/**
    Unpause all time sources.
*/
void
TimeManager::ContinueAll()
{
    IndexT i;
    for (i = 0; i < this->mTimeSourceArray.Size(); i++)
    {
        this->mTimeSourceArray[i]->Continue();
    }
}

//------------------------------------------------------------------------------
/**
Update our time sources
*/
void TimeManager::OnBeginFrame()
{
	this->Update();
}


//------------------------------------------------------------------------------
/**
*/
void
TimeManager::OnFrame()
{
    
}

//------------------------------------------------------------------------------
/**
    Update all time sources. This method is called very early in the frame
    by the current application state handler. This will get the current frame time
    and call UpdateTime() on all attached time sources.

    FIXME:
    * properly handle time exceptions!!!
*/
void
TimeManager::Update()
{
	++mFrameIndex;
    // compute the current frame time
	Timing::Time curTime = this->mTimer.GetTime();

    Timing::Time frameTime = curTime - this->mLastRealTime;           

    IndexT i;
    for (i = 0; i < this->mTimeSourceArray.Size(); i++)
    {
        this->mTimeSourceArray[i]->UpdateTime(frameTime);
    }
    this->mLastRealTime = curTime;
}

}; // namespace Game
