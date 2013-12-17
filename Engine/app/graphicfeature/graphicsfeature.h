/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
#ifndef __GRAPHICSFEATURE_H__
#define __GRAPHICSFEATURE_H__
#include "appframework/feature.h"
#include "appframework/scene.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Camera/Camera.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "foundation/delegates/delegatetype.h"

//------------------------------------------------------------------------------
namespace App
{

	class GraphicsFeature : public App::Feature    
	{
		__DeclareSubClass(GraphicsFeature, Feature);
		__DeclareImageSingleton(GraphicsFeature);   
	public:
		typedef Delegates::delegates::CMultiDelegate1<GraphicsFeature*> EventHandle_DeviceReset;
		/// constructor
		GraphicsFeature();
		/// destructor
		virtual ~GraphicsFeature();

		/// called from GameServer::ActivateComponents()
		virtual void OnActivate();
		/// called from GameServer::DeactivateComponents()
		virtual void OnDeactivate();           
		/// called from within GameServer::OnStart() after OnLoad when the complete world exist
		virtual void OnStart();      
		/// called on begin of frame
		virtual void OnBeginFrame();
		/// called in the middle of the feature trigger cycle
		virtual void OnFrame();        
		/// called at the end of the feature trigger cycle
		virtual void OnEndFrame();

		/// get the graphicsystem
		const GPtr<Graphic::GraphicSystem>& GetGraphicSystem(void) const;

		///// Assign camera actor which is current used as main camera
		//void AssignDefaultCamera(const GPtr<App::Actor>& camActor);


		///// get the camera actor
		GPtr<App::Actor> GetDefaultCameraActor() const;   

		void SetMainWindow(WindHandle hWnd);
		/// get window handle
		WindHandle GetMainWindow(void) const;
		/// default mainwindow
		void SetWindowSize( int width, int height);

		GPtr<Graphic::ViewPortWindow> CreateViewPortWindow( WindHandle hWnd);

		void DestroyViewPortWindow(GPtr<Graphic::ViewPortWindow>& view);

		GPtr<Graphic::ViewPortWindow>& GetMainViewPort();

		/// set started as web version
		void SetWebVersion(bool bWebVersion);
		/// is started as web version
		const bool IsWebVersion() const;

		void SetDeviceLostCallBack(RenderBase::deviceLostCallBackFunc func);

		void OnDeviceLost();
		bool CheckReset();
		void OnDeviceReset();

		EventHandle_DeviceReset eventDeviceReset;

	protected:

		void onMainViewPortChange(Graphic::ViewPortWindow* sender);

		GPtr<Graphic::GraphicSystem> mGraphicSystem;
		//GPtr<App::Actor> mDefaultCameraActor;
		GPtr<Graphic::ViewPortWindow> mMainViewPort;
		bool mWebVersion;
		WindHandle mMainWindow;
		int mWindowHeight;
		int mWindowWidth;
		bool mWindowSizeChanged;
		void* mChangeWindow;
	};

	//------------------------------------------------------------------------
	inline
		const GPtr<Graphic::GraphicSystem>& 
		GraphicsFeature::GetGraphicSystem(void) const
	{
		return mGraphicSystem;
	}
	//--------------------------------------------------------------------------------
	inline
		WindHandle
		GraphicsFeature::GetMainWindow(void) const
	{
		return mMainWindow;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		GraphicsFeature::SetWebVersion(bool bWebVersion)
	{
		this->mWebVersion = bWebVersion;
	}
	//------------------------------------------------------------------------
	inline
		const bool 
		GraphicsFeature::IsWebVersion() const
	{
		return this->mWebVersion;
	}
	//------------------------------------------------------------------------
	inline
		void
		GraphicsFeature::SetDeviceLostCallBack(RenderBase::deviceLostCallBackFunc func)
	{
		this->mGraphicSystem->SetDeviceLostCallBack(func);
	}

} // namespace GraphicsFeatureUnit
//------------------------------------------------------------------------------

#endif //__GRAPHICSFEATURE_H__
