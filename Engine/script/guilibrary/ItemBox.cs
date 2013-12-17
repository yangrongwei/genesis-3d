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
    /// <summary>
    /// 用户界面控件信息类
    /// </summary>
    public class ItemInfo
    {
        internal ItemInfo(Widget parent, Widget item)
        {
            mParent = parent;
            mItem = item;
        }
        /// <summary>
        /// 加入窗口面板操作
        /// </summary>
        /// <param name="file_name">加入窗口面板的文件名</param>
        /// <param name="delay_load">是否延迟加载</param>
        /// <param name="visible">加载后是否可见</param>
        public void AddLayout(String file_name, bool delay_load, bool visible)
        {
            GUI.RegisterLayout(mParent.ParentLayout.Name, mItem.Name, mLayoutName, file_name, delay_load, visible);//sender
        }
        internal void Clear()
        {
            mParent = null;
            mItem = null;
            mLayoutName = null;
        }
        /// <summary>
        /// 控件名称
        /// </summary>
        public FString ItemName
        {
            get
            {
                return mItem.Name;
            }
        }
        /// <summary>
        /// 界面名称
        /// </summary>
        public FString LayoutName
        {
            get
            {
                return mLayoutName;
            }
            internal set
            {
                mLayoutName = value;
            }
        }
        internal Widget Item
        {
            get
            {
                return mItem;
            }
        }

        private Widget mParent;
        private Widget mItem;
        private FString mLayoutName;
    }
    internal class ItemBox : DDContainer
    {
        internal ItemBox(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.ItemBox)
        {

        }

        ~ItemBox()
        {
            clearAll();
        }
        private void clearAll()
        {
            foreach (KeyValuePair<IntPtr, ItemInfo> pair in mItems)
            {
                GUI.UnregisterLayout(pair.Value.LayoutName);
                mParentLayout.RemoveWidget(pair.Value.Item.Name);
                pair.Value.Clear();
            }
            mItems.Clear();
            RemoveAllItems();

            clearEventsWidthOutParent();
        }
        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandleCoordItem, EventType.RequestCoordItem);
            clearEvent(ref mHandleCreateWidgetItem, EventType.RequestCreateWidgetItem);
            clearEvent(ref mHandleDrawItem, EventType.RequestDrawItem);
        }
        internal override void Dispose()
        {
            clearAll();
            base.Dispose();
        }

        internal Event.SenderRefIntCoordBool RequestCoordItem
        {
            set
            {
                mHandleCoordItem = value;
                if (null == mHandleCoordItem)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RequestCoordItem);
                }
                else
                {
                    ICall_appendEvent(this, mInstance.Ptr, EventType.RequestCoordItem);
                }
            }
        }
        protected Event.SenderRefIntCoordBool mHandleCoordItem;

        internal Event.SenderItemInfo RequestCreateWidgetItem
        {
            set
            {
                mHandleCreateWidgetItem = value;
                if (null == mHandleCreateWidgetItem)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RequestCreateWidgetItem);
                }
                else
                {
                    ICall_appendEvent(this, mInstance.Ptr, EventType.RequestCreateWidgetItem);
                }
            }
        }
        protected Event.SenderItemInfo mHandleCreateWidgetItem;

        internal Event.SenderItemInfoIBDrawInfo RequestDrawItem
        {
            set
            {
                mHandleDrawItem = value;
                if (null == mHandleDrawItem)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RequestDrawItem);
                }
                else
                {
                    ICall_appendEvent(this, mInstance.Ptr, EventType.RequestDrawItem);
                }
            }
        }
        protected Event.SenderItemInfoIBDrawInfo mHandleDrawItem;


        internal static void OnSelectItemAccept(ItemBox widget, ItemEventArg arg)
        {

            widget.mHandleSelectItemAccept(widget.Name, (int)arg.index);
        }
        internal event Event.SenderInt EventSelectItemAccept
        {
            add
            {
                if (null == mHandleSelectItemAccept)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.SelectItemAccept))
                    {
                        return;
                    }
                }
                mHandleSelectItemAccept += value;
            }
            remove
            {
                mHandleSelectItemAccept -= value;
                if (null == mHandleSelectItemAccept)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.SelectItemAccept);
                }
            }
        }
        protected Event.SenderInt mHandleSelectItemAccept;

        internal static void OnChangeItemPosition(ItemBox widget, ItemEventArg arg)
        {

            widget.mHandleSelectItemAccept(widget.Name, (int)arg.index);
        }
        internal event Event.SenderInt EventChangeItemPosition
        {
            add
            {
                if (null == mHandleChangeItemPosition)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ChangeItemPosition))
                    {
                        return;
                    }
                }
                mHandleChangeItemPosition += value;
            }
            remove
            {
                mHandleChangeItemPosition -= value;
                if (null == mHandleChangeItemPosition)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ChangeItemPosition);
                }
            }
        }
        protected Event.SenderInt mHandleChangeItemPosition;

        internal static void OnMouseItemActivate(ItemBox widget, ItemEventArg arg)
        {
            widget.mHandleSelectItemAccept(widget.Name, (int)arg.index);
        }
        internal event Event.SenderInt EventMouseItemActivate
        {
            add
            {
                if (null == mHandleMouseItemActivate)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseItemActivate))
                    {
                        return;
                    }
                }
                mHandleMouseItemActivate += value;
            }
            remove
            {
                mHandleMouseItemActivate -= value;
                if (null == mHandleMouseItemActivate)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseItemActivate);
                }
            }
        }
        protected Event.SenderInt mHandleMouseItemActivate;

        internal static void OnNotifyItem(ItemBox widget, NotifyItemEventArg arg)
        {
            IBNotifyItemData info = Util.PtrToStruct<IBNotifyItemData>(arg.IBNotifyItemData);
            widget.mHandleNotifyItem(widget.Name, ref info);
        }
        internal event Event.SenderRefIBNotifyItemData EventNotifyItem
        {
            add
            {
                if (null == mHandleNotifyItem)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.NotifyItem))
                    {
                        return;
                    }
                } 
                mHandleNotifyItem += value;
            }
            remove
            {
                mHandleNotifyItem  -= value;
                if (null == mHandleNotifyItem)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.NotifyItem);
                }
            }
        }
        protected Event.SenderRefIBNotifyItemData mHandleNotifyItem;




        internal void AddItem(object obj)
        {
            mItemData.Add(obj);
            ICall_addItem(mInstance.Ptr, obj);
        }
        internal object GetItemDataAt(int index)
        {
            return mItemData[index];
        }

        internal int ItemCount
        {
            get
            {
                return (int)ICall_getItemCount(mInstance.Ptr);
            }
        }

        internal void InsetItemAt(int index, object data)
        {
            mItemData.Insert(index, data);
            ICall_insertItemAt(mInstance.Ptr, (uint)index, data);
        }

        internal void RemoveItemAt(int index)
        {
            mItemData.RemoveAt(index);
            ICall_removeItemAt(mInstance.Ptr, (uint)index);
        }
        internal void RedrawItemAt(int index)
        {
            ICall_redrawItemAt(mInstance.Ptr, (uint)index);
        }
        internal void RedrawAllItems()
        {
            ICall_redrawAllItems(mInstance.Ptr);
        }
        internal int IndexSelect
        {
            get
            {
                uint select = ICall_getIndexSelected(mInstance.Ptr);
                if (int.MaxValue <= select)
                {
                    return Util.UNVALID_COUNT;
                }
                return (int)select;
            }
            set
            {
                ICall_setIndexSelected(mInstance.Ptr, (uint)value);
            }
        }
        internal void ClearIndexSelect()
        {
            ICall_clearIndexSelected(mInstance.Ptr);
        }

        internal void SetItemDataAt(int index, object data)
        {
            mItemData[index] = data;
            ICall_setItemDataAt(mInstance.Ptr, (uint)index, data);
        }

        internal void CleartemDataAt(int index)
        {
            mItemData[index] = null;
            ICall_clearItemDataAt(mInstance.Ptr, (uint)index);
        }

        internal void RemoveAllItems()
        {
            ICall_removeAllItems(mInstance.Ptr);
            mItemData.Clear();//必须放到ICall_removeAllItems()之后。
        }
        internal bool VerticalAlignment
        {
            get
            {
                return ICall_getVerticalAlignment(mInstance.Ptr);
            }
            set
            {
                ICall_setVerticalAlignment(mInstance.Ptr, value);
            }
        }

        internal int GetIndexByWidget(Widget widget)
        {
            uint index = ICall_getIndexByWidget(mInstance.Ptr, widget.Instance.Ptr);
            if (index >= ItemCount)
            {
                return Util.UNVALID_COUNT;
            }
            return (int)index;
        }
        internal Widget GetWidgetDrag()
        {
            Instance inst = ICall_getWidgetDrag(mInstance.Ptr);
            ItemInfo info = null;
            if (mItems.TryGetValue(inst.Ptr, out info))
            {
                return info.Item;
            }
            return null;
        }
        internal Widget GetWidgetByIndex(int index)
        {
            Instance inst = ICall_getWidgetByIndex(mInstance.Ptr, (uint)index);
            ItemInfo info = null;
            if (mItems.TryGetValue(inst.Ptr, out info))
            {
                return info.Item;
            }
            return null;
        }
        internal void ResetDrag()
        {
            ICall_resetDrag(mInstance.Ptr);
        }
        protected ItemInfo findItem(Instance inst)
        {
            ItemInfo info = null;
            mItems.TryGetValue(inst.Ptr, out info);
            if (null == info)
            {
                int temp = mInstance.Ptr.ToInt32() + inst.Ptr.ToInt32();
                string name = mName.Name + "_item_" + temp.ToString();
                Widget widget = Widget.CreateWidget(inst, name, mParentLayout);//
                info = new ItemInfo(this, widget);
      
                mItems.Add(inst.Ptr, info);
                mParentLayout.AddWidget(info.Item);
            }
            return info;
        }

        protected Dictionary<IntPtr, ItemInfo> mItems = new Dictionary<IntPtr, ItemInfo>();
        protected List<object> mItemData = new List<object>();

        unsafe internal static void OnRequestCoordItem(ItemBox item_box, RequestCoordWidgetItemEventArg rc_arg)
        {
            bool drag = rc_arg.drop;
            IntCoord* coord = (IntCoord*)rc_arg.Coord.ToPointer();
            item_box.mHandleCoordItem(item_box.mName, ref (*coord), drag);

        }

        internal static void OnRequestCreateWidgetItem(ItemBox item_box, RequestCreateWidgetItemEventArg rc_arg)
        {
            Instance inst = rc_arg.Item;
            ItemInfo info = item_box.findItem(inst);
            if (null != info)
            {
                info.LayoutName = item_box.mName.Name + "_Layout_" + inst.Ptr.ToString(); //;//(item_box.ItemCount - 1).ToString()
                //item_box.mHandleCreateWidgetItem(item_box.Name, info.mItem.Name);

                item_box.mHandleCreateWidgetItem(item_box.Name, info);
            }
        }

        internal static void OnRequestDrawItem(ItemBox item_box, RequestDrawItemEventArg rc_arg)
        {
            Instance inst = rc_arg.Item;

            ItemInfo info = item_box.findItem(inst);
            if (null != info && null != info.Item)
            {
                IBDrawItemInfo draw_info = (IBDrawItemInfo)Util.PtrToStruct<IBDrawItemInfo>(rc_arg.DrawItemInfo);
                item_box.mHandleDrawItem(item_box.Name, info, draw_info);
            }
        }


        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getItemCount(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_addItem(IntPtr itembox_ptr, object item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_removeAllItems(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_insertItemAt(IntPtr itembox_ptr, uint index, object item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_removeItemAt(IntPtr itembox_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_redrawItemAt(IntPtr itembox_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_redrawAllItems(IntPtr itembox_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getIndexSelected(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setIndexSelected(IntPtr itembox_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_clearIndexSelected(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemDataAt(IntPtr itembox_ptr, uint index, object data);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_clearItemDataAt(IntPtr itembox_ptr, uint index);




        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setVerticalAlignment(IntPtr itembox_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getVerticalAlignment(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getIndexByWidget(IntPtr itembox_ptr, IntPtr widget_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getWidgetDrag(IntPtr itembox_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getWidgetByIndex(IntPtr itembox_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static new void ICall_resetDrag(IntPtr itembox_ptr);


        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_(IntPtr itembox_ptr, uint index);
    }
}
