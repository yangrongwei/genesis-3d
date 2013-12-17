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
#ifdef __WIN32__
#include "rendersystem/d3d9/TextureD3D9.h"
#endif
#include "graphicfeature/components/rendercomponent.h"
#include "graphicsystem/base/RenderToTexture.h"
#include "graphicsystem/Camera/Camera.h"

namespace App
{

	class LightprobeComponent : public App::RenderComponent
	{
		__DeclareSubClass(LightprobeComponent, App::RenderComponent);
	public:
		LightprobeComponent();
		~LightprobeComponent();
		virtual void OnActivate();
		/// called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		/// override to register accepted messages
		virtual void SetupAcceptedMessages();
		/// handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);
		virtual void _OnBeginFrame();

		/// called before rendering happens
		virtual void _OnFrame();

		/// @Component::_OnEndFrame called after movement has happened. 
		virtual void _OnEndFrame();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		// set the camera pos
		void SetCameraPos( Math::float4& pos);

		// get the camera pos
		Math::float4& GetCameraPos();

		// take a cube map on this frame
		void TakePhoto();

		// set texture save path
		void SetTexturePath(const Util::String& path);

		// an enum of camera direction
		enum CameraFacingDirection
		{
			X_POS	=	0,
			X_NEG		 ,
			Y_POS		 ,
			Y_NEG		 ,
			Z_POS		 ,
			Z_NEG
		};
	protected:
		// save cube texture
		void SaveRenderResult(const Util::String& path);

		void _UpdateRenderQueue();
#ifdef __WIN32__
		GPtr<D3D9::TextureD3D9>             m_pExportCubeTex;
#endif

		GPtr<Graphic::RenderToTexture>      m_pXPosDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pXPosTexture;
		GPtr<Graphic::Camera>               m_pXPosCam;

		GPtr<Graphic::RenderToTexture>      m_pXNegDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pXNegTexture;
		GPtr<Graphic::Camera>               m_pXNegCam;


		GPtr<Graphic::RenderToTexture>      m_pYPosDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pYPosTexture;
		GPtr<Graphic::Camera>               m_pYPosCam;

		GPtr<Graphic::RenderToTexture>      m_pYNegDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pYNegTexture;
		GPtr<Graphic::Camera>               m_pYNegCam;

		GPtr<Graphic::RenderToTexture>      m_pZPosDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pZPosTexture;
		GPtr<Graphic::Camera>               m_pZPosCam ;

		GPtr<Graphic::RenderToTexture>      m_pZNegDepthTex;
		GPtr<Graphic::RenderToTexture>      m_pZNegTexture;
		GPtr<Graphic::Camera>               m_pZNegCam ;

		int								   m_RenderTime;
		Util::String                       m_TexturePath;
		int								   rendertime;

	protected:
		void CreateCameraAndRT();
		void RemoveCamera();
		void AddCamera();

		void __CreateCamAndRT( GPtr<Graphic::RenderToTexture>& rt,GPtr<Graphic::Camera>& cam , CameraFacingDirection direction);
	};

	inline void LightprobeComponent::SetTexturePath(const Util::String& path)
	{
		m_TexturePath = path;
	}
}