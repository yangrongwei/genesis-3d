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
#include "core/sysfunc.h"
#include "util/array.h"
#include "util/dictionary.h"
#include "memory/heap.h"


#include "math/float4.h"
#include "math/float3.h"
#include "math/float2.h"
#include "math/matrix44.h"
#include "math/bbox.h"


#include "memory/poolarrayallocator.h"

//------------------------------------------------------------------------------
namespace Util
{
	// - forward declare
	class String;
	struct AssetPath;

	// - typedefs 
	typedef Array<String> TStringArray;

#define STRING_FORMAT(fmtString, ...) Util::String().Format2(fmtString, __VA_ARGS__)//Util::String().Format2

class String
{
public:
    /// override new operator
    void* operator new(size_t s);
    /// override delete operator
    void operator delete(void* ptr);

    /// constructor
    String();
    /// copy constructor
    String(const String& rhs);
    /// construct from C string
    String(const char* cStr);
    /// destructor
    ~String();

    /// assignment operator
    void operator=(const String& rhs);
    /// assign from const char*
    void operator=(const char* cStr);
    /// += operator
    void operator +=(const String& rhs);
    /// equality operator
    friend bool operator==(const String& a, const String& b);
    /// shortcut equality operator
    friend bool operator==(const String& a, const char* cStr);
    /// shortcut equality operator
    friend bool operator==(const char* cStr, const String& a);
    /// inequality operator
    friend bool operator !=(const String& a, const String& b);
	/// less-then operator
	friend bool operator <(const String& a, const String& b);
	/// greater-then operator
	friend bool operator >(const String& a, const String& b);
	/// less-or-equal operator
	friend bool operator <=(const String& a, const String& b);
	/// greater-then operator
	friend bool operator >=(const String& a, const String& b);
    /// read-only index operator
    char operator[](IndexT i) const;
    /// read/write index operator
    char& operator[](IndexT i);

    /// reserve internal buffer size to prevent heap allocs
    void Reserve(SizeT newSize);
    /// return length of string
    SizeT Length() const;
    /// clear the string
    void Clear();
    /// return true if string object is empty
    bool IsEmpty() const;
    /// return true if string object is not empty
    bool IsValid() const;
    /// copy to char buffer (return false if buffer is too small)
    bool CopyToBuffer(char* buf, SizeT bufSize) const;

    /// append string
    void Append(const String& str);
    /// append c-string
    void Append(const char* str);
    /// append a range of characters
    void AppendRange(const char* str, SizeT numChars);

    /// convert string to lower case
	void ToLower();
    /// convert string to upper case
	void ToUpper();
    /// convert first char of string to upper case
    void FirstCharToUpper();
    /// tokenize string into a provided String array (faster if tokens array can be reused)
    SizeT Tokenize(const String& whiteSpace, Array<String>& outTokens) const;
    /// tokenize string into a provided String array, SLOW since new array will be constructed
    Array<String> Tokenize(const String& whiteSpace) const;
    /// tokenize string, keep strings within fence characters intact (faster if tokens array can be reused)
    SizeT Tokenize(const String& whiteSpace, char fence, Array<String>& outTokens) const;
    /// tokenize string, keep strings within fence characters intact, SLOW since new array will be constructed
    Array<String> Tokenize(const String& whiteSpace, char fence) const;
    /// extract substring
    String ExtractRange(IndexT fromIndex, SizeT numChars) const;
    /// extract substring to end of this string
    String ExtractToEnd(IndexT fromIndex) const;
	/// erase substring of this string.
	String EraseRange(IndexT fromIndex, SizeT numChars) const;
	/// insert substring.
	String InsertRange(IndexT fromIndex,const String& str) const;
    /// terminate string at first occurence of character in set
    void Strip(const String& charSet);
    /// return start index of substring, or InvalidIndex if not found
    IndexT FindStringIndex(const String& s, IndexT startIndex = 0) const;
    /// return index of character in string, or InvalidIndex if not found
    IndexT FindCharIndex(char c, IndexT startIndex = 0) const;
	/// search a char in a  backward direction for the first occurrence, return the index(forward direction) if success.
	IndexT BackwardFindChar(char c, IndexT startIndex = 0 ) const;
    /// terminate string at given index
    void TerminateAtIndex(IndexT index);
    /// returns true if string contains any character from set
    bool ContainsCharFromSet(const String& charSet) const;
    /// delete characters from charset at left side of string
    void TrimLeft(const String& charSet);
    /// delete characters from charset at right side of string
    void TrimRight(const String& charSet);
    /// trim characters from charset at both sides of string
    void Trim(const String& charSet);
    /// substitute every occurance of a string with another string
    void SubstituteString(const String& str, const String& substStr);
    /// substiture every occurance of a character with another character
    void SubstituteChar(char c, char subst);
    /// format string printf-style
    void __cdecl Format(const char* fmtString, ...);
	const Util::String& __cdecl Format2(const char* fmtString, ...);
    /// format string printf-style with varargs list
    void __cdecl FormatArgList(const char* fmtString, va_list argList);
    /// return true if string only contains characters from charSet argument
    bool CheckValidCharSet(const String& charSet) const;
    /// replace any char set character within a srtring with the replacement character
    void ReplaceChars(const String& charSet, char replacement);
    /// concatenate array of strings into new string
    static String Concatenate(const Array<String>& strArray, const String& whiteSpace);
    /// pattern matching
    static bool MatchPattern(const String& str, const String& pattern);
    /// return a 32-bit hash code for the string
    IndexT HashCode() const;

    /// set content to char ptr
    void SetCharPtr(const char* s);
    /// set as char ptr, with explicit length
    void Set(const char* ptr, SizeT length);
    /// set as int value
    void SetInt(int val);
    /// set as float value
    void SetFloat(float val);
    /// set as bool value
    void SetBool(bool val);	
    
    
    /// set as float2 value
    void SetFloat2(const Math::float2& v);
	/// set as float3 value
	void SetFloat3(const Math::float3& v);
    /// set as float4 value
    void SetFloat4(const Math::float4& v);
    /// set as matrix44 value
    void SetMatrix44(const Math::matrix44& v);
	/// set as bbox
	void SetBBox(const Math::bbox& v);
	/// set as assetpath
	void SetAssetPath(const Util::AssetPath& v);
    
    /// generic setter
    template<typename T> void Set(const T& t);

    /// append int value
    void AppendInt(int val);
    /// append float value
    void AppendFloat(float val);
    /// append bool value
    void AppendBool(bool val);
    #if !__OSX__
	/// append float2 value
	void AppendFloat2(const Math::float2& v);
    /// append float4 value
    void AppendFloat4(const Math::float4& v);
    /// append matrix44 value
    void AppendMatrix44(const Math::matrix44& v);
    #endif
    /// generic append
    template<typename T> void Append(const T& t);

    /// return contents as character pointer
    const char* AsCharPtr() const;
    /// *** OBSOLETE *** only Nebula2 compatibility
    const char* Get() const;
    /// return contents as integer
    int AsInt() const;
    /// return contents as float
    float AsFloat() const;
    /// return contents as bool
    bool AsBool() const;
    
	/// return contents as float2
	Math::float2 AsFloat2() const;
	/// return contents as float3
	Math::float3 AsFloat3() const;
    /// return contents as float4
    Math::float4 AsFloat4() const;
    /// return contents as matrix44
    Math::matrix44 AsMatrix44() const;
	 /// return contents as bbox
	Math::bbox AsBBox() const;
	Util::AssetPath AsAssetPath() const;
    
    /// convert to "anything"
    template<typename T> T As() const;

    /// return true if the content is a valid integer
    bool IsValidInt() const;
    /// return true if the content is a valid float
    bool IsValidFloat() const;
    /// return true if the content is a valid bool
    bool IsValidBool() const;
 
	/// return true if the content is a valid float2
	bool IsValidFloat2() const;
	/// return true if the content is a valid float3
	bool IsValidFloat3() const;
    /// return true if the content is a valid float4
    bool IsValidFloat4() const;
    /// return true if content is a valid matrix44
    bool IsValidMatrix44() const;
	/// return true if the content is a valid bbox
	bool IsValidBBox() const;
    
    /// generic valid checker
    template<typename T> bool IsValid() const;

    /// construct a string from an int
    static String FromInt(int i);
    /// construct a string from a float
    static String FromFloat(float f);
    /// construct a string from a bool
    static String FromBool(bool b);
    
	/// construct a string from float2
	static String FromFloat2(const Math::float2& v);
    /// construct a string from float4
    static String FromFloat4(const Math::float4& v);
    /// construct a string from matrix44
    static String FromMatrix44(const Math::matrix44& m);
    
    /// convert from "anything"
    template<typename T> static String From(const T& t);

    /// get filename extension without dot
    String GetFileExtension() const;
    /// check file extension
    bool CheckFileExtension(const String& ext) const;
    /// convert backslashes to slashes
    void ConvertBackslashes();
    /// remove file extension
    void StripFileExtension();
    /// change file extension
    void ChangeFileExtension(const Util::String& newExt);
    /// extract the part after the last directory separator
    String ExtractFileName() const;
    /// extract the last directory of the path
    String ExtractLastDirName() const;
    /// extract the part before the last directory separator
    String ExtractDirName() const;
    /// extract path until last slash
    String ExtractToLastSlash() const;
    /// replace illegal filename characters
    void ReplaceIllegalFilenameChars(char replacement);

    /// test if provided character is a digit (0..9)
    static bool IsDigit(char c);
    /// test if provided character is an alphabet character (A..Z, a..z)
    static bool IsAlpha(char c);
    /// test if provided character is an alpha-numeric character (A..Z,a..z,0..9)
    static bool IsAlNum(char c);
    /// test if provided character is a lower case character
    static bool IsLower(char c);
    /// test if provided character is an upper-case character
    static bool IsUpper(char c);
	/// test if provided character is an space
	static bool IsSpace(char c);

    /// lowlevel string compare wrapper function
    static int StrCmp(const char* str0, const char* str1);
    /// lowlevel string length function
    static int StrLen(const char* str);
    /// find character in string
    static const char* StrChr(const char* str, int c);

    /// parse key/value pair string ("key0=value0 key1=value1")
    static Dictionary<String,String> ParseKeyValuePairs(const String& str);

private:
    /// delete contents
    void Delete();
    /// get pointer to last directory separator
    char* GetLastSlash() const;
    /// allocate the string buffer (discards old content)
    void Alloc(SizeT size);
    /// (re-)allocate the string buffer (copies old content)
    void Realloc(SizeT newSize);

    enum
    {
        LocalStringSize = 20,
    };
    char* heapBuffer;
    char localBuffer[LocalStringSize];
    SizeT strLen;
    SizeT heapBufferSize;
};

//------------------------------------------------------------------------------
/**
*/
__forceinline void*
String::operator new(size_t size)
{
    #if NEBULA3_DEBUG
    n_assert(size == sizeof(String));
    #endif

    #if NEBULA3_OBJECTS_USE_MEMORYPOOL
        return Memory::ObjectPoolAllocator->Alloc(size);
    #else
        return Memory::Alloc(Memory::ObjectHeap, size);
    #endif
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
String::operator delete(void* ptr)
{
    #if NEBULA3_OBJECTS_USE_MEMORYPOOL
        return Memory::ObjectPoolAllocator->Free(ptr, sizeof(String));
    #else
        return Memory::Free(Memory::ObjectHeap, ptr);
    #endif
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String() :
    heapBuffer(0),
    strLen(0),
    heapBufferSize(0)
{
    this->localBuffer[0] = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Delete()
{
    if (this->heapBuffer)
    {
        Memory::Free(Memory::StringDataHeap, (void*) this->heapBuffer);
        this->heapBuffer = 0;
    }
    this->localBuffer[0] = 0;
    this->strLen = 0;
    this->heapBufferSize = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline 
String::~String()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
    Allocate a new heap buffer, discards old contents.
*/
inline void
String::Alloc(SizeT newSize)
{
    n_assert(newSize > (this->strLen + 1));
    n_assert(newSize > this->heapBufferSize);

    // free old buffer
    if (this->heapBuffer)
    {
        Memory::Free(Memory::StringDataHeap, (void*) this->heapBuffer);
        this->heapBuffer = 0;
    }

    // allocate new buffer
    this->heapBuffer = (char*) Memory::Alloc(Memory::StringDataHeap, newSize);
    this->heapBufferSize = newSize;
    this->localBuffer[0] = 0;
}

//------------------------------------------------------------------------------
/**
    (Re-)allocate external buffer and copy existing string contents there.
*/
inline void
String::Realloc(SizeT newSize)
{
    n_assert(newSize > (this->strLen + 1));
    n_assert(newSize > this->heapBufferSize);

    // allocate a new buffer
    char* newBuffer = (char*) Memory::Alloc(Memory::StringDataHeap, newSize);

    // copy existing contents there...
    if (this->strLen > 0)
    {
        const char* src = this->AsCharPtr();
        Memory::Copy(src, newBuffer, this->strLen);
    }
    newBuffer[this->strLen] = 0;

    // assign new buffer
    if (this->heapBuffer)
    {
        Memory::Free(Memory::StringDataHeap, (void*) this->heapBuffer);
        this->heapBuffer = 0;
    }
    this->localBuffer[0] = 0;
    this->heapBuffer = newBuffer;
    this->heapBufferSize = newSize;
}

//------------------------------------------------------------------------------
/**
    Reserves internal space to prevent excessive heap re-allocations.
    If you plan to do many Append() operations this may help alot.
*/
inline void
String::Reserve(SizeT newSize)
{
    if (newSize > this->heapBufferSize)
    {
        this->Realloc(newSize);
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetInt(int val)
{
    this->Format("%d", val);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetFloat(float val)
{
    this->Format("%.6f", val);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetBool(bool val)
{
    if (val)
    {
        this->SetCharPtr("true");
    }
    else
    {
        this->SetCharPtr("false");
    }
}


//------------------------------------------------------------------------------
/**
*/
inline void
String::SetFloat2(const Math::float2& v)
{
    this->Format("%.6f,%.6f", v.x(), v.y());
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetFloat3(const Math::float3& v)
{
	this->Format("%.6f,%.6f,%.6f", v.x(), v.y(),v.z());
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetFloat4(const Math::float4& v)
{
    this->Format("%.6f,%.6f,%.6f,%.6f", v.x(), v.y(), v.z(), v.w());
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetMatrix44(const Math::matrix44& m)
{
    this->Format("%.6f, %.6f, %.6f, %.6f, "
                 "%.6f, %.6f, %.6f, %.6f, "
                 "%.6f, %.6f, %.6f, %.6f, "
                 "%.6f, %.6f, %.6f, %.6f",
                 m.getrow0().x(), m.getrow0().y(), m.getrow0().z(), m.getrow0().w(),
                 m.getrow1().x(), m.getrow1().y(), m.getrow1().z(), m.getrow1().w(),
                 m.getrow2().x(), m.getrow2().y(), m.getrow2().z(), m.getrow2().w(),
                 m.getrow3().x(), m.getrow3().y(), m.getrow3().z(), m.getrow3().w());
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::SetBBox(const Math::bbox& v)
{
	this->Format("%.6f,%.6f,%.6f,%.6f,%.6f,%.6f",
				v.pmin.x(), v.pmin.y(), v.pmin.z(), 
				v.pmax.x(), v.pmax.y(), v.pmax.z());
}
//------------------------------------------------------------------------------
/**
*/
inline
String::String(const char* str) :
    heapBuffer(0),
    strLen(0),
    heapBufferSize(0)
{
    this->localBuffer[0] = 0;
    this->SetCharPtr(str);
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(const String& rhs) :
    heapBuffer(0),
    strLen(0),
    heapBufferSize(0)
{
    this->localBuffer[0] = 0;
    this->SetCharPtr(rhs.AsCharPtr());
}

//------------------------------------------------------------------------------
/**
*/
inline const char*
String::AsCharPtr() const
{
    if (this->heapBuffer)
    {
        return this->heapBuffer;
    }
    else
    {
        return this->localBuffer;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline const char*
String::Get() const
{
    return this->AsCharPtr();
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::operator=(const String& rhs)
{
    if (&rhs != this)
    {
        this->SetCharPtr(rhs.AsCharPtr());
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::operator=(const char* cStr)
{
    this->SetCharPtr(cStr);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Append(const String& str)
{
    this->AppendRange(str.AsCharPtr(), str.strLen);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::operator += (const String& rhs)
{
    this->Append(rhs);    
}

//------------------------------------------------------------------------------
/**
*/
inline char
String::operator[](IndexT i) const
{
    n_assert(i <= this->strLen);
    return this->AsCharPtr()[i];
}

//------------------------------------------------------------------------------
/**
    NOTE: unlike the read-only indexer, the terminating 0 is NOT a valid
    part of the string because it may not be overwritten!!!
*/
inline char&
String::operator[](IndexT i)
{
    n_assert(i <= this->strLen);
    return (char&)(this->AsCharPtr())[i];
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
String::Length() const
{
    return this->strLen;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Clear()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::IsEmpty() const
{
    return (0 == this->strLen);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::IsValid() const
{
    return (0 != this->strLen);
}

//------------------------------------------------------------------------------
/**
    This method computes a hash code for the string. The method is
    compatible with the Util::HashTable class.
*/
inline IndexT
String::HashCode() const
{
    IndexT hash = 0;
    const char* ptr = this->AsCharPtr();
    SizeT len = this->strLen;
    IndexT i;
    for (i = 0; i < len; i++)
    {
        hash += ptr[i];
        hash += hash << 10;
        hash ^= hash >>  6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash &= ~(1<<31);       // don't return a negative number (in case IndexT is defined signed)
    return hash;
}

//------------------------------------------------------------------------------
/**
*/
static inline String
operator+(const String& s0, const String& s1)
{
    String newString = s0;
    newString.Append(s1);
    return newString;
}

//------------------------------------------------------------------------------
/**
    Replace character with another.
*/
inline void
String::SubstituteChar(char c, char subst)
{
    char* ptr = const_cast<char*>(this->AsCharPtr());
    IndexT i;
    for (i = 0; i <= this->strLen; i++)
    {
        if (ptr[i] == c)
        {
            ptr[i] = subst;
        }
    }
}

//------------------------------------------------------------------------------
/**
    Converts backslashes to slashes.
*/
inline void
String::ConvertBackslashes()
{
    this->SubstituteChar('\\', '/');
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::CheckFileExtension(const String& ext) const
{
    return (this->GetFileExtension() == ext);
}

//------------------------------------------------------------------------------
/**
    Return a String object containing the part after the last
    path separator.
*/
inline String
String::ExtractFileName() const
{
    String pathString;
    const char* lastSlash = this->GetLastSlash();
    if (lastSlash)
    {
        pathString = &(lastSlash[1]);
    }
    else
    {
        pathString = *this;
    }
    return pathString;
}

//------------------------------------------------------------------------------
/**
    Return a path string object which contains of the complete path
    up to the last slash. Returns an empty string if there is no
    slash in the path.
*/
inline String
String::ExtractToLastSlash() const
{
    String pathString(*this);
    char* lastSlash = pathString.GetLastSlash();
    if (lastSlash)
    {
        lastSlash[1] = 0;
    }
    else
    {
        pathString = "";
    }
    return pathString;
}

//------------------------------------------------------------------------------
/**
    Return true if the string only contains characters which are in the defined
    character set.
*/
inline bool
String::CheckValidCharSet(const String& charSet) const
{
    IndexT i;
    for (i = 0; i < this->strLen; i++)
    {
        if (InvalidIndex == charSet.FindCharIndex((*this)[i], 0))
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::IsValidInt() const
{
    return this->CheckValidCharSet(" \t-+01234567890");
}

//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidFloat() const
{
    return this->CheckValidCharSet(" \t-+.e1234567890");
}


//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidFloat2() const
{
    return this->CheckValidCharSet(" \t-+.,e1234567890");
}

//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidFloat3() const
{
    return this->CheckValidCharSet(" \t-+.,e1234567890");
}

//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidFloat4() const
{
    return this->CheckValidCharSet(" \t-+.,e1234567890");
}

//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidMatrix44() const
{
    return this->CheckValidCharSet(" \t-+.,e1234567890");
}
//------------------------------------------------------------------------------
/**
    Note: this method is not 100% correct, it just checks for invalid characters.
*/
inline bool
String::IsValidBBox() const
{
    return this->CheckValidCharSet(" \t-+.,e1234567890");
} 

//------------------------------------------------------------------------------
/**
*/
inline void
String::ReplaceIllegalFilenameChars(char replacement)
{
    this->ReplaceChars("\\/:*?\"<>|", replacement);
}

//------------------------------------------------------------------------------
/**
*/
inline String
String::FromInt(int i)
{	
    String str;
    str.SetInt(i);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline String
String::FromFloat(float f)
{
    String str;
    str.SetFloat(f);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline String
String::FromBool(bool b)
{
    String str;
    str.SetBool(b);
    return str;
}


//------------------------------------------------------------------------------
/**
*/
inline String
String::FromFloat2(const Math::float2& v)
{
    String str;
    str.SetFloat2(v);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline String
String::FromFloat4(const Math::float4& v)
{
    String str;
    str.SetFloat4(v);
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline String
String::FromMatrix44(const Math::matrix44& m)
{
    String str;
    str.SetMatrix44(m);
    return str;
}

    
//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendInt(int val)
{
    this->Append(FromInt(val));
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendFloat(float val)
{
    this->Append(FromFloat(val));
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendBool(bool val)
{
    this->Append(FromBool(val));
}

#if !__OSX__    
//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendFloat2(const Math::float2& val)
{
    this->Append(FromFloat2(val));
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendFloat4(const Math::float4& val)
{
    this->Append(FromFloat4(val));
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::AppendMatrix44(const Math::matrix44& val)
{
    this->Append(FromMatrix44(val));
}
#endif
    
} // namespace Util
//------------------------------------------------------------------------------

