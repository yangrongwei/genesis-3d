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
#include "resource/resource_stdneb.h"
#include "resource/animationresloader.h"
#include "resource/reslable.h"
//#include "foundation/math/curve.h"
#include "DataChunkPacket.h"

using namespace Animations;

namespace Resources
{
	__ImplementClass(Resources::AnimationResLoader, 'ARLD', Resources::ResourceLoader );

	//------------------------------------------------------------------------
	AnimationResLoader::AnimationResLoader()
	{

	}
	//------------------------------------------------------------------------
	AnimationResLoader::~AnimationResLoader()
	{

	}
	//------------------------------------------------------------------------
	bool 
		AnimationResLoader::LoadResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &AnimationRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<AnimationRes> pAnimRes = pRes.downcast<AnimationRes>();
		n_assert(pAnimRes.isvalid());

		if ( !mStream.isvalid() )
		{
			return false;
		}

		GPtr<IO::BinaryReader> pReader = IO::BinaryReader::Create();
		n_assert(pReader.isvalid());

		pReader->SetStream( mStream );

		//Every file shuold be LittleEndian
#ifdef __OSX__
		pReader->SetStreamByteOrder(System::ByteOrder::BigEndian);
#else
		pReader->SetStreamByteOrder(System::ByteOrder::LittleEndian);
#endif
		if ( !pReader->Open() )
		{
			return false;
		}

		// skeleton don't support stream load. To current reload, need unload first
		pAnimRes->UnLoadImpl();

		// load data
		if ( !LoadAnimation(pReader, pAnimRes) )
		{
			pReader->Close();
			return false;
		}

		pReader->Close();

		return true;
	}
	//------------------------------------------------------------------------
	bool AnimationResLoader::LoadAnimation(GPtr<IO::BinaryReader>& pReader, GPtr<AnimationRes>& pAnimRes )
	{
		n_assert( pReader.isvalid() && pAnimRes.isvalid() );

		int magicNum = pReader->ReadInt();

		if ( magicNum != ResLable::L_Animation )
		{
			return false;
		}

		int version = pReader->ReadInt();
		if ( version == 1)
		{
			// read AnimClip count
			int count = pReader->ReadInt();

			// read Anim
			for ( int index = 0; index < count; ++index )
			{
				if( !ReadAnimationClip( pReader, pAnimRes ) )
				{
					return false;
				}
			}

			// read end sign
			int end = pReader->ReadInt();
			if ( end == ResLable::L_End )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else		
		{
			// not support other version now
			return false;
		}

		return false;
	}

	//------------------------------------------------------------------------
	bool
		AnimationResLoader::ReadAnimationClip(GPtr<IO::BinaryReader>& pReader, GPtr<AnimationRes>& pAnimRes)
	{
		n_assert(pAnimRes.isvalid());

		int StorageType = pReader->ReadInt();
		if ( StorageType == ResLable::L_AnimClip )
		{
			GPtr<AnimationClip> pClip = AnimationClip::Create();
			Util::String name = pReader->ReadString();
			Util::String animID = pAnimRes->GetResourceId().AsString();

#if NEBULA3_BOUNDSCHECKS
			n_assert(!name.IsEmpty());
			if ( name.IsEmpty() )
			{
				return false;
			}
			/*if (animID.FindStringIndex(name) == InvalidIndex)
			{
			n_warning("AnimationResLoader: Open animation res error!");
			return false;
			}*/
#endif
			/*const Util::String assetPreFix = "asset:";
			if (animID.FindStringIndex(assetPreFix) == 0)
			{
			animID = animID.ExtractToEnd(assetPreFix.Length());
			}*/
			pClip->SetName(animID);

			float sampeRate = pReader->ReadFloat();
			pClip->SetSampleRate(sampeRate);

			int nodestorage = pReader->ReadInt();
			if ( nodestorage == ResLable::S_StdAnimNode )
			{		
				// standard save form
				if ( ReadAnimationNode(pReader,  pClip ) )
				{
					return pAnimRes->AddClip(pClip);
				}
			}
		}
		return false;
	}
	//------------------------------------------------------------------------
	bool 
		AnimationResLoader::ReadAnimationNode(GPtr<IO::BinaryReader>& pReader, GPtr<Animations::AnimationClip>& clip )
	{
		ushort nodeCount = pReader->ReadUShort();
		for ( IndexT indexNode = 0; indexNode < nodeCount; ++indexNode )
		{
			GPtr<AnimationNode> pNode = AnimationNode::Create();
			Util::String nodeName = pReader->ReadString();

#if NEBULA3_BOUNDSCHECKS
			n_assert(!nodeName.IsEmpty());
			if( nodeName.IsEmpty() )
			{
				return false;
			}
#endif

			pNode->SetID( nodeName );

			ushort parentIndex = pReader->ReadUShort();
			pNode->SetParentIndex(parentIndex);

			Math::vector defaultTrans = pReader->ReadVector();
			pNode->SetDefaultNodeTrans(Math::float3(defaultTrans.x(), defaultTrans.y(), defaultTrans.z()));

			Math::vector defaultScale = pReader->ReadVector();
			pNode->SetDefaultNodeScale(Math::float3(defaultScale.x(), defaultScale.y(), defaultScale.z()));

			Math::float4 defaultRot = pReader->ReadFloat4();
			pNode->SetDefaultNodeRot(Math::quaternion(defaultRot.x(), defaultRot.y(), defaultRot.z(), defaultRot.w()));

			uchar curveCount = pReader->ReadUChar();
			for ( IndexT nodeIndex = 0; nodeIndex < curveCount; ++nodeIndex )
			{
				if ( !ReadAnimationCurve(pReader, pNode ) )
				{
					return false;
				}
			}

			if( !clip->AddNode(pNode) )
			{
				return false;
			}
		}
		return true;
	}
	//------------------------------------------------------------------------
	/// Fast read an array. ElemSize is array's element byte size. Check is or not equal to T::value_type to avoid error
	template<int ElemSize, typename T>
	bool _FastReadArray(T& t, GPtr<IO::BinaryReader>& pReader)
	{
		n_static_assert( sizeof( typename T::value_type ) == ElemSize );

		int count = pReader->ReadInt();
		if ( count < 0 )
		{
			return false;
		}

		if( count == 0 )
		{
			t.Clear();
			return true;
		}

#if __WIN32__ || __ANDROID__ || __OSX__
		// need not swap. so can copy memory 

		t.Resize(count, typename T::value_type() );
		pReader->ReadRawData( &t[0], count*sizeof(typename T::value_type) );

		return true;
#else

#error		// don't kown if can directly copy now, should impl by Platform 

#endif
	}
	//------------------------------------------------------------------------
	bool 
		AnimationResLoader::ReadAnimationCurve(GPtr<IO::BinaryReader>& pReader, GPtr<Animations::AnimationNode>& node )
	{
		int type = pReader->ReadInt();
		switch ( type )
		{
		case ResLable::S_StdCurveTrans:
			{			
				TransCurve& curve = node->GetTransCurve();

				// direct write memory, avoid memory copy
				TransCurve::Container& container = const_cast<TransCurve::Container&>( curve.GetContainer() ); 
#if NEBULA3_BOUNDSCHECKS
				//	read and check is or not sorted
				if ( _FastReadArray<16>(container, pReader ) )
				{
					return curve.Validate();
				}
				else
				{
					return false;
				}
#else	
				return _FastReadArray<16>(container, pReader );
#endif

			}
		case ResLable::S_PackedCurveTrans:
			{
				TransCurve& curve = node->GetTransCurve();
				TransCurve::Container& container = const_cast<TransCurve::Container&>( curve.GetContainer() ); 
				return ReadPackedFloat<TransCurve::Container, Math::Float3fKeyFrame>(pReader, container);
			}
		case ResLable::S_StdCurveScale:
			{
				ScaleCurve& curve = node->GetScaleCurve();

				// direct write memory, avoid memory copy
				ScaleCurve::Container& container = const_cast<ScaleCurve::Container&>( curve.GetContainer() ); 

#if NEBULA3_BOUNDSCHECKS
				//	read and check is or not sorted
				if ( _FastReadArray<16>(container, pReader ) )
				{
					return curve.Validate();
				}
				else
				{
					return false;
				}
#else	
				return _FastReadArray<16>(container, pReader );
#endif
			}
		case ResLable::S_PackedCurveScale:
			{
				ScaleCurve& curve = node->GetScaleCurve();
				ScaleCurve::Container& container = const_cast<ScaleCurve::Container&>( curve.GetContainer() ); 
				return ReadPackedFloat<ScaleCurve::Container, Math::Float3fKeyFrame>(pReader, container);
			}
		case ResLable::S_StdCurveRota:
			{
				RotateCurve& curve = node->GetRotateCurve();
				RotateCurve::Container& container = const_cast<RotateCurve::Container&>( curve.GetContainer() ); 

				// XNA's Quaternion must be 16Byte alignment, there can not direct copy memory
				int count = pReader->ReadInt();
				if ( count < 0 )
				{
					return false;
				}

				if( count == 0 )
				{
					container.Clear();
					return true;
				}

				container.Reserve(count);
				for ( IndexT i = 0; i < count; ++i )
				{
					n_static_assert( sizeof(Math::float4) == 16 );

					Math::quaternion q( pReader->ReadFloat4() );
					float time = pReader->ReadFloat();
					RotateCurve::KeyFrame key(time, q );
					container.Append( key );
				}

#if NEBULA3_BOUNDSCHECKS
				//	check is or not sorted
				return curve.Validate();
#else	
				return true;
#endif

			}
		case ResLable::S_PackedCurveRota:
			{
				RotateCurve::Container tmpRotateCurve;
				if (!ReadPackedFloat<RotateCurve::Container, Math::QuaternionKeyFrame>(pReader, tmpRotateCurve) )
				{
					return false;
				}

				RotateCurve& curve = node->GetRotateCurve();
				RotateCurve::Container& container = const_cast<RotateCurve::Container&>( curve.GetContainer() ); 
				container.Resize(tmpRotateCurve.Size(), Math::TemplateKeyframe<Math::quaternion>());
				// import.dll write file is use x,y,z,w's sequence, but Math::quaternion's sequence is w,x,y,z, must transform
				Math::quaternion tmpQ;
				for (int i = 0; i < tmpRotateCurve.Size(); ++i)
				{
					Math::TemplateKeyframe<Math::quaternion> tkf = tmpRotateCurve[i];
					tmpQ.x() = tkf.GetValue().w();
					tmpQ.y() = tkf.GetValue().x();
					tmpQ.z() = tkf.GetValue().y();
					tmpQ.w() = tkf.GetValue().z();
					container[i].SetValue(tmpQ);
					container[i].SetTime(tkf.GetTime());
				}
				return true;
			}
		default:
			return false;
		}
	}

}
