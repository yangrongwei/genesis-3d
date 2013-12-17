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
    @file timing/time.h
  
    Typedefs for the Timing subsystem
    
    (C) 2006 Radon Labs GmbH
*/    
#include "core/types.h"

//------------------------------------------------------------------------------
namespace Timing
{
/// the time datatype
typedef double Time;
/// the tick datatype (one tick == 1 millisecond)
typedef int Tick;

typedef uint64 MicrosecondTick;
//------------------------------------------------------------------------------
/**
    Convert ticks to seconds.
*/
inline Time
TicksToSeconds(Tick ticks)
{
    return ticks * 0.001;
}

//------------------------------------------------------------------------------
/**
    Convert seconds to ticks
*/
inline Tick
SecondsToTicks(Time t)
{
    // perform correct rounding
    return Tick((t * 1000.0) + 0.5);
}

//------------------------------------------------------------------------------
/**
    Put current thread to sleep for specified amount of seconds.
*/
inline void
Sleep(Time t)
{
    n_sleep(t);
}

};
//------------------------------------------------------------------------------
