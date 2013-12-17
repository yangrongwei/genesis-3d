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
#ifndef __particle_H__
#define __particle_H__

#include "particles/particle_fwd_decl.h"

namespace Particles
{
	struct Particle
	{
		/// Particle's position 
		Math::float3	mPosition;			

		/// Particle's Direction (and speed)
		Math::float3	mDirection;			

		/// Particle's Size. X-width, Y-height, Z-depth . logic in world space
		Math::float3    mInitSize;
		Math::float3	mSize;				

		/// Orientation is only useful for 3D particles, such as Boxes and Spheres
		Math::quaternion  mOrientation;		

		/// Particle's mass
		Math::scalar	mMass;				

		/// Particle's rotation in degrees (around the Z-axis)
		Math::scalar	mZRotation;			

		/// Particle's anguluar velocity in radian per second.
		Math::scalar	mZRotationSpeed;	

		/// Total Time to live, number of seconds of particles natural life
		Math::scalar	mTotalTimeToLive;	

		/// Time to live, number of seconds left of particles natural life
		Math::scalar	mTimeToLive;		

		/// !
		Math::scalar	mTimeFraction;		

		/// Particle's color 
		Math::Color32	mColor;				

		/// Particle's texcoord index. for texture animation
		IndexT			mTexCoordIndex;		

		/// the contrail of one particle
		Util::Array<Math::float3>	mOrbitPositions;

		/// the random 
		Math::scalar  mRandom0;
		Math::scalar  mRandom1;
		Math::scalar  mRandom2;
		Math::scalar  mRandom3;
	};

}






#endif // __particle_H__
