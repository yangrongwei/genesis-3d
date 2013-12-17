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
#include "appframework/actor.h"
#include "appframework/actormanager.h"
#include "util/guid.h"
namespace App
{
	class ActorSerialization
	{
	public:
		ActorSerialization( const Actor* pActor )
			:mObject(pActor)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(pReader);
				return;
			}
			else if ( 3 == ver )
			{
				Load_3(pReader);
				return;
			}
			else if ( 4 == ver )
			{
				Load_4(pReader);
				return;
			}
			else if( 5 == ver )
			{
				Load_5(pReader);
				return;
			}
			else if ( 6 == ver )
			{
				Load_6(pReader);
				return;
			}
			else if ( 7 == ver )
			{
				Load_7(pReader);
				return;
			}
			n_error(" SceneSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Load_3( AppReader* pReader );
		void Load_4( AppReader* pReader );
		void Load_5( AppReader* pReader );
		void Load_6( AppReader* pReader);
		void Load_7( AppReader* pReader);
		void Save( AppWriter* pWriter );
	protected:
		const Actor* mObject;
	};

	const char* s_ActorTemplateName = "ActorTemplateName";
	const char* s_ActorName = "ActorName";
	const char* s_ActorTemplateLink = "ActorTemplateLink";
	const char* s_ActorLayerID = "ActorLayerID";
	const char* s_ActorTagID = "ActorTagID";
	const char* s_ActorPosition = "ActorPosition";
	const char* s_ActorRotation = "ActorRotation";
	const char* s_ActorScale = "ActorScale";
	const char* s_ActorComponentCount = "ActorComponentCount";
	const char* s_ActorChildActorCount = "ActorChildActorCount";
	const char* s_ActorActive = "ActorActive";
	const char* s_ActorInheritRotation = "ActorInheritRotation";
	const char* s_ActorInheritScale = "ActorInheritScale";
	const char* s_ActorGUID = "ActorGUID";
	const char* s_ActorResourcePriority = "ActorResourcePriority";
	const char* s_ActorEditorStaticFlag = "ActorEditorStaticFlag";
	const char* s_ActorVisable = "ActorVisable";
	//------------------------------------------------------------------------
	void ActorSerialization::Load_1(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		////bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>();
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}
		}
		else
		{
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active();
		//}
	}
	//------------------------------------------------------------------------
	void ActorSerialization::Load_2(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		////bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );

			bool temp = true;
			pSerialize->SerializeBool( s_ActorInheritRotation, temp/*pActor->mInheritRotation*/ );
			pSerialize->SerializeBool( s_ActorInheritScale, temp/*pActor->mInheritScale */);

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>();
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}

			// Serialize child
			{
				SizeT count;
				ActorSerializationArgs args(pActor);
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);
				}
			}
		}
		else
		{
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active();
		//}
	}

	//------------------------------------------------------------------------
	void ActorSerialization::Load_3(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );
		ActorManager* pActMgr = ActorManager::Instance();
		////bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );

			bool temp = true;
			pSerialize->SerializeBool( s_ActorInheritRotation, temp/*pActor->mInheritRotation*/ );
			pSerialize->SerializeBool( s_ActorInheritScale, temp/*pActor->mInheritScale*/ );

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
			Util::String guidStr;
			pSerialize->SerializeString( s_ActorGUID, guidStr);
			pActor->mGuid = Util::Guid::FromString(guidStr);
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>();
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}

			// Serialize child
			{
				SizeT count;
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				ActorSerializationArgs args(pActor);
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);
				}
			}
		}
		else
		{
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active();//pActMgr->_AddActiveActor(pActor);
		//}
	}
	//------------------------------------------------------------------------
	void ActorSerialization::Load_4(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		//bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
			Util::String guidStr;
			pSerialize->SerializeString( s_ActorGUID, guidStr);
			pActor->mGuid = Util::Guid::FromString(guidStr);
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				ComponentSerializationArgs args(pActor->GetPriority());
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>(&args);
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}

			// Serialize child
			{
				SizeT count;
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				ActorSerializationArgs args(pActor);
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);
				}
			}
		}
		else
		{
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active(false);
		//}
	}
	//------------------------------------------------------------------------
	void ActorSerialization::Load_5(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		//bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
			Util::String guidStr;
			pSerialize->SerializeString( s_ActorGUID, guidStr);
			pActor->mGuid = Util::Guid::FromString(guidStr);

			Resources::Priority actorResourcePriority;
			pSerialize->SerializeInt( s_ActorResourcePriority, actorResourcePriority);
			pActor->SetPriority(actorResourcePriority);
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				ComponentSerializationArgs args(pActor->GetPriority());
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>(&args);
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}

			// Serialize child
			{
				SizeT count;
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				ActorSerializationArgs args(pActor);
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);

				}
			}
		}
		else
		{
			/*程序流程走到这里代表actor是由模板创建的，并且没有做过任何修改，如果模板缓冲中有的话
			可以直接从模板缓冲中复制，不用走序列化流程，这样可以加快加载时间。但要注意actor的位置
			等私有属性应该保留*/
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active(false);
		//}
	}
  //------------------------------------------------------------------------
	void ActorSerialization::Load_6(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		//bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString( s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString( s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );
			pSerialize->SerializeUInt(    s_ActorEditorStaticFlag, pActor->mEditorFlag);

			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
			Util::String guidStr;
			pSerialize->SerializeString( s_ActorGUID, guidStr);
			pActor->mGuid = Util::Guid::FromString(guidStr);

			Resources::Priority actorResourcePriority;
			pSerialize->SerializeInt( s_ActorResourcePriority, actorResourcePriority);
			pActor->SetPriority(actorResourcePriority);
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				ComponentSerializationArgs args(pActor->GetPriority());
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>(&args);
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
			}

			// Serialize child
			{
				SizeT count;
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				ActorSerializationArgs args(pActor);
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);
				}
			}
		}
		else
		{
			/*程序流程走到这里代表actor是由模板创建的，并且没有做过任何修改，如果模板缓冲中有的话
			可以直接从模板缓冲中复制，不用走序列化流程，这样可以加快加载时间。但要注意actor的位置
			等私有属性应该保留*/
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active(false);
		//}
	}
	//------------------------------------------------------------------------
	void ActorSerialization::Load_7(AppReader* pSerialize)
	{
		Actor* pActor = const_cast<Actor*>( mObject );

		bool visible;
		//bool isActive = false;
		//private data
		{
			Util::String templataName; 
			pSerialize->SerializeString(  s_ActorTemplateName,   templataName );
			pActor->SetTemplateName( templataName );
			pSerialize->SerializeString(  s_ActorName,   pActor->mName );
			pSerialize->SerializeBool(    s_ActorTemplateLink,   pActor->mIsLinkTemplate);
			pSerialize->SerializeUInt(    s_ActorLayerID,     pActor->mLayerID );
			pSerialize->SerializeUInt(    s_ActorTagID,     pActor->mTagID );
			pSerialize->SerializeUInt(    s_ActorEditorStaticFlag, pActor->mEditorFlag);

			pSerialize->SerializeBool(	  s_ActorVisable,visible	);
			
			Math::float4 pos;
			pSerialize->SerializeFloat4(  s_ActorPosition, pos);
			Math::float4 rot;
			pSerialize->SerializeFloat4(  s_ActorRotation, rot);
			Math::float4 scale;
			pSerialize->SerializeFloat4(  s_ActorScale, scale);

			// use function to dirty flag
			pActor->SetTransform(pos, Math::quaternion(rot), scale );

			pSerialize->SerializeBool( s_ActorActive, pActor->mActiveControl );
			Util::String guidStr;
			pSerialize->SerializeString( s_ActorGUID, guidStr);
			pActor->mGuid = Util::Guid::FromString(guidStr);

			Resources::Priority actorResourcePriority;
			pSerialize->SerializeInt( s_ActorResourcePriority, actorResourcePriority);
			pActor->SetPriority(actorResourcePriority);
		}

		// child component
		if ( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				ComponentSerializationArgs args(pActor->GetPriority());
				SizeT count;
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					GPtr<Component> pComponent = pSerialize->SerializeObject<Component>(&args);
					if (pComponent.isvalid())
					{
						pActor->AttachComponent( pComponent );
					}
				}
#ifdef __GENESIS_EDITOR__
				pActor->SetVisible(visible, false);
#endif

			}

			// Serialize child
			{
				SizeT count;
				pSerialize->SerializeInt(s_ActorChildActorCount, count );
				ActorSerializationArgs args(pActor);
				for ( IndexT index = 0; index < count; ++index )
				{
					pSerialize->SerializeObject<Actor>(&args);
				}
			}
		}
		else
		{
			/*程序流程走到这里代表actor是由模板创建的，并且没有做过任何修改，如果模板缓冲中有的话
			可以直接从模板缓冲中复制，不用走序列化流程，这样可以加快加载时间。但要注意actor的位置
			等私有属性应该保留*/
			ActorManager* pActMgr = ActorManager::Instance();
			// the actor template is all unlink. so actMgr mush active now
			n_assert( pActMgr && pActMgr->IsActive() );	
			GPtr<Actor> pTemp(pActor);
			bool bOK = pActMgr->CopyFromTemplate( pActor->GetTemplateName().AsString(), pTemp, false );
			if ( !bOK )
			{
				n_warning( "ActorSerialization: Copy form template %s Failed.\n", pActor->GetTemplateName().AsString().AsCharPtr() );
			}
		}

		//if ( isActive )
		//{
		//	pActor->Active(false);
		//}
	}
	//------------------------------------------------------------------------
	void ActorSerialization::Save(AppWriter* pSerialize)
	{
		const Actor* pActor = mObject;

		//private data
		{
			pSerialize->SerializeString( s_ActorTemplateName,   pActor->GetTemplateName().AsString() );
			pSerialize->SerializeString( s_ActorName, pActor->GetName() );
			pSerialize->SerializeBool(   s_ActorTemplateLink,   pActor->IsLinkTemplate() );
			pSerialize->SerializeInt(    s_ActorLayerID,     pActor->GetLayerID() );
			pSerialize->SerializeInt(    s_ActorTagID,     pActor->GetTagID() );
			pSerialize->SerializeInt(    s_ActorEditorStaticFlag,  pActor->GetEditorFlag() );
			pSerialize->SerializeBool(	 s_ActorVisable, pActor->GetVisible() );

			pSerialize->SerializeFloat4(  s_ActorPosition, pActor->mLocalPosition);
			Math::quaternion qRot = pActor->GetRotation();
			Math::float4 fRot = Math::float4(qRot.x(),qRot.y(),qRot.z(),qRot.w());
			pSerialize->SerializeFloat4(  s_ActorRotation, fRot);
			pSerialize->SerializeFloat4(  s_ActorScale, pActor->mLocalScale);
			pSerialize->SerializeBool( s_ActorActive, pActor->GetActiveControl() );
			pSerialize->SerializeString(s_ActorGUID, pActor->mGuid.AsString());
			pSerialize->SerializeInt( s_ActorResourcePriority, pActor->GetPriority());
		}


		// child component
		if( !pActor->IsLinkTemplate() )
		{
			// Serialize component
			{
				const Util::Array<GPtr<Component> >& Components = pActor->mComponents;
				SizeT count = Components.Size();
				pSerialize->SerializeInt( s_ActorComponentCount, count );
				for ( IndexT index = 0; index < count; ++index )
				{
					const GPtr<Component>& pComponent = Components[index];
					pSerialize->SerializeObject(pComponent);
				}
			}

			// Serialize child
			{
				SizeT count = pActor->GetChildCount();
				pSerialize->SerializeInt( s_ActorChildActorCount, count );
				for ( IndexT index = 0; index < count; ++index)
				{
					const GPtr<Actor>& pChildActor = pActor->GetChild( index );
					n_assert( pChildActor );
					pSerialize->SerializeObject(pChildActor);
				}
			}
		}
		else
		{
			// do nothing. we can deSerialization from actor template
		}
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version Actor::GetVersion() const
	{
		return 7; //当前版本号为7
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void Actor::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		n_assert(!mActivated);
		n_assert(!mActiveControl);
		n_assert(NULL == mParent);
		if (args)
		{
			const ActorSerializationArgs* aargs = args->cast_fast<ActorSerializationArgs>();
			if (aargs->parent)
			{
				GPtr<Actor> tmpActor = GPtr<Actor>(this);
				aargs->parent->mChildren.Append(tmpActor);
				mParent = aargs->parent;
			}
		}
		ActorSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void Actor::Save( AppWriter* pWriter ) const
	{
		ActorSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

}


