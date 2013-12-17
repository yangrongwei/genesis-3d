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
#ifndef __MESH_BUILDER_H__
#define __MESH_BUILDER_H__

#ifdef __OSX__
#include "core/types.h"
#include "math/matrix44.h"
#else
#include "foundation/core/types.h"
#include "foundation/math/matrix44.h"
#endif

namespace MeshBuilder
{
	inline unsigned char* _bias_in_bytes(void* ptr, size_t bias)
	{
		return reinterpret_cast<unsigned char*>(ptr) + bias;
	}

	void _transforms(ubyte* buffer, SizeT vertexCount, SizeT vertexSize, SizeT posBias, const Math::matrix44& trans);

	// buffer: vertex buffer, vertexSize: a vertex element's size, posBias: the starting location(in bytes) of position data in a vertex element
	// trans: transform matrix
	template<typename T>
	inline void TransformPositions(T* buffer, SizeT vertexCount, SizeT vertexSize, SizeT posBias, const Math::matrix44& trans)
	{
		_transforms(reinterpret_cast<ubyte*>(buffer), vertexCount, vertexSize, posBias, trans);
	}

	// buffer: vertex buffer, vertexSize: a vertex element's size, normBias: the starting location(in bytes) of normal data in a vertex element
	// trans: transform matrix
	template<typename T>
	inline void TransformNormals(T* buffer, SizeT vertexCount, SizeT vertexSize, SizeT normBias, const Math::matrix44& trans)
	{
		Math::matrix44 Inverse      = Math::matrix44::inverse(trans);
		Math::matrix44 InvTranspose = Math::matrix44::transpose(Inverse);
		InvTranspose.set_position(Math::float4(0, 0, 0, 1));
		_transforms(reinterpret_cast<ubyte*>(buffer), vertexCount, vertexSize, normBias, InvTranspose);
	}


	// ----------------------------------------------------------------------------------------
	// const iterator
	template<typename TYPE>
	class elem_iterator_const
	{
	public:
		elem_iterator_const(const ubyte* begin, SizeT vertex_size);
		elem_iterator_const(ubyte* begin, SizeT vertex_size);
		void operator ++();
		void operator --();
		const TYPE& operator *() const;
		const TYPE* operator->() const;
		const TYPE* get() const;
		const TYPE* get(SizeT elem_bias) const;
	protected:
		union
		{
			mutable ubyte* ptr;
			TYPE* elem_ptr;
		};
		SizeT vertex_size;
	};

	template<typename TYPE>
	inline elem_iterator_const<TYPE>::elem_iterator_const(const ubyte* begin, SizeT vertex_size)
	{
		n_assert(NULL != begin);
		this->ptr = const_cast<ubyte*>(begin);
		this->vertex_size = vertex_size;
	}

	template<typename TYPE>
	inline elem_iterator_const<TYPE>::elem_iterator_const(ubyte* begin, SizeT vertex_size)
	{
		n_assert(NULL != begin);
		this->ptr = begin;
		this->vertex_size = vertex_size;
	}

	template<typename TYPE>
	inline void elem_iterator_const<TYPE>::operator ++()
	{
		this->ptr += vertex_size;
	}	

	template<typename TYPE>
	inline void elem_iterator_const<TYPE>::operator --()
	{
		this->ptr -= vertex_size;
	}

	template<typename TYPE>
	inline const TYPE& elem_iterator_const<TYPE>::operator *() const
	{
		return *(this->elem_ptr);
	}

	template<typename TYPE>
	inline const TYPE* elem_iterator_const<TYPE>::operator->() const
	{
		return this->elem_ptr;
	}

	template<typename TYPE>
	inline const TYPE* elem_iterator_const<TYPE>::get() const
	{
		return this->elem_ptr;
	}

	template<typename TYPE>
	inline const TYPE* elem_iterator_const<TYPE>::get(SizeT elem_bias) const
	{
		return reinterpret_cast <TYPE*>(this->ptr + elem_bias * vertex_size);
	}
	// ===================================================================================================
	// unconst iterator
	template<typename TYPE>
	class elem_iterator : public elem_iterator_const<TYPE>
	{
	public:
		typedef elem_iterator<TYPE> self;
		elem_iterator(ubyte* begin, SizeT vertex_size);
		TYPE& operator *() const;
		TYPE* operator->() const;
		self& operator ++ () const;
		const self& operator ++ (int) const;

		TYPE* get() const;		
		TYPE* get(SizeT elem_bias) const;
		void set(const TYPE& info);
	protected:
		typedef elem_iterator_const<TYPE> super;

	};

	template<typename TYPE>
	inline elem_iterator<TYPE>::elem_iterator(ubyte* begin, SizeT vertex_size)
		: super(begin, vertex_size)
	{
	}

	template<typename TYPE>
	inline TYPE& elem_iterator<TYPE>::operator *() const
	{
		return *(this->elem_ptr);
	}

	template<typename TYPE>
	inline TYPE* elem_iterator<TYPE>::operator->() const
	{
		return this->elem_ptr;
	}

	template<typename TYPE>
	inline elem_iterator<TYPE>& elem_iterator<TYPE>::operator ++ () const
	{
		this->ptr += this->vertex_size;
		return *((self*)this);
	}
	template<typename TYPE>
	inline const elem_iterator<TYPE>& elem_iterator<TYPE>::operator ++ (int) const
	{
		this->ptr += this->vertex_size;
		return *((self*)this);
	}


	template<typename TYPE>
	inline TYPE* elem_iterator<TYPE>::get() const
	{
		return this->elem_ptr;
	}

	template<typename TYPE>
	inline TYPE* elem_iterator<TYPE>::get(SizeT elem_bias) const
	{
		return reinterpret_cast <TYPE*>(this->ptr + elem_bias * this->vertex_size);
	}

	template<typename TYPE>
	inline void elem_iterator<TYPE>::set(const TYPE& info)
	{
		*(this->elem_ptr) = info;
	}
}

#endif //__MESH_BUILDER_H__