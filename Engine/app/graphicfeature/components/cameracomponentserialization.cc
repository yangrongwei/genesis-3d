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
#include "appframework/component.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicsystem/Material/Material.h"


namespace App
{
	using namespace Graphic;

	class CameraComponentSerialization
	{
	public:
		CameraComponentSerialization( const CameraComponent* pComponent )
			
		{
			mObject = const_cast<CameraComponent*>(pComponent);
		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				load_1(pReader);
			}
			else if ( 2 == ver )
			{
				load_2(pReader);
			}
			else if ( 3 == ver )
			{
				load_3(pReader);
			}
			else if ( 4 == ver )
			{
				load_4(pReader);
			}
			else if ( 5 == ver )
			{
				load_5(pReader);
			}
			else if ( 6 == ver )
			{
				load_6(pReader);
			}
			else 
			{
				n_error(" SceneSerialization::Load unknonw version " );
			}
			if (sListener)
			{
				sListener->OnLoad(mObject);
			}
		}
		void Save( AppWriter* pWriter );
		static CameraComponentLoadListener* sListener;
	protected:

		void load_1(AppReader* pSerialize);
		void load_2(AppReader* pSerialize);
		void load_3(AppReader* pSerialize);
		void load_4(AppReader* pSerialize);
		void load_5(AppReader* pSerialize);
		void load_6(AppReader* pSerialize);


		void _load_3(AppReader* pSerialize);
		void _load_4(AppReader* pSerialize);

		CameraComponent* mObject;

	};
	CameraComponentLoadListener* CameraComponentSerialization::sListener = NULL;
	const char* s_CameraOrder = "CameraOrder";

	const char* s_UseSkyBox = "UseSkyBox";
	const char* s_SkyTexCubeRes = "TexCubeRes";

	const char* s_CameraFov = "CameraFov";//[2012/10/25 zhongdaohuan]正交投影的时候，表示可视范围,透视投影的时候表示视角。
	const char* s_CameraAspact = "CameraAspact";
	const char* s_CameraZNear = "CameraZNear";
	const char* s_CameraZFar= "CameraZFar";
	//版本4后添加的属性
	const char* s_ViewType = "ViewType";
	const char* s_CullMark = "CullMark";
	const char* s_RenderMode = "s_RenderMode";
	//增加阴影参数
	const char* s_ShadowDistance = "ShadowDistance";
	//Render DepthMap
	const char* s_RenderDepth = "RenderDepth";
	//------------------------------------------------------------------------
	void CameraComponentSerialization::load_1(AppReader* pSerialize)
	{
		int eCameraOrder;
		pSerialize->SerializeInt(s_CameraOrder, eCameraOrder);
		mObject->SetCameraOrder( static_cast<Graphic::CameraOrder>(eCameraOrder) );

		return;
	}

	void CameraComponentSerialization::load_2(AppReader* pSerialize)
	{
		int eCameraOrder;
		bool bUseSkyBox;
		Util::String sTexCubeRes;
		pSerialize->SerializeInt(s_CameraOrder, eCameraOrder);
		mObject->SetCameraOrder( static_cast<Graphic::CameraOrder>(eCameraOrder) );
		pSerialize->SerializeBool(s_UseSkyBox, bUseSkyBox);
		mObject->SetUseSkyBox( bUseSkyBox );
		pSerialize->SerializeString(s_SkyTexCubeRes, sTexCubeRes);
		mObject->SetTexRes( sTexCubeRes );

		return;
	}
	void CameraComponentSerialization::_load_3(AppReader* pSerialize)
	{
		load_2(pSerialize);
		float fov;
		float aspect;
		float z_near;
		float z_far;

		pSerialize->SerializeFloat(s_CameraFov, fov);
		pSerialize->SerializeFloat(s_CameraAspact, aspect);
		pSerialize->SerializeFloat(s_CameraZNear, z_near);
		pSerialize->SerializeFloat(s_CameraZFar, z_far);

		mObject->SetProj( fov, z_near, z_far, Graphic::Camera::VT_persp);
		mObject->SetRenderMode(Camera::ForwardMode);
		mObject->SetCullMarkID(RenderLayerConverter::Convert(eRLCameraRenderAll));
		
	}
	void CameraComponentSerialization::load_3(AppReader* pSerialize)
	{
		_load_3(pSerialize);

	}

	void CameraComponentSerialization::_load_4(AppReader* pSerialize)
	{
		load_2(pSerialize);

		float fovOrHeight;
		//float aspect;
		float z_near;
		float z_far;

		uint cullmark;
		int viewtype;
		int rendermode;

		pSerialize->SerializeFloat(s_CameraFov, fovOrHeight);
		//pSerialize->SerializeFloat(s_CameraAspact, aspect);
		pSerialize->SerializeFloat(s_CameraZNear, z_near);
		pSerialize->SerializeFloat(s_CameraZFar, z_far);

		pSerialize->SerializeUInt(s_CullMark, cullmark);
		pSerialize->SerializeInt(s_ViewType, viewtype);
		pSerialize->SerializeInt(s_RenderMode, rendermode);


		mObject->SetCullMarkID(cullmark);
		mObject->SetRenderMode(static_cast<Camera::RenderMode>(rendermode));

		mObject->SetProj(fovOrHeight, z_near, z_far, static_cast<Graphic::Camera::ViewType>(viewtype));//[zhongdaohuan]
	}

	void CameraComponentSerialization::load_4(AppReader* pSerialize)
	{
		_load_4(pSerialize);
	}

	void CameraComponentSerialization::load_5(AppReader* pSerialize)
	{
		load_2(pSerialize);

		float fovOrHeight;
		//float aspect;
		float z_near;
		float z_far;

		uint cullmark;
		int viewtype;
		int rendermode;
		float shadowDistance;

		pSerialize->SerializeFloat(s_CameraFov, fovOrHeight);
		//pSerialize->SerializeFloat(s_CameraAspact, aspect);
		pSerialize->SerializeFloat(s_CameraZNear, z_near);
		pSerialize->SerializeFloat(s_CameraZFar, z_far);

		pSerialize->SerializeUInt(s_CullMark, cullmark);
		pSerialize->SerializeInt(s_ViewType, viewtype);
		pSerialize->SerializeInt(s_RenderMode, rendermode);

		pSerialize->SerializeFloat(s_ShadowDistance, shadowDistance);
		
		mObject->SetCullMarkID(cullmark);
		mObject->SetRenderMode(static_cast<Camera::RenderMode>(rendermode));

		mObject->SetProj(fovOrHeight, z_near, z_far, static_cast<Graphic::Camera::ViewType>(viewtype));//[zhongdaohuan]
		
		mObject->SetShadowDistence(shadowDistance);
		
	}

	void CameraComponentSerialization::load_6(AppReader* pSerialize)
	{
		load_5(pSerialize);
		bool renderdepth;
		pSerialize->SerializeBool(s_RenderDepth,renderdepth);
		mObject->SetRenderDepth(renderdepth);
	}
	//------------------------------------------------------------------------
	void CameraComponentSerialization::Save(AppWriter* pSerialize)
	{
		Graphic::CameraOrder order = mObject->GetCameraOrder();
		if (Graphic::eCO_PuppetMain == order)
		{
			order = Graphic::eCO_Main;
		}
		pSerialize->SerializeInt(s_CameraOrder, order);

		pSerialize->SerializeBool(s_UseSkyBox, mObject->m_bUseSkyBox);
		pSerialize->SerializeString(s_SkyTexCubeRes, mObject->m_skyBoxRes.AsString());

		if(Camera::VT_ortho == mObject->GetViewType())
		{
			pSerialize->SerializeFloat(s_CameraFov, mObject->GetNearHeight());
		}
		else
		{
			pSerialize->SerializeFloat(s_CameraFov, mObject->GetFov());
		}

		//pSerialize->SerializeFloat(s_CameraAspact, mObject->GetAspect());
		pSerialize->SerializeFloat(s_CameraZNear, mObject->GetZNear());
		pSerialize->SerializeFloat(s_CameraZFar, mObject->GetZFar());

		pSerialize->SerializeUInt(s_CullMark, mObject->GetCullMarkID());
		pSerialize->SerializeInt(s_ViewType, mObject->GetViewType());
		pSerialize->SerializeInt(s_RenderMode, mObject->GetRenderMode());
		pSerialize->SerializeFloat(s_ShadowDistance, mObject->GetShadowDistence());
		pSerialize->SerializeBool(s_RenderDepth, mObject->IsRenderDepth());
		return;
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version CameraComponent::GetVersion() const
	{
		return 6;	//	当前版本号是6
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void CameraComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		CameraComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void CameraComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		CameraComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

	void CameraComponent::RegisterLoadListener(CameraComponentLoadListener* Listener)
	{
		CameraComponentSerialization::sListener = Listener;
	}

}


