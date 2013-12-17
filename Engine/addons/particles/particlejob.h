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
#ifndef __particlejob_H__
#define __particlejob_H__
#include "particle_fwd_decl.h"
#include "jobs/jobport.h"
#include "jobs/job.h"

namespace Particles
{
	typedef Util::Array<ParticleSystemPtr> ParSystemList;

	struct ParticleJobData
	{
		ParticleJobData()
			: mUpdateList(NULL)
			, mBeginIndex(0)
			, mEndIndex(InvalidIndex)
		{ }
		ParSystemList* mUpdateList;
		IndexT mBeginIndex;
		IndexT mEndIndex;
	};

	class ParticleJob: public Core::RefCounted
	{
		__DeclareClass(ParticleJob); 
	public:
		ParticleJob();
		virtual ~ParticleJob();

		void Setup( ParSystemList* updateList, IndexT begin, IndexT end );

		/// run job
		void Run();

		/// is finished
		bool IsFinished() const;

		/// wait for finished
		bool WaitForFinished() const;

		/// finish clear
		void End();

	protected:
		ParticleJobData mData;
		GPtr<Jobs::JobPort> mJobPort;
		GPtr<Jobs::Job>     mJob;
	};

	//------------------------------------------------------------------------------
	inline
		bool 
		ParticleJob::IsFinished() const
	{
		if ( mJobPort.isvalid() )
		{
			return mJobPort->CheckDone();
		}
		return true;
	}

	//------------------------------------------------------------------------------
	inline
		bool
		ParticleJob::WaitForFinished() const
	{
		if ( mJobPort.isvalid() )
		{
			mJobPort->WaitDone();
			return true;
		}
		return true;
	} 


}





#endif // __particlejob_H__
