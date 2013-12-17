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
    @class IO::IoInterfaceHandler
    
    Handler class for io interfaces.
    
*/
#include "interface/interfacehandlerbase.h"
#include "io/console.h"
#include "io/iointerfaceprotocol.h"
#if __NEBULA3_HTTP_FILESYSTEM__
#include "http/httpclientregistry.h"
#endif

//------------------------------------------------------------------------------
namespace IO
{
class IoServer;

class IoInterfaceHandler : public Interface::InterfaceHandlerBase
{
    __DeclareClass(IoInterfaceHandler);
public:
    /// constructor
    IoInterfaceHandler();
    /// destructor
    virtual ~IoInterfaceHandler();
    
    /// open the handler
    virtual void Open();
    /// close the handler
    virtual void Close();
    /// handle a message, return true if handled
    virtual bool HandleMessage(const GPtr<Messaging::Message>& msg);
	/// for continuous work
    virtual void DoWork();
protected:
    /// handle CreateDirectory message
    void OnCreateDirectory(const GPtr<IO::CreateDirectory>& msg);
    /// handle DeleteDirectory message
    void OnDeleteDirectory(const GPtr<IO::DeleteDirectory>& msg);
    /// handle DeleteFile message
    void OnDeleteFile(const GPtr<IO::DeleteFile>& msg);
    /// handle WriteStream message
    void OnWriteStream(const GPtr<IO::WriteStream>& msg);
    /// handle ReadStream message
    void OnReadStream(const GPtr<IO::ReadStream>& msg);
    /// handle CopyFile message
    void OnCopyFile(const GPtr<IO::CopyFile>& msg);
    /// handle MountArchive message
    void OnMountArchive(const GPtr<IO::MountArchive>& msg);

    GPtr<IO::IoServer> ioServer;
    //#if __NEBULA3_HTTP_FILESYSTEM__
    //GPtr<Http::HttpClientRegistry> httpClientRegistry;
    //#endif

};

} // namespace IO
//------------------------------------------------------------------------------
    
    