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
#ifndef __PixelFormat_H__
#define __PixelFormat_H__

#include "../foundation/util/string.h"

namespace RenderBase
{
	 /** from Ogre
     * Flags defining some on/off properties of pixel formats
     */
    enum PixelFormatFlags {
        // This format has an alpha channel
        PFF_HASALPHA        = 0x00000001,      
        // This format is compressed. This invalidates the values in elemBytes,
        // elemBits and the bit counts as these might not be fixed in a compressed format.
        PFF_COMPRESSED    = 0x00000002,
        // This is a floating point format
        PFF_FLOAT           = 0x00000004,         
        // This is a depth format (for depth textures)
        PFF_DEPTH           = 0x00000008,
        // Format is in native endian. Generally true for the 16, 24 and 32 bits
        // formats which can be represented as machine integers.
        PFF_NATIVEENDIAN    = 0x00000010,
        // This is an intensity format instead of a RGB one. The luminance
        // replaces R,G and B. (but not A)
        PFF_LUMINANCE       = 0x00000020
    };

	/** From Ogre  Pixel component format */
	enum PixelComponentType
	{
		PCT_BYTE = 0,    /// Byte per component (8 bit fixed 0.0..1.0)
		PCT_SHORT = 1,   /// Short per component (16 bit fixed 0.0..1.0))
		PCT_FLOAT16 = 2, /// 16 bit float per component
		PCT_FLOAT32 = 3, /// 32 bit float per component
		PCT_COUNT = 4    /// Number of pixel types
	};

		//-----------------------------------------------------------------------
    /**  From Ogre
    * A record that describes a pixel format in detail.
    */
    struct PixelFormatDescription {
        /* Name of the format, as in the enum */
        const char *name;
        /* Number of bytes one element (colour value) takes. */
        unsigned char elemBytes;
        /* Pixel format flags, see enum PixelFormatFlags for the bit field
        * definitions
        */
        uint32 flags;
        /** Component type
         */
        PixelComponentType componentType;
        /** Component count
         */
        unsigned char componentCount;
        /* Number of bits for red(or luminance), green, blue, alpha
        */
        unsigned char rbits,gbits,bbits,abits; /*, ibits, dbits, ... */

        /* Masks and shifts as used by packers/unpackers */
        uint32 rmask, gmask, bmask, amask;
        unsigned char rshift, gshift, bshift, ashift;
    };

	// 修改此枚举时记得要和脚本的格式同步ScriptRuntime._PixelFormat。
	// 像素格式中的顺序指从左到右的顺序。具体的内存字节序取决于当前运行的平台。
	// 比如A8B8G8R8代表{A、R、G、B}，但在小端机器上（PC）上，内存顺序是[B、G、R、A]。
	// 这个约定和D3D、OpenGL是一致的，即内存顺序取决于客户端机器的顺序
	// !!!!!!!!!!!修改枚举后，记得对应修改PixelFormatDescription _pixelFormats 和 CommonCount、iOSCount 等！！！！！！！！！！！！！
	class PixelFormat
	{
	public:
		/// enums
		enum Code
		{
			// begin common
			X8R8G8B8 = 0,
			R8G8B8,
			B8G8R8,
			B8G8R8A8,
			R8G8B8A8,
			A8B8G8R8,
			A8R8G8B8,
			R5G6B5,
			A1R5G5B5,
			A4R4G4B4,
			DXT1,
			DXT2,
			DXT3,
			DXT4,
			DXT5,
			R16F,                       
			G16R16F,                    
			A16B16G16R16F,              
			R32F,                      
			G32R32F,                    
			A32B32G32R32F,              
			A8,
			L8,
			L8A8,						//[2012/4/12 zhongdaohuan] mygui 用到的格式
			L16,
			G16R16,
			D24X8,
			D24S8,
			// end common   CommonCount

			// begin iPhone /  PowerVR
			PVRTC_RGB2,
			PVRTC_RGBA2,
			PVRTC_RGB4,
			PVRTC_RGBA4,
			// end iphone / PowerVR end   iOSCount

			//ETC
			ETC1_RGB8,
			
			NumPixelFormats,
			InvalidPixelFormat,
			DescPixelFormatsCount,	//	不调整NumPixelFormats和InvalidPixelFormat的顺序，以免引起BUG。用于像素格式描述的数组

			// 记录分块的标志位。 更改枚举之后，记得修改
			CommonCount = D24S8 + 1, 
			iOSCount = PVRTC_RGBA4 + 1,
			
		};

		/// From Ogre:
		static bool IsCompressed(Code code);

		/** From Ogre: Returns the size in bytes of an element of the given pixel format.
		* GetNumElemBytes  
		* @param: Code code  
		* @return: SizeT  
			The size in bytes of an element. See Remarks.
		* @see: 
		* @remark:  
			Passing PF_UNKNOWN will result in returning a size of 0 bytes.
		*/
		static SizeT GetNumElemBytes(Code code);

		// From Ogre: Gives the masks for the R, G, B and A component. Only valid for native endian formats
		static void GetBitMasks(Code format, uint32 rgba[4]);

		// From Ogre: Gives the number of bits (RGBA) for a format.  For non-colour formats (dxt, depth) this returns [0,0,0,0].  
		static void GetBitDepths(Code format, int rgba[4]);

		// From Ogre:Returns the size in memory of a region with the given extents and pixel format with consecutive memory layout
		static SizeT GetMemorySize(SizeT width, SizeT height, SizeT depth, Code format);

		/// convert from string
		static Code FromString(const Util::String& str);
		/// convert to string
		static Util::String ToString(Code code);

        /** From Ogre: Returns the property flags for this pixel format
        * GetFlags  
        * @param: Code format  
        * @return: unsigned int  
				A bitfield combination of PFF_HASALPHA, PFF_ISCOMPRESSED,
				PFF_FLOAT, PFF_DEPTH, PFF_NATIVEENDIAN, PFF_LUMINANCE
        * @see: 
        * @remark:  
        */
        static unsigned int GetFlags( Code format );
	};
}







#endif // __PixelFormat_H__
