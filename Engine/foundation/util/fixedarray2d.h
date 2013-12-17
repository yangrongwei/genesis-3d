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

#ifndef __fixedarray2d_H__
#define __fixedarray2d_H__

#include "util/fixedarray.h"

namespace Util
{
	/**
		简单的固定大小的2维数组的实现。可退化到1维数组使用
		1、表示一个固定大小的二维数组。
		2、列优先存储。
		(0,0)(1,0)(2,0)
	**/
	template<typename TYPE>
	class FixedArray2D
	{
	public:
		/// define element iterator
		typedef TYPE* Iterator;

		FixedArray2D();

		FixedArray2D(SizeT rowSize, SizeT colSize, const TYPE& initialValue);

		/// all elems count 
		SizeT Size() const;

		/// max row size
		SizeT RowSize() const;
		
		/// max column size
		SizeT ColSize() const;

		/// reset  size 
		void Resize(SizeT rowSize, SizeT colSize);

		/// reset  size  with initialValue
		void Resize(SizeT rowSize, SizeT colSize, const TYPE& initialValue);

		/// clear all elems
		void Clear();

		/// for get elem
		const TYPE& At(IndexT row, IndexT col) const;

		/// for get and set elem
		TYPE& At(IndexT row, IndexT col);

		/// get iterator to first element
		Iterator Begin() const;

		/// get iterator past last element
		Iterator End() const;

		/// (row,col) to 1D Index
		IndexT Index(IndexT row, IndexT col) const;

	protected:
		 Util::FixedArray<TYPE> _array;
		 SizeT _rowSize;	//	行数
		 SizeT _colSize;	//  列数
	};

	//------------------------------------------------------------------------------
	template<typename TYPE>
	FixedArray2D<TYPE>::FixedArray2D() :
	_rowSize(0),
	_colSize(0),
	_array(0)
	{
		// empty
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	FixedArray2D<TYPE>::FixedArray2D(SizeT rowSize, SizeT colSize, const TYPE& initialValue) :
	_rowSize(rowSize),
	_colSize(colSize),
	_array(rowSize*colSize,initialValue)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(rowSize > 0 && colSize >0 );
#endif
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT
	FixedArray2D<TYPE>::Size() const
	{
		return _array.Size();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT
	FixedArray2D<TYPE>::RowSize() const
	{
		return _rowSize;
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT
	FixedArray2D<TYPE>::ColSize() const
	{
		return _colSize;
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void
	FixedArray2D<TYPE>::Resize(SizeT rowSize, SizeT colSize)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(rowSize > 0 && colSize >0 );
#endif

		_rowSize = rowSize;
		_colSize = colSize;
		_array.Resize(_rowSize*_colSize);
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void
	FixedArray2D<TYPE>::Resize(SizeT rowSize, SizeT colSize, const TYPE& initialValue)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(rowSize > 0 && colSize >0 );
#endif

		_rowSize = rowSize;
		_colSize = colSize;
		_array.Resize(_rowSize*_colSize);
		FixedArray2D<TYPE>::Iterator itor = Begin();
		FixedArray2D<TYPE>::Iterator end = End();
		for (; itor != end; ++itor )
		{
			(*itor) = initialValue;
		}
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void 
	FixedArray2D<TYPE>::Clear()
	{
		_array.Clear();
		_colSize = 0;
		_rowSize = 0;
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	const TYPE& 
	FixedArray2D<TYPE>::At(IndexT row, IndexT col) const
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(row >= 0 && row < _rowSize);
		n_assert(col >= 0 && col < _colSize);
#endif

		IndexT index = Index(row,col);
		return _array[index];
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	TYPE& 
	FixedArray2D<TYPE>::At(IndexT row, IndexT col)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(row >= 0 && row < _rowSize);
		n_assert(col >= 0 && col < _colSize);
#endif

		IndexT index = Index(row,col);
		return _array[index];
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	typename FixedArray2D<TYPE>::Iterator 
	FixedArray2D<TYPE>::Begin() const
	{
		return _array.Begin();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	typename FixedArray2D<TYPE>::Iterator 
	FixedArray2D<TYPE>::End() const
	{
		return _array.End();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	IndexT 
	FixedArray2D<TYPE>::Index(IndexT row, IndexT col) const
	{
		return row + col * _rowSize;
	}
}






#endif // __fixedarray2d_H__








