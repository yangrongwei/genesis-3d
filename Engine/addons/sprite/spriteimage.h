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
#ifndef __SPRITE_IMAGE_H__
#define __SPRITE_IMAGE_H__
#include "foundation/math/size.h"
#include "resource/resource.h"
#include "sprite/spriteobject.h"


namespace Resources
{
	class TextureResInfo;
}

namespace Sprite
{
	class SpriteImage : public SpriteObject
	{
		__DeclareSubClass(SpriteImage, SpriteObject)
	public:
		typedef GPtr<Resources::TextureResInfo> TextureResPtr;
		SpriteImage();
		virtual ~SpriteImage();
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		TextureResPtr GetTextureRes() const;

		void RemoveTextureID();
		void SetTextureID(const Resources::ResourceId& id, const Math::sizef& size, Resources::Priority priority);
		void SetPixelSize(const Math::sizef& size);
		void SetName(const Util::String& name);
		void SetTileNum(int rowNum, int colNum);
		int GetTileRowNum() const;
		int GetTileColNum() const;

		const Util::String& GetName() const;
		const Math::sizef& GetPixelSize() const;

		void PushTexture();

		bool Empty() const;

	private:
		void _setTextureID(const Resources::ResourceId& id, Resources::Priority priority);
		TextureResPtr mTextureRes;
		Util::String mName;
		Math::sizef mPixelSize;
		int mRowNum;
		int mColNum;
		static const uint sVersion;
	};

	inline SpriteImage::TextureResPtr SpriteImage::GetTextureRes() const
	{
		return mTextureRes;
	}

	inline const Math::sizef& SpriteImage::GetPixelSize() const
	{
		return mPixelSize;
	}

	inline void SpriteImage::SetPixelSize(const Math::sizef& size)
	{
		mPixelSize = size;
		__SPRITE_OBJECT_CHANGE__
	}

	inline const Util::String& SpriteImage::GetName() const
	{
		return mName;
	}

	inline void SpriteImage::SetName(const Util::String& name)
	{
		mName = name;
	}

	inline void SpriteImage::SetTileNum(int rowNum, int colNum)
	{
		mRowNum = rowNum;
		mColNum = colNum;
	}

	inline int SpriteImage::GetTileRowNum() const
	{
		return mRowNum;
	}

	inline int SpriteImage::GetTileColNum() const
	{
		return mColNum;
	}

	inline bool SpriteImage::Empty() const
	{
		return (!mTextureRes.isvalid());
	}
}

#endif //__SPRITE_IMAGE_H__