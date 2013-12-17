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
using System.Runtime.CompilerServices;
using ScriptRuntime;

namespace ScriptRuntime
{

    /// <summary>
    /// 组件类，可以挂接到游戏对象上
    /// </summary>
    public partial class Component : Base
    {
        private Component(DummyClass__ dummyObj)
        {
            // empty
        }

        protected Component()
        { }
        /// <summary>
        /// 游戏组件类型，获得持有该组件的游戏对象
        /// </summary>
        public Actor Owner
        {
            get
            {
                return ICall_Component_GetOwner(this);
            }
        }
        /// <summary>
        /// 布尔值，标示组件是否被激活，被激活为true,未被激活为false
        /// </summary>
        public bool Active
        {
            get
            {
                return ICall_Component_Active(this);
            }
        }

        ~Component()
        {
            ICall_Component_Release(this);
        }
    }
}