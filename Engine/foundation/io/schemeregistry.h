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
    @class IO::SchemeRegistry
    
    Central registry for URI schemes, associates an URI scheme (e.g. http, 
    file, ...) with a Nebula3 stream class.
*/
#include "core/refcounted.h"
#include "core/singleton.h"    
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace IO
{
class SchemeRegistry : public Core::RefCounted
{
    __DeclareClass(SchemeRegistry);
    __DeclareImageSingleton(SchemeRegistry);
public:
    /// constructor
    SchemeRegistry();
    /// destructor
    virtual ~SchemeRegistry();
    
    /// setup the scheme registry (may only be called at app startup by the main thread)
    void Setup();
    /// discard the scheme registry
    void Discard();
    /// return true if the scheme registry is valid
    bool IsValid() const;

    /// associate an uri scheme with a stream class
    void RegisterUriScheme(const Util::String& uriScheme, const Core::Rtti& classRtti);
    /// unregister an uri scheme
    void UnregisterUriScheme(const Util::String& uriScheme);
    /// return true if an uri scheme has been registered
    bool IsUriSchemeRegistered(const Util::String& uriScheme) const;
    /// get the registered stream class for an uri scheme
    const Core::Rtti& GetStreamClassByUriScheme(const Util::String& uriScheme) const;
    /// get an array of all registered schemes
    Util::Array<Util::String> GetAllRegisteredUriSchemes() const;

private:
    /// register standard URI schemes, called by the Setup method
    void SetupStandardSchemes();

    Threading::CriticalSection critSect;
    Util::Dictionary<Util::String, const Core::Rtti*> schemeRegistry;
    bool isValid;
};

} // namespace IO
//------------------------------------------------------------------------------
