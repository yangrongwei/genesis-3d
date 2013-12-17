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
#ifndef __animationres_H__
#define __animationres_H__
#include "resource/resource.h"
#include "util/dictionary.h"
#include "animation/animationclip.h"

namespace Resources
{
	class AnimationRes: public Resources::Resource
	{
		__DeclareSubClass(AnimationRes, Resource );
	public:
		AnimationRes();
		virtual ~AnimationRes();

		SizeT GetClipCount(void) const;

		bool HasClip(const Util::String& clipName);

		const GPtr<Animations::AnimationClip>& GetClip(Util::String& name ) const;

		const GPtr<Animations::AnimationClip>& GetClip(IndexT index) const;

		/// Failed if clip name is repeat or empty 
		bool AddClip(const GPtr<Animations::AnimationClip>& clip );

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;
	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

	protected:
		typedef Util::Dictionary<Util::String , GPtr<Animations::AnimationClip> > Container;
		Container mContainer; 
		friend class AnimationResLoader;
	};
	//------------------------------------------------------------------------
	inline
		SizeT 
		AnimationRes::GetClipCount(void) const
	{
		return mContainer.Size();
	}
	//------------------------------------------------------------------------
	inline
		bool 
		AnimationRes::HasClip(const Util::String& clipName)
	{
		return mContainer.Contains(clipName);
	}
}

#endif // __animationres_H__
