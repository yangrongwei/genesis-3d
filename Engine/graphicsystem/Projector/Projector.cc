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
#include "GraphicSystem.h"
#include "Projector.h"
#include "graphicsystem/Renderable/RenderObject.h"

namespace Graphic
{
	__ImplementClass(Projector,'PJGO',GraphicObject);

	const float Projector::PerspNormalFov		= 60.0f;
	const float Projector::OrthoNormalHeight	= 10.0f;


	Projector::Projector()
		:	mRenderScene(NULL),
		mFov(60.0f),
		mAspectRatio(1.0f),
		mNearClipPlane(0.1f),
		mFarClipPlane(25000.0f),
		mOrthSize(50.0f),
		mViewType(VT_Ortho),
		mIgnoreLayers(0)
	{

		SetProj( VT_Ortho, mOrthSize, mNearClipPlane, mFarClipPlane);
		// init position & projection matrix
		m_transform = Math::matrix44::identity();
		mViewProj = Math::matrix44::identity();
	}
	//--------------------------------------------------------------------------------
	Projector::~Projector()
	{
	}
	//--------------------------------------------------------------------------------
	Math::matrix44 Projector::_CalcProjMatrix()
	{
		Math::matrix44 projection;
		if( mViewType == VT_Ortho )
			projection = Math::matrix44::orthooffcenterrh( -mOrthSize * mAspectRatio / 2.0f , mOrthSize * mAspectRatio / 2.0f, -mOrthSize / 2.0f, mOrthSize / 2.0f, mNearClipPlane, mFarClipPlane );
		else
			projection = Math::matrix44::perspfovrh( n_deg2rad(mFov), mAspectRatio, mNearClipPlane, mFarClipPlane );
		return projection;
	}
	//--------------------------------------------------------------------------------
	void Projector::_UpdateProjector()
	{
		mRenderObjs.Clear(false);	

		if (NULL == mRenderScene)
		{
			return;

		}
		mViewProj = Math::matrix44::multiply( _CalcProjMatrix(), Math::matrix44::inverse(m_transform));

		// set param in fx_projector.fx
		GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
		pGMP->SetMatrixParam(eGShaderMatProjector, mViewProj);

		// cull the render object in frustum
		GPtr<Vis::VisQuery> pVisQuery = mRenderScene->Cull(mViewProj, m_transform.get_position());
		n_assert(pVisQuery.isvalid());

		const Util::Array<GPtr<Vis::VisEntity> >& viEnityList = pVisQuery->GetQueryResult();
		for (IndexT i = 0; i < viEnityList.Size(); ++i)
		{
			const GPtr<Vis::VisEntity>& visEnt = viEnityList[i];
			n_assert( visEnt.isvalid() );
			const GPtr<RefCounted> obj = visEnt->GetUserData();
			n_assert( obj && obj->GetRtti()->IsDerivedFrom( RenderObject::RTTI ) );

			GPtr<RenderObject> renderObj = obj.downcast<RenderObject>();	//	not safe, but for engine's hierarchy simple herit is OK
			n_assert(renderObj);

			mRenderObjs.Append(renderObj);
		}
	}
	//--------------------------------------------------------------------------------
	void Projector::SetProj( ViewType vt, float fovOrHeight, float nearClipPlane, float farClipPlane)
	{
		// assign
		mViewType		= vt;
		mNearClipPlane = nearClipPlane;
		mFarClipPlane	= farClipPlane;

		if ( VT_Persp == mViewType )
		{
			mFov	= fovOrHeight;
			float tan_fov = tan( n_deg2rad(fovOrHeight*0.5f) );
			// near size
			mNearHeight = 2.0f * mNearClipPlane * tan_fov;
			mNearWidth  = mNearHeight * mAspectRatio;
			// far size
			mFarHeight = 2.0f * mFarClipPlane * tan_fov;
			mFarWidth  = mFarHeight * mAspectRatio;
		}
		else if ( VT_Ortho == mViewType )
		{
			mOrthSize = fovOrHeight;
			// near size
			mNearHeight = mOrthSize;
			mNearWidth  = mOrthSize * mAspectRatio;
			// far size
			mFarHeight	 = mOrthSize;
			mFarWidth  = mOrthSize * mAspectRatio;
		}
	}
	//--------------------------------------------------------------------------------
	void Projector::CopyParam( const GPtr<Projector>& source )
	{
		// near plane
		mNearClipPlane = source->mNearClipPlane;
		mNearWidth     = source->mNearWidth;
		mNearHeight	= source->mNearHeight;

		// far plane
		mFarClipPlane  = source->mFarClipPlane;
		mFarWidth		= source->mFarWidth;
		mFarHeight		= source->mFarHeight;

		mOrthSize		= source->mOrthSize;
		mFov			= source->mFov;
		mAspectRatio	= source->mAspectRatio;

		mViewType		= source->mViewType;

		mIgnoreLayers	= source->mIgnoreLayers;
	}
	//--------------------------------------------------------------------------------

}