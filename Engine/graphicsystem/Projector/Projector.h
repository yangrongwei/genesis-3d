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
#ifndef __PROJECTOR_H__
#define __PROJECTOR_H__

#include "Material/Material.h"

namespace Graphic
{
	class RenderScene;
	class Projector : public GraphicObject
	{
		__DeclareSubClass(Projector,GraphicObject)

	public:
		Projector();		
		~Projector();

		enum ViewType
		{
			VT_Ortho,	//ortho projector
			VT_Persp	//VT_Persp projector
		};

		void SetRenderScene(RenderScene* scene);


		// Near plane
		void SetNearClipPlane (float inNear) ;
		float GetNearClipPlane () const;

		float GetNearWidth() const;
		float GetNearHeight() const;

		// Far plane
		void SetFarClipPlane (float farPlane);
		float GetFarClipPlane () const;

		float GetFarWidth() const;
		float GetFarHeight() const;

		// Persp vertical angle or ortho height
		void SetFov (float angle);
		float GetFov () const ;

		// Aspect radio
		void SetAspectRatio (float aspect) ;
		float GetAspectRatio () const ;

		// Persp or Ortho
		void SetViewType(ViewType type);
		ViewType GetViewType() const;

		// Ignore Layers
		uint GetIgnoreLayers () ;
		void SetIgnoreLayers(uint layer) ;

		// Get view projection
		const Math::matrix44& GetViewProjMatrix() const;

		void SetProj(ViewType vt, float fovOrHeight, float zNear, float zFar);

		Math::matrix44 _CalcProjMatrix();
		void _UpdateProjector();
		const Util::Array<GPtr<RenderObject> >& GetRenderObjs() const;

		void CopyParam(const GPtr<Projector>& source);
	protected:

		RenderScene* mRenderScene;

		// near plane
		float           mNearClipPlane;
		float			mNearWidth;
		float			mNearHeight;

		// far plane
		float           mFarClipPlane;
		float			mFarWidth;
		float			mFarHeight;

		float           mOrthSize;
		float			mFov;
		float           mAspectRatio;

		ViewType        mViewType;

		uint			mIgnoreLayers;

		Math::matrix44  mViewProj;

		Util::Array<GPtr<RenderObject> > mRenderObjs;

		static	const	float			PerspNormalFov;	
		static  const	float			OrthoNormalHeight;
	};
	//--------------------------------------------------------------------------------
	inline 
		void 
		Projector::SetRenderScene(RenderScene* scene)
	{ 
		mRenderScene = scene;
	}
	//--------------------------------------------------------------------------------
	inline 
		void 
		Projector::SetNearClipPlane (float inNear) 
	{ 
		if ( mViewType == VT_Ortho)
			SetProj( mViewType, mOrthSize, inNear, mFarClipPlane);
		else
			SetProj( mViewType, mFov, inNear, mFarClipPlane);
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetNearClipPlane () const 
	{ 
		return mNearClipPlane; 
	}
	//--------------------------------------------------------------------------------
	inline 
		void 
		Projector::SetFarClipPlane (float farPlane) 
	{
		if ( mViewType == VT_Ortho)
			SetProj( mViewType, mOrthSize, mNearClipPlane, farPlane);
		else
			SetProj( mViewType, mFov, mNearClipPlane, farPlane);
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetFarClipPlane () const 
	{ 
		return mFarClipPlane;
	}
	//--------------------------------------------------------------------------------
	inline
		void 
		Projector::SetFov (float angle) 
	{ 
		SetProj( mViewType, angle, mNearClipPlane, mFarClipPlane);
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetFov () const
	{
		return mViewType == VT_Ortho ? mOrthSize : mFov; 
	}
	//--------------------------------------------------------------------------------
	inline
		Projector::ViewType 
		Projector::GetViewType() const
	{
		return mViewType;
	}
	//--------------------------------------------------------------------------------
	inline
		void 
		Projector::SetViewType(ViewType type)
	{
		if (type == VT_Ortho)
			SetProj( type, mOrthSize, mNearClipPlane, mFarClipPlane);
		else if ( type == VT_Persp )
			SetProj( type, mFov, mNearClipPlane, mFarClipPlane);
	}
	//--------------------------------------------------------------------------------
	inline 
		void 
		Projector::SetAspectRatio (float aspect) 
	{ 
		mAspectRatio = aspect;
		if (mViewType == VT_Ortho)
			SetProj( mViewType, mOrthSize, mNearClipPlane, mFarClipPlane);
		else if ( mViewType == VT_Persp )
			SetProj( mViewType, mFov, mNearClipPlane, mFarClipPlane);
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetAspectRatio () const 
	{ 
		return mAspectRatio; 
	}	
	//--------------------------------------------------------------------------------
	inline 
		uint 
		Projector::GetIgnoreLayers () 
	{ 
		return mIgnoreLayers;
	}
	//--------------------------------------------------------------------------------
	inline 
		void 
		Projector::SetIgnoreLayers(uint layer) 
	{
		mIgnoreLayers = layer;
	}
	//--------------------------------------------------------------------------------
	inline 
		const Util::Array<GPtr<RenderObject> >& 
		Projector::GetRenderObjs() const
	{
		return mRenderObjs;
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetNearWidth() const
	{
		return mNearWidth;
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetNearHeight() const
	{
		return mNearHeight;
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetFarWidth() const
	{
		return mFarWidth;
	}
	//--------------------------------------------------------------------------------
	inline 
		float 
		Projector::GetFarHeight() const
	{
		return mFarHeight;
	}
	//--------------------------------------------------------------------------------
	inline
		const Math::matrix44&
		Projector::GetViewProjMatrix() const
	{
		return mViewProj;
	}

}


#endif // __PROJECTOR_H__