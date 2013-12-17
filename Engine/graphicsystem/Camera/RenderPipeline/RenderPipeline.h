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
#ifndef RENDERPIPELINE_H_
#define RENDERPIPELINE_H_
#include "core/refcounted.h"
#include "graphicsystem/Camera/RenderPipeline/RenderPipelineManager.h"
#include "graphicsystem/base/RenderBase.h"
#include "rendersystem/base/RenderDeviceTypes.h"

namespace Math
{
	class bbox;
}

namespace Graphic
{
	class Material;
	class RenderToTexture;

	class PipelineParamters;

	class RenderPipeline : public Core::RefCounted
	{
		__DeclareClass(RenderPipeline)

	public:
		RenderPipeline();
		virtual ~RenderPipeline();
		virtual void Render(PipelineParamters& params) {}

	protected:
		void setGlobalShaderParam(PipelineParamters& params);
		void setCommonLights(PipelineParamters& params);//e.g. sun light, direction light.

		void setLight(const GPtr<Light>& light, SizeT lightindex);
		// note enable = true only used for directlight
		void setEnableLight(SizeT lightindex,bool bEnable);
		void renderRenderableList(PipelineParamters& params, RenderData::Type type , RenderPassType passType, const Material* customMat);
		void renderRenderableList(PipelineParamters& params, RenderData::Type type , RenderPassType passType, const Material* customMat, uint mark);
		bool empty(PipelineParamters& params, RenderData::Type type);
		bool contain(PipelineParamters& params, RenderData::Type type);
		void renderRenderableListWidthLight(PipelineParamters& params, RenderData::Type type, const Material* customMat); 

		void renderDepthMap(PipelineParamters& params);
		void renderLightLitMap(PipelineParamters& params);
		void renderCustomized(PipelineParamters& params);

		void renderSpecialPost(PipelineParamters& params);
		void renderCustomObjs(PipelineParamters& params);
		void renderMain(PipelineParamters& params);
		void renderScreenObjs(PipelineParamters& params);

		GPtr<RenderToTexture> m_currentRT;
	public:
		static const int s_lightSupport;
	};
}
#endif //RENDERPIPELINE_H_
