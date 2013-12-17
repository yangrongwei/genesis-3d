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
    /// 脚本回调返回结构
    /// </summary>
    public class UserReportPair
    {
        private UserReportPair(DummyClass__ haha)
        {

        }
        /// <summary>
        /// 设置脚本回调返回结构的值
        /// </summary>
        /// <param name="body1">脚本回调的对象</param>
        /// <param name="body2">脚本回调的对象</param>
        public void SetValue(PhysicsBodyComponent body1, PhysicsBodyComponent body2)
        {
            self = body1;
            other = body2;
        }
        /// <summary>
        /// 自身脚本回调的对象
        /// </summary>
        public PhysicsBodyComponent self;
        /// <summary>
        /// 其他脚本回调的对象
        /// </summary>
        public PhysicsBodyComponent other;
    };

    /// <summary>
    /// 挂接脚本入口的基类
    /// </summary>
    public abstract class ScriptableClass : Base
    {
        virtual public void OnLoad()
        { }
        virtual public void OnBeginFrame()
        { }
        virtual public void OnFrame()
        { }
        virtual public void OnEndFrame()
        { }
        virtual public void OnExit()
        { }
        virtual public void OnStopped()
        { }
        virtual public void OnResumed()
        { }
        virtual public bool OnRenderPostEffect(CameraComponent sender, RenderToTexture source, RenderToTexture destination)
        { return false; }
        virtual public void OnWillRenderObject(RenderComponent sender)
        { }

        virtual public void OnControllerShapeCollision(UserReportPair pair)
        { }
        virtual public void OnTriggerEnter(UserReportPair pair)
        { }
        virtual public void OnTriggerStay(UserReportPair pair)
        { }
        virtual public void OnTriggerLeave(UserReportPair pair)
        { }
        virtual public void OnCollisionEnter(UserReportPair pair)
        { }

        /// <summary>
        /// 获取与设置脚本实例的名称
        /// </summary>
        public String Name
        {
            
            get
            {
                return ICall_ScriptableClass_GetName(this);
            }

            set
            {
                ICall_ScriptableClass_SetName(this, value);
            }
        }

        /// <summary>
        /// 获取挂接脚本Actor的实例
        /// </summary>
        public Actor Owner
        {
            get
            {
             
                  return ICall_ScriptableClass_GetOwner(this);
           
            }
        }

        ~ScriptableClass()
        {
            ICall_ScriptableClass_Release(this);
        }

        // - internal call define
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_ScriptableClass_GetOwner(ScriptableClass self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ScriptableClass_SetName(ScriptableClass self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_ScriptableClass_GetName(ScriptableClass self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ScriptableClass_Release(ScriptableClass self);

    }
}
