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
#ifndef __SoundSystemDSP_H__
#define __SoundSystemDSP_H__
#ifndef __SOUND_COMMIT__

#include "core/refcounted.h"
#include "SoundBuffer.h"
#include "util/array.h"
#include "core/singleton.h"
#include "GenesisSound.h"

namespace Sound
{
	class SoundSystemSource;

	class SoundSystemDSP :  public Core::RefCounted
	{
		__DeclareClass(SoundSystemDSP);
	public:

		SoundSystemDSP();
		virtual ~SoundSystemDSP();

		virtual bool init(uint type) { return true; }
		virtual bool uninit(){ return true;}
		virtual bool remove(){ return true;}
		virtual bool setParameter(int index, float value, bool integer = false){ return true; }
		virtual bool setParameters(int index, float*) { return true;}
		virtual uint getType() { return 0; }
		virtual bool apply(SoundSystemSource* sss, int sendIndex) { return true; }
		virtual bool unapply(SoundSystemSource* sss) { return true; }
		virtual int GetSendIndex() { return 0; }
	};
}

#endif // __SOUND_COMMIT__
#endif//__SoundSystemDSP_H__