/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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

#pragma once
//------------------------------------------------------------------------------
/**
    @class Base::GameContentServerBase
    
    The game content server initializes access to game content on console
    platforms. The GameContentServer must be created by the main thread
    before the first IoServer is created.
*/
#include "core/refcounted.h"
#include "core/singleton.h"

//------------------------------------------------------------------------------
namespace Base
{
class GameContentServerBase : public Core::RefCounted
{
    __DeclareClass(GameContentServerBase);
    __DeclareImageSingleton(GameContentServerBase);
public:
    /// constructor
    GameContentServerBase();
    /// destructor
    virtual ~GameContentServerBase();

    /// set human readable game title
    void SetTitle(const Util::String& title);
    /// get human readable game title
    const Util::String& GetTitle() const;
    /// set title id
    void SetTitleId(const Util::String& titleId);
    /// get title id
    const Util::String& GetTitleId() const;
    /// set title version
    void SetVersion(const Util::String& version);
    /// get title version
    const Util::String& GetVersion() const;

    /// setup the object
    void Setup();
    /// discard the object
    void Discard();
    /// return true if object has been setup
    bool IsValid() const;

protected:
    Util::String title;
    Util::String titleId;
    Util::String version;
    bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
GameContentServerBase::IsValid() const
{
    return this->isValid;
}

//------------------------------------------------------------------------------
/**
*/
inline void
GameContentServerBase::SetTitle(const Util::String& t)
{
    this->title = t;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
GameContentServerBase::GetTitle() const
{
    return this->title;
}

//------------------------------------------------------------------------------
/**
*/
inline void
GameContentServerBase::SetTitleId(const Util::String& tid)
{
    this->titleId = tid;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
GameContentServerBase::GetTitleId() const
{
    return this->titleId;
}

//------------------------------------------------------------------------------
/**
*/
inline void
GameContentServerBase::SetVersion(const Util::String& v)
{
    this->version = v;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
GameContentServerBase::GetVersion() const
{
    return this->version;
}

} // namespace Base
//------------------------------------------------------------------------------

