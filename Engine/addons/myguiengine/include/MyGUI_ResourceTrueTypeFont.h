/*!
	@file
	@author		Albert Semenov
	@date		06/2009
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __MYGUI_RESOURCE_TRUE_TYPE_FONT_H__
#define __MYGUI_RESOURCE_TRUE_TYPE_FONT_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_IFont.h"

#ifdef MYGUI_USE_FREETYPE
	#include "ft2build.h"
	#include FT_FREETYPE_H
#endif // MYGUI_USE_FREETYPE

namespace MyGUI
{

	// --------------------------- [2012/5/8 zhongdaohuan]拓展 -------------------------------------------
	class FTFactory;
	class FTFace;

	class RectanglePackerBase
	{
	protected:
		int _width;
		int _height;

	public:
		RectanglePackerBase(int width, int height)
			: _width(width)
			, _height(height)
		{
		}

		int getWidth() const
		{
			return _width;
		}

		int getHeight() const
		{
			return _height;
		}
	};
	/** Packer using a stack algorithm.
@remarks
    The algorithm always places rectangles as low as possible in the packing
    area. So, for any new rectangle that is to be added, the packer has to
    determine the X coordinate at which the rectangle can have the lowest
    overall height without intersecting any other rectangles.
@para
    To quickly discover these locations, the packer uses a sophisticated
    data structure that stores the upper silhouette of the packing area. When
    a new rectangle needs to be added, only the silhouette edges need to be
    analyzed to find the position where the rectangle would achieve the lowest
    placement possible in the packing area.
*/
	class StackRectanglePacker : public RectanglePackerBase
	{
	protected:
		struct CoordI
		{
			int x;
			int y;

			CoordI()
			{
			}

			CoordI(int x, int y)
				: x(x), y(y)
			{
			}
		};

		struct SizeI
		{
			int width;
			int height;

			SizeI()
			{
			}

			SizeI(int width, int height)
				: width(width), height(height)
			{
			}
		};

		/// Stores the silhouette of the rectangles.
		typedef std::vector<CoordI> Slices;
		typedef Slices::const_iterator ConstIterator;
		typedef Slices::iterator Iterator;
		Slices _slices;

		template <class T>
		static inline T _next(T x) { return ++x; }

		template <class T>
		static inline T _prior(T x) { return --x; }

	public:
		StackRectanglePacker(int width, int height)
			: RectanglePackerBase(width, height)
			, _slices()
		{
			prepareSlices();
		}

		bool resetSize(int width, int height)
		{
			_width = width;
			_height = height;
			clear();
			return true;
		}


		/** Deallocate all rectangles.
		@returns
			true if the packing algorithm supports deallocate all rectangles.
		*/
		bool clear()
		{
			// Remove all slices
			_slices.clear();
	    
			prepareSlices();
			return true;
		}

		/** Get used space.
		@returns
			Sum of the area of all allocated rectangles and wasted area.
		*/
		int getUsedSpace() const
		{
			int usedSpace = 0;

			ConstIterator it = _slices.begin();
			do
			{
				usedSpace += (_next(it)->x - it->x) * it->y;
			} while (++it != _slices.end());

			return usedSpace;
		}

		/** Allocate space for a rectangle in the packing region.
		@param w
			The width of the rectangle to allocate.
		@param h
			The height of the rectangle to allocate.
		@param x
			Output parameter receiving the rectangle's x placement.
		@param y
			Output parameter receiving the rectangle's y placement.
		@returns
			true if space for the rectangle could be allocated.
		*/
		bool allocate(int w, int h, int& x, int &y)
		{
			CoordI placement;
			if (!allocate(SizeI(w, h), placement))
				return false;

			x = placement.x;
			y = placement.y;
			return true;
		}

	protected:

		/** Allocate space for a rectangle in the packing region.
		@param size
			The size of the rectangle to allocate.
		@param placement
			Output parameter receiving the rectangle's placement.
		@returns
			true if space for the rectangle could be allocated.
		*/
		bool allocate(const SizeI& size, CoordI& placement)
		{
			// The size must not be less that zero
			if (size.width < 0 || size.height < 0)
				return false;

			// If the rectangle is larger than the packing area in any dimension,
			// it will never fit!
			if (size.width > _width || size.height > _height)
				return false;

			// Determine the placement for the new rectangle
			if (!findBestPlacement(size, placement))
				return false;

			// If a place for the rectangle could be found, update the slice table to
			// mark the region of the rectangle as being taken.
			if (size.width > 0 && size.height > 0)
			{
				integrateRectangle(placement.x, size.width, placement.y + size.height);
			}

			return true;
		}

	protected:

		/// Compares the starting position of slices.
		struct SliceStartComparer
		{
			bool operator()(const CoordI& lhs, const CoordI& rhs) const
			{
				return lhs.x < rhs.x;
			}
		};

		/// Compares the height position of slices.
		struct SliceHeightComparer
		{
			bool operator()(const CoordI& lhs, const CoordI& rhs) const
			{
				return lhs.y < rhs.y;
			}
		};

		/** Prepare to empty state.
		*/
		void prepareSlices()
		{
			// At the beginning, the packing area is a single slice of height 0
			_slices.push_back(CoordI(0, 0));

			// Add end slice on the right of the packing area with height same as packing area
			_slices.push_back(CoordI(_width, _height));
		}

		/** Finds the best position for a rectangle of the given dimensions.
		@returns
			true if a valid placement for the rectangle could be found.
		*/
		bool findBestPlacement(const SizeI size, CoordI& placement) const
		{
			assert(size.width >= 0 && size.height >= 0);

			CoordI bestPlacement(-1, -1);   // position of the best placement found
			int bestScore = _height;        // lower == better!

			// This is the counter for the currently checked position. The search works by
			// skipping from slice to slice, determining the suitability of the location for the
			// placement of the rectangle.
			ConstIterator itLeftSlice = _slices.begin();

			// Determine the slice in which the right end of the rectangle is located when
			// the rectangle is placed at the far left of the packing area.
			ConstIterator itRightSlice =
				std::lower_bound(_slices.begin(), _slices.end(), CoordI(size.width, 0), SliceStartComparer());

			// If we crossed the end of the slice array, the rectangle's right end has left
			// the packing area, and thus, our search ends.
			while (itRightSlice != _slices.end())
			{
				// Determine the highest slice within the slices covered by the rectangle at
				// its current placement. We cannot put the rectangle any lower than this without
				// overlapping the other rectangles.
				ConstIterator itHighestSlice = std::max_element(itLeftSlice, itRightSlice, SliceHeightComparer());
				int highest = itHighestSlice->y;

				// Only process this position if it doesn't leave the packing area
				if (highest + size.height <= _height)
				{
					int score = highest;
					if (score < bestScore)
					{
						bestPlacement.x = itLeftSlice->x;
						bestPlacement.y = highest;
						bestScore = score;
					}
				}

				// There are no better placement on the left of highest slice.
				itLeftSlice = itHighestSlice;

				// Advance the starting slice to the next slice start
				if (++itLeftSlice == _slices.end())
					break;

				// Advance the ending slice until we're on the proper slice again, given the new
				// starting position of the rectangle.
				int rightEnd = itLeftSlice->x + size.width;
				do
				{
					int rightSliceStart = itRightSlice->x;

					// Is this the slice we're looking for?
					if (rightSliceStart >= rightEnd)
						break;

				} while (++itRightSlice != _slices.end());
			}

			// Return the best placement we found for this rectangle. If the rectangle
			// didn't fit anywhere, the best placement will still have its initialization value
			// of (-1, -1) and we can report that no placement could be found.
			if (bestPlacement.x < 0 || bestPlacement.y < 0)
				return false;

			placement = bestPlacement;
			return true;
		}

		/** Integrates a new rectangle into the slice table.
		@param left
			Position of the rectangle's left side.
		@param width
			Width of the rectangle.
		@param bottom
			Position of the rectangle's lower side.
		*/
		void integrateRectangle(int left, int width, int bottom)
		{
			assert(width > 0);

			// Find the first slice that is touched by the rectangle
			Iterator itStartSlice =
				std::lower_bound(_slices.begin(), _slices.end(), CoordI(left, 0), SliceStartComparer());

			// Since the placement algorithm always places rectangles on the slices,
			// the binary search should never some up with a miss!
			assert(itStartSlice != _slices.end());
			assert(itStartSlice->x == left);
			assert(itStartSlice->y < bottom);

			// The right side of the rectangle
			int right = left + width;

			// Skip first slice
			++itStartSlice;

			// Find the last slice that is touched by the rectangle
			Iterator itEndSlice =
				std::lower_bound(itStartSlice, _slices.end(), CoordI(right, 0), SliceStartComparer());

			// Since we have highest slice at the end of slice table, so end slice should exists always
			assert(itEndSlice != _slices.end());

			// Record height of last slice
			int lastSliceHeight = _prior(itEndSlice)->y;

			// Remove all slices that fully covered by the rectangle.
			itStartSlice = _slices.erase(itStartSlice, itEndSlice);

			// Replace height of first slice
			_prior(itStartSlice)->y = bottom;

			// Insert new slice if last slice isn't fully covered
			if (right < itStartSlice->x)
			{
				_slices.insert(itStartSlice, CoordI(right, lastSliceHeight));
			}
		}
	};

	// ----------------------------------------------------------------------------
	class MYGUI_EXPORT ResourceTrueTypeFont :
		public IFont
	{
		MYGUI_RTTI_DERIVED( ResourceTrueTypeFont )

	public:
		ResourceTrueTypeFont();
		virtual ~ResourceTrueTypeFont();

		virtual void deserialization(xml::ElementPtr _node, Version _version);

		// Returns the glyph info for the specified code point, or the glyph info for a substitute glyph if the code point does not
		// exist in this font. Returns nullptr if there is a problem with the font.
		//virtual GlyphInfo* getGlyphInfo(Char _id);

		virtual bool getGlyphInfo(Char _id, GlyphInfo** _info);	//[2012/5/8 zhongdaohuan] 如果找不到_id那么返回值为false, _info返回默认值(是一个方框的info),如果_info为空，说明这个font有问题

		virtual ITexture* getTextureFont();

		// получившаяся высота при генерации в пикселях
		virtual int getDefaultHeight();

		// [2012/5/8 zhongdaohuan] 用于动态添加字体 ----------------
		virtual bool lock();
		virtual bool appendChar(Char _codePoint, GlyphInfo** _info);
		virtual void unlock();
		// ---------------------------------------------------------

		// Returns a collection of code-point ranges that are supported by this font. Each range is specified as [first, second];
		// for example, a range containing a single code point will have the same value for both first and second.
		std::vector<std::pair<Char, Char> > getCodePointRanges() const;

		// Returns the code point that is used as a substitute for code points that don't exist in the font. The default substitute
		// code point is FontCodeType::NotDefined, but it can be customized in the font definition file.
		Char getSubstituteCodePoint() const;


	private:
		void addCodePoint(Char _codePoint);
		void removeCodePoint(Char _codePoint);

		void addCodePointRange(Char _first, Char _second);
		void removeCodePointRange(Char _first, Char _second);

		void clearCodePoints();

		void initialise();

		// The following variables are set directly from values specified by the user.
		std::string mSource; // Source (filename) of the font.
		float mSize; // Size of the font, in points (there are 72 points per inch).
		uint mResolution; // Resolution of the font, in pixels per inch.
		bool mAntialias; // Whether or not to anti-alias the font by copying its alpha channel to its luminance channel.
		float mSpaceWidth; // The width of a "Space" character, in pixels. If zero, the default width is used.
		float mTabWidth; // The width of the "Tab" special character, in pixels.
		int mOffsetHeight; // How far up to nudge text rendered in this font, in pixels. May be negative to nudge text down.
		Char mSubstituteCodePoint; // The code point to use as a substitute for code points that don't exist in the font.

		// The following variables are calculated automatically.
		int mDefaultHeight; // The nominal height of the font in pixels.
		GlyphInfo* mSubstituteGlyphInfo; // The glyph info to use as a substitute for code points that don't exist in the font.
		MyGUI::ITexture* mTexture; // The texture that contains all of the rendered glyphs in the font.

		// The following constants used to be mutable, but they no longer need to be. Do not modify their values!
		static const int mGlyphSpacing; // How far apart the glyphs are placed from each other in the font texture, in pixels.
		static const float mSelectedWidth; // The width of the "Selected" and "SelectedBack" special characters, in pixels.
		static const float mCursorWidth; // The width of the "Cursor" special character, in pixels.

#ifdef MYGUI_USE_FREETYPE

	private:
		// A map of code points to glyph indices.
		typedef std::map<Char, FT_UInt> CharMap;

		// A map of glyph indices to glyph info objects.
		typedef std::map<FT_UInt, GlyphInfo> GlyphMap;

		// A map of glyph heights to the set of paired glyph indices and glyph info objects that are of that height.
		typedef std::map<FT_Pos, std::map<FT_UInt, GlyphInfo*> > GlyphHeightMap;

		template<bool LAMode, bool Antialias>
		void initialiseFreeType();

		// Loads the font face as specified by mSource, mSize, and mResolution. Automatically adjusts code-point ranges according
		// to the capabilities of the font face.
		// Returns a handle to the FreeType face object for the face, or nullptr if the face could not be loaded.
		// Keeps the font file loaded in memory and stores its location in _fontBuffer. The caller is responsible for freeing this
		// buffer when it is done using the face by calling delete[] on the buffer after calling FT_Done_Face() on the face itself.
		//FT_Face loadFace(const FT_Library& _ftLibrary, uint8*& _fontBuffer);

		FTFace* loadFace(const FT_Library& _ftLibrary); //[2012/5/28 zhongdaohuan]

		// Wraps the current texture coordinates _texX and _texY to the beginning of the next line if the specified glyph width
		// doesn't fit at the end of the current line. Automatically takes the glyph spacing into account.
		void autoWrapGlyphPos(int _glyphWidth, int _texWidth, int _lineHeight, int& _texX, int& _texY);

		// Creates a GlyphInfo object using the specified information.
		GlyphInfo createFaceGlyphInfo(Char _codePoint, int _fontAscent, FT_GlyphSlot _glyph);

		// Creates a glyph with the specified glyph index and assigns it to the specified code point.
		// Automatically updates _glyphHeightMap, mCharMap, and mGlyphMap with data from the new glyph..
		int createGlyph(FT_UInt _glyphIndex, const GlyphInfo& _glyphInfo, GlyphHeightMap& _glyphHeightMap);

		// Creates a glyph with the specified index from the specified font face and assigns it to the specified code point.
		// Automatically updates _glyphHeightMap with data from the newly created glyph.
		int createFaceGlyph(FT_UInt _glyphIndex, Char _codePoint, int _fontAscent, const FT_Face& _face, GlyphHeightMap& _glyphHeightMap);

		// Renders all of the glyphs in _glyphHeightMap into the specified texture buffer using data from the specified font face.
		template<bool LAMode, bool Antialias>
		void renderGlyphs(const GlyphHeightMap& _glyphHeightMap, const FT_Library& _ftLibrary, const FT_Face& _face, uint8* _texBuffer, int _texWidth, int _texHeight);

		// Renders the glyph described by the specified glyph info according to the specified parameters.
		// Supports two types of rendering, depending on the value of UseBuffer: Texture block transfer and rectangular color fill.
		// The _luminance0 value is used for even-numbered columns (from zero), while _luminance1 is used for odd-numbered ones.
		template<bool LAMode, bool UseBuffer, bool Antialias>
		void renderGlyph(GlyphInfo& _info, uint8 _luminance0, uint8 _luminance1, uint8 _alpha, int _lineHeight, uint8* _texBuffer, int _texWidth, int _texHeight, int& _texX, int& _texY, uint8* _glyphBuffer = nullptr);

		CharMap mCharMap; // A map of code points to glyph indices.
		GlyphMap mGlyphMap; // A map of glyph indices to glyph info objects.

		// ------------------ [2012/5/8 zhongdaohuan] ----------------------------------------------------;
		class FTLock
		{
		public:
			FTLock()
				:IsLock(false)
				,TexBuffer(nullptr)
				,FTBitmap(nullptr)
			{
			}
			bool IsLock;
			uint8* TexBuffer;
			FT_Bitmap* FTBitmap;
			
		} mFTLock;

		FTFactory* mFTFactory;		
		//FT_Face mFTFace;
		//uint8* mFTBuffer;
		FTFace* mFTFace;
		int mFontAscent;
		int mFontDescent;	
		bool mLaMode;

		StackRectanglePacker mTexturePacker;	// 字体纹理缓冲管理
		int mTextureWidth;						// 字体纹理缓冲的像素宽
		int mTextureHeight;						// 字体纹理缓冲的像素高
		bool mAutoTextureSize;					// 自动匹配纹理缓冲的大小,这通常是只能容下存在于预加载表中的字符



		//static const uint sMaxTextureBufferWidth;
		//static const uint sMaxTextureBufferHeight;
		static const int sDefaultTextureBufferWidth;
		static const int sDefaultTextureBufferHeight;


		//static std::list<string, FT_Face> sFaceList;

		// -----------------------------------------------------------------------------------------------
#endif // MYGUI_USE_FREETYPE

	};

} // namespace MyGUI

#endif // __MYGUI_RESOURCE_TRUE_TYPE_FONT_H__
