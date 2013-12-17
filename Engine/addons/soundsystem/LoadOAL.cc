/*
 * Copyright (c) 2006, Creative Labs Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * 	     the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 * 	     and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of Creative Labs Inc. nor the names of its contributors may be used to endorse or
 * 	     promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "LoadOAL.h"

#ifdef __WIN32__
#include "windows.h"
#define GLoadLibrary(path) LoadLibrary(path)
#define GGetProcAddress(handle,name) GetProcAddress(handle,name)
#define GFreeLibrary(handle) FreeLibrary(handle)

#define GOutputDebugString(str) OutputDebugString(str)
HINSTANCE g_hOpenALDLL = NULL;

#elif __ANDROID__
#include "dlfcn.h" 
#include "core/android/precompiled.h"

#define GLoadLibrary(path) dlopen(path,RTLD_LAZY)
#define GGetProcAddress(handle,name)  dlsym(handle, name)
#define GFreeLibrary(handle) dlclose(handle)

#define GOutputDebugString(str) LOGI(str)

void* g_hOpenALDLL = 0;

#elif __OSX__
#include <stdio.h>
#include <memory.h>

#define GLoadLibrary(path) NULL
#define GGetProcAddress(handle,name) 
#define GFreeLibrary(handle) 

#define GOutputDebugString(str) printf(str)

void* g_hOpenALDLL = 0;
#endif




ALboolean LoadOAL10Library(char *szOALFullPathName, LPOPENALFNTABLE lpOALFnTable)
{
	if (!lpOALFnTable)
		return AL_FALSE;

	if (szOALFullPathName)
	{
		g_hOpenALDLL = GLoadLibrary(szOALFullPathName);
	}
	else
	{
#ifdef __ANDROID__
// 		g_hOpenALDLL = GLoadLibrary("/data/data/com.android.test/lib/libOpenAL32.so");
		
#else
// 		g_hOpenALDLL = GLoadLibrary("openal32.dll");
		
#endif
	}
	
	

	memset(lpOALFnTable, 0, sizeof(OPENALFNTABLE));

	// Get function pointers
	lpOALFnTable->alEnable = (LPALENABLE)alEnable;
	if (lpOALFnTable->alEnable == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alEnable' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDisable = (LPALDISABLE)alDisable;
	if (lpOALFnTable->alDisable == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDisable' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alIsEnabled = (LPALISENABLED)alIsEnabled;
	if (lpOALFnTable->alIsEnabled == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alIsEnabled' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetBoolean = (LPALGETBOOLEAN)alGetBoolean;
	if (lpOALFnTable->alGetBoolean == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetBoolean' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetInteger = (LPALGETINTEGER)alGetInteger;
	if (lpOALFnTable->alGetInteger == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetInteger' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetFloat = (LPALGETFLOAT)alGetFloat;
	if (lpOALFnTable->alGetFloat == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetFloat' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetDouble = (LPALGETDOUBLE)alGetDouble;
	if (lpOALFnTable->alGetDouble == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetDouble' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetBooleanv = (LPALGETBOOLEANV)alGetBooleanv;
	if (lpOALFnTable->alGetBooleanv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetBooleanv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetIntegerv = (LPALGETINTEGERV)alGetIntegerv;
	if (lpOALFnTable->alGetIntegerv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetIntegerv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetFloatv = (LPALGETFLOATV)alGetFloatv;
	if (lpOALFnTable->alGetFloatv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetFloatv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetDoublev = (LPALGETDOUBLEV)alGetDoublev;
	if (lpOALFnTable->alGetDoublev == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetDoublev' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetString = (LPALGETSTRING)alGetString;
	if (lpOALFnTable->alGetString == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetString' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetError = (LPALGETERROR)alGetError;
	if (lpOALFnTable->alGetError == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetError' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alIsExtensionPresent = (LPALISEXTENSIONPRESENT)alIsExtensionPresent;
	if (lpOALFnTable->alIsExtensionPresent == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alIsExtensionPresent' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetProcAddress = (LPALGETPROCADDRESS)alGetProcAddress;
	if (lpOALFnTable->alGetProcAddress == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetProcAddress' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetEnumValue = (LPALGETENUMVALUE)alGetEnumValue;
	if (lpOALFnTable->alGetEnumValue == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetEnumValue' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alListeneri = (LPALLISTENERI)alListeneri;
	if (lpOALFnTable->alListeneri == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alListeneri' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alListenerf = (LPALLISTENERF)alListenerf;
	if (lpOALFnTable->alListenerf == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alListenerf' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alListener3f = (LPALLISTENER3F)alListener3f;
	if (lpOALFnTable->alListener3f == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alListener3f' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alListenerfv = (LPALLISTENERFV)alListenerfv;
	if (lpOALFnTable->alListenerfv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alListenerfv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetListeneri = (LPALGETLISTENERI)alGetListeneri;
	if (lpOALFnTable->alGetListeneri == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetListeneri' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetListenerf =(LPALGETLISTENERF)alGetListenerf;
	if (lpOALFnTable->alGetListenerf == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetListenerf' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetListener3f = (LPALGETLISTENER3F)alGetListener3f;
	if (lpOALFnTable->alGetListener3f == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetListener3f' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetListenerfv = (LPALGETLISTENERFV)alGetListenerfv;
	if (lpOALFnTable->alGetListenerfv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetListenerfv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGenSources = (LPALGENSOURCES)alGenSources;
	if (lpOALFnTable->alGenSources == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGenSources' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDeleteSources = (LPALDELETESOURCES)alDeleteSources;
	if (lpOALFnTable->alDeleteSources == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDeleteSources' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alIsSource = (LPALISSOURCE)alIsSource;
	if (lpOALFnTable->alIsSource == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alIsSource' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcei = (LPALSOURCEI)alSourcei;
	if (lpOALFnTable->alSourcei == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcei' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcef = (LPALSOURCEF)alSourcef;
	if (lpOALFnTable->alSourcef == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcef' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSource3f = (LPALSOURCE3F)alSource3f;
	if (lpOALFnTable->alSource3f == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSource3f' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcefv = (LPALSOURCEFV)alSourcefv;
	if (lpOALFnTable->alSourcefv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcefv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetSourcei = (LPALGETSOURCEI)alGetSourcei;
	if (lpOALFnTable->alGetSourcei == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetSourcei' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetSourcef = (LPALGETSOURCEF)alGetSourcef;
	if (lpOALFnTable->alGetSourcef == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetSourcef' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetSourcefv = (LPALGETSOURCEFV)alGetSourcefv;
	if (lpOALFnTable->alGetSourcefv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetSourcefv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcePlayv = (LPALSOURCEPLAYV)alSourcePlayv;
	if (lpOALFnTable->alSourcePlayv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcePlayv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourceStopv = (LPALSOURCESTOPV)alSourceStopv;
	if (lpOALFnTable->alSourceStopv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourceStopv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcePlay = (LPALSOURCEPLAY)alSourcePlay;
	if (lpOALFnTable->alSourcePlay == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcePlay' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourcePause = (LPALSOURCEPAUSE)alSourcePause;
	if (lpOALFnTable->alSourcePause == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourcePause' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourceStop = (LPALSOURCESTOP)alSourceStop;
	if (lpOALFnTable->alSourceStop == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourceStop' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGenBuffers = (LPALGENBUFFERS)alGenBuffers;
	if (lpOALFnTable->alGenBuffers == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGenBuffers' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDeleteBuffers = (LPALDELETEBUFFERS)alDeleteBuffers;
	if (lpOALFnTable->alDeleteBuffers == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDeleteBuffers' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alIsBuffer = (LPALISBUFFER)alIsBuffer;
	if (lpOALFnTable->alIsBuffer == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alIsBuffer' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alBufferData = (LPALBUFFERDATA)alBufferData;
	if (lpOALFnTable->alBufferData == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alBufferData' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetBufferi = (LPALGETBUFFERI)alGetBufferi;
	if (lpOALFnTable->alGetBufferi == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetBufferi' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alGetBufferf = (LPALGETBUFFERF)alGetBufferf;
	if (lpOALFnTable->alGetBufferf == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alGetBufferf' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourceQueueBuffers = (LPALSOURCEQUEUEBUFFERS)alSourceQueueBuffers;
	if (lpOALFnTable->alSourceQueueBuffers == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourceQueueBuffers' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alSourceUnqueueBuffers = (LPALSOURCEUNQUEUEBUFFERS)alSourceUnqueueBuffers;
	if (lpOALFnTable->alSourceUnqueueBuffers == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alSourceUnqueueBuffers' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDistanceModel = (LPALDISTANCEMODEL)alDistanceModel;
	if (lpOALFnTable->alDistanceModel == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDistanceModel' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDopplerFactor = (LPALDOPPLERFACTOR)alDopplerFactor;
	if (lpOALFnTable->alDopplerFactor == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDopplerFactor' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alDopplerVelocity = (LPALDOPPLERVELOCITY)alDopplerVelocity;
	if (lpOALFnTable->alDopplerVelocity == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alDopplerVelocity' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetString = (LPALCGETSTRING)alcGetString;
	if (lpOALFnTable->alcGetString == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetString' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetIntegerv = (LPALCGETINTEGERV)alcGetIntegerv;
	if (lpOALFnTable->alcGetIntegerv == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetIntegerv' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcOpenDevice = (LPALCOPENDEVICE)alcOpenDevice;
	if (lpOALFnTable->alcOpenDevice == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcOpenDevice' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcCloseDevice = (LPALCCLOSEDEVICE)alcCloseDevice;
	if (lpOALFnTable->alcCloseDevice == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcCloseDevice' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcCreateContext = (LPALCCREATECONTEXT)alcCreateContext;
	if (lpOALFnTable->alcCreateContext == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcCreateContext' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcMakeContextCurrent = (LPALCMAKECONTEXTCURRENT)alcMakeContextCurrent;
	if (lpOALFnTable->alcMakeContextCurrent == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcMakeContextCurrent' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcProcessContext = (LPALCPROCESSCONTEXT)alcProcessContext;
	if (lpOALFnTable->alcProcessContext == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcProcessContext' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetCurrentContext = (LPALCGETCURRENTCONTEXT)alcGetCurrentContext;
	if (lpOALFnTable->alcGetCurrentContext == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetCurrentContext' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetContextsDevice = (LPALCGETCONTEXTSDEVICE)alcGetContextsDevice;
	if (lpOALFnTable->alcGetContextsDevice == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetContextsDevice' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcSuspendContext = (LPALCSUSPENDCONTEXT)alcSuspendContext;
	if (lpOALFnTable->alcSuspendContext == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcSuspendContext' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcDestroyContext = (LPALCDESTROYCONTEXT)alcDestroyContext;
	if (lpOALFnTable->alcDestroyContext == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcDestroyContext' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetError = (LPALCGETERROR)alcGetError;
	if (lpOALFnTable->alcGetError == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetError' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcIsExtensionPresent = (LPALCISEXTENSIONPRESENT)alcIsExtensionPresent;
	if (lpOALFnTable->alcIsExtensionPresent == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcIsExtensionPresent' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetProcAddress = (LPALCGETPROCADDRESS)alcGetProcAddress;
	if (lpOALFnTable->alcGetProcAddress == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetProcAddress' function address\n");
		return AL_FALSE;
	}
	lpOALFnTable->alcGetEnumValue = (LPALCGETENUMVALUE)alcGetEnumValue;
	if (lpOALFnTable->alcGetEnumValue == NULL)
	{
		GOutputDebugString("Failed to retrieve 'alcGetEnumValue' function address\n");
		return AL_FALSE;
	}

	return AL_TRUE;
}

ALvoid UnloadOAL10Library()
{
	// Unload the dll
	
	
}

