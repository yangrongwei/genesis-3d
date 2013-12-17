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

//
// 此头文件为swig扫描对象之一，慎重修改。
//
#ifndef _RENDERBASE_H_
#define _RENDERBASE_H_
#include "foundation/core/types.h"
namespace Graphic
{
	enum RenderPassType
	{
		eCustomized = 0,//
		eForward,//
		eDepth,
		eShadow,
		eGBuffer,
		eDeferredLightPass,
		ePassCount
	};

	//[zhongdaohuan] 
	//主要是为了把物体归类到不同的组里边，摄像机渲染的时候会以组为单位决定哪些该渲染，哪些不该渲染。
	//eRLCustomBegin之前为引擎自用，
	//eRLCustomBegin 到eRLCustomEnd之间的标记位预留给用户来自定义。
	//脚本也会有一个_RenderLayer的枚举。在layer.cs中，如果这里做了任何修改，请一并确保脚本相关枚举的正确性。
	enum RenderLayer
	{
		eRLNone = BIT_FLAG_NONE,
		eRLDefault = BIT_FLAG(0),
		eRLWater = BIT_FLAG(4),
		eRLCustomBegin = BIT_FLAG(6),//
		eRLCustomEnd = BIT_FLAG(29),//
		eRLDebug = BIT_FLAG(31),

		eRLSYSAll = eRLDefault | eRLWater,
		eRLCustomAll = BIT_FLAG(6) | BIT_FLAG(7) | 0x0fffff00 | BIT_FLAG(28) | BIT_FLAG(29),
		eRLCameraRenderAll = eRLSYSAll | eRLCustomAll,

		eRLRenderAll = BIT_FLAG_ALL,//渲染所有layer。

	};

	enum MaterialParameterType
	{
		eMaterialParamInvailid = -1,
		eMaterialParamMatrix,
		eMaterialParamVector,
		eMaterialParamFloat,
		eMaterialParamTexture1D,
		eMaterialParamTexture2D,
		eMaterialParamTexture3D,
		eMaterialParamTextureCUBE,
		eMaterialParamCount
	};

	enum CameraOrder
	{
		eCO_InvalidCamera = -1,
		eCO_Shadow = 0,
		eCO_Main = 13,
		eCO_PuppetMain = 1000,//[zhongdaohuan]标记为Main，但永远不能被激活。
	};
}


#endif
