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
#ifndef __SoundSystemDspOpenAL_H__
#define __SoundSystemDspOpenAL_H__
#ifndef __SOUND_COMMIT__

#include "core/refcounted.h"
#include "SoundBuffer.h"
#include "util/array.h"
#include "core/singleton.h"
#include "GenesisSound.h"
#include "SoundSystemDSP.h"


namespace Sound
{
	class SoundSystemDSPOpenAL :  public SoundSystemDSP
	{
		__DeclareSubClass(SoundSystemDSPOpenAL, SoundSystemDSP);
	public:
		SoundSystemDSPOpenAL();
		virtual ~SoundSystemDSPOpenAL();

		virtual bool init(ALuint type);
		virtual bool uninit();
		virtual bool remove();
		virtual uint getType(){ return m_type; }
		virtual bool setParameter(int index, float value, bool integer = false);
		virtual bool setParameters(int index, float*);
		virtual bool apply(SoundSystemSource* sss, int sendIndex);
		virtual bool unapply(SoundSystemSource* sss);
		int GetSendIndex() { return m_sendIndex; }

	protected:
		ALuint m_type;
		ALuint m_uiEffectSlot;	// effect slot
		ALuint m_uiFilter;		// filter
		int    m_sendIndex;
	};
}

#endif // __SOUND_COMMIT__
#endif//__SoundSystemDspOpenAL_H__