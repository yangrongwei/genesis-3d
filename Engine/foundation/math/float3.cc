/****************************************************************************
Copyright (c) 2007,RadonLabs GmbH
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
#include "float3.h"

namespace Math
{
	const float float3::epsilon = 0.00001F;

	//------------------------------------------------------------------------
	float4 float3::calculateFaceNormalWithoutNormalize( const float3& v1, const float3& v2, const float3& v3 )
	{
		float3 normal = calculateBasicFaceNormalWithoutNormalize( v1, v2, v3);
		return float4(normal.x(), normal.y(), normal.z(),-(normal.dotProduct(v1)));
	}
	//------------------------------------------------------------------------
	float3 float3::calculateBasicFaceNormalWithoutNormalize(const float3& v1, const float3& v2, const float3& v3)
	{
		float3 normal = (v2-v1).crossProduct(v3 - v1);
		return normal;
	}
	//-------------------------------------------------------------------------
	void float3::hermite(Math::float3 *pOut,const Math::float3 *pV1,const Math::float3 *pT1,const Math::float3 *pV2,const Math::float3 *pT2,Math::scalar s)
	{
		Math::scalar fLenSD =  (*pV2 - *pV1).length();
		Math::float3 T1;
		Math::float3 T2;
		T1 = Math::float3::normalize(*pT1);
		T2 = Math::float3::normalize(*pT2);

		T1 *= fLenSD;
		T2 *= fLenSD;

		*pOut = ((2*s*s*s - 3*s*s + 1) * (*pV1) + (-2*s*s*s + 3*s*s)*(*pV2) + (s*s*s - 2*s*s +s)*(T1) + (s*s*s - s*s)*(T2));
	}
}