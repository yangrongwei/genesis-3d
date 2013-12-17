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
#include "memory/memory.h"
#include "foundation/io/memorystream.h"
#include "foundation/io/iointerfaceprotocol.h"
#include "foundation/io/ioserver.h"
#include "foundation/io/binaryreader.h"
#include "foundation/io/memorystream.h"
#include "foundation/io/iointerface.h"
#include "resource/resourceserver.h"
#include "graphicsystem/Material/GlobalShaderParam.h"
#include "materialmaker/GenesisMaterial.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "materialres.h"
#include "resourcemanager.h"
#include "graphicsystem/Material/materialinstance.h"

#include "spritepackageres.h"
#include "meshSpliter.h"

// make a FileServcie class, do not write code about FileService here!
const Util::String PreloadFileName = "Preload.ttt";

const Resources::ResourceId BaseResList( "project:" + PreloadFileName );




//------------------------------------------------------------------------------
const Util::String& GetFileServiceDirectory()
{
	static Util::String sFsDirectory;
	if ( sFsDirectory.IsEmpty() )
	{
		IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
		IO::URI tem = pAssignRegistry->ResolveAssigns("project:");//do not hard code assign here.
		sFsDirectory = tem.LocalPath();
	}

	return sFsDirectory;
}


namespace Resources
{
	//------------------------------------------------------------------------
	__ImplementClass( ResourceManager, 'AREM',Core::RefCounted);
	__ImplementImageSingleton( ResourceManager );


	//------------------------------------------------------------------------
	const GPtr<baseResInfo>&
		ResInfoContainer::CreateOrGetResInfo(const ResourceId& resId)
	{
		n_assert( m_resInfoType&&m_resDataType );
		// get exist
		for(IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			if (m_ResInfos[i]->GetResID() == resId)
			{
				return m_ResInfos[i];
			}
		}

		// new
		GPtr<Core::RefCounted> resInfoObj = m_resInfoType->Create();
		GPtr<baseResInfo> resInfo = resInfoObj.downcast<baseResInfo>();
		n_assert(resInfo);
		resInfo->SetContainer(this);
		resInfo->SetResID( resId );
		GPtr<Resource> pRes = ResourceServer::Instance()->CreateOrGetResource( resId, m_resDataType );
		resInfo->SetRes( pRes );

		m_ResInfos.Append(resInfo);
		return m_ResInfos.Back();
	}
	//------------------------------------------------------------------------
	bool ResInfoContainer::RemoveDefResInfoFromCurResInfo(const ResourceId& resId)
	{
		n_assert( m_resInfoType&&m_resDataType );

		IndexT foundIndex = -1;
		// get exist
		for(IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			if (m_ResInfos[i]->GetResID() == resId)
			{
				foundIndex =  i;
			}
		}

		if (foundIndex < 0)
		{
			return false;
		}

		if ( m_ResInfos[foundIndex]->IsDefaultResUsed() )
		{
			m_ResInfos[foundIndex]->SetDefaultResUsed(false);
			//ResourceServer::Instance()->UnLoadUnreferencedResources();
			GPtr<Resource> pRes = ResourceServer::Instance()->CreateOrGetResource( resId, m_resDataType );
			// 修改资源的状态为unload状态
			pRes->UnLoad();
			m_ResInfos[foundIndex]->ResetHandle();
			m_ResInfos[foundIndex]->SetRes( pRes );
		}

		return true;
	}

	//------------------------------------------------------------------------

	GPtr<baseResInfo> ResInfoContainer::GetResInfo(const ResourceId& resId)
	{
		// get exist
		for(IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			if (m_ResInfos[i]->GetResID() == resId)
			{
				return m_ResInfos[i];
			}
		}
		return NULL;
	}
	//------------------------------------------------------------------------
	void ResInfoContainer::DelResInfo(const ResourceId& resId)
	{
		GPtr<baseResInfo> pResInfo = GetResInfo(resId);
		if ( pResInfo.isvalid() )
		{
			IndexT idx = m_ResInfos.FindIndex(pResInfo);
			m_ResInfos.EraseIndex(idx);
		}

	}

	//------------------------------------------------------------------------
	void ResInfoContainer::UpdateResource(const ResourceId& resID, ResourceManager* mgr,bool isDeleted)
	{
		for (IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			const GPtr<baseResInfo> info =  m_ResInfos[i];
			/*if(IsResIdSame(info->GetResID().Value(), resID.Value()))*/
			if( info->GetResID() == resID  )
			{
				bool isCompile;

				if ( info->IsDefaultResUsed() )
				{
					// 把默认资源的信息从当前的ResInfo中去掉
					RemoveDefResInfoFromCurResInfo( resID );
					info->SetNeedReCompile(true);
				}
				else
				{
					//设置资源的状态为unload
					info->GetRes()->UnLoad();

					if ( info->GetRtti() ==  &MaterialResInfo::RTTI)
					{
						info->SetNeedReCompile(true);
					}

					isCompile = info->IsCompiled();
				}

				info->GetRes()->SetResourceId(resID);		//设置Res的ResourceID，可能是DefaultID，导致资源加载加载的Default资源;
				mgr->SynLoadSingleResData(info);
				break;
			}
		}
	}
	//------------------------------------------------------------------------
	void ResInfoContainer::SaveMaterial(const ResourceId& resID, ResourceManager* mgr)
	{
		mgr->SaveMaterial(resID);
	}

	//------------------------------------------------------------------------
	void ResInfoContainer::SaveMaterials(ResourceManager* mgr)
	{
		for (IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			GPtr<MaterialResInfo> matResInfo = m_ResInfos[i].downcast<MaterialResInfo>();
			if ( matResInfo->GetSave() )
			{
				if (matResInfo->GetImport() && IO::IoServer::Instance()->FileExists(matResInfo->GetMatID()))
				{
					n_warning("Importing material: %s already exist!skip!\n",matResInfo->GetMatID().Value());
					continue;
				}
				SaveMaterial(matResInfo->GetMatID(),mgr);
			}

		}
	}

	//------------------------------------------------------------------------
	void ResInfoContainer::Close()
	{
		for (IndexT i = 0; i < m_ResInfos.Size(); ++i)
		{
			m_ResInfos[i]->Discard();
		}

		m_ResInfos.Clear(true);
		if (m_DefaultResInfo.isvalid())
		{
			m_DefaultResInfo->Discard();
			m_DefaultResInfo = NULL;
		}

		m_resInfoType = NULL;
		m_resDataType = NULL;
	}
	//------------------------------------------------------------------------
	const GPtr<baseResInfo>& 
		ResInfoContainer::GetDefaultRes()
	{
		if ( m_DefaultResInfo )
		{
			return m_DefaultResInfo;
		}
		else
		{
			if ( !m_DefaultResID.IsValid() )
			{
				return m_DefaultResInfo;
			}

			GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
			n_assert( pStream );
			GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
			n_assert( readStreamMsg );
			readStreamMsg->SetFileName( m_DefaultResID );
			readStreamMsg->SetStream( pStream );
			IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

			if ( !readStreamMsg->GetResult() )
			{
				n_error( "\nCan't Find DefaultRes: %s!Please check your asset dir and make sure your file is correct.\n", m_DefaultResID.AsString().AsCharPtr() );
			}
			m_DefaultResInfo = ResourceManager::Instance()->_CreateResInfo(this,m_DefaultResID,0);
			return m_DefaultResInfo;
		}

	}

	//------------------------------------------------------------------------
	void 
		ResInfoContainer::SetDefaultResID(const Resources::ResourceId& defaultID)
	{
		m_DefaultResID = defaultID;
	}

	//------------------------------------------------------------------------
#if RENDERDEVICE_D3D9
	const Resources::ResourceId ResourceManager::DefaultTextureID("sys:MIssing_Texture.dds");
#elif RENDERDEVICE_OPENGLES
	const Resources::ResourceId ResourceManager::DefaultTextureID("sys:white.jpg");
#endif
	const Resources::ResourceId ResourceManager::DefaultMeshID("sys:MissingWarningBox.mesh");
	const Resources::ResourceId ResourceManager::DefalutShaderID("shd:Common_Diffuse.shader");
	const Resources::ResourceId ResourceManager::DefaultSoundID("sys:sound_miss.wav");
	const Resources::ResourceId ResourceManager::DefaultSkeletonID("sys:skeleton_miss.skel");
	const Resources::ResourceId ResourceManager::DefaultAnimationID("sys:anim_miss.anim");
	const Resources::ResourceId ResourceManager::DefaultMaterialID("sys:Missing_Material.material");
	const Resources::ResourceId ResourceManager::DefaultSpritePackageID("sys:SpritePackage_miss.spackage");
	//------------------------------------------------------------------------
	ResourceManager::ResourceManager()
	{
		__ConstructImageSingleton;

		m_PrimitiveResInfoContainer.SetDataType( &PrimitiveResInfo::RTTI, &MeshRes::RTTI );
		m_TextureResInfoContainer.SetDataType( &TextureResInfo::RTTI, &ImageRes::RTTI);
		m_RawResInfoContainer.SetDataType(&RawResInfo::RTTI,&RawRes::RTTI);
		m_TemplateResInfoContainer.SetDataType(&TemplateResInfo::RTTI,&TemplateRes::RTTI);
		m_AnimationResInfoContainer.SetDataType(&AnimationResInfo::RTTI,&AnimationRes::RTTI);
		m_SkeletonResInfoContainer.SetDataType(&SkeletonResInfo::RTTI,&SkeletonRes::RTTI);
		m_AudioResInfoContainer.SetDataType(&AudioResInfo::RTTI,&AudioRes::RTTI);
		m_PhysXMaterialResInfoContainer.SetDataType(&PhysXMaterialResInfo::RTTI, &PhysXMaterialRes::RTTI);
		m_MaterialResInfoContainer.SetDataType(&MaterialResInfo::RTTI, &MaterialRes::RTTI);

		m_SpritePackageResInfoContainer.SetDataType(&SpritePackageResInfo::RTTI, &SpritePackageRes::RTTI);

		// 设置读取失败后的，默认替代资源。应该放在System文件夹中
		m_PrimitiveResInfoContainer.SetDefaultResID( ResourceManager::DefaultMeshID );
		m_TextureResInfoContainer.SetDefaultResID( ResourceManager::DefaultTextureID );
		m_AudioResInfoContainer.SetDefaultResID(ResourceManager::DefaultSoundID);
		m_SkeletonResInfoContainer.SetDefaultResID(ResourceManager::DefaultSkeletonID);
		m_AnimationResInfoContainer.SetDefaultResID(ResourceManager::DefaultAnimationID);
		m_MaterialResInfoContainer.SetDefaultResID(ResourceManager::DefaultMaterialID);
		m_SpritePackageResInfoContainer.SetDefaultResID(ResourceManager::DefaultSpritePackageID);

		m_UsedForResourceHotLoader = false;

		if ( !mMeshSpliter.isvalid() )
		{
			mMeshSpliter = MeshSpliter::Create();
		}
	}
	//------------------------------------------------------------------------
	ResourceManager::~ResourceManager()
	{
		__DestructImageSingleton;
		mMeshSpliter = 0;
	}
	//------------------------------------------------------------------------

	GPtr<baseResInfo> ResourceManager::_CreateResInfo(ResInfoContainer* pManager, const ResourceId& resId, int p )
	{
		n_assert(pManager);

		Resources::Priority priority = Math::n_min(p, MAX_RES_LOAD_PRIORITY);

		GPtr<baseResInfo> resInfo = pManager->CreateOrGetResInfo(resId);
		n_assert(resInfo);

		resInfo->SetPriority(priority);

		if ( resInfo->CanUsable() )
		{
			return resInfo;
		}

		if ( priority > Resources::ResourcePriority::Synchronization )
		{
			// 异步加载
			_AddAsynRequestList(resInfo);
		}
		else
		{
			//同步加载
			if ( !_FlushSingleResInfo(resInfo) )	//	可能存在数据已经存在的情况
			{
				bool ret = SynLoadSingleResData(resInfo);
			}
		}

		return resInfo;

	}
	bool ResourceManager::SynLoadSingleResData(const GPtr<baseResInfo>& resInfo )
	{
		// 同步加载数据，结果是加载成功或加载失败
		_LoadSingleResData(resInfo, false);	
		return _FlushSingleResInfo(resInfo);
	}
	//------------------------------------------------------------------------
	void ResourceManager::_AddAsynRequestList(const GPtr<baseResInfo>& resInfo)
	{
		n_assert(resInfo);
		if ( resInfo->IsAsynLoading() )
		{
			return;
		}

		m_AsynRequsetList.push_back(resInfo);

		resInfo->SetAsynLoading(true);
	}

	//------------------------------------------------------------------------
	class PrioritySorter
	{
	public:
		bool operator() (const GPtr<baseResInfo>& lhs, const GPtr<baseResInfo>& rhs) const
		{
			return lhs->GetPriority() < rhs->GetPriority();
		}
	};

	void ResourceManager::_OnLoadingAsynList()
	{
		ResourceServer* resServer = ResourceServer::Instance();

		for (BaseResInfoList::iterator itorLoad = m_AsynLoadingList.begin();
			itorLoad != m_AsynLoadingList.end(); 
			)
		{
			GPtr<baseResInfo>& resInfo = *itorLoad;
			if ( _FlushSingleResInfo(resInfo) )
			{
				resInfo->SetAsynLoading(false);
				itorLoad = m_AsynLoadingList.erase(itorLoad);
			}
			else
			{
				++itorLoad;
			}
		}

		// 把Request List 按照优先级大小进行排序
		m_AsynRequsetList.sort( PrioritySorter() );

		const int MaxLoadingCount = 5;
		int loadingCount = 0;
		for ( BaseResInfoList::iterator itorReq = m_AsynRequsetList.begin();
			itorReq != m_AsynRequsetList.end();++loadingCount )
		{
			if(loadingCount > MaxLoadingCount)
				break;

			GPtr<baseResInfo>& resInfo = *itorReq;
			if ( _FlushSingleResInfo(resInfo) )
			{
				resInfo->SetAsynLoading(false);
				itorReq = m_AsynRequsetList.erase(itorReq);
			}
			else
			{
				// 发出调度申请，移到Loading列表
				_LoadSingleResData(resInfo,true);
				m_AsynLoadingList.push_back( *itorReq );
				itorReq = m_AsynRequsetList.erase(itorReq);
			}
		}
	}
	//------------------------------------------------------------------------
	bool ResourceManager::_LoadSingleResData(const GPtr<baseResInfo>& resInfo, bool asyn)
	{
		n_assert(resInfo && resInfo->GetRes() );

		ResourceServer* resServer = ResourceServer::Instance();
		GPtr<Resource> pRes = resInfo->GetRes();
		return resServer->LoadResource( pRes, asyn );
	}
	//------------------------------------------------------------------------

	bool ResourceManager::_FlushSingleResInfo(const GPtr<baseResInfo>& resInfo)
	{
		n_assert(resInfo);
		ResInfoContainer* mgr = resInfo->GetContainer();
		n_assert(mgr);

		if ( resInfo->CanUsable() )
		{
			return true;
		}
		else if ( resInfo->GetRes()->GetState() == Resource::Loaded )
		{
			if ( !resInfo->Compile() )
			{
				resInfo->AssignDefaultResCompile( mgr->GetDefaultRes() );
			}
			return true;
		}
		else if ( resInfo->GetRes()->GetState() == Resource::Failed )
		{
			//默认资源不应该设置为Unload，这样会导致同一份资源再次加载
			/*const GPtr<baseResInfo>& defaultInfo = mgr->GetDefaultRes();
			if ( defaultInfo.isvalid() && defaultInfo->GetRes().isvalid() )
			{			
			const GPtr<Resources::Resource>& defaultRes = defaultInfo->GetRes();
			defaultRes->SetState(Resource::UnLoaded);//UnLoad会卸载默认资源必须设置成UnLoad，下次用到的时候重新加载。;

			}*/

			resInfo->AssignDefaultResData(mgr->GetDefaultRes());
			resInfo->AssignDefaultResCompile( mgr->GetDefaultRes() );
			return true;
		}

		return false;
	}
	//------------------------------------------------------------------------
	GPtr<PrimitiveResInfo> ResourceManager::CreatePrimitiveInfo(const ResourceId& resId, Resources::Priority priority)
	{
		return _CreateResInfo(&m_PrimitiveResInfoContainer, resId, priority).downcast<PrimitiveResInfo>();
	}
	//------------------------------------------------------------------------
	GPtr<TextureResInfo> ResourceManager::CreateTextureInfo(const ResourceId& resId, Resources::Priority priority)
	{
		return _CreateResInfo(&m_TextureResInfoContainer, resId, priority).downcast<TextureResInfo>();
	}

	//------------------------------------------------------------------------
	GPtr<RawResInfo> ResourceManager::CreateRawResInfo(const ResourceId& resId, Resources::Priority priority)
	{
		return _CreateResInfo(&m_RawResInfoContainer, resId, priority).downcast<RawResInfo>();
	}
	//--------------------------------------------------------------------------------
	GPtr<TemplateResInfo> ResourceManager::CreateTemplateResInfo(const ResourceId& resId)//, Resources::Priority priority)
	{
		return _CreateResInfo(&m_TemplateResInfoContainer, resId, Resources::ResourcePriority::Synchronization).downcast<TemplateResInfo>();
	}
	//--------------------------------------------------------------------------------
	GPtr<SpritePackageResInfo> ResourceManager::CreateSpritePackageResInfo(const ResourceId& resId)//, Resources::Priority priority)
	{
		return _CreateResInfo(&m_SpritePackageResInfoContainer, resId, Resources::ResourcePriority::Synchronization).downcast<SpritePackageResInfo>();
	}

	//--------------------------------------------------------------------------------
	GPtr<AnimationResInfo> ResourceManager::CreateAnimationResInfo(const ResourceId& resId, Resources::Priority priority )
	{
		return _CreateResInfo(&m_AnimationResInfoContainer, resId, priority).downcast<AnimationResInfo>();
	}
	//--------------------------------------------------------------------------------
	GPtr<AudioResInfo> ResourceManager::CreateAudioResInfo(const ResourceId& resId, Resources::Priority priority )
	{
		return _CreateResInfo(&m_AudioResInfoContainer, resId, priority).downcast<AudioResInfo>();
	}
	//--------------------------------------------------------------------------------
	GPtr<SkeletonResInfo> ResourceManager::CreateSkeletonResInfo(const ResourceId& resId, Resources::Priority priority )
	{
		return _CreateResInfo(&m_SkeletonResInfoContainer, resId, priority).downcast<SkeletonResInfo>();
	}
	//--------------------------------------------------------------------------------
	GPtr<PhysXMaterialResInfo> ResourceManager::CreatePhysXMaterialResInfo(const ResourceId& resId, Resources::Priority priority)
	{
		return _CreateResInfo(&m_PhysXMaterialResInfoContainer, resId, priority).downcast<PhysXMaterialResInfo>();
	}


	GPtr<MaterialResInfo> ResourceManager::CreateMaterialInfo(const ResourceId& resId,bool bSave /*= false*/)
	{// 该接口是读取shader文件生成的材质 resID 是shaderID（材质参数都是默认的） 以后要废掉
		GPtr<Graphic::MaterialInstanceManager>& matinsMng = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		GPtr<Graphic::MaterialInstance> pMatIns = matinsMng->CreateMaterialInstance(resId);
		if ( !pMatIns.isvalid() )
		{
			return GPtr<MaterialResInfo>(NULL);
		}
		n_assert(pMatIns.isvalid());

		GPtr<MaterialResInfo> matResInfo = _BindMaterialInstaneToResinfo(pMatIns);
		n_assert(matResInfo);

		_SetMaterialDefaultAttr(matResInfo);	
		matResInfo->SetSave(bSave);



		return matResInfo;
	}
	//------------------------------------------------------------------------
	GPtr<MaterialResInfo> 
		ResourceManager::CreateMaterialInfoByMatID(const ResourceId& resId,const bool bCopy /*= false*/ )
	{// 读material文件 resID是材质id
		//有材质实例，则引用，否则创建个再引用它

		// material 是同步加载
		Resources::Priority priority = 0; 
		GPtr<MaterialResInfo> matResInfo;

		if ( !bCopy )
		{

			matResInfo = _CreateResInfo(&m_MaterialResInfoContainer, resId, priority).downcast<MaterialResInfo>();
			if (matResInfo.isvalid() && Util::String(resId.Value()).FindStringIndex("asset:") != 0)
			{
				matResInfo->SetSave(false);
			}
			return matResInfo;
		}
		else
		{
			GPtr<Graphic::MaterialInstanceManager>& matInstMgr = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
			if ( !matInstMgr->HaveMaterialInstance(resId) )
			{//没有该材质先创建
				matResInfo = _CreateResInfo(&m_MaterialResInfoContainer, resId, priority).downcast<MaterialResInfo>();
				if (matResInfo.isvalid() && Util::String(resId.Value()).FindStringIndex("asset:") != 0)
				{
					matResInfo->SetSave(false);
				}
				n_assert(matResInfo->GetHandle().isvalid());
			}


			GPtr<Graphic::MaterialInstance> pMatIns = matInstMgr->NewMaterialInstanceCopyByMatID(resId);

			// 把拷贝出来的材质放入ResInfoContainer(包括，创建materialRes MaterialResInfo)
			GPtr<MaterialResInfo> matResInfo = _BindMaterialInstaneToResinfo(pMatIns);
			//matResInfo->SetSave(false);
			return matResInfo;

		}


	}
	//------------------------------------------------------------------------

	GPtr<MaterialResInfo> ResourceManager::_BindMaterialInstaneToResinfo(GPtr<Graphic::MaterialInstance>& mat)
	{
		ResourceId newMatID = mat->GetMaterialID();
		GPtr<baseResInfo> resInfo = m_MaterialResInfoContainer.CreateOrGetResInfo(newMatID);
		n_assert(resInfo);

		resInfo->SetPriority(0);
		n_assert( resInfo->GetRes().isvalid() );
		resInfo->GetRes()->SetState(Resource::Loaded);
		//n_assert( resInfo->CanUsable() );

		// 手动绑定关系
		GPtr<MaterialRes> pMatRes = resInfo->GetRes().downcast<MaterialRes>();
		pMatRes->SetMaterialInstance(mat);		

		GPtr<MaterialResInfo> tmpMatResInfo = resInfo.downcast<MaterialResInfo>();		
		tmpMatResInfo->SetHandle(mat);	
		return tmpMatResInfo;

	}
	//------------------------------------------------------------------------
	GPtr<MaterialResInfo> 
		ResourceManager::ModifyMaterialInfo(const ResourceId& matID,const ResourceId& newShaderID)
	{
		GPtr<MaterialResInfo> sri = MaterialResInfo::Create();
		sri->priority = 0;	
		sri->SetMatID(matID);

		//资源的修改
		_ModifyMaterial(sri,newShaderID);
		return sri;
	}
	//------------------------------------------------------------------------
	void ResourceManager::_ModifyMaterial(GPtr<MaterialResInfo>& sri,const ResourceId& newShaderID)
	{
		ResourceId resID = sri->GetMatID();

		//修改材质管理器中的材质
		GPtr<Graphic::MaterialInstanceManager>& matinsMng = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		GPtr<Graphic::MaterialInstance> pMatIns = matinsMng->ModifyMaterialInstance(sri->GetMatID(),newShaderID);
		sri->SetHandle( pMatIns );	
		if ( !sri->GetHandle().isvalid() )
		{
			n_warning("Invalid material ID. Use Default Material's copy");
			sri->SetHandle( matinsMng->CreateMaterialInstance(DefalutShaderID) );
			sri->SetMatID( sri->GetHandle()->GetMaterialID() );
		}
		n_assert( sri->GetHandle().isvalid() );


		if ( !sri->GetHandle()->GetRenderState().isvalid() )
		{
			GPtr<RenderBase::RenderStateDesc> pState = RenderBase::RenderStateDesc::Create();
			pState->Setup();
			RenderBase::DeviceSamplerState samplerState;
			samplerState.m_textureIndexEnable[0] = true;
			samplerState.m_Filter[0] = RenderBase::eTFLINEAR;
			samplerState.m_maxAnisotropy[0] = 16;
			pState->SetSamplerState(samplerState);
			pState->SetUpdateFlag(RenderBase::RenderStateDesc::eAllRenderState);
			RenderBase::DeviceRasterizerState rasterState;
			rasterState.m_fillMode = RenderBase::eFMSOLID;
			//FIXME: soldier model is imported as left handed axis!so use CULLFRONT
			rasterState.m_cullMode = RenderBase::eCMFRONT;
			pState->SetRasterizerState(rasterState);
			RenderBase::DeviceDepthAndStencilState dsState;
			dsState.m_depthEnable = true;
			pState->SetDepthAndStencilState(dsState);

			sri->GetHandle()->SetRenderState(pState);
		}

		sri->GetHandle()->_SetBuildState(true);

	}
	//------------------------------------------------------------------------
	void 
		ResourceManager::RemoveMaterialInstanceByMatID( const Resources::ResourceId& matID )
	{
		GPtr<Graphic::MaterialInstanceManager>& matinsMng = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		matinsMng->RemoveMaterialInstance(matID);

		m_MaterialResInfoContainer.DelResInfo(matID);
	}
	//------------------------------------------------------------------------
	void ResourceManager::SaveMaterial(const ResourceId& resID)
	{
		const GPtr<baseResInfo> resInfo = m_MaterialResInfoContainer.CreateOrGetResInfo(resID);
		n_assert(resInfo.isvalid());
		GPtr<MaterialResInfo> matResInfo = resInfo.downcast<MaterialResInfo>();

		const GPtr<baseResInfo>& baseResInfo = matResInfo->GetContainer()->GetDefaultRes();
		ResourceId defaultResID = baseResInfo->GetResID();
		ResourceId resourceID = matResInfo->GetRes()->GetResourceId();

		if ( defaultResID == resourceID )
		{
			return;
		}

		if ( matResInfo->GetSave() && matResInfo->GetRes()->GetState() == Resource::Loaded)
		{
			IO::URI urlMat(matResInfo->GetMatID().AsString());
#ifdef __GENESIS_EDITOR__
			Util::String filePath = urlMat.GetOriginalPath();
			Util::String dirPath = filePath.ExtractDirName();
			if (!IO::IoServer::Instance()->DirectoryExists(dirPath))
				IO::IoServer::Instance()->CreateDirectory(dirPath);
#endif
			bool bRet = ResourceServer::Instance()->SaveResource(resInfo->GetRes(),urlMat);
			n_assert(bRet);
		}

	}
	//------------------------------------------------------------------------
	void ResourceManager::ModifyMaterialInstanceID(const ResourceId& matID,const ResourceId& newMatID,bool import)
	{
		GPtr<baseResInfo> existResInfo = m_MaterialResInfoContainer.GetResInfo(matID);

		// 检测是否存在，如果存在，则需要copy
		GPtr<baseResInfo> newResInfo = m_MaterialResInfoContainer.GetResInfo(newMatID);

		if ( newResInfo.isvalid() )
		{
			//需要从新的材质里面copy信息
			newResInfo->CopyFrom(existResInfo);
			m_MaterialResInfoContainer.DelResInfo(matID);
		}

		n_assert(existResInfo.isvalid());
		GPtr<MaterialResInfo> matResInfo = existResInfo.downcast<MaterialResInfo>();

		// resinfo
		matResInfo->SetResID(newMatID);
		matResInfo->SetImport(import);
		// resource
		GPtr<Resource> res = matResInfo->GetRes();
		n_assert(res.isvalid());
		res->SetResourceId(newMatID);

		//matInstance
		GPtr<MaterialRes> matRes = res.downcast<MaterialRes>();
		GPtr<Graphic::MaterialInstance> matIns = matRes->GetMaterialInstance();
		n_assert(matIns);
		matIns->SetMaterialID(newMatID);

	}
	//------------------------------------------------------------------------
	void ResourceManager::SaveMaterials()
	{
		m_MaterialResInfoContainer.SaveMaterials(this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::OnLoadingShader()
	{
		const ResInfoArray& resInfo = m_MaterialResInfoContainer.GetAllResInfo();
		for (SizeT i = 0; i < resInfo.Size(); ++i)
		{
			const GPtr<MaterialResInfo>& matResInfo = resInfo[i].downcast<MaterialResInfo>();
			n_assert(matResInfo->GetHandle());
			_RefreshMaterial(matResInfo->GetHandle());		
		}
	}
	//------------------------------------------------------------------------
	void ResourceManager::ReloadAllVideoMemResource()
	{
		const ResInfoArray& meshResInfos = m_PrimitiveResInfoContainer.GetAllResInfo();

		for (IndexT i = 0; i < meshResInfos.Size(); ++i)
		{
			const ResourceId& id = meshResInfos[i]->GetResID();

			UpdateMeshResource(id);
		}

		const ResInfoArray& texResInfos = m_TextureResInfoContainer.GetAllResInfo();

		for (IndexT i = 0; i < texResInfos.Size(); ++i)
		{
			const ResourceId& id = texResInfos[i]->GetResID();

			UpdateTexResource(id);
		}
	}
	//------------------------------------------------------------------------------
	void ResourceManager::UpdateMeshResource(const ResourceId& resID,bool isDeleted)
	{
		m_PrimitiveResInfoContainer.UpdateResource(resID,this,isDeleted);
	}
	//------------------------------------------------------------------------------
	void ResourceManager::UpdateTexResource(const ResourceId& resID)
	{
		m_TextureResInfoContainer.UpdateResource(resID,this);
	}
	//--------------------------------------------------------------------------------
	void ResourceManager::UpdateAnimationResource(const ResourceId& resID)
	{
		m_AnimationResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------

	void ResourceManager::_SetMaterialDefaultAttr(GPtr<MaterialResInfo>& sri)
	{	
		if ( !sri->GetHandle().isvalid() )
		{
			n_warning("Invalid shader ID. Use Default Material");

			GPtr<Graphic::MaterialInstanceManager>& matinsMng = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
			GPtr<Graphic::MaterialInstance> matIns = matinsMng->CreateMaterialInstance(DefalutShaderID);		
			sri->SetHandle( matIns );
		}
		n_assert( sri->GetHandle().isvalid() );

		ResourceId matID = sri->GetHandle()->GetMaterialID();
		sri->SetResID(matID);

		if ( !sri->GetHandle()->GetRenderState().isvalid() )
		{
			GPtr<RenderBase::RenderStateDesc> pState = RenderBase::RenderStateDesc::Create();
			pState->Setup();
			RenderBase::DeviceSamplerState samplerState;
			samplerState.m_textureIndexEnable[0] = true;
			samplerState.m_Filter[0] = RenderBase::eTFLINEAR;
			samplerState.m_maxAnisotropy[0] = 16;
			pState->SetSamplerState(samplerState);
			pState->SetUpdateFlag(RenderBase::RenderStateDesc::eAllRenderState);
			RenderBase::DeviceRasterizerState rasterState;
			rasterState.m_fillMode = RenderBase::eFMSOLID;
			//FIXME: soldier model is imported as left handed axis!so use CULLFRONT
			rasterState.m_cullMode = RenderBase::eCMFRONT;
			pState->SetRasterizerState(rasterState);
			RenderBase::DeviceDepthAndStencilState dsState;
			dsState.m_depthEnable = true;
			pState->SetDepthAndStencilState(dsState);

			sri->GetHandle()->SetRenderState(pState);
		}

		sri->GetHandle()->_SetBuildState(true);
	}
	//------------------------------------------------------------------------
	void ResourceManager::_LoadingMaterial(GPtr<MaterialResInfo>& sri,const bool bCopy /*= false*/ )
	{


	}

	void ResourceManager::_RefreshMaterial(GPtr<Graphic::MaterialInstance>& mat)
	{
		if ( mat->IsDirty() )
		{
			bool bAllTextureLoaded = true;

			if (mat->UpateState())
			{
				mat->AssignTextures();
			}
		}
	}

	//--------------------------------------------------------------------------------
	void ResourceManager::UpdateAudioResource(const ResourceId& resID)
	{
		m_AudioResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::UpdateSkeletonResource(const ResourceId& resID)
	{
		m_SkeletonResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::UpdatePhysXMaterialResource( const ResourceId& resID )
	{
		m_PhysXMaterialResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::UpdateMaterialResource(const ResourceId& resID)
	{
		m_MaterialResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::UpdateTemplateResource(const ResourceId& resID)
	{
		m_TemplateResInfoContainer.UpdateResource(resID,this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::UpdateSpritePackage( const ResourceId& resID )
	{
		m_SpritePackageResInfoContainer.UpdateResource(resID, this);
	}
	//------------------------------------------------------------------------
	void ResourceManager::BeginUsedForResHotLoad()
	{
		m_UsedForResourceHotLoader = true;
	}
	//------------------------------------------------------------------------
	void ResourceManager::EndUsedForResHotLoad()
	{
		m_UsedForResourceHotLoader = false;
	}
	//------------------------------------------------------------------------
	void ResourceManager::OnBeginFrame()
	{
		MeshSpliter::Instance()->Init();
		_OnLoadingAsynList();

		OnLoadingShader();
	}
	//------------------------------------------------------------------------
	void ResourceManager::Close()
	{
		m_PrimitiveResInfoContainer.Close();
		m_TextureResInfoContainer.Close();
		m_RawResInfoContainer.Close();
		m_TemplateResInfoContainer.Close();
		m_AnimationResInfoContainer.Close();
		m_SkeletonResInfoContainer.Close();
		m_AudioResInfoContainer.Close();
		m_PhysXMaterialResInfoContainer.Close();
		m_MaterialResInfoContainer.Close();

	}

	//------------------------------------------------------------------------
	bool ResourceManager::UpdateShaderUsedMaterial(const ResourceId& shaderID)
	{
		// reload shader
		GPtr<Graphic::MaterialInstanceManager>& matinsMng = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		GPtr<Graphic::MaterialInstance> newMat = matinsMng->UpdateShader(shaderID);
		if ( !newMat.isvalid() )
		{
			return false;
		}

		// find all effected material and update
		const ResInfoArray& allMatInfo = m_MaterialResInfoContainer.GetAllResInfo();
		for ( IndexT idx = 0; idx < allMatInfo.Size(); idx++ )
		{
			GPtr<MaterialResInfo> matResInfo = allMatInfo[idx].downcast<MaterialResInfo>();
			GPtr<Graphic::MaterialInstance> curMatIns = matResInfo->GetHandle();
			if ( curMatIns->GetShaderID() == shaderID )
			{
				// 不拷贝系统默认的丢失材质的参数列表
				// 保证新材质不为fallback,是为了保证fallback的参数不被覆盖掉,材质可变为fallback默认的参数
				// 保证当前材质不为fallback,是为了保证新材质的默认参数不被fallback材质覆盖掉,材质可变为新材质的默认参数
				if (curMatIns->GetName() != "defaultFallBackShader" && newMat->GetName() != "defaultFallBackShader" )
					newMat->CopyParamList(curMatIns);

				curMatIns->CopyFrom(newMat);
			}
		}	
		return true;

	}

	ResInfoContainer& ResourceManager::GetMaterialResInfoContainer()
	{
		return m_MaterialResInfoContainer;
	}

	Util::String ResourceManager::GetInitParamValue(const Resources::ResourceId& matID,int paramIndex)
	{
		return App::GraphicObjectManager::Instance()->GetMaterialInstanceManager()->GetInitParamValue(matID,paramIndex);
	}

}
