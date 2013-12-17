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
    /// 简单天空渲染组件类
    /// </summary>
    public class SimpleSkyComponent : MeshRenderComponent
    {
        private SimpleSkyComponent(DummyClass__ dummy)
        {

        }

        protected SimpleSkyComponent()
        {

        }
    }
    /// <summary>
    /// 网格渲染组件类
    /// </summary>
    public partial class MeshRenderComponent : RenderComponent

    {
        public static readonly System.Type thisType = typeof(MeshRenderComponent);

        private MeshRenderComponent(DummyClass__ dummy)
        {

        }

        protected MeshRenderComponent()
        {

        }

        /// <summary>
        /// 为网格组件设置模型资源
        /// </summary>
        /// <param name="sMeshId">模型资源路径</param>
        /// <param name="priority">加载的方式,0为同步加载,1为异步加载</param>
        public void SetMeshID(String sMeshId, int priority)
        {
            ICall_MeshRenderComponent_SetMeshID(this, sMeshId, priority);
        }
        /// <summary>
        /// 获取网格组件ID
        /// </summary>
        /// <returns>ID</returns>
        public string GetMeshID()
        {
            return ICall_MeshRenderComponent_GetMeshID(this);
        }

        /// <summary>
        /// 设置绘制深度
        /// </summary>
        /// <param name="bDraw"></param>
        public void SetDrawDepth(bool bDraw)
        {
            ICall_MeshRenderComponent_SetDrawDepth(this, bDraw);
        }

        /// <summary>
        /// 获得网格组件中模型的三角面数
        /// </summary>
        /// <returns>返回三角面总数</returns>
        public int GetTriangleCount()
        {
            return ICall_MeshRenderComponent_GetTriangleCount(this);
        }

        /// <summary>
        /// 获得网格组件中模型的顶点数
        /// </summary>
        /// <returns>返回顶点总数</returns>
        public int GetVertexCount()
        {
             return ICall_MeshRenderComponent_GetVertexCount(this);
        }
     }
}
