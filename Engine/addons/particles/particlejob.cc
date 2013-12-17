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
#include "particles/particlejob.h"
#include "particles/particlesystem.h"
#include "jobs/stdjob.h"

namespace Particles{

	void ParticleJobFunc(const JobFuncContext& ctx)
	{
		ParticleJobData* data = (ParticleJobData*)ctx.uniforms[0];
		ParSystemList& loopList = *(data->mUpdateList);
		for( IndexT index = data->mBeginIndex; index < data->mEndIndex; ++index )
		{
			loopList[index]->Update();
		}
	}

} // namespace Vis
__ImplementSpursJob(Particles::ParticleJobFunc);

namespace Particles
{
	__ImplementClass(Particles::ParticleJob, 'PARJ', Core::RefCounted)
		//------------------------------------------------------------------------
		ParticleJob::ParticleJob()
	{

	}
	//------------------------------------------------------------------------
	ParticleJob::~ParticleJob()
	{
		n_assert( !mData.mUpdateList ); 
		n_assert( mData.mBeginIndex == 0 );
		n_assert( mData.mEndIndex == InvalidIndex);
		n_assert( !mJobPort.isvalid() );
		n_assert( !mJob.isvalid() );
	}
	//------------------------------------------------------------------------
	void ParticleJob::Setup( ParSystemList* updateList, IndexT begin, IndexT end )
	{
		mData.mUpdateList = updateList;
		mData.mBeginIndex = begin;
		mData.mEndIndex = end;
		n_assert( mData.mEndIndex > mData.mBeginIndex ); 
	}

	//------------------------------------------------------------------------
	void 
		ParticleJob::Run()
	{
		n_assert( !mJobPort.isvalid() );
		n_assert( mData.mUpdateList != NULL );
		n_assert( mData.mBeginIndex < mData.mEndIndex );

		mJobPort = Jobs::JobPort::Create();
		mJobPort->Setup();

		// create new job           
		mJob = Jobs::Job::Create();

		// input data for job  
		// function
		Jobs::JobFuncDesc jobFunction(ParticleJobFunc);   

		Jobs::JobUniformDesc uniformData( &mData, sizeof(void*), 0 );

		Jobs::JobDataDesc inputData( &mData, sizeof(void*), sizeof(void*) );
		Jobs::JobDataDesc outputData( &mData, sizeof(void*), sizeof(void*) );

		// setup job with data
		mJob->Setup(uniformData, inputData, outputData, jobFunction);

		mJobPort->PushJob( mJob );
	}
	//------------------------------------------------------------------------
	void 
		ParticleJob::End()
	{
		mData.mUpdateList = NULL;
		mData.mBeginIndex = 0;
		mData.mEndIndex = InvalidIndex;
		mJobPort = NULL;
		mJob = NULL;
	}

}