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
#include "basegamefeature/managers/gameconfigmanger.h"


namespace App
{
	class GameConfigSerialization
	{
	public:
		GameConfigSerialization(const GameConfigManager* pMgr)
			:mObject(pMgr)
		{

		}


		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			n_error(" GameConfigSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Save( AppWriter* pWriter );
	protected:
		const GameConfigManager* mObject;
		
	};
	const static char* s_GameName = "GameName";
	const static char* s_CompanyName = "CompanyName";
	const static char* s_GameGUID = "GameGUID";
	const static char* s_AssginCount = "AssginCount";
	const static char* s_AssginName= "AssginName";
	const static char* s_PathName= "pathName";


	//------------------------------------------------------------------------
	void GameConfigSerialization::Load_1( AppReader* pSerialize )
	{
		GameConfigManager* pManager = const_cast<GameConfigManager*>(mObject);
		
		pSerialize->SerializeString( s_GameName, pManager->mGameName );
		pSerialize->SerializeString( s_CompanyName, pManager->mCompanyName );
		Util::String tmpStr = pManager->mGameGUID.AsString();
		pSerialize->SerializeString( s_GameGUID, tmpStr );

		// assgin data
		{
			SizeT count;
			pSerialize->SerializeInt( s_AssginCount, count );

			if ( count != 0 )
			{
				GameConfigManager::GameAssgins& assgins = pManager->mGameAssigns;
				assgins.Reserve(count);

				for ( IndexT index = 0; index < count; ++index )
				{
					GameConfigManager::AssginData data;
					pSerialize->SerializeString( s_AssginName, data.mAssginName );
					pSerialize->SerializeString( s_PathName, data.mPath );
					assgins.Append( data );
				}
			}
		}
	}
	//------------------------------------------------------------------------
	void GameConfigSerialization::Save( AppWriter* pSerialize )
	{
		const GameConfigManager* pManager = mObject;

		pSerialize->SerializeString( s_GameName, pManager->mGameName );
		pSerialize->SerializeString( s_CompanyName, pManager->mCompanyName );
		pSerialize->SerializeString( s_GameGUID, pManager->mGameGUID.AsString() );

		// assgin data
		{
			const GameConfigManager::GameAssgins& assgins = pManager->mGameAssigns;
			SizeT count = assgins.Size();
			pSerialize->SerializeInt( s_AssginCount, count );
			for ( IndexT index = 0; index < count; ++index )
			{
				const GameConfigManager::AssginData& data = assgins[index];
				pSerialize->SerializeString( s_AssginName, data.mAssginName );
				pSerialize->SerializeString( s_PathName, data.mPath );
			}
		}
	}


}


namespace App
{
	__ImplementClass(App::GameConfigManager, 'GGCM', App::Manager);

	__ImplementThreadSingleton(App::GameConfigManager);

	//------------------------------------------------------------------------
	GameConfigManager::GameConfigManager()
	{
		__ConstructThreadSingleton;
	}
	//------------------------------------------------------------------------
	GameConfigManager::~GameConfigManager()
	{
		__DestructThreadSingleton;
	}
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version 
	GameConfigManager::GetVersion() const
	{
		return 1;
	}
	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void GameConfigManager::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args ) 
	{
		GameConfigSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	// @ISerialization::Save
	void GameConfigManager::Save( AppWriter* pWriter ) const
	{
		GameConfigSerialization Serialize(this);
		Serialize.Save( pWriter );
	}
}



