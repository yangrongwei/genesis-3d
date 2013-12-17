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
#include "graphicfeature/components/animationcomponent.h"

namespace App
{
	class AnimationComponentSerialization
	{
	public:
		AnimationComponentSerialization(AnimationComponent* pComponent);
		~AnimationComponentSerialization();

	public:
		void Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_1(AppReader* pReader);
		void Load_2(AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_3(AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_4(AppReader* pReader, const Serialization::SerializationArgs* args );
		void Save(AppWriter* pWriter) const ;

	protected:
		AnimationComponent* m_Object;
	};

	const char* s_AnimCount      = "AnimationCount";
	const char* s_Animation      = "Animation";
	const char* s_AnimationDummy = "EmptyNull";
	const char* s_WrpaMode       = "WrapMode";
	const char* s_AnimationSpeed = "AnimationSpeed";
	const char* s_AttachedActorCount = "AttachedActorCount";
	const char* s_AttachedActorGUID = "AttachedActorGUID";
	const char* s_AttachedSkelName = "AttachedSkelName";
	const char* s_AttachedActorTrans = "AttachedActorTrans";
	const char* s_DefaultAnimName = "DefaultAnimName";

	AnimationComponentSerialization::AnimationComponentSerialization(AnimationComponent* pComponent)
		: m_Object(pComponent)
	{

	}

	AnimationComponentSerialization::~AnimationComponentSerialization()
	{

	}

	void AnimationComponentSerialization::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		if (ver == 1)
		{
			Load_1(pReader);
		}
		else if(ver == 2)
		{
			Load_2(pReader, args);
		}
		else if(ver == 3)
		{
			Load_3(pReader, args);
		}
		else if(ver == 4)
		{
			Load_4(pReader, args);
		}
		else
		{
			n_error("SceneSerialization::Load unknown version");
		}
	}

	void AnimationComponentSerialization::Load_1(AppReader* pReader)
	{
		SizeT count = 0;
		pReader->SerializeInt(s_AnimCount, count);

		for (int i = 0; i<count; ++i)
		{
			Util::String animName;
			pReader->SerializeString(s_Animation, animName);
			m_Object->SetAnimationID(animName);	
		}
	}

	void AnimationComponentSerialization::Load_2(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		SizeT count = 0;
		pReader->SerializeInt(s_AnimCount, count);

		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();
		Resources::Priority priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::AnimationDefault : cargs->getPriority();
		for (int i = 0; i<count; ++i)
		{
			Util::String animName;
			pReader->SerializeString(s_Animation, animName);


			m_Object->SetAnimationID(animName, priority);
			int wrapMode;
			pReader->SerializeInt(s_WrpaMode,wrapMode);
			m_Object->SetWrapMode(animName,wrapMode);
			float speed;
			pReader->SerializeFloat(s_AnimationSpeed, speed);
			m_Object->SetAnimationSpeed(animName,speed);
		}
	}

	void AnimationComponentSerialization::Load_3(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_2(pReader, args);

		SizeT attachCount = 0;
		pReader->SerializeInt(s_AttachedActorCount, attachCount);

		m_Object->GetTempAttachedActors().Clear();

		Util::Dictionary< Util::Guid, AttachedActorInfo > tempAttach;

		for(int i=0; i<attachCount; ++i)
		{
			Util::String actorGUID;
			pReader->SerializeString(s_AttachedActorGUID, actorGUID);
			Util::String skelName;
			pReader->SerializeString(s_AttachedSkelName, skelName);
			Math::matrix44 trans;
			pReader->SerializeMatrix44(s_AttachedActorTrans, trans);

			Util::Guid guid;
			guid = Util::Guid::FromString(actorGUID);

			AttachedActorInfo attachInfo;
			attachInfo.attachedActorTrans = trans;
			attachInfo.attachedSkelName = skelName;

			tempAttach.Add(guid,attachInfo);

		}

		m_Object->SetTempAttachedActors(tempAttach);

	}

	void AnimationComponentSerialization::Load_4(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_3(pReader, args);
		Util::String defaultAnim;
		pReader->SerializeString(s_DefaultAnimName, defaultAnim);
		m_Object->SetDefaultAnimName(defaultAnim);
	}

	void AnimationComponentSerialization::Save(AppWriter* pWriter) const
	{	
		SizeT count = m_Object->GetAnimResCount();
		pWriter->SerializeInt(s_AnimCount, count);

		for (int i = 0; i<count; ++i)
		{
			//const Resources::ResourceId& animID = m_Object->GetAnimResID(i);
			Util::String animID = m_Object->GetAnimResID(i).AsString();
			animID.ReplaceChars("\\", '/');
			n_assert(animID.IsValid());
			pWriter->SerializeString(s_Animation, animID);
			int wrapMode = m_Object->GetWrapMode(animID);
			pWriter->SerializeInt(s_WrpaMode,wrapMode);
			float speed = m_Object->GetAnimationSpeed(animID);
			pWriter->SerializeFloat(s_AnimationSpeed,speed);
		}

		SizeT attachCount = 0;
		pWriter->SerializeInt(s_AttachedActorCount, attachCount);

		pWriter->SerializeString(s_DefaultAnimName, m_Object->GetDefaultAnimName().AsString());
	}
}

namespace App
{
	Version AnimationComponent::GetVersion() const
	{
		return 4;
	}

	void AnimationComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		AnimationComponentSerialization Serialize(this);
		Serialize.Load(ver, pReader, args);
	}

	void AnimationComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		AnimationComponentSerialization Serialize(const_cast<AnimationComponent*>(this));
		Serialize.Save(pWriter);
	}

}



