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
#ifndef _SCREENMESHRENDEROBJECT_H_
#define _SCREENMESHRENDEROBJECT_H_
#include "graphicfeature/components/apprenderobject.h"
#include "graphicfeature/components/apprenderable.h"
namespace App
{
	class Mesh2dRenderComponent;
	class AppRenderable;
	class ScreenMeshRenderObject : public AppRenderObject
	{
		__DeclareSubClass(ScreenMeshRenderObject,AppRenderObject);
	public:
		typedef AppRenderable RenderableType;
		ScreenMeshRenderObject();
		virtual ~ScreenMeshRenderObject();

		//The overrided fuctions of Graphic::RenderObject 
		virtual void Render(const Graphic::Renderable* renderable, Graphic::RenderPassType passType, const Graphic::Material* customizedMaterial);

	protected:
		int mObjIndex;
	private:
		Mesh2dRenderComponent* getOwner();
	};
	inline Mesh2dRenderComponent* ScreenMeshRenderObject::getOwner()
	{
		return GetOwner<Mesh2dRenderComponent>();
	}
}
#endif //_MESH2dRENDEROBJECT_H_