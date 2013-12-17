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
#include "graphicfeature/components/skeletoncomponent.h"

namespace App
{
	class SkeletonComponentSerialization
	{
	public:
		SkeletonComponentSerialization(SkeletonComponent* pComponent);
		~SkeletonComponentSerialization();

	public:
		void Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_1(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Save(AppWriter* pWriter) const;

	protected:
		SkeletonComponent* m_Object;
	};

	const char* s_Skeleton      = "Skeleton";
	const char* s_SkeletonDummy = "EmptyNull";

	SkeletonComponentSerialization::SkeletonComponentSerialization(SkeletonComponent* pComponent)
		: m_Object(pComponent)
	{

	}

	SkeletonComponentSerialization::~SkeletonComponentSerialization()
	{

	}

	void SkeletonComponentSerialization::Load(Version ver, AppReader *pReader, const Serialization::SerializationArgs* args)
	{
		if (ver == 1)
		{
			Load_1(pReader, args);
		}
		else
			n_error(" SceneSerialization::Load unknown version " );
	}

	void SkeletonComponentSerialization::Load_1(AppReader* pReader, const Serialization::SerializationArgs* args)
	{

		Util::String skeletonName;
		pReader->SerializeString(s_Skeleton, skeletonName);

		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();
		Resources::Priority priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::SkeletonDefault : cargs->getPriority();
		if (skeletonName != s_SkeletonDummy)
		{
			m_Object->SetSkeletonID(skeletonName);
		}

	}

	void SkeletonComponentSerialization::Save(AppWriter* pWriter) const
	{
		if (m_Object->GetSkeletonID().IsValid())
		{
			pWriter->SerializeString(s_Skeleton, m_Object->GetSkeletonID().AsString());
		} 
		else
		{
			pWriter->SerializeString(s_Skeleton, Util::String(s_SkeletonDummy));
		}

	}

	Version SkeletonComponent::GetVersion() const
	{
		return 1;
	}

	void SkeletonComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SkeletonComponentSerialization Serialize(this);
		Serialize.Load(ver, pReader, args);
	}

	void SkeletonComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SkeletonComponentSerialization Serialize(const_cast<SkeletonComponent*>(this));
		Serialize.Save(pWriter);
	}


}

