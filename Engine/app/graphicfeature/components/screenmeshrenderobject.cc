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
#include "screenmeshrenderobject.h"
#include "graphicfeature/components/mesh2drendercomponent.h"
#include "graphicsystem/Material/Material.h"
namespace App
{
	using namespace Graphic;
	__ImplementClass(ScreenMeshRenderObject,'SMOB',AppRenderObject)
	ScreenMeshRenderObject::ScreenMeshRenderObject()
		:mObjIndex(-1)
	{
		SetLayerID(0);
	}
	ScreenMeshRenderObject::~ScreenMeshRenderObject()
	{

	}
	void ScreenMeshRenderObject::Render(const Renderable* renderable, RenderPassType passType, const Material* customizedMaterial)
	{
		n_assert(renderable);

		Mesh2dRenderComponent* mesh2dRC = getOwner();
		n_assert( mesh2dRC );

		if (!mesh2dRC->IsAllTexLoaded())
		{
			return;
		}
		const RenderableType* rd = renderable->cast_fast<RenderableType>();
		const RenderBase::PrimitiveHandle& priHandle = mesh2dRC->GetPrimive();
		if ( passType && priHandle.IsValid() )
		{
			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

			pGMP->SetMatrixParam(eGShaderMatM, GetTransform());//Math::matrix44::identity());//

			Math::matrix44 Inverse, InvTranspose;
			Inverse      = Math::matrix44::inverse(GetTransform());
			InvTranspose = Math::matrix44::transpose(Inverse);
			pGMP->SetMatrixParam(eGShaderMatInverseTransposeM,InvTranspose);
			rd->RenderForward(passType, priHandle, customizedMaterial);
		}
	}
}