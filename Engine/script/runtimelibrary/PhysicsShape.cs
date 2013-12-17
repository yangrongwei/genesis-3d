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
    /// 物理形状类
    /// 设置物理性状后,可以根据设置的形状进行碰撞等物理模拟
    /// </summary>
    public partial class PhysicsShape:Base
    {

        private PhysicsShape( DummyClass__ dummyObj )
        {

        }

        protected PhysicsShape()
        {

        }

        /// <summary>
        /// 读写属性：物理形状的相对中心位置
        /// </summary>
        public Vector3 Center
        {
            get
            {
                Vector3 temp;
                ICall_PhysicsShape_GetCenterPos(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsShape_SetCenterPos(this, ref value);
            }
        }

        /// <summary>
        /// 读写属性：物理形状的相对旋转角度
        /// </summary>
        public Quaternion Roation
        {
            get
            {
                Quaternion temp;
                ICall_PhysicsShape_GetRotation(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsShape_SetRotation(this, ref value);
            
            }
        }
        /// <summary>
        /// 读写属性：物理形状的材质文件
        /// </summary>
        public String MaterialID
        {
            get
            {
                return ICall_PhysicsShape_GetMaterialID(this);  
            }
            set
            {
                ICall_PhysicsShape_SetMaterialID(this, value);
            }
        }
        /// <summary>
        /// 读写属性：物理形状的UserData数据
        /// </summary>
        public object UserData
        {
            get 
            {
                return ICall_PhysicsShape_GetUserData(this);
            }
            set
            {
                ICall_PhysicsShape_SetUserData(this, value);
            }
        }

        /// <summary>
        /// 读写属性：物理形状碰撞分组
        /// </summary>
        public int Group
        {
            get
            {
                return ICall_PhysicsShape_GetGroup(this);
            }
            set
            {
                ICall_PhysicsShape_SetGroup(this, value);
            }
        }
        /// <summary>
        /// 读写属性：设置物理碰撞体密度
        /// </summary>
        public float Density
        {
            get
            {
                return ICall_PhysicsShape_GetDensity(this);
            }
            set
            {
                ICall_PhysicsShape_SetDensity(this, value);
            }
        }
    }
}
