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
#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "appframework/component.h"
#include "graphicsystem/Camera/Camera.h"

namespace Graphic
{
	class ViewPortWindow;
}

namespace App
{


typedef TypeConvert<Graphic::Camera::ViewType> ViewTypeConvert;
class CameraComponent;
class CameraComponentLoadListener
{
public:
	~CameraComponentLoadListener(){};
	virtual void OnLoad(CameraComponent* sender) = 0;
};

/*

*/

class CameraComponent : public App::Component
{
	__DeclareSubClass(CameraComponent, Component);
public:
	typedef uint CullMarkID;

    /// constructor
    CameraComponent();
    /// destructor
    virtual ~CameraComponent();

	/// setup callbacks for this component, call by Actor in OnActivate()
	virtual void SetupCallbacks();

	/// list all reference resource ids
	virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

	/// override to register accepted messages
	virtual void SetupAcceptedMessages();
	/// handle a single message
	virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

	void SetCameraOrder(Graphic::CameraOrder order );

	Graphic::CameraOrder GetCameraOrder() const;

	void SetTargetWindow(Graphic::ViewPortWindow* target);

	Graphic::ViewPortWindow* GetTargetWindow() const;

	bool IsMainCamera(void) const;

	bool IsNeedApply() const;

	bool IsUseSkyBox(void);
	void SetUseSkyBox(bool useSkyBox);

	void SetTexRes(const RenderBase::ResourcePath& str);
	const RenderBase::ResourcePath& GetTexRes(void);

	// get View Matrix
	const Math::matrix44& GetViewMat() ;

	// get Proj Matrix
	const Math::matrix44& GetProjMat() ;

	// get Proj Matrix
	const Math::matrix44& GetViewProjMat() ;

	Math::matrix44 GetViewMat_ex() ;
	Math::matrix44 GetProjMat_ex() ;

	Graphic::Camera::ViewType GetViewType() const;

	float GetFov() const;
	float GetNearWidth() const;
	float GetNearHeight() const;
	float GetAspect() const;
	float GetZNear() const;
	float GetZFar() const;
	float GetFarWidth() const;
	float GetFarHeight() const;
	float GetShadowDistence() const;
	bool GetProjParam( float* nearWidth , float* nearHeight , float* nearPlaneDis , float* farPlaneDis );
	bool SetProjParam( float nearW , float nearH , float nearDis , float farDis );
	bool SetProj(float fovOrHeight, float zNear, float zFar, Graphic::Camera::ViewType vt);
	bool SetProj(float fovOrHeight, float zNear, float zFar);
	void SetPerspectiveFovRH(float fov, float aspect, float zNear, float zFar);
	void SetPerspectiveFovRHEx(float fov, float aspect, float zNear, float zFar,const Math::float4& clipPlane_, bool reflection);

	void SetZFar(float zFar);
	void SetZNear(float zNear);
	void SetShadowDistence(float shadowDis);

	CullMarkID GetCullMarkID() const;
	void SetCullMarkID(CullMarkID id);

	void SetRenderMode(Graphic::Camera::RenderMode mode);
	Graphic::Camera::RenderMode GetRenderMode() const;

	const GPtr<Graphic::Camera>& GetCameraObject() const;

	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	virtual Version GetVersion() const;

	// @ISerialization::Load 
	virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

	// @ISerialization::Save
	virtual void Save( AppWriter* pWriter ) const;

	// copy from other component
	virtual void CopyFrom( const GPtr<Component>& pComponent );

	static void RegisterLoadListener(CameraComponentLoadListener* Listener);

	void SetRenderCustom(bool custom);

	bool IsRenderCustom();

	void SetRenderNormal(bool normal);

	bool IsRenderNormal();

	void SetRenderDepth(bool RenderDepth);

	bool IsRenderDepth();

	void SetRenderToTexture(const GPtr<Graphic::RenderToTexture>& rtt);

	void SetLightLitTexture(const GPtr<Graphic::RenderToTexture>& rtt);

	void SetUseBeforeDrawEvent(bool enable);

	bool GetUseBeforeDrawEvent() const;

	virtual void SetupAllResource();

	virtual bool IsAllResourceLoaded();

	//temp function.
	void SetRenderShadowMap(bool enable);

	bool GetRenderShadowMap() const;

protected:
	friend class CameraComponentSerialization;

	/// called from Actor::ActivateComponents()
	virtual void OnActivate();
	/// called from Actor::DeactivateComponents()
	virtual void OnDeactivate();

	virtual void OnRenderSceneChanged();

	/// called on begin of frame
	virtual void _OnBeginFrame();

	/// called before rendering happens
	virtual void _OnFrame();
	/// @Component::Component called after movement has happened. 
	/// this will change the camera view matrix when Actor change
	virtual void _OnMoveAfter();



	void AttachCamera();
	void DetachCamera();

	void AttachSkyBox();
	void DetachSkyBox();

	GPtr<Graphic::Camera> m_camera;
	RenderBase::ResourcePath m_skyBoxRes;

	bool m_bUseSkyBox;
	bool m_bSkyBoxDirty;

	bool m_bAttached;
	bool m_bInit;


};
//------------------------------------------------------------------------
inline
void 
CameraComponent::SetCameraOrder(Graphic::CameraOrder order )
{
	m_camera->SetCameraOrder(order);
}

//------------------------------------------------------------------------
inline Graphic::CameraOrder 
CameraComponent::GetCameraOrder() const
{
	return m_camera->GetCameraOrder();
}

//------------------------------------------------------------------------
inline
bool 
CameraComponent::IsMainCamera(void) const
{
	return m_camera->GetCameraOrder() == Graphic::eCO_Main;
}
//------------------------------------------------------------------------
inline 
const Math::matrix44& 
CameraComponent::GetViewMat() 
{
	return m_camera->GetViewTransform();
}
//------------------------------------------------------------------------
inline 
const Math::matrix44& 
CameraComponent::GetProjMat() 
{
	return m_camera->GetProjTransform();
}
//------------------------------------------------------------------------
inline 
	const Math::matrix44& 
	CameraComponent::GetViewProjMat() 
{
	return m_camera->GetViewProjTransform();
}
//------------------------------------------------------------------------
inline
Math::matrix44 
CameraComponent::GetViewMat_ex()
{ 
	return m_camera->GetViewTransform();
}
//------------------------------------------------------------------------
inline
Math::matrix44 
CameraComponent::GetProjMat_ex()
{
	return m_camera->GetProjTransform();
}
//------------------------------------------------------------------------
inline
Graphic::Camera::ViewType
CameraComponent::GetViewType() const
{
	return m_camera->GetViewType();
}
//------------------------------------------------------------------------
inline
float
CameraComponent::GetFov() const
{
	return m_camera->GetCameraSetting().GetFov();
}
//------------------------------------------------------------------------
inline
	float
	CameraComponent::GetNearWidth() const
{
	return m_camera->GetCameraSetting().GetNearWidth();
}
//------------------------------------------------------------------------
inline
	float
	CameraComponent::GetNearHeight() const
{
	return m_camera->GetCameraSetting().GetNearHeight();
}
//------------------------------------------------------------------------
inline
	float
	CameraComponent::GetFarWidth() const
{
	return m_camera->GetCameraSetting().GetFarWidth();
}
//------------------------------------------------------------------------
inline
	float
	CameraComponent::GetFarHeight() const
{
	return m_camera->GetCameraSetting().GetFarHeight();
}
//------------------------------------------------------------------------
inline
float
CameraComponent::GetAspect() const
{
	return m_camera->GetCameraSetting().GetAspect();
}
//------------------------------------------------------------------------
inline
float
CameraComponent::GetZNear() const
{
	return m_camera->GetCameraSetting().GetZNear();
}
//------------------------------------------------------------------------
inline
float
CameraComponent::GetZFar() const
{
	return m_camera->GetCameraSetting().GetZFar();
}
//------------------------------------------------------------------------
inline
Graphic::Camera::RenderMode
CameraComponent::GetRenderMode() const
{
	return m_camera->GetRenderMode();
}
//------------------------------------------------------------------------
inline
void
CameraComponent::SetRenderMode(Graphic::Camera::RenderMode mode)
{
	m_camera->SetRenderMode(mode);
}

inline 
void 
CameraComponent::SetTargetWindow(Graphic::ViewPortWindow* target)
{
	m_camera->SetTargetWindow(target);
}

inline
Graphic::ViewPortWindow* 
CameraComponent::GetTargetWindow() const
{
	return m_camera->GetTargetWindow();
}
//------------------------------------------------------------------------
inline
CameraComponent::CullMarkID
CameraComponent::GetCullMarkID() const
{
	return m_camera->GetCullMask();
}
//------------------------------------------------------------------------
inline
	void 
	CameraComponent::SetShadowDistence(float shadowDis)
{
	m_camera->SetShadowDistence(shadowDis);
}

//------------------------------------------------------------------------
inline float
	CameraComponent::GetShadowDistence() const
{
	return m_camera->GetShadowDistence();
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------


inline
const GPtr<Graphic::Camera>& 
CameraComponent::GetCameraObject() const
{
	return m_camera;
}
//------------------------------------------------------------------------
inline
void
CameraComponent::SetTexRes(const RenderBase::ResourcePath& str)
{
	if (str != m_skyBoxRes)
	{
		m_bSkyBoxDirty = true;
		m_skyBoxRes = str;
	}
}

inline
const RenderBase::ResourcePath& 
CameraComponent::GetTexRes(void)
{
	return m_skyBoxRes;
}

inline
void
CameraComponent::SetUseBeforeDrawEvent(bool enable)
{
	m_camera->SetBeforeDrawEvent(enable);
}

inline
bool
CameraComponent::GetUseBeforeDrawEvent() const
{
	return m_camera->IsUseBeforeDrawEvent();
}

inline 
void
CameraComponent::SetRenderShadowMap(bool enable)
{
	m_camera->SetRenderLightLitMap(enable);
}

inline
bool
CameraComponent::GetRenderShadowMap() const
{
	return m_camera->HasLightLitMap();
}

inline
void
CameraComponent::SetLightLitTexture(const GPtr<Graphic::RenderToTexture>& rtt)
{
	m_camera->SetLightLitMap(rtt);
}

}; // namespace GraphicsFeature
//------------------------------------------------------------------------------
#endif //__CAMERACOMPONENT_H__
