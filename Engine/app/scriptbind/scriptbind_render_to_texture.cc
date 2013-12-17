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
#include "foundation/math/float4.h"

namespace App 
{
  

    void ICallReg_ScriptRuntime_RenderToTexture( void );

    //------------------------------------------------------------------------
  
    //------------------------------------------------------------------------
	static void ICall_RenderToTexture_Bind( MonoObject* pMonoObj )
	{
		Graphic::RenderToTexture* pRTT = Graphic::RenderToTexture::Create();

		n_assert( NULL!=pRTT );
		BindCppObjWithMonoObj<Graphic::RenderToTexture>(pRTT,pMonoObj);
	}


	static void ICall_RenderToTexture_Setup(MonoObject* pMonoObj,int width,int height,int pixelFormat, uint flag, Math::float4& color,mono_bool useDepth
												,float screenRatio,int antiAliasQuality,int texLeft,int texRight,int texTop,int texBottom)
	{
		ScriptObjWrapper<Graphic::RenderToTexture> self( pMonoObj );
		bool b = false;
		if ( c_iMonoBool_True==useDepth )
		{
			b = true;
		}
		self->Setup(width,height,(RenderBase::PixelFormat::Code)pixelFormat,flag,color,b,screenRatio,(RenderBase::AntiAliasQuality::Code)antiAliasQuality
			,Math::rectangle<int>(texLeft,texRight,texTop,texBottom));
	}

	static void ICall_RenderToTexture_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Graphic::RenderToTexture> self( pMonoObj );
		Graphic::RenderToTexture* pRT = self.GetCppObjPtr();
		n_assert( NULL!=pRT );

		ReleaseCppObjWithMonoObj<Graphic::RenderToTexture>( pRT, pMonoObj );
	}
	static const RenderBase::TextureHandle* ICall_RenderToTexture_GetTextureHandlePtr( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Graphic::RenderToTexture> self( pMonoObj );
		return &(self->GetTextureHandle());
	}

    //------------------------------------------------------------------------
    void ICallReg_ScriptRuntime_RenderToTexture( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
 			{ "ScriptRuntime.RenderToTexture::ICall_RenderToTexture_Bind",							(void*)&ICall_RenderToTexture_Bind },
			{ "ScriptRuntime.RenderToTexture::ICall_RenderToTexture_Release",						(void*)&ICall_RenderToTexture_Release },
			{ "ScriptRuntime.RenderToTexture::ICall_RenderToTexture_Setup",							(void*)&ICall_RenderToTexture_Setup },
			{ "ScriptRuntime.RenderToTexture::ICall_RenderToTexture_GetTextureHandlePtr",			(void*)&ICall_RenderToTexture_GetTextureHandlePtr },
        };

        int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
        for( int ii=0; ii<size; ii++ )
        {
            mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
                s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
        }
    }
}
