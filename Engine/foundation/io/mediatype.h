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
#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::MediaType
  
    Encapsulates a MIME conformant media type description (text/plain, 
    image/jpg, etc...).
*/    
#include "util/string.h"

//------------------------------------------------------------------------------
namespace IO
{
class MediaType
{
public:
    /// constructor
    MediaType();
    /// init constructor from string
    MediaType(const Util::String& str);
    /// init constructor from type and subtype
    MediaType(const Util::String& type, const Util::String& subType);
    /// copy constructor
    MediaType(const MediaType& rhs);

    /// assignment operator
    void operator=(const MediaType& rhs);
    /// equality operator
    bool operator==(const MediaType& rhs);
    /// inequality operator
    bool operator!=(const MediaType& rhs);

    /// return true if not empty
    bool IsValid() const;
    /// clear the media type object
    void Clear();
    /// set as string (must be of the form "xxx/yyy")
    void Set(const Util::String& str);
    /// set as type and subtype
    void Set(const Util::String& type, const Util::String& subType);
    /// return as string
    Util::String AsString() const;
    /// get type
    const Util::String& GetType() const;
    /// get subtype
    const Util::String& GetSubType() const;

private:
    Util::String type;
    Util::String subType;
};

//------------------------------------------------------------------------------
/**
*/
inline
MediaType::MediaType()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
void
MediaType::Set(const Util::String& str)
{
    n_assert(str.IsValid());
    Util::Array<Util::String> tokens = str.Tokenize("/");
    n_assert(tokens.Size() == 2);
    this->type = tokens[0];
    this->subType = tokens[1];
}

//------------------------------------------------------------------------------
/**
*/
inline
MediaType::MediaType(const Util::String& str)
{
    this->Set(str);
}

//------------------------------------------------------------------------------
/**
*/
inline
MediaType::MediaType(const Util::String& t, const Util::String& s) :
    type(t),
    subType(s)
{
    n_assert(this->type.IsValid());
    n_assert(this->subType.IsValid());
}

//------------------------------------------------------------------------------
/**
*/
inline
MediaType::MediaType(const MediaType& rhs) :
    type(rhs.type),
    subType(rhs.subType)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
void
MediaType::operator=(const MediaType& rhs)
{
    this->type = rhs.type;
    this->subType = rhs.subType;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
MediaType::operator==(const MediaType& rhs)
{
    return ((this->type == rhs.type) && (this->subType == rhs.subType));
}

//------------------------------------------------------------------------------
/**
*/
inline bool
MediaType::operator!=(const MediaType& rhs)
{
    return !(*this == rhs);
}

//------------------------------------------------------------------------------
/**
*/
inline void
MediaType::Set(const Util::String& t, const Util::String& s)
{
    n_assert(t.IsValid() && s.IsValid());
    this->type = t;
    this->subType = s;
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
MediaType::AsString() const
{
    Util::String str;
    str.Reserve(128);
    str = this->type;
    str.Append("/");
    str.Append(this->subType);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
MediaType::GetType() const
{
    return this->type;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
MediaType::GetSubType() const
{
    return this->subType;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
MediaType::IsValid() const
{
    return this->type.IsValid() && this->subType.IsValid();
}

//------------------------------------------------------------------------------
/**
*/
inline void
MediaType::Clear()
{
    this->type.Clear();
    this->subType.Clear();
}

} // namespace IO
//------------------------------------------------------------------------------
