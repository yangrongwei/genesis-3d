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
#ifndef __SOUNDFILTERCOMPONENT_H__
#define __SOUNDFILTERCOMPONENT_H__

#include "appframework/component.h"
#include "soundfeature/SoundFeature.h"
#include "soundsystem/SoundSystemDSP.h"

#include "soundsystem/Framework.h"



namespace App
{

	class SoundFilterComponent : public Component
	{
		__DeclareSubClass(SoundFilterComponent, Component);
	public:
		SoundFilterComponent();
		virtual ~SoundFilterComponent();

		GPtr<Sound::SoundSystemDSP> GetDSP();

		void Setup();
		void Uninit();

		enum FilterState
		{
			__Active,
			__Deactive
		};

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();
		/// called from Actor::DeactivateComponents()
		virtual void OnDeactivate();
		virtual void SetDspParamter();
		virtual void AttachFilter(FilterState fs, int iSendIndex);

		// Attach & Detach For Script
		void	Attach();
		void	Detach();

	protected:

		GPtr<Sound::SoundSystemDSP>		mDSP;
		uint							mDspType;
	};

}



#endif // __SOUNDFILTERCOMPONENT_H__