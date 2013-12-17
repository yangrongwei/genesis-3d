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
#ifndef __feature_H__
#define __feature_H__

#include "core/refcounted.h"
#include "appframework/manager.h"
#include "core/singleton.h"
#include "util/commandlineargs.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace App
{

	class Feature : public Core::RefCounted    
	{
		__DeclareClass(Feature);
	public:
		/// constructor
		Feature();
		/// destructor
		virtual ~Feature();

		/// called from GameServer::AttachGameFeature()
		virtual void OnActivate();
		/// called from GameServer::RemoveGameFeature()
		virtual void OnDeactivate();
		/// return true if Component is currently active
		bool IsActive() const;

		/// called from within GameServer::Load() after attributes are loaded
		virtual void OnLoad();
		/// called from within GameServer::Save() before attributes are saved back to database
		virtual void OnSave();

		/// called from within GameServer::Start() after OnLoad when the complete world exist
		virtual void OnStart();
		/// called from within GameServer::Stop() before OnLoad when the complete world stop
		virtual void OnStop();


		/// called on begin of frame
		virtual void OnBeginFrame();    
		/// called in the middle of the feature trigger cycle
		virtual void OnFrame();
		/// called at the end of the feature trigger cycle
		virtual void OnEndFrame();

		/// called when game debug visualization is on
		virtual void OnRenderDebug();


		/// attach a manager to the game world
		virtual void AttachManager(const GPtr<Manager>& manager);
		/// remove a manager from the game world
		virtual void RemoveManager(const GPtr<Manager>& manager);

		/// set command line args
		void SetCmdLineArgs(const Util::CommandLineArgs& a);
		/// get command line args
		const Util::CommandLineArgs& GetCmdLineArgs() const;

		/// set flag for rendering debug information
		void SetRenderDebug(bool b);
		/// get flag for rendering debug information
		bool HasRenderDebug() const;    

		/// get the name of feature
		const Util::String& GetFeatureName() const;

	protected:

		Util::Array<GPtr<Manager> > mManagers;
		bool mActive;
		bool mRenderDebug;
		Util::String mFeatureName;

		// cmdline args for configuration from cmdline
		Util::CommandLineArgs mArgs;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline bool
		Feature::IsActive() const
	{
		return this->mActive;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		Feature::SetCmdLineArgs(const Util::CommandLineArgs& a)
	{
		this->mArgs = a;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Util::CommandLineArgs&
		Feature::GetCmdLineArgs() const
	{
		return this->mArgs;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Util::String&
		Feature::GetFeatureName() const
	{
		return this->mFeatureName;
	}

} // namespace FeatureUnit
//------------------------------------------------------------------------------






#endif // __feature_H__




