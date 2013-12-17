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

#include "stdneb.h"
#include "Lightmap/lightmapSetting.h"
#include "serialization/serializeserver.h"
#include "appframework/serialization.h"

namespace App
{
	const char* s_IndexMapCounts = "IndexMapCounts";
	const char* s_LightmapIndex = "LightmapIndex";
	const char* s_LightmapName = "LightmapName";

	class LightMapSerialization
	{
	public:
		LightMapSerialization()
		{

		}
		inline void Load( LightmapSetting* obj, Version ver, AppReader* pReader)
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" LightMapSerialization::Load unknonw version " );
		}

		void Load_1( LightmapSetting* obj, AppReader* pReader )
		{
			SizeT count;
			int lightmapIndex;
			Util::String  lightmapName;

			pReader->SerializeInt(s_IndexMapCounts, count);

			for (IndexT objIdx = 0; objIdx < count; ++ objIdx)
			{
				pReader->SerializeInt(s_LightmapIndex, lightmapIndex);
				pReader->SerializeString(s_LightmapName, lightmapName);
				obj->SetLightmap(lightmapIndex, lightmapName);
			}
		}

		void Save( const LightmapSetting* obj , AppWriter* pWriter )
		{
			SizeT count = obj->GetLightmapCounts();

			pWriter->SerializeInt(s_IndexMapCounts, count);

			const LightmapIndexToName & indexmap = obj->GetINdexToNameMap();

			LightmapIndexToName::Iterator itBegin = indexmap.Begin();
			LightmapIndexToName::Iterator itEnd = indexmap.End();

			for (; itBegin != itEnd; ++itBegin)
			{
				int index = itBegin->Key();
				Resources::ResourceId currentResID = itBegin->Value();
				
				pWriter->SerializeInt(s_LightmapIndex, index);
				pWriter->SerializeString(s_LightmapName, currentResID.AsString());
				
			}
		}
	};

}

namespace App
{
	__ImplementClass(App::LightmapFile, 'LMIN', Core::RefCounted);

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version LightmapFile::GetVersion() const
	{
		return 1;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void LightmapFile::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		LightMapSerialization Serialize;
		LightmapSetting& lightmapSetting = LightmapSetting::GetInstance();
		Serialize.Load( &lightmapSetting, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void LightmapFile::Save( AppWriter* pWriter ) const
	{
		LightMapSerialization Serialize;
		LightmapSetting& lightmapSetting = LightmapSetting::GetInstance();
		Serialize.Save(&lightmapSetting,  pWriter );
	}
}