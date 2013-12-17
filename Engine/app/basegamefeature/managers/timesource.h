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
#ifndef __timesource_H__
#define __timesource_H__

#include "core/refcounted.h"
#include "timing/time.h"
#include "core/singleton.h"

namespace App
{
	class TimeManager;

	class TimeSource : public Core::RefCounted
	{
		__DeclareClass(TimeSource);

	public:
		/// constructor
		TimeSource();
		/// destructor
		virtual ~TimeSource();

		/// called when time source is attached to the time manager
		virtual void OnActivate();
		/// called when time source is removed from the time manager
		virtual void OnDeactivate();

		/// reset the time source to 0.0
		virtual void Reset();
		/// pause the time source (increments pause counter)
		virtual void Pause();
		/// unpause the time source (decrements pause counter)
		virtual void Continue();
		/// return true if currently paused
		bool IsPaused() const;

		/// set acceleration/deceleration factor
		virtual void SetFactor(float f);
		/// get acceleration/deceleration factor
		float GetFactor() const;
		/// get the current time
		Timing::Time GetTime() const;
		/// get the current frame time
		Timing::Time GetFrameTime() const;

	protected:
		friend class TimeManager;

		/// update current time (called by time manager)
		virtual void UpdateTime(Timing::Time frameTime);

		Timing::Time mFrameTime; 
		Timing::Time mTime;
		int mPauseCounter;
		float mTimeFactor;
	};

	//------------------------------------------------------------------------
	class GameTime: public TimeSource
	{
		__DeclareClass(GameTime);
		__DeclareImageSingleton(GameTime);
	public:
		GameTime();
		~GameTime();
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	Timing::Time
	TimeSource::GetFrameTime() const
	{
		if (this->IsPaused())
		{
			return 0.0f;
		}
		else
		{
			return this->mFrameTime;
		}
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	Timing::Time
	TimeSource::GetTime() const
	{
		return this->mTime;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	TimeSource::SetFactor(float f)
	{
		n_assert(f > 0.0f);
		this->mTimeFactor = f;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	float
	TimeSource::GetFactor() const
	{
		return this->mTimeFactor;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	TimeSource::IsPaused() const
	{
		return (this->mPauseCounter > 0);
	}

} // namespace BaseGameFeature
//------------------------------------------------------------------------------



#endif // __timesource_H__

