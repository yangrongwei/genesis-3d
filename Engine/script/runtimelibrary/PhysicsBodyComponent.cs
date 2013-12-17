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

    public enum ForceType
    {
		NX_FORCE,
		NX_IMPULSE,
    };

    /// <summary>
    /// 物理体组件
    /// </summary>
    public partial class PhysicsBodyComponent : Component
    {
        public static readonly System.Type thisType = typeof(PhysicsBodyComponent);

        private PhysicsBodyComponent(DummyClass__ dummyObj)
        {

        }

        protected PhysicsBodyComponent()
        {


        }
        /// <summary>
        /// 读写属性：物理体瞬时速度
        /// </summary>
        public Vector3 LinearVelocity
        {
            get
            {
                Vector3 temp;
                ICall_PhysicsBodyComponent_GetLinearVelocity(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsBodyComponent_SetLinearVelocity(this, ref value);
            }
        }
        /// <summary>
        /// 读写属性：物理体瞬时角速度
        /// </summary>
        public Vector3 AngularVelocity
        {
            get
            {
                Vector3 temp;
                ICall_PhysicsBodyComponent_GetAngularVelocity(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsBodyComponent_SetAngularVelocity(this, ref value);
            }
        }
        /// <summary>
        /// 读写属性：物理体线性阻尼
        /// </summary>
        public float LinearDamping
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetLinearDamping(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetLinearDamping(this, value);
            }
        }
        /// <summary>
        /// 读写属性:物理体角度阻尼
        /// </summary>
        public float AngularDamping
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetAngularDamping(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetAngularDamping(this, value);
            }
        }
        /// <summary>
        /// 只读属性：获取物理体总质量
        /// </summary>
        public float Mass
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetMass(this);
            }
        }
        /// <summary>
        /// 读写属性：设置为静态或者动态物理体
        /// </summary>
        public bool Dynamic
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetDynamic(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetDynamic(this, value);
            }
        }
        /// <summary>
        /// 读写属性:设置为动力学物理体
        /// </summary>
        public bool Kinematic
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetKinematic(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetKinematic(this, value);
            }
        }
        /// <summary>
        /// 读写属性：是否开启重力
        /// </summary>
        public bool UseGravity
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetUseGravity(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetUseGravity(this, value);
            }
        }
        /// <summary>
        /// 读写属性：是否发生碰撞检测
        /// </summary>
        public bool Collision
        {
            get
            {
                return ICall_PhysicsBodyComponent_GetCollision(this);
            }
            set
            {
                ICall_PhysicsBodyComponent_SetCollision(this, value);
            }
        }
        /// <summary>
        /// 读写属性：给物理体添加恒力
        /// </summary>
        public Vector4 ConstForce
        {
            get
            {
                Vector4 temp;
                ICall_PhysicsBodyComponent_GetConstForce(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsBodyComponent_SetConstForce(this, ref value);
            }
        }
        /// <summary>
        /// 读写属性：给物理体添加恒定转矩
        /// </summary>
        public Vector4 ConstTorque
        {
            get
            {
                Vector4 temp;
                ICall_PhysicsBodyComponent_GetConstTorque(this, out temp);
                return temp;
            }
            set
            {
                ICall_PhysicsBodyComponent_SetConstTorque(this, ref value);
            }
        }
        /// <summary>
        /// 按照给的距离移动物理体或者角色控制器
        /// </summary>
        /// <param name="f3Pos">移动的距离</param>
        public void MovePosition(ref Vector3 f3Pos)
        {
            ICall_PhysicsBodyComponent_MovePostion(this, ref f3Pos);
        }
        /// <summary>
        /// 移动物理体到指定位置
        /// </summary>
        /// <param name="f3Pos">移动到的目标位置</param>
        public void MoveToPosition(ref Vector3 f3Pos)
        {
            ICall_PhysicsBodyComponent_MoveToPostion(this, ref f3Pos);
        }
        /// <summary>
        /// 按照给定的角度选择物理体
        /// </summary>
        /// <param name="rot">旋转角</param>
        public void RotationRotation(ref Quaternion rot)
        {
            ICall_PhysicsBodyComponent_RotateRotation(this, ref rot);
        }
        /// <summary>
        /// 旋转到指定的角度
        /// </summary>
        /// <param name="rot">旋转到的目标角度</param>
        public void RotationToRotation(ref Quaternion rot)
        {
            ICall_PhysicsBodyComponent_RotateToRotation(this, ref rot);
        }
        /// <summary>
        /// 添加力
        /// </summary>
        /// <param name="force">力</param>
        /// <param name="forcetype">力的类型</param>
        /// <param name="bWakeUp">是否唤醒Actor</param>
        public void AddForce(Vector3 force, ForceType forcetype, bool bWakeUp)
        {
            ICall_PhysicsBodyComponent_AddForce(this, ref force, forcetype, bWakeUp);
        }
        /// <summary>
        /// 在世界位置添加力
        /// </summary>
        /// <param name="force">力</param>
        /// <param name="pos">力的施加位置</param>
        /// <param name="forcetype">力的类型</param>
        /// <param name="bWakeUp">是否唤醒Actor</param>
        public void AddForceAtPos(Vector3 force, Vector3 pos, ForceType forcetype, bool bWakeUp)
        {
            ICall_PhysicsBodyComponent_AddForceAtPos(this, ref force, ref pos, forcetype, bWakeUp);
        }
        /// <summary>
        /// 在世界位置添加本地力
        /// </summary>
        /// <param name="force">力</param>
        /// <param name="pos">力的施加位置</param>
        /// <param name="forcetype">力的类型</param>
        /// <param name="bWakeUp">是否唤醒Actor</param>
        public void AddLocalForceAtPos(Vector3 force, Vector3 pos, ForceType forcetype, bool bWakeUp)
        {
            ICall_PhysicsBodyComponent_AddLocalForceAtPos(this, ref force, ref pos, forcetype, bWakeUp);
        }
        /// <summary>
        /// 在本地位置添加力
        /// </summary>
        /// <param name="force">力</param>
        /// <param name="pos">力的施加位置</param>
        /// <param name="forcetype">力的类型</param>
        /// <param name="bWakeUp">是否唤醒Actor</param>
        public void AddForceAtLocalPos(Vector3 force, Vector3 pos, ForceType forcetype, bool bWakeUp)
        {
            ICall_PhysicsBodyComponent_AddForceAtLocalPos(this, ref force, ref pos, forcetype, bWakeUp);
        }
        /// <summary>
        /// 在本地位置添加本地力
        /// </summary>
        /// <param name="force">力</param>
        /// <param name="pos">力的施加位置</param>
        /// <param name="forcetype">力的类型</param>
        /// <param name="bWakeUp">是否唤醒Actor</param>
        public void AddLocalForceAtLocalPos(Vector3 force, Vector3 pos, ForceType forcetype, bool bWakeUp)
        {
            ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos(this,ref force,ref pos, forcetype, bWakeUp);
        }
        /// <summary>
        /// 添加物理形状
        /// </summary>
        /// <param name="type">形状类型</param>
        public void CreateShape(PhyXShapeType type)
        {
            ICall_PhysicsEntity_CreateShape(this, (int)type);
        }
        /// <summary>
        /// 删除指定为位置的物理形状
        /// </summary>
        /// <param name="index">指定位置</param>
        public void RemoveShapeAt(int index)
        {
            ICall_PhysicsEntity_RemoveShapeAt(this, index);
        }
        /// <summary>
        /// 替换指定位置物理形状
        /// </summary>
        /// <param name="index">指定位置</param>
        /// <param name="type">替换为的物理形状类型</param>
        public void ReplaceShape(int index, PhyXShapeType type)
        {
            ICall_PhysicsEntity_ReplaceShape(this, index, (int)type);
        }
        /// <summary>
        /// 获取指定位置物理形状
        /// </summary>
        /// <param name="index">指定位置</param>
        /// <returns>物理形状指针</returns>
        public PhysicsShape GetShapeAt(int index)
        {
            return ICall_PhysicsEntity_GetShapeAt(this, index);
        }
        /// <summary>
        /// 获取物理形状个数
        /// </summary>
        /// <returns></returns>
        public int GetShapeCount()
        {
            return ICall_PhysicsEntity_GetShapeCount(this);
        }
        /// <summary>
        /// 只读属性：角色控制器是否接触地面
        /// </summary>
        public bool IsOnGround
        {
            get
            {
                return ICall_PhysicsRole_IsOnGround(this);
            }
        }
        /// <summary>
        /// 只读属性：角色控制器是否悬空
        /// </summary>
        public bool IsFreeFloat
        {
            get
            {
                return ICall_PhysicsRole_IsFreeFloat(this);
            }
        }
        /// <summary>
        /// 只读属性：角色控制器是否接触天花板
        /// </summary>
        public bool IsTouchCeil
        {
            get
            {
                return ICall_PhysicsRole_IsTouchCeil(this);
            }
        }
        /// <summary>
        /// 只读属性：角色控制器是否接触物体边缘
        /// </summary>
        public bool IsTouchSides
        {
            get
            {
                return ICall_PhysicsRole_IsTouchSides(this);
            }
        }
        /// <summary>
        /// 可读写属性：斜坡高度
        /// </summary>
        public float SlopeLimit
        {
            set
            {
                ICall_PhysicsRole_SetSlopeLimit(this, value);
            }
            get
            {
                return ICall_PhysicsRole_GetSlopeLimit(this);
            }
        }
        /// <summary>
        /// 可读写属性：可跨越的障碍物最大高度
        /// </summary>
        public float StepOffset
        {
            set
            {
                ICall_PhysicsRole_SetStepOffset(this, value);
            }
            get
            {
                return ICall_PhysicsRole_GetStepOffset(this);
            }
        }
        /// <summary>
        /// 读写属性：角色控制器胶囊体半径
        /// </summary>
        public float Radius
        {
            set
            {
                ICall_PhysicsRole_SetRadius(this, value);
            }
            get
            {
                return ICall_PhysicsRole_GetRadius(this);
            }
        }
        /// <summary>
        /// 读写属性：角色控制器胶囊体高度
        /// </summary>
        public float Height
        {
            set
            {
                ICall_PhysicsRole_SetHeight(this, value);
            }
            get
            {
                return ICall_PhysicsRole_GetHeight(this);
            }
        }
        /// <summary>
        /// 读写属性：角色控制器胶囊体高度
        /// </summary>
        public Vector3 LocalCenter
        {
            set
            {
                ICall_PhysicsRole_SetCenter(this, ref value);
            }
            get
            {
                return ICall_PhysicsRole_GetCenter(this);
            }
        }
    }
}
