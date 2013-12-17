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
#include "stdneb.h"
#include "io/logfileconsolehandler.h"
#include "io/ioserver.h"
#include "timing/calendartime.h"
#include "core/coreserver.h"

namespace IO
{
__ImplementClass(IO::LogFileConsoleHandler, 'LFCH', IO::ConsoleHandler);

using namespace Util;
using namespace Timing;

//------------------------------------------------------------------------------
/**
*/
LogFileConsoleHandler::LogFileConsoleHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
LogFileConsoleHandler::~LogFileConsoleHandler()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::Open()
{
    ConsoleHandler::Open();
    IoServer* ioServer = IoServer::Instance();

    // make sure log directory exists
    ioServer->CreateDirectory("home:logfiles");

    // build a file name for the log file
    String calString = CalendarTime::Format("{YEAR}_{MONTH}_{DAY}_{HOUR}_{MINUTE}_{SECOND}", CalendarTime::GetLocalTime());
    String fileName;
    fileName.Format("home:logfiles/%s_%s.txt", Core::CoreServer::Instance()->GetAppName().Value(), calString.AsCharPtr());

    // open file stream
    this->stream = ioServer->CreateFileStream(URI(fileName));
    this->textWriter = TextWriter::Create();
    this->textWriter->SetStream(this->stream);
    this->textWriter->Open();
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::Close()
{
    n_assert(this->IsOpen());

    if (this->textWriter->IsOpen())
    {
        this->textWriter->Close();
    }
    this->textWriter = 0;
    this->stream = 0;
    
    ConsoleHandler::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::Print(const String& s)
{
    if (this->textWriter->IsOpen())
    {
        this->textWriter->WriteString(s);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::Error(const String& s)
{
    if (this->textWriter->IsOpen())
    {
        String str("[ERROR] ");
        str.Append(s);
        this->textWriter->WriteString(str);
        this->stream->Flush();
    }
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::Warning(const String& s)
{
    if (this->textWriter->IsOpen())
    {
        String str("[WARNING] ");
        str.Append(s);
        this->textWriter->WriteString(str);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
LogFileConsoleHandler::DebugOut(const String& s)
{
    if (this->textWriter->IsOpen())
    {
        String str("[DEBUGOUT] ");
        str.Append(s);
        this->textWriter->WriteString(str);
    }
}

} // namespace IO
