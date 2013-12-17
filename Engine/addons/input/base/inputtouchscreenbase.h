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
#ifndef __inputtouchscreenbase_H__
#define __inputtouchscreenbase_H__

#include "input/inputhandler.h"
#include "util/fixedarray.h"
#include "input/inputeventtypes.h"
namespace Input
{
	class InputTouchScreenBase : public Input::InputHandler
{
	__DeclareClass(InputTouchScreenBase);

public:

	/// constructor
	InputTouchScreenBase();
	/// destructor
	virtual ~InputTouchScreenBase();

	/// return true if nth Finger is currently pressed
	bool FingerPressing(const IndexT nPointer = 0) const;
	/// return true if nth Finger was down at least once in current frame 
	bool FingerDown(const IndexT nPointer = 0) const;
	/// return true if nth Finger was up at least once in current frame 
	bool FingerUp(const IndexT nPointer = 0) const;
	/// get current absolute nth Finger position (in pixels)
	const Math::float2& GetPixelPosition(const IndexT nPointer = 0) const;
	/// get current screen space nth Finger position (0.0 .. 1.0)
	const Math::float2& GetScreenPosition(const IndexT nPointer = 0) const;
	/// get nth Finger movement
	const Math::float2& GetMovement(const IndexT nPointer = 0) const;

	int GetTouchCount();

	int GetTouchID(int index);

	int GetCurrentEventCount() const;

	TouchEvent GetCurrentEvent(int index) const;

protected:

	/// called when the handler is attached to the input server
	virtual void OnAttach(const GPtr<InputServerBase>& inputServer);
	/// called on InputServer::BeginFrame()
	virtual void OnBeginFrame();
	/// called when an input event should be processed
	virtual bool OnEvent(const Input::InputEvent& inputEvent);
	/// reset the input handler
	virtual void OnReset();

private:

	/// update finger position members
	void UpdateFingerPositions(const Math::float2& pixelPos, const Math::float2& screenPos, const IndexT nPointer = 0);

	void PointerIdHelper(const IndexT& id, const Math::float2& pixelPos, const Math::float2& screenPos);

	struct FingerState
	{
	public:
		/// constructor
		FingerState() : pressed(false), down(false), up(false)
		{

		};

		bool pressed;
		bool down;
		bool up;

	};

	Util::Dictionary<IndexT, Math::float2 >  m_PixelPositions;
	Util::Dictionary<IndexT, Math::float2 >  m_ScreenPositions;
	Util::Dictionary<IndexT, Math::float2 >  m_Movements;

	bool                              m_bInitialMovement;
    
protected:
    Util::Dictionary<IndexT, FingerState>     m_FingerStates;
	Util::Array<TouchEvent>		m_CurrentEvents;

};

inline bool InputTouchScreenBase::FingerPressing(const IndexT nPointer /* = 0 */) const
{
	return m_FingerStates[nPointer].pressed;
}

inline bool InputTouchScreenBase::FingerDown(const IndexT nPointer /* = 0 */) const
{
	return m_FingerStates[nPointer].down;
}

inline bool InputTouchScreenBase::FingerUp(const IndexT nPointer /* = 0 */) const
{
	return m_FingerStates[nPointer].up;
}

inline const Math::float2& InputTouchScreenBase::GetPixelPosition(const IndexT nPointer /* = 0 */) const
{
	return m_PixelPositions[nPointer];
}

inline const Math::float2& InputTouchScreenBase::GetScreenPosition(const IndexT nPointer /* = 0 */) const
{
	return m_ScreenPositions[nPointer];
}

inline const Math::float2& InputTouchScreenBase::GetMovement(const IndexT nPointer /* = 0 */) const
{
	return m_Movements[nPointer];
}

inline int InputTouchScreenBase::GetTouchCount()
{
	return m_ScreenPositions.Size();
}

inline int InputTouchScreenBase::GetTouchID( int index )
{
	return m_ScreenPositions.KeyAtIndex(index);
}

inline int InputTouchScreenBase::GetCurrentEventCount() const
{
	return m_CurrentEvents.Size();
}

inline TouchEvent InputTouchScreenBase::GetCurrentEvent(int index) const
{
	return m_CurrentEvents[index];
}
}

#endif 