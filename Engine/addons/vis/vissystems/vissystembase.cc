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
#include "vis/vissystems/vissystembase.h"

namespace Vis
{
__ImplementClass(Vis::VisSystemBase, 'VISS', Core::RefCounted);
         
using namespace Util;
using namespace Math;

//------------------------------------------------------------------------------
/**
*/
VisSystemBase::VisSystemBase() 
	: isOpen(false)
	, orderIndex(InvalidIndex)
{
}

//------------------------------------------------------------------------------
/**
*/
VisSystemBase::~VisSystemBase()
{
    n_assert(!this->isOpen);
}

//------------------------------------------------------------------------------
/**
*/
void
VisSystemBase::Open(IndexT orderIndex)
{
    n_assert(!this->isOpen);
    this->isOpen = true;
	this->orderIndex = orderIndex;
}

//------------------------------------------------------------------------------
/**
*/
void
VisSystemBase::Close()
{
    n_assert(this->isOpen);
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void 
VisSystemBase::InsertVisEntity(const GPtr<VisEntity>& entityVis)
{
    // implement in derived class
    n_error("VisibilitySystemBase::InsertVisibilityContext: Implement in derived class!");
}

//------------------------------------------------------------------------------
/**
*/
void 
VisSystemBase::RemoveVisEntity(const GPtr<VisEntity>& entityVis)
{
    // implement in derived class
    n_error("VisibilitySystemBase::RemoveVisibilityContext: Implement in derived class!");
}

//------------------------------------------------------------------------------
/**
*/
void 
VisSystemBase::UpdateVisEntity(const GPtr<VisEntity>& entityVis)
{       
    // implement in derived class
    n_error("VisibilitySystemBase::UpdateVisibilityContext: Implement in derived class!");
}
//------------------------------------------------------------------------
SizeT 
VisSystemBase::GetNumEntity()
{
	n_error("VisibilitySystemBase::GetNumEntity: Implement in derived class!");
	return 0;
}

//------------------------------------------------------------------------------
/**
*/
void 
VisSystemBase::OnRenderDebug()
{       
    // implement in derived class
    n_error("VisibilitySystemBase::OnRenderDebug: Implement in derived class!");
}

//------------------------------------------------------------------------------
/**
*/
GPtr<Jobs::Job>
VisSystemBase::CreateVisJob( const GPtr<ObserverContext>& observer, Util::Array<GPtr<VisEntity> >& outEntitiyArray )
{
    // implement in subclass
    n_error("VisibilitySystemBase::AttachVisibilityJob called: Implement in subclass! Do it!");

    GPtr<Jobs::Job> result;
    return result;
}

} // namespace Vis
