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
#include "stdneb.h"
#include "io/debug/iopagehandler.h"
#include "http/html/htmlpagewriter.h"
#include "io/ioserver.h"
#include "io/archfs/archivefilesystem.h"
#include "io/archfs/archive.h"
#include "io/console.h"

namespace Debug
{
__ImplementClass(Debug::IoPageHandler, 'DIOP', Http::HttpRequestHandler);

using namespace Http;
using namespace IO;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
IoPageHandler::IoPageHandler()
{
    this->SetName("IO");
    this->SetDesc("show debug information about IO subsystem");
    this->SetRootLocation("inout");
}

//------------------------------------------------------------------------------
/**
*/
void
IoPageHandler::HandleRequest(const GPtr<HttpRequest>& request) 
{
    n_assert(HttpMethod::Get == request->GetMethod());

    // first check if a command has been defined in the URI
    Dictionary<String,String> query = request->GetURI().ParseQuery();
    if (query.Contains("ls"))
    {
        this->ListDirectory(query["ls"], request);
        return;
    }

    // no command, display root page
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Genesis IO Subsystem Info");
    if (htmlWriter->Open())
    {
        AssignRegistry* assignRegistry = AssignRegistry::Instance();
        SchemeRegistry* schemeRegistry = SchemeRegistry::Instance();
        htmlWriter->Element(HtmlElement::Heading1, "IO Subsystem");
        htmlWriter->AddAttr("href", "/index.html");
        htmlWriter->Element(HtmlElement::Anchor, "Home");

        // display registered URI schemes
        htmlWriter->Element(HtmlElement::Heading3, "Registered Schemes");
        htmlWriter->Begin(HtmlElement::Table);
        Array<String> uriSchemes = schemeRegistry->GetAllRegisteredUriSchemes();
        IndexT schemeIndex;
        for (schemeIndex = 0; schemeIndex < uriSchemes.Size(); schemeIndex++)
        {
            htmlWriter->Begin(HtmlElement::TableRow);
            htmlWriter->Element(HtmlElement::TableData, uriSchemes[schemeIndex]);
            htmlWriter->Element(HtmlElement::TableData, schemeRegistry->GetStreamClassByUriScheme(uriSchemes[schemeIndex]).GetName());
            htmlWriter->End(HtmlElement::TableRow);
        }
        htmlWriter->End(HtmlElement::Table);
        
        // display registered assigns
        htmlWriter->Element(HtmlElement::Heading3, "Registered Assigns");
        htmlWriter->Begin(HtmlElement::Table);
        Array<Assign> assigns = assignRegistry->GetAllAssigns();
        IndexT assignIndex;
        for (assignIndex = 0; assignIndex < assigns.Size(); assignIndex++)
        {
            htmlWriter->Begin(HtmlElement::TableRow);
            htmlWriter->Begin(HtmlElement::TableData);
                htmlWriter->AddAttr("href", "/inout?ls=" + assigns[assignIndex].GetName() + ":");
                htmlWriter->Element(HtmlElement::Anchor, assigns[assignIndex].GetName());
            htmlWriter->End(HtmlElement::TableData);
            htmlWriter->Element(HtmlElement::TableData, assigns[assignIndex].GetPath());
            htmlWriter->Element(HtmlElement::TableData, assignRegistry->ResolveAssigns(assigns[assignIndex].GetPath()).AsString());
            htmlWriter->End(HtmlElement::TableRow);
        }
        htmlWriter->End(HtmlElement::Table);

        // display mounted archives
        htmlWriter->Element(HtmlElement::Heading3, "Mounted Archives");
        Array<GPtr<Archive> > archives = ArchiveFileSystem::Instance()->GetMountedArchives();
        if (archives.Size() > 0)
        {
            htmlWriter->Begin(HtmlElement::UnorderedList);
            IndexT arcIndex;
            for (arcIndex = 0; arcIndex < archives.Size(); arcIndex++)
            {
                htmlWriter->Element(HtmlElement::ListItem, archives[arcIndex]->GetURI().AsString());
            }
            htmlWriter->End(HtmlElement::UnorderedList);
        }
        else
        {
            htmlWriter->Text("[NONE]");
        }

        // display attached console handlers
        htmlWriter->Element(HtmlElement::Heading3, "Attached Console Handlers");
        htmlWriter->Begin(HtmlElement::UnorderedList);
        Array<GPtr<ConsoleHandler> > handlers = Console::Instance()->GetHandlers();
        IndexT conHandlerIndex;
        for (conHandlerIndex = 0; conHandlerIndex < handlers.Size(); conHandlerIndex++)
        {
            htmlWriter->Element(HtmlElement::ListItem, handlers[conHandlerIndex]->GetClassName());
        }
        htmlWriter->End(HtmlElement::UnorderedList);
        htmlWriter->Close();
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
IoPageHandler::ListDirectory(const Util::String& path, const GPtr<HttpRequest>& request)
{
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Genesis Directory Listing");
    if (htmlWriter->Open())
    {
        IoServer* ioServer = IoServer::Instance();        
        AssignRegistry* assignRegistry = AssignRegistry::Instance();
        htmlWriter->Element(HtmlElement::Heading1, "Directory Listing");
        htmlWriter->AddAttr("href", "/index.html");
        htmlWriter->Element(HtmlElement::Anchor, "Home");
        htmlWriter->LineBreak();
        htmlWriter->AddAttr("href", "/inout");
        htmlWriter->Element(HtmlElement::Anchor, "IO Subsystem Home");
        htmlWriter->LineBreak();
        if (path[path.Length() - 1] != ':')
        {
            // add parent directory navigation entry (if not top-level)
            String str = "/inout?ls=" + path.ExtractDirName();
            str.TrimRight("/");
            htmlWriter->AddAttr("href", str);
            htmlWriter->Element(HtmlElement::Anchor, "Parent Directory");
        }
        htmlWriter->LineBreak();
        
        htmlWriter->Element(HtmlElement::Heading3, path + "    (" + assignRegistry->ResolveAssigns(path).AsString() + ")");
        Array<String> dirs = ioServer->ListDirectories(path, "*");
        Array<String> files = ioServer->ListFiles(path, "*");

        htmlWriter->Begin(HtmlElement::UnorderedList);
        IndexT i;
        for (i = 0; i < dirs.Size(); i++)
        {
            htmlWriter->Begin(HtmlElement::ListItem);
            if (path[path.Length() - 1] == ':')
            {
                // don't add a slash right after an assign
                htmlWriter->AddAttr("href", "/inout?ls=" + path + dirs[i]);
            }
            else
            {                   
                htmlWriter->AddAttr("href", "/inout?ls=" + path + "/" + dirs[i]);
            }
            htmlWriter->Element(HtmlElement::Anchor, dirs[i]);
            htmlWriter->End(HtmlElement::ListItem);
        }
        for (i = 0; i < files.Size(); i++)
        {
            htmlWriter->Element(HtmlElement::ListItem, files[i]);
        }
        htmlWriter->End(HtmlElement::UnorderedList);

        htmlWriter->Close();
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

} // namespace Debug
