/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#if WIN32


#include "stdneb.h"
#include "timing/calendartime.h"

namespace Win360
{
using namespace Timing;
using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
CalendarTime
Win360CalendarTime::FromWin32SystemTime(const SYSTEMTIME& t)
{
    CalendarTime calTime;
    calTime.year    = t.wYear;
    calTime.month   = (Month) t.wMonth;
    calTime.weekday = (Weekday) t.wDayOfWeek;
    calTime.day     = t.wDay;
    calTime.hour    = t.wHour;
    calTime.minute  = t.wMinute;
    calTime.second  = t.wSecond;
    calTime.milliSecond = t.wMilliseconds;
    return calTime;
}

//------------------------------------------------------------------------------
/**
*/
SYSTEMTIME
Win360CalendarTime::ToWin32SystemTime(const CalendarTime& calTime)
{
    SYSTEMTIME t;
    t.wYear         = (WORD) calTime.year;
    t.wMonth        = (WORD) calTime.month;
    t.wDayOfWeek    = (WORD) calTime.weekday;
    t.wDay          = (WORD) calTime.day;
    t.wHour         = (WORD) calTime.hour;
    t.wMinute       = (WORD) calTime.minute;
    t.wSecond       = (WORD) calTime.second;
    t.wMilliseconds = (WORD) calTime.milliSecond;
    return t;
}

//------------------------------------------------------------------------------
/**
    Obtains the current system time. This does not depend on the current
    time zone.
*/
CalendarTime
Win360CalendarTime::GetSystemTime()
{
    SYSTEMTIME t;
    ::GetSystemTime(&t);
    return FromWin32SystemTime(t);
}

//------------------------------------------------------------------------------
/**
    Obtains the current local time (with time-zone adjustment).
*/
CalendarTime
Win360CalendarTime::GetLocalTime()
{
    SYSTEMTIME t;
    ::GetLocalTime(&t);
    return FromWin32SystemTime(t);
}

//------------------------------------------------------------------------------
/**
*/
FileTime
Win360CalendarTime::SystemTimeToFileTime(const CalendarTime& systemTime)
{
    SYSTEMTIME t = ToWin32SystemTime(systemTime);
    FileTime fileTime;
    ::SystemTimeToFileTime(&t, &fileTime.time);
    return fileTime;
}

//------------------------------------------------------------------------------
/**
*/
CalendarTime
Win360CalendarTime::FileTimeToSystemTime(const FileTime& fileTime)
{
    SYSTEMTIME t;
    ::FileTimeToSystemTime(&fileTime.time, &t);
    return FromWin32SystemTime(t);
}

//------------------------------------------------------------------------------
/**
*/
FileTime
Win360CalendarTime::LocalTimeToFileTime(const CalendarTime& localTime)
{
    SYSTEMTIME t = ToWin32SystemTime(localTime);
    FileTime localFileTime;
    FileTime fileTime;
    ::SystemTimeToFileTime(&t, &localFileTime.time);
    ::LocalFileTimeToFileTime(&localFileTime.time, &fileTime.time);
    return fileTime;
}

//------------------------------------------------------------------------------
/**
*/
CalendarTime
Win360CalendarTime::FileTimeToLocalTime(const FileTime& fileTime)
{
    FileTime localFileTime;
    ::FileTimeToLocalFileTime(&fileTime.time, &localFileTime.time);
    SYSTEMTIME t;
    ::FileTimeToSystemTime(&localFileTime.time, &t);
    return FromWin32SystemTime(t);
}

} // namespace Win360

#endif