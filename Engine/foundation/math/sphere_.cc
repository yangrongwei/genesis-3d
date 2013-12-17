/****************************************************************************
Copyright (c) 2004, Radon Labs GmbH
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
#include "math/sphere_.h" // avoid confilct with ODE sphere.h

namespace Math
{

//------------------------------------------------------------------------------
/**
    Check if sphere intersects with box.
    Taken from "Simple Intersection Tests For Games",
    Gamasutra, Oct 18 1999
*/
bool
sphere::intersects(const bbox& box) const
{
    n_error("sphere::intersects(): NOT IMPLEMENTED!");
    return false;
/*
    float s, d = 0;

    // find the square of the distance
    // from the sphere to the box,
    if (p.x < box.vmin.x)
    {
        s = p.x - box.vmin.x;
        d += s*s;
    }
    else if (p.x > box.vmax.x)
    {
        s = p.x - box.vmax.x;
        d += s*s;
    }

    if (p.y < box.vmin.y)
    {
        s = p.y - box.vmin.y;
        d += s*s;
    }
    else if (p.y > box.vmax.y)
    {
        s = p.y - box.vmax.y;
        d += s*s;
    }

    if (p.z < box.vmin.z)
    {
        s = p.z - box.vmin.z;
        d += s*s;
    }
    else if (p.z > box.vmax.z)
    {
        s = p.z - box.vmax.z;
        d += s*s;
    }

    return d <= r*r;
*/
}

//------------------------------------------------------------------------------
/**
    Check if 2 moving spheres have contact.
    Taken from "Simple Intersection Tests For Games"
    article in Gamasutra, Oct 18 1999

    @param  va  [in] distance travelled by 'this'
    @param  sb  [in] the other sphere
    @param  vb  [in] distance travelled by sb
    @param  u0  [out] normalized intro contact
    @param  u1  [out] normalized outro contact
*/
bool
sphere::intersect_sweep(const vector& va, const sphere&  sb, const vector& vb, float& u0, float& u1) const
{
    n_error("sphere::intersect_sweep(): NOT IMPLEMENTED!");
    return false;
    
/*
    vector3 vab(vb - va);
    vector3 ab(sb.p - p);
    float rab = r + sb.r;

    // check if spheres are currently overlapping...
    if ((ab % ab) <= (rab * rab)) 
    {
        u0 = 0.0f;
        u1 = 0.0f;
        return true;
    } 
    else 
    {
        // check if they hit each other
        float a = vab % vab;
        if ((a < -TINY) || (a > +TINY)) 
        {
            // if a is '0' then the objects don't move relative to each other
            float b = (vab % ab) * 2.0f;
            float c = (ab % ab) - (rab * rab);
            float q = b*b - 4*a*c;
            if (q >= 0.0f) 
            {
                // 1 or 2 contacts
                float sq = (float) sqrt(q);
                float d  = 1.0f / (2.0f*a);
                float r1 = (-b + sq) * d;
                float r2 = (-b - sq) * d;
                if (r1 < r2) 
                {
                    u0 = r1;
                    u1 = r2;
                } 
                else 
                {
                    u0 = r2;
                    u1 = r1;
                }
                return true;
            } 
            else 
            {
                return false;
            }
        } 
        else 
        {
            return false;
        }
    }
*/
}

//------------------------------------------------------------------------------
/**
    Project the sphere (defined in global space) to a screen space rectangle, 
    given the current View and Projection matrices. The method assumes that
    the sphere is at least partially visible.
*/
rectangle<scalar>
sphere::project_screen_rh(const matrix44& view, const matrix44& projection, float nearZ) const
{
    n_error("sphere::project_screen_rh(): NOT IMPLEMENTED!");
    return rectangle<scalar>(0, 0, 0, 0);
/*
    // compute center point of the sphere in view space
    vector3 viewPos = view * this->p;
    if (viewPos.z > -nearZ)
    {
        viewPos.z = -nearZ;
    }
    vector3 screenPos  = projection.mult_divw(viewPos);
    screenPos.y = -screenPos.y;

    // compute size of sphere at its front size
    float frontZ = viewPos.z + this->r;
    if (frontZ > -nearZ)
    {
        frontZ = -nearZ;
    }
    vector3 screenSize = projection.mult_divw(vector3(this->r, this->r, frontZ));
    screenSize.y = -screenSize.y;        
    float left   = n_saturate(0.5f * (1.0f + (screenPos.x - screenSize.x)));
    float right  = n_saturate(0.5f * (1.0f + (screenPos.x + screenSize.x)));
    float top    = n_saturate(0.5f * (1.0f + (screenPos.y + screenSize.y)));
    float bottom = n_saturate(0.5f * (1.0f + (screenPos.y - screenSize.y)));

    return rectangle(vector2(left, top), vector2(right, bottom));
*/
}

//------------------------------------------------------------------------------
/**
*/
void sphere::transform(const matrix44& m)
{
	p = matrix44::transform(m, p);
	float num4 = ((m.mx[0][0] * m.mx[0][0]) + (m.mx[1][0] * m.mx[1][0])) + (m.mx[2][0] * m.mx[2][0]);
	float num3 = ((m.mx[0][1] * m.mx[0][1]) + (m.mx[1][1] * m.mx[1][1])) + (m.mx[2][1] * m.mx[2][1]);
	float num2 = ((m.mx[0][2] * m.mx[0][2]) + (m.mx[1][2] * m.mx[1][2])) + (m.mx[2][2] * m.mx[2][2]);
	float num = n_max(num4, n_max(num3, num2));
	r = r * ((float)n_sqrt(num));
}

} // namespace Math
