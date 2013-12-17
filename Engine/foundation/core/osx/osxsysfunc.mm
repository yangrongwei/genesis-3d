/****************************************************************************
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
#include "osxsysfunc.h"
#include "system/systeminfo.h"
#include "util/globalstringatomtable.h"
#include "threading/thread.h"
#include "util/localstringatomtable.h"  

namespace OSX
{

	bool volatile SysFunc::SetupCalled = false;
	const Core::ExitHandler* SysFunc::ExitHandlers = 0;
	System::SystemInfo SysFunc::systemInfo;

	Util::GlobalStringAtomTable* globalStringAtomTable = 0;
#if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
	Util::LocalStringAtomTable* localStringAtomTable = 0;
#endif


	void SysFunc::Setup()
	{
		if (!SetupCalled)
		{
			SetupCalled = true;
			Memory::SetupHeaps();

			Threading::Thread::SetupMyThreadRunTime("MainThread");

			Memory::Heap::Setup();


			globalStringAtomTable = n_new(Util::GlobalStringAtomTable);
#if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
			localStringAtomTable = n_new(Util::LocalStringAtomTable);
#endif
		}
	

	}

	void SysFunc::Exit(int exitCode)
	{
		// delete string atom tables
		n_delete(globalStringAtomTable);
#if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
		n_delete(localStringAtomTable);
#endif

		// call exit handlers
		const Core::ExitHandler* exitHandler = SysFunc::ExitHandlers;
		while (0 != exitHandler)
		{
			exitHandler->OnExit();
			exitHandler = exitHandler->Next();
		}

		// shutdown global factory object
		Core::Factory::Destroy();

		exit(0);
	}
	
	void SysFunc::Error(const char* error)
	{
		NSLog(@"\nError:%s",error);
        abort();
	}

	void SysFunc::MessageBox(const char* msg)
	{
		return;
	}

	void SysFunc::DebugOut(const char* msg)
	{
        NSLog(@"\nWarning:%s",msg);
		return;
	}

	void SysFunc::Sleep(double sec)
	{
		return;
	}

	const Core::ExitHandler*
		SysFunc::RegisterExitHandler(const Core::ExitHandler* exitHandler)
	{
		const Core::ExitHandler* firstHandler = ExitHandlers;
		ExitHandlers = exitHandler;
		return firstHandler;
	}

	const System::SystemInfo*
		SysFunc::GetSystemInfo()
	{
		return &SysFunc::systemInfo;
	}
}