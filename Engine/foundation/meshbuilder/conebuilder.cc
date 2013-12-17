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
#include "conebuilder.h"

namespace MeshBuilder
{
	using namespace Math;
	void ConeBuilder::setCircleVector(float angle, float3& dir)
	{
		float dx = (float)n_cos(angle);
		float dz = (float)n_sin(angle);

		return dir.set(dx, 0.0f, dz);
	}

	void ConeBuilder::setPositions(ubyte* buffer, SizeT vertexSize, SizeT posBias, SizeT tessellation, float r, float topHeight, const Math::float3& center)
	{
		n_assert(tessellation > 2);
		n_assert(NULL != buffer);
		n_assert(posBias <= (vertexSize - (SizeT)sizeof(float3)));

		elem_iterator<float3> elem(buffer + posBias, vertexSize);	
		elem.set(center);//锥底圆心

		++elem;
		elem.set(center);
		elem->y() += topHeight;	//锥顶

		float x = N_PI_DOUBLE / (float)tessellation;
		float angle = 0;
		float3 normal;
		for (int i = 0; i < tessellation; ++i)		//底面边缘的顶点
		{
			angle = i * x;
			setCircleVector(angle, normal);
			++elem;
			elem.set(normal * r + center);
		}
	}

	void ConeBuilder::calNormal(const float3& point0, const float3& point1, const float3& point2, float3& normal)
	{
		float3 dir0 = point1 - point0;
		float3 dir1 = point2 - point0;
		normal = dir1.crossProduct(dir0);
		normal.normalise();
	}

	void ConeBuilder::calBottomNormal(elem_iterator_const<float3> begin, SizeT tessellation, float3& bottomNormal)
	{
		int temp = tessellation / 3;

		const float3* point0 = begin.get();
		const float3* point1 = begin.get(temp);
		const float3* point2 =  begin.get(temp * 2);		
		calNormal(*point0, *point1, *point2, bottomNormal);
	}

	void ConeBuilder::calBottomSidePosNormal(const Math::float3& curPos, const Math::float3& nextPos, const Math::float3& prePos, const Math::float3& topPos, const Math::float3& bottomNormal, Math::float3& normal)
	{
		float3 normal0;
		float3 normal1;
		calNormal(prePos, curPos, topPos, normal1);
		calNormal(curPos, nextPos, topPos, normal1);
		normal = normal0 + normal1 + bottomNormal;
		normal.normalise();
		
	}

	void ConeBuilder::setNormals(ubyte* buffer, SizeT vertexSize, SizeT normalBias, SizeT tessellation, const ubyte* posBuffer, SizeT posBufferVertexSize, SizeT posBias)
	{
		n_assert(tessellation > 2);
		elem_iterator<float3> norm_it(buffer + normalBias, vertexSize);
		elem_iterator_const<float3> pos_it(posBuffer + posBias, posBufferVertexSize);
		float3 bottom_normal;

		float3 center = *pos_it;
		++pos_it;
		float3 top = *pos_it;

		++pos_it;
		calBottomNormal(pos_it, tessellation, bottom_normal);
		norm_it.set(bottom_normal);		//第一个顶点的法线

		++norm_it;
		float3 bottom_to_top = top - center;
		bottom_to_top.normalise();
		norm_it.set(bottom_to_top);		//第二个顶点的法线

		++norm_it;
		for (int i = 0; i < tessellation; i++)
		{
			int pre_index = (i - 1 + tessellation) % tessellation;
			int next_index = (i + 1) % tessellation;
			const float3* next_pos = pos_it.get(next_index);
			const float3* pre_pos = pos_it.get(pre_index);
			calBottomSidePosNormal(*pos_it, *next_pos, *pre_pos, top, bottom_normal, *norm_it);
			
			++norm_it;
			++pos_it;
		}

	}

	void ConeBuilder::SetIndices(ushort* buffer, SizeT tessellation)
	{
		n_assert(tessellation > 2);
		n_assert(NULL != buffer);
		ushort* begin_buffer = buffer;
		for (int i = 0; i < tessellation; i++)
		{
			ushort index0 = i;
			ushort index1 = (index0 + 1) % tessellation;
			index0 += 2;
			index1 += 2;

			*begin_buffer = index0;
			++begin_buffer;
			*begin_buffer = index1;
			++begin_buffer;
			*begin_buffer = 0;
			++begin_buffer;

			*begin_buffer = index1;
			++begin_buffer;
			*begin_buffer = index0;
			++begin_buffer;
			*begin_buffer = 1;
			++begin_buffer;
		}
	}
}