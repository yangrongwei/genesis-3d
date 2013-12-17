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
#include "appframework/actor.h"
#include "scriptfeature/inc/script_utility.h"
#include "graphicfeature/components/animationcomponent.h"

namespace App
{
	void ICallReg_ScriptRuntime_AnimationComponent( void );

	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_SetAnimationID( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		const Util::String& name = Utility_MonoStringToCppString( pMonoString );
		self->SetAnimationID( name );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_CrossFading( MonoObject* pMonoObj, MonoString* pMonoString,int type ,float time )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		const Util::String& name = Utility_MonoStringToCppString( pMonoString );
		self->CrossFading( name ,type,time );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_PlayAnimation( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->PlayAnimation( name );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_StopAnimation( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->StopAnimation( name );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_BlendingAnimation( MonoObject* pMonoObj, MonoString* pMonoString, float weight, float time  )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->BlendingAnimation( name, weight, time );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_SetAnimationSpeed( MonoObject* pMonoObj, MonoString* pMonoString, float fSpeed )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->SetAnimationSpeed(name, fSpeed );
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_SetAnimationWrapMode( MonoObject* pMonoObj, MonoString* pMonoString, int iWrapMode )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->SetWrapMode(name,iWrapMode);
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_SetAnimationLayer( MonoObject* pMonoObj, MonoString* pMonoString, int layer )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		self->SetLayer(name,layer);
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_AddAffectedNodes( MonoObject* pMonoObj, MonoString* pMonoString_1, MonoString* pMonoString_2, mono_bool recursive)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String animName = Utility_MonoStringToCppString( pMonoString_1 );
		Util::String nodeName = Utility_MonoStringToCppString( pMonoString_2 );
		self->AddAffectedNodes(animName,nodeName,Utility_MonoBool(recursive));
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_RemoveAffectedNodes( MonoObject* pMonoObj, MonoString* pMonoString_1, MonoString* pMonoString_2)//for old dll.
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String animName = Utility_MonoStringToCppString( pMonoString_1 );
		Util::String nodeName = Utility_MonoStringToCppString( pMonoString_2 );
		self->RemoveAffectedNodes(animName,nodeName);
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_RemoveAffectedNodes_2( MonoObject* pMonoObj, MonoString* pMonoString_1, MonoString* pMonoString_2, mono_bool recursive)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String animName = Utility_MonoStringToCppString( pMonoString_1 );
		Util::String nodeName = Utility_MonoStringToCppString( pMonoString_2 );
		self->RemoveAffectedNodes(animName,nodeName, Utility_MonoBool(recursive));
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_AddAttachedActor( MonoObject* pMonoObj, MonoObject* pActor, MonoString* pMonoString)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		ScriptObjWrapper<Actor> actor( pActor );
		Util::String skelName = Utility_MonoStringToCppString( pMonoString );
		self->AddAttachedActor(actor.GetCppObjPtr(),skelName);
	}
	//------------------------------------------------------------------------
	static void ICall_AnimationComponent_RemoveAttachedActor( MonoObject* pMonoObj, MonoObject* pActor)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		ScriptObjWrapper<Actor> actor( pActor );
		self->RemoveAttachedActor(actor.GetCppObjPtr());
	}

	//------------------------------------------------------------------------
	static mono_bool ICall_AnimationComponent_IsAnimationPlaying( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		return Utility_MonoBool( self->IsAnimationPlaying(name) );
	}
	//------------------------------------------------------------------------
	static float ICall_AnimationComponent_GetCurAnimCurrentFrame( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		return self->GetCurrentFrame();
	}
	//------------------------------------------------------------------------
	static float ICall_AnimationComponent_GetCurrentFrame( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		return self->GetCurrentFrame(name);
	}
	//------------------------------------------------------------------------
	static int ICall_AnimationComponent_GetAnimFrameCount(MonoObject* pMonoObj, MonoString* pMonoString)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		return self->GetAnimFrameCount(name);
	}
	//------------------------------------------------------------------------
	static int ICall_AnimationComponent_GetCurrentAnimFrameCount(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		return self->GetCurrentAnimFrameCount();
	}
	//------------------------------------------------------------------------
	static MonoString* ICall_AnimationComponent_GetCurrentAnimation(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String sName = self->GetCurrentAnimation().AsString();
		return Utility_NewMonoString( sName );
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_AnimationComponent_GetNodeTransform( MonoObject* pMonoObj, MonoString* pMonoString , Math::matrix44& outMatrix )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name;
		Utility_MonoStringToCppString<Util::String>(pMonoString,name);
		bool found = self->GetNodeTransform(name, outMatrix);
		return Utility_MonoBool(found);

	}
	//------------------------------------------------------------------------
	static int ICall_AnimationComponent_GetWrapMode( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<AnimationComponent> self( pMonoObj );
		Util::String name;
		Utility_MonoStringToCppString<Util::String>(pMonoString,name);
		int wrapMode = self->GetWrapMode(name);
		return wrapMode;

	}
}

#include "autogen/scriptbind_AnimationComponent_register.h"