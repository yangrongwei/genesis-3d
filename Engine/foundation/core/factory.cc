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
#include "stdneb.h"
#include "core/factory.h"
#include "core/refcounted.h"
#include "core/rtti.h"
#include "core/sysfunc.h"

namespace Core
{
Factory* Factory::Singleton = 0;
using namespace Util;

//------------------------------------------------------------------------------
/**
    The factory's constructor is called by the Instance() method, and 
    nobody else.
*/
Factory*
Factory::Instance()
{
    if (0 == Singleton)
    {
        Singleton = n_new(Factory);
        n_assert(0 != Singleton);
    }
    return Singleton;
}

//------------------------------------------------------------------------------
/**
    This static method is used to destroy the factory object and should be
    called right before the main function exits. It will make sure that
    no accidential memory leaks are reported by the debug heap.
*/
void
Factory::Destroy()
{
    if (0 != Singleton)
    {
        n_delete(Singleton);
        Singleton = 0;
    }
}

//------------------------------------------------------------------------------
/**
    The factory's constructor is private so that it may only be called 
    by Factory::Instance().
*/
Factory::Factory() :
    nameTable(512)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    The factory's destructor is private so that it may only be called
    by Factory::Destroy().
*/
Factory::~Factory()
{
    this->nameTable.Clear();
    this->fourccTable.Clear();
}

//------------------------------------------------------------------------------
/**
    This registers an Rtti object with the factory and is called from
    an Rtti object's constructor. The function will fail with an error
    message box if a class with an identical class name or fourcc code
    has already been registered.

    NOTE: we cannot use the class name of fourcc from the RTTI object, 
    because it may be that the RTTI object hasn't been initialized yet
    when this method is called (initialization order of global variables
    is undefined).
*/
void
Factory::Register(const Rtti* rtti, const String& className, const FourCC& classFourCC)
{
    n_assert(0 != rtti);

    // check if class name already exists
    if (this->ClassExists(className))
    {
        // NOTE: can't use n_error() here, because Console is not setup yet
        // when this method Register() is called!
        String errorMsg;
        errorMsg.Format("Class name '%s' has already been registered!", className.AsCharPtr());
        SysFunc::Error(errorMsg.AsCharPtr());
        return;
    }

    // check if class fourcc already exists
    if (this->ClassExists(classFourCC))
    {
        // NOTE: can't use n_error() here, because Console is not setup yet
        // when this method Register() is called!
        String errorMsg;
        errorMsg.Format("Class fourcc '%s' (name: %s) has already been registered!", 
            classFourCC.AsString().AsCharPtr(),
            className.AsCharPtr());
        SysFunc::Error(errorMsg.AsCharPtr());
        return;
    }

    // register with lookup tables
    this->nameTable.Add(className, rtti);
    this->fourccTable.Add(classFourCC, rtti);
}

//------------------------------------------------------------------------------
/**
    Legacy version of Register() which doesn't require a class fourcc code.
    This is for compatibility with old Mangalore applications.
*/
void
Factory::Register(const Rtti* rtti, const String& className)
{
    n_assert(0 != rtti);

    // check if class name already exists
    if (this->ClassExists(className))
    {
        // NOTE: can't use n_error() here, because Console is not setup yet
        // when this method Register() is called!
        String errorMsg;
        errorMsg.Format("Class name '%s' has already been registered!", className.AsCharPtr());
        SysFunc::Error(errorMsg.AsCharPtr());
        return;
    }

    // register with lookup tables
    this->nameTable.Add(className, rtti);
}

//------------------------------------------------------------------------------
/**
    This method checks if a class with the given name has been registered.
*/
bool
Factory::ClassExists(const String& className) const
{
    //n_assert(className.IsValid());
	if (!className.IsValid())
	{
		return false;
	}
    return this->nameTable.Contains(className);
}

//------------------------------------------------------------------------------
/**
    This method checks if a class with the given fourcc code has been
    registered.
*/
bool
Factory::ClassExists(const FourCC fourCC) const
{
    //n_assert(fourCC.IsValid());
	if (!fourCC.IsValid())
	{
		return false;
	}
    return this->fourccTable.Contains(fourCC);
}

//------------------------------------------------------------------------------
/**
*/
const Rtti*
Factory::GetClassRtti(const String& className) const
{
    n_assert(className.IsValid());
    n_assert(this->ClassExists(className));
    return this->nameTable[className];
}

//------------------------------------------------------------------------------
/**
*/
const Rtti*
Factory::GetClassRtti(const FourCC& classFourCC) const
{
    n_assert(classFourCC.IsValid());
    n_assert(this->ClassExists(classFourCC));
    return this->fourccTable[classFourCC];
}

//------------------------------------------------------------------------------
/**
    Create an object by class name.
*/
RefCounted*
Factory::Create(const String& className) const
{
    n_assert(className.IsValid());
    
    // check if class exists, otherwise give a meaningful error
    if (!this->ClassExists(className))
    {
        String errorMsg;
        errorMsg.Format("Factory::Create('%s'): unknown class name!", className.AsCharPtr());
        SysFunc::Error(errorMsg.AsCharPtr());
        return 0;
    }

    // lookup RTTI object of class through hash table and create new object
    const Rtti* rtti = this->nameTable[className];
    n_assert(0 != rtti);
    RefCounted* newObject = rtti->Create();
    return newObject;
}

//------------------------------------------------------------------------------
/**
    Create an object by FourCC code.
*/
RefCounted*
Factory::Create(const FourCC classFourCC) const
{
    n_assert(classFourCC.IsValid());

    // check if class exists, otherwise give meaningful error
    if (!this->ClassExists(classFourCC))
    {
        String errorMsg;
        errorMsg.Format("Factory::Create('%s'): unknown class FourCC code!", classFourCC.AsString().AsCharPtr());
        SysFunc::Error(errorMsg.AsCharPtr());
        return 0;
    }

    // lookup RTTI object of class through hash table and create new object
    const Rtti* rtti = this->fourccTable[classFourCC];
    n_assert(0 != rtti);
    RefCounted* newObject = rtti->Create();
    return newObject;
}

} // namespace Core