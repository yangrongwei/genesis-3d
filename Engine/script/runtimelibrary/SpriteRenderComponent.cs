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
    /// 精灵渲染组件
    /// </summary>
    public partial class SpriteRenderComponent : Component
    {
        public static readonly System.Type thisType = typeof(SpriteRenderComponent);

        private SpriteRenderComponent(DummyClass__ dummy)
        {

        }
        /// <summary>
        /// 创建一个精灵
        /// </summary>
        public SpriteRenderComponent()
        {
            ICall_SpriteRenderComponent_Bind(this);
        }
        /// <summary>
        /// 通过资源包ID装载组件
        /// </summary>
        /// <param name="packID">资源包ID</param>
        public void Setup(string packID)
        {
            ICall_SpriteRenderComponent_Setup(this, packID);
        }
        /// <summary>
        /// 获取资源包ID
        /// </summary>
        public String PackageID
        {
            get
            {
                return ICall_SpriteRenderComponent_GetPackageID(this);
            }
        }

        /// <summary>
        /// 设置图块
        /// </summary>
        /// <param name="name">T图块名称</param>
        public void SetBlock(string name)
        {
            ICall_SpriteRenderComponent_SetBlock(this, name);
        }
        /// <summary>
        /// 设置动画
        /// </summary>
        /// <param name="name">动画名</param>
        public void SetAnimation(string name)
        {
            SetAnimation(name, 0, 1.0f, true);
        }

        /// <summary>
        /// 移除图块的设置
        /// </summary>
        public void RemoveBlock()
        {
            ICall_SpriteRenderComponent_RemoveBlock(this);
        }

        /// <summary>
        /// 移除动画的设置
        /// </summary>
        public void RemoveAnimation()
        {
            ICall_SpriteRenderComponent_RemoveAnimation(this);
        }
        /// <summary>
        /// 设置动画
        /// </summary>
        /// <param name="name">动画名</param>
        /// <param name="loops">播放循环</param>
        /// <param name="speed">动画速度，默认为1.0f.</param>
        /// <param name="play">是否现在播放</param>
        public void SetAnimation(string name, int loops, float speed, bool play)
        {
            ICall_SpriteRenderComponent_SetAnimation(this, name, loops, play, speed);
        }
        /// <summary>
        /// 设置与获取动画速度
        /// </summary>
        public float AnimationSpeed
        {
            get
            {
                return ICall_SpriteRenderComponent_GetAnimationSpeed(this);
            }
            set
            {
                ICall_SpriteRenderComponent_SetAnimationSpeed(this, value);
            }
        }
        /// <summary>
        /// 播放动画
        /// </summary>
        public void Play()
        {
            ICall_SpriteRenderComponent_Play(this);
        }
        /// <summary>
        /// 重新播放动画
        /// </summary>
        public void Replay()
        {
            ICall_SpriteRenderComponent_Replay(this);
        }

        /// <summary>
        /// 暂定动画
        /// </summary>
        public void Pause()
        {
            ICall_SpriteRenderComponent_Pause(this);
        }
        /// <summary>
        /// 停止动画
        /// </summary>
        public void Stop()
        {
            ICall_SpriteRenderComponent_Stop(this);
        }
        /// <summary>
        /// 播放暂停动画
        /// </summary>
        public bool PlayOnWake
        {
            get
            {
                return ICall_SpriteRenderComponent_GetPlayOnWake(this);
            }
            set
            {
                ICall_SpriteRenderComponent_SetPlayOnWake(this, value);
            }
        }
        /// <summary>
        /// 获取图块名称
        /// </summary>
        public String BlockName
        {
            get
            {
                return ICall_SpriteRenderComponent_GetBlockName(this);
            }

        }
        /// <summary>
        /// 获取动画名称
        /// </summary>
        public String AnimationName
        {
            get
            {
                return ICall_SpriteRenderComponent_GetAnimationName(this);
            }
        }
        /// <summary>
        /// 获取动画循环设置
        /// </summary>
        public int AnimationLoops
        {
            get
            {
                return ICall_SpriteRenderComponent_GetAnimationLoops(this);
            }
        }
        /// <summary>
        /// 获取动画是否正在播放
        /// </summary>
        public bool IsAnimationPlaying
        {
            get
            {
                return ICall_SpriteRenderComponent_IsAnimationPlaying(this);
            }
        }

    }
}
