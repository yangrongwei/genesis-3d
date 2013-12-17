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
#ifndef __pool_H__
#define __pool_H__
#include "util/stl.h"



namespace Particles
{

	template <typename T>
	class Pool
	{
	public:
		typedef typename Util::STL_list<T*>::type PoolList;
		typedef typename PoolList::iterator PoolIterator; 
		PoolIterator mPoolIterator;

		//-----------------------------------------------------------------------
		Pool () 
		{
		};
		//-----------------------------------------------------------------------
		virtual ~Pool (void)
		{
		};
		//-----------------------------------------------------------------------

		inline bool isEmpty(void)
		{
			return mReleased.empty();
		};
		//-----------------------------------------------------------------------

		inline SizeT getSize(void)
		{
			return (SizeT)mReleased.size();
		};
		//-----------------------------------------------------------------------
		inline void resetIterator (void)
		{
			mPoolIterator = mReleased.begin();
		};
		//-----------------------------------------------------------------------
		inline T* getFirst (void)
		{
			resetIterator();
			if (end())
				return 0;

			return *mPoolIterator;
		};
		//-----------------------------------------------------------------------
		inline T* getNext (void)
		{
			if (end())
				return 0;

			mPoolIterator++;
			if (end())
				return 0;

			return *mPoolIterator;
		};
		//-----------------------------------------------------------------------
		inline bool end (void)
		{
			return mPoolIterator == mReleased.end();
		};
		//-----------------------------------------------------------------------
		inline void clear (void)
		{
			mLocked.clear();
			mReleased.clear();
		};
		//-----------------------------------------------------------------------
		/** 
		*/
		inline void addElement (T* element)
		{
			mLocked.push_back(element);
		};
		//-----------------------------------------------------------------------
		inline T* releaseElement (void)
		{
			if (mLocked.empty())
				return 0;

			T* t = mLocked.front();
			mReleased.splice(mReleased.end(), mLocked, mLocked.begin());
			return t;
		};
		//-----------------------------------------------------------------------
		inline void releaseAllElements (void)
		{
			mReleased.splice(mReleased.end(), mLocked);
			resetIterator();
		};
		//-----------------------------------------------------------------------
		inline void lockLatestElement (void)
		{
			mLocked.push_back(*mPoolIterator);
			mPoolIterator = mReleased.erase(mPoolIterator);
			if (mPoolIterator != mReleased.begin() && mPoolIterator != mReleased.end())
			{
				mPoolIterator--;
			}
		};
		//-----------------------------------------------------------------------
		inline void lockAllElements (void)
		{
			mLocked.splice(mLocked.end(), mReleased);
			resetIterator();
		};
		//-----------------------------------------------------------------------
		inline PoolList& getActiveElementsList(void)
		{
			return mReleased;
		};

	protected:
		PoolList mReleased;
		PoolList mLocked;
	};
}





#endif // __pool_H__
