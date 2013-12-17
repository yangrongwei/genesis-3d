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
	void ICallReg_ScriptGUI_ImageBox();

	static mono_bool ICall_setItemResource(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(value, str);
		return box->setItemResource(str);
	}


	static void ICall_setItemGroup(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(value, str);
		box->setItemGroup(str);
	}


	static void ICall_setItemName(gconstpointer widget_ptr, MonoString* value)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(value, str);
		box->setItemName(str);
	}

	
	static void ICall_setImageInfo(gconstpointer widget_ptr, MonoString* texture, MyGUI::IntCoord& coord, MyGUI::IntSize& tile)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(texture, str);
		box->setImageInfo(str, coord, tile);
	}

	
	static void ICall_setImageTexture(gconstpointer widget_ptr, MonoString* texture)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		std::string str;
		GuiUtility::MonoStringToStdString(texture, str);
		box->setImageTexture(str);
	}

	
	static void ICall_setImageRect(gconstpointer widget_ptr, MyGUI::IntRect& value)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setImageRect(value);
	}

	
	static void ICall_setImageCoord(gconstpointer widget_ptr, MyGUI::IntCoord& coord)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setImageCoord(coord);
	}

	
	static void ICall_setImageTile(gconstpointer widget_ptr, MyGUI::IntSize& tile)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setImageTile(tile);
	}

	
	static void ICall_setImageIndex(gconstpointer widget_ptr, size_t index)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setImageIndex(index);
	}

	
	static size_t ICall_getImageIndex(gconstpointer widget_ptr)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		return box->getImageIndex();
	}

	
	static size_t ICall_getItemCount(gconstpointer widget_ptr)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		return box->getItemCount();
	}

	
	static void ICall_setItemSelect(gconstpointer widget_ptr, size_t index)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setItemSelect(index);
	}

	
	static size_t ICall_getItemSelect(gconstpointer widget_ptr)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		return box->getItemSelect();
	}

	
	static void ICall_resetItemSelect(gconstpointer widget_ptr)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->resetItemSelect();
	}

	
	static void ICall_insertItem(gconstpointer widget_ptr, size_t index, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->insertItem(index, item);
	}

	
	static void ICall_addItem(gconstpointer widget_ptr, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->addItem(item);
	}

	
	static void ICall_setItem(gconstpointer widget_ptr, size_t index, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setItem(index, item);
	}

	
	static void ICall_deleteItem(gconstpointer widget_ptr, size_t index)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->deleteItem(index);
	}

	
	static void ICall_deleteAllItems(gconstpointer widget_ptr)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->deleteAllItems();
	}

	
	static void ICall_addItemFrame(gconstpointer widget_ptr, size_t index, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->addItemFrame(index, item);
	}

	
	static void ICall_insertItemFrame(gconstpointer widget_ptr, size_t index, size_t indexFrame, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->insertItemFrame(index, indexFrame, item);
	}

	
	static void ICall_addItemFrameDublicate(gconstpointer widget_ptr, size_t index, size_t indexSourceFrame)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->addItemFrameDublicate(index, indexSourceFrame);
	}

	
	static void ICall_insertItemFrameDublicate(gconstpointer widget_ptr, size_t index, size_t indexFrame, size_t indexSourceFrame)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->insertItemFrameDublicate(index, indexFrame, indexSourceFrame);
	}

	
	static void ICall_setItemFrame(gconstpointer widget_ptr, size_t index, size_t indexFrame, MyGUI::IntCoord& item)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setItemFrame(index, indexFrame, item);
	}

	
	static void ICall_deleteItemFrame(gconstpointer widget_ptr, size_t index, size_t indexFrame)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->deleteItemFrame(index, indexFrame);
	}

	
	static void ICall_deleteAllItemFrames(gconstpointer widget_ptr, size_t index)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->deleteAllItemFrames(index);
	}

	
	static void ICall_setItemFrameRate(gconstpointer widget_ptr, size_t index, float rate)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		box->setItemFrameRate(index, rate);
	}

	
	static float ICall_getItemFrameRate(gconstpointer widget_ptr, size_t index)
	{
		MyGUI::ImageBox* box = static_cast<MyGUI::ImageBox*>(widget_ptr);
		return box->getItemFrameRate(index);
	}



	void ICallReg_ScriptGUI_ImageBox()
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptGUI.ImageBox::ICall_setItemResource",				(void*)&ICall_setItemResource}
			,{ "ScriptGUI.ImageBox::ICall_setItemGroup",				(void*)&ICall_setItemGroup}
			,{ "ScriptGUI.ImageBox::ICall_setItemName",					(void*)&ICall_setItemName}

			,{ "ScriptGUI.ImageBox::ICall_setImageInfo",				(void*)&ICall_setImageInfo}
			,{ "ScriptGUI.ImageBox::ICall_setImageTexture",				(void*)&ICall_setImageTexture}
			,{ "ScriptGUI.ImageBox::ICall_setImageRect",				(void*)&ICall_setImageRect}
			,{ "ScriptGUI.ImageBox::ICall_setImageCoord",				(void*)&ICall_setImageCoord}
			,{ "ScriptGUI.ImageBox::ICall_setImageTile",				(void*)&ICall_setImageTile}
			,{ "ScriptGUI.ImageBox::ICall_setImageIndex",				(void*)&ICall_setImageIndex}
			,{ "ScriptGUI.ImageBox::ICall_getImageIndex",				(void*)&ICall_getImageIndex}
			,{ "ScriptGUI.ImageBox::ICall_getItemCount",				(void*)&ICall_getItemCount}
			,{ "ScriptGUI.ImageBox::ICall_setItemSelect",				(void*)&ICall_setItemSelect}
			,{ "ScriptGUI.ImageBox::ICall_getItemSelect",				(void*)&ICall_getItemSelect}
			,{ "ScriptGUI.ImageBox::ICall_resetItemSelect",				(void*)&ICall_resetItemSelect}
			,{ "ScriptGUI.ImageBox::ICall_insertItem",					(void*)&ICall_insertItem}
			,{ "ScriptGUI.ImageBox::ICall_addItem",						(void*)&ICall_addItem}
			,{ "ScriptGUI.ImageBox::ICall_setItem",						(void*)&ICall_setItem}
			,{ "ScriptGUI.ImageBox::ICall_deleteItem",					(void*)&ICall_deleteItem}
			,{ "ScriptGUI.ImageBox::ICall_deleteAllItems",				(void*)&ICall_deleteAllItems}
			,{ "ScriptGUI.ImageBox::ICall_addItemFrame",				(void*)&ICall_addItemFrame}
			,{ "ScriptGUI.ImageBox::ICall_insertItemFrame",				(void*)&ICall_insertItemFrame}
			,{ "ScriptGUI.ImageBox::ICall_addItemFrameDublicate",		(void*)&ICall_addItemFrameDublicate}
			,{ "ScriptGUI.ImageBox::ICall_insertItemFrameDublicate",	(void*)&ICall_insertItemFrameDublicate}
			,{ "ScriptGUI.ImageBox::ICall_setItemFrame",				(void*)&ICall_setItemFrame}
			,{ "ScriptGUI.ImageBox::ICall_deleteItemFrame",				(void*)&ICall_deleteItemFrame}
			,{ "ScriptGUI.ImageBox::ICall_deleteAllItemFrames",			(void*)&ICall_deleteAllItemFrames}
			,{ "ScriptGUI.ImageBox::ICall_setItemFrameRate",			(void*)&ICall_setItemFrameRate}
			,{ "ScriptGUI.ImageBox::ICall_getItemFrameRate",			(void*)&ICall_getItemFrameRate}
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}