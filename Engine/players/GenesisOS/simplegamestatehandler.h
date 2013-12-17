#pragma once

#include "appframework/statehandler.h"
#include "appframework/actor.h"
#include "graphicfeature/components/animationcomponent.h"

namespace iOSGame
{
	

	class SimpleStateHandler : public App::StateHandler
	{
		__DeclareClass(SimpleStateHandler);
	public:    

		/// constructor
		SimpleStateHandler();
		/// destructor
		virtual ~SimpleStateHandler();

		/// called when the state represented by this state handler is entered
		virtual void OnStateEnter(const Util::String& prevState);
		/// called when the state represented by this state handler is left
		virtual void OnStateLeave(const Util::String& nextState);
		/// called each frame as long as state is current, return new state
		virtual Util::String OnFrame();

		/// set level filename, required by setup mode LoadLevel
		void SetSceneName(const Util::String& n);
		/// get level name
		const Util::String& GetSceneName() const;

		bool ResetScene(const char* strSceneName);
		void HeldScene();

	private:    
		Util::String mSceneName;

		App::Actor::FastId mMeshActorID;
		Util::String mCurMeshName;
		Util::String mCurShaderName;
		Util::String mCurTexName;

	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		SimpleStateHandler::SetSceneName(const Util::String& n)
	{
		this->mSceneName = n;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Util::String&
		SimpleStateHandler::GetSceneName() const
	{

		return this->mSceneName;
	}
}