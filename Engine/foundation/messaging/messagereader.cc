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

#include "stdneb.h"
#include "messaging/messagereader.h"
#include "core/factory.h"
#include "messaging/message.h"

namespace Messaging
{
__ImplementClass(Messaging::MessageReader, 'MGRR', IO::StreamReader);

using namespace IO;
using namespace Util;
using namespace Core;

//------------------------------------------------------------------------------
/**
*/
MessageReader::MessageReader()
{
    this->binaryReader = BinaryReader::Create();
}

//------------------------------------------------------------------------------
/**
*/
void
MessageReader::SetStream(const GPtr<IO::Stream>& s)
{
    n_assert(s.isvalid());
    StreamReader::SetStream(s);
    this->binaryReader->SetStream(s);
}

//------------------------------------------------------------------------------
/**
    This constructs a new message from the stream. First the FourCC class id
    of the message will be read, and a new message object constructed from
    it, then the message object will be asked to initialize itself from
    the stream.
*/
Message*
MessageReader::ReadMessage()
{
    // read FourCC from stream and build a new message
    FourCC classFourCC = this->binaryReader->ReadUInt();
    Message* msg = (Message*) Factory::Instance()->Create(classFourCC);

    // let message initialize itself from the rest of the stream
    msg->Decode(this->binaryReader);
    return msg;
}

} // namespace Messaging