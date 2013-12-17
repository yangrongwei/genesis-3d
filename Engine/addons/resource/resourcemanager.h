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

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "foundation/core/singleton.h"
#include "meshres.h"
#include "imageres.h"
#include "resource.h"
#include "rawres.h"
#include "templateres.h"
#include "animationres.h"
#include "audiores.h"
#include "skeletonres.h"
#include "physxmaterialres.h"
#include "resource/resinfo.h"

#include "foundation/util/stl.h"

namespace Resources
{
	class ResourceManager;
	typedef Util::Array< GPtr<baseResInfo> > ResInfoArray;
	// 内部抽象使用
	class ResInfoContainer
	{

	public:
		ResInfoContainer();

		const GPtr<baseResInfo>& CreateOrGetResInfo(const ResourceId& resId);

		// Remove the default resource from current resource info
		bool RemoveDefResInfoFromCurResInfo(const ResourceId& resId);

		void UpdateResource(const ResourceId& resID, ResourceManager* mgr,bool isDeleted = false);
		void SaveMaterial(const ResourceId& resID, ResourceManager* mgr);
		void SaveMaterials(ResourceManager* mgr);

		void Close();

		void SetDefaultRes( const GPtr<baseResInfo>& defaultRes ){
			m_DefaultResInfo = defaultRes;
		}

		const GPtr<baseResInfo>& GetDefaultRes();
		const ResInfoArray& GetAllResInfo() const
		{
			return m_ResInfos;
		}

		void SetDataType(Core::Rtti* resInfoType,  Core::Rtti* resDataType)
		{
			m_resInfoType = resInfoType;
			m_resDataType = resDataType;
			n_assert(m_resInfoType && m_resDataType);
		}

		void SetDefaultResID(const Resources::ResourceId& defaultID);

		GPtr<baseResInfo> GetResInfo(const ResourceId& resId);

		void DelResInfo(const ResourceId& resId);

	protected:
		ResInfoArray m_ResInfos;
		GPtr<baseResInfo> m_DefaultResInfo;	//	默认的资源信息，一般出错时使用
		Resources::ResourceId m_DefaultResID;	
		Core::Rtti* m_resInfoType;
		Core::Rtti* m_resDataType;
	private:
		void operator = (const ResInfoContainer&);
		ResInfoContainer(const ResInfoContainer&);
	};
	class MeshSpliter;
	class ResourceManager : public Core::RefCounted
	{
		__DeclareClass(ResourceManager);
		__DeclareImageSingleton(ResourceManager);
	public:
		ResourceManager();
		virtual ~ResourceManager();

		GPtr<PrimitiveResInfo> CreatePrimitiveInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<TextureResInfo> CreateTextureInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<RawResInfo> CreateRawResInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<TemplateResInfo> CreateTemplateResInfo(const ResourceId& resId);
		GPtr<SpritePackageResInfo> CreateSpritePackageResInfo(const ResourceId& resId);

		GPtr<AnimationResInfo> CreateAnimationResInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<AudioResInfo> CreateAudioResInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<SkeletonResInfo> CreateSkeletonResInfo(const ResourceId& resId, Resources::Priority priority);
		GPtr<PhysXMaterialResInfo> CreatePhysXMaterialResInfo(const ResourceId& resId, Resources::Priority priority);

		GPtr<MaterialResInfo> CreateMaterialInfo(const ResourceId& resId,bool bSave = false);
		GPtr<MaterialResInfo> CreateMaterialInfoByMatID(const ResourceId& resId,const bool bCopy = false );
		GPtr<MaterialResInfo> ModifyMaterialInfo(const ResourceId& matID,const ResourceId& newShaderID);

		void RemoveMaterialInstanceByMatID( const ResourceId& matID );
		void SaveMaterial(const ResourceId& resID);

		void SaveMaterials();
		void ModifyMaterialInstanceID(const ResourceId& matID,const ResourceId& newMatID,bool import = false);

		ResInfoContainer& GetMaterialResInfoContainer();

		void OnBeginFrame();

		void Close();

		Util::String							GetInitParamValue(const Resources::ResourceId& matID,int paramIndex);
	public:
		void UpdateMeshResource(const ResourceId& resID,bool isDeleted = false);
		void UpdateTexResource(const ResourceId& resID);
		void UpdateAnimationResource(const ResourceId& resID);
		void UpdateSkeletonResource(const ResourceId& resID);
		void UpdateAudioResource(const ResourceId& resID);
		void UpdatePhysXMaterialResource(const ResourceId& resID);
		void UpdateMaterialResource(const ResourceId& resID);
		bool UpdateShaderUsedMaterial(const ResourceId& shaderID);
		void UpdateTemplateResource(const ResourceId& resID);
		void UpdateSpritePackage(const ResourceId& resID);

		void BeginUsedForResHotLoad();
		void EndUsedForResHotLoad();

		void ReloadAllVideoMemResource();

		const ResInfoContainer& GetSpritePackageResInfoContainer();

		static const Resources::ResourceId DefalutShaderID;
		static const Resources::ResourceId DefaultTextureID;
		static const Resources::ResourceId DefaultMeshID;
		static const Resources::ResourceId DefaultSoundID;
		static const Resources::ResourceId DefaultSkeletonID;
		static const Resources::ResourceId DefaultAnimationID;
		static const Resources::ResourceId DefaultTemplateID;
		static const Resources::ResourceId DefaultMaterialID;
		static const Resources::ResourceId DefaultSpritePackageID;

	public:
		bool SynLoadSingleResData(const GPtr<baseResInfo>& resInfo );

	public:
		// 创建资源信息的通用函数，内部使用
		GPtr<baseResInfo> _CreateResInfo(ResInfoContainer* container, const ResourceId& resId, int p);

	protected:

		// 将需要异步加载的资源加入到申请列表中
		void _AddAsynRequestList(const GPtr<baseResInfo>& resInfo);

		// 每帧调用，已经加载的资源进行编译等。 申请列表中的资源排序后，依次向后台线程发出加载申请
		void _OnLoadingAsynList();

		// 加载一个单独的资源数据，同步或者异步
		bool _LoadSingleResData(const GPtr<baseResInfo>& resInfo, bool asyn);

		// true: 当资源数据加载成功，进行编译。 加载失败或编译失败，使用默认资源进行替换。 
		// true: 资源还没有加载
		bool _FlushSingleResInfo(const GPtr<baseResInfo>& resInfo);

		bool _UpdateResInfoContainer(ResInfoContainer* container);



	private:

		void OnLoadingShader();
		void _SetMaterialDefaultAttr(GPtr<MaterialResInfo>& sri);	
		void _LoadingMaterial(GPtr<MaterialResInfo>& sri,const bool bCopy = false );
		void _ModifyMaterial(GPtr<MaterialResInfo>& sri,const ResourceId& newShaderID);
		void _DownloadingMaterial(const ResourceId& matID);
		void _RefreshMaterial(GPtr<Graphic::MaterialInstance>& mat);

		GPtr<MaterialResInfo> _BindMaterialInstaneToResinfo(GPtr<Graphic::MaterialInstance>& mat);
	private:

		typedef ResInfoContainer PrimitiveResInfoContainer;
		typedef ResInfoContainer TextureResInfoContainer;
		typedef ResInfoContainer RawResInfoContainer;
		typedef ResInfoContainer TemplateResInfoContainer;
		typedef ResInfoContainer AnimationResInfoContainer;
		typedef ResInfoContainer AudioResInfoContainer;
		typedef ResInfoContainer SkeletonResInfoContainer;
		typedef ResInfoContainer PhysXMaterialResInfoContainer;
		typedef ResInfoContainer MaterialResInfoContainer;
		typedef ResInfoContainer SpritePackageResInfoContainer;

		PrimitiveResInfoContainer		m_PrimitiveResInfoContainer;
		TextureResInfoContainer			m_TextureResInfoContainer;
		RawResInfoContainer				m_RawResInfoContainer;
		TemplateResInfoContainer		m_TemplateResInfoContainer;
		AnimationResInfoContainer		m_AnimationResInfoContainer;
		SkeletonResInfoContainer		m_SkeletonResInfoContainer;
		AudioResInfoContainer			m_AudioResInfoContainer;
		PhysXMaterialResInfoContainer	m_PhysXMaterialResInfoContainer;
		MaterialResInfoContainer		m_MaterialResInfoContainer;
		SpritePackageResInfoContainer	m_SpritePackageResInfoContainer;

		typedef Util::STL_list< GPtr<baseResInfo> >::type BaseResInfoList;
		BaseResInfoList m_AsynRequsetList;
		BaseResInfoList m_AsynLoadingList;	//	待加载的资源列表

		bool m_UsedForResourceHotLoader;
		GPtr<MeshSpliter> mMeshSpliter;
	};

	inline const ResInfoContainer& ResourceManager::GetSpritePackageResInfoContainer()
	{
		return m_SpritePackageResInfoContainer;
	}

}

#endif //RESOURCEMANAGER_H_
