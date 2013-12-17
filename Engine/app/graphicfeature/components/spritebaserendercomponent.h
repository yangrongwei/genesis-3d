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
#ifndef SPRITEBASERENDERCOMPONENT_H_
#define SPRITEBASERENDERCOMPONENT_H_

#include "foundation/math/ray.h"
#include "graphicfeature/components/rendercomponent.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "sprite/sprite.h"

namespace Sprite
{
	class SpriteImage;
}

namespace App
{
	class SpriteRenderObject;

	class SpriteBaseRenderComponent: public App::RenderComponent
	{
		__DeclareSubClass(SpriteBaseRenderComponent, App::RenderComponent)
	public:
		SpriteBaseRenderComponent();
		virtual ~SpriteBaseRenderComponent();
		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		virtual void UpdateRenderLayer();

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;
		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		virtual void Setup(const Resources::ResourceId& packId);

		virtual void SetVisible(bool bVis);

		virtual void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );

		virtual void SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave = true );

		virtual void ModifyMaterialShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID);

		Resources::ResourceId GetPackageID() const;

		const RenderBase::PrimitiveHandle& _getHandle() const;

		Math::bbox GetLocalBoundingBox();

		bool Intersect(const Math::Ray& worldRay, Math::scalar& fout, Math::scalar fTolerance = N_TINY);

	protected:
		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		virtual void OnDestroy();

		virtual void OnRenderSceneChanged();
		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

		void _BuildSimpleRenderObject();
		void _SetMaterial();
		bool _BuildSimpleRenderable();
		void _UpdateBoundingBox();
		void _SetImage(const GPtr<Sprite::SpriteImage>& texture);
		void _ClearRenderable();

		typedef SpriteRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> RenderObjectPtr;

		void _DeattachRenderObject();

		void _AttachRenderObject();

		RenderObjectPtr mRenderObject;

		Sprite::SpriteInfo mSpriteInfo;
	};
}



#endif // SPRITEBASERENDERCOMPONENT_H_
