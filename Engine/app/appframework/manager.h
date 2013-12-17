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
#ifndef __manager_H__
#define __manager_H__

#include "messaging/dispatcher.h"

//------------------------------------------------------------------------------
namespace App
{
class Manager : public Messaging::Dispatcher
{
    __DeclareClass(Manager);
public:
    /// constructor
    Manager();
    /// destructor
    virtual ~Manager();

    /// called when attached to game server
    virtual void OnActivate();
    /// called when removed from game server
    virtual void OnDeactivate();
    /// return true if currently active
    bool IsActive() const;
    /// called before frame by the game server
    virtual void OnBeginFrame();
    /// called per-frame by the game server
    virtual void OnFrame();
    /// called after frame by the game server
    virtual void OnEndFrame();
    /// called after loading game state
    virtual void OnLoad();
    /// called before saving game state
    virtual void OnSave();
    /// called by App::Server::Start() when the world is started
    virtual void OnStart();
	/// called by App::Server::Start() when the world is stopped
	virtual void OnStop();
    /// render a debug visualization 
    virtual void OnRenderDebug();

private:
    bool mIsActive;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
Manager::IsActive() const
{
    return this->mIsActive;
}

}; // namespace Game
//------------------------------------------------------------------------------





#endif // __manager_H__



 
    
    