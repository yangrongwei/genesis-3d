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
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "appframework/actor.h"
#include "graphicfeature/graphicsfeature.h"
#include "app/basegamefeature/managers/timesource.h"
#include "spriterendercomponent.h"
#include "spriterenderobject.h"
#include "foundation/math/matrix44.h"
#include "foundation/math/float2.h"
#include "foundation/math/float3.h"
#include "foundation/meshbuilder/parallelogrambuilder.h"
#include "sprite/spriteimage.h"
namespace App
{
	using namespace Math;
	__ImplementClass(App::SpriteRenderComponent, 'SPRC', App::SpriteBaseRenderComponent)

	SpriteRenderComponent::SpriteRenderComponent()
					:mPlayOnWake(true)
	{

	}

	SpriteRenderComponent::~SpriteRenderComponent()
	{
		
	}

	void SpriteRenderComponent::OnActivate()
	{
		Super::OnActivate();

		GraphicsFeature::Instance()->eventDeviceReset += Delegates::newDelegate(this, &SpriteRenderComponent::_OnDeviceLost);

#ifndef __GENESIS_EDITOR__
		if (mPlayOnWake)
		{
			Play();
		}
#endif

	}

	void SpriteRenderComponent::OnDeactivate()
	{
		Stop();
		Super::OnDeactivate();
		GraphicsFeature::Instance()->eventDeviceReset -= Delegates::newDelegate(this, &SpriteRenderComponent::_OnDeviceLost);
	}

	void SpriteRenderComponent::StandaloneRender(const GPtr<Graphic::Material>& customMat)
	{
		Graphic::RenderableResUnitArray::Iterator begin = mRenderableResUnitList.Begin();
		Graphic::RenderableResUnitArray::Iterator end = mRenderableResUnitList.End();
		Graphic::GraphicRenderer::ResetCache();
		while(begin != end)
		{
			Graphic::Renderable* rdbl = begin->GetRenderable();
			if (rdbl)
			{
				Graphic::GraphicRenderer::BeforeRender(rdbl, Graphic::eCustomized, customMat.get_unsafe());
				mRenderObject->Render(rdbl, Graphic::eCustomized, customMat.get_unsafe());
			}

			++begin;
		}
	}

	void SpriteRenderComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, OnFrame);
		Super::SetupCallbacks();
	}

	void SpriteRenderComponent::_OnFrame()
	{
		mPlayer.Tick((float)GameTime::Instance()->GetFrameTime());	
		if (mPlayer.IsDirty())
		{
			_Update();
			mPlayer.RemoveDirtyFlag();
		}
	}



	void SpriteRenderComponent::_Update()
	{
		_UpdateBoundingBox();
		if (mPlayer.CanDraw())
		{
			GPtr<Sprite::SpriteImage> image = mPlayer.GetImage();
			if (image->Empty())
			{
				_ClearRenderable();
			}
			else
			{
				_SetImage(image);
			}
		}
		else
		{
			_ClearRenderable();
		}
	}

	void SpriteRenderComponent::Setup(const Resources::ResourceId& packId)
	{

		Super::Setup(packId);
		mPlayer.Reset(&mSpriteInfo);
	}


	void SpriteRenderComponent::SetBlock(const Util::String& blockName)
	{
		mPlayer.SetBlock(blockName);
		if (IsActive())
		{
			_Update();
		}
	}

	void SpriteRenderComponent::MaterialDirty()
	{
		_ClearRenderable();
		mPlayer.Dirty();
	}

	void SpriteRenderComponent::_OnDeviceLost(GraphicsFeature* sender)
	{
		mPlayer.DeviceLost();
	}

	void SpriteRenderComponent::SetAnimation(const Util::String& name, int loops /* = 0  */, bool play /* = true */, float speed /* = 1.0f */)
	{
		mPlayer.SetAnimation(name, loops, speed);
		if (IsActive())
		{
			if (play)
			{
				mPlayer.Play();
			}
			_Update();
		}
	}

	void SpriteRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		Super::CopyFrom(pComponent);
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		if ( IsActive() )
		{
			return;
		}
		
		const GPtr<SpriteRenderComponent> rh = pComponent.downcast<SpriteRenderComponent>();
		mPlayOnWake = rh->mPlayOnWake;
		//mPlayer.CopyFrom(rh->mPlayer);
		if (rh->mPlayer.HasBlcok())
		{
			SetBlock(rh->GetBlockName());
		}
		else
		{
			RemoveBlock();
		}

		if (rh->mPlayer.HasAnimation())
		{
			SetAnimation(rh->GetAnimationName(), rh->GetAnimationLoops(), rh->IsAnimationPlaying(), rh->GetAnimationSpeed());
		}
		else
		{
			RemoveAnimation();
		}
	}





}