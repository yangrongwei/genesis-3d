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

using System.Globalization;
using System.Runtime.InteropServices;

namespace ScriptRuntime
{
    /// <summary>
    /// Actor对象,游戏中所有的对象的基本单位
    /// 组件等都是挂接在Actor上的
    /// </summary>
    public partial class Actor : Base
    {
        // - private data
        private String m_sName;
        private String m_sTemplateName;
        private UInt32 m_iTagID;
        private UInt32 m_iFastID;
        private AnimationComponent m_animationComponent;
        private SpriteRenderComponent m_spriteRenderComponent;
        private MeshRenderComponent m_meshRenderComponent;
        private SkinnedMeshRenderComponent m_skinnedMeshRenderComponent;
        private ProjectorRenderComponent m_projectorRenderComponent;
        private SkeletonComponent m_skeletonComponent;
        private ParticleRenderComponent m_particleRenderComponent;
        private ScriptComponent m_scriptComponent;
        private CameraComponent m_cameraComponent;
        private SoundSource m_SoundSource;
        private SoundEchoFilterComponent m_EchoFilter;
        private SoundLowPassFilterComponent m_LowPassFilter;
        private SoundReverbFilterComponent m_ReverbFilter;

        private object userdata = null;

        private Actor(DummyClass__ dummyObj)
        {
            //empty
            initialize();
        }

        ~Actor()
        {
            //   DeactiveWithoutChildren(0.0f);
            ICall_Actor_Release(this);
        }

        /// <summary>
        /// Actor的构造函数
        /// </summary>
        public Actor()
        {
            initialize();
            ICall_Actor_Bind(this);
        }
        /// <summary>
        /// Actor的构造函数
        /// </summary>
        /// <param name="name">Actor的名字</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = new Actor("test");
        actor.Active();
        @endcode
        */
        public Actor(String name)
        {
            initialize();
            ICall_Actor_Bind(this);
            ICall_Actor_SetName(this, name);
        }

        private void reset()
        {
            m_animationComponent = null;
            m_meshRenderComponent = null;
            m_spriteRenderComponent = null;
            m_skinnedMeshRenderComponent = null;
            m_skeletonComponent = null;
            m_particleRenderComponent = null;
            m_projectorRenderComponent = null;
            m_scriptComponent = null;
            m_cameraComponent = null;
            m_SoundSource = null;
            m_EchoFilter = null;
            m_LowPassFilter = null;
            m_ReverbFilter = null;
        }

        private void initialize()
        {
            m_iTagID = UInt32.MaxValue;
        }

        //--------------------------------basic-----------------------------------//
        /// <summary>
        /// 设置与返回Actor的名字
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = new Actor();
        actor.Name = "Test";
        string sTemp = actor.Name;
        @endcode
        */
        public String Name
        {
            get
            {
                if (null == m_sName)
                {
                    m_sName = ICall_Actor_GetName(this);
                }

                return m_sName;
            }

            set
            {
                m_sName = value;
                ICall_Actor_SetName(this, value);
            }
        }

        /// <summary>
        /// 设置或返回用户数据
        /// </summary>
        public object UserData
        {
            get
            {
                return userdata;
            }
            set
            {
                userdata = value;
            }
        }

        /// <summary>
        /// 获取模板的名字
        /// </summary>
        /// <returns>返回模板名</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            string sTemp = actor.GetTemplateName();
        }
        @endcode
        */
        public String GetTemplateName()
        {
            if (null == m_sTemplateName)
            {
                m_sTemplateName = ICall_Actor_GetTemplateName(this);
            }

            return m_sTemplateName;
        }
        /// <summary>
        /// 获取和设置layerID,layerID的范围是0到31
        /// </summary>
        public LayerID LayerID
        {
            get
            {
                return (LayerID)ICall_Actor_GetLayerID(this);
            }
            set
            {
                ICall_Actor_SetLayerID(this, (uint)value);
            }
        }
        /// <summary>
        /// 获取或设置与模板关联的状态
        /// </summary>
        public bool IsLinkTemplate
        {
            get
            {
                return ICall_Actor_IsLinkTemplate(this);
            }

            set
            {
                ICall_Actor_SetLinkTemplate(this, value);
            }
        }
        /// <summary>
        /// 获取与设置GroupID
        /// </summary>
        public UInt32 GroupID
        {
            get
            {
                if (UInt32.MaxValue == m_iTagID)
                {
                    m_iTagID = ICall_Actor_GetTagID(this);
                }

                return m_iTagID;
            }
            set
            {
                m_iTagID = value;
                ICall_Actor_SetTagID(this, value);
            }
        }
        /// <summary>
        /// 获取Actor的Guid
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            Guid guid = actor.Guid;
        }
        @endcode
        */
        public Guid Guid
        {
            get
            {
                return new Guid(Actor.ICall_Actor_GetGuid(this));
            }
        }
        /// <summary>
        /// 得到Actor的FastID
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            UInt32 fastID = actor.FastID;
        }
        @endcode
        */
        public UInt32 FastID
        {
            get
            {
                if (0 == m_iFastID)
                {
                    m_iFastID = ICall_Actor_GetFastId(this);
                }
                return m_iFastID;
            }
        }
        /// <summary>
        /// 判断Actor是否处于激活状态
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && !actor.IsActive)
        {
            actor.Active();
        }
        @endcode
        */
        public bool IsActive
        {
            get
            {
                return ICall_Actor_IsActive(this);
            }
        }

        /// <summary>
        /// ActiveControl会被置为true，并尝试激活此Actor，如果有父actor，并且父actor为非激活状态，则激活失败。如果激活成功，子actor的激活状态由子actor的ActiveControl属性决定。
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && !actor.IsActive)
        {
            actor.Active();
        }
        @endcode
        */
        public void Active()
        {
            ICall_Actor_Active(this, false);
        }
        /// <summary>
        /// ActiveControl会被置为true，并使Actor和其所有的子actor都一起true。
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && !actor.IsActive)
        {
            actor.ActiveWithChildren();
        }
        @endcode
        */
        public void ActiveWithChildren()
        {
            ICall_Actor_Active(this, true);
        }
        /// <summary>
        /// ActiveControl会被置为true，子actor不受影响。
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && !actor.IsActive)
        {
            actor.ActiveWithoutChildren();
        }
        @endcode
        */
        public void ActiveWithoutChildren()
        {
            ICall_Actor_Active(this, false);
        }
        /// <summary>
        /// ActiveControl会被置为false，并使Actor和其所有的子actor都一起失效.
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && actor.IsActive)
        {
            actor.Deactive();
        }
        @endcode
        */
        public void Deactive()
        {
            ICall_Actor_Deactive(this, false);
        }
        /// <summary>
        /// ActiveControl会被置为false，并使Actor和其所有的子actor都一起失效.
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && actor.IsActive)
        {
            actor.DeactiveWithChildren();
        }
        @endcode
        */
        public void DeactiveWithChildren()
        {
            ICall_Actor_Deactive(this, true);
        }
        /// <summary>
        /// ActiveControl会被置为false。子actor不受影响
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        if (null != actor && actor.IsActive)
        {
            actor.DeactiveWithoutChildren();
        }
        @endcode
        */
        public void DeactiveWithoutChildren()
        {
            ICall_Actor_Deactive(this, false);
        }
        /// <summary>
        /// 判断Actor的激活控制。ActiveControl决定了当前actor在父actor激活的时候，会不会跟着被激活。
        /// </summary>
        public bool ActiveControl
        {
            get
            {
                return ICall_Actor_GetActiveControl(this);
            }
        }

        /// <summary>
        /// 获取与设置Actir的父Actor
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.GetActiveActor(0);
        Actor parentActor = ActorManager.GetActiveActor(1);
        if (null != actor && null != parentActor)
        {
            if (null == actor.Parent)
            {
                actor.Parent = parentActor;
            }
        }
        @endcode
        */
        public Actor Parent
        {
            get
            {
                return ICall_Actor_GetParent(this);
            }
            set
            {
                ICall_Actor_SetParent(this, value);
            }
        }

        /// <summary>
        /// 得到当前Actor的所有子Actor的数量
        /// </summary>
        /// <returns>返回子Actor的数量</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            int iCount = actor.GetChildCount();
        }
        @endcode
        */
        public int GetChildCount()
        {
            return ICall_Actor_GetChildCount(this);
        }

        /// <summary>
        /// 用子Actor的索引来获取到当前Actor的第i个Actor
        /// </summary>
        /// <param name="idx">子Actor的索引</param>
        /// <returns>第idx个Actor</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (0 < actor.GetChildCount())
            {
                Actor child = actor.GetChild(0);
            }
        }
        @endcode
        */
        public Actor GetChild(int idx)
        {
            return ICall_Actor_GetChild(this, idx);
        }
        /// <summary>
        /// 使用子Actor的FastID来获取当前Actor的子Actor
        /// </summary>
        /// <param name="fastId">子Actor的FastID</param>
        /// <returns>返回对应fastID的子Actor</returns>
        public Actor FindChild(UInt32 fastId)
        {
            return ICall_Actor_FindChild(this, fastId);
        }
        /// <summary>
        /// 通过子Actor的FastID来获取这个子Actor的索引
        /// </summary>
        /// <param name="fastId">子Actor的FastID</param>
        /// <returns>子Actor所对应的索引</returns>
        public int FindChildIndex(UInt32 fastId)
        {
            return ICall_Actor_FindChildIndex(this, fastId);
        }
        /// <summary>
        /// 添加一个子Actor
        /// </summary>
        /// <param name="child">子Actor</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        Actor child = ActorManager.FindActiveActor("child");
        if (null != actor && null != child)
        {
            actor.AddChild(child);
        }
        @endcode
        */
        public void AddChild(Actor child)
        {
            ICall_Actor_AddChild(this, child);
        }
        /// <summary>
        /// 删除当前Actor的索引为index的子Actor
        /// </summary>
        /// <param name="idx">删除的Actor索引</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (0 < actor.GetChildCount())
            {
                actor.RemoveChild(0);
            }
        }
        @endcode
        */
        public void RemoveChild(int idx)
        {
            ICall_Actor_RemoveChild(this, idx);
        }

        //----------------------------Transform -----------------------------------//
        /// <summary>
        /// 获取与设置本地坐标系的位置
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (0 != actor.LocalPosition.X)
            {
                actor.LocalPosition = new Vector3(0, 0, 0);
            }
        }
        @endcode
        */
        public Vector3 LocalPosition
        {
            get
            {
                Vector3 temp;
                ICall_Actor_GetLocalPos(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetLocalPos(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置本地坐标系的四元数旋转
        /// </summary>
        public Quaternion LocalRotation
        {
            get
            {
                Quaternion temp;
                ICall_Actor_GetLocalRotation(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetLocalRotation(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置本地坐标系的缩放
        /// </summary>
        public Vector3 LocalScale
        {
            get
            {
                Vector3 temp;
                ICall_Actor_GetLocalScale(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetLocalScale(this, ref value);
            }
        }
        /// <summary>
        /// 以z轴旋转Actor
        /// </summary>
        /// <param name="angle">z轴的旋转弧度</param>
        public void Roll(float angle)
        {
            ICall_Actor_Roll(this, angle);
        }
        /// <summary>
        /// 以x轴旋转Actor
        /// </summary>
        /// <param name="angle">x轴的旋转弧度</param>
        public void Pitch(float angle)
        {
            ICall_Actor_Pitch(this, angle);
        }
        /// <summary>
        /// 以y轴旋转Actor
        /// </summary>
        /// <param name="angle">y轴的旋转弧度</param>
        public void Yaw(float angle)
        {
            ICall_Actor_Yaw(this, angle);
        }
        /// <summary>
        /// 转换Actor,以z,x,y欧拉角
        /// </summary>
        /// <param name="roll">z轴的旋转弧度</param>
        /// <param name="pitch">x轴的旋转弧度</param>
        /// <param name="yaw">y轴的旋转弧度</param>
        public void Rotate(float roll, float pitch, float yaw)
        {
            ICall_Actor_Rotate(this, roll, pitch, yaw);
        }
        /// <summary>
        /// 获取与设置本地坐标系的变换矩阵
        /// </summary>
        public Matrix44 LocalTransform
        {
            get
            {
                Matrix44 temp;
                ICall_Actor_GetTransform(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetTransform(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置世界坐标系下的变换矩阵
        /// </summary>
        public Matrix44 WorldTransform
        {
            get
            {
                Matrix44 temp;
                ICall_Actor_GetWorldTransform(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetWorldTransform(this, ref value);
            }
        }

        /// <summary>
        /// 获取与设置世界坐标系下的旋转四元数
        /// </summary>
        public Quaternion WorldRotation
        {
            get
            {
                Quaternion temp;
                ICall_Actor_GetWorldRotation(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetWorldRotation(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置世界坐标
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            if (0 != actor.WorldPosition.X)
            {
                actor.WorldPosition = new Vector3(0, 0, 0);
            }
        }
        @endcode
        */
        public Vector3 WorldPosition
        {
            get
            {
                Vector3 temp;
                ICall_Actor_GetWorldPos(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetWorldPos(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置缩放
        /// </summary>
        public Vector3 WorldScale
        {
            get
            {
                Vector3 temp;
                ICall_Actor_GetWorldScale(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetWorldScale(this, ref value);
            }
        }
        //-------------------------------boundingbox------------------------------//
        /// <summary>
        /// 返回当前Actor的世界坐标系下的包围盒
        /// </summary>
        public BoundingBox WorldBoundingBox
        {
            get
            {
                BoundingBox temp;
                ICall_Actor_GetWorldBoundingBox(this, out temp);
                return temp;
            }
        }
        /// <summary>
        /// 返回世界坐标系下Actor及其子Actor的包围盒
        /// </summary>
        public BoundingBox WorldBoundingBoxWithChildren
        {
            get
            {
                BoundingBox temp;
                ICall_Actor_GetWorldBoundingBoxWithChild(this, out temp);
                return temp;
            }
        }
        /// <summary>
        /// 设置和返回本地坐标系下的包围盒
        /// </summary>
        public BoundingBox LocalBoundingBox
        {
            get
            {
                BoundingBox temp;
                ICall_Actor_GetLocalBoundingBox(this, out temp);
                return temp;
            }
            set
            {
                ICall_Actor_SetLocalBoundingBox(this, ref value);
            }
        }

        /// <summary>
        /// 设置与返回Actor加载的优先级
        /// </summary>
        public int Priority
        {
            get
            {
                return ICall_Actor_GetPriority(this);
            }
            set
            {
                ICall_Actor_SetPriority(this, value);
            }
        }
        /// <summary>
        /// 为Actor添加模板类型的组件
        /// </summary>
        /// <typeparam name="T">添加的组件的模板类型</typeparam>
        /// <returns>返回要添加的组件</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            actor.AddComponent<ScriptComponent>();
        }
        @endcode
        */
        public T AddComponent<T>() where T : Component
        {
            System.Type comType = typeof(T);
            String sTypeName = comType.Name;
            Component com = ICall_Actor_AddComponentByName(this, sTypeName);
            if (null == com)
            {
                return null;
            }

            AssignComponent(com);
            return com as T;
        }
        /// <summary>
        /// 使用组件的字符串名称为Actor添加组件
        /// </summary>
        /// <param name="sName">要添加的组件的字符串名称</param>
        /// <returns>返回想要添加的组件</returns>
        public Component AddComponent(String sName)
        {
            Component com = ICall_Actor_AddComponentByName(this, sName);
            if (null == com)
            {
                return null;
            }

            AssignComponent(com);
            return com;
        }
        /// <summary>
        /// 为Actor移除组件
        /// </summary>
        /// <param name="comp">要移除组件的实例</param>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ScriptComponent scriptComp = actor.GetComponent<ScriptComponent>();
            if (null != scriptComp)
            {
                actor.RemoveComponent(scriptComp);
            }
        }
        @endcode
        */
        public void RemoveComponent(Component comp)
        {
            if (comp != null)
            {
                ICall_Actor_RemoveComponent(this, comp);
                DeAssignComponent(comp);
            }
        }
        /// <summary>
        /// 通过组件的模板来获取当前Actor的组件实例
        /// </summary>
        /// <typeparam name="T">组件的类型模板</typeparam>
        /// <returns>返回组件的实例,如果组件不存在返回NULL</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ScriptComponent scriptComp = actor.GetComponent<ScriptComponent>();
            if (null != scriptComp)
            {
                actor.RemoveComponent(scriptComp);
            }
        }
        @endcode
        */
        public T GetComponent<T>() where T : Component
        {
            System.Type comType = typeof(T);
            String sTypeName = comType.Name;
            Component com = ICall_Actor_GetComponentByName(this, sTypeName);

            return com as T;
        }
        /// <summary>
        /// 通过组件的字符串名称来获取当前Actor的组件实例
        /// </summary>
        /// <param name="sName">组件的字符串名称</param>
        /// <returns>返回组件的实例,如果组件不存在返回NULL</returns>
        public Component GetComponent(String sName)
        {
            Component com = ICall_Actor_GetComponentByName(this, sName);
            return com;
        }
        /// <summary>
        /// 判断是否Actor所加载的资源是否加载完毕
        /// </summary>
        /// <returns>加载成果返回true,加载失败返回false</returns>
        public bool IsAllResourcePrepared()
        {
            return ICall_Actor_IsAllResourcePrepared(this);
        }

        /// <summary>
        /// 获取到动画组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            AnimationComponent animationComp = actor.Animation;
        }
        @endcode
        */
        public AnimationComponent Animation
        {
            get
            {
                if (null == m_animationComponent)
                {
                    m_animationComponent = GetComponent<AnimationComponent>();
                }

                return m_animationComponent;
            }
        }
        /// <summary>
        /// 获取到摄像机组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            CameraComponent cameraComp= actor.Camera;
        }
        @endcode
        */
        public CameraComponent Camera
        {
            get
            {
                if (null == m_cameraComponent)
                {
                    m_cameraComponent = GetComponent<CameraComponent>();
                }
                return m_cameraComponent;
            }
        }

        /// <summary>
        /// 获取到投影体组件
        /// </summary>
        public ProjectorRenderComponent ProjectorRender
        {
            get
            {
                if (null == m_projectorRenderComponent)
                {
                    m_projectorRenderComponent = GetComponent<ProjectorRenderComponent>();
                    m_projectorRenderComponent.EnableProjector = true;
                    m_projectorRenderComponent.SetMaterialID(0, "sys:projector.material", false);
                }
                return m_projectorRenderComponent;
            }
        }

        /// <summary>
        /// 获取到Mesh组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            MeshRenderComponent meshRenderComp= actor.MeshRender;
        }
        @endcode
        */
        public MeshRenderComponent MeshRender
        {
            get
            {
                if (null == m_meshRenderComponent)
                {
                    m_meshRenderComponent = GetComponent<MeshRenderComponent>();
                }

                return m_meshRenderComponent;
            }
        }

        /// <summary>
        /// 获取到精灵组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            SpriteRenderComponent spriteRenderComp = actor.SpriteRender;
        }
        @endcode
        */
        public SpriteRenderComponent SpriteRender
        {
            get
            {
                if (null == m_spriteRenderComponent)
                {
                    m_spriteRenderComponent = GetComponent<SpriteRenderComponent>();
                }

                return m_spriteRenderComponent;
            }
        }

        /// <summary>
        /// 获取到粒子组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ParticleRenderComponent particleRenderComp = actor.ParticleRender;
        }
        @endcode
        */
        public ParticleRenderComponent ParticleRender
        {
            get
            {
                if (null == m_particleRenderComponent)
                {
                    m_particleRenderComponent = GetComponent<ParticleRenderComponent>();
                }

                return m_particleRenderComponent;
            }
        }
        /// <summary>
        /// 获取到脚本组件
        /// </summary>
        /**@brief<b>示例</b>
        *@code{.cpp}
        Actor actor = ActorManager.FindActiveActor("test");
        if (null != actor)
        {
            ScriptComponent scriptComp = actor.Script;
        }
        @endcode
        */
        public ScriptComponent Script
        {
            get
            {
                if (null == m_scriptComponent)
                {
                    m_scriptComponent = GetComponent<ScriptComponent>();
                }

                return m_scriptComponent;
            }
        }
        /// <summary>
        /// 引用计数
        /// </summary>
        /// <returns>次数</returns>
        public int GetRefCount()
        {
            return ICall_Actor_GetRefCount(this);
        }

        // - private function
        private void AssignComponent(Component component)
        {
            System.Type comType = component.GetType();
            if (AnimationComponent.thisType == comType)
            {
                m_animationComponent = component as AnimationComponent;
            }
            else if (MeshRenderComponent.thisType == comType)
            {
                m_meshRenderComponent = component as MeshRenderComponent;
            }
            else if (SkinnedMeshRenderComponent.thisType == comType)
            {
                m_skinnedMeshRenderComponent = component as SkinnedMeshRenderComponent;
            }
            else if (ProjectorRenderComponent.thisType == comType)
            {
                m_projectorRenderComponent = component as ProjectorRenderComponent;
                m_projectorRenderComponent.EnableProjector = true;
                m_projectorRenderComponent.SetMaterialID(0, "sys:projector.material", false);
            }
            else if (SkeletonComponent.thisType == comType)
            {
                m_skeletonComponent = component as SkeletonComponent;
            }
            else if (ParticleRenderComponent.thisType == comType)
            {
                m_particleRenderComponent = component as ParticleRenderComponent;
            }
            else if (SpriteRenderComponent.thisType == comType)
            {
                m_spriteRenderComponent = component as SpriteRenderComponent;
            }
            else if (ScriptComponent.thisType == comType)
            {
                m_scriptComponent = component as ScriptComponent;
            }
            else if (CameraComponent.thisType == comType)
            {
                m_cameraComponent = component as CameraComponent;
            }
            else if (SoundSource.thisType == comType)
            {
                m_SoundSource = component as SoundSource;
            }
#if FMOD_IMPLEMENT
            else if (SoundReverbZone.thisType == comType)
            {
                m_SoundReverb = component as SoundReverbZone;
            }
            else if (SoundHighPassFilterComponent.thisType == comType)
            {
                m_HighPassFilter = component as SoundHighPassFilterComponent;
            }
            else if (SoundLowPassFilterComponent.thisType == comType)
            {
                m_LowPassFilter = component as SoundLowPassFilterComponent;
            }
            else if (SoundChorusFilterComponent.thisType == comType)
            {
                m_ChorusFilter = component as SoundChorusFilterComponent;
            }
            else if (SoundDistortionFilterComponent.thisType == comType)
            {
                m_DistortionFilter = component as SoundDistortionFilterComponent;
            }
            else if (SoundEchoFilterComponent.thisType == comType)
            {
                m_EchoFilter = component as SoundEchoFilterComponent;
            }
            else if (SoundReverbFilterComponent.thisType == comType)
            {
                m_ReverbFilter = component as SoundReverbFilterComponent;
            }
#endif
        }
        // - private function
        private void DeAssignComponent(Component component)
        {
            System.Type comType = component.GetType();
            if (AnimationComponent.thisType == comType)
            {
                m_animationComponent = null;
            }
            else if (MeshRenderComponent.thisType == comType)
            {
                m_meshRenderComponent = null;
            }
            else if (SkinnedMeshRenderComponent.thisType == comType)
            {
                m_skinnedMeshRenderComponent = null;
            }
            else if (ProjectorRenderComponent.thisType == comType)
            {
                m_projectorRenderComponent = null;
            }
            else if (SkeletonComponent.thisType == comType)
            {
                m_skeletonComponent = null;
            }
            else if (ParticleRenderComponent.thisType == comType)
            {
                m_particleRenderComponent = null;
            }
            else if (ScriptComponent.thisType == comType)
            {
                m_scriptComponent = null;
            }
            else if (CameraComponent.thisType == comType)
            {
                m_cameraComponent = null;
            }
            else if (SoundSource.thisType == comType)
            {
                m_SoundSource = null;
            }
            else if (SpriteRenderComponent.thisType == comType)
            {
                m_spriteRenderComponent = null;
            }
#if FMOD_IMPLEMENT
            else if (SoundReverbZone.thisType == comType)
            {
                m_SoundReverb = null;
            }
            else if (SoundHighPassFilterComponent.thisType == comType)
            {
                m_HighPassFilter = null;
            }
            else if (SoundLowPassFilterComponent.thisType == comType)
            {
                m_LowPassFilter = null;
            }
            else if (SoundChorusFilterComponent.thisType == comType)
            {
                m_ChorusFilter = null;
            }
            else if (SoundDistortionFilterComponent.thisType == comType)
            {
                m_DistortionFilter = null;
            }
            else if (SoundEchoFilterComponent.thisType == comType)
            {
                m_EchoFilter = null;
            }
            else if (SoundReverbFilterComponent.thisType == comType)
            {
                m_ReverbFilter = null;
            }
#endif
        }
    }
}
