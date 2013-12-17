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
#include "vegetation/GrassInstanceMap.h"
#include "vegetation/VegetationObejct.h"

namespace Vegetation
{	

	using namespace RenderBase;
	using namespace Math;

	__ImplementClass( Vegetation::GrassInstanceMap, 'VGIM', Vegetation::VegeInstanceMap);

	GrassInstanceMap::GrassInstanceMap():VegeInstanceMap()
	{		
		mRenderMode = eBillboard;
		//m_Name = Util::String("GrassInstanceMap");
	}

	//------------------------------------------------------------------------
	GrassInstanceMap::~GrassInstanceMap()
	{

	}
	//------------------------------------------------------------------------
	bool GrassInstanceMap::BuildPrimitive()
	{

		//if use shaderInstancing


		if (m_bHWInstancing)
		{
			m_nInstUsingCount = 1;
			m_nVertLimitCount = 1;
		}
		else
		{
			m_nInstUsingCount = mInstances.Size();

			if ( m_nInstUsingCount > g_nNumBatchInstance)
			{
				m_nVertLimitCount = g_nNumBatchInstance;
			}
			else
				m_nVertLimitCount = m_nInstUsingCount;
		}

		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		RenderBase::VertexComponents& vertexComponents = vbd2.GetVertexComponents();
		BuildVertexComponents(GPtr<Resources::MeshRes>());
		vertexComponents = m_vVerDeclare;

		// copy vbo & ibo

		SizeT numVertex = g_VertexCount * m_nVertLimitCount;
		SizeT numIndex = m_nInstUsingCount * g_IndexCount;
		SizeT indexSizeInByte = numIndex * RenderBase::IndexBufferData::SizeOf(RenderBase::IndexBufferData::Int16);
		vbd2.Setup(numVertex, sizeof(VEGE_VERTEX_INSTANCE), RenderBase::BufferData::Static, RenderBase::PrimitiveTopology::TriangleList, true);
		ibd2.Setup(numIndex, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
		mVegeObject->GetVertices().Resize(numVertex);
		mVegeObject->GetIndices().Resize(indexSizeInByte);

		ushort* indices =  (ushort*)&(mVegeObject->GetIndices()[0]);

		VEGE_VERTEX_INSTANCE* instanceVertex = &(mVegeObject->GetVertices()[0]);

		for (SizeT si = 0; si < m_nInstUsingCount; ++si)
		{
			//TODO : Transform vertex wave
			if ( si < g_nNumBatchInstance )
			{
				_GenerateVertex(instanceVertex, si);
				_GenerateIndices(indices, si);
				instanceVertex += g_VertexCount;
				indices += g_IndexCount;
			}
			else
			{
				SizeT curIndex =  si % g_nNumBatchInstance;
				_GenerateIndices(indices, curIndex);
				indices += g_IndexCount;
			}
			//_GenerateIndices(indices, curIndex);

		}

		vbd2.SetVertices(&mVegeObject->GetVertices()[0], numVertex);
		ibd2.SetIndices(&mVegeObject->GetIndices()[0], numIndex);
		RenderBase::PrimitiveHandle handle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);

		RenderBase::PrimitiveHandle& old = mVegeObject->GetPrimHandle();
		if (old.IsValid())
		{
			Graphic::GraphicSystem::Instance()->RemovePrimitive(old);
		}
		mVegeObject->SetPrimHandle(handle);

		SetDirty(false);
		return true;
	}
	//------------------------------------------------------------------------
	void GrassInstanceMap::_GenerateVertex(VEGE_VERTEX_INSTANCE* vertext, IndexT instIndex)
	{
		float u0 = 0.0f;
		float u1 = 1.0f;
		float v0 = 0.0f;
		float v1 = 1.0f;
		Math::Color32 defClr(255,255,255,255);

		Math::scalar fIndex =  (Math::scalar)instIndex;
		Math::scalar fWave = Math::n_rand(0.5f, 1.0f);
		vertext[0].pos = Math::float3(-1.0f , 2.0f, 0)/* * mInstances[instIndex].scale*/;
		vertext[0].color.Set(defClr);
		vertext[0].uv.set( u0, v0 );
		vertext[0].index = Math::float2(fIndex, fWave);

		vertext[1].pos = Math::float3(-1.0f , 0.0f, 0);
		vertext[1].color.Set(defClr);
		vertext[1].uv.set( u0, v1 );
		vertext[1].index = Math::float2(fIndex, 0.f);

		vertext[2].pos = Math::float3(1.0f , 0.0f, 0);
		vertext[2].color.Set(defClr);
		vertext[2].uv.set( u1, v1  );
		vertext[2].index = Math::float2(fIndex, 0.f);

		vertext[3].pos = Math::float3(1.0f , 2.0f, 0); 
		vertext[3].color.Set(defClr);
		vertext[3].uv.set( u1, v0  );
		vertext[3].index = Math::float2(fIndex, fWave);


		Math::float3 normal = Math::float3::normalize(vertext[1].pos - vertext[0].pos);
		normal = normal.crossProduct( Math::float3::normalize(vertext[1].pos - vertext[2].pos) );
		normal = Math::float3::normalize( normal );

		vertext[0].normal = normal;
		vertext[1].normal = normal;
		vertext[2].normal = normal;
		vertext[3].normal = normal;


	}

	void GrassInstanceMap::_GenerateIndices(ushort* indices, IndexT instIndex)
	{

		IndexT curVertIndex = instIndex * g_VertexCount;
		indices[0] = curVertIndex;
		indices[1] = curVertIndex + 1;
		indices[2] = curVertIndex + 2;
		indices[3] = curVertIndex + 2;
		indices[4] = curVertIndex + 3;
		indices[5] = curVertIndex;
	}
	//------------------------------------------------------------------------
	void GrassInstanceMap::Update()
	{


		if ( !mVegeObject || mInstances.IsEmpty())
			return;		

		if ( m_bInstDirty )
		{
			BuildPrimitive();
		}	

	}
}