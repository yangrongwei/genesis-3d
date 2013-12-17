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
#include "VegetationRenderObject.h"
#include "vegetation/VegetationObejct.h"
#include "graphicsystem/Camera/RenderPipeline/RenderData.h"
#include "graphicsystem/Material/Material.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
namespace Vegetation
{
	__ImplementClass(VegetationRenderObject,'VROB',Graphic::RenderObject)

		using namespace Graphic;
	VegetationRenderObject::VegetationRenderObject()
	{

	}
	VegetationRenderObject::~VegetationRenderObject()
	{

	}
	void VegetationRenderObject::AddToCollection(Graphic::RenderDataCollection* colection)
	{
		const Graphic::RenderableResUnitArray& list = mOwner->GetResUnits();
		Graphic::RenderableResUnitArray::Iterator begin = list.Begin();
		Graphic::RenderableResUnitArray::Iterator end = list.End();
		while(begin != end)
		{
			if (begin->Complete())
			{
				colection->Push(begin->GetRenderable());
			}
			++begin;
		}
	}

	void VegetationRenderObject::Render(const Renderable* renderable, RenderPassType passType, const Material* customizedMaterial)
	{
		n_assert(renderable);
		const RenderableType* grassRenderable = renderable->cast_fast<const RenderableType>();
		switch(mOwner->GetRenderType())
		{
		case eRT_Grass:
			_RenderGrass(grassRenderable, passType, customizedMaterial);
			break;
		case eRT_DetailMesh:
		case eRT_Tree:
			_RenderTree(grassRenderable, passType, customizedMaterial);
			break;
		default:
			break;
		}	
	}
	//--------------------------------------------------------------------------------
	void VegetationRenderObject::_RenderTree(const RenderableType* renderable, RenderPassType passType, const Material* customizedMaterial)
	{
		// TODO : if renderable submesh is 0, render the bole, 1 is leaves pieces

		if (mOwner->GetPrimHandle().IsValid())
		{
			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

			//TODO:: 			
			//camera cull
			const Math::matrix44* camera = &(Graphic::GraphicSystem::Instance()->GetRenderingCamera()->GetTransform());		
			GPtr<Vegetation::VegeInstanceMap> pInstMap = mOwner->GetInstanceMap();
			if ( !pInstMap.isvalid())
				return;

			Math::vector objscale =  mOwner->GetScale();
			Math::quaternion objrot =  mOwner->GetRotation();

			Math::scalar fCullDistance = mOwner->GetCullDistance();

			SizeT nInstCount = pInstMap->GetInstanceCount();
			for (SizeT i = 0; i	< nInstCount; ++i)
			{
				INSTANCEDATA_POS* tmpInst = pInstMap->GetInstance(i);

				Math::float4 _pos(tmpInst->pos.x(),tmpInst->pos.y(), tmpInst->pos.z(), 1);

				Math::float4 fDistance = camera->get_position() - _pos;

				// while in the visual range , draw a single Tree 
				if ( fDistance.length() < fCullDistance )
				{				

					Math::quaternion _quat = Math::quaternion::rotationyawpitchroll( tmpInst->rotate.y() * N_PI / 180 , tmpInst->rotate.x()* N_PI / 180, tmpInst->rotate.z()* N_PI / 180);
					_quat = Math::quaternion::multiply(_quat,objrot);
					Math::float4 _scale = Math::float4(tmpInst->scale.x() * objscale.x(), tmpInst->scale.y()* objscale.y(), tmpInst->scale.z()* objscale.z(), 0);
					Math::matrix44 _mat = Math::matrix44::transformation( _scale, _quat, _pos );


					Math::float4 tempRegst = Math::float4(tmpInst->color, tmpInst->wave, 0, 0);
					int startIndex = 13;
					GraphicSystem::Instance()->SetVertexShaderConstantVectorF(startIndex, &tempRegst, 1);

					pGMP->SetMatrixParam(eGShaderMatM, _mat);

					Math::matrix44 Inverse, InvTranspose;
					Inverse      = Math::matrix44::inverse(_mat);
					InvTranspose = Math::matrix44::transpose(Inverse);

					pGMP->SetMatrixParam(eGShaderMatInverseM,Inverse);
					pGMP->SetMatrixParam(eGShaderMatInverseTransposeM,InvTranspose);

					_Render(renderable, passType,//mat, passType, 
						mOwner->GetPrimHandle(),	
						renderable->GetFirstVertix(),
						renderable->GetNumVertex(),
						renderable->GetFirstIndex(),
						renderable->GetNumIndex(),
						customizedMaterial);						
				}
			}	
		}
	}

	//--------------------------------------------------------------------------------
	void VegetationRenderObject::_RenderGrass(const RenderableType* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial)
	{		

		if (mOwner->GetPrimHandle().IsValid())
		{
			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();

			//TODO:: 			
			//camera cull
			const Camera* renderingCamera = Graphic::GraphicSystem::Instance()->GetRenderingCamera();
			const Math::matrix44* camera = &(renderingCamera->GetTransform());	
			Math::vector objscale =  mOwner->GetScale();
			Math::quaternion objrot =  mOwner->GetRotation();

			GPtr<Vegetation::VegeInstanceMap>& pInstMap = mOwner->GetInstanceMap();

			if ( !pInstMap.isvalid())
				return;

			Math::scalar fCullDistance = mOwner->GetCullDistance();

			if ( pInstMap->IsHWInstancing() )
			{
				n_assert(0);

				return;
			}	
			else
			{
				SizeT nTotalCount = pInstMap->GetInstanceCount();
				SizeT nVisualIndex = 0;	
				Util::Array<Math::matrix44> grassMatArray;

				for (SizeT i = 0; i < nTotalCount; ++i)
				{

					INSTANCEDATA_POS* tmpInst = pInstMap->GetInstance(i);

					Math::float4 _pos(tmpInst->pos.x(), tmpInst->pos.y(), tmpInst->pos.z(),1);	

					Math::float4 fDistance = camera->get_position() - _pos;
					//max value 1000f, should be set outside
					if ( fDistance.length() < fCullDistance )
					{
						Math::quaternion _quat = Math::quaternion::rotationyawpitchroll( tmpInst->rotate.y()* N_PI / 180 , tmpInst->rotate.x()* N_PI / 180, tmpInst->rotate.z()* N_PI / 180);
						Math::float4 _scale = Math::float4(tmpInst->scale.x() , tmpInst->scale.y() , tmpInst->scale.z() , 0);
						Math::matrix44 _mat = Math::matrix44::transformation( _scale, _quat, _pos );

						if (customizedMaterial)
						{
							//TODO:  while WireFrame mode : need to calculate the Matrix at here ,because the shader will has not the calculation step
							pGMP->SetMatrixParam(eGShaderMatM, _mat);

							_Render(renderable, passType,
								mOwner->GetPrimHandle(),			
								renderable->GetFirstVertix(),
								renderable->GetNumVertex(),
								renderable->GetFirstIndex(),
								renderable->GetNumIndex(),
								customizedMaterial);
						}
						else
						{
							float4 tfloat4 = _mat.getrow3();
							tfloat4.x() = tmpInst->color;
							tfloat4.y() = tmpInst->wave; 
							tfloat4.z() = _scale.y(); 
							_mat.setrow3(tfloat4);
							grassMatArray.Append(_mat);
						}
						++nVisualIndex;
					}					

				}

				if (customizedMaterial)
					return;

				bool meshRT = (eRT_DetailMesh == mOwner->GetRenderType());
				SizeT vertLimitCount = pInstMap->GetVertLimitCount();
				SizeT nremainingInst = nVisualIndex;				
				while ( nremainingInst > 0 )
				{
					SizeT nRenderIndicesCount =  Math::n_min(nremainingInst, g_nNumBatchInstance);
					if (meshRT)
						nRenderIndicesCount = Math::n_min(nRenderIndicesCount, vertLimitCount);


					SizeT nRenderVertInst =  Math::n_min(nremainingInst, vertLimitCount);
					nRenderVertInst =  Math::n_min(nRenderVertInst, nRenderIndicesCount);

					SizeT nbegin = nVisualIndex - nremainingInst;

					//TODO : DrawPrimitive
					if ( grassMatArray.Size() > 0 )
					{
						int startIndex = 0;
						if (meshRT)
							startIndex = 12;			
						else
							startIndex = 12;
						GraphicSystem::Instance()->SetVertexShaderConstantMatrixF(startIndex, &grassMatArray[nbegin], nRenderIndicesCount);	
					}			
					pGMP->SetMatrixParam(eGShaderMatM, matrix44::identity());

					_Render(renderable, passType,//mat, passType, 
						mOwner->GetPrimHandle(),			
						renderable->GetFirstVertix(),
						nRenderVertInst * renderable->GetNumVertex(),
						nbegin * renderable->GetNumIndex(),
						nRenderIndicesCount * renderable->GetNumIndex(),
						customizedMaterial);
					nremainingInst -= nRenderIndicesCount;
				}

			}		
		}

	}

	//--------------------------------------------------------------------------------
	void VegetationRenderObject::_Render(const RenderableType* renderable, Graphic::RenderPassType passType, const RenderBase::PrimitiveHandle& handle, 
		IndexT firstVert, SizeT numVert, IndexT firstIndex, SizeT numIndex, const Graphic::Material* customizedMaterial)
	{
		const Graphic::Material* material = (NULL == customizedMaterial) ? renderable->GetMaterial() : customizedMaterial;
		if (passType && material->GetTech()->IsTemplateTech())
		{

			GraphicRenderer::RenderForward(passType, renderable, handle, firstVert, numVert, firstIndex, numIndex, customizedMaterial);
		}
		else
		{
			GraphicRenderer::RenderForward(eForward, renderable, handle, firstVert, numVert, firstIndex, numIndex, customizedMaterial);
		}
	}
}