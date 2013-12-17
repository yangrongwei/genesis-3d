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
#include "stdneb.h"
#include "serialization/serialize.h"


namespace Serialization
{
	const SerializationArgs* SerializationArgs::Empty = NULL;


	SerializationArgs::SerializationArgs()
	{

	}
	SerializationArgs::~SerializationArgs()
	{

	}





	__ImplementClass(Serialization::SerializeBase, 'SSZB', Core::RefCounted);
	//------------------------------------------------------------------------
	SerializeBase::SerializeBase()
		: mIsOpen(false)
	{
		
	}
	//------------------------------------------------------------------------
	SerializeBase::~SerializeBase()
	{
		n_assert(!mIsOpen);
	}

	__ImplementClass(Serialization::SerializeReader, 'ARDE', Serialization::SerializeBase);
	//------------------------------------------------------------------------
	void SerializeReader::SerializeVersion( SVersion& ver)
	{
		n_error("SerializeReader::SerializeVersion empty code");
	}

	void SerializeReader::SerializeInt(const char* attrm, int& i )
	{
		n_error("SerializeReader::SerializeInt empty code");
	}	

	void SerializeReader::SerializeUInt(const char* attr, uint& i )
	{
		n_error("SerializeReader::SerializeUInt empty code");
	}

	void SerializeReader::SerializeBool(const char* attr, bool& b)
	{
		n_error("SerializeReader::SerializeBool empty code");
	}

	void SerializeReader::SerializeFloat(const char* attr, float& f)
	{
		n_error("SerializeReader::SerializeFloat empty code");
	}

	void SerializeReader::SerializeDouble(const char* attr, double& f)
	{
		n_error("SerializeReader::SerializeDouble empty code");
	}

	void SerializeReader::SerializeString(const char* attr, Util::String& str)
	{
		n_error("SerializeReader::SerializeString empty code");
	}

	void SerializeReader::SerializeFloat2(const char* attr, Math::float2& f2 )
	{
		n_error("SerializeReader::SerializeFloat2 empty code");
	}

	void SerializeReader::SerializeFloat3(const char* attr, Math::float3& f3 )
	{
		n_error("SerializeReader::SerializeFloat3 empty code");
	}

	void SerializeReader::SerializeFloat4(const char* attr, Math::float4& f4 )
	{
		n_error("SerializeReader::SerializeFloat4 empty code");
	}

	void SerializeReader::SerializeQuaternion(const char* attr, Math::quaternion& q )
	{
		n_error("SerializeReader::SerializeQuaternion empty code");
	}

	void SerializeReader::SerializeMatrix44(const char* attr, Math::matrix44& m )
	{
		n_error("SerializeReader::SerializeMatrix44 empty code");
	}

	void SerializeReader::SerializeColor32(const char* attr, Math::Color32& c32 )
	{
		n_error("SerializeReader::SerializeColor32 empty code");
	}

	void SerializeReader::SerializeColorF(const char* attr, Math::ColorF& cf )
	{
		n_error("SerializeReader::SerializeColorF empty code");
	}

	void SerializeReader::SerializeAssetPath(const char* attr, Util::AssetPath& ap )
	{
		n_error("SerializeReader::SerializeAssetPath empty code");
	}

	void SerializeReader::SerializeBBox(const char* attr, Math::bbox& bb )
	{
		n_error("SerializeReader::SerializeBBox empty code");
	}

	void SerializeReader::SerializeVariant(const char* attr, Util::Variant& v )
	{
		n_error("SerializeReader::SerializeVariant empty code");
	}

	bool SerializeReader::BeginFileSerialize()
	{
		n_error("SerializeReader::BeginFileSerialize empty code");
		return false;
	}

	bool SerializeReader::EndFileSerialize()
	{
		n_error("SerializeReader::EndFileSerialize empty code");
		return false;
	}

	void SerializeReader::BeginSerializeObject( Util::FourCC& fourcc )
	{
		n_error("SerializeReader::BeginSerializeObject");
	}
	void SerializeReader::EndSerializeObject()
	{
		n_error("SerializeReader::EndSerializeObject");
	}
	void SerializeReader::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		n_error("SerializeReader::BeginSerializeSuper");
	}
	void SerializeReader::EndSerializeSuper()
	{
		n_error("SerializeReader::EndSerializeSuper");
	}
}
namespace Serialization
{
	__ImplementClass(Serialization::SerializeWriter, 'AWRT', Serialization::SerializeBase);
	//---------------	---------------------------------------------------------
	void SerializeWriter::SerializeVersion( SVersion ver)
	{
		n_error("SerializeWriter::SerializeVersion empty code");
	}

	void SerializeWriter::SerializeInt(const char* attrm, int i )
	{
		n_error("SerializeWriter::SerializeInt empty code");
	}	

	void SerializeWriter::SerializeUInt(const char* attr, uint i )
	{
		n_error("SerializeWriter::SerializeUInt empty code");
	}

	void SerializeWriter::SerializeBool(const char* attr, bool b)
	{
		n_error("SerializeWriter::SerializeBool empty code");
	}

	void SerializeWriter::SerializeFloat(const char* attr, float f)
	{
		n_error("SerializeWriter::SerializeFloat empty code");
	}

	void SerializeWriter::SerializeDouble(const char* attr, double f)
	{
		n_error("SerializeWriter::SerializeDouble empty code");
	}	

	void SerializeWriter::SerializeString(const char* attr, const Util::String& str)
	{
		n_error("SerializeWriter::SerializeString empty code");
	}

	void SerializeWriter::SerializeFloat2(const char* attr, const Math::float2& f2 )
	{
		n_error("SerializeWriter::SerializeFloat2 empty code");
	}

	void SerializeWriter::SerializeFloat3(const char* attr, const Math::float3& f3 )
	{
		n_error("SerializeWriter::SerializeFloat3 empty code");
	}

	void SerializeWriter::SerializeFloat4(const char* attr, const Math::float4& f4 )
	{
		n_error("SerializeWriter::SerializeFloat4 empty code");
	}

	void SerializeWriter::SerializeQuaternion(const char* attr, const Math::quaternion& q )
	{
		n_error("SerializeWriter::SerializeQuaternion empty code");
	}

	void SerializeWriter::SerializeMatrix44(const char* attr, const Math::matrix44& m )
	{
		n_error("SerializeWriter::SerializeMatrix44 empty code");
	}

	void SerializeWriter::SerializeColor32(const char* attr, const Math::Color32& c32 )
	{
		n_error("SerializeWriter::SerializeColor32 empty code");
	}

	void SerializeWriter::SerializeColorF(const char* attr, const Math::ColorF& cf )
	{
		n_error("SerializeWriter::SerializeColorF empty code");
	}

	void SerializeWriter::SerializeAssetPath( const char* attr, const Util::AssetPath& ap )
	{
		n_error("SerializeWriter::SerializeAssetPath empty code");
	}

	void SerializeWriter::SerializeBBox(const char* attr, const Math::bbox& bb )
	{
		n_error("SerializeWriter::SerializeBBox empty code");
	}

	void SerializeWriter::SerializeVariant(const char* attr, const Util::Variant& v )
	{
		n_error("SerializeWriter::SerializeVariant empty code");
	}

	void SerializeWriter::BeginFileSerialize()
	{
		n_error("SerializeWriter::BeginFileSerialize empty code");
	}

	void SerializeWriter::EndFileSerialize()
	{
		n_error("SerializeWriter::EndFileSerialize empty code");
	}

	void SerializeWriter::BeginSerializeObject( const Util::FourCC& fourcc )
	{
		n_error("SerializeWriter::BeginSerializeObject");
	}
	void SerializeWriter::EndSerializeObject()
	{
		n_error("SerializeWriter::EndSerializeObject");
	}

	void SerializeWriter::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		n_error("SerializeWriter::BeginSerializeSuper");
	}
	void SerializeWriter::EndSerializeSuper()
	{
		n_error("SerializeWriter::EndSerializeSuper");
	}


}
