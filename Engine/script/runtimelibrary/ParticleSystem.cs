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
    /// 粒子系统，控制粒子系统的运行。
    /// </summary>
    public class ParticleSystem : Base
    {
         private ParticleSystem(DummyClass__ dummyObj )
        {

        }

        /// <summary>
        /// 粒子系统构造函数
        /// </summary>
        public ParticleSystem()
        {
            ICall_ParticleSystem_Bind(this);
        }

        ~ParticleSystem()
        {
            ICall_ParticleSystem_Release(this);
        }

        /// <summary>
        ///  粒子系统名字的设置和获取.
        /// </summary>
        /// <param value>粒子系统的名字.</param>
        /// <returns>粒子系统的名字.</returns>
        public String Name
        {
            set 
            {
                ICall_ParticleSystem_SetName(this, value);
            }
            get
            {
                return ICall_ParticleSystem_GetName(this);
            }
        }
        /// <summary>
        ///  播放粒子.
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                partial.Play();
            }
        }
        @endcode
        */
        public void Play( )
        {
            ICall_ParticleSystem_Play( this );
        }
        /// <summary>
        ///  暂停粒子.
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                partial.Pause();
            }
        }
        @endcode
        */
        public void Pause()
        {
            ICall_ParticleSystem_Pause(this);
        }
        /// <summary>
        ///  停止粒子.
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                partial.Stop();
            }
        }
        @endcode
        */
        public void Stop()
        {
            ICall_ParticleSystem_Stop(this);
        }
        /// <summary>
        ///  当前粒子系统是否在播放.
        /// </summary>
        /// <returns>粒子系统播放与否.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                bool bIsPlaying = partial.IsPlaying;
            }
        }
        @endcode
        */
        public bool IsPlaying
        {
            get
            {
                return ICall_ParticleSystem_IsPlaying(this);
            }
        }
        /// <summary>
        ///  当前粒子系统是否在暂停.
        /// </summary>
        /// <returns>粒子系统暂停与否.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                bool bIsPaused = partial.IsPaused;
            }
        }
        @endcode
        */
        public bool IsPaused
        {
            get
            {
                return ICall_ParticleSystem_IsPaused(this);
            }
        }
        /// <summary>
        ///  当前粒子系统是否在停止.
        /// </summary>
        /// <returns>粒子系统停止与否.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleSystem partial = actor.ParticleRender.GetParticleSystem();
            if (null != partial)
            {
                bool bIsStop = partial.IsStop;
            }
        }
        @endcode
        */
        public bool IsStop
        {
            get
            {
                return ICall_ParticleSystem_IsStop(this);
            }
        }
        /// <summary>
        ///  粒子系统的播放速率.
        /// </summary>
        public float PlayRateScale
        {
            set
            {
                ICall_ParticleSystem_SetPlayRateScale(this, value);
            }
            get
            {
                return ICall_ParticleSystem_GetPlayRateScale(this);
            }
        }

        /// <summary>
        /// 获取与设置粒子系统中的粒子数量
        /// </summary>
        public int ParticleQuato
        {
            set
            {
                ICall_ParticleSystem_SetQuato(this, value);
            }
            get
            {
                return (int)ICall_ParticleSystem_GetQuato(this);
            }
        }

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_Bind(ParticleSystem self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_Release(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_SetName(ParticleSystem ps, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static string ICall_ParticleSystem_GetName(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_Play(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_Pause(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_Stop(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_ParticleSystem_IsPlaying(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_ParticleSystem_IsPaused(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_ParticleSystem_IsStop(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_SetPlayRateScale(ParticleSystem ps, float rateScale);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ParticleSystem_GetPlayRateScale(ParticleSystem ps);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ParticleSystem_SetQuato(ParticleSystem ps, int quato);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ParticleSystem_GetQuato(ParticleSystem ps);
    }
}
