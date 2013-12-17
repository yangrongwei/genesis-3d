#include "animation/animation_stdneb.h"
#include "AnimationLayer.h"
#include "ClipControl.h"
namespace Animations
{

	AnimationLayer::AnimationLayer()
		:m_LayerIndex(InvalidIndex)
	{

	}

	AnimationLayer::~AnimationLayer()
	{

	}

	void AnimationLayer::FadeOutAll(float fadingTime)
	{
		ClipControls copylist = m_ActiveControls;// must copy.
		ClipControls::Iterator it = copylist.Begin();
		while(it != copylist.End())
		{
			(*it)->FadeOut(fadingTime);
			++it;
		}
	}

	bool AnimationLayer::Update(float time)
	{
		if (0 == m_ActiveControls.Size())
		{
			return false;
		}
		ClipControls copylist = m_ActiveControls;// must copy.
		ClipControls::Iterator it = copylist.Begin();
		while(it != copylist.End())
		{
			(*it)->Update(time);
			++it;
		}
		return true;
	}

	void AnimationLayer::_FadeOutOther(ClipControlPtr except, float fadingTime)
	{
		ClipControls copylist = m_ActiveControls;
		ClipControls::Iterator it = copylist.Begin();
		while(it != copylist.End())
		{
			if ((*it) != except)
			{
				(*it)->FadeOut(fadingTime);

			}
			++it;
		}	
	}

	void AnimationLayer::SetLayerIndex(int index)
	{
		n_assert(m_ClipControls.IsEmpty());
		m_LayerIndex = index;
	}

	void AnimationLayer::_AddActive(ClipControl* ptr)
	{
		IndexT index = m_ActiveControls.FindIndex(ptr);
		if (InvalidIndex == index)
		{
			m_ActiveControls.Append(ptr);
		}
	}

	void AnimationLayer::_AddControl(ClipControlPtr control)
	{
		n_assert(InvalidIndex != m_LayerIndex);
		n_assert (InvalidIndex == m_ClipControls.FindIndex(control));

		m_ClipControls.Append(control);
	}

	void AnimationLayer::_RemoveControl(ClipControlPtr control)
	{
		int index = m_ClipControls.FindIndex(control);
		if (InvalidIndex != index)
		{
			m_ClipControls.EraseIndex(index);
		}
	}

	void AnimationLayer::_RemoveActive(ClipControl* ptr)
	{
		IndexT index = m_ActiveControls.FindIndex(ptr);
		if (InvalidIndex != index)
		{
			m_ActiveControls.EraseIndex(index);
		}
	}
}