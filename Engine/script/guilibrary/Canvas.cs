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

    public enum TextureResizeMode : int
    {
        //
        TRM_PT_CONST_SIZE, /// Texture doesn't resizes and fills all widget space
        TRM_PT_VIEW_REQUESTED, /// You can view all pixels of texture, texture cropped by sizes of widget
        TRM_PT_VIEW_ALL /// Texture resizes and fills all widget space
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct Canvas_Event
    {
        [MarshalAs(UnmanagedType.U1)]
        public bool textureChanged;
        [MarshalAs(UnmanagedType.U1)]
        public bool widgetResized;
        [MarshalAs(UnmanagedType.U1)]
        public bool requested;/// This update was caused by calling updateTexture();
    }

    internal partial class Canvas : Widget
    {
        internal Canvas(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.Canvas)
        {

        }
        internal Canvas(Instance inst, FString name, Layout parent, WidgetType type)
            : base(inst, name, parent, type)
        {

        }

        ~Canvas()
        {
            clearEventsWidthOutParent();
            mRenderTarget = null;
        }

        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandlePreTextureChanges, EventType.PreTextureChanges);
            clearEvent(ref mHandleRequestUpdateCanvas, EventType.RequestUpdateCanvas);
        }

        internal override void Dispose()
        {
            clearEventsWidthOutParent();
            mRenderTarget = null;
            base.Dispose();
        }

        internal int TextureRealWidth
        {
            get
            {
                return ICall_getTextureRealWidth(mInstance.Ptr);
            }
        }
        internal int TextureRealHeight
        {
            get
            {
                return ICall_getTextureRealHeight(mInstance.Ptr);
            }
        }
        internal int TextureSrcWidth
        {
            get
            {
                return ICall_getTextureSrcWidth(mInstance.Ptr);
            }
        }
        internal int TextureSrcHeight
        {
            get
            {
                return ICall_getTextureSrcHeight(mInstance.Ptr);
            }
        }
        internal PixelFormat TextureFormat
        {
            get
            {
                return ICall_getTextureFormat(mInstance.Ptr);
            }
        }
        internal TextureResizeMode ResizeMode
        {
            get
            {
                return ICall_getResizeMode(mInstance.Ptr);
            }
        }
        internal bool IsTextureSrcSize
        {
            get
            {
                return ICall_isTextureSrcSize(mInstance.Ptr);
            }
        }
        internal bool IsTextureCreated
        {
            get
            {
                return ICall_isTextureCreated(mInstance.Ptr);
            }
        }
        internal bool IsTextureManaged
        {
            get
            {
                return ICall_isTextureManaged(mInstance.Ptr);
            }
        }

        internal void CreateTexture(TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format)
        {
            ICall_createTexture(mInstance.Ptr, _resizeMode, _usage, _format);
        }
        internal void CreateTexture(int _width, int _height, TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format)
        {
            ICall_createTexture_WidthSize(mInstance.Ptr, _width, _height, _resizeMode, _usage, _format);
        }

        internal void CreateTexture(ScriptRuntime.RenderToTexture rtt)
        {
            mRenderTarget = new RenderTarget(rtt);
            ICall_createTexture_FromTarget(mInstance.Ptr, mRenderTarget.Instance.Ptr);
        }

        internal void DestroyTexture()
        {
            ICall_destroyTexture(mInstance.Ptr);
        }

        internal void UpdateTexture()
        {
            ICall_updateTexture(mInstance.Ptr);
        }

        internal static void OnPreTextureChanges(Canvas canvas, EventArg arg)
        {
            canvas.mHandlePreTextureChanges(canvas.mName);
        }
        internal event Event.SenderVoid EventPreTextureChanges
        {
            add
            {
                if (null == mHandlePreTextureChanges)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.PreTextureChanges))
                    {
                        return;
                    }
                }
                mHandlePreTextureChanges += value;
            }
            remove
            {
                mHandlePreTextureChanges -= value;
                if (null == mHandlePreTextureChanges)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.PreTextureChanges);
                }
            }
        }
        protected Event.SenderVoid mHandlePreTextureChanges;

        unsafe internal static void OnRequestUpdateCanvas(Canvas canvas, RequestUpdateCanvasEventArg ru_arg)
        {
            Canvas_Event* ce = (Canvas_Event*)ru_arg.CanvesEvent.ToPointer();
            canvas.mHandleRequestUpdateCanvas(canvas.mName, *ce);
        }
        internal Event.SenderCanvas_Event RequestUpdateCanvas
        {
            set
            {
                if (null == mHandleRequestUpdateCanvas)
                {
                    if (ICall_appendEvent(this, mInstance.Ptr, EventType.RequestUpdateCanvas))
                    {
                        mHandleRequestUpdateCanvas = value;
                    }
                }
            }
        }
        protected Event.SenderCanvas_Event mHandleRequestUpdateCanvas;

        private RenderTarget mRenderTarget;
        internal const TextureUsage DefaultTextureUsage = TextureUsage.Stream | TextureUsage.Write;
        internal const PixelFormat DefaultTextureFormat = PixelFormat.R8G8B8A8;

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_createTexture(IntPtr widget_ptr, TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format);
    
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_createTexture_WidthSize(IntPtr widget_ptr, int _width, int _height, TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_createTexture_FromTarget(IntPtr widget_ptr, IntPtr rt_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_destroyTexture(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_updateTexture(IntPtr widget_ptr);

        ////[zhongdaohuan]勿删，lock,unlock, islock未启用，没想好脚本怎么用。
        //[MethodImplAttribute(MethodImplOptions.InternalCall)]       
        //    extern private static IntPtr ICall_lock(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_unlock(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static bool ICall_isLocked(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getTextureRealWidth(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getTextureRealHeight(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getTextureSrcWidth(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getTextureSrcHeight(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static PixelFormat ICall_getTextureFormat(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static TextureResizeMode ICall_getResizeMode(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isTextureSrcSize(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isTextureCreated(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_isTextureManaged(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static  (IntPtr widget_ptr);
        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static  (IntPtr widget_ptr);
    }
}
