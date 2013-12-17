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

#ifndef __BOX_BUILDER_H__
#define __BOX_BUILDER_H__

#include "meshbuilder/meshbuilder.h"
#include "math/float3.h"

namespace MeshBuilder
{
#define BOX_VERTEX_COUNT 8
#define BOX_INDICES_COUNT 36

	// ======== 顶点分布 ================
	// ---- font  ------ back  ---------
	// ---- 0 - 1 ------ 4 - 5 --------
	// ---- | / | ------ | / | ---------
	// ---- 2 - 3 ------ 6 - 7 --------
	// ------------ 展开 ---------------
	// ------------ 4 - 5 -------------
	// ------------ | / | --------------
	// -------- 4 - 0 - 1 - 5 - 4 -----
	// -------- | / | / | / | / | ------
	// -------- 6 - 2 - 3 - 7 - 6 -----
	// ------------ | / | --------------
	// ------------ 6 - 7 -------------
	// indices: font,back,top,bottom,left,right
	// indices: {0,2,1; 1,2,3} {5,7,4; 4,7,6} {4,0,5; 5,0,1} {2,6,3; 3,6,7} {4,6,0; 0,6,2} {1,3,5; 5,3,7}
	// postion :float3 , normal : float3
	class BoxBuilder
	{
	public:
		// the vertex count in a rect
		static SizeT VertexCount();

		// the index count in a rect
		static SizeT IndexCount();

		// buffer: vertex buffer, vertexSize: a vertex element's size, posBias: the starting location(in bytes) of position data in a vertex element
		// sideX: the side in x coord, sideY: the side in y coord, sideZ: the side in z coord, center: the center of the box
		template<typename T>
		static void SetPositions(T* buffer, SizeT vertexSize, SizeT posBias, float sideX, float sideY, float sideZ, const Math::float3& center);

		// buffer: vertex buffer, vertexSize: a vertex element's size, normalBias: the starting location(in bytes) of normal data in a vertex element
		// posBuffer: vertex buffer, posBufferVertexSize: a vertex element's size of posBuffer, posBias: the starting location(in bytes) of position data in a vertex element of posBuffer
		template<typename T1, typename T2>
		static void SetNormals(T1* buffer, SizeT vertexSize, SizeT normalBias, const T2* posBuffer, SizeT posBufferVertexSize, SizeT posBias);

		// set indices
		static void SetIndices(ushort* buffer);

	private:
		static void setPositions(ubyte* buffer, SizeT vertexSize, SizeT posBias, float sideX, float sideY, float sideZ, const Math::float3& center);
		static void setNormals(ubyte* buffer, SizeT vertexSize, SizeT normalBias, const ubyte* posBuffer, SizeT posBufferVertexSize, SizeT posBias);

		BoxBuilder(){}
	};

	inline SizeT BoxBuilder::VertexCount()
	{
		return BOX_VERTEX_COUNT;
	}

	inline SizeT BoxBuilder::IndexCount()
	{
		return BOX_INDICES_COUNT;
	}

	template<typename T>
	inline void BoxBuilder::SetPositions(T* buffer, SizeT vertexSize, SizeT posBias, float sideX, float sideY, float sideZ, const Math::float3& center)
	{
		setPositions(reinterpret_cast<ubyte*>(buffer), vertexSize, posBias, sideX, sideY, sideZ, center);
	}

	template<typename T1, typename T2>
	inline void BoxBuilder::SetNormals(T1* buffer, SizeT vertexSize, SizeT normalBias, const T2* posBuffer, SizeT posBufferVertexSize, SizeT posBias)
	{
		setNormals(reinterpret_cast<ubyte*>(buffer), vertexSize, normalBias, reinterpret_cast<const ubyte*>(posBuffer), posBufferVertexSize, posBias);
	}
}

#endif //__BOX_BUILDER_H__
