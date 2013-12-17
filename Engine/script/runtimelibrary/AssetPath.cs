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
using ScriptRuntime.Graphics.PackedVector;
using System;
using System.ComponentModel;
using System.Globalization;
using System.Runtime.InteropServices;

namespace ScriptRuntime
{

    public enum ResType
    {
        Invalid = -1,
        Dir,
        Other,
        Texture,
        Mesh,
        Script,
        Sound,
        Shader,
        Model,
        Skeleton,
        Animation,
        Template,
        FBX,
        Scene,
        Material,
        PhysicsMaterial,
        SpritePackageRes,
    }

    /// <summary>
    /// 资源路径,这个类型可反射到编辑器脚本反射面板
    /// </summary>
    public class AssetPath
    {
        public string   assetPath;
        public int      resType;

        public AssetPath()
        {
            assetPath = "";
            resType = (int)ResType.Material;
        }

        public AssetPath(string path,ResType type)
        {
            assetPath = path;
            resType =   (int)type;
        }
    }
}


