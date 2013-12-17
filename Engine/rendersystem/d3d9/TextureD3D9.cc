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

#if WIN32



#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "TextureD3D9.h"
#include "D3D9Types.h"
#include "RenderDeviceD3D9.h"
#include "io/ioserver.h"
#include "io/uri.h"
#include "util/algorithm.h"

//#include <dxerr9.h>

namespace D3D9
{
	__ImplementClass(TextureD3D9,'TTD9',Texture)

		TextureD3D9::TextureD3D9():
	d3d9BaseTexture(0),
		d3d9Texture(0),
		d3d9CubeTexture(0),
		d3d9VolumeTexture(0),
		mapCount(0),
		d3dpoolType(D3DPOOL_MANAGED)
	{
		// empty
	}
	TextureD3D9::~TextureD3D9()
	{
		Unload();
		n_assert(0 == this->d3d9BaseTexture);
		n_assert(0 == this->mapCount);
		n_assert(0 == this->d3d9Texture);
		n_assert(0 == this->d3d9CubeTexture);
		n_assert(0 == this->d3d9VolumeTexture);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		TextureD3D9::Unload()
	{
		n_assert(0 == this->mapCount);
		if (0 != this->d3d9BaseTexture)
		{
			this->d3d9BaseTexture->Release();
			this->d3d9BaseTexture = 0;
		}
		if (0 != this->d3d9Texture)
		{
			this->d3d9Texture->Release();
			this->d3d9Texture = 0;
		}
		if (0 != this->d3d9CubeTexture)
		{
			this->d3d9CubeTexture->Release();
			this->d3d9CubeTexture = 0;
		}
		if (0 != this->d3d9VolumeTexture)
		{
			this->d3d9VolumeTexture->Release();
			this->d3d9VolumeTexture = 0;
		}

		d3dpoolType = D3DPOOL_MANAGED;

		PROFILER_ADDDEVICESTATEVAL(videoRam, -memorySize);
		PROFILER_ADDDEVICESTATEVAL(texRam, -memorySize );
		PROFILER_ADDDEVICESTATEVAL(textureNum, -1);		
		memorySize = 0;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		TextureD3D9::Map(IndexT mipLevel, MapType mapType, MapInfo& outMapInfo)
	{
		n_assert((this->type == Texture2D) || (this->type == Texture3D));
		n_assert(MapWriteNoOverwrite != mapType);
		bool retval = false;
		DWORD lockFlags = 0;
		if (Texture2D == this->type)
		{
			D3DLOCKED_RECT lockedRect = { 0 };
			HRESULT hr = this->GetD3D9Texture()->LockRect(mipLevel, &lockedRect, NULL, lockFlags);
			if (SUCCEEDED(hr))
			{
				outMapInfo.data = lockedRect.pBits;
				outMapInfo.rowPitch = lockedRect.Pitch;
				outMapInfo.depthPitch = 0;
				retval = true;
			}
		}
		else if (Texture3D == this->type)
		{
			D3DLOCKED_BOX lockedBox = { 0 };
			HRESULT hr = this->GetD3D9VolumeTexture()->LockBox(mipLevel, &lockedBox, NULL, lockFlags);
			if (SUCCEEDED(hr))
			{
				outMapInfo.data = lockedBox.pBits;
				outMapInfo.rowPitch = lockedBox.RowPitch;
				outMapInfo.depthPitch = lockedBox.SlicePitch;
				retval = true;
			}
		}
		if (retval)
		{
			this->mapCount++;
		}
		return retval;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		TextureD3D9::Unmap(IndexT mipLevel)
	{
		n_assert(this->mapCount > 0);
		n_assert((Texture2D == this->type) || (Texture3D == this->type));
		if (Texture2D == this->type)
		{
			this->GetD3D9Texture()->UnlockRect(mipLevel);
		}
		else if (Texture3D == this->type)
		{
			this->GetD3D9VolumeTexture()->UnlockBox(mipLevel);
		}
		this->mapCount--;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		TextureD3D9::MapCubeFace(CubeFace face, IndexT mipLevel, MapType mapType, MapInfo& outMapInfo)
	{
		n_assert(TextureCube == this->type);
		n_assert(MapWriteNoOverwrite != mapType);
		DWORD lockFlags = D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK;
		switch (mapType)
		{
		case MapRead:
			n_assert((UsageDynamic == this->usage) && (AccessRead == this->access));
			lockFlags |= D3DLOCK_READONLY;
			break;
		case MapWrite:
			n_assert((UsageDynamic == this->usage) && (AccessWrite == this->access));
			break;
		case MapReadWrite:
			n_assert((UsageDynamic == this->usage) && (AccessReadWrite == this->access));
			break;
		case MapWriteDiscard:
			n_assert((UsageDynamic == this->usage) && (AccessWrite == this->access));
			lockFlags |= D3DLOCK_DISCARD;
			break;
		}
		D3DCUBEMAP_FACES d3d9Face = (D3DCUBEMAP_FACES) face;
		D3DLOCKED_RECT lockedRect = { 0 };
		HRESULT hr = this->GetD3D9CubeTexture()->LockRect(d3d9Face, mipLevel, &lockedRect, NULL, lockFlags);
		if (SUCCEEDED(hr))
		{
			outMapInfo.data = lockedRect.pBits;
			outMapInfo.rowPitch = lockedRect.Pitch;
			outMapInfo.depthPitch = 0;
			this->mapCount++;
			return true;
		}
		else
		{
			return false;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		TextureD3D9::UnmapCubeFace(CubeFace face, IndexT mipLevel)
	{
		n_assert(TextureCube == this->type);
		n_assert(this->mapCount > 0);
		D3DCUBEMAP_FACES d3d9Face = (D3DCUBEMAP_FACES) face;
		this->GetD3D9CubeTexture()->UnlockRect(d3d9Face, mipLevel);
		this->mapCount--;
	}
	//------------------------------------------------------------------------------
	/**
	Helper method to setup the texture object from a D3D9 2D texture.
	*/
	void
		TextureD3D9::SetupFromD3D9Texture(IDirect3DTexture9* tex2D, const bool setLoaded)
	{
		n_assert(0 != tex2D);    
		HRESULT hr;

		// need to query for base interface under Win32
		this->d3d9Texture = tex2D;
		hr = d3d9Texture->QueryInterface(IID_IDirect3DBaseTexture9, (void**) &this->d3d9BaseTexture);
		n_assert(SUCCEEDED(hr));

		this->SetType(Texture2D);
		D3DSURFACE_DESC desc;
		Memory::Clear(&desc, sizeof(desc));
		hr = tex2D->GetLevelDesc(0, &desc);
		n_assert(SUCCEEDED(hr));
		this->SetWidth(desc.Width);
		this->SetHeight(desc.Height);
		this->SetDepth(1);
		this->SetNumMipLevels(tex2D->GetLevelCount());
		this->SetPixelFormat(D3D9Types::AsGenesisPixelFormat(desc.Format));
		this->d3dpoolType = desc.Pool;

	}

	//------------------------------------------------------------------------------
	/**
	Helper method to setup the texture object from a D3D9 volume texture.
	*/
	void
		TextureD3D9::SetupFromD3D9VolumeTexture(IDirect3DVolumeTexture9* texVolume, const bool setLoaded)
	{
		n_assert(0 != texVolume);
		HRESULT hr;

		this->d3d9VolumeTexture = texVolume;
		hr = texVolume->QueryInterface(IID_IDirect3DBaseTexture9, (void**) &this->d3d9BaseTexture);
		n_assert(SUCCEEDED(hr));

		this->SetType(Texture3D);
		D3DVOLUME_DESC desc;
		Memory::Clear(&desc, sizeof(desc));
		hr = texVolume->GetLevelDesc(0, &desc);
		n_assert(SUCCEEDED(hr));
		this->SetWidth(desc.Width);
		this->SetHeight(desc.Height);
		this->SetDepth(desc.Depth);
		this->SetNumMipLevels(texVolume->GetLevelCount());
		this->SetPixelFormat(D3D9Types::AsGenesisPixelFormat(desc.Format));
		this->d3dpoolType = desc.Pool;

	}

	//------------------------------------------------------------------------------
	/**
	Helper method to setup the texture object from a D3D9 cube texture.
	*/
	void
		TextureD3D9::SetupFromD3D9CubeTexture(IDirect3DCubeTexture9* texCube, const bool setLoaded)
	{
		n_assert(0 != texCube);
		HRESULT hr;

		this->d3d9CubeTexture = texCube;
		hr = texCube->QueryInterface(IID_IDirect3DBaseTexture9, (void**) &this->d3d9BaseTexture);
		n_assert(SUCCEEDED(hr));

		this->SetType(TextureCube);
		D3DSURFACE_DESC desc;
		Memory::Clear(&desc, sizeof(desc));
		hr = texCube->GetLevelDesc(0, &desc);
		n_assert(SUCCEEDED(hr));
		this->SetWidth(desc.Width);
		this->SetHeight(desc.Height);
		this->SetDepth(1);
		this->SetNumMipLevels(texCube->GetLevelCount());
		this->SetPixelFormat(D3D9Types::AsGenesisPixelFormat(desc.Format));
		this->d3dpoolType = desc.Pool;

	}
	bool TextureD3D9::LoadFileFromBuffers()
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		GPtr<IO::Stream> stream = m_stream;

		stream->SetAccessMode(IO::Stream::ReadAccess);
		if (stream->Open())
		{
			void* srcData = stream->Map();
			UINT srcDataSize = stream->GetSize();

			HRESULT hr = S_FALSE;
			// first need to check image info whether to determine texture type
			D3DXIMAGE_INFO imageInfo = { 0 };
			hr = D3DXGetImageInfoFromFileInMemory(srcData, srcDataSize, &imageInfo);
			if (FAILED(hr))
			{
				n_error("TextureD3D9::LoadFileFromBuffers: failed to obtain image info from file '%s'!", m_texPath.Value());
				return false;
			}

			// load texture based on texture type
			if (D3DRTYPE_TEXTURE == imageInfo.ResourceType)
			{
				// load 2D texture
				IDirect3DTexture9* d3d9Texture = 0;
				hr = device->D3DXCreateTextureFromFileInMemory(srcData, srcDataSize, &d3d9Texture);
				if (FAILED(hr))
				{
					n_error("TextureD3D9::LoadFileFromBuffers: D3DXCreateTextureFromFileInMemory() failed for file '%s'!", m_texPath.Value());
					return false;
				}
				SetupFromD3D9Texture(d3d9Texture);
			}
			else if (D3DRTYPE_VOLUMETEXTURE == imageInfo.ResourceType)
			{
				// load 3D texture
				IDirect3DVolumeTexture9* d3d9VolumeTexture = 0;
				hr = device->D3DXCreateVolumeTextureFromFileInMemory(srcData, srcDataSize, &d3d9VolumeTexture);
				if (FAILED(hr))
				{
					n_error("TextureD3D9::LoadFileFromBuffers: D3DXCreateVolumeTextureFromFileInMemory() failed for file '%s'!", m_texPath.Value());
					return false;
				}
				SetupFromD3D9VolumeTexture(d3d9VolumeTexture);
			}
			else if (D3DRTYPE_CUBETEXTURE == imageInfo.ResourceType)
			{
				// load cube texture
				IDirect3DCubeTexture9* d3d9CubeTexture = 0;
				hr = device->D3DXCreateCubeTextureFromFileInMemory(srcData, srcDataSize, &d3d9CubeTexture);
				if (FAILED(hr))
				{
					n_error("D3D9StreamTextureLoader: D3DXCreateCubeTextureFromFileInMemory() failed for file '%s'!", m_texPath.Value());
					return false;
				}
				SetupFromD3D9CubeTexture(d3d9CubeTexture);
			}
			stream->Unmap();
			stream->Close();
			memorySize = PixelFormat::GetMemorySize(GetWidth(), GetHeight(), GetDepth(), GetPixelFormat());
			PROFILER_ADDDEVICESTATEVAL(videoRam, memorySize);
			PROFILER_ADDDEVICESTATEVAL(texRam, memorySize );
			PROFILER_ADDDEVICESTATEVAL(textureNum, 1);
			return true;
		}
		n_error("TextureD3D9::LoadFileFromBuffers failed for file '%s'!", m_texPath.Value());
		return false;
	}
	//------------------------------------------------------------------------
	inline void MoveCursorToNextMipMap (PixelFormat::Code format, ubyte*& srcData, SizeT& texWidth, SizeT& texHeight, SizeT texDepth = 1 )
	{
		srcData += PixelFormat::GetMemorySize(texWidth, texHeight, texDepth, format);
		texWidth =  Math::n_max( texWidth / 2, 1 );
		texHeight = Math::n_max( texHeight / 2, 1 );
	}
	//------------------------------------------------------------------------
	inline void BlitCopyImage( ubyte* dest, SizeT destRowPitch, SizeT destHeight,  
							   ubyte* src, SizeT srcRowPitch, SizeT srcHeight)
	{

		for ( IndexT hIndex = 0; hIndex < destHeight && hIndex < srcHeight; ++ hIndex )
		{
			SizeT copyRow = Math::n_min(destRowPitch,  srcRowPitch);
			Memory::Copy(src, dest, copyRow );
			dest += destRowPitch;
			src += srcRowPitch;
		}
	}
	//------------------------------------------------------------------------
	IDirect3DTexture9* 
	TextureD3D9::_LoadNormBuffer(ubyte* srcData, SizeT size )
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();

		if( GetDepth() != 1 || GetWidth() <= 0 || GetHeight() <= 0 )
		{
			return NULL;
		}

		if( !Util::IsPowerTwo( GetHeight() ) || !Util::IsPowerTwo( GetWidth() ) )
		{
			return NULL;
		}

		if( GetPixelFormat() == PixelFormat::InvalidPixelFormat )
		{
			return NULL;
		}

		SizeT texWidth = GetWidth();
		SizeT texHeight = GetHeight();
		SizeT texMipMap = GetNumMipLevels();	//	in d3d , this is count.
		PixelFormat::Code format = GetPixelFormat();
		D3DFORMAT d3d9Format = D3D9Types::AsD3D9PixelFormat( format );
		n_assert( d3d9Format != D3DFMT_UNKNOWN );

		IDirect3DTexture9* d3d9Texture = 0;
		d3dpoolType = D3DPOOL_MANAGED;
		HRESULT hr = device->CreateTexture( texWidth, texHeight, texMipMap,0, d3d9Format , d3dpoolType, &d3d9Texture, 0 );
		if (FAILED(hr))
		{
			const char* msg = DXGetErrorDescription9(hr);
			n_warning("TextureD3D9::_LoadNormBuffer: CreateTexture failed for file '%s'!", m_texPath.Value());
			return NULL;
		}

		if ( PixelFormat::IsCompressed( format ) )
		{
			// must be dxt
			for( int level = 0; level < texMipMap; ++level )
			{
				D3DLOCKED_RECT lockedRect = { 0 };
				HRESULT hr = d3d9Texture->LockRect( level, &lockedRect, NULL, 0 );
				if( FAILED(hr) )
				{
					n_warning("TextureD3D9::_LoadNormBuffer: CreateTexture LockRect % level failed for file '%s'!", level, m_texPath.Value());
					d3d9Texture->Release();
					return NULL;
				}

				// copy pixel
				SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);
				Memory::CopyToGraphicsMemory(srcData, lockedRect.pBits, levelPixelSize );

				d3d9Texture->UnlockRect(level);
				MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
			}
		}
		else
		{
			for( int level = 0; level < texMipMap; ++level )
			{
				D3DLOCKED_RECT lockedRect = { 0 };
				HRESULT hr = d3d9Texture->LockRect( level, &lockedRect, NULL, 0 );
				if( FAILED(hr) )
				{
					n_warning("TextureD3D9::_LoadNormBuffer: CreateTexture LockRect % level failed for file '%s'!", level, m_texPath.Value());
					d3d9Texture->Release();
					return NULL;
				}

				// copy pixel
				SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);
				BlitCopyImage( (ubyte*)lockedRect.pBits, lockedRect.Pitch, texHeight,
								srcData, srcRowPitch,  texHeight);

				d3d9Texture->UnlockRect(level);
				MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
			}
		}

		return d3d9Texture;
	}
	//------------------------------------------------------------------------
	IDirect3DTexture9* TextureD3D9::_LoadNormErrorBuffer()
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		IDirect3DTexture9* d3d9Texture = 0;
		d3dpoolType = D3DPOOL_MANAGED;
		HRESULT hr = device->CreateTexture( 1, 1, 1, 0, D3DFMT_A8R8G8B8 , d3dpoolType, &d3d9Texture, 0 );
		if (FAILED(hr))
		{
			n_error( "TextureD3D9::_LoadNormErrorBuffer Failed" );
			return NULL;
		}
		else
		{
			return d3d9Texture;
		}
	}
	//------------------------------------------------------------------------
	IDirect3DCubeTexture9* TextureD3D9::_LoadCubeBuffer(ubyte* srcCube, SizeT size)
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();

		if( GetDepth() != 1 || GetWidth() <= 0 || GetHeight() <= 0 )
		{
			return NULL;
		}

		if( !Util::IsPowerTwo( GetHeight() ) || !Util::IsPowerTwo( GetWidth() ) )
		{
			return NULL;
		}

		if( GetPixelFormat() == PixelFormat::InvalidPixelFormat )
		{
			return NULL;
		}

		if ( GetWidth() != GetHeight() )
		{
			return NULL;
		}

		SizeT cubeTexWidth = GetWidth();
		SizeT cubeTexHeight = GetHeight();
		SizeT cubeTexMipMap = GetNumMipLevels();	//	in d3d , this is count.
		PixelFormat::Code format = GetPixelFormat();
		D3DFORMAT d3d9Format = D3D9Types::AsD3D9PixelFormat( format );
		n_assert( d3d9Format != D3DFMT_UNKNOWN );

		IDirect3DCubeTexture9* d3d9Texture = 0;
		HRESULT hr = device->CreateCubeTexture( cubeTexWidth, cubeTexMipMap, 0, d3d9Format , D3DPOOL_MANAGED, &d3d9Texture, 0 );
		if (FAILED(hr))
		{
			const char* msg = DXGetErrorDescription9(hr);
			n_warning("TextureD3D9::_LoadCubeBuffer: CreateTexture failed for file '%s'!", m_texPath.Value());
			return NULL;
		}

		SizeT faceSize = 0;
		{
			SizeT cubeEdgeSize = cubeTexWidth;
			for( int level = 0; level < cubeTexMipMap; ++level )
			{
				faceSize += PixelFormat::GetMemorySize(cubeEdgeSize, cubeEdgeSize, 1, format);
				cubeEdgeSize =  Math::n_max( cubeEdgeSize / 2, 1 );
			}
		}

		if ( PixelFormat::IsCompressed( format ) )
		{
			for ( int face=0; face<6; ++face )
			{
				ubyte* faceData = srcCube + face*faceSize;
				SizeT texWidth = cubeTexWidth;
				SizeT texHeight = cubeTexHeight;

				// must be dxt
				for( int level = 0; level < cubeTexMipMap; ++level )
				{
					D3DLOCKED_RECT lockedRect = { 0 };
					HRESULT hr = d3d9Texture->LockRect( (D3DCUBEMAP_FACES)face, level, &lockedRect, NULL, 0 );
					if( FAILED(hr) )
					{
						n_warning("TextureD3D9::_LoadCubeBuffer: CreateTexture LockRect % level failed for file '%s'!", level, m_texPath.Value());
						d3d9Texture->Release();
						return NULL;
					}

					// copy pixel
					SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);
					Memory::CopyToGraphicsMemory(faceData, lockedRect.pBits, levelPixelSize );

					d3d9Texture->UnlockRect((D3DCUBEMAP_FACES)face,level);
					MoveCursorToNextMipMap(format, faceData, texWidth, texHeight );
				}
			}

		}
		else
		{
			for ( int face=0; face<6; ++face )
			{
				ubyte* faceData = srcCube + face*faceSize;
				SizeT texWidth = cubeTexWidth;
				SizeT texHeight = cubeTexHeight;

				for( int level = 0; level < cubeTexMipMap; ++level )
				{
					D3DLOCKED_RECT lockedRect = { 0 };
					HRESULT hr = d3d9Texture->LockRect( (D3DCUBEMAP_FACES)face,level, &lockedRect, NULL, 0 );
					if( FAILED(hr) )
					{
						n_warning("TextureD3D9::_LoadCubeBuffer: CreateTexture LockRect % level failed for file '%s'!", level, m_texPath.Value());
						d3d9Texture->Release();
						return NULL;
					}

					// copy pixel
					SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);
					BlitCopyImage( (ubyte*)lockedRect.pBits, lockedRect.Pitch, texHeight,
						faceData, srcRowPitch,  texHeight);

					d3d9Texture->UnlockRect((D3DCUBEMAP_FACES)face,level);
					MoveCursorToNextMipMap(format, faceData, texWidth, texHeight );
				}
			}
		}

		return d3d9Texture;
	}
	//------------------------------------------------------------------------
	IDirect3DCubeTexture9* TextureD3D9::_LoadCubeErrorBuffer()
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		IDirect3DCubeTexture9* d3d9Texture = 0;
		HRESULT hr = device->CreateCubeTexture( 1, 1, 0, D3DFMT_A8R8G8B8 , D3DPOOL_MANAGED, &d3d9Texture, 0 );
		if (FAILED(hr))
		{
			n_error( "TextureD3D9::_LoadCubeErrorBuffer Failed" );
			return NULL;
		}
		else
		{
			return d3d9Texture;
		}
	}
	//------------------------------------------------------------------------

	IDirect3DVolumeTexture9* TextureD3D9::_LoadVolumeBuffer( ubyte* src, SizeT size )
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();

		if(  GetWidth() <= 0 || GetHeight() <= 0 )
		{
			return NULL;
		}

		if( !Util::IsPowerTwo( GetHeight() ) || !Util::IsPowerTwo( GetWidth() ) )
		{
			return NULL;
		}

		if( GetPixelFormat() == PixelFormat::InvalidPixelFormat )
		{
			return NULL;
		}

		SizeT texWidth = GetWidth();
		SizeT texHeight = GetHeight();
		SizeT texMipMap = GetNumMipLevels();	//	in d3d , this is count.
		SizeT depth   = GetDepth();
		PixelFormat::Code format = GetPixelFormat();
		D3DFORMAT d3d9Format = D3D9Types::AsD3D9PixelFormat( format );
		n_assert( d3d9Format != D3DFMT_UNKNOWN );

		IDirect3DVolumeTexture9* d3d9Texture = 0;
		d3dpoolType = D3DPOOL_MANAGED;

		HRESULT hr = device->CreateVolumeTexture(texWidth,texHeight,depth,texMipMap,0, d3d9Format , d3dpoolType, &d3d9Texture, 0);

		if (FAILED(hr))
		{
			const char* msg = DXGetErrorDescription9(hr);
			n_warning("TextureD3D9::_LoadVolumeBuffer: CreateTexture failed for file '%s'!", m_texPath.Value());
			return NULL;
		}


		if ( PixelFormat::IsCompressed( format ) )
		{
			// must be dxt
			for( int level = 0; level < texMipMap; ++level )
			{
				//D3DLOCKED_RECT lockedRect = { 0 };
				D3DLOCKED_BOX lockedBox = {0};
				HRESULT hr = d3d9Texture->LockBox( level, &lockedBox, NULL, 0 );
				if( FAILED(hr) )
				{
					n_warning("TextureD3D9::_LoadNormBuffer: CreateTexture LockBox % level failed for file '%s'!", level, m_texPath.Value());
					d3d9Texture->Release();
					return NULL;
				}

				// copy pixel
				SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, depth, format);
				Memory::CopyToGraphicsMemory(src, lockedBox.pBits, levelPixelSize );

				d3d9Texture->UnlockBox(level);
				MoveCursorToNextMipMap(format, src, texWidth, texHeight );
			}
		}
		else
		{
			for( int level = 0; level < texMipMap; ++level )
			{
				//D3DLOCKED_RECT lockedRect = { 0 };
				D3DLOCKED_BOX lockedBox = {0};
				HRESULT hr = d3d9Texture->LockBox( level, &lockedBox, NULL, 0 );
				if( FAILED(hr) )
				{
					n_warning("TextureD3D9::_LoadNormBuffer: CreateTexture LockRect % level failed for file '%s'!", level, m_texPath.Value());
					d3d9Texture->Release();
					return NULL;
				}
				
				// copy pixel
				SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);


				ubyte* lockedBoxCopy =  (ubyte*)lockedBox.pBits;
				ubyte* srcCopy = src;
				for( int i=0 ; i<depth ; i++ )
				{
					BlitCopyImage( lockedBoxCopy, lockedBox.RowPitch, texHeight,
						srcCopy, srcRowPitch,  texHeight);
					lockedBoxCopy += lockedBox.SlicePitch;
					srcCopy       += srcRowPitch*texHeight;
				}
			
				d3d9Texture->UnlockBox(level);
				MoveCursorToNextMipMap(format, src, texWidth, texHeight );
			}
		}

		return d3d9Texture;

	}
	//------------------------------------------------------------------------

	IDirect3DVolumeTexture9* TextureD3D9::_LoadVolumeErrorBuffer()
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		IDirect3DVolumeTexture9*  d3d9Texture = 0;

		HRESULT hr = device->CreateVolumeTexture(1,1,1,0,0 , D3DFMT_A8R8G8B8 , d3dpoolType, &d3d9Texture, 0);

		if (FAILED(hr))
		{
			n_error( "TextureD3D9::_LoadCubeErrorBuffer Failed" );
			return NULL;
		}
		else
		{
			return d3d9Texture;
		}
	}
	//------------------------------------------------------------------------
	bool TextureD3D9::LoadBuffers()
	{
		D3DFORMAT d3d9Format = D3D9Types::AsD3D9PixelFormat( GetPixelFormat() );
		if( d3d9Format == D3DFMT_UNKNOWN || GetType() == InvalidType )
		{
			IDirect3DTexture9* d3d9Texture = _LoadNormErrorBuffer();
			SetupFromD3D9Texture(d3d9Texture);
			return false;
		}

		if ( !m_stream.isvalid() )
		{
			IDirect3DTexture9* d3d9Texture = _LoadNormErrorBuffer();
			SetupFromD3D9Texture(d3d9Texture);
			return false;
		}

		GPtr<IO::Stream> stream = m_stream;
		stream->SetAccessMode(IO::Stream::ReadAccess);
		memorySize = 0;
		if (stream->Open())
		{
			bool bCreateOK = false;

			if ( GetType() == Texture2D )
			{			
				ubyte* srcData = (ubyte*)stream->Map();
				UINT srcDataSize = stream->GetSize();

				IDirect3DTexture9* d3d9Texture = _LoadNormBuffer(srcData, srcDataSize);
				if ( d3d9Texture )
				{
					SetupFromD3D9Texture(d3d9Texture);
					bCreateOK = true;
				}
				else
				{
					d3d9Texture = _LoadNormErrorBuffer();
					SetupFromD3D9Texture(d3d9Texture);
					bCreateOK = false;
				}				
			}
			else if ( GetType() == Texture3D )
			{
				n_assert( GetDepth() > 1 );
				
				ubyte* srcData = (ubyte*)stream->Map();
				UINT srcDataSize = stream->GetSize();
				IDirect3DVolumeTexture9* d3d9VolumeTexture = 0;
				d3d9VolumeTexture = _LoadVolumeBuffer(srcData,srcDataSize);
				if(d3d9VolumeTexture)
				{
					SetupFromD3D9VolumeTexture(d3d9VolumeTexture);
					bCreateOK = true;
				}
				else
				{
					d3d9VolumeTexture = _LoadVolumeErrorBuffer();
					SetupFromD3D9VolumeTexture(d3d9VolumeTexture);
					bCreateOK = false;
				}
			}
			else if ( GetType() == TextureCube )
			{
				n_assert( GetDepth() == 1 );

				ubyte* srcData = (ubyte*)stream->Map();
				UINT srcDataSize = stream->GetSize();

				IDirect3DCubeTexture9* d3d9Texture = _LoadCubeBuffer(srcData, srcDataSize);
				if ( d3d9Texture )
				{
					SetupFromD3D9CubeTexture(d3d9Texture);
					bCreateOK = true;
				}
				else
				{
					d3d9Texture = _LoadCubeErrorBuffer();
					SetupFromD3D9CubeTexture(d3d9Texture);
					bCreateOK = false;
				}				

				bCreateOK = false;
			}
			else
			{
				n_error("TextureD3D9::LoadBuffers: Invalid tex type");

				bCreateOK = false;
			}

			
			stream->Close();
			memorySize = PixelFormat::GetMemorySize(GetWidth(), GetHeight(), GetDepth(), GetPixelFormat());
			PROFILER_ADDDEVICESTATEVAL(videoRam, memorySize);
			PROFILER_ADDDEVICESTATEVAL(texRam, memorySize );
			PROFILER_ADDDEVICESTATEVAL(textureNum, 1);
			return bCreateOK;
		}

		IDirect3DTexture9* d3d9Texture = _LoadNormErrorBuffer();
		SetupFromD3D9Texture(d3d9Texture);



		return false;
	}

	void TextureD3D9::Setup(const GPtr<Texture>& srcTex)
	{
		Super::Setup();
		/// set texture resouce path
		SetTexturePath(srcTex->GetTexturePath());
		/// set texture stream
		SetStream(srcTex->GetStream());
		/// set texture unit index
		SetUnitIndex(srcTex->GetUnitIndex());
		/// set attri
		SetType( srcTex->GetType() );
		SetWidth( srcTex->GetWidth() );
		SetHeight( srcTex->GetHeight() );
		SetDepth( srcTex->GetDepth() );
		SetNumMipLevels( srcTex->GetNumMipLevels() );
		SetPixelFormat( srcTex->GetPixelFormat() );
		SetSkippedMips( srcTex->GetSkippedMips() );

		SetUsage(srcTex->GetUsage());		//[2012/4/13 zhongdaohuan]
		SetAccess(srcTex->GetAccess());		//[2012/4/13 zhongdaohuan]
	}

	void TextureD3D9::UpdateTexture(UpdateFunction texUpdateFunc, void* tag)
	{
		MapInfo mapInfo;
		for(SizeT i = 0; i < GetNumMipLevels(); ++i)
		{
			if(!Map(i,MapWriteDiscard,mapInfo))
			{
				Unmap(i);
				break;
			}
			texUpdateFunc(mapInfo,GetWidth(),GetHeight(),GetDepth(),GetPixelFormat(),i, tag);
			Unmap(i);
		}
		
	}

	void TextureD3D9::UpdateTexture(GPtr<Texture> srcTex)
	{
		MapInfo mapInfo;
		SizeT texMipMap = GetNumMipLevels();

		GPtr<IO::Stream> stream = srcTex->GetStream();
		stream->SetAccessMode(IO::Stream::ReadAccess);

		if (stream->Open())
		{
			this->SetStream( stream );
			ubyte* srcData = (ubyte*)stream->Map();
			UINT srcDataSize = stream->GetSize();
			SizeT texWidth = srcTex->GetWidth();
			SizeT texHeight = srcTex->GetHeight();
			SizeT depth   = srcTex->GetDepth();

			for(SizeT i = 0; i < texMipMap; ++i)
			{
				if(!Map(i,MapWriteDiscard,mapInfo))
				{
					Unmap(i);
					break;
				}

				PixelFormat::Code format = GetPixelFormat();
				D3DFORMAT d3d9Format = D3D9Types::AsD3D9PixelFormat( format );
				n_assert( d3d9Format != D3DFMT_UNKNOWN );

				if ( GetType() == Texture2D )
				{
					if ( PixelFormat::IsCompressed( format ) )
					{
						// must be dxt
						// copy pixel
						SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);
						Memory::CopyToGraphicsMemory(srcData, mapInfo.data, levelPixelSize );
						MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
					}
					else
					{
						// copy pixel
						SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);
						BlitCopyImage( (ubyte*)mapInfo.data, mapInfo.rowPitch, texHeight,
							srcData, srcRowPitch,  texHeight);
						MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
					}
				}
				else if ( GetType() == Texture3D )
				{
					if ( PixelFormat::IsCompressed( format ) )
					{
						// copy pixel
						SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, depth, format);
						Memory::CopyToGraphicsMemory(srcData, mapInfo.data, levelPixelSize );

						MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
					}
					else
					{
						// copy pixel
						SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);
						ubyte* lockedBoxCopy =  (ubyte*)mapInfo.data;
						ubyte* srcCopy = srcData;

						for( int i=0 ; i<depth ; i++ )
						{
							BlitCopyImage( lockedBoxCopy, mapInfo.rowPitch, texHeight,
								srcCopy, srcRowPitch,  texHeight);

							lockedBoxCopy += mapInfo.depthPitch;
							srcCopy       += srcRowPitch*texHeight;
						}

						MoveCursorToNextMipMap(format, srcData, texWidth, texHeight );
					}
				}
				else if ( GetType() == TextureCube )
				{

					SizeT faceSize = 0;
					{
						SizeT cubeEdgeSize = texWidth;
						for( int level = 0; level < texMipMap; ++level )
						{
							faceSize += PixelFormat::GetMemorySize(cubeEdgeSize, cubeEdgeSize, 1, format);
							cubeEdgeSize =  Math::n_max( cubeEdgeSize / 2, 1 );
						}
					}


					if ( PixelFormat::IsCompressed( format ) )
					{
						for ( int face=0; face<6; ++face )
						{
							ubyte* faceData = srcData + face*faceSize;
							// copy pixel
							SizeT levelPixelSize = PixelFormat::GetMemorySize(texWidth, texHeight, 1, format);
							Memory::CopyToGraphicsMemory(faceData, mapInfo.data, levelPixelSize );
							MoveCursorToNextMipMap(format, faceData, texWidth, texHeight );
						}
					}
					else
					{
						for ( int face=0; face<6; ++face )
						{
							ubyte* faceData = srcData + face*faceSize;
							// copy pixel
							SizeT srcRowPitch = PixelFormat::GetMemorySize(texWidth, 1, 1, format);
							BlitCopyImage( (ubyte*)mapInfo.data, mapInfo.rowPitch, texHeight,
								faceData, srcRowPitch,  texHeight);

							MoveCursorToNextMipMap(format, faceData, texWidth, texHeight );
						}
					}
				}
				Unmap(i);
			}

			stream->Close();
		}
	}

	void TextureD3D9::OnDeviceLost()
	{
		if (GetD3D9PoolType() == D3DPOOL_DEFAULT)
		{
			Unload();
		}
		
	}

	void TextureD3D9::OnDeviceReset()
	{
		//TODO
		
	}

	bool TextureD3D9::GetTextureData( ubyte* data ) const
	{
		if( d3d9Texture!=NULL )
		{
			return __GetNormalData(data);
		}
		
		return false;
	}

	const SizeT TextureD3D9::GetTextureSize() const
	{
		return RenderBase::PixelFormat::GetMemorySize(width, height, 1, pixelFormat);
	}

	void TextureD3D9::GenerateCubeMap(const TextureD3D9& texFront,const TextureD3D9& texBack,const TextureD3D9& texTop,const TextureD3D9& texUnder,const TextureD3D9& texLeft,const TextureD3D9& texRight )
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
	
		SetType( TextureCube );
		SetWidth( texFront.GetWidth() );
		SetHeight(texFront.GetHeight() );
		SetDepth( texFront.GetDepth() );
		SetNumMipLevels( texFront.GetNumMipLevels() );
		SetPixelFormat( texFront.GetPixelFormat() );
		SetSkippedMips( texFront.GetSkippedMips() );


		ubyte* srcDataOffset = NULL;
		ubyte* srcData = NULL;
		srcData = n_new_array(ubyte,texFront.GetTextureSize()*6);
		n_assert(srcData!=NULL);

		srcDataOffset = srcData; 
		texFront.GetTextureData(srcData);
		
		srcDataOffset += texFront.GetTextureSize();
		texBack.GetTextureData(srcDataOffset);

		srcDataOffset += texBack.GetTextureSize();
		texTop.GetTextureData(srcDataOffset);

		srcDataOffset += texTop.GetTextureSize();
		texUnder.GetTextureData(srcDataOffset);

		srcDataOffset += texUnder.GetTextureSize();
		texLeft.GetTextureData(srcDataOffset);

		srcDataOffset += texLeft.GetTextureSize();
		texRight.GetTextureData(srcDataOffset);


 		IDirect3DCubeTexture9* d3d9CubeTexture = 0;
 		d3d9CubeTexture = _LoadCubeBuffer(srcData,texFront.GetTextureSize()*6);
 		if(d3d9CubeTexture)
 		{
 			SetupFromD3D9CubeTexture(d3d9CubeTexture);
 
 		}
		else
		{
			n_error("generate cubeTex failed");
		}
		n_delete_array(srcData);
	}

	void TextureD3D9::GenerateCubeMapData( ubyte* srcData,const TextureD3D9& texFront,const TextureD3D9& texBack,const TextureD3D9& texTop,const TextureD3D9& texUnder,const TextureD3D9& texLeft,const TextureD3D9& texRight )
	{
		n_assert(srcData!=NULL);
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();

		SetType( TextureCube );
		SetWidth( texFront.GetWidth() );
		SetHeight(texFront.GetHeight() );
		SetDepth( texFront.GetDepth() );
		SetNumMipLevels( texFront.GetNumMipLevels() );
		SetPixelFormat( texFront.GetPixelFormat() );
		SetSkippedMips( texFront.GetSkippedMips() );

		ubyte* srcDataOffset = NULL;
		srcDataOffset = srcData;
		texFront.GetTextureData(srcData);

		srcDataOffset += texFront.GetTextureSize();
		texBack.GetTextureData(srcDataOffset);

		srcDataOffset += texBack.GetTextureSize();
		texTop.GetTextureData(srcDataOffset);

		srcDataOffset += texTop.GetTextureSize();
		texUnder.GetTextureData(srcDataOffset);

		srcDataOffset += texUnder.GetTextureSize();
		texLeft.GetTextureData(srcDataOffset);

		srcDataOffset += texLeft.GetTextureSize();
		texRight.GetTextureData(srcDataOffset);
	}

	bool TextureD3D9::__GetNormalData( ubyte* data ) const
	{
		if(d3d9Texture==NULL)
		{
			return false;
		}

		IDirect3DSurface9* d3d9Surface9;


		IDirect3DSurface9* d3d9Surface9Final;

		IDirect3DTexture9* d3d9TextureFinal;

		HRESULT hr = D3D9::RenderDeviceD3D9::Instance()->CreateTexture(width, height, 1, 0, D3D9::D3D9Types::AsD3D9PixelFormat(pixelFormat),D3DPOOL_SYSTEMMEM ,&d3d9TextureFinal,NULL );
		if(FAILED(hr))
		{
			return false;
		}
		hr = d3d9Texture->GetSurfaceLevel(0, &(d3d9Surface9));
		if(FAILED(hr))
		{
			return false;
		}
		hr = d3d9TextureFinal->GetSurfaceLevel(0,&(d3d9Surface9Final));
		if(FAILED(hr))
		{
			return false;
		}
		hr =  D3D9::RenderDeviceD3D9::Instance()->GetRenderTargetData( d3d9Surface9, d3d9Surface9Final);
		if(FAILED(hr))
		{
			return false;
		}
		SizeT levelPixelSize = RenderBase::PixelFormat::GetMemorySize(width, height, 1, pixelFormat);
		D3DLOCKED_RECT lockedRect = {0};
		hr = d3d9Surface9Final->LockRect(&lockedRect, NULL, 0);
		if(FAILED(hr))
		{
			return false;
		}

		n_assert(data!=NULL);
		Memory::Copy(lockedRect.pBits, data, levelPixelSize);
		d3d9Surface9Final->UnlockRect();
		d3d9TextureFinal->Release();
		d3d9Surface9Final->Release();
		d3d9Surface9->Release();

		return true;
	}

	


}

#endif