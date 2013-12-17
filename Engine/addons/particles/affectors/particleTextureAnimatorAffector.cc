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
#include "particleTextureAnimatorAffector.h"
#include "particles/particlesystem.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::TextureAnimatorAffector, CPFCC::AFFECTOR_TEXTUREANIMATOR, Particles::ParticleAffector);

	const Math::scalar TextureAnimatorAffector::DEFAULT_TA_TIME_STEP = 0.0f;
	const ushort TextureAnimatorAffector::DEFAULT_TA_TEXCOORDS_START = 0;
	const ushort TextureAnimatorAffector::DEFAULT_TA_TEXCOORDS_END = 0;
	const TextureAnimatorAffector::TextureAnimationType TextureAnimatorAffector::DEFAULT_TA_ANIMATION_TYPE = TextureAnimatorAffector::TAT_WHOLE_SHEET;
	const bool TextureAnimatorAffector::DEFAULT_TA_START_RANDOM = true;
	//-----------------------------------------------------------------------
	TextureAnimatorAffector::TextureAnimatorAffector(void) : ParticleAffector(),
		mAnimationTimeStepCount(DEFAULT_TA_TIME_STEP),
		mAnimationTimeStep(DEFAULT_TA_TIME_STEP),
		mTextureAnimationType(DEFAULT_TA_ANIMATION_TYPE),
		mIsSingleRowRandom(DEFAULT_TA_START_RANDOM),
		mRowIndex(0),
		mCycles(1),
		mTileX(1),
		mTileY(1)
	{
		mName = "TextureAnimatorAffector";
		mMinMaxTexAnimation.SetCurveState(Math::MinMaxCurve::Curve);
	}
	//--------------------------------------------------------------------------------
	void TextureAnimatorAffector::_onActivate(void)
	{
		Super::_onActivate();
		if (mParentSystem)
		{
			ParticleTarget* target = mParentSystem->GetTarget().get();
			if (target)
			{
				if(mEnable)
					target->SetTexCoordSize(mTileX, mTileY);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void TextureAnimatorAffector::SetTileX(ushort nCount)
	{
		mTileX = nCount;

		if(mTileX == 0)
			mTileX = 1;
		if (mParentSystem)
		{
			ParticleTarget* target = mParentSystem->GetTarget().get();
			if (target)
			{
				target->SetTexCoordRowSize(mTileX);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void TextureAnimatorAffector::SetTextureAnimationType(TextureAnimatorAffector::TextureAnimationType textureAnimationType)
	{
		mTextureAnimationType = textureAnimationType;
		if (mTextureAnimationType == TAT_WHOLE_SHEET )
		{
			int total = mTileX * mTileY;
		}
	}
	//--------------------------------------------------------------------------------
	void TextureAnimatorAffector::SetTileY(ushort nCount)
	{
		mTileY = nCount;
		if(mTileY == 0)
			mTileY = 1;
		if (mRowIndex > mTileY)
			mRowIndex = mTileY;

		if (mParentSystem)
		{
			ParticleTarget* target = mParentSystem->GetTarget().get();
			if (target)
			{
				target->SetTexcoordColumnSize(mTileY);
			}
		}
	}

	//-----------------------------------------------------------------------
	void TextureAnimatorAffector::_initParticleForEmission(Particle* particle)
	{		

	}
	//-----------------------------------------------------------------------
	void TextureAnimatorAffector::_affect(Particle* particle)
	{
		if(!GetEnable())
			return;
		if(!mEnable)
			return;

		float percent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;

		float time = mCycles * percent;
		float texCoordIndex = 0;
		float texCoordMaxIndex = 0;

		time = time - int(time);
		texCoordIndex = mMinMaxTexAnimation.Calculate(time,particle->mRandom0);

		int iTexCoordIndex = (int)texCoordIndex;

		if (mTextureAnimationType == TAT_WHOLE_SHEET)
		{
			iTexCoordIndex = iTexCoordIndex % (mTileX * mTileY);
		}
		else
		{
			int startRowIndex = mRowIndex ;

			if (mIsSingleRowRandom)
			{
				startRowIndex = (int)(particle->mRandom1 * mTileY) ;
			}

			startRowIndex = startRowIndex % ((int)mTileY );
			iTexCoordIndex = iTexCoordIndex % ((int)mTileX);
			iTexCoordIndex = startRowIndex * mTileX + iTexCoordIndex;
		}

		particle->mTexCoordIndex = iTexCoordIndex;

	}

}