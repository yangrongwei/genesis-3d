/****************************************************************************
Copyright (c) 2010,Radon Labs GmbH
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
#include "vis/visentity.h"

namespace Vis
{
__ImplementClass(Vis::VisEntity, 'VIET', Core::RefCounted);

using namespace Util;
using namespace Math;

const int VisEntity::MAX_VIS_SYSTEM_COUNT = 4;
//------------------------------------------------------------------------------
/**
*/
VisEntity::VisEntity()
	: mUserData(NULL)
	, mCustomUserData(NULL)
	, mCells(MAX_VIS_SYSTEM_COUNT, NULL )
{
}

//------------------------------------------------------------------------------
/**
*/
VisEntity::~VisEntity()
{
	mUserData = NULL;
	mCustomUserData = NULL;
	mCells.Clear();
}

//------------------------------------------------------------------------------
/**
*/
void 
VisEntity::Setup(const Math::bbox& box, UserData* userData)
{
	this->mBoundingBox = box;
    this->mUserData = userData;
}
//--------------------------------------------------------------------------------
//void VisEntity::Setup(const Math::bbox& box,  void* userData )
//{
//	this->mBoundingBox = box;
//	this->mCustomUserData = userData;
//}

//------------------------------------------------------------------------------
/**
*/
void 
VisEntity::UpdateBoundingBox(const Math::bbox& box)
{
    this->mBoundingBox = box;
}
} // namespace Vis
