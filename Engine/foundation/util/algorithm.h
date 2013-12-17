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

#ifndef __algorithm_H__
#define __algorithm_H__
#include "util/array.h"
#include "util/dictionary.h"

namespace Util
{

	// TEMPLATE FUNCTION swap (from <algorithm>)
	// if container. use container::swap
	template<class _Ty> inline
	void Swap(_Ty& _Left, _Ty& _Right)
	{	// exchange values stored at _Left and _Right
		if (&_Left != &_Right)
		{	// different, worth swapping
			_Ty _Tmp = _Left;

			_Left = _Right;
			_Right = _Tmp;
		}
	}
	//------------------------------------------------------------------------
	inline bool IsPowerTwo(SizeT size)
	{
		return (size & (size -1)) == 0;
	}
}






#endif // __algorithm_H__
