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
    /// 混音过滤器组件
    /// 主要用于声音特效
    /// 要使过滤器生效,必须有声音组件
    /// </summary>
    public partial class SoundReverbFilterComponent : Component
    {
        public static readonly System.Type thisType = typeof(SoundReverbFilterComponent);

        private SoundReverbFilterComponent(DummyClass__ dummy)
        {

        }

        /// <summary>
        /// 混音过滤器组件构造函数
        /// </summary>
        public SoundReverbFilterComponent()
        {
            ICall_SoundReverbFilterComponent_Bind(this);
        }

        /// <summary>
        /// 激活混音过滤器
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
        }
        @endcode
        */
        public void Attach()
        {
            ICall_SoundReverbFilterComponent_Attach(this);
        }

        /// <summary>
        /// 暂停混音过滤器
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Detach();
        }
        @endcode
        */
        public void Detach()
        {
            ICall_SoundReverbFilterComponent_Detach(this);
        }

        public enum SoundReverbMode
        {
            OFF,
            GENERIC,
            PADDEDCELL,
            ROOM,
            BATHROOM,
            STONEROOM,
            AUDITORIUM,
            CONCERTHALL,
            CAVE,
            ARENA,
            HANGAR,
            HALLWAY,
            STONECORRIDOR,
            ALLEY,
            FOREST,
            CITY,
            MOUNTAINS,
            QUARRY,
            PLAIN,
            PARKINGLOT,
            SEWERPIPE,
            UNDERWATER,   
        } 


        /// <summary>
        /// 获取与设置混音过滤器的种类
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            if (SoundReverbFilterComponent.SoundReverbMode.OFF != actor.GetComponent<SoundReverbFilterComponent>().ReverbMode)
            {
                actor.GetComponent<SoundReverbFilterComponent>().ReverbMode = SoundReverbFilterComponent.SoundReverbMode.OFF;
            }
        }
        @endcode
        */
        public SoundReverbMode ReverbMode
        {
            get
            {
                return (SoundReverbMode)ICall_SoundReverbFilterComponent_GetReverbPreset(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetReverbPreset(this, (int)value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的回声密度
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().Density = 0.0f;
        }
        @endcode
        */
        public float Density
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDensity(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDensity(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的回声扩散
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().Diffusion = 0.0f;
        }
        @endcode
        */
        public float Diffusion
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDiffusion(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDiffusion(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的增益属性
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().Gain = 0.0f;
        }
        @endcode
        */
        public float Gain
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetGain(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetGain(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的高频增益属性
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().GainHF = 0.0f;
        }
        @endcode
        */
        public float GainHF
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetGainHF(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetGainHF(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的混音衰减
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().DecayTime = 0.0f;
        }
        @endcode
        */
        public float DecayTime
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDecayTime(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDecayTime(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的高频衰减
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().DecayHFRatio = 0.0f;
        }
        @endcode
        */
        public float DecayHFRatio
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDecayHFRatio(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDecayHFRatio(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的低频衰减
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().DecayLFRatio = 0.0f;
        }
        @endcode
        */
        public float DecayLFRatio
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDecayLFRatio(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDecayLFRatio(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的回声增益属性
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ReflectionsGain = 0.0f;
        }
        @endcode
        */
        public float ReflectionsGain
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetReflectionsGain(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetReflectionsGain(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的回声衰减属性
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ReflectionsDelay = 0.0f;
        }
        @endcode
        */
        public float ReflectionsDelay
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetReflectionsDelay(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetReflectionsDelay(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的混音增益
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ReverbGain = 0.0f;
        }
        @endcode
        */
        public float ReverbGain
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetReverbGain(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetReverbGain(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的混音衰减
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ReverbDelay = 0.0f;
        }
        @endcode
        */
        public float ReverbDelay
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetReverbDelay(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetReverbDelay(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的回声时间
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().EchoTime = 0.0f;
        }
        @endcode
        */
        public float EchoTime
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetEchoTime(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetEchoTime(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的调制深度
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().EchoDepth = 0.0f;
        }
        @endcode
        */
        public float EchoDepth
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetEchoDepth(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetEchoDepth(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的调制时间
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ModulationTime = 0.0f;
        }
        @endcode
        */
        public float ModulationTime
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetModulationTime(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetModulationTime(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的调制深度
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().ModulationDepth = 0.0f;
        }
        @endcode
        */
        public float ModulationDepth
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetModulationDepth(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetModulationDepth(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的媒介增益
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().AirGainHF = 0.0f;
        }
        @endcode
        */
        public float AirGainHF
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetAirGainHF(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetAirGainHF(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的高频基准频率
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().HFReference = 0.0f;
        }
        @endcode
        */
        public float HFReference
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetHFReference(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetHFReference(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的低频基准频率
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().LFReference = 0.0f;
        }
        @endcode
        */
        public float LFReference
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetLFReference(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetLFReference(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的空间衰减
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            actor.GetComponent<SoundReverbFilterComponent>().RoomRolloff = 0.0f;
        }
        @endcode
        */
        public float RoomRolloff
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetRoomRolloff(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetRoomRolloff(this, value);
            }
        }

        /// <summary>
        /// 获取与设置混音过滤器的高频衰减界限
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            actor.AddComponent<SoundReverbFilterComponent>();
            actor.GetComponent<SoundReverbFilterComponent>().Attach();
            if (!actor.GetComponent<SoundReverbFilterComponent>().DecayHFLimit)
            {
                actor.GetComponent<SoundReverbFilterComponent>().DecayHFLimit = true;
            }
        }
        @endcode
        */
        public bool DecayHFLimit
        {
            get
            {
                return ICall_SoundReverbFilterComponent_GetDecayHFLimit(this);
            }
            set
            {
                ICall_SoundReverbFilterComponent_SetDecayHFLimit(this, value);
            }
        }
    }
}



