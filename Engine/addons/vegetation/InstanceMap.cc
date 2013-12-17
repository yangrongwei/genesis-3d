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
#include "vegetation/InstanceMap.h"
#include "vegetation/VegetationServer.h"
#include <functional>

namespace Vegetation
{	
	using namespace RenderBase;
	using namespace Math;

	__ImplementClass( Vegetation::VegeInstanceMap, 'VEIM', Core::RefCounted);

#ifdef __GENESIS_EDITOR__
	uint INSTANCEDATA_POS::Index = 0;
#endif

	const GPtr<VegeInstanceMap> VegeInstanceMap::NullVegeInstMap(NULL);
	//------------------------------------------------------------------------
	VegeInstanceMap::VegeInstanceMap()
		:mIsActive(false)
		,mVegeObject(NULL)
		,m_bHWInstancing(false)
		,m_nVertCount(g_VertexCount)
		,m_nIndicesCount(g_IndexCount)
		,m_nVertexDataSize(0)
		,m_nInstUsingCount(0)
		,m_nVertLimitCount(0)
		,m_bInstDirty(true)
	{

	}

	//------------------------------------------------------------------------
	VegeInstanceMap::~VegeInstanceMap()
	{

	}
	//--------------------------------------------------------------------------------
	bool VegeInstanceMap::BuildPrimitive()
	{
		return false;
	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::Active(void)
	{
		VegetationServer::Instance()->_attachVegetationInstMap( GPtr<VegeInstanceMap>(this) );
	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::DeActive(void)
	{
		VegetationServer::Instance()->_deattachVegetationInstMap( GPtr<VegeInstanceMap>(this) );
	}	
	//------------------------------------------------------------------------
	void VegeInstanceMap::_onActivate(void)
	{
		n_assert( !mIsActive );
		mIsActive = true;
	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::_onDeactivate(void)
	{
		n_assert( mIsActive );
		mIsActive = false;
	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::Update()
	{

	}
	//--------------------------------------------------------------------------------
	void VegeInstanceMap::UpdateInstData()
	{

	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::AddInstance(const INSTANCEDATA_POS& inst)
	{
		mInstances.Append(inst);		

	}
	//--------------------------------------------------------------------------------
	void VegeInstanceMap::_calcAxisVec(ushort axis, Math::vector& retVec)
	{
		switch(axis	)
		{
		case  0:
			retVec = Math::vector(1,0,0);
			break;
		case 2:
			retVec = Math::vector(0,0,1);
			break;
		default:
			retVec = Math::vector(0,1,0);
			break;
		}
	}
	//--------------------------------------------------------------------------------
	void VegeInstanceMap::BuildVertexComponents(const GPtr<Resources::MeshRes>& meshres)
	{
		m_vVerDeclare.Clear();
		if ( meshres.isvalid() )
		{
			//SizeT vertexByteSize = 0;
			{
				n_assert(meshres);

				if( meshres->GetVertexData<PositionData>() )
				{
					m_vVerDeclare.Append( VertexComponent(VertexComponent::Position,0, VertexComponent::Float3) );
				}

				if ( meshres->GetVertexData<NormalData>() )
				{
					m_vVerDeclare.Append( VertexComponent(VertexComponent::Normal,0, VertexComponent::Float3) );
				}

				if ( meshres->GetVertexData<ColorData>() )
				{
					//if ( RenderSystem::Instance()->GetRendererType() == eRendererD3D9 )
					if(true)
					{
						m_vVerDeclare.Append( VertexComponent(VertexComponent::Color,0, VertexComponent::ColorBGRA) );
					}
					else
					{
						n_error(" should decide device use bgra or rgba");
					}
				}

				const SizeT deviceSupportTexCount = 8;	// should be defined by render system
				for ( IndexT iTex = 0; iTex < deviceSupportTexCount; ++iTex )
				{
					if ( meshres->GetVertexData<TexCoordData>(iTex) )
					{
						m_vVerDeclare.Append( VertexComponent(VertexComponent::TexCoord, iTex, VertexComponent::Float2) );
					}
					else
					{
						break;
					}
				}	

				m_vVerDeclare.Append( VertexComponent(VertexComponent::TexCoord,1, VertexComponent::Float2) );
			}
		}
		else
		{
			//SizeT vertexByteSize = 0;
			{
				m_vVerDeclare.Append( VertexComponent(VertexComponent::Position,0, VertexComponent::Float3) );
				m_vVerDeclare.Append( VertexComponent(VertexComponent::Normal,0, VertexComponent::Float3) );

				// @todo D3D¡¢OpenGLES¡¢OpenGL£¬ should use native color format
				m_vVerDeclare.Append( VertexComponent(VertexComponent::Color,0, VertexComponent::ColorBGRA) );

				m_vVerDeclare.Append( VertexComponent(VertexComponent::TexCoord, 0, VertexComponent::Float2) );

				m_vVerDeclare.Append( VertexComponent(VertexComponent::TexCoord, 1, VertexComponent::Float2) );
			}
		}
	}
	//--------------------------------------------------------------------------------
	bool VegeInstanceMap::CreateInstanceVBuffer(  GPtr<RenderBase::PrimitiveGroup>& pPrimiGoup)
	{
		if( mInstances.Size() < 1 ) 
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------
	void VegeInstanceMap::_FillInstanceVBuffer( GPtr<VertexBuffer>& pVBO  )
	{


	}
	//--------------------------------------------------------------------------------
	void VegeInstanceMap::SetParentMatrix( const Math::matrix44& m  )
	{
		if ( mVegeObject == NULL)
		{
			return;
		}

		//const Math::matrix44& invMatrix = Math::matrix44::inverse(mVegeObject->GetWorldMatrix());

		for ( IndexT idx = 0; idx < mInstances.Size(); ++idx )
		{
			//mInstances[idx].pos = mInstances[idx].pos.transformPoint(invMatrix);
			mInstances[idx].pos = mInstances[idx].pos.transformPoint(m);	

		}
		//m_bInstDirty = true;
	}

}