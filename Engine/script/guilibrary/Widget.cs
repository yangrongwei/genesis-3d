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
using System.Runtime.InteropServices;

namespace ScriptGUI
{
    internal partial class Widget// : IDisposable
    {
        internal Widget(Instance inst, FString name, Layout parent, WidgetType type)
        {
            mInstance = inst;
            mType = type;
            mName = name;
            mParentLayout = parent;
        }
        ~Widget()
        {
            clearEventsWidthOutParent();
            mInstance = Instance.NullInstance;
        }
        internal virtual void Dispose()
        {
            clearEventsWidthOutParent();
            GUI.DisposeWidget(mInstance);
            mInstance = Instance.NullInstance; 
        }
        internal FString Name
        {
            get
            {
                return mName;
            }
        }

        internal bool Visible
        {
            set
            {
                ICall_setVisible(mInstance.Ptr, value);
            }
            get
            {
                return ICall_getVisible(mInstance.Ptr);
            }
            
        }

        internal bool InheritedVisible
        {
            get 
            {
                return ICall_getInheritedVisible(mInstance.Ptr);
            }
        }

        internal Colour Colour
        {
            set
            {
                ICall_setColor(mInstance.Ptr, ref value);
            }
        }

        internal IntCoord ClientCoord
        {
            get
            {
                IntCoord value;
                ICall_getClientCoord(mInstance.Ptr,out value);
                return value;

                //return (IntCoord)Marshal.PtrToStructure(ICall_getClientCoord(mInstance.Ptr), typeof(IntCoord));
            }
        }

        internal IntCoord Coord
        {
            set
            {
                ICall_setCoord(mInstance.Ptr, ref value);
            }
            get
            {
                return (IntCoord)Marshal.PtrToStructure(ICall_getCoord(mInstance.Ptr), typeof(IntCoord));
            }
        }

        internal WidgetType WidgetType
        {
            get
            {
                return mType;
            }
            
        }

        internal Instance Instance
        {
            get
            {
                return mInstance;
            }
        }

        internal object UserData
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

        internal Layout ParentLayout
        {
            get
            {
                return mParentLayout;
            }
        }

        internal IntPoint Position
        {
            get
            {
                IntPoint value;
                ICall_getPosition(mInstance.Ptr, out value);
                return value;
                //return (IntPoint)Marshal.PtrToStructure(ICall_getPosition(mInstance.Ptr), typeof(IntPoint));
            }
            set
            {
                ICall_setPosition(mInstance.Ptr, ref value);
            }
        }
        internal IntSize Size
        {
            get
            {
                IntSize value;
                ICall_getSize(mInstance.Ptr, out value);
                return value;
                //return (IntSize)Marshal.PtrToStructure(ICall_getSize(mInstance.Ptr), typeof(IntSize));
            }
            set
            {
                ICall_setSize(mInstance.Ptr, ref value);
            }
        }

        internal void SetRealPosition(FloatPoint pos)
        {
            ICall_setRealPosition(mInstance.Ptr, ref pos);
        }
        internal void SetRealSize(FloatSize size)
        {
            ICall_setRealSize(mInstance.Ptr, ref size);
        }
        internal void SetRealCoord(FloatCoord coord)
        {
            ICall_setRealCoord(mInstance.Ptr, ref coord);
        }
        internal IntPoint AbsolutePosition
        {
            get
            {
                return (IntPoint)Marshal.PtrToStructure(ICall_getAbsolutePosition(mInstance.Ptr), typeof(IntPoint));
            }
        }
        internal IntRect AbsoluteRect
        {
            get
            {
                IntRect value;
                ICall_getAbsoluteRect(mInstance.Ptr, out value);
                return value;
                //return (IntRect)Marshal.PtrToStructure(ICall_getAbsoluteRect(mInstance.Ptr), typeof(IntRect));
            }
        }
        internal IntCoord AbsoluteCoord
        {
            get
            {
                IntCoord value;
                ICall_getAbsoluteCoord(mInstance.Ptr, out value);
                return value;
                //return (IntCoord)Marshal.PtrToStructure(ICall_getAbsoluteCoord(mInstance.Ptr), typeof(IntCoord));
            }
        }

        internal Align Align
        {
            get
            {
                return ICall_getAlign(mInstance.Ptr);
            }
            set
            {
                ICall_setAlign(mInstance.Ptr, value);
            }
        }
        internal float Alpha
        {
            get
            {
                return ICall_getAlpha(mInstance.Ptr);
            }
            set
            {
                ICall_setAlpha(mInstance.Ptr, value);
            }
        }
        internal bool InheritsAlpha
        {
            get
            {
                return ICall_getInheritsAlpha(mInstance.Ptr);
            }
            set
            {
                ICall_setInheritsAlpha(mInstance.Ptr, value);
            }
        }
        internal bool Enabled
        {
            get
            {
                return ICall_getEnabled(mInstance.Ptr);
            }
            set
            {
                ICall_setEnabled(mInstance.Ptr, value);
            }
        }

        protected static String GetName(IntPtr ptr)
        {
            return ICall_getName(ptr);
        }

        internal static Widget CreateWidget(Instance inst, Layout parent_layout)
        {
            Widget widget = CreateWidget(inst, null, parent_layout);
            widget.mName = GetName(widget.mInstance.Ptr);
            return widget;
        }

        internal static Widget CreateWidget(Instance inst, FString name, Layout parent_layout)
        {
            WidgetType type = ICall_getType(inst.Ptr);

            Widget widget = null;
            switch (type)
            {
                case WidgetType.Widget:
                    widget = new Widget(inst, name, parent_layout, WidgetType.Widget);
                    break;
                case WidgetType.ImageBox:
                    widget = new ImageBox(inst, name, parent_layout);
                    break;
                case WidgetType.Window:
                    widget = new Window(inst, name, parent_layout);
                    break;
                case WidgetType.TextBox:
                    widget = new TextBox(inst, name, parent_layout);
                    break;
                case WidgetType.ListBox:
                    widget = new ListBox(inst, name, parent_layout);
                    break;
                case WidgetType.Button:
                    widget = new Button(inst, name, parent_layout);
                    break;
                case WidgetType.EditBox:
                    widget = new EditBox(inst, name, parent_layout);
                    break;
                case WidgetType.ComboBox:
                    widget = new ComboBox(inst, name, parent_layout);
                    break;

                case WidgetType.ScrollBar:
                    widget = new ScrollBar(inst, name, parent_layout);
                    break;
                case WidgetType.DDContainer:
                    widget = new DDContainer(inst, name, parent_layout);
                    break;
                case WidgetType.ItemBox:
                    widget = new ItemBox(inst, name, parent_layout);
                    break;
                case WidgetType.Canvas:
                    widget = new Canvas(inst, name, parent_layout);
                    break;
                default:
                    widget = new Widget(inst, name, parent_layout, WidgetType.Unknown);
                    break;
            }
            return widget;
        }

        internal static Widget CreateWidget(Instance inst)
        {
            return CreateWidget(inst, null, null);
        }


        protected Instance mInstance;
        protected FString mName;
        protected Layout mParentLayout;
        protected WidgetType mType = WidgetType.Unknown;
        protected object mUserData;




#region Engine Interface

        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setVisible(IntPtr widget_ptr, bool visible);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getVisible(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getInheritedVisible(IntPtr widget_ptr);

        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static WidgetType ICall_getType(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isType(IntPtr widget_ptr, WidgetType type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_getName(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getClientCoord(IntPtr widget_ptr, out IntCoord value);//IntCoord

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setColor(IntPtr widget_ptr, ref Colour colour);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setPosition(IntPtr widget_ptr, ref IntPoint value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setSize(IntPtr widget_ptr, ref IntSize value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setCoord(IntPtr widget_ptr, ref IntCoord coord);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setRealPosition(IntPtr widget_ptr, ref FloatPoint value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setRealSize(IntPtr widget_ptr, ref FloatSize value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setRealCoord(IntPtr widget_ptr, ref FloatCoord value);



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getPosition(IntPtr widget_ptr, out IntPoint value);//IntPoint

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getSize(IntPtr widget_ptr, out IntSize value);//IntSize

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getCoord(IntPtr widget_ptr);//IntCoord


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getAbsolutePosition(IntPtr widget_ptr);//IntPoint

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getAbsoluteRect(IntPtr widget_ptr, out IntRect value);//IntRect

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getAbsoluteCoord(IntPtr widget_ptr, out IntCoord value);//IntCoord


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setAlign(IntPtr widget_ptr, Align value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Align ICall_getAlign(IntPtr widget_ptr);


		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setAlpha(IntPtr widget_ptr, float value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_getAlpha(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setInheritsAlpha(IntPtr widget_ptr, bool _value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getInheritsAlpha(IntPtr widget_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setEnabled(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getEnabled(IntPtr widget_ptr);




#endregion
    }
}
