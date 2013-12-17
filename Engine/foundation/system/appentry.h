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
#pragma once
//------------------------------------------------------------------------------
/**
    @class System::AppEntry
    
    Implements a platform-indepent app-entry point. In your main file,
    put the line
    
    ImplementNebulaApplication();
    
    And then replace your main() function with:
    
    void NebulaMain(const CommandLineArgs& args)
*/
#include "core/types.h"
#include "util/commandlineargs.h"

//------------------------------------------------------------------------------
#if __WIN32__
#define ImplementNebulaApplication() \
void NebulaMain(const Util::CommandLineArgs& args); \
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
{ \
    Util::CommandLineArgs args(lpCmdLine); \
    NebulaMain(args); \
    return 0; \
}
#elif __XBOX360__
#define ImplementNebulaApplication() \
void NebulaMain(const Util::CommandLineArgs& args); \
void __cdecl main() \
{ \
    Util::CommandLineArgs args; \
    NebulaMain(args); \
}
#elif __WII__
#define ImplementNebulaApplication() \
void NebulaMain(const Util::CommandLineArgs& args); \
void main() \
{ \
    Util::CommandLineArgs args; \
    NebulaMain(args); \
}
#elif __PS3__
// ps3gen.exe needs SYS_PROCESS_PARAM to burn DVD/BDVD (thread-prio and stack-size)
#define ImplementNebulaApplication() \
SYS_PROCESS_PARAM(1001, 65536);\
void NebulaMain(const Util::CommandLineArgs& args); \
int main() \
{ \
    Util::CommandLineArgs args; \
    NebulaMain(args); \
    return 0; \
}
#else
#define ImplementNebulaApplication() \
void NebulaMain(const Util::CommandLineArgs& args); \
int __cdecl main(int argc, const char** argv) \
{ \
    Util::CommandLineArgs args(argc, argv); \
    NebulaMain(args); \
    return 0; \
}
#endif
//------------------------------------------------------------------------------
