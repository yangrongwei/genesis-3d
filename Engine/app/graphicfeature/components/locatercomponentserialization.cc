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
#include "graphicfeature/components/locatercomponent.h"

namespace App
{
	class LocaterComponentSerialization
	{
	public:
		LocaterComponentSerialization(LocaterComponent* pComponent);
		~LocaterComponentSerialization();

	public:
		void Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_1(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Save(AppWriter* pWriter) const;

	protected:
		LocaterComponent* m_Object;
	};

	const char* s_AttachedName   = "AttachedName";
	const char* s_RelativeTrans      = "RelativeTrans";

	LocaterComponentSerialization::LocaterComponentSerialization(LocaterComponent* pComponent)
		: m_Object(pComponent)
	{

	}

	LocaterComponentSerialization::~LocaterComponentSerialization()
	{

	}

	void LocaterComponentSerialization::Load(Version ver, AppReader *pReader, const Serialization::SerializationArgs* args)
	{
		if (ver == 1)
		{
			Load_1(pReader, args);
		}
		else
			n_error(" SceneSerialization::Load unknown version " );
	}

	void LocaterComponentSerialization::Load_1(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Util::String attachedSkelName;
		pReader->SerializeString(s_AttachedName, attachedSkelName);

		m_Object->SetAttachedSkelName(attachedSkelName);

		Math::matrix44 relativeTrans;
		pReader->SerializeMatrix44(s_RelativeTrans, relativeTrans);

		m_Object->SetRelativeTrans(relativeTrans);
	}

	void LocaterComponentSerialization::Save(AppWriter* pWriter) const
	{
		pWriter->SerializeString(s_AttachedName, m_Object->GetAttachedSkelName());

		pWriter->SerializeMatrix44(s_RelativeTrans, m_Object->GetRelativeTrans());
	}

	Version LocaterComponent::GetVersion() const
	{
		return 1;
	}

	void LocaterComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		LocaterComponentSerialization Serialize(this);
		Serialize.Load(ver, pReader, args);
	}

	void LocaterComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		LocaterComponentSerialization Serialize(const_cast<LocaterComponent*>(this));
		Serialize.Save(pWriter);
	}


}

