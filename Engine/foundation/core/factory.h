/****************************************************************************
Copyright (c) 2005, Radon Labs GmbH
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
    @class Core::Factory

    Provides the central object factory mechanism for Nebula3. Classes
    which are derived from RefCounted register themselves automatically
    to the central Factory object through the __DeclareClass and
    __ImplementClass macros.
*/
#include "util/array.h"
#include "util/string.h"
#include "util/fourcc.h"
#include "util/dictionary.h"
#include "util/hashtable.h"
#include "core/ptr.h"

//------------------------------------------------------------------------------
namespace Core 
{
class RefCounted;
class Rtti;

//------------------------------------------------------------------------------
class Factory
{
public:
    /// get pointer to singleton instance (cannot use singleton.h!)
    static Factory* Instance();
    /// static instance destruction method
    static void Destroy();

    /// register a RTTI object with the factory (with class name and class fourcc code)
    void Register(const Rtti* rtti, const Util::String& className, const Util::FourCC& classFourCC);
    /// register a RTTI object with the factory (without fourcc code)
    void Register(const Rtti* rtti, const Util::String& className);
    /// check if a class exists by class name
    bool ClassExists(const Util::String& className) const;
    /// check if a class exists by FourCC code
    bool ClassExists(const Util::FourCC classFourCC) const;
    /// get class rtti object by name
    const Rtti* GetClassRtti(const Util::String& className) const;
    /// get class rtti object by fourcc code
    const Rtti* GetClassRtti(const Util::FourCC& classFourCC) const;
    /// create an object by class name
    RefCounted* Create(const Util::String& className) const;
    /// create an object by FourCC code
    RefCounted* Create(const Util::FourCC classFourCC) const;

private:
    /// constructor is private
    Factory();
    /// destructor is private
    ~Factory();

    static Factory* Singleton;
    Util::HashTable<Util::String, const Rtti*> nameTable;     // for fast lookup by class name
    Util::Dictionary<Util::FourCC, const Rtti*> fourccTable;  // for fast lookup by fourcc code
};

} // namespace Foundation
//------------------------------------------------------------------------------
