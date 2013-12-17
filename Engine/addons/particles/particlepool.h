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
#ifndef __particlepool_H__
#define __particlepool_H__

#include "particles/particle_fwd_decl.h"
#include "particles/pool.h"


namespace App{
	class Actor;
}

namespace Particles
{
	using namespace App;

	class ParticlePool: public Core::RefCounted
	{
		__DeclareClass(ParticlePool)
	public:
		ParticlePool(void);
		virtual ~ParticlePool (void);

		void IncreaseVisualParticlePool(SizeT size);

		void DestroyAllVisualParticles(void);

		void SetParticleVisible();

		bool IsEmpty(void);

		SizeT GetSize(void);

		Particle* ReleaseParticle ();

		void ReleaseAllParticles (void);

		void LockLatestParticle (void);

		void LockAllParticles (void);

		void ResetIterator(void);

		Particle* GetFirst(void);

		Particle* GetNext(void);

		bool End(void);

	protected:
		typedef Pool<Particle>::PoolList		PoolList;
		typedef Pool<Particle>::PoolIterator	PoolIterator;

		Pool<Particle>		mParticlesPool;
		Particle*			mLatestParticle;
	}; 

	//-----------------------------------------------------------------------
	inline bool ParticlePool::IsEmpty(void)
	{
		return mParticlesPool.isEmpty();
	};
	//-----------------------------------------------------------------------
	inline SizeT ParticlePool::GetSize(void)
	{
		return mParticlesPool.getSize();
	};
	//-----------------------------------------------------------------------
	inline Particle* ParticlePool::ReleaseParticle ()
	{
		return mParticlesPool.releaseElement();
	}
	//-----------------------------------------------------------------------
	inline bool ParticlePool::End(void)
	{
		return mParticlesPool.end(); 
	}
	//------------------------------------------------------------------------
}

#endif // __particlepool_H__
