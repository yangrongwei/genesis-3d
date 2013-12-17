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
    /// 游戏程序类，整个游戏程序相关的基本操作
    /// 如打开、关闭场景，退出等
    /// </summary>
    public static partial class Application
    {
        /// <summary>
        /// 打开场景
        /// </summary>
        /// <param name="sceneResID">场景资源名字</param>
        /// <returns>打开成功返回true，否则返回false</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        bool bRet = ScriptRuntime.Application.OpenScene("scene");
        @endcode
        */
        public static bool OpenScene(String sceneResID)
        {
            return ICall_Application_OpenScene(sceneResID);
        }
        /// <summary>
        /// 关闭场景
        /// </summary>
        /// <param name="sceneResID">场景资源名字</param>
        /// <returns>关闭成功返回true，否则返回false</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        bool bRet = ScriptRuntime.Application.CloseScene("scene");
        @endcode
        */
        public static bool CloseScene(String sceneResID)
        {
            return ICall_Application_CloseScene(sceneResID);
        }
        /// <summary>
        /// 退出应用程序
        /// </summary>
        public static void Quit()
        {
            ICall_Application_Quit();
        }
        /// <summary>
        /// 获取资源路径
        /// </summary>
        /// <returns>得到的资源路径作为字符串返回</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        string sAssetPath = ScriptRuntime.Application.GetAssetPath();
        @endcode
        */
        public static string GetAssetPath()
        {
            return ICall_Application_GetAssetPath();
        }
        /// <summary>
        /// 获取移动应用程序的路径
        /// </summary>
        /// <returns>得到的路径作为字符串返回</returns>
        public static string GetAppDicOnMobile()
        {
            return ICall_Application_GetAppDicOnMobile();
        }
        /// <summary>
        /// 获取移动显示设备高度
        /// </summary>
        /// <returns>得到的高度作为字符串返回</returns>
        public static float GetDPIHeight()
        {
            return ICall_Application_GetDPIHeight();
        }
        /// <summary>
        /// 获取移动显示设备宽度
        /// </summary>
        /// <returns>得到的宽度作为字符串返回</returns>
        public static float GetDPIWidth()
        {
            return ICall_Application_GetDPIWidth();
        }  
        /// <summary>
        /// 当前场景
        /// </summary>
        public static Scene CurrentScene
        {
            get
            {
                return ICall_Application_GetCurrentScene();
            }
        }
    }
}
