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
#ifndef __simplesky_component_H__
#define __simplesky_component_H__

#include "meshrendercomponent.h"
#include "graphicsystem/Camera/Camera.h"

namespace App
{
	class SimpleSkyComponent : public App::MeshRenderComponent
{
	__DeclareSubClass(SimpleSkyComponent, App::MeshRenderComponent);

public:

	SimpleSkyComponent();

	virtual ~SimpleSkyComponent();

public:

	/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
	virtual void SetupCallbacks();
protected:

	/// @Component::OnActivate  called from Actor::ActivateComponents()
	virtual void OnActivate();

	/// @Component::OnDeactivate called from Actor::DeactivateComponents()
	virtual void OnDeactivate();

	// @Component::_OnDestroy called only form Actor::Destroy
	virtual void OnDestroy();

	/// @Component::Component called after movement has happened. 
	virtual void _OnMoveAfter();

	/// @Component::_OnBeginFrame called after movement has happened. 
	virtual void _OnBeginFrame();

	virtual void _BuildRenderObject();

	virtual void _BuildRenderRes();

	// update renderqueue of renderables from materials
	void _UpdateRenderQueue();

	void updateScale( Graphic::Camera* camera);
public:

	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	virtual Version GetVersion() const;

	// @ISerialization::Load 
	virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

	// @ISerialization::Save
	virtual void Save( AppWriter* pWriter ) const;

	// copy from other component
	virtual void CopyFrom( const GPtr<Component>& pComponent );

	/// list all reference resource ids
	virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

	virtual void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );

public:
	void SetSkyTexByNum( int num, Util::String& tex );
	const Util::String GetSkyTexByNum( int num );
protected:
    Util::String m_skyTex0;
	Util::String m_skyTex1;
	Util::String m_skyTex2;
	Util::String m_skyTex3;
	Util::String m_skyTex4;
	Util::String m_skyTex5;
};

}


#endif