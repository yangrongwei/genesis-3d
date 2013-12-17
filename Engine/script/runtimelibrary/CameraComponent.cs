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
    /// 指定渲染与视口相关的属性
    /// </summary>
    public partial class CameraComponent : Component
    {
        public static readonly System.Type thisType = typeof(CameraComponent);

        private CameraComponent(DummyClass__ dummy)
        {

        }
        /// <summary>
        /// 摄像机组件构造函数
        /// 默认创建一个透视投影的摄像机
        /// </summary>
        public CameraComponent()
        {
            ICall_CameraComponent_Bind(this);
            SetupPerspectiveFovRH(MathHelper.PiOver4, 1, 1000);
        }
        /// <summary>
        /// 创建正交投影
        /// </summary>
        /// <param name="height">正交投影的高度</param>
        /// <param name="zNear">指定正交投影的近裁剪面</param>
        /// <param name="zFar">指定正交投影的远裁剪面</param>
        public void SetupOrthogonal(float height, float zNear, float zFar)
        {
            ICall_CameraComponent_SetProj(this, height, zNear, zFar, Orth);
        }
        /// <summary>
        /// 创建透视投影
        /// </summary>
        /// <param name="fov">摄像机的纵向视角(角度)</param>
        /// <param name="zNear">指定透视投影的近裁剪面</param>
        /// <param name="zFar">指定透视投影的远裁剪面</param>
        public void SetupPerspectiveFovRH(float fov, float zNear, float zFar)
        {
            ICall_CameraComponent_SetProj(this, fov, zNear, zFar, Persp);
        }
        /// <summary>
        /// 获取摄像机类型
        /// </summary>
        public ViewType ViewType
        {
            get
            {
                return converViewType(ICall_CameraComponent_GetViewType(this));
            }
        }
        /// <summary>
        /// 判断摄像机是否为透视投影
        /// </summary>
        public bool IsPerspective
        {
            get
            {
                return Persp == ICall_CameraComponent_GetViewType(this);
            }
        }
        /// <summary>
        /// 获取摄像机的纵向视角(角度)
        /// </summary>
        public float Fov
        {
            get
            {
                return ICall_CameraComponent_GetFov(this);
            }
        }
        /// <summary>
        /// 获取摄像机的横纵比
        /// </summary>
        public float Aspect
        {
            get
            {
                return ICall_CameraComponent_GetAspect(this);
            }
        }
        /// <summary>
        /// 获取与设置近裁剪面的距离
        /// </summary>
        public float NearClipPlane
        {
            get
            {
                return ICall_CameraComponent_GetZNear(this);
            }
            set
            {
                if ( value < 0.01f )
                {
                    return;
                }

                ICall_CameraComponent_SetZNear(this, value);

                if ( value >= FarClipPlane )
                {
                    FarClipPlane = value + 0.01f;
                }

                if ( ShadowDistance < value )
                {
                    ShadowDistance = value;
                }

            }
        }
        /// <summary>
        /// 获取与设置远裁剪面的距离
        /// </summary>
        public float FarClipPlane
        {
            get
            {
                return ICall_CameraComponent_GetZFar(this);
            }
            set
            {
                if ( value < 0.02f )
                {
                    return;
                }

                ICall_CameraComponent_SetZFar(this, value);

                if ( NearClipPlane >= value )
                {
                    NearClipPlane = value - 0.01f;
                }

                if ( ShadowDistance > value )
                {
                    ShadowDistance = value;
                }
            }
        }
        /// <summary>
        /// 获取远裁剪面的宽度
        /// </summary>
        public float FarWidth
        {
            get
            {
                return ICall_CameraComponent_GetFarWidth(this);
            }
        }
        /// <summary>
        /// 获取远裁剪面的高度
        /// </summary>
        public float FarHeight
        {
            get
            {
                return ICall_CameraComponent_GetFarHeight(this);
            }
        }
        /// <summary>
        /// 获取近裁剪面的宽度
        /// </summary>
        public float NearWidth
        {
            get
            {
                return ICall_CameraComponent_GetNearWidth(this);
            }
        }
        /// <summary>
        /// 获取近裁剪面的高度
        /// </summary>
        public float NearHeight
        {
            get
            {
                return ICall_CameraComponent_GetNearHeight(this);
            }
        }


        /// <summary>
        /// 获取与设置阴影的距离
        /// </summary>
        public float ShadowDistance
        {
            get
            {
                return ICall_CameraComponent_GetShadowDistance(this);
            }
            set
            {
                if ( value <= FarClipPlane && value >= NearClipPlane )
                {
                    ICall_CameraComponent_SetShadowDistance(this, value);                    
                }
            }
        }


        /// <summary>
        /// 获取摄像机的相机变换矩阵
        /// </summary>
        public Matrix44 View
        {
            get
            {
                Matrix44 temp;
                ICall_CameraComponent_GetView(this, out temp);
                return temp;
            }
        }
        /// <summary>
        /// 获取摄像机的透视投影矩阵
        /// </summary>
        public Matrix44 Proj
        {
            get
            {
                Matrix44 temp;
                ICall_CameraComponent_GetProj(this, out temp);
                return temp;
            }
        }

        /// <summary>
        /// 获取摄像机的变换矩阵
        /// 透视投影矩阵乘以相机变换矩阵(OpenGL)
        /// </summary>
        public Matrix44 ViewProj
        {
            get
            {
                Matrix44 temp;
                ICall_CameraComponent_GetViewProj(this, out temp);
                return temp;
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
                ICall_CameraComponent_SetRenderToTexture(this, rtt);
            }
        }

        /// <summary>
        /// 设置光照纹理
        /// </summary>
        /// <param name="rtt">指定光照纹理的目标</param>
        public void SetLightLitTexture(RenderToTexture rtt)
        {
            if (null != rtt)
            {
                ICall_CameraComponent_SetLightLitTexture(this, rtt);
            }
        }

        /// <summary>
        /// 为摄像机创建透视投影
        /// </summary>
        /// <param name="fov">纵向视角的角度</param>
        /// <param name="aspect">横纵比</param>
        /// <param name="zNear">近裁剪面距离</param>
        /// <param name="zFar">远裁剪面距离</param>
        public void SetupPerspectiveFovRH(float fov, float aspect, float zNear, float zFar)
        {
            ICall_CameraComponent_SetupPerspectiveFovRH(this, fov, aspect, zNear, zFar);
        }

        /// <summary>
        /// 创建一个用于水面反射与折射的投影矩阵
        /// </summary>
        /// <param name="fov">纵向视角的角度</param>
        /// <param name="aspect">横纵比</param>
        /// <param name="zNear">近裁剪面距离</param>
        /// <param name="zFar">远裁剪面距离</param>
        /// <param name="clipPlane">反射与折射的平面</param>
        /// <param name="reflect">设置是否为反射</param>
        public void SetupPerspectiveFovRHEx(float fov, float aspect, float zNear, float zFar, ref Vector4 clipPlane, bool reflect)
        {
            ICall_CameraComponent_SetupPerspectiveFovRHEx(this, fov, aspect, zNear, zFar, ref clipPlane, reflect);
        }

        /// <summary>
        /// 获取与设置是否渲染深度
        /// </summary>
        public bool RenderDepth
        {
            set
            {
                ICall_CameraComponent_SetRenderDepth(this, value);
            }
            get
            {
                return ICall_CameraComponent_GetRenderDepth(this);
            }

        }

        /// <summary>
        /// 获取与设置是否正常渲染
        /// </summary>
        public bool RenderNormal
        {
            set
            {
                ICall_CameraComponent_SetRenderNormal(this, value);
            }
            get
            {
                return ICall_CameraComponent_GetRenderNormal(this);
            }
        }

        /// <summary>
        /// 获取摄像机变换矩阵
        /// </summary>
        public Matrix44 ViewTransform
        {
            get
            {
                Matrix44 temp;
                ICall_CameraComponent_GetViewTransForm(this, out temp);
                return temp;
            }
        }
  
        /// <summary>
        /// 设置与获取用户自定义渲染
        /// </summary>
        public bool RenderCustomised
        {
            set
            {
                ICall_CameraComponent_SetCustomise(this, value);
            }
            get
            {
                return ICall_CameraComponent_IsCustomise(this);
            }
        }

        /// <summary>
        /// 获取与设置摄像机的剔除标记位
        /// </summary>
        public LayerMark CullMask
        {
            set
            {
                ICall_CameraComponent_SetCullMask(this, value.MarkAsUINT);
            }
            get
            {
                return ICall_CameraComponent_GetCullMask(this);
            }
        }

        /// <summary>
        /// 获取与设置摄像机的剔除标记位
        /// </summary>
        public uint CullMaskUINT
        {
            set
            {
                ICall_CameraComponent_SetCullMask(this, value);
            }
            get
            {
                return ICall_CameraComponent_GetCullMask(this);
            }
        }

        internal static ViewType converViewType(int viewType)
        {
            return (ViewType)viewType;
        }
        
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
                ICall_CameraComponent_SetUseBeforeDrawEvent(this, value);
            }
            get
            {
                return ICall_CameraComponent_GetUseBeforeDrawEvent(this);
            }
        }

        /// <summary>
        /// 设置是否渲染阴影
        /// </summary>
        public bool RenderShadowMap
        {
            set
            {
                ICall_CameraComponent_SetRenderShadowMap(this, value);
            }
            get
            {
                return ICall_CameraComponent_GetRenderShadowMap(this);
            }
        }
    }
}
