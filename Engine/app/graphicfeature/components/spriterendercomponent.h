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
#ifndef SPRITERENDERCOMPONENT_H_
#define SPRITERENDERCOMPONENT_H_
#include "rendersystem/base/RenderDeviceTypes.h"
#include "graphicfeature/components/spritebaserendercomponent.h"


namespace App
{
	class GraphicsFeature;
	class SpriteRenderComponent: public App::SpriteBaseRenderComponent
	{
		__DeclareSubClass(SpriteRenderComponent, App::SpriteBaseRenderComponent)
	public:
		SpriteRenderComponent();
		virtual ~SpriteRenderComponent();
		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		virtual void Setup(const Resources::ResourceId& packId);

		virtual void StandaloneRender(const GPtr<Graphic::Material>& customMat);

		void MaterialDirty();

		void SetBlock(const Util::String& blockName);

		void SetAnimation(const Util::String& name, int loops = 0 , bool play = true, float speed = 1.0f);

		void SetAnimationSpeed(float speed);

		void RemoveBlock();

		void RemoveAnimation();

		void Replay();

		void Play();

		void Pause();

		void Stop();

		Util::String GetBlockName() const;

		Util::String GetAnimationName() const;

		int GetAnimationLoops() const;

		float GetAnimationSpeed() const;

		bool IsAnimationPlaying() const;

		void SetPlayOnWake(bool bPlayOnWake);

		bool GetPlayOnWake() const;

		int GetFrameCount() const;

		int GetCurrentFrameIndex() const;

		void SetCurrentFrame(int frameIndex);

		float GetTotalUnits() const;

		float GetCurrentUnits() const;

		void SetCurrentUnits(float units);

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;
		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;


		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

	protected:
		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		virtual void _OnFrame();

		void _Update();

		void _OnDeviceLost(GraphicsFeature* sender);

		void Load_1( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_2( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );
	private:
		typedef SpriteRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> RenderObjectPtr;
		Sprite::SpritePlayer mPlayer;
		bool mPlayOnWake;

	};

	inline Util::String SpriteRenderComponent::GetBlockName() const
	{
		return mPlayer.GetBlockName();
	}

	inline Util::String SpriteRenderComponent::GetAnimationName() const
	{
		return mPlayer.GetAnimationName();
	}

	inline void SpriteRenderComponent::SetAnimationSpeed(float speed)
	{
		mPlayer.SetAnimationSpeed(speed);
	}

	inline void SpriteRenderComponent::RemoveBlock()
	{
		mPlayer.RemoveBlock();
	}

	inline void SpriteRenderComponent::RemoveAnimation()
	{
		mPlayer.RemoveAnimation();
	}

	inline void SpriteRenderComponent::Replay()
	{
		mPlayer.Replay();
	}

	inline void SpriteRenderComponent::Play()
	{
		mPlayer.Play();
	}

	inline void SpriteRenderComponent::Pause()
	{
		mPlayer.Pause();
	}

	inline void SpriteRenderComponent::Stop()
	{
		mPlayer.Stop();
	}
	inline int SpriteRenderComponent::GetAnimationLoops() const
	{
		return mPlayer.GetAnimationLoops();
	}

	inline float SpriteRenderComponent::GetAnimationSpeed() const
	{
		return mPlayer.GetAnimationSpeed();
	}

	inline bool SpriteRenderComponent::IsAnimationPlaying() const
	{
		return mPlayer.IsAnimationPlaying();
	}

	inline void SpriteRenderComponent::SetPlayOnWake(bool bPlayOnWake)
	{
		mPlayOnWake = bPlayOnWake;
	}

	inline bool SpriteRenderComponent::GetPlayOnWake() const
	{
		return mPlayOnWake;
	}

	inline int SpriteRenderComponent::GetFrameCount() const
	{
		return mPlayer.GetAnimationLoops();
	}

	inline int SpriteRenderComponent::GetCurrentFrameIndex() const
	{
		return mPlayer.GetCurrentFrameIndex();
	}

	inline void SpriteRenderComponent::SetCurrentFrame(int frameIndex)
	{
		return mPlayer.SetCurrentFrame(frameIndex);
	}

	inline float SpriteRenderComponent::GetTotalUnits() const
	{
		return mPlayer.GetTotalUnits();
	}

	inline float SpriteRenderComponent::GetCurrentUnits() const
	{
		return mPlayer.GetCurrentUnits();
	}

	inline void SpriteRenderComponent::SetCurrentUnits(float units)
	{
		mPlayer.SetCurrentUnits(units);
	}
}




#endif // SPRITERENDERCOMPONENT_H_
