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
	void ICallReg_ScriptGUI_TextBox( void );

	static MonoString* ICall_getCaption(gconstpointer textbox_ptr)
	{
		const MyGUI::UString caption = static_cast<MyGUI::TextBox*>(textbox_ptr)->getCaption();
		return GuiUtility::UStringToMonoString(caption);
	}
	static void ICall_setCaption(gconstpointer textbox_ptr, MonoString* caption)
	{
		MyGUI::TextBox* textbox = static_cast<MyGUI::TextBox*>(textbox_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(caption, str);
		textbox->setCaption(str);
	}


	static void ICall_getTextRegion(gconstpointer widget_ptr, MyGUI::IntCoord& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		value = text_box->getTextRegion();
	}


	static void ICall_getTextSize(gconstpointer widget_ptr, MyGUI::IntSize& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		value = text_box->getTextSize();
	}


	static void ICall_setFontName(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(value, str);
		text_box->setFontName(str);
	}


	static MonoString* ICall_getFontName(gconstpointer widget_ptr)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		return GuiUtility::StdStringToMonoString(text_box->getFontName());
	}


	static void ICall_setFontHeight(gconstpointer widget_ptr, int value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		text_box->setFontHeight(value);
	}


	static int ICall_getFontHeight(gconstpointer widget_ptr)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		return text_box->getFontHeight();
	}


	static void ICall_setTextAlign(gconstpointer widget_ptr, MyGUI::Align& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		text_box->setTextAlign(value);
	}


	static int ICall_getTextAlign(gconstpointer widget_ptr)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		return text_box->getTextAlign().GetValue();
	}


	static void ICall_setTextColour(gconstpointer widget_ptr, MyGUI::Colour& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		text_box->setTextColour(value);
	}


	static void ICall_getTextColour(gconstpointer widget_ptr, MyGUI::Colour& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		value = text_box->getTextColour();
	}


	static void ICall_setCaptionWithReplacing(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(value, str);
		text_box->setCaptionWithReplacing(str);
	}


	static void ICall_setTextShadowColour(gconstpointer widget_ptr, MyGUI::Colour& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		text_box->setTextShadowColour(value);
	}


	static void ICall_getTextShadowColour(gconstpointer widget_ptr, MyGUI::Colour& value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		value = text_box->getTextShadowColour();
	}


	static void ICall_setTextShadow(gconstpointer widget_ptr, mono_bool value)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		text_box->setTextShadow(value == c_iMonoBool_True);
	}


	static mono_bool ICall_getTextShadow(gconstpointer widget_ptr)
	{
		MyGUI::TextBox* text_box = static_cast<MyGUI::TextBox*>(widget_ptr);
		return text_box->getTextShadow();
	}



	void ICallReg_ScriptGUI_TextBox()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = 
		{{ "ScriptGUI.TextBox::ICall_setCaption",					(void*)&ICall_setCaption}
		,{ "ScriptGUI.TextBox::ICall_getCaption",					(void*)&ICall_getCaption}
		,{ "ScriptGUI.TextBox::ICall_getTextRegion",				(void*)&ICall_getTextRegion}
		,{ "ScriptGUI.TextBox::ICall_getTextSize",					(void*)&ICall_getTextSize}
		,{ "ScriptGUI.TextBox::ICall_setFontName",					(void*)&ICall_setFontName}
		,{ "ScriptGUI.TextBox::ICall_getFontName",					(void*)&ICall_getFontName}
		,{ "ScriptGUI.TextBox::ICall_setFontHeight",				(void*)&ICall_setFontHeight}
		,{ "ScriptGUI.TextBox::ICall_getFontHeight",				(void*)&ICall_getFontHeight}
		,{ "ScriptGUI.TextBox::ICall_setTextAlign",					(void*)&ICall_setTextAlign}
		,{ "ScriptGUI.TextBox::ICall_getTextAlign",					(void*)&ICall_getTextAlign}
		,{ "ScriptGUI.TextBox::ICall_setTextColour",				(void*)&ICall_setTextColour}
		,{ "ScriptGUI.TextBox::ICall_getTextColour",				(void*)&ICall_getTextColour}
		,{ "ScriptGUI.TextBox::ICall_setCaptionWithReplacing",		(void*)&ICall_setCaptionWithReplacing}
		,{ "ScriptGUI.TextBox::ICall_setTextShadowColour",			(void*)&ICall_setTextShadowColour}
		,{ "ScriptGUI.TextBox::ICall_getTextShadowColour",			(void*)&ICall_getTextShadowColour}
		,{ "ScriptGUI.TextBox::ICall_setTextShadow",				(void*)&ICall_setTextShadow}
		,{ "ScriptGUI.TextBox::ICall_getTextShadow",				(void*)&ICall_getTextShadow}

		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}