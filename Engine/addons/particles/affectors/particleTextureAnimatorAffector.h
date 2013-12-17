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
#ifndef __PARTICLE_TEXTUREANIMATOR_AFFECTOR_H__
#define __PARTICLE_TEXTUREANIMATOR_AFFECTOR_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particleaffector.h"

namespace Particles
{
	class TextureAnimatorAffector: public ParticleAffector
	{
		__DeclareSubClass( TextureAnimatorAffector, ParticleAffector);


	public:
		enum TextureAnimationType
		{
			TAT_WHOLE_SHEET,
			TAT_SINGLE_ROW,
		};		

		static const Math::scalar DEFAULT_TA_TIME_STEP;
		static const ushort DEFAULT_TA_TEXCOORDS_START;
		static const ushort DEFAULT_TA_TEXCOORDS_END;
		static const TextureAnimationType DEFAULT_TA_ANIMATION_TYPE;
		static const bool DEFAULT_TA_START_RANDOM;

	public:

		TextureAnimatorAffector();
		virtual ~TextureAnimatorAffector(){};

		virtual void _onActivate(void);

		TextureAnimationType GetTextureAnimationType(void) const;

		void SetTextureAnimationType(TextureAnimationType textureAnimationType);

		ushort GetTileX(void) const;
		void SetTileX(ushort);

		ushort GetTileY(void) const;
		void SetTileY(ushort);

		bool IsSingleRowRandom(void) const;

		void SetSingleRowRandom(bool startRandom);

		void _initParticleForEmission(Particle* particle);

		virtual void _affect(Particle* particle);

		void SetRowIndex(int);
		int GetRowIndex(void) const;

		void SetCycles(int);
		int GetCycles(void) const;

		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct)
		{
			switch(pct)
			{
			case 	Affetor_TexAnimation:
				return &mMinMaxTexAnimation;
			default:
				return NULL;					
			}
		}

	protected:
		Math::scalar mAnimationTimeStep;
		Math::scalar mAnimationTimeStepCount;

		TextureAnimationType mTextureAnimationType;
		bool mIsSingleRowRandom;
		int			mRowIndex;
		ushort	mTileX;
		ushort	mTileY;
		int			mCycles;

		Math::MinMaxCurve			mMinMaxTexAnimation;


	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleAffectorPtr& affector );
	};
	//--------------------------------------------------------------------------------
	inline ushort TextureAnimatorAffector::GetTileX(void) const
	{
		return mTileX;
	}
	inline ushort TextureAnimatorAffector::GetTileY(void) const
	{
		return mTileY;
	}

	//-------------------------------------------------------------------------
	inline TextureAnimatorAffector::TextureAnimationType TextureAnimatorAffector::GetTextureAnimationType(void) const
	{
		return mTextureAnimationType;
	}

	//-------------------------------------------------------------------------
	inline bool TextureAnimatorAffector::IsSingleRowRandom(void) const
	{
		return mIsSingleRowRandom;
	}

	//-------------------------------------------------------------------------
	inline void TextureAnimatorAffector::SetSingleRowRandom(bool bRandom)
	{
		mIsSingleRowRandom = bRandom;
	}
	//--------------------------------------------------------------------------------
	inline void TextureAnimatorAffector::SetRowIndex(int ncount)
	{
		mRowIndex = ncount;
		if(mRowIndex < 0)
			mRowIndex = 0;
	}
	inline int TextureAnimatorAffector::GetRowIndex(void) const
	{
		return mRowIndex;
	}
	//--------------------------------------------------------------------------------
	inline void TextureAnimatorAffector::SetCycles(int ncount)
	{
		mCycles = ncount;
	}
	inline int TextureAnimatorAffector::GetCycles(void) const
	{
		return mCycles;
	}
}
#endif