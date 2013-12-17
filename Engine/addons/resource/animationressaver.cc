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
#include "resource/animationressaver.h"
#include "resource/reslable.h"

using namespace Animations;

namespace Resources
{
	__ImplementClass( Resources::AnimationResSaver, 'ARSV', Resources::ResourceSaver);
	//------------------------------------------------------------------------
	AnimationResSaver::AnimationResSaver()
	{

	}
	//------------------------------------------------------------------------
	AnimationResSaver::~AnimationResSaver()
	{

	}
	//------------------------------------------------------------------------
	bool 
		AnimationResSaver::SaveResource(Resource* res )
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

		// Only loaded res can be saved
		if ( pAnimRes->GetState() != Resource::Loaded )
		{
			return false;
		}

		GPtr<IO::BinaryWriter> pWriter = IO::BinaryWriter::Create();
		n_assert(pWriter.isvalid());

		pWriter->SetStream( mStream );

		//  Every file should be LittleEndian
		pWriter->SetStreamByteOrder(System::ByteOrder::LittleEndian);

		if ( !pWriter->Open() )
		{
			return false;
		}

		// save data
		if ( !SaveAnimation(pWriter, pAnimRes) )
		{
			pWriter->Close();
			return false;
		}

		pWriter->Close();
		return true;
	}
	//------------------------------------------------------------------------
	bool 
		AnimationResSaver::SaveAnimation(GPtr<IO::BinaryWriter>& pWriter, const GPtr<AnimationRes>& pAnimRes )
	{
		pWriter->WriteInt( ResLable::L_Animation );
		pWriter->WriteInt(1);	//	version

		SizeT count = pAnimRes->GetClipCount();
		pWriter->WriteInt(count);
		for ( IndexT index = 0; index < count; ++index )
		{
			if( !WriteAnimationClip( pWriter, pAnimRes->GetClip(index) ) )
			{
				return false;
			}
		}

		pWriter->WriteInt( ResLable::L_End ); 
		return true;
	}
	//------------------------------------------------------------------------
	bool 
		AnimationResSaver::WriteAnimationClip(GPtr<IO::BinaryWriter>& pWriter, const GPtr<Animations::AnimationClip>& clip)
	{
		if ( !clip.isvalid() )
			return false;

		pWriter->WriteInt( ResLable::L_AnimClip );

		if( clip->GetName().AsString().IsEmpty() )
			return false;
		pWriter->WriteString( clip->GetName().AsString() );

		// animationNode's type, only has 'ANDS' now
		pWriter->WriteInt( ResLable::S_StdAnimNode );

		int nodeCount = clip->GetNodeCount();
		n_assert( nodeCount < 0xFFFF );
		pWriter->WriteUShort( (ushort)nodeCount );
		for ( IndexT index = 0; index < nodeCount; ++index )
		{
			if( !WriteAnimationNode( pWriter, clip->GetNode(index) ) )
			{
				return false;
			}
		}

		return true;

	}
	//------------------------------------------------------------------------
	/// Fast read an array. ElemSize is array's element byte size. Check is or not equal to T::value_type to avoid error
	template<int ElemSize, typename T>
	bool _FastWriteArray(const T& t,GPtr<IO::BinaryWriter>& pWriter)
	{
		n_static_assert( sizeof( typename T::value_type ) == ElemSize );

		int count = t.Size();
		pWriter->WriteInt(count);

		if( count == 0 )
		{
			return true;
		}

#if __WIN32__ || __ANDROID__ || __OSX__
		// need not swap. so can copy memory 

		pWriter->WriteRawData( &t[0], count*sizeof(typename T::value_type) );

		return true;
#else

#error		// don't kown if can directly copy now, should impl by Platform 

#endif

	}

	//------------------------------------------------------------------------
	bool 
		AnimationResSaver::WriteAnimationNode(GPtr<IO::BinaryWriter>& pWriter, const GPtr<Animations::AnimationNode>& node )
	{
		if ( !node.isvalid() )
		{
			return false;
		}

		if( !node->GetID().IsValid() )
			return false;
		pWriter->WriteString( node->GetID().AsString() );

		TransCurve& transCurve = node->GetTransCurve();
		ScaleCurve& scaleCurve = node->GetScaleCurve();
		RotateCurve& rotateCurve = node->GetRotateCurve();

		SizeT numCurve = ( transCurve.GetKeyFrameCount() == 0 ? 0 : 1 );
		numCurve += ( scaleCurve.GetKeyFrameCount() == 0 ? 0 : 1 );
		numCurve += ( rotateCurve.GetKeyFrameCount() == 0 ? 0 : 1 );

		pWriter->WriteUChar( (uchar)numCurve );
		if ( numCurve != 0 )
		{
			if ( transCurve.GetKeyFrameCount() != 0 )
			{
				pWriter->WriteInt( ResLable::S_StdCurveTrans );
				const TransCurve::Container& container = transCurve.GetContainer() ; 
				_FastWriteArray<16>(container,pWriter );
			}

			if ( scaleCurve.GetKeyFrameCount() != 0 )
			{
				pWriter->WriteInt( ResLable::S_StdCurveScale );
				const ScaleCurve::Container& container = scaleCurve.GetContainer() ; 
				_FastWriteArray<16>(container,pWriter );
			}

			if ( rotateCurve.GetKeyFrameCount() != 0 )
			{
				//XNA's Quaternion must be 16Byte alignment, there can not direct copy memory
				pWriter->WriteInt( ResLable::S_StdCurveRota );
				SizeT numKey = rotateCurve.GetKeyFrameCount();
				pWriter->WriteInt(numKey);
				for ( IndexT iK = 0; iK < numKey; ++iK )
				{
					const RotateCurve::KeyFrame& keyFrame = rotateCurve.GetKeyFrame(iK);
					const Math::quaternion& q = keyFrame.GetValue();
					pWriter->WriteFloat( q.x() );
					pWriter->WriteFloat( q.y() );
					pWriter->WriteFloat( q.z() );
					pWriter->WriteFloat( q.w() );

					pWriter->WriteFloat( keyFrame.GetTime() );
				}
			}

		}

		return true;
	}


}
