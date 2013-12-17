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
#include "Camera/CameraSetting.h"
#include "foundation/math/float3.h"

namespace Graphic
{
	using namespace Math;

	//------------------------------------------------------------------------------
	/**
	*/
	CameraSetting::CameraSetting() :
	viewProjDirty(true),
		viewMatrix(matrix44::identity()),
		viewProjMatrix(matrix44::identity())
	{
		zShadowDistance = 1000.0f;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	CameraSetting::~CameraSetting()
	{
		//empty
	}
	//------------------------------------------------------------------------------
	/**
	Setup camera as perspective projection. This method can be called
	before or after setting up the object. When the object is alive,
	an update message will be sent to the render-thread.
	*/
	void
		CameraSetting::SetupPerspectiveFovRH(float fov_, float aspect_, float zNear_, float zFar_)
	{
		this->isPersp = true;
		this->zNear   = zNear_;
		this->zFar    = zFar_;
		this->fov     = fov_;
		this->aspect  = aspect_;

		this->projMatrix = matrix44::perspfovrh(this->fov, this->aspect, this->zNear, this->zFar);
		this->invProjMatrix = matrix44::inverse(this->projMatrix);

		float tan_fov = tan(fov_ * 0.5f);
		this->nearHeight = 2.0f * this->zNear * tan_fov;
		this->nearWidth = this->nearHeight * aspect_;

		this->farHeight = 2.0f * this->zFar * tan_fov;
		this->farWidth = this->farHeight * aspect_;


		float yLen = Math::n_tan(0.5f * this->fov);
		float xLen = yLen * this->aspect;
		this->focalLength.set(xLen, yLen);

		this->viewProjDirty = true;
	}

	//------------------------------------------------------------------------------
	/**
	Setup camera as perspective projection with a proj clip plane. 
	This method can be called before or after setting up the object. 
	When the object is alive, an update message will be sent to the
	render-thread.
	*/
	void
		CameraSetting::SetupPerspectiveFovRH(float fov_, float aspect_, float zNear_, float zFar_, float4 clipPlane_, bool reflection)
	{
		float4 plane;

		SetupPerspectiveFovRH(fov_,aspect_,zNear_,zFar_);

		if (reflection)
		{
			plane = clipPlane_;
		}
		else
		{
			plane = float4::transform(matrix44::transpose(matrix44::inverse(this->viewMatrix)), clipPlane_);
		}

		Math::float3 normal = Math::float3(plane.x(), plane.y(), plane.z());
		plane.set_w(plane.w() / normal.normalise());


		float4 vec;
		vec.set_x( (n_sign(plane.x()) + projMatrix.getrow0().z()) / projMatrix.getrow0().x());
		vec.set_y( (n_sign(plane.y()) + projMatrix.getrow1().z()) / projMatrix.getrow1().y());
		vec.set_z(-1.f);
		vec.set_w((1.f + projMatrix.getrow2().z()) / projMatrix.getrow2().w());

		// Calculate the scaled plane vector
		float4 clipPlane4d(plane.x(), plane.y(), plane.z(), plane.w());
		float4 c = clipPlane4d * ( 2.f / (float4::dot4(clipPlane4d,vec)));

#if RENDERDEVICE_D3D9
		projMatrix.setrowcol((c.x() + projMatrix.getrow3().x()) / 2,2,0);
		projMatrix.setrowcol((c.y() + projMatrix.getrow3().y()) / 2,2,1);
		projMatrix.setrowcol((c.z() + 1.f + projMatrix.getrow3().z()) / 2,2,2);
		projMatrix.setrowcol((c.w() + projMatrix.getrow3().w()) / 2, 2,3);
#endif

#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
		projMatrix.setrowcol(c.x(),2,0);
		projMatrix.setrowcol(c.y(),2,1);
		projMatrix.setrowcol(c.z() + 1.0f,2,2);
		projMatrix.setrowcol(c.w(),2,3);
#endif	

		UpdateViewFrustum();
	}

	//------------------------------------------------------------------------------
	/**
	Setup camera as orthogonal projection.  This method can be called
	before or after setting up the object. When the object is alive,
	an update message will be sent to the render-thread.
	*/
	void
		CameraSetting::SetupOrthogonal(float w, float h, float zNear_, float zFar_)
	{
		this->isPersp    = false;
		this->zNear      = zNear_;
		this->zFar       = zFar_;
		this->fov        = 0.0f;
		this->aspect     = w / h;
		this->nearWidth  = w;
		this->nearHeight = h;
		this->farWidth   = w;
		this->farHeight  = h;
		this->focalLength.set(1.0f, 1.0f);

		this->projMatrix = matrix44::orthorh(w, h, this->zNear, this->zFar);
		this->invProjMatrix = matrix44::inverse(this->projMatrix);

		this->viewProjDirty = true;
	}

	//------------------------------------------------------------------------------
	/**
	Setup camera as orthogonal projection.  This method can be called
	before or after setting up the object. When the object is alive,
	an update message will be sent to the render-thread.
	*/
	void
		CameraSetting::SetupOffCenterOrthogonal(float l, float r, float b, float t, float zNear_, float zFar_)
	{
		this->isPersp    = false;
		this->zNear      = zNear_;
		this->zFar       = zFar_;
		this->fov        = 0.0f;
		this->aspect     = (r-l) / (t - b);
		this->nearWidth  = r-l;
		this->nearHeight = t - b;
		this->farWidth   = r-l;
		this->farHeight  = t - b;
		this->focalLength.set(1.0f, 1.0f);

		this->projMatrix = matrix44::orthooffcenterrh(l, r, b, t, this->zNear, this->zFar);
		this->invProjMatrix = matrix44::inverse(this->projMatrix);

		this->viewProjDirty = true;
	}

	//------------------------------------------------------------------------------
	/**
	Updates the view-projection matrix.
	*/
	void
		CameraSetting::UpdateViewProjMatrix() const
	{
		n_assert(this->viewProjDirty);
		this->viewProjDirty = false;
		this->viewProjMatrix = matrix44::multiply(this->projMatrix, this->viewMatrix);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		CameraSetting::UpdateViewFrustum() const
	{

		this->viewFrustum.setmatrix(GetViewProjTransform());
		this->viewFrustumDirty = false;
	}

} // namespace Graphic