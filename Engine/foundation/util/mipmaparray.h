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

#ifndef __miparray_H__
#define __miparray_H__
#include "util/fixedarray2d.h"
#include "util/array.h"

namespace Util
{
	/** 用于线性的存储四分金字塔数据。mip=0时，精度最高。 mip范围是[0,mipCount)
		暂只支持行列相等的金字塔
	**/
	template<typename TYPE>
	class MipmapArray
	{
	public:
		MipmapArray();

		void Resize(SizeT mipCount, const TYPE& elem);

		void Resize(SizeT mipCount);

		void Clear();

		/// all elems count in all levels
		SizeT GetAllElemsCount() const;

		/// get mipmap count
		SizeT GetMipCount() const;

		/// row size in level
		SizeT RowSize(IndexT level) const;

		/// column size in level
		SizeT ColSize(IndexT level) const;

		const TYPE& At(IndexT row, IndexT col, IndexT level) const;

		TYPE& At(IndexT row, IndexT col, IndexT level);

		/// (row,col,level) to 1D Index
		IndexT Index(IndexT row, IndexT col, IndexT level) const;

	protected:
		typedef Util::FixedArray2D<TYPE> _interContaner;
		typedef Util::Array<_interContaner> Container;
		
		/// 先存储n*n，(n-1)*(n-1), 1*1, 从精度最高向最低存储
		Container _array;
	};
	//------------------------------------------------------------------------
	template<typename TYPE>
	MipmapArray<TYPE>::MipmapArray()
	{

	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void 
	MipmapArray<TYPE>::Resize(SizeT mipCount, const TYPE& elem)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(mipCount>=0);
#endif

		Clear();

		if ( mipCount > 0 )
		{
			_array.Resize( mipCount, _interContaner());
			for ( IndexT i = 0; i < mipCount; ++i)
			{
				SizeT rowSizeInLevel = 1 << (mipCount-1-i);
				_array[i].Resize(rowSizeInLevel, rowSizeInLevel,elem);
			}
		}
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void 
	MipmapArray<TYPE>::Resize(SizeT mipCount)
	{
#if NEBULA3_BOUNDSCHECKS
		n_assert(mipCount>=0);
#endif

		Clear();

		if ( mipCount > 0 )
		{
			_array.Resize( mipCount );
			for ( IndexT i = 0; i < mipCount; ++i)
			{
				SizeT rowSizeInLevel = 1 << (mipCount-1-i);
				_array[i].Resize(rowSizeInLevel, rowSizeInLevel);
			}
		}
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT 
	MipmapArray<TYPE>::GetAllElemsCount() const
	{
		//@TODO If Has Quick Method? 
		SizeT size = 0;
		for ( IndexT i =0; i < _array.Size(); ++i)
		{
			size += ( _array[i].Size() );
		}
		return size;
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT 
	MipmapArray<TYPE>::GetMipCount() const
	{
		return _array.Size();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	void 
	MipmapArray<TYPE>::Clear()
	{
		_array.Clear();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT MipmapArray<TYPE>::RowSize(IndexT level) const
	{
		return _array[level].RowSize();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	SizeT MipmapArray<TYPE>::ColSize(IndexT level) const
	{
		return _array[level].ColSize();
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	const TYPE& 
	MipmapArray<TYPE>::At(IndexT row, IndexT col, IndexT level) const
	{
		const _interContaner& inner = _array[level];
		return inner.At(row,col);
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	TYPE& 
	MipmapArray<TYPE>::At(IndexT row, IndexT col, IndexT level)
	{
		_interContaner& inner = _array[level];
		return inner.At(row,col);
	}
	//------------------------------------------------------------------------
	template<typename TYPE>
	IndexT 
	MipmapArray<TYPE>::Index(IndexT row, IndexT col, IndexT level) const
	{
		IndexT index = 0;
		for ( IndexT mip = 0; mip < level ; ++mip )
		{
			index += ( _array[mip].Size() );
		}

		index += _array[level].Index(row, col);

		return index;
	}
	//------------------------------------------------------------------------

}








#endif // __miparray_H__
