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
#include "graphicfeature/components/skeletoncomponent.h"
#include "foundation/math/float3.h"
#include "foundation/math/ray.h"

namespace App
{
	void ICallReg_ScriptRuntime_SkeletonComponent( void );
	//------------------------------------------------------------------------
	static void ICall_SkeletonComponent_SetSkeletonID( MonoObject* pMonoObj, MonoString* pMonoStr, Resources::Priority priority )
	{
		ScriptObjWrapper<SkeletonComponent> self( pMonoObj );
		Util::String sSkeletonId = Utility_MonoStringToCppString( pMonoStr );

		self->SetSkeletonID( sSkeletonId );
	}
	//------------------------------------------------------------------------
	void ICallReg_ScriptRuntime_SkeletonComponent( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.SkeletonComponent::ICall_SkeletonComponent_SetSkeletonID", (void*)&ICall_SkeletonComponent_SetSkeletonID },
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}