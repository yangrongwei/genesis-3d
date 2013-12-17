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
   
#include "util/array.h"
#include "util/keyvaluepair.h"

//------------------------------------------------------------------------------
namespace Util
{
template<class KEYTYPE, class VALUETYPE> class Dictionary
{
public:
	// add typedefs
	typedef KEYTYPE		key_type;
	typedef VALUETYPE	value_type;
	typedef KeyValuePair<KEYTYPE, VALUETYPE> key_value_pair_type;
	/// define iterator
	typedef key_value_pair_type* Iterator;
    /// default constructor
    Dictionary();
    /// copy constructor
    Dictionary(const Dictionary<KEYTYPE, VALUETYPE>& rhs);
    /// assignment operator
    void operator=(const Dictionary<KEYTYPE, VALUETYPE>& rhs);
    /// read/write [] operator
    VALUETYPE& operator[](const KEYTYPE& key);
    /// read-only [] operator
    const VALUETYPE& operator[](const KEYTYPE& key) const;
    /// return number of key/value pairs in the dictionary
    SizeT Size() const;
    /// clear the dictionary
    void Clear();
    /// return true if empty
    bool IsEmpty() const;
    /// reserve space (useful if number of elements is known beforehand)
    void Reserve(SizeT numElements);
	/// return iterator to beginning of array
	Iterator Begin() const;
	/// return iterator to end of array
	Iterator End() const;
    /// begin a bulk insert (array will be sorted at End)
    void BeginBulkAdd();
    /// add a key/value pair
    void Add(const KeyValuePair<KEYTYPE, VALUETYPE>& kvp);
    /// add a key and associated value
    void Add(const KEYTYPE& key, const VALUETYPE& value);
    /// end a bulk insert (this will sort the internal array)
    void EndBulkAdd();
    /// erase a key and its associated value
    void Erase(const KEYTYPE& key);
    /// erase a key at index
    void EraseAtIndex(IndexT index);
    /// find index of key/value pair (InvalidIndex if doesn't exist)
    IndexT FindIndex(const KEYTYPE& key) const;
    /// return true if key exists in the array
    bool Contains(const KEYTYPE& key) const;
    /// get a key at given index
    const KEYTYPE& KeyAtIndex(IndexT index) const;
    /// access to value at given index
    VALUETYPE& ValueAtIndex(IndexT index);
    /// get a value at given index
    const VALUETYPE& ValueAtIndex(IndexT index) const;
    /// get key/value pair at index
    KeyValuePair<KEYTYPE, VALUETYPE>& KeyValuePairAtIndex(IndexT index) const;
    /// get all keys as an Util::Array
    Array<KEYTYPE> KeysAsArray() const;
    /// get all keys as an Util::Array
    Array<VALUETYPE> ValuesAsArray() const;
    /// get all keys as (typically) an array
    template<class RETURNTYPE> RETURNTYPE KeysAs() const;
    /// get all keys as (typically) an array
    template<class RETURNTYPE> RETURNTYPE ValuesAs() const;
	/// swap data from two Dictionary
	void Swap( Dictionary<KEYTYPE, VALUETYPE>& rhs );
protected:
    /// make sure the key value pair array is sorted
    void SortIfDirty() const;

    Array<KeyValuePair<KEYTYPE, VALUETYPE> > keyValuePairs;
    bool inBulkInsert;

};

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
Dictionary<KEYTYPE, VALUETYPE>::Dictionary() :
    inBulkInsert(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
Dictionary<KEYTYPE, VALUETYPE>::Dictionary(const Dictionary<KEYTYPE, VALUETYPE>& rhs) :
    keyValuePairs(rhs.keyValuePairs),
    inBulkInsert(false)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!rhs.inBulkInsert);
    #endif
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::operator=(const Dictionary<KEYTYPE, VALUETYPE>& rhs)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    n_assert(!rhs.inBulkInsert);
    #endif
    this->keyValuePairs = rhs.keyValuePairs;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::Clear()
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    this->keyValuePairs.Clear();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> SizeT
Dictionary<KEYTYPE, VALUETYPE>::Size() const
{
    return this->keyValuePairs.Size();
}
//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> typename Dictionary<KEYTYPE, VALUETYPE>::Iterator
	Dictionary<KEYTYPE, VALUETYPE>::Begin() const
{
	return this->keyValuePairs.Begin();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> typename Dictionary<KEYTYPE, VALUETYPE>::Iterator
	Dictionary<KEYTYPE, VALUETYPE>::End() const
{
	return this->keyValuePairs.End();
}
//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> bool
Dictionary<KEYTYPE, VALUETYPE>::IsEmpty() const
{
    return (0 == this->keyValuePairs.Size());
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::Add(const KeyValuePair<KEYTYPE, VALUETYPE>& kvp)
{
    if (this->inBulkInsert)
    {
        this->keyValuePairs.Append(kvp);
    }
    else
    {
        this->keyValuePairs.InsertSorted(kvp);
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::Reserve(SizeT numElements)
{
    this->keyValuePairs.Reserve(numElements);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::BeginBulkAdd()
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    this->inBulkInsert = true;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::EndBulkAdd()
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(this->inBulkInsert);
    #endif
    this->keyValuePairs.Sort();
    this->inBulkInsert = false;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::Add(const KEYTYPE& key, const VALUETYPE& value)
{
    //n_assert(!this->Contains(key));
    KeyValuePair<KEYTYPE, VALUETYPE> kvp(key, value);
    if (this->inBulkInsert)
    {
        this->keyValuePairs.Append(kvp);
    }
    else
    {
        this->keyValuePairs.InsertSorted(kvp);
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::Erase(const KEYTYPE& key)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    IndexT eraseIndex = this->keyValuePairs.BinarySearchIndex(key);
    #if NEBULA3_BOUNDSCHECKS
    n_assert(InvalidIndex != eraseIndex);
    #endif
    this->keyValuePairs.EraseIndex(eraseIndex);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> void
Dictionary<KEYTYPE, VALUETYPE>::EraseAtIndex(IndexT index)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    this->keyValuePairs.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> IndexT
Dictionary<KEYTYPE, VALUETYPE>::FindIndex(const KEYTYPE& key) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return this->keyValuePairs.BinarySearchIndex(key);
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> bool
Dictionary<KEYTYPE, VALUETYPE>::Contains(const KEYTYPE& key) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return (InvalidIndex != this->keyValuePairs.BinarySearchIndex(key));
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> const KEYTYPE&
Dictionary<KEYTYPE, VALUETYPE>::KeyAtIndex(IndexT index) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return this->keyValuePairs[index].Key();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> VALUETYPE&
Dictionary<KEYTYPE, VALUETYPE>::ValueAtIndex(IndexT index)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return this->keyValuePairs[index].Value();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> const VALUETYPE&
Dictionary<KEYTYPE, VALUETYPE>::ValueAtIndex(IndexT index) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return this->keyValuePairs[index].Value();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> KeyValuePair<KEYTYPE, VALUETYPE>&
Dictionary<KEYTYPE, VALUETYPE>::KeyValuePairAtIndex(IndexT index) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    return this->keyValuePairs[index];
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> VALUETYPE&
Dictionary<KEYTYPE, VALUETYPE>::operator[](const KEYTYPE& key)
{
    int keyValuePairIndex = this->FindIndex(key);
    #if NEBULA3_BOUNDSCHECKS
    n_assert(InvalidIndex != keyValuePairIndex);
    #endif   
    return this->keyValuePairs[keyValuePairIndex].Value();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> const VALUETYPE&
Dictionary<KEYTYPE, VALUETYPE>::operator[](const KEYTYPE& key) const
{
    int keyValuePairIndex = this->FindIndex(key);
    #if NEBULA3_BOUNDSCHECKS
    n_assert(InvalidIndex != keyValuePairIndex);
    #endif
    return this->keyValuePairs[keyValuePairIndex].Value();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
template<class RETURNTYPE>
RETURNTYPE
Dictionary<KEYTYPE, VALUETYPE>::ValuesAs() const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(!this->inBulkInsert);
    #endif
    RETURNTYPE result(this->Size(),this->Size());
    IndexT i;
    for (i = 0; i < this->keyValuePairs.Size(); i++)
    {
        result.Append(this->keyValuePairs[i].Value());
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
Array<VALUETYPE>
Dictionary<KEYTYPE, VALUETYPE>::ValuesAsArray() const
{
    return this->ValuesAs<Array<VALUETYPE> >();
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE> 
template<class RETURNTYPE>
RETURNTYPE
Dictionary<KEYTYPE, VALUETYPE>::KeysAs() const
{
    #if NEBULA3_BOUNDSCHECKS    
    n_assert(!this->inBulkInsert);
    #endif
    RETURNTYPE result(this->Size(),this->Size());
    IndexT i;
    for (i = 0; i < this->keyValuePairs.Size(); i++)
    {
        result.Append(this->keyValuePairs[i].Key());
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
template<class KEYTYPE, class VALUETYPE>
Array<KEYTYPE>
Dictionary<KEYTYPE, VALUETYPE>::KeysAsArray() const
{
    return this->KeysAs<Array<KEYTYPE> >();
}

//------------------------------------------------------------------------
template<class KEYTYPE, class VALUETYPE>
void 
Dictionary<KEYTYPE, VALUETYPE>::Swap( Dictionary<KEYTYPE, VALUETYPE>& rhs )
{
	bool bBulkAdd = this->inBulkInsert;
	this->inBulkInsert = rhs.inBulkInsert;
	this->keyValuePairs.Swap( rhs.keyValuePairs );
	rhs.inBulkInsert = bBulkAdd;
}

} // namespace Util
//------------------------------------------------------------------------------
