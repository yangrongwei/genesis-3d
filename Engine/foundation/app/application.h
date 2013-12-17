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
#include "core/types.h"
#include "core/singleton.h"
#include "util/string.h"
#include "util/commandlineargs.h"
#include "system/appentry.h"
//------------------------------------------------------------------------------
namespace App
{
class Application
{
    __DeclareThreadSingleton(Application);
public:
    /// constructor
    Application();
    /// destructor
    virtual ~Application();
    /// set company name
    void SetCompanyName(const Util::String& n);
    /// get company name
    const Util::String& GetCompanyName() const;
    /// set application name
    void SetAppTitle(const Util::String& n);
    /// get application name
    const Util::String& GetAppTitle() const;
    /// set application id
    void SetAppID(const Util::String& n);
    /// get application id
    const Util::String& GetAppID() const;   
    /// set application version
    void SetAppVersion(const Util::String& n);
    /// get application version
    const Util::String& GetAppVersion() const;
    /// set command line args
    void SetCmdLineArgs(const Util::CommandLineArgs& a);
    /// get command line args
    const Util::CommandLineArgs& GetCmdLineArgs() const;

    /// return true if app is open
    bool IsOpen() const;
	/// return true if app is start
	bool IsStart() const;
    /// get the return code
    int GetReturnCode() const;

    /// open the application
    virtual bool Open();
	/// start the application
	virtual bool Start();
    /// close the application
    virtual void Close();
    /// exit the application, call right before leaving main()
    virtual void Exit();
    /// run the application, return when user wants to exit
    virtual void Run();
	/// destroy TLS
	static void ShutDown();
protected:
    /// set return code
    void SetReturnCode(int c);

    Util::String companyName;
    Util::String appName;
    Util::String appID;
    Util::String appVersion;
    Util::CommandLineArgs args;
    bool isOpen;
	bool isStart;
    int returnCode;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
Application::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/

inline
bool
Application::IsStart() const
{
	return this->isStart;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
Application::SetCompanyName(const Util::String& n)
{
    this->companyName = n;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::String&
Application::GetCompanyName() const
{
    return this->companyName;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
Application::SetAppTitle(const Util::String& n)
{
    this->appName = n;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::String&
Application::GetAppTitle() const
{
    return this->appName;
}     

//------------------------------------------------------------------------------
/**
*/
inline
void
Application::SetAppID(const Util::String& n)
{
    this->appID = n;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::String&
Application::GetAppID() const
{
    return this->appID;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
Application::SetAppVersion(const Util::String& n)
{
    this->appVersion = n;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::String&
Application::GetAppVersion() const
{
    return this->appVersion;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
Application::SetCmdLineArgs(const Util::CommandLineArgs& a)
{
    this->args = a;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::CommandLineArgs&
Application::GetCmdLineArgs() const
{
    return this->args;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Application::SetReturnCode(int c)
{
    this->returnCode = c;
}

//------------------------------------------------------------------------------
/**
*/
inline int
Application::GetReturnCode() const
{
    return this->returnCode;
}

} // namespace App
//------------------------------------------------------------------------------
