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
#include "stdneb.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>
#include <sstream>
#include "androidguid.h"

namespace Android
{
using namespace Util;
typedef boost::uuids::uuid* uuidTP;
//------------------------------------------------------------------------------
/**
 */
void
AndroidGuid::operator=(const AndroidGuid& rhs)
{
   *(uuidTP)m_pUuid = *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
void
AndroidGuid::operator=(const String& rhs)
{
	n_assert(rhs.IsValid());
	std::stringstream streamStr;
	streamStr<<rhs.Get();
	streamStr>>(*((uuidTP)m_pUuid));
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator==(const AndroidGuid& rhs) const
{
   return *(uuidTP)m_pUuid == *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator!=(const AndroidGuid& rhs) const
{
	 return *(uuidTP)m_pUuid != *(uuidTP)rhs.m_pUuid;
}
                
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator<(const AndroidGuid& rhs) const
{
   return *(uuidTP)m_pUuid < *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator<=(const AndroidGuid& rhs) const
{
    return *(uuidTP)m_pUuid <= *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator>(const AndroidGuid& rhs) const
{
   return *(uuidTP)m_pUuid > *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::operator>=(const AndroidGuid& rhs) const
{
   return *(uuidTP)m_pUuid >= *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */
bool
AndroidGuid::IsValid() const
{
    return (*(uuidTP)m_pUuid).is_nil();
}
    
//------------------------------------------------------------------------------
/**
 */
void
AndroidGuid::Generate()
{
	static boost::mt19937 ran;
	ran.seed(time(NULL)); // one should likely seed in a better way
	static boost::uuids::basic_random_generator<boost::mt19937> gen(&ran);
	*(uuidTP)m_pUuid = gen();
}
    
//------------------------------------------------------------------------------
/**
 */
String
AndroidGuid::AsString() const
{
	char uuidStr[50]={0};
	std::stringstream streamStr;
	streamStr<<(*(uuidTP)m_pUuid);
	streamStr>>uuidStr;

	String result = uuidStr;
	return result;
}
    
//------------------------------------------------------------------------------
/**
    This method allows read access to the raw binary data of the m_pUuid.
    It returns the number of bytes in the buffer, and a pointer to the
    data.
*/
SizeT
AndroidGuid::AsBinary(const unsigned char*& outPtr) const
{
	outPtr = (const unsigned char*) this->m_pUuid;
	return sizeof(boost::uuids::uuid);
}
    
//------------------------------------------------------------------------------
/**
*/
AndroidGuid
AndroidGuid::FromString(const Util::String& str)
{
    AndroidGuid newGuid;
    newGuid = str;
    return newGuid;
}
    
//------------------------------------------------------------------------------
/**
    Constructs the guid from binary data, as returned by the AsBinary().
*/
AndroidGuid
AndroidGuid::FromBinary(const unsigned char* ptr, SizeT numBytes)
{
    AndroidGuid newGuid(ptr, numBytes);
    return newGuid;
}
    
//------------------------------------------------------------------------------
/**
    This method returns a hash code for the m_pUuid, compatible with 
    Util::HashTable.
    This is simply copied from String::HashCode...
*/
IndexT
AndroidGuid::HashCode() const
{
	static boost::hash<boost::uuids::uuid> uuid_hasher;
	uint uuid_hash_value = uuid_hasher(*(uuidTP)m_pUuid);
	return (IndexT)uuid_hash_value;
}

AndroidGuid::AndroidGuid()
{
	m_pUuid = new boost::uuids::uuid(); 
}
//------------------------------------------------------------------------
AndroidGuid::~AndroidGuid()
{
	if ( m_pUuid )
	{
		delete (uuidTP)m_pUuid;
	}

}
    
//------------------------------------------------------------------------------
/**
 */

AndroidGuid::AndroidGuid(const AndroidGuid& rhs)
{
   *(uuidTP)m_pUuid = *(uuidTP)rhs.m_pUuid;
}
    
//------------------------------------------------------------------------------
/**
 */

AndroidGuid::AndroidGuid(const unsigned char* ptr, SizeT size)
{
	n_assert((0 != ptr) && (size == sizeof(boost::uuids::uuid)));
	Memory::Copy(ptr, this->m_pUuid, sizeof(boost::uuids::uuid));
}
    
//------------------------------------------------------------------------------
/**
 */
 SizeT
AndroidGuid::BinarySize()
{
    return sizeof(boost::uuids::uuid);
}
}
#endif