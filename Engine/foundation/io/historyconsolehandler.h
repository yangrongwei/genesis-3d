/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
    @class IO::HistoryConsoleHandler
    
    A console handler which stores the last N log messages in a
    Util::RingBuffer<String>.
    
    (C) 2008 Radon Labs GmbH
*/
#include "io/consolehandler.h"
#include "util/ringbuffer.h"

//------------------------------------------------------------------------------
namespace IO
{
class HistoryConsoleHandler : public ConsoleHandler
{
    __DeclareClass(HistoryConsoleHandler);
public:
    /// constructor
    HistoryConsoleHandler();

    /// set history size
    void SetHistorySize(SizeT numLines);
    /// get history size
    SizeT GetHistorySize() const;
    /// get accumulated log messages
    const Util::RingBuffer<Util::String>& GetHistory() const;

    /// called by console to output data
    virtual void Print(const Util::String& s);
    /// called by console with serious error
    virtual void Error(const Util::String& s);
    /// called by console to output warning
    virtual void Warning(const Util::String& s);
    /// called by console to output debug string
    virtual void DebugOut(const Util::String& s);

private:
    Util::RingBuffer<Util::String> history;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HistoryConsoleHandler::SetHistorySize(SizeT numLines)
{
    this->history.SetCapacity(numLines);
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
HistoryConsoleHandler::GetHistorySize() const
{
    return this->history.Size();
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::RingBuffer<Util::String>&
HistoryConsoleHandler::GetHistory() const
{
    return this->history;
}

} // namespace IO
//------------------------------------------------------------------------------
