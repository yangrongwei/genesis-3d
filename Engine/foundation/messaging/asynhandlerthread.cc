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
#include "messaging/asynhandlerthread.h"
#include "messaging/batchmessage.h"
namespace Messaging
{
__ImplementClass(Messaging::AsynHandlerThread, 'ASHT', Messaging::HandlerThreadBase);

//------------------------------------------------------------------------------
/**
*/
AsynHandlerThread::AsynHandlerThread() :
    waitTimeout(200)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This adds a new message to the thread's message queue.
*/
void
AsynHandlerThread::AddMessage(const MessagePtr& msg)
{
    n_assert(msg.isvalid());
    this->msgQueue.Enqueue(msg);
}
//------------------------------------------------------------------------------
/**
*/
void
AsynHandlerThread::WaitForMessage(const GPtr<Message>& msg)
{
	while (!msg->Handled())
	{
		n_sleep(0.005);//this->msgHandledEvent.Wait();
	}
}
//------------------------------------------------------------------------------
/**
    This removes a message from the thread's message queue, regardless
    of its state.
*/
void
AsynHandlerThread::CancelMessage(const MessagePtr& msg)
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
AsynHandlerThread::EmitWakeupSignal()
{
    // wake up our thread if it's waiting for messages
    this->msgQueue.Signal();
}

//------------------------------------------------------------------------------
/**
    The message processing loop.
*/
void
AsynHandlerThread::DoWork()
{
    this->ThreadOpenHandlers();
    while (!this->ThreadStopRequested())
    {
        if (this->waitTimeout > 0)
        {
            this->msgQueue.WaitTimeout(this->waitTimeout);
        }
        else
        {
            this->msgQueue.Wait();
        }
        
        //// update state of deferred messages
        //msgHandled = this->ThreadUpdateDeferredMessages();

        // process messages
        if (!this->msgQueue.IsEmpty())
        {
            Util::Array<MessagePtr> msgArray;
            //this->msgQueue.DequeueAll(msgArray);
			this->msgQueue.DequeueAllBySwap(msgArray);
            this->_ThreadHandleMessages(msgArray);
        }
        // signal if at least one message has been handled
        this->ThreadSignalMessageHandled();

        // do per-frame update on attached handlers
        this->ThreadUpdateHandlers();
    }

    // cleanup and exit thread
    //this->ThreadDiscardDeferredMessages();
    this->ThreadCloseHandlers();
}

void
AsynHandlerThread::_ThreadHandleMessages(const Messages& msgArray)
{
	this->handlersCritSect.Enter();

	IndexT msgIdx;
	for (msgIdx = 0; msgIdx < msgArray.Size(); ++msgIdx)
	{
		const GPtr<Message>& msg = msgArray[msgIdx];
		// special case: batch message?
		if (msg->CheckId(BatchMessage::Id))
		{
			// process batched messages
			const Util::Array<GPtr<Message> >& msgBatch = msg.cast<BatchMessage>()->GetMessages();
			IndexT msgBatchIndex;
			for (msgBatchIndex = 0; msgBatchIndex < msgBatch.Size(); msgBatchIndex++)
			{
				this->_ThreadHandleSingleMessage(msgBatch[msgBatchIndex]);
			}
		}
		else
		{
			// a normal message
			this->_ThreadHandleSingleMessage(msg);
		}
	}
	this->handlersCritSect.Leave();
}

void
AsynHandlerThread::_ThreadHandleSingleMessage(const MessagePtr& msg)
{
	// let each handler look at the message
	IndexT i;
	for (i = 0; i < this->handlers.Size(); i++)
	{    
		const GPtr<Handler>& curHandler = this->handlers[i];

		// open handler on demand (a handler may have
		// been added as the result of a message call,
		// so let's make sure it will be able to handle 
		// message as soon as possible
		if (!curHandler->IsOpen())
		{
			curHandler->Open();
		}

		// let handler handle the current message
		if (curHandler->HandleMessage(msg))
		{
			// break after the first handler accepts the message
			break;
		}
	}
}

} // namespace Messaging