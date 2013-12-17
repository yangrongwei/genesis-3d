/****************************************************************************
Copyright (c) 2009,Radon Labs GmbH
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
#include "apputil/mouserayutil.h"

namespace AppUtil
{
using namespace Math;

//------------------------------------------------------------------------------
/**
    Utility function which computes a ray in world space between the eye
    and the current mouse position on the near plane.
    Mouse position is expected in the range 0..1.
*/
line
MouseRayUtil::ComputeWorldMouseRay(const float2& mousePos, float length, const matrix44& invViewMatrix, const matrix44& invProjMatrix, float nearPlane)
{
    // Compute mouse position in world coordinates.
    point screenCoord3D((mousePos.x() - 0.5f) * 2.0f, (mousePos.y() - 0.5f) * 2.0f, 1.0f);
    vector viewCoord = matrix44::transform(invProjMatrix,screenCoord3D);
    point localMousePos = viewCoord * nearPlane * 1.1f;
    localMousePos.y() = -1 * localMousePos.y();
    point worldMousePos = matrix44::transform(invViewMatrix,localMousePos);
    vector worldMouseDir = worldMousePos - point(invViewMatrix.get_position());
    worldMouseDir = vector::normalize(worldMouseDir);
    worldMouseDir *= length;

    return line(worldMousePos, worldMousePos + worldMouseDir);
}

Math::line 
MouseRayUtil::ComputeWorldMouseLine(const float2& mousePos, const matrix44& invViewMatrix, float nearPlaneDist, 
											float nearPlaneWidth, float nearPlaneHeight, Graphic::Camera::ViewType viewType /*= Graphic::Camera::VT_persp*/, float length /*= 10000*/)
{
	float4 camPos = invViewMatrix.get_position();
	// we think invViewMatrix is not including scale information.If it doesn't contain scale information,
	// then the vector would be normalized, If it contains scale information, then the data blow is not right.
	float4 camBackDir = vector::normalize(invViewMatrix.get_zaxis());
	float4 camUpDir = vector::normalize(invViewMatrix.get_yaxis());
	float4 camRightDir = vector::normalize(invViewMatrix.get_xaxis());

	float4 bias = camBackDir * (-nearPlaneDist) 
		+ camUpDir * ((0.5f - mousePos.y()) * nearPlaneHeight) 
		+ camRightDir * ((mousePos.x() - 0.5f) * nearPlaneWidth);

	float4 worldMousePos = camPos + bias;
	float3 dir;
	if (Graphic::Camera::VT_ortho == viewType)
	{
		dir.set(-camBackDir.x(), -camBackDir.y(), -camBackDir.z());
	}
	else
	{
		dir.setFromFloat4(bias);	
		dir.normalise();
	}

	float3 endPos = dir * length;
	return line(worldMousePos, point(endPos.x(), endPos.y(), endPos.z()));
}

//------------------------------------------------------------------------
Math::Ray 
MouseRayUtil::ComputeWorldMouseRay(const Math::float2& mousePos, const Math::matrix44& invViewMatrix, const Math::matrix44& invProjMatrix, float nearPlane,Graphic::Camera::ViewType viewType)
{
	// Compute mouse position in world coordinates.
	point screenCoord3D((mousePos.x() - 0.5f) * 2.0f, (mousePos.y() - 0.5f) * 2.0f, 1.0f);
	vector viewCoord = matrix44::transform( invProjMatrix,screenCoord3D);
	point localMousePos = viewCoord * nearPlane * 1.0f;
	localMousePos.y() = -1 * localMousePos.y();
	point worldMousePos = matrix44::transform(invViewMatrix,localMousePos);
	vector worldMouseDir = worldMousePos - point(invViewMatrix.get_position());
	if(Graphic::Camera::VT_ortho == viewType)
	{
		worldMouseDir = vector(0.0f,0.0f,1.0f);
		worldMouseDir = matrix44::transform(invViewMatrix,worldMouseDir);
	}
	worldMouseDir = vector::normalize(worldMouseDir);

	float3 dir;
	dir.setFromFloat4(worldMouseDir);
	dir = float3::normalize(dir);
	if (float3::isNormalize(dir))
	{	
		return Ray( float3(worldMousePos.x(), worldMousePos.y(), worldMousePos.z() ), dir);
	}
	return Ray( float3(0,100000000,0), float3(0,1,0));

}
//------------------------------------------------------------------------
Math::Ray 
MouseRayUtil::ComputeWorldMouseRay(const Math::float2& mouseScreenPos, const Math::matrix44& invViewMatrix, float nearPlaneWidth, float nearPlaneHeight, float neardistane, Graphic::Camera::ViewType viewType)
{
	float4 camPos = invViewMatrix.get_position();
	// we think invViewMatrix is not including scale information.If it doesn't contain scale information,
	// then the vector would be normalized, If it contains scale information, then the data blow is not right.
	float4 camBackDir = invViewMatrix.get_zaxis();
	float4 camUpDir = invViewMatrix.get_yaxis();
	float4 camRightDir = invViewMatrix.get_xaxis();

	float4 bias = camBackDir * (-neardistane) 
		+ camUpDir * ((0.5f - mouseScreenPos.y()) * nearPlaneHeight) 
		+ camRightDir * ((mouseScreenPos.x() - 0.5f) * nearPlaneWidth);

	float4 worldMousePos = camPos + bias;
	float3 dir;
	if (Graphic::Camera::VT_ortho == viewType)
	{
		dir.set(-camBackDir.x(), -camBackDir.y(), -camBackDir.z());
	}
	else
	{
		dir.setFromFloat4(bias);	
		dir.normalise();
	}

	return Ray( float3(worldMousePos.x(), worldMousePos.y(), worldMousePos.z()), dir);
}

} // namespace RenderUtil
