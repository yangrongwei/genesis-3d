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
#include "vegetation/TreeInstanceMap.h"
#include "vegetation/VegetationObejct.h"

namespace Vegetation
{	

	using namespace RenderBase;
	using namespace Math;

	__ImplementClass( Vegetation::TreeInstanceMap, 'VTIM', Vegetation::VegeInstanceMap);


	TreeInstanceMap::TreeInstanceMap():VegeInstanceMap()
	{		
		//m_Name = Util::String("TreeInstanceMap");
	}

	//------------------------------------------------------------------------
	TreeInstanceMap::~TreeInstanceMap()
	{

	}
	//------------------------------------------------------------------------
	bool TreeInstanceMap::BuildPrimitive()
	{
		if ( !mVegeObject)
			return false;	

		const Resources::PrimitiveResInfo* pMeshInfo = mVegeObject->GetMeshInfo();
		if ( !pMeshInfo->GetRes())
			return false;

		const GPtr<Resources::MeshRes>& pMesh = pMeshInfo->GetRes().downcast<Resources::MeshRes>();
		// must has vertex and index
		if ( pMesh->GetIndexCount() == 0 
			|| pMesh->GetVertexCount() == 0 
			|| pMesh->GetTopologyType() == RenderBase::PrimitiveTopology::InvalidPrimitiveTopology )
		{
			return false;
		}

		//MeshInstance can only have m_nVertLimitCount = 1 and m_nInstUsingCount = 1
		m_bHWInstancing = false;
		m_nInstUsingCount = 1;
		m_nVertLimitCount = 1;

		RenderBase::PrimitiveHandle handle =  App::GraphicObjectManager::Instance()->CreatePrimitiveHandle(pMesh);

		RenderBase::PrimitiveHandle& old = mVegeObject->GetPrimHandle();
		if (old.IsValid())
		{
			App::GraphicObjectManager::Instance()->DiscardPrimitiveHandle(old);//Graphic::GraphicSystem::Instance()->RemovePrimitive(old);
		}
		mVegeObject->SetPrimHandle(handle);

		SetDirty(false);
		return true;
	}

	//------------------------------------------------------------------------
	void TreeInstanceMap::_GenerateVertex(const GPtr<Resources::MeshRes>& pMesh, VEGE_VERTEX_INSTANCE* vertext, ushort* indices,  const INSTANCEDATA_POS& InstPos, IndexT instIndex)
	{
		n_assert( pMesh.isvalid() );
		for ( IndexT index = 0; index < m_vVerDeclare.Size(); ++index )
		{
			_CopyVBOComponent(pMesh, m_vVerDeclare[index], (uchar*)vertext, sizeof(VEGE_VERTEX_INSTANCE), pMesh->GetVertexCount());
		}
	}
	//------------------------------------------------------------------------
	uchar* TreeInstanceMap::_CopyVBOData(const GPtr<MeshRes> &pMesh, const Util::Array<VertexComponent> &verDeclare, SizeT &vertexDataSize)
	{
		n_assert( pMesh.isvalid() );
		n_assert( !verDeclare.IsEmpty() );
		SizeT numVertices = pMesh->GetVertexCount();
		n_assert( numVertices > 0 );

		SizeT VertexSize = 0;
		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			VertexSize += verDeclare[index].GetByteSize();
		}
		n_assert( VertexSize > 0 );

		vertexDataSize = VertexSize * numVertices ;

		uchar* vertexDataPtr = n_new_array(uchar,vertexDataSize);
		n_assert( vertexDataPtr );

		uchar* vetTemp = vertexDataPtr;

		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			_CopyVBOComponent(pMesh, verDeclare[index], vetTemp, VertexSize, numVertices);

		}		

		return vertexDataPtr;
	}
	//------------------------------------------------------------------------
	void TreeInstanceMap::_CopyVBOComponent(const GPtr<MeshRes> &pMesh, const VertexComponent &vcdef, uchar *vertexDataPtr, SizeT VertexSize, SizeT numVertices)
	{
		switch( vcdef.GetSemanticName() )
		{
		case VertexComponent::Position:
			{
				PositionData::Elem* elem = pMesh->GetVertexData<PositionData>();
				n_assert( vcdef.GetByteSize() == 12 );
				StripeCopy<PositionData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

			}
			break;
		case VertexComponent::Normal:
			{
				NormalData::Elem* elem = pMesh->GetVertexData<NormalData>();
				n_assert( vcdef.GetByteSize() == 12 );
				StripeCopy<NormalData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

			}
			break;
		case VertexComponent::Tangent:
			{
				TangentData::Elem* elem = pMesh->GetVertexData<TangentData>();
				n_assert( vcdef.GetByteSize() == 16 );
				StripeCopy<TangentData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Binormal:
			{
				BiNormalData::Elem* elem = pMesh->GetVertexData<BiNormalData>();
				n_assert( vcdef.GetByteSize() == 16 );
				StripeCopy<BiNormalData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::TexCoord:
			{
				if ( vcdef.GetSemanticIndex() == 1 )
				{
					//Temporary Code
					//Math::scalar fBatch = 0.f;
					Math::float2 IndexWave(0.f, Math::n_rand(0.5,1.0f));
					StripeCopyValue<Math::float2,sizeof(Math::float2)>(&IndexWave, vertexDataPtr, VertexSize,vcdef.GetByteOffset(), numVertices );

				}
				else
				{
					TexCoordData::Elem* elem = pMesh->GetVertexData<TexCoordData>( vcdef.GetSemanticIndex() );
					n_assert( vcdef.GetByteSize() == 8 );
					StripeCopy<TexCoordData::Elem,8>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

				}
			}
			break;
		case VertexComponent::Color:
			{
				ColorData::Elem* elem = pMesh->GetVertexData<ColorData>( vcdef.GetSemanticIndex() );

				n_assert( vcdef.GetByteSize() == 4 );
				if ( vcdef.GetFormat() == VertexComponent::ColorRGBA )
				{
					StripeCopy<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				}
				else if(  vcdef.GetFormat() == VertexComponent::ColorBGRA )
				{
					StripeSwapCopyColor<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
					//StripeCopy<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				}
				else
				{
					n_assert(" GraphicObjectManager|copyVBOComponent: unknown color format" );
				}

			}
			break;
		case VertexComponent::SkinJIndices:
			{
				BoneInfoData::Elem* elem = pMesh->GetVertexData<BoneInfoData>( vcdef.GetSemanticIndex() );

				n_assert( vcdef.GetByteSize() == 8 );
				StripeCopy<BoneInfoData::Elem,24>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );

				//m_BoneInfoIndex = vcdef.GetSemanticIndex();
			}
			break;
		case VertexComponent::SkinWeights:
			{
				n_assert( vcdef.GetByteSize() == 16 );
			}
			break;
		default:
			n_error("GraphicObjectManager|copyVBOComponent: invalid VertexComponent::SemanticName/n");
		}
		return;
	}
	//------------------------------------------------------------------------
	void TreeInstanceMap::Update()
	{
		if ( !mVegeObject || mInstances.IsEmpty())
			return;	


		if ( m_bInstDirty )
		{
			BuildPrimitive();	
		}	
	}	
}
