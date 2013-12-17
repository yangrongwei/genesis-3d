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

#ifndef __poly_curve_H__
#define __poly_curve_H__
#include "util/array.h"
#include "curve.h"

namespace Math
{
	template<typename T>
	class PolyCurve:public Curve<T>
	{
	public:
		struct FrameLever
		{
			FrameLever(){}
			FrameLever(const T& leftkey,  const T& rightkey)
			{
				_left = leftkey;
				_right = rightkey;
			}
			T _left;
			T _right;
		};
		typedef Util::Array<FrameLever> LeverContainer;


		struct CurveType
		{
			CurveType()
			{
				_leftLinner = false;
				_rightLinner = false;
			}
			CurveType(bool leftLinner,bool rightLinner)
			{
				_leftLinner = leftLinner;
				_rightLinner = rightLinner;
			}
			bool _leftLinner;
			bool _rightLinner;
		};
		typedef Util::Array<CurveType> TypeContainer;

	public:
		PolyCurve(){}
		~PolyCurve(){}

		T EvaluatePolyCurveFloat(float t);

		//void AddKeyFrameAndLever(const Util::Array<T>& contaner);

		IndexT AddFrameLever(const T& leftkey,  const T& rightkey) {
			mFrameLevers.Append(FrameLever(leftkey, rightkey));
			return mFrameLevers.Size() -1;
		}

		void AddLeftLever(IndexT nIdx, const T& key) {
			if ( nIdx >= mFrameLevers.Size())
			{
				mFrameLevers.Append(FrameLever());
				mFrameLevers.Back()._left = key;
			}
			else
			{
				mFrameLevers[nIdx]._left = key;
			}
		}
		const T& GetLeftLever(IndexT nIdx){
			n_assert( nIdx >= 0 && nIdx < mFrameLevers.Size() );
			return mFrameLevers[nIdx]._left;
		}

		void AddRightLever(IndexT nIdx, const T& key) {
			if ( nIdx >= mFrameLevers.Size())
			{
				mFrameLevers.Append(FrameLever());
				mFrameLevers.Back()._right = key;
			}
			else
			{
				mFrameLevers[nIdx]._right = key;
			}
		}
		const T& GetRightLever(IndexT nIdx){
			n_assert( nIdx >= 0 && nIdx < mFrameLevers.Size() );
			return mFrameLevers[nIdx]._right;
		}
		const FrameLever& GetFrameLever(IndexT index) const {
			n_assert( index >= 0 && index < mFrameLevers.Size() );
			return mFrameLevers[index];
		}

		FrameLever& GetFrameLever(IndexT index) {
			n_assert( index >= 0 && index < mFrameLevers.Size() );
			return mFrameLevers[index];
		}

		SizeT GetFrameLeversCount() const
		{
			return  mFrameLevers.Size();
		}

		void ClearFrameLevers()
		{
			mFrameLevers.Clear();
		}

		void RemoveFrameLevers(IndexT index)
		{
			if ( index >= 0 && index < mFrameLevers.Size() ) {
				mFrameLevers.EraseIndex( index );
			}	
		}

		IndexT AddCurveType(bool leftkey,bool rightkey) {
			mCurveTypes.Append(CurveType(leftkey, rightkey));
			return mCurveTypes.Size() -1;
		}

		void AddLeftCurveType(IndexT nIdx, bool key) {
			if ( nIdx >= mCurveTypes.Size())
			{
				mCurveTypes.Append(CurveType());
				mCurveTypes.Back()._leftLinner = key;
			}
			else
			{
				mCurveTypes[nIdx]._leftLinner = key;
			}
		}

		bool GetLeftCurveType(IndexT nIdx) const
		{
			n_assert( nIdx >= 0 && nIdx < mCurveTypes.Size() );
			return mCurveTypes[nIdx]._leftLinner;
		}

		void AddRightCurveType(IndexT nIdx,bool key) {
			if ( nIdx >= mCurveTypes.Size())
			{
				mCurveTypes.Append(CurveType());
				mCurveTypes.Back()._rightLinner = key;
			}
			else
			{
				mCurveTypes[nIdx]._rightLinner = key;
			}
		}
		bool GetRightCurveType(IndexT nIdx)const
		{
			n_assert( nIdx >= 0 && nIdx < mCurveTypes.Size() );
			return mCurveTypes[nIdx]._rightLinner;
		}

		SizeT GetCurveTypesCount() const
		{
			return  mCurveTypes.Size();
		}

		void ClearCurveTypes()
		{
			mCurveTypes.Clear();
		}

		void AddPolyKeyFrame(const T& key ,bool leftLinner = false ,bool rightLinner = false) {
			IndexT InX = this->AddKeyFrame(key);
			mCurveTypes.Insert(InX,CurveType(leftLinner,rightLinner));
		}
	protected:
		LeverContainer mFrameLevers;
		TypeContainer mCurveTypes;
	};


	typedef PolyCurve<Math::FloatKeyFrame>         FloatPolyCurve;

	//--------------------------------------------------------------------------------
	template<typename T>
	T PolyCurve<T>::EvaluatePolyCurveFloat(float t)
	{
		int keyCount = this->mKeyFrames.Size();		
		T resultFrame;

		if(t < this->mKeyFrames[0].GetTime()  || keyCount < 2)
		{
			 float result = this->mKeyFrames[0].GetValue();
			 resultFrame.SetValue(result);
		}
		else if (t > this->mKeyFrames[keyCount-1].GetTime() )
		{
			float result = this->mKeyFrames[keyCount-1].GetValue();
			resultFrame.SetValue(result );
		}		
		else
		{

			//--------------------------------------------------------------------------------
			T first;
			T second;
			float percentage;
			int nIdx = this->CalculateKeyFrame(t, first, second, percentage);
			if ( nIdx >= this->mFrameLevers.Size() || (mCurveTypes[nIdx]._rightLinner && mCurveTypes[nIdx+1]._leftLinner))
			{
				// if isnt exit,linner
				return Curve<T>::EvaluateFloat(t);
			}

			T& firstRight = this->mFrameLevers[nIdx]._left;
			T& secondLeft = this->mFrameLevers[nIdx]._right;

			if ( secondLeft.GetTime() < TINY )
				return first;
			if ( firstRight.GetTime() < TINY )
				return second;


			//--------------------------------------------------------------------------------
			float tSquared, tCubed; 
			float result; 

			float timeLength = second.GetTime() - first.GetTime();
			float curPercentage = ( t -  first.GetTime() ) / timeLength;

			tSquared = curPercentage * curPercentage; 
			tCubed = tSquared * curPercentage; 

			float t_ = 1.0f - curPercentage;
			float t_Squared = t_ * t_;
			float t_Cubed = t_ * t_ * t_;

			result = t_Cubed * first.GetValue() + 3 * curPercentage * t_Squared * firstRight.GetValue()
				     + 3 * tSquared * t_ * secondLeft.GetValue() + tCubed * second.GetValue();
			/***/
			resultFrame.SetValue(result);
		}

		return resultFrame;
	}
	//--------------------------------------------------------------------------------
	//template<typename T>
	//void PolyCurve<T>::AddKeyFrameAndLever(const Util::Array<T>& contaner)
	//{

	//}
}




#endif // __poly_curve_H__
