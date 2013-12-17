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

namespace ScriptGUI
{
    /// <summary>
    /// HashID类
    /// </summary>
    public struct HashID
    {
        private HashID(Int32 value)
        {
            id = value;
        }
        /// <summary>
        /// 判断两个哈希值是否相等
        /// </summary>
        /// <param name="ls">哈希值</param>
        /// <param name="rs">哈希值</param>
        /// <returns>相等true，不相等false</returns>
        public static bool operator ==(HashID ls, HashID rs)
        {
            return ls.id == rs.id;
        }
        /// <summary>
        /// 判断两个哈希值是否不等
        /// </summary>
        /// <param name="ls">哈希值</param>
        /// <param name="rs">哈希值</param>
        /// <returns>不相等true，相等false</returns>
        public static bool operator !=(HashID ls, HashID rs)
        {
            return ls.id != rs.id;
        }
        /// <summary>
        /// 隐式操作符
        /// </summary>
        /// <param name="hash_id">整型哈希值</param>
        /// <returns>哈希码</returns>
        public static implicit operator HashID(int hash_id)
        {
            return new HashID(hash_id);
        }
        /// <summary>
        /// 判断对象哈希值是否相等
        /// </summary>
        /// <param name="obj">指定的对象</param>
        /// <returns>相等true，不相等false</returns>
        public override bool Equals(object obj)
        {
            return ((obj is HashID) && (this == ((HashID)obj)));
        }
        /// <summary>
        /// 获得哈希值
        /// </summary>
        /// <returns>哈希值</returns>
        public override int GetHashCode()
        {
            return id;
        }

        private Int32 id;
    }
    /// <summary>
    /// 自定义字符串类
    /// </summary>
    public class FString
    {
        private FString(String str, HashID id)
        {
            mName = str;
            mID = id;
        }
        /// <summary>
        /// 创建一个FString
        /// </summary>
        /// <param name="str">字符串</param>
        /// <returns>创建后的FString</returns>
        public static FString CreateString(String str)
        {
            if (null == str)
            {
                return null;
            }
            HashID id = str.GetHashCode();
            return new FString(str, id);
        }
        /// <summary>
        /// 创建一个FString
        /// </summary>
        /// <param name="hash_id">哈希码</param>
        /// <returns>创建后的FString</returns>
        public static FString CreateString(HashID hash_id)
        {
            return new FString(null, hash_id);
        }
        /// <summary>
        /// 隐式操作符
        /// </summary>
        /// <param name="str">普通字符串</param>
        /// <returns>转换后的Fstring</returns>
        public static implicit operator FString(String str)
        {
            return CreateString(str);
        }
        /// <summary>
        /// 判断两个FString 是否相等
        /// </summary>
        /// <param name="ls">FString</param>
        /// <param name="rs">FString</param>
        /// <returns>相等true，不相等false</returns>
        internal static bool Equals(FString ls, FString rs)
        {
            if (ReferenceEquals(ls, null))
            {
                return ReferenceEquals(rs, null);
            }
            else if (ReferenceEquals(rs, null))
            {
                return false;
            }
            return (ls.mID == rs.mID);
        }
        /// <summary>
        /// 判断两个FString 是否相等
        /// </summary>
        /// <param name="ls">FString</param>
        /// <param name="rs">FString</param>
        /// <returns>相等true，不相等false</returns>
        public static bool operator ==(FString ls, FString rs)
        {
            return Equals(ls, rs);
        }
        /// <summary>
        /// 判断两个FString 是否不相等
        /// </summary>
        /// <param name="ls">FString</param>
        /// <param name="rs">FString</param>
        /// <returns>不相等true，相等false</returns>
        public static bool operator !=(FString ls, FString rs)
        {
            return !Equals(ls, rs);
        }
        /// <summary>
        /// 判断对象的FString是否相等
        /// </summary>
        /// <param name="obj">指定的对象</param>
        /// <returns>相等true，不相等false</returns>
        public override bool Equals(object obj)
        {

            return (obj is FString) && (this == (obj as FString));
        }
        /// <summary>
        /// 获取哈希码
        /// </summary>
        /// <returns>哈希码</returns>
        public override int GetHashCode()
        {
            return mID.GetHashCode();
        }

        internal String Name
        {
            get
            {
                return mName;
            }
        }

        private HashID mID;
        private String mName;

        //private static Dictionary<HashID, FString> mStringTable = new Dictionary<HashID, FString>();
    }
    
}
