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

#ifndef __ANDROIDCALENDARTIME_H__
#define __ANDROIDCALENDARTIME_H__

#include "timing/base/calendartimebase.h"

namespace Android
{
	class AndroidCalendarTime : public Base::CalendarTimeBase
{
public:
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

private:
};

}

#endif