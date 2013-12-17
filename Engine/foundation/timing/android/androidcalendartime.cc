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

#ifdef __ANDROID__
#include "stdneb.h"
#include "timing/calendartime.h"

namespace Android
{
	using namespace Timing;
	using namespace Util;
	using namespace IO;



//------------------------------------------------------------------------------
/**
    Obtains the current system time. This does not depend on the current
    time zone.
*/
CalendarTime
AndroidCalendarTime::GetSystemTime()
{
    CalendarTime time;
	return time;
}

//------------------------------------------------------------------------------
/**
    Obtains the current local time (with time-zone adjustment).
*/
CalendarTime
AndroidCalendarTime::GetLocalTime()
{
	CalendarTime time;
	return time;
}

//------------------------------------------------------------------------------
/**
*/
FileTime
AndroidCalendarTime::SystemTimeToFileTime(const CalendarTime& systemTime)
{
    FileTime fileTime;
 
    return fileTime;
}

//------------------------------------------------------------------------------
/**
*/
CalendarTime
AndroidCalendarTime::FileTimeToSystemTime(const FileTime& fileTime)
{
	CalendarTime time;
	return time;
}

//------------------------------------------------------------------------------
/**
*/
FileTime
AndroidCalendarTime::LocalTimeToFileTime(const CalendarTime& localTime)
{
   
    FileTime localFileTime;
    FileTime fileTime;
   
    return fileTime;
}

//------------------------------------------------------------------------------
/**
*/
CalendarTime
AndroidCalendarTime::FileTimeToLocalTime(const FileTime& fileTime)
{
	CalendarTime time;
	return time;
}
}
#endif