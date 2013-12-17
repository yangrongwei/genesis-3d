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

#include "stdneb.h"
#if !__WII__
#include "net/messageclient.h"

namespace Net
{
__ImplementClass(Net::MessageClient,'MSGC',Net::TcpClient);

using namespace IO;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
MessageClient::MessageClient()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
MessageClient::~MessageClient()
{
    if (this->IsConnected())
    {
        this->Disconnect();
    }
}

//------------------------------------------------------------------------------
/**
    Establish a connection with the server. See TcpClient for details.
*/
TcpClient::Result
MessageClient::Connect()
{
    n_assert(!this->sendMessageStream.isvalid());
    n_assert(!this->recvMessageStream.isvalid());
    TcpClient::Result res = TcpClient::Connect();
    if (TcpClient::Success == res)
    {
        this->sendMessageStream = MemoryStream::Create();
    }
    return res;
}

//------------------------------------------------------------------------------
/**
*/
void
MessageClient::Disconnect()
{
    TcpClient::Disconnect();
    this->sendMessageStream = 0;
    this->recvMessageStream = 0;
}

//------------------------------------------------------------------------------
/**
*/
bool
MessageClient::Send()
{
    n_assert(this->sendMessageStream.isvalid());
    if (this->sendMessageStream->GetSize() == 0)
    {
        // nothing to send
        return Socket::Success;
    }
    Socket::Result res = Socket::Error;
    this->sendMessageStream->SetAccessMode(Stream::ReadAccess);
    this->codec.EncodeToMessage(this->sendMessageStream,TcpClient::GetSendStream());
    this->sendMessageStream->SetSize(0);
    return TcpClient::Send();
}

//------------------------------------------------------------------------------
/**
*/
const GPtr<IO::Stream>&
MessageClient::GetSendStream()
{
    return this->sendMessageStream;
}

//------------------------------------------------------------------------------
/**
*/
bool
MessageClient::Recv()
{
    // first check if new data is available from the socket
    if (TcpClient::Recv())
    {
        // decode incoming data into separate message, and queue the
        // message for later use
        this->codec.DecodeStream(this->recvStream);
        if (this->codec.HasMessages())
        {
            Array<GPtr<Stream> > msgArray = this->codec.DequeueMessages();
            IndexT i;
            for (i = 0; i < msgArray.Size(); i++)
            {
                this->msgQueue.Enqueue(msgArray[i]);
            }
        }
    }

    // set the oldest received message from the message queue
    // as receive stream (we either return 1 complete message,
    // or none at all per call to Recv()
    if (!this->msgQueue.IsEmpty())
    {
        this->recvMessageStream = this->msgQueue.Dequeue();
        return true;
    }
    else
    {
        // no messages to return
        return false;
    }
}

//------------------------------------------------------------------------------
/**
*/
const GPtr<IO::Stream>&
MessageClient::GetRecvStream()
{
    return this->recvMessageStream;
}

} // namespace Net

#endif // #if not __WII__