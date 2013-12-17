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
#include "serialization/binaryserialize.h"

// - simple to help typing fast
#define __ISVALID_READER__( FunName ) 	if ( !(this->IsInit()) ) { n_assert( "SerializeBinaryReader::"#FunName",haven't been init" ); return; }
#define __ISVALID_WRITER__( FunName ) 	if ( !(this->IsInit()) ) { n_assert( "SerializeBinaryWriter::"#FunName",haven't been init" ); return; }

namespace Serialization
{
	__ImplementClass(Serialization::SerializeBinaryReader, 'SRBR', Serialization::SerializeReader);
	__ImplementClass(Serialization::SerializeBinaryWriter, 'SRBW', Serialization::SerializeWriter);
	
	const static SVersion s_ciDefaultFileVersion = 1;
	const static uint s_ciIdentifyTag			 = 0xFF0000FF;


	//------------------------------------------------------------------------
	SerializeBinaryReader::SerializeBinaryReader()
		: mInit( false )
		, mBinReaderPtr( NULL )
		, mVersion( s_ciDefaultFileVersion )
	{}
	//------------------------------------------------------------------------
	SerializeBinaryWriter::SerializeBinaryWriter()
		: mInit( false )
		, mBinWriterPtr( NULL )
		, mVersion( s_ciDefaultFileVersion )
	{}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeVersion( SVersion& ver)
	{
		__ISVALID_READER__ ( SerializeVersion() );

		uint v = mBinReaderPtr->ReadUInt();
		ver = static_cast<SVersion>( v );
	}
	void SerializeBinaryWriter::SerializeVersion( SVersion ver)
	{
		__ISVALID_WRITER__ ( SerializeVersion() );
		uint v = static_cast<uint>( ver );
		mBinWriterPtr->WriteUInt( v );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeInt(const char* attrm, int& i )
	{
		__ISVALID_READER__( SerializeInt() );
		i = mBinReaderPtr->ReadInt();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeInt(const char* attrm, int i )
	{
		__ISVALID_WRITER__( SerializeInt() );
		mBinWriterPtr->WriteInt( i );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeUInt(const char* attr, uint& i )
	{
		__ISVALID_READER__( SerializeUInt() );

		i = mBinReaderPtr->ReadUInt();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeUInt(const char* attr, uint i )
	{
		__ISVALID_WRITER__( SerializeUInt() );

		mBinWriterPtr->WriteUInt( i );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeBool(const char* attr, bool& b)
	{
		__ISVALID_READER__( SerializeBool() );

		b = mBinReaderPtr->ReadBool();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeBool(const char* attr, bool b)
	{
		__ISVALID_WRITER__( SerializeBool() );

		mBinWriterPtr->WriteBool( b );
	}	
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeFloat(const char* attr, float& f)
	{
		__ISVALID_READER__( SerializeFloat() );

		f = mBinReaderPtr->ReadFloat();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeFloat(const char* attr, float f)
	{
		__ISVALID_WRITER__( SerializeFloat() );

		mBinWriterPtr->WriteFloat( f );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeDouble(const char* attr, double& f)
	{
		__ISVALID_READER__( SerializeDouble() );

		f = mBinReaderPtr->ReadDouble();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeDouble(const char* attr, double f)
	{
		__ISVALID_WRITER__( SerializeDouble() );

		mBinWriterPtr->WriteDouble( f );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeString(const char* attr, Util::String& str)
	{
		__ISVALID_READER__( SerializeString() );

		str = mBinReaderPtr->ReadString();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeString(const char* attr, const Util::String& str)
	{
		__ISVALID_WRITER__( SerializeString() );

		mBinWriterPtr->WriteString( str );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeFloat2(const char* attr, Math::float2& f2 )
	{
		__ISVALID_READER__( SerializeFloat2() );
		
		f2 = mBinReaderPtr->ReadFloat2();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeFloat2(const char* attr, const Math::float2& f2 )
	{
		__ISVALID_WRITER__( SerializeFloat2() );

		mBinWriterPtr->WriteFloat2( f2 );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeFloat3(const char* attr, Math::float3& f3 )
	{
		__ISVALID_READER__( SerializeFloat3() );

		Math::float2 f2 = mBinReaderPtr->ReadFloat2();
		float f  = mBinReaderPtr->ReadFloat();
		Math::scalar s = static_cast<Math::scalar>( f );
		Math::float3 v( f2.x(), f2.y(), s );
		f3 = v;
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeFloat3(const char* attr, const Math::float3& f3 )
	{
		__ISVALID_WRITER__( SerializeFloat3() );
		Math::float2 f2( f3.x(), f3.y() );
		Math::scalar s = f3.z();

		mBinWriterPtr->WriteFloat2( f2 );
		mBinWriterPtr->WriteFloat( s );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeFloat4(const char* attr, Math::float4& f4 )
	{
		__ISVALID_READER__( SerializeFloat4() );

		f4 = mBinReaderPtr->ReadFloat4();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeFloat4(const char* attr, const Math::float4& f4 )
	{
		__ISVALID_WRITER__( SerializeFloat4() );

		mBinWriterPtr->WriteFloat4( f4 );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeQuaternion(const char* attr, Math::quaternion& q )
	{
		__ISVALID_READER__( SerializeQuaternion() );

		Math::float4 f4 = mBinReaderPtr->ReadFloat4();
		q.set( f4 );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeQuaternion(const char* attr, const Math::quaternion& q )
	{
		__ISVALID_WRITER__( SerializeQuaternion() );

		Math::float4 f4( q.x(), q.y(), q.z(), q.w() );
		mBinWriterPtr->WriteFloat4( f4 );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeMatrix44(const char* attr, Math::matrix44& m )
	{
		__ISVALID_READER__( SerializeMatrix44() );

		m = mBinReaderPtr->ReadMatrix44();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeMatrix44(const char* attr, const Math::matrix44& m )
	{
		__ISVALID_WRITER__( SerializeMatrix44() );

		mBinWriterPtr->WriteMatrix44( m );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeColor32(const char* attr, Math::Color32& c32 )
	{
		__ISVALID_READER__( SerializeColor32() );

		uint ui = mBinReaderPtr->ReadUInt();
		c32 = Math::Color32( ui );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeColor32(const char* attr, const Math::Color32& c32 )
	{
		__ISVALID_WRITER__( SerializeColor32() );

		uint ui = c32.ToUInt();
		mBinWriterPtr->WriteUInt( ui );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeColorF(const char* attr, Math::ColorF& cf )
	{
		__ISVALID_READER__( SerializeColorF() );

		Math::float4 temp = mBinReaderPtr->ReadFloat4();
		cf.r = temp.x();
		cf.g = temp.y();
		cf.b = temp.z();
		cf.a = temp.w();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeColorF(const char* attr, const Math::ColorF& cf )
	{
		__ISVALID_WRITER__( SerializeColorF() );

		Math::float4 f4( cf.r, cf.g, cf.b, cf.a );
		mBinWriterPtr->WriteFloat4( f4 );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeAssetPath( const char* attr, Util::AssetPath& ap )
	{
		__ISVALID_READER__( SerializeAssetPath() );

		Util::String assetPath	= mBinReaderPtr->ReadString();
		int				type	= mBinReaderPtr->ReadInt();

		ap.path = assetPath;
		ap.type	= type;
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeAssetPath( const char* attr, const Util::AssetPath& ap )
	{
		__ISVALID_WRITER__( SerializeAssetPath() );

		mBinWriterPtr->WriteString( ap.path);
		mBinWriterPtr->WriteInt( ap.type);
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeBBox(const char* attr, Math::bbox& bb )
	{
		__ISVALID_READER__( SerializeBBox() );

		Math::float4 fMin = mBinReaderPtr->ReadFloat4();
		Math::float4 fMax = mBinReaderPtr->ReadFloat4();
		
		Math::point pointMin( fMin );
		Math::point pointMax( fMax );
		
		bb.set( pointMin, pointMax );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeBBox(const char* attr, const Math::bbox& bb )
	{
		__ISVALID_WRITER__( SerializeBBox() );

		mBinWriterPtr->WriteFloat4( bb.pmin );
		mBinWriterPtr->WriteFloat4( bb.pmax );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::SerializeVariant(const char* attr, Util::Variant& v )
	{
		n_error( "SerializeBinaryReader::SerializeVariant, not support this in binary reader" );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::SerializeVariant(const char* attr, const Util::Variant& v )
	{
		n_error( "SerializeBinaryWriter::SerializeVariant, not support this in binary writer" );
	}
	//------------------------------------------------------------------------
	bool SerializeBinaryReader::BeginFileSerialize()
	{
		n_assert( mStream );
		//n_assert( !mStream->IsOpen() );
		n_assert( !mBinReaderPtr.isvalid() );

		mBinReaderPtr = IO::BinaryReader::Create();
		if ( NULL==mBinReaderPtr )
		{
			n_error( "SerializeBinaryReader::BeginFileSerialize, mBinReaderPtr Null pointer!" );
			return false;
		}

		mBinReaderPtr->SetStream( mStream );
		bool bOK = mBinReaderPtr->Open();
		if ( !bOK )
		{
			n_printf( "SerializeBinaryWriter::Init, can't open the stream!" );
			n_assert( "SerializeBinaryWriter::Init, can't open the stream!" );
			return false;
		}

		uint identify = mBinReaderPtr->ReadUInt();
		if ( identify!=s_ciIdentifyTag )
		{
			n_printf( "SerializeBinaryWriter::Init, error tag!" );
			n_assert( "SerializeBinaryWriter::Init, error!" );		
			return false;
		}

		mInit = true;

		// - begin file serialize
		mVersion = mBinReaderPtr->ReadUInt();

		return true;
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::BeginFileSerialize()
	{
		n_assert( mStream.isvalid() );
		//n_assert( !mStream->IsOpen() );
		n_assert( !mBinWriterPtr.isvalid() );

		mBinWriterPtr = IO::BinaryWriter::Create();
		if ( NULL==mBinWriterPtr )
		{
			n_error( "SerializeBinaryWriter::Init, mBinWriterPtr Null pointer!" );
		}

		mBinWriterPtr->SetStream( mStream );
		bool bOK = mBinWriterPtr->Open();
		if ( !bOK )
		{
			n_printf( "SerializeBinaryWriter::Init, can't open the stream!" );
			n_assert( "SerializeBinaryWriter::Init, can't open the stream!" );
			return;
		}

		mInit = true;

		// - begin file file serialize
		// - write identify tag
		mBinWriterPtr->WriteUInt( s_ciIdentifyTag );

		mBinWriterPtr->WriteUInt( mVersion );
	}
	//------------------------------------------------------------------------
	bool SerializeBinaryReader::EndFileSerialize()
	{
		if ( !(this->IsInit()) ) 
		{ 
			n_assert( "SerializeBinaryReader::EndFileSerialize(),haven't been init" ); 
			return false; 
		}

		mBinReaderPtr->Close();
		return true;
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::EndFileSerialize()
	{
		__ISVALID_WRITER__( EndFileSerialize() );

		mBinWriterPtr->Close();
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		__ISVALID_READER__( BeginSerializeSuper() );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		__ISVALID_WRITER__( BeginSerializeSuper() );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::EndSerializeSuper()
	{
		__ISVALID_READER__( EndSerializeSuper() );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::EndSerializeSuper()
	{
		__ISVALID_WRITER__( EndSerializeSuper() );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::BeginSerializeObject( Util::FourCC& fourcc )
	{
		__ISVALID_READER__( BeginSerializeObject() );
		Util::FourCC fcc = mBinReaderPtr->ReadUInt();
		fourcc = fcc;
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::BeginSerializeObject( const Util::FourCC& fourcc )
	{
		__ISVALID_WRITER__( BeginSerializeObject() );
		uint ui= fourcc.AsUInt();
		mBinWriterPtr->WriteUInt( ui );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryReader::EndSerializeObject()
	{
		__ISVALID_READER__( EndSerializeObject() );
	}
	//------------------------------------------------------------------------
	void SerializeBinaryWriter::EndSerializeObject()
	{
		__ISVALID_WRITER__( EndSerializeObject() );
	}
}


