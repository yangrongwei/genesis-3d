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
#ifndef _PHYSICSUTIL_H_
#define _PHYSICSUTIL_H_

#include "math/float3.h"
#include "PxVec3.h"
#include "PxVersionNumber.h"
#include "PxExtended.h"
#include "PxQuat.h"
#include "PxMat33.h"
#include "PxMat44.h"
namespace App
{
	struct PhysicsFlag
	{
		enum
		{
			eSL_CCD_FLAG = 1<<31
		};
	};

	inline PxExtendedVec3 Float3ToPxExtended(const Math::float3& v)
	{
		return PxExtendedVec3((Math::scalar)v.x(), (Math::scalar)v.y(), (Math::scalar)v.z());
	}

	inline Math::float3 PxExtendedToFloat3(const PxExtendedVec3& v)
	{
		return Math::float3((Math::scalar)v.x, (Math::scalar)v.y, (Math::scalar)v.z);
	}

	inline PxVec3 Float3ToPxVec(const Math::float3& v)
	{
		return PxVec3((Math::scalar)v.x(), (Math::scalar)v.y(), (Math::scalar)v.z());
	}

	inline Math::float3 PxVecToFloat3(const PxVec3& v)
	{
		return Math::float3((Math::scalar)v.x, (Math::scalar)v.y, (Math::scalar)v.z);
	}

	inline Math::quaternion PxQuatToQuat(const PxQuat& quat)
	{
		return Math::quaternion(quat.x,quat.y,quat.z,quat.w);
	}

	inline PxMat44 RotPosToPxMat( const Math::float3& f3Center,const Math::quaternion& qRotation)
	{
		PxQuat quat(qRotation.x(),qRotation.y(),qRotation.z(),qRotation.w());
		PxMat33 rot(quat);
		PxVec3 trans(f3Center.x(),f3Center.y(),f3Center.z());	
		return PxMat44(rot,trans);
	}
}

#endif
