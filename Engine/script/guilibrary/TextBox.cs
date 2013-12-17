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

    internal class TextBox : Widget
    {
        internal TextBox(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.TextBox)
        {

        }
        internal TextBox(Instance inst, FString name, Layout parent, WidgetType type)
            : base(inst, name, parent, type)
        {

        }

        internal virtual string Caption
        {
            set
            {
                ICall_setCaption(mInstance.Ptr, value);
            }
            get
            {
                return ICall_getCaption(mInstance.Ptr);
            }

        }

        internal virtual Colour TextColour
        {
            set
            {
                ICall_setTextColour(mInstance.Ptr, ref value);
            }
            get
            {
                Colour colour;
                ICall_getTextColour(mInstance.Ptr, out colour);
                return colour;
            }
        }

        /** Get text region coordinate */
		internal  IntCoord TextRegion
        {
            get
            {
                IntCoord coord;
                ICall_getTextRegion(mInstance.Ptr, out coord);
                return coord;
            }


        }

		/** Get text region size */
		internal  IntSize TextSize
        {
            get
            {
                IntSize value;
                ICall_getTextSize(mInstance.Ptr, out value);
                return value;
            }


        }


		/** Set widget text font */
		internal  string FontName
        {
            get
            {
                return ICall_getFontName(mInstance.Ptr);
            }
            set
            {
                ICall_setFontName(mInstance.Ptr, value);
            }
        }

		/** Set widget text font height */
		internal  int FontHeight
        {
            get
            {
                return ICall_getFontHeight(mInstance.Ptr);
            }
            set
            {
                ICall_setFontHeight(mInstance.Ptr, value);
            }
        }

		/** Set widget text align */
		internal  Align TextAlign
        {
            get
            {
                return ICall_getTextAlign(mInstance.Ptr);
            }
            set
            {
                ICall_setTextAlign(mInstance.Ptr, ref  value);
            }
        }

		/** Set TextBox caption and replace special sequences.\n
			"\\n" will be replaced with new line character;\n
			"#{Keyword}" replaced with string from LanguageManager or
			left as it is if kayword wasn't found.
		*/
		internal void SetCaptionWithReplacing(string value)
        {
            ICall_setCaptionWithReplacing(mInstance.Ptr, value);
        }

		/** Set widget text shadow colour */
        internal Colour TextShadowColour
        {
            get
            {
                Colour value;
                ICall_getTextShadowColour(mInstance.Ptr, out value);
                return value;
            }
            set
            {
                ICall_setTextShadowColour(mInstance.Ptr, ref value);
            }
        }
		/** Set widget text shadow */
        internal bool TextShadow
        {
            get
            {
                return ICall_getTextShadow(mInstance.Ptr);
            }
            set
            {
                ICall_setTextShadow(mInstance.Ptr, value);
            }
        }





        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_setTextColor(IntPtr widget_ptr, Colour colour);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setCaption(IntPtr widget_ptr, String caption);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_getCaption(IntPtr widget_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getTextRegion(IntPtr widget_ptr, out IntCoord value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getTextSize(IntPtr widget_ptr, out IntSize value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setFontName(IntPtr widget_ptr, String value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_getFontName(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setFontHeight(IntPtr widget_ptr, int value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getFontHeight(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setTextAlign(IntPtr widget_ptr, ref Align value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Align ICall_getTextAlign(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setTextColour(IntPtr widget_ptr, ref Colour value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getTextColour(IntPtr widget_ptr, out Colour value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setCaptionWithReplacing(IntPtr widget_ptr, String value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setTextShadowColour(IntPtr widget_ptr, ref Colour value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getTextShadowColour(IntPtr widget_ptr, out Colour value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setTextShadow(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_getTextShadow(IntPtr widget_ptr);
    }
}
