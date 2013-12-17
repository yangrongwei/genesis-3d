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
#include "guifeature/guiutility.h"
#include "foundation/util/monoapi.h"


namespace App
{

// ----------------------------- event class -------------------------------

	template<typename Delegate, typename Function>
	void _reg_event(MyGUI::Widget* widget, EventType::_type event_type, bool advise, Delegate& _delegate, Function& _function)
	{
		if (advise)
		{
			_delegate += MyGUI::newDelegate(&_function);
		}
		else
		{
			_delegate -= MyGUI::newDelegate(&_function);
		}
	}
	template<typename Delegate, typename Function>
	void _reg_event2(MyGUI::Widget* widget, EventType::_type event_type, bool advise, Delegate& _delegate, Function& _function)
	{
		if (advise)
		{
			_delegate = MyGUI::newDelegate(&_function);
		}
		else
		{
			_delegate = NULL;
		}
	}
	inline void _sendEvent(MyGUI::Widget* widget, EventArg* arg)
	{
		GUIServer* server = GUIServer::Instance();
		if (server)
		{
			server->GetGuiEvent().OnEvent(widget, arg);
		}
	}
	MyGUI::Widget* GuiUtility::getRootWidget(MyGUI::Widget* widget)
	{
		MyGUI::Widget* root = widget;
		MyGUI::Widget* temp = widget;

		while (NULL != temp)
		{
			root = temp;
			temp = temp->getParent();
		}
		return root;
	}


	bool GuiUtility::IsWidgetType(MyGUI::Widget* widget, WidgetType::_type wt)
	{
		bool ret = false;
		switch (wt)
		{
		case WidgetType::Widget:
			ret = widget->isType<MyGUI::Widget>();
			break;
		case WidgetType::Canvas:
			ret = widget->isType<MyGUI::Canvas>();
			break;
		case WidgetType::DDContainer:
			ret = widget->isType<MyGUI::DDContainer>();
			break;
		case WidgetType::ItemBox:
			ret = widget->isType<MyGUI::ItemBox>();
			break;

		case WidgetType::ImageBox:
			ret = widget->isType<MyGUI::ImageBox>();
			break;
		case WidgetType::ListBox:
			ret = widget->isType<MyGUI::ListBox>();
			break;
		case WidgetType::MultiListItem:
			ret = widget->isType<MyGUI::MultiListItem>();
			break;
		case WidgetType::MultiListBox:
			ret = widget->isType<MyGUI::MultiListBox>();
			break;
		case WidgetType::MenuItem:
			ret = widget->isType<MyGUI::MenuItem>();
			break;
		case WidgetType::MenuControl:
			ret = widget->isType<MyGUI::MenuControl>();
			break;
		case WidgetType::MenuBar:
			ret = widget->isType<MyGUI::MenuBar>();
			break;
		case WidgetType::PopupMenu:
			ret = widget->isType<MyGUI::PopupMenu>();
			break;
		case WidgetType::ProgressBar:
			ret = widget->isType<MyGUI::ProgressBar>();
			break;

		case WidgetType::TextBox:
			ret = widget->isType<MyGUI::TextBox>();
			break;
		case WidgetType::Button:
			ret = widget->isType<MyGUI::Button>();
			break;
		case WidgetType::EditBox:
			ret = widget->isType<MyGUI::EditBox>();
			break;
		case WidgetType::ComboBox:
			ret = widget->isType<MyGUI::ComboBox>();
			break;

		case WidgetType::Window:
			ret = widget->isType<MyGUI::Window>();
			break;

		case WidgetType::TabControl:
			ret = widget->isType<MyGUI::TabControl>();
			break;
		case WidgetType::TabItem:
			ret = widget->isType<MyGUI::TabItem>();
			break;
		case WidgetType::ScrollBar:
			ret = widget->isType<MyGUI::ScrollBar>();
			break;
		case WidgetType::ScrollView:
			ret = widget->isType<MyGUI::ScrollView>();
			break;
		}

		return ret;
	}


// -------------------- event -------------------------------------------
	bool GuiUtility::SetEvent(MyGUI::Widget* widget, EventType::_type event_type, bool advise)
	{
		switch(event_type)
		{

		case EventType::MouseButtonPressed:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseButtonPressed, onMouseButtonPressed);
			}
			break;//widget
		case EventType::MouseButtonReleased:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseButtonReleased, onMouseButtonReleased);
			}
			break;//widget
		case EventType::MouseButtonClick:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseButtonClick, onMouseButtonClick);
			}
			break;//widget
		case EventType::MouseButtonDoubleClick:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseButtonDoubleClick, onMouseButtonDoubleClick);
			}
			break;//widget
		case EventType::MouseLostFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseLostFocus, onMouseLostFocus);
			}
			break;//widget
		case EventType::MouseSetFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseSetFocus, onMouseSetFocus);
			}
			break;//widget
		case EventType::MouseDrag:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseDrag, onMouseDrag);
			}
			break;//widget
		case EventType::MouseMove:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseMove, onMouseMove);
			}
			break;//widget
		case EventType::MouseWheel:
			{
				_reg_event(widget, event_type, advise, widget->eventMouseWheel, onMouseWheel);
			}
			break;//widget

		case EventType::KeyLostFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventKeyLostFocus, onKeyLostFocus);
			}
			break;//widget
		case EventType::KeySetFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventKeySetFocus, onKeySetFocus);
			}
			break;//widget
		case EventType::KeyButtonPressed:
			{
				_reg_event(widget, event_type, advise, widget->eventKeyButtonPressed, onKeyButtonPressed);
			}
			break;//widget
		case EventType::KeyButtonReleased:
			{
				_reg_event(widget, event_type, advise, widget->eventKeyButtonReleased, onKeyButtonReleased);
			}
			break;//widget
		case EventType::RootMouseChangeFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventRootMouseChangeFocus, onRootMouseChangeFocus);
			}
			break;//widget
		case EventType::RootKeyChangeFocus:
			{
				_reg_event(widget, event_type, advise, widget->eventRootKeyChangeFocus, onRootKeyChangeFocus);
			}
			break;//widget
		case EventType::ToolTip:
			{
				_reg_event(widget, event_type, advise, widget->eventToolTip, onToolTip);
			}
			break;//widget


		case EventType::ScrollChangePosition:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ScrollBar>()->eventScrollChangePosition, onScrollChangePosition);
			}
			break;
		case EventType::StartDrag:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::DDContainer>()->eventStartDrag, onStartDrag);
			}
			break;

		case EventType::RequestDrop:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::DDContainer>()->eventRequestDrop, onRequestDrop);
			}
			break;

		case EventType::DropResult:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::DDContainer>()->eventDropResult, onDropResult);
			}
			break;
		case EventType::ChangeDDState:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::DDContainer>()->eventChangeDDState, onChangeDDState);
			}
			break;
		case EventType::RequestDragWidgetInfo:
			{
				_reg_event2(widget, event_type, advise, widget->castType<MyGUI::DDContainer>()->requestDragWidgetInfo, onRequestDragWidgetInfo);
			}
			break;



		case EventType::RequestCoordItem:
			{
				_reg_event2(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->requestCoordItem, onRequestCoordWidgetItem);
			}
			break;
		case EventType::RequestCreateWidgetItem:
			{
				_reg_event2(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->requestCreateWidgetItem, onRequestCreateWidgetItem);
			}
			break;
		case EventType::RequestDrawItem:
			{
				_reg_event2(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->requestDrawItem, onRequestDrawItem);
			}
			break;
		case EventType::SelectItemAccept:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->eventSelectItemAccept, onSelectItemAccept);
			}
			break;
		case EventType::ChangeItemPosition:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->eventChangeItemPosition, onChangeItemPosition);
			}
			break;
		case EventType::MouseItemActivate:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->eventMouseItemActivate, onMouseItemActivate);
			}
			break;
		case EventType::NotifyItem:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ItemBox>()->eventNotifyItem, onNotifyItem);
			}
			break;

		// --------------------------------------- list box event ------------------------------------------------
		case EventType::ListSelectAccept:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ListBox>()->eventListSelectAccept, onListSelectAccept);
			}
			break;

		case EventType::ListChangePosition:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ListBox>()->eventListChangePosition, onListChangePosition);
			}
			break;

		case EventType::ListMouseItemActivate:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ListBox>()->eventListMouseItemActivate, onListMouseItemActivate);
			}
			break;

		case EventType::ListMouseItemFocus:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ListBox>()->eventListMouseItemFocus, onListMouseItemFocus);
			}
			break;

		case EventType::ListChangeScroll:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::ListBox>()->eventListChangeScroll, onListChangeScroll);
			}
			break;
    // -------------------------------- Window event ----------------------------------
		case EventType::WindowButtonPressed:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::Window>()->eventWindowButtonPressed, onWindowButtonPressed);
			}
			break;
		case EventType::WindowChangeCoord:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::Window>()->eventWindowChangeCoord, onWindowChangeCoord);
			}
			break;
	// -------------------------------- Canvas event ----------------------------------
		case EventType::PreTextureChanges:
			{
				_reg_event(widget, event_type, advise, widget->castType<MyGUI::Canvas>()->eventPreTextureChanges, onPreTextureChanges);
			}
		case EventType::RequestUpdateCanvas:
			{
				_reg_event2(widget, event_type, advise, widget->castType<MyGUI::Canvas>()->requestUpdateCanvas, onRequestUpdateCanvas);
			}
			break;
		default:
			break;
		}

		return true;
	}

// ------------------- String -----------------------------------------------------


	MonoString* GuiUtility::StdStringToMonoString(const std::string& std_string)
	{
		return mono_string_new_wrapper(std_string.c_str());
	}
	MonoString* GuiUtility::UStringToMonoString(const MyGUI::UString& ustring)
	{
		return mono_string_new_utf16(mono_domain_get(), ustring.c_str(), ustring.length());
	}

	void GuiUtility::MonoStringToStdString(MonoString* mono_string, std::string& out)
	{
		char* ptr = mono_string_to_utf8( mono_string );
		out = ptr;
		mono_free(ptr);
	}

	void GuiUtility::MonoStringToUString(MonoString* mono_string, MyGUI::UString& out)
	{
		MyGUI::UString::code_point* ptr = mono_string_to_utf16(mono_string);
		out = ptr;//mono_string_to_utf16(mono_string);
		mono_free(ptr);
	}


	// -------------------------------- widget event -----------


	void GuiUtility::onMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
	{
		static FocusEventArg arg;
		arg.EventType = EventType::MouseLostFocus;
		arg.new_widget = _new;
		arg.new_widget_root = getRootWidget(_new);

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
	{
		static FocusEventArg arg;
		arg.EventType = EventType::MouseSetFocus;
		arg.new_widget = _old;
		arg.new_widget_root = getRootWidget(_old);
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseDrag(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
	{
		static MouseDragEventArg arg;
		arg.EventType = EventType::MouseDrag;
		arg.Left = _left;
		arg.Top = _top;
		arg.ButtonID = _id;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseMove(MyGUI::Widget* _sender, int _left, int _top)
	{
		static MouseMoveEventArg arg;
		arg.EventType = EventType::MouseMove;
		arg.Left = _left;
		arg.Top = _top;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseWheel(MyGUI::Widget* _sender, int _rel)
	{
		static MouseWheelEventArg arg;
		arg.EventType = EventType::MouseWheel;
		arg.Rel = _rel;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseButtonPressed(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
	{
		static MouseButtonEventArg arg;
		arg.EventType = EventType::MouseButtonPressed;
		arg.Left = _left;
		arg.Top = _top;
		arg.ButtonID = _id;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseButtonReleased(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
	{
		static MouseButtonEventArg arg;
		arg.EventType = EventType::MouseButtonReleased;
		arg.Left = _left;
		arg.Top = _top;
		arg.ButtonID = _id;
		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onMouseButtonClick(MyGUI::Widget* _sender)
	{
		static EventArg arg;
		arg.EventType = EventType::MouseButtonClick;

		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onMouseButtonDoubleClick(MyGUI::Widget* _sender)
	{
		static EventArg arg;
		arg.EventType = EventType::MouseButtonDoubleClick;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onKeyLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
	{
		static FocusEventArg arg;
		arg.EventType = EventType::KeyLostFocus;
		arg.new_widget = _new;
		arg.new_widget_root = getRootWidget(_new);

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onKeySetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
	{
		static FocusEventArg arg;
		arg.EventType = EventType::KeySetFocus;		
		arg.new_widget = _old;
		arg.new_widget_root = getRootWidget(_old);

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onKeyButtonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char)
	{
		static KeyButtonPressedEventArg arg;
		arg.EventType = EventType::KeyButtonPressed;
		arg.Key = _key;
		arg.Char = _char;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onKeyButtonReleased(MyGUI::Widget* _sender, MyGUI::KeyCode _key)
	{
		static KeyButtonReleasedEventArg arg;
		arg.EventType = EventType::KeyButtonReleased;
		arg.Key = _key;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onRootMouseChangeFocus(MyGUI::Widget* _sender, bool _focus)
	{
		static RootChangeFocusEventArg arg;
		arg.EventType = EventType::RootMouseChangeFocus;
		arg.Focus = _focus;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onRootKeyChangeFocus(MyGUI::Widget* _sender, bool _focus)
	{
		static RootChangeFocusEventArg arg;
		arg.EventType = EventType::RootKeyChangeFocus;
		arg.Focus = _focus;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info)
	{
		static ToolTipEventArg arg;
		arg.EventType = EventType::ToolTip;
		arg.Tool_Tip = &_info;
		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onScrollChangePosition(MyGUI::ScrollBar* scroll_bar, size_t position)
	{
		static ScrollChangePositionEventArg arg;
		arg.EventType = EventType::ScrollChangePosition;


		_sendEvent(scroll_bar, &arg);
	}

	// --------------------------------------- DDContainer event ------------------------------------------------
	void GuiUtility::onStartDrag(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result)
	{
		static DragEventArg arg;
		arg.EventType = EventType::StartDrag;
		arg.DDItemInfo = &_info;
		arg.result = & _result;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onRequestDrop(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result)	
	{
		static DragEventArg arg;
		arg.EventType = EventType::RequestDrop;
		arg.DDItemInfo = &_info;
		arg.result = & _result;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onDropResult(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool _result)	
	{
		static DragEventArg arg;
		arg.EventType = EventType::DropResult;
		arg.DDItemInfo = &_info;
		arg.result = & _result;

		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onChangeDDState(MyGUI::DDContainer* _sender, MyGUI::DDItemState _state)
	{
		static ChangeDDStateEventArg arg;
		arg.EventType = EventType::ChangeDDState;
		arg.State = _state;

		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onRequestDragWidgetInfo(MyGUI::DDContainer* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension)
	{
		
		static RequestDragWidgetInfoEventArg arg;
		arg.EventType = EventType::RequestDragWidgetInfo;
		arg.Item = &_item;
		arg.Dimension = &_dimension;

		_sendEvent(_sender, &arg);
	}
	// -------------------------------- item box event -----------
	void GuiUtility::onRequestCoordWidgetItem(MyGUI::ItemBox* item_box, MyGUI::IntCoord& _coord, bool _drop)
	{
		static RequestCoordWidgetItemEventArg arg;
		arg.EventType = EventType::RequestCoordItem;
		arg.Coord = &_coord;
		arg.drop = (int)_drop;

		_sendEvent(item_box, &arg);
	}

	void GuiUtility::onRequestCreateWidgetItem(MyGUI::ItemBox* item_box, MyGUI::Widget* item)
	{
		static RequestCreateWidgetItemEventArg arg;
		arg.EventType = EventType::RequestCreateWidgetItem;
		arg.Item = item;

		_sendEvent(item_box, &arg);
	}

	void GuiUtility::onRequestDrawItem(MyGUI::ItemBox* item_box, MyGUI::Widget* item, const MyGUI::IBDrawItemInfo& _data)
	{
		static RequestDrawItemEventArg arg;
		arg.EventType = EventType::RequestDrawItem;
		arg.Item = item;
		arg.DrawItemInfo = &_data;

		_sendEvent(item_box, &arg);
	}

	void GuiUtility::onSelectItemAccept(MyGUI::ItemBox* _sender, size_t _index)
	{
		static ItemEventArg arg;
		arg.EventType = EventType::SelectItemAccept;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onChangeItemPosition(MyGUI::ItemBox* _sender, size_t _index)
	{
		static ItemEventArg arg;
		arg.EventType = EventType::ChangeItemPosition;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index)
	{
		static ItemEventArg arg;
		arg.EventType = EventType::MouseItemActivate;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onNotifyItem(MyGUI::ItemBox* _sender, const MyGUI::IBNotifyItemData& _info)
	{
		static NotifyItemEventArg arg;
		arg.EventType = EventType::NotifyItem;
		arg.IBNotifyItemData = &_info;
		_sendEvent(_sender, &arg);
	}




	// --------------------------------------- list box event ------------------------------------------------
	void GuiUtility::onListSelectAccept(MyGUI::ListBox* _sender, size_t _index)
	{
		static ListBoxEventArg arg;
		arg.EventType = EventType::ListSelectAccept;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}

	void GuiUtility::onListChangePosition(MyGUI::ListBox* _sender, size_t _index)
	{
		static ListBoxEventArg arg;
		arg.EventType = EventType::ListChangePosition;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onListMouseItemActivate(MyGUI::ListBox* _sender, size_t _index)
	{
		static ListBoxEventArg arg;
		arg.EventType = EventType::MouseItemActivate;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onListMouseItemFocus(MyGUI::ListBox* _sender, size_t _index)
	{
		static ListBoxEventArg arg;
		arg.EventType = EventType::ListMouseItemFocus;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onListChangeScroll(MyGUI::ListBox* _sender, size_t _index)
	{
		static ListBoxEventArg arg;
		arg.EventType = EventType::ListChangeScroll;
		arg.index = _index;
		_sendEvent(_sender, &arg);
	}
	// -------------------------------- Window event ----------------------------------
	void GuiUtility::onWindowButtonPressed(MyGUI::Window* _sender, const std::string& _name)
	{
		static WindowButtonPressedEventArg arg;
		arg.EventType = EventType::WindowButtonPressed;
		arg.Name = GuiUtility::StdStringToMonoString(_name);
		_sendEvent(_sender, &arg);
	}
	void GuiUtility::onWindowChangeCoord(MyGUI::Window* _sender)
	{
		static EventArg arg;
		arg.EventType = EventType::WindowChangeCoord;
		_sendEvent(_sender, &arg);
	}
	// -------------------------------- Canvas event ----------------------------------
	void GuiUtility::onPreTextureChanges(MyGUI::Canvas* _canvas)
	{
		static EventArg arg;
		arg.EventType = EventType::PreTextureChanges;
		_sendEvent(_canvas, &arg);
	}
	void GuiUtility::onRequestUpdateCanvas(MyGUI::Canvas* _canvas, MyGUI::Canvas::Event _event)
	{
		static RequestUpdateCanvasEventArg arg;
		arg.EventType = EventType::RequestUpdateCanvas;
		arg.CanvesEvent = &_event;
		_sendEvent(_canvas, &arg);
	}

}