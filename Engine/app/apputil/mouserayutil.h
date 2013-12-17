#pragma once
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

#include "math/float2.h"
#include "math/matrix44.h"
#include "math/line.h"
#include "math/ray.h"
#include "graphicsystem/Camera/Camera.h"

//------------------------------------------------------------------------------
namespace AppUtil
{

class MouseRayUtil
{
public:
	/// compute world-space line segment( line's length is by in_param float length) from mouse position (mouse screen position is expected in the range 0..1)
    static Math::line ComputeWorldMouseRay(const Math::float2& mouseScreenPos, float length, const Math::matrix44& invViewMatrix, const Math::matrix44& invProjMatrix, float nearPlane);
	static Math::line ComputeWorldMouseLine(const Math::float2& mousePos, const Math::matrix44& invViewMatrix, float nearPlaneDist, float nearPlaneWidth, float nearPlaneHeight, Graphic::Camera::ViewType viewType = Graphic::Camera::VT_persp, float length = 10000);

	/// compute world-space ray from mouse position (mouse screen position is expected in the range 0..1)
	static Math::Ray ComputeWorldMouseRay(const Math::float2& mouseScreenPos, const Math::matrix44& invViewMatrix, const Math::matrix44& invProjMatrix, float nearPlane, Graphic::Camera::ViewType viewType = Graphic::Camera::VT_persp);
	
	static Math::Ray ComputeWorldMouseRay(const Math::float2& mouseScreenPos, const Math::matrix44& invViewMatrix, float nearPlaneWidth, float nearPlaneHeight, float neardistane, Graphic::Camera::ViewType viewType);
};

} // namespace RenderUtil
//------------------------------------------------------------------------------

