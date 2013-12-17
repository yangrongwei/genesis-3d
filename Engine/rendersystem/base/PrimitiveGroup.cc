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
#include "PrimitiveGroup.h"

namespace RenderBase
{
	__ImplementClass(PrimitiveGroup,'PGRS',RenderCommandType)

	PrimitiveGroup::PrimitiveGroup() :
	baseVertex(0),
		numVertices(0),
		baseIndex(0),
		numIndices(0),
		m_InstanceCount(0),
		primitiveTopology(PrimitiveTopology::InvalidPrimitiveTopology)
	{
		
	}
	
	PrimitiveGroup::~PrimitiveGroup()
	{
		Discard();
		// empty
	}

	void PrimitiveGroup::Discard()
	{
		baseVertex = 0;
		numVertices = 0;
		baseIndex = 0;
		numIndices = 0;

		m_vertexBuffer = NULL;
		m_indexBuffer = NULL;

		m_InstanceVBuffers.Clear();
	}

//------------------------------------------------------------------------------
/**
    Computes the number of primitives from a given primitive topology
    and number of vertices (the opposite of ComputeNumberOfVertices()).
*/

SizeT
PrimitiveGroup::NumberOfPrimitives(PrimitiveTopology::Code topology, SizeT numVertices) const
{
    switch (topology)
    {
        case PrimitiveTopology::PointList:     return numVertices;
        case PrimitiveTopology::LineList:      return numVertices / 2;
        case PrimitiveTopology::LineStrip:     return numVertices - 1;
        case PrimitiveTopology::TriangleList:  return numVertices / 3;
        case PrimitiveTopology::TriangleStrip: return numVertices - 2;

        default:
            n_error("PrimitiveTopology::NumberOfPrimitives(): invalid topology!");
            return InvalidIndex;
    }
}

//------------------------------------------------------------------------------
/**
    Computes the number of required vertices for a given primitive
    topology and number of primitives.
*/
SizeT
PrimitiveGroup::NumberOfVertices(PrimitiveTopology::Code topology, SizeT numPrimitives) const
{
    switch (topology)
    {
        case PrimitiveTopology::PointList:     return numPrimitives;
        case PrimitiveTopology::LineList:      return numPrimitives * 2;
        case PrimitiveTopology::LineStrip:     return numPrimitives + 1;
        case PrimitiveTopology::TriangleList:  return numPrimitives * 3;
        case PrimitiveTopology::TriangleStrip: return numPrimitives + 2;

        default:
            n_error("PrimitiveTopology::NumberOfVertices(): invalid topology!");
            return InvalidIndex;
    }
}

void PrimitiveGroup::OnDeviceLost()
{

}

void PrimitiveGroup::OnDeviceReset()
{

}

}