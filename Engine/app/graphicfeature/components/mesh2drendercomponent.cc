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
#include "graphicfeature/components/mesh2drendercomponent.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "graphicfeature/components/screenmeshrenderobject.h"
#include "graphicfeature/components/apprenderable.h"

#include "resource/meshres.h"
#include "resource/resourceserver.h"
#include "appframework/actor.h"
#include "graphicfeature/components/cameracomponent.h"

#include "foundation/util/array.h"
#include "graphicsystem/GraphicSystem.h"
#include "rendersystem/base/IndexBuffer.h"
#include "rendersystem/base/VertexBuffer.h"
#include "rendersystem/base/VertexComponent.h"
#include "foundation/meshbuilder/parallelogrambuilder.h"
#include "foundation/meshbuilder/conebuilder.h"
#include "foundation/meshbuilder/boxbuilder.h"

namespace App
{
	using namespace Resources;
	using namespace Graphic;
	using namespace RenderBase;
	using namespace Math;
	using namespace MeshBuilder;


	static const float R_Side = 1.0f;

	static const float3 B_Center(0.0f,0.0f, 0.0f);
	static const float B_Side = 1.0f;

	static const int C_Tessellation  = 12; //tessellation
	static const float C_Radius = 0.5f;
	static const float3 C_Center(0.0f,0.0f, 0.0f);
	static const float C_TopHeight = 1.0f;

	class _SimpleVertex
	{
	public:
		float3 position;    //
		float2 tex_uv;
		float3 normal;
		//Color32 color;
		static const SizeT normal_bias_in_byte = sizeof(float3) + sizeof(float2);
	};

	class _SimpleVertex2
	{
	public:
		float3 position;    //
		float3 normal;
		static const SizeT normal_bias_in_byte = sizeof(float3);
	};

	FillMode _FillModeToGSType(Mesh2dFillMode::_type mode)
	{
		FillMode pm = eFMSOLID;
		switch(mode)
		{
		case Mesh2dFillMode::Point:
			pm = eFMPOINT;
			break;

		case Mesh2dFillMode::Line:
			pm = eFMWIREFRAME;
			break;
		}
		return pm;
	}

	template<typename Vertex>
	inline void _setupVertexIndex(Graphic::VertexBufferData2& vbd2, SizeT vertex_count, Graphic::IndexBufferData2& ibd2, SizeT index_count)
	{
		vbd2.Setup(vertex_count, sizeof(Vertex), RenderBase::BufferData::Static, RenderBase::PrimitiveTopology::TriangleList, true);
		ibd2.Setup(index_count, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
	}



	__ImplementClass(App::Mesh2dRenderComponent, 'M2RC', App::RenderComponent );

	const float4 Mesh2dRenderComponent::sDefaultColor(1.0f, 1.0f, 1.0f, 1.0f);
	const float4 Mesh2dRenderComponent::sDefaultAmbient(0.6f,0.6f,0.6f,1.0f);
	const float4 Mesh2dRenderComponent::sDefaultLightDiffuse(0.4f,0.4f,0.4f,1.0f);
	const float4 Mesh2dRenderComponent::sDefaultLightDir(0.0f, 0.0f, -1.0f, 0.0f);

	const Resources::ResourceId Mesh2dRenderComponent::sDefaultShaderID = "sys:simple2d.shader";//sys:
	const Resources::ResourceId Mesh2dRenderComponent::sDefaultMap = "sys:white.dds";
	const ShaderParamString Mesh2dRenderComponent::sColorName = "_color";
	const ShaderParamString Mesh2dRenderComponent::sAmbientName = "_ambient";
	const ShaderParamString Mesh2dRenderComponent::sLightDiffuseName = "_light_diffuse";
	const ShaderParamString Mesh2dRenderComponent::sLightDirName = "_light_dir";
	const ShaderParamString Mesh2dRenderComponent::sDiffuseMapName = "_diffuseMap";

	Mesh2dRenderComponent::Mesh2dRenderComponent()
		:mPrimHandle(NULL)
		,mScreenObject()
		,mTargetCamera(NULL)
		,mMeshType(Mesh2dType::Unknown)
	{
		//empty
	}

	Mesh2dRenderComponent::~Mesh2dRenderComponent()
	{
	}
	void Mesh2dRenderComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, MoveAfter);
		mActor->RegisterComponentCallback(this, BeginFrame);
		Super::SetupCallbacks();
	}
	//------------------------------------------------------------------------
	void Mesh2dRenderComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------
	void Mesh2dRenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		n_assert(msg);
		Super::HandleMessage(msg);
	}

	void Mesh2dRenderComponent::UpdateRenderLayer()
	{
		if (mScreenObject.isvalid())
		{
			mScreenObject->SetLayerID(mActor->GetLayerID());
		}
	}

	void Mesh2dRenderComponent::OnActivate()
	{		
		if (mVisible)
		{
			_AttachRenderObject();
		};
		Super::OnActivate();

	}

	void Mesh2dRenderComponent::OnDeactivate()
	{
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}
		Super::OnDeactivate();		
	}

	void Mesh2dRenderComponent::SetVisible(bool bVis)
	{
		mVisible = bVis;
		if (IsActive())
		{
			if (mVisible)
			{
				_AttachRenderObject();
			}
			else
			{
				_DeattachRenderObject();
			}
		}
	}
	void Mesh2dRenderComponent::SetTargetCamera(CameraComponent* camera)
	{
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}		
		mTargetCamera = camera;//必须在中间
		if (IsActive() && mVisible)
		{
			_AttachRenderObject();
		}
	}
	void Mesh2dRenderComponent::_OnMoveAfter()
	{
		if(mActor && mScreenObject.isvalid())
		{
			mScreenObject->SetTransform(mActor->GetWorldTransform());
		}
	}

	void Mesh2dRenderComponent::_OnBeginFrame()
	{
		Super::_OnBeginFrame();
	}

	void Mesh2dRenderComponent::_AttachRenderObject()
	{
		if (mScreenObject.isvalid())
		{
			if (mTargetCamera)
			{
				mScreenObject->AttachNoCull((mTargetCamera->GetCameraObject().get())->GetCameraScene());
			}
			else
			{
				n_assert(mActor);
				mScreenObject->AttachNoCull(mActor->GetRenderScene());
			}

		}
	}

	void Mesh2dRenderComponent::_DeattachRenderObject()
	{
		if (mScreenObject.isvalid())
		{

			mScreenObject->Detach();
			
		}
	}

	void Mesh2dRenderComponent::_BuildRenderable(const _Mesh2dInfo& info, const GPtr<Resources::MeshRes>& meshRes, IndexT index)
	{
		SubMesh* subMesh = meshRes->GetSubMesh(index);
		n_assert(subMesh);
		RenderObjectType::RenderableType* renderable = mRenderableResUnitList[index].ResetRenderable<RenderObjectType::RenderableType>();
		renderable->SetRenderInfo(			
			subMesh->firstVertex, 
			subMesh->numVertex,
			subMesh->FirstIndex,
			subMesh->numIndex);
		renderable->GetMaterial()->SetRenderQueue(_getRenderQueue(info));
	}

	void Mesh2dRenderComponent::_BuildSimpleRenderable(const _Mesh2dInfo& info, SizeT vertexCount, SizeT indexCount)
	{
		RenderObjectType::RenderableType* renderable = mRenderableResUnitList[0].ResetRenderable<RenderObjectType::RenderableType>();
		renderable->SetRenderInfo(
			0, 
			vertexCount,
			0,
			indexCount);

		renderable->GetMaterial()->SetRenderQueue(_getRenderQueue(info));
	}

	void Mesh2dRenderComponent::SetActorTransform(GPtr<Actor>& actor, const Math::float2& pos, const Math::float3& scales)
	{
		n_assert(actor.isvalid());
		matrix44 mat = matrix44::identity();
		mat.mx[0][0] = scales.x();
		mat.mx[1][1] = scales.y();
		mat.mx[2][2] = scales.z();

		mat.mx[0][3] = pos.x();
		mat.mx[1][3] = -pos.y();
		actor->SetTransform(mat);
		

	}

	void Mesh2dRenderComponent::SetActorTransform(GPtr<Actor>& actor, const Math::float2& pos, const Math::float3& scales, const Math::float4& axis, float angle)
	{
		n_assert(actor.isvalid());

		matrix44 mat = matrix44::rotationaxis(axis, angle);
		mat.scale(float4(scales.x(), scales.y(), scales.z(), 1.0f));

		mat.mx[0][3] = pos.x();
		mat.mx[1][3] = -pos.y();
		mat.mx[2][3] = 0.0f;
		mat.mx[3][3] = 1.0f;
		actor->SetTransform(mat);
	}

	void Mesh2dRenderComponent::ChangeRenderInfo(int subMesh, const Mesh2dRenderInfo& info)
	{
		if (subMesh < mRenderableResUnitList.Size())
		{
			const Graphic::Renderable* renderable = mRenderableResUnitList[subMesh].GetRenderable();
			GPtr<RenderBase::RenderStateDesc>& desc = renderable->GetMaterial()->GetTech()->GetDefaultPass()->GetRenderStateObject();
			_setRenderState(desc, info, mMeshType);

			renderable->GetMaterial()->SetRenderQueue(_getRenderQueue(info));
		}

	}

	void Mesh2dRenderComponent::_resetRenderStateObj(const GPtr<Graphic::MaterialInstance>& material, const _Mesh2dInfo& info)
	{
		GPtr<RenderBase::RenderStateDesc>& desc = material->GetTech()->GetDefaultPass()->GetRenderStateObject();
		_setRenderState(desc, info, mMeshType);
	}

	void Mesh2dRenderComponent::_resetRenderStateObjs(const _Mesh2dInfo& info)
	{
		int index = 0;
		while(true)
		{
			const GPtr<Graphic::MaterialInstance>& material = GetMaterial(index);
			if (material == Graphic::MaterialInstance::NullMaterial)
			{
				return;
			}
			_resetRenderStateObj(material, info);
			++index;
		}

	}

	void Mesh2dRenderComponent::OnDestroy()
	{
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}
		mRenderableResUnitList.Clear();
		if (NULL != mPrimHandle)
		{
			if (Mesh2dType::Custom != mMeshType)
			{
				GraphicSystem::Instance()->RemovePrimitive(mPrimHandle);
			}

			mPrimHandle = RenderBase::PrimitiveHandle();
		}
		//mPrimGroup = NULL;

		Super::OnDestroy();
	}

	void Mesh2dRenderComponent::SetSimpleMesh(const _Mesh2dInfo& meshInfo)
	{
		
		if (Mesh2dType::Custom == meshInfo.mMeshType)
		{
			_buildCustomMesh(meshInfo, sDefaultMap);
		}
		else
		{
			_buildSimpleMesh(meshInfo, sDefaultMap);
		}
		//生成新的RenderObject
		mScreenObject = ScreenMeshRenderObject::Create();
		mScreenObject->SetOwner(this);
	}

	void Mesh2dRenderComponent::SetMesh2dParam(
		int index,
		const Math::float4& color, 
		const Math::float4& ambient /* = sDefaultAmbient */, 
		const Math::float4& lightDiffuse /* = sDefaultLightDiffuse */, 
		const Math::float4& lightDir /* = sDefaultLightDir */)
	{
		//int index = 0;
		int count = mRenderableResUnitList.Size();
		if (index >= 0 && index < count)
		{
			float4 dir = -lightDir;
			dir.set_w(0);
			SetShaderConstantParam(index, sColorName, color);
			SetShaderConstantParam(index, sAmbientName, ambient);
			SetShaderConstantParam(index, sLightDiffuseName, lightDiffuse);
			SetShaderConstantParam(index, sLightDirName, dir);
		}

	}

	void Mesh2dRenderComponent::SetSimpleMeshTex(const Resources::ResourceId& texID)
	{
		SetTexture(0, sDiffuseMapName, texID);
	}


	void Mesh2dRenderComponent::_buildSimpleMesh(const _Mesh2dInfo& meshInfo, const Resources::ResourceId& texID)
	{
		n_assert(Mesh2dType::Custom != meshInfo.mMeshType);		
		OnDestroy();
		SizeT vertexCount = 0;
		SizeT indexCount = 0;
		switch(meshInfo.mMeshType)
		{
		case Mesh2dType::Rectangle:
			{
				mPrimHandle = _createRectangle(meshInfo.mTransform, vertexCount, indexCount);
			}
			break;
		case Mesh2dType::Box:
			{
				mPrimHandle = _createBox(meshInfo.mTransform, vertexCount, indexCount);
			}
			break;
		case Mesh2dType::Cone:
			{
				ConeInfo* cone = (ConeInfo*)&meshInfo;
				mPrimHandle = _createCone(cone->mTessellation, meshInfo.mTransform, vertexCount, indexCount);
			}
			break;
		default:
			{
				n_error("Unsupport Mesh2dType:%d", (int)meshInfo.mMeshType);
			}
			break;
		}
		mMeshType = meshInfo.mMeshType;
		SetMaterialByShaderID(0, sDefaultShaderID, false);
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}

		// simple mesh只有一个renderable，如果前一个mesh有多个renderalbe，那么要把多余的去掉
		for(int i = mRenderableResUnitList.Size() - 1; i > 1; --i)
		{
			mRenderableResUnitList.EraseIndex(i);
		}
		_BuildSimpleRenderable(meshInfo, vertexCount, indexCount);
		_resetRenderStateObjs(meshInfo);
		SetTexture(0, sDiffuseMapName, texID, 1);
		SetMesh2dParam(0, sDefaultColor, sDefaultAmbient, sDefaultLightDiffuse);
	}
	
	void Mesh2dRenderComponent::_buildCustomMesh(const _Mesh2dInfo& meshInfo, const Resources::ResourceId& texID)
	{
		n_assert(Mesh2dType::Custom == meshInfo.mMeshType);
		CustomInfo* custom = (CustomInfo*)&meshInfo;
		OnDestroy();

		mPrimitiveResInfo = ResourceManager::Instance()->CreatePrimitiveInfo(custom->mID ,0);
		mMeshType = meshInfo.mMeshType;
		//SetShaderID(0, sDefaultShaderID);

		n_assert( GraphicSystem::HasInstance() );
		if (IsActive() && mVisible)
		{
			_DeattachRenderObject();
		}
		mRenderableResUnitList.Clear();

		const GPtr<MeshRes>& meshRes = mPrimitiveResInfo->GetRes().downcast<MeshRes>();
		mPrimHandle = mPrimitiveResInfo->GetHandle();


		// 生成新的renderable
		int sub_count = meshRes->GetSubMeshCount();
		for ( IndexT index = 0; index < sub_count; ++index )
		{

			SetMaterialByShaderID(index, sDefaultShaderID, false);
			_BuildRenderable(meshInfo, meshRes, index);
			SetMesh2dParam(index, sDefaultColor, sDefaultAmbient, sDefaultLightDiffuse);
		}
		_resetRenderStateObjs(meshInfo);
	}

	PrimitiveHandle Mesh2dRenderComponent::_createRectangle(const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount)
	{
		vertexCount = RECT_VERTEX_COUNT;
		indexCount = RECT_INDICES_COUNT;
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex<_SimpleVertex>(vbd2, RECT_VERTEX_COUNT, ibd2, RECT_INDICES_COUNT);

		_SimpleVertex* vertices = vbd2.GetBufferPtr<_SimpleVertex>();//_SimpleVertex vertices[RECT_VERTEX_COUNT];
		float hRS = R_Side * 0.5f;
		float3 top(0.0f, hRS, 0.0f);
		float3 right(hRS, 0.0f, 0.0f);
		float3 center(0.0f, 0.0f, 0.0f);
		MeshBuilder::ParallelogramBuilder::Set(vertices, top, right, center, 0, _SimpleVertex::normal_bias_in_byte);

		//RectBuilder::SetPositions(vertices, sizeof(_SimpleVertex), R_Side, R_Side);

		//RectBuilder::SetNormals(vertices, sizeof(_SimpleVertex), _SimpleVertex::normal_bias_in_byte);

		if (transform)
		{
			MeshBuilder::TransformPositions(vertices, RECT_VERTEX_COUNT, sizeof(_SimpleVertex), 0, *transform);
			MeshBuilder::TransformNormals(vertices, RECT_VERTEX_COUNT, sizeof(_SimpleVertex), _SimpleVertex::normal_bias_in_byte, *transform);
		}

		vertices[0].tex_uv = float2(0.0f, 0.0f);
		vertices[1].tex_uv = float2(1.0f, 0.0f);
		vertices[2].tex_uv = float2(0.0f, 1.0f);
		vertices[3].tex_uv = float2(1.0f, 1.0f);


		ushort* indices = ibd2.GetBufferPtr<ushort>();//ushort indices[RECT_INDICES_COUNT];
		ParallelogramBuilder::SetIndices(indices);

		
		Util::Array<VertexComponent>& vertexComponents = vbd2.GetVertexComponents();//Util::Array<VertexComponent> vertexComponents;
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord,0, RenderBase::VertexComponent::Float2));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Normal,0, RenderBase::VertexComponent::Float3));
		
		return Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		//return _buildMeshInfo(vertices, vertexComponents,RECT_VERTEX_COUNT, indices, RECT_INDICES_COUNT);
	}

	PrimitiveHandle Mesh2dRenderComponent::_createBox(const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount)
	{
		vertexCount = BOX_VERTEX_COUNT;
		indexCount = BOX_INDICES_COUNT;
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex<_SimpleVertex2>(vbd2, BOX_VERTEX_COUNT, ibd2, BOX_INDICES_COUNT);

		_SimpleVertex2* vertices = vbd2.GetBufferPtr<_SimpleVertex2>();//_SimpleVertex2 vertices[BOX_VERTEX_COUNT];

		BoxBuilder::SetPositions(vertices, sizeof(_SimpleVertex2), 0, B_Side, B_Side, B_Side, B_Center);
		BoxBuilder::SetNormals(vertices, sizeof(_SimpleVertex2), _SimpleVertex2::normal_bias_in_byte,
			vertices, sizeof(_SimpleVertex2), 0);

		if (transform)
		{
			MeshBuilder::TransformPositions(vertices, BOX_VERTEX_COUNT, sizeof(_SimpleVertex2), 0, *transform);
			MeshBuilder::TransformNormals(vertices, BOX_VERTEX_COUNT, sizeof(_SimpleVertex2), _SimpleVertex2::normal_bias_in_byte, *transform);
		}

		ushort* indices = ibd2.GetBufferPtr<ushort>();//ushort indices[BOX_INDICES_COUNT];
		BoxBuilder::SetIndices(indices);

		Util::Array<VertexComponent>& vertexComponents = vbd2.GetVertexComponents();//static Util::Array<VertexComponent> vertexComponents;
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Normal,0, RenderBase::VertexComponent::Float3));
		
		return Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
	}

	PrimitiveHandle Mesh2dRenderComponent::_createCone(int tessellation, const Math::matrix44* transform, SizeT& vertexCount, SizeT& indexCount)
	{
		int vertex_count = ConeBuilder::VertexCount(tessellation);
		int index_count = ConeBuilder::IndexCount(tessellation);
		vertexCount = vertex_count;
		indexCount = index_count;

		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex<_SimpleVertex2>(vbd2, vertex_count, ibd2, index_count);

		_SimpleVertex2* vertices = vbd2.GetBufferPtr<_SimpleVertex2>();//Util::FixedArray<_SimpleVertex2> vertices(vertex_count);

		ConeBuilder::SetPositions(vertices, sizeof(_SimpleVertex2), 0, tessellation, C_Radius, C_TopHeight, C_Center);
		ConeBuilder::SetNormals(vertices, sizeof(_SimpleVertex2), _SimpleVertex2::normal_bias_in_byte, tessellation,
								vertices, sizeof(_SimpleVertex2), 0);


		if (transform)
		{
			MeshBuilder::TransformPositions(vertices, vertex_count, sizeof(_SimpleVertex2), 0, *transform);
			MeshBuilder::TransformNormals(vertices, vertex_count, sizeof(_SimpleVertex2), _SimpleVertex2::normal_bias_in_byte, *transform);
		}

		ushort* indices = ibd2.GetBufferPtr<ushort>();//Util::FixedArray<ushort> indices(index_count);
		ConeBuilder::SetIndices(indices, tessellation);
		Util::Array<VertexComponent>& vertexComponents = vbd2.GetVertexComponents();//Util::Array<VertexComponent> vertexComponents;
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Normal,0, RenderBase::VertexComponent::Float3));
		return Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
	}

	static const SizeT Alpha_Mask = 2;
	static const SizeT Add_Mask = 1;
	static const SizeT NoZTest_Mask = 1<<2;

	Graphic::RenderQueue Mesh2dRenderComponent::_getRenderQueue(const Mesh2dRenderInfo& info)
	{
		SizeT forSort = 0;
		if (!info.mZTest)
		{
			forSort += NoZTest_Mask;
		}
		switch (info.mBlendMode)
		{
		case Mesh2dBlendMode::Alpha:
			{
				forSort += Alpha_Mask;
			}
			break;
		case Mesh2dBlendMode::Add:
			{
				forSort += Add_Mask;
			}
			break;
		}
		return Graphic::RenderQueue(Graphic::RenderQueue::eRQTScreen, forSort);
	}

	//struct Mesh2dRenderableSort : public std::binary_function<const GPtr<Renderable>&, const GPtr<Renderable>&, std::size_t>
	//{
	//	bool operator() (const GPtr<Renderable>& lhs, const GPtr<Renderable>& rhs) const
	//	{
	//		const GPtr<Mesh2dRenderable>& l2d = lhs.downcast<Mesh2dRenderable>();
	//		const GPtr<Mesh2dRenderable>& r2d = rhs.downcast<Mesh2dRenderable>();

	//		return l2d->GetSort() < r2d->GetSort();
	//	}
	//};

	//void Mesh2dRenderComponent::_sortMesh2dRenderable()
	//{
	//	GraphicSystem* gs = GraphicSystem::Instance();
	//	n_assert(gs);
	//	Util::Array<GPtr<Renderable>>& mesh2d_list = gs->GetRenderable2dList();
	//	Util::CustomSortArray<GPtr<Renderable>, Mesh2dRenderableSort>(mesh2d_list);

	//}

	void Mesh2dRenderComponent::_setBlendState(DeviceBlendState& state, Mesh2dBlendMode::_type mode)
	{
		switch(mode)
		{
		case Mesh2dBlendMode::Alpha:
			{
				state.m_alphaBlendEnable[0] = true;
				state.m_srcBlendAlpha[0] = eBFSRCALPHA;
				state.m_destBlendAlpha[0] = eBFINVSRCALPHA;
				break;
			}
		case Mesh2dBlendMode::Add:
			{
				state.m_alphaBlendEnable[0] = true;
				state.m_srcBlendAlpha[0] = eBFSRCALPHA;
				state.m_destBlendAlpha[0] = eBFONE;
				break;
			}
		case Mesh2dBlendMode::Opacity:
			{
				state.m_alphaBlendEnable[0] = false;
				break;
			}
		}
	}

	void Mesh2dRenderComponent::_setRenderState(GPtr<RenderBase::RenderStateDesc>& state, const Mesh2dRenderInfo& info, Mesh2dType::_type meshType)
	{
		DeviceRasterizerState rasterizerState = state->GetRasterizerState();
		DeviceBlendState blendState = state->GetBlendState();
		DeviceDepthAndStencilState depthState = state->GetDepthAndStencilState();

		rasterizerState.m_fillMode = _FillModeToGSType(info.mFillMode);			
		_setBlendState(blendState, info.mBlendMode);
		depthState.m_depthEnable = info.mZTest;

		if (Mesh2dType::Rectangle == meshType || Mesh2dBlendMode::Add == info.mBlendMode)
		{
			rasterizerState.m_cullMode = RenderBase::eCMNONE;			
		}

		state->SetRasterizerState(rasterizerState);
		state->SetBlendState(blendState);
		state->SetDepthAndStencilState(depthState);
	}
		 
}
