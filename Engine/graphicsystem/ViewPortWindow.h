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
#ifndef __ViewPortWindow_H__
#define __ViewPortWindow_H__
#include "Camera/Camera.h"
#include "rendersystem/base/RenderDisplay.h"
#include "foundation/delegates/delegatetype.h"

class RenderWindow;

namespace Graphic
{
	enum ViewportType
	{
		VPT_Unkown = -1,
		VPT_CustomBegin = 0,
		VPT_CustomEnd = 999999,
		VPT_MAIN,
	};
	typedef Delegates::delegates::CMultiDelegate1<ViewPortWindow*> EventHandle_ViewportChange;
	class ViewPortWindow : public Core::RefCounted
	{
		__DeclareClass(ViewPortWindow);

		//public:
		//enum ViewPortPerspec

	public:
		ViewPortWindow();
		virtual ~ViewPortWindow();

		//void SetDisplay();
		void SetDisplayMode(const RenderBase::DisplayMode& mode);

		void ChangeSize(SizeT width, SizeT height);

		const RenderBase::DisplayMode& GetDisplayMode(void) const;

		void SetDeviceWindow(RenderWindow*);
		RenderWindow* GetRenderWindow(void) const;

		void ApplyGlobalShaderParam() const;

		void OnDeviceReset();

		ViewportType GetType() const;

		bool _IsDirty() const;
		void _OnChangeSize();

		void _SetType(ViewportType type);

		EventHandle_ViewportChange eventViewportChange;
	private:
		ViewportType					mViewportType;
		RenderWindow*				    mpWindow;
		RenderBase::DisplayMode			mDisplayMode;
		bool							mDirty;
	};

	//--------------------------------------------------------------------------------
	inline void ViewPortWindow::SetDisplayMode(const RenderBase::DisplayMode& mode)
	{
		mDisplayMode = mode;
	}
	//--------------------------------------------------------------------------------
	inline const RenderBase::DisplayMode& ViewPortWindow::GetDisplayMode(void) const
	{
		return mDisplayMode;
	}
	//--------------------------------------------------------------------------------
	inline RenderWindow* ViewPortWindow::GetRenderWindow(void) const
	{
		return mpWindow;
	}

	inline bool ViewPortWindow::_IsDirty() const
	{
		return mDirty;
	}

	inline ViewportType ViewPortWindow::GetType() const
	{
		return mViewportType;
	}

	inline void ViewPortWindow::_SetType(ViewportType type)
	{
		mViewportType = type;
	}
}
#endif // __ViewPortWindow_H__
