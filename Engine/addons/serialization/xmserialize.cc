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
#include "exception/exceptions.h"
#include "serialization/xmserialize.h"

namespace Serialization
{
	__ImplementClass(Serialization::SerializeXmlReader, 'AXRD', Serialization::SerializeReader);
	__ImplementClass(Serialization::SerializeXmlWriter, 'AXWT', Serialization::SerializeWriter);

	
	const static SVersion s_XmlFileVersion = 1;
	const static Util::String s_FileRoot("AppXMLFileTag");

	const static Util::String s_FileHeader("AppXMLFileHeaderTag");
	const static char* s_FileHeadVersion = "AppXMLFileVersionTag";

	const static Util::String s_ObjectHeader("AppObjectTag");
	const static char* s_ObjectFourCC = "AppObjectFourCCTag";

	const static Util::String s_ObjectSuperHeader("AppObjectSuperTag");
	const static char* s_ObjectSuperName = "AppObjectSuperNameTag";

	const static char* s_ObjectVersion = "AppObjectVersionTag";

	const static char* s_ObjectAttribute = "AppAttributeTag";

	const static char* s_ObjectVariantValue = "AppVariantValueTag";


	//------------------------------------------------------------------------
	SerializeXmlReader::SerializeXmlReader()
		: mCurrentNodeIndex(-1)
		, mChildNodeIndex(-1)
	{
		mXmlNodeList.Fill( mXmlNodeList.Size(), 16, NULL );	//	16 depth maybe enough
	}
	//------------------------------------------------------------------------
	SerializeXmlWriter::SerializeXmlWriter()
	{
		mFileHeader.mVersion = s_XmlFileVersion;
	}

	//------------------------------------------------------------------------
	bool SerializeXmlReader::BeginFileSerialize()
	{
		n_assert( mStream );
		n_assert( !mXmlReader.isvalid() );

		mXmlReader = IO::XmlReader::Create();
		mXmlReader->SetStream( mStream );
		bool bOK = mXmlReader->Open(); 
		if (!bOK)
		{
			//n_warning("SerializeXmlReader::BeginFileSerialize(): failed to open %s",mStream->GetURI().AsString().AsCharPtr());
			return false;
		}

		// file root
		if (NULL == mXmlReader->GetCurrentNode())//	root AppXMLFileTag
		{
			SYS_EXCEPT(Exceptions::SerializeException, 
				STRING_FORMAT("can not read xml head, where %s.", mStream->GetURI().AsString().AsCharPtr()),
				GET_FUNCTION_NAME()
				);
		}
		PushXmlNode();
	
		FindNextChild( s_FileHeader );  // first object is file header
		PushXmlNode();	//	push file header node
		mFileHeader.mVersion = mXmlReader->GetInt( s_FileHeadVersion );
		PopXmlNode();	//	pop file header node

		return true;
	}
	void SerializeXmlWriter::BeginFileSerialize()
	{
		n_assert( mStream.isvalid() );
		n_assert( !mStream->IsOpen() );
		n_assert( !mXmlWriter.isvalid() );

		mXmlWriter = IO::XmlWriter::Create();
		mXmlWriter->SetStream( mStream );
		bool bOK = mXmlWriter->Open();

		if (!bOK)
		{
			SYS_EXCEPT(Exceptions::SerializeException, 
				STRING_FORMAT("xml, that is %s, open false.", mStream->GetURI().LocalPath().AsCharPtr()),
				GET_FUNCTION_NAME()
				);
		}
		// root
		bOK = mXmlWriter->BeginNode( s_FileRoot );

		// first object is file header
		bOK = mXmlWriter->BeginNode( s_FileHeader );

		if (!bOK)
		{
			SYS_EXCEPT(Exceptions::SerializeException, 
				STRING_FORMAT("no head, %s, open false.", s_FileHeader.AsCharPtr()),
				GET_FUNCTION_NAME()
				);
		}
		mXmlWriter->SetInt( s_FileHeadVersion, mFileHeader.mVersion );
		mXmlWriter->EndNode();
	}
	//------------------------------------------------------------------------
	bool SerializeXmlReader::EndFileSerialize()
	{
		n_assert( mXmlReader.isvalid() && mXmlReader->IsOpen() );
		

		TiXmlElement* curNode = mXmlReader->GetCurrentNode();
		if (curNode && mCurrentNodeIndex == 0 && mChildNodeIndex == 1)
		{
			mXmlReader->Close();
			return true;
		}
		mXmlReader->Close();
		return false;
	}
	void SerializeXmlWriter::EndFileSerialize()
	{
		n_assert( mXmlWriter.isvalid() && mXmlWriter->IsOpen() );

		mXmlWriter->EndNode();	//end root
		mXmlWriter->Close();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::BeginSerializeObject( Util::FourCC& fourcc )
	{

		n_assert( mXmlReader && mXmlReader->IsOpen() );

		TiXmlElement* curNode = mXmlReader->GetCurrentNode();
		//if (!curNode)
		//{
		//	n_warning("SerializeXmlReader::BeginSerializeObject(): failed to open %s",mStream->GetURI().AsString().AsCharPtr());
		//	return;
		//}

		if (NULL == curNode)//	root AppXMLFileTag
		{
			mXmlReader->Close();
			SetOpen(false);
			SYS_EXCEPT(Exceptions::SerializeException, 
				STRING_FORMAT("object serialize error in %s.", mStream->GetURI().AsString().AsCharPtr()),
				GET_FUNCTION_NAME()
				);
		}
		
		FindNextChild( s_ObjectHeader );
		PushXmlNode();
		
		Util::String strFourCC = mXmlReader->GetString( s_ObjectFourCC );
		fourcc.SetFromString( strFourCC );
	}
	void SerializeXmlWriter::BeginSerializeObject( const Util::FourCC& fourcc )
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );

		bool bOK = mXmlWriter->BeginNode( s_ObjectHeader );	//	begin object
		n_assert( bOK );
		mXmlWriter->SetString( s_ObjectFourCC, fourcc.AsString() );

	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::EndSerializeObject()
	{
		n_assert( mXmlReader && mXmlReader->IsOpen() );

		TiXmlElement* curNode = mXmlReader->GetCurrentNode();
		if (!curNode)
		{
			return;
		}

		PopXmlNode();
	}
	void SerializeXmlWriter::EndSerializeObject()
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );

		mXmlWriter->EndNode();	// end object
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		n_assert( mXmlReader && mXmlReader->IsOpen() );

		FindNextChild( s_ObjectSuperHeader );
		PushXmlNode();

		// just for debug
		Util::String strSuperName = mXmlReader->GetString( s_ObjectSuperName );
	}
	void SerializeXmlWriter::BeginSerializeSuper( const Core::Rtti* pRtti )
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );

		bool bOK = mXmlWriter->BeginNode( s_ObjectSuperHeader );	//	begin object
		n_assert( bOK );

		// just for debug
		mXmlWriter->SetString( s_ObjectSuperName, pRtti->GetFourCC().AsString() );
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::EndSerializeSuper()
	{
		n_assert( mXmlReader && mXmlReader->IsOpen() );
		PopXmlNode();
	}
	void SerializeXmlWriter::EndSerializeSuper()
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );

		mXmlWriter->EndNode();	// end object
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::BeginAttribute()
	{
		n_assert( mXmlReader && mXmlReader->IsOpen() );
		FindNextChild( s_ObjectAttribute );
		PushXmlNode();
	}
	void SerializeXmlWriter::BeginAttribute()
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );
		bool bOK = mXmlWriter->BeginNode( s_ObjectAttribute );	//	begin Attribute
		n_assert( bOK );
	}

	//------------------------------------------------------------------------
	void SerializeXmlReader::EndAttribute()
	{
		n_assert( mXmlReader && mXmlReader->IsOpen() );
		PopXmlNode();
	}
	void SerializeXmlWriter::EndAttribute()
	{
		n_assert( mXmlWriter && mXmlWriter->IsOpen() );
		mXmlWriter->EndNode();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeVersion( SVersion& ver)
	{
		if ( mXmlReader->HasAttr( s_ObjectVersion))
			ver = (SVersion)( mXmlReader->GetInt( s_ObjectVersion ) );
		else
			ver = -1;
	}
	void SerializeXmlWriter::SerializeVersion( SVersion ver)
	{
		mXmlWriter->SetInt( s_ObjectVersion, (int)ver );
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeInt(const char* attrm, int& i )
	{
		BeginAttribute();
		i = mXmlReader->GetInt( attrm );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeInt(const char* attrm, int i )
	{
		BeginAttribute();
		mXmlWriter->SetInt( attrm, i );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeUInt(const char* attr, uint& i )
	{
		BeginAttribute();
		i = (uint)( mXmlReader->GetInt( attr ) );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeUInt(const char* attr, uint i )
	{
		BeginAttribute();
		mXmlWriter->SetInt( attr, (int)i );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeBool(const char* attr, bool& b)
	{
		BeginAttribute();
		b = mXmlReader->GetBool( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeBool(const char* attr, bool b)
	{
		BeginAttribute();
		mXmlWriter->SetBool( attr, b );
		EndAttribute();
	}	
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeFloat(const char* attr, float& f)
	{
		BeginAttribute();
		f = mXmlReader->GetFloat( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeFloat(const char* attr, float f)
	{
		BeginAttribute();
		mXmlWriter->SetFloat( attr, f );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeDouble(const char* attr, double& f)
	{
		BeginAttribute();
		f = mXmlReader->GetFloat( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeDouble(const char* attr, double f)
	{
		BeginAttribute();
		mXmlWriter->SetFloat( attr, (float)f );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeString(const char* attr, Util::String& str)
	{
		BeginAttribute();
		str = mXmlReader->GetString( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeString(const char* attr, const Util::String& str)
	{
		BeginAttribute();
		mXmlWriter->SetString( attr, str );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeFloat2(const char* attr, Math::float2& f2 )
	{
		BeginAttribute();
		f2 = mXmlReader->GetFloat2( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeFloat2(const char* attr, const Math::float2& f2 )
	{
		BeginAttribute();
		mXmlWriter->SetFloat2( attr, f2 );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeFloat3(const char* attr, Math::float3& f3 )
	{
		BeginAttribute();
		f3 = mXmlReader->GetFloat3(attr);
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeFloat3(const char* attr, const Math::float3& f3 )
	{
		BeginAttribute();
		mXmlWriter->SetFloat3( attr, f3 );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeFloat4(const char* attr, Math::float4& f4 )
	{
		BeginAttribute();
		f4 =  mXmlReader->GetFloat4( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeFloat4(const char* attr, const Math::float4& f4 )
	{
		BeginAttribute();
		mXmlWriter->SetFloat4( attr, f4 );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeQuaternion(const char* attr, Math::quaternion& q )
	{
		BeginAttribute();
		Math::float4 temp =  mXmlReader->GetFloat4( attr );
		q.set( temp.x(), temp.y(), temp.z(), temp.w() );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeQuaternion(const char* attr, const Math::quaternion& q )
	{
		BeginAttribute();
		mXmlWriter->SetFloat4( attr, Math::float4( q.x(), q.y(), q.z(), q.w() ) );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeMatrix44(const char* attr, Math::matrix44& m )
	{
		BeginAttribute();
		m = mXmlReader->GetMatrix44( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeMatrix44(const char* attr, const Math::matrix44& m )
	{
		BeginAttribute();
		mXmlWriter->SetMatrix44( attr, m );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeColor32(const char* attr, Math::Color32& c32 )
	{
		BeginAttribute();
		int temp = mXmlReader->GetInt( attr );
		c32 = Math::Color32( uint(temp) );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeColor32(const char* attr, const Math::Color32& c32 )
	{
		BeginAttribute();
		mXmlWriter->SetInt( attr, int(c32.ToUInt()) );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeColorF(const char* attr, Math::ColorF& cf )
	{
		BeginAttribute();
		Math::float4 temp = mXmlReader->GetFloat4( attr );
		cf.r = temp.x();
		cf.g = temp.y();
		cf.b = temp.z();
		cf.a = temp.w();
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeColorF(const char* attr, const Math::ColorF& cf )
	{
		BeginAttribute();
		mXmlWriter->SetFloat4( attr, Math::float4( cf.r, cf.g, cf.b, cf.a ) );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeAssetPath( const char* attr, Util::AssetPath& ap )
	{
		BeginAttribute();
		ap = mXmlReader->GetAssetPath( attr );
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeAssetPath( const char* attr, const Util::AssetPath& ap )
	{
		BeginAttribute();
		mXmlWriter->SetAssetPath( attr, ap);
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeBBox(const char* attr, Math::bbox& bb )
	{
		BeginAttribute();
		Util::String temp = mXmlReader->GetString( attr );
		n_assert( temp.IsValidBBox() );
		bb = temp.AsBBox();
		EndAttribute();
	}
	void SerializeXmlWriter::SerializeBBox(const char* attr, const Math::bbox& bb )
	{
		BeginAttribute();
		Util::String temp;
		temp.SetBBox( bb );
		mXmlWriter->SetString( attr, temp );
		EndAttribute();
	}
	//------------------------------------------------------------------------
	void SerializeXmlReader::SerializeVariant(const char* attr, Util::Variant& v )
	{
		BeginAttribute();
		
		Util::String strType = mXmlReader->GetString(attr);
		Util::Variant::Type t = Util::Variant::StringToType( strType );
		v.SetType( t );

		switch( t )
		{
		case Util::Variant::Int:
			v.SetInt( mXmlReader->GetInt( s_ObjectVariantValue ) );
			break;
		case Util::Variant::Float:
			v.SetFloat( mXmlReader->GetFloat( s_ObjectVariantValue ) );
			break;
		case Util::Variant::Bool:
			v.SetBool( mXmlReader->GetBool( s_ObjectVariantValue ) );
			break;
		case Util::Variant::Float4:
			v.SetFloat4( mXmlReader->GetFloat4( s_ObjectVariantValue ) );
			break;
		case Util::Variant::String:
			v.SetString( mXmlReader->GetString( s_ObjectVariantValue ) );
			break;
		case Util::Variant::Matrix44:
			v.SetMatrix44( mXmlReader->GetMatrix44( s_ObjectVariantValue ) );
			break; 
		default:
			n_error( "SerializeXmlReader::SerializeVariant: not support now for %s", Util::Variant::TypeToString(t).AsCharPtr() );
			break;
		}

		EndAttribute();
	}

	bool SerializeXmlReader::HasAttr( const char* attrm )
	{

		TiXmlElement* cur = mXmlReader->GetCurrentNode();

		TiXmlElement* next = cur->FirstChildElement(s_ObjectAttribute);

		return (0 != next->Attribute(attrm));
	
	}

	void SerializeXmlWriter::SerializeVariant(const char* attr, const Util::Variant& v )
	{
		BeginAttribute();

		Util::Variant::Type t = v.GetType();
		mXmlWriter->SetString( attr, Util::Variant::TypeToString(t) );
		
		switch( t )
		{
		case Util::Variant::Int:
			mXmlWriter->SetInt( s_ObjectVariantValue,  v.GetInt() );
			break;
		case Util::Variant::Float:
			mXmlWriter->SetFloat( s_ObjectVariantValue,  v.GetFloat() );
			break;
		case Util::Variant::Bool:
			mXmlWriter->SetBool( s_ObjectVariantValue,  v.GetBool() );
			break;
		case Util::Variant::Float4:
			mXmlWriter->SetFloat4( s_ObjectVariantValue,  v.GetFloat4() );
			break;
		case Util::Variant::String:
			mXmlWriter->SetString( s_ObjectVariantValue,  v.GetString() );
			break;
		case Util::Variant::Matrix44:
			mXmlWriter->SetMatrix44( s_ObjectVariantValue,  v.GetMatrix44() );
			break; 
		default:
			n_error( "SerializeXmlWriter::SerializeVariant: not support now for %s", Util::Variant::TypeToString(t).AsCharPtr() );
			break;
		}

		EndAttribute();
	}

	void SerializeXmlWriter::SetString( const Util::String& attributeName , const Util::String& attributeValue )
	{
		mXmlWriter->SetString( attributeName , attributeValue ) ;
	}

	//------------------------------------------------------------------------
	void SerializeXmlReader::FindNextChild( const Util::String& childName  )
	{
		n_assert( mChildNodeIndex == mCurrentNodeIndex + 1 );
		n_assert( mChildNodeIndex < mXmlNodeList.Size() );

		if ( mXmlNodeList[mChildNodeIndex] )
		{

			mXmlReader->SetCurrentNode( mXmlNodeList[mChildNodeIndex] );
			bool bOK = mXmlReader->SetToNextChild( childName );
			if (!bOK)//	root AppXMLFileTag
			{
				SYS_EXCEPT(Exceptions::SerializeException, 
					STRING_FORMAT("object serialize error in %s.", mStream->GetURI().AsString().AsCharPtr()),
					GET_FUNCTION_NAME()
					);
			}
		}
		else
		{
			bool bOK = mXmlReader->SetToFirstChild( childName );
			if (!bOK)//	root AppXMLFileTag
			{
				SYS_EXCEPT(Exceptions::SerializeException, 
					STRING_FORMAT("object serialize error in %s.", mStream->GetURI().AsString().AsCharPtr()),
					GET_FUNCTION_NAME()
					);
			}
		}
	}
}


