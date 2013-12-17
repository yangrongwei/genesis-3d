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
#if __APPLE__

#include "input/input_stdneb.h"
#include "input/osx/osxinputsource.h"
#include "input/inputserver.h"
#include "input/osx/osxtouchevent.h"
#include "graphicsystem/GraphicSystem.h"
#include "input/inputmobileconfig.h"

namespace OSXInput
{
	using namespace Input;

	__ImplementClass(OSXInput::OSXInputSource, 'ANIS', Input::InputSource );

OSXInputSource::OSXInputSource()
{
	m_TouchPostions.Reserve(MaxPointerSupport);

	for (IndexT i = 0; i < MaxPointerSupport; ++i)
	{
		m_TouchPostions.Add(i, Math::float2(0.0f, 0.0f));
	}
}

OSXInputSource::~OSXInputSource()
{
	m_TouchPostions.Clear();
}

void OSXInputSource::Open(const GPtr<Input::InputServerBase>& inputServer)
{
	Super::Open(inputServer);
}

void OSXInputSource::Close()
{
	Super::Close();
}

void OSXInputSource::BeginFrame(void)
{
	n_assert(mInputServer.isvalid());
	SizeT count = m_InputEventList.Size();
	for ( IndexT i = 0; i < count; ++i )
	{
		mInputServer->PutEvent( m_InputEventList[i] );
	}
	m_InputEventList.Clear();

}

int OSXInputSource::OnOSXProc(MoibleInputEvent* pEvent)
{
	n_assert(pEvent != NULL)

    MobileTouchEvent* pTouchEvent    = static_cast<MobileTouchEvent*>(pEvent);
	OSXTouchEvent* pAndroidEvent = static_cast<OSXTouchEvent*>(pTouchEvent);

	const MoibleInputEvent::Type        lEventType = pEvent->GetType();
	const OSXTouchEvent::SourceType sourceType = pAndroidEvent->GetSourceType();

	switch (lEventType)
	{
	case MoibleInputEvent::INPUT_EVENT_TYPE_MOTION:
		switch (sourceType)
		{
		case OSXTouchEvent::INPUT_SOURCE_TOUCHSCREEN:
			OnTouchEvent(pTouchEvent);
			break;

		case OSXTouchEvent::INPUT_SOURCE_TRACKBALL:
			break;
		}
		break;

	case MoibleInputEvent::INPUT_EVENT_TYPE_KEY:
		break;
	}

	return 0;
}

void OSXInputSource::OnTouchEvent(const MobileTouchEvent* pEvent)
{
	const MobileTouchEvent::MotionType actionType  = pEvent->GetMotionType();

	switch (actionType)
	{
	case MobileTouchEvent::MOTION_EVENT_ACTION_MOVE:
		OnTouchMove(pEvent);
		break;

	case MobileTouchEvent::MOTION_EVENT_ACTION_DOWN:
	case MobileTouchEvent::MOTION_EVENT_ACTION_UP:
		OnTouch(pEvent, actionType);
		break;
	}
}

void OSXInputSource::OnTouch(const MobileTouchEvent* pEvent, const int type)
{
	const SizeT nPointers = pEvent->GetPointersCount();

	InputEvent inputEvent;

	for (IndexT i = 0; i < nPointers; ++i)
	{
		const IndexT id = pEvent->GetPointerId(i);

		Math::float2 absMousePos  = ComputeAbsTouchPos(pEvent, id);
		Math::float2 normMousePos = ComputeNormTouchPos(absMousePos);

		inputEvent.SetPointerId(id);
		inputEvent.SetAbsTouchPos( absMousePos, id );
		inputEvent.SetNormTouchPos( normMousePos, id );
	}
		
	

	switch (type)
	{
	case MobileTouchEvent::MOTION_EVENT_ACTION_DOWN:
		inputEvent.SetType(InputEvent::TouchMotionDown);
		m_InputEventList.Append(inputEvent);
		break;

	case MobileTouchEvent::MOTION_EVENT_ACTION_UP:
		inputEvent.SetType(InputEvent::TouchMotionUp);
		m_InputEventList.Append(inputEvent);
		break;
	}
}

void OSXInputSource::OnTouchMove(const MobileTouchEvent* pEvent)
{
	
	const SizeT nPointers = pEvent->GetPointersCount();

	InputEvent inputEvent;

	n_assert(mInputServer.isvalid() && mInputServer->GetRtti()->IsDerivedFrom( OSXInputServer::RTTI ) );
	GPtr<OSXInputServer> osxInputServer = mInputServer.downcast<OSXInputServer>();
	n_assert( osxInputServer.isvalid() );

	for (IndexT i = 0; i < nPointers; ++i)
	{
		const IndexT id = pEvent->GetPointerId(i);

		Math::float2 absTouchPos  = this->ComputeAbsTouchPos(pEvent, id);
		Math::float2 normTouchPos = this->ComputeNormTouchPos(absTouchPos);

		inputEvent.SetPointerId(id);
		inputEvent.SetType(InputEvent::TouchMotionMove);
		inputEvent.SetAbsTouchPos(absTouchPos, id);
		inputEvent.SetNormTouchPos(normTouchPos, id);

		Math::float2 touchmove = absTouchPos - m_TouchPostions[id];

		//0.01和上层的相机操纵算法相关，以后再改
		touchmove.set( touchmove.x() * (float)0.01, touchmove.y() * (float)0.01 );

		m_TouchPostions[id] = absTouchPos;

		osxInputServer->SetTouchMovement(touchmove, id);
	}
		

	m_InputEventList.Append(inputEvent);

	
}

Math::float2 OSXInputSource::ComputeAbsTouchPos(const MobileTouchEvent* pEvent, IndexT nPointer)
{
	return pEvent->GetPointerPos(nPointer);
}

Math::float2 OSXInputSource::ComputeNormTouchPos(const Math::float2& absTouchPos) const
{
	Math::float2 normMousePos;

	const GPtr<Graphic::ViewPortWindow>& pMainWindow = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow();
	const RenderBase::DisplayMode& dm = pMainWindow->GetDisplayMode();

	int width  = dm.GetWidth();
	int height = dm.GetHeight();

	normMousePos.set(absTouchPos.x() / float(width), absTouchPos.y() / float(height));

	return normMousePos;
}

}


#endif