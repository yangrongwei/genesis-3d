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

namespace ScriptGUI
{
    public class Event
    {
        //public delegate void 

        public delegate void Void(ScriptGUI.FString sender);
        public delegate void FString(ScriptGUI.FString sender, ScriptGUI.FString value);
        public delegate void Bool(ScriptGUI.FString sender, bool value);
        public delegate void Int(ScriptGUI.FString sender, int value);
        public delegate void IntInt(ScriptGUI.FString sender, int value1, int value2);
        public delegate void IntIntMouseButton(FString sender, int value1, int value2, MouseButton button);
        public delegate void KeyCode(ScriptGUI.FString sender, KeyCode code);
        public delegate void KeyCodeChar(ScriptGUI.FString sender, KeyCode code, char ch);
        public delegate void ToolTipInfo(ScriptGUI.FString sender, ToolTipInfo info);



        private static void onEvent(Widget widget, EventArg arg)
        {
            switch (arg.EventType)
            {
                case EventType.MouseButtonClick:
                    Widget.OnMouseButtonClick(widget, arg);
                    break;
            }
        }
    }
}
