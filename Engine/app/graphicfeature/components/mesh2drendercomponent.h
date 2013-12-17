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
#ifndef __simplemeshrendercomponent_H__
#define __simplemeshrendercomponent_H__

#include "graphicfeature/components/rendercomponent.h"
#include "graphicsystem/Material/materialinstance.h"
#include "resource/resourcemanager.h"
#include "rendersystem/base/PrimitiveGroup.h"
namespace App
{

	// --------------------------------------------------------------------------------------
	struct Mesh2dType
	{
		enum _type
		{
			Unknown = -1,			
			//Triangle,	//未实现
			Rectangle,
			Box,		
			Cone,		//圆锥
			Custom		
		};

	private:
		Mesh2dType(){}
	};
	// --------------------------------------------------------------------------------------
	struct Mesh2dBlendMode
	{
		enum _type
		{
			Add,
			Alpha,
			Opacity
		};
	};
	// --------------------------------------------------------------------------------------
	struct Mesh2dFillMode
	{
		enum _type
		{
			Point,
			Line,
			Fill
		};
	};
	// --------------------------------------------------------------------------------------
	struct Mesh2dRenderInfo
	{
	public:
		bool mZTest;
		Mesh2dBlendMode::_type mBlendMode;
		Mesh2dFillMode::_type mFillMode;
		Mesh2dRenderInfo();
	};
	inline Mesh2dRenderInfo::Mesh2dRenderInfo()
	{
		mZTest = true;
		mBlendMode = Mesh2dBlendMode::Opacity;
		mFillMode = Mesh2dFillMode::Fill;
	}
	// --------------------------------------------------------------------------------------
	struct _Mesh2dInfo : public Mesh2dRenderInfo
	{
	public:
		Mesh2dType::_type mMeshType;
		Math::matrix44* mTransform;
	protected:
		_Mesh2dInfo(Mesh2dType::_type type_);
	};

	inline _Mesh2dInfo::_Mesh2dInfo(Mesh2dType::_type type_)
	{
		mMeshType = type_;
		mTransform = NULL;
		mBlendMode = Mesh2dBlendMode::Opacity;
		mFillMode = Mesh2dFillMode::Fill;
		mZTest = true;
	}
	// --------------------------------------------------------------------------------------
	struct RectInfo : public _Mesh2dInfo
	{
	public:
		RectInfo();
	};

	inline RectInfo::RectInfo()
		: _Mesh2dInfo(Mesh2dType::Rectangle)
	{

	}
	// --------------------------------------------------------------------------------------
	struct BoxInfo : public _Mesh2dInfo
	{
	public:
		BoxInfo();
	};

	inline BoxInfo::BoxInfo()
		:  _Mesh2dInfo(Mesh2dType::Box)
	{

	}
	// --------------------------------------------------------------------------------------
	struct ConeInfo : public _Mesh2dInfo
	{
	public:
		int mTessellation;
		ConeInfo(int tessellation = 12);
	};

	inline ConeInfo::ConeInfo(int tessellation /* = 12 */)
		:  _Mesh2dInfo(Mesh2dType::Cone)
	{
		mTessellation = tessellation;
	}
	// --------------------------------------------------------------------------------------
	struct CustomInfo : public _Mesh2dInfo
	{
	public:
		Resources::ResourceId mID;
		CustomInfo(Resources::ResourceId id);
	};

	inline CustomInfo::CustomInfo(Resources::ResourceId id)
		: _Mesh2dInfo(Mesh2dType::Custom)
	{
		mID = id;
	}


	class CameraComponent;
	class ScreenMeshRenderObject;

	// --------------------------------------------------------------------------------------
	/*
	管理要渲染一个简单mesh需要的数据。包括VBO、材质、材质参数等信息, 暂时不支持流失加载。
	*/
	class Mesh2dRenderComponent : public App::RenderComponent
	{
		__DeclareSubClass(Mesh2dRenderComponent, App::RenderComponent);
	public:
		Mesh2dRenderComponent();
		virtual ~Mesh2dRenderComponent();

		// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		virtual void UpdateRenderLayer();

		//	Serialization

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		//virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
		{
			n_error("no suport");
		}

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const{n_error("no suport");}

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent ){n_error("no suport");}

		// 将renderable从graphicsystem中移除
		void _DeattachRenderables();

		// 将renderable加入到graphicsystem中
		void _AttachRenderables();

		//virtual bool _IsAllResourceLoaded();

		friend class Mesh2dRenderable;
		friend class Mesh2dRenderer;

	public: // get resource

		const GPtr<Resources::PrimitiveResInfo>& GetPrimtiveResInfo() const;

		void SetSimpleMesh(const _Mesh2dInfo& meshInfo);

		void SetSimpleMeshTex(const Resources::ResourceId& texID);

		//************************************
		// Method:    SetSimpleMeshParam
		// FullName:  App::Mesh2dRenderComponent::SetSimpleMeshParam
		// Access:    public 
		// Returns:   void
		// Qualifier: 设置简单的模型状态下的光照参数
		// Parameter: const Math::ColorF & color 颜色衰减
		// Parameter: const Math::float4 & ambient 环境反射参数
		// Parameter: const Math::float4 & lightDiffuse 光照漫反射参数，现在光照方向默认为垂直屏幕向里
		//************************************
		void SetMesh2dParam(
			int index,
			const Math::float4& color, 
			const Math::float4& ambient = sDefaultAmbient, 
			const Math::float4& lightDiffuse = sDefaultLightDiffuse,
			const Math::float4& lightDir = sDefaultLightDir);

		void ChangeRenderInfo(int subMesh, const Mesh2dRenderInfo& info);

		void SetVisible(bool bVis);

		const RenderBase::PrimitiveHandle& GetPrimive() const;

		void SetTargetCamera(CameraComponent* camera);
		CameraComponent* GetTargetCamera() const;

		//************************************
		// Method:    SetTransform
		// FullName:  App::Mesh2dRenderComponent::SetTransform
		// Access:    public 
		// Returns:   void
		// Qualifier: 设置方位参数，单位: 像素
		// Parameter: const Math::float2 & pos 位置
		// Parameter: const Math::float3 & scales 缩放
		//************************************
		static void SetActorTransform(GPtr<Actor>& actor, const Math::float2& pos, const Math::float3& scales);


		//************************************
		// Method:    SetTransform
		// FullName:  App::Mesh2dRenderComponent::SetTransform
		// Access:    public 
		// Returns:   void
		// Qualifier: 设置方位参数，单位: 像素, 弧度
		// Parameter: const Math::float2 & pos 位置
		// Parameter: const Math::float3 & scales 缩放
		// Parameter: const Math::float4 & axis 旋转轴, 必须单位化
		// Parameter: float angle 旋转角的弧度
		//************************************
		static void SetActorTransform(GPtr<Actor>& actor, const Math::float2& pos, const Math::float3& scales, const Math::float4& axis, float angle);

	protected:

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		virtual void OnDestroy();

		virtual void _OnBeginFrame();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

	private:

		void _BuildSimpleRenderable(const _Mesh2dInfo& info, SizeT vertexCount, SizeT indexCount);

		void _BuildRenderable(const _Mesh2dInfo& info, const GPtr<Resources::MeshRes>& meshRes, IndexT index);

		// 将renderable从graphicsystem中移除
		void _DeattachRenderObject();

		// 将renderable加入到graphicsystem中
		void _AttachRenderObject();

		void _buildSimpleMesh(const _Mesh2dInfo& meshInfo, const Resources::ResourceId& texID);
		void _buildCustomMesh(const _Mesh2dInfo& meshInfo, const Resources::ResourceId& texID);
		void _resetRenderStateObjs(const _Mesh2dInfo& info);
		void _resetRenderStateObj(const GPtr<Graphic::MaterialInstance>& material, const _Mesh2dInfo& info);

		static RenderBase::PrimitiveHandle _createRectangle(const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount);
		static RenderBase::PrimitiveHandle _createBox(const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount);
		static RenderBase::PrimitiveHandle _createCone(int tessellation, const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount);
		static Graphic::RenderQueue _getRenderQueue(const Mesh2dRenderInfo& info);
		static void _setBlendState(RenderBase::DeviceBlendState& state, Mesh2dBlendMode::_type mode);
		static void _setRenderState(GPtr<RenderBase::RenderStateDesc>& state, const Mesh2dRenderInfo& info, Mesh2dType::_type meshType);
		//static void _sortMesh2dRenderable();

		//template<typename Vertex>
		//static RenderBase::PrimitiveHandle _buildMeshInfo(Vertex vertices[], const Util::Array<RenderBase::VertexComponent>& vertex_components, SizeT vertex_count, ushort indices[], SizeT index_count);

	private:
		typedef ScreenMeshRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> RenderObjectPtr;
		RenderObjectPtr mScreenObject;

		GPtr<Resources::PrimitiveResInfo> mPrimitiveResInfo;
		RenderBase::PrimitiveHandle mPrimHandle;
		
		Mesh2dType::_type mMeshType;
		CameraComponent* mTargetCamera;

		static const Math::float4 sDefaultColor;
		static const Math::float4 sDefaultAmbient;
		static const Math::float4 sDefaultLightDiffuse;
		static const Math::float4 sDefaultLightDir;

		static const Resources::ResourceId sDefaultShaderID;
		static const Resources::ResourceId sDefaultMap;
		static const ShaderParamString sColorName;
		static const ShaderParamString sAmbientName;
		static const ShaderParamString sLightDiffuseName;
		static const ShaderParamString sLightDirName;
		static const ShaderParamString sDiffuseMapName;
	};

	inline const GPtr<Resources::PrimitiveResInfo>& Mesh2dRenderComponent::GetPrimtiveResInfo() const
	{
		return mPrimitiveResInfo;		 
	}

	inline const RenderBase::PrimitiveHandle& Mesh2dRenderComponent::GetPrimive() const
	{
		return mPrimHandle;
	}

	inline CameraComponent* Mesh2dRenderComponent::GetTargetCamera() const
	{
		return mTargetCamera;
	}
}



#endif // __simplemeshrendercomponent_H__

