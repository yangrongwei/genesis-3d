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
#ifndef __SoundListenerComponent_H__
#define __SoundListenerComponent_H__

#include "appframework/component.h"
#include "soundfeature/SoundFeature.h"

namespace App
{

	class SoundListener : public Component
	{
		__DeclareSubClass(SoundListener, Component);
	public:
		SoundListener();
		virtual ~SoundListener();

		virtual void OnActivate();
		/// called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		virtual void UpdateListenerInfo();
		const Math::vector& GetPosition() const { return mLatestPos; }

		void AttachFilters();

		void SetVolume(float volume);
		float GetVolume ();

		//	Serialization
	public:	
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		virtual void SetupAllResource();
		virtual bool IsAllResourceLoaded();

	private:
		Math::vector        mLatestPos;
	};

}

#endif //__SoundListenerComponent_H__

