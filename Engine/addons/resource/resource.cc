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
#include "resource/resource_stdneb.h"
#include "exception/exceptions.h"
#include "resource/resource.h"
#include "util/delegate.h"
#include "resource/resourcemanager.h"


namespace Resources
{
	__ImplementClass(Resources::Resource, 'RSRC', Core::RefCounted);
	__ImplementClass(Resources::ResourceLoader, 'RSRL', Core::RefCounted);
	__ImplementClass(Resources::ResourceSaver, 'RSRS', Core::RefCounted);
	__ImplementClass(Resources::ResourceNotifier, 'RSRN', Core::RefCounted);





	ResourceId Resource::EmptyResID;

	//------------------------------------------------------------------------

	Resource::Resource() 
		: mState(UnLoaded)
		, mAsynProcessingIndex(0)
		, mManuLoad(false)

	{
		// empty
	}

	//------------------------------------------------------------------------
	Resource::~Resource()    
	{
		n_assert( mNotifierList.IsEmpty() ) ;
	}
	//------------------------------------------------------------------------
	void 
		Resource::AttachNotifier(const WeakPtr<ResourceNotifier>& notifier )
	{
		if ( notifier.isvalid() )
		{
			notifier->Attach( this );
			mNotifierList.Append( notifier );
		}
	}
	//------------------------------------------------------------------------
	void 
		Resource::DeattachNotifier(const WeakPtr<ResourceNotifier>& notifier)
	{
		IndexT findIndex = mNotifierList.FindIndex( notifier );
		if ( findIndex != InvalidIndex )
		{
			notifier->Deattach(this);
			mNotifierList.EraseIndex(findIndex);
		}
	}
	//------------------------------------------------------------------------
	bool 
		Resource::Load( const GPtr<ResourceLoader>& pLoader )
	{
		bool bLoadOK = false;

		if ( pLoader.isvalid() )
		{
			try
			{
				bLoadOK = pLoader->LoadResource( this );
			}
			catch(const Exceptions::Exception& e)
			{
				n_warning("Resource load error: %s", e.what());
				bLoadOK = false;
			}
			catch (...)
			{
				bLoadOK = false;
			}
		}

		if ( bLoadOK )
		{
			// 有数据改变，可能是新加载或者再次加载
			SetState(Loaded);
		}
		else
		{
			n_warning("Resource::Load %s Falied:\n" ,mResourceID.AsString().AsCharPtr() );

			//数据失效了，已经有的全部卸载。
			UnLoadImpl();

			SetState(Failed );
		}

		return bLoadOK;
	}
	//------------------------------------------------------------------------
	bool 
		Resource::Save( const GPtr<ResourceSaver>& pSaver )
	{
		bool bSaveOK = false;

		if ( pSaver.isvalid() && mState==Loaded )
		{

			try
			{
				bSaveOK = pSaver->SaveResource(this);
			}
			catch (...)
			{
				bSaveOK = false;
			}
		}

		if ( !bSaveOK )
		{
			n_warning("Resource::Save %s Falied:\n" ,mResourceID.AsString().AsCharPtr() );
		}

		return bSaveOK;
	}
	//------------------------------------------------------------------------
	void 
		Resource::UnLoad()
	{
		if ( GetState() != UnLoaded )
		{
			UnLoadImpl();
			SetState( UnLoaded );
		}
	}
	//------------------------------------------------------------------------
	bool 
		Resource::SwapLoad(const GPtr<Resource>& tempRes )
	{
		bool bSwapOK = false;

		if ( tempRes.isvalid() && tempRes->GetState() == Loaded )
		{
			try
			{
				bSwapOK = SwapLoadImpl( tempRes );
			}
			catch (...)
			{
				bSwapOK = false;
			}
		}

		//进行状态切换
		if ( bSwapOK )
		{
			// 有数据改变，无论状态是否真正改变，都发出一次通知。
			SetState(Loaded);
		}
		else
		{
			n_warning("Resource::SwapLoad %s Falied:\n" ,mResourceID.AsString().AsCharPtr() );

			// 执行了交换操作，但是数据交换失败，认为已经有的数据全部失效了
			UnLoadImpl();

			SetState( Failed );
		}

		return bSwapOK;
	}
	//------------------------------------------------------------------------
	void 
		Resource::SetState( State newState)
	{
		State oldState = mState;

		mState = newState;

		//	if(newState != Resources::Resource::Loaded)
		//		return;
		IndexT size = mNotifierList.Size();
		for ( IndexT index = 0; index < size; ++index )
		{
			n_assert( mNotifierList[index].isvalid() );
			mNotifierList[index]->Notify( this, oldState );
		}

	}
	//------------------------------------------------------------------------
	bool 
		Resource::SwapLoadImpl( const GPtr<Resource>& tempRes)
	{
		// should impl in Derived Resource
		return false;
	}
	//------------------------------------------------------------------------
	void Resource::UnLoadImpl(void)
	{
		// should impl in Derived Resource
	}
	//------------------------------------------------------------------------
	SizeT Resource::CalculateRuntimeSize(void) const
	{
		return sizeof(Resource);
	}
	//------------------------------------------------------------------------
	void Resource::InitLoadParam( const GPtr<Resource>& res )
	{
		mState = res->GetState();
		mResourceID = res->GetResourceId();
	}

}
