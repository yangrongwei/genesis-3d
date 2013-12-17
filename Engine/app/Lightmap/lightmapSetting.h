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
#pragma once

#ifndef __LIGHTMAPSETTING_H__
#define __LIGHTMAPSETTING_H__

#include "foundation/core/singleton.h"
#include "resource/resource.h"
#include "addons/resource/resourcemanager.h"
#include "appframework/serialization.h"

namespace App
{
	typedef Util::StringAtom LightmapName;
	typedef Util::Dictionary<LightmapName, GPtr<Resources::TextureResInfo> > LightMapInfos;
	typedef Util::Dictionary<int, LightmapName > LightmapIndexToName;

	class LightmapSetting
	{
	private:
		/// constructor
		LightmapSetting();
		/// destructor
		virtual ~LightmapSetting();
	public:
		/// get lightmapTexture handle
		RenderBase::TextureHandle GetLightmapTexHandle(int lightmapIndex);
		/// clearn up lightmap resource detail
		void ClearLightmapInfos();
		/// set lightmap
		void SetLightmap(int lightmapIndex,Util::String & lightmapName);
		/// get lightmap
		void GetLightmap( int lightmapIndex, LightmapName &LightmapName) const;
		/// update the exist all lightmaps

#ifdef __GENESIS_EDITOR__
		void UpdateLightmaps();
		/// update single lightmap
		void UpdateSingleLightmap(Resources::ResourceId);
#endif
		/// get instance
		static LightmapSetting& GetInstance()
		{
			static LightmapSetting lightmapSetting;
			return lightmapSetting;
		}

		/// get indexToName counts
		SizeT GetLightmapCounts() const
		{
			return indexToName.Size();
		}

		/// get indexToName map
		const LightmapIndexToName & GetINdexToNameMap() const
		{
			return indexToName;
		}

	private:
		LightMapInfos m_LightmapInfos;
		LightmapIndexToName indexToName;
		//int  m_LightmapTextureCount;
	};


	class LightmapFile: public Core::RefCounted, App::ISerialization
	{
		__DeclareClass(LightmapFile)
	public:
		LightmapFile(){ }

		virtual ~LightmapFile(){ }

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const ;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args ) ;

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const ;
	};
	
} // namespace InputFeature

#endif //__LIGHTMAPSETTING_H__