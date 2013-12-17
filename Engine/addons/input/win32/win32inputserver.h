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
#ifndef __win32inputserver_H__
#define __win32inputserver_H__


#include "core/singleton.h"
#include "input/base/inputserverbase.h"


namespace Win32Input
{
	class Win32HardwareInputSource;
	class Win32WindowInputSource;
}

//------------------------------------------------------------------------------
namespace Win32Input
{
class Win32InputServer : public Input::InputServerBase
{
    __DeclareClass(Win32InputServer);
public:
    /// constructor
    Win32InputServer();
    /// destructor
    virtual ~Win32InputServer();

    /// open the input server
    void Open();
    /// close the input server
    void Close();
    /// call after processing window events (reads DInput raw mouse events)
    void OnFrame();

    /// get the current mouse movement
    const Math::float2& GetMouseMovement() const;

	// set the current mouse movement
	void SetMouseMovement( const Math::float2& mouseMovement );

protected:

    Math::float2 mMouseMovement;
};

//------------------------------------------------------------------------------
/**
*/
inline const Math::float2&
Win32InputServer::GetMouseMovement() const
{
    return this->mMouseMovement;
}
//------------------------------------------------------------------------
inline 
void 
Win32InputServer::SetMouseMovement( const Math::float2& mouseMovement )
{
	mMouseMovement = mouseMovement;
}

} // namespace Win32Input
//------------------------------------------------------------------------------





#endif // __win32inputserver_H__

