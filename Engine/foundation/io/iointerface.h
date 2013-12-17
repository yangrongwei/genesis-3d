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
    @class IO::Interface
    
    Implements the asynchronous interface to the IO subsystem. This will
    run a minimal Nebula3 runtime with an IO subsystem in an extra thread.
    Communication with the IO::Interface happens by sending messages to
    the Interface object. Messages are guaranteed to be handled sequentially 
    in FIFO order (there's exactly one handler thread which handles all 
    messages).
*/
#include "interface/interfacebase.h"
#include "io/console.h"
#include "io/iointerfaceprotocol.h"

//------------------------------------------------------------------------------
namespace IO
{
class IoInterface : public Interface::InterfaceBase
{
    __DeclareClass(IoInterface);
    __DeclareImageSingleton(IoInterface);
public:
    /// constructor
    IoInterface();
    /// destructor
    virtual ~IoInterface();
    /// open the interface object
    virtual void Open();

	/// begin by Zeng Zhuo 2011.11.7
	bool IsAsynLoad( const URI& uri ) ;
	/// end by Zeng Zhuo 2011.11.7
};

} // namespace IO
//------------------------------------------------------------------------------
    