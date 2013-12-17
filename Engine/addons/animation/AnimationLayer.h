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

#ifndef __ANIMATION_LAYER_H__
#define __ANIMATION_LAYER_H__
#include "util/array.h"
#include "animation/ClipControl.h"
namespace Animations
{
	class AnimationLayer
	{
	public:
		typedef ClipControl* ClipControlPtr;		
		typedef Util::Array<ClipControlPtr> ClipControls;
		AnimationLayer();
		~AnimationLayer();

		void SetLayerIndex(int index);

		int GetLayerIndex() const;

		ClipControls& GetActiveList();

		void FadeOutAll(float fadingTime);

		bool Update(float time);

		void BonesSample();

		//internal call.
		void _AddControl(ClipControlPtr control);
		void _RemoveControl(ClipControlPtr control);
		void _AddActive(ClipControl* ptr);
		void _RemoveActive(ClipControl* ptr);

		void _FadeOutOther(ClipControlPtr except, float fadingTime);
	private:

		ClipControls m_ClipControls;
		ClipControls m_ActiveControls;
		int m_LayerIndex;
	};

	inline AnimationLayer::ClipControls& AnimationLayer::GetActiveList()
	{
		return m_ActiveControls;
	}

	inline int AnimationLayer::GetLayerIndex() const
	{
		return m_LayerIndex;
	}
}

#endif //__ANIMATION_LAYER_H__
