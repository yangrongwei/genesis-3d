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

#ifndef __CONE_BUILDER_H__
#define __CONE_BUILDER_H__

#include "meshbuilder/meshbuilder.h"
#include "math/float3.h"

namespace MeshBuilder
{

#define CONE_VERTEX_COUNT(tessellation) tessellation + 2
#define CONE_INDEX_COUNT(tessellation) tessellation * 6//tessellation * 2 * 3;
	// 第一个顶点为底面圆心，第二个顶点为锥顶，后面的顶点为地面边缘顶点（如果中心点设在了坐标原点，则第一个顶点在x轴上，其余顺时针排列）。
	// 所谓tessellation，意思就是圆锥的底面的边缘的顶点个数
	class ConeBuilder
	{
	public:
		//tessellation下的顶点总数
		static SizeT VertexCount(SizeT tessellation);
		//tessellation下索引总数
		static SizeT IndexCount(SizeT tessellation);
		// set indices
		static void SetIndices(ushort* buffer, SizeT tessellation);
		// buffer: vertex buffer, vertexSize: a vertex element's size, posBias: the starting location(in bytes) of position data in a vertex element
		// tessellation: tessellation, r: the radius of bottom, topHeight: the cone's height, center: the centre of bottom
		template<typename T>
		static void SetPositions(T* buffer, SizeT vertexSize, SizeT posBias, SizeT tessellation, float r, float topHeight, const Math::float3& center);
		// buffer: vertex buffer, vertexSize: a vertex element's size, normalBias: the starting location(in bytes) of normal data in a vertex element
		// tessellation: tessellation
		// posBuffer: vertex buffer, posBufferVertexSize: a vertex element's size of posBuffer, posBias: the starting location(in bytes) of position data in a vertex element of posBuffer
		template<typename T1, typename T2>
		static void SetNormals(T1* buffer, SizeT vertexSize, SizeT normalBias, SizeT tessellation, const T2* posBuffer, SizeT posBufferVertexSize, SizeT posBias);

	private:
		static void setPositions(ubyte* buffer, SizeT vertexSize, SizeT posBias, SizeT tessellation, float r, float topHeight, const Math::float3& center);
		static void setNormals(ubyte* buffer, SizeT vertexSize, SizeT normalBias, SizeT tessellation, const ubyte* posBuffer, SizeT posBufferVertexSize, SizeT posBias);
		static void setCircleVector(float angle, Math::float3& dir);
		static void calBottomNormal(elem_iterator_const<Math::float3> begin, SizeT tessellation, Math::float3& bottomNormal);
		static void calBottomSidePosNormal(const Math::float3& curPos, const Math::float3& nextPos, const Math::float3& prePos, const Math::float3& topPos, const Math::float3& bottomNormal, Math::float3& normal);
		static void calNormal(const Math::float3& point0, const Math::float3& point1, const Math::float3& point2, Math::float3& normal);
		ConeBuilder();
	};

	template<typename T>
	inline void ConeBuilder::SetPositions(T* buffer, SizeT vertexSize, SizeT posBias, SizeT tessellation, float r, float topHeight, const Math::float3& center)
	{
		setPositions(reinterpret_cast<ubyte*>(buffer), vertexSize, posBias, tessellation, r, topHeight, center);
	}
	template<typename T1, typename T2>
	inline void ConeBuilder::SetNormals(T1* buffer, SizeT vertexSize, SizeT normalBias, SizeT tessellation, const T2* posBuffer, SizeT posBufferVertexSize, SizeT posBias)
	{
		setNormals(reinterpret_cast<ubyte*>(buffer),vertexSize,normalBias,tessellation,
					reinterpret_cast<const ubyte*>(posBuffer), posBufferVertexSize, posBias);
	}


	inline SizeT ConeBuilder::VertexCount(SizeT tessellation)
	{
		n_assert(tessellation > 2);
		return CONE_VERTEX_COUNT(tessellation);
	}

	inline SizeT ConeBuilder::IndexCount(SizeT tessellation)
	{
		n_assert(tessellation > 2);
		return CONE_INDEX_COUNT(tessellation);
	}
}
#endif //__CONE_BUILDER_H__
