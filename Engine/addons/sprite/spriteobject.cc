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
#include "serialization/serialize.h"
#include "spriteobject.h"


namespace Sprite
{
	const uint SpriteObject::sVersion = 1;
	const int SpriteObject::DestroyFlagInt = -1111;

	__ImplementClass(SpriteObject,'SPOB', Core::RefCounted);

	SpriteObject::SpriteObject()
		:mParent(NULL)
#ifdef __SPRITE_CHECK__
		,mChangeCount(default_change_count)
#endif //__SPRITE_CHECK__
	{

	}

	SpriteObject::~SpriteObject()
	{

	}

	void SpriteObject::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);
	}

	void SpriteObject::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);
	}

	void SpriteObject::CopyFrom(const GPtr<SpriteObject>& obj)
	{
#ifdef __SPRITE_CHECK__
		mChangeCount = obj->mChangeCount;
		__SPRITE_OBJECT_CHANGE__
#endif // _DEBUG
			mParent = NULL;
		/// empty.
	}


}