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
#include "appframework/actor.h"
#include "math/scalar.h"
#include "basegamefeature/managers/timesource.h"
#include "soundfeature/components/SoundSourceComponent.h"
#include "SoundFilterComponent.h"
#include "soundsystem/SoundSystemSource.h"

namespace App
{

	__ImplementClass(SoundFilterComponent, 'SFCP', Component);

	//------------------------------------------------------------------------------
	SoundFilterComponent::SoundFilterComponent(): mDSP(NULL), mDspType(NULL) {}
	//------------------------------------------------------------------------------
	SoundFilterComponent::~SoundFilterComponent ()
	{
		Uninit();
	}
	//------------------------------------------------------------------------------
	void SoundFilterComponent::Uninit()
	{
		if (mDSP)
		{
			mDSP->uninit();
			mDSP = NULL;
		}
	}
	//------------------------------------------------------------------------------
	void SoundFilterComponent::Setup()
	{	
		if ( mDSP.isvalid() )
		{
			return;
		}

		bool result = SoundFeature::Instance()->GetSoundSystem()->createDSPByType( mDspType, mDSP);
	}
	//------------------------------------------------------------------------------
	GPtr<Sound::SoundSystemDSP> SoundFilterComponent::GetDSP()
	{
		if (!mDSP)
			Setup();
		return mDSP;	
	}
	//------------------------------------------------------------------------------
	void SoundFilterComponent::OnActivate()
	{
		Super::OnActivate();
		Attach();
	}
	//------------------------------------------------------------------------------
	void SoundFilterComponent::OnDeactivate()
	{
		Super::OnDeactivate();

		Detach();
	}

	void SoundFilterComponent::SetDspParamter()
	{
		//empty
	}

	void SoundFilterComponent::AttachFilter(FilterState fs, int iSendIndex)
	{
		const Actor* actor = GetActor();
		if (!actor)
			return;

		GPtr<Component> soundSourceCom = actor->FindComponent(SoundSource::RTTI);

		if (soundSourceCom.isvalid() )
		{
			GPtr<SoundSource> pSoundSource = soundSourceCom.downcast<SoundSource>();

			if (!pSoundSource.isvalid() )
				return;

			if ( fs == __Active)
				mDSP->apply( pSoundSource->GetSoundSystemSource(), iSendIndex);
			else
				mDSP->unapply( pSoundSource->GetSoundSystemSource() );
		}
		else
		{
			GPtr<Component> com = actor->FindComponent(SoundListener::RTTI);
			if ( !com.isvalid() )
				return;

			GPtr<SoundListener> pListener = com.downcast<SoundListener>();
			if(!pListener.isvalid())
				return;

			if ( fs == __Active )
				pListener->AttachFilters();
			else
				;	// TODO
		}
	}


	void SoundFilterComponent::Attach()
	{
		const Actor* actor = GetActor();
		Util::Array<GPtr<Component> > FilterArray = actor->FindComponents(SoundFilterComponent::RTTI);
		int iNewSendIndex = 0;
		int iExistSendIndex = 0;
		int iTempIndex = 0;
		while(true)
		{
			iTempIndex = iNewSendIndex;
			for (int i=0;i<FilterArray.Size();i++)
			{
				GPtr<SoundFilterComponent> pSoundFilter = FilterArray[i].downcast<SoundFilterComponent>();

				if (!pSoundFilter.isvalid() )
				{
					continue;
				}

				if (this == pSoundFilter)
				{
					continue;
				}

				GPtr<Sound::SoundSystemDSP> dsp = pSoundFilter->GetDSP();
				if (dsp.isvalid() )
				{
					uint dspType = dsp->getType();
					if (AL_FILTER_LOWPASS == dspType )
					{
						continue;
					}

					iExistSendIndex = dsp->GetSendIndex();
					if ( iExistSendIndex == iNewSendIndex)
					{
						iNewSendIndex++;
						break;
					}
				}
			}

			if (iTempIndex == iNewSendIndex)
			{
				break;
			}
		}

		AttachFilter(__Active, iNewSendIndex);
	}

	void SoundFilterComponent::Detach()
	{
		const Actor* actor = GetActor();
		if (!actor)
			return;

		AttachFilter(__Deactive, NULL);
	}

}
#endif //__SOUND_COMMIT__

