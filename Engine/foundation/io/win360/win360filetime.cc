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
#ifdef __WIN32__


#include "stdneb.h"
#include "io/win360/win360filetime.h"

namespace Win360
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
Win360FileTime::Win360FileTime(const String& str)
{
    Array<String> tokens = str.Tokenize("#");
    n_assert(tokens.Size() == 2);
    this->time.dwHighDateTime = tokens[0].AsInt();
    this->time.dwLowDateTime = tokens[1].AsInt();
}

//------------------------------------------------------------------------------
/**
*/
String
Win360FileTime::AsString() const
{
    String str;
    str.Format("%d#%d", this->time.dwHighDateTime, this->time.dwLowDateTime);
    return str;
}

} // namespace Win360

#endif