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
    /// 摄像机组件
    /// </summary>
    public  class Camera : Base
    {
        public static readonly System.Type thisType = typeof(Camera);

        private Camera(DummyClass__ dummy)
        {

        }
        /// <summary>
        /// 创建一个透视摄影摄像机
        /// </summary>
        public Camera()
        {
            ICall_Camera_Bind(this);
        }
        /// <summary>
        /// 获取或设置视野范围
        /// </summary>
        public float Fov
        {
            get
            {
                return ICall_Camera_GetFov(this);
            }
        }
        /// <summary>
        /// 获取方向参数
        /// </summary>
        public float Aspect
        {
            get
            {
                return ICall_Camera_GetAspect(this);
            }
        }
        /// <summary>
        /// 设置渲染到纹理
        /// </summary>
        /// <param name="rtt">指定渲染到纹理的目标</param>
        public void SetRenderTarget(RenderToTexture rtt)
        {
            if (null != rtt)
            {
                ICall_Camera_SetRenderToTexture(this, rtt);
            }
        }
        /// <summary>
        /// 设置光照渲染纹理
        /// </summary>
        /// <param name="rtt">指定光照纹理的目标</param>
        public void SetLightLitTexture(RenderToTexture rtt)
        {
            if (null != rtt)
            {
                ICall_Camera_SetLightLitTexture(this, rtt);
            }
        }
        /// <summary>
        /// 为摄像机创建透视投影
        /// </summary>
        /// <param name="fov">纵向视角</param>
        /// <param name="aspect">横纵比</param>
        /// <param name="zNear">近裁剪面</param>
        /// <param name="zFar">远裁剪面</param>
        public void SetupPerspectiveFovRH(float fov, float aspect, float zNear, float zFar)
        {
            ICall_Camera_SetupPerspectiveFovRH(this, fov, aspect, zNear, zFar);
        }
        /// <summary>
        /// 创建一个用于水面反射与折射的投影矩阵
        /// </summary>
        /// <param name="fov">纵向视角</param>
        /// <param name="aspect">横纵比</param>
        /// <param name="zNear">近裁剪面</param>
        /// <param name="zFar">远裁剪面</param>
        /// <param name="clipPlane">反射与折射的平面</param>
        /// <param name="reflect">是否为反射</param>
        public void SetupPerspectiveFovRHEx(float fov, float aspect, float zNear, float zFar, ref Vector4 clipPlane, bool reflect)
        {
            ICall_Camera_SetupPerspectiveFovRHEx(this, fov, aspect, zNear, zFar, ref clipPlane, reflect);
        }
        /// <summary>
        /// 获取与设置是否渲染深度
        /// </summary>
        public bool RenderDepth
        {
            set
            {
                ICall_Camera_SetRenderDepth(this, value);
            }
            get
            {
                return ICall_Camera_GetRenderDepth(this);
            }

        }
        /// <summary>
        /// 获取与设置是否正常渲染
        /// </summary>
        public bool RenderNormal
        {
            set
            {
                ICall_Camera_SetRenderNormal(this, value);
            }
            get
            {
                return ICall_Camera_GetRenderNormal(this);
            }
        }
        /// <summary>
        /// 获取与设置摄像机的变换矩阵
        /// </summary>
        public Matrix44 ViewTransform
        {
            set
            {
              
                ICall_Camera_SetViewTransForm(this, ref value);
              
            }
            get
            {
                Matrix44 temp;
                ICall_Camera_GetViewTransForm(this, out temp);
                return temp;
            }
        }
        /// <summary>
        /// 获取与设置用户自定义渲染
        /// </summary>
        public bool RenderCustomised
        {
            set
            {
                ICall_Camera_SetCustomise(this, value);
            }
            get
            {
                return ICall_Camera_IsCustomise(this);
            }
        }
        /// <summary>
        /// 获取与设置摄像机的剔除标记位
        /// </summary>
        public LayerMark CullMask
        {
            set
            {
                ICall_Camera_SetCullMask(this, value.MarkAsUINT);
            }
            get
            {
                return ICall_Camera_GetCullMask(this);
            }
        }

        /// <summary>
        /// 获取与设置摄像机的剔除标记位
        /// </summary>
        public uint CullMaskUINT
        {
            set
            {
                ICall_Camera_SetCullMask(this, value);
            }
            get
            {
                return ICall_Camera_GetCullMask(this);
            }
        }

        /// <summary>
        /// 从整型转为摄像机类型枚举
        /// </summary>
        /// <param name="viewType">要转换的整型</param>
        /// <returns>返回整型对应的摄像机枚举类型</returns>
        internal static ViewType converViewType(int viewType)
        {
            return (ViewType)viewType;
        }
        /// <summary>
        /// 从摄像机类型枚举转为整型
        /// </summary>
        /// <param name="viewType">摄像机枚举类型</param>
        /// <returns>返回摄像机枚举类型对应的整型</returns>
        internal static int converViewType(ViewType viewType)
        {
            return (int)viewType;
        }
        private static int Orth = converViewType(ViewType.Orthogonal);
        private static int Persp = converViewType(ViewType.Perspective);
        /// <summary>
        /// 设置是否使用前置渲染事件
        /// </summary>
        public bool UseBeforeDrawEvent
        {
            set
            {
                ICall_Camera_SetUseBeforeDrawEvent(this, value);
            }
        }
        /// <summary>
        /// 设置是否渲染阴影
        /// </summary>
        public bool RenderShadowMap
        {
            set
            {
                ICall_Camera_SetRenderShadowMap(this, value);
            }
        }


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_Bind(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_Release(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetupPerspectiveFovRH(Camera self, float fov, float aspect, float zNear, float zFar);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetupPerspectiveFovRHEx(Camera self, float fov, float aspect, float zNear, float zFar, ref Vector4 clipPlane_, bool reflection);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetRenderToTexture(Camera self, RenderToTexture renderToTexture);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetRenderDepth(Camera self, bool bRenderDepth);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Camera_GetRenderDepth(Camera self);

        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetRenderNormal(Camera pMonoObj, bool bRenderNormal);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Camera_GetRenderNormal(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_GetViewTransForm(Camera self, out Matrix44 view);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_GetProjTransForm(Camera self, out Matrix44 proj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetViewTransForm(Camera self, ref Matrix44 proj);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_Camera_GetAspect(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_Camera_GetFov(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_Camera_GetNear(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_Camera_GetFar(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetCullMask(Camera self,UInt32 mask);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_Camera_GetCullMask(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetCustomise(Camera self, bool customise);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Camera_IsCustomise(Camera self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetUseBeforeDrawEvent(Camera self, bool enable);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetRenderShadowMap(Camera self, bool enable);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Camera_SetLightLitTexture(Camera self, RenderToTexture renderToTexture);
         

    }
}
