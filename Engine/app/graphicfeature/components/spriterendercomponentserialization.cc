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
#include "spriterendercomponent.h"

namespace App
{
#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name

	DEFINE_SERIAL_ITEM_NAME(BlockName);
	DEFINE_SERIAL_ITEM_NAME(AnimName);
	DEFINE_SERIAL_ITEM_NAME(Loops);
	DEFINE_SERIAL_ITEM_NAME(Speed);
	DEFINE_SERIAL_ITEM_NAME(PlayOnWake);

	Version SpriteRenderComponent::GetVersion() const
	{
		return 2;
	}

	// @ISerialization::Load 
	void SpriteRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		if (1 == ver)
		{
			Load_1(ver, pReader, args);
			return;
		}
		else if (2 == ver)
		{
			Load_2(ver, pReader, args);
			return;
		}

		n_error(" %s Load unknown version.\n", this->GetClassName().AsCharPtr() );
	}

	void SpriteRenderComponent::Load_1( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);

		Util::String blockName;
		Util::String animName;

		int loops = 0;
		float speed = 1.0f;

		pReader->SerializeString(gBlockNameTag, blockName);

		pReader->SerializeString(gAnimNameTag, animName);
		pReader->SerializeInt(gLoopsTag, loops);
		pReader->SerializeFloat(gSpeedTag, speed);

		if (blockName.Length())
		{
			SetBlock(blockName);
		}
		
		if (animName.Length())
		{
			SetAnimation(animName, loops);
		}

	}

	void SpriteRenderComponent::Load_2( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);

		Util::String blockName;
		Util::String animName;

		int loops = 0;
		float speed = 1.0f;

		pReader->SerializeBool(gPlayOnWakeTag, mPlayOnWake);
		pReader->SerializeString(gBlockNameTag, blockName);

		pReader->SerializeString(gAnimNameTag, animName);
		pReader->SerializeInt(gLoopsTag, loops);
		pReader->SerializeFloat(gSpeedTag, speed);

		if (blockName.Length())
		{
			SetBlock(blockName);
		}

		if (animName.Length())
		{
			SetAnimation(animName, loops, false, speed);
		}
	}

	// @ISerialization::Save
	void SpriteRenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);

		pWriter->SerializeBool(gPlayOnWakeTag, mPlayOnWake);
		pWriter->SerializeString(gBlockNameTag, mPlayer.GetBlockName());

		pWriter->SerializeString(gAnimNameTag, mPlayer.GetAnimationName());
		pWriter->SerializeInt(gLoopsTag, mPlayer.GetAnimationLoops());
		pWriter->SerializeFloat(gSpeedTag, mPlayer.GetAnimationSpeed());
	}
}