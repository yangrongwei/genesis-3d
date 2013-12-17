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
#include "particleColorAffector.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::ColorAffector, CPFCC::AFFECTOR_COLOR, Particles::ParticleAffector);

	const ColorAffector::ColorOperation ColorAffector::DEFAULT_COLOR_OPERATION = ColorAffector::CAO_SET;

	//-----------------------------------------------------------------------
	ColorAffector::ColorAffector(void) : ParticleAffector(),mMinAlpha(0.0f),mMaxAlpha(1.0f),mTimeAlpha(false)
		, mColorCtlType(CCT_GRADCURVE)
	{
		mMinMaxColorA.SetCurveState(Math::MinMaxCurve::Curve);	
		mMinMaxColorR.SetCurveState(Math::MinMaxCurve::Curve);
		mMinMaxColorG.SetCurveState(Math::MinMaxCurve::Curve);
		mMinMaxColorB.SetCurveState(Math::MinMaxCurve::Curve);


		mName = "ColorAffector";

		Util::Array<Math::float2> _list;
		Util::Array<bool> _type;
		_list.Append(Math::float2(0,1));
		_type.Append(true);
		_type.Append(true);
		mMinMaxColorA.SetCurveFromArray(_list,_type,_list,_type);
		_list.Clear();
		_list.Append(Math::float2(0,0.5));
		mMinMaxColorB.SetCurveFromArray(_list,_type,_list,_type);
		mMinMaxColorG.SetCurveFromArray(_list,_type,_list,_type);
		mMinMaxColorR.SetCurveFromArray(_list,_type,_list,_type);

		mMinMaxColorR.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorG.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorB.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorA.SetRandomScalar(Math::float2(1.0f,1.0f));
	}
	//-----------------------------------------------------------------------
	void ColorAffector::_affect(Particle* particle)
	{		
		if(!GetEnable())
			return;
		Math::Color32 clr;

		float percent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;

		float randomSid = Math::n_rand(0.0f,1.0f);
		clr.r =  Math::n_scalartoByte(mMinMaxColorR.Calculate(percent,randomSid));
		clr.g =  Math::n_scalartoByte(mMinMaxColorG.Calculate(percent,randomSid));
		clr.b =  Math::n_scalartoByte(mMinMaxColorB.Calculate(percent,randomSid)) ;
		clr.a =  Math::n_scalartoByte(mMinMaxColorA.Calculate(percent,randomSid));

		particle->mColor = clr;

	}
	//------------------------------------------------------------------------
	void ColorAffector::_preProcessParticles(void)
	{

	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* ColorAffector::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case	Affector_ColorR:
			return &mMinMaxColorR;
		case	Affector_ColorG:
			return &mMinMaxColorG;
		case	Affector_ColorB:
			return &mMinMaxColorB;
		case	Affector_ColorA:
			return &mMinMaxColorA;

		default:
			return Super::getMinMaxCurve(pct);					
		}
	}
}

