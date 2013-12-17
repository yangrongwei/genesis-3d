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
    //copy from Engine\rendersystem\base\PixelFormat.h
    internal enum _PixelFormat : int
    {
        // begin common
        X8R8G8B8 = 0,
        R8G8B8,
        B8G8R8,
        B8G8R8A8,
        R8G8B8A8,
        A8B8G8R8,
        A8R8G8B8,
        R5G6B5,
        A1R5G5B5,
        A4R4G4B4,
        DXT1,
        DXT2,
        DXT3,
        DXT4,
        DXT5,
        R16F,                       // 16 bit float, red only
        G16R16F,                    // 32 bit float, 16 bit red, 16 bit green
        A16B16G16R16F,              // 64 bit float, 16 bit rgba each
        R32F,                       // 32 bit float, red only
        G32R32F,                    // 64 bit float, 32 bit red, 32 bit green
        A32B32G32R32F,              // 128 bit float, 32 bit rgba each
        A8,
        L8,
        L8A8,						//[2012/4/12 zhongdaohuan] mygui 用到的格式
        L16,
        G16R16,
        D24X8,
        D24S8,
        // end common   CommonCount

        // begin iPhone /  PowerVR
        PVRTC_RGB2,
        PVRTC_RGBA2,
        PVRTC_RGB4,
        PVRTC_RGBA4,
        // end iphone / PowerVR end   iOSCount

        //ETC
        ETC1_RGB8,

        NumPixelFormats,
        InvalidPixelFormat,
        DescPixelFormatsCount,	//	不调整NumPixelFormats和InvalidPixelFormat的顺序，以免引起BUG。用于像素格式描述的数组

        // 记录分块的标志位。 更改枚举之后，记得修改
        CommonCount = D24S8 + 1,
        iOSCount = PVRTC_RGBA4 + 1,
    };

    public enum PixelFormat : int
    {
        X8R8G8B8 = _PixelFormat.X8R8G8B8,
        R16F = _PixelFormat.R16F,
        G16R16F = _PixelFormat.G16R16F,
        A16B16G16R16F = _PixelFormat.A16B16G16R16F,
        R32F = _PixelFormat.R32F,
        G32R32F = _PixelFormat.G32R32F,
        A32B32G32R32F = _PixelFormat.A32B32G32R32F,

    }

    public enum ClearFlag
    {
        ClearColor = (1 << 0),
        ClearDepth = (1 << 1),
        ClearStencil = (1 << 2),
        ClearAll = ClearColor | ClearDepth | ClearStencil,
    };

    /// <summary>
    /// 渲染到纹理
    /// </summary>
    public class RenderToTexture : Texture
    {
        private RenderToTexture(DummyClass__ dummyObj)
        {

        }

        ~RenderToTexture()
        {
            ICall_RenderToTexture_Release(this);
        }

        /// <summary>
        /// 默认构造函数
        /// </summary>
        public RenderToTexture()
        {
            ICall_RenderToTexture_Bind(this);
        }

        /// <summary>
        /// 创建一个用户自定义的渲染到纹理
        /// </summary>
        /// <param name="width">渲染到纹理的宽度</param>
        /// <param name="height">渲染到纹理的高度</param>
        /// <param name="format">渲染到纹理的格式</param>
        /// <param name="flag">渲染到纹理的渲染标志</param>
        /// <param name="color">渲染到纹理的颜色</param>
        /// <param name="useDepth">渲染到纹理是否使用深度</param>
        /// <param name="screenRatio">渲染到纹理的纵横比</param>
        public void Setup(int width, int height, PixelFormat format, ClearFlag flag, ref Vector4 color, bool useDepth, float screenRatio)
        {
            ICall_RenderToTexture_Setup(this, width, height,(int)format,(uint)flag, ref color,useDepth,screenRatio,0,0,0,0,0);
        }

        /// <summary>
        /// 创建一个用户自定义的渲染到纹理
        /// </summary>
        /// <param name="width">渲染到纹理的宽度</param>
        /// <param name="height">渲染到纹理的高度</param>
        /// <param name="format">渲染到纹理的格式</param>
        /// <param name="flag">渲染到纹理的渲染标志</param>
        /// <param name="color">渲染到纹理的颜色</param>
        /// <param name="useDepth">渲染到纹理是否使用深度</param>
        public void Setup(int width, int height, PixelFormat format, ClearFlag flag, ref Vector4 color, bool useDepth)
        {
            ICall_RenderToTexture_Setup(this, width, height, (int)format, (uint)flag, ref color, useDepth, 0, 0, 0, 0, 0, 0);
        }

        internal override IntPtr GetTextureHandlePtr()
        {
            return ICall_RenderToTexture_GetTextureHandlePtr(this);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderToTexture_Bind(RenderToTexture self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderToTexture_Release(RenderToTexture self);

        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderToTexture_Setup(RenderToTexture self,int width,int height,int pixelFormat
            , uint flag, ref Vector4 color, bool useDepth
			,float screenRatio,int antiAliasQuality,int texLeft,int texRight,int texTop,int texBottom);
         
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_RenderToTexture_GetTextureHandlePtr(RenderToTexture self);
    }
}
