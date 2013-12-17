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
#include "meshrenderobject.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicsystem/Camera/RenderPipeline/RenderData.h"
#include "appframework/actor.h"

namespace App
{
	using namespace  Graphic;
	__ImplementClass(MeshRenderObject,'MROB',AppRenderObject)

	MeshRenderObject::MeshRenderObject()
	{

	}
	MeshRenderObject::~MeshRenderObject()
	{

	}

	void MeshRenderObject::Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial)
	{
		n_assert(NULL != renderable);
		n_assert(mOwner);

		const Graphic::Material* material = (NULL == customizedMaterial) ? renderable->GetMaterial() : customizedMaterial;
		const RenderableType* rd = renderable->cast_fast<RenderableType>();
		const RenderBase::PrimitiveHandle& priHandle = getOwner()->GetPrimitiveHandle();
		if (priHandle.IsValid())//( (customizedMat.isvalid() || mat.isvalid()) && priHandle.IsValid() )
		{
			GlobalMaterialParam* pGMP = Graphic::Material::GetGlobalMaterialParams();

			pGMP->SetMatrixParam(eGShaderMatM,GetTransform());

			{//判断是否需要设置逆矩阵
				//const Material* material = eCustomized == passType ? customizedMaterial : renderable->GetMaterial();
				//int passindex = eCustomized == passType ? eForward - 1 : passType -1;
				int passindex = (eCustomized == passType) ? 0 : passType -1;
				const Util::Array< GPtr<MaterialPass> >& passList = material->GetTech()->GetPassList();
				if(passindex >= passList.Size())			//我们现在不支持深度Pass，按照温洋的建议，先return掉，以后支持后，这块再改掉。
					return;
				const GPtr<MaterialPass>& pass = passList[passindex];
				if ( pass->isGlobalParamUsed( eGShaderMatInverseM )//如果没有使用这几个全局的矩阵参数，就不求逆矩阵了，提高效率
					|| pass->isGlobalParamUsed( eGShaderMatInverseTransposeM ) )
				{
					Math::matrix44 Inverse, InvTranspose;
					Inverse      = Math::matrix44::inverse(GetTransform());
					InvTranspose = Math::matrix44::transpose(Inverse);

					pGMP->SetMatrixParam(eGShaderMatInverseM,Inverse);
					pGMP->SetMatrixParam(eGShaderMatInverseTransposeM,InvTranspose);
				}
			}

			if ( IsUseLM() && IsLMHandleValid() )
			{
				// lightmap support
				const Math::float4 lmTexParam = getOwner()->GetLMTexParam();
				RenderBase::TextureHandle lmHandle = getOwner()->GetLMTextureHandle();
				// set lightmap params
				pGMP->SetVectorParam(eGShaderMatLMEnable, float4(1.0f,1.0f,1.0f,1.0f));
				pGMP->SetVectorParam(eGShaderMatLMTexParam, lmTexParam);
				pGMP->SetTextureParam(eGShaderTexLightmap, lmHandle);
			}
			else
			{
				pGMP->SetVectorParam(eGShaderMatLMEnable, float4(0.0f,0.0f,0.0f,0.0f));
				pGMP->SetVectorParam(eGShaderMatLMTexParam, float4(1.0f,1.0f,0.0f,0.0f));
			}

			bool isReceiveShadow = this->GetReceiveShadow();
			pGMP->SetVectorParam(eGShaderMatShadowReceive, float4(isReceiveShadow,0.0f,0.0f,0.0f));

			//render passType
			if (passType && material->GetTech()->IsTemplateTech())
			{
				rd->RenderForward(passType, priHandle, customizedMaterial);
			}
			else
			{
				rd->RenderForward(eForward, priHandle, customizedMaterial);
			}

			// reset lightmap params
			pGMP->SetVectorParam(eGShaderMatLMEnable, float4(0.0f,0.0f,0.0f,0.0f));
		}
	}

	const Util::StringAtom& MeshRenderObject::GetMeshName() const
	{
		return getOwner()->GetMeshID();
	}

	inline bool MeshRenderObject::IsUseLM() const
	{
		return getOwner()->IsUseLM();
	}

	inline bool MeshRenderObject::IsLightmapHandleValid() const
	{
		RenderBase::TextureHandle lightmapHandle = getOwner()->GetLMTextureHandle();
		return lightmapHandle.IsValid();
	}
}