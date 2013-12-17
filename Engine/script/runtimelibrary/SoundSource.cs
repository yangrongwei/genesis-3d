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

    public enum SoundRollOffMode
    {
        Inverse = 0,
        Linear = 1,
        LinearSquare = 2,
    }
    /// <summary>
    /// 声音组件类，继承自组件类
    /// 可以挂接到游戏对象上，控制对声音的操作
    /// </summary>
    public partial class SoundSource : Component
    {
        /// <summary>
        /// 音源组件的组件类型
        /// </summary>
        public static readonly System.Type thisType = typeof(SoundSource);

        private SoundSource(DummyClass__ dummy)
        {

        }
        /// <summary>
        /// 播放声音
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
        }
        @endcode
        */
        public void Play()
        {
            ICall_SoundSource_Play(this);
        }
        /// <summary>
        /// 停止播放声音
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Stop();
        }
        @endcode
        */
        public void Stop()
		{
		    ICall_SoundSource_Stop(this);
		}
        /// <summary>
        /// 暂停播放声音
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Pause();
        }
        @endcode
        */
        public void Pause()
		{
		    ICall_SoundSource_Pause(this);
		}
        /// <summary>
        /// 布尔值，声音否在播放中，播放中为true,否则为false
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            bool bIsPlaying = actor.GetComponent<SoundSource>().IsPlaying;
            actor.GetComponent<SoundSource>().Play();
            bIsPlaying = actor.GetComponent<SoundSource>().IsPlaying;
        }
        @endcode
        */
        public bool IsPlaying
		{
		   get
           {
               return ICall_SoundSource_IsPlaying(this);
           }
            
		}

        /// <summary>
        /// 布尔值，声音是否循环播放，若为循环播放为true,否则为false
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            bool bLoop = actor.GetComponent<SoundSource>().Loop;
        }
        @endcode
        */
        public bool Loop
        {
            get
            {
                return ICall_SoundSource_GetLoop(this);
            }
            set
            {
                ICall_SoundSource_SetLoop(this, value);
            }
        }
        
        /// <summary>
        /// 浮点型，音量
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            float fVolume = actor.GetComponent<SoundSource>().Volume;
            if (1.0f > fVolume)
            {
                actor.GetComponent<SoundSource>().Volume = 1.0f;
            }
        }
        @endcode
        */
        public float Volume
        {
            get
            {
                return ICall_SoundSource_GetVolume(this);
            }
            set
            {
                ICall_SoundSource_SetVolume(this, value);
            }
        }
        /// <summary>
        /// 枚举类型，声音衰减模式，可取：Inverse（0），Linear（1），LinearSquare（2）三种
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            SoundRollOffMode rollOffMode = actor.GetComponent<SoundSource>().RollOffMode;
            actor.GetComponent<SoundSource>().RollOffMode = SoundRollOffMode.Linear;
        }
        @endcode
        */
        public SoundRollOffMode RollOffMode
        {
            get
            {
                return (SoundRollOffMode)ICall_SoundSource_GetRolloffMode(this);
            }
            set
            {
                ICall_SoundSource_SetRolloffMode(this, (int)value);
            }
        }
        
        /// <summary>
        ///获得声音名字
        /// </summary>
        /// <returns>声音名字</returns>
        public String GetSoundResID()
		{
			return ICall_SoundSource_GetName(this);
		}
        /// <summary>
        /// 重载函数，设置声音名字
        /// </summary>
        /// <param name="name">声音名字</param>
        /// <param name="loadpriority">优先级</param>
        public void SetSoundResID(String name, int loadpriority)
		{
            ICall_SoundSource_SetName(this, name, loadpriority);
		}
        /// <summary>
        /// 重载函数，设置声音名字
        /// </summary>
        /// <param name="name">声音名字</param>
        public void SetSoundResID(String name)
        {
            int loadpriority = 0;
            ICall_SoundSource_SetName(this, name, loadpriority);
        }

        /// <summary>
        /// 浮点值，音调
        /// </summary>
        public float Pitch
        {
            get
            {
                return ICall_SoundSource_GetPitch(this);
            }
            set
            {
                ICall_SoundSource_SetPitch(this, value);
            }
        }
        /// <summary>
        /// 布尔值，true为3D,false为2D
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            actor.GetComponent<SoundSource>().Play();
            bool bIs3D = actor.GetComponent<SoundSource>().Is3D;
        }
        @endcode
        */
        public bool Is3D
        {
            get
            {
                return ICall_SoundSource_Is3D(this);
            }
            set
            {
                ICall_SoundSource_Set3D(this, value);
            }
        }
        /// <summary>
        /// 浮点值，声音最小距离
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            float fMinDistance = actor.GetComponent<SoundSource>().MinDistance;
            actor.GetComponent<SoundSource>().MinDistance = 10;
        }
        @endcode
        */
        public float MinDistance
       {
           get
           {
               return ICall_SoundSource_GetMinDistance(this);
           }
           set
           {
               ICall_SoundSource_SetMinDistance(this, value);
           }
       }

        /// <summary>
        /// 浮点值，声音最大距离
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("sound");
        if (null != actor)
        {
            float fMaxDistance = actor.GetComponent<SoundSource>().MaxDistance;
            actor.GetComponent<SoundSource>().MaxDistance = 100;
        }
        @endcode
        */
        public float MaxDistance
         {
            get
             {
                 return ICall_SoundSource_GetMaxDistance(this);
             }
            set
             {
                 ICall_SoundSource_SetMaxDistance(this, value);
             }
         }
        /// <summary>
        ///  获得声音资源的优先级
        /// </summary>
        /// <returns>声音资源优先级，整型</returns>
        public int GetLoadPriority()
        {
            return ICall_SoundSource_GetLoadPriority(this);
        }
        /// <summary>
        /// 判断声音资源是否被加载成功
        /// </summary>
        /// <returns>布尔值，true表示加载成功，false表示加载失败</returns>
        public bool IsAllLoaded()
        {
            return ICall_SoundSource_IsAllLoaded(this);
        }
    }
}

