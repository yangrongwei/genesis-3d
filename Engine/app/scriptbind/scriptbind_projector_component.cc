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
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "graphicfeature/components/projectorcomponent.h"

namespace App
{
	void ICallReg_ScriptRuntime_ProjectorRenderComponent( void );

	//--------------------------------------------------------------------------------
	static float ICall_ProjectorRenderComponent_GetFov( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		float fov = self->GetFov();
		return fov;
	}

	static void ICall_ProjectorRenderComponent_SetFov( MonoObject* pMonoObj, float angle)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetFov(angle);
	}
	//--------------------------------------------------------------------------------
	static int ICall_ProjectorRenderComponent_GetViewType( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		int viewType = self->GetViewType();
		return viewType;
	}

	static void ICall_ProjectorRenderComponent_SetViewType( MonoObject* pMonoObj , int viewType)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetViewType(Graphic::Projector::ViewType(viewType));
	}
	//--------------------------------------------------------------------------------
	static float ICall_ProjectorRenderComponent_GetAspect( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		float aspect = self->GetAspectRatio();
		return aspect;
	}

	static void ICall_ProjectorRenderComponent_SetAspect( MonoObject* pMonoObj, float angle)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetAspectRatio(angle);
	}
	//--------------------------------------------------------------------------------
	static float ICall_ProjectorRenderComponent_GetZNear( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		float nearPlane = self->GetNearClipPlane();
		return nearPlane;
	}

	static void ICall_ProjectorRenderComponent_SetZNear( MonoObject* pMonoObj , float nearPlane)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetNearClipPlane(nearPlane);
	}
	//--------------------------------------------------------------------------------
	static float ICall_ProjectorRenderComponent_GetZFar( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		float farPlane = self->GetFarClipPlane();
		return farPlane;
	}

	static void ICall_ProjectorRenderComponent_SetZFar(MonoObject* pMonoObj ,float farPlane)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetFarClipPlane(farPlane);
	}
	//--------------------------------------------------------------------------------
	static float ICall_ProjectorRenderComponent_GetNearHeight( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		float nearHeight = self->GetFov();
		return nearHeight;
	}

	static void ICall_ProjectorRenderComponent_SetNearHeight(MonoObject* pMonoObj ,float nearheight)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetFov(nearheight);
	}
	//--------------------------------------------------------------------------------
	static uint32 ICall_ProjectorRenderComponent_GetIgnoreLayers( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		uint32 ignoreLayers = self->GetIgnoreLayers();
		return ignoreLayers;
	}

	static void ICall_ProjectorRenderComponent_SetIgnoreLayers( MonoObject* pMonoObj , uint32 ignoreLayers)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->SetIgnoreLayers(ignoreLayers);
	}
	//--------------------------------------------------------------------------------
	static void ICall_ProjectorRenderComponent_EnableProjector( MonoObject* pMonoObj, mono_bool b)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		self->EnableProjectorUpdate( c_iMonoBool_True == b );
	}

	static mono_bool ICall_ProjectorRenderComponent_IsEnabledProjector( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<ProjectorRenderComponent> self( pMonoObj );
		bool b = self->IsProjectorEnabled();
		if (b)
			return c_iMonoBool_True;
		else
			return c_iMonoBool_False;
	}
}

#include "autogen/scriptbind_projector_component_register.h"
