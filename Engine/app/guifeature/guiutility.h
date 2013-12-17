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
#ifndef __gui_utility_H__
#define __gui_utility_H__
#include "guifeature/gui.h"
#include "foundation/util/monotypes.h"

namespace App
{

	template<typename T> 
	 int GuiUtil_StructEnumToInt(T value)
	{
		return *((int*)(&value));
	}

	class WidgetType
	{
	public:
		enum _type			//inherit, sub type must be behind the parent. //
		{
			Unknown = 0,
			First,
			Widget = First,
			
			Canvas,			//Widget
			DDContainer,	//Widget
			ItemBox,		//DDContainer
			ImageBox,		//Widget
			ListBox,		//Widget
			MultiListItem,	//Widget
			MultiListBox,	//Widget
			MenuItem,		//Widget
			MenuControl,	//Widget
			MenuBar,		//MenuControl
			PopupMenu,		//MenuControl
			ProgressBar,	//Widget

			TextBox,		//Widget
			Button,			//TextBox
			EditBox,		//TextBox
			ComboBox,		//EditBox
			Window,			//TextBox
			
			TabControl,		//Widget
			TabItem,		//Widget
			ScrollBar,		//Widget
			ScrollView,		//Widget	

			Last = ScrollView,
		};
	};

	class EventType
	{
	public:
		enum _type
		{			
			MouseButtonPressed = 0,//widget
			MouseButtonReleased,//widget
			MouseButtonClick,//widget
			MouseButtonDoubleClick,//widget
			MouseLostFocus,//widget
			MouseSetFocus,//widget
			MouseDrag,//widget
			MouseMove,//widget
			MouseWheel,//widget

			KeyLostFocus,//widget
			KeySetFocus,//widget
			KeyButtonPressed,//widget
			KeyButtonReleased,//widget
			RootMouseChangeFocus,//widget
			RootKeyChangeFocus,//widget
			ToolTip,//widget

			ScrollChangePosition,// scroll bar

			StartDrag,//DDContainer
			RequestDrop,//DDContainer
			DropResult,//DDContainer
			ChangeDDState,//DDContainer
			RequestDragWidgetInfo,//DDContainer

			RequestCoordItem,//item box
			RequestCreateWidgetItem,//item box
			RequestDrawItem,//item box
			SelectItemAccept,//item box
			ChangeItemPosition,//item box
			MouseItemActivate,//item box
			NotifyItem,//item box

			ListSelectAccept,//list box
			ListChangePosition,//list box
			ListMouseItemActivate,//list box
			ListMouseItemFocus,//list box
			ListChangeScroll,//list box

			WindowButtonPressed,//window
			WindowChangeCoord,//window

			PreTextureChanges,//Canvas
			RequestUpdateCanvas,//Canvas
			Max = 0xffffffff
		};
	};


	//[StructLayout(LayoutKind.Sequential)]
	struct EventArg
	{
	public:
		//[MarshalAs(UnmanagedType.I4)]	
		int EventType;
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct ScrollChangePositionEventArg : public EventArg
	{
	public:
		//[MarshalAs(UnmanagedType.I4)]
		int Position;
	};

	// -------------------------------- widget event ----------------------------------
	//[StructLayout(LayoutKind.Sequential)]
	struct FocusEventArg : public EventArg//EventArg //Mouse Lost Focus, Mouse Set Focus, Key Lost Focus, Key Set Focus
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::Widget* new_widget; //MyGUI::Widget*

		MyGUI::Widget* new_widget_root; //MyGUI::Widget*
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct MouseDragEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		int Left;
		//[MarshalAs(UnmanagedType.I4)]
		int Top;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::MouseButton ButtonID;
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct MouseMoveEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		int Left;
		//[MarshalAs(UnmanagedType.I4)]
		int Top;
	};


	//[StructLayout(LayoutKind.Sequential)]
	struct MouseWheelEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		int Rel;
	};



	//[StructLayout(LayoutKind.Sequential)]
	struct MouseButtonEventArg : public EventArg//EventArg //Mouse Button Pressed, Mouse Button Released
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;

		//[MarshalAs(UnmanagedType.I4)]
		int Left;
		//[MarshalAs(UnmanagedType.I4)]
		int Top;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::MouseButton ButtonID;

	};

	//[StructLayout(LayoutKind.Sequential)]
	struct KeyButtonPressedEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::KeyCode Key;
		//[MarshalAs(UnmanagedType.U4)]
		MyGUI::Char Char;
	};


	//[StructLayout(LayoutKind.Sequential)]
	struct KeyButtonReleasedEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::KeyCode Key;
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct RootChangeFocusEventArg : public EventArg//EventArg      //Root Mouse Change Focus, Root Key Change Focus
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.Bool)]
		int Focus;
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct ToolTipEventArg : public EventArg//EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		const MyGUI::ToolTipInfo* Tool_Tip; //const MyGUI::ToolTipInfo& _info
	};

	// -------------------------------- DDContainer event ----------------------------------

	//[StructLayout(LayoutKind.Sequential)]
	struct DragEventArg : public EventArg     //StartDrag, RequestDrop, DropResult
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		const MyGUI::DDItemInfo* DDItemInfo;  //const MyGUI::DDItemInfo&
		//[MarshalAs(UnmanagedType.Bool)]
		bool* result;
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct ChangeDDStateEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::DDItemState State;//MyGUI::DDItemState 
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct RequestDragWidgetInfoEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		//EventArg BaseArg;

		//[MarshalAs(UnmanagedType.Struct)]
		MyGUI::Widget** Item;//MyGUI::Widget*&

		//[MarshalAs(UnmanagedType.Struct)]
		MyGUI::IntCoord* Dimension;
	};
	// -------------------------------- Item Box event ----------------------------------
	//[StructLayout(LayoutKind.Sequential)]
	struct RequestCoordWidgetItemEventArg : public EventArg
	{
	public:
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::IntCoord* Coord;
		//[MarshalAs(UnmanagedType.Bool)]
		int drop;// int 作为bool型使用
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct RequestCreateWidgetItemEventArg : public EventArg
	{
	public:
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::Widget* Item; //MyGUI::Widget*
	};

	//[StructLayout(LayoutKind.Sequential)]
	struct RequestDrawItemEventArg : public EventArg
	{
	public:
		//[MarshalAs(UnmanagedType.I4)]
		MyGUI::Widget* Item; //MyGUI::Widget*
		//[MarshalAs(UnmanagedType.I4)]
		const MyGUI::IBDrawItemInfo* DrawItemInfo; //const MyGUI::IBDrawItemInfo& _data
	};


	//[StructLayout(LayoutKind.Sequential)]
	struct ItemEventArg : public EventArg//SelectItemAccept, ChangeItemPosition
	{
		//[MarshalAs(UnmanagedType.I4)]
		uint index; //

	};

	//[StructLayout(LayoutKind.Sequential)]
	struct NotifyItemEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.I4)]
		const MyGUI::IBNotifyItemData* IBNotifyItemData;//const MyGUI::IBNotifyItemData&

	};

	// -------------------------------- List Box event ----------------------------------
	//[StructLayout(LayoutKind.Sequential)]
	struct ListBoxEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.U4)]
		size_t index;
	};
    // -------------------------------- Window event ----------------------------------

	//[StructLayout(LayoutKind.Sequential)]
	struct WindowButtonPressedEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.U4)]
		MonoString* Name;
	};

	// -------------------------------- Canvas event ----------------------------------
	//[StructLayout(LayoutKind.Sequential)]
	struct RequestUpdateCanvasEventArg : public EventArg
	{
		//[MarshalAs(UnmanagedType.Struct)]
		EventArg BaseArg;
		//[MarshalAs(UnmanagedType.I4)]
		const MyGUI::Canvas::Event* CanvesEvent;//const MyGUI::Canvas::Event&
	};


	class GuiUtility
	{

	public:
		static bool IsWidgetType(MyGUI::Widget* widget, WidgetType::_type wt);
		static bool SetEvent(MyGUI::Widget* widget, EventType::_type event_type, bool advise);


		static MonoString* StdStringToMonoString(const std::string& std_string);
		static MonoString* UStringToMonoString(const MyGUI::UString& ustring);

		static void MonoStringToUString(MonoString* mono_string, MyGUI::UString& out);
		static void MonoStringToStdString(MonoString* mono_string, std::string& out);
	private:
		static MyGUI::Widget* getRootWidget(MyGUI::Widget* widget);

		static void onScrollChangePosition(MyGUI::ScrollBar* scroll_bar, size_t position);

		// --------------------------------------- widget event ------------------------------------------------
		static void onMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new);
		static void onMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
		static void onMouseDrag(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
		static void onMouseMove(MyGUI::Widget* _sender, int _left, int _top);
		static void onMouseWheel(MyGUI::Widget* _sender, int _rel);
		static void onMouseButtonPressed(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
		static void onMouseButtonReleased(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);		
		static void onMouseButtonClick(MyGUI::Widget* _sender);
		static void onMouseButtonDoubleClick(MyGUI::Widget* _sender);
		static void onKeyLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new);
		static void onKeySetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
		static void onKeyButtonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);
		static void onKeyButtonReleased(MyGUI::Widget* _sender, MyGUI::KeyCode _key);
		static void onRootMouseChangeFocus(MyGUI::Widget* _sender, bool _focus);
		static void onRootKeyChangeFocus(MyGUI::Widget* _sender, bool _focus);
		static void onToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info);
		// --------------------------------------- DDContainer event ------------------------------------------------
		static void onStartDrag(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result);
		static void onRequestDrop(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result);
		static void onDropResult(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool _result);
		static void onChangeDDState(MyGUI::DDContainer* _sender, MyGUI::DDItemState _state);
		static void onRequestDragWidgetInfo(MyGUI::DDContainer* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension);

		// --------------------------------------- item box event ------------------------------------------------
		static void onRequestCoordWidgetItem(MyGUI::ItemBox* item_box, MyGUI::IntCoord& _coord, bool _drop);
		static void onRequestCreateWidgetItem(MyGUI::ItemBox* item_box, MyGUI::Widget* item);
		static void onRequestDrawItem(MyGUI::ItemBox* item_box, MyGUI::Widget* item, const MyGUI::IBDrawItemInfo& _data);

		static void onSelectItemAccept(MyGUI::ItemBox* _sender, size_t _index);
		static void onChangeItemPosition(MyGUI::ItemBox* _sender, size_t _index);
		static void onMouseItemActivate(MyGUI::ItemBox* _sender, size_t _index);
		static void onNotifyItem(MyGUI::ItemBox* _sender, const MyGUI::IBNotifyItemData& _info);

		// --------------------------------------- list box event ------------------------------------------------
		static void onListSelectAccept(MyGUI::ListBox* _sender, size_t _index);
		static void onListChangePosition(MyGUI::ListBox* _sender, size_t _index);
		static void onListMouseItemActivate(MyGUI::ListBox* _sender, size_t _index);
		static void onListMouseItemFocus(MyGUI::ListBox* _sender, size_t _index);
		static void onListChangeScroll(MyGUI::ListBox* _sender, size_t _index);

		// -------------------------------- Window event ----------------------------------
		static void onWindowButtonPressed(MyGUI::Window* _sender, const std::string& _name);
		static void onWindowChangeCoord(MyGUI::Window* _sender);

		// -------------------------------- Canvas event ----------------------------------
		static void onPreTextureChanges(MyGUI::Canvas* _canvas);
		static void onRequestUpdateCanvas(MyGUI::Canvas* _canvas, MyGUI::Canvas::Event _event);
		//static void on;
		//static void on;
		//static void on;
		//static void on;

		GuiUtility()
		{
		}
	};



}


#endif //__gui_utility_H__