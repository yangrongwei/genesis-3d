/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef _TEXTURED3D9_H_
#define _TEXTURED3D9_H_
#include "rendersystem/base/Texture.h"
namespace D3D9
{
	using namespace RenderBase;

	class TextureD3D9 : public Texture
	{
		__DeclareSubClass(TextureD3D9,Texture)
	public:
		TextureD3D9();
		virtual ~TextureD3D9();
		
		/// unload the resource, or cancel the pending load
		void Unload();
		/// map a texture mip level for CPU access
		bool Map(IndexT mipLevel, MapType mapType, MapInfo& outMapInfo);
		/// unmap texture after CPU access
		void Unmap(IndexT mipLevel);
		/// map a cube map face for CPU access
		bool MapCubeFace(CubeFace face, IndexT mipLevel, MapType mapType, MapInfo& outMapInfo);
		/// unmap cube map face after CPU access
		void UnmapCubeFace(CubeFace face, IndexT mipLevel);

		/// get d3d9 base texture pointer
		IDirect3DBaseTexture9* GetD3D9BaseTexture() const;
		/// get d3d9 texture pointer
		IDirect3DTexture9* GetD3D9Texture() const;
		/// get d3d9 cube texture pointer
		IDirect3DCubeTexture9* GetD3D9CubeTexture() const;
		/// get d3d9 volume texture pointer
		IDirect3DVolumeTexture9* GetD3D9VolumeTexture() const;

		/// setup from a IDirect3DTexture9
		void SetupFromD3D9Texture(IDirect3DTexture9* ptr, const bool setLoaded = true);
		/// setup from a IDirect3DCubeTexture
		void SetupFromD3D9CubeTexture(IDirect3DCubeTexture9* ptr, const bool setLoaded = true);
		/// setup from a IDirect3DVolumeTexture
		void SetupFromD3D9VolumeTexture(IDirect3DVolumeTexture9* ptr, const bool setLoaded = true);

		/// load Buffers;
		bool LoadBuffers();
		IDirect3DTexture9* _LoadNormBuffer(ubyte* src, SizeT size );
		IDirect3DTexture9* _LoadNormErrorBuffer();
		IDirect3DCubeTexture9* _LoadCubeBuffer(ubyte* src, SizeT size);
		IDirect3DCubeTexture9* _LoadCubeErrorBuffer();

		IDirect3DVolumeTexture9* _LoadVolumeBuffer(ubyte* src, SizeT size );
		IDirect3DVolumeTexture9* _LoadVolumeErrorBuffer();

		/// load from file
		bool LoadFileFromBuffers();

		D3DPOOL GetD3D9PoolType();

		/// 
		void UpdateTexture(UpdateFunction texUpdateFunc, void* tag);
		void UpdateTexture(GPtr<Texture> srcTex);
		void Setup(const GPtr<Texture>& srcTex);
		virtual void OnDeviceLost();
		virtual void OnDeviceReset();
		

		bool GetTextureData(ubyte* data) const;
		const SizeT GetTextureSize() const;

		void GenerateCubeMap(const TextureD3D9& texFront,const TextureD3D9& texBack,const TextureD3D9& texTop,const TextureD3D9& texUnder,const TextureD3D9& texLeft,const TextureD3D9& texRight);
		void GenerateCubeMapData( ubyte* srcData,const TextureD3D9& texFront,const TextureD3D9& texBack,const TextureD3D9& texTop,const TextureD3D9& texUnder,const TextureD3D9& texLeft,const TextureD3D9& texRight );

	protected:
		bool __GetNormalData(ubyte* data) const;
		void __GetCubeData(ubyte* data) const;


		IDirect3DBaseTexture9* d3d9BaseTexture;
		int mapCount;

		IDirect3DTexture9* d3d9Texture;                 // valid if type is Texture2D
		IDirect3DCubeTexture9* d3d9CubeTexture;         // valid if type is TextureCube
		IDirect3DVolumeTexture9* d3d9VolumeTexture;     // valid if type is Texture3D
		D3DPOOL d3dpoolType;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DBaseTexture9*
		TextureD3D9::GetD3D9BaseTexture() const
	{
		n_assert(0 != this->d3d9BaseTexture);
		n_assert(0 == this->mapCount);
		return this->d3d9BaseTexture;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DTexture9*
		TextureD3D9::GetD3D9Texture() const
	{
		// need to use QueryInterface()'d pointer under Win32
		n_assert(0 != this->d3d9Texture);
		return this->d3d9Texture;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DCubeTexture9*
		TextureD3D9::GetD3D9CubeTexture() const
	{
		// need to use QueryInterface()'d pointer under Win32
		n_assert(0 != this->d3d9CubeTexture);
		return this->d3d9CubeTexture;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DVolumeTexture9*
		TextureD3D9::GetD3D9VolumeTexture() const
	{
		// need to use QueryInterface()'d pointer under Win32
		n_assert(0 != this->d3d9VolumeTexture);
		return this->d3d9VolumeTexture;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline D3DPOOL TextureD3D9::GetD3D9PoolType()
	{
		return d3dpoolType;
	}

}
#endif