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
#include "particles/affectors/particleTextureAnimatorAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_AnimationTimeStep = "AnimationTimeStep";
	const static char* s_AnimationTimeStepSet = "AnimationTimeStepSet";
	const static char* s_TextureAnimationType = "TextureAnimationType";
	const static char* s_TextureCoordsStart = "TextureCoordsStart";
	const static char* s_TextureCoordsEnd = "TextureCoordsEnd";
	const static char* s_StartRandom = "StartRandom";
	const static char* s_DirectionUp = "DirectionUp";

	const static char* s_IsSingleRowRandom = "IsSingleRowRandom";
	const static char* s_RowIndex = "RowIndex";
	const static char* s_Tiles = "Tiles";
	const static char* s_Cycles = "Cycles";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;


	class TextureAnimatorAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( TextureAnimatorAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(obj, pReader);
				return;
			}
			else if(3 == ver)
			{
				Load_3(obj,pReader);
				return;
			}
			else if( 4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			else if(5 == ver)
			{
				Load_5(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_5(TextureAnimatorAffector* obj, SerializeReader* pReader)
		{
			int mTextureAnimationType;
			pReader->SerializeInt(s_TextureAnimationType, mTextureAnimationType );
			obj->SetTextureAnimationType((TextureAnimatorAffector::TextureAnimationType)mTextureAnimationType );

			bool mIsSingleRowRandom;
			pReader->SerializeBool(s_IsSingleRowRandom, mIsSingleRowRandom );
			obj->SetSingleRowRandom(mIsSingleRowRandom);

			int nRowIndex;
			pReader->SerializeInt(s_RowIndex, nRowIndex );
			obj->SetRowIndex(nRowIndex);

			Math::float2 fTiles;
			pReader->SerializeFloat2(s_Tiles, fTiles );
			obj->SetTileX((ushort)fTiles.x());
			obj->SetTileY((ushort)fTiles.y());

			int nSycles;
			pReader->SerializeInt(s_Cycles, nSycles );
			obj->SetCycles(nSycles);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affetor_TexAnimation),"TexOverTime",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_4(TextureAnimatorAffector* obj, SerializeReader* pReader)
		{
			Load_2(obj,pReader);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affetor_TexAnimation),"TexOverTime",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_3(TextureAnimatorAffector* obj, SerializeReader* pReader)
		{
			Load_2(obj,pReader);
			Util::Array<Math::float2> keyframelist1;
			Util::Array<Math::float2> keyframelist2;
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affetor_TexAnimation);
			_serializeLoadCurveOld(pReader, keyframelist1, "TexOverTimeMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "TexOverTimeMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	
		}
		//------------------------------------------------------------------------
		void Load_1(TextureAnimatorAffector* obj, SerializeReader* pReader)
		{
			Math::scalar mAnimationTimeStep;
			bool mAnimationTimeStepSet;
			pReader->SerializeFloat(s_AnimationTimeStep, mAnimationTimeStep );
			pReader->SerializeBool(s_AnimationTimeStepSet, mAnimationTimeStepSet );

			int mTextureAnimationType;
			pReader->SerializeInt(s_TextureAnimationType, mTextureAnimationType );
			obj->SetTextureAnimationType((TextureAnimatorAffector::TextureAnimationType)mTextureAnimationType );

			int mTextureCoordsStart;
			pReader->SerializeInt(s_TextureCoordsStart, mTextureCoordsStart );

			int mTextureCoordsEnd;
			pReader->SerializeInt(s_TextureCoordsEnd, mTextureCoordsEnd );

			bool mStartRandom;
			pReader->SerializeBool(s_StartRandom, mStartRandom );
			obj->SetSingleRowRandom(mStartRandom);

			bool mDirectionUp;
			pReader->SerializeBool(s_DirectionUp, mDirectionUp );

		}
		//------------------------------------------------------------------------
		void Load_2(TextureAnimatorAffector* obj, SerializeReader* pReader)
		{

			int mTextureAnimationType;
			pReader->SerializeInt(s_TextureAnimationType, mTextureAnimationType );
			obj->SetTextureAnimationType((TextureAnimatorAffector::TextureAnimationType)mTextureAnimationType );

			bool mIsSingleRowRandom;
			pReader->SerializeBool(s_IsSingleRowRandom, mIsSingleRowRandom );
			obj->SetSingleRowRandom(mIsSingleRowRandom);

			int nRowIndex;
			pReader->SerializeInt(s_RowIndex, nRowIndex );
			obj->SetRowIndex(nRowIndex);

			Math::float2 fTiles;
			pReader->SerializeFloat2(s_Tiles, fTiles );
			obj->SetTileX((ushort)fTiles.x());
			obj->SetTileY((ushort)fTiles.y());

			int mTextureCoordsStart;
			pReader->SerializeInt(s_TextureCoordsStart, mTextureCoordsStart );

			int mTextureCoordsEnd;
			pReader->SerializeInt(s_TextureCoordsEnd, mTextureCoordsEnd );

			int nSycles;
			pReader->SerializeInt(s_Cycles, nSycles );
			obj->SetCycles(nSycles);

		}
		//------------------------------------------------------------------------
		void Save( const TextureAnimatorAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_TextureAnimationType, (int)obj->GetTextureAnimationType() );

			pWriter->SerializeBool(s_IsSingleRowRandom, obj->IsSingleRowRandom() );
			pWriter->SerializeInt(s_RowIndex, obj->GetRowIndex() );
			pWriter->SerializeFloat2(s_Tiles, Math::float2((float)obj->GetTileX(), (float)obj->GetTileY()) );

			pWriter->SerializeInt(s_Cycles, obj->GetCycles() );

			_serializeSaveMinMaxCurve(pWriter,*((TextureAnimatorAffector* )obj)->getMinMaxCurve(Affetor_TexAnimation),"TexOverTime",s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion TextureAnimatorAffector::GetVersion() const
	{
		return 5;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void TextureAnimatorAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		TextureAnimatorAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void TextureAnimatorAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		TextureAnimatorAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void TextureAnimatorAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<TextureAnimatorAffector> source = target.downcast<TextureAnimatorAffector>();

		SetTextureAnimationType( source->GetTextureAnimationType());
		SetSingleRowRandom(source->IsSingleRowRandom());
		SetRowIndex(source->GetRowIndex());
		SetTileX(source->GetTileX());
		SetTileY(source->GetTileY());
		SetCycles(source->GetCycles());

		_serializeCopyMinMaxCurve(source->mMinMaxTexAnimation,this->mMinMaxTexAnimation);
	}

}