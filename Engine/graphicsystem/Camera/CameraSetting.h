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
#ifndef __CAMERA_SETTING_H__
#define __CAMERA_SETTING_H__
#include "math/matrix44.h"
#include "math/float2.h"
#include "math/frustum.h"
namespace Graphic
{
	class CameraSetting
	{
	public:
		/// default constructor
		CameraSetting();
		/// default destructor
		virtual ~CameraSetting();
		/// setup a perspective view volume
		void SetupPerspectiveFovRH(float fov, float aspect, float zNear, float zFar);
		/// setup a perspective oblique view volume with a clipplane
		void SetupPerspectiveFovRH(float fov, float aspect, float zNear, float zFar, Math::float4 clipPlane, bool reflection = false);
		/// setup an orthogonal projection transform
		void SetupOrthogonal(float w, float h, float zNear, float zFar);
		/// setup an orthogonal projection transform at offcenter
		void SetupOffCenterOrthogonal(float l, float r, float b, float t, float zNear, float zFar);
		/// update view matrix
		void UpdateViewMatrix(const Math::matrix44& m);

		/// set shadow distance
		void SetShadowDistance(float shadowDistance);
		/// get projection matrix
		const Math::matrix44& GetProjTransform() const;
		/// get the inverse projection matrix
		const Math::matrix44& GetInvProjTransform() const;
		/// get view transform (inverse transform)
		const Math::matrix44& GetViewTransform() const;
		/// get view projection matrix (non-const!)
		const Math::matrix44& GetViewProjTransform() const;
		/// get view frustum 
		const Math::frustum& GetViewFrustum() const;
		/// get focal length (computed from fov and aspect ratio)
		const Math::float2& GetFocalLength() const;

		/// return true if this is a perspective projection
		bool IsPerspective() const;
		/// return true if this is an orthogonal transform
		bool IsOrthogonal() const;
		/// get near plane distance
		float GetZNear() const;
		/// get far plane distance
		float GetZFar() const;
		/// get shadow distance
		float GetShadowDistance() const;
		/// get field-of-view (only if perspective)
		float GetFov() const;
		/// get aspect ration (only if perspective)
		float GetAspect() const;
		/// get width of near plane
		float GetNearWidth() const;
		/// get height of near plane
		float GetNearHeight() const;
		/// get width of far plane
		float GetFarWidth() const;
		/// get height of far plane
		float GetFarHeight() const;

	private:
		/// update the view projection matrix
		void UpdateViewProjMatrix() const;
		/// update the view frustum
		void UpdateViewFrustum() const;

		Math::matrix44 projMatrix;
		Math::matrix44 invProjMatrix;
		Math::matrix44 viewMatrix;
		mutable Math::matrix44 viewProjMatrix;
		mutable Math::frustum viewFrustum;
		mutable bool viewProjDirty;
		mutable bool viewFrustumDirty;

		bool isPersp;
		float zNear;
		float zFar;
		float zShadowDistance;
		float fov;
		float aspect;
		float nearWidth;
		float nearHeight;
		float farWidth;
		float farHeight;
		Math::float2 focalLength;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		CameraSetting::UpdateViewMatrix(const Math::matrix44& m)
	{
		this->viewMatrix = m;
		this->viewProjDirty = true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		CameraSetting::GetProjTransform() const
	{
		return this->projMatrix;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		CameraSetting::GetInvProjTransform() const
	{
		return this->invProjMatrix;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		CameraSetting::GetViewTransform() const
	{
		return this->viewMatrix;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		CameraSetting::GetViewProjTransform() const
	{
		if (this->viewProjDirty)
		{
			this->UpdateViewProjMatrix();
		}
		return this->viewProjMatrix;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::frustum&
		CameraSetting::GetViewFrustum() const
	{
		if (this->viewFrustumDirty)
		{
			this->UpdateViewFrustum();
		}
		return this->viewFrustum;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline bool
		CameraSetting::IsPerspective() const
	{
		return this->isPersp;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline bool
		CameraSetting::IsOrthogonal() const
	{
		return !this->isPersp;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetZNear() const
	{
		return this->zNear;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetShadowDistance() const
	{
		return this->zShadowDistance;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline
		void CameraSetting::SetShadowDistance(float shadowDistance)
	{
		this->zShadowDistance = shadowDistance;
	}
	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetZFar() const
	{
		return this->zFar;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetFov() const
	{
		return this->fov;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetAspect() const
	{
		return this->aspect;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetNearWidth() const
	{
		return this->nearWidth;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetNearHeight() const
	{
		return this->nearHeight;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetFarWidth() const
	{
		return this->farWidth;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline float
		CameraSetting::GetFarHeight() const
	{
		return this->farHeight;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::float2&
		CameraSetting::GetFocalLength() const
	{
		return this->focalLength;
	}
}

#endif //__CAMERA_SETTING_H__

