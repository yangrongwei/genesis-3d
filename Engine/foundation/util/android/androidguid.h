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
#ifdef __ANDROID__
#ifndef __ANDROIDGUID_H__
#define __ANDROIDGUID_H__


#include "core/types.h"
#include "util/string.h"
#include "core/sysfunc.h"

namespace Android
{
	
	class AndroidGuid
{
public:
	/// override new operator
	void* operator new(size_t s);
	/// override delete operator
	void operator delete(void* ptr);

	/// constructor
	AndroidGuid();
	/// copy constructor
	AndroidGuid(const AndroidGuid& rhs);
	/// construct from raw binary data as returned by AsBinary()
	AndroidGuid(const unsigned char* ptr, SizeT size);
	~AndroidGuid();
	/// assignement operator
	void operator=(const AndroidGuid& rhs);
	/// assignment operator from string
	void operator=(const Util::String& rhs);
	/// equality operator
	bool operator==(const AndroidGuid& rhs) const;
	/// inequlality operator
	bool operator!=(const AndroidGuid& rhs) const;
	/// less-then operator
	bool operator<(const AndroidGuid& rhs) const;
	/// less-or-equal operator
	bool operator<=(const AndroidGuid& rhs) const;
	/// greater-then operator
	bool operator>(const AndroidGuid& rhs) const;
	/// greater-or-equal operator
	bool operator>=(const AndroidGuid& rhs) const;
	/// return true if the contained guid is valid (not NIL)
	bool IsValid() const;
	/// generate a new guid
	void Generate();
	/// construct from string representation
	static AndroidGuid FromString(const Util::String& str);
	/// construct from binary representation
	static AndroidGuid FromBinary(const unsigned char* ptr, SizeT numBytes);
	/// get as string
	Util::String AsString() const;
	/// get pointer to binary data
	SizeT AsBinary(const unsigned char*& outPtr) const;
	/// return the size of the binary representation in bytes
	static SizeT BinarySize();
	/// get a hash code (compatible with Util::HashTable)
	IndexT HashCode() const;
private:
	void* m_pUuid;	

};

//------------------------------------------------------------------------------
/**
 */
__forceinline void*
AndroidGuid::operator new(size_t size)
{
  
    return Memory::Alloc(Memory::ObjectHeap, size);
    
}
    
//------------------------------------------------------------------------------
/**
 */
__forceinline void
AndroidGuid::operator delete(void* ptr)
{  
    return Memory::Free(Memory::ObjectHeap, ptr);  
}
    


}


#endif
#endif 