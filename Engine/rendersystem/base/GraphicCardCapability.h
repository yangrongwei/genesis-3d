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

#pragma once

#ifndef GRAPHICCARDCAPABILITY_H_
#define GRAPHICCARDCAPABILITY_H_
#ifdef __OSX__
#include "../rendersystem/config/RenderDeviceConfig.h"
#include "../rendersystem/base/RenderDeviceTypes.h"
#else
#include "config/RenderDeviceConfig.h"
#include "base/RenderDeviceTypes.h"
#endif


namespace RenderBase
{

struct GraphicCardCapability
{
	GraphicCardCapability()
	{
	}

	Util::String mDriverName;
	Util::String mApiVersion;

	SizeT mMaxTextureWidth;
	SizeT mMaxTextureHeight;
	
#if RENDERDEVICE_OPENGLES
	int  mMaxUniformVectors;
	int  mHighFloatRange[2];
	int  mHighFloatPrecision;
	bool mFragmentHightPrecision;
	bool mIndexUint;
	bool mDepthFormat;
	bool mSeparateAplhaBlend;
	bool mStencilTwoSize;
#endif

#if RENDERDEVICE_D3D9
	void DetectGraphicCardCapsD3D9();
#endif
#if RENDERDEVICE_OPENGLES
	void DetectGraphicCardCapsGLES20();
#endif

};
}
#endif




