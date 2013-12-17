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

namespace ScriptRuntime
{
    /// <summary>
    /// 场景类
    /// 主要用户查找当前场景Actor等功能
    /// </summary>
    public partial class Scene : Base
    {
        private Scene(DummyClass__ dummyObj)
        {
            // empty
        }
        private Scene()
        {
            
        }
        ~Scene()
        {
            ICall_Scene_Release(this);
        }
        /// <summary>
        /// 获取场景中Actor的数量
        /// </summary>
        public int ActorCount
        {
            get
            {
                return ICall_Scene_GetActorCount(this);
            }
        }
        /// <summary>
        /// 根据Actor列表的索引,返回对应的Actor
        /// </summary>
        /// <param name="index">Actor列表中的索引</param>
        /// <returns>返回对应Actor</returns>
        public Actor GetActor(int index)
        {
            return ICall_Scene_GetActor(this, index);
        }
        /// <summary>
        /// 根据fastID返回场景中其对应的Actor
        /// </summary>
        /// <param name="fastID">fastID的值</param>
        /// <returns>返回对应Actor</returns>
        public Actor FindActor(uint fastID)
        {
            return ICall_Scene_FindActorByFastID(this, fastID);
        }
         /// <summary>
        /// 根据tagID返回场景中其对应的Actor
        /// </summary>
        /// <param name="tagID">tagID的值</param>
        /// <returns>返回对应Actor</returns>
        public Actor FindActorInGroup(uint tagID)
        {
            return ICall_Scene_FindActorByTag(this, tagID);
        }

        /// <summary>
        /// 根据GroupID返回场景中其对应Actor列表
        /// </summary>
        /// <param name="GroupID">GroupID的值</param>
        /// <returns>返回对应的Actor列表</returns>
        public Actor[] FindActorsInGroup(uint tagID)
        {
            return ICall_Scene_FindActorsByTag(this, tagID);
        }
        /// <summary>
        /// 根据guid返回场景中其对应的Actor
        /// </summary>
        /// <param name="guid">guid的值</param>
        /// <returns>返回对应Actor</returns>
        public Actor FindActor(Guid guid)
        {
            byte[] guidarray = guid.ToByteArray();
            return ICall_Scene_FindActorByGuid(this, guidarray);
        }
        /// <summary>
        /// 根据Actor的名字返回对应Actor
        /// </summary>
        /// <param name="name">Actor的名字</param>
        /// <returns>返回对应的Actor</returns>
        public Actor FindActor(String name)
        {
            return ICall_Scene_FindActorByName(this, name);
        }
        /// <summary>
        /// 给场景添加一个Actor
        /// </summary>
        /// <param name="obj">要添加的Actor实例</param>
        /// <returns>添加成功返回true,反之返回false</returns>
        public bool AddActor(Actor obj)
        {
            return ICall_Scene_AddActor(this, obj);
        }
        /// <summary>
        /// 移除场景中对应的Actor实例
        /// </summary>
        /// <param name="obj">要移除的Actor实例</param>
        /// <returns>移除成功返回true,反之返回false</returns>
        public bool RemoveActor(Actor obj)
        {
            return ICall_Scene_RemoveActor(this, obj);
        }

    }
}
