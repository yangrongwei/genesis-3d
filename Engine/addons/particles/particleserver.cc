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
#include "serialization/serializeserver.h"
#include "particles/particleserver.h"
#include "particles/particlesystem.h"
#include "particles/particleemitter.h"
#include "particles/particleaffector.h"
#include "particles/particletarget.h"
#include "particles/particle.h"
#include "particles/particlejob.h"



namespace Particles
{
	__ImplementClass(Particles::ParticleServer, 'PSEV', Core::RefCounted);
	__ImplementClass(Particles::ParticleSystemContainer, 'PPSC', Core::RefCounted);
	__ImplementImageSingleton(ParticleServer);

	const SizeT Particle_Job_Count = 4;

	//------------------------------------------------------------------------
	ParticleServer::ParticleServer()
	{
		__ConstructImageSingleton;
		//mTemplates = ParticleSystemContainer::Create();

		mJobs.Reserve( Particle_Job_Count );
		for ( IndexT i = 0; i < Particle_Job_Count; ++i)
		{
			mJobs.Append( ParticleJob::Create() );
		}

		_RegisterDynamicClass();
	}
	//------------------------------------------------------------------------
	ParticleServer::~ParticleServer()
	{
		__DestructImageSingleton;
		n_assert( mActives.IsEmpty() );
		//mTemplates = NULL; 
	}
	//------------------------------------------------------------------------
	void 
		ParticleServer::_attachParticleSystem( const ParticleSystemPtr& particleSystem )
	{
		if ( particleSystem.isvalid() && !particleSystem->IsActive() )
		{
			mActives.Append( particleSystem );
			particleSystem->_onActive();
		}
	}
	//-----------------------------------------------------------------------
	void 
		ParticleServer::_deattachParticleSystem( const ParticleSystemPtr& particleSystem )
	{
		if ( particleSystem.isvalid() && particleSystem->IsActive() )
		{
			IndexT findIndex = mActives.FindIndex( particleSystem );
			n_assert( findIndex != InvalidIndex );

			particleSystem->_onDeactive();

			if ( findIndex != InvalidIndex )
			{
				mActives.EraseIndex( findIndex );
			}
		}
	}
	/***
	//------------------------------------------------------------------------
	void 
	ParticleServer::OpenTemplateFile( Util::String filePath )
	{
	Serialization::SerializationServer* pSerialzeMgr = Serialization::SerializationServer::Instance();
	if ( !pSerialzeMgr )
	{
	return;
	}

	GPtr<Serialization::SerializeReader> pReader = pSerialzeMgr->OpenReadFile( filePath );
	if ( pReader )
	{
	mTemplates = pReader->SerializeObject<ParticleSystemContainer>();
	n_assert( mTemplates.isvalid() );

	pSerialzeMgr->CloseReadFile( pReader );		
	}
	}
	//------------------------------------------------------------------------
	void 
	ParticleServer::SaveTemplateFile( Util::String filePath  )
	{

	Serialization::SerializationServer* pSerialzeMgr = Serialization::SerializationServer::Instance();
	if( !pSerialzeMgr )
	{
	return;
	}

	GPtr<Serialization::SerializeWriter> pWriter = pSerialzeMgr->OpenWriteFile( filePath );
	if ( pWriter )
	{
	pWriter->SerializeObject( mTemplates );
	pSerialzeMgr->CloseWriteFile( pWriter );
	}
	}
	//------------------------------------------------------------------------
	ParticleSystemPtr 
	ParticleServer::CreateFromTemplate(const Util::StringAtom& tplname)
	{
	if ( !tplname.IsValid() )
	{
	return ParticleSystemPtr(NULL);
	}

	const ParticleSystemPtr& source = FindTemplate( tplname );
	if ( source.isvalid() )
	{
	ParticleSystemPtr dest = Clone( source );
	return dest;
	}
	else
	{
	return ParticleSystemPtr(NULL);
	}
	}
	//------------------------------------------------------------------------
	bool 
	ParticleServer::AddTemplate(const Util::StringAtom& tplname, const ParticleSystemPtr& parSystem )
	{
	if ( !parSystem.isvalid() || !tplname.IsValid() )
	{
	return false;
	}

	ParticleSystemPtr tpl = Clone( parSystem );
	tpl->SetName( tplname.AsString() );

	IndexT findIndex =  mTemplates->mContainer.FindIndex( tplname );
	if ( findIndex != InvalidIndex )
	{
	mTemplates->mContainer.ValueAtIndex(findIndex) = tpl;
	}
	else
	{
	mTemplates->mContainer.Add(tplname, tpl);
	}
	return true;
	}
	//------------------------------------------------------------------------
	void 
	ParticleServer::RemoveTemplate( const Util::StringAtom& tplName )
	{
	IndexT findIndex = mTemplates->mContainer.FindIndex( tplName );
	if ( findIndex != InvalidIndex )
	{
	mTemplates->mContainer.EraseAtIndex( findIndex );
	}
	}
	***/
	//--------------------------------update----------------------------------------
	void 
		ParticleServer::Update()
	{
		if ( mActives.IsEmpty() )
		{
			return;
		}

		//@todo 

		bool useMutilThread = false;

		if ( !useMutilThread )
		{
			SizeT count = mActives.Size();
			for ( IndexT i = 0; i < count; ++i)
			{
				mActives[i]->Update();
			}
		}
		else
		{
			SizeT count = mActives.Size();

			SizeT perJob = Math::n_frnd( (float)count / (float)Particle_Job_Count );
			if ( perJob == 0 )
			{
				perJob = 1;
			}

			SizeT jobToStart = 0;

			SizeT parSystemToJob = 0;
			for (IndexT i = 0; i < Particle_Job_Count; ++i )
			{
				++jobToStart;
				if ( parSystemToJob + perJob >= count )
				{
					mJobs[i]->Setup( &mActives, parSystemToJob, count );
					parSystemToJob = count;
					break;
				}
				else
				{
					mJobs[i]->Setup( &mActives, parSystemToJob, parSystemToJob + perJob );
					parSystemToJob += perJob;
				}	
			}
			n_assert( parSystemToJob == count );
			n_assert( jobToStart <= Particle_Job_Count );

			for ( IndexT i = 0; i < jobToStart; ++i )
			{
				mJobs[i]->Run();
			}

			for ( IndexT i = 0; i < jobToStart; ++i )
			{
				mJobs[i]->WaitForFinished();
				mJobs[i]->End();
			}
		}
	}

}
