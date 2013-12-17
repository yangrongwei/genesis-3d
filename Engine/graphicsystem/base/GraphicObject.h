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

#ifndef GRAPHICOBJECT_H_
#define GRAPHICOBJECT_H_
#include "math/matrix44.h"
#include "math/bbox.h"
#include "core/refcounted.h"
#include "timing/time.h"
#include "vis/visentity.h"

namespace Graphic
{
	class GraphicObject : public Core::RefCounted
	{
		__DeclareClass(GraphicObject)
	public:
		GraphicObject();
		virtual ~GraphicObject();

		const Math::matrix44& GetTransform() const;

		virtual void SetTransform(const Math::matrix44& trans);

		virtual void SetBoundingBox(const Math::bbox& box);

		const Math::bbox& GetBoundingBox() const;

		void GetBoudingBoxInWorld(Math::bbox& worldBox) const;



	protected:
		Math::matrix44 m_transform;	//	world transform
		Math::bbox m_boundingBox;		//	local bound
	};
	inline GraphicObject::GraphicObject()
	{
		//empty
	}

	inline GraphicObject::~GraphicObject()
	{
		//empty
	}
	inline const Math::matrix44&
		GraphicObject::GetTransform() const
	{
		return m_transform;
	}

	inline const Math::bbox&
		GraphicObject::GetBoundingBox() const
	{
		return m_boundingBox;
	}

	inline void
		GraphicObject::GetBoudingBoxInWorld(Math::bbox& worldBox) const
	{
		worldBox = m_boundingBox;
		worldBox.transform(m_transform);
	}
}
#endif //GRAPHICOBJECT_H_