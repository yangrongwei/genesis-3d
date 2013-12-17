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
#ifndef __SoundRes_H__
#define __SoundRes_H__

#ifndef __SOUND_COMMIT__

#include "core/refcounted.h"
#include "soundfeature/SoundFeature.h"
#include "addons/resource/audiores.h"


#include "soundsystem/SoundBuffer.h"
#include "soundsystem/SoundSystemSource.h"

namespace App
{

	class SoundSource;

	class SoundRes : public Core::RefCounted
	{
		__DeclareClass(SoundRes)
	public:
		enum  {
			LOAD_DECOMPRESS = 0,
			MEMORY_DECOPRESS = 1,
			STREAM_DECOPRESS = 2,
			DECOPRESS_COUNT
		};

		SoundRes();
		virtual ~SoundRes();

		bool Init(const Util::String &name, const bool &is3D = false);

		void Discard();

		const Util::String& GetName(void) const { return mName; }
		bool SetName(const Util::String &name, int priority = 1);

		Resources::Priority GetPriority(void) const { return mPriority; }
		void SetPriority(const Resources::Priority priority);

		bool Is3D() const { return mIs3D; }
		bool Set3D(const bool is3D);

		int GetDecompressFlag(void) const;
		void SetDecompressFlag(const int flag);

		Sound::SoundSystemSource* CreateSoundSystemSource();

		bool CreateSoundBuffer(const char* nameOrData, SizeT dataSize, 
			GENESISOUND_MODE mode,
			GENESIS_FILE_FORMAT fileFormat);

		void SetSoundSystemSource(Sound::SoundSystemSource *ptr);
		Sound::SoundSystemSource* GetSoundSystemSource() const;


		uint GetLength(void) const;

		uint GetFrequency() const;

		bool IsSoundValiad();

		void CopyFrom(const SoundRes& src);
	private:
		Util::String		mName;
		Resources::Priority	mPriority;
		bool				mIs3D;
		int                 mDecompressFlag;
		uint                mFrequency;

		Sound::SoundBuffer*           mSoundBuffer; 
		Sound::SoundSystemSource*     mSoundSystemSource;
	};

}

#endif // __SOUND_COMMIT__

#endif //__SoundRes_H__

