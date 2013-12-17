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


	void ICallReg_ScriptGUI_Widget( void );

	static void ICall_setVisible(gconstpointer widget_ptr, mono_bool visible)
	{
		static_cast<MyGUI::Widget*>(widget_ptr)->setVisible(c_iMonoBool_True == visible);
	}

	static mono_bool ICall_getVisible(gconstpointer widget_ptr, mono_bool visible)
	{
		return static_cast<MyGUI::Widget*>(widget_ptr)->getVisible();
	}

	static mono_bool ICall_getInheritedVisible(gconstpointer widget_ptr, mono_bool visible)
	{
		return static_cast<MyGUI::Widget*>(widget_ptr)->getInheritedVisible();
	}

	static int ICall_getType(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		for (int x = WidgetType::Last; x >= WidgetType::First; --x)
		{
			if (GuiUtility::IsWidgetType(widget, (WidgetType::_type)x))
			{
				return x;
			}
		}
		return WidgetType::Unknown;
	}
	mono_bool ICall_isType(gconstpointer widget_ptr, int widget_type)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return GuiUtility::IsWidgetType(widget, (WidgetType::_type)widget_type);
	}
	
	static mono_bool ICall_appendEvent(MonoObject* widget_ptr_cs, gconstpointer widget_ptr, int event_type)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setUserData(widget_ptr_cs);
		GuiUtility::SetEvent(widget, (EventType::_type)event_type, true);
		return true;
	}
	
	static void ICall_removeEvent(MonoObject* widget_ptr_cs, gconstpointer widget_ptr, int event_type)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setUserData(NULL);
		GuiUtility::SetEvent(widget, (EventType::_type)event_type, false);
	}
	
	static MonoString* ICall_getName(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return GuiUtility::StdStringToMonoString(widget->getName());
	}
	static void ICall_getClientCoord(gconstpointer widget_ptr, MyGUI::IntCoord& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		value = widget->getClientCoord();
	}
	static void ICall_setColor(gconstpointer widget_ptr, MyGUI::Colour& colour)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setColour(colour);
	}
	
	static void ICall_setPosition(gconstpointer widget_ptr, MyGUI::IntPoint& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setPosition(value);
	}

	
	static void ICall_setSize(gconstpointer widget_ptr, MyGUI::IntSize& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setSize(value);
	}

	
	static void ICall_setCoord(gconstpointer widget_ptr, MyGUI::IntCoord& coord)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setCoord(coord);
	}

	
	static void ICall_setRealPosition(gconstpointer widget_ptr, MyGUI::FloatPoint& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setRealPosition(value);
	}

	
	static void ICall_setRealSize(gconstpointer widget_ptr, MyGUI::FloatSize& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setRealSize(value);
	}

	
	static void ICall_setRealCoord(gconstpointer widget_ptr, MyGUI::FloatCoord& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setRealCoord(value);
	}

	
	static void ICall_getPosition(gconstpointer widget_ptr, MyGUI::IntPoint& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		value = widget->getPosition();
	}

	
	static void ICall_getSize(gconstpointer widget_ptr, MyGUI::IntSize& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		value = widget->getSize();
	}

	
	static const MyGUI::IntCoord& ICall_getCoord(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);

		return widget->getCoord();
	}


	
	static const MyGUI::IntPoint& ICall_getAbsolutePosition(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);

		return widget->getAbsolutePosition();
	}

	
	static void ICall_getAbsoluteRect(gconstpointer widget_ptr, MyGUI::IntRect& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		value = widget->getAbsoluteRect();
	}

	
	static void ICall_getAbsoluteCoord(gconstpointer widget_ptr, MyGUI::IntCoord& value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		value = widget->getAbsoluteCoord();
	}
	
	static void ICall_setAlign(gconstpointer widget_ptr, int value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		MyGUI::Align alignment((MyGUI::Align::Enum)value);
		widget->setAlign(alignment);
	}

	static int ICall_getAlign(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getAlign().GetValue();
	}


	
	static void ICall_setAlpha(gconstpointer widget_ptr, float value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setAlpha(value);
	}

	
	static float ICall_getAlpha(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getAlpha();
	}

	
	static void ICall_setInheritsAlpha(gconstpointer widget_ptr, bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setInheritsAlpha(value);
	}

	
	static bool ICall_getInheritsAlpha(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getInheritsAlpha();
	}


	
	static void ICall_setEnabled(gconstpointer widget_ptr, mono_bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setEnabled(c_iMonoBool_True == value);
	}

	
	static mono_bool ICall_getEnabled(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getEnabled();
	}



	// ----------------------------------- widget_input -----------------------------------------------------------------------


	
	static void ICall_setNeedToolTip(gconstpointer widget_ptr, bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setNeedToolTip(value);
	}

	
	static mono_bool ICall_getNeedToolTip(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getNeedToolTip();
	}

	
	static void ICall_setPointer(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(value, str);
		widget->setPointer(str);
	}

	
	static MonoString* ICall_getPointer(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return GuiUtility::StdStringToMonoString(widget->getPointer());
	}

	
	static void ICall_setNeedKeyFocus(gconstpointer widget_ptr, bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setNeedKeyFocus(value);
	}

	
	static mono_bool ICall_getNeedKeyFocus(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getNeedKeyFocus();
	}

	
	static void ICall_setNeedMouseFocus(gconstpointer widget_ptr, mono_bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setNeedMouseFocus(c_iMonoBool_True == value);
	}

	
	static mono_bool ICall_getNeedMouseFocus(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getNeedMouseFocus();
	}


	
	static void ICall_setInheritsPick(gconstpointer widget_ptr, mono_bool value)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		widget->setInheritsPick(c_iMonoBool_True == value);
	}

	
	static mono_bool ICall_getInheritsPick(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getInheritsPick();
	}


	
	static void ICall_setMaskPick(gconstpointer widget_ptr, MonoString* filename)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(filename, str);
		widget->setMaskPick(str);
	}

	
	static mono_bool ICall_isMaskPickInside(gconstpointer widget_ptr, MyGUI::IntPoint& point, MyGUI::IntCoord& coord)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->isMaskPickInside(point, coord);
	}

	
	static mono_bool ICall_getRootMouseFocus(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getRootMouseFocus();
	}

	
	static mono_bool ICall_getRootKeyFocus(gconstpointer widget_ptr)
	{
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return widget->getRootKeyFocus();
	}



	void ICallReg_ScriptGUI_Widget()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = 
			{{ "ScriptGUI.Widget::ICall_setVisible",				(void*)&ICall_setVisible}
			,{ "ScriptGUI.Widget::ICall_getVisible",				(void*)&ICall_getVisible}
			,{ "ScriptGUI.Widget::ICall_getInheritedVisible",		(void*)&ICall_getInheritedVisible}
			,{ "ScriptGUI.Widget::ICall_getType",					(void*)&ICall_getType}
			,{ "ScriptGUI.Widget::ICall_isType",					(void*)&ICall_isType}
			,{ "ScriptGUI.Widget::ICall_appendEvent",				(void*)&ICall_appendEvent}
			,{ "ScriptGUI.Widget::ICall_removeEvent",				(void*)&ICall_removeEvent}
			,{ "ScriptGUI.Widget::ICall_getName",					(void*)&ICall_getName}
			,{ "ScriptGUI.Widget::ICall_getClientCoord",			(void*)&ICall_getClientCoord}
			,{ "ScriptGUI.Widget::ICall_setColor",					(void*)&ICall_setColor}

			,{ "ScriptGUI.Widget::ICall_setPosition",				(void*)&ICall_setPosition}
			,{ "ScriptGUI.Widget::ICall_setSize",					(void*)&ICall_setSize}
			,{ "ScriptGUI.Widget::ICall_setCoord",					(void*)&ICall_setCoord}
			,{ "ScriptGUI.Widget::ICall_setRealPosition",			(void*)&ICall_setRealPosition}
			,{ "ScriptGUI.Widget::ICall_setRealSize",				(void*)&ICall_setRealSize}
			,{ "ScriptGUI.Widget::ICall_setRealCoord",				(void*)&ICall_setRealCoord}

			,{ "ScriptGUI.Widget::ICall_getPosition",				(void*)&ICall_getPosition}
			,{ "ScriptGUI.Widget::ICall_getSize",					(void*)&ICall_getSize}
			,{ "ScriptGUI.Widget::ICall_getCoord",					(void*)&ICall_getCoord}
			,{ "ScriptGUI.Widget::ICall_getAbsolutePosition",		(void*)&ICall_getAbsolutePosition}
			,{ "ScriptGUI.Widget::ICall_getAbsoluteRect",			(void*)&ICall_getAbsoluteRect}
			,{ "ScriptGUI.Widget::ICall_getAbsoluteCoord",			(void*)&ICall_getAbsoluteCoord}

			,{ "ScriptGUI.Widget::ICall_setAlign",					(void*)&ICall_setAlign}
			,{ "ScriptGUI.Widget::ICall_getAlign",					(void*)&ICall_getAlign}

			,{ "ScriptGUI.Widget::ICall_setAlpha",					(void*)&ICall_setAlpha}
			,{ "ScriptGUI.Widget::ICall_getAlpha",					(void*)&ICall_getAlpha}

			,{ "ScriptGUI.Widget::ICall_setInheritsAlpha",			(void*)&ICall_setInheritsAlpha}
			,{ "ScriptGUI.Widget::ICall_getInheritsAlpha",			(void*)&ICall_getInheritsAlpha}

			,{ "ScriptGUI.Widget::ICall_setEnabled",				(void*)&ICall_setEnabled}
			,{ "ScriptGUI.Widget::ICall_getEnabled",				(void*)&ICall_getEnabled}


			,{ "ScriptGUI.Widget::ICall_setNeedToolTip",			(void*)&ICall_setNeedToolTip}
			,{ "ScriptGUI.Widget::ICall_getNeedToolTip",			(void*)&ICall_getNeedToolTip}
			,{ "ScriptGUI.Widget::ICall_setPointer",				(void*)&ICall_setPointer}
			,{ "ScriptGUI.Widget::ICall_getPointer",				(void*)&ICall_getPointer}
			,{ "ScriptGUI.Widget::ICall_setNeedKeyFocus",			(void*)&ICall_setNeedKeyFocus}
			,{ "ScriptGUI.Widget::ICall_getNeedKeyFocus",			(void*)&ICall_getNeedKeyFocus}
			,{ "ScriptGUI.Widget::ICall_setNeedMouseFocus",			(void*)&ICall_setNeedMouseFocus}
			,{ "ScriptGUI.Widget::ICall_getNeedMouseFocus",			(void*)&ICall_getNeedMouseFocus}
			,{ "ScriptGUI.Widget::ICall_setInheritsPick",			(void*)&ICall_setInheritsPick}
			,{ "ScriptGUI.Widget::ICall_getInheritsPick",			(void*)&ICall_getInheritsPick}
			,{ "ScriptGUI.Widget::ICall_setMaskPick",				(void*)&ICall_setMaskPick}
			,{ "ScriptGUI.Widget::ICall_isMaskPickInside",			(void*)&ICall_isMaskPickInside}
			,{ "ScriptGUI.Widget::ICall_getRootMouseFocus",		(void*)&ICall_getRootMouseFocus}
			,{ "ScriptGUI.Widget::ICall_getRootKeyFocus",			(void*)&ICall_getRootKeyFocus}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}