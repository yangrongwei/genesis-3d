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
#ifndef	DEFERREDLIGHTING_RENDERPIPELINE_H_
#define DEFERREDLIGHTING_RENDERPIPELINE_H_
#include "RenderPipeline.h"
#include "DeferredLightingPass.h"
#include "ForwardShadingRenderPipeline.h"

namespace Graphic
{
	class PipelineParamters;

	class DeferredLightingRenderPipeline : public ForwardShadingRenderPipeline
	{
		__DeclareSubClass(DeferredLightingRenderPipeline, ForwardShadingRenderPipeline);
	public:
		DeferredLightingRenderPipeline();
		virtual ~DeferredLightingRenderPipeline();

		virtual void Render(PipelineParamters& context);
	private:
		void _RenderGBuffer(PipelineParamters& context);
		void _RenderLightMap(PipelineParamters& context);
		void _RenderOtherObjs(PipelineParamters& context);
		void _RenderFinalScene(PipelineParamters& context);

		GPtr<DeferredLightingPass> mLightPass;
	};
}

#endif 
