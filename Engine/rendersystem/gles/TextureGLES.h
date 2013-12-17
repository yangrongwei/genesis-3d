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

#ifndef __TextureGLES_H__
#define __TextureGLES_H__

#include "base/Texture.h"
#include "OpenGLES.h"
#include "util/dictionary.h"

namespace GLES
{
	struct TexInfo 
	{
		IndexT width;
		IndexT height;
	};

	class TextureGLES: public RenderBase::Texture
{
	__DeclareSubClass(TextureGLES, RenderBase::Texture );

public:
	TextureGLES();

	virtual ~TextureGLES();

	/// unload the resource, or cancel the pending load
	void Unload();

	// RenderBase::Texture::Setup
	void Setup(const GPtr<RenderBase::Texture>& srcTex);

	/// load Buffers;
	bool LoadBuffers();
	GLuint GetGLESTexture() const;
	void UpdateTexture(UpdateFunction texUpdateFunc, void* tag);
	void SetupFromGLESTexture(const GLuint& glTex);

	const bool IsUseMipMap() const;

	void ClearDummy();

	///// map the a texture mip level for CPU access
	virtual bool Map(IndexT mipLevel, MapType mapType, MapInfo& outMapInfo);
	///// unmap texture after CPU access
	virtual void Unmap(IndexT mipLevel);
	///// map a cube map face for CPU access
	virtual bool MapCubeFace(CubeFace face, IndexT mipLevel, MapType mapType, MapInfo& outMapInfo);
	///// unmap cube map face after CPU access
	virtual void UnmapCubeFace(CubeFace face, IndexT mipLevel);

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

	void SetTexAddresingModeU(IndexT u);

	IndexT GetTexAddresingModeU() const;

	void SetTexAddresingModeV(IndexT v);

	IndexT GetTexAddresingModeV() const;

	void SetTexFilterOp(IndexT texop);

	IndexT GetTexFilterOp() const;

protected:
	bool _LoadNormBuffer(ubyte* src, SizeT size );
	bool _LoadNormErrorBuffer();
	bool _LoadCubeBuffer(ubyte* src, SizeT size);
	bool _LoadCubeErrorBuffer();

	void _DeleteTextureObject();
	void _CreateTextureObject();

protected:
	GLuint m_textureGLES;
	bool   m_bMipMap;
	bool   m_bAttachedFBO;
	Util::Dictionary<IndexT, TexInfo> m_TextureMipmapInfo;

	IndexT m_CurrentAddresingModeU;
	IndexT m_CurrentAddresingModeV;
	IndexT m_CurrentTexFilterOp;
};

inline GLuint TextureGLES::GetGLESTexture() const
{
	return m_textureGLES;
}

inline void TextureGLES::SetupFromGLESTexture(const GLuint& glTex)
{
	n_assert(glTex != 0);

	m_textureGLES = glTex;
	this->SetType(Texture2D);

	m_bAttachedFBO = true;
}

inline const bool TextureGLES::IsUseMipMap() const
{
	return m_bMipMap;
}

inline void TextureGLES::ClearDummy()
{
	if (m_bAttachedFBO)
	{
		m_textureGLES = 0;
	}
}

inline void TextureGLES::SetTexAddresingModeU(IndexT u)
{
	m_CurrentAddresingModeU = u;
}

inline IndexT TextureGLES::GetTexAddresingModeU() const
{
	return m_CurrentAddresingModeU;
}

inline void TextureGLES::SetTexAddresingModeV(IndexT v)
{
	m_CurrentAddresingModeV = v;
}

inline IndexT TextureGLES::GetTexAddresingModeV() const
{
	return m_CurrentAddresingModeV;
}

inline void TextureGLES::SetTexFilterOp(IndexT texop)
{
	m_CurrentTexFilterOp = texop;
}

inline IndexT TextureGLES::GetTexFilterOp() const
{
	return m_CurrentTexFilterOp;
}

}


#endif