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
#include "ActiveLight.h"
#include "foundation/math/intersection.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Renderable/RenderObject.h"
namespace Graphic
{
	using namespace Math;

	ActiveLightManager::ActiveLightManager()
	{

	}

	ActiveLightManager::~ActiveLightManager()
	{

	}
	void ActiveLightManager::_reset()
	{
		mActiveLights.Clear();
		mAttLightBeginIndex = 0;
		mTempLightBlock.Clear();
		mTempObj = NULL;
	}

	void ActiveLightManager::CameraCull(Camera* camera)
	{
		_reset();
		switch(camera->GetCameraOrder())
		{
		case eCO_Main:
			{
				break;
			}
		default:
			{
				return;
			}
		}


		frustum view_frustum;
		view_frustum.setmatrix(camera->GetViewProjTransform());

		float4 camera_pos = camera->GetTransform().get_position();
		float4 view_dir = -camera->GetTransform().get_zaxis();
		view_dir = float4::normalize(view_dir);
		plane camera_plane(camera_pos, view_dir);
		float zfar = camera->GetCameraSetting().GetZFar();

		RenderScene* camera_scene = camera->GetRenderScene();

		const RenderScene::Lights& lights = camera_scene->GetLights();

		RenderScene::Lights::Iterator it = lights.Begin();
		RenderScene::Lights::Iterator end = lights.End();
		// sort the light type, the first of them is sunlight , then the directional light
		// others the attenuation lights
		for( ; it != end; ++it )
		{
			Light* light = *it;
			if (!light->IsEnabled() 
				|| light->GetLightmapType() == Light::eLM_JustForBaked ) //
			{
				continue;
			}
			Light::LightType lightType = light->GetLightType();

			// sort the light type, the first of them is sunlight , then the directional light
			// others the attenuation lights
			if (Light::eSunLight == lightType || Light::eDirectionalLight == lightType)
			{			
				ActiveLightInfo& outLight = mActiveLights.PushBack();
				_setActiveDirectionallight(light, outLight);
				continue;
			}

			float4 temp = light->GetTransform().get_position();
			point lightPos(temp.x(), temp.y(), temp.z());
			float lightRange = light->GetLightRange();

			if(Intersection::Intersect(sphere(lightPos, lightRange), view_frustum))
			{
				float viewDistance = camera_plane.distance(lightPos);

				if (Light::ePointLight == lightType)
				{
					ActiveLightInfo& outLight = mActiveLights.PushBack();
					outLight.light = light;
					vector boxSize(lightRange, lightRange, lightRange);
					outLight.boundingBox = bbox(lightPos, boxSize);
				}
				else if (Light::eSpotLight == lightType)
				{
					Pyramid bounds;
					_buildPyramid(*light, bounds);
					bbox box(bounds.points[0], bounds.points[0]);

					for (int i = 1; i < Pyramid::PointCount; i++)
						box.extend(bounds.points[i]);

					if (ClipStatus::Outside != view_frustum.clipstatus(box))
					{
						ActiveLightInfo& outLight = mActiveLights.PushBack();
						outLight.boundingBox = box;
						outLight.light = light;
					}
				}
				else //Light::eInvailidLightType
				{
					n_warning("unknown light type: %d.", (int)lightType);
				}
				
			}

		}
	}
	const ActiveLightInfo* ActiveLightManager::FindSunLight() const
	{
		if (mActiveLights.Count())
		{
			if (Light::eSunLight == mActiveLights[0].light->GetLightType())
			{
				return &mActiveLights[0];
			}
		}
		return NULL;
	}


	const TempLightBlock& ActiveLightManager::FindActiveAttLights(const RenderObject* obj, int max_count, bool& bUsedForLightmap) const
	{
		bUsedForLightmap = false;

		if (mTempObj == obj)
		{
			return mTempLightBlock;
		}
		else
		{
			mTempObj = obj;
			mTempLightBlock.Clear();
		}

		bUsedForLightmap = obj->IsUseLM() && obj->IsLMHandleValid();
		// 在lightmap模式下,动态灯光只支持一盏
		max_count = bUsedForLightmap? Math::n_min(1,max_count) :max_count;

		int a_count = mActiveLights.Count();
		int index = mAttLightBeginIndex;

		if ( index < a_count )
		{
			bbox worldBox;
			obj->GetBoudingBoxInWorld(worldBox);
			while( index < a_count && mTempLightBlock.Count() < max_count)
			{
				ActiveLightInfo& alight = mActiveLights[index];
				bool  bRealtimeLight = (alight.light->GetLightmapType() == Light::eLM_NoBaked);

				if ( ((bUsedForLightmap && bRealtimeLight) || (!bUsedForLightmap))
					&& _inLight(obj, worldBox, mActiveLights[index]))
				{
					mTempLightBlock.PushBack(&alight);
				}
				++index;
			}
		}
		return mTempLightBlock;
	}

	void ActiveLightManager::_buildPyramid (const Light& light, Pyramid& outPyramid)
	{
		//默认光照方向为z轴负方向。所以distZ取负。
		float negativeZ = -light.GetLightRange();
		float farRadius = negativeZ * n_clamp(n_tan(n_acos(light.GetCosHalfOuterAngle())), 0.0f, 1.0f);

		outPyramid.points[0] = light.GetTransform().get_position();
		outPyramid.points[1] = matrix44::transform(light.GetTransform(), float4(-farRadius,-farRadius, negativeZ, 1.0f) );
		outPyramid.points[2] = matrix44::transform(light.GetTransform(), float4( farRadius,-farRadius, negativeZ, 1.0f) );
		outPyramid.points[3] = matrix44::transform(light.GetTransform(), float4( farRadius, farRadius, negativeZ, 1.0f) );
		outPyramid.points[4] = matrix44::transform(light.GetTransform(), float4(-farRadius, farRadius, negativeZ, 1.0f) );
	}

	bool ActiveLightManager::_inLight(const RenderObject* renderObj, const Math::bbox& worldBox, const ActiveLightInfo& actLight)
	{
		bool ret = false;
		const Light* light = actLight.light;

		switch(light->GetLightType())
		{
		case Light::eSunLight:
		case Light::eDirectionalLight:
			{
				ret = true;
				break;
			}
		case  Light::ePointLight:
			{
				if(worldBox.intersects(actLight.boundingBox))//只是简单裁剪
				{
					//精细裁剪
					const bbox& localBox = renderObj->GetBoundingBox();
					matrix44 invMat44 = matrix44::inverse(renderObj->GetTransform());

					sphere sph(actLight.light->GetLightPos(), actLight.light->GetLightRange());
					sph.transform(invMat44);
					ret = Intersection::Intersect(localBox, sph);

				}
				break;
			}
		case  Light::eSpotLight:
			{
				if(worldBox.intersects(actLight.boundingBox))//只是简单裁剪
				{
					//精细裁剪.暂时包围盒裁剪方法来裁剪聚光灯。其实可以用视锥来做精细的裁剪，不过效率会略低。有待评估。
					const bbox& localBox = renderObj->GetBoundingBox();
					matrix44 invMat44 = matrix44::inverse(renderObj->GetTransform());
					bbox box = actLight.boundingBox;
					box.transform(invMat44);

					ret = localBox.intersects(box);

				}
				break;
			}
		}

		return ret;
	}

	void ActiveLightManager::_setActiveDirectionallight(Light* light, ActiveLightInfo& alight)
	{
		alight.light = light;
		alight.boundingBox = bbox(point::origin(), vector(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()));
		//衰减光源的起始位置。现在默认在灯光列表里，无衰减的光源都是在列表的最前面的。
		//所以最后一个方向光的下一个灯光必然是衰减光源的起始
		mAttLightBeginIndex = mActiveLights.Count();
	}
}