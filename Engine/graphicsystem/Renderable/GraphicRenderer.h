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
#ifndef GRAPHICRENDERER_H_
#define GRAPHICRENDERER_H_

#include "core/refcounted.h"
#include "Material/Material.h"
namespace Graphic
{
	class Renderable;

	class GraphicRenderer : public Core::RefCounted
	{
		__DeclareAbstractClass(GraphicRenderer)
	public:
		GraphicRenderer();
		virtual ~GraphicRenderer();

		virtual void Setup();		

		static void SetGlobalVertexShaderConstant(const ShaderParam& sp);
		static void SetGlobalPixelShaderConstant(const ShaderParam& sp);
		static void FindBindingRegister(MaterialParam* mpl, const ShaderParamBindingList& binding);
		static void SetVSBindingShadersOrTextures(int reg,MaterialParam* mpl);
		static void SetPSBindingShadersOrTextures(int reg,MaterialParam* mpl);


		static void ResetCache();
		static void ResetMaterialCache();
		static void SetMaterialParams(const MaterialParamList& mpl,const GPtr<MaterialPass>& pass);//virtual
		static void SetMaterialCommonParams(const GPtr<MaterialPass>& pass);
		static void SetMaterialCustomParams(const MaterialParamList& mpl,const GPtr<MaterialPass>& pass);

		static void SetMaterialCustomParams(const Material* material, Graphic::RenderPassType surType);


		static void RenderForward(Graphic::RenderPassType surType, const Renderable* renderalbe, const RenderBase::PrimitiveHandle& primHandle,
			IndexT firstVertex, SizeT numVertex, IndexT firstIndex, SizeT numIndex, const Material* customed);
		static void RenderForward(Graphic::RenderPassType surType, const Renderable* renderalbe, const RenderBase::PrimitiveHandle& primHandle, const Material* customed);

		static void BeforeRender(const Renderable* renderable, RenderPassType passType, const Material* customizedMat);
	protected:
		static void _SetMaterialCustomParams(const Renderable* renderalbe, const Material* customed, Graphic::RenderPassType surType);
		static void _SetMaterialCustomParamsOfGlobalBuffer(const Material* material, Graphic::RenderPassType surType);

		static uint s_preShaderInstanceID;
		static void* s_pPreMaterialInstance;
	};

	inline void GraphicRenderer::ResetCache()
	{
		s_preShaderInstanceID = 0;
		s_pPreMaterialInstance = 0;
	}

	inline void GraphicRenderer::ResetMaterialCache()
	{
		s_pPreMaterialInstance = 0;
	}

}

#endif // GRAPHICRENDERER_H_