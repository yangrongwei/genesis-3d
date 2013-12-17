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
#include "apputil/manuresutil.h"
#include "resource/resourceserver.h"

namespace AppUtil
{
	using namespace Resources;
	using namespace Util;
	using namespace Math;

	GPtr<Resources::Resource> 
	ManuResUtil::CreateManuResource( const Util::String& expectResID, const Core::Rtti* ResType)
	{
		if ( !ResourceServer::HasInstance() )
		{
			return GPtr<Resource>();
		}

		ResourceServer* resServer = ResourceServer::Instance();

		String realID = expectResID;

		{
			IndexT i = 0;
			while( resServer->HasResource( realID ) )
			{
				realID.Format( "%s_%i", expectResID.AsCharPtr(), i);
				++i;
			}
		}

		n_assert( !resServer->HasResource( realID ) );

		GPtr<Resource> res = resServer->CreateOrGetResource(realID, ResType );

		// 设置为手动加载
		if ( res.isvalid() )
		{
			res->SetManuLoad(true);
		}

		return res;
	}
	//------------------------------------------------------------------------
	GPtr<Resources::MeshRes> 
	ManuResUtil::CreateManuMesh( const Util::String& expectResID )
	{
		GPtr<Resources::Resource> pRes = CreateManuResource(expectResID, &MeshRes::RTTI );

		if ( pRes.isvalid() )
		{
			GPtr<MeshRes> pMesh = pRes.downcast<MeshRes>();
			n_assert( pMesh.isvalid() );
			return pMesh;
		}
		else
		{
			return GPtr<MeshRes>();
		}
	}
	//------------------------------------------------------------------------
	GPtr<Resources::MeshRes> 
	ManuResUtil::CreateManuMesh_LineList( const Util::String& expectResID,
		SizeT numVertex,
		const Math::float3* position,
		Math::Color32 color,
		SizeT numIndex ,
		const Index16Container::value_type* indicies )
	{
		GPtr<Resources::MeshRes> mesh = CreateManuMesh( expectResID );
		if ( !mesh.isvalid() )
		{
			return GPtr<MeshRes>();
		}

		if ( ManuResUtil::SetMesh_LineList(mesh, numVertex, position, color, numIndex, indicies ) )
		{
			return mesh;
		}
		else
		{
			return  GPtr<MeshRes>();
		}
	}
	//------------------------------------------------------------------------
	void 
	ManuResUtil::Build_Box(const Math::bbox& bb, PositionData& pos, Index16Container& indicies)
	{
		scalar minX = bb.pmin.x();
		scalar minY = bb.pmin.y();
		scalar minZ = bb.pmin.z();

		scalar maxX = bb.pmax.x();
		scalar maxY = bb.pmax.y();
		scalar maxZ = bb.pmax.z();

		// vertex
		n_assert( pos.IsEmpty() );
		pos.Reserve(8);

		pos.Append( Math::float3(minX, minY, minZ )  );
		pos.Append( Math::float3(minX, maxY, minZ )  );
		pos.Append( Math::float3(maxX, maxY, minZ )  );
		pos.Append( Math::float3(maxX, minY, minZ )  );

		pos.Append( Math::float3(minX, minY, maxZ )  );
		pos.Append( Math::float3(minX, maxY, maxZ )  );
		pos.Append( Math::float3(maxX, maxY, maxZ )  );
		pos.Append( Math::float3(maxX, minY, maxZ )  );

		// index
		n_assert( indicies.IsEmpty() );
		indicies.Reserve( 24 ); 

		// bottom
		{
			indicies.Append( 0 );
			indicies.Append( 1 );
			indicies.Append( 2 );

			indicies.Append( 2 );
			indicies.Append( 3 );
			indicies.Append( 0 );

		}

		// top
		{
			indicies.Append( 4 );
			indicies.Append( 5 );
			indicies.Append( 6 );

			indicies.Append( 6 );
			indicies.Append( 7 );
			indicies.Append( 4 );
		}

		// font
		{
			indicies.Append( 1 );
			indicies.Append( 2 );
			indicies.Append( 6 );

			indicies.Append( 6 );
			indicies.Append( 5 );
			indicies.Append( 1 );
		}
		// back
		{
			indicies.Append( 0 );
			indicies.Append( 4 );
			indicies.Append( 7 );

			indicies.Append( 7 );
			indicies.Append( 3 );
			indicies.Append( 0 );
		}
		// left
		{
			indicies.Append( 0 );
			indicies.Append( 1 );
			indicies.Append( 5 );

			indicies.Append( 5 );
			indicies.Append( 4 );
			indicies.Append( 0 );
		}
		// right
		{
			indicies.Append( 2 );
			indicies.Append( 3 );
			indicies.Append( 7 );

			indicies.Append( 7 );
			indicies.Append( 6 );
			indicies.Append( 2 );
		}
	}
	//------------------------------------------------------------------------
	void Build_LineList_Box(const Math::bbox& bb, PositionData& pos, Index16Container& indicies)
	{
		scalar minX = bb.pmin.x();
		scalar minY = bb.pmin.y();
		scalar minZ = bb.pmin.z();

		scalar maxX = bb.pmax.x();
		scalar maxY = bb.pmax.y();
		scalar maxZ = bb.pmax.z();

		// vertex 
		n_assert( pos.IsEmpty() );
		pos.Reserve(8);

		pos.Append( Math::float3(minX, minY, minZ )  );
		pos.Append( Math::float3(minX, maxY, minZ )  );
		pos.Append( Math::float3(maxX, maxY, minZ )  );
		pos.Append( Math::float3(maxX, minY, minZ )  );

		pos.Append( Math::float3(minX, minY, maxZ )  );
		pos.Append( Math::float3(minX, maxY, maxZ )  );
		pos.Append( Math::float3(maxX, maxY, maxZ )  );
		pos.Append( Math::float3(maxX, minY, maxZ )  );

		// index
		n_assert( indicies.IsEmpty() );
		indicies.Reserve( 24 ); 

		// bottom
		{
			indicies.Append( 0 );
			indicies.Append( 1 );

			indicies.Append( 1 );
			indicies.Append( 2 );

			indicies.Append( 2 );
			indicies.Append( 3 );

			indicies.Append( 3 );
			indicies.Append( 0 );
		}

		// top
		{
			indicies.Append( 4 );
			indicies.Append( 5 );

			indicies.Append( 5 );
			indicies.Append( 6 );

			indicies.Append( 6 );
			indicies.Append( 7 );

			indicies.Append( 7 );
			indicies.Append( 4 );
		}

		// side
		{
			indicies.Append( 1 );
			indicies.Append( 5 );

			indicies.Append( 0 );
			indicies.Append( 4 );

			indicies.Append( 2 );
			indicies.Append( 6 );

			indicies.Append( 3 );
			indicies.Append( 7 );
		}
	}

	//------------------------------------------------------------------------
	void 
	ManuResUtil::Build_Cone(Math::float3 inAxis, Resources::PositionData& position, Resources::Index16Container& indicies, Math::scalar sThickness, Math::scalar sHRatio)
	{
		position.Append(inAxis);
		Math::matrix44 mat = Math::matrix44::identity() ;
		mat.set_position(float4(inAxis.x(),inAxis.y(),inAxis.z(),1));
		//add the cone
		for (int j = 0;j<=36;j++)
		{	

			mat = matrix44::rotationaxis( float4(inAxis.x(),
				inAxis.y(),
				inAxis.z(),
				1.0),
				j*10 / 57.3f ) ;

			//--- vertext of  the cone
			Math::float4 _oriVec(sThickness+inAxis.x()*sHRatio,sThickness+inAxis.y()*sHRatio,sThickness+inAxis.z()*sHRatio , 0);
			_oriVec = Math::matrix44::transform(mat,_oriVec);
			position.Append(Math::float3(_oriVec.x(),_oriVec.y(),_oriVec.z())	);

			if(j>35)
				continue;

			//add cone 1 triangle 
			indicies.Append(j+1);
			indicies.Append(0);	
			indicies.Append(j+2);

		}
	}
	//-------------------------------------------------------------------------
	void 
	ManuResUtil::Build_Column(Math::float3 inAxis, Resources::PositionData& position, Resources::Index16Container& indicies, Math::scalar sThickness)
	{
		if (inAxis.x() == 0 && inAxis.y() == 0 && inAxis.z() == 0)
			return;
		
		//position.Append(inAxis);
		int PosReady = position.Size();
		Math::matrix44 mat = Math::matrix44::identity() ;
		mat.set_position(float4(inAxis.x(),inAxis.y(),inAxis.z(),1));
		//add the cone
		for (int j = 0;j<=36;j++)
		{	

			mat = matrix44::rotationaxis( float4(inAxis.x(),
				inAxis.y(),
				inAxis.z(),
				1.0),
				j*10 / 57.3f ) ;

			//---- vertext of the column
			Math::float4 _column(sThickness + inAxis.x(), sThickness + inAxis.y(), sThickness + inAxis.z(), 0);//柱高
			_column = Math::matrix44::transform( mat,_column);
			position.Append(Math::float3(_column.x(),_column.y(),_column.z())	);
			//axis value (0,0,0)
			scalar sx = _column.x()* (inAxis.x()>0.0f?0:1);
			scalar sy = _column.y()* (inAxis.y()>0.0f?0:1);
			scalar sz = _column.z()* (inAxis.z()>0.0f?0:1);
			Math::float3 tmp(sx,sy,sz) ;
			position.Append(tmp);
			//draw the column ====

			if(j>35)
				continue;

			//add colomn 2 triangles
			indicies.Append(PosReady + j*2+1);
			indicies.Append(PosReady + j*2);
			indicies.Append(PosReady + j*2+2);	

			indicies.Append(PosReady + j*2+2);	
			indicies.Append(PosReady + j*2+3);
			indicies.Append(PosReady + j*2+1);
		}
	}

	//------------------------------------------------------------------------
	GPtr<Resources::MeshRes> 
		ManuResUtil::CreateManuMesh_WithTopology( const Util::String& expectResID,
		SizeT numVertex,
		const Math::float3* position,
		Math::Color32 color,
		SizeT numIndex,
		const Resources::Index16Container::value_type* indicies,
		RenderBase::PrimitiveTopology::Code ptCode)
	{
		GPtr<Resources::MeshRes> mesh = CreateManuMesh( expectResID );
		if ( !mesh.isvalid() )
		{
			return GPtr<MeshRes>();
		}
		if ( numVertex < 2 || numVertex > 65535 || position == NULL )
		{
			return GPtr<MeshRes>();
		}


		mesh->SetTopologyType( ptCode );

		// set position
		if( !mesh->SetVertexData<PositionData>(position, numVertex ) )
		{
			return GPtr<MeshRes>();
		}
		// set color
		ColorData colorData;
		colorData.Fill(0, numVertex, color );
		if( !mesh->SetVertexData<ColorData>(&colorData[0], numVertex ) )
		{
			return GPtr<MeshRes>();
		}

		n_assert( indicies );
		if ( !mesh->SetIndex16(indicies, numIndex ) )
		{
			return GPtr<MeshRes>();
		}	

		// create submesh. must has submesh now
		SubMesh subMesh;
		subMesh.FirstIndex = 0;
		subMesh.numIndex = numIndex;
		subMesh.firstVertex = 0;
		subMesh.numVertex = numVertex;

		if ( !mesh->SetSubMesh(&subMesh,0 ) )
		{
			return GPtr<MeshRes>();
		}

		// set boundingbox
		mesh->RecalculateBounds(true);

		// set resource state
		mesh->SetState(Resource::Loaded);

		//-------
		return mesh;
	}

//------------------------------------------------------------------------
	bool 
	ManuResUtil::SetMesh_LineList( GPtr<MeshRes>& mesh,
		SizeT numVertex,
		const Math::float3* position,
		Math::Color32 color,
		SizeT numIndex ,
		const Resources::Index16Container::value_type* indicies )
	{
		if ( !mesh.isvalid() )
		{
			return false;
		}

		if ( numVertex < 2 || numVertex > 65535 || position == NULL )
		{
			return false;
		}

		if ( numIndex != 0 && indicies == NULL )
		{
			return false;
		}

		mesh->SetTopologyType( RenderBase::PrimitiveTopology::LineList );

		// set position
		if( !mesh->SetVertexData<PositionData>(position, numVertex ) )
		{
			return false;
		}

		// set color
		ColorData colorData;
		colorData.Fill(0, numVertex, color );
		if( !mesh->SetVertexData<ColorData>(&colorData[0], numVertex ) )
		{
			return false;
		}

		// create index. must has index now
		SizeT realIndexCount = 0;

		if ( numIndex == 0  )
		{
			realIndexCount = (numVertex-1) * 2;
			Index16Container indexArray;
			indexArray.Resize( realIndexCount, 0 );

			for ( IndexT index = 0; index < numVertex-1; ++index )
			{
				n_assert( index < 65535 );
				indexArray[index*2] = (ushort)index;
				indexArray[index*2 + 1 ] = (ushort)(index + 1);
			}

			if( !mesh->SetIndex16( &indexArray[0], realIndexCount) )
			{
				return false; 
			}
		}
		else
		{
			realIndexCount = numIndex;
			n_assert( indicies );
			if ( !mesh->SetIndex16(indicies, numIndex ) )
			{
				return false; 
			}	
		}

		// set boundingbox
		mesh->RecalculateBounds(true);

		// set resource state
		mesh->SetState(Resource::Loaded);

		return true;
	}

}

