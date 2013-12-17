#include "stdneb.h"
#include "simplegamestatehandler.h"
#include "basegamefeature/basegamefeature.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "graphicfeature/graphicsfeature.h"
#include "appframework/gameserver.h"
#include "appframework/scene.h"
#include "appframework/actor.h"

#include "input/inputserver.h"
#include "input/inputkeyboard.h"
#include "app/inputfeature/inputfeature.h"
#include "input/inputkey.h"

#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Light/Light.h"
#include "graphicsystem/Camera/Camera.h"





namespace iOSGame
{
	__ImplementClass(iOSGame::SimpleStateHandler, 'SSHD', App::StateHandler);

	using namespace Graphic;
	using namespace App;

	//------------------------------------------------------------------------------
	/**
	*/
	SimpleStateHandler::SimpleStateHandler()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	SimpleStateHandler::~SimpleStateHandler()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	This method is called when the state associated with this state handler
	is entered. The parameter indicates the previously active state.

	@param  prevState   previous state
	*/
	void
		SimpleStateHandler::OnStateEnter(const Util::String& prevState)
	{
		

		App::BaseGameFeature::Instance()->SetRenderDebug(true);

		// setup the game
		// start game world
		App::GameServer::Instance()->Start();
		App::SceneScheduleManager* pSceneSchedule = App::SceneScheduleManager::Instance();

		pSceneSchedule->OpenScene(  GetSceneName() , false );
		GPtr<App::Scene> pScene = pSceneSchedule->GetScene();
		n_assert( pScene );

	}

	//------------------------------------------------------------------------------
	/**
	This method is called when the state associated with this state handler
	is left. The parameter indicates the next active state.

	@param  nextState   next state
	*/
	void
		SimpleStateHandler::OnStateLeave(const Util::String& nextState)
	{
		// stop game world
		App::GameServer::Instance()->Stop();
	}

	//------------------------------------------------------------------------------
	/**
	This method is called once a frame while the state is active. The method
	must return a state identifier. If this is different from the current
	state, a state switch will occur after the method returns. 

	@return     a state identifier
	*/
	Util::String
		SimpleStateHandler::OnFrame()
	{
		if( App::GameServer::Instance()->IsQuitRequested() )
		{
			App::SceneScheduleManager* pSceneSchedule = App::SceneScheduleManager::Instance();
			pSceneSchedule->CloseScene();
			return "Exit";
		}
		else
		{																
			//----------------------------------------------------------------------------------------
			return this->GetName();
		}
	}
	
			
		

} // namespace Application
