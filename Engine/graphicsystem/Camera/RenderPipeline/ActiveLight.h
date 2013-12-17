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
#ifndef _ACTIVELIGHT_H_
#define _ACTIVELIGHT_H_
#include "foundation/math/bbox.h"
#include "graphicsystem/base/DataCollection.h"
namespace Graphic
{

	struct Pyramid
	{
		enum 
		{ 
			PointCount = 5 
		};
		Math::point points[PointCount];
	};

	class Light;
	class Camera;
	class RenderObject;
	struct ActiveLightInfo 
	{
		Light* light;
		Math::bbox boundingBox;
	};
	typedef DataCollection<ActiveLightInfo> ActiveLightCollection;

	typedef DataCollection<const ActiveLightInfo*> TempLightBlock;
	class ActiveLightManager
	{
	public:
		ActiveLightManager();
		~ActiveLightManager();
		void CameraCull(Camera* camera);
		const ActiveLightInfo* FindSunLight() const;
		const TempLightBlock& FindActiveAttLights(const RenderObject* obj, int max_count, bool& bUsedForLightmap) const;
		ActiveLightCollection& GetActiveLights();
		int GetAttLightBeginIndex() const;
		int GetAttLightCount() const;
		int GetNotAttLightCount() const;
	private:
		void _reset();
		void _setActiveDirectionallight(Light* light, ActiveLightInfo& alight);
		static bool _inLight( const RenderObject* renderObj, const Math::bbox& worldBox, const ActiveLightInfo& actLight);
		static void _buildPyramid(const Light& light, Pyramid& outPyramid);
		ActiveLightCollection mActiveLights;
		int mAttLightBeginIndex;//the first index of attenuation light.in default light list, no attenuation lights always at the front of list.  
		mutable TempLightBlock mTempLightBlock;
		mutable const RenderObject* mTempObj;
	};

	inline ActiveLightCollection& ActiveLightManager::GetActiveLights()
	{
		return mActiveLights;
	}

	inline int ActiveLightManager::GetAttLightBeginIndex() const
	{
		return mAttLightBeginIndex;
	}
	inline int ActiveLightManager::GetAttLightCount() const
	{
		return mActiveLights.Count() - mAttLightBeginIndex;
	}
	inline int ActiveLightManager::GetNotAttLightCount() const
	{
		return mAttLightBeginIndex;
	}

}
#endif //_ACTIVELIGHT_H_

