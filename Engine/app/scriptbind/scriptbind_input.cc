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
#include "stdneb.h"
#include "input/inputmouse.h"
#include "input/inputkeyboard.h"
#include "input/inputserver.h"
#include "input/inputkey.h"
#include "app/inputfeature/inputfeature.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"

#if defined ANDROID
#include "input/android/androidinputserver.h"
#include "input/inputtouchscreen.h"
#elif defined __OSX__
#include "input/OSX/OSXinputserver.h"
#include "input/inputtouchscreen.h"
#endif

namespace App
{
	void ICallReg_ScriptRuntime_Input( void );
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_KeyDown( int iKeyCode)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
		return (mono_bool)keyboard->KeyDown((Input::InputKey::Code)iKeyCode);	
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_KeyUp( int iKeyCode)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
		return (mono_bool)keyboard->KeyUp((Input::InputKey::Code)iKeyCode);	
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_KeyPressed( int iKeyCode)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
		return (mono_bool)keyboard->KeyPressed((Input::InputKey::Code)iKeyCode);	
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_MouseButtonDown( int iBtn)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		return (mono_bool)mouse->ButtonDown( (Input::InputMouseButton::Code)iBtn );
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_MouseButtonPressed( int iBtn)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		return (mono_bool)mouse->ButtonPressed( (Input::InputMouseButton::Code)iBtn );
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_MouseButtonUp( int iBtn)
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		return (mono_bool)mouse->ButtonUp( (Input::InputMouseButton::Code)iBtn );
	}
	//------------------------------------------------------------------------
	static void ICall_Input_GetScreenPosition(Math::float2& outFloat2)
	{
#ifdef __OSX__
        return;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		outFloat2 = mouse->GetScreenPosition();
	}
	//------------------------------------------------------------------------
	static void ICall_Input_MouseGetMovement( Math::float2& outFloat2 )
	{
#ifdef __OSX__
        return;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		outFloat2 = mouse->GetMovement();
	}
   	//------------------------------------------------------------------------
	static mono_bool ICall_Input_MouseWheelForward()
	{
#ifdef __OSX__
        return 0;
#endif
       const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
	   return (mono_bool)mouse->WheelForward();
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_Input_MouseWheelBack()
	{
#ifdef __OSX__
        return 0;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		return (mono_bool)mouse->WheelBackward();
	}
	//------------------------------------------------------------------------
	static int ICall_Input_GetScreenTouchCount()
	{
#ifdef ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetTouchCount();
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetTouchCount();
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return 0;
#endif
	}

	static int ICall_Input_GetScreenTouchID(int index)
	{
#ifdef ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetTouchID(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetTouchID(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return 0;
#endif
	}

	static bool ICall_Input_IsFingerDown(int index)
	{
#ifdef ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerDown(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerDown(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return false;
#endif
	}

	static bool ICall_Input_IsFingerPressing(int index)
	{
#if ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerPressing(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerPressing(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return false;
#endif
	}

	static bool ICall_Input_IsFingerUp(int index)
	{
#if ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerUp(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->FingerUp(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return false;
#endif
	}

	static void ICall_Input_GetScreenTouchMovement(int index, Math::float2& moveMent)
	{
#if ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		moveMent = touchScreen->GetMovement(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		moveMent = touchScreen->GetMovement(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
#endif
	}

	static void ICall_Input_GetScreenTouchScreenPos(int index, Math::float2& screenPos)
	{
#if ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		screenPos = touchScreen->GetScreenPosition(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		screenPos = touchScreen->GetScreenPosition(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
#endif
	}

	static void ICall_Input_GetScreenTouchPixelPos(int index, Math::float2& pixelPos)
	{
#if ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		pixelPos = touchScreen->GetPixelPosition(index);
#elif defined __OSX__
        const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		pixelPos = touchScreen->GetPixelPosition(index);
#else
		n_warning("No Implemention on WIN32 ver.\n");
#endif
	}

	static int ICall_Input_GetCurrentKeyEventCount()
	{
#ifdef __OSX__
		return 0;
#endif
		const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
		return keyboard->GetCurrentEventCount();	
	}

	static void ICall_Input_GetCurrentKeyEvent(int index, int& code, int& event)
	{
#ifdef __OSX__
		return;
#endif
		const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
		Input::KeyEvent ke = keyboard->GetCurrentEvent(index);
		code = (int)ke.key;
		event = (int)ke.event;
	}

	static int ICall_Input_GetCurrentMouseButtonEventCount()
	{
#ifdef __OSX__
		return 0;
#endif
		const GPtr< Input::InputMouse> mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		return mouse->GetCurrentEventCount();
	}

	static void ICall_Input_GetCurrentMouseButtonEvent(int index, int& code, int& event)
	{
#ifdef __OSX__
		return;
#endif
		const GPtr< Input::InputMouse>& mouse =  App::InputFeature::Instance()->GetInputServer()->GetDefaultMouse();
		Input::MouseButtonEvent mbe = mouse->GetCurrentEvent(index);
		code = mbe.button;
		event = mbe.event;
	}

	static int ICall_Input_GetCurrentTouchEventCount()
	{
#ifdef ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetCurrentEventCount();
#elif defined __OSX__
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		return  touchScreen->GetCurrentEventCount();
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return -1;
#endif
	}

	static void ICall_Input_GetCurrentTouchEvent(int index, int& id, int& event)
	{
#ifdef ANDROID 
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<AndroidInput::AndroidInputServer>()->GetDefaultTouchScreen();
		Input::TouchEvent te = touchScreen->GetCurrentEvent(index);
		id = te.id;
		event = te.event;
#elif defined __OSX__
		const GPtr< Input::InputTouchScreen>& touchScreen = App::InputFeature::Instance()->GetInputServer().downcast<OSXInput::OSXInputServer>()->GetDefaultTouchScreen();
		Input::TouchEvent te = touchScreen->GetCurrentEvent(index);
		id = te.id;
		event = te.event;
#else
		n_warning("No Implemention on WIN32 ver.\n");
		return;
#endif
	}

	//------------------------------------------------------------------------
	void ICallReg_ScriptRuntime_Input( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.Input::ICall_Input_KeyDown"			     , (void*)&ICall_Input_KeyDown },
			{ "ScriptRuntime.Input::ICall_Input_KeyUp"			         , (void*)&ICall_Input_KeyUp },
			{ "ScriptRuntime.Input::ICall_Input_KeyPressed"			     , (void*)&ICall_Input_KeyPressed},
			{ "ScriptRuntime.Input::ICall_Input_MouseButtonDown"	     , (void*)&ICall_Input_MouseButtonDown},
			{ "ScriptRuntime.Input::ICall_Input_MouseButtonPressed"      , (void*)&ICall_Input_MouseButtonPressed},
			{ "ScriptRuntime.Input::ICall_Input_MouseButtonUp"		     , (void*)&ICall_Input_MouseButtonUp},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenPosition"	     , (void*)&ICall_Input_GetScreenPosition},
			{ "ScriptRuntime.Input::ICall_Input_MouseWheelBack"	         , (void*)&ICall_Input_MouseWheelBack},
			{ "ScriptRuntime.Input::ICall_Input_MouseWheelForward"	     , (void*)&ICall_Input_MouseWheelForward},
			{ "ScriptRuntime.Input::ICall_Input_MouseGetMovement"		 , (void*)&ICall_Input_MouseGetMovement},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenTouchCount"	 , (void*)&ICall_Input_GetScreenTouchCount},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenTouchID"		 , (void*)&ICall_Input_GetScreenTouchID},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenTouchMovement"	 , (void*)&ICall_Input_GetScreenTouchMovement},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenTouchScreenPos" , (void*)&ICall_Input_GetScreenTouchScreenPos},
			{ "ScriptRuntime.Input::ICall_Input_GetScreenTouchPixelPos"  , (void*)&ICall_Input_GetScreenTouchPixelPos},
			{ "ScriptRuntime.Input::ICall_Input_IsFingerDown"			 , (void*)&ICall_Input_IsFingerDown},
			{ "ScriptRuntime.Input::ICall_Input_IsFingerPressing"        , (void*)&ICall_Input_IsFingerPressing},
			{ "ScriptRuntime.Input::ICall_Input_IsFingerUp"				 , (void*)&ICall_Input_IsFingerUp},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentKeyEventCount"			, (void*)&ICall_Input_GetCurrentKeyEventCount},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentKeyEvent"					, (void*)&ICall_Input_GetCurrentKeyEvent},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentMouseButtonEventCount"	, (void*)&ICall_Input_GetCurrentMouseButtonEventCount},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentMouseButtonEvent"			, (void*)&ICall_Input_GetCurrentMouseButtonEvent},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentTouchEventCount"			, (void*)&ICall_Input_GetCurrentTouchEventCount},
			{ "ScriptRuntime.Input::ICall_Input_GetCurrentTouchEvent"				, (void*)&ICall_Input_GetCurrentTouchEvent},


		};


		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}