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
#include "graphicsystem/GraphicSystem.h"
#include "sprite/spriteimage.h"
#include "graphicfeature/components/spritebaserendercomponent.h"
#include "graphicsystem/Camera/RenderPipeline/RenderData.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "spriterenderobject.h"

namespace App
{
	//static const ShaderParamString& gDiffuseParam = "_diffuseMap";
	using namespace  Graphic;


	SpriteRenderable::SpriteRenderable()
	{
	}

	SpriteRenderable::~SpriteRenderable()
	{
	}

	void SpriteRenderable::RenderForward(Graphic::RenderPassType surType, const RenderBase::PrimitiveHandle& primHandle, const Graphic::Material* custom) const
	{
		mImage->PushTexture();
		Graphic::GraphicRenderer::ResetMaterialCache();
		Graphic::GraphicRenderer::RenderForward(surType, this, primHandle, custom);
	}


	__ImplementClass(SpriteRenderObject,'SPRO',AppRenderObject);

	SpriteRenderObject::SpriteRenderObject()
	{

	}
	SpriteRenderObject::~SpriteRenderObject()
	{

	}

	void SpriteRenderObject::Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial)
	{
		const Graphic::Material* material = (NULL == customizedMaterial) ? renderable->GetMaterial() : customizedMaterial;
		const RenderableType* rd = renderable->cast_fast<RenderableType>();

		const RenderBase::PrimitiveHandle& priHandle = getOwner()->_getHandle();
		if (priHandle.IsValid())//( (customizedMat.isvalid() || mat.isvalid()) && priHandle.IsValid() )
		{
			GlobalMaterialParam* pGMP = Graphic::Material::GetGlobalMaterialParams();

			pGMP->SetMatrixParam(eGShaderMatM,GetTransform());

			Math::matrix44 Inverse, InvTranspose;
			Inverse      = Math::matrix44::inverse(GetTransform());
			InvTranspose = Math::matrix44::transpose(Inverse);

			pGMP->SetMatrixParam(eGShaderMatInverseM,Inverse);
			pGMP->SetMatrixParam(eGShaderMatInverseTransposeM,InvTranspose);

			//render passType
			if (passType && material->GetTech()->IsTemplateTech())
			{
				rd->RenderForward(passType, priHandle, customizedMaterial);
			}
			else
			{
				rd->RenderForward(eForward, priHandle, customizedMaterial);
			}
		}

	}
}