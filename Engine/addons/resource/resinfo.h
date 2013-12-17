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
#ifndef __resinfo_H__
#define __resinfo_H__

#include "resource.h"
#include "graphicsystem/Material/materialinstance.h"
#include "graphicsystem/GraphicObjectManager.h"

namespace Sprite
{
	class SpritePackage;
}

namespace Resources
{
	const int MAX_RES_LOAD_PRIORITY = 65535;
	const int DEFAULT_RES_LOAD_PRIORITY = 65535;
	//--------------------------------------------------------------------------------
	/** 
	资源有三种表现形态： 
	1、在外部存储设备上的表现形态，可能是一个文件，文件的一部分，或者数据库中的一条记录。简称为文件形态
	2、在内存中的资源数据的表现形态，从Resources::Resource的派生类。简称为对象形态
	3、在某个功能模块的上下文环境中的表现形态，比如渲染系统中的一个句柄。 简称为上下文形态
	4、一般来说，一个文件形态对应一个对象形态
	5、对某些资源类型，对象形态和上下文形态是一样的。也就不存在上下文形态
	6、对某些资源类型，对象形态可能对应多种上下文形态，比如MeshRes可用于渲染，也可用于物理

	baseResInfo主要管理上下文形态和它对应的资源形态。当上下文形态不同时，应该存在不同的baseResInfo
	三种对象形态的状态变化
	1、当从文件形态成功加载到对象形态时，该资源信息是已经加载了(Loaded)
	2、当从对象形态成功编译到上下文形态后，该资源信息是已经编译了(Compiled)
	3、当资源信息已经加载并且成功编译后， 该资源信息是可用的(CanUsable)
	4、从性能等角度考虑，不同的资源可能有区别，状态判断函数均实现为虚函数，可派生修改。因此这些状态暂只作为内部使用，不作为外部判断有效性的依据

	*/

	class ResInfoContainer;

	class baseResInfo : public Core::RefCounted
	{
		__DeclareClass(baseResInfo);
	public:
		baseResInfo() : 
		  priority(DEFAULT_RES_LOAD_PRIORITY),
			  isAsynLoading(false),
			  container(0),
			  defaultResUsed(false),
			  needReCompile(false)
		  {};
		  virtual ~baseResInfo()
		  {};

		  // 资源ID
		  const Resources::ResourceId& GetResID() const {
			  return resID;
		  }
		  void SetResID(const Resources::ResourceId& id){
			  resID = id;
		  }

		  // 资源加载的优先级。 >0 表示延迟加载。数字越大，加载优先级越低
		  Priority GetPriority(void) const { 
			  return priority;
		  }
		  void SetPriority(Priority p ){
			  priority = p;
		  }

		  // 资源数据对象
		  const GPtr<Resources::Resource>& GetRes() const{
			  return resData;
		  }

		  void SetRes(const GPtr<Resources::Resource>& res){
			  resData = res;
		  }

		  void SetContainer(ResInfoContainer* m)
		  {
			  container = m;
		  }
		  ResInfoContainer* GetContainer()
		  {
			  return container;
		  }

		  // 上下文形态是否存在。默认情况下，对象形态和上下文形态一致。派生类根据需要改写
		  virtual bool IsCompiled() const
		  {
			  return IsLoaded()&&!needReCompile;
		  }

		  // 内部使用的接口

		  // 资源信息是否准备完毕，可以被业务逻辑使用了。
		  // 不同的类型资源的状态判断不同。派生类应该根据需要重写改函数
		  virtual bool CanUsable() const
		  {
			  return IsLoaded() && IsCompiled();
		  }

		  // 对象形态是否存在并加载
		  virtual bool IsLoaded() const
		  {

			  return resData && resData->GetState() == Resources::Resource::Loaded;

		  }



		  // 编译上下文形态
		  bool Compile();

		  // 需要的派生类重载该函数，完成上下文形态的编译和赋值
		  virtual void OnCompile(){ }

		  // 放弃，变为初始状态
		  virtual void Discard(){
			  resData = 0;
			  resID.Clear();
			  isAsynLoading = false;
			  priority = DEFAULT_RES_LOAD_PRIORITY;
		  }

		  // 设置默认的资源数据
		  virtual void AssignDefaultResData(const GPtr<baseResInfo>& defaultRes)
		  {
			  if ( defaultRes )
			  {
				  ResourceId tempResID;
				  Priority   tempPriority;
				  bool tempAsynLoading;

				  tempResID = resID;
				  tempPriority = priority;
				  tempAsynLoading = isAsynLoading;

				  Discard();
				  //ResetHandle();


				  resID = tempResID;
				  priority = tempPriority;
				  isAsynLoading = tempAsynLoading;
				  resData = defaultRes->resData;
				  defaultResUsed = true;
			  }
		  }

		  // 主要是为了支持fbx导入加入了这个方法
		  // 用于其他情况下请注意，可能会出现bug
		  // 这个copy需要res的信息是完整的，而且copy完了需要删除之前的res，否则就会出问题
		  // 
		  virtual void CopyFrom(const GPtr<baseResInfo>& res)
		  {
			  if ( res )
			  {
				  ResourceId tempResID;
				  Priority   tempPriority;
				  bool tempAsynLoading;

				  tempResID = resID;
				  tempPriority = priority;
				  tempAsynLoading = isAsynLoading;

				  Discard();

				  resID = tempResID;
				  priority = tempPriority;
				  isAsynLoading = tempAsynLoading;
				  resData = res->resData;

				  AssignDefaultResCompile( res );

				  defaultResUsed = false;
			  }
		  }

		  // 设置默认的上下文形态
		  virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes)
		  {
			  return;
		  }

		  // 是否正在异步加载
		  bool IsAsynLoading() const
		  {
			  return isAsynLoading;
		  }
		  void SetAsynLoading(bool b)
		  {
			  isAsynLoading = b;
		  }

		  bool IsDefaultResUsed()
		  {
			  return defaultResUsed;
		  }

		  void SetDefaultResUsed(bool isUsed)
		  {
			  defaultResUsed = isUsed;
		  }

		  void SetNeedReCompile(bool isNeedReCompile)
		  {
			  needReCompile = isNeedReCompile;
		  }

		  bool IsNeedReCompile()
		  {
			  return needReCompile;
		  }

		  virtual void ResetHandle()
		  {

		  }

	protected:
		friend class ResourceManager;
		Priority priority;
		Resources::ResourceId resID;
		GPtr<Resources::Resource> resData;
		bool isAsynLoading;
		ResInfoContainer* container;
		bool defaultResUsed;
		bool needReCompile;
	};
	//------------------------------------------------------------------------

	class TextureResInfo : public baseResInfo
	{
		__DeclareSubClass(TextureResInfo,baseResInfo);
	public:
		TextureResInfo()
		{
			texHandle = RenderBase::TextureHandle();
		}
		virtual ~TextureResInfo()
		{
		}
		void SetData(const Resources::ResourceId& tex_id, const RenderBase::TextureHandle& handle)
		{
			resID = tex_id;
			texHandle = handle;
		}
		void SetHandle(const RenderBase::TextureHandle& handle)
		{
			texHandle = handle;
		}
		const RenderBase::TextureHandle& GetHandle() const
		{
			return texHandle;
		}

		// 上下文形态是否存在
		virtual bool IsCompiled() const
		{
#ifdef __GENESIS_EDITOR__
			return GetHandle().IsValid() && Super::IsCompiled();
#else
			return GetHandle().IsValid();
#endif
		}

		virtual void ResetHandle() 
		{
			texHandle = RenderBase::TextureHandle();
		}

		virtual void Discard();

		// 编译上下文形态
		virtual void OnCompile();

		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

#ifndef __GENESIS_EDITOR__	
		virtual bool CanUsable() const
		{
			return IsCompiled();
		}
#endif

	protected:
		RenderBase::TextureHandle texHandle;
	};

	//--------------------------------------------------------------------------------
	class PrimitiveResInfo : public baseResInfo
	{
		__DeclareSubClass(PrimitiveResInfo,baseResInfo);
	public:
		PrimitiveResInfo()
		{
			primHandle = RenderBase::PrimitiveHandle();
		}
		virtual ~PrimitiveResInfo()
		{

		}
		const RenderBase::PrimitiveHandle& GetHandle() const
		{
			return primHandle;
		}
		void SetHandle( const RenderBase::PrimitiveHandle& h)
		{
			primHandle = h;
		}

		// 上下文形态是否存在
		virtual bool IsCompiled() const
		{
#ifdef __GENESIS_EDITOR__
			return GetHandle().IsValid() && Super::IsCompiled();
#else
			return GetHandle().IsValid();
#endif
		}

		virtual void ResetHandle()
		{
			primHandle = RenderBase::PrimitiveHandle();
		}

		virtual void Discard();

		// 编译上下文形态
		virtual void OnCompile();

		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

#ifndef __GENESIS_EDITOR__
		virtual bool CanUsable() const
		{
			return IsCompiled();
		}
#endif

	protected:
		RenderBase::PrimitiveHandle primHandle;
	};
	//------------------------------------------------------------------------

	class MaterialResInfo : public baseResInfo
	{
		__DeclareSubClass(MaterialResInfo,baseResInfo);
	public:
		MaterialResInfo()
		{
			matIns = NULL;
			mbSave = true;
			mbImport = false;
		}
		virtual ~MaterialResInfo()
		{

		}

		const Resources::ResourceId& GetMatID() const
		{
			return GetResID();
		}

		void  SetMatID(const Resources::ResourceId& matID)
		{
			SetResID(matID);
		}

		const GPtr<Graphic::MaterialInstance>& GetHandle() const
		{
			return matIns;
		}

		GPtr<Graphic::MaterialInstance>& GetHandle()
		{
			return matIns;
		}

		void SetHandle(const GPtr<Graphic::MaterialInstance>& m )
		{
			matIns = m;
		}
		void SetSave(const bool bFlag )
		{
			mbSave = bFlag;
		}
		bool GetSave()
		{
			return mbSave;
		}
		void SetImport(const bool bImport)
		{
			mbImport = bImport;
		}
		bool GetImport()
		{
			return mbImport;
		}
		virtual void AssignDefaultResCompile(const GPtr<baseResInfo>& defaultRes);

		virtual void ResetHandle()
		{
			matIns = NULL;
		}
		virtual void CopyFrom(const GPtr<baseResInfo>& res)
		{			
			baseResInfo::CopyFrom(res);
			GPtr<MaterialResInfo> matInfo = res.downcast<MaterialResInfo>();
			mbSave = matInfo->mbSave;
			mbImport = matInfo->mbImport;
		}

	protected:

		// 上下文形态是否存在
		virtual bool IsCompiled() const
		{
			return GetHandle().isvalid()&&Super::IsCompiled();
		}
		// 编译上下文形态
		virtual void OnCompile();

	protected:
		GPtr<Graphic::MaterialInstance> matIns;
		bool							mbSave;
		bool							mbImport;
		friend class ResourceManager;
	};

	class SpritePackageResInfo : public baseResInfo
	{
		__DeclareSubClass(SpritePackageResInfo,baseResInfo);
	public:
		GPtr<Sprite::SpritePackage> GetPackage() const;
	};

	//------------------------------------------------------------------------
	// 下列是简单的资源，不需要生成特定的对象

	typedef baseResInfo TemplateResInfo;

	typedef baseResInfo AudioResInfo;

	typedef baseResInfo AudioResInfo;

	typedef baseResInfo RawResInfo;

	typedef baseResInfo AnimationResInfo;

	typedef baseResInfo SkeletonResInfo;

	typedef baseResInfo PhysXMaterialResInfo;

	//------------------------------------------------------------------------
}






#endif // __resinfo_H__
