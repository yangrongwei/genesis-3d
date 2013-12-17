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
    public enum WrapMode
    {
        ONCE     = 1,
		LOOP     = 2,
		PINGPONG = 4,
		ClAMP    = 8
    }
    public enum PlayMode
    {
        StopSameAnimLayer = 0,
        StopAllAnim = 4
    };

    /// <summary>
    /// 动画组件类
    /// 设置动画的播放状态，进行动画挂接
    /// </summary>
    public partial class AnimationComponent : Component
    {
        public static readonly System.Type thisType = typeof(AnimationComponent);

        private AnimationComponent(DummyClass__ dummy)
        {

        }

        /// <summary>
        /// 设置动画路径
        /// </summary>
        /// <param name="id">动画路径</param>
        public void SetAnimationID(String id)
        {
            ICall_AnimationComponent_SetAnimationID(this, id);
        }
        
        /// <summary>
        /// 过渡至目标动画
        /// </summary>
        /// <param name="name">需要要过渡的动画路径</param>
        /// <param name="type">动画播放模式</param>
        /// <param name="time">过渡时间长度</param>
        public void CrossFading(String name ,PlayMode type ,float time)
        {
            ICall_AnimationComponent_CrossFading(this, name,(int) type , time);
        }

        /// <summary>
        /// 过渡至目标动画
        /// </summary>
        /// <param name="name">需要要过渡的动画路径</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            actor.Animation.PlayAnimation("first");
            actor.Animation.CrossFading("second");
        }
        @endcode
        */
        public void CrossFading(String name)
        {
            CrossFading(name, PlayMode.StopSameAnimLayer,0.3f);
        }

        /// <summary>
        /// 过渡至目标动画
        /// </summary>
        /// <param name="name">需要要过渡的动画路径</param>
        /// <param name="time">过渡时间长度</param>
        public void CrossFading(String name,float time)
        {
            CrossFading(name, PlayMode.StopSameAnimLayer, time);
        }

        /// <summary>
        /// 播放动画
        /// </summary>
        /// <param name="name">需要播放的动画路径</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            actor.Animation.PlayAnimation("first");
        }
        @endcode
        */
        public void PlayAnimation(String name)
        {
            ICall_AnimationComponent_PlayAnimation(this, name);
        }

        /// <summary>
        /// 停止播放动画
        /// </summary>
        /// <param name="name">要停止播放的动画路径</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (actor.Animation.IsAnimationPlaying("first"))
            {
                actor.Animation.StopAnimation("first");
            }
        }
        @endcode
        */
        public void StopAnimation(String name)
        {
            ICall_AnimationComponent_StopAnimation(this, name);
        }

        /// <summary>
        /// 与当前正在播放的动画进行混合
        /// </summary>
        /// <param name="name">想要混合的动画路径</param>
        /// <param name="weight">混合的权重</param>
        /// <param name="time">混合到目标权重所需时间</param>
        public void BlendingAnimation(String name, float weight, float time)
        {
            ICall_AnimationComponent_BlendingAnimation(this, name, weight, time);
        }

        /// <summary>
        /// 与当前正在播放的动画进行混合
        /// </summary>
        /// <param name="name">想要混合的动画路径</param>
        /// <param name="weight">混合的权重</param>
        public void BlendingAnimation(String name, float weight)
        {
            BlendingAnimation(name, weight, 0.3f);
        }

        /// <summary>
        /// 设置动画播放速度
        /// </summary>
        /// <param name="name">要设置的动画路径</param>
        /// <param name="speed">速度</param>
        public void SetAnimationSpeed(String name, float speed)
        {
            ICall_AnimationComponent_SetAnimationSpeed(this, name, speed);
        }

        /// <summary>
        /// 设置动画播放模式
        /// </summary>
        /// <param name="name">要设置的动画路径</param>
        /// <param name="wrapMode">播放模式</param>
        public void SetWrapMode(String name, WrapMode wrapMode)
        {
            ICall_AnimationComponent_SetAnimationWrapMode(this, name, (int)wrapMode);
        }

        /// <summary>
        /// 设置动画层级
        /// </summary>
        /// <param name="name">要设置的动画路径</param>
        /// <param name="layer">动画层级</param>
        public void SetLayer(String name, int layer)
        {
            ICall_AnimationComponent_SetAnimationLayer(this, name, layer);
        }

        /// <summary>
        /// 添加会影响动画骨骼节点
        /// </summary>
        /// <param name="animName">要影响的动画路径</param>
        /// <param name="nodeName">骨骼节点名称</param>
        /// <param name="recursive">是否包括所有子节点</param>
        public void AddAffectedNodes(String animName, String nodeName, bool recursive)
        {
            ICall_AnimationComponent_AddAffectedNodes(this, animName, nodeName, recursive);
        }

        /// <summary>
        /// 添加会影响动画骨骼节点
        /// </summary>
        /// <param name="animName">要影响的动画路径</param>
        /// <param name="nodeName">骨骼节点名称</param>
        public void AddAffectedNodes(String animName, String nodeName)
        {
            ICall_AnimationComponent_AddAffectedNodes(this, animName, nodeName, true);
        }

        /// <summary>
        /// 移除会影响动画骨骼节点
        /// </summary>
        /// <param name="animName">要影响的动画路径</param>
        /// <param name="nodeName">骨骼节点名称</param>
        public void RemoveAffectedNodes(String animName, String nodeName)
        {
            ICall_AnimationComponent_RemoveAffectedNodes_2(this, animName, nodeName, true);
        }

        /// <summary>
        /// 移除会影响动画骨骼节点
        /// </summary>
        /// <param name="animName">要影响的动画路径</param>
        /// <param name="nodeName">骨骼节点名称</param>
        /// <param name="recursive">是否包括所有子节点</param>
        public void RemoveAffectedNodes(String animName, String nodeName, bool recursive)
        {
            ICall_AnimationComponent_RemoveAffectedNodes_2(this, animName, nodeName, recursive);
        }
        /// <summary>
        /// 添加挂接物体
        /// </summary>
        /// <param name="actor">需要挂接上去的Actor</param>
        /// <param name="skelName">挂接目标骨骼</param>
        public void AddAttachedActor(Actor actor, String skelName)
        {
            ICall_AnimationComponent_AddAttachedActor(this, actor, skelName);
        }

        /// <summary>
        /// 移除挂接物体
        /// </summary>
        /// <param name="actor">想要移除的Actor</param>
        public void RemoveAttachedActor(Actor actor)
        {
            ICall_AnimationComponent_RemoveAttachedActor(this, actor);
        }

        /// <summary>
        /// 检测动画是否在播放
        /// </summary>
        /// <param name="name">所检测的动画路径</param>
        /// <returns>返回是否在播放</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (actor.Animation.IsAnimationPlaying("first"))
            {
                actor.Animation.StopAnimation("first");
            }
        }
        @endcode
        */
        public bool IsAnimationPlaying(String name)
        {
            return ICall_AnimationComponent_IsAnimationPlaying(this, name);
        }

        /// <summary>
        /// 根据名称获取动画播放到了第几帧
        /// </summary>
        /// <returns>返回当前帧数</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (actor.Animation.IsAnimationPlaying("first"))
            {
                float frame = actor.Animation.GetCurrentFrame("first");
            }
        }
        @endcode
        */
        public float GetCurrentFrame(String name)
        {
            return ICall_AnimationComponent_GetCurrentFrame(this, name);
        }

        /// <summary>
        /// 获取当前动画播放到了第几帧
        /// </summary>
        /// <returns>返回当前帧数</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            float frame = actor.Animation.GetCurrentFrame();
        }
        @endcode
        */
        public float GetCurrentFrame()
        {
            return ICall_AnimationComponent_GetCurAnimCurrentFrame(this);
        }

        /// <summary>
        /// 根据名称获取动画的总帧数
        /// </summary>
        /// <param name="name">动画名称</param>
        /// <returns>总帧数</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            float frame = actor.Animation.GetAnimFrameCount("first");
        }
        @endcode
        */
        public int GetAnimFrameCount(String name)
        {
            return ICall_AnimationComponent_GetAnimFrameCount(this, name);
        }

        /// <summary>
        /// 获取当前播放的动画的总帧数
        /// </summary>
        /// <returns>总帧数</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            float frame = actor.Animation.GetCurrentAnimFrameCount();
        }
        @endcode
        */
        public int GetCurrentAnimFrameCount()
        {
            return ICall_AnimationComponent_GetCurrentAnimFrameCount(this);
        }

        /// <summary>
        /// 获取当前播放的动画名称
        /// </summary>
        /// <returns>动画名称</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            string sName = actor.Animation.GetCurrentAnimation();
        }
        @endcode
        */
        public String GetCurrentAnimation()
        {
            return ICall_AnimationComponent_GetCurrentAnimation(this);
        }

        /// <summary>
        /// 获取骨骼节点的变换矩阵
        /// </summary>
        /// <param name="name">查找的骨骼节点名称</param>
        /// <param name="trans">输出的矩阵</param>
        /// <returns>返回是否查找到节点</returns>
        public bool GetNodeTransform(String name, out Matrix44 trans)
        {
            return ICall_AnimationComponent_GetNodeTransform(this, name, out trans);
        }

        /// <summary>
        /// 根据名称获取动画的播放模式
        /// </summary>
        /// <param name="name">动画名称</param>
        /// <returns>播放模式</returns>
        public WrapMode GetWrapMode(String name)
        {
            WrapMode wrapMode = (WrapMode)ICall_AnimationComponent_GetWrapMode(this, name);
            return wrapMode;
        }
    }
}
