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
#ifndef __timemanager_H__
#define __timemanager_H__

#include "app/appframework/manager.h"
#include "app/basegamefeature/managers/timesource.h"
#include "core/singleton.h"
#include "timing/timer.h"

//------------------------------------------------------------------------------
namespace App
{
	class TimeManager : public App::Manager
	{
		__DeclareClass(TimeManager);
		__DeclareImageSingleton(TimeManager);

	public:
		/// constructor
		TimeManager();
		/// destructor
		virtual ~TimeManager();

		/// called when attached to game server
		virtual void OnActivate();
		/// called when removed from game server
		virtual void OnDeactivate();
		/// called before frame by the game server
		virtual void OnBeginFrame();
		/// on frame 
		virtual void OnFrame();
		/// reset all time sources
		void ResetAll();
		/// pause all time sources
		void PauseAll();
		/// continue all time sources
		void ContinueAll();

		/// get frame index
		IndexT GetFrameIndex(void) const;

		/// attach a time source
		void AttachTimeSource(const GPtr<TimeSource>& timeSource);
		/// remove a time source
		void RemoveTimeSource(const GPtr<TimeSource>& timeSource);
		/// get number of time source
		int GetNumTimeSources() const;
		/// get pointer to time source by index
		const GPtr<TimeSource>& GetTimeSourceByIndex(int index) const;
		/// get pointer to time source by class name
		GPtr<TimeSource> GetTimeSourceByClassName(const Util::String& n) const;

	protected:

		/// update the time manager
		void Update();

		IndexT mFrameIndex;
		Timing::Time mLastRealTime;
		Timing::Timer mTimer;
	
		Util::Array<GPtr<TimeSource> > mTimeSourceArray;
	};

	//------------------------------------------------------------------------
	inline
	IndexT 
	TimeManager::GetFrameIndex(void) const
	{
		return mFrameIndex;
	}

} // namespace BaseGameFeature

//------------------------------------------------------------------------------





#endif // __timemanager_H__


