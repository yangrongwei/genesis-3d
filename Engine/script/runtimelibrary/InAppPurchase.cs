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
    /// 应用程序购买类
    /// </summary>
    public class InAppPurchase:Base
    {
        /// <summary>
        /// 请求产品信息
        /// </summary>
        /// <param name="valStr">产品信息指示</param>
        static public void RequestProductInfo(String valStr)
        {
            ICall_InAppPurchase_RequestProductInfo(valStr);  
        }
        /// <summary>
        /// 购买产品操作
        /// </summary>
        /// <param name="valStr">产品信息指示</param>
        static public void BuyProduct(String valStr)
        {
            ICall_InAppPurchase_BuyProduct(valStr);  
        }
        
   

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_InAppPurchase_RequestProductInfo(String valStr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_InAppPurchase_BuyProduct(String valStr);
       
    }
}