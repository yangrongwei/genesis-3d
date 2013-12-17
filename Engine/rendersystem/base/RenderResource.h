/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef RENDERRESOURCE_H_
#define RENDERRESOURCE_H_
#include "core/refcounted.h"
//------------------------------------------------------------------------------
namespace RenderBase
{
class RenderResource : public Core::RefCounted
{
    __DeclareClass(RenderResource);
public:
    /// resource usage flags
    enum Usage
    {
        UsageImmutable,      //> can only be read by GPU, not written, cannot be accessed by CPU
        UsageDynamic,        //> can only be read by GPU, can only be written by CPU
        UsageCpu,            //> a resource which is only accessible by the CPU and can't be used for rendering
    };

    // cpu access flags
    enum Access
    {
        AccessNone,         // CPU does not require access to the resource (best)
        AccessWrite,        // CPU has write access
        AccessRead,         // CPU has read access
        AccessReadWrite,    // CPU has read/write access
    };

    // mapping types
    enum MapType
    {
        MapRead,                // gain read access, must be UsageDynamic and AccessRead
        MapWrite,               // gain write access, must be UsageDynamic and AccessWrite
        MapReadWrite,           // gain read/write access, must be UsageDynamic and AccessReadWrite
        MapWriteDiscard,        // gain write access, discard previous content, must be UsageDynamic and AccessWrite
        MapWriteNoOverwrite,    // gain write access, must be UsageDynamic and AccessWrite, see D3D10 docs for details
    };

    /// constructor
    RenderResource();
    /// destructor
    virtual ~RenderResource();
	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

    /// set resource usage type
    void SetUsage(Usage usage);
    /// get resource usage type
    Usage GetUsage() const;
    /// set resource cpu access type
    void SetAccess(Access access);
    /// get cpu access type
    Access GetAccess() const;

protected:
	void copyFrom(const RenderResource& rr);
    Usage usage;
    Access access;
};

//------------------------------------------------------------------------------
/**
*/
inline void
RenderResource::SetUsage(Usage u)
{
    this->usage = u;
}

//------------------------------------------------------------------------------
/**
*/
inline RenderResource::Usage
RenderResource::GetUsage() const
{
    return this->usage;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderResource::SetAccess(Access a)
{
    this->access = a;
}

//------------------------------------------------------------------------------
/**
*/
inline RenderResource::Access
RenderResource::GetAccess() const
{
    return this->access;
}
//------------------------------------------------------------------------------
/**
*/
inline void
RenderResource::copyFrom(const RenderResource& rr)
{
	this->access = rr.access;
	this->usage = rr.usage;
}

} // namespace RenderBase
//------------------------------------------------------------------------------
#endif//RENDERRESOURCE_H_