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
#include "DeferredLightingPass.h"
#include "graphicsystem/Light/Light.h"
#include "graphicsystem/Camera/RenderPipeline/ActiveLight.h"
#include "graphicsystem/Camera/RenderPipeline/RenderPipelineManager.h"
#include "foundation/meshbuilder/parallelogrambuilder.h"
#include "foundation/meshbuilder/conebuilder.h"
#include "foundation/meshbuilder/boxbuilder.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "foundation/math/newMath/new_scalar.h"
namespace Graphic
{

	static const float S_COS15 = Math::n_cos((float)PI / 12.0f);

	using namespace Math;
	using namespace RenderBase;
	////公用

	static const float3 P_Center(0.0f,0.0f, 0.0f);
	static const float P_Side = 2.0f;

	static const int S_Tessellation  = 12; //tessellation
	static const int S_VertexCount = CONE_VERTEX_COUNT(S_Tessellation);
	static const int S_IndexCount = CONE_INDEX_COUNT(S_Tessellation);
	static const float S_Radius = 1.0f;
	static const float3 S_Center(0.0f,-1.0f, 0.0f);

	static const float S_TopHeight = 1.0f;
	struct _light_vertex
	{
	public:
		Math::float3 position;
	};

	void _setupVertexIndex(Graphic::VertexBufferData2& vbd2, SizeT vertex_count, Graphic::IndexBufferData2& ibd2, SizeT index_count)
	{
		vbd2.Setup(vertex_count, sizeof(_light_vertex), RenderBase::BufferData::Static, RenderBase::PrimitiveTopology::TriangleList, true);
		ibd2.Setup(index_count, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
	}

	__ImplementClass(DeferredLightingPass,'DFLP',Core::RefCounted)

		DeferredLightingPass::DeferredLightingPass()
	{
	}

	DeferredLightingPass::~DeferredLightingPass()
	{
	}
	void DeferredLightingPass::Init()
	{
		_buildSunLight();
		_buildDirectionalLight();
		_buildPointLight();
		_buildSpotLight();
	}

	void DeferredLightingPass::RenderActiveLights(PipelineParamters& params)
	{
		ActiveLightCollection& active_lights = params.m_activeLights.GetActiveLights();; 
		const GPtr<RenderToTexture>& light_target = params.m_camera->GetDeferredLightMap();


		GraphicSystem* gs = GraphicSystem::Instance();
		n_assert(NULL != gs);

		gs->SetRenderTarget(light_target, 0, RenderBase::RenderTarget::ClearAll);



		ActiveLightCollection::Iterator it = active_lights.Begin();
		ActiveLightCollection::Iterator end = active_lights.End();
		while(it != end)
		{
			_renderLight(*it);
			++it;
		}
	}

	void DeferredLightingPass::_buildSunLight()
	{
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex(vbd2, RECT_VERTEX_COUNT, ibd2, RECT_INDICES_COUNT);
		_light_vertex* pos = vbd2.GetBufferPtr<_light_vertex>();
		ushort* indices = ibd2.GetBufferPtr<ushort>();

		float3 top(0.0f, 1.0f, 0.0f);
		float3 right(1.0f, 0.0f, 0.0f);
		float3 center(0.0f, 0.0f, 0.0f);
		MeshBuilder::ParallelogramBuilder::Set(pos, top, right, center, 0);
		MeshBuilder::ParallelogramBuilder::SetIndices(indices);

		mSunLightMesh.mPrimHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		Util::StringAtom fileName("sys:Deferred_SunLight.shader");
		mSunLightMesh.mMaterial = GenesisMaterialMaker::MakeFromShader(fileName);
		mSunLightMesh.mShaderHandle = const_cast<RenderBase::GPUProgramHandle*>(&mSunLightMesh.mMaterial->GetTech(0)->GetDefaultPass()->GetGPUProgramHandle());
	}
	void DeferredLightingPass::_buildDirectionalLight()
	{
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex(vbd2, RECT_VERTEX_COUNT, ibd2, RECT_INDICES_COUNT);
		_light_vertex* pos = vbd2.GetBufferPtr<_light_vertex>();
		ushort* indices = ibd2.GetBufferPtr<ushort>();

		float3 top(0.0f, 1.0f, 0.0f);
		float3 right(1.0f, 0.0f, 0.0f);
		float3 center(0.0f, 0.0f, 0.0f);
		MeshBuilder::ParallelogramBuilder::Set(pos, top, right, center, 0);
		MeshBuilder::ParallelogramBuilder::SetIndices(indices);

		mDirectionalLightMesh.mPrimHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		Util::StringAtom fileName("sys:Deferred_DirectionalLight.shader");
		mDirectionalLightMesh.mMaterial = GenesisMaterialMaker::MakeFromShader(fileName);
		mDirectionalLightMesh.mShaderHandle = const_cast<RenderBase::GPUProgramHandle*>(&mDirectionalLightMesh.mMaterial->GetTech(0)->GetDefaultPass()->GetGPUProgramHandle());

	}
	void DeferredLightingPass::_buildPointLight()
	{
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex(vbd2, BOX_VERTEX_COUNT, ibd2, BOX_INDICES_COUNT);

		_light_vertex* pos = vbd2.GetBufferPtr<_light_vertex>();
		ushort* indices = ibd2.GetBufferPtr<ushort>();
		MeshBuilder::BoxBuilder::SetPositions(pos, sizeof(_light_vertex), 0, P_Side, P_Side, P_Side, P_Center);
		MeshBuilder::BoxBuilder::SetIndices(indices);

		mPointLightMesh.mPrimHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		Util::StringAtom fileName("sys:Deferred_PointLight.shader");
		mPointLightMesh.mMaterial = GenesisMaterialMaker::MakeFromShader(fileName);
		mPointLightMesh.mShaderHandle = const_cast<RenderBase::GPUProgramHandle*>(&mPointLightMesh.mMaterial->GetTech(0)->GetDefaultPass()->GetGPUProgramHandle());

	}
	void DeferredLightingPass::_buildSpotLight()
	{
		////效果是，锥顶在坐标原点，朝向是z轴正方向。
		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex(vbd2, S_VertexCount, ibd2, S_IndexCount);

		_light_vertex* pos = vbd2.GetBufferPtr<_light_vertex>();
		ushort* indices = ibd2.GetBufferPtr<ushort>();
		MeshBuilder::ConeBuilder::SetPositions(pos, sizeof(_light_vertex), 0, S_Tessellation, S_Radius, S_TopHeight, S_Center);
		MeshBuilder::ConeBuilder::SetIndices(indices, S_Tessellation);

		matrix44 trans = matrix44::rotationx(N_PI * 0.5f);
		MeshBuilder::TransformPositions(pos, S_VertexCount, sizeof(_light_vertex), 0, trans);


		mSpotLightMesh.mPrimHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		Util::StringAtom fileName("sys:Deferred_SpotLight.shader");
		mSpotLightMesh.mMaterial = GenesisMaterialMaker::MakeFromShader(fileName);
		mSpotLightMesh.mShaderHandle = const_cast<RenderBase::GPUProgramHandle*>(&mSpotLightMesh.mMaterial->GetTech(0)->GetDefaultPass()->GetGPUProgramHandle());
	}

	void DeferredLightingPass::_renderLight(const ActiveLightInfo& activeLight)
	{
		Light::LightType light_type = activeLight.light->GetLightType();
		switch (light_type)
		{
		case Light::eSunLight:
			{
				_renderSunLight(activeLight);
			}
			break;
		case Light::eDirectionalLight:
			{
				_renderDirectionalLight(activeLight);
			}
			break;
		case Light::ePointLight:
			{
				_renderPointLight(activeLight);
			}
			break;
		case Light::eSpotLight:
			{
				_renderSpotLight(activeLight);
			}
			break;
		default:
			{

			}
			break;
		}
	}
	void DeferredLightingPass::_renderSunLight(const ActiveLightInfo& activeLight)
	{
		const GPtr<Light>& light = activeLight.light; 
		GraphicSystem* gs = GraphicSystem::Instance();
		n_assert(NULL != gs);

		float4 color = light->GetLightColor() * light->GetLightIntensity();

		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
		pGMP->SetVectorParam(eGShaderVecLightDir0, light->GetTransform().get_zaxis());
		pGMP->SetVectorParam(eGShaderVecLightDiffuse0, color);



		const Util::Array<GPtr<Camera> >& smcList = light->GetShadowMapCameraList();
		float lightCameraFarDistance[4] = {0.f,0.f,0.f,0.f};
		for (SizeT i = 0; i < smcList.Size(); ++i)
		{
			if (i == 0)
				pGMP->SetMatrixParam(eGShaderMatLightV,smcList[i]->GetViewTransform());

			lightCameraFarDistance[i] = smcList[i]->GetCameraSetting().GetZFar() - smcList[i]->GetCameraSetting().GetZNear();
			pGMP->SetMatrixParam(static_cast<GlobalMatrixParamIndex>(eGShaderMatLightP0 + i ),smcList[i]->GetProjTransform());
		}
		pGMP->SetVectorParam(eGShaderVecLightCameraFar,float4(lightCameraFarDistance[0],lightCameraFarDistance[1],lightCameraFarDistance[2],lightCameraFarDistance[3]));



		const GPtr<MaterialPass>& pass = mSunLightMesh.mMaterial->GetTech()->GetDefaultPass();
		GraphicRenderer::SetMaterialCommonParams(pass);
		GraphicRenderer::SetMaterialCustomParams(mSunLightMesh.mMaterial->GetParamList(), pass);

		gs->SetShaderProgram(*mSunLightMesh.mShaderHandle);
		gs->SetRenderState(mSunLightMesh.mMaterial->GetTech()->GetDefaultPass()->GetRenderStateObject());

		gs->DrawPrimitive(mSunLightMesh.mPrimHandle);

	}
	void DeferredLightingPass::_renderDirectionalLight(const ActiveLightInfo& activeLight)
	{
		const GPtr<Light>& light = activeLight.light; 
		GraphicSystem* gs = GraphicSystem::Instance();
		n_assert(NULL != gs);

		float4 color = light->GetLightColor() * light->GetLightIntensity();
		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
		pGMP->SetVectorParam(eGShaderVecLightDir0, light->GetTransform().get_zaxis());
		pGMP->SetVectorParam(eGShaderVecLightDiffuse0, color);

		const GPtr<MaterialPass>& pass = mDirectionalLightMesh.mMaterial->GetTech()->GetDefaultPass();
		GraphicRenderer::SetMaterialCommonParams(pass);
		GraphicRenderer::SetMaterialCustomParams(mDirectionalLightMesh.mMaterial->GetParamList(), pass);

		gs->SetShaderProgram(*mDirectionalLightMesh.mShaderHandle);
		gs->SetRenderState(mDirectionalLightMesh.mMaterial->GetTech()->GetDefaultPass()->GetRenderStateObject());

		gs->DrawPrimitive(mDirectionalLightMesh.mPrimHandle);

	}
	void DeferredLightingPass::_renderPointLight(const ActiveLightInfo& activeLight)
	{
		const GPtr<Light>& light = activeLight.light; 
		GraphicSystem* gs = GraphicSystem::Instance();
		n_assert(NULL != gs);

		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

		const matrix44& view = pGMP->GetMatrixParam(eGShaderMatV);

		float4 light_pos = light->GetLightPos();
		const float4& camPos = pGMP->GetVectorParam(eGShaderVecCameraPos);
		float4 cam_to_light = light_pos - camPos;

		matrix44 trans = matrix44::identity();

		float scale = light->GetLightRange();
		trans.mx[0][0] = scale;
		trans.mx[1][1] = scale;
		trans.mx[2][2] = scale;		
		float4 pos = matrix44::transform(view, light_pos);
		trans.set_position(pos);


		float4 color = light->GetLightColor() * light->GetLightIntensity();

		Math::float4 attenuation;
		attenuation.set_x(light->GetConstantAttenuation());
		attenuation.set_y(light->GetLinearAttenuation());
		attenuation.set_z(light->GetQuadraticAttenuation());

		pGMP->SetMatrixParam(eGShaderMatM, trans);
		pGMP->SetVectorParam(eGShaderVecLightDir0, light->GetTransform().get_zaxis());
		pGMP->SetVectorParam(eGShaderVecLightDiffuse0, color);
		pGMP->SetVectorParam(eGShaderVecLightPos0, light_pos);
		pGMP->SetVectorParam(eGShaderVecLightAttenuation0, attenuation);

		const GPtr<MaterialPass>& pass = mPointLightMesh.mMaterial->GetTech()->GetDefaultPass();
		GraphicRenderer::SetMaterialCommonParams(pass);
		GraphicRenderer::SetMaterialCustomParams(mPointLightMesh.mMaterial->GetParamList(), pass);

		gs->SetShaderProgram(*mPointLightMesh.mShaderHandle);
		gs->SetRenderState(mPointLightMesh.mMaterial->GetTech()->GetDefaultPass()->GetRenderStateObject());

		gs->DrawPrimitive(mPointLightMesh.mPrimHandle);
	}

	void DeferredLightingPass::_calSpotWorld(const Light* light, Math::matrix44& trans)
	{

		float z = light->GetLightRange();

		float cut = light->GetCosHalfOuterAngle();
		float l = z / cut;
		float xy = n_sqrt(l * l - z * z) / S_COS15;//底面圆的半径
		matrix44 scale_mat = matrix44::scaling(xy, xy, z);
		trans = matrix44::multiply(light->GetTransform(), scale_mat);
	}

	void DeferredLightingPass::_renderSpotLight(const ActiveLightInfo& activeLight)
	{
		const Light* light = activeLight.light; 
		GraphicSystem* gs = GraphicSystem::Instance();
		n_assert(NULL != gs);

		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

		matrix44 world;
		_calSpotWorld(light, world);

		float4 dir = light->GetTransform().get_zaxis();
		dir.set_w(light->GetCosHalfOuterAngle());
		float4 color = light->GetLightColor() * light->GetLightIntensity();

		Math::float4 attenuation;
		attenuation.set_x(light->GetConstantAttenuation());
		attenuation.set_y(light->GetLinearAttenuation());
		attenuation.set_z(light->GetQuadraticAttenuation());
		attenuation.set_w(light->GetExponent());

		float4 light_pos = light->GetLightPos();


		pGMP->SetMatrixParam(eGShaderMatM, world);
		pGMP->SetVectorParam(eGShaderVecLightDir0, dir);
		pGMP->SetVectorParam(eGShaderVecLightDiffuse0, color);
		pGMP->SetVectorParam(eGShaderVecLightPos0, light_pos);
		pGMP->SetVectorParam(eGShaderVecLightAttenuation0, attenuation);

		const GPtr<MaterialPass>& pass = mSpotLightMesh.mMaterial->GetTech()->GetDefaultPass();
		GraphicRenderer::SetMaterialCommonParams(pass);
		GraphicRenderer::SetMaterialCustomParams(mSpotLightMesh.mMaterial->GetParamList(), pass);


		gs->SetShaderProgram(*mSpotLightMesh.mShaderHandle);
		gs->SetRenderState(mSpotLightMesh.mMaterial->GetTech()->GetDefaultPass()->GetRenderStateObject());

		gs->DrawPrimitive(mSpotLightMesh.mPrimHandle);
	}
}