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
#ifndef __SPRITE_OBJECT_H__
#define __SPRITE_OBJECT_H__
#include "foundation/core/refcounted.h"
#include "serialization/serialize.h"
#include "sprite/spritedef.h"

namespace Sprite
{
	class SpriteVertexUnit;
	class SpriteBlock;
	class SpriteImage;
	class SpritePackage;
	class _sprite_vertex;


#define	__SaveSuper(writer) SpriteObject::saveSuper<Super>(writer, this);
#define	__LoadSuper(reader) SpriteObject::loadSuper<Super>(reader, this);
#ifdef __SPRITE_CHECK__
#define __SPRITE_OBJECT_CHANGE__ objectChange();
#define __SPRITE_CHANGE__ 	if(mParent){mParent->_Dirty();}
#else
#define __SPRITE_OBJECT_CHANGE__
#define __SPRITE_CHANGE__
#endif


	class SpriteObject : public Core::RefCounted
	{
		__DeclareClass(SpriteObject);
	public:
		SpriteObject();
		virtual ~SpriteObject();
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		void _SetParent(SpritePackage* parent);
	protected:

		template <typename T>
		static void saveSuper(GPtr<Serialization::SerializeWriter>& pWriter, const T* obj);
		template <typename T>
		static void loadSuper(const GPtr<Serialization::SerializeReader>& pReader, T* obj);

		SpritePackage* mParent;

		static const uint sVersion;
		const static int DestroyFlagInt;

#ifdef __SPRITE_CHECK__
	public:
		change_count getChangeCount() const;
		void objectChange();
	protected:

		change_count mChangeCount;
#endif //__SPRITE_CHECK__

	};

	inline void SpriteObject::_SetParent(SpritePackage* parent)
	{
		mParent = parent;
	}

	template <typename T>
	inline void SpriteObject::saveSuper(GPtr<Serialization::SerializeWriter>& pWriter,  const T* obj)
	{
		pWriter->BeginSerializeObject(T::RTTI.GetFourCC());//fourcc
		obj->T::Save(pWriter);
		pWriter->EndSerializeObject();
	}

	template <typename T>
	inline void SpriteObject::loadSuper(const GPtr<Serialization::SerializeReader>& pReader, T* obj)
	{
		Util::FourCC fourcc;
		pReader->BeginSerializeObject(fourcc);
		obj->T::Load(pReader);
		pReader->EndSerializeObject();
	}
#ifdef __SPRITE_CHECK__
	inline void SpriteObject::objectChange()
	{
		++mChangeCount;
	}

	inline change_count SpriteObject::getChangeCount() const
	{
		return mChangeCount;
	}
#endif
}

#endif //__SPRITE_OBJECT_H__
