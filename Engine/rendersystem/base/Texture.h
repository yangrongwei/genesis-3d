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
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include "RenderDeviceTypes.h"
#include "RenderCommandType.h"
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace RenderBase
{
class Texture : public RenderCommandType
{
    __DeclareSubClass(Texture,RenderCommandType);
public:

    /// texture types
    enum Type
    {
        InvalidType,

        Texture2D,      //> a 2-dimensional texture
        Texture3D,      //> a 3-dimensional texture
        TextureCube,    //> a cube texture
    };

    /// cube map face
    enum CubeFace
    {
        PosX = 0,
        NegX,
        PosY,
        NegY,
        PosZ,
        NegZ,
    };

    /// access info filled by Map methods
    class MapInfo
    {
    public:
        /// constructor
        MapInfo() : data(0), rowPitch(0), depthPitch(0) {};
        
        void* data;
        SizeT rowPitch;
        SizeT depthPitch;
    };

	typedef void (*UpdateFunction)(MapInfo& texMap,int width,int height, int depth, PixelFormat::Code format, int mipLevel, void* tag);

    /// constructor
    Texture();
    /// destructor
    virtual ~Texture();

	/// init func
	void Setup();


	/// set texture type
	void SetType(Type t);
    /// get texture type
    Type GetType() const;

	/// set texture width
	void SetWidth(SizeT w);
    /// get width of texture 
    SizeT GetWidth() const;

	/// set texture height
	void SetHeight(SizeT h);
    /// get height of texture (if 2d or 3d texture)
    SizeT GetHeight() const;

	/// set texture depth
	void SetDepth(SizeT d);
    /// get depth of texture (if 3d texture)
    SizeT GetDepth() const;

	/// set number of mip levels
	void SetNumMipLevels(SizeT n);
    /// get number of mip levels
    SizeT GetNumMipLevels() const;

	/// set pixel format
	void SetPixelFormat(PixelFormat::Code f);
    /// get pixel format of the texture
    PixelFormat::Code GetPixelFormat() const;
	
	SizeT GetSize() const;
    
    void SetSize( const SizeT& s );

    /// set number of currently skipped mip levels
    void SetSkippedMips(SizeT m);
    /// get number of currently skipped mip levels
    SizeT GetSkippedMips() const;

	/// set texture unit
	void SetUnitIndex(SizeT i);
	/// get index of texture unit 
	SizeT GetUnitIndex() const;

	/// set texture path
	void SetTexturePath(const ResourcePath& path);
	/// get texture path
	const ResourcePath& GetTexturePath() const;

	/// set stream for store the image data
	void SetStream(GPtr<IO::Stream> stream);
	/// get stream
	GPtr<IO::Stream> GetStream();

    /// map the a texture mip level for CPU access
    virtual bool Map(IndexT mipLevel, Access accessMode, MapInfo& outMapInfo);
    /// unmap texture after CPU access
    virtual void Unmap(IndexT mipLevel);
    /// map a cube map face for CPU access
    virtual bool MapCubeFace(CubeFace face, IndexT mipLevel, Access accessMode, MapInfo& outMapInfo);
    /// unmap cube map face after CPU access
    virtual void UnmapCubeFace(CubeFace face, IndexT mipLevel);

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

protected:

    Type type;
    SizeT width;
    SizeT height;
    SizeT depth;
    SizeT numMipLevels;
    SizeT skippedMips;
	SizeT memorySize;
    PixelFormat::Code pixelFormat;
	SizeT m_unitIndex;

	ResourcePath m_texPath;
	GPtr<IO::Stream> m_stream;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetType(Type t)
{
    this->type = t;
}

//------------------------------------------------------------------------------
/**
*/
inline Texture::Type
Texture::GetType() const
{
    return this->type;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetWidth(SizeT w)
{
    this->width = w;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetWidth() const
{
    return this->width;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetHeight(SizeT h)
{
    this->height = h;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetHeight() const
{
    return this->height;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetDepth(SizeT d)
{
    this->depth = d;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetDepth() const
{
    return this->depth;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetSize() const
{
	return memorySize;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetNumMipLevels(SizeT n)
{
    this->numMipLevels = n;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetNumMipLevels() const
{
    return this->numMipLevels;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetSkippedMips(SizeT m)
{
    this->skippedMips = m;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
Texture::GetSkippedMips() const
{
    return this->skippedMips;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::SetPixelFormat(PixelFormat::Code f)
{
    this->pixelFormat = f;
}

//------------------------------------------------------------------------------
/**
*/
inline PixelFormat::Code
Texture::GetPixelFormat() const
{
    return this->pixelFormat;
}

inline void Texture::SetTexturePath(const ResourcePath& path)
{
	m_texPath = path;
}

inline const ResourcePath& Texture::GetTexturePath() const
{
	return m_texPath;
}

inline void Texture::SetStream(GPtr<IO::Stream> stream)
{
	m_stream = stream;
}

inline GPtr<IO::Stream> Texture::GetStream()
{
	return m_stream;
}

inline void Texture::SetUnitIndex(SizeT i)
{
	m_unitIndex = i;
}

inline SizeT Texture::GetUnitIndex() const
{
	return m_unitIndex;
}
    
    inline void Texture::SetSize( const SizeT& s )
    {
        memorySize = s;
    }

} // namespace RenderBase
//------------------------------------------------------------------------------
#endif