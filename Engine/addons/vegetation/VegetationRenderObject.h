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

#ifndef _VEGETATIONRENDEROBJECT_H_
#define _VEGETATIONRENDEROBJECT_H_
#include "graphicsystem/Renderable/RenderObject.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "vegetation/VegetationRenderable.h"

namespace Vegetation
{
	class VegetationObject;
	class VegetationRenderObject : public Graphic::RenderObject
	{
		__DeclareSubClass(VegetationRenderObject, Graphic::RenderObject)
	public:
		typedef VegetationObject Owner;
		typedef VegetationRenderable RenderableType;
		VegetationRenderObject();
		virtual ~VegetationRenderObject();
		virtual void AddToCollection(Graphic::RenderDataCollection* colection);
		virtual void Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);
		void SetOwner(Owner* owner, Graphic::LayerID layerID);
		Owner* GetOwner() const;
	protected:	
		void _RenderGrass(const RenderableType* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);
		void _RenderTree(const RenderableType* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);
		void _Render(const RenderableType* renderable, Graphic::RenderPassType passType, const RenderBase::PrimitiveHandle& handle, 
			IndexT firstVert, SizeT numVert, IndexT firstIndex, SizeT numIndex, const Graphic::Material* customizedMaterial);
		Owner* mOwner;
	};

	inline void VegetationRenderObject::SetOwner(Owner* owner, Graphic::LayerID layerID)
	{
		mOwner = owner;
		SetLayerID(layerID);
	}

	inline VegetationRenderObject::Owner* VegetationRenderObject::GetOwner() const
	{
		return mOwner;
	}
}

#endif //_VEGETATIONRENDEROBJECT_H_