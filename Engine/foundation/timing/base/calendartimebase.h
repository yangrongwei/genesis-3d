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

#pragma once
//------------------------------------------------------------------------------
/**
    @class Base::CalendarTimeBase
    
    Allows to obtain the current point in time as year, month, day, etc...
    down to milliseconds, convert between filetime and CalendarTime, and
    format the time to a human readable string.

    (C) 2007 Radon Labs GmbH
*/
#include "core/types.h"
#include "io/filetime.h"
#include "util/string.h"

namespace Timing
{
    class CalendarTime;
}

//------------------------------------------------------------------------------
namespace Base
{
class CalendarTimeBase
{
public:
    /// typedefs
    typedef unsigned int Year;
    typedef unsigned int Day;
    typedef unsigned int Hour;
    typedef unsigned int Minute;
    typedef unsigned int Second;
    typedef unsigned int MilliSecond;

    /// months enum
    enum Month 
    {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    };
    /// weekdays enum
    enum Weekday
    {
        Sunday = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
    };

    /// constructor
    CalendarTimeBase();
    /// set the year
    void SetYear(Year y);
    /// get the year
    Year GetYear() const;
    /// set the month
    void SetMonth(Month m);
    /// get the month
    Month GetMonth() const;
    /// set the day-of-week
    void SetWeekday(Weekday wd);
    /// get the day-of-week
    Weekday GetWeekday() const;
    /// set the day (of month)
    void SetDay(Day d);
    /// get the day (of month)
    Day GetDay() const;
    /// set hour-of-day
    void SetHour(Hour h);
    /// get hour-of-day
    Hour GetHour() const;
    /// set minute-of-hour
    void SetMinute(Minute m);
    /// get minute-of-hour
    Minute GetMinute() const;
    /// set second-of-minute
    void SetSecond(Second s);
    /// get second-of-minute
    Second GetSecond() const;
    /// set milliseconds
    void SetMilliSecond(MilliSecond ms);
    /// get milliseconds
    MilliSecond GetMilliSecond() const;
    
    /// get the current system time
    static Timing::CalendarTime GetSystemTime();
    /// get the current local time
    static Timing::CalendarTime GetLocalTime();
    /// convert system time to file time
    static IO::FileTime SystemTimeToFileTime(const Timing::CalendarTime& systemTime);
    /// convert file time to system time
    static Timing::CalendarTime FileTimeToSystemTime(const IO::FileTime& fileTime);
    /// convert local time to file time
    static IO::FileTime LocalTimeToFileTime(const Timing::CalendarTime& localTime);
    /// convert file time to local time
    static Timing::CalendarTime FileTimeToLocalTime(const IO::FileTime& fileTime);
    /// format to string
    static Util::String Format(const Util::String& fmtString, const Timing::CalendarTime& calTime);
    /// convert month to string
    static Util::String MonthToString(Month m);
    /// convert string to month
    static Month StringToMonth(const Util::String& str);
    /// convert weekday to string
    static Util::String WeekdayToString(Weekday d);
    /// convert string to weekday
    static Weekday StringToWeekday(const Util::String& str);

protected:
    Year year;
    Month month;
    Weekday weekday;
    Day day;
    Hour hour;
    Minute minute;
    Second second;
    MilliSecond milliSecond;
};

} // namespace Base
//------------------------------------------------------------------------------
