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
#include "soundfeature/SoundRes.h"
#include "addons/resource/resourcemanager.h"
#include "soundfeature/components/SoundSourceComponent.h"

namespace App
{

	__ImplementClass(App::SoundRes, 'SDRS' , Core::RefCounted);

	//------------------------------------------------------------------------------
	SoundRes::SoundRes()
		: mName("")
		, mIs3D(false)
		, mDecompressFlag(MEMORY_DECOPRESS)
		, mFrequency(0)
		, mPriority(Resources::ResourcePriority::SoundDefault)
		, mSoundBuffer(NULL)
		, mSoundSystemSource(NULL)
	{}

	//------------------------------------------------------------------------------
	SoundRes::~SoundRes()
	{
		if (mSoundBuffer)
		{
			mSoundBuffer->ReleaseBuffer();
		}
	}

	//------------------------------------------------------------------------------
	bool SoundRes::Init(const Util::String &name, const bool &is3D)
	{
		return SetName(name) && Set3D(is3D);
	}

	//------------------------------------------------------------------------------
	bool SoundRes::SetName(const Util::String &name, int priority)
	{
		if (mName != name)
		{
			mName = name;

			if (mSoundBuffer)
			{
				mSoundBuffer->ReleaseBuffer();
				mSoundBuffer = NULL;
			}
		}
		mPriority = priority;
		return true;
	}

	//------------------------------------------------------------------------------
	bool SoundRes::Set3D(const bool is3D)
	{
		mIs3D = is3D;

		bool ret = false;

		if (mSoundSystemSource)
		{
			ret = mSoundSystemSource->SetMode(mIs3D ? GENESISSOUND_3D_WORLDRELATIVE : 
				GENESISSOUND_3D_HEADRELATIVE );
		}

		return ret;	
	}
	//------------------------------------------------------------------------------
	void SoundRes::SetPriority(const Resources::Priority priority)
	{
		mPriority = priority;
	}

	//------------------------------------------------------------------------------
	Sound::SoundSystemSource* SoundRes::CreateSoundSystemSource()
	{
		if (!mSoundBuffer)
		{
			return mSoundSystemSource = NULL;
		}

		mSoundSystemSource = SoundFeature::Instance()->GetFreeSoundSystemSource(mSoundBuffer);

		return mSoundSystemSource;
	}
	//------------------------------------------------------------------------------
	bool SoundRes::CreateSoundBuffer(const char* nameOrData, SizeT dataSize, 
		GENESISOUND_MODE mode, 
		GENESIS_FILE_FORMAT fileFormat)
	{
		n_assert(SoundFeature::HasInstance());

		mSoundBuffer = SoundFeature::Instance()->CreateSoundBuffer(
			nameOrData, dataSize, 
			mode, fileFormat);

		if (mSoundBuffer == NULL)
			return false;
		else
			return true;
	}

	//------------------------------------------------------------------------------
	void SoundRes::SetSoundSystemSource( Sound::SoundSystemSource *ptr )
	{
		mSoundSystemSource = ptr;
	}
	//------------------------------------------------------------------------------
	Sound::SoundSystemSource* SoundRes::GetSoundSystemSource() const
	{
		return mSoundSystemSource;
	}


	//------------------------------------------------------------------------------
	uint SoundRes::GetLength(void) const
	{
		n_assert(!mName.IsEmpty());
		n_assert(SoundFeature::HasInstance());

		return 0;
	}
	//------------------------------------------------------------------------------
	uint SoundRes::GetFrequency() const
	{
		return mFrequency;
	}
	//------------------------------------------------------------------------------
	int SoundRes::GetDecompressFlag(void) const
	{
		return mDecompressFlag;
	}
	//------------------------------------------------------------------------------
	void SoundRes::SetDecompressFlag(const int flag)
	{
		if (flag<LOAD_DECOMPRESS || flag>STREAM_DECOPRESS)
		{
			mDecompressFlag = MEMORY_DECOPRESS;
		}
		else
		{
			mDecompressFlag = flag;
		}

		return;
	}
	//--------------------------------------------------------------------------------
	bool SoundRes::IsSoundValiad()
	{
		return mSoundBuffer != NULL;
	}

	void SoundRes::Discard()
	{
		if (mSoundBuffer)
		{
			mSoundBuffer->ReleaseBuffer();
			mSoundBuffer = NULL;
		}
	}
	//--------------------------------------------------------------------------------
	void SoundRes::CopyFrom(const SoundRes& src)
	{
		mName = src.GetName();
		mIs3D = src.Is3D();

		//Because 'mSoundSystemSource' need a new value when copying, so must 
		//set its value to null. Then when execute 'SoundSource::Play(void)',
		//'mSoundSystemSource' will be assigned to a new value.
		mSoundSystemSource = NULL;

		mDecompressFlag = src.GetDecompressFlag();
		mFrequency = src.GetFrequency();
	}

} // namespace App




#endif //__SOUND_COMMIT__
