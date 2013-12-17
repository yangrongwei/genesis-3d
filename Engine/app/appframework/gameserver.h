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
#ifndef __gameserver_H__
#define __gameserver_H__

#include "core/refcounted.h"
#include "core/ptr.h"
#include "math/bbox.h"
#include "core/singleton.h"
#include "appframework/feature.h"
#include "util/dictionary.h"
//#include "debug/debugtimer.h"


//------------------------------------------------------------------------------
namespace App
{
class Actor;
class Manager;

class GameServer : public Core::RefCounted
{
    __DeclareClass(GameServer);
    __DeclareThreadSingleton(GameServer);
public:
    /// constructor
    GameServer();
    /// destructor
    virtual ~GameServer();

    /// open the game world
    bool Open();
    /// close the game world
    void Close();
    /// start the game world
    bool Start();
    /// has the game world already started
    bool HasStarted() const;
    /// stop the game world
    void Stop();
    /// trigger the game world
    void OnFrame();
	void OnFrameWithoutGraphics();
	/// stop the game in Editor
	void StopGameInEditor();
   
    /// call OnLoad on all game features
    void NotifyGameLoad();
    /// call OnSave on all game features
    void NotifyGameSave();
        
    /// add game feature
    void AttachGameFeature(const GPtr<Feature>& feature);
    /// remove game feature
    void RemoveGameFeature(const GPtr<Feature>& feature);
    /// is feature attached
    bool IsFeatureAttached(const Util::String& stringName) const;

    /// is quit requested
    bool IsQuitRequested() const;
    /// request quit
    void SetQuitRequested();

#ifdef __GENESIS_EDITOR__
	
	bool StartInEditor();

#endif

protected:
	template<bool _graphic>
	void onFrame();

    bool mOpen;
    bool mStarted;
    bool mQuitRequested;
    //Util::Array<GPtr<Feature> > mGameFeatures;
	typedef Util::Dictionary< Util::String, GPtr<Feature> > GameFeatures;
	GameFeatures mGameFeatures;
	GPtr<Feature> mDebugRenderFeature;

	bool mbScript;
	bool mbPhysics;
	bool mbAnimation;
	bool mbParticle;
	bool mbNetwork;
	bool mbVegetaion;
	bool mbSound;
	bool mbFont;

    //_declare_timer(mGameServerOnFrame);
};

//------------------------------------------------------------------------------
/**
*/
inline bool 
GameServer::IsQuitRequested() const
{
    return this->mQuitRequested;
}

//------------------------------------------------------------------------------
/**
*/
inline void 
GameServer::SetQuitRequested()
{
    this->mQuitRequested = true;
}

}; // namespace Game
//------------------------------------------------------------------------------

#endif //__gameserver_H__
