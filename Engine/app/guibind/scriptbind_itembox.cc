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
	//using namespace MyGUI;
	void ICallReg_ScriptGUI_ItemBox( void );

	static void ICall_addItem(gconstpointer itembox_ptr, MonoObject* item_ptr_cs)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->addItem(itembox_ptr);
	}

	static void ICall_removeAllItems(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->removeAllItems();
	}

	
	static uint ICall_getItemCount(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		return itembox->getItemCount();
	}

	
	static void ICall_insertItemAt(gconstpointer itembox_ptr, uint index, MonoObject* item)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->insertItemAt(index, item);
	}

	
	static void ICall_removeItemAt(gconstpointer itembox_ptr, uint index)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->removeItemAt(index);
	}

	
	static void ICall_redrawItemAt(gconstpointer itembox_ptr, uint index)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->redrawItemAt(index);
	}

	
	static void ICall_redrawAllItems(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->redrawAllItems();
	}


	
	static uint ICall_getIndexSelected(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		return itembox->getIndexSelected();
	}

	
	static void ICall_setIndexSelected(gconstpointer itembox_ptr, uint index)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->setIndexSelected(index);
	}

	
	static void ICall_clearIndexSelected(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->clearIndexSelected();
	}

	
	static void ICall_setItemDataAt(gconstpointer itembox_ptr, uint index, MonoObject* data)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->setItemDataAt(index, data);
	}

	
	static void ICall_clearItemDataAt(gconstpointer itembox_ptr, uint index)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->clearItemDataAt(index);
	}

	
	static void ICall_setVerticalAlignment(gconstpointer itembox_ptr, mono_bool value)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->setVerticalAlignment(c_iMonoBool_True == value);
	}

	static mono_bool ICall_getVerticalAlignment(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		return itembox->getVerticalAlignment();
	}

	static size_t ICall_getIndexByWidget(gconstpointer itembox_ptr, gconstpointer widget_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		MyGUI::Widget* widget = static_cast<MyGUI::Widget*>(widget_ptr);
		return itembox->getIndexByWidget(widget);
	}

	static MyGUI::Widget* ICall_getWidgetDrag(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		return itembox->getWidgetDrag();
	}

	static MyGUI::Widget* ICall_getWidgetByIndex(gconstpointer itembox_ptr, uint index)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		return itembox->getWidgetByIndex(index);
	}

	static void ICall_resetDrag(gconstpointer itembox_ptr)
	{
		MyGUI::ItemBox* itembox = static_cast<MyGUI::ItemBox*>(itembox_ptr);
		itembox->resetDrag();
	}

	void ICallReg_ScriptGUI_ItemBox()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = 
		{{ "ScriptGUI.ItemBox::ICall_getItemCount",                 (void*)&ICall_getItemCount}
		,{ "ScriptGUI.ItemBox::ICall_addItem",						(void*)&ICall_addItem}
		,{ "ScriptGUI.ItemBox::ICall_insertItemAt",                 (void*)&ICall_insertItemAt}
		,{ "ScriptGUI.ItemBox::ICall_removeItemAt",                 (void*)&ICall_removeItemAt}
        ,{ "ScriptGUI.ItemBox::ICall_removeAllItems",               (void*)&ICall_removeAllItems}
		,{ "ScriptGUI.ItemBox::ICall_redrawItemAt",                 (void*)&ICall_redrawItemAt}
		,{ "ScriptGUI.ItemBox::ICall_redrawAllItems",               (void*)&ICall_redrawAllItems}
		,{ "ScriptGUI.ItemBox::ICall_getIndexSelected",            (void*)&ICall_getIndexSelected}
		,{ "ScriptGUI.ItemBox::ICall_setIndexSelected",             (void*)&ICall_setIndexSelected}
		,{ "ScriptGUI.ItemBox::ICall_clearIndexSelected",           (void*)&ICall_clearIndexSelected}
		,{ "ScriptGUI.ItemBox::ICall_setItemDataAt",                (void*)&ICall_setItemDataAt}
		,{ "ScriptGUI.ItemBox::ICall_clearItemDataAt",              (void*)&ICall_clearItemDataAt}

		,{ "ScriptGUI.ItemBox::ICall_setVerticalAlignment",			(void*)&ICall_setVerticalAlignment}
		,{ "ScriptGUI.ItemBox::ICall_getVerticalAlignment",			(void*)&ICall_getVerticalAlignment}
		,{ "ScriptGUI.ItemBox::ICall_getIndexByWidget",				(void*)&ICall_getIndexByWidget}
		,{ "ScriptGUI.ItemBox::ICall_getWidgetDrag",				(void*)&ICall_getWidgetDrag}
		,{ "ScriptGUI.ItemBox::ICall_getWidgetByIndex",				(void*)&ICall_getWidgetByIndex}
		,{ "ScriptGUI.ItemBox::ICall_resetDrag",					(void*)&ICall_resetDrag}
		,{ "ScriptGUI.ItemBox::ICall_clearItemDataAt",              (void*)&ICall_clearItemDataAt}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}