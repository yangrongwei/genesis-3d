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
#include "parallelogrambuilder.h"

namespace MeshBuilder
{
	using namespace Math;

	const Math::float3 ParallelogramBuilder::sDefaultNormal(0.0f, 0.0f, 1.0f);

	void ParallelogramBuilder::Set(void* vertices, size_t vertex_size, const float3& top, const float3& right, const float3& center, 
		size_t position_bias)
	{
		n_assert(vertex_size >= sizeof(float3));
		elem_iterator<float3> elem(_bias_in_bytes(vertices, position_bias), vertex_size);
		*(elem) = center + top - right;//0
		*(++elem) = center + top + right;//1
		*(++elem) = center - top - right;//2
		*(++elem) = center - top + right;//3
	}

	void ParallelogramBuilder::Set(void* vertices, size_t vertex_size, const float3& top, const float3& right, const float3& center,
		size_t position_bias, size_t normal_bias)
	{
		n_assert(vertex_size >= sizeof(float3) * 2);
		Set(vertices, vertex_size, top, right, center, position_bias);
		float3 normal = right.crossProduct(top);
		normal = float3::normalize(normal);
		elem_iterator<float3> normal_elem(_bias_in_bytes(vertices, normal_bias), vertex_size);
		*normal_elem = normal;
		*(++normal_elem) = normal;
		*(++normal_elem) = normal;
		*(++normal_elem) = normal;
	}
	void ParallelogramBuilder::SetIndices(ushort* buffer)
	{
		n_assert(NULL != buffer);
		buffer[0] = 0;
		buffer[1] = 2;
		buffer[2] = 1;

		buffer[3] = 1;
		buffer[4] = 2;
		buffer[5] = 3;
	}
}