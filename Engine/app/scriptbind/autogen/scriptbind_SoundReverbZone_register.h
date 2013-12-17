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
namespace App
{ 
    static void ICall_SoundReverbZone_Bind( MonoObject* self);

    static float ICall_SoundReverbZone_GetMinDistance( MonoObject* self);

    static void ICall_SoundReverbZone_SetMinDistance( MonoObject* self, float minDistance);

    static float ICall_SoundReverbZone_GetMaxDistance( MonoObject* self);

    static void ICall_SoundReverbZone_SetMaxDistance( MonoObject* self, float maxDistance);

    static int ICall_SoundReverbZone_GetReverbPreset( MonoObject* self);

    static void ICall_SoundReverbZone_SetReverbPreset( MonoObject* self, int preset);

    static int ICall_SoundReverbZone_GetRoom( MonoObject* self);

    static void ICall_SoundReverbZone_SetRoom( MonoObject* self, int room);

    static int ICall_SoundReverbZone_GetRoomHF( MonoObject* self);

    static void ICall_SoundReverbZone_SetRoomHF( MonoObject* self, int roomHF);

    static float ICall_SoundReverbZone_GetDecayTime( MonoObject* self);

    static void ICall_SoundReverbZone_SetDecayTime( MonoObject* self, float decayTime);

    static float ICall_SoundReverbZone_GetDecayHFRatio( MonoObject* self);

    static void ICall_SoundReverbZone_SetDecayHFRatio( MonoObject* self, float decayHFRatio);

    static float ICall_SoundReverbZone_GetReflectionsDelay( MonoObject* self);

    static void ICall_SoundReverbZone_SetReflectionsDelay( MonoObject* self, float reflectionsDelay);

    static int ICall_SoundReverbZone_GetReflections( MonoObject* self);

    static void ICall_SoundReverbZone_SetReflections( MonoObject* self, int reflections);

    static int ICall_SoundReverbZone_GetReverb( MonoObject* self);

    static void ICall_SoundReverbZone_SetReverb( MonoObject* self, int reverb);

    static float ICall_SoundReverbZone_GetReverbDelay( MonoObject* self);

    static void ICall_SoundReverbZone_SetReverbDelay( MonoObject* self, float reverbDelay);

    static float ICall_SoundReverbZone_GetHFReference( MonoObject* self);

    static void ICall_SoundReverbZone_SetHFReference( MonoObject* self, float hfReference);

    static float ICall_SoundReverbZone_GetDiffusion( MonoObject* self);

    static void ICall_SoundReverbZone_SetDiffusion( MonoObject* self, float diffusion);

    static float ICall_SoundReverbZone_GetDensity( MonoObject* self);

    static void ICall_SoundReverbZone_SetDensity( MonoObject* self, float density);

    static int ICall_SoundReverbZone_GetRoomLF( MonoObject* self);

    static void ICall_SoundReverbZone_SetRoomLF( MonoObject* self, int roomLF);

    static float ICall_SoundReverbZone_GetLFReference( MonoObject* self);

    static void ICall_SoundReverbZone_SetLFReference( MonoObject* self, float lfReference);

    static void ICall_SoundReverbZone_CopyValueFromPreset( MonoObject* self, int preset);

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_SoundReverbZone( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_Bind",                         (void*)&ICall_SoundReverbZone_Bind},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetMinDistance",               (void*)&ICall_SoundReverbZone_GetMinDistance},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetMinDistance",               (void*)&ICall_SoundReverbZone_SetMinDistance},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetMaxDistance",               (void*)&ICall_SoundReverbZone_GetMaxDistance},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetMaxDistance",               (void*)&ICall_SoundReverbZone_SetMaxDistance},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetReverbPreset",              (void*)&ICall_SoundReverbZone_GetReverbPreset},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetReverbPreset",              (void*)&ICall_SoundReverbZone_SetReverbPreset},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetRoom",                      (void*)&ICall_SoundReverbZone_GetRoom},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetRoom",                      (void*)&ICall_SoundReverbZone_SetRoom},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetRoomHF",                    (void*)&ICall_SoundReverbZone_GetRoomHF},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetRoomHF",                    (void*)&ICall_SoundReverbZone_SetRoomHF},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetDecayTime",                 (void*)&ICall_SoundReverbZone_GetDecayTime},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetDecayTime",                 (void*)&ICall_SoundReverbZone_SetDecayTime},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetDecayHFRatio",              (void*)&ICall_SoundReverbZone_GetDecayHFRatio},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetDecayHFRatio",              (void*)&ICall_SoundReverbZone_SetDecayHFRatio},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetReflectionsDelay",          (void*)&ICall_SoundReverbZone_GetReflectionsDelay},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetReflectionsDelay",          (void*)&ICall_SoundReverbZone_SetReflectionsDelay},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetReflections",               (void*)&ICall_SoundReverbZone_GetReflections},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetReflections",               (void*)&ICall_SoundReverbZone_SetReflections},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetReverb",                    (void*)&ICall_SoundReverbZone_GetReverb},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetReverb",                    (void*)&ICall_SoundReverbZone_SetReverb},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetReverbDelay",               (void*)&ICall_SoundReverbZone_GetReverbDelay},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetReverbDelay",               (void*)&ICall_SoundReverbZone_SetReverbDelay},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetHFReference",               (void*)&ICall_SoundReverbZone_GetHFReference},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetHFReference",               (void*)&ICall_SoundReverbZone_SetHFReference},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetDiffusion",                 (void*)&ICall_SoundReverbZone_GetDiffusion},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetDiffusion",                 (void*)&ICall_SoundReverbZone_SetDiffusion},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetDensity",                  (void*) &ICall_SoundReverbZone_GetDensity},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetDensity",                  (void*) &ICall_SoundReverbZone_SetDensity},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetRoomLF",                   (void*) &ICall_SoundReverbZone_GetRoomLF},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetRoomLF",                   (void*) &ICall_SoundReverbZone_SetRoomLF},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_GetLFReference",              (void*) &ICall_SoundReverbZone_GetLFReference},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_SetLFReference",              (void*) &ICall_SoundReverbZone_SetLFReference},
             { "ScriptRuntime.SoundReverbZone::ICall_SoundReverbZone_CopyValueFromPreset",         (void*) &ICall_SoundReverbZone_CopyValueFromPreset},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
