/****************************************************************************
Copyright (c) 2007 Radon Labs GmbH
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
//------------------------------------------------------------------------------
/**
    @class Timing::CalendarTime
    
    Allows to obtain the current point in time as year, month, day, etc...
    down to milliseconds, convert between filetime and CalendarTime, and
    format the time to a human readable string
*/
#include "core/config.h"
#if (__WIN32__ || __XBOX360__)
#include "timing/win360/win360calendartime.h"
namespace Timing
{
class CalendarTime : public Win360::Win360CalendarTime
{ };
}
#elif __WII__
#include "timing/wii/wiicalendartime.h"
namespace Timing
{
class CalendarTime : public Wii::WiiCalendarTime
{ };
}
#elif __PS3__
#include "timing/ps3/ps3calendartime.h"
namespace Timing
{
class CalendarTime : public PS3::PS3CalendarTime
{ };
}
#elif __ANDROID__
#include "timing/android/androidcalendartime.h"
namespace Timing
{
	class CalendarTime : public Android::AndroidCalendarTime
	{ };
}
#elif __OSX__
#include "timing/osx/osxcalendartime.h"
namespace Timing
{
	class CalendarTime : public OSX::OSXCalendarTime
	{ };
}
#else
#error "Timing::CalendarTime not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
