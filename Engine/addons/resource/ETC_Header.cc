/*
* This confidential and proprietary software may be used only as
* authorised by a licensing agreement from ARM Limited
* (C) COPYRIGHT 2012 ARM Limited
* ALL RIGHTS RESERVED
* The entire notice above must be reproduced on all authorised
* copies and copies may only be made to the extent permitted
* by a licensing agreement from ARM Limited.
*/
#include "stdneb.h"
#include "ETC_Header.h"

ETCHeader::ETCHeader(unsigned char *data)
{
	/*
	* Load from a ETC compressed pkm image file. 
	* First 6 bytes are the name of the file format and version/packing type.
	* Bytes 7 and 8 are blank.
	*/
	/* Beware endianess issues with most/least significant bits of the height and width. */
	paddedWidthMSB = data[8];
	paddedWidthLSB = data[9];
	paddedHeightMSB = data[10];
	paddedHeightLSB = data[11];
	widthMSB = data[12];
	widthLSB = data[13];
	heightMSB = data[14];
	heightLSB = data[15];
}

unsigned short ETCHeader::getWidth(void)
{
	return (widthMSB << 8) | widthLSB;
}

unsigned short ETCHeader::getHeight(void)
{
	return (heightMSB << 8) | heightLSB;
}

unsigned short ETCHeader::getPaddedWidth(void)
{
	return (paddedWidthMSB << 8) | paddedWidthLSB;
}

unsigned short ETCHeader::getPaddedHeight(void)
{
	return (paddedHeightMSB << 8) | paddedHeightLSB;
}
