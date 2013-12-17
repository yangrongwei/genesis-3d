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
#include "particles/particlepool.h"
#include "particles/particle.h"
#include "memory/memory.h"

namespace Particles
{
	__ImplementClass(Particles::ParticlePool, 'PPOL', Core::RefCounted )

		ParticlePool::ParticlePool(void)
		: mLatestParticle(NULL)
	{

	}
	//-----------------------------------------------------------------------
	ParticlePool::~ParticlePool (void)
	{
		DestroyAllVisualParticles();
	}
	//-----------------------------------------------------------------------
	void ParticlePool::DestroyAllVisualParticles(void)
	{
		mParticlesPool.releaseAllElements();
		PoolList& list = mParticlesPool.getActiveElementsList();

		for ( PoolIterator itr = list.begin(); itr != list.end(); ++itr)
			n_delete(*itr);

		mParticlesPool.clear();
	}
	//-----------------------------------------------------------------------
	void ParticlePool::IncreaseVisualParticlePool(SizeT size)
	{
		int oldSize = mParticlesPool.getActiveElementsList().size();
		if (size < oldSize)
			return;

		Particle* particle = NULL;
		for (IndexT i = oldSize; i < size; i++)
		{
			particle = n_new(Particle);
			mParticlesPool.addElement(particle);
		}

		ResetIterator();
	}
	//-----------------------------------------------------------------------
	void ParticlePool::ReleaseAllParticles (void)
	{
		mParticlesPool.releaseAllElements();
		ResetIterator();
	}
	//-----------------------------------------------------------------------
	void ParticlePool::LockLatestParticle (void)
	{
		if (mLatestParticle)
		{
			mParticlesPool.lockLatestElement();
		}
	}
	//-----------------------------------------------------------------------
	void ParticlePool::LockAllParticles (void)
	{
		mParticlesPool.lockAllElements();
		ResetIterator();
	}
	//-----------------------------------------------------------------------
	void ParticlePool::ResetIterator(void)
	{
		mParticlesPool.resetIterator();
		mLatestParticle = 0;
	}
	//-----------------------------------------------------------------------
	Particle* ParticlePool::GetFirst(void)
	{
		ResetIterator();
		mLatestParticle = mParticlesPool.getFirst();
		return mLatestParticle;
	}
	//-----------------------------------------------------------------------
	Particle* ParticlePool::GetNext(void)
	{
		if (!mLatestParticle)
			return 0;

		mLatestParticle = mParticlesPool.getNext();

		return mLatestParticle;
	}
	//-----------------------------------------------------------------------
}

