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
#include "core/refcounted.h"
#include "foundation/util/scriptbind.h"
#include "foundation/util/string.h"
#include "graphicsystem/GraphicSystem.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "graphicsystem/base/RenderToTexture.h"
#include "graphicsystem/base/ImageFilters.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "resource/resourcemanager.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicfeature/graphicsfeature.h"
#include "resource/resinfo.h"

namespace App 
{
  

    void ICallReg_ScriptRuntime_GraphicSystem( void );

	//------------------------------------------------------------------------
	static MonoObject* ICall_GraphicSystem_GetSceneCamera( )
	{
		CameraComponent * ret = static_cast<CameraComponent *>(Graphic::GraphicSystem::Instance()->GetRenderingCamera()->GetOwner());
		return CppPointerToScriptObj<CameraComponent>(ret);
	}
    //------------------------------------------------------------------------
	static void ICall_GraphicSystem_RenderCamera( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		Graphic::GraphicSystem::Instance()->_RenderCamera(self.GetCppObjPtr());
	}
    //------------------------------------------------------------------------
	static void ICall_GraphicSystem_SetRenderTarget( MonoObject* pMonoObj ,int value)
	{
		ScriptObjWrapper<Graphic::RenderToTexture> self( pMonoObj );
		GPtr<Graphic::RenderToTexture> rt = self.GetCppObjPtr();
		Graphic::GraphicSystem::Instance()->SetRenderTarget(rt,0,RenderBase::RenderTarget::ClearAll);
	}

	static int ICall_GraphicSystem_GetWidth( )
	{
		const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();
		return dm.GetWidth();
	}

	static int ICall_GraphicSystem_GetHeight( )
	{
		const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();
		return dm.GetHeight();
	}
	

	static MonoObject* ICall_GraphicSystem_GetCameraRenderToTextureByCameraType(int type)
	{	
		GPtr<Graphic::Camera> glowCam = Graphic::GraphicSystem::Instance()->GetCameraByType((Graphic::CameraOrder)type);
		Graphic::RenderToTexture* rtt =glowCam->GetRenderToTexture();
		return CppObjectToScriptObj(*rtt);
	}

	static MonoObject* ICall_GraphicSystem_CreateMaterial( MonoString* resID)
	{
		Util::String res;
		Utility_MonoStringToCppString(resID, res);
		GPtr<Resources::MaterialResInfo> matResInfo = Resources::ResourceManager::Instance()->CreateMaterialInfo(res);
		if ( !matResInfo.isvalid() )
		{
			return NULL;
		}
		GPtr<Graphic::MaterialInstance>& mtrl = matResInfo->GetHandle();
		if ( mtrl.isvalid() )
		{
			return CppObjectToScriptObj( *mtrl );
		}
		return NULL;
	}

	static void ICall_GraphicSystem_BlitImage(gpointer textureHandlePtr, MonoObject* destObj, MonoObject* matObj, int passIndex)
	{
		Graphic::RenderToTexture* target = ScriptObjWrapper<Graphic::RenderToTexture>::Convert( destObj );
		Graphic::MaterialInstance* material = ScriptObjWrapper<Graphic::MaterialInstance>::Convert( matObj );
		RenderBase::TextureHandle* tex = static_cast<RenderBase::TextureHandle*>(textureHandlePtr);

		Graphic::ImageFiltrationSystem::Render(tex, target, material, passIndex);
	}
	
    //------------------------------------------------------------------------
    void ICallReg_ScriptRuntime_GraphicSystem( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_GetSceneCamera",							(void*)&ICall_GraphicSystem_GetSceneCamera },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_RenderCamera",								(void*)&ICall_GraphicSystem_RenderCamera },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_SetRenderTarget",							(void*)&ICall_GraphicSystem_SetRenderTarget },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_GetWidth",									(void*)&ICall_GraphicSystem_GetWidth },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_GetHeight",									(void*)&ICall_GraphicSystem_GetHeight },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_GetCameraRenderToTextureByCameraType",		(void*)&ICall_GraphicSystem_GetCameraRenderToTextureByCameraType },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_CreateMaterial",							(void*)&ICall_GraphicSystem_CreateMaterial },
			{ "ScriptRuntime.GraphicSystem::ICall_GraphicSystem_BlitImage",									(void*)&ICall_GraphicSystem_BlitImage },
		};

        int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
        for( int ii=0; ii<size; ii++ )
        {
            mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
                s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
        }
    }
}
