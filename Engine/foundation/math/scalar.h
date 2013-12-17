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
#pragma once
//------------------------------------------------------------------------------
/**
    @file math/scalar.h

    Nebula's scalar datatype.

    NOTE: do not add CRT math function calls to this call, but instead
    into the platform specific headers (for instance, on the Wii the sinf()
    functions are called and must be placed into a .cc file, not into the
    header.
*/

#if __WIN32__ || __XBOX360__ || __ANDROID__ || __OSX__
#include "math/newMath/new_scalar.h"
#elif __WII__
#include "math/wii/wii_scalar.h"
#elif __PS3__
#include "math/ps3/ps3scalar.h"
#else
#error "scalar class not implemented!"
#endif

// common platform-agnostic definitions
namespace Math
{
#ifndef PI
#define PI (3.1415926535897932384626433832795028841971693993751)
#endif

// the half circle
#ifndef N_PI
#define N_PI (Math::scalar(PI))
#endif
// the whole circle
#ifndef N_PI_DOUBLE
#define N_PI_DOUBLE (Math::scalar(6.283185307179586476925286766559))
#endif
// a quarter circle
#ifndef N_PI_HALF
#define N_PI_HALF (Math::scalar(1.5707963267948966192313216916398f))
#endif
// ---HOTFIXED

#ifndef TINY
#define TINY (0.0000001f)
#endif
#define N_TINY TINY

const Math::scalar N_INFINITY = 1e38f;

#define N_FLOAT32_MAX 3.402823E+38f

#define N_FLOAT32_MIN -3.402823E+38f



//------------------------------------------------------------------------------
/**
    A fuzzy floating point equality check
*/
__forceinline bool
n_fequal(scalar f0, scalar f1, scalar tol)
{
    scalar f = f0 - f1;
    return ((f > (-tol)) && (f < tol));
}


__forceinline uint n_upper_power_of_two(uint val)
{
	--val;
	val |= val >> 16;
	val |= val >> 8;
	val |= val >> 4;
	val |= val >> 2;
	val |= val >> 1;
	++val;
	return val;
}




#if !SPU
//------------------------------------------------------------------------
template<typename T>
T n_max(T a, T b)
{
	return (a > b) ? a : b;
}
//------------------------------------------------------------------------
template<typename T>
T n_min(T a, T b)
{
	 return (a < b) ? a : b;
}
//------------------------------------------------------------------------
template<typename T>
T n_abs(T a)
{
	return (a < 0.0f) ? -a : a;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
n_sgn(scalar a)
{
    return (a < 0.0f) ? -1.0f : 1.0f;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
n_deg2rad(scalar d)
{
    return (scalar)((d * PI) / 180.0f);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
n_rad2deg(scalar r)
{
    return (scalar)((r * 180.0f) / PI);
}

//------------------------------------------------------------------------------
/**
    Integer clamping.
*/
__forceinline int
n_iclamp(int val, int minVal, int maxVal)
{
    if (val < minVal)      return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}

//------------------------------------------------------------------------------
/**
    A fuzzy floating point less-then check.
*/
__forceinline bool
n_fless(scalar f0, scalar f1, scalar tol)
{
    return ((f0 - f1) < tol);
}

//------------------------------------------------------------------------------
/**
    A fuzzy floating point greater-then check.
*/
__forceinline bool
n_fgreater(scalar f0, scalar f1, scalar tol)
{
    return ((f0 - f1) > tol);
}

//------------------------------------------------------------------------------
/**
    Clamp a value against lower und upper boundary.
*/
__forceinline scalar
n_clamp(scalar val, scalar lower, scalar upper)
{
    if (val < lower)      return lower;
    else if (val > upper) return upper;
    else                  return val;
}

//------------------------------------------------------------------------------
/**
Clamp a value against lower und upper boundary (integer version).
*/
__forceinline int
n_clamp(int val, int lower, int upper)
{
	if (val < lower)      return lower;
	else if (val > upper) return upper;
	else                  return val;
}


//------------------------------------------------------------------------------
/**
    Saturate a value (clamps between 0.0f and 1.0f)
*/
__forceinline scalar
n_saturate(scalar val)
{
    if (val < 0.0f)      return 0.0f;
    else if (val > 1.0f) return 1.0f;
    else return val;
}

//------------------------------------------------------------------------------
/**
Saturate a value (clamps between 0.0f and 1.0f)
*/
__forceinline double
n_saturate(double val)
{
    if (val < 0.0)      return 0.0;
    else if (val > 1.0) return 1.0;
    else return val;
}

//------------------------------------------------------------------------------
/**
    Linearly interpolate between 2 values: ret = x + l * (y - x)
*/
__forceinline scalar
n_lerp(scalar x, scalar y, scalar l)
{
    return x + l * (y - x);
}

//------------------------------------------------------------------------------
/**
    Linearly interpolate between 2 values: ret = x + l * (y - x)
*/
__forceinline double
n_lerp(double x, double y, double l)
{
    return x + l * (y - x);
}

//------------------------------------------------------------------------------
/**
    Returns true if the input scalar is denormalized (#DEN)
*/
__forceinline bool
n_isdenormal(scalar s)
{
#if __GNUC__
    union { scalar s; uint u; } pun;
    pun.s = s;
    return ((pun.u&0x7f800000)==0);
#else
    return (((*(uint*)&s)&0x7f800000)==0);
#endif
}

//------------------------------------------------------------------------------
/**
    Returns 0 if scalar is denormal.
*/
__forceinline float
n_undenormalize(scalar s)
{
    if (n_isdenormal(s))
    {
        return 0.0f;
    }
    else
    {
        return s;
    }
}

//------------------------------------------------------------------------------
/**
    test of nearly equal given a tolerance (epsilon)
*/
__forceinline bool
n_nearequal(scalar a, scalar b, scalar epsilon)
{
    return n_abs(a - b) <= epsilon;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
n_cot(scalar x)
{
    return scalar(1.0) / n_tan(x);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
n_smoothstep(scalar edge0, scalar edge1, scalar x)
{
    // Scale, bias and saturate x to 0..1 range
    x = n_saturate((x - edge0) / (edge1 - edge0)); 
    // Evaluate polynomial
    return x*x*(3-2*x);     
}

//------------------------------------------------------------------------
/**
*/
__forceinline bool
n_isNaN(scalar f)
{
	// from Ogre;
	// std::isnan() is C99, not supported by all compilers
	// However NaN always fails this next test, no other number does.
	return f != f;
}
//------------------------------------------------------------------------
/// [0,0f 1.0f] -> [0,255]
__forceinline 
ubyte
n_scalartoByte(scalar f)
{
	f = n_max( f, 0.0F);
	f = n_min( f, 1.0F);
	return ubyte(f*255.0f);
}
//------------------------------------------------------------------------
//[0,255]->[0,0f 1.0f]
__forceinline 
scalar
n_scalarfromByte(ubyte u)
{
	return (scalar)u / 255.0F;
}

#endif // #if !SPU

} // namespace Math
//------------------------------------------------------------------------------
