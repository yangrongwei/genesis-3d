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
    /// 脚本组件
    /// 控制用户逻辑的核心组件
    /// </summary>
    public class ScriptComponent : Component
    {
        public static readonly System.Type thisType = typeof(ScriptComponent);

        private ScriptComponent(DummyClass__ dummy)
        {

        }

        /// <summary>
        /// 通过脚本实例名称来获取脚本实例
        /// </summary>
        /// <param name="name">脚本实例名称</param>
        /// <returns>返回脚本实例</returns>
        public ScriptableClass GetScriptByName(String name)
        {
            return ICall_ScriptComponent_GetScriptByName(this, name);
        }
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static ScriptableClass ICall_ScriptComponent_GetScriptByName(ScriptComponent self, String name);
    }
}
