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
#include "graphicsystem/Vision/RenderScene.h"
#include "RenderObject.h"


namespace Graphic
{
	using namespace Math;
	__ImplementClass(RenderObject,'REOB', GraphicObject)
		RenderObject::RenderObject()
		: m_Root(NULL)
		, m_LayerID(0)
		, m_NeedCullCallBack(false)
		, m_Projected(true)
		, mbReceiveShadow(true)
		, mbCastShadow(true)
	{	
		m_transform = matrix44::identity();
	}
	RenderObject::~RenderObject()
	{

	}
	//------------------------------------------------------------------------
	void RenderObject::SetBoundingBox(const bbox& box)
	{
		Super::SetBoundingBox(box);
		if ( m_VisEnt.isvalid() && m_Root )	//	update BoundingBox and visEntity in visSystem
		{
			Math::bbox worldBB = m_boundingBox;
			worldBB.transform( m_transform );
			m_VisEnt->UpdateBoundingBox( worldBB );

			m_Root->_UpdateVisEntity( m_VisEnt );
		}
	}
	//------------------------------------------------------------------------
	void RenderObject::SetTransform(const matrix44& trans)
	{
		Super::SetTransform(trans);
		if ( m_VisEnt.isvalid() && m_Root )	//	update BoundingBox and visEntity in visSystem
		{
			Math::bbox worldBB = m_boundingBox;
			worldBB.transform( m_transform );
			m_VisEnt->UpdateBoundingBox( worldBB );

			m_Root->_UpdateVisEntity( m_VisEnt );
		}
	}

	void RenderObject::Attach(IRenderScene* rnsc)
	{
		Detach();
		n_assert(rnsc);
		m_Root = rnsc;
		rnsc->_AddRenderObject(this);
	}

	void RenderObject::AttachNoCull(IRenderScene* rnsc)
	{
		Detach();
		n_assert(rnsc);
		m_Root = rnsc;
		rnsc->_AddRenderObjectNotCull(this);
	}

	void RenderObject::Detach()
	{
		if (m_Root)
		{
			if (m_VisEnt.isvalid())
			{
				m_Root->_RemoveRenderObject(this);
			}
			else
			{
				m_Root->_RemoveRenderObjectNotCull(this);
			}
			m_Root = NULL;
		}
	}

	//------------------------------------------------------------------------
	// !!!!!!internal call!!!!!  for vis manage. 
	void RenderObject::_SetVisEnt(const GPtr<Vis::VisEntity>& visEnt, IRenderScene* root)
	{
		n_assert( !m_VisEnt.isvalid() || !visEnt.isvalid() ) ;
		if ( m_VisEnt.isvalid() )
		{
			m_VisEnt->Setup( Math::bbox(), NULL );
		}

		m_VisEnt = visEnt;
		m_Root = root;

		if ( m_VisEnt.isvalid() && m_Root)
		{
			Math::bbox worldBB = m_boundingBox;
			worldBB.transform( m_transform );
			m_VisEnt->Setup( worldBB, this );
		}
	}


	void RenderObject::Render(const Renderable* renderable, RenderPassType passType, const Material* customizedMaterial)
	{
		n_error("empty");
	}
	void RenderObject::AddToCollection(RenderDataCollection* collection)
	{
		n_error("empty");
	}
	void RenderObject::OnWillRenderObject(Camera* sender)
	{
		n_error("empty");
	}
}