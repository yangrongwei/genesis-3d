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
#ifndef __androidinputsource_H__
#define __androidinputsource_H__

#include "input/inputsource.h"
#include "input/inputevent.h"


namespace Input
{
	class MoibleInputEvent;
	class MobileTouchEvent;
}


namespace AndroidInput
{

	class AndroidInputSource : public Input::InputSource
{
	__DeclareSubClass(AndroidInputSource, Input::InputSource);
public:

	AndroidInputSource();

	virtual ~AndroidInputSource();

	virtual void Open(const GPtr<Input::InputServerBase>& inputServer);

	// @ InputSource::Close()
	virtual void Close();

	/// called when the input server BeginFrame. Maybe Create InputEvent there
	virtual void BeginFrame(void);

	int OnAndroidProc(Input::MoibleInputEvent* pEvent);

	Math::float2 ComputeAbsTouchPos(const Input::MobileTouchEvent* pEvent, IndexT nPointer = 0);

	Math::float2 ComputeNormTouchPos(const Math::float2& absTouchPos) const;


protected:

	void OnTouchEvent(const Input::MobileTouchEvent* pEvent);

	void OnTouchMove(const Input::MobileTouchEvent* pEvent);

	void OnTouch(const Input::MobileTouchEvent* pEvent, const int type);

protected:
	Util::Array<Input::InputEvent> m_InputEventList;

    Util::Dictionary<IndexT, Math::float2> m_TouchPostions;
	
};



}



#endif