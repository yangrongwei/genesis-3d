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
#ifndef __PROJECTORCOMPONENT_H__
#define __PROJECTORCOMPONENT_H__

#include "graphicfeature/components/rendercomponent.h"
#include "Projector/Projector.h"

namespace App
{
class ProjectorRenderObject;
class TerrainRenderComponent;
class TerrainNode;

class ProjectorRenderComponent : public App::RenderComponent
{
	__DeclareSubClass(ProjectorRenderComponent, App::RenderComponent);
public:
    /// constructor
    ProjectorRenderComponent();
    /// destructor
    virtual ~ProjectorRenderComponent();

	/// setup callbacks for this component, call by Actor in OnActivate()
	virtual void SetupCallbacks();

	/// override to register accepted messages
	virtual void SetupAcceptedMessages();
	/// handle a single message
	virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	virtual Version GetVersion() const;

	virtual void UpdateRenderLayer();

	// @ISerialization::Load 
	virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

	// @ISerialization::Save
	virtual void Save( AppWriter* pWriter ) const;

	void ActiveProjector(bool enable);

	const RenderBase::PrimitiveHandle& GetPrimitiveHandleByRenderable(const Graphic::Renderable* renderable) const;

	// View type
	void SetViewType(Graphic::Projector::ViewType viewType);
	Graphic::Projector::ViewType GetViewType() const;

	// Fov
	void SetFov(float fileOfView);
	float GetFov() const;

	// Aspect radio
	float GetAspectRatio() const;
	void SetAspectRatio(float angles);

	// Near clip plane
	void  SetNearClipPlane(float nearClipPlane);
	float GetNearClipPlane() const;
	float GetNearWidth() const;
	float GetNearHeight() const;

	// Far clip plane
	void SetFarClipPlane(float farClipPlane);
	float GetFarClipPlane() const;
	float GetFarWidth() const;
	float GetFarHeight() const;

	// Ignore Layers
	void SetIgnoreLayers(uint ignoreLayers);
	uint GetIgnoreLayers() const;

	// Material
	void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );
	const Resources::ResourceId& GetMaterialID(IndexT iSubMesh ); 

	// Get view projection
	const Math::matrix44& GetViewProjMatrix() const;

	void SetProj( Graphic::Projector::ViewType viewType, float fovOrHeight, float zNear, float zFar);

	// copy from other component
	virtual void CopyFrom( const GPtr<Component>& pComponent );

public:
	
	/** 
		Worldspace clipping planes.
	*/
	enum FrustumPlane
	{
		FRUSTUM_PLANE_NEAR   = 0,
		FRUSTUM_PLANE_FAR    = 1,
		FRUSTUM_PLANE_LEFT   = 2,
		FRUSTUM_PLANE_RIGHT  = 3,
		FRUSTUM_PLANE_TOP    = 4,
		FRUSTUM_PLANE_BOTTOM = 5,
		FRUSTUM_PLANE_COUNT  = 6
	};

	void _UpdateProjector();

	void SetProjectorTrans(const Math::matrix44& trans);

	void EnableProjectorUpdate(bool bEnable);

	Math::scalar GetAlphaValue(Math::scalar u, Math::scalar v);

	const GPtr<Graphic::Projector>& GetProJector() const;

	const bool IsProjectorEnabled() const;

protected:
	friend class CameraComponentSerialization;

	void _BuildRenderable();

	void _BuildRenderObject();

	void _BuildMeshInfo();

	// Attach renderable to render object
	void _AttachRenderObject();

	// Deattach renderable to render object
	void _DeattachRenderObject();

	void _UpdateBoundingBox(const Math::float3 &p);

	/// called from Actor::ActivateComponents()
	virtual void OnActivate();
	/// called from Actor::DeactivateComponents()
	virtual void OnDeactivate();

	virtual void OnRenderSceneChanged();

	/// called on begin of frame
	virtual void _OnBeginFrame();
	/// called on frame
	virtual void _OnFrame();

	/// @Component::Component called after movement has happened. 
	/// this will change the camera view matrix when Actor change
	virtual void _OnMoveAfter();


protected:
	typedef ProjectorRenderObject RenderObjectType;

	GPtr<Graphic::Projector> mProjector;

	bool  mIsNeedUpdate;

	// Mesh postion data
	Util::Array<Math::float3>	mVertexs;
	SizeT						mVertexLimit;

	// Terrain position & indices data
	Util::Array<Math::float3>   mTerrainVertexs;
	Util::Array<unsigned short>	mTerrainIndices;

	// aabb
	Math::bbox					mAabb;

	// Mesh primitive
	RenderBase::PrimitiveHandle mPrimitive;
	// Terrain primitive
	RenderBase::PrimitiveHandle mTerrainPrimitive;

	GPtr<ProjectorRenderObject>  mProjectorRenderObject;

#ifdef __GENESIS_EDITOR__
public:
	// Editor brush state
	bool GetBrushState() const;
	void SetBrushState(const bool b);

protected:
	// brush helper
	bool mIsBrushHelper;
#endif
};
//------------------------------------------------------------------------------
inline 
const GPtr<Graphic::Projector>& 
ProjectorRenderComponent::GetProJector() const
{
	n_assert(mProjector);
	return mProjector;

}
//--------------------------------------------------------------------------------
inline
void 
ProjectorRenderComponent::SetViewType( Graphic::Projector::ViewType viewType )
{
	mProjector->SetViewType(viewType);
}
//--------------------------------------------------------------------------------
inline
void 
ProjectorRenderComponent::SetProj( Graphic::Projector::ViewType viewType, float fovOrHeight, float zNear, float zFar)
{
	mProjector->SetProj( viewType, fovOrHeight, zNear, zFar);
}
//--------------------------------------------------------------------------------
inline
void 
ProjectorRenderComponent::SetAspectRatio( float angles )
{
	mProjector->SetAspectRatio(angles);
}
//--------------------------------------------------------------------------------
inline
float
ProjectorRenderComponent::GetAspectRatio() const
{
	return mProjector->GetAspectRatio();
}
//--------------------------------------------------------------------------------
inline
uint 
ProjectorRenderComponent::GetIgnoreLayers() const
{
	return mProjector->GetIgnoreLayers();
}
//--------------------------------------------------------------------------------
inline
float 
ProjectorRenderComponent::GetFarClipPlane() const
{
	return mProjector->GetFarClipPlane();
}
//--------------------------------------------------------------------------------
inline
float 
ProjectorRenderComponent::GetNearClipPlane() const
{
	return mProjector->GetNearClipPlane();
}
//--------------------------------------------------------------------------------
inline
void 
ProjectorRenderComponent::SetFov( float fileOfView )
{
	mProjector->SetFov(fileOfView);
}
//--------------------------------------------------------------------------------
inline
float 
ProjectorRenderComponent::GetFov() const
{
	return mProjector->GetFov();
}
//--------------------------------------------------------------------------------
inline
float
ProjectorRenderComponent::GetFarWidth() const
{
	return mProjector->GetFarWidth();
}
//--------------------------------------------------------------------------------
inline
Graphic::Projector::ViewType
ProjectorRenderComponent::GetViewType() const
{
	return mProjector->GetViewType();
}
//--------------------------------------------------------------------------------
inline
float
ProjectorRenderComponent::GetFarHeight() const
{
	return mProjector->GetFarHeight();
}
//--------------------------------------------------------------------------------
inline
void
ProjectorRenderComponent::SetIgnoreLayers( uint ignoreLayers )
{
	mProjector->SetIgnoreLayers(ignoreLayers);
}
//--------------------------------------------------------------------------------
inline
float
ProjectorRenderComponent::GetNearWidth() const
{
	return mProjector->GetNearWidth();
}
//--------------------------------------------------------------------------------
inline
float
ProjectorRenderComponent::GetNearHeight() const
{
	return mProjector->GetNearHeight();
}
//--------------------------------------------------------------------------------
inline
void
ProjectorRenderComponent::SetNearClipPlane( float nearClipPlane )
{
	mProjector->SetNearClipPlane(nearClipPlane);
}
//--------------------------------------------------------------------------------
inline
void
ProjectorRenderComponent::SetFarClipPlane( float farClipPlane )
{
	mProjector->SetFarClipPlane(farClipPlane);
}
//--------------------------------------------------------------------------------
inline
const Math::matrix44& 
ProjectorRenderComponent::GetViewProjMatrix() const
{
	return mProjector->GetViewProjMatrix();
}
//--------------------------------------------------------------------------------
inline
void 
ProjectorRenderComponent::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy /* = false */ )
{
	for ( IndexT i = 0; i < 2; ++i)
	{
		Super::SetMaterialID( i, matID, false);
	}
}
//--------------------------------------------------------------------------------
inline 
const Resources::ResourceId& 
ProjectorRenderComponent::GetMaterialID( IndexT iSubMesh )
{
	return Super::GetMaterialID(0);
}

}; // namespace GraphicsFeature
#endif // __PROJECTORCOMPONENT_H__
