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

#include "core/types.h"
#include "math/scalar.h"
#include "math/float4.h"
#include "math/plane.h"
#include "math/quaternion.h"
#include "math/OgreMath/OgreMatrix4.h"
#include "../rendersystem/config/RenderDeviceConfig.h"

//------------------------------------------------------------------------------
namespace Math
{
class quaternion;
class plane;
// could not get the compiler to really pass it in registers for xbox, so
// this is a reference so far
typedef const matrix44& __Matrix44Arg;

 
class matrix44
{
public:
    /// default constructor, NOTE: does NOT setup components!
    matrix44();
    /// construct from components
    matrix44(float4 const &row0, float4 const &row1, float4 const &row2, float4 const &row3);
    /// copy constructor
    //matrix44(const matrix44& rhs);
    /// construct from Ogre::Matrix4
	matrix44(const Ogre::Matrix4& rhs);
    
    /// assignment operator
    void operator=(const matrix44& rhs);
    /// assign Ogre::Matrix4
	void operator=(const Ogre::Matrix4& rhs);
    /// equality operator
    bool operator==(const matrix44& rhs) const;
    /// inequality operator
    bool operator!=(const matrix44& rhs) const;
	/// get value operator
	float*	operator[](SizeT iRow);
	/// get const value operator
	const float* const operator[](SizeT iRow) const;

	/// load content from unaligned memory
	void loadu(const scalar* ptr);
	/// write content to unaligned memory through the write cache
	void storeu(scalar* ptr) const;
    /// stream content to 16-byte-aligned memory circumventing the write-cache
    void stream(scalar* ptr) const;

    /// set content
    void set(float4 const &row0, float4 const &row1, float4 const &row2, float4 const &row3);
    /// write access to x component
    void setrow0(float4 const &row0);
    /// write access to y component
    void setrow1(float4 const &row1);
    /// write access to z component
    void setrow2(float4 const &row2);
    /// write access to w component
    void setrow3(float4 const &row3);
	/// wrtie access to specified component
	void setrowcol(const float& val, const int& row,const int& col);
    /// read-only access to x component
    const float4 getrow0() const;
    /// read-only access to y component
    const float4 getrow1() const;
    /// read-only access to z component
    const float4 getrow2() const;
    /// read-only access to w component
    const float4 getrow3() const;

    /// write access to x component
    void set_xaxis(float4 const &x);
    /// write access to y component
    void set_yaxis(float4 const &y);
    /// write access to z component
    void set_zaxis(float4 const &z);
    /// write access to w component / pos component
    void set_position(float4 const &pos);
    /// read access to x component
    const float4 get_xaxis() const;
    /// read access to y component
    const float4 get_yaxis() const;
    /// read access to z component
    const float4 get_zaxis() const;
    /// read access to w component / pos component
    const float4 get_position() const;
    /// add a translation to pos_component
    void translate(float4 const &t);
    /// scale matrix
    void scale(float4 const &v);

    /// return true if matrix is identity
    bool isidentity() const;
    /// decompose into scale, rotation and translation
    /// !!! Note: 
    void decompose(float4& outScale, quaternion& outRotation, float4& outTranslation) const;

	float determinant() const;

	void print() const;

	/// build zero matrix
	static matrix44 zero();
    /// build identity matrix
    static matrix44 identity();
	/// compute the inverse of a matrix
    static matrix44 inverse(const matrix44& m);
    /// build right handed lookat matrix
    static matrix44 lookatrh(float4 const &eye, float4 const &at, float4 const &up);
    /// multiply 2 matrices
    static matrix44 multiply(const matrix44& m0, const matrix44& m1);
    /// build right handed orthogonal projection matrix
    static matrix44 orthorh(scalar w, scalar h, scalar zn, scalar zf);
	/// build right handed orthogonal projection matrix not at specific center
	static matrix44 orthooffcenterrh(scalar l, scalar r, scalar b, scalar t, scalar zn, scalar zf);
    /// build right-handed perspective projection matrix based on field-of-view
    static matrix44 perspfovrh(scalar fovy, scalar aspect, scalar zn, scalar zf);
	/// build reflect matrix from a plane
	static matrix44 reflect(const float4& p);
    /// build rotation matrix around arbitrary axis
    static matrix44 rotationaxis(float4 const &axis, scalar angle);
    /// build x-axis-rotation matrix
    static matrix44 rotationx(scalar angle);
    /// build y-axis-rotation matrix
    static matrix44 rotationy(scalar angle);
    /// build z-axis-rotation matrix
    static matrix44 rotationz(scalar angle);
    /// build rotation matrix from yaw, pitch and roll
    static matrix44 rotationyawpitchroll(scalar yaw, scalar pitch, scalar roll);
	/// build rotation matrix from quaternion
	static matrix44 rotationquaternion(const quaternion& q);
	/// make quaternion from matrix44
	static quaternion rotationmatrix(const matrix44& m);
    /// build a scaling matrix from components
    static matrix44 scaling(scalar sx, scalar sy, scalar sz);
    /// build a scaling matrix from float4
    static matrix44 scaling(float4 const &s);
    /// build a transformation matrix
    static matrix44 transformation(float4 const &scaling,const quaternion& rotation, float4 const &translation);
    /// build a translation matrix
    static matrix44 translation(scalar x, scalar y, scalar z);
    /// build a translation matrix from point
    static matrix44 translation(float4 const &t);
    /// return the transpose of a matrix
    static matrix44 transpose(const matrix44& m);
    /// transform 4d vector by matrix44, faster inline version than float4::transform
    static float4 transform(const matrix44 &m, const float4 &v);
    /// transform a plane with a matrix
    static plane transform(const matrix44& m, const plane& p);
    /// check if point lies inside matrix frustum
    static bool ispointinside(const matrix44& m, const float4& p);
    /// convert to any type
    template<typename T> T as() const;


	Ogre::Matrix4 mx;
private:
    friend class float4;
    friend class plane;
    friend class quaternion;

};

//------------------------------------------------------------------------------
/**
*/
__forceinline
matrix44::matrix44():
mx(Ogre::Matrix4::IDENTITY)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
matrix44::matrix44(float4 const &row0, float4 const &row1, float4 const &row2, float4 const &row3)
{
	this->mx = Ogre::Matrix4(	row0.vec.x,row0.vec.y,row0.vec.z,row0.vec.w,
								row1.vec.x,row1.vec.y,row1.vec.z,row1.vec.w,
								row2.vec.x,row2.vec.y,row2.vec.z,row2.vec.w,
								row3.vec.x,row3.vec.y,row3.vec.z,row3.vec.w		);
}


//------------------------------------------------------------------------------
/**
*/
__forceinline
matrix44::matrix44(const Ogre::Matrix4& rhs) :
    mx(rhs)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::operator=(const matrix44& rhs)
{
    this->mx = rhs.mx;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::operator=(const Ogre::Matrix4& rhs)
{
    this->mx = rhs;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
matrix44::operator==(const matrix44& rhs) const
{
	return this->mx == rhs.mx; 
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
matrix44::operator!=(const matrix44& rhs) const
{
	return this->mx != rhs.mx; 
}
//------------------------------------------------------------------------------
/**
*/
__forceinline float* 
matrix44::operator[]( SizeT iRow )
{
	return this->mx[iRow];
}
//------------------------------------------------------------------------------
/**
*/
__forceinline const float* const
matrix44::operator[]( SizeT iRow ) const
{
	return this->mx[iRow];
}
//------------------------------------------------------------------------------
/**
*/
__forceinline float
matrix44::determinant() const
{
	return mx.determinant();
}
//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::loadu(const scalar* ptr)
{
	memcpy((void*)&this->mx,ptr,sizeof(matrix44));
}
//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::storeu(scalar* ptr) const
{
	memcpy(ptr,(void*)&this->mx,sizeof(matrix44));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::stream(scalar* ptr) const
{
	memcpy(ptr,(void*)&this->mx,sizeof(matrix44));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::set(float4 const &row0, float4 const &row1, float4 const &row2, float4 const &row3)
{
	this->mx = Ogre::Matrix4(	row0.vec.x,row0.vec.y,row0.vec.z,row0.vec.w,
		row1.vec.x,row1.vec.y,row1.vec.z,row1.vec.w,
		row2.vec.x,row2.vec.y,row2.vec.z,row2.vec.w,
		row3.vec.x,row3.vec.y,row3.vec.z,row3.vec.w		);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::setrow0(float4 const &r)
{
    this->mx.setRow(0,r.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::getrow0() const
{
	
	return this->mx.getRow(0);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::setrow1(float4 const &r)
{
    this->mx.setRow(1,r.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::getrow1() const
{
    return float4(mx.getRow(1));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::setrow2(float4 const &r)
{
    this->mx.setRow(2,r.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::getrow2() const
{
    return float4(mx.getRow(2));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::setrow3(float4 const &r)
{
    this->mx.setRow(3,r.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::getrow3() const
{
    return float4(mx.getRow(3));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void 
matrix44::setrowcol(const float& val, const int& row,const int& col)
{
	mx[row][col] = val;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::set_xaxis(float4 const &x)
{
	Ogre::Vector4 colVec = this->mx.getCol(0);
	colVec.x = x.vec.x;
	colVec.y = x.vec.y;
	colVec.z = x.vec.z;
	this->mx.setCol(0,colVec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::set_yaxis(float4 const &y)
{
	Ogre::Vector4 colVec = this->mx.getCol(1);
	colVec.x = y.vec.x;
	colVec.y = y.vec.y;
	colVec.z = y.vec.z;
	this->mx.setCol(1,colVec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::set_zaxis(float4 const &z)
{
	Ogre::Vector4 colVec = this->mx.getCol(2);
	colVec.x = z.vec.x;
	colVec.y = z.vec.y;
	colVec.z = z.vec.z;
	this->mx.setCol(2,colVec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::set_position(float4 const &pos)
{
	Ogre::Vector4 colVec = this->mx.getCol(3);
	colVec.x = pos.vec.x;
	colVec.y = pos.vec.y;
	colVec.z = pos.vec.z;
	this->mx.setCol(3,colVec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::get_xaxis() const
{
    return float4(this->mx.getCol(0));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::get_yaxis() const
{
    return float4(this->mx.getCol(1));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::get_zaxis() const
{
    return float4(this->mx.getCol(2));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline const float4
matrix44::get_position() const
{
    return float4(this->mx.getCol(3));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
void 
matrix44::translate(float4 const &t)
{
    #if _DEBUG
    n_assert2(t.w() == 0, "w component not 0, use vector for translation not a point!");
    #endif

	this->mx.setCol(3,this->mx.getCol(3) + t.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
matrix44::scale(float4 const &s) 
{    
    // need to make sure that last column isn't erased
    float4 scl = s;
    scl.set_w(1.0f);

	this->mx.setRow(0,this->mx.getRow(0) * scl.vec);
	this->mx.setRow(1,this->mx.getRow(1) * scl.vec);
	this->mx.setRow(2,this->mx.getRow(2) * scl.vec);
	this->mx.setRow(3,this->mx.getRow(3) * scl.vec);

}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
matrix44::isidentity() const
{
	return this->mx == Ogre::Matrix4::IDENTITY;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::identity()
{
    return matrix44(Ogre::Matrix4::IDENTITY);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::zero()
{
	return matrix44(Ogre::Matrix4::ZERO);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::inverse(const matrix44& m)
{
	Ogre::Matrix4 mat(m.mx);
	return matrix44(mat.inverse());
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::lookatrh(float4 const &eye, float4 const &at, float4 const &up)
{
#if NEBULA3_DEBUG
    n_assert(up.length() > 0);
#endif

	const float4 zaxis = float4::normalize(eye - at);
	float4 normUp = float4::normalize(up);
	const float4 xaxis = float4::cross3(normUp, zaxis);
	const float4 yaxis = float4::cross3(zaxis, xaxis);

	float4 row0 = xaxis;
	row0.set_w(-float4::dot3(xaxis,eye));
	float4 row1 = yaxis;
	row1.set_w(-float4::dot3(yaxis,eye));
	float4 row2 = zaxis;
	row2.set_w(-float4::dot3(zaxis,eye));
	float4 row3(0.f,0.f,0.f,1.f);
	matrix44 mat(row0,row1,row2,row3);
	return mat;

}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::multiply(const matrix44& m0, const matrix44& m1)
{
	return m0.mx * m1.mx;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::orthorh(scalar w, scalar h, scalar zn, scalar zf)
{
	float4 row0(2/w, 0.f, 0.f, 0.f);
	float4 row1(0.f, 2/h, 0.f, 0.f);

#if RENDERDEVICE_D3D9
	float4 row2(0.f, 0.f, 1 / (zn - zf ), zn / (zn - zf) );
#endif

#if RENDERDEVICE_NULL
	float4 row2(0.f, 0.f, 1 / (zn - zf ), zn / (zn - zf) );
#endif

#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
	float4 row2(0.f, 0.f, 2 / (zn - zf ), (zn + zf) / (zn - zf) );
#endif	
	
	float4 row3(0.f, 0.f, 0.f, 1.f);
	return matrix44(row0,row1,row2,row3);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::orthooffcenterrh(scalar l, scalar r, scalar b, scalar t, scalar zn, scalar zf)
{
	float4 row0(2/(r-l), 0.f, 0.f, (l+r)/(l-r));
	float4 row1(0.f, 2/(t-b), 0.f, (t+b)/(b-t));

#if RENDERDEVICE_D3D9
	float4 row2(0.f, 0.f, 1 / (zn - zf ), zn / (zn - zf) );
#endif

#if RENDERDEVICE_NULL
	float4 row2(0.f, 0.f, 1 / (zn - zf ), zn / (zn - zf) );
#endif

#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
	float4 row2(0.f, 0.f, 2 / (zn - zf ), (zn + zf) / (zn - zf) );
#endif

	float4 row3(0.f, 0.f, 0.f, 1.f);
	return matrix44(row0,row1,row2,row3);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::perspfovrh(scalar fovy, scalar aspect, scalar zn, scalar zf)
{
	scalar yScale = n_cot(scalar(fovy * 0.5));
	scalar xScale = yScale / aspect;
	float4 row0(xScale, 0.f, 0.f, 0.f);
	float4 row1(0.f, yScale, 0.f, 0.f);

#if RENDERDEVICE_D3D9
	float4 row2(0.f, 0.f, zf / (zn - zf ), zn * zf / (zn - zf) );
#endif

#if RENDERDEVICE_NULL
	float4 row2(0.f, 0.f, zf / (zn - zf ), zn * zf / (zn - zf) );
#endif

#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
	float4 row2(0.f, 0.f, -(zf + zn) / (zf - zn), -2.0f * (zn * zf) / (zf - zn));
#endif

	float4 row3(0.f, 0.f, -1.f, 0.f);

	return matrix44(row0,row1,row2,row3);
}

__forceinline matrix44
matrix44::reflect(const float4& p)
{
	float4 row0(-2 * p.x() * p.x() + 1, -2 * p.x() * p.y() , -2 * p.x() * p.z() , -2 * p.x() * p.w());
	float4 row1(-2 * p.y() * p.x(), -2 * p.y() * p.y() + 1, -2 * p.y() * p.z() , -2 * p.y() * p.w() );
	float4 row2(-2 * p.z() * p.x(), -2 * p.z() * p.y(), -2 * p.z() * p.z() + 1, -2 * p.z() * p.w() );
	float4 row3(0.f, 0.f, 0.f, 1.f);
	return matrix44(row0,row1,row2,row3);
}
//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::rotationaxis(float4 const &axis, scalar angle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis(Ogre::Radian(angle),Ogre::Vector3(axis.x(),axis.y(),axis.z()));
	Ogre::Matrix3 rotM;
	q.ToRotationMatrix(rotM);
	matrix44 result;
	result.set_xaxis(float4(rotM.GetColumn(0).x,rotM.GetColumn(0).y,rotM.GetColumn(0).z,0.f));
	result.set_yaxis(float4(rotM.GetColumn(1).x,rotM.GetColumn(1).y,rotM.GetColumn(1).z,0.f));
	result.set_zaxis(float4(rotM.GetColumn(2).x,rotM.GetColumn(2).y,rotM.GetColumn(2).z,0.f));
	result.set_position(float4(0.f,0.f,0.f,1.f));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::rotationx(scalar angle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis(Ogre::Radian(angle),Ogre::Vector3::UNIT_X);
	Ogre::Matrix3 rotM;
	q.ToRotationMatrix(rotM);
	matrix44 result;
	result.set_xaxis(float4(rotM.GetColumn(0).x,rotM.GetColumn(0).y,rotM.GetColumn(0).z,0.f));
	result.set_yaxis(float4(rotM.GetColumn(1).x,rotM.GetColumn(1).y,rotM.GetColumn(1).z,0.f));
	result.set_zaxis(float4(rotM.GetColumn(2).x,rotM.GetColumn(2).y,rotM.GetColumn(2).z,0.f));
	result.set_position(float4(0.f,0.f,0.f,1.f));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::rotationy(scalar angle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis(Ogre::Radian(angle),Ogre::Vector3::UNIT_Y);
	Ogre::Matrix3 rotM;
	q.ToRotationMatrix(rotM);
	matrix44 result;
	result.set_xaxis(float4(rotM.GetColumn(0).x,rotM.GetColumn(0).y,rotM.GetColumn(0).z,0.f));
	result.set_yaxis(float4(rotM.GetColumn(1).x,rotM.GetColumn(1).y,rotM.GetColumn(1).z,0.f));
	result.set_zaxis(float4(rotM.GetColumn(2).x,rotM.GetColumn(2).y,rotM.GetColumn(2).z,0.f));
	result.set_position(float4(0.f,0.f,0.f,1.f));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::rotationz(scalar angle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis(Ogre::Radian(angle),Ogre::Vector3::UNIT_Z);
	Ogre::Matrix3 rotM;
	q.ToRotationMatrix(rotM);
	matrix44 result;
	result.set_xaxis(float4(rotM.GetColumn(0).x,rotM.GetColumn(0).y,rotM.GetColumn(0).z,0.f));
	result.set_yaxis(float4(rotM.GetColumn(1).x,rotM.GetColumn(1).y,rotM.GetColumn(1).z,0.f));
	result.set_zaxis(float4(rotM.GetColumn(2).x,rotM.GetColumn(2).y,rotM.GetColumn(2).z,0.f));
	result.set_position(float4(0.f,0.f,0.f,1.f));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::rotationyawpitchroll(scalar yaw, scalar pitch, scalar roll)
{
	Ogre::Quaternion q;
	q = q.CalRollPitchYaw(roll,pitch,yaw);
	Ogre::Matrix3 rotM;
	q.ToRotationMatrix(rotM);
	matrix44 result;
	result.set_xaxis(float4(rotM.GetColumn(0).x,rotM.GetColumn(0).y,rotM.GetColumn(0).z,0.f));
	result.set_yaxis(float4(rotM.GetColumn(1).x,rotM.GetColumn(1).y,rotM.GetColumn(1).z,0.f));
	result.set_zaxis(float4(rotM.GetColumn(2).x,rotM.GetColumn(2).y,rotM.GetColumn(2).z,0.f));
	result.set_position(float4(0.f,0.f,0.f,1.f));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::scaling(scalar sx, scalar sy, scalar sz)
{
	matrix44 mat(Ogre::Matrix4::IDENTITY);
	mat.mx.setScale(Ogre::Vector3(sx,sy,sz));
	return mat;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::scaling(float4 const &s)
{
	matrix44 mat(Ogre::Matrix4::IDENTITY);
	mat.mx.setScale(Ogre::Vector3(s.x(),s.y(),s.z()));
	return mat;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::translation(scalar x, scalar y, scalar z)
{
	matrix44 mat(Ogre::Matrix4::IDENTITY);
	mat.set_position(float4(x,y,z,1.f));
	return mat;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::translation(float4 const &t)
{
	matrix44 mat(Ogre::Matrix4::IDENTITY);
	mat.set_position(t);
	return mat;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline matrix44
matrix44::transpose(const matrix44& m)
{
	
	return matrix44(m.mx.transpose());
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
float4
matrix44::transform(const matrix44 &m, const float4 &v)
{
	return m.mx * v.vec;
}
//------------------------------------------------------------------------------
/**
*/
__forceinline
void 
matrix44::print() const
{
	n_printf("%f, %f, %f, %f \n%f, %f, %f, %f\n %f, %f, %f, %f\n%f, %f, %f, %f\n",
		mx[0][0],mx[0][1],mx[0][2],mx[0][3],
		mx[1][0],mx[1][1],mx[1][2],mx[1][3],
		mx[2][0],mx[2][1],mx[2][2],mx[2][3],
		mx[3][0],mx[3][1],mx[3][2],mx[3][3]);
}
} // namespace Math
//------------------------------------------------------------------------------

