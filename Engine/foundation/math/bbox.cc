/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#include "math/bbox.h"
#ifdef __OSX__
#include "../rendersystem/config/RenderDeviceConfig.h"
#else
#include "rendersystem/config/RenderDeviceConfig.h"
#endif
namespace Math
{

const bbox
bbox::Zero(point(0,0,0), point(0,0,0));

//------------------------------------------------------------------------------
/**
    Return box/box clip status.
*/
ClipStatus::Type
bbox::clipstatus(const bbox& other) const
{
    if (this->contains(other))
    {
        return ClipStatus::Inside;
    }
    else if (this->intersects(other))
    {
        return ClipStatus::Clipped;
    }
    else 
    {
        return ClipStatus::Outside;
    }
}

//------------------------------------------------------------------------------
/**
    Returns one of the 8 corners of the bounding box.
*/
point
bbox::corner_point(int index) const
{
    n_assert((index >= 0) && (index < 8));
    switch (index)
    {
        case 0:     return this->pmin;
        case 1:     return point(this->pmin.x(), this->pmax.y(), this->pmin.z());
        case 2:     return point(this->pmax.x(), this->pmax.y(), this->pmin.z());
        case 3:     return point(this->pmax.x(), this->pmin.y(), this->pmin.z());
        case 4:     return this->pmax;
        case 5:     return point(this->pmin.x(), this->pmax.y(), this->pmax.z());
        case 6:     return point(this->pmin.x(), this->pmin.y(), this->pmax.z());
        default:    return point(this->pmax.x(), this->pmin.y(), this->pmax.z());
    }    
}

//------------------------------------------------------------------------------
/**
    Get the bounding box's side planes in clip space.
*/
void
bbox::get_clipplanes(const matrix44& viewProj, Util::Array<plane>& outPlanes) const
{
    matrix44 inverseTranspose = matrix44::transpose(matrix44::inverse(viewProj));
    plane planes[6];
    planes[0].set(-1, 0, 0, +this->pmax.x());
    planes[1].set(+1, 0, 0, -this->pmin.x());
    planes[2].set(0, -1, 0, +this->pmax.y());
    planes[3].set(0, +1, 0, -this->pmin.y());
    planes[4].set(0, 0, -1, +this->pmax.z());
    planes[5].set(0, 0, +1, -this->pmin.z());
    IndexT i;
    for (i = 0; i < 6; i++)
    {
        outPlanes.Append(matrix44::transform(inverseTranspose,planes[i]));
    }
}

//------------------------------------------------------------------------------
/**
    Check for intersection with a view volume defined by a view-projection
    matrix.
*/
ClipStatus::Type
bbox::clipstatus(const matrix44& viewProjection) const
{
    // @todo: needs optimization!
    int andFlags = 0xffff;
    int orFlags  = 0;

    // corner points
    point p[8];
    p[0] = this->pmin;
    p[1].set(this->pmin.x(), this->pmin.y(), this->pmax.z());
    p[2].set(this->pmax.x(), this->pmin.y(), this->pmax.z());
    p[3].set(this->pmax.x(), this->pmin.y(), this->pmin.z());
    p[4].set(this->pmin.x(), this->pmax.y(), this->pmin.z());
    p[5].set(this->pmin.x(), this->pmax.y(), this->pmax.z());
    p[6].set(this->pmax.x(), this->pmax.y(), this->pmin.z());
    p[7] = this->pmax;
    
    // check each corner point
    float4 p1;
    IndexT i;
    for (i = 0; i < 8; i++)
    {
        int clip = 0;
        p1 = matrix44::transform(viewProjection,p[i]);

        // @todo: vectorize compare operation!
        if (p1.x() < -p1.w())       clip |= ClipLeft;
        if (p1.x() > p1.w())   clip |= ClipRight;
        if (p1.y() < -p1.w())       clip |= ClipBottom;
        if (p1.y() > p1.w())   clip |= ClipTop;
        if (p1.z() > p1.w())       clip |= ClipFar;

#if RENDERDEVICE_D3D9
		if (p1.z() < 0.0f)   clip |= ClipNear;

#endif

#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
		 if (p1.z() < -1.0f)   clip |= ClipNear;
#endif

       

        andFlags &= clip;
        orFlags  |= clip;
    }
    if (0 == orFlags)       return ClipStatus::Inside;
    else if (0 != andFlags) return ClipStatus::Outside;
    else                    return ClipStatus::Clipped;
}

//------------------------------------------------------------------------
// see <Geometric Tools for Computer Graphics> chinese version, P286 
scalar 
bbox::distancesq(const Math::vector &p) const
{
	// Transform p into box's coordinate frame
	Math::vector offset = p - this->center();
	// need not pPrime for axis aligned. pPrime = offset

	// project pPrime onto box
	scalar distanceSquared = 0.0f;
	scalar d = 0.0f;

	// extents is box.uHalf, box.vHalf box.wHalf
	Math::vector extents = this->extents();

	for (int i=0;i<3;++i)
	{
		if ( offset[i] < -extents[i] )
		{
			d = offset[i] + extents[i];
			distanceSquared += d * d;
			offset[i] = -extents[i];
		}
		else if ( offset[i] > extents[i] )
		{
			d = offset[i] - extents[i];
			distanceSquared += d * d;
			offset[i] = extents[i];
		}
	}

	return distanceSquared;
}

} // namespace Math