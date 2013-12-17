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
#ifndef __RENDERSCENE_H
#define __RENDERSCENE_H

#include "foundation/core/refcounted.h"
#include "foundation/util/array.h"
namespace Vis
{
	class VisServer;
	class VisQuery;
	class VisEntity;
}
namespace Graphic
{
	extern const Math::float4 AmbientColorOfDefaultLight;

	class RenderObject;
	class Camera;
	class Light;

	class IRenderScene
	{
	public:
		virtual ~IRenderScene() {};

		// internal call
		virtual void _UpdateVisEntity(const GPtr<Vis::VisEntity>& visEnt) = 0;
		virtual void _AddRenderObject(RenderObject* obj) = 0;
		virtual void _RemoveRenderObject(RenderObject* obj) = 0;
		// internal call
		virtual void _AddRenderObjectNotCull(RenderObject* obj) = 0;
		virtual void _RemoveRenderObjectNotCull(RenderObject* obj) = 0;
	};



	class RenderScene : public IRenderScene
	{
	public:
		struct Environment
		{
			Math::float4 fogColor;
			Math::float4 fogParam;
			Math::float4 ambientColor;
			Math::float4 softShadowParam;
			Math::float4 shadowStrength;//nerver be used. defined in light class.
			Math::float3 graivty;
			float skinWidth;
			float bounce;
			float sleepVel;
			float sleepAngular;
			float maxAngular;
			Util::String defaultMat;
			Util::Array<uint> layerIDArray;
			Environment();
		};
		typedef Util::Array<Light*> Lights;
		RenderScene();
		virtual ~RenderScene();

		void Setup();
		void Destroy();

		const Util::Array<RenderObject*>& GetNotCullRenderObjects() const;

		GPtr<Vis::VisQuery> Cull(const Camera& camera);
		GPtr<Vis::VisQuery> Cull(const Math::matrix44& viewProj, const Math::float4& pos);


		Light* GetSunLight() const;
		const Lights& GetLights() const;
		Lights& GetLights();

		void SetEnvironment(Environment* environment);
		Environment* GetEnvironment() const;

		void ApplyEnvironment() const;

		// internal call
		void _AddLight(Light* light);
		void _RemoveLight(Light* light);
		void _SortLights();

		virtual void _UpdateVisEntity(const GPtr<Vis::VisEntity>& visEnt );
		virtual void _AddRenderObject(RenderObject* obj);
		virtual void _RemoveRenderObject(RenderObject* obj);

		virtual void _AddRenderObjectNotCull(RenderObject* obj);
		virtual void _RemoveRenderObjectNotCull(RenderObject* obj);

	private:
		GPtr<Vis::VisServer>	mVisServer;
		Util::Array<RenderObject*>	mNotCullRenderObjects;
		Lights mLights;
		Environment* mEnvironment;
	};

	inline const Util::Array<RenderObject*>& RenderScene::GetNotCullRenderObjects() const
	{
		return mNotCullRenderObjects;
	}

	inline void RenderScene::SetEnvironment(Environment* environment)
	{
		mEnvironment = environment;
	}

	inline RenderScene::Environment* RenderScene::GetEnvironment() const
	{
		return mEnvironment;
	}

	inline const RenderScene::Lights& RenderScene::GetLights() const
	{
		return mLights;
	}

	inline RenderScene::Lights& RenderScene::GetLights()
	{
		return mLights;
	}
}


#endif //__RENDERSCENE_H