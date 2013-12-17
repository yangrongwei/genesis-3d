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
//using  LayerID = System.UInt32;
namespace ScriptRuntime
{
    //这个枚举源于RenderBase.h中的RenderLayer。如果这里做了任何修改，请一并确保RenderBase.h的正确性。
    internal enum _RenderLayer : uint
    {
        eRLNone = FlagUtil.BIT_FLAG_NONE,
        eRLDefault = FlagUtil.BIT_FLAG_0,
        eRLWater = FlagUtil.BIT_FLAG_4,
        eRLCustomBegin = FlagUtil.BIT_FLAG_6,//
        eRLCustomEnd = FlagUtil.BIT_FLAG_29,//

        eRLSYSAll = eRLDefault | eRLWater,
        eRLCustomAll = FlagUtil.BIT_FLAG_6 | FlagUtil.BIT_FLAG_7 | 0x0fffff00 | FlagUtil.BIT_FLAG_28 | FlagUtil.BIT_FLAG_29,
        eRLCameraRenderAll = eRLSYSAll | eRLCustomAll,//渲染所有layer。
    }
    //LayerID的数值要和_RenderLayer匹配
    public enum LayerID : uint
    {  
        Default = 0,
        Water = 4,
        CustomBegin = 6,
        CustomEnd = 29,
        Min = Default,
        Max = 31,
        Unknown = UInt32.MaxValue,
    }

    public enum LayerFlag : uint
    {  
        Default = _RenderLayer.eRLDefault,
        Water = _RenderLayer.eRLWater,
        CustomBegin = _RenderLayer.eRLCustomBegin,
        CustomEnd = _RenderLayer.eRLCustomEnd,

        None = _RenderLayer.eRLNone,
        All = _RenderLayer.eRLCameraRenderAll,
    };


    public struct LayerMark : IEquatable<LayerMark>
    {
        public LayerFlag Mark
        {
            get
            {
                return (LayerFlag)Mark;
            }
            set
            {
                MarkAsUINT = (uint)value;
            }
        }

        public uint MarkAsUINT;

        public static LayerMark None
        {
            get
            {
                return FlagUtil.BIT_FLAG_NONE;
            }
        }
        public LayerMark(LayerFlag flag)
        {
            this.MarkAsUINT = (uint)flag;
        }
        public LayerMark(LayerID layerid)
        {
            this.MarkAsUINT = ConvertToMark(layerid);
        }
        public LayerMark(uint mark)
        {
            this.MarkAsUINT = mark;
        }

        public static implicit operator LayerMark(uint mark)
        {
            return new LayerMark(mark);
        }

        public static implicit operator LayerMark(LayerFlag flag)
        {
            return new LayerMark(flag);
        }

        public void AddLayer(LayerFlag flag)
        {
            MarkAsUINT |= (uint)flag;
        }
        public void AddLayer(LayerID layerID)
        {
            if (LayerID.Min <= layerID && layerID < LayerID.Max)
            {
                MarkAsUINT |= FlagUtil.BIT_FLAG((int)layerID);
            }
        }
        public void RemoveLayers(LayerFlag flag)
        {
            MarkAsUINT &= ~((uint)flag);
        }
        public void RemoveLayers(uint mark)
        {
            MarkAsUINT &= ~((uint)mark);
        }
        public void RemoveLayer(LayerID layerID)
        {
            if (LayerID.Min <= layerID && layerID < LayerID.Max)
            {
                MarkAsUINT &= ~(FlagUtil.BIT_FLAG((int)layerID));
            }
        }
        public bool ContainLayer(LayerID layerID)
        {
            return (MarkAsUINT & ConvertToMark(layerID)) != (uint)0;
        }

        public bool ContainAllLayers(LayerFlag flag)
        {
            return (MarkAsUINT & (uint)(flag)) == (uint)flag;
        }

        public bool ContainAllLayers(uint mark)
        {
            return (MarkAsUINT & (uint)(mark)) == (uint)mark;
        }

        public bool ContainAllLayers(LayerMark lm)
        {
            return (Mark & lm.Mark) == lm.Mark;
        }

        public bool Equals(LayerMark other)
        {
            return (this.Mark == other.Mark);
        }
        public override bool Equals(object obj)
        {
            bool flag = false;
            if (obj is LayerMark)
            {
                flag = this.Equals((LayerMark)obj);
            }
            return flag;
        }

        public static LayerFlag ConvertToLayerFlag(uint mark)
        {
            return (LayerFlag)mark;
        }

        public static LayerFlag ConvertToLayerFlag(int layerID)
        {
            return (LayerFlag)FlagUtil.BIT_FLAG(layerID);
        }

        public static uint ConvertToMark(LayerFlag flag)
        {
            return (uint)flag;
        }

        public static uint ConvertToMark(LayerID layerID)
        {
            return (uint)FlagUtil.BIT_FLAG((int)layerID);
        }

        static LayerMark()
        {
        }

    }
}
