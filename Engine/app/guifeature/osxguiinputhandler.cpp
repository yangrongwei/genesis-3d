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
#ifdef __OSX__
#include "input/input_stdneb.h"
#include "osxguiinputhandler.h"
#include "input/inputserver.h"

#include "gui.h"
#include "myguiplatforms/include/MyGUI_GenesisInput.h"
namespace Input
{
	__ImplementClass(Input::OSXGuiInputHandler, 'OGIH', Input::InputTouchScreen);
    
	using namespace Input;
	//------------------------------------------------------------------------
	OSXGuiInputHandler::OSXGuiInputHandler()
	{
        
	}
	//------------------------------------------------------------------------
	OSXGuiInputHandler::~OSXGuiInputHandler()
	{
        
	}
	//------------------------------------------------------------------------
	bool OSXGuiInputHandler::OnEvent( const Input::InputEvent& inputEvent )
	{        
        
		MyGUI::GenesisInputManager* gui_input = MyGUI::GenesisInputManager::getInstancePtr();
		if (!gui_input)
		{
			return false;
		}
        
        
		bool ret = false;
		static int mouse_z = 0;
		switch (inputEvent.GetType())
		{
                // reset input handler if another one begins to capture
            case InputEvent::TouchMotionDown:
			{
				IndexT idxTouch(0);
                
				//«ø÷∆≤˙…˙“ª∏ˆmove ¬º˛
				const Math::float2& pos_n = inputEvent.GetNormTouchPos(idxTouch);
				if ( !(pos_n.x() < 0.0f || pos_n.x() > 1.0f || pos_n.y() < 0.0f || pos_n.y() > 1.0f))
				{
					gui_input->injectMouseMove(pos_n.x(), pos_n.y(), mouse_z);
				}
				
				ret |= gui_input->injectMousePress(pos_n.x(), pos_n.y(), MyGUI::MouseButton::Left);
			}
                break;
            case InputEvent::TouchMotionUp:
			{
				IndexT idxTouch(0);
				const Math::float2&  pos = inputEvent.GetNormTouchPos(idxTouch);
				ret |= gui_input->injectMouseRelease(pos.x(), pos.y(), MyGUI::MouseButton::Left);
			}
                break;
            case InputEvent::TouchMotionMove:
			{
				IndexT idxTouch(0);
				const Math::float2& pos_n = inputEvent.GetNormTouchPos(idxTouch);
				if ( pos_n.x() < 0.0f || pos_n.x() > 1.0f || pos_n.y() < 0.0f || pos_n.y() > 1.0f)
				{
					break;
				}
				ret |= gui_input->injectMouseMove(pos_n.x(), pos_n.y(), mouse_z);
			}
                break;
            default:
                break;
		}
		
        
		return !ret;
	}
    
}
#endif