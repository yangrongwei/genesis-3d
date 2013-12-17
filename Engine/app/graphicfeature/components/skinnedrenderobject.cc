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
#include "skinnedrenderobject.h"
#include "skinnedmeshrendercomponent.h"
#include "graphicsystem/GraphicSystem.h"
#include "foundation/math/matrix44.h"

namespace App
{
	using namespace  Graphic;
	__ImplementClass(SkinnedRenderObject,'SROB',MeshRenderObject)

		SkinnedRenderObject::SkinnedRenderObject()
	{

	}

	SkinnedRenderObject::~SkinnedRenderObject()
	{

	}

	void SkinnedRenderObject::AddToCollection(Graphic::RenderDataCollection* collection)
	{
		getOwner()->_NeedUpdate();
		Super::AddToCollection(collection);
	}

	void SkinnedRenderObject::Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial)
	{
		n_assert(renderable);
		const RenderableType* srl= renderable->cast_fast<RenderableType>();

		if (srl->UseDrawMats()) 
		{
			if ( !srl->GetDrawMats())
				return;

			DrawMatrices::Iterator it = srl->GetDrawMats()->Begin();
			DrawMatrices::Iterator end = srl->GetDrawMats()->End();
			for ( ; it !=  end; it++ )
			{
				render(srl, passType, customizedMaterial, *it );
			}
		}
		else
		{
			render(srl, passType, customizedMaterial, GetTransform());
		}
	}

	void SkinnedRenderObject::render(const RenderableType* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMat, const Math::matrix44& _matrix)
	{

		SkinnedMeshRenderComponent* skinnedMeshRC = getOwner();
		const RenderBase::PrimitiveHandle& priHandle = skinnedMeshRC->GetPrimitiveHandle();

		if (priHandle.IsValid())
		{
			//Hardware Skinning, set the final transform
			if( renderable->HasUseHWSkinning() && passType !=  Graphic::eCustomized)
			{
				const AffectedTransform& tranforms = renderable->GetAffectedTransform();
				int regIndex = renderable->GetRegIndexOfAffected(passType - 1);
				if(regIndex != InvalidIndex)
				{
					GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(regIndex, tranforms.Begin(), tranforms.Size());		
				}
			}
			Super::Render(renderable, passType, customizedMat);

		}
	}

}