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
#ifndef __serialize_H__
#define __serialize_H__


#include "core/types.h"
#include "core/refcounted.h"
#include "io/stream.h"
#include "messaging/port.h"
#include "util/variant.h"
#include "math/float2.h"
#include "math/float3.h"
#include "math/quaternion.h"
#include "math/color.h"
#include "math/bbox.h"
#include "util/assetpath.h"


namespace Serialization
{
	class SerializeReader;
	class SerializeWriter;
	class SerializationServer;
	typedef uint SVersion; 


	class SerializationArgs
	{
	public:
		SerializationArgs();
		virtual ~SerializationArgs();
		template<typename T> 
		const T* cast_fast() const;
		static const SerializationArgs* Empty;
	private:
	};

	template<typename T>
	inline const T* SerializationArgs::cast_fast() const
	{
		return static_cast<const T*>(this);
	}

	// abstract interface, define the protocol of the serialization object
	struct ISerialize
	{
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual SVersion GetVersion() const = 0;

		// @ISerialization::Load 
		virtual void Load( SVersion ver, SerializeReader* pReader, const SerializationArgs* args ) = 0;

		// @ISerialization::Save
		virtual void Save( SerializeWriter* pWriter ) const = 0;
	};

	class SerializeBase: public Core::RefCounted
	{
		__DeclareClass(SerializeBase);
	public:
		SerializeBase();
		virtual ~SerializeBase();
		bool IsOpen() const;
	protected:
		void SetOpen(bool bOpen);
	protected:
		bool mIsOpen;
		friend class SerializationServer;
	};

	class SerializeReader: public SerializeBase
	{
		__DeclareClass(SerializeReader);
	public:
		SerializeReader(){ };
		virtual ~SerializeReader(){ };

		/// set stream to read from
		void SetStream(const GPtr<IO::Stream>& s);

		/// get currently set stream 
		const GPtr<IO::Stream>& GetStream() const;

		virtual void SerializeVersion( SVersion& ver);

		virtual void SerializeInt(const char* attrm, int& i );

		virtual void SerializeUInt(const char* attr, uint& i );

		virtual void SerializeBool(const char* attr, bool& b);

		virtual void SerializeFloat(const char* attr, float& f);

		virtual void SerializeDouble(const char* attr, double& f);

		virtual void SerializeString(const char* attr, /*const*/ Util::String& str);

		virtual void SerializeFloat2(const char* attr, Math::float2& f2 );

		virtual void SerializeFloat3(const char* attr, Math::float3& f3 );

		virtual void SerializeFloat4(const char* attr, Math::float4& f4 );

		virtual void SerializeQuaternion(const char* attr, Math::quaternion& q );

		virtual void SerializeMatrix44(const char* attr, Math::matrix44& m );

		virtual void SerializeColor32(const char* attr, Math::Color32& c32 );

		virtual void SerializeColorF(const char* attr, Math::ColorF& cf );

		virtual void SerializeAssetPath( const char* attr, Util::AssetPath& ap);

		virtual void SerializeBBox(const char* attr, Math::bbox& bb );

		virtual void SerializeVariant(const char* attr, Util::Variant& v );

		template<typename T>
		GPtr<T> SerializeObject(const SerializationArgs* args = SerializationArgs::Empty);

		template<typename T>
		GPtr<T> SerializeObjectWidthOutEnd(const SerializationArgs* args = SerializationArgs::Empty);

		template<typename superT, typename T>
		void SerializeSuper( T* p, const SerializationArgs* args );

		///  BeginFileRead and EndFileRead will be called only by read control class. 
		///  So we can optimal the file storage, like use string table etc. 
		virtual bool BeginFileSerialize();
		virtual bool EndFileSerialize();


		/// can save more information for test or type_safe 
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );
		virtual void EndSerializeSuper();


		virtual void BeginSerializeObject( Util::FourCC& fourcc );
		virtual void EndSerializeObject();

		template<typename T>
		GPtr<T> BeginSerializeObjectT();

	protected:
		GPtr<IO::Stream> mStream;
	};

	class SerializeWriter: public SerializeBase
	{
		__DeclareClass(SerializeWriter);
	public:
		SerializeWriter(){ };
		virtual ~SerializeWriter(){ };

	public:
		/// set stream to read from
		void SetStream(const GPtr<IO::Stream>& s);

		/// get currently set stream 
		const GPtr<IO::Stream>& GetStream() const;

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

		template<typename T>
		void SerializeObject( const GPtr<T>& pObj );

		template<typename superT, typename T>
		void SerializeSuper( T* p );

		///  BeginFileRead and EndFileRead will be called only by read control class. 
		///  So we can optimal the file storage, like use string table etc. 
		virtual void BeginFileSerialize();

		virtual void EndFileSerialize();

		/// can save more information for test or type_safe 
		virtual void BeginSerializeSuper( const Core::Rtti* pRtti );
		virtual void EndSerializeSuper();

		virtual void BeginSerializeObject( const Util::FourCC& fourcc );
		virtual void EndSerializeObject();

	protected:
		GPtr<IO::Stream> mStream;

	};
	//------------------------------------------------------------------------
	inline
	bool
	SerializeBase::IsOpen() const
	{
		return mIsOpen;
	}
	//------------------------------------------------------------------------
	inline
	void 
	SerializeBase::SetOpen(bool bOpen)
	{
		mIsOpen = bOpen;
	}
	//------------------------------------------------------------------------
	inline
	void
	SerializeReader::SetStream(const GPtr<IO::Stream>& s)
	{
		mStream = s;
	}
	//------------------------------------------------------------------------
	inline 
		const GPtr<IO::Stream>&
		SerializeReader::GetStream(void) const
	{
		return mStream;
	}
	//------------------------------------------------------------------------
	template<typename superT, typename T>
	void SerializeReader::SerializeSuper( T* p, const Serialization::SerializationArgs* args )
	{
		BeginSerializeSuper( p->superT::GetRtti() );

		SVersion ver = 0;
		SerializeVersion(ver);

		p->superT::Load(ver, this, args);

		EndSerializeSuper();
	}
	//------------------------------------------------------------------------
	template<typename T>
	GPtr<T> 
	SerializeReader::SerializeObject(const SerializationArgs* args)
	{
		Util::FourCC fourCC;
		BeginSerializeObject(fourCC);
		SVersion ver = 0;
		SerializeVersion(ver);

		if ( ver == -1)
		{
			n_warning("unknown object(FourCC, %s) version %d.", fourCC.AsString().AsCharPtr(), ver);
			EndSerializeObject();
			return NULL;
		}

		Core::Factory* pFactory = Core::Factory::Instance();
		n_assert( pFactory );
		if( pFactory->ClassExists( fourCC ) )
		{
			GPtr<RefCounted> pRef = pFactory->Create( fourCC );
			n_assert( pRef );

			bool isCanDowncast = pRef->GetRtti()->IsDerivedFrom(T::RTTI);
			if (isCanDowncast)
			{
				GPtr<T> pSerialize = pRef.downcast<T>();

				pSerialize->Load( ver, this, args );

				EndSerializeObject();
				return pSerialize;
			}
			else
			{
				n_warning("%s is not the sub class of %s.", pRef->GetClassName().AsCharPtr(), T::RTTI.GetName().AsCharPtr());
				EndSerializeObject();
				return NULL;
			}

			GPtr<T> pSerialize = pRef.downcast<T>();

			pSerialize->Load( ver, this, args );

			EndSerializeObject();
			return pSerialize;
		}

		//n_warning(" can not read object, error FourCC type: %s." , fourCC.AsString().AsCharPtr() );
		EndSerializeObject();
		return NULL;
	}
	//------------------------------------------------------------------------
	template<typename T>
	GPtr<T> 
		SerializeReader::SerializeObjectWidthOutEnd(const SerializationArgs* args)
	{
		Util::FourCC fourCC;
		BeginSerializeObject(fourCC);
		SVersion ver = 0;
		SerializeVersion(ver);

		Core::Factory* pFactory = Core::Factory::Instance();
		n_assert( pFactory );
		if( pFactory->ClassExists( fourCC ) )
		{
			GPtr<RefCounted> pRef = pFactory->Create( fourCC );
			n_assert( pRef );
			GPtr<T> pSerialize = pRef.downcast<T>();
			pSerialize->Load( ver, this, args );
			return pSerialize;
		}
		else
		{
			//n_warning(" can not read object, error FourCC type: %s." , fourCC.AsString().AsCharPtr() );
			return NULL;
		}

	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	template<typename T>
	GPtr<T> 
		SerializeReader::BeginSerializeObjectT()
	{
		Util::FourCC fourCC;
		BeginSerializeObject(fourCC);

		Core::Factory* pFactory = Core::Factory::Instance();
		n_assert( pFactory );
		if( pFactory->ClassExists( fourCC ) )
		{
			GPtr<RefCounted> pRef = pFactory->Create( fourCC );
			n_assert( pRef );
			GPtr<T> pSerialize = pRef.downcast<T>();
			return pSerialize;
		}
		else
		{
			n_warning(" can not read object, error FourCC type: %s." , fourCC.AsString().AsCharPtr() );
			return NULL;
		}
		return NULL;
	}
	//------------------------------------------------------------------------
	inline
	void
	SerializeWriter::SetStream(const GPtr<IO::Stream>& s)
	{
		mStream = s;
	}
	//------------------------------------------------------------------------
	inline 
	const GPtr<IO::Stream>&
	SerializeWriter::GetStream(void) const
	{
		return mStream;
	}
	//------------------------------------------------------------------------
	template<typename superT, typename T>
	void SerializeWriter::SerializeSuper( T* pT )
	{
		BeginSerializeSuper( pT->superT::GetRtti() );

		SVersion ver = pT->superT::GetVersion();
		SerializeVersion( ver );
		pT->superT::Save(this);

		EndSerializeSuper();
	}
	//------------------------------------------------------------------------
	template<typename T>
	void SerializeWriter::SerializeObject( const GPtr<T>& pObj )
	{
		n_assert(pObj);
		n_assert(Core::Factory::Instance()->ClassExists( pObj->GetRtti()->GetFourCC() ) );

		BeginSerializeObject( pObj->GetRtti()->GetFourCC() );

		SVersion ver = pObj->GetVersion();
		SerializeVersion( ver );
		pObj->Save( this );

		EndSerializeObject();
	}

}

#endif // __serialize_H__

