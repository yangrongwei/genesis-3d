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
#ifndef DEFERREDLIGHTINGPASS_RENDERPIPELINE_H_
#define DEFERREDLIGHTINGPASS_RENDERPIPELINE_H_

#include "rendersystem/base/PrimitiveGroup.h"
#include "rendersystem/base/RenderDeviceTypes.h"

namespace RenderBase
{
	class PrimitiveGroup;
}

namespace Graphic
{
	class Light;
	class Camera;
	class Material;
	struct ActiveLightInfo;
	class PipelineParamters;
	class DeferredLightingPass : public Core::RefCounted
	{
		__DeclareClass(DeferredLightingPass);
	public:
		DeferredLightingPass();
		~DeferredLightingPass();

		void Init();

		void RenderActiveLights(PipelineParamters& params);

	private:
		class _MeshInfo
		{
		public:
			RenderBase::PrimitiveHandle mPrimHandle;
			GPtr<Material> mMaterial;
			RenderBase::GPUProgramHandle* mShaderHandle;
			bool isInit();

			_MeshInfo()
				: mShaderHandle(NULL)
			{
			}
		};
		void _buildSunLight();
		void _buildDirectionalLight();
		void _buildPointLight();
		void _buildSpotLight();

		void _renderSunLight(const ActiveLightInfo& activeLight);
		void _renderLight(const ActiveLightInfo& activeLight);
		void _renderDirectionalLight(const ActiveLightInfo& activeLight);
		void _renderPointLight(const ActiveLightInfo& activeLight);
		void _renderSpotLight(const ActiveLightInfo& activeLight);
		void _calSpotWorld(const Light* light, Math::matrix44& trans);

		_MeshInfo mSunLightMesh;
		_MeshInfo mDirectionalLightMesh;
		_MeshInfo mPointLightMesh;
		_MeshInfo mSpotLightMesh;

	};

	inline bool DeferredLightingPass::_MeshInfo::isInit()
	{
		return mPrimHandle.IsValid();
	}
}

#endif //DEFERREDLIGHTINGPASS_RENDERPIPELINE_H_