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
#include "stdneb.h"
#include "particles/particleserver.h"
#include "particles/particlesystem.h"
#include "particles/particleemitter.h"
#include "particles/emitters/particlePointEmitter.h"
#include "particles/emitters/particleBoxEmitter.h"
#include "particles/emitters/particleSphereSurfaceEmitter.h"
#include "particles/emitters/particleConeEmitter.h"
#include "particles/emitters/particleModelEmitter.h"

#include "particles/particleaffector.h"
#include "particles/affectors/particleColorAffector.h"
#include "particles/affectors/particleFollowerAffector.h"
#include "particles/affectors/particleGravityAffector.h"
#include "particles/affectors/particleLinearForceAffector.h"
#include "particles/affectors/particleRandomiserAffector.h"
#include "particles/affectors/particleScaleAffector.h"
#include "particles/affectors/particleTextureAnimatorAffector.h"
#include "particles/affectors/particleTextureRotatorAffector.h"
#include "particles/affectors/particleVortexAffector.h"

#include "particles/particletarget.h"
#include "particles/targets/particlebillboardtarget.h"
#include "particles/targets/particleBeamTarget.h"
#include "particles/targets/particleEntityTarget.h"
#include "particles/targets/particleRibbonTrailTarget.h"
#include "particles/targets/particleTrailTarget.h"
#include "particles/targets/particleDecalTarget.h"

namespace Particles
{
	void ParticleServer::_RegisterDynamicClass() const
	{
		ParticleSystem::RegisterWithFactory();

		ParticleEmitter::RegisterWithFactory();
		PointEmitter::RegisterWithFactory();
		BoxEmitter::RegisterWithFactory();
		SphereSurfaceEmitter::RegisterWithFactory();
		ConeEmitter::RegisterWithFactory();
		ModelEmitter::RegisterWithFactory();

		ParticleAffector::RegisterWithFactory();
		ColorAffector::RegisterWithFactory();
		ParticleFollowerAffector::RegisterWithFactory();
		GravityAffector::RegisterWithFactory();
		LinearForceAffector::RegisterWithFactory();
		RandomiserAffector::RegisterWithFactory();
		ScaleAffector::RegisterWithFactory();
		TextureAnimatorAffector::RegisterWithFactory();
		TextureRotatorAffector::RegisterWithFactory();
		VortexAffector::RegisterWithFactory();

		ParticleTarget::RegisterWithFactory();
		ParticleBillBoardTarget::RegisterWithFactory();
		ParticleBeamTarget::RegisterWithFactory();
		ParticleEntityTarget::RegisterWithFactory();
		RibbonTrailTarget::RegisterWithFactory();
		ParticleDecalTarget::RegisterWithFactory();
		ParticleTrailTarget::RegisterWithFactory();
	}
}

