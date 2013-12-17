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
    /// 图形系统类，包括与图形相关的操作，
    /// 如相机、视口、材质等
    /// </summary>
    public static class GraphicSystem
    {

 
        /// <summary>
        /// 获取场景中的主相机
        /// </summary>
        /// <returns>相机组件</returns>
        public static CameraComponent GetSceneCamera()
        {
            return ICall_GraphicSystem_GetSceneCamera();
        }
        /// <summary>
        /// 以相机作为参数，渲染场景
        /// </summary>
        /// <param name="cam">摄像机</param>
        public static void RenderCamera(Camera cam)
        {
            ICall_GraphicSystem_RenderCamera(cam);
        }
        /// <summary>
        /// 利用RenderToTexture和缓冲区清理标志位，设置渲染目标
        /// </summary>
        /// <param name="target">RenderToTexture，输入参数</param>
        /// <param name="index">渲染目标的缓冲区清理标志位</param>
        public static void SetRenderTarget(RenderToTexture target, int index)
        {
            ICall_GraphicSystem_SetRenderTarget(target, index);
        }

        //public static RenderResourceHandle CreateTexture(String path)
        //{
        //    return ICall_GraphicSystem_CreateTexture(path);
        //}
        /// <summary>
        /// 获得视口的宽度
        /// </summary>
        /// <returns>视口宽度</returns>
        public static int GetWidth()
        {
            return ICall_GraphicSystem_GetWidth();
        }
        /// <summary>
        /// 获得视口的高度
        /// </summary>
        /// <returns>视口高度</returns>
        public static int GetHeight()
        {
            return ICall_GraphicSystem_GetHeight();
        }
        /// <summary>
        /// 根据相机类型获得相机的RenderToTexture
        /// </summary>
        /// <param name="type">相机类型参数，值可选:eCO_InvalidCamera,eCO_Shadow,eCO_Main,eCO_PuppetMain</param>
        /// <returns>返回RenderToTexture</returns>
        public static RenderToTexture GetCameraRenderToTextureByCameraType(int type)
        {
            return ICall_GraphicSystem_GetCameraRenderToTextureByCameraType(type);
        }
        /// <summary>
        /// 根据资源ID创建材质实例
        /// </summary>
        /// <param name="resID">资源ID</param>
        /// <returns>返回材质实例</returns>
        public static MaterialInstance CreateMaterial(String resID)
        {
            return ICall_GraphicSystem_CreateMaterial(resID);
        }
        /// <summary>
        /// 利用材质实例的特定通道，将指定纹理渲染至目标RenderToTexture
        /// </summary>
        /// <param name="source">指定的纹理</param>
        /// <param name="destination">目标RenderToTexture</param>
        /// <param name="material">材质实例</param>
        /// <param name="passIndex">材质实例的通道</param>
        public static void BlitImage(Texture source, RenderToTexture destination, MaterialInstance material, int passIndex)
        {
            if (null == source)
            {

                ICall_GraphicSystem_BlitImage(IntPtr.Zero, destination, material, passIndex);
            }
            else
            {
                ICall_GraphicSystem_BlitImage(source.GetTextureHandlePtr(), destination, material, passIndex);
            }
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static CameraComponent ICall_GraphicSystem_GetSceneCamera();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_GraphicSystem_RenderCamera(Camera render);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_GraphicSystem_SetRenderTarget(RenderToTexture target, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_GraphicSystem_GetWidth();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_GraphicSystem_GetHeight();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static RenderToTexture ICall_GraphicSystem_GetCameraRenderToTextureByCameraType(int type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static MaterialInstance ICall_GraphicSystem_CreateMaterial(String resID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_GraphicSystem_BlitImage(IntPtr textureHandlePtr, RenderToTexture destination, MaterialInstance material, int passIndex);
    }
}
