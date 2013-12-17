/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
//------------------------------------------------------------------------------
/**
    @class Base::SystemInfoBase
    
    Provide runtime-system-information.
*/
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Base
{
class SystemInfoBase
{
public:
    /// host platforms
    enum Platform
    {
        Win32,
        Xbox360,
        Wii,
        PS3,
        Android,
        UnknownPlatform,        
    };
    
    /// CPU types
    enum CpuType
    {
        X86_32,             // any 32-bit x86
        X86_64,             // any 64-bit x86
        PowerPC_Xbox360,    // Xbox 360 CPU
        PowerPC_PS3,        // PS3 Cell CPU
        PowerPC_Wii,        // Wii CPU
		ARM,                // Android
        UnknownCpuType,
    };

    /// constructor
    SystemInfoBase();

    /// get host platform
    Platform GetPlatform() const;
    /// get cpu type
    CpuType GetCpuType() const;
    /// get number of processors
    SizeT GetNumCpuCores() const;
    /// get page size
    SizeT GetPageSize() const;
    
    /// convert platform to string
    static Util::String PlatformAsString(Platform p);
    /// convert CpuType to string
    static Util::String CpuTypeAsString(CpuType cpu);

protected:
    Platform platform;
    CpuType cpuType;
    SizeT numCpuCores;
    SizeT pageSize;
};

//------------------------------------------------------------------------------
/**
*/
inline SystemInfoBase::Platform
SystemInfoBase::GetPlatform() const
{
    return this->platform;
}

//------------------------------------------------------------------------------
/**
*/
inline SystemInfoBase::CpuType
SystemInfoBase::GetCpuType() const
{
    return this->cpuType;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
SystemInfoBase::GetNumCpuCores() const
{
    return this->numCpuCores;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
SystemInfoBase::GetPageSize() const
{
    return this->pageSize;
}

} // namespace Base
//------------------------------------------------------------------------------
    
    