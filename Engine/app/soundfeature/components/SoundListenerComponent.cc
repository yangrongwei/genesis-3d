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
#ifndef __SOUND_COMMIT__
#include "stdneb.h"
#include "io/assignregistry.h"
#include "math/scalar.h"
#include "appframework/actor.h"
#include "basegamefeature/managers/timesource.h"

#include "SoundListenerComponent.h"
#include "soundfeature/components/SoundFilterComponent.h"

namespace App
{

	__ImplementClass(SoundListener, 'SLCP', Component);

	//------------------------------------------------------------------------------
	SoundListener::SoundListener() {}

	//------------------------------------------------------------------------------
	SoundListener::~SoundListener() {}

	//------------------------------------------------------------------------------
	void SoundListener::OnActivate()
	{
		n_assert(mActor);
		n_assert(SoundFeature::HasInstance());
		Super::OnActivate();

		SoundFeature::Instance()->AttachSoundListener(this);
		AttachFilters();
		return;
	}
	//------------------------------------------------------------------------------
	void SoundListener::OnDeactivate()
	{
		n_assert(mActor);
		n_assert(SoundFeature::HasInstance());
		Super::OnDeactivate();

		SoundFeature::Instance()->DetachSoundListener(this);
		return;
	}
	//------------------------------------------------------------------------------
	void SoundListener::UpdateListenerInfo()
	{
		n_assert(mActor);

		const Math::vector pos = mActor->GetWorldPosition();

		double dFrameTime = GameTime::Instance()->GetFrameTime();
		float frameTime = static_cast<float>(dFrameTime);
		float inverseFrameTime = SoundFeature::Instance()->CalcInvFrameTime(frameTime);
		Math::vector vel = (pos - mLatestPos) * inverseFrameTime;

		const Math::matrix44& transform = mActor->GetWorldTransform();
		Math::float4 ZAxis = transform.get_zaxis();
		Math::float3 forward( ZAxis.x(), ZAxis.y(), ZAxis.z() );
		forward = Math::float3::normalize(forward);
		Math::float4 YAxis = transform.get_yaxis();
		Math::float3 up( YAxis.x(), YAxis.y(), YAxis.z() );
		up = Math::float3::normalize(up);

		mLatestPos = pos;

		SoundFeature::Instance()->UpdateListenerAttrs(pos, vel,
			Math::vector( forward.x(), forward.y(), forward.z() ),
			Math::vector( up.x(), up.y(), up.z() )
			);

		return;
	}
	//------------------------------------------------------------------------------
	void SoundListener::SetVolume(float volume)
	{
		SoundFeature::Instance()->SetVolume(volume);
	}
	//------------------------------------------------------------------------------
	float SoundListener::GetVolume()
	{
		return SoundFeature::Instance()->GetVolume();
	}
	//------------------------------------------------------------------------------
	void SoundListener::AttachFilters()
	{
		const Actor* actor = GetActor();
		Util::Array<GPtr<Component> > FilterArray = actor->FindComponents(SoundFilterComponent::RTTI);

		if (FilterArray.Size()>0)
		{
			for (int i=0;i<FilterArray.Size();i++)
			{
				GPtr<SoundFilterComponent> pSoundFilter = FilterArray[i].downcast<SoundFilterComponent>();

				if (pSoundFilter.isvalid())
				{
					pSoundFilter->SetDspParamter();
				}
			}
		}	
	}

	//----------------------------------------------------------------------------------
	// copy from other component
	void SoundListener::CopyFrom( const GPtr<Component>& pComponent )
	{

	}

	void SoundListener::SetupAllResource()
	{
		return;
	}

	bool SoundListener::IsAllResourceLoaded()
	{
		return true;
	}

}
#endif


