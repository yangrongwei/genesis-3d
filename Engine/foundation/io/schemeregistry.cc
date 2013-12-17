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
#include "stdneb.h"
#include "io/schemeregistry.h"
#include "io/stream.h"
#include "io/filestream.h"
#include "http/httpstream.h"
#include "http/httpnzstream.h"

namespace IO
{
__ImplementClass(IO::SchemeRegistry, 'SCRG', Core::RefCounted);
__ImplementImageSingleton(IO::SchemeRegistry);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
SchemeRegistry::SchemeRegistry() :
    isValid(false)
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
SchemeRegistry::~SchemeRegistry()
{
    if (this->IsValid())
    {
        this->Discard();
    }
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
SchemeRegistry::Setup()
{
    this->critSect.Enter();

    n_assert(!this->IsValid());
    this->isValid = true;
    this->SetupStandardSchemes();
    
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
SchemeRegistry::Discard()
{
    this->critSect.Enter();

    n_assert(this->IsValid());
    this->isValid = false;
    this->schemeRegistry.Clear();

    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
bool
SchemeRegistry::IsValid() const
{
    return this->isValid;
}

//------------------------------------------------------------------------------
/**
    Associates an URI scheme with a stream class. If the same URI
    scheme is already registered, the old association will be overwritten.
*/
void
SchemeRegistry::RegisterUriScheme(const String& uriScheme, const Core::Rtti& classRtti)
{
    this->critSect.Enter();

    n_assert(classRtti.IsDerivedFrom(Stream::RTTI));
    n_assert(uriScheme.IsValid());
    if (this->schemeRegistry.Contains(uriScheme))
    {
        this->UnregisterUriScheme(uriScheme);
    }
    this->schemeRegistry.Add(uriScheme, &classRtti);

    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
SchemeRegistry::UnregisterUriScheme(const String& uriScheme)
{
    this->critSect.Enter();

    n_assert(uriScheme.IsValid());
    n_assert(this->schemeRegistry.Contains(uriScheme));
    this->schemeRegistry.Erase(uriScheme);

    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
bool
SchemeRegistry::IsUriSchemeRegistered(const String& uriScheme) const
{
    this->critSect.Enter();
    n_assert(uriScheme.IsValid());
    bool result = this->schemeRegistry.Contains(uriScheme);
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
const Core::Rtti&
SchemeRegistry::GetStreamClassByUriScheme(const String& uriScheme) const
{
    this->critSect.Enter();
    n_assert(uriScheme.IsValid());
    const Core::Rtti& result = *(this->schemeRegistry[uriScheme]);
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
Array<String> 
SchemeRegistry::GetAllRegisteredUriSchemes() const
{
    this->critSect.Enter();
    Array<String> result = this->schemeRegistry.KeysAsArray();
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
    Registers the standard URI schemes.
    NOTE: private method, thus no critical section protection is necessary!
*/
void
SchemeRegistry::SetupStandardSchemes()
{
    this->RegisterUriScheme("file", FileStream::RTTI);

#if __NEBULA3_HTTP_FILESYSTEM__
    this->RegisterUriScheme("http", Http::HttpStream::RTTI);
    this->RegisterUriScheme("httpnz", Http::HttpNzStream::RTTI);
#endif
}

} // namespace IO
