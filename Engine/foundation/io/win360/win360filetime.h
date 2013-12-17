/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
    @class Win360::Win360FileTime
    
    Implements a Win32/Xbox360-specific file-access time stamp.
*/
#include "core/types.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Win360
{
class Win360FileTime
{
public:
    /// constructor
    Win360FileTime();
    /// construct from string
    Win360FileTime(const Util::String& str);
    /// operator ==
    friend bool operator==(const Win360FileTime& a, const Win360FileTime& b);
    /// operator !=
    friend bool operator!=(const Win360FileTime& a, const Win360FileTime& b);
    /// operator >
    friend bool operator>(const Win360FileTime& a, const Win360FileTime& b);
    /// operator <
    friend bool operator<(const Win360FileTime& a, const Win360FileTime& b);
    /// convert to string
    Util::String AsString() const;

    FILETIME time;
};

//------------------------------------------------------------------------------
/**
*/
inline
Win360FileTime::Win360FileTime()
{
    time.dwLowDateTime = 0;
    time.dwHighDateTime = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool 
operator==(const Win360FileTime& a, const Win360FileTime& b)
{
    return (0 == CompareFileTime(&(a.time), &(b.time)));
}

//------------------------------------------------------------------------------
/**
*/
inline bool 
operator!=(const Win360FileTime& a, const Win360FileTime& b)
{
    return (0 != CompareFileTime(&(a.time), &(b.time)));
}

//------------------------------------------------------------------------------
/**
*/
inline bool
operator>(const Win360FileTime& a, const Win360FileTime& b)
{
    return (1 == CompareFileTime(&(a.time), &(b.time)));
}

//------------------------------------------------------------------------------
/**
*/
inline bool
operator <(const Win360FileTime& a, const Win360FileTime& b)
{
    return (-1 == CompareFileTime(&(a.time), &(b.time)));
}

}; // namespace Win360
//------------------------------------------------------------------------------
