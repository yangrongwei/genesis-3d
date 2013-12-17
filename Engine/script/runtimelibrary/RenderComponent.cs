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
    /// 渲染相关的组件
    /// </summary>
    public partial class RenderComponent : Component
    {
        private RenderComponent(DummyClass__ dummyObj)
        {

        }

        protected RenderComponent()
        {

        }

        /// <summary>
        /// 获得渲染相关组件的第i个材质的资源名
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <returns>返回的资源名称</returns>
        public string GetMaterialID(int index)
        {
            return ICall_RenderComponent_GetMaterialID(this, index);
        }

        /// <summary>
        /// 获得渲染相关组件的第i个材质的材质实例
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <returns>返回的材质实例</returns>
        public MaterialInstance GetMaterialInstance(int index)
        {
            return ICall_RenderComponent_GetMaterialInstance(this, index);
        }

        /// <summary>
        /// 设置材质资源到指定的材质索引
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="pMonoStr">要设置的资源路径</param>
        /// <param name="bCopy">是否要拷贝材质,默认是使用内存中的同一份材质</param>
        public void SetMaterialID(int index, String pMonoStr, bool bCopy = false)
        {
            ICall_RenderComponent_SetMaterialID(this, index, pMonoStr, bCopy);
        }

        /// <summary>
        /// 设置材质实例到指定的材质索引
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="pMonoObj">要设置的材质实例</param>
        /// <param name="bCopy">是否要拷贝材质,默认是使用内存中的同一份材质</param>
        public void SetMaterialInstance(int index, MaterialInstance pMonoObj, bool bCopy = false)
        {
            ICall_RenderComponent_SetMaterialInstance(this, index, pMonoObj, bCopy);
        }

        /// <summary>
        /// 获得渲染相关组件的第i个材质的着色器名称
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <returns>返回相应材质的着色器名称</returns>
        public String GetShaderID(int index)
        {
            return ICall_RenderComponent_GetShaderID(this, index);
        }

        /// <summary>
        /// 设置渲染相关组件的第i个材质的着色器
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="sSharderId">要设置的着色器名称</param>
        public void SetShaderID(int index, String sSharderId)
        {
            ICall_RenderComponent_SetShaderID(this, index, sSharderId);
        }

        /// <summary>
        /// 设置渲染相关组件的第i个材质的指定贴图参数的资源路径
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="sParamName">材质的贴图参数名称</param>
        /// <param name="sTexId">要设置的贴图资源路径</param>
        /// <param name="iPriority">默认的0表示同步加载,1表示异步加载</param>
        public void SetTexture(int index, String sParamName, String sTexId, int iPriority)
        {
            ICall_RenderComponent_SetTexture(this, index, sParamName, sTexId, iPriority);
        }

        /// <summary>
        /// 设置渲染相关组件的第i个材质的指定渲染到纹理参数的参数实例
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="sParamName">材质的渲染到纹理参数名称</param>
        /// <param name="rtt">要设置的渲染到纹理实例</param>
        public void SetTexture(int index, String sParamName, RenderToTexture rtt)
        {
            ICall_RenderComponent_SetTextureRTT(this, index, sParamName, rtt);
        }

        /// <summary>
        /// 设置渲染相关组件的第i个材质的指定浮点参数的值
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="sParamName">材质的浮点参数名称</param>
        /// <param name="val">要设置的浮点数参数值</param>
        public void SetShaderConstantParam(int index, String sParamName, float val)
        {
            ICall_RenderComponent_SetShaderConstantParam(this, index, sParamName, val);
        }

        /// <summary>
        /// 设置渲染相关组件的第i个材质的指定向量参数的向量值
        /// </summary>
        /// <param name="index">渲染相关组件的材质索引</param>
        /// <param name="sParamName">材质的向量参数名称</param>
        /// <param name="val">要设置的向量参数值</param>
        public void SetShaderConstantParam(int index, String sParamName, ref Vector4 val)
        {
            ICall_RenderComponent_SetShaderConstantParamF4(this, index, sParamName, ref val);
        }

        /// <summary>
        /// 获得渲染相关组件的着色器数量
        /// </summary>
        /// <returns>返回组件的着色器数量</returns>
        public uint GetShaderCount()
        {
            return ICall_RenderComponent_GetShaderCount(this);
        }


        /// <summary>
        /// 获得渲染相关组件的材质数量
        /// </summary>
        /// <returns>返回组件的材质数量</returns>
        public uint GetMaterialCount()
        {
            return ICall_RenderComponent_GetShaderCount(this);
        }

        /// <summary>
        /// 获得渲染相关组件的子网格个数
        /// </summary>
        /// <returns>返回子网格的个数</returns>
        public uint GetSubMeshCount()
        {
            return ICall_RenderComponent_GetShaderCount(this);
        }

        /// <summary>
        /// 设置渲染相关组件是否可见
        /// </summary>
        /// <param name="bVis">设置是否可见</param>
        public void SetVisible(bool bVis)
        {
            ICall_RenderComponent_SetVisible(this, bVis);
        }

        /// <summary>
        /// 获取渲染相关组件是否可见
        /// </summary>
        /// <returns>返回true则可见,反之</returns>
        public bool IsVisible()
        {
            return ICall_RenderComponent_IsVisible(this);
        }

        /// <summary>
        /// 单独渲染组件
        /// </summary>
        /// <param name="customMaterial">单独渲染组件使用的材质</param>
        public void StandaloneRender(MaterialInstance customMaterial)
        {
            ICall_RenderComponent_StandaloneRender(this, customMaterial);
        }
    }
}
