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
#ifndef __BINARY_SERIALIZE_H__
#define __BINARY_SERIALIZE_H__

#include "serialization/serialize.h"

namespace Serialization
{
	class SerializeBinaryReader: public Serialization::SerializeReader
	{
		typedef GPtr<IO::BinaryReader> TBinaryReaderPtr;
		__DeclareClass( SerializeBinaryReader );
	public:
		SerializeBinaryReader();
		virtual ~SerializeBinaryReader(){ };

		virtual void SerializeVersion( SVersion& ver);
		virtual void SerializeInt(const char* attrm, int& i );
		virtual void SerializeUInt(const char* attr, uint& i );
		virtual void SerializeBool(const char* attr, bool& b);
		virtual void SerializeFloat(const char* attr, float& f);
		virtual void SerializeDouble(const char* attr, double& f);
		virtual void SerializeString(const char* attr, Util::String& str);
		virtual void SerializeFloat2(const char* attr, Math::float2& f2 );
		virtual void SerializeFloat3(const char* attr, Math::float3& f3 );
		virtual void SerializeFloat4(const char* attr, Math::float4& f4 );
		virtual void SerializeQuaternion(const char* attr, Math::quaternion& q );
		virtual void SerializeMatrix44(const char* attr, Math::matrix44& m );
		virtual void SerializeColor32(const char* attr, Math::Color32& c32 );
		virtual void SerializeColorF(const char* attr, Math::ColorF& cf );
		virtual void SerializeAssetPath(const char* attr, Util::AssetPath& ap );
		virtual void SerializeBBox(const char* attr, Math::bbox& bb );
		virtual void SerializeVariant(const char* attr, Util::Variant& v );
		virtual bool BeginFileSerialize();
		virtual bool EndFileSerialize();
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );
		virtual void EndSerializeSuper();
		virtual void BeginSerializeObject( Util::FourCC& fourcc );
		virtual void EndSerializeObject();
	private:
		bool IsInit();
		// - private data
		bool mInit;
		TBinaryReaderPtr mBinReaderPtr;
		SVersion mVersion;
	};

	class SerializeBinaryWriter: public Serialization::SerializeWriter
	{
		typedef GPtr<IO::BinaryWriter> TBinaryWriterPtr;
		__DeclareClass( SerializeBinaryWriter );
	public:
		SerializeBinaryWriter();
		virtual ~SerializeBinaryWriter(){ };

		virtual void SerializeVersion( SVersion ver);
		virtual void SerializeInt(const char* attrm, int i );
		virtual void SerializeUInt(const char* attr, uint i );
		virtual void SerializeBool(const char* attr, bool b);
		virtual void SerializeFloat(const char* attr, float f);
		virtual void SerializeDouble(const char* attr, double f);
		virtual void SerializeString(const char* attr, const Util::String& str);
		virtual void SerializeFloat2(const char* attr, const Math::float2& f2 );
		virtual void SerializeFloat3(const char* attr, const Math::float3& f3 );
		virtual void SerializeFloat4(const char* attr, const Math::float4& f4 );
		virtual void SerializeQuaternion(const char* attr, const Math::quaternion& q );
		virtual void SerializeMatrix44(const char* attr, const Math::matrix44& m );
		virtual void SerializeColor32(const char* attr, const Math::Color32& c32 );
		virtual void SerializeColorF(const char* attr, const Math::ColorF& cf );
		virtual void SerializeAssetPath(const char* attr, const Util::AssetPath& ap );
		virtual void SerializeBBox(const char* attr, const Math::bbox& bb );
		virtual void SerializeVariant(const char* attr, const Util::Variant& v );
		virtual void BeginFileSerialize();
		virtual void EndFileSerialize();
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );
		virtual void EndSerializeSuper();
		virtual void BeginSerializeObject( const Util::FourCC& fourcc );
		virtual void EndSerializeObject();
	private:
		bool IsInit();
		// - private data
		bool mInit;
		TBinaryWriterPtr mBinWriterPtr;
		SVersion mVersion;
	};

	inline bool SerializeBinaryReader::IsInit()
	{
		return mInit;
	}

	inline bool SerializeBinaryWriter::IsInit()
	{
		return mInit;
	}

};

#endif // __BINARY_SERIALIZE_H__
