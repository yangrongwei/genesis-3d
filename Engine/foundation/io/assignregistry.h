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
    @class IO::AssignRegistry
    
    Central registry for path assigns. This is a true singleton, visible
    from all threads.
*/
//#include "core/refcounted.h"
#include "io/assign.h"
#include "io/uri.h"
#include "util/hashtable.h"
//#include "threading/criticalsection.h"
#include "core/singleton.h"

//------------------------------------------------------------------------------
namespace IO
{
class AssignRegistry //: public Core::RefCounted
{
    //__DeclareClass(AssignRegistry);
    __DeclareImageSingleton(AssignRegistry);
public:
    /// constructor
    AssignRegistry();
    /// destructor
    virtual ~AssignRegistry();
    
    /// setup the assign registry (may only be called once from the main thread)
    void Setup();
    /// discard the assign registry
    void Discard();
    /// set a new assign
    void SetAssign(const Assign& assign);
    /// return true if an assign exists
    /// clear an assign
    void ClearAssign(const Util::String& assignName);

    /// return true if the object has been setup
    bool IsValid() const;
    bool HasAssign(const Util::String& assignName) const;
    /// get an assign
    Util::String GetAssign(const Util::String& assignName) const;

    /// return an array of all currently defined assigns
    Util::Array<Assign> GetAllAssigns() const;
    /// resolve any assigns in an URI
    URI ResolveAssigns(const URI& uri) const;
    /// resolve any assigns in a string (must have URI form)
    Util::String ResolveAssignsInString(const Util::String& uriString) const;

private:
    ///// setup standard system assigns (e.g. home:, etc...)
    //void SetupSystemAssigns();
    ///// setup standard project assigns (e.g. msh:, model:, etc...)
    //void SetupProjectAssigns();

    bool isValid;
    //Threading::CriticalSection critSect;
    Util::HashTable<Util::String, Util::String> assignTable;
};

} // namespace IO
//------------------------------------------------------------------------------
