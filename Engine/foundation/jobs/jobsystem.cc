//------------------------------------------------------------------------------
//  jobsystem.cc
//  (C) 2009 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "jobs/jobsystem.h"

namespace Jobs
{
#if __PS3__
__ImplementClass(Jobs::JobSystem, 'JOBS', PS3::PS3JobSystem);
#elif (NEBULA3_USE_SERIAL_JOBSYSTEM || __WII__)
__ImplementClass(Jobs::JobSystem, 'JOBS', Jobs::SerialJobSystem);
#elif (__WIN32__ || __XBOX360__ || __WII__ || __ANDROID__ || __OSX__)
__ImplementClass(Jobs::JobSystem, 'JOBS', Jobs::TPJobSystem);
#else
#error "Job::JobSystem not implemented on this platform!"
#endif
__ImplementImageSingleton(Jobs::JobSystem);

//------------------------------------------------------------------------------
/**
*/
JobSystem::JobSystem()
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
JobSystem::~JobSystem()
{
    __DestructImageSingleton;
}

} // namespace Jobs
