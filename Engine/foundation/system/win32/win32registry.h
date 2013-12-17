/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
    @class System::Win32Registry
    
    A simple wrapper class to access the Win32 registry.
    NOTE: using this class restricts your code to the Win32 platform.

*/
#include "core/types.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace System
{
class Win32Registry
{
public:
    /// key enumeration
    enum RootKey
    {
        ClassesRoot,
        CurrentUser,
        LocalMachine,
        Users,
    };

    /// return true if a registry entry exists
    static bool Exists(RootKey rootKey, const Util::String& key, const Util::String& name);
    /// write a registry entry
    static bool WriteString(RootKey rootKey, const Util::String& key, const Util::String& name, const Util::String& value);
    /// read a string registry entry, the string will be UTF-8 encoded!
    static Util::String ReadString(RootKey rootKey, const Util::String& key, const Util::String& name);
    /// read an int registry entry
    static int ReadInt(RootKey rootKey, const Util::String& key, const Util::String& name);
    /// delete a registry key (and all its contained values)
    static bool Delete(RootKey rootKey, const Util::String& key);
    /// convert rootkey from string
    static RootKey AsRootKey(const Util::String& str);
private:
    /// convert RootKey enum into Win32 key handle
    static HKEY RootKeyToWin32KeyHandle(RootKey rootKey);
};

} // namespace System
//------------------------------------------------------------------------------
