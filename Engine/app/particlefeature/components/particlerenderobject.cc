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
#include "particlefeature/components/particlerenderobject.h"
#include "particlefeature/components/particlerendercomponent.h"
#include "addons/particles/particletarget.h"
namespace App
{
	using namespace Graphic;
	using namespace Particles;
	__ImplementClass(ParticleRenderObject,'PROB',AppRenderObject)

		ParticleRenderObject::ParticleRenderObject()
	{

	}
	ParticleRenderObject::~ParticleRenderObject()
	{

	}
	void ParticleRenderObject::AddToCollection( Graphic::RenderDataCollection* collection )
	{
		getOwner()->NeedUpdate();
		Super::AddToCollection(collection);
	}
	void ParticleRenderObject::Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial)
	{
		n_assert(renderable);
		const RenderableType* particlerenderable = renderable->cast_fast<RenderableType>();		

		ParticleRenderComponent* particleRC = getOwner();
		n_assert( particleRC );

		bool bSetTrans = particleRC->IsSetTransParam();

		const Graphic::Material* material = (NULL == customizedMaterial) ? renderable->GetMaterial() : customizedMaterial;

		const ParticleRenderComponent::RenderData* renderData = particleRC->GetRenderData( particlerenderable->GetResourceIndex() );



		if (renderData && renderData->mPrimitiveHandle.IsValid() )
		{

			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

			Util::Array<Math::matrix44> getMats;
			Util::Array<Math::float4> getColors;
			ushort mParType;
			Math::matrix44 gModleMaterix;

			gModleMaterix = Math::matrix44::identity();

			if (renderData->mPartType == ParticleTarget::Mesh
				|| renderData->mPartType == ParticleTarget::Decal)
			{
				particleRC->GetTargetInfo( mParType, getMats, getColors);
				if (getMats.Size() > 0)
				{
					gModleMaterix = getMats[0];
				}
			}

			if ( renderData->mPartType == ParticleTarget::Mesh )
			{
				SizeT curcycle = 0;
				SizeT possize = getMats.Size();
				while ( curcycle < possize )
				{	
					gModleMaterix = getMats[curcycle];
					pGMP->SetMatrixParam(eGShaderMatM, gModleMaterix);

					pGMP->SetVectorParam(eGShaderParticleMeshColor,getColors[curcycle]);

					if (passType && material->GetTech()->IsTemplateTech())
					{
						particlerenderable->RenderForward(passType, renderData->mPrimitiveHandle, customizedMaterial);

					}
					else
					{
						particlerenderable->RenderForward(eForward, renderData->mPrimitiveHandle, customizedMaterial);			
					}

					curcycle++;
				}
			}
			else
			{
				pGMP->SetMatrixParam(eGShaderMatM,gModleMaterix);
				pGMP->SetVectorParam(eGShaderParticleMeshColor,Math::float4(1.0f,1.0f,1.0f,1.0f));

				if (passType && material->GetTech()->IsTemplateTech())
				{
					particlerenderable->RenderForward(passType, renderData->mPrimitiveHandle, customizedMaterial);
				}
				else
				{
					particlerenderable->RenderForward(eForward, renderData->mPrimitiveHandle, customizedMaterial);	

				}
			}
		}
	}
}