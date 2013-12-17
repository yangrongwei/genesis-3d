/****************************************************************************
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
#ifndef __inputmousebutton_H__
#define __inputmousebutton_H__

#include "core/types.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Input
{
class InputMouseButton
{
public:
    /// code enums
    enum Code
    {
        LeftButton   = 0,
        RightButton  = 1,
        MiddleButton = 2,

        NumMouseButtons,
        InvalidMouseButton,
    };
    
    /// convert to string
    static Util::String ToString(Code code);
    /// convert from string
    static Code FromString(const Util::String& str);
};

} // namespace Input
//------------------------------------------------------------------------------





#endif // __inputmousebutton_H__




    