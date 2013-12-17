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
#include "apprenderobject.h"
#include "appframework/actor.h"
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicsystem/Camera/RenderPipeline/RenderData.h"
namespace App
{
	__ImplementClass(AppRenderObject,'AROB',Graphic::RenderObject)

	AppRenderObject::AppRenderObject()
		:mOwner(NULL)
	{

	}
	AppRenderObject::~AppRenderObject()
	{

	}
	void AppRenderObject::AddToCollection(Graphic::RenderDataCollection* collection)
	{
		//check castshadows
		Graphic::RenderDataCollection::UseFor useFor = collection->GetUseFor();
		bool bCastShadow = this->GetCastShadow();
		bool bLMUsed = this->IsUseLM() && this->IsLMHandleValid();

		if (useFor == Graphic::RenderDataCollection::Shadow && (!bCastShadow || bLMUsed))
		{
			return;
		}

		const Graphic::RenderableResUnitArray& list = mOwner->GetRenderResource();
		Graphic::RenderableResUnitArray::Iterator begin = list.Begin();
		Graphic::RenderableResUnitArray::Iterator end = list.End();
		while(begin != end)
		{
			if (begin->Complete())
			{
				collection->Push(begin->GetRenderable());
			}
			++begin;
		}
	}

	void AppRenderObject::OnWillRenderObject(Graphic::Camera* sender)
	{
		mOwner->OnWillRenderObject(sender);
	}

	void AppRenderObject::SetOwner(RenderComponent* owner)
	{
		mOwner = owner;
		if (mOwner->GetActor())
		{
			SetLayerID(mOwner->GetActor()->GetLayerID());
		}
	}
}