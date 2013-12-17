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
#ifndef __androidtouchevent_H__
#define __androidtouchevent_H__

#include "input/mobiletouchevent.h"


namespace AndroidInput
{
	class AndroidTouchEvent : public Input::MobileTouchEvent
{
public:
	
	enum SourceType
	{
		INPUT_SOURCE_UNKNOWN = 0,

		INPUT_SOURCE_KEYBOARD,
		INPUT_SOURCE_DPAD,
		INPUT_SOURCE_TOUCHSCREEN,
		INPUT_SOURCE_MOUSE,
		INPUT_SOURCE_TRACKBALL,
		INPUT_SOURCE_TOUCHPAD,
	};

	AndroidTouchEvent();

	~AndroidTouchEvent();

	void SetSourceType(const SourceType type);

	const SourceType GetSourceType() const;

protected:

	SourceType    m_SourceType;
};

inline AndroidTouchEvent::AndroidTouchEvent()
: m_SourceType(INPUT_SOURCE_UNKNOWN)
{
	
}

inline AndroidTouchEvent::~AndroidTouchEvent()
{
	
}

inline void AndroidTouchEvent::SetSourceType(const SourceType type)
{
	m_SourceType = type;
}

inline const AndroidTouchEvent::SourceType AndroidTouchEvent::GetSourceType() const
{
	return m_SourceType;
}

}

#endif