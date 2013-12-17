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
#include "resource/resource_stdneb.h"
#include "resource/animationres.h"

namespace Resources
{
	__ImplementClass( Resources::AnimationRes, 'ANRS', Resources::Resource);
	//------------------------------------------------------------------------
	AnimationRes::AnimationRes()
	{

	}
	//------------------------------------------------------------------------
	AnimationRes::~AnimationRes()
	{

	}
	//------------------------------------------------------------------------
	const GPtr<Animations::AnimationClip>& 
		AnimationRes::GetClip(Util::String& name ) const
	{
		IndexT findIndex = mContainer.FindIndex(name);
		if ( findIndex != InvalidIndex )
		{
			return mContainer.ValueAtIndex(findIndex);
		}
		else
		{
			return Animations::AnimationClip::NullClip;
		}
	}
	//------------------------------------------------------------------------
	const GPtr<Animations::AnimationClip>& 
		AnimationRes::GetClip(IndexT index) const
	{
		if ( index >=0 && index < mContainer.Size() )
		{
			return mContainer.ValueAtIndex(index);
		}
		else
		{
			return Animations::AnimationClip::NullClip;
		}
	}
	//------------------------------------------------------------------------
	bool 
		AnimationRes::AddClip(const GPtr<Animations::AnimationClip>& clip )
	{
		if ( clip.isvalid() && !clip->GetName().AsString().IsEmpty() )
		{
			if ( !HasClip( clip->GetName().AsString() ) )
			{
				mContainer.Add( clip->GetName().AsString(), clip );
				return true;
			}
		}
		return false;
	}
	//------------------------------------------------------------------------
	SizeT 
		AnimationRes::CalculateRuntimeSize(void) const
	{
		SizeT size = sizeof( AnimationRes );
		for ( IndexT index = 0; index < mContainer.Size(); ++index )
		{
			size += mContainer.ValueAtIndex(index)->CalculateRuntimeSize();
		}
		return size;
	}
	//------------------------------------------------------------------------
	bool 
		AnimationRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{
		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<AnimationRes> tempAnimRes = tempRes.downcast<AnimationRes>();
			n_assert( tempAnimRes.isvalid() );
			this->mContainer.Swap( tempAnimRes->mContainer );
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------
	void AnimationRes::UnLoadImpl(void)
	{
		mContainer.Clear();
	}
}
