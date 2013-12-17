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
#include "boxbuilder.h"

namespace MeshBuilder
{
	using namespace Math;

	void BoxBuilder::setPositions(ubyte* buffer, SizeT vertexSize, SizeT posBias, float sideX, float sideY, float sideZ, const float3& center)
	{
		n_assert(NULL != buffer);
		n_assert(posBias <= (vertexSize - (SizeT)sizeof(float3)));

		float half_x = sideX * 0.5f;
		float half_y = sideY * 0.5f;
		float half_z = sideZ * 0.5f;

		elem_iterator<float3> elem(buffer + posBias, vertexSize);

		elem->set(center.x()-half_x, center.y()+half_y, center.z()+half_z);
		++elem;
		elem->set(center.x()+half_x, center.y()+half_y, center.z()+half_z);
		++elem;
		elem->set(center.x()-half_x, center.y()-half_y, center.z()+half_z);
		++elem;
		elem->set(center.x()+half_x, center.y()-half_y, center.z()+half_z);
		++elem;
		elem->set(center.x()-half_x, center.y()+half_y, center.z()-half_z);
		++elem;
		elem->set(center.x()+half_x, center.y()+half_y, center.z()-half_z);
		++elem;
		elem->set(center.x()-half_x, center.y()-half_y, center.z()-half_z);
		++elem;
		elem->set(center.x()+half_x, center.y()-half_y, center.z()-half_z);
	}
	void setNormal(elem_iterator<float3>& norm_it, const elem_iterator_const<float3>& pos_it, int index_0, int index_1)
	{
		const float3* point0 = pos_it.get(index_0);
		const float3* point1 = pos_it.get(index_1);
		float3 normal = *point0 - *point1;
		normal.normalise();
		*norm_it.get(index_0) = normal;
		*norm_it.get(index_1) = - normal;
	}
	void BoxBuilder::setNormals(ubyte* buffer, SizeT vertexSize, SizeT normalBias, const ubyte* posBuffer, SizeT posBufferVertexSize, SizeT posBias)
	{
		elem_iterator<float3> norm_it(buffer + normalBias, vertexSize);
		elem_iterator_const<float3> pos_it(posBuffer + posBias, posBufferVertexSize);
		setNormal(norm_it, pos_it, 0, 7);
		setNormal(norm_it, pos_it, 1, 6);
		setNormal(norm_it, pos_it, 2, 5);
		setNormal(norm_it, pos_it, 3, 4);

	}

	void BoxBuilder::SetIndices(ushort* buffer)
	{
		// indices: {0,2,1; 1,2,3} {5,7,4; 4,7,6} {4,0,5; 5,0,1} {2,6,3; 3,6,7} {4,6,0; 0,6,2} {1,3,5; 5,3,7}
		n_assert(NULL != buffer);
		buffer[0] = 0;
		buffer[1] = 2;
		buffer[2] = 1;
		buffer[3] = 1;
		buffer[4] = 2;
		buffer[5] = 3;

		buffer[6] = 5;
		buffer[7] = 7;
		buffer[8] = 4;
		buffer[9] = 4;
		buffer[10] = 7;
		buffer[11] = 6;

		buffer[12] = 4;
		buffer[13] = 0;
		buffer[14] = 5;
		buffer[15] = 5;
		buffer[16] = 0;
		buffer[17] = 1;

		buffer[18] = 2;
		buffer[19] = 6;
		buffer[20] = 3;
		buffer[21] = 3;
		buffer[22] = 6;
		buffer[23] = 7;

		buffer[24] = 4;
		buffer[25] = 6;
		buffer[26] = 0;
		buffer[27] = 0;
		buffer[28] = 6;
		buffer[29] = 2;

		buffer[30] = 1;
		buffer[31] = 3;
		buffer[32] = 5;
		buffer[33] = 5;
		buffer[34] = 3;
		buffer[35] = 7;
	}
}
