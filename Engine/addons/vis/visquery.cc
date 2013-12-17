/****************************************************************************
Copyright (c) 2010,Radon Labs GmbH
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
#include "vis/visquery.h"

namespace Vis
{
__ImplementClass(Vis::VisQuery, 'VIQU', Core::RefCounted);

using namespace Util;
using namespace Math;
using namespace Jobs;

//------------------------------------------------------------------------------
/**
*/
VisQuery::VisQuery()
{
}

//------------------------------------------------------------------------------
/**
*/
VisQuery::~VisQuery()
{
    this->mJobPort = 0;
    this->mObserverContext = 0;
	mResultList.Clear();
	mVisibilitySystems.Clear();
	mJobs.Clear();
}

//------------------------------------------------------------------------------
/**
*/
void 
VisQuery::Run()
{
	if ( !mObserverContext.isvalid() || mVisibilitySystems.Size() == 0 || mJobPort.isvalid())
	{
		return;
	}

#ifdef __WIN32__

	this->mJobPort = Jobs::JobPort::Create();
	this->mJobPort->Setup();

#endif
	mTempResults.Clear();

	// create worker thread which goes thru all vis systems. one system one job
	mTempResults.Fill(0, mVisibilitySystems.Size(), RSList() );

    for (IndexT index = 0; index < this->mVisibilitySystems.Size(); ++index)
    {   
        const GPtr<VisSystemBase>& visSystem = this->mVisibilitySystems[index];
		RSList& rs = mTempResults[index];
		if ( visSystem->GetNumEntity() > 0 )
		{
			rs.Reserve( visSystem->GetNumEntity() );
		}

        GPtr<Job> newJob = visSystem->CreateVisJob(this->mObserverContext, 
                                                         mTempResults[index] );

        // for non multi-threaded 
        if (newJob.isvalid())
        {
			mJobs.Append( newJob );
#ifdef __WIN32__
			this->mJobPort->PushJob( newJob );
#endif
        }        
    }
}  

//------------------------------------------------------------------------
void
VisQuery::EndQuery()
{
	mJobPort = NULL;
	mVisibilitySystems.Clear();
	mJobs.Clear();

	// 拷贝到最终结果缓冲区，大量的智能指针的拷贝，可能会有性能问题。 
	SizeT AllCount = 0;
	for ( IndexT index = 0; index < mTempResults.Size(); ++index )
	{
		RSList& rs = mTempResults[index];
		AllCount += rs.Size();
	}
          
	this->mResultList.Clear();
	if ( AllCount != 0 )
	{
		this->mResultList.Reserve( AllCount );

		for ( IndexT index = 0; index < mTempResults.Size(); ++index )
		{
			RSList& rs = mTempResults[index];
			mResultList.AppendArray( rs );
		}
	}

	mTempResults.Clear();
}

} // namespace Vis
