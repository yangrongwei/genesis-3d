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
#include "appframework/actormanager.h"


namespace App
{
	class ActorManagerSerialization
	{
	public:
		ActorManagerSerialization( const ActorManager* pManager )
			:mObject(pManager)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			n_error(" ActorManagerSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Save( AppWriter* pWriter );
	protected:
		const ActorManager* mObject;
	};

	const static char* s_TemplateActorCount = "TemplateActorCount";

	//------------------------------------------------------------------------
	void ActorManagerSerialization::Load_1(AppReader* pSerialize)
	{
		ActorManager* pManager = const_cast<ActorManager*>(mObject);

		/// 读取actor的模板
		{
			SizeT tempSize;
			pSerialize->SerializeInt( s_TemplateActorCount, tempSize );
			
			if ( tempSize != 0 )
			{
				// do not use " ActorManager::ActorTemplateContainer& actorTemplates=pManager->mTemplateActors "
				// for did not init actor_template from actor_template
				ActorManager::ActorTemplateContainer actorTemplates;
				Serialization::FileType fileType = Serialization::FT_DEFAULT;

				actorTemplates.Reserve( tempSize );
				actorTemplates.BeginBulkAdd();
				for ( IndexT index = 0; index < tempSize; ++index )
				{
					GPtr<Actor> pActor = pSerialize->SerializeObject<Actor>();
					n_assert( pActor );
					actorTemplates.Add( pActor->GetTemplateName().AsString(), ActorManager::TemplateInfo(pActor,fileType ));
				}
				actorTemplates.EndBulkAdd();

				pManager->mTemplateActors = actorTemplates;
			}
		}

	}
	//------------------------------------------------------------------------
	void ActorManagerSerialization::Save(AppWriter* pSerialize)
	{
		const ActorManager* pManager = mObject;

		/// 存储actor的模板
		{
			const ActorManager::ActorTemplateContainer& actorTemplates = pManager->mTemplateActors;
			SizeT tempSize = actorTemplates.Size();
			pSerialize->SerializeInt( s_TemplateActorCount, tempSize );
			for ( IndexT index = 0; index < tempSize; ++index )
			{
				const GPtr<Actor>& pActor = actorTemplates.ValueAtIndex( index ).m_ptr;
				pSerialize->SerializeObject( pActor );
			}
		}
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version ActorTemplateFile::GetVersion() const
	{
		return 1;	//	当前版本号是1
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ActorTemplateFile::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{

		ActorManagerSerialization Serialize( ActorManager::Instance() );
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ActorTemplateFile::Save( AppWriter* pWriter ) const
	{
		ActorManagerSerialization Serialize( ActorManager::Instance() );
		Serialize.Save( pWriter );
	}

}

