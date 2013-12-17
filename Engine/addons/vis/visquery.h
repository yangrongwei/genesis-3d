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
#ifndef __visquery_H__
#define __visquery_H__


#include "core/refcounted.h"
#include "vis/vissystems/vissystembase.h"
#include "vis/visentity.h"
#include "vis/observercontext.h"
#include "jobs/jobport.h"

//------------------------------------------------------------------------------
namespace Vis
{   
	class VisServer;

	class VisQuery : public Core::RefCounted
	{
		__DeclareClass(VisQuery);
	public:
		/// constructor
		VisQuery();
		/// destructor
		virtual ~VisQuery();

		/// get visible Context   
		const Util::Array<GPtr<VisEntity> >& GetQueryResult() const;

	protected:
		/// attach visible system, used by this job
		void AttachVisSystem(const GPtr<VisSystemBase>& visSystem); 

		/// set Observer
		void SetObserver(const GPtr<ObserverContext>& observe); 

		/// get Observer
		const GPtr<ObserverContext>& GetObserver() const;  

		/// run job
		void Run();

		/// is finished
		bool IsFinished() const;

		/// wait for finished
		bool WaitForFinished() const;

		/// finish clear
		void EndQuery();

	protected:  
		friend class VisServer;	

		GPtr<ObserverContext> mObserverContext;
		Util::Array<GPtr<VisEntity> > mResultList;
		Util::Array<GPtr<VisSystemBase> > mVisibilitySystems;       
		GPtr<Jobs::JobPort> mJobPort;
		Util::Array<GPtr<Jobs::Job> > mJobs;

		typedef Util::Array<GPtr<VisEntity> > RSList;
		Util::Array< RSList > mTempResults;
	};
	//------------------------------------------------------------------------
	inline
	void 
	VisQuery::AttachVisSystem(const GPtr<VisSystemBase>& visSystem)
	{
		this->mVisibilitySystems.Append(visSystem);
	}
	//------------------------------------------------------------------------------
	inline 
	void 
	VisQuery::SetObserver(const GPtr<ObserverContext>& observer)
	{
		mObserverContext = observer;
	}

	//------------------------------------------------------------------------------
	inline 
	const GPtr<ObserverContext>&
	VisQuery::GetObserver() const
	{
		return mObserverContext;
	}
	//------------------------------------------------------------------------
	inline
	const Util::Array<GPtr<VisEntity> >& 
	VisQuery::GetQueryResult() const
	{
		return mResultList;
	}
	//------------------------------------------------------------------------------
	inline
	bool 
	VisQuery::IsFinished() const
	{
		if ( mJobPort.isvalid() )
		{
			return this->mJobPort->CheckDone();
		}
		return true;
	}

	//------------------------------------------------------------------------------
	inline
	bool
	VisQuery::WaitForFinished() const
	{
		if ( mJobPort.isvalid() )
		{
			this->mJobPort->WaitDone();
			return true;
		}
		return true;
	} 
} // namespace Vis
//------------------------------------------------------------------------------





#endif // __visquery_H__



