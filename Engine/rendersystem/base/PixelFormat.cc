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

#include "stdneb.h"
#ifdef __OSX__
#include "../rendersystem/base/PixelFormat.h"
#include "../rendersystem/base/PixelFormatDesc.h"
#include "math/scalar.h"
#else
#include "rendersystem/base/PixelFormat.h"
#include "rendersystem/base/PixelFormatDesc.h"
#endif
namespace RenderBase
{

	const PixelFormatDescription& getDescriptionFor(PixelFormat::Code format)
	{
		const int ord = (int)format;
		n_assert( ord >= 0 && ord < PixelFormat::DescPixelFormatsCount );
		return _pixelFormats[ord];
	}
	//------------------------------------------------------------------------------
	/**
	Convert a pixel format string into a pixel format code.
	*/
	PixelFormat::Code
	PixelFormat::FromString(const Util::String& str)
	{
		for ( int i = 0; i < PixelFormat::DescPixelFormatsCount; ++i )
		{
			const PixelFormatDescription& desc = getDescriptionFor( (PixelFormat::Code)i );
			if ( str == desc.name )
			{
				return (PixelFormat::Code)i;
			}
		}

		return PixelFormat::InvalidPixelFormat;
	}
	//------------------------------------------------------------------------

    unsigned int PixelFormat::GetFlags( Code format )
	{
		return getDescriptionFor(format).flags; 
	}

	//------------------------------------------------------------------------
	bool 
	PixelFormat::IsCompressed(Code code)
	{
		return (GetFlags(code) & PFF_COMPRESSED) > 0;
	}
	//------------------------------------------------------------------------
	SizeT 
	PixelFormat::GetNumElemBytes(Code code)
	{
		 return getDescriptionFor(code).elemBytes;
	}
	//------------------------------------------------------------------------
	void 
	PixelFormat::GetBitMasks(Code format, uint32 rgba[4])
	{
		const PixelFormatDescription &des = getDescriptionFor(format);
		rgba[0] = des.rmask;
		rgba[1] = des.gmask;
		rgba[2] = des.bmask;
		rgba[3] = des.amask;
	}
	//------------------------------------------------------------------------
	void 
	PixelFormat::GetBitDepths(Code format, int rgba[4])
	{
		const PixelFormatDescription &des = getDescriptionFor(format);
		rgba[0] = des.rbits;
		rgba[1] = des.gbits;
		rgba[2] = des.bbits;
		rgba[3] = des.abits;
	}

	//------------------------------------------------------------------------
	SizeT 
	PixelFormat::GetMemorySize(SizeT width, SizeT height, SizeT depth, Code format)
	{
		if(IsCompressed(format))
		{
			switch(format)
			{
				//  un compressed dxt
			case A8R8G8B8:
				return width*height*4;
			case R8G8B8:
				return width*height*3;
				// DXT formats work by dividing the image into 4x4 blocks, then encoding each
				// 4x4 block with a certain number of bytes. 
			case DXT1:
				return ((width+3)/4)*((height+3)/4)*8 * depth;
			case DXT2:
			case DXT3:
			case DXT4:
			case DXT5:
				return ((width+3)/4)*((height+3)/4)*16 * depth;

				// Size calculations from the PVRTC OpenGL extension spec
				// http://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
				// Basically, 32 bytes is the minimum texture size.  Smaller textures are padded up to 32 bytes
			case PVRTC_RGB2:
			case PVRTC_RGBA2:
				n_assert(depth == 1);
				return ( Math::n_max( width, 16 ) * Math::n_max( height, 8 ) * 2 + 7 ) / 8;
			case PVRTC_RGB4:
			case PVRTC_RGBA4:
				n_assert(depth == 1);
				return (Math::n_max((int)width, 8) * Math::n_max((int)height, 8) * 4 + 7) / 8;
			default:
				n_error("PixelFormat::GetMemorySize: Invalid compressed pixel format" );
				return 0;
			}
		}
		else
		{
			return width*height*depth*GetNumElemBytes(format);
		}
	}	
	//------------------------------------------------------------------------------
	/**
	Convert pixel format code into a string.
	*/
	Util::String
	PixelFormat::ToString(PixelFormat::Code code)
	{
		return getDescriptionFor(code).name;
	}
}
