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
#ifndef __gameconfigmanger_H__
#define __gameconfigmanger_H__
#include "appframework/manager.h"
#include "appframework/serialization.h"
#include "core/singleton.h"



namespace App
{
	class GameConfigManager: public App::Manager, public App::ISerialization
	{
		__DeclareClass(GameConfigManager);
		__DeclareThreadSingleton(GameConfigManager);
	public:
		GameConfigManager();
		virtual ~GameConfigManager();

		// Game Name
		const Util::String& GetGameName(void) const;

		void SetGameName(const Util::String& name);

		// company name
		const Util::String& GetCompanyName(void) const;

		void SetCompanyName(const Util::String& name);

		// game UIID
		const Util::Guid& GetGameGUID(void) const;

		void SetGameGUID(const Util::Guid& guid);

		/**
		* AddGamePath  
		* @param: const String & assgine  
		* @param: const String & path  
		* @return: void  
		* @see: 
		* @remark:  like: AddGamePath("data", "export:data");
		            must add before active
		*/
		void AddGamePath(const Util::String& assgine, const Util::String& path);

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const ;

	protected:
		Util::String mGameName;
		Util::String mCompanyName;
		Util::Guid mGameGUID;

		struct AssginData
		{
			Util::String mAssginName;
			Util::String mPath;

		};

		// use array for assgin has fix order
		typedef Util::Array<AssginData> GameAssgins;
		GameAssgins mGameAssigns;

		friend class GameConfigSerialization;
	};
	//------------------------------------------------------------------------
	inline 
	const Util::String& 
	GameConfigManager::GetGameName(void) const
	{
		return mGameName;
	}
	//------------------------------------------------------------------------
	inline 
	void 
	GameConfigManager::SetGameName(const Util::String& name)
	{
		mGameName = name;
	}
	//------------------------------------------------------------------------
	inline 
	const Util::String& 
	GameConfigManager::GetCompanyName(void) const
	{
		return mCompanyName;
	}
	//------------------------------------------------------------------------
	inline 
	void 
	GameConfigManager::SetCompanyName(const Util::String& name)
	{
		mCompanyName = name;
	}
	//------------------------------------------------------------------------
	inline 
	const Util::Guid& 
	GameConfigManager::GetGameGUID(void) const
	{
		return mGameGUID;
	}
	//------------------------------------------------------------------------
	inline
	void 
	GameConfigManager::SetGameGUID(const Util::Guid& guid)
	{
		mGameGUID = guid;
	}
	//------------------------------------------------------------------------
	inline
	void 
	GameConfigManager::AddGamePath(const Util::String& assgine, const Util::String& path)
	{
		AssginData data;
		data.mAssginName = assgine;
		data.mPath = path;
		mGameAssigns.Append(data );
	}
}





#endif // __gameconfigmanger_H__
