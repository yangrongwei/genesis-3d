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
    @class Core::CoreServer
    
    The central core server object initializes a minimal Nebula3 runtime
    environment necessary to boot up the rest of Nebula3. It should be the
    first object a Nebula3 application creates, and the last to destroy
    before shutdown.
*/    
#include "core/ptr.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "io/console.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
namespace Core
{
class CoreServer : public RefCounted
{
    __DeclareClass(CoreServer);
    __DeclareThreadSingleton(CoreServer);
public:
    /// constructor
    CoreServer();
    /// destructor
    virtual ~CoreServer();
    /// set the company name
    void SetCompanyName(const Util::StringAtom& s);
    /// get the company name
    const Util::StringAtom& GetCompanyName() const;
    /// set the application name
    void SetAppName(const Util::StringAtom& s);
    /// get the application name
    const Util::StringAtom& GetAppName() const;
    /// set the root directory of the application (default is "home:")
    void SetRootDirectory(const Util::StringAtom& s);
    /// get the root directory of the application
    const Util::StringAtom& GetRootDirectory() const;

    /// open the core server
    void Open();
    /// close the core server
    void Close();
    /// return true if currently open
    bool IsOpen() const;
    /// trigger core server, updates console
    void Trigger();

private:
    GPtr<IO::Console> con;
    Util::StringAtom companyName;
    Util::StringAtom appName;
    Util::StringAtom rootDirectory;
    bool isOpen;
};

//------------------------------------------------------------------------------
/*
*/
inline bool
CoreServer::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/*
*/
inline void
CoreServer::SetCompanyName(const Util::StringAtom& s)
{
    this->companyName = s;
}

//------------------------------------------------------------------------------
/*
*/
inline const Util::StringAtom&
CoreServer::GetCompanyName() const
{
    return this->companyName;
}

//------------------------------------------------------------------------------
/*
*/
inline void
CoreServer::SetAppName(const Util::StringAtom& s)
{
    this->appName = s;
}

//------------------------------------------------------------------------------
/*
*/
inline const Util::StringAtom&
CoreServer::GetAppName() const
{
    return this->appName;
}

//------------------------------------------------------------------------------
/*
*/
inline void
CoreServer::SetRootDirectory(const Util::StringAtom& s)
{
    this->rootDirectory = s;
}

//------------------------------------------------------------------------------
/*
*/
inline const Util::StringAtom&
CoreServer::GetRootDirectory() const
{
    return this->rootDirectory;
}

} // namespace Core
//------------------------------------------------------------------------------
