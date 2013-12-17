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
#include "ImageFilters.h"
#include "graphicsystem/GraphicSystem.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "graphicsystem/Renderable/QuadRenderable.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
namespace Graphic
{
	ImageFilterManager::~ImageFilterManager()
	{
		RemoveAll();		
	}	

	void ImageFilterManager::RemoveAll()
	{
		if (!mFilters.IsEmpty())
		{
			Filters::Iterator begin = mFilters.Begin();
			const Filters::Iterator end = mFilters.End();
			while(end != begin)
			{
				n_delete(*begin);
				++begin;
			}
			mFilters.Clear();
		}
	}


	GPtr<Material> ImageFiltrationSystem::sImageCopyMaterial = NULL;
	RenderBase::RenderTargetHandle ImageFiltrationSystem::sNullTarget; 

	void ImageFiltrationSystem::Init()
	{
		Util::StringAtom fileName("sys:Image_Copy.shader");
		sImageCopyMaterial = GenesisMaterialMaker::MakeFromShader(fileName);
	}
	void ImageFiltrationSystem::ResizeWindow()
	{

	}
	void ImageFiltrationSystem::Shutdown()
	{
		sImageCopyMaterial->Discard();
		sImageCopyMaterial = NULL;
	}

	void ImageFiltrationSystem::Render(const RenderBase::TextureHandle* texture, const RenderToTexture* target, const Material* material, int passIndex /* = 0 */, uint clearflag /* = */ )
	{
		QuadRenderable* renderable = NULL;
		if (texture)
		{
			GlobalMaterialParam* pGMP = Material::GetGlobalMaterialParams();
			pGMP->SetTextureParam(eGShaderTexMainBuffer, *texture);

		}
		Graphic::GraphicSystem* gs = Graphic::GraphicSystem::Instance();
		if (target)
		{			
			const GPtr<RenderBase::RenderTarget>& rt = target->GetRenderTarget();
			renderable = target->GetRenderable();
			gs->SetRenderTarget(target->GetTargetHandle(), 0, clearflag);

		}
		else
		{

			renderable = gs->GetRenderingCamera()->GetQuadRenderable().get();

			gs->SetRenderTarget(sNullTarget, 0, clearflag);

		}
		if (NULL == material)
		{
			material = sImageCopyMaterial.get();
			passIndex = 0;
		}

		const Graphic::MaterialParamList& mpl = material->GetParamList();

		const Util::Array<GPtr<Graphic::MaterialPass> >& passList = material->GetTech()->GetPassList();

		const GPtr<Graphic::MaterialPass>& pass = passList[passIndex];

		Graphic::GraphicSystem::Instance()->SetShaderProgram( pass->GetGPUProgramHandle() );

		GraphicRenderer::SetMaterialParams( mpl, pass );
		const GPtr<RenderBase::RenderStateDesc>& rso = pass->GetRenderStateObject();

		Graphic::GraphicSystem::Instance()->SetRenderState( rso );

		Graphic::GraphicSystem::Instance()->DrawPrimitive( renderable->GetQuadHandle() );
	}

	void ImageFilterManager::_removeFiltersByOwner(const void* owner)
	{
		for (int i = mFilters.Size() - 1; i >= 0; --i)
		{
			if (owner == mFilters[i]->mOwner)
			{
				n_delete(mFilters[i]);
				mFilters.EraseIndex(i);
			}
		}
	}
	bool ImageFilterManager::_contain(const void* owner,ImageFilter::FilterIndexForSort indexForSort)
	{
		Filters::Iterator begin = mFilters.Begin();
		const Filters::Iterator end = mFilters.End();
		while(begin != end)
		{
			if (owner == (*begin)->mOwner&&indexForSort==(*begin)->mSortIndex)
			{
				return true;
			}
			++begin;
		}
		return false;
	}

	void ImageFilterManager::_insert(void* owner, ImageFilter* filter, ImageFilter::FilterIndexForSort indexForSort)
	{
		filter->mSortIndex = indexForSort;
		filter->mOwner = owner;
		for (int i = 0; i < mFilters.Size(); ++i)
		{
			if (mFilters[i]->mSortIndex > indexForSort)
			{
				mFilters.Insert(i, filter);
				return;
			}
		}
		mFilters.Append(filter);
	}
}