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
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;

namespace ScriptGUI
{
    internal class ListBox : Widget
    {
        internal ListBox(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.ListBox)
        {

        }

        ~ListBox()
        {
            RemoveAllItems();
            clearEventsWidthOutParent();
        }
        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandleListSelectAccept, EventType.ListSelectAccept);
            clearEvent(ref mHandleListChangePosition, EventType.ListChangePosition);
            clearEvent(ref mHandleListMouseItemActivate, EventType.ListMouseItemActivate);
            clearEvent(ref mHandleListMouseItemFocus, EventType.ListMouseItemFocus);
            clearEvent(ref mHandleListChangeScroll, EventType.ListChangeScroll);
        }
        internal override void Dispose()
        {
            RemoveAllItems();
            clearEventsWidthOutParent();
            base.Dispose();
        }

        //------------------------------------------------------------------------------//
		/** @name Item Methods.
			Methods used to manipulate items.
		*/
		//@{
		//! Get number of items
		internal int ItemCount
        {
            get
            {
                return mItemInfos.Count;
            }
        }

		//! Insert an item into a array at a specified position
		internal void InsertItemAt(int index,  string name, object data)
        {
            ItemInfo info = new ItemInfo(name, data);
            mItemInfos.Insert(index, info);
            ICall_insertItemAt(mInstance.Ptr, (uint)index, name, info);
        }

		//! Add an item to the end of a array
		internal void AddItem( string name, object data)
        {
            ItemInfo info = new ItemInfo(name, data);
            mItemInfos.Add(info);
            ICall_addItem(mInstance.Ptr, name, info);
        }

		//! Remove item at a specified position
		internal void RemoveItemAt(int index)
        {
            mItemInfos.RemoveAt(index);
            ICall_removeItemAt(mInstance.Ptr, (uint)index);
        }

		//! Remove all items
		internal void RemoveAllItems()
        {
            mItemInfos.Clear();
            ICall_removeAllItems(mInstance.Ptr);
        }

		//! Swap items at a specified positions
		internal void SwapItemsAt(int index1, int index2)
        {
            ItemInfo temp = mItemInfos[index1];
            mItemInfos[index1] = mItemInfos[index2];
            mItemInfos[index2] = temp;
            ICall_swapItemsAt(mInstance.Ptr, (uint)index1, (uint)index2);
        }


		//! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
		internal int FindItemIndexWith(string name)
        {
            return mItemInfos.FindIndex(
                delegate (ItemInfo info){
                    return (name == info.Name);
                }
                );
        }
		//@}

		//------------------------------------------------------------------------------//
		/** @name Item Selection Methods
			Methods used to manipulate item selection.
		*/
		//@{
		/** Get index of selected item (-1 if none selected) */
		internal int IndexSelected
        {
            get
            {
                uint index = ICall_getIndexSelected(mInstance.Ptr);
                return (index >= int.MaxValue) ? -1 : (int)index;
            }
            set
            {
                ICall_setIndexSelected(mInstance.Ptr, (uint)value);
            }
        }

		/** Clear item selection */
		internal void ClearIndexSelected()
        {
            ICall_clearIndexSelected(mInstance.Ptr);
        }

		//@}

		//------------------------------------------------------------------------------//

		/** @name Item Data Methods
			Methods used to manipulate item user data.
		*/
		//@{
		//! Replace an item data at a specified position
		internal void SetItemDataAt(int index, object data)
        {
            mItemInfos[index].UserData = data;
        }

		//! Clear an item data at a specified position
		internal void ClearItemDataAt(int index)
        {
            mItemInfos[index].UserData = null;
        }

        //! Get item data from specified position
        internal object GetItemDataAt(int index)
        {
            return mItemInfos[index].UserData;
        }

		//! Get item data from specified position
        internal T GetItemDataAt<T>(int index)
            where T : class
		{
			return mItemInfos[index].UserData as T;
		}
		//@}

		//------------------------------------------------------------------------------//

		//! Replace an item name at a specified position
		internal void SetItemNameAt(int index,  string name)
        {
            mItemInfos[index].Name = name;
            ICall_setItemNameAt(mInstance.Ptr, (uint)index, name);
        }

		//! Get item name from specified position
		 internal string GetItemNameAt(int index)
         {
             return mItemInfos[index].Name;
         }


		//------------------------------------------------------------------------------//
		// манипуляции выдимостью

		/** @name Item Visibility Methods
			Methods used to determine and manipulate item visibility.
		*/
		//@{
		//! Move all elements so specified becomes visible
		internal void BeginToItemAt(int index)
        {
            ICall_beginToItemAt(mInstance.Ptr, (uint)index);
        }

		//! Move all elements so first becomes visible
		internal void BeginToItemFirst()
        {
            ICall_beginToItemFirst(mInstance.Ptr);
        }

		//! Move all elements so last becomes visible
		internal void BeginToItemLast()
        {
            ICall_beginToItemLast(mInstance.Ptr);
        }

		//! Move all elements so selected becomes visible
		internal void BeginToItemSelected()
        {
            ICall_beginToItemSelected(mInstance.Ptr);
        }

		//------------------------------------------------------------------------------//

		/** Return true if item visible
			@param
				_index of item
			@param
				_fill
					false: function return true when whole item is visible
					true: function return true when at least part of item is visible
		*/
		internal bool IsItemVisibleAt(int index, bool fill)
        {
            return ICall_isItemVisibleAt(mInstance.Ptr, (uint)index, fill);
        }

        internal bool IsItemVisibleAt(int index)
        {
            return IsItemVisibleAt(index, true);
        }
		//! Same as ListBox::isItemVisibleAt for selected item
		internal bool IsItemSelectedVisible(bool fill)
        {
            return ICall_isItemSelectedVisible(mInstance.Ptr, fill);
        }

        internal bool IsItemSelectedVisible()
        {
            return IsItemSelectedVisible(true);
        }


		//! Set scroll visible when it needed
        internal void SetScrollVisible(bool visible)
        {
            ICall_setScrollVisible(mInstance.Ptr, visible);
        }
		//! Set scroll position
        internal void SetScrollPosition(int position)
        {
            ICall_setScrollPosition(mInstance.Ptr, (uint)position);
        }
		//@}
		//! Return optimal height to fit all items in ListBox
        internal int OptimalHeight
        {
            get
            {
                return ICall_getOptimalHeight(mInstance.Ptr);
            }
        }


#region Events

        internal static void OnListSelectAccept(ListBox widget, ListBoxEventArg arg)
        {
            uint index = arg.index;
            widget.mHandleListSelectAccept(widget.Name, (index >= int.MaxValue) ? -1 : (int)index);
        }
        internal event Event.SenderInt EventListSelectAccept
        {
            add
            {
                if (null == mHandleListSelectAccept)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ListSelectAccept))
                    {
                        return;
                    }
                }
                mHandleListSelectAccept += value;
            }
            remove
            {
                mHandleListSelectAccept -= value;
                if (null == mHandleListSelectAccept)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ListSelectAccept);
                }
            }
        }
        protected Event.SenderInt mHandleListSelectAccept;

        internal static void OnListChangePosition(ListBox widget, ListBoxEventArg arg)
        {
            uint index = arg.index;
            widget.mHandleListChangePosition(widget.Name, (index >= int.MaxValue) ? -1 : (int)index);
        }
        internal event Event.SenderInt EventListChangePosition
        {
            add
            {
                if (null == mHandleListChangePosition)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ListChangePosition))
                    {
                        return;
                    }
                }
                mHandleListChangePosition += value;
            }
            remove
            {
                mHandleListChangePosition -= value;
                if (null == mHandleListChangePosition)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ListChangePosition);
                }
            }
        }
        protected Event.SenderInt mHandleListChangePosition;

        internal static void OnListMouseItemActivate(ListBox widget, ListBoxEventArg arg)
        {
            uint index = arg.index;
            widget.mHandleListMouseItemActivate(widget.Name, (index >= int.MaxValue) ? -1 : (int)index);
        }
        internal event Event.SenderInt EventListMouseItemActivate
        {
            add
            {
                if (null == mHandleListMouseItemActivate)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ListMouseItemActivate))
                    {
                        return;
                    }
                }
                mHandleListMouseItemActivate += value;
            }
            remove
            {
                mHandleListMouseItemActivate -= value;
                if (null == mHandleListMouseItemActivate)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ListMouseItemActivate);
                }
            }
        }
        protected Event.SenderInt mHandleListMouseItemActivate;

        internal static void OnListMouseItemFocus(ListBox widget, ListBoxEventArg arg)
        {
            uint index = arg.index;
            widget.mHandleListMouseItemFocus(widget.Name, (index >= int.MaxValue) ? -1 : (int)index);
        }
        internal event Event.SenderInt EventListMouseItemFocus
        {
            add
            {
                if (null == mHandleListMouseItemFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ListMouseItemFocus))
                    {
                        return;
                    }
                }
                mHandleListMouseItemFocus += value;
            }
            remove
            {
                mHandleListMouseItemFocus -= value;
                if (null == mHandleListMouseItemFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ListMouseItemFocus);
                }
            }
        }
        protected Event.SenderInt mHandleListMouseItemFocus;

        internal static void OnListChangeScroll(ListBox widget, ListBoxEventArg arg)
        {
            uint index = arg.index;
            widget.mHandleListChangeScroll(widget.Name, (index >= int.MaxValue) ? -1 : (int)index);
        }
        internal event Event.SenderInt EventListChangeScroll
        {
            add
            {
                if (null == mHandleListChangeScroll)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ListChangeScroll))
                    {
                        return;
                    }
                } 
                mHandleListChangeScroll += value;
            }
            remove
            {
                mHandleListChangeScroll -= value;
                if (null == mHandleListChangeScroll)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ListChangeScroll);
                }
            }
        }
        protected Event.SenderInt mHandleListChangeScroll;

#endregion







        private class ItemInfo
        {
            public ItemInfo(String name, object data)
            {
                mName = name;
                mUserData = data;
            }
            public String Name
            {
                get
                {
                    return mName;
                }
                set
                {
                    mName = value;
                }
            }
            public object UserData
            {
                get
                {
                    return mUserData;
                }
                set
                {
                    mUserData = value;
                }
            }
            private String mName;
            private object mUserData;
        }
        private List<ItemInfo> mItemInfos = new List<ItemInfo>();


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getItemCount(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_insertItemAt(IntPtr widget_ptr, uint _index, String _name, object _data);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_addItem(IntPtr widget_ptr, String _name, object _data);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_removeItemAt(IntPtr widget_ptr, uint _index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_removeAllItems(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_swapItemsAt(IntPtr widget_ptr, uint _index1, uint _index2);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_findItemIndexWith(IntPtr widget_ptr, String _name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getIndexSelected(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setIndexSelected(IntPtr widget_ptr, uint _index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_clearIndexSelected(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void setItemDataAt(uint _index, object _data);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_clearItemDataAt(IntPtr widget_ptr, uint _index);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static ValueType* getItemDataAt(uint _index, bool _throw = true);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemNameAt(IntPtr widget_ptr, uint _index, String _name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_getItemNameAt(IntPtr widget_ptr, uint _index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_beginToItemAt(IntPtr widget_ptr, uint _index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_beginToItemFirst(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_beginToItemLast(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_beginToItemSelected(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isItemVisibleAt(IntPtr widget_ptr, uint _index, bool _fill);//bool _fill = true

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isItemSelectedVisible(IntPtr widget_ptr, bool _fill);//bool _fill = true

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setScrollVisible(IntPtr widget_ptr, bool _visible);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setScrollPosition(IntPtr widget_ptr, uint _position);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getOptimalHeight(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static ;

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static ;

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static ;

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static ;




    }
}
