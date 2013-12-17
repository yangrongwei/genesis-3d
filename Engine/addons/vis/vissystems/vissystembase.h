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
#ifndef __vissystembase_H__
#define __vissystembase_H__
#include "core/refcounted.h"
#include "vis/observercontext.h"
#include "vis/visentity.h"
#include "jobs/jobport.h"
              
//------------------------------------------------------------------------------
namespace Vis
{    

class VisSystemBase : public Core::RefCounted
{
    __DeclareClass(VisSystemBase);
public:
    /// constructor
    VisSystemBase();
    /// destructor
    virtual ~VisSystemBase();
    
    /// open the graphics server
    virtual void Open(IndexT orderIndex);
    /// close the graphics server
    virtual void Close(void);
    /// return true if graphics server is open
    bool IsOpen(void) const;

    /// insert entity visibility
    virtual void InsertVisEntity(const GPtr<VisEntity>& entityVis);
    /// remove entity visibility
    virtual void RemoveVisEntity(const GPtr<VisEntity>& entityVis);
    /// update entity visibility
    virtual void UpdateVisEntity(const GPtr<VisEntity>& entityVis);
	/// get the num of entity in visibility system
	virtual SizeT GetNumEntity();

    /// attach visibility job to port
    virtual GPtr<Jobs::Job> CreateVisJob(const GPtr<ObserverContext>& observer, Util::Array<GPtr<VisEntity> >& outResultArray );
    /// render debug visualizations
    virtual void OnRenderDebug(void);    

	/// get OrderIndex of this VisSystem
	IndexT OrderIndex() const;

protected:  
    bool isOpen; 
	IndexT orderIndex;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
VisSystemBase::IsOpen() const
{
    return this->isOpen;
}
//------------------------------------------------------------------------
inline
IndexT 
VisSystemBase::OrderIndex() const
{
	return orderIndex;
}
} // namespace Vis
//------------------------------------------------------------------------------

#endif

