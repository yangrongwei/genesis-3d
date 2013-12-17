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
#ifndef __xmserialize_H__
#define __xmserialize_H__

#include "util/stack.h"
#include "serialization/serialize.h"
#include "io/xmlreader.h"
#include "io/xmlwriter.h"

namespace Serialization
{
	struct XmlFileHeader
	{
		XmlFileHeader()
			: mVersion(0)
		{}
		SVersion mVersion;
	};
}


namespace Serialization
{
	class SerializeXmlReader: public Serialization::SerializeReader
	{
		__DeclareClass(SerializeXmlReader);
	public:

		SerializeXmlReader();
		virtual ~SerializeXmlReader(){ };

	public:
		// @ Serialization::SerializeReader::SerializeVersion
		virtual void SerializeVersion( SVersion& ver);

		// @ Serialization::SerializeReader::SerializeInt
		virtual void SerializeInt(const char* attrm, int& i );

		// @ Serialization::SerializeReader::SerializeUInt
		virtual void SerializeUInt(const char* attr, uint& i );

		// @ Serialization::SerializeReader::SerializeBool
		virtual void SerializeBool(const char* attr, bool& b);

		// @ Serialization::SerializeReader::SerializeFloat
		virtual void SerializeFloat(const char* attr, float& f);

		// @ Serialization::SerializeReader::SerializeDouble
		virtual void SerializeDouble(const char* attr, double& f);

		// @ Serialization::SerializeReader::SerializeString
		virtual void SerializeString(const char* attr, Util::String& str);

		// @ Serialization::SerializeReader::SerializeFloat2
		virtual void SerializeFloat2(const char* attr, Math::float2& f2 );

		// @ Serialization::SerializeReader::SerializeFloat3
		virtual void SerializeFloat3(const char* attr, Math::float3& f3 );

		// @ Serialization::SerializeReader::SerializeFloat4
		virtual void SerializeFloat4(const char* attr, Math::float4& f4 );

		// @ Serialization::SerializeReader::SerializeQuaternion
		virtual void SerializeQuaternion(const char* attr, Math::quaternion& q );

		// @ Serialization::SerializeReader::SerializeMatrix44
		virtual void SerializeMatrix44(const char* attr, Math::matrix44& m );

		// @ Serialization::SerializeReader::SerializeColor32
		virtual void SerializeColor32(const char* attr, Math::Color32& c32 );

		// @ Serialization::SerializeReader::SerializeColorF
		virtual void SerializeColorF(const char* attr, Math::ColorF& cf );

		// @ Serialization::SerializeReader::SerializeAssetPath
		virtual void SerializeAssetPath(const char* attr, Util::AssetPath& ap);

		// @ Serialization::SerializeReader::SerializeBBox
		virtual void SerializeBBox(const char* attr, Math::bbox& bb );

		// @ Serialization::SerializeReader::SerializeVariant
		virtual void SerializeVariant(const char* attr, Util::Variant& v );

		// @ Serialization::SerializeReader::BeginFileSerialize
		virtual bool BeginFileSerialize();

		// @ Serialization::SerializeReader::EndFileSerialize
		virtual bool EndFileSerialize();

		// @ Serialization::SerializeReader::BeginSerializeSuper
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );

		// @ Serialization::SerializeReader::EndSerializeSuper
		virtual void EndSerializeSuper();

		// @ Serialization::SerializeReader::BeginSerializeObject
		virtual void BeginSerializeObject( Util::FourCC& fourcc );

		// @ Serialization::SerializeReader::EndSerializeObject
		virtual void EndSerializeObject();

		//@ Serialization::SerializeReader::IsAttr.
		virtual bool HasAttr(const char* attrm);
	protected:
		void PushXmlNode(void);
		void PopXmlNode();
		void FindNextChild( const Util::String& childName );
		void BeginAttribute();
		void EndAttribute();
	
	protected:
		GPtr<IO::XmlReader> mXmlReader;
		XmlFileHeader mFileHeader;

		// support reading the Objects recursively.
		Util::Array<TiXmlElement*> mXmlNodeList;
		IndexT mChildNodeIndex;	   
		IndexT mCurrentNodeIndex;
	};

	//------------------------------------------------------------------------
	inline 
	void
	SerializeXmlReader::PushXmlNode(void)
	{
		++mCurrentNodeIndex;
		mChildNodeIndex = mCurrentNodeIndex + 1;
		if ( mChildNodeIndex >= mXmlNodeList.Size() )
		{
			// multiple the container
			mXmlNodeList.Fill( mXmlNodeList.Size(), mChildNodeIndex, NULL );
		}
		mXmlNodeList[mCurrentNodeIndex] = mXmlReader->GetCurrentNode();

	}
	//------------------------------------------------------------------------
	inline
	void
	SerializeXmlReader::PopXmlNode(void)
	{
		n_assert( mChildNodeIndex == mCurrentNodeIndex + 1 );
		n_assert( mChildNodeIndex < mXmlNodeList.Size() );
		mXmlNodeList[mChildNodeIndex] = NULL;

		mChildNodeIndex = mCurrentNodeIndex;
		--mCurrentNodeIndex;
		n_assert( mXmlNodeList[mCurrentNodeIndex] );
		mXmlReader->SetCurrentNode( mXmlNodeList[mCurrentNodeIndex] );
	}
}



namespace Serialization
{
	class SerializeXmlWriter: public Serialization::SerializeWriter
	{
		__DeclareClass(SerializeXmlWriter);
	public:
		SerializeXmlWriter();

		virtual ~SerializeXmlWriter(){ };


	public:

		// @ Serialization::SerializeWriter::SerializeVersion
		virtual void SerializeVersion( SVersion ver);

		// @ Serialization::SerializeWriter::SerializeInt
		virtual void SerializeInt(const char* attrm, int i );

		// @ Serialization::SerializeWriter::SerializeUInt
		virtual void SerializeUInt(const char* attr, uint i );

		// @ Serialization::SerializeWriter::SerializeBool
		virtual void SerializeBool(const char* attr, bool b);

		// @ Serialization::SerializeWriter::SerializeFloat
		virtual void SerializeFloat(const char* attr, float f);

		// @ Serialization::SerializeWriter::SerializeDouble
		virtual void SerializeDouble(const char* attr, double f);

		// @ Serialization::SerializeWriter::SerializeString
		virtual void SerializeString(const char* attr, const Util::String& str);

		// @ Serialization::SerializeWriter::SerializeFloat2
		virtual void SerializeFloat2(const char* attr, const Math::float2& f2 );

		// @ Serialization::SerializeWriter::SerializeFloat3
		virtual void SerializeFloat3(const char* attr, const Math::float3& f3 );

		// @ Serialization::SerializeWriter::SerializeFloat4
		virtual void SerializeFloat4(const char* attr, const Math::float4& f4 );

		// @ Serialization::SerializeWriter::SerializeQuaternion
		virtual void SerializeQuaternion(const char* attr, const Math::quaternion& q );

		// @ Serialization::SerializeWriter::SerializeMatrix44
		virtual void SerializeMatrix44(const char* attr, const Math::matrix44& m );

		// @ Serialization::SerializeWriter::SerializeColor32
		virtual void SerializeColor32(const char* attr, const Math::Color32& c32 );

		// @ Serialization::SerializeWriter::SerializeColorF
		virtual void SerializeColorF(const char* attr, const Math::ColorF& cf );

		// @ Serialization::SerializeWriter::SerializeAssetPath
		virtual void SerializeAssetPath(const char* attr, const Util::AssetPath& ap );

		// @ Serialization::SerializeWriter::SerializeVariant
		virtual void SerializeBBox(const char* attr, const Math::bbox& bb );

		// @ Serialization::SerializeWriter::SerializeVariant
		virtual void SerializeVariant(const char* attr, const Util::Variant& v );

		// @ Serialization::SerializeWriter::BeginFileSerialize
		virtual void BeginFileSerialize();

		// @ Serialization::SerializeWriter::EndFileSerialize
		virtual void EndFileSerialize();

		// @ Serialization::SerializeWriter::BeginSerializeSuper
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );

		// @ Serialization::SerializeWriter::EndSerializeSuper
		virtual void EndSerializeSuper();

		// @ Serialization::SerializeWriter::BeginSerializeObject
		virtual void BeginSerializeObject( const Util::FourCC& fourcc );

		// @ Serialization::SerializeWriter::EndSerializeObject
		virtual void EndSerializeObject();
	
		// @ Serialization::SerializeWriter::SetString
		virtual void SetString( const Util::String& attributeName , const Util::String& attributeValue ) ;
		
	protected:
		void BeginAttribute();
		void EndAttribute();

	protected:
		GPtr<IO::XmlWriter> mXmlWriter;
		XmlFileHeader mFileHeader;
	};

}

#endif // __xmserialize_H__
