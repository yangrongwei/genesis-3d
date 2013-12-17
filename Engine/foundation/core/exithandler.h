/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
    @class Core::ExitHandler
    
    ExitHandlers are static objects which register themselves automatically
    once at startup and are called back from the Core::SysFunc::Exit()
    static method which is called right before a Nebula3 application exists.  
    Please note that the Nebula3 runtime usually doesn't yet exist when
    the ExitHandler is created or destroyed, so don't put anything complex
    into the constructor or destructor of the class!
*/    
#include "core/types.h"

//------------------------------------------------------------------------------
namespace Core
{
class ExitHandler
{
public:
    /// constructor
    ExitHandler();
    /// destructor
    virtual ~ExitHandler();
    /// virtual method called from SysFunc::Exit()
    virtual void OnExit() const;
    /// get pointer to next exit handler in forward linked list
    const ExitHandler* Next() const;

private:
    const ExitHandler* nextExitHandler; // for forward linking...
};

} // namespace Core
//------------------------------------------------------------------------------
