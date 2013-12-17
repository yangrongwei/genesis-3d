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
#include "stdneb.h"
#include "io/uri.h"
#include "io/ioserver.h"
#include "io/fswrapper.h"
#include "core/config.h"

namespace IO
{
using namespace Util;

//------------------------------------------------------------------------------
/**
    Resolve assigns and split URI string into its components.

    @todo: this is too complicated...
*/
bool
URI::Split(const String& s)
{
    n_assert(s.IsValid());
    this->Clear();
    this->isEmpty = false;
    
    // resolve assigns
    String str;
    if (AssignRegistry::HasInstance())
    {
        str = AssignRegistry::Instance()->ResolveAssignsInString(s);
    }
    else
    {
        str = s;
    }

    // scheme is the first components and ends with a :
    IndexT schemeColonIndex = str.FindCharIndex(':');
    String potentialScheme;
    bool schemeIsDevice = false;
    if (InvalidIndex != schemeColonIndex)
    {
        potentialScheme = str.ExtractRange(0, schemeColonIndex);
        if (FSWrapper::IsDeviceName(potentialScheme))
        {
            // there is either no scheme given, or the "scheme"
            // is actually a device name
            // in both cases we fall back to the default scheme "file", and
            // just set the whole string as local path, there will be no
            // other components
            schemeIsDevice = true;
        }
    }
    if ((InvalidIndex == schemeColonIndex) || schemeIsDevice)
    {
        this->SetScheme(DEFAULT_IO_SCHEME);
        this->SetLocalPath(str);
        return true;
    }

    // check is a valid scheme was provided
    if (InvalidIndex != schemeColonIndex)
    {
        // a valid scheme is given
        this->SetScheme(potentialScheme);

        // after the scheme, and before the host, there must be a double slash
        if (!((str[schemeColonIndex + 1] == '/') && (str[schemeColonIndex + 2] == '/')))
        {
			this->SetScheme(DEFAULT_IO_SCHEME);
			this->SetLocalPath(str);
			return true;
        }
    }

    // extract UserInfo, Host and Port components
    IndexT hostStartIndex = schemeColonIndex + 3;
    IndexT hostEndIndex = str.FindCharIndex('/', hostStartIndex);
    String userInfoHostPort;
    String path;
    if (InvalidIndex == hostEndIndex)
    {
        userInfoHostPort = str.ExtractToEnd(hostStartIndex);
    }
    else
    {
        userInfoHostPort = str.ExtractRange(hostStartIndex, hostEndIndex - hostStartIndex);
        path = str.ExtractToEnd(hostEndIndex + 1);
    }

    // extract port number if exists
    IndexT portIndex = userInfoHostPort.FindCharIndex(':');
    IndexT atIndex = userInfoHostPort.FindCharIndex('@');
    if (InvalidIndex != portIndex)
    {
        if (InvalidIndex != atIndex)
        {
            n_assert(portIndex > atIndex);
        }
        this->SetPort(userInfoHostPort.ExtractToEnd(portIndex + 1));
        userInfoHostPort.TerminateAtIndex(portIndex);
    }
    if (InvalidIndex != atIndex)
    {
        this->SetHost(userInfoHostPort.ExtractToEnd(atIndex + 1));
        userInfoHostPort.TerminateAtIndex(atIndex);
        this->SetUserInfo(userInfoHostPort);
    }
    else
    {
        this->SetHost(userInfoHostPort);
    }

    // split path part into components
    if (path.IsValid())
    {
        IndexT fragmentIndex = path.FindCharIndex('#');
        IndexT queryIndex = path.FindCharIndex('?');
        if (InvalidIndex != queryIndex)
        {
            if (InvalidIndex != fragmentIndex)
            {
                n_assert(queryIndex > fragmentIndex);
            }
            this->SetQuery(path.ExtractToEnd(queryIndex + 1));
            path.TerminateAtIndex(queryIndex);
        }
        if (InvalidIndex != fragmentIndex)
        {
            this->SetFragment(path.ExtractToEnd(fragmentIndex + 1));
            path.TerminateAtIndex(fragmentIndex);
        }
        this->SetLocalPath(path);
    }
    return true;
}

//------------------------------------------------------------------------------
/**
    This builds an URI string from its components.
*/
String
URI::Build() const
{
    n_assert(!this->IsEmpty());

    String str;
    str.Reserve(256);
    if (this->scheme.IsValid())
    {
        str.Append(this->scheme);
        str.Append("://");
    }
    if (this->userInfo.IsValid())
    {
        str.Append(this->userInfo);
        str.Append("@");
    }
    if (this->host.IsValid())
    {
        str.Append(this->host);
    }
    if (this->port.IsValid())
    {
        str.Append(":");
        str.Append(this->port);
    }
    if (this->localPath.IsValid())
    {
        str.Append("/");
        str.Append(this->localPath);
    }
    if (this->fragment.IsValid())
    {
        str.Append("#");
        str.Append(this->fragment);
    }
    if (this->query.IsValid())
    {
        str.Append("?");
        str.Append(this->query);
    }
    return str;
}

//------------------------------------------------------------------------------
/**
    This returns the "tail", which is the local path, the fragment and
    the query concatenated into one string.
*/
String
URI::GetTail() const
{   
    String str;
    str.Reserve(256);
    if (this->localPath.IsValid())
    {
        str.Append(this->localPath);
    }
    if (this->fragment.IsValid())
    {
        str.Append("#");
        str.Append(this->fragment);
    }
    if (this->query.IsValid())
    {
        str.Append("?");
        str.Append(this->query);
    }
    return str;
}

//------------------------------------------------------------------------------
/**
    Returns the host and local path in the form "//host/localpath".
    If no host has been set, only "/localpath" will be returned.
*/
String
URI::GetHostAndLocalPath() const
{
    String str;
    str.Reserve(this->host.Length() + this->localPath.Length() + 8);
    if (this->host.IsValid())
    {
        str.Append("//");
        str.Append(this->host);
        str.Append("/");
    }
    str.Append(this->localPath);
    return str;
}

//------------------------------------------------------------------------------
/**
    Appends an element to the local path. Automatically inserts
    a path delimiter "/".
*/
void
URI::AppendLocalPath(const String& pathComponent)
{
    n_assert(pathComponent.IsValid());
    this->localPath.Append("/");
    this->localPath.Append(pathComponent);
}

//------------------------------------------------------------------------------
/**
    This parses the query part of the URI (in the form
    param1=value&param2=value&param3=value ...) into a dictionary. Ill-formatted
    query fragments will be ignored.
*/
Dictionary<String,String>
URI::ParseQuery() const
{
    Dictionary<String,String> result;
    Array<String> keyValuePairs = this->query.Tokenize("&");
    IndexT i;
    for (i = 0; i < keyValuePairs.Size(); i++)
    {
        Array<String> keyValueTokens = keyValuePairs[i].Tokenize("=");
        if (keyValueTokens.Size() == 2)
        {
            result.Add(keyValueTokens[0], keyValueTokens[1]);
        }
    }
    return result;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
Util::String URI::GetRawPathFromUri( const char* uri )
{
	if (!uri)
	{
		return "";
	}
	const IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
	n_assert(pAssignRegistry);
	Util::String uriStr = uri;
	if(uriStr.Length() < 1)
	{
		return "";
	}

	IndexT index = uriStr.FindCharIndex(':');
	Util::String pre;
	if (index == InvalidIndex)
	{
		pre = uriStr;
	}
	else if (index == 0)
	{
		return "";
	}
	else
	{
		pre = uriStr.ExtractRange(0, index);
	}
	if (!pAssignRegistry->HasAssign(pre))
	{
		return "";
	}

	Util::String rawPath;
	if (index == InvalidIndex)
	{
		Util::String helper = ":a.b";
		rawPath = pAssignRegistry->ResolveAssigns((uriStr + helper).AsCharPtr()).LocalPath();
		rawPath = rawPath.ExtractRange(0, rawPath.Length() - helper.Length());
	}
	else if (index == uriStr.Length()-1)
	{
		Util::String helper = "a.b";
		rawPath = pAssignRegistry->ResolveAssigns((uriStr + helper).AsCharPtr()).LocalPath();
		rawPath = rawPath.ExtractRange(0, rawPath.Length() - helper.Length() - 1);
	}
	else
	{
		rawPath = pAssignRegistry->ResolveAssigns(uri).LocalPath();
	}


	//#ifdef __WIN32__
	rawPath.ReplaceChars("\\", '/');
	//#endif

	if (rawPath.BackwardFindChar('/') == rawPath.Length() - 1)
	{
		rawPath = rawPath.ExtractRange(0, rawPath.Length() - 1);
	}
	return rawPath;
}

//------------------------------------------------------------------------
Util::String URI::GetUriFromRawPath( const Util::String spath ,const Util::String spre)
{
	const char* path = spath.Get();
	const char* pre = spre.Get();
	if (!path || !pre)
	{
		return "";
	}
	const IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
	n_assert(pAssignRegistry);
	Util::String assignPath = GetRawPathFromUri(pre);
	if (assignPath.Length() < 1)
	{
		return "";
	}
	Util::String fullPath = path;
	if (fullPath.Length() < 1)
	{
		return "";
	}
	if (fullPath.FindCharIndex(':') > 1)
	{
		fullPath = GetRawPathFromUri(path);
	}

	assignPath.ReplaceChars("\\", '/');
	fullPath.ReplaceChars("\\", '/');
	IndexT index = fullPath.FindStringIndex(assignPath, 0);
	if (index == 0)
	{
		Util::String extractedStr = fullPath.ExtractRange(assignPath.Length(), fullPath.Length() - assignPath.Length());
		if (extractedStr.FindCharIndex('/') == 0)
		{
			extractedStr = extractedStr.ExtractToEnd(1);
		}
		Util::String result = pre;
		if (result.BackwardFindChar(':') != result.Length() - 1)
		{
			result = result + ":";
		}
		result += extractedStr;
		return result;
	}
	else
	{
		return ""; // failed!
	}
}

} // namespace IO