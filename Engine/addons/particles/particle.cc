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
#include "stdneb.h"
#include "particles/particle.h"

namespace Particles
{
	const Math::float3 ConstDefine::FLOAT3_ZERO(0.0f, 0.0f, 0.0f);
	const Math::float3 ConstDefine::FLOAT3_IDENTITY(1.0f, 1.0f, 1.0f);
	const Math::float3 ConstDefine::FLOAT3_UNIT_X(1.0f, 0.0f, 0.0f);
	const Math::float3 ConstDefine::FLOAT3_UNIT_Y(0.0f, 1.0f, 0.0f);
	const Math::float3 ConstDefine::FLOAT3_UNIT_Z(0.0f, 0.0f, 1.0f);

	const Math::quaternion ConstDefine::QUATERNION_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const Math::quaternion ConstDefine::QUATERNION_IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

	const SizeT ConstDefine::DEFAULT_TECHNIQUE_QUOTA = 200;
	const SizeT ConstDefine::MAX_TECHNIQUE_QUOTA = 15000;

	const Math::float3 ConstDefine::DEFAULT_EMITTER_DIRECTION(0.0f, 1.0f, 0.0f);
	const Math::scalar ConstDefine::DEFAULT_EMITTER_MIN_DIRECTION = 0.0f;
	const Math::scalar ConstDefine::DEFAULT_EMITTER_MAX_DIRECTION = N_PI_DOUBLE;
	const Math::float3 ConstDefine::DEFAULT_EMITTER_VELOCITY(1.0f, 1.0f, 1.0f);

	const SizeT ConstDefine::DEFAULT_MIN_EMITTER_RATE = 50;
	const SizeT ConstDefine::DEFAULT_MAX_EMITTER_RATE = 100;

	const Math::scalar ConstDefine::DEFAULT_ROTATION_SPEED = 0.0f;

	const Math::scalar ConstDefine::DEFAULT_MIN_TIME_LIVE = 1.0f;
	const Math::scalar ConstDefine::DEFAULT_MAX_TIME_LIVE = 10.0f;

	const Math::scalar ConstDefine::DEFAULT_MASS = 1.0f;

	const Math::ColorF ConstDefine::DEFAULT_MIN_COLOR(0.0,0.0,0.0,0.0);
	const Math::ColorF ConstDefine::DEFAULT_MAX_COLOR(1.0,1.0,1.0,1.0);

	const Math::float3 ConstDefine::DEFAULT_SIZE(1.0f, 1.0f, 1.0f);

	const IndexT ConstDefine::DEFAULT_TEXCOORD_INDEX = 0;

	const Math::matrix44 ConstDefine::MATRIX_IDENTITY;

	const Math::float2 ConstDefine::DEFAULT_ACCELERATION(1.0f, 10.0f);

}