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

#ifndef __vegetation_fwd_decl_H__
#define __vegetation_fwd_decl_H__

#include "core/ptr.h"
#include "core/singleton.h"
#include "timing/time.h"
#include "util/stringatom.h"
#include "math/float3.h"
#include "math/float2.h"
#include "math/quaternion.h"
#include "util/array.h"
#include "util/stl.h"
#include "math/color.h"
#include "serialization/serialize.h"
#include "util/algorithm.h"


namespace Vegetation
{	

	class VegetationObject;
	class VegetationBrush;
	class VegeInstanceMap;
	class VegetationRenderable;
	class VegetationServer;



	typedef GPtr<VegetationObject>           VegetationObjectPtr;
	typedef GPtr<VegetationBrush>			VegetationBrushPtr;
	typedef GPtr<VegeInstanceMap>			VegeInstanceMapPtr;
	typedef GPtr<VegetationRenderable>		VegetationRenderablePtr;
	typedef GPtr<VegetationServer>			VegetationServerPtr;


}

namespace Vegetation
{
	template<typename T>
	GPtr<T> Clone(const GPtr<T>& source)
	{
		n_assert( source.isvalid() );
		GPtr<Core::RefCounted> pObj = source->GetRtti()->Create();
		GPtr<T> dest = pObj.downcast<T>();
		n_assert( dest.isvalid() );
		dest->CopyFrom( source );
		return dest;
	}
}


#endif // __vegetation_fwd_decl_H__
