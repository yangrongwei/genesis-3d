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
#include "messaging/blockinghandlerthread.h"

namespace Messaging
{
__ImplementClass(Messaging::BlockingHandlerThread, 'BLHT', Messaging::HandlerThreadBase);

//------------------------------------------------------------------------------
/**
*/
BlockingHandlerThread::BlockingHandlerThread() :
    waitTimeout(200)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This adds a new message to the thread's message queue.
*/
void
BlockingHandlerThread::AddMessage(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    this->msgQueue.Enqueue(msg);
}

//------------------------------------------------------------------------------
/**
    This removes a message from the thread's message queue, regardless
    of its state.
*/
void
BlockingHandlerThread::CancelMessage(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    this->msgQueue.EraseMatchingElements(msg);
}

//------------------------------------------------------------------------------
/**
    This method is called by Thread::Stop() after setting the 
    stopRequest event and before waiting for the thread to stop.
*/
void
BlockingHandlerThread::EmitWakeupSignal()
{
    // wake up our thread if it's waiting for messages
    this->msgQueue.Signal();
}

//------------------------------------------------------------------------------
/**
    The message processing loop.
*/
void
BlockingHandlerThread::DoWork()
{
    this->ThreadOpenHandlers();
    while (!this->ThreadStopRequested())
    {
        // wait for next message, or timeout
        bool msgHandled = false;
        if (this->waitTimeout > 0)
        {
            this->msgQueue.WaitTimeout(this->waitTimeout);
        }
        else
        {
            this->msgQueue.Wait();
        }
        
        // update state of deferred messages
        msgHandled = this->ThreadUpdateDeferredMessages();

        // process messages
        if (!this->msgQueue.IsEmpty())
        {
            Util::Array<GPtr<Message> > msgArray;
            //this->msgQueue.DequeueAll(msgArray);
			this->msgQueue.DequeueAllBySwap(msgArray);
            msgHandled |= this->ThreadHandleMessages(msgArray);
        }
        // signal if at least one message has been handled
        if (msgHandled)
        {
            this->ThreadSignalMessageHandled();
        }

        // do per-frame update on attached handlers
        this->ThreadUpdateHandlers();
    }

    // cleanup and exit thread
    this->ThreadDiscardDeferredMessages();
    this->ThreadCloseHandlers();
}

} // namespace Messaging