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
namespace App
{
	static float ICall_ProjectorRenderComponent_GetFov(MonoObject* self);
	
	static void ICall_ProjectorRenderComponent_SetFov(MonoObject* self, float fov);

	static int ICall_ProjectorRenderComponent_GetViewType(MonoObject* self);

	static void ICall_ProjectorRenderComponent_SetViewType(MonoObject* self, int viewType);

	static float ICall_ProjectorRenderComponent_GetAspect(MonoObject* self);

	static void ICall_ProjectorRenderComponent_SetAspect(MonoObject* self, float aspect);

	static float ICall_ProjectorRenderComponent_GetZNear(MonoObject* self);

	static void ICall_ProjectorRenderComponent_SetZNear(MonoObject* self, float znear);

	static float ICall_ProjectorRenderComponent_GetZFar(MonoObject* self);

	static void ICall_ProjectorRenderComponent_SetZFar(MonoObject* self, float zfar);
	
	static float ICall_ProjectorRenderComponent_GetNearHeight(MonoObject* self);
	
	static void ICall_ProjectorRenderComponent_SetNearHeight(MonoObject* self, float nearHeight);
	
	static uint32 ICall_ProjectorRenderComponent_GetIgnoreLayers(MonoObject* self);

	static void ICall_ProjectorRenderComponent_SetIgnoreLayers(MonoObject* self, uint32 mask);

	static void ICall_ProjectorRenderComponent_EnableProjector( MonoObject* pMonoObj, mono_bool b);

	static mono_bool ICall_ProjectorRenderComponent_IsEnabledProjector( MonoObject* pMonoObj);

	void ICallReg_ScriptRuntime_ProjectorRenderComponent( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetFov",								 (void*)&ICall_ProjectorRenderComponent_GetFov },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetFov",								 (void*)&ICall_ProjectorRenderComponent_SetFov },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetViewType",							 (void*)&ICall_ProjectorRenderComponent_GetViewType },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetViewType",							 (void*)&ICall_ProjectorRenderComponent_SetViewType },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetAspect",								 (void*)&ICall_ProjectorRenderComponent_GetAspect },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetAspect",								 (void*)&ICall_ProjectorRenderComponent_SetAspect },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetZNear",								 (void*)&ICall_ProjectorRenderComponent_GetZNear },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetZNear",								 (void*)&ICall_ProjectorRenderComponent_SetZNear },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetZFar",								 (void*)&ICall_ProjectorRenderComponent_GetZFar },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetZFar",								 (void*)&ICall_ProjectorRenderComponent_SetZFar },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetNearHeight",							 (void*)&ICall_ProjectorRenderComponent_GetNearHeight },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetNearHeight",							 (void*)&ICall_ProjectorRenderComponent_SetNearHeight },
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_GetIgnoreLayers",					     (void*)&ICall_ProjectorRenderComponent_GetIgnoreLayers },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_SetIgnoreLayers",					     (void*)&ICall_ProjectorRenderComponent_SetIgnoreLayers },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_EnableProjector",					     (void*)&ICall_ProjectorRenderComponent_EnableProjector },	 
			{ "ScriptRuntime.ProjectorRenderComponent::ICall_ProjectorRenderComponent_IsEnabledProjector",					     (void*)&ICall_ProjectorRenderComponent_IsEnabledProjector },	 
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}	 
}