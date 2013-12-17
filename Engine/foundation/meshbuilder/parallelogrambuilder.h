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

#ifndef __RECT_BUILDER_H__
#define __RECT_BUILDER_H__

#include "meshbuilder/meshbuilder.h"
#include "math/float3.h"

namespace MeshBuilder
{
	// ======== ¶¥µã·Ö²¼ ================
	// ----------------------------------
	// ---- 0 - 1 ---------------------
	// ---- | / | ----------------------
	// ---- 2 - 3 ---------------------
	// ----------------------------------
	// indices: 0,2,1; 1,2,3
	// postion :Math::float3 , normal : Math::float3

#define RECT_VERTEX_COUNT 4
#define RECT_INDICES_COUNT 6
	class ParallelogramBuilder
	{
	public:
		// the vertex count in a rect
		static SizeT VertexCount();

		// the index count in a rect
		static SizeT IndexCount();

		// set indices
		static void SetIndices(ushort* buffer);

		static void Set(void* vertices, size_t vertex_size, const Math::float3& top, const Math::float3& right, const Math::float3& center, 
			size_t position_bias);

		static void Set(void* vertices, size_t vertex_size, const Math::float3& top, const Math::float3& right, const Math::float3& center, 
			size_t position_bias, size_t normal_bias);

		template<typename Vertex>
		static inline void Set(Vertex* vertices, const Math::float3& top, const Math::float3& right, const Math::float3& center, 
			size_t position_bias)
		{
			Set(vertices, sizeof(Vertex), top, right, center, position_bias);
		}

		template<typename Vertex>
		static inline void Set(Vertex* vertices, const Math::float3& top, const Math::float3& right, const Math::float3& center, 
			size_t position_bias, size_t normal_bias)
		{
			Set(vertices, sizeof(Vertex), top, right, center, position_bias, normal_bias);
		}

	private:

		static const Math::float3 sDefaultNormal;

		ParallelogramBuilder(){}
	};

	inline SizeT ParallelogramBuilder::VertexCount()
	{
		return RECT_VERTEX_COUNT;
	}

	inline SizeT ParallelogramBuilder::IndexCount()
	{
		return RECT_INDICES_COUNT;
	}
}
#endif//__RECT_BUILDER_H__
