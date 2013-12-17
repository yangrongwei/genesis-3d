/****************************************************************************
Copyright (c) 2002, Radon Labs GmbH
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
#include "core/types.h"
#include "core/sysfunc.h"
#include "io/console.h"
#include "util/string.h"

//------------------------------------------------------------------------
__pCustomAssertCallback __pCustomAssertFunc = NULL;

//------------------------------------------------------------------------------
/**
    This function is called by n_assert() when the assertion fails.
*/
void 
n_barf(const char* exp, const char* file, int line)
{
    if (IO::Console::HasInstance())
    {
        n_error("*** GENESIS ASSERTION ***\nexpression: %s\nfile: %s\nline: %d\n", exp, file, line);
    }
    else
    {
    	Util::String msg;
    	msg.Format("*** GENESIS ASSERTION ***\nexpression: %s\nfile: %s\nline: %d\n", exp, file, line);
        Core::SysFunc::Error(msg.AsCharPtr());
    }
}

//------------------------------------------------------------------------------
/**
    This function is called by n_assert2() when the assertion fails.
*/
void
n_barf2(const char* exp, const char* msg, const char* file, int line)
{
    if (IO::Console::HasInstance())
    {
        n_error("*** GENESIS ASSERTION ***\nprogrammer says: %s\nexpression: %s\nfile: %s\nline: %d\n", msg, exp, file, line);
    }
    else
    {
    	Util::String excInfo;
    	excInfo.Format("*** GENESIS ASSERTION ***\nexpression: %s\ndetail:%s\nfile: %s\nline: %d\n", exp, msg, file, line);
        Core::SysFunc::Error(excInfo.AsCharPtr());
    }
}

//------------------------------------------------------------------------------
/**
    This function is called when a serious situation is encountered which
    requires abortion of the application.
*/

#if (_DEBUG || DEBUG || __WIN32__ ) && ( __WIN32__ ||__OSX__)
void __cdecl
n_error(const char* msg, ...)
{
	va_list argList;
	if (__pCustomAssertFunc)
	{
		va_start(argList, msg);
		Util::String str;
		str.FormatArgList(msg, argList);
		va_end(argList);
		__pCustomAssertFunc("n_error", str.AsCharPtr(), NULL, 0);
		
	}
	else
	{
		va_start(argList, msg);
		if (IO::Console::HasInstance())
		{
			IO::Console::Instance()->Error(msg, argList);
		}
		else
		{
			Util::String str;
			str.FormatArgList(msg, argList);
			Core::SysFunc::Error(str.AsCharPtr());
		}
		va_end(argList);
	}
}

//------------------------------------------------------------------------------
/**
    This function is called when a warning should be issued which doesn't
    require abortion of the application.
*/
void __cdecl
n_warning(const char* msg, ...)
{
    va_list argList;
    va_start(argList, msg);
    if (IO::Console::HasInstance())
    {
        IO::Console::Instance()->Warning(msg, argList);
    }
    else
    {
        Util::String str;
        str.FormatArgList(msg, argList);
        Core::SysFunc::MessageBox(str.AsCharPtr());
    }
    va_end(argList);
}        

//------------------------------------------------------------------------------
/**
    This function is called when a message should be displayed to the
    user which requires a confirmation (usually displayed as a MessageBox).
*/
void __cdecl
n_confirm(const char* msg, ...)
{
    va_list argList;
    va_start(argList, msg);
    if (IO::Console::HasInstance())
    {
        IO::Console::Instance()->Confirm(msg, argList);
    }
    else
    {
        Util::String str;
        str.FormatArgList(msg, argList);
        Core::SysFunc::MessageBox(str.AsCharPtr());
    }
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
    Nebula's printf replacement. Will redirect the text to the console
    and/or logfile.

     - 27-Nov-98   floh    created
*/
void __cdecl
n_printf(const char *msg, ...)
{
	va_list argList;
	va_start(argList, msg);
	IO::Console::Instance()->Print(msg, argList);
	va_end(argList);
}

//------------------------------------------------------------------------------
/**
    Put the message to the debug window.

    - 26-Mar-05    kims    created
*/
void __cdecl
n_dbgout(const char *msg, ...)
{
    va_list argList;
    va_start(argList,msg);
    IO::Console::Instance()->DebugOut(msg, argList);
    va_end(argList);
}
#endif

//------------------------------------------------------------------------------
/**
    Put process to sleep.

     - 21-Dec-98   floh    created
*/
void 
n_sleep(double sec)
{
    Core::SysFunc::Sleep(sec);
}

//------------------------------------------------------------------------

void n_setCustomAssert( __pCustomAssertCallback callback )
{
	__pCustomAssertFunc = callback;
}
//------------------------------------------------------------------------
#if (__NEBULA_NO_ASSERT__ == 0)
void n_custom_assert( const char* exp, const char* file, int line )
{
	if (__pCustomAssertFunc)
	{
		__pCustomAssertFunc("n_assert", exp, file, line);
	}
	else
	{
		n_barf(exp, file, line);
	}
}

void n_custom_assert2( const char* exp, const char* msg, const char* file, int line )
{
	if (__pCustomAssertFunc)
	{
		Util::String tmpExpMsg(exp);
		if (msg)
		{
			tmpExpMsg.Append(" , ");
			tmpExpMsg.Append(msg);
		}
		__pCustomAssertFunc("n_assert2", tmpExpMsg.AsCharPtr(), file, line);
	}
	else
	{
		n_barf2(exp, msg, file, line);
	}
}

#endif
//------------------------------------------------------------------------

