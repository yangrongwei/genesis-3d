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
#ifndef __CollisionModel_H__
#define __CollisionModel_H__

#include "foundation/core/refcounted.h"
#include "foundation/core/ptr.h"
#include "math/float3.h"
#include "util/array.h"
#include "util/string.h"

namespace Opcode
{
	class Model;
}

namespace RenderBase
{
	class PrimitiveGroup;
}

namespace Graphic
{
	class OpModelImp;

	class CollisionModel : public Core::RefCounted
	{
		__DeclareClass(CollisionModel);

	public:

		CollisionModel();

		~CollisionModel();

	public:

		void SetPrimitveInfo(const Util::String& name);

		void CreateOpModel();

		const Opcode::Model& GetOpCodeModel() const;

		SizeT GetMemoryUsage() const;

		const Util::Array<Math::float3>& GetVertices() const;

		const Util::Array<uint>& GetIndices() const;

		const Util::Array<Math::float4>& GetFaceNormals() const; 

	protected:

		OpModelImp*                m_pOpModelImp;

		SizeT                      m_nMemoryUsage;

		Util::Array<Math::float3>  m_Vertices;
		Util::Array<uint>          m_Indices;
		Util::Array<Math::float4>  m_FaceNormals;

		bool                       m_bIndex16;

	};

	inline SizeT CollisionModel::GetMemoryUsage() const
	{
		return m_nMemoryUsage;
	}

	inline const Util::Array<Math::float3>& CollisionModel::GetVertices() const
	{
		return m_Vertices;
	}

	inline const Util::Array<uint>& CollisionModel::GetIndices() const
	{
		return m_Indices;
	}

	inline const Util::Array<Math::float4>& CollisionModel::GetFaceNormals() const
	{
		return m_FaceNormals;
	}

}



#endif