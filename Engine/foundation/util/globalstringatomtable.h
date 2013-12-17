#pragma once
/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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

#include "util/stringatomtablebase.h"
#include "core/singleton.h"
#include "threading/criticalsection.h"
#include "util/stringbuffer.h"

//------------------------------------------------------------------------------
namespace Util
{
class GlobalStringAtomTable : public StringAtomTableBase
{
    __DeclareImageSingleton(GlobalStringAtomTable);
public:
    /// constructor
    GlobalStringAtomTable();
    /// destructor
    ~GlobalStringAtomTable();

    /// get pointer to global string buffer
    StringBuffer* GetGlobalStringBuffer() const;

    /// debug functionality: DebugInfo struct
    struct DebugInfo
    {
        Util::Array<const char*> strings;
        SizeT chunkSize;
        SizeT numChunks;
        SizeT allocSize;
        SizeT usedSize;
        bool growthEnabled;
    };
    
    /// debug functionality: get copy of the string atom table
    DebugInfo GetDebugInfo() const;

private:
    friend class StringAtom;

    /// take the critical section
    void Lock();
    /// add a string pointer to the atom table and string buffer (must be called inside Lock())
    const char* Add(const char* str);
    /// release the critical section
    void Unlock();

    Threading::CriticalSection critSect;
    StringBuffer stringBuffer;
};

} // namespace Util
//------------------------------------------------------------------------------

