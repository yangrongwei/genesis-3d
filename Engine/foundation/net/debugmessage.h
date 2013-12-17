#pragma once
/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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

#include "core/types.h"
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace Net
{
class DebugMessage
{
public:
    /// default constructor
    DebugMessage();
    /// constructor
    DebugMessage(ushort port, const GPtr<IO::Stream>& data);
    /// get the port number
    ushort GetPort() const;
    /// get the data stream
    const GPtr<IO::Stream>& GetStream() const;
    /// return true if the message is valid
    bool IsValid() const;
    
private:
    ushort portNum;
    GPtr<IO::Stream> dataStream;
};

//------------------------------------------------------------------------------
/**
*/
inline 
DebugMessage::DebugMessage() :
    portNum(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
DebugMessage::DebugMessage(ushort p, const GPtr<IO::Stream>& s) :
    portNum(p),
    dataStream(s)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline ushort
DebugMessage::GetPort() const
{
    return this->portNum;
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<IO::Stream>&
DebugMessage::GetStream() const
{
    return this->dataStream;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
DebugMessage::IsValid() const
{
    return this->dataStream.isvalid();
}

} // namespace Net
//------------------------------------------------------------------------------

