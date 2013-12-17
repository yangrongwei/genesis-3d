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
#include "scriptfeature/inc/script_utility.h"
#include "foundation/math/float3.h"
#include "foundation/math/ray.h"
#include "apputil/intersectutil.h"
#include "appframework/app_fwd_decl.h"

namespace App
{
	void ICallReg_ScriptRuntime_IntersectWorld( void );

	//-TODO:these functions may be rewrite later.
    static void ICall_IntersectWorld_ComputeRay(Math::float2& screenPos,Math::Ray& outRay)
	{
		Math::Ray worldRay;
		AppUtil::IntersectUtil::ComputeDefaultWorldMouseRay( NULL, screenPos, worldRay );
		outRay = worldRay ;
	}

	static mono_bool ICall_IntersectWorld_IntersectActor(MonoObject* monoact, const Math::Ray& ray, uint select_mark,Math::float3& outpos)
	{
		ScriptObjWrapper<Actor>  pActor(monoact);

		float dis=0.0f;
		AppUtil::IntersectResultList rsList;
		bool ret =	AppUtil::IntersectUtil::IntersectActor(ray,pActor.GetCppObjPtr(), select_mark, false, dis);

		outpos = ray.PointAt(dis);

		return Utility_MonoBool(ret);
	}

	static MonoObject* ICall_IntersectWorld_Actor(const Math::Ray& ray, uint select_mark)
	{
		
		AppUtil::IntersectResultList rsList;
	    AppUtil::IntersectUtil::IntersectWorld(ray, select_mark, false, rsList );
		rsList.Sort();
		if (rsList.IsEmpty())
		{
			return NULL;
		}
		App::TActorPtr pActor = rsList[0].actor;
		if(!pActor.isvalid()){
			return NULL;
		}
		return CppObjectToScriptObj( *pActor );	
	}

	static void ICall_IntersectWorld_Point(const Math::Ray& ray, uint select_mark,Math::float3& outFloat3)
	{
		
		AppUtil::IntersectResultList rsList;
		AppUtil::IntersectUtil::IntersectWorld(ray, select_mark, false, rsList );
		rsList.Sort();
		if (rsList.IsEmpty())
		{
			outFloat3 = Math::float3(0,0,0);
			return;
		}
        outFloat3 = ray.PointAt( rsList[0].intersectPoint );
		
	}

	static void ICall_IntersectWorld_Triangle(const Math::Ray& ray,uint select_mark,Math::float3& outPoint1,Math::float3& outPoint2,Math::float3& outPoint3)
	{
		AppUtil::IntersectResultList rsList;
		AppUtil::IntersectTriangle triAngle;
		AppUtil::IntersectUtil::IntersectWorld(ray, select_mark, false, rsList, N_TINY, &triAngle );
		rsList.Sort();
		outPoint1 = triAngle.point0;
		outPoint2 = triAngle.point1;
		outPoint3 = triAngle.point2;
	}

	void ICallReg_ScriptRuntime_IntersectWorld( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.IntersectWorld::ICall_IntersectWorld_Actor", (void*)&ICall_IntersectWorld_Actor },
			{ "ScriptRuntime.IntersectWorld::ICall_IntersectWorld_Point", (void*)&ICall_IntersectWorld_Point },
			{ "ScriptRuntime.IntersectWorld::ICall_IntersectWorld_Triangle", (void*)&ICall_IntersectWorld_Triangle },
			{ "ScriptRuntime.IntersectWorld::ICall_IntersectWorld_ComputeRay", (void*)&ICall_IntersectWorld_ComputeRay },
			{ "ScriptRuntime.IntersectWorld::ICall_IntersectWorld_IntersectActor", (void*)&ICall_IntersectWorld_IntersectActor },
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}