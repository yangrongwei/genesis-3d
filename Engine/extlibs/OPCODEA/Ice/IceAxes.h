///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains axes definition.
 *	\file		IceAxes.h
 *	\author		Pierre Terdiman
 *	\date		January, 29, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEAXES_H__
#define __ICEAXES_H__

	enum PointComponent
	{
		_XOP					= 0,
		_YOP					= 1,
		_ZOP					= 2,
		_WOP					= 3,

		_FORCE_DWORD		= 0x7fffffff
	};

	enum AxisOrder
	{
		AXES_XYZ			= (_XOP)|(_YOP<<2)|(_ZOP<<4),
		AXES_XZY			= (_XOP)|(_ZOP<<2)|(_YOP<<4),
		AXES_YXZ			= (_YOP)|(_XOP<<2)|(_ZOP<<4),
		AXES_YZX			= (_YOP)|(_ZOP<<2)|(_XOP<<4),
		AXES_ZXY			= (_ZOP)|(_XOP<<2)|(_YOP<<4),
		AXES_ZYX			= (_ZOP)|(_YOP<<2)|(_XOP<<4),

		AXES_FORCE_DWORD	= 0x7fffffff
	};

	class ICEMATHS_API Axes
	{
		public:

		inline_			Axes(AxisOrder order)
						{
							mAxis0 = (order   ) & 3;
							mAxis1 = (order>>2) & 3;
							mAxis2 = (order>>4) & 3;
						}
		inline_			~Axes()		{}

				udword	mAxis0;
				udword	mAxis1;
				udword	mAxis2;
	};

#endif // __ICEAXES_H__
