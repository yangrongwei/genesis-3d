//
//  Todo.cpp
//  FreeImage
//
//  Created by zhaopeng on 13-6-24.
//  Copyright (c) 2013年 webJet. All rights reserved.
//

#include "Freeimage.h"
#include <stdio.h>

void ShowError(const char* error)
{
    printf( "Using Undefined function %s", error );
}


DLL_API BOOL DLL_CALLCONV FreeImage_Invert(FIBITMAP *dib)
{
    ShowError( "FreeImage_Invert" );
    return false;
}


DLL_API FIBITMAP *DLL_CALLCONV FreeImage_Rotate(FIBITMAP *dib, double angle, const void *bkcolor )
{
    ShowError( "FreeImage_Rotate" );
    return NULL;
}

DLL_API FIBITMAP *DLL_CALLCONV FreeImage_GetChannel(FIBITMAP *dib, FREE_IMAGE_COLOR_CHANNEL channel)
{
    ShowError( "FreeImage_GetChannel" );
    return NULL;
}

DLL_API BOOL DLL_CALLCONV FreeImage_SetChannel(FIBITMAP *dst, FIBITMAP *src, FREE_IMAGE_COLOR_CHANNEL channel)
{
    ShowError( "FreeImage_SetChannel" );
    return false;
}

DLL_API BOOL DLL_CALLCONV FreeImage_FlipHorizontal(FIBITMAP *dib)
{
    ShowError( "FreeImage_FlipHorizontal" );
    return false;
}

DLL_API BOOL DLL_CALLCONV FreeImage_FlipVertical(FIBITMAP *dib)
{
    ShowError( "FreeImage_FlipVertical" );
    return false;
}