/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
    @file core/config.h

    Nebula3 compiler specific defines and configuration.
*/

// setup platform identification macros
#ifdef __XBOX360__
#undef __XBOX360__
#endif
#ifdef _XBOX
#define __XBOX360__ (1)
#endif

#ifdef __WIN32__
#undef __WIN32__
#endif
#ifdef WIN32
#define __WIN32__ (1)
#endif

#ifdef __PS3__
#undef __PS3__
#endif
#ifdef __CELLOS_LV2__
#define __PS3__ (1)
#endif

#ifdef __ANDROID__
#undef __ANDROID__
#endif
#ifdef ANDROID
#define __ANDROID__ (1)
#endif

#ifdef ANDROID
#undef _MSC_VER
#endif

#ifdef __APPLE__
#define __OSX__ (1)
#endif
//------------------------------------------------------------------------------
/**
    Nebula3 configuration.
*/

#ifdef _DEBUG
#define NEBULA3_DEBUG (1)
#endif

/// max size of a data slice is 16 kByte - 1 byte
/// this needs to be in a header, which is accessable from SPU too,
/// thats why its here
static const int JobMaxSliceSize = 0x3FFF;

#if __WII__
#define __WII_PROFILING__ (0)
#endif

#if PUBLIC_BUILD
#define __NEBULA_NO_ASSERT__ (0)    // DON'T SET THIS TO (1) - PUBLIC_BUILD SHOULD STILL DISPLAY ASSERTS!
#else
#define __NEBULA_NO_ASSERT__ (0)
#endif


// define whether a platform comes with archive support built into the OS
#if __PS3__
#define NEBULA3_NATIVE_ARCHIVE_SUPPORT (1)
#else
#define NEBULA3_NATIVE_ARCHIVE_SUPPORT (0)
#endif

// enable/disable Nebula3 memory stats
#if NEBULA3_DEBUG
#define NEBULA3_MEMORY_STATS (1)
#define NEBULA3_MEMORY_ADVANCED_DEBUGGING (0)
#else
#define NEBULA3_MEMORY_STATS (0) // not useable on xbox360 in release mode cause of HeapWalk
#define NEBULA3_MEMORY_ADVANCED_DEBUGGING (0)
#endif

// enable/disable memory pool allocation for refcounted object
// FIXME -> memory pool is disabled for all platforms, cause it causes crashes (reproducable on xbox360)
#if (__WII__ || __MAYA__ || __WIN32__ || __PS3__)
#define NEBULA3_OBJECTS_USE_MEMORYPOOL (0)
#else
#define NEBULA3_OBJECTS_USE_MEMORYPOOL (0)
#endif

// Enable/disable serial job system (ONLY SET FOR DEBUGGING!)
// You'll also need to fix the foundation_*.epk file to use the jobs/serial source files
// instead of jobs/tp!
// On the Wii, the serial job system is always active.
#define NEBULA3_USE_SERIAL_JOBSYSTEM (0)

// enable/disable thread-local StringAtom tables
#if (__WII__) || (__ANDROID__) || (__OSX__)
#define NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES (0)
#else
#define NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES (1)
#endif

// enable/disable growth of StringAtom buffer
#define NEBULA3_ENABLE_GLOBAL_STRINGBUFFER_GROWTH (1)

// size of of a chunk of the global string buffer for StringAtoms
#define NEBULA3_GLOBAL_STRINGBUFFER_CHUNKSIZE (32 * 1024)

// enable/disable Nebula3 animation system log messages
#define NEBULA3_ANIMATIONSYSTEM_VERBOSELOG (0)
#define NEBULA3_ANIMATIONSYSTEM_FRAMEDUMP (0)

// override SQLite filesystem functions with Nebula functions?
// only useful on consoles
// win32 doesn't work without !!!
#if __WIN32__
#define NEBULA3_OVERRIDE_SQLITE_FILEFUNCTIONS (1)
#else
#define NEBULA3_OVERRIDE_SQLITE_FILEFUNCTIONS (1)
#endif

// enable/disable bounds checking in the container util classes
#if NEBULA3_DEBUG
#define NEBULA3_BOUNDSCHECKS (1)
#else
#define NEBULA3_BOUNDSCHECKS (1)
#endif
 
// enable/disable the builtin HTTP server
#if PUBLIC_BUILD || __WII_PROFILING__
#define __NEBULA3_HTTP__ (0)
#else
#define __NEBULA3_HTTP__ (0)	
#endif

// enable/disable the transparent web filesystem
#if __WIN32__
#define __NEBULA3_HTTP_FILESYSTEM__ (1)
#else
#define __NEBULA3_HTTP_FILESYSTEM__ (0)
#endif

// enable/disable profiling (see Debug::DebugTimer, Debug::DebugCounter)
#if PUBLIC_BUILD
#define NEBULA3_ENABLE_PROFILING (0)
#elif __NEBULA3_HTTP__
// profiling needs http
#define NEBULA3_ENABLE_PROFILING (1)
#else 
#define NEBULA3_ENABLE_PROFILING (0)
#endif

// max length of a path name
#define NEBULA3_MAXPATH (512)

// enable/disable support for Nebula2 file formats and concepts
#define NEBULA3_LEGACY_SUPPORT (1)

// enable/disable mini dumps
#define NEBULA3_ENABLE_MINIDUMPS (1)

// enable/disable debug messages in fmod coreaudio
#define NEBULA3_FMOD_COREAUDIO_VERBOSE_ENABLED  (0)

// enable fmod profiling feature
#define NEBULA3_FMOD_ENABLE_PROFILING (0)

// Nebula3's main window class
#define NEBULA3_WINDOW_CLASS "Nebula3::MainWindow"

// number of lines in the IO::HistoryConsoleHandler ring buffer
#if __WII__
#define NEBULA3_CONSOLE_HISTORY_SIZE (64)
#else
#define NEBULA3_CONSOLE_HISTORY_SIZE (256)
#endif

// maximum number of local players for local coop games
#define NEBULA3_MAX_LOCAL_PLAYERS (4)

// use raknet on xbox360 platform?
#define XBOX360_USE_RAKNET    (0)

// enable legacy support for database vectors (vector3/vector4 stuff)
#define NEBULA3_DATABASE_LEGACY_VECTORS (1)

// enable legacy support for 3-component vectors in XML files
#define NEBULA3_XMLREADER_LEGACY_VECTORS (1)

#define DEFAULT_IO_SCHEME "file"


// VisualStudio settings
#ifdef _MSC_VER
#define __VC__ (1)
#endif
#ifdef __VC__
#pragma warning( disable : 4251 )       // class XX needs DLL interface to be used...
#pragma warning( disable : 4355 )       // initialization list uses 'this' 
#pragma warning( disable : 4275 )       // base class has not dll interface...
#pragma warning( disable : 4786 )       // symbol truncated to 255 characters
#pragma warning( disable : 4530 )       // C++ exception handler used, but unwind semantics not enabled
#pragma warning( disable : 4995 )       // _OLD_IOSTREAMS_ARE_DEPRECATED
#pragma warning( disable : 4996 )       // _CRT_INSECURE_DEPRECATE, VS8: old string routines are deprecated
#pragma warning( disable : 4512 )       // 'class' : assignment operator could not be generated
#pragma warning( disable : 4610 )       // object 'class' can never be instantiated - user-defined constructor required
#pragma warning( disable : 4510 )       // 'class' : default constructor could not be generated
#endif

// CodeWarrior settings
#ifdef __MWERKS__
#pragma warning off (10216)     // illegal empty declaration used ( ; ; )
#pragma warning off (10317)     
#pragma warning off (10342)     // ...not inlined
#pragma warning off (10182)     // arg not used in function 
#pragma warning off (10358)     // illegal or unsupported __attribute__
#endif

// GCC settings
#if defined __GNUC__
#define __cdecl
#define __forceinline inline
#endif

#if !defined(__GNUC__) && !defined(__WII__)
#define  __attribute__(x)  /**/
#endif




//------------------------------------------------------------------------------
