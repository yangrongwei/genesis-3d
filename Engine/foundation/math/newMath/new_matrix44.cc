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
#include "math/matrix44.h"
#include "math/plane.h"
#include "math/quaternion.h"

namespace Math
{

//------------------------------------------------------------------------------
/**
*/
void
matrix44::decompose(float4& outScale, quaternion& outRotation, float4& outTranslation) const
{
	/*
    BOOL result = XMMatrixDecompose(&outScale.vec, 
                        &outRotation.vec, 
                        &outTranslation.vec, 
                        this->mx);
    n_assert(result);
	outScale.set_w(0.0f);
	outTranslation.set_w(0.0f);
	*/
	Ogre::Vector3 outS;
	Ogre::Quaternion outR;
	Ogre::Vector3 outT;
	this->mx.decomposition(outT,outS,outR);
	outScale.set(outS.x,outS.y,outS.z,0.0f);
	outTranslation.set(outT.x,outT.y,outT.z,0.f);
	outRotation.set(outR.x,outR.y,outR.z,outR.w);
}
//------------------------------------------------------------------------------
/**
*/
matrix44
matrix44::transformation(float4 const &scaling, const quaternion& rotation, float4 const &translation)
{
	Ogre::Matrix4 mat;
	mat.makeTransform(	Ogre::Vector3(translation.x(),translation.y(),translation.z()),
						Ogre::Vector3(scaling.x(),scaling.y(),scaling.z()),
						Ogre::Quaternion(rotation.vec) );
	return matrix44(mat);
	/*
    return XMMatrixTransformation(scalingCenter.vec,
                                  scalingRotation.vec,
                                  scaling.vec,
                                  rotationCenter.vec,
                                  rotation.vec,
                                  translation.vec);
	*/
}

//------------------------------------------------------------------------------
/**
*/
bool 
matrix44::ispointinside(const matrix44& m, const float4& p)
{
    float4 p1 = matrix44::transform(m, p);
    // vectorized compare operation
    return !(float4::less4_any(float4(p1.x(), p1.w(), p1.y(), p1.w()), 
             float4(-p1.w(), p1.x(), -p1.w(), p1.y()))
            ||
            float4::less4_any(float4(p1.z(), p1.w(), 0, 0), 
            float4(-p1.w(), p1.z(), 0, 0)));
}

//------------------------------------------------------------------------------
/**
*/
plane
matrix44::transform(const matrix44& m, const plane &p)
{
	return m.mx * p.vec;
}

matrix44
matrix44::rotationquaternion(const quaternion& q)
{
	return Ogre::Matrix4(q.vec);
}

quaternion 
matrix44::rotationmatrix(const matrix44& m)
{
	return m.mx.extractQuaternion();
}

} // namespace Math
