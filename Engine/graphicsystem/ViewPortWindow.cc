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
#include "ViewPortWindow.h"
#include "base/RenderWindow.h"
#include "graphicsystem/GraphicSystem.h"
namespace Graphic
{
	__ImplementClass(ViewPortWindow,'VPWS',Core::RefCounted);
	ViewPortWindow::ViewPortWindow()
		:mDirty(false)
		,mViewportType(VPT_Unkown)
		,mpWindow(NULL)
	{
	}
	//--------------------------------------------------------------------------------
	ViewPortWindow::~ViewPortWindow()
	{
		n_assert(NULL == mpWindow);
	}
	//--------------------------------------------------------------------------------
	void ViewPortWindow::SetDeviceWindow(RenderWindow* dwnd)
	{
		mpWindow = dwnd;
	}

	void ViewPortWindow::ChangeSize(SizeT width, SizeT height)
	{
		mDisplayMode.SetWidth(width);
		mDisplayMode.SetHeight(height);
		mDirty = true;
		GraphicSystem::Instance()->_ViewPortDirty();
	}

	void ViewPortWindow::_OnChangeSize() 
	{
		eventViewportChange(this);
		mDirty = false;
	}

	void ViewPortWindow::ApplyGlobalShaderParam() const
	{
		Material::GetGlobalMaterialParams()->SetVectorParam(eGShaderVecScreenSize,float4(float(),float(mDisplayMode.GetHeight()),float(0.5/mDisplayMode.GetWidth()),float(0.5/mDisplayMode.GetHeight())));
	}
}
