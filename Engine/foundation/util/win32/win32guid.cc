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

#if WIN32


#include "stdneb.h"
#include "exception/exceptions.h"
#include "util/win32/win32guid.h"

namespace Win32
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
void
Win32Guid::operator=(const Win32Guid& rhs)
{
    if (this != &rhs)
    {
        this->uuid = rhs.uuid;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Win32Guid::operator=(const String& rhs)
{
    n_assert(rhs.IsValid());
    RPC_STATUS result = UuidFromString((RPC_CSTR) rhs.AsCharPtr(), &(this->uuid));
    n_assert(RPC_S_INVALID_STRING_UUID != result);
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator==(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return (0 == result);
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator!=(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return (0 != result);
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator<(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return (-1 == result);
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator<=(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return ((-1 == result) || (0 == result));
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator>(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return (1 == result);
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::operator>=(const Win32Guid& rhs) const
{
    RPC_STATUS status;
    int result = UuidCompare(const_cast<UUID*>(&this->uuid), const_cast<UUID*>(&rhs.uuid), &status);
    return ((1 == result) || (0 == result));
}

//------------------------------------------------------------------------------
/**
*/
bool
Win32Guid::IsValid() const
{
    RPC_STATUS status;
    int result = UuidIsNil(const_cast<UUID*>(&this->uuid), &status);
    return (TRUE != result);
}

//------------------------------------------------------------------------------
/**
*/
void
Win32Guid::Generate()
{
    UuidCreate(&this->uuid);
}

//------------------------------------------------------------------------------
/**
*/
String
Win32Guid::AsString() const
{
    const char* uuidStr;
    UuidToString((UUID*) &this->uuid, (RPC_CSTR*) &uuidStr);
    String result = uuidStr;
    RpcStringFree((RPC_CSTR*)&uuidStr);
    return result;
}

//------------------------------------------------------------------------------
/**
    This method allows read access to the raw binary data of the uuid.
    It returns the number of bytes in the buffer, and a pointer to the
    data.
*/
SizeT
Win32Guid::AsBinary(const unsigned char*& outPtr) const
{
    outPtr = (const unsigned char*) &this->uuid;
    return sizeof(UUID);
}

//------------------------------------------------------------------------------
/**
*/
Win32Guid
Win32Guid::FromString(const Util::String& str)
{
    Win32Guid newGuid;
    RPC_STATUS success = UuidFromString((RPC_CSTR)str.AsCharPtr(), &(newGuid.uuid));
    if(RPC_S_OK != success)
	{
		SYS_EXCEPT(Exceptions::FormatException, 
			STRING_FORMAT("error guid value, %s.", str.AsCharPtr()),
			GET_FUNCTION_NAME()
			);
	}
    return newGuid;
}

//------------------------------------------------------------------------------
/**
    Constructs the guid from binary data, as returned by the AsBinary().
*/
Win32Guid
Win32Guid::FromBinary(const unsigned char* ptr, SizeT numBytes)
{
    n_assert((0 != ptr) && (numBytes == sizeof(UUID)));
    Win32Guid newGuid;
    Memory::Copy(ptr, &(newGuid.uuid), sizeof(UUID));
    return newGuid;
}

//------------------------------------------------------------------------------
/**
    This method returns a hash code for the uuid, compatible with 
    Util::HashTable.
*/
IndexT
Win32Guid::HashCode() const
{
    RPC_STATUS status;
    unsigned short hashCode = UuidHash((UUID*)&this->uuid, &status);
    return (IndexT) hashCode;
}

}; // namespace Win32

#endif