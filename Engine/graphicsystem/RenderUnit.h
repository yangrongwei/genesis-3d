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
#ifndef __RenderUnit_H__
#define __RenderUnit_H__


#include "math/matrix44.h"
#include "resource/resourcemanager.h"
#include "graphicsystem/Renderable/Renderable.h"

//------------------------------------------------------------------------------

namespace Graphic
{



	struct MeshInfo
	{
		Resources::ResourceId meshID;
		Resources::Priority priority;
		bool dirty;
		inline MeshInfo()
			:priority(1)
			,dirty(false)
		{

		}
	};

	class RenderbleResUnit
	{
	public:
		RenderbleResUnit();
		~RenderbleResUnit();
		bool Complete();
		template<typename T>
		T* ResetRenderable();
		void SetResInfo(const GPtr<Resources::MaterialResInfo>& res);
		const GPtr<Resources::MaterialResInfo>& GetResInfo() const;

		Graphic::Renderable* GetRenderable() const;
		template<typename T>
		T* GetRenderableSafe() const;// safe, but slow
		template<typename T>
		T* GetRenderableFast() const;// unsafe, but fast

		//
		void CopyFrom(const RenderbleResUnit& rhs, bool isCopyReable = false);
	private:
		void _destroy();
		friend class Util::Array<RenderbleResUnit>;
		void operator = (const RenderbleResUnit& rhs);//just be used for RenderableResUnitArray.

		mutable GPtr<Resources::MaterialResInfo> mShaderRes;
		mutable Graphic::Renderable* mRenderable;
	};
	typedef Util::Array<RenderbleResUnit> RenderableResUnitArray;

	inline const GPtr<Resources::MaterialResInfo>& RenderbleResUnit::GetResInfo() const
	{
		return mShaderRes;
	}

	inline bool RenderbleResUnit::Complete()
	{
		n_assert(mShaderRes.isvalid());//set material first.
		return (NULL != mRenderable);
	}

	inline Graphic::Renderable* RenderbleResUnit::GetRenderable() const
	{
		n_assert(mShaderRes.isvalid());//set material first.
		return mRenderable;
	}

	template<typename T>
	inline T* RenderbleResUnit::GetRenderableSafe() const
	{
		n_assert(mShaderRes.isvalid());//set material first.
		return reinterpret_cast<T*>(mRenderable);
	}
	template<typename T>
	inline T* RenderbleResUnit::GetRenderableFast() const
	{
		n_assert(mShaderRes.isvalid());//set material first.
		return static_cast<T*>(mRenderable);
	}
	template<typename T>
	inline T* RenderbleResUnit::ResetRenderable()
	{
		n_assert(mShaderRes.isvalid());//set material first.
		n_delete(mRenderable);
		mRenderable = n_new(T);
		mRenderable->SetMaterial(mShaderRes->GetHandle().get_unsafe());
		return static_cast<T*>(mRenderable);
	}


} 
//------------------------------------------------------------------------------
#endif // __RenderUnit_H__
