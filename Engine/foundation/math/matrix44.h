/****************************************************************************
Copyright (c) 2006,RadonLabs GmbH
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

#pragma once
#ifndef MATH_MATRIX44_H
#define MATH_MATRIX44_H
//------------------------------------------------------------------------------
/**
    @file math/matrix44.h

    Frontend header for matrix classes.

    (C) 2006 Radon Labs GmbH
*/
#if __WIN32__ || __XBOX360__ || __ANDROID__ || __OSX__
#include "math/newMath/new_matrix44.h"
#elif __WII__
#include "math/wii/wii_matrix44.h"
#elif __PS3__
#include "math/ps3/ps3matrix44.h"
#else
#error "matrix44 class not implemented!"
#endif
//-------------------------------------------------------------------
#endif
