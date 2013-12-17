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
#include "vis/visserver.h"

namespace Vis
{
using namespace Util;
using namespace Math;

#define NUM_JOBS_PERFRAME 64

__ImplementClass(Vis::VisServer, 'VISE', Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
VisServer::VisServer()
	: mIsOpen(false)

{ 

}

//------------------------------------------------------------------------------
/**
*/
VisServer::~VisServer()
{

}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::RegisterVisEntity(const GPtr<VisEntity>& entity, IndexT VisibilitySystemIndex)
{
	n_assert( VisibilitySystemIndex<VisEntity::MAX_VIS_SYSTEM_COUNT );
	if ( InvalidIndex == VisibilitySystemIndex )
	{
		// insert in each attached visibility system
		IndexT index;
		SizeT size = this->mVisibilitySystems.Size();
		for (index = 0; index < size; ++index)
		{
    		this->mVisibilitySystems[index]->InsertVisEntity(entity);
		}		
	}
	else
	{
		n_assert( VisibilitySystemIndex >=0 && VisibilitySystemIndex < mVisibilitySystems.Size() ); 
		if ( VisibilitySystemIndex >=0 && VisibilitySystemIndex < mVisibilitySystems.Size() )
		{
			mVisibilitySystems[VisibilitySystemIndex]->InsertVisEntity(entity);
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::UnregisterVisEntity(const GPtr<VisEntity>& entity, IndexT VisibilitySystemIndex )
{
	n_assert( VisibilitySystemIndex<VisEntity::MAX_VIS_SYSTEM_COUNT );
	if ( InvalidIndex == VisibilitySystemIndex )
	{
		IndexT index;
		SizeT size = this->mVisibilitySystems.Size();
		for (index = 0; index < size; ++index)
		{
			this->mVisibilitySystems[index]->RemoveVisEntity(entity);
		}
	}
	else
	{
		n_assert( VisibilitySystemIndex >=0 && VisibilitySystemIndex < mVisibilitySystems.Size() ); 
		if ( VisibilitySystemIndex >=0 && VisibilitySystemIndex < mVisibilitySystems.Size() )
		{
			mVisibilitySystems[VisibilitySystemIndex]->RemoveVisEntity(entity);
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::AttachVisSystem(const GPtr<VisSystemBase>& system)
{
	IndexT index = this->mVisibilitySystems.FindIndex(system);

    n_assert(InvalidIndex == index );  
	if ( InvalidIndex == index )
	{
		if ( mIsOpen && !system->IsOpen() )
		{
			system->Open( mVisibilitySystems.Size() );
		}
		mVisibilitySystems.Append( system );
	}
	n_assert( mVisibilitySystems.Size() <= VisEntity::MAX_VIS_SYSTEM_COUNT );
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::RemoveVisSystem(const GPtr<VisSystemBase>& system)
{
    IndexT index = this->mVisibilitySystems.FindIndex(system);

    n_assert(InvalidIndex != index);
	if ( InvalidIndex != index )
	{
		this->mVisibilitySystems.EraseIndex(index);
		if ( system->IsOpen() )
		{
			system->Close();
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::UpdateVisEntity(const GPtr<VisEntity>& entity)
{         
	IndexT index;
	SizeT size = this->mVisibilitySystems.Size();
	for (index = 0; index < size; ++index)
    {
        this->mVisibilitySystems[index]->UpdateVisEntity(entity);
    }
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::Open()
{
    n_assert(!this->mIsOpen);    
    IndexT i;
    for (i = 0; i < this->mVisibilitySystems.Size(); ++i)
    {
        this->mVisibilitySystems[i]->Open(i);    	
    }        
    this->mIsOpen = true;        
}

//------------------------------------------------------------------------------
/**
*/
void 
VisServer::Close()
{
    n_assert(this->mIsOpen);
    IndexT i;
    for (i = 0; i < this->mVisibilitySystems.Size(); ++i)
    {
        this->mVisibilitySystems[i]->Close();    	
    }
	mVisibilitySystems.Clear();
    this->mIsOpen = false;
}


//------------------------------------------------------------------------------
/**
*/
void 
VisServer::OnRenderDebug()
{
    IndexT i;
    for (i = 0; i < this->mVisibilitySystems.Size(); ++i)
    {
        this->mVisibilitySystems[i]->OnRenderDebug();                	
    }
}
//------------------------------------------------------------------------
GPtr<VisQuery>
VisServer::PerformVisQuery(const GPtr<ObserverContext>& observer , 
		                                  const Util::Array<IndexT>& systemIndex )
{
	GPtr<VisQuery> pQuery = CreateVisQuery( observer, systemIndex );
	pQuery->Run();
#ifdef __WIN32__ 
	pQuery->WaitForFinished();
#endif
	pQuery->EndQuery();
	return pQuery;
}
//------------------------------------------------------------------------
void 
VisServer::PerformVisQuery( const Util::Array< GPtr<ObserverContext> >& observers , 
								 const Util::Array<IndexT>& systemIndex,
								 Util::Array< GPtr<VisQuery> >& results )
{

	SizeT ObserveSize = observers.Size();
	for ( IndexT index = 0; index < ObserveSize; ++index )
	{
		GPtr<VisQuery> pQuery = CreateVisQuery( observers[index], systemIndex );
		pQuery->Run();
		results.Append( pQuery );
	}

	for ( IndexT index = 0; index < ObserveSize; ++index )
	{
		results[index]->WaitForFinished();
		results[index]->EndQuery();
	}
}
//------------------------------------------------------------------------
GPtr<VisQuery> 
VisServer::CreateVisQuery(const GPtr<ObserverContext>& observer , const Util::Array<IndexT>& systemIndex )
{
	GPtr<VisQuery> pQuery = VisQuery::Create();
	
	if ( !observer.isvalid() )
	{
		return pQuery;
	}

	pQuery->SetObserver( observer );

	if ( systemIndex.Size() == 0 )
	{
		SizeT systemSize = mVisibilitySystems.Size();
		for ( IndexT index = 0; index < systemSize; ++index )
		{
			pQuery->AttachVisSystem( mVisibilitySystems[index] );
		}
	}
	else
	{
		SizeT systemSize = systemIndex.Size();
		for ( IndexT index = 0; index < systemSize; ++index )
		{
			if ( index >=0 && index < mVisibilitySystems.Size() )
			{
				pQuery->AttachVisSystem( mVisibilitySystems[index] );
			}
		}
	}


	
	return pQuery;
}

} // namespace Vis
