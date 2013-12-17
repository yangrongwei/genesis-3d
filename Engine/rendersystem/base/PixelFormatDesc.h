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

#ifndef __PixelFormatDesc_H__
#define __PixelFormatDesc_H__
#ifdef __OSX__
#include "core/types.h"
#include "../rendersystem/base/PixelFormat.h"
#else
#include "foundation/core/types.h"
#include "rendersystem/base/PixelFormat.h"
#endif

namespace RenderBase
{
	// From Ogre
	PixelFormatDescription _pixelFormats[PixelFormat::DescPixelFormatsCount] = {
		//------------------------------------------------------------------------
		{"X8R8G8B8" ,
		/* Bytes per element */
		4,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000,
		16, 8, 0, 24
		},
		//------------------------------------------------------------------------
		{"R8G8B8",
		/* Bytes per element */
		3,  // 24 bit integer -- special
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0xFF0000, 0x00FF00, 0x0000FF, 0,
		16, 8, 0, 0
		},
		//------------------------------------------------------------------------
		{"B8G8R8",
		/* Bytes per element */
		3,  // 24 bit integer -- special
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0x0000FF, 0x00FF00, 0xFF0000, 0,
		0, 8, 16, 0
		},
		//------------------------------------------------------------------------
		{"B8G8R8A8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF,
		8, 16, 24, 0
		},
		//------------------------------------------------------------------------
		{"R8G8B8A8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF,
		24, 16, 8, 0
		},
		//------------------------------------------------------------------------
		{"A8B8G8R8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000,
		0, 8, 16, 24,
		},
		//------------------------------------------------------------------------
		{"A8R8G8B8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000,
		16, 8, 0, 24
		},
		//------------------------------------------------------------------------
		{"R5G6B5",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		5, 6, 5, 0,
		/* Masks and shifts */
		0xF800, 0x07E0, 0x001F, 0,
		11, 5, 0, 0
		},
		//------------------------------------------------------------------------
		{"A1R5G5B5",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		5, 5, 5, 1,
		/* Masks and shifts */
		0x7C00, 0x03E0, 0x001F, 0x8000,
		10, 5, 0, 15,
		},
		//------------------------------------------------------------------------
		{"A4R4G4B4",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		4, 4, 4, 4,
		/* Masks and shifts */
		0x0F00, 0x00F0, 0x000F, 0xF000,
		8, 4, 0, 12
		},
		//------------------------------------------------------------------------
		{"DXT1",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 3, // No alpha
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"DXT2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"DXT3",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"DXT4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"DXT5",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"R16F",                       // 16 bit float, red only
		/* Bytes per element */
		2,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT16, 1,
		/* rbits, gbits, bbits, abits */
		16, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"G16R16F",                    // 32 bit float, 16 bit red, 16 bit green
		/* Bytes per element */
		4,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT16, 2,
		/* rbits, gbits, bbits, abits */
		16, 16, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"A16B16G16R16F",              // 64 bit float, 16 bit rgba each
		/* Bytes per element */
		8,
		/* Flags */
		PFF_FLOAT | PFF_HASALPHA,
		/* Component type and count */
		PCT_FLOAT16, 4,
		/* rbits, gbits, bbits, abits */
		16, 16, 16, 16,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"R32F",                       // 32 bit float, red only
		/* Bytes per element */
		4,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT32, 1,
		/* rbits, gbits, bbits, abits */
		32, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"G32R32F",                    // 64 bit float, 32 bit red, 32 bit green
		/* Bytes per element */
		8,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT32, 2,
		/* rbits, gbits, bbits, abits */
		32, 32, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"A32B32G32R32F",              // 128 bit float, 32 bit rgba each
		/* Bytes per element */
		16,
		/* Flags */
		PFF_FLOAT | PFF_HASALPHA,
		/* Component type and count */
		PCT_FLOAT32, 4,
		/* rbits, gbits, bbits, abits */
		32, 32, 32, 32,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"A8",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 1,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 8,
		/* Masks and shifts */
		0, 0, 0, 0xFF, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"L8",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 1,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 0,
		/* Masks and shifts */
		0xFF, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"L8A8",						//[2012/4/12 zhongdaohuan] mygui 用到的格式
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_LUMINANCE,
		/* Component type and count */
		PCT_BYTE, 2,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 8,
		/* Masks and shifts */
		0,0,0,0,0,0,0,0
		},
		//------------------------------------------------------------------------
		{"L16",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_SHORT, 1,
		/* rbits, gbits, bbits, abits */
		16, 0, 0, 0,
		/* Masks and shifts */
		0xFFFF, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"G16R16",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_SHORT, 2,
		/* rbits, gbits, bbits, abits */
		16, 16, 0, 0,
		/* Masks and shifts */
		0x0000FFFF, 0xFFFF0000, 0, 0, 
		0, 16, 0, 0
		},
		//------------------------------------------------------------------------
		{"D24X8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_DEPTH,
		/* Component type and count */
		PCT_FLOAT32, 1, // ?
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"D24S8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_DEPTH,
		/* Component type and count */
		PCT_FLOAT32, 1, // ?
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGB2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGBA2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGB4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGBA4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"ETC1_RGB8",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"InvalidPixelFormat",    // ----- PixelFormat::InvalidPixelFormat
		/* Bytes per element */
		0,
		/* Flags */
		0,
		/* Component type and count */
		PCT_BYTE, 0,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"InvalidPixelFormat",	// ----- PixelFormat::InvalidPixelFormat
		/* Bytes per element */
		0,
		/* Flags */
		0,
		/* Component type and count */
		PCT_BYTE, 0,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------


	};
}







#endif // __PixelFormatDesc_H__
