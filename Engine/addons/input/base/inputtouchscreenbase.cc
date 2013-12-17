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
#if (ANDROID || __APPLE__)
#include "input/input_stdneb.h"
#include "input/base/inputtouchscreenbase.h"
#include "input/inputserver.h"
#include "input/inputmobileconfig.h"

namespace Input
{
	__ImplementClass(Input::InputTouchScreenBase, 'TSBS', Input::InputHandler);

InputTouchScreenBase::InputTouchScreenBase()
	: m_bInitialMovement(false)
{

}

InputTouchScreenBase::~InputTouchScreenBase()
{
	 n_assert(!this->IsAttached());
}

void InputTouchScreenBase::OnAttach(const GPtr<InputServerBase>& inputServer)
{
	InputHandler::OnAttach(inputServer);

	FingerState  initialState;
	Math::float2 initialPos(0.0f, 0.0f);

	for (IndexT i = 0; i < MaxPointerSupport; ++i)
	{
		m_FingerStates.Add(i, initialState);
	}
	
	m_PixelPositions.Reserve(MaxPointerSupport);
	m_ScreenPositions.Reserve(MaxPointerSupport);
	
	m_Movements.Reserve(MaxPointerSupport);

	m_bInitialMovement = true;
}

void InputTouchScreenBase::OnBeginFrame()
{
	InputHandler::OnBeginFrame();

	for (IndexT i = 0; i < m_FingerStates.Size(); ++i)
	{
		FingerState& state = m_FingerStates.ValueAtIndex(i);

		if (state.up)
		{
#ifndef __OSX__
			state.pressed = false;

			if (!m_ScreenPositions.IsEmpty() && !m_PixelPositions.IsEmpty())
			{
				m_ScreenPositions.Erase(m_FingerStates.KeyAtIndex(i));
				m_PixelPositions.Erase(m_FingerStates.KeyAtIndex(i));
			}
#else
            state.pressed = false;
            m_ScreenPositions.Clear();
            m_PixelPositions.Clear();
#endif
		}

		state.down = false;
		state.up = false;
		m_CurrentEvents.Clear();
	}



#ifndef __OSX__
#if _DEBUG
	for (IndexT i = 0; i < m_PixelPositions.Size(); ++i)
	{
		n_warning("INDEX:%d -- POSX:%f -- POSY:%f",i,m_PixelPositions.ValueAtIndex(i).x(),m_PixelPositions.ValueAtIndex(i).y());
	}
#endif
#endif
}

bool InputTouchScreenBase::OnEvent(const Input::InputEvent& inputEvent)
{
	switch (inputEvent.GetType())
	{
	case InputEvent::TouchMotionMove:
		{
			const SizeT count = inputEvent.GetPointersCount();

			for (IndexT i = 0; i < count; ++i)
			{
				const IndexT id = inputEvent.GetPointerId(i);
				m_FingerStates[id].pressed = true;
				UpdateFingerPositions(inputEvent.GetAbsTouchPos(id), inputEvent.GetNormTouchPos(id), id);
				m_CurrentEvents.Append(TouchEvent(id, inputEvent.GetType()));
			}
		}
		
		break;

	case InputEvent::TouchMotionDown:
		{
			const SizeT count = inputEvent.GetPointersCount();

			for (IndexT i = 0; i < count; ++i)
			{
				const IndexT id = inputEvent.GetPointerId(i);
				m_FingerStates[id].down    = true;
				UpdateFingerPositions(inputEvent.GetAbsTouchPos(id), inputEvent.GetNormTouchPos(id), id);
				m_CurrentEvents.Append(TouchEvent(id, inputEvent.GetType()));
			}
		}
		break;

	case InputEvent::TouchMotionUp:
		{
			const SizeT count = inputEvent.GetPointersCount();

			for (IndexT i = 0; i < count; ++i)
			{
				const IndexT id = inputEvent.GetPointerId(i);
				m_FingerStates[id].up = true;
				UpdateFingerPositions(inputEvent.GetAbsTouchPos(id), inputEvent.GetNormTouchPos(id), id);
				m_CurrentEvents.Append(TouchEvent(id, inputEvent.GetType()));
			}
		}
		break;

	case InputEvent::TouchMotionCancel:
		{
			const SizeT count = inputEvent.GetPointersCount();

			for (IndexT i = 0; i < count; ++i)
			{
				const IndexT id = inputEvent.GetPointerId(i);
				m_FingerStates[id].down    = false;
				m_FingerStates[id].pressed = false;
				m_FingerStates[id].up = true;
				m_CurrentEvents.Append(TouchEvent(id, inputEvent.GetType()));
			}
		}
	}
	 return InputHandler::OnEvent(inputEvent);
}

void InputTouchScreenBase::PointerIdHelper(const IndexT& id, const Math::float2& pixelPos, const Math::float2& screenPos)
{
	IndexT result = m_PixelPositions.FindIndex(id);

	if (result != InvalidIndex)
	{
		m_PixelPositions[id]  = pixelPos;
	} 
	else
	{
		m_PixelPositions.Add(id, pixelPos);
	}

	result = m_ScreenPositions.FindIndex(id);

	if (result != InvalidIndex)
	{
		m_ScreenPositions[id] = screenPos;
	} 
	else
	{

		m_ScreenPositions.Add(id, screenPos);
	}
}

void InputTouchScreenBase::UpdateFingerPositions(const Math::float2& pixelPos, const Math::float2& screenPos, const IndexT nPointer /* = 0 */)
{
	PointerIdHelper(nPointer, pixelPos, screenPos);
}

void InputTouchScreenBase::OnReset()
{
	for (IndexT i = 0; i < MaxPointerSupport; ++i)
	{
		FingerState& state = m_FingerStates[i];

		if (state.pressed)
		{
			state.up = true;
		}
		else
		{
			state.up = false;
		}
		state.down    = false;
		state.pressed = false;
	}

	m_bInitialMovement = true;
}

}








#endif
