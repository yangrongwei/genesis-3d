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
#ifndef __SoundSourceComponentSerialization_H__
#define __SoundSourceComponentSerialization_H__

#include "stdneb.h"
#include "SoundSourceComponent.h"

namespace App
{

	class SoundSourceComponentSerialization
	{
	public:
		SoundSourceComponentSerialization(SoundSource* pComponent)
			: mObject(pComponent)
		{}

		~SoundSourceComponentSerialization() {}

		inline void Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args)
		{
			switch (ver)
			{
			case 1:
				{
					Load_1(pReader, args);
					break;
				}
			case 2:
				{
					Load_2(pReader, args);
					break;
				}
			case 3:
				{
					Load_3(pReader, args);
					break;
				}
			case 4:
				{
					Load_4(pReader, args);
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

		void Load_1(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_2(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_3(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_4(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Save(AppWriter* pWriter);

	protected:
		SoundSource* mObject;
	}; //class SoundSourceComponentSerialization



	/// 
	const char* s_SoundName = "SoundName";
	const char* s_Is3D = "Is3D";
	const char* s_Loop = "Loop";
	const char* s_AutoPlay = "AutoPlay";
	const char* s_Mute = "Mute";
	const char* s_Volume = "Volume";
	const char* s_Pitch = "Pitch";
	const char* s_PanLevel = "PanLevel";
	const char* s_Spread = "Spread";
	const char* s_Pan = "Pan";
	const char* s_MinDistance = "MinDistance";
	const char* s_MaxDistance = "MaxDistance";
	const char* s_RolloffMode = "RolloffMode";
	const char* s_Streamed	= "Streamed";
	const char* s_Compressed = "Compressed";
	const char* s_Decompress = "Decompress";
	const char* s_Statistics = "Statistics";

	//------------------------------------------------------------------------------
	void SoundSourceComponentSerialization::Load_1(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		n_assert(mObject);

		// name
		Util::String name;
		pReader->SerializeString(s_SoundName, name);
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();
		Resources::Priority priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::SkeletonDefault : cargs->getPriority();
		mObject->SetName(name, priority);

		// 3D
		bool is3D;
		pReader->SerializeBool(s_Is3D, is3D);
		mObject->Set3D(is3D);

		// loop
		bool loop;
		pReader->SerializeBool(s_Loop, loop);
		mObject->SetLoop(loop);

		// mute
		bool mute;
		pReader->SerializeBool(s_Mute, mute);
		mObject->SetMute(mute);

		// volume
		float volume;
		pReader->SerializeFloat(s_Volume, volume);
		mObject->SetVolume(volume);

		// pitch
		float pitch;
		pReader->SerializeFloat(s_Pitch, pitch);
		mObject->SetPitch(pitch);

		// PanLevel
		float panlevel;
		pReader->SerializeFloat(s_PanLevel, panlevel);

		// Spread
		float spread;
		pReader->SerializeFloat(s_Spread, spread);
		mObject->SetSpread(spread);

		// Pan
		float pan;
		pReader->SerializeFloat(s_Pan, pan);
		mObject->SetPan(pan);

		// MinDistance
		float minDistance;
		pReader->SerializeFloat(s_MinDistance, minDistance);
		mObject->SetMinDistance(minDistance);

		// MaxDistance
		float maxDistance;
		pReader->SerializeFloat(s_MaxDistance, maxDistance);
		mObject->SetMaxDistance(maxDistance);

		// RolloffMode
		int mode;
		pReader->SerializeInt(s_RolloffMode, mode);
		mObject->SetRolloffMode(static_cast<RolloffMode>(mode));

		mObject->SetDirty();

		return;
	}
	//------------------------------------------------------------------------------
	/**
	不同版本的scene加载函数,来处理加载不同的版本
	重用上一版scene加载的代码
	*/
	void SoundSourceComponentSerialization::Load_2( AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		Load_1(pReader, args);

		// Streamed
		bool streamed;
		pReader->SerializeBool(s_Streamed, streamed);
		mObject->SetSteamed(streamed);;

		// Decompress
		bool decompress;
		pReader->SerializeBool(s_Decompress, decompress);
		mObject->SetDecompress(decompress);

		// Compressed
		bool compressed;
		pReader->SerializeBool(s_Compressed, compressed);
		mObject->SetCompressed(compressed);

		// Statistics
		bool statistics;
		pReader->SerializeBool(s_Statistics, statistics);
		mObject->SetStatistics(statistics);

		mObject->SetDirty();

		return;
	}
	//------------------------------------------------------------------------------
	void SoundSourceComponentSerialization::Load_3( AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		Load_2(pReader, args);

		// AutoPlay
		bool autoPlay;
		pReader->SerializeBool(s_AutoPlay, autoPlay);
		mObject->SetPlayOnActive(autoPlay);

		mObject->SetDirty();	
	}
	//------------------------------------------------------------------------------
	void SoundSourceComponentSerialization::Load_4(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		n_assert(mObject);

		// name
		Util::String name;
		pReader->SerializeString(s_SoundName, name);
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();
		Resources::Priority priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::SkeletonDefault : cargs->getPriority();
		mObject->SetName(name, priority);

		// 3D
		bool is3D;
		pReader->SerializeBool(s_Is3D, is3D);
		mObject->Set3D(is3D);

		// loop
		bool loop;
		pReader->SerializeBool(s_Loop, loop);
		mObject->SetLoop(loop);

		// mute
		bool mute;
		pReader->SerializeBool(s_Mute, mute);
		mObject->SetMute(mute);

		// volume
		float volume;
		pReader->SerializeFloat(s_Volume, volume);
		mObject->SetVolume(volume);

		// pitch
		float pitch;
		pReader->SerializeFloat(s_Pitch, pitch);
		mObject->SetPitch(pitch);

		// Spread
		float spread;
		pReader->SerializeFloat(s_Spread, spread);
		mObject->SetSpread(spread);

		// Pan
		float pan;
		pReader->SerializeFloat(s_Pan, pan);
		mObject->SetPan(pan);

		// MinDistance
		float minDistance;
		pReader->SerializeFloat(s_MinDistance, minDistance);
		mObject->SetMinDistance(minDistance);

		// MaxDistance
		float maxDistance;
		pReader->SerializeFloat(s_MaxDistance, maxDistance);
		mObject->SetMaxDistance(maxDistance);

		// RolloffMode
		int mode;
		pReader->SerializeInt(s_RolloffMode, mode);
		mObject->SetRolloffMode(static_cast<RolloffMode>(mode));

		// Streamed
		bool streamed;
		pReader->SerializeBool(s_Streamed, streamed);
		mObject->SetSteamed(streamed);;

		// Decompress
		bool decompress;
		pReader->SerializeBool(s_Decompress, decompress);
		mObject->SetDecompress(decompress);

		// Compressed
		bool compressed;
		pReader->SerializeBool(s_Compressed, compressed);
		mObject->SetCompressed(compressed);

		// Statistics
		bool statistics;
		pReader->SerializeBool(s_Statistics, statistics);
		mObject->SetStatistics(statistics);

		// AutoPlay
		bool autoPlay;
		pReader->SerializeBool(s_AutoPlay, autoPlay);
		mObject->SetPlayOnActive(autoPlay);

		return;
	}
	//------------------------------------------------------------------------------
	void SoundSourceComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);

		// name
		Util::String name = mObject->GetName();
		pWriter->SerializeString(s_SoundName, name);

		// 3D
		bool is3D = mObject->Is3D();
		pWriter->SerializeBool(s_Is3D, is3D);

		// loop
		bool loop = mObject->GetLoop();
		pWriter->SerializeBool(s_Loop, loop);

		// mute
		bool mute = mObject->GetMute();
		pWriter->SerializeBool(s_Mute, mute);

		// volume
		float volume = mObject->GetVolume();
		pWriter->SerializeFloat(s_Volume, volume);

		// Pitch
		float pitch = mObject->GetPitch();
		pWriter->SerializeFloat(s_Pitch, pitch);

		// Spread
		float spread = mObject->GetSpread();
		pWriter->SerializeFloat(s_Spread, spread);

		// Pan
		float pan = mObject->GetPan();
		pWriter->SerializeFloat(s_Pan, pan);

		// MinDistance
		float minDistance = mObject->GetMinDistance();
		pWriter->SerializeFloat(s_MinDistance, minDistance);

		// MaxDistance
		float maxDistance = mObject->GetMaxDistance();
		pWriter->SerializeFloat(s_MaxDistance, maxDistance);

		// RolloffMode
		int mode = mObject->GetRolloffMode();
		pWriter->SerializeInt(s_RolloffMode, mode);

		// Streamed
		bool streamed = mObject->IsSteamed();
		pWriter->SerializeBool(s_Streamed, streamed);

		// Decompress
		bool decompress = mObject->IsDecompress();
		pWriter->SerializeBool(s_Decompress, decompress);

		// Compressed
		bool compressed = mObject->IsCompressed();
		pWriter->SerializeBool(s_Compressed, compressed);

		// Statistics
		bool statistics = mObject->IsStatistics();
		pWriter->SerializeBool(s_Statistics, statistics);

		// AutoPlay
		bool autoPlay = mObject->GetPlayOnActive();
		pWriter->SerializeBool(s_AutoPlay, autoPlay);

		return;
	}
	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SoundSource::GetVersion() const
	{
		return 4;	//	Current version number is 4.
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void SoundSource::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SoundSourceComponentSerialization serialize(this);
		serialize.Load(ver, pReader, args);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void SoundSource::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SoundSourceComponentSerialization serialize(const_cast<SoundSource*>(this));
		serialize.Save(pWriter);
	}

}

#endif //__SoundSourceComponentSerialization_H__ 
#endif //__SOUND_COMMIT__


