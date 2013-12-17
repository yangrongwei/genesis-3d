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
	void ICallReg_ScriptGUI_ListBox();

	
	static size_t ICall_getItemCount(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return list_box->getItemCount();
	}
	
	static void ICall_insertItemAt(gconstpointer widget_ptr, size_t _index, MonoString* _name, MonoObject* _data)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(_name, str);
		list_box->insertItemAt(_index, str, _data);
	}

	
	static void ICall_addItem(gconstpointer widget_ptr, MonoString* _name, MonoObject* _data)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(_name, str);
		list_box->addItem(str, _data);
	}

	
	static void ICall_removeItemAt(gconstpointer widget_ptr, size_t _index)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->_removeItemAt(_index);
	}

	
	static void ICall_removeAllItems(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->removeAllItems();
	}

	
	static void ICall_swapItemsAt(gconstpointer widget_ptr, size_t _index1, size_t _index2)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->swapItemsAt(_index1, _index2);
	}

	
	static size_t ICall_findItemIndexWith(gconstpointer widget_ptr, MonoString* _name)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(_name, str);
		return list_box->findItemIndexWith(str);
	}

	
	static size_t ICall_getIndexSelected(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return list_box->getIndexSelected();
	}

	
	static void ICall_setIndexSelected(gconstpointer widget_ptr, size_t _index)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->setIndexSelected(_index);
	}

	
	static void ICall_clearIndexSelected(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->clearIndexSelected();
	}


	
	static void ICall_clearItemDataAt(gconstpointer widget_ptr, size_t _index)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->clearItemDataAt(_index);
	}

	
	static void ICall_setItemNameAt(gconstpointer widget_ptr, size_t _index, MonoString* _name)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		MyGUI::UString str;
		GuiUtility::MonoStringToUString(_name, str);
		list_box->setItemNameAt(_index, str);
	}

	
	static MonoString* ICall_getItemNameAt(gconstpointer widget_ptr, size_t _index)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return GuiUtility::UStringToMonoString(list_box->getItemNameAt(_index));
	}

	
	static void ICall_beginToItemAt(gconstpointer widget_ptr, size_t _index)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->beginToItemAt(_index);
	}

	
	static void ICall_beginToItemFirst(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->beginToItemFirst();
	}

	
	static void ICall_beginToItemLast(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->beginToItemLast();
	}

	
	static void ICall_beginToItemSelected(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->beginToItemSelected();
	}

	
	static mono_bool ICall_isItemVisibleAt(gconstpointer widget_ptr, size_t _index, mono_bool _fill)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return list_box->isItemVisibleAt(_index,  c_iMonoBool_True == _fill);
	}

	
	static mono_bool ICall_isItemSelectedVisible(gconstpointer widget_ptr, mono_bool _fill)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return list_box->isItemSelectedVisible(c_iMonoBool_True == _fill);
	}

	
	static void ICall_setScrollVisible(gconstpointer widget_ptr, mono_bool _visible)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->setScrollVisible(c_iMonoBool_True == _visible);
	}

	
	static void ICall_setScrollPosition(gconstpointer widget_ptr, size_t _position)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		list_box->setScrollPosition(_position);
	}

	
	static int ICall_getOptimalHeight(gconstpointer widget_ptr)
	{
		MyGUI::ListBox* list_box = static_cast<MyGUI::ListBox*>(widget_ptr);
		return list_box->getOptimalHeight();
	}

	void ICallReg_ScriptGUI_ListBox()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptGUI.ListBox::ICall_getItemCount",					(void*)&ICall_getItemCount}
			,{ "ScriptGUI.ListBox::ICall_insertItemAt",					(void*)&ICall_insertItemAt}
			,{ "ScriptGUI.ListBox::ICall_addItem",						(void*)&ICall_addItem}
			,{ "ScriptGUI.ListBox::ICall_removeItemAt",					(void*)&ICall_removeItemAt}
			,{ "ScriptGUI.ListBox::ICall_removeAllItems",				(void*)&ICall_removeAllItems}
			,{ "ScriptGUI.ListBox::ICall_swapItemsAt",					(void*)&ICall_swapItemsAt}
			,{ "ScriptGUI.ListBox::ICall_findItemIndexWith",			(void*)&ICall_findItemIndexWith}
			,{ "ScriptGUI.ListBox::ICall_getIndexSelected",				(void*)&ICall_getIndexSelected}
			,{ "ScriptGUI.ListBox::ICall_setIndexSelected",				(void*)&ICall_setIndexSelected}
			,{ "ScriptGUI.ListBox::ICall_clearIndexSelected",			(void*)&ICall_clearIndexSelected}
			,{ "ScriptGUI.ListBox::ICall_clearItemDataAt",				(void*)&ICall_clearItemDataAt}
			,{ "ScriptGUI.ListBox::ICall_setItemNameAt",				(void*)&ICall_setItemNameAt}
			,{ "ScriptGUI.ListBox::ICall_getItemNameAt",				(void*)&ICall_getItemNameAt}
			,{ "ScriptGUI.ListBox::ICall_beginToItemAt",				(void*)&ICall_beginToItemAt}
			,{ "ScriptGUI.ListBox::ICall_beginToItemFirst",				(void*)&ICall_beginToItemFirst}
			,{ "ScriptGUI.ListBox::ICall_beginToItemLast",				(void*)&ICall_beginToItemLast}
			,{ "ScriptGUI.ListBox::ICall_beginToItemSelected",			(void*)&ICall_beginToItemSelected}
			,{ "ScriptGUI.ListBox::ICall_isItemVisibleAt",				(void*)&ICall_isItemVisibleAt}
			,{ "ScriptGUI.ListBox::ICall_isItemSelectedVisible",		(void*)&ICall_isItemSelectedVisible}
			,{ "ScriptGUI.ListBox::ICall_setScrollVisible",				(void*)&ICall_setScrollVisible}
			,{ "ScriptGUI.ListBox::ICall_setScrollPosition",			(void*)&ICall_setScrollPosition}
			,{ "ScriptGUI.ListBox::ICall_getOptimalHeight",				(void*)&ICall_getOptimalHeight}

		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}