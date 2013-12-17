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
#ifndef __SCRIPT_FEATURE_H__
#define __SCRIPT_FEATURE_H__

#include "appframework/feature.h"
#include "foundation/util/array.h"
#include "app/scriptfeature/inc/script_fwd_decl.h"

namespace App
{
	class ScriptInstance;
	class ScriptComponent;

class ScriptFeature : public App::Feature
{
		__DeclareClass(ScriptFeature);
		__DeclareImageSingleton(ScriptFeature);

	public:
		/// constructor
		ScriptFeature();
		/// destructor
		virtual ~ScriptFeature();
	public:
		/// call this method when this feature has been activated
		virtual void OnActivate();
		/// called from BaseGameFeature::DeactivateProperties()
		virtual void OnDeactivate();
		/// called before one frame
		virtual void OnBeginFrame();
		/// called on a frame every time 
		virtual void OnFrame();
		/// called every time when a frame is over
		virtual void OnEndFrame();
		/// called every time when game should be stoped
		virtual void OnStopped();
		/// called every time when game should be resumed
		virtual void OnResumed();
	public:
		/// add script instances to this feature
		void AttachScriptInstances(const Util::Array< GPtr<ScriptInstance> >& scriptInstances);
		/// add script components to this feature
		void AttachScriptCom(ScriptComponent* const pCom);

		/// remove script instances
		void RemoveScriptInstances(const ScriptInstances& scriptInstances);
		/// remove script component
		void RemoveScriptCom(ScriptComponent* const pCom);
		/// remove script general
		void RemoveScript(ScriptComponent* const pCom, const ScriptInstances& scriptInstances);
		/// attach script general
		void AttachScript(ScriptComponent* const pCom, const ScriptInstances& scriptInstances);
	protected:

		ScriptInstanceArraies m_ScriptInstances;
		Util::Array <ScriptComponent*>                    m_pScriptComs;
	};

}


#endif