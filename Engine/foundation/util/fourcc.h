#pragma once
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

#include "core/types.h"
#include "exception/exceptions.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Util
{
class FourCC
{
public:
    /// default constructor
    FourCC();
    /// construct from 32-bit-value (e.g. FourCC('ABCD'))
    FourCC(uint f);
    /// construct from string
    FourCC(const String& s);
    /// equality operator
    bool operator==(const FourCC& rhs) const;
    /// inequality operator
    bool operator!=(const FourCC& rhs) const;
    /// less-then operator
    bool operator<(const FourCC& rhs) const;
    /// less-or-equal operator
    bool operator<=(const FourCC& rhs) const;
    /// greater-then operator
    bool operator>(const FourCC& rhs) const;
    /// greater-or-equal operator
    bool operator>=(const FourCC& rhs) const;
    /// return true if valid
    bool IsValid() const;
    /// set from 32-bit-value
    void SetFromUInt(uint f);
    /// get as 32-bit-value
    uint AsUInt() const;
    /// set as string
    void SetFromString(const String& s);
    /// get as string
    String AsString() const;
    /// convert fourcc to string
    static String ToString(const FourCC& f);
    /// convert string to fourcc
    static FourCC FromString(const String& s);

private:
    uint fourCC;
};

//------------------------------------------------------------------------------
/**
*/
inline
FourCC::FourCC() :
    fourCC(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
FourCC::FourCC(uint f) :
    fourCC(f)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
FourCC::FourCC(const String& s)
{
    this->SetFromString(s);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator==(const FourCC& rhs) const
{
    return (this->fourCC == rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator!=(const FourCC& rhs) const
{
    return (this->fourCC != rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator>(const FourCC& rhs) const
{
    return (this->fourCC > rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator>=(const FourCC& rhs) const
{
    return (this->fourCC >= rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator<(const FourCC& rhs) const
{
    return (this->fourCC < rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::operator<=(const FourCC& rhs) const
{
    return (this->fourCC <= rhs.fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
FourCC::IsValid() const
{
    return (0 != this->fourCC);
}

//------------------------------------------------------------------------------
/**
*/
inline void
FourCC::SetFromUInt(uint f)
{
    n_assert(0 != f);
    this->fourCC = f;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
FourCC::AsUInt() const
{
    return this->fourCC;
}

//------------------------------------------------------------------------------
/**
*/
inline void
FourCC::SetFromString(const String& s)
{
    *this = FromString(s);
}

//------------------------------------------------------------------------------
/**
*/
inline String
FourCC::AsString() const
{
    return ToString(*this);
}

//------------------------------------------------------------------------------
/**
*/
inline String
FourCC::ToString(const FourCC& f)
{
    n_assert(f.IsValid());
    String str("xzyw");
    str[0] = (char) ((f.fourCC & 0xFF000000) >> 24);
    str[1] = (char) ((f.fourCC & 0x00FF0000) >> 16);
    str[2] = (char) ((f.fourCC & 0x0000FF00) >> 8);
    str[3] = (char) (f.fourCC & 0x000000FF);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline FourCC
FourCC::FromString(const String& s)
{
    if(s.IsValid() && s.Length() == 4)
	{
		return FourCC(uint(s[0] << 24 | s[1]<<16 | s[2]<<8 | s[3]));
	}
	else
	{
		SYS_EXCEPT(Exceptions::FormatException,
					STRING_FORMAT("error fourCC format: %s", s.AsCharPtr()),
					GET_FUNCTION_NAME()
					);
	}
}

} // namespace Util
//------------------------------------------------------------------------------
