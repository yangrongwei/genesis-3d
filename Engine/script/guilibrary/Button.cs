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
    internal class Button : TextBox
    {
        internal Button(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.Button)
        {

        }
        internal bool StateSelected
        {
            get
            {
                return ICall_getStateSelected(mInstance.Ptr);
            }
            set
            {
                ICall_setStateSelected(mInstance.Ptr, value);
            }
        }       
        /** Enable or disable Image mode\n
		    Image mode: when button state changed Image on button also change it's picture.\n
		    Disabled (false) by default.
		*/
        internal bool ModeImage
        {
            get
            {
                return ICall_getModeImage(mInstance.Ptr);
            }
            set
            {
                ICall_setModeImage(mInstance.Ptr, value);
            }
        }


        internal void SetImageResource(String name)
        {
            ICall_setImageResource(mInstance.Ptr, name);
        }

        internal void SetImageGroup(String name)
        {
            ICall_setImageGroup(mInstance.Ptr, name);
        }

        internal void SetImageName(String name)
        {
            ICall_setImageName(mInstance.Ptr, name);
        }



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setStateSelected(IntPtr widget_ptr, bool _selected);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getStateSelected(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setModeImage(IntPtr widget_ptr, bool _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static bool ICall_getModeImage(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setImageResource(IntPtr widget_ptr, String _name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setImageGroup(IntPtr widget_ptr, String _name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageName(IntPtr widget_ptr, String _name);

    }
}
