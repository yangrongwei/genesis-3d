/****************************************************************************
Copyright (c) 2007,RadonLabs GmbH
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
#include "math/line.h"
#include "math/scalar.h"

namespace Math
{

//------------------------------------------------------------------------------
/**
    Get line/line intersection. Returns the shortest line between two lines.

    @todo: Untested! Replace with simpler code.
*/
bool
line::intersect(const line& l, point& pa, point& pb) const
{
    const scalar EPS = 2.22e-16f;
    point p1 = this->b;
    point p2 = this->pointat(10.0f);
    point p3 = l.b;
    point p4 = l.pointat(10.0f);

    vector p13 = p1 - p3;
    vector p43 = p4 - p3;
    vector p21 = p2 - p1;
    if (p43.lengthsq() < EPS) return false;
    if (p21.lengthsq() < EPS) return false;

    scalar d1343 = float4::dot3(p13, p43);
    scalar d4321 = float4::dot3(p43, p21);
    scalar d1321 = float4::dot3(p13, p21);
    scalar d4343 = float4::dot3(p43, p43);
    scalar d2121 = float4::dot3(p21, p21);

    scalar denom = d2121 * d4343 - d4321 * d4321;
    if (n_abs(denom) < EPS) return false;
    scalar numer = d1343 * d4321 - d1321 * d4343;

    scalar mua = numer / denom;
    scalar mub = (d1343 + d4321 * (mua)) / d4343;

    pa = p1 + p21 * mua;
    pb = p3 + p43 * mub;

    return true;
}

} // namespace Math