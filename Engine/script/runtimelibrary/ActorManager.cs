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
    /// 一个管理游戏中所有Actor的类。
    /// </summary>
    public static partial class ActorManager
    {
        /// <summary>
        /// 通过Template创建一个Actor.
        /// </summary>
        /// <param name="name">Template的路径.</param>
        /// <param name="bCopy">是否拷贝Template，默认为False.</param>
        /// <returns>创建出来的Actor.</returns>
        static public Actor CreateFromTemplate(String name,bool bCopy = false)
        {
            return ICall_ActorManager_CreateFromTemplate(name,bCopy);
        }  
        /// <summary>
        /// 通过Index获取当前活动的Actor。
        /// </summary>
        /// <param name="index">Index值.</param>
        /// <returns>Index对应的活动Actor.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        int iCount = ActorManager.GetActiveActorCount();
        if (0 < iCount)
        {
            Actor actor = ActorManager.GetActiveActor(0);
        }
        @endcode
        */
        static public Actor GetActiveActor(int index)
        {
            return ICall_ActorManager_GetActiveActor(index);
        }
        /// <summary>
        /// 获取当前活动的Actor数目.
        /// </summary>
        /// <returns>当前活动的Actor数目.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        int iCount = ActorManager.GetActiveActorCount();
        if (0 < iCount)
        {
            Actor actor = ActorManager.GetActiveActor(0);
        }
        @endcode
        */
        static public int GetActiveActorCount()
        {
            return ICall_ActorManager_GetActiveActorCount();
        }
        /// <summary>
        /// 通过ActorID获取Actor.
        /// </summary>
        /// <param name="fastID">Actor的ActorID.</param>
        /// <returns>被找到的Actor.</returns>
        static public Actor FindActiveActor(uint fastID)
        {
            return ICall_ActorManager_FindActiveActorByFastID(fastID);
        }

        /// <summary>
        /// 通过标签找到标签为tagID的第一个Actor.
        /// </summary>
        /// <param name="GroupID">标签ID.</param>
        /// <returns>被找到的第一个Actor.</returns>
        static public Actor FindActiveActorInGroup(uint tagID)
        {
            return ICall_ActorManager_FindActiveActorInGroup(tagID);
        }

        /// <summary>
        /// 通过标签找到所有标签为tagID的Actor.
        /// </summary>
        /// <param name="GroupID">标签ID.</param>
        /// <returns>被找到的所有Actor.</returns>
        static public Actor[] FindActiveActorsInGroup(uint tagID)
        {
            return ICall_ActorManager_FindActiveActorsInGroup(tagID);
        }
        /// <summary>
        /// 通过GUID找Actor.
        /// </summary>
        /// <param name="guid">GUID</param>
        /// <returns>被找到的Actor.</returns>
        static public Actor FindActiveActor(Guid guid)
        {
            byte[] guidarray = guid.ToByteArray();
            return ICall_ActorManager_FindActiveActorByGuid(guidarray);
        }
        /// <summary>
        /// 通过名字查找Actor.
        /// </summary>
        /// <param name="name">名字</param>
        /// <returns>被找到的Actor.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ScriptRuntime.Debug.Printf("ActorManager.FindActiveActor");
        }
        @endcode
        */
        static public Actor FindActiveActor(String name)
        {
            return ICall_ActorManager_FindActiveActorByName(name);
        }
        /// <summary>
        /// 获取主摄像机.
        /// </summary>
        /// <returns>主摄像机的Actor.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.MainCameraActor;
        @endcode
        */
        static public Actor MainCameraActor
        {
            get
            {
                return ICall_ActorManager_GetMainCameraActor();
            }
        }
    }
}
