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
#include "resource/audiores.h"

namespace Resources
{
	__ImplementClass(Resources::AudioRes, 'AUDR', Resources::Resource);

	//------------------------------------------------------------------------
	AudioRes::AudioRes()
		: mSize(0)
		, mRaw(NULL)
	{
	}

	//------------------------------------------------------------------------
	AudioRes::~AudioRes()
	{
		if ( mRaw )
		{
			n_delete_array(mRaw);
			mRaw = NULL;
		}
		mSize = 0;
	}

	//------------------------------------------------------------------------
	void AudioRes::Setup(const SizeT size)
	{
		if ( size <= 0 )
		{
			mSize = 0;
			if ( mRaw )
			{
				n_delete_array(mRaw);
				mRaw = NULL;
			}
		}
		else if ( mSize != size )
		{
			if ( mRaw )
			{
				n_delete_array(mRaw);
				mRaw = NULL;
			}

			mSize = size;
			mRaw = n_new_array(char,mSize);
		}
		else	//	mSize = size
		{
			n_assert(mRaw);
		}
	}
	//--------------------------------------------------------------------------------
	bool AudioRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{
		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<AudioRes> tempAudioRes = tempRes.downcast<AudioRes>();
			n_assert( tempAudioRes.isvalid() );
			this->Setup(tempAudioRes->mSize);
			memcpy(this->mRaw, tempAudioRes->mRaw, this->mSize);
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------
	void AudioRes::UnLoadImpl(void)
	{
		this->mRaw = NULL;
		this->mSize = 0;
	}
}
