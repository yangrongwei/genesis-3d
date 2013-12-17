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
#ifndef __sceneschedulemanager_H__
#define __sceneschedulemanager_H__

#include "appframework/manager.h"
#include "appframework/scene.h"
#include "core/singleton.h"

namespace Graphic
{
	class RenderScene;
}

namespace App
{

	class SceneScheduleManager: public App::Manager
	{
		__DeclareClass(SceneScheduleManager);
		__DeclareThreadSingleton(SceneScheduleManager);
	public:
		typedef GPtr<Scene> ScenePtr;
		typedef Util::Array<ScenePtr> Scenes;
		SceneScheduleManager();

		virtual ~SceneScheduleManager();

		virtual void OnBeginFrame();

		void Open();

		void Close();

		ScenePtr OpenScene(const Util::String& sceneName, bool newScene, bool privateScene = false);

		bool SaveScene(const Util::String& sceneFile );

		bool SaveScene(const Util::String& sceneFile, int iFileType);

		bool CloseScene(const Util::String& sceneName);

		bool CloseScene(ScenePtr& scene);

		void CloseAllScenes();

		ScenePtr GetScene(const Util::String& sceneName) const;

		const ScenePtr& GetMainScene(void) const;

		// internal call.
		Graphic::RenderScene* _GetMainRenderScene() const;

	protected:
		bool _SetMainScene(const Util::String& sceneName);

		GPtr<Scene> mMainScene;
		Graphic::RenderScene* mMainRenderScene;
		Scenes mScenes;
		Scenes mScenesDelayDel;
	};
	//------------------------------------------------------------------------
	inline
	const GPtr<Scene>&
	SceneScheduleManager::GetMainScene(void) const
	{
		return mMainScene;
	}

	inline
	Graphic::RenderScene*
	SceneScheduleManager::_GetMainRenderScene() const
	{
		return mMainRenderScene;
	}
}








#endif // __sceneschedulemanager_H__
