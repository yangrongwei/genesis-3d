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
#include "guifeature/guiutility.h"
namespace App
{
	using namespace MyGUI;
	void ICallReg_ScriptGUI_Canvas();

	static void ICall_createTexture(gconstpointer widget_ptr, Canvas::TextureResizeMode _resizeMode, TextureUsage::Enum _usage, MyGUI::PixelFormat::Enum _format)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->createTexture(_resizeMode, _usage, _format);
	}

	static void ICall_createTexture_WidthSize(gconstpointer widget_ptr, int _width, int _height, Canvas::TextureResizeMode _resizeMode, TextureUsage::Enum _usage, PixelFormat::Enum _format)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->createTexture(_width, _height, _resizeMode, _usage, _format);
	}

	static void ICall_createTexture_FromTarget(gconstpointer widget_ptr, gconstpointer rtt_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		MyGUI::IRenderTarget* rtt = static_cast<MyGUI::IRenderTarget*>(rtt_ptr);
		canvas->createTexture(rtt);
	}

	static void ICall_destroyTexture(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->destroyTexture();
	}

	static void ICall_updateTexture(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->updateTexture();
	}
	////[zhongdaohuan]勿删，lock,unlock未启用，没想好脚本怎么用。
	//static void* ICall_lock(gconstpointer widget_ptr, TextureUsage::Enum _usage)
	//{
	//	MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
	//	return canvas->lock(_usage);
	//}	

	//static void ICall_unlock(gconstpointer widget_ptr)
	//{
	//	MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
	//	canvas->unlock();
	//}

	static mono_bool ICall_isLocked(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->isLocked();
	}

	static int ICall_getTextureRealWidth(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->getTextureRealWidth();
	}
	static int ICall_getTextureRealHeight(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->getTextureRealHeight();
	}
	static int ICall_getTextureSrcWidth(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->getTextureSrcWidth();
	}
	static int ICall_getTextureSrcHeight(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->getTextureSrcHeight();
	}
	static int ICall_getTextureFormat(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return GuiUtil_StructEnumToInt(canvas->getTextureFormat());
	}
	static int ICall_getResizeMode(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return TypeConvert<Canvas::TextureResizeMode>::Conver(canvas->getResizeMode());
	}

	static void ICall_setResizeMode(gconstpointer widget_ptr, int _value)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->setResizeMode(TypeConvert<Canvas::TextureResizeMode>::Conver(_value));
	}

	static mono_bool ICall_isTextureSrcSize(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->isTextureSrcSize();
	}

	static mono_bool ICall_isTextureCreated(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->isTextureCreated();
	}
	static mono_bool ICall_isTextureManaged(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->isTextureManaged();
	}
	static ITexture* ICall_getTexture(gconstpointer widget_ptr)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		return canvas->getTexture();
	}
	static void ICall_setTextureManaged(gconstpointer widget_ptr, mono_bool _value)
	{
		MyGUI::Canvas* canvas = static_cast<MyGUI::Canvas*>(widget_ptr);
		canvas->setTextureManaged(c_iMonoBool_True == _value);
	}

	void ICallReg_ScriptGUI_Canvas()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptGUI.Canvas::ICall_createTexture",							(void*)(&ICall_createTexture)}
			,{ "ScriptGUI.Canvas::ICall_createTexture_WidthSize",				(void*)(&ICall_createTexture_WidthSize)}
			,{ "ScriptGUI.Canvas::ICall_createTexture_FromTarget",				(void*)(&ICall_createTexture_FromTarget)}
			,{ "ScriptGUI.Canvas::ICall_destroyTexture",						(void*)(&ICall_destroyTexture)}
			,{ "ScriptGUI.Canvas::ICall_updateTexture",							(void*)(&ICall_updateTexture)}
			////[zhongdaohuan]勿删，lock,unlock未启用，没想好脚本怎么用。
			//,{ "ScriptGUI.Canvas::ICall_lock",									&ICall_lock}
			//,{ "ScriptGUI.Canvas::ICall_unlock",								&ICall_unlock}
			,{ "ScriptGUI.Canvas::ICall_isLocked",								(void*)(&ICall_isLocked)}
			,{ "ScriptGUI.Canvas::ICall_getTextureRealWidth",					(void*)(&ICall_getTextureRealWidth)}
			,{ "ScriptGUI.Canvas::ICall_getTextureRealHeight",					(void*)(&ICall_getTextureRealHeight)}
			,{ "ScriptGUI.Canvas::ICall_getTextureSrcWidth",					(void*)(&ICall_getTextureSrcWidth)}
			,{ "ScriptGUI.Canvas::ICall_getTextureSrcHeight",					(void*)(&ICall_getTextureSrcHeight)}
			,{ "ScriptGUI.Canvas::ICall_getTextureFormat",						(void*)(&ICall_getTextureFormat)}
			,{ "ScriptGUI.Canvas::ICall_getResizeMode",							(void*)(&ICall_getResizeMode)}
			,{ "ScriptGUI.Canvas::ICall_setResizeMode",							(void*)(&ICall_setResizeMode)}
			,{ "ScriptGUI.Canvas::ICall_isTextureSrcSize",						(void*)(&ICall_isTextureSrcSize)}
			,{ "ScriptGUI.Canvas::ICall_isTextureCreated",						(void*)(&ICall_isTextureCreated)}
			,{ "ScriptGUI.Canvas::ICall_isTextureManaged",						(void*)(&ICall_isTextureManaged)}
			,{ "ScriptGUI.Canvas::ICall_getTexture",							(void*)(&ICall_getTexture)}
			,{ "ScriptGUI.Canvas::ICall_setTextureManaged",						(void*)(&ICall_setTextureManaged)}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}