/****************************************************************************
This source file is part of OGRE
Copyright (c) 2000-2009 Torus Knot Software Ltd
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
#ifndef __DDS_Header_H__
#define __DDS_Header_H__

#if __VC__
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

// Nested structure
struct DDSPixelFormat
{
	uint32 size;
	uint32 flags;
	uint32 fourCC;
	uint32 rgbBits;
	uint32 redMask;
	uint32 greenMask;
	uint32 blueMask;
	uint32 alphaMask;
};

// Nested structure
struct DDSCaps
{
	uint32 caps1;
	uint32 caps2;
	uint32 reserved[2];
};
// Main header, note preceded by 'DDS '
struct DDSHeader
{
	uint32 size;		
	uint32 flags;
	uint32 height;
	uint32 width;
	uint32 sizeOrPitch;
	uint32 depth;
	uint32 mipMapCount;
	uint32 reserved1[11];
	DDSPixelFormat pixelFormat;
	DDSCaps caps;
	uint32 reserved2;
};

// An 8-byte DXT colour block, represents a 4x4 texel area. Used by all DXT formats
struct DXTColourBlock
{
	// 2 colour ranges
	uint16 colour_0;
	uint16 colour_1;
	// 16 2-bit indexes, each byte here is one row
	uint8 indexRow[4];
};
// An 8-byte DXT explicit alpha block, represents a 4x4 texel area. Used by DXT2/3
struct DXTExplicitAlphaBlock
{
	// 16 4-bit values, each 16-bit value is one row
	uint16 alphaRow[4];
};
// An 8-byte DXT interpolated alpha block, represents a 4x4 texel area. Used by DXT4/5
struct DXTInterpolatedAlphaBlock
{
	// 2 alpha ranges
	uint8 alpha_0;
	uint8 alpha_1;
	// 16 3-bit indexes. Unfortunately 3 bits doesn't map too well to row bytes
	// so just stored raw
	uint8 indexes[6];
};

#if __VC__
#pragma pack (pop)
#else
#pragma pack ()
#endif

const uint32 DDS_MAGIC = FOURCC('D', 'D', 'S', ' ');
const uint32 DDS_PIXELFORMAT_SIZE = 8 * sizeof(uint32);
const uint32 DDS_CAPS_SIZE = 4 * sizeof(uint32);
const uint32 DDS_HEADER_SIZE = 19 * sizeof(uint32) + DDS_PIXELFORMAT_SIZE + DDS_CAPS_SIZE;

const uint32 DDSD_CAPS = 0x00000001;
const uint32 DDSD_HEIGHT = 0x00000002;
const uint32 DDSD_WIDTH = 0x00000004;
const uint32 DDSD_PITCH = 0x00000008;
const uint32 DDSD_PIXELFORMAT = 0x00001000;
const uint32 DDSD_MIPMAPCOUNT = 0x00020000;
const uint32 DDSD_LINEARSIZE = 0x00080000;
const uint32 DDSD_DEPTH = 0x00800000;
const uint32 DDPF_ALPHAPIXELS = 0x00000001;
const uint32 DDPF_FOURCC = 0x00000004;
const uint32 DDPF_RGB = 0x00000040;
const uint32 DDPF_RGBA = 0x00000041;
const uint32 DDSCAPS_COMPLEX = 0x00000008;
const uint32 DDSCAPS_TEXTURE = 0x00001000;
const uint32 DDSCAPS_MIPMAP = 0x00400000;
const uint32 DDSCAPS2_CUBEMAP = 0x00000200;
const uint32 DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400;
const uint32 DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800;
const uint32 DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000;
const uint32 DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000;
const uint32 DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000;
const uint32 DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000;
const uint32 DDSCAPS2_VOLUME = 0x00200000;

// Special FourCC codes
const uint32 D3DFMT_R16F			= 111;
const uint32 D3DFMT_G16R16F			= 112;
const uint32 D3DFMT_A16B16G16R16F	= 113;
const uint32 D3DFMT_R32F            = 114;
const uint32 D3DFMT_G32R32F         = 115;
const uint32 D3DFMT_A32B32G32R32F   = 116;







#endif // __DDS_Header_H__
