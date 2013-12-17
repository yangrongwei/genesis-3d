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
    /// 灯光组件
    /// </summary>
    public partial class LightComponent : Component
    {
        private LightComponent(DummyClass__ dummy)
        {
        }
        /// <summary>
        /// 创建一个光源组件,默认为电光源
        /// </summary>
        public LightComponent()
        {
            ICall_LightComponent_Bind(this);
        }
        /// <summary>
        /// 获取与改变光源类型
        /// </summary>
        public LightType LightType
        {
            get
            {
                return converLightType(ICall_LightComponent_GetLightType(this));
            }
            set
            {
                ICall_LightComponent_SetLightType(this, converLightType(value));
            }
        }
        /// <summary>
        /// 获取与设置光源位置
        /// </summary>
        public Vector3 Position
        {
            get
            {
                Vector3 pos;
                ICall_LightComponent_GetPosition(this, out pos);
                return pos;
            }
            set
            {
                ICall_LightComponent_SetPosition(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置光源方向
        /// </summary>
        public Vector3 Direction
        {
            get
            {
                Vector3 dir;
                ICall_LightComponent_GetDirection(this, out dir);
                return dir;
            }
            set
            {
                ICall_LightComponent_SetDirection(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置灯光颜色
        /// </summary>
        public ColorF Color
        {
            get
            {
                ColorF cf;
                ICall_LightComponent_GetColorF(this, out cf);
                return cf;
            }
            set
            {
                ICall_LightComponent_SetColorF(this, ref value);
            }
        }
        /// <summary>
        /// 获取与设置灯光强度
        /// </summary>
        public float Intensity
        {
            get
            {
                return ICall_LightComponent_GetIntensity(this);
            }
            set
            {
                value = Math.Max(0.0f, value);
                ICall_LightComponent_SetIntensity(this, value);
            }
        }
        /// <summary>
        /// 获取与设置灯光的光照范围
        /// </summary>
        public float Range
        {
            get
            {
                return ICall_LightComponent_GetRange(this);
            }
            set
            {
                if ( value < 0.01f)
                {
                    value = 0.01f;
                }
                ICall_LightComponent_SetRange(this, value);
            }
        }
        /// <summary>
        /// 光源随距离的衰减
        /// </summary>
        public float DistanceFallOff
        {
            get
            {
                return ICall_LightComponent_GetDistanceFallOff(this);
            }
            set
            {
                if (value < 0.0f)
                {
                    value = 0.0f;
                }
                ICall_LightComponent_SetDistanceFallOff(this, value);
            }
        }

        /// <summary>
        /// 聚光灯的内角
        /// </summary>
        public float SpotInnerAngle
        {
            get
            {
                return ICall_LightComponent_GetSpotInnerAngle(this);
            }
            set
            {
                if (value < 0.0f)
                {
                    value = 0.0f;
                }
                ICall_LightComponent_SetSpotInnerAngle(this, value);
            }
        }
        /// <summary>
        /// 聚光灯的外角
        /// </summary>
        public float SpotOuterAngle
        {
            get
            {
                return ICall_LightComponent_GetSpotOuterAngle(this);
            }
            set
            {
                if (value < 0.0f)
                {
                    value = 0.0f;
                }
                ICall_LightComponent_SetSpotOuterAngle(this, value);
            }
        }

        /// <summary>
        /// 聚光灯的半径衰减
        /// </summary>
        public float RadialFallOff
        {
            get
            {
                return ICall_LightComponent_GetSpotExponent(this);
            }
            set
            {
                if (value < 0.0f)
                {
                    value = 0.0f;
                }
                ICall_LightComponent_SetSpotExponent(this, value);
            }
        }

        private const float S_C_ATTEN_REF = 20;//[zhongdaohuan]参见light.h的S_C_ATTEN_REF
        private const float S_C_RANGE_REF = 0.00001f;
        private const float S_C_LINEAR_REF = 100000000f;

        internal static LightType converLightType(int lightType)
        {
            return (LightType)lightType;
        }

        internal static int converLightType(LightType lightType)
        {
            return (int)lightType;
        }
    }
}
