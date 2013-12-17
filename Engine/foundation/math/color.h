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

#ifndef __color_H__
#define __color_H__

#include "math/scalar.h"
#include "rendersystem/config/RenderDeviceConfig.h"

namespace Math
{

typedef uint32 RGBA;
class Color32;

class ColorF
{
public:
	ColorF ();
	ColorF (scalar red, scalar green, scalar blue, scalar alpha = 1.0F);
	ColorF (const Color32& color);

	scalar operator [] ( const IndexT i ) const;
	scalar& operator [] ( const IndexT i );

public:
	scalar	r, g, b, a;
};

class Color32
{
public:
	Color32 ();						
	Color32 (ubyte red, ubyte green, ubyte blue, ubyte alpha);
	Color32 (RGBA color); 

	ubyte operator [] ( const IndexT i ) const;
	ubyte& operator [] ( const IndexT i );

	void Set(const Color32& color);

	ubyte* Ptr();	

	uint ToUInt() const; 
	
	uint HexARGB() const; 
public:
	ubyte	r, g, b, a;
};

//------------------------------------------------------------------------
inline
ColorF::ColorF ()
{
}
//------------------------------------------------------------------------
inline 
ColorF::ColorF (scalar red, scalar green, scalar blue, scalar alpha) 
: r(red), g(green), b(blue), a(alpha) 
{
}
//------------------------------------------------------------------------
inline
ColorF::ColorF (const Color32& color)
{
	this->r = n_scalarfromByte(color.r);
	this->g = n_scalarfromByte(color.g);
	this->b = n_scalarfromByte(color.b); 
	this->a = n_scalarfromByte(color.a);
}
//------------------------------------------------------------------------
inline
scalar 
ColorF::operator [] ( const IndexT i ) const
{
	n_assert( i < 4 );
	return *(&r+i);
}
//------------------------------------------------------------------------
inline 
scalar& 
ColorF::operator [] ( const IndexT i )
{
	n_assert( i < 4 );
	return *(&r+i);
}
//------------------------------------------------------------------------
inline
Color32::Color32 ()	
{
}
//------------------------------------------------------------------------
inline
Color32::Color32 (ubyte red, ubyte green, ubyte blue, ubyte alpha)
: r(red), g(green), b(blue), a(alpha) 
{ 
}
////------------------------------------------------------------------------
inline
Color32::Color32 (RGBA color)						
{
	*(uint*)this = color;
}
//------------------------------------------------------------------------
inline 
ubyte 
Color32::operator [] ( const IndexT i ) const
{
	n_assert( i < 4 );
	return *(&r+i);
}
//------------------------------------------------------------------------
inline
ubyte&
Color32::operator [] ( const IndexT i )
{
	n_assert( i < 4 );
	return *(&r+i);
}
//------------------------------------------------------------------------
inline 
void 
Color32::Set(const Color32& color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}
//------------------------------------------------------------------------
inline
ubyte* 
Color32::Ptr ()		
{
	return &r;
}
//------------------------------------------------------------------------
inline
uint 
Color32::ToUInt() const 
{
	return *((uint*)(&r));
}
//------------------------------------------------------------------------
inline
uint 
Color32::HexARGB() const
{
	uint R = r;
	uint G = g;
	uint B = b;
	uint A = a;

#if RENDERDEVICE_D3D9
	return N_ARGB(A,R,G,B);
#elif RENDERDEVICE_OPENGLES
	return N_ARGB(A,B,G,R);
#endif
	
}


}	//	namespace Math




#endif // __color_H__
