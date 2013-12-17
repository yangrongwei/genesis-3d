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

//------------------------------------------------------------------------------
namespace Util
{
template<class KEYTYPE, class VALUETYPE> class KeyValuePair
{
public:
	// add typedefs
	typedef KEYTYPE		key_type;
	typedef VALUETYPE	value_type;

    /// default constructor
    KeyValuePair();
    /// constructor with key and value
    KeyValuePair(const KEYTYPE& k, const VALUETYPE& v);
    /// constructor with key and undefined value
    KeyValuePair(const KEYTYPE& k);
    /// copy constructor
    KeyValuePair(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs);
    /// assignment operator
    void operator=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs);
    /// equality operator
    bool operator==(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
    /// inequality operator
    bool operator!=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
    /// greater operator
    bool operator>(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
    /// greater-or-equal operator
    bool operator>=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
    /// lesser operator
    bool operator<(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
    /// lesser-or-equal operator
    bool operator<=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const;
	/// read/write access to key
	KEYTYPE& Key();
    /// read/write access to value
    VALUETYPE& Value();
    /// read access to key
    const KEYTYPE& Key() const;
    /// read access to key
    const VALUETYPE& Value() const;

protected:
    KEYTYPE keyData;
    VALUETYPE valueData;
};

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
KeyValuePair<KEYTYPE, VALUETYPE>::KeyValuePair()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
KeyValuePair<KEYTYPE, VALUETYPE>::KeyValuePair(const KEYTYPE& k, const VALUETYPE& v) :
    keyData(k),
    valueData(v)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This strange constructor is useful for search-by-key if
    the key-value-pairs are stored in a Util::Array.
*/
template<class KEYTYPE, class VALUETYPE>
KeyValuePair<KEYTYPE, VALUETYPE>::KeyValuePair(const KEYTYPE& k) :
    keyData(k)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
KeyValuePair<KEYTYPE, VALUETYPE>::KeyValuePair(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) :
    keyData(rhs.keyData),
    valueData(rhs.valueData)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
void
KeyValuePair<KEYTYPE, VALUETYPE>::operator=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs)
{
    this->keyData = rhs.keyData;
    this->valueData = rhs.valueData;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator==(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData == rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator!=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData != rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator>(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData > rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator>=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData >= rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator<(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData < rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
bool
KeyValuePair<KEYTYPE, VALUETYPE>::operator<=(const KeyValuePair<KEYTYPE, VALUETYPE>& rhs) const
{
    return (this->keyData <= rhs.keyData);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
VALUETYPE&
KeyValuePair<KEYTYPE, VALUETYPE>::Value()
{
    return this->valueData;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
KEYTYPE&
KeyValuePair<KEYTYPE, VALUETYPE>::Key()
{
	return this->keyData;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
const KEYTYPE&
KeyValuePair<KEYTYPE, VALUETYPE>::Key() const
{
    return this->keyData;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
const VALUETYPE&
KeyValuePair<KEYTYPE, VALUETYPE>::Value() const
{
    return this->valueData;
}

} // namespace Util
//------------------------------------------------------------------------------
    