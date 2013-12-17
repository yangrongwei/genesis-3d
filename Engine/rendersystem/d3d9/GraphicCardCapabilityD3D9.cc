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

#if WIN32


#include "stdneb.h"
#include "rendersystem//base/GraphicCardCapability.h"
#include "RenderDeviceD3D9.h"
#include "D3D9Types.h"
#include "RenderSystem.h"
#pragma warning(disable:4800)
namespace RenderBase
{

using namespace D3D9;

#if RENDERDEVICE_D3D9
void GraphicCardCapability::DetectGraphicCardCapsD3D9()
{

	mDriverName = "Direct3D";
    mApiVersion = "9";


	RenderDeviceD3D9* d3dDevice = RenderDeviceD3D9::Instance();
	DWORD d3dAdapter = d3dDevice->GetAdapter();
	D3DDEVTYPE d3dDevType = d3dDevice->GetDeviceType();

	D3DCAPS9	d3dCaps;
	d3dDevice->GetDeviceCaps( d3dAdapter, d3dDevType, &d3dCaps );

	mMaxTextureWidth = d3dCaps.MaxTextureWidth;
	mMaxTextureHeight = d3dCaps.MaxTextureHeight;
}
#endif

}

#endif