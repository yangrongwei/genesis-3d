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
    /// 射线检测相关算法的集合
    /// </summary>
    public static class IntersectWorld// : Base
    {
        /// <summary>
        /// 构造一条从当前默认相机发出的射线
        /// </summary>
        /// <param name="screenPos">射线起点的位置，取值范围：[0,1]</param>
        /// <param name="outRay">返回值（构造出的射线）</param>
        static public void IntersectWorld_ComputeRay(ref Vector2 screenPos, out Ray outRay)
        {
            ICall_IntersectWorld_ComputeRay(ref screenPos,out outRay);
        }

        /// <summary>
        /// 射线检测指定的Actor
        /// </summary>
        /// <param name="act">要检测的Actor</param>
        /// <param name="ray">射线</param>
        /// <param name="layerid">参与检测的层</param>
        /// <param name="pos">射线打到Actor上的点的坐标</param>
        /// <returns>是否检测到Actor</returns>
        static public bool IntersectActor(Actor act, ref Ray ray, LayerID layerid, out Vector3 pos)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                return ICall_IntersectWorld_IntersectActor(act, ref ray, LayerMark.ConvertToMark(layerid), out pos);
            }
            pos = Vector3.Zero;
            return false;
        }

        /// <summary>
        /// 射线检测Actor
        /// </summary>
        /// <param name="ray">指定的射线</param>
        /// <param name="layerid">参与检测的层</param>
        /// <returns>射线检测到Actor（射线从起点发出，第一个检测到的Actor），若没有检测到任何Actor，返回NULL</returns>
        static public Actor IntersectWorld_Actor(ref Ray ray, LayerID layerid)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                return ICall_IntersectWorld_Actor(ref ray, LayerMark.ConvertToMark(layerid));
            }
            return null;
        }

        /// <summary>
        /// 获取射线检测到场景里(网格)Actor的第一个点的坐标
        /// </summary>
        /// <param name="ray">指定的射线</param>
        /// <param name="layerid">参与检测的层</param>
        /// <param name="outPoint">返回值（检测到的第一个点的坐标）</param>
        static public void IntersectWorld_Point(ref Ray ray, LayerID layerid, out Vector3 outPoint)
        {
            if (LayerID.Min <= layerid && layerid < LayerID.Max)
            {
                ICall_IntersectWorld_Point(ref ray, LayerMark.ConvertToMark(layerid), out outPoint);
            }
            else
            {
                outPoint = Vector3.Zero;
            }
        }

        /// <summary>
        /// 获取射线与指定(网格)Actor的交点
        /// </summary>
        /// <param name="act">要检测的Actor</param>
        /// <param name="ray">要检测的射线</param>
        /// <param name="mark">Actor的过滤层(只有这个层的Actor参与射线检测)</param>
        /// <param name="pos">射线与Actor的焦点</param>
        /// <returns>射线与Actor是否有交点</returns>
        static public bool IntersectActor(Actor act, ref Ray ray, LayerMark mark, out Vector3 pos)
        {
            return ICall_IntersectWorld_IntersectActor(act, ref ray, mark.MarkAsUINT, out pos);
        }

        /// <summary>
        /// 获取射线打中的第一个(网格)Actor
        /// </summary>
        /// <param name="ray">指定的射线</param>
        /// <param name="mark">Actor的过滤层(只有这个层的Actor参与射线检测)</param>
        /// <returns></returns>
        static public Actor IntersectWorld_Actor(ref Ray ray, LayerMark mark)
        {
            return ICall_IntersectWorld_Actor(ref ray, mark.MarkAsUINT);
        }

        /// <summary>
        /// 获取射线打中的第一个(网格)Actor的交点
        /// </summary>
        /// <param name="ray">指定的射线</param>
        /// <param name="mark">Actor的过滤层(只有这个层的Actor参与射线检测)</param>
        /// <param name="outPoint">射线与第一个Actor的交点</param>
        static public void IntersectWorld_Point(ref Ray ray, LayerMark mark, out Vector3 outPoint)
        {
            ICall_IntersectWorld_Point(ref ray, mark.MarkAsUINT, out outPoint);
        }

        /// <summary>
        /// 获取射线打中的第一个网格上的三角形的三个点
        /// </summary>
        /// <param name="ray">指定的射线</param>
        /// <param name="mark">Actor的过滤层(只有这个层的Actor参与射线检测)</param>
        /// <param name="outPoint1">三角形的第一个点</param>
        /// <param name="outPoint2">三角形的第二个点</param>
        /// <param name="outPoint3">三角形的第三个点</param>
        static public void IntersectWorld_Triangle(ref Ray ray, LayerMark mark, out Vector3 outPoint1, out Vector3 outPoint2, out Vector3 outPoint3)
        {
            ICall_IntersectWorld_Triangle(ref ray, mark.MarkAsUINT, out outPoint1, out outPoint2, out outPoint3);
        }

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_ComputeRay(ref Vector2 screenPos, out Ray outRay);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_IntersectWorld_IntersectActor(Actor act, ref Ray ray, uint selectMark, out Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_IntersectWorld_Actor(ref Ray ray, uint selectMark);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_Point(ref Ray ray, uint selectMark, out Vector3 outFloat3);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IntersectWorld_Triangle(ref Ray ray, uint selectMark, out Vector3 outPoint1, out Vector3 outPoint2, out Vector3 outPoint3);
    }
}
