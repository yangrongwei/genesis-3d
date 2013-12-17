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
#include "timing/calendartime.h"

namespace OSX
{
	using namespace Timing;
	using namespace Util;
	using namespace IO;
    
    //------------------------------------------------------------------------------
    /**
     */
    /*CalendarTime
     AndroidCalendarTime::FromWin32SystemTime(const SYSTEMTIME& t)
     {
     
     }*/
    
    //------------------------------------------------------------------------------
    /**
     */
    /*SYSTEMTIME
     AndroidCalendarTime::ToWin32SystemTime(const CalendarTime& calTime)
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
     }*/
    
    //------------------------------------------------------------------------------
    /**
     Obtains the current system time. This does not depend on the current
     time zone.
     */
    CalendarTime
    OSXCalendarTime::GetSystemTime()
    {
        CalendarTime time;
        return time;
    }
    
    //------------------------------------------------------------------------------
    /**
     Obtains the current local time (with time-zone adjustment).
     */
    CalendarTime
    OSXCalendarTime::GetLocalTime()
    {
        CalendarTime time;
        return time;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    FileTime
    OSXCalendarTime::SystemTimeToFileTime(const CalendarTime& systemTime)
    {
        FileTime fileTime;
        
        return fileTime;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    CalendarTime
    OSXCalendarTime::FileTimeToSystemTime(const FileTime& fileTime)
    {
        CalendarTime time;
        return time;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    FileTime
    OSXCalendarTime::LocalTimeToFileTime(const CalendarTime& localTime)
    {
        
        FileTime localFileTime;
        FileTime fileTime;
        
        return fileTime;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    CalendarTime
    OSXCalendarTime::FileTimeToLocalTime(const FileTime& fileTime)
    {
        CalendarTime time;
        return time;
    }
}
