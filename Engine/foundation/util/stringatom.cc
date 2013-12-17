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
#include "util/stringatom.h"
#include "util/localstringatomtable.h"
#include "util/globalstringatomtable.h"

#include <string.h>

namespace Util
{

//------------------------------------------------------------------------------
/**
*/
void
StringAtom::Setup(const char* str)
{
    #if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
        // first check our thread-local string atom table whether the string
        // is already registered there, this does not require any thread
        // synchronisation
        LocalStringAtomTable* localTable = LocalStringAtomTable::Instance();
        this->content = localTable->Find(str);
        if (0 != this->content)
        {
            // yep, the string is in the local table, we're done
            return;
        }
    #endif

    // the string wasn't in the local table (or thread-local tables are disabled), 
    // so we need to check the global table, this involves thread synchronisation
    GlobalStringAtomTable* globalTable = GlobalStringAtomTable::Instance();
    globalTable->Lock();
    this->content = globalTable->Find(str);
    if (0 == this->content)
    {
        // hrmpf, string isn't in global table either yet, so add it...
        this->content = globalTable->Add(str);
    }
    globalTable->Unlock();

    #if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
        // finally, add the new string to our local table as well, so the
        // next lookup from our thread of this string will be faster
        localTable->Add(this->content);
    #endif
}

//------------------------------------------------------------------------------
/**
    Compare with raw string. Careful, slow!
*/
bool
StringAtom::operator==(const char* rhs) const
{
    if (0 == this->content)
    {
        return false;
    }
    else
    {
        return (0 == strcmp(this->content, rhs));
    }
}

//------------------------------------------------------------------------------
/**
    Compare with raw string. Careful, slow!
*/
bool
StringAtom::operator!=(const char* rhs) const
{
    if (0 == this->content)
    {
        return false;
    }
    else
    {
        return (0 == strcmp(this->content, rhs));
    }
}

} // namespace Util