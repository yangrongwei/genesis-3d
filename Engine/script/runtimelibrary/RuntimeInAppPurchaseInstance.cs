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
using System.Collections.Generic;
using System.Text;



namespace ScriptRuntime
{
    /// <summary>
    /// 运行时应用程序购买实例类
    /// </summary>
    public class RuntimeInAppPurchaseInstance
    {
        public enum SKErrorType
        {

            SKErrorUnknown = 0,
            SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
            SKErrorPaymentCancelled,    // user cancelled the request, etc.
            SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
            SKErrorPaymentNotAllowed,    // this device is not allowed to make the payment
            SKErrorRequestFailed

        };
        /// <summary>
        /// 获取产品信息虚方法
        /// </summary>
        /// <param name="pid">产品编号</param>
        /// <param name="price">产品价格</param>
        virtual public void OnSKGetProductInfo(string pid,string price)
        {

        }
        /// <summary>
        /// 成功购买虚方法
        /// </summary>
        /// <param name="pid">产品编号</param>
        /// <param name="tid">产品价格</param>
        /// <param name="receipt">成功信息</param>
        virtual public void OnSKPurchaseSucc(string pid,string tid,string receipt)
        {

        }
        /// <summary>
        /// 失败购买虚方法
        /// </summary>
        /// <param name="pid">产品编号</param>
        /// <param name="tid">产品价格</param>
        /// <param name="errorType">错误类型</param>
        /// <param name="error">错误内容</param>
        virtual public void OnSKPruchaseFailed(string pid, string tid, SKErrorType errorType, string error)
        {

        }
        /// <summary>
        /// 验证失败虚方法
        /// </summary>
        /// <param name="pid">产品编号</param>
        virtual public void OnSKValidateFailed(string pid)
        {

        }
    }
}

