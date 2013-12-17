/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
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
#ifndef __basegamefeature_H__
#define __basegamefeature_H__

#include "math/bbox.h"
#include "appframework/feature.h"
#include "appframework/actormanager.h"

#include "basegamefeature/managers/gameconfigmanger.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "basegamefeature/managers/timemanager.h"
#include "resource/resourceserver.h"
#include "resource/resourcemanager.h"
#include "serialization/serializeserver.h"




//----------------------------------------------------------------------------------------------
namespace App
{

	class BaseGameFeature : public App::Feature    
	{
		__DeclareClass(BaseGameFeature);
		__DeclareThreadSingleton(BaseGameFeature);    

	public:

		/// constructor
		BaseGameFeature();
		/// destructor
		virtual ~BaseGameFeature();

		// 加载*.atp文件。默认是actor.atp
		void LoadActorTemplate(const Util::String& templatePath = Util::String("asset:actor.atp") );

		/// called from BaseGameFeature::ActivateProperties()
		virtual void OnActivate();
		/// called from BaseGameFeature::DeactivateProperties()
		virtual void OnDeactivate();

		/// called on begin of frame
		virtual void OnBeginFrame();    
		/// called at the end of the feature trigger cycle
		virtual void OnEndFrame();
		/// called when game debug visualization is on
		virtual void OnRenderDebug();
		/// 
		virtual void OnFrame();

		virtual void OnStop();

		/// set optional world dimensions
		void SetWorldDimensions(const Math::bbox& box);

		/// get world dimensions
		const Math::bbox& GetWorldDimensions() const;

	protected:
		/// handle input keys
		void HandleInput();
		Math::bbox worldBox;

		GPtr<Resources::ResourceServer> mResServer;
		GPtr<Resources::ResourceManager> mResManager;
		GPtr<Serialization::SerializationServer> mSerializationServer;

		// managers
		GPtr<GameConfigManager> mGameCfgMgr;
		GPtr<SceneScheduleManager> mSceneScheduleMgr;
		GPtr<ActorManager> mActorMgr;
		GPtr<TimeManager> mTimeMgr;

	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
	BaseGameFeature::SetWorldDimensions(const Math::bbox& box)
	{
		this->worldBox = box;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::bbox&
	BaseGameFeature::GetWorldDimensions() const
	{
		return this->worldBox;
	}

} // namespace BaseGameFeature
//------------------------------------------------------------------------------










#endif // __basegamefeature_H__



