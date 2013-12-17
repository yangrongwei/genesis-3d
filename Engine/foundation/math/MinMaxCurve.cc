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
#include "MinMaxCurve.h"

namespace Math
{
	MinMaxCurve::MinMaxCurve(CurveState curveState):
	mMinScalar(0.0f),
	mMaxScalar(1.0f),
	mCurveState(curveState),
	mMaxY(0)
	{
		mMinCurve.AddPolyKeyFrame(FloatKeyFrame(0.0f, 0.0f));
		mMaxCurve.AddPolyKeyFrame(FloatKeyFrame(0.0f, 1.0f));
	}
	float MinMaxCurve::Calculate(float time,float randomValue)
	{
		float ans = 0.0f;
		switch(mCurveState)
		{
		case Scalar:
			ans = mMinScalar;
			break;
		case RandomScalar:
			ans = n_lerp(mMinScalar,mMaxScalar,randomValue);
			break;
		case Curve:
			ans = mMinCurve.EvaluatePolyCurveFloat(time).GetValue();
			break;
		case TwoCurves:
			ans = n_lerp(mMinCurve.EvaluatePolyCurveFloat(time).GetValue(),
				mMaxCurve.EvaluatePolyCurveFloat(time).GetValue(),randomValue);
			break;
		}
		return ans;
	}
	
	void MinMaxCurve::SetCurveState(CurveState state)
	{
		if( (Scalar == mCurveState || RandomScalar == mCurveState) 
			&& Curve == state )
		{
			//clear the curve data
			mMinCurve.ClearFrames();
			mMinCurve.ClearFrameCache();
			mMinCurve.ClearFrameLevers();

			mMinCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMinScalar) );
		}
		else if (  RandomScalar == mCurveState
			&& TwoCurves == state )
		{
			//clear the curve data
			mMinCurve.ClearFrames();
			mMinCurve.ClearFrameCache();
			mMinCurve.ClearFrameLevers();

			mMinCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMinScalar) );

			mMaxCurve.ClearFrames();
			mMaxCurve.ClearFrameCache();
			mMaxCurve.ClearFrameLevers();

			mMaxCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMaxScalar) );
		}
		else if (Scalar == mCurveState
			&& TwoCurves == state )
		{
			mMinCurve.ClearFrames();
			mMinCurve.ClearFrameCache();
			mMinCurve.ClearFrameLevers();

			mMinCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMinScalar) );
		}
		else if ( ( mCurveState == Curve || mCurveState == TwoCurves ) 
			&& RandomScalar == state )
		{
			if (!mMinCurve.IsEmpty())
			{
				mMinScalar = mMinCurve.EvaluatePolyCurveFloat(0.0f).GetValue();

				mMinCurve.ClearFrames();
				mMinCurve.ClearFrameCache();
				mMinCurve.ClearFrameLevers();

				mMinCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMinScalar) );
			}
			if (!mMaxCurve.IsEmpty())
			{
				mMaxScalar = mMaxCurve.EvaluatePolyCurveFloat(0.0f).GetValue();

				mMaxCurve.ClearFrames();
				mMaxCurve.ClearFrameCache();
				mMaxCurve.ClearFrameLevers();

				mMaxCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMaxScalar) );
			}
		}
		else if (( mCurveState == Curve || mCurveState == TwoCurves ) 
			&& Scalar == state )
		{
			if (!mMinCurve.IsEmpty())
			{
				mMinScalar = mMinCurve.EvaluatePolyCurveFloat(0.0f).GetValue();

				mMinCurve.ClearFrames();
				mMinCurve.ClearFrameCache();
				mMinCurve.ClearFrameLevers();

				mMinCurve.AddPolyKeyFrame( FloatKeyFrame(0.0f, mMinScalar) );
			}
		}

		mCurveState = state;
	}
	
	void MinMaxCurve::CopyFrom(const MinMaxCurve& source)
	{
		this->mMinScalar = source.mMinScalar;
		this->mMaxScalar = source.mMaxScalar;
		this->mCurveState = source.mCurveState;
		this->mMinCurve = source.mMinCurve;
		this->mMaxCurve = source.mMaxCurve;
	}
	void MinMaxCurve::GetArrayFromCurve(Util::Array<float2>& _list,Util::Array<bool>& _curveTypes) const
	{
		_getCurve(mMinCurve,_list,_curveTypes);
	}
	void MinMaxCurve::SetCurveFromArray(const Util::Array<float2>& _list,const Util::Array<bool>& _curveTypes)
	{
		_setCurve(mMinCurve,_list,_curveTypes);
	}
	void MinMaxCurve::GetArrayFromCurve(Util::Array<float2>& _list1,Util::Array<bool>& _curveTypes1, Util::Array<float2>& _list2,Util::Array<bool>& _curveTypes2) const
	{
		_getCurve(mMinCurve,_list1,_curveTypes1);
		_getCurve(mMaxCurve,_list2,_curveTypes2);
	}
	void MinMaxCurve::SetCurveFromArray(const Util::Array<float2>& _list1, const Util::Array<bool>& _curveTypes1, const Util::Array<float2>& _list2, const Util::Array<bool>& _curveTypes2)
	{
		_setCurve(mMinCurve,_list1,_curveTypes1);
		_setCurve(mMaxCurve,_list2,_curveTypes2);
	}
	void MinMaxCurve::Clear()
	{		
		mMinCurve.ClearCurveTypes();
		mMinCurve.ClearFrameCache();
		mMinCurve.ClearFrameLevers();
		mMinCurve.ClearFrames();

		mMaxCurve.ClearCurveTypes();
		mMaxCurve.ClearFrameCache();
		mMaxCurve.ClearFrameLevers();
		mMaxCurve.ClearFrames();
	}
	void MinMaxCurve::SetMaxY(float Value)
	{
		mMaxY = Value;
		if(Curve != mCurveState && TwoCurves != mCurveState)
			return;
		SizeT count = mMinCurve.GetKeyFrameCount();
		for (IndexT i = 0; i < count; i++)
		{
			FloatKeyFrame key = mMinCurve.GetKeyFrame(i);
			if(key.GetValue() > mMaxY)
			{
				mMinCurve.RemoveKeyFrame(i);
				key.SetValue(mMaxY);
				mMinCurve.AddKeyFrame(key);
			}
		}
		count = mMinCurve.GetFrameLeversCount();
		for(IndexT i=0;i<count;i++)
		{
			FloatKeyFrame leftkey = mMinCurve.GetLeftLever(i);
			FloatKeyFrame rightkey = mMinCurve.GetRightLever(i);
			if(leftkey.GetValue() > mMaxY || rightkey.GetValue() > mMaxY)
			{
				mMinCurve.RemoveFrameLevers(i);
				if(leftkey.GetValue() > mMaxY)
					leftkey.SetValue(mMaxY);
				if(rightkey.GetValue() > mMaxY)
					rightkey.SetValue(mMaxY);
				mMinCurve.AddFrameLever(leftkey,rightkey);
			}
		}
		if(TwoCurves != mCurveState)
			return;
		count = mMaxCurve.GetKeyFrameCount();
		for (IndexT i = 0; i < count; i++)
		{
			FloatKeyFrame key = mMaxCurve.GetKeyFrame(i);
			if(key.GetValue() > mMaxY)
			{
				mMaxCurve.RemoveKeyFrame(i);
				key.SetValue(mMaxY);
				mMaxCurve.AddKeyFrame(key);
			}
		}
		count = mMaxCurve.GetFrameLeversCount();
		for (IndexT i = 0; i < count; i++)
		{
			FloatKeyFrame leftkey = mMaxCurve.GetLeftLever(i);
			FloatKeyFrame rightkey = mMaxCurve.GetRightLever(i);
			if(leftkey.GetValue() > mMaxY || rightkey.GetValue() > mMaxY)
			{
				mMaxCurve.RemoveFrameLevers(i);
				if(leftkey.GetValue() > mMaxY)
					leftkey.SetValue(mMaxY);
				if(rightkey.GetValue() > mMaxY)
					rightkey.SetValue(mMaxY);
				mMaxCurve.AddFrameLever(leftkey,rightkey);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void MinMaxCurve::_setCurve(FloatPolyCurve& curve, const Util::Array<float2>& _list, const Util::Array<bool>& _curveTypes)
	{
		//n_assert(_list.Size > 2);
		curve.ClearFrames();
		curve.ClearFrameCache();
		curve.ClearFrameLevers();
		curve.ClearCurveTypes();
		// make sure the  keys and levers are symmetrical
		//   |/     |/     |
		//   O~~O~~O
		//   |     /|    / |
		SizeT count = (_list.Size() + 2 ) /3 - 1;

		if (count < 0 )
		{
			return;
		}
		SizeT typeCount = _curveTypes.Size();
		
		for (IndexT Idx = 0; Idx < count ; Idx++)
		{
			bool leftLinner = true;
			bool rightLinner = true;
			int curIdx = Idx * 3;
			if(typeCount > 2*Idx + 1 )
			{
				leftLinner = _curveTypes[2*Idx];
				rightLinner = _curveTypes[2*Idx+1];
			}
			curve.AddPolyKeyFrame(FloatKeyFrame ( _list[curIdx].x(), _list[curIdx].y()),leftLinner,rightLinner);
			float time = _list[curIdx+1].x();
			float value = _list[curIdx+1].y();
			if(typeCount > 2*Idx+1  && _curveTypes[2*Idx+1])			//如果是Linner，控制点设为左到右的三分之一处。;
			{
				time = _list[curIdx].x() + (_list[curIdx+3].x() - _list[curIdx].x()) / 3.0f;
				value = _list[curIdx].y() + (_list[curIdx+3].y() - _list[curIdx].y()) / 3.0f;
				
			}
			curve.AddLeftLever(Idx , FloatKeyFrame ( time,value) );

			time = _list[curIdx+2].x();
			value = _list[curIdx+2].y();
			if(typeCount > 2*Idx+2 && _curveTypes[2*Idx+2] )			//如果是Linner，控制点设为左到右的三分之二处。;
			{
				time = _list[curIdx+3].x() - (_list[curIdx+3].x() - _list[curIdx].x()) / 3.0f;
				value = _list[curIdx+3].y() - (_list[curIdx+3].y() - _list[curIdx].y()) / 3.0f;
			}
			curve.AddRightLever(Idx , FloatKeyFrame (time,value) );
			
		}	
		bool leftLinner = true;
		bool rightLinner = true;
		if(typeCount > 2*count + 1 && 0 <= 2*count)
		{
			leftLinner = _curveTypes[2*count];
			rightLinner = _curveTypes[2*count+1];
		}
		curve.AddPolyKeyFrame(FloatKeyFrame ( _list[count * 3].x(), _list[count * 3].y()) ,leftLinner,rightLinner);
		
	}
	//--------------------------------------------------------------------------------
	void MinMaxCurve::_getCurve(const FloatPolyCurve& curve, Util::Array<float2>& _list,Util::Array<bool>& _curveTypes) const
	{
		_list.Clear();
		_curveTypes.Clear();
		SizeT count = curve.GetKeyFrameCount();
		SizeT nLevCnt = curve.GetFrameLeversCount();

		for (IndexT i = 0; i < count; i++)
		{
			FloatKeyFrame key = curve.GetKeyFrame(i);
			float2 tKF(key.GetTime(), key.GetValue());
			_list.Append(tKF);
			_curveTypes.Append(curve.GetLeftCurveType(i));
			_curveTypes.Append(curve.GetRightCurveType(i));

			if (i < nLevCnt)
			{
				FloatPolyCurve::FrameLever lever = curve.GetFrameLever(i);
				float2 leftLever(lever._left.GetTime(), lever._left.GetValue());
				float2 rightLever(lever._right.GetTime(), lever._right.GetValue());

				_list.Append(leftLever);
				_list.Append(rightLever);
			}
		}
	}	
}