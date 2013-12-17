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
#include "Material/materialinstance.h"
#include "Renderable/Renderable.h"
#include "GraphicRenderer.h"
#include "GraphicSystem.h"
namespace Graphic
{

	uint GraphicRenderer::s_preShaderInstanceID = 0;
	void* GraphicRenderer::s_pPreMaterialInstance = 0;
	__ImplementAbstractClass(GraphicRenderer,'GFGS',Core::RefCounted)

		GraphicRenderer::GraphicRenderer()
	{
		//empty
	}

	GraphicRenderer::~GraphicRenderer()
	{
		//empty
	}

	void GraphicRenderer::Setup()
	{
		//empty
	}

	void GraphicRenderer::SetGlobalVertexShaderConstant(const ShaderParam& sp)
	{
		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();

		for ( SizeT i = eGShaderMatBegin; i < eGShaderMatEnd; ++i )//eGShaderMatMVP
		{
			Util::String paramName;
			Math::matrix44 matVal;
			gsp->GetMatrixParam(static_cast<GlobalMatrixParamIndex>(i),paramName,matVal);
			if (paramName == sp.GetName())
			{
				GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(sp.GetRegister(), &matVal,1);
				return;
			}
		}

		for ( SizeT i = eGShaderVecBegin; i < eGShaderVecEnd; ++i )
		{
			Util::String paramName;
			Math::float4 vecVal;
			gsp->GetVectorParam(static_cast<GlobalVectorParamIndex>(i),paramName,vecVal);
			if (paramName == sp.GetName())
			{
				GraphicSystem::Instance()->SetVertexShaderConstantVectorF(sp.GetRegister(), &vecVal,1);
				return;
			}
		}

		for ( IndexT i = eGShaderTexBegin; i < eGShaderTexEnd; ++i )
		{
			Util::String paramName;
			RenderBase::TextureHandle texHandle;

			gsp->GetTextureParam(static_cast<GlobalTexParamIndex>(i),paramName,texHandle);
			if (paramName == sp.GetName() && texHandle.IsValid())
			{
				GraphicSystem::Instance()->SetTexture(sp.GetRegister(),texHandle);
				return;
			}
		}

	}

	void GraphicRenderer::SetGlobalPixelShaderConstant(const ShaderParam& sp)
	{
		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();

		for ( SizeT i = eGShaderMatBegin; i < eGShaderMatEnd; ++i )
		{
			Util::String paramName;
			Math::matrix44 matVal;
			gsp->GetMatrixParam(static_cast<GlobalMatrixParamIndex>(i),paramName,matVal);
			if (paramName == sp.GetName())
			{
				GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(sp.GetRegister(), &matVal,1);
				return;
			}
		}

		for ( SizeT i = eGShaderVecBegin; i < eGShaderVecEnd; ++i )
		{
			Util::String paramName;
			Math::float4 vecVal;
			gsp->GetVectorParam(static_cast<GlobalVectorParamIndex>(i),paramName,vecVal);
			if (paramName == sp.GetName())
			{
				GraphicSystem::Instance()->SetPixelShaderConstantVectorF(sp.GetRegister(), &vecVal,1);
				return;
			}
		}


		for ( IndexT i = eGShaderTexBegin; i < eGShaderTexEnd; ++i )
		{
			Util::String paramName;
			RenderBase::TextureHandle texHandle;

			gsp->GetTextureParam(static_cast<GlobalTexParamIndex>(i),paramName,texHandle);
			if (paramName == sp.GetName() && texHandle.IsValid())
			{
				GraphicSystem::Instance()->SetTexture(sp.GetRegister(),texHandle);
				return;
			}
		}
	}

	void GraphicRenderer::BeforeRender(const Renderable* renderable, RenderPassType passType, const Material* customizedMat)
	{
		const MaterialInstance* material_instance = renderable->GetMaterial();

		if (passType && material_instance && material_instance->GetTech()->IsTemplateTech())
		{
			const Util::Array< GPtr<MaterialPass> >& passList = material_instance->GetTech()->GetPassList();
			const GPtr<MaterialPass>& pass = passList[passType-1];
			GraphicSystem::Instance()->SetShaderProgram(pass->GetGPUProgramHandle());

			if (s_preShaderInstanceID != material_instance->GetShaderInstanceID())
			{
				const Util::Array< GPtr<MaterialPass> >& passList = material_instance->GetTech()->GetPassList();
				const GPtr<MaterialPass>& pass = passList[passType-1];
				SetMaterialCommonParams(pass);
				s_preShaderInstanceID = material_instance->GetShaderInstanceID();
			}

		}
		else if (customizedMat)
		{
			const GPtr<MaterialPass>& pass = customizedMat->GetTech()->GetDefaultPass();
			GraphicSystem::Instance()->SetShaderProgram(pass->GetGPUProgramHandle());

			if (s_preShaderInstanceID != customizedMat->GetShaderInstanceID())
			{
				const GPtr<MaterialPass>& pass = customizedMat->GetTech()->GetDefaultPass();
				SetMaterialCommonParams(pass);
				s_preShaderInstanceID = customizedMat->GetShaderInstanceID();

				return;
			}
		}
		else if (material_instance)
		{
			const GPtr<MaterialPass>& pass = material_instance->GetTech()->GetDefaultPass();
			GraphicSystem::Instance()->SetShaderProgram(pass->GetGPUProgramHandle());

			if (s_preShaderInstanceID != material_instance->GetShaderInstanceID())
			{
				const GPtr<MaterialPass>& pass = material_instance->GetTech()->GetDefaultPass();
				SetMaterialCommonParams(pass);
				s_preShaderInstanceID = material_instance->GetShaderInstanceID();
			}
		}
	}

	void GraphicRenderer::SetMaterialParams(const MaterialParamList& mpl,const GPtr<MaterialPass>& pass)
	{
#if 1
		ResetCache();
		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();

		const GPtr<ShaderParamBindingMap>& bindings = pass->GetParamBindings();

		// vs 
		{

			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_VS);

			for ( IndexT globalIndex = 0; globalIndex < globalbinds.Size(); ++globalIndex )
			{
				MatParamBinding& global = globalbinds[globalIndex];

				if( global.bindIndex < eGShaderMatEnd )
				{
					const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
					GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(global.Regiter, &m,1);
				}
				else if ( global.bindIndex < eGShaderVecEnd )
				{
					const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
					GraphicSystem::Instance()->SetVertexShaderConstantVectorF(global.Regiter, &vecVal,1);
				}
				else if ( global.bindIndex < eGShaderTexEnd )
				{
					const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
					if ( texHandle.IsValid() )
					{
						GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
					}
				}
			}

			const MatParamBindings& localbinds = bindings->GetLocalBinding(SCT_VS);
			for ( IndexT localIndex = 0; localIndex < localbinds.Size(); ++localIndex )
			{
				MatParamBinding& localbind = localbinds[localIndex];
				SetVSBindingShadersOrTextures( localbind.Regiter, mpl[localbind.bindIndex] );
			}
		}

		// ps
		{

			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_PS);

			for ( IndexT globalIndex = 0; globalIndex < globalbinds.Size(); ++globalIndex )
			{
				MatParamBinding& global = globalbinds[globalIndex];

				if( global.bindIndex < eGShaderMatEnd )
				{
					const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
					GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(global.Regiter, &m,1);
				}
				else if ( global.bindIndex < eGShaderVecEnd )
				{
					const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
					GraphicSystem::Instance()->SetPixelShaderConstantVectorF(global.Regiter, &vecVal,1);
				}
				else if ( global.bindIndex < eGShaderTexEnd )
				{
					const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
					if ( texHandle.IsValid() )
					{
						GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
					}
				}
			}

			const MatParamBindings& localbinds = bindings->GetLocalBinding(SCT_PS);
			for ( IndexT localIndex = 0; localIndex < localbinds.Size(); ++localIndex )
			{
				MatParamBinding& localbind = localbinds[localIndex];
				SetPSBindingShadersOrTextures( localbind.Regiter, mpl[localbind.bindIndex] );
			}
		}




#else	//	bind by string . old and slow
		const GPtr<ShaderParamBindingMap>& bindings = pass->GetParamBindings();

		if(mpl.IsEmpty())
		{
			MaterialParam dummymp;
			FindBindingRegister(&dummymp,bindings->GetShaderParamBindingList() );
		}
		else
		{
			for (SizeT i = 0; i < mpl.Size(); ++i)
			{
				FindBindingRegister(mpl[i],bindings->GetShaderParamBindingList() );
			}
		}
#endif 
	}

	void GraphicRenderer::SetMaterialCommonParams(const GPtr<MaterialPass>& pass)
	{
		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();

		const GPtr<ShaderParamBindingMap>& bindings = pass->GetParamBindings();

		// vs 
		{
			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_VS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_VS);

			for (IndexT index = 0; index < globalInfo.MatCommonEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(global.Regiter, &m,1);
			}
			for (IndexT index = globalInfo.VecCommonBegin; index < globalInfo.VecCommonEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantVectorF(global.Regiter, &vecVal,1);
			}


		}

		// ps
		{
			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_PS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_PS);

			for (IndexT index = 0; index < globalInfo.MatCommonEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(global.Regiter,&m,1);
			}
			for (IndexT index = globalInfo.VecCommonBegin; index < globalInfo.VecCommonEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantVectorF(global.Regiter, &vecVal,1);
			}

		}
	}

	void GraphicRenderer::SetMaterialCustomParams(const Material* material, Graphic::RenderPassType surType)
	{
		const Util::Array< GPtr<MaterialPass> >& passList = material->GetTech()->GetPassList();
		const GPtr<MaterialPass>& pass = passList[surType-1];
		SetMaterialCustomParams(material->GetParamList(), pass);		
		GraphicSystem::Instance()->SetRenderState(pass->GetRenderStateObject());
	}
	void GraphicRenderer::SetMaterialCustomParams(const MaterialParamList& mpl,const GPtr<MaterialPass>& pass)
	{
		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();

		const GPtr<ShaderParamBindingMap>& bindings = pass->GetParamBindings();

		// vs 
		{

			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_VS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_VS);

			for (IndexT index = globalInfo.MatCustomBegin; index < globalInfo.MatCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(global.Regiter, &m,1);
			}
			for (IndexT index = globalInfo.VecCustomBegin; index < globalInfo.VecCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantVectorF(global.Regiter, &vecVal,1);
			}
			for (IndexT index = globalInfo.TexBegin; index < globalbinds.Size(); ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
				if ( texHandle.IsValid() )
				{
					GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
				}
			}


			const MatParamBindings& localbinds = bindings->GetLocalBinding(SCT_VS);
			for ( IndexT localIndex = 0; localIndex < localbinds.Size(); ++localIndex )
			{
				MatParamBinding& localbind = localbinds[localIndex];
				SetVSBindingShadersOrTextures( localbind.Regiter, mpl[localbind.bindIndex] );
			}
		}

		// ps
		{

			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_PS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_PS);

			for (IndexT index = globalInfo.MatCustomBegin; index < globalInfo.MatCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(global.Regiter, &m,1);
			}
			for (IndexT index = globalInfo.VecCustomBegin; index < globalInfo.VecCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantVectorF(global.Regiter, &vecVal,1);
			}
			for (IndexT index = globalInfo.TexBegin; index < globalbinds.Size(); ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
				if ( texHandle.IsValid() )
				{
					GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
				}
			}

			const MatParamBindings& localbinds = bindings->GetLocalBinding(SCT_PS);
			for ( IndexT localIndex = 0; localIndex < localbinds.Size(); ++localIndex )
			{
				MatParamBinding& localbind = localbinds[localIndex];
				SetPSBindingShadersOrTextures( localbind.Regiter, mpl[localbind.bindIndex] );
			}
		}
	}

	void GraphicRenderer::_SetMaterialCustomParamsOfGlobalBuffer(const Material* material, Graphic::RenderPassType surType)
	{

		GlobalMaterialParam* gsp = Material::GetGlobalMaterialParams();
		const Util::Array< GPtr<MaterialPass> >& passList = material->GetTech()->GetPassList();
		const GPtr<MaterialPass>& pass = passList[surType-1];

		const GPtr<ShaderParamBindingMap>& bindings = pass->GetParamBindings();

		// vs
		{
			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_VS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_VS);

			for (IndexT index = globalInfo.MatCustomBegin; index < globalInfo.MatCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(global.Regiter, &m,1);
			}
			for (IndexT index = globalInfo.VecCustomBegin; index < globalInfo.VecCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetVertexShaderConstantVectorF(global.Regiter, &vecVal,1);
			}
			for (IndexT index = globalInfo.TexBegin; index < globalbinds.Size(); ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
				if ( texHandle.IsValid() )
				{
					GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
				}
			}
		}
		// ps
		{

			const MatParamBindings& globalbinds = bindings->GetGlobalBinding(SCT_PS);
			const GlobalBindingInfo& globalInfo = bindings->GetGlobalBindingInfo(SCT_PS);

			for (IndexT index = globalInfo.MatCustomBegin; index < globalInfo.MatCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::matrix44& m = gsp->GetMatrixParam( static_cast<GlobalMatrixParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(global.Regiter, &m,1);
			}
			for (IndexT index = globalInfo.VecCustomBegin; index < globalInfo.VecCustomEnd; ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const Math::float4& vecVal = gsp->GetVectorParam( static_cast<GlobalVectorParamIndex>(global.bindIndex) );
				GraphicSystem::Instance()->SetPixelShaderConstantVectorF(global.Regiter, &vecVal,1);
			}
			for (IndexT index = globalInfo.TexBegin; index < globalbinds.Size(); ++index)
			{
				MatParamBinding& global = globalbinds[index];
				const RenderBase::TextureHandle& texHandle = gsp->GetTextureParam( static_cast<GlobalTexParamIndex>(global.bindIndex) );
				if ( texHandle.IsValid() )
				{
					GraphicSystem::Instance()->SetTexture(global.Regiter,texHandle);
				}
			}
		}
	}


	void GraphicRenderer::RenderForward(Graphic::RenderPassType surType, const Renderable* renderalbe, const RenderBase::PrimitiveHandle& primHandle,
		IndexT firstVertex, SizeT numVertex, IndexT firstIndex, SizeT numIndex, const Material* customed)
	{
		_SetMaterialCustomParams(renderalbe, customed, surType);
		GraphicSystem::Instance()->DrawPrimitive(primHandle,firstVertex,numVertex,firstIndex,numIndex );
	}
	void GraphicRenderer::RenderForward(Graphic::RenderPassType surType, const Renderable* renderalbe, const RenderBase::PrimitiveHandle& primHandle, const Material* customed)
	{
		_SetMaterialCustomParams(renderalbe, customed, surType);
		GraphicSystem::Instance()->DrawPrimitive(primHandle);
	}

	void GraphicRenderer::_SetMaterialCustomParams(const Renderable* renderalbe, const Material* customed, Graphic::RenderPassType surType)
	{
		if (customed)
		{
			SetMaterialCustomParams(customed, surType);
			s_pPreMaterialInstance = 0;
		}
		else if (s_pPreMaterialInstance != renderalbe->GetMaterial())
		{
			SetMaterialCustomParams(renderalbe->GetMaterial(), surType);
			s_pPreMaterialInstance = renderalbe->GetMaterial();
		}
		else
		{
			_SetMaterialCustomParamsOfGlobalBuffer(renderalbe->GetMaterial(), surType);
		}
	}


	void GraphicRenderer::FindBindingRegister(MaterialParam* mpl, const ShaderParamBindingList& binding)
	{
		// vs
		{
			const ShaderParamList& spl = binding[SCT_VS];
			for (SizeT i = 0; i < spl.Size(); ++i)
			{
				if( spl[i].GetName() == mpl->GetName() )
				{
					SetVSBindingShadersOrTextures(spl[i].GetRegister(),mpl);
				}
				else
				{
					SetGlobalVertexShaderConstant(spl[i]);
				}
			}
		}

		// ps
		{
			const ShaderParamList& spl = binding[SCT_PS];
			for (SizeT i = 0; i < spl.Size(); ++i)
			{
				if( spl[i].GetName() == mpl->GetName() )
				{
					SetPSBindingShadersOrTextures(spl[i].GetRegister(),mpl);
				}
				else
				{
					SetGlobalPixelShaderConstant(spl[i]);
				}
			}
		}

	}

	void GraphicRenderer::SetVSBindingShadersOrTextures(int reg,MaterialParam* mpl)
	{
		switch (mpl->GetType())
		{
		case eShaderParamMatrix :
			GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(reg,&(static_cast<MaterialParamMatrix*>(mpl)->GetValue()),1);
			break;
		case eShaderParamVector :
			GraphicSystem::Instance()->SetVertexShaderConstantVectorF(reg,&(static_cast<MaterialParamVector*>(mpl)->GetValue()),1);
			break;
		case eShaderParamFloat :
			GraphicSystem::Instance()->SetVertexShaderConstantFloat(reg,(static_cast<MaterialParamFloat*>(mpl)->GetValue()));
			break;
		case eShaderParamTexture1D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex1D*>(mpl)->GetHandle());
			break;
		case eShaderParamTexture2D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex2D*>(mpl)->GetHandle());
			break;
		case eShaderParamTexture3D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex3D*>(mpl)->GetHandle());
			break;
		case eShaderParamTextureCUBE :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTexCube*>(mpl)->GetHandle());
			break;
		default:
			n_error("no matching shader param type found!\n");
		}

	}

	void GraphicRenderer::SetPSBindingShadersOrTextures(int reg,MaterialParam* mpl)
	{
		switch (mpl->GetType())
		{
		case eShaderParamFloat :
			GraphicSystem::Instance()->SetPixelShaderConstantFloat(reg,(static_cast<MaterialParamFloat*>(mpl)->GetValue()));
			break;
		case eShaderParamVector :	
			GraphicSystem::Instance()->SetPixelShaderConstantVectorF(reg,&(static_cast<MaterialParamVector*>(mpl)->GetValue()),1);
			break;
		case eShaderParamMatrix :
			GraphicSystem::Instance()->SetPixelShaderConstantMatrixF(reg,&(static_cast<MaterialParamMatrix*>(mpl)->GetValue()),1);
			break;
		case eShaderParamTexture1D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex1D*>(mpl)->GetHandle());
			break;
		case eShaderParamTexture2D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex2D*>(mpl)->GetHandle());
			break;
		case eShaderParamTexture3D :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTex3D*>(mpl)->GetHandle());
			break;
		case eShaderParamTextureCUBE :
			GraphicSystem::Instance()->SetTexture(reg,static_cast<MaterialParamTexCube*>(mpl)->GetHandle());
			break;
		default:
			n_error("no matching type found!\n");
		}

	}

}
