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
#include "serialization/serializeserver.h"
#include "vegetation/VegetationServer.h"
#include "vegetation/VegetationObejct.h"
#include "vegetation/InstanceMap.h"
#include "vegetation/GrassInstanceMap.h"
#include "vegetation/TreeInstanceMap.h"
#include "vegetation/MeshInstanceMap.h"
#include "addons/resource/templateressaver.h"

namespace Vegetation
{
	__ImplementClass(Vegetation::VegetationServer, 'VSEV', Core::RefCounted);
	__ImplementClass(Vegetation::VegetationInstanceContainer, 'VVIC', Core::RefCounted);
	__ImplementImageSingleton(VegetationServer);

	const SizeT Vegetation_Job_Count = 4;
	const Util::String StrEmpty("");

	//------------------------------------------------------------------------
	VegetationServer::VegetationServer()
	{
		__ConstructImageSingleton;
		mTemplates = VegetationInstanceContainer::Create();

		//mJobs.Reserve( Vegetation_Job_Count );
		//for ( IndexT i = 0; i < Vegetation_Job_Count; ++i)
		//{
		//	mJobs.Append( ParticleJob::Create() );
		//}

		//_RegisterDynamicClass
		{
			VegetationObject::RegisterWithFactory();
			VegeInstanceMap::RegisterWithFactory();
			//VegetationBrush::RegisterWithFactory();

			GrassInstanceMap::RegisterWithFactory();
			TreeInstanceMap::RegisterWithFactory();
			MeshInstanceMap::RegisterWithFactory();
		}
	}
	//------------------------------------------------------------------------
	VegetationServer::~VegetationServer()
	{
		__DestructImageSingleton;
		mActives.Clear();
		mTemplates = NULL; 
	}
	//------------------------------------------------------------------------
	void VegetationServer::_attachVegetationInstMap( const VegeInstanceMapPtr& pInstmap )
	{
		if ( pInstmap.isvalid() && !pInstmap->IsActive() )
		{
			mActives.Append( pInstmap );
			pInstmap->_onActivate();
		}
	}
	//-----------------------------------------------------------------------
	void VegetationServer::_deattachVegetationInstMap( const VegeInstanceMapPtr& pInstmap )
	{
		if ( pInstmap.isvalid() && pInstmap->IsActive() )
		{
			IndexT findIndex = mActives.FindIndex( pInstmap );
			n_assert( findIndex != InvalidIndex );

			pInstmap->_onDeactivate();

			if ( findIndex != InvalidIndex )
			{
				mActives.EraseIndex( findIndex );
			}
		}
	}
	//------------------------------------------------------------------------
	bool VegetationServer::OpenTemplateFile( Util::String filePath )
	{
		GPtr<Resources::TemplateResInfo> templateResInfo = Resources::ResourceManager::Instance()->CreateTemplateResInfo(filePath);

		if (templateResInfo.isvalid())
		{
			const GPtr<Resources::Resource>& resource = templateResInfo->GetRes();
			if ( !resource.isvalid() || resource->GetState() != Resources::Resource::Loaded)
			{
				return false;
			}

			const GPtr<Resources::TemplateRes>& res = resource.downcast<Resources::TemplateRes>();

			GPtr<Resources::TemplateResSaver> tplresSaver = Resources::TemplateResSaver::Create();
			if(tplresSaver->SaveResource(res))
			{			
				Serialization::SerializationServer* serialize = Serialization::SerializationServer::Instance();

				if (serialize)
				{
					GPtr<Serialization::SerializeReader> pReader = serialize->OpenReadFile( tplresSaver->GetStream() );
					if ( pReader )
					{
						const GPtr<VegeInstanceMap>& instmap = pReader->SerializeObject<VegeInstanceMap>();
						serialize->CloseReadFile(pReader);

						if ( instmap.isvalid() )
						{
							RemoveTemplate( filePath );
							AddTemplate( filePath, instmap);					
							return true;
						}
					}
				}
			}
		}

		return false;
	}
	//------------------------------------------------------------------------
	void VegetationServer::SaveTemplateFile(  Util::String filePath  )
	{		
		Serialization::SerializationServer* pSerialzeMgr = Serialization::SerializationServer::Instance();
		if( !pSerialzeMgr )
		{
			return;
		}

		GPtr<Serialization::SerializeWriter> pWriter = pSerialzeMgr->OpenWriteFile( filePath );
		if ( pWriter )
		{
			IndexT idx = mTemplates->mContainer.FindIndex(filePath);
			if ( idx != InvalidIndex )
			{
				const GPtr<VegeInstanceMap>& instmap = mTemplates->mContainer.ValueAtIndex(idx);
				pWriter->SerializeObject( instmap );
			}

			pSerialzeMgr->CloseWriteFile( pWriter );
		}

	}
	//------------------------------------------------------------------------
	VegeInstanceMapPtr VegetationServer::CreateFromTemplate(const Util::StringAtom& tplname)
	{
		if ( !tplname.IsValid() )
		{
			return VegeInstanceMapPtr(NULL);
		}

		const VegeInstanceMapPtr& source = FindTemplate( tplname );
		if ( source.isvalid() )
		{
			VegeInstanceMapPtr dest = Clone( source );
			return dest;
		}
		else
		{
			return VegeInstanceMapPtr(NULL);
		}
	}

	//------------------------------------------------------------------------
	bool VegetationServer::AddTemplate(const Util::StringAtom& tplname, const VegeInstanceMapPtr& instmap )
	{
		if ( !instmap.isvalid() || !tplname.IsValid() )
		{
			return false;
		}

		VegeInstanceMapPtr tpl = Clone( instmap );

		IndexT findIndex =  mTemplates->mContainer.FindIndex( tplname );
		if ( findIndex != InvalidIndex )
		{
			mTemplates->mContainer.ValueAtIndex(findIndex) = tpl;
		}
		else
		{
			mTemplates->mContainer.Add(tplname, tpl);
		}
		return true;
	}
	//------------------------------------------------------------------------
	void VegetationServer::RemoveTemplate( const Util::StringAtom& tplName )
	{
		IndexT findIndex = mTemplates->mContainer.FindIndex( tplName );
		if ( findIndex != InvalidIndex )
		{
			mTemplates->mContainer.EraseAtIndex( findIndex );
		}
	}
	//------------------------------------------------------------------------
	void VegetationServer::Update()
	{
		if ( mActives.IsEmpty() )
		{
			return;
		}

		bool useMutilThread = false;

		if ( !useMutilThread )
		{
			SizeT count = mActives.Size();
			for ( IndexT i = 0; i < count; ++i)
			{
				mActives[i]->Update();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void VegetationServer::ClearActives()
	{
		if ( mActives.IsEmpty() )
		{
			return;
		}
		SizeT count = mActives.Size();
		for ( IndexT i = 0; i < count; ++i)
		{
			mActives[i]= NULL;
		}
		mActives.Clear();
	}
}
