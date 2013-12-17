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
#ifndef _SPRITERENDEROBJECT_H_
#define _SPRITERENDEROBJECT_H_

#include "util/stringatom.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "graphicsystem/Renderable/Renderable.h"
#include "graphicfeature/components/apprenderobject.h"

namespace Sprite
{
	class SpriteImage;
}

namespace App
{
	class SpriteRenderObject;
	class SpriteBaseRenderComponent;

	class SpriteRenderable : public Graphic::Renderable
	{
	public:
		SpriteRenderable();
		~SpriteRenderable();
		void RenderForward(Graphic::RenderPassType surType, const RenderBase::PrimitiveHandle& primHandle, const Graphic::Material* custom) const;
		void SetImage(const GPtr<Sprite::SpriteImage>& texture);
	protected:
		GPtr<Sprite::SpriteImage> mImage;
	};

	inline void SpriteRenderable::SetImage(const GPtr<Sprite::SpriteImage>& texture)
	{
		mImage = texture;
	}


	class SpriteRenderObject : public AppRenderObject
	{
		__DeclareSubClass(SpriteRenderObject, AppRenderObject)
	public:
		typedef SpriteRenderable RenderableType;
		typedef SpriteBaseRenderComponent Owner;
		SpriteRenderObject();
		virtual ~SpriteRenderObject();
		//The overrided fuctions of Graphic::RenderObject 
		virtual void Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);
	private:
		Owner* getOwner() const;
	};
	inline SpriteRenderObject::Owner* SpriteRenderObject::getOwner() const
	{
		return GetOwner<Owner>();
	}

	
}


#endif //_SPRITERENDEROBJECT_H_