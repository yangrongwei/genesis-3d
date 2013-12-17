#pragma once
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

#include "util/string.h"

//------------------------------------------------------------------------------
namespace Util
{
class StringAtom
{
public:
    /// default constructor
    StringAtom();
    /// copy constructor
    StringAtom(const StringAtom& rhs);
    /// construct from char ptr
    StringAtom(char* ptr);
    /// construct from char ptr
    StringAtom(const char* ptr);
    /// construct from char ptr
    StringAtom(unsigned char* ptr);
    /// construct from char ptr
    StringAtom(const unsigned char* ptr);
    /// construct from string object
    StringAtom(const String& str);

    /// assignment
    void operator=(const StringAtom& rhs);
    /// assignment from char ptr
    void operator=(const char* ptr);
    /// assignment from string object
    void operator=(const String& str);

    /// equality operator
    bool operator==(const StringAtom& rhs) const;
    /// inequality operator
    bool operator!=(const StringAtom& rhs) const;
    /// greater-then operator
    bool operator>(const StringAtom& rhs) const;
    /// less-then operator
    bool operator<(const StringAtom& rhs) const;
    /// greater-or-equal operator
    bool operator>=(const StringAtom& rhs) const;
    /// less-or-equal operator
    bool operator<=(const StringAtom& rhs) const;

    /// equality with char* (SLOW!)
    bool operator==(const char* rhs) const;
    /// inequality with char* (SLOW!)
    bool operator!=(const char* rhs) const;
    /// equality with string object (SLOW!)
    bool operator==(const String& rhs) const;
    /// inequality with string object (SLOW!)
    bool operator!=(const String& rhs) const;

    /// clear content (becomes invalid)
    void Clear();
    /// return true if valid (contains a non-empty string)
    bool IsValid() const;
    /// get contained string as char ptr (fast)
    const char* Value() const;
    /// get containted string as string object (SLOW!!!)
    String AsString() const;

private:
    /// setup the string atom from a string pointer
    void Setup(const char* str);

    const char* content;
};

//------------------------------------------------------------------------------
/**
*/
__forceinline
StringAtom::StringAtom() :
    content(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
StringAtom::StringAtom(const StringAtom& rhs) :
    content(rhs.content)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
StringAtom::StringAtom(char* str)
{
    if (0 != str)
    {
        this->Setup(str);
    }
    else
    {
        this->content = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
StringAtom::StringAtom(const char* str)
{
    if (0 != str)
    {
        this->Setup(str);
    }
    else
    {
        this->content = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
StringAtom::StringAtom(unsigned char* str)
{
    if (0 != str)
    {
        this->Setup((const char*)str);
    }
    else
    {
        this->content = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
StringAtom::StringAtom(const unsigned char* str)
{
    if (0 != str)
    {
        this->Setup((const char*)str);
    }
    else
    {
        this->content = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
StringAtom::StringAtom(const String& str)
{
    this->Setup(str.AsCharPtr());   
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
StringAtom::operator=(const StringAtom& rhs)
{
    this->content = rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
inline void
StringAtom::operator=(const char* str)
{
    if (0 != str)
    {
        this->Setup(str);
    }
    else
    {
        this->content = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
StringAtom::operator=(const String& str)
{
    this->Setup(str.AsCharPtr());    
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator==(const StringAtom& rhs) const
{
    return this->content == rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator!=(const StringAtom& rhs) const
{
    return this->content != rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator>(const StringAtom& rhs) const
{
    return this->content > rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator<(const StringAtom& rhs) const
{
    return this->content < rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator>=(const StringAtom& rhs) const
{
    return this->content >= rhs.content;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::operator<=(const StringAtom& rhs) const
{
    return this->content <= rhs.content;
}

//------------------------------------------------------------------------------
/**
    Compare with String object. Careful, slow!
*/
inline bool
StringAtom::operator==(const String& rhs) const
{
    if (0 == this->content)
    {
        return false;
    }
    else
    {
        return (rhs == this->content);
    }
}

//------------------------------------------------------------------------------
/**
    Compare with String object. Careful, slow!
*/
inline bool
StringAtom::operator!=(const String& rhs) const
{
    if (0 == this->content)
    {
        return false;
    }
    else
    {
        return (rhs != this->content);
    }
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
StringAtom::Clear()
{
    this->content = 0;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
StringAtom::IsValid() const
{
    return (0 != this->content) && (0 != this->content[0]);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const char*
StringAtom::Value() const
{
    return this->content;
}

//------------------------------------------------------------------------------
/**
    SLOW!!!
*/
inline String
StringAtom::AsString() const
{
    return String(this->content);
}

} // namespace Util
//------------------------------------------------------------------------------
