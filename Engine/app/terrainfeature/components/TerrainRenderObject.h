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

#ifndef _TERRAINRENDEROBJECT_H_
#define _TERRAINRENDEROBJECT_H_
#include "graphicfeature/components/apprenderable.h"
#include "graphicfeature/components/apprenderobject.h"
#include "resource/meshres.h"

namespace App
{
	class TerrainRenderComponent;
	class TerrainNode;

	class TerrainRenderObject : public AppRenderObject
	{
		__DeclareSubClass(TerrainRenderObject, AppRenderObject)
	public:
		typedef AppSimpleRenderable RenderableType;
		typedef TerrainRenderComponent Owner;

		TerrainRenderObject();
		virtual ~TerrainRenderObject();
		virtual void AddToCollection(Graphic::RenderDataCollection* collection);
		virtual void Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);
		void Set(Owner* comObject, TerrainNode* node, const Math::matrix44& world);
		TerrainNode* GetTerrainNode();

		virtual bool IsUseLM() const;
		virtual bool IsLMHandleValid() const;
		Resources::Index16Container::value_type* GetTerrainNodeIndexData();
		SizeT									 GetTerrainNodeIndexDataCount();

		const Resources::PositionData::Elem*	 GetTerrainNodePosData();
		SizeT									 GetTerrainNodePosCount();

	protected:
		TerrainNode* m_TerrainNode;
	private:
		Owner* getOwner() const;
	};

	//------------------------------------------------------------------------
	inline TerrainNode* TerrainRenderObject::GetTerrainNode(){
		return m_TerrainNode;
	}


}

#endif //_TERRAINRENDEROBJECT_H_