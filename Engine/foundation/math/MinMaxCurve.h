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

#ifndef __MinMax_Curve_H__
#define __MinMax_Curve_H__
#include "PolyCurve.h"
#include "util/array.h"

namespace Math
{
	class MinMaxCurve
	{
	public:
		enum	CurveState { Scalar = 0,RandomScalar = 1,Curve = 2, TwoCurves = 3,};
		MinMaxCurve(CurveState curveState = Scalar);
		~MinMaxCurve(){}

		float Calculate(float time,float randomValue = 1.0f);
		void SetTwoCurve(const FloatPolyCurve& curve1, const FloatPolyCurve& curve2);
		void GetTwoCurve(FloatPolyCurve& curve1, FloatPolyCurve& curve2)const;
		void SetOneCurve(const FloatPolyCurve& curve1);
		void GetOneCurve(FloatPolyCurve& curve1)const;
		void SetMaxY(float Value);
		void SetScalar(float Value);
		float GetMaxY(void) const;
		float GetScalar(void) const;
		void SetRandomScalar(float2 Value);
		float2 GetRandomScalar() const;
		void SetCurveState(CurveState state);
		CurveState GetCurveState(void) const;
		void CopyFrom(const MinMaxCurve& source);
		void GetArrayFromCurve(Util::Array<float2>& _list,Util::Array<bool>& _curveTypes) const;
		void SetCurveFromArray(const Util::Array<float2>& _list, const Util::Array<bool>& _curveTypes);
		void GetArrayFromCurve(Util::Array<float2>& _list1,Util::Array<bool>& _curveTypes1,
			Util::Array<float2>& _list2,Util::Array<bool>& _curveTypes2) const;
		void SetCurveFromArray(const Util::Array<float2>& _list1, const Util::Array<bool>& _curveTypes1,
			const Util::Array<float2>& _list2, const Util::Array<bool>& _curveTypes2);
		void Clear();
	protected:
		FloatPolyCurve	mMinCurve;
		FloatPolyCurve	mMaxCurve;

		float					mMinScalar;
		float                   mMaxScalar;
		float					mMaxY;
		float					mMinY;
		CurveState        mCurveState;

		void _getCurve(const FloatPolyCurve& curve, Util::Array<float2>& _list,Util::Array<bool>& _curveTypes)const;
		void _setCurve(FloatPolyCurve& curve, const Util::Array<float2>& _list, const Util::Array<bool>& _curveTypes);
	};
	inline void MinMaxCurve::GetTwoCurve(FloatPolyCurve& curve1, FloatPolyCurve& curve2) const
	{
		curve1 = mMinCurve;
		curve2 = mMaxCurve;
	}
	inline void MinMaxCurve::SetTwoCurve(const FloatPolyCurve& curve1, const FloatPolyCurve& curve2)
	{
		mMinCurve = curve1;
		mMaxCurve = curve2;
	}
	inline void MinMaxCurve::SetOneCurve(const FloatPolyCurve& curve1)
	{
		mMinCurve = curve1;
	}
	inline void MinMaxCurve::GetOneCurve(FloatPolyCurve& curve1) const
	{
		curve1 = mMinCurve;
	}
	inline void MinMaxCurve::SetScalar(float Value)
	{
		mMinScalar = Value;
	}
	inline float MinMaxCurve::GetMaxY(void) const
	{
		return mMaxY;
	}
	inline float MinMaxCurve::GetScalar(void) const
	{
		return mMinScalar;
	}
	inline void MinMaxCurve::SetRandomScalar(float2 Value)
	{
		mMinScalar = Value.x();
		mMaxScalar = Value.y();
	}
	inline float2 MinMaxCurve::GetRandomScalar() const
	{
		return float2(mMinScalar,mMaxScalar);
	}
	inline MinMaxCurve::CurveState MinMaxCurve::GetCurveState(void) const
	{
		return mCurveState;
	}
}








#endif //__MinMax_curve_H__