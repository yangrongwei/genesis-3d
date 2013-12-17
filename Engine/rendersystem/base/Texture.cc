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

//------------------------------------------------------------------------------
//  texture.cc
//  Copyright (c) 2011,WebJet Business Division,CYOU
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "Texture.h"

namespace RenderBase
{
	__ImplementClass(RenderBase::Texture, 'TXRR', RenderBase::RenderCommandType);

	//------------------------------------------------------------------------------
	/**
	*/
	Texture::Texture() :
	type(InvalidType),
		width(0),
		height(0),
		depth(0),
		numMipLevels(0),
		skippedMips(0),
		memorySize(0),
		m_unitIndex(0),
		pixelFormat(PixelFormat::InvalidPixelFormat)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Texture::~Texture()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		Texture::Map(IndexT mipLevel, Access accessMode, MapInfo& outMapInfo)
	{
		n_error("Base Texture::Map() called!");
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		Texture::Unmap(IndexT mipLevel)
	{
		n_error("Base Texture::Unmap() called!");
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		Texture::MapCubeFace(CubeFace face, IndexT mipLevel, Access accessMode, MapInfo& outMapInfo)
	{
		n_error("Base Texture::MapCubeFace() called!");
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		Texture::UnmapCubeFace(CubeFace cubeFace, IndexT mipLevel)
	{
		n_error("Base Texture::UnmapCubeFace() called!");
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void Texture::Setup()
	{
		SetRenderCommandType(RenderCommandType::SetTexture);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void Texture::OnDeviceLost()
	{

	}

	//------------------------------------------------------------------------------
	/**
	*/
	void Texture::OnDeviceReset()
	{

	}

} // namespace RenderBase
