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
#ifndef __PVRTC_Header_H__
#define __PVRTC_Header_H__

#if __VC__
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

const uint32 PVR_MAGIC = FOURCC('P', 'V', 'R', '!');
#define PVR_TEXTURE_FLAG_TYPE_MASK	0xff

enum EPVRTColourSpace
{
	ePVRTCSpacelRGB,
	ePVRTCSpacesRGB
};

//Compressed pixel formats
enum EPVRTPixelFormat
{
	ePVRTPF_PVRTCI_2bpp_RGB,
	ePVRTPF_PVRTCI_2bpp_RGBA,
	ePVRTPF_PVRTCI_4bpp_RGB,
	ePVRTPF_PVRTCI_4bpp_RGBA,
	ePVRTPF_PVRTCII_2bpp,
	ePVRTPF_PVRTCII_4bpp,
	ePVRTPF_ETC1,
	ePVRTPF_DXT1,
	ePVRTPF_DXT2,
	ePVRTPF_DXT3,
	ePVRTPF_DXT4,
	ePVRTPF_DXT5,

	//These formats are identical to some DXT formats.
	ePVRTPF_BC1 = ePVRTPF_DXT1,
	ePVRTPF_BC2 = ePVRTPF_DXT3,
	ePVRTPF_BC3 = ePVRTPF_DXT5,

	//These are currently unsupported:
	ePVRTPF_BC4,
	ePVRTPF_BC5,
	ePVRTPF_BC6,
	ePVRTPF_BC7,
	ePVRTPF_UYVY,
	ePVRTPF_YUY2,
	ePVRTPF_BW1bpp,
	ePVRTPF_SharedExponentR9G9B9E5,
	ePVRTPF_RGBG8888,
	ePVRTPF_GRGB8888,
	ePVRTPF_ETC2_RGB,
	ePVRTPF_ETC2_RGBA,
	ePVRTPF_ETC2_RGB_A1,
	ePVRTPF_EAC_R11_Unsigned,
	ePVRTPF_EAC_R11_Signed,
	ePVRTPF_EAC_RG11_Unsigned,
	ePVRTPF_EAC_RG11_Signed,
	ePVRTPF_NumCompressedPFs
};

typedef struct _PVRTCTexHeader
{
	uint32 headerLength;
	uint32 height;
	uint32 width;
	uint32 numMipmaps;
	uint32 flags;
	uint32 dataLength;
	uint32 bpp;
	uint32 bitmaskRed;
	uint32 bitmaskGreen;
	uint32 bitmaskBlue;
	uint32 bitmaskAlpha;
	uint32 pvrTag;
	uint32 numSurfs;
} PVRTCTexHeader;

typedef struct New_PVRTCTexHeader
{
	uint32	u32Version;			//Version of the file header, used to identify it.
	uint32	u32Flags;			//Various format flags.
	uint64	u64PixelFormat;		//The pixel format, 8cc value storing the 4 channel identifiers and their respective sizes.
	uint32	u32ColourSpace;		//The Colour Space of the texture, currently either linear RGB or sRGB.
	uint32	u32ChannelType;		//Variable type that the channel is stored in. Supports signed/unsigned int/short/byte or float for now.
	uint32	u32Height;			//Height of the texture.
	uint32	u32Width;			//Width of the texture.
	uint32	u32Depth;			//Depth of the texture. (Z-slices)
	uint32	u32NumSurfaces;		//Number of members in a Texture Array.
	uint32	u32NumFaces;		//Number of faces in a Cube Map. Maybe be a value other than 6.
	uint32	u32MIPMapCount;		//Number of MIP Maps in the texture - NB: Includes top level.
	uint32	u32MetaDataSize;	//Size of the accompanying meta data.
} New_PVRTCTexHeader;

#if __VC__
#pragma pack (pop)
#else
#pragma pack ()
#endif





#endif // __PVRTC_Header_H__
