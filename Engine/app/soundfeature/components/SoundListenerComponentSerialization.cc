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
#ifndef __SoundListenerComponentSerialization_H__
#define __SoundListenerComponentSerialization_H__

#include "stdneb.h"
#include "SoundListenerComponent.h"

namespace App
{

	class SoundListenerComponentSerialization
	{
	public:
		SoundListenerComponentSerialization(const SoundListener* pComponent)
			: mObject(pComponent) 
		{}

		~SoundListenerComponentSerialization() {}

		inline void Load(Version ver, AppReader* pReader)
		{
			switch (ver)
			{
			case 1:
				{
					Load_1(pReader);
					break;
				}
			default:
				{
					n_error(" SoundSourceComponentSerialization::Load unknonw version " );
					break;
				}
			}

			return;
		}

		void Load_1(AppReader* pReader);
		void Save(AppWriter* pWriter);

	protected:
		const SoundListener* mObject;
	}; //class SoundSourceComponentSerialization



	/// 

	//------------------------------------------------------------------------------
	void SoundListenerComponentSerialization::Load_1(AppReader* pReader)
	{
		n_assert(mObject);

		return;
	}

	//------------------------------------------------------------------------------
	void SoundListenerComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);

		return;
	}

	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SoundListener::GetVersion() const
	{
		return 1;	//	Current version number is 1.
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void SoundListener::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SoundListenerComponentSerialization serialize(this);
		serialize.Load(ver, pReader);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void SoundListener::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SoundListenerComponentSerialization serialize(this);
		serialize.Save(pWriter);
	}

}

#endif //__SoundListenerComponentSerialization_H__

#endif //__SOUND_COMMIT__
