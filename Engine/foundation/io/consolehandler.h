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
    @class IO::ConsoleHandler

    Base class for all console handlers. Console handlers are attached to
    Nebula3's central console object and are notified by the console
    object about output and deliver input to the console.
*/
#include "core/refcounted.h"
#include "util/array.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace IO
{
class ConsoleHandler : public Core::RefCounted
{
    __DeclareClass(ConsoleHandler);
public:
    /// constructor
    ConsoleHandler();
    /// destructor
    virtual ~ConsoleHandler();
    /// called by console when attached
    virtual void Open();
    /// called by console when removed
    virtual void Close();
    /// return true if currently open
    bool IsOpen() const;
    /// called by Console::Update()
    virtual void Update();
    /// called by console to output data
    virtual void Print(const Util::String& s);
    /// called by console with serious error
    virtual void Error(const Util::String& s);
    /// called by console to output warning
    virtual void Warning(const Util::String& s);
    /// called by console to display a confirmation message box
    virtual void Confirm(const Util::String& s);
    /// called by console to output debug string
    virtual void DebugOut(const Util::String& s);
    /// return true if input is available
    virtual bool HasInput();
    /// read available input
    virtual Util::String GetInput();

private:
    bool isOpen;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
ConsoleHandler::IsOpen() const
{
    return this->isOpen;
}

} // namespace IO
//------------------------------------------------------------------------------
