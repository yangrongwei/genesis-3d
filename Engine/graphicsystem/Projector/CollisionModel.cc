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
#ifndef __PROJECTOR_COMMIT__
#include "stdneb.h"
#include "CollisionModel.h"
#include "resource/meshres.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "rendersystem/base/VertexBuffer.h"
#include "rendersystem/base/IndexBuffer.h"
#include "resource/resourcemanager.h"

#define ICE_NO_DLL
#if __ANDROID__
#include "extlibs/OPCODEA/Opcode.h"
#elif __WIN32__
#include "extlibs/OPCODE/Opcode.h"
#elif __OSX__
#include "Opcode.h"
#endif
namespace Graphic
{

	class OpModelImp
	{
		Opcode::Model             m_OpModel;
		Opcode::MeshInterface     m_OpMeshInterface;

		friend class CollisionModel;
	};

	__ImplementClass(CollisionModel, 'CLMD', Core::RefCounted);

	CollisionModel::CollisionModel()
		: m_pOpModelImp(NULL),
		m_nMemoryUsage(0),
		m_bIndex16(true)
	{

	}

	CollisionModel::~CollisionModel()
	{
		n_delete(m_pOpModelImp);
		m_pOpModelImp = NULL;

		m_Vertices.Clear();
		m_Indices.Clear();
		m_FaceNormals.Clear();
		m_nMemoryUsage = 0;
	}

	const Opcode::Model& CollisionModel::GetOpCodeModel() const
	{
		return m_pOpModelImp->m_OpModel;
	}

	void CollisionModel::SetPrimitveInfo( const Util::String& name)
	{
		// TODO : Î¬»¤MeshµÄÄÚ´æ³Ø
		GPtr<Resources::PrimitiveResInfo> primitiveResInfo = Resources::ResourceManager::Instance()->CreatePrimitiveInfo(name, 0);

		if (primitiveResInfo.isvalid())
		{
			const GPtr<Resources::MeshRes>& meshRes = primitiveResInfo->GetRes().downcast<Resources::MeshRes>();

			if (meshRes.isvalid() && meshRes->GetState() == Resources::Resource::Loaded)
			{
				Resources::PositionData::Elem* pPosData = meshRes->GetVertexData<Resources::PositionData>();
				SizeT vertexCount = meshRes->GetVertexCount();

				m_Vertices.Resize( vertexCount, Math::float3(0.0f, 0.0f, 0.0f));

				for (IndexT iVert = 0; iVert < vertexCount; ++iVert)
				{
					m_Vertices[iVert] = Math::float3( pPosData[iVert].x(), pPosData[iVert].y(), pPosData[iVert].z());
				}

				const Resources::Index16Container::value_type* pIndex16;
				const Resources::Index32Container::value_type* pIndex32;

				SizeT indexCount = meshRes->GetIndexCount();
				m_Indices.Resize(indexCount, 0);

				if (indexCount > 65535)
				{
					pIndex32 = meshRes->GetIndex32();

					for (IndexT i = 0; i < indexCount; ++i)
					{
						m_Indices[i] = pIndex32[i];
					}
				} 
				else
				{
					pIndex16 = meshRes->GetIndex16();

					for (IndexT i = 0; i < indexCount; ++i)
					{
						m_Indices[i] = static_cast<uint>(pIndex16[i]);
					}
				}
			}
		}

		primitiveResInfo = NULL;
	}

	void CollisionModel::CreateOpModel()
	{
		m_pOpModelImp = n_new(OpModelImp);

		m_pOpModelImp->m_OpMeshInterface.SetNbVertices(m_Vertices.Size());
		m_pOpModelImp->m_OpMeshInterface.SetNbTriangles(m_Indices.Size() / 3);
		m_pOpModelImp->m_OpMeshInterface.SetPointers(
			reinterpret_cast<const IceMaths::IndexedTriangle*>(&m_Indices[0]),
			reinterpret_cast<const IceMaths::Point*>(&m_Vertices[0])
			);

		if (! m_pOpModelImp->m_OpMeshInterface.IsValid() )
		{
			n_error("Opcode MeshInterface is invalid!");
		}

		Opcode::OPCODECREATE buildInfo;
		buildInfo.mIMesh            = &m_pOpModelImp->m_OpMeshInterface;
		buildInfo.mSettings.mLimit  = 1;
		buildInfo.mSettings.mRules  = Opcode::SPLIT_BALANCED | Opcode::SPLIT_GEOM_CENTER;
		buildInfo.mNoLeaf           = true;
		buildInfo.mQuantized        = true;
		buildInfo.mKeepOriginal     = false;
		buildInfo.mCanRemap         = false;

		if (! m_pOpModelImp->m_OpModel.Build(buildInfo))
		{
			n_error("Can not build Opcode Model");
		}

		// Compute triangle face normals
		SizeT numTriangles = m_Indices.Size() / 3;
		m_FaceNormals.Reserve(numTriangles);
		for ( SizeT i = 0; i < numTriangles; ++i)
		{
			const Math::float3& v0 = m_Vertices[m_Indices[i*3 + 0]];
			const Math::float3& v1 = m_Vertices[m_Indices[i*3 + 1]];
			const Math::float3& v2 = m_Vertices[m_Indices[i*3 + 2]];

			m_FaceNormals.Append(
				Math::float3::calculateFaceNormalWithoutNormalize(v0,v1,v2));
		}

		// Calculate used memory
		m_nMemoryUsage = m_pOpModelImp->m_OpModel.GetUsedBytes() +
			m_Vertices.Size() * sizeof(Math::float3) +
			m_FaceNormals.Size() * sizeof(m_FaceNormals[0]) +
			m_Indices.Size()  * m_bIndex16 ? sizeof(uint16) : sizeof(uint);
	}

}
#endif // __PROJECTOR_COMMIT__
