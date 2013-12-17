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
#include "math/vector.h"
#include "math/OgreMath/OgreQuaternion.h"

//------------------------------------------------------------------------------
namespace Math
{
class quaternion;

// win32 VC++ does not support passing aligned objects as value so far
// here is a bug-report at microsoft saying so:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=334581
typedef const quaternion& __QuaternionArg;
 
class quaternion
{
public:
    /// default constructor, NOTE: does NOT setup components!
    quaternion();
    /// construct from components
    quaternion(scalar x, scalar y, scalar z, scalar w);
    /// construct from float4
    quaternion(float4 const &rhs);
    /// copy constructor
    /// !!!! copy constructor forbidden, otherwise passing point's to a function
    /// !!!! via Registers doesnt work
    //quaternion(const quaternion& rhs);
    /// construct from Ogre::Quaternion
    quaternion(Ogre::Quaternion rhs);

    /// assignment operator
    void operator=(const quaternion& rhs);
    /// assign Ogre::Quaternion
    void operator=(Ogre::Quaternion rhs);
    /// equality operator
    bool operator==(const quaternion& rhs) const;
    /// inequality operator
    bool operator!=(const quaternion& rhs) const;
	// rotation of a vector by a quaternion
	vector operator* (const vector& rkVector) const;
	// plus operator
	quaternion operator+ (const quaternion& rkQ) const;
	// minus operator
	quaternion operator- (const quaternion& rkQ) const;

	/// load content from 16-byte-aligned memory
    void load(const scalar* ptr);
    /// stream content to 16-byte-aligned memory circumventing the write-cache
    void stream(scalar* ptr) const;

    /// set content
    void set(scalar x, scalar y, scalar z, scalar w);
    /// set from float4
    void set(float4 const &f4);
    /// set the x component
    void set_x(scalar x);
    /// set the y component
    void set_y(scalar y);
    /// set the z component
    void set_z(scalar z);
    /// set the w component
    void set_w(scalar w);

    /// read/write access to x component
    scalar& x();
    /// read/write access to y component
    scalar& y();
    /// read/write access to z component
    scalar& z();
    /// read/write access to w component
    scalar& w();
    /// read-only access to x component
    scalar x() const;
    /// read-only access to y component
    scalar y() const;
    /// read-only access to z component
    scalar z() const;
    /// read-only access to w component
    scalar w() const;
    
    /// return true if quaternion is identity
    bool isidentity() const;
    /// returns length
    scalar length() const;
    /// returns length squared
    scalar lengthsq() const;
    /// un-denormalize quaternion (this is sort of a hack since Maya likes to return denormal quaternions)
    void undenormalize();
	///dot product
	scalar dot(const quaternion& q) const;

    /// calculate the exponential
    static quaternion exp(const quaternion& q0);
    /// returns an identity quaternion
    static quaternion identity();
	/// conjugates quaternion
	static quaternion conjugate(const quaternion& q);
    /// conjugates and renormalizes quaternion
    static quaternion inverse(const quaternion& q);
    /// calculate the natural logarithm
    static quaternion ln(const quaternion& q);
    /// multiply 2 quaternions
    static quaternion multiply(const quaternion& q0, const quaternion& q1);
    /// compute unit length quaternion
    static quaternion normalize(const quaternion& q);
    /// build quaternion from yaw, pitch and roll
    static quaternion rotationyawpitchroll(scalar yaw, scalar pitch, scalar roll);
    /// interpolate between 2 quaternion using spherical interpolation
    static quaternion slerp(const quaternion& q1, const quaternion& q2, scalar t);
    /// convert quaternion to axis and angle
    static void to_axisangle(const quaternion& q, float4& outAxis, scalar& outAngle);
	/// rotate axis by angle
	static quaternion rotationaxis(const float4& inAxis, const scalar& inAngle);
	/// get yaw pitch roll in degree
	static void getyawpitchroll(const quaternion& q, scalar& yaw, scalar& pitch, scalar& roll);
	


private:
    friend class matrix44;

	Ogre::Quaternion vec;
};

//------------------------------------------------------------------------------
/**
*/
__forceinline
quaternion::quaternion()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
quaternion::quaternion(scalar x, scalar y, scalar z, scalar w)
{
	this->vec = Ogre::Quaternion(w,x,y,z);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
quaternion::quaternion(float4 const &rhs)
{
    this->vec = Ogre::Quaternion(rhs.w(),rhs.x(),rhs.y(),rhs.z());
}
    
//------------------------------------------------------------------------------
/**
*/
__forceinline 
quaternion::quaternion(Ogre::Quaternion rhs) :
    vec(rhs)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::operator=(const quaternion& rhs)
{
    this->vec = rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::operator=(Ogre::Quaternion rhs)
{
    this->vec = rhs;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
quaternion::operator==(const quaternion& rhs) const
{
	return this->vec == rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
quaternion::operator!=(const quaternion& rhs) const
{
	return this->vec != rhs.vec;
}
//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion 
quaternion::operator+( const quaternion& ths ) const
{
	return quaternion( vec.x+ths.vec.x, vec.y+ths.vec.y, vec.z+ths.vec.z, vec.w+ths.vec.w);
}
//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion 
quaternion::operator-( const quaternion& ths ) const
{
	return quaternion( vec.x-ths.vec.x, vec.y-ths.vec.y, vec.z-ths.vec.z, vec.w-ths.vec.w);
}
//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::load(const scalar* ptr)
{
	memcpy((void*)this->vec.ptr(),ptr,sizeof(quaternion));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::stream(scalar* ptr) const
{
	memcpy(ptr,(void*)this->vec.ptr(),sizeof(quaternion));
    //XMStoreFloat4A((XMFLOAT4A*)ptr, this->vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::set(scalar x, scalar y, scalar z, scalar w)
{
	this->vec = Ogre::Quaternion(w,x,y,z);
}

//------------------------------------------------------------------------------
/**
*/
inline void 
quaternion::set_x(scalar x)
{
	this->vec.x = x;
}

//------------------------------------------------------------------------------
/**
*/
inline void 
quaternion::set_y(scalar y)
{
	this->vec.y = y;
}

//------------------------------------------------------------------------------
/**
*/
inline void 
quaternion::set_z(scalar z)
{
	this->vec.z = z;
}

//------------------------------------------------------------------------------
/**
*/
inline void 
quaternion::set_w(scalar w)
{
	this->vec.w = w;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::set(float4 const &f4)
{
	this->vec = quaternion(f4).vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
quaternion::x()
{
    return this->vec.x;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::x() const
{
    return this->vec.x;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
quaternion::y()
{
    return this->vec.y;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::y() const
{
    return this->vec.y;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
quaternion::z()
{
    return this->vec.z;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::z() const
{
    return this->vec.z;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
quaternion::w()
{
    return this->vec.w;

}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::w() const
{
    return this->vec.w;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
quaternion::isidentity() const
{
	return this->vec == Ogre::Quaternion::IDENTITY;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::length() const
{
	return float4(this->vec.x,this->vec.y,this->vec.z,this->vec.w).length();
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
quaternion::lengthsq() const
{
	return float4(this->vec.x,this->vec.y,this->vec.z,this->vec.w).lengthsq();
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::undenormalize()
{
    // nothing to do on the xbox, since denormal numbers are not supported by the vmx unit, 
    // it is being set to zero anyway

    this->set_x(n_undenormalize(this->x()));
    this->set_y(n_undenormalize(this->y()));
    this->set_z(n_undenormalize(this->z()));
    this->set_w(n_undenormalize(this->w()));

}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::exp(const quaternion& q)
{
	return quaternion(q.vec.Exp());
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::identity()
{

	return quaternion(Ogre::Quaternion::IDENTITY);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::conjugate(const quaternion& q)
{
	return quaternion(-q.vec.x, -q.vec.y, -q.vec.z, q.vec.w);
}

//------------------------------------------------------------------------------
/**
*/

__forceinline quaternion
quaternion::inverse(const quaternion& q)
{
	quaternion ret = q;
	ret.vec.Inverse();
	return ret;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::ln(const quaternion& q)
{
	quaternion ret = q;
	ret.vec.Log();
	return ret;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::multiply(const quaternion& q0, const quaternion& q1)
{
	return quaternion(q0.vec * q1.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::normalize(const quaternion& q)
{
	quaternion ret = q;
	ret.vec.normalise();
	return ret;
}


//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::rotationyawpitchroll(scalar yaw, scalar pitch, scalar roll)
{
	//quaternion q;
	//q.vec = q.vec.CalRollPitchYaw(roll,pitch,yaw);
	//return q;

	quaternion result;
	float num9 = roll * 0.5f;
	float num6 = n_sin(num9);
	float num5 = n_cos(num9);
	float num8 = pitch * 0.5f;
	float num4 = n_sin(num8);
	float num3 = (float)n_cos(num8);
	float num7 = yaw * 0.5f;
	float num2 = n_sin(num7);
	float num = n_cos(num7);
	result.x() = ((num * num4) * num5) + ((num2 * num3) * num6);
	result.y() = ((num2 * num3) * num5) - ((num * num4) * num6);
	result.z() = ((num * num3) * num6) - ((num2 * num4) * num5);
	result.w() = ((num * num3) * num5) + ((num2 * num4) * num6);

	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline quaternion
quaternion::slerp(const quaternion& q1, const quaternion& q2, scalar t)
{
	return quaternion(Ogre::Quaternion::Slerp(t,q1.vec,q2.vec));
}
//------------------------------------------------------------------------------
/**
*/
__forceinline void
quaternion::to_axisangle(const quaternion& q, float4& outAxis, scalar& outAngle)
{
	Ogre::Degree d;
	Ogre::Vector3 outA;
	q.vec.ToAngleAxis(d,outA);
	outAngle = d.valueRadians();
	outAxis.set(outA.x,outA.y,outA.z,0.0f);
}

__forceinline quaternion
quaternion::rotationaxis(const float4& inAxis, const scalar& inAngle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis( Ogre::Radian(inAngle), Ogre::Vector3(inAxis.x(),inAxis.y(),inAxis.z()));
	return q;
}

__forceinline void
quaternion::getyawpitchroll(const quaternion& q, scalar& yaw, scalar& pitch, scalar& roll)
{
	
// 	Ogre::Radian y,p,r;
// 
// 	q.vec.GetYawPitchRoll(y, p, r);
// 
// 	yaw = y.valueRadians();
// 	pitch = p.valueRadians();
// 	roll = r.valueRadians();

	//算法出自
	//[3D数学基础：图形与游戏开发].(3D.Math.Primer.for.Graphics.and.Game.Development).(美)Fletcher.Dunn.扫描版.pdf
	//章节10.6.6, 第173页，程序清单10.6


// 	//计算 sin(pitch)
	float sp = -2.0f * (q.y() * q.z() - q.w() * q.x());

	//检查万向锁，允许有一定误差。
	if(n_abs(sp) > 0.9999f)
	{
		//向正上或正下看
		pitch = 1.570796f * sp;
		//计算 heading, bank置零
		yaw = n_atan2(-q.x() * q.z() + q.w() * q.y(), 0.5f - q.y() * q.y() - q.z() * q.z());
		roll = 0.0f;
	} 
	else
	{
		//计算角度
		pitch = n_asin(sp);
		yaw = n_atan2(q.x() * q.z() + q.w() * q.y(), 0.5f - q.x() * q.x() - q.y() * q.y());
		roll = n_atan2(q.x() * q.y() + q.w() * q.z(), 0.5f - q.x() * q.x() - q.z() * q.z());
	}
}

__forceinline scalar
quaternion::dot(const Math::quaternion &q) const
{
	return vec.Dot(Ogre::Quaternion(q.w(),q.x(),q.y(),q.z()));
}

} // namespace Math
//------------------------------------------------------------------------------
