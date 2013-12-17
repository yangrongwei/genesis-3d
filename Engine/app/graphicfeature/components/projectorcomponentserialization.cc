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
#include "graphicfeature/components/projectorcomponent.h"

namespace App
{
class ProjectorComponentSerialization
{
public:
	ProjectorComponentSerialization( const ProjectorRenderComponent* pComponent )
		:mObject(pComponent)
	{

	}
	inline void Load( Version ver, AppReader* pReader )
	{
		if ( 1 == ver )
		{
			Load_1(pReader);
			return;
		}
		if ( 2 == ver )
		{
			Load_2(pReader);
			return;
		}
		if ( 3 == ver)
		{
			Load_3(pReader);
		}
		else
		{
			n_error(" SceneSerialization::Load unknonw version " );
		}
	}

	void Load_1( AppReader* pReader );
	void Load_2( AppReader* pReader );
	void Load_3( AppReader* pReader );
	void Save( AppWriter* pWriter );
protected:
	const ProjectorRenderComponent* mObject;

};

/// 
const char* s_ProjectorViewType = "ViewType";
const char* s_FovOrHeight = "FovOrHeight";
const char* s_AspectRatio = "AspectRatio";
const char* s_NearClippingPlane = "NearClippingPlane";
const char* s_FarClippingPlane = "FarClippingPlane";
const char* s_Material = "Material";
const char* s_IgnoreLayers = "IgnoreLayers";

//------------------------------------------------------------------------
void ProjectorComponentSerialization::Load_1(AppReader* pSerialize)
{
	ProjectorRenderComponent* pPC = const_cast<ProjectorRenderComponent*>( mObject );

	return;
}

void ProjectorComponentSerialization::Load_2(AppReader* pSerialize)
{
	ProjectorRenderComponent* pPC = const_cast<ProjectorRenderComponent*>( mObject );


	return;
}
void ProjectorComponentSerialization::Load_3( AppReader* pReader )
{
	n_assert( mObject );

	ProjectorRenderComponent* pProjector = const_cast<ProjectorRenderComponent*>(mObject);
	n_assert(pProjector);

	// ViewType
	int viewType;
	pReader->SerializeInt(s_ProjectorViewType,viewType);
	pProjector->SetViewType((Graphic::Projector::ViewType)viewType);

	// Fov or height
	float fovOrHeight;
	pReader->SerializeFloat(s_FovOrHeight,fovOrHeight);
	pProjector->SetFov(fovOrHeight);

	// Aspect ratio
	float aspectRatio;
	pReader->SerializeFloat(s_AspectRatio,aspectRatio);
	pProjector->SetAspectRatio(aspectRatio);

	// Near clip plane
	float nearClipPlane;
	pReader->SerializeFloat(s_NearClippingPlane,nearClipPlane);
	pProjector->SetNearClipPlane(nearClipPlane);

	// Far clip plane
	float farClipPlane;
	pReader->SerializeFloat(s_FarClippingPlane,farClipPlane);
	pProjector->SetFarClipPlane(farClipPlane);

	// Material
	Util::String materialName;
	pReader->SerializeString(s_Material,materialName);
	pProjector->SetMaterialID(0,materialName,false);

	// Ignore Layers
	uint ignoreLayers;
	pReader->SerializeUInt(s_IgnoreLayers,ignoreLayers);
	pProjector->SetIgnoreLayers(ignoreLayers);

	pProjector->EnableProjectorUpdate(true);

	return;
}
//------------------------------------------------------------------------
void ProjectorComponentSerialization::Save(AppWriter* pWriter)
{
	n_assert(mObject);
	n_assert(pWriter);

	ProjectorRenderComponent* pProjector = const_cast<ProjectorRenderComponent*>(mObject);

	// ViewType
	int viewType = (int)pProjector->GetViewType();
	pWriter->SerializeInt(s_ProjectorViewType,viewType);

	// Fov or height
	float fovOrHeight = pProjector->GetFov();
	pWriter->SerializeFloat(s_FovOrHeight,fovOrHeight);

	// Aspect ratio
	float aspectRatio = pProjector->GetAspectRatio();
	pWriter->SerializeFloat(s_AspectRatio,aspectRatio);

	// Near clip plane
	float nearClipPlane = pProjector->GetNearClipPlane();
	pWriter->SerializeFloat(s_NearClippingPlane,nearClipPlane);

	// Far clip plane
	float farClipPlane = pProjector->GetFarClipPlane();
	pWriter->SerializeFloat(s_FarClippingPlane,farClipPlane);

	// Material
	const Resources::ResourceId& materialName = pProjector->GetMaterialID(0);
	pWriter->SerializeString(s_Material,materialName.AsString());

	// Ignore Layers
	uint ignoreLayers = pProjector->GetIgnoreLayers();
	pWriter->SerializeUInt(s_IgnoreLayers,ignoreLayers);

	return;
}

}

namespace App
{
//------------------------------------------------------------------------
// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
Version ProjectorRenderComponent::GetVersion() const
{
	return 3;	//	当前版本号是2
}

//------------------------------------------------------------------------
// @ISerialization::Load 
void ProjectorRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
{
	pReader->SerializeSuper<Super>(this, args);
	ProjectorComponentSerialization Serialize(this);
	Serialize.Load( ver, pReader );
}

//------------------------------------------------------------------------
// @ISerialization::Save
void ProjectorRenderComponent::Save( AppWriter* pWriter ) const
{
	pWriter->SerializeSuper<Super>(this);
	ProjectorComponentSerialization Serialize(this);
	Serialize.Save( pWriter );
}

}


