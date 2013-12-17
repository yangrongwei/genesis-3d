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
#ifndef _IMAGEFILTERS_H_
#define _IMAGEFILTERS_H_
#include "foundation/util/array.h"
#include "rendersystem/base/RenderDeviceTypes.h"

namespace Graphic
{
	class Material;
	class RenderToTexture;
	class QuadRenderable;
	class ImageFilter
	{
	public:
		enum FilterIndexForSort
		{
			FilterIndexForSort_System1 = 0,
			FilterIndexForSort_ScriptBegin = 100,
			FilterIndexForSort_ScriptEnd = 99999,
			FilterIndexForSort_System2 = FilterIndexForSort_ScriptEnd + 1,
		};
		virtual ~ImageFilter(){}
		virtual bool RenderFilter(RenderToTexture* source, RenderToTexture* destination) = 0;
	protected:
		template<typename Onwer> 
		Onwer* getOwner();
		friend class ImageFilterManager;
		FilterIndexForSort mSortIndex;
		void* mOwner;
	};
	template<typename Onwer>
	Onwer* ImageFilter::getOwner()
	{
		return static_cast<Onwer*>(mOwner);
	}

	class ImageFilterManager
	{
	public:
		~ImageFilterManager();

		template<typename Filter, typename Owner>
		Filter* InsertFilter(Owner* owner, ImageFilter::FilterIndexForSort indexForSort);
		template<typename Owner>
		bool Contain(const Owner* owner, ImageFilter::FilterIndexForSort indexForSort );
		template<typename Owner>
		void RemoveFiltersByOwner(const Owner* owner);
		void RemoveAll();
		int Size();
		ImageFilter* GetFilter(int index);

	private:	
		bool _contain(const void* owner,ImageFilter::FilterIndexForSort indexForSort);
		void _removeFiltersByOwner(const void* owner);
		void _insert(void* owner, ImageFilter* filter, ImageFilter::FilterIndexForSort indexForSort);
		typedef Util::Array<ImageFilter*> Filters;
		Filters mFilters;
	};

	template<typename Filter, typename Owner>
	Filter* ImageFilterManager::InsertFilter(Owner* owner, ImageFilter::FilterIndexForSort indexForSort)
	{
		Filter* filter = n_new(Filter);
		_insert(owner, filter, indexForSort);
		return filter;
	}

	template<typename Owner>
	void ImageFilterManager::RemoveFiltersByOwner(const Owner* owner)
	{
		_removeFiltersByOwner(owner);
	}
	template<typename Owner>
	bool ImageFilterManager::Contain(const Owner* owner,ImageFilter::FilterIndexForSort indexForSort)
	{
		return _contain(owner,indexForSort);
	}
	inline int ImageFilterManager::Size()
	{
		return mFilters.Size();
	}

	inline ImageFilter* ImageFilterManager::GetFilter(int index)
	{
		return mFilters[index];
	}
	class ImageFiltrationSystem
	{
	public:
		static void Init();
		static void ResizeWindow();
		static void Shutdown();
		static void Render(const RenderBase::TextureHandle* texture, const RenderToTexture* target, const Material* material, int passIndex = 0, uint clearflag = BIT_FLAG(0));
	private:
		static GPtr<Material> sImageCopyMaterial;
		static RenderBase::RenderTargetHandle sNullTarget;
	};



}
#endif //_IMAGEFILTERS_H_