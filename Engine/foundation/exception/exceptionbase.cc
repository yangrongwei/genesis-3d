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
#include "exceptionbase.h"

namespace Exceptions
{
	Exception::~Exception() throw()
	{

	}

	Exception::Exception(const String& description_, const String& source_)
	:line(0)
	,type(EXT_UNDEF_TYPE)
	,title("Exception")
	,description(description_)
	,source(source_)
	{
		// Log this error - not any more, allow catchers to do it
		//LogManager::getSingleton().logMessage(this->getFullDescription());
	}

	Exception::Exception(const String& description_, const String& source_, const char* file_, long line_)
		:type(EXT_UNDEF_TYPE)
		,title("Exception")
		,description(description_)
		,source(source_)
		,file(file_)
		,line(line_)
		
	{
		// Log this error - not any more, allow catchers to do it
		//LogManager::getSingleton().logMessage(this->getFullDescription());
	}

	Exception::Exception(int type_, const String& description_, const String& source_, const char* tile_, const char* file_, long line_)
		:line(line_)
		,type(type_)
		,title(tile_)
		,description(description_)
		,source(source_)
		,file(file_)
	{

	}

	Exception::Exception(const Exception& rhs)
		: line(rhs.line), 
		type(rhs.type), 
		title(rhs.title), 
		description(rhs.description), 
		source(rhs.source), 
		file(rhs.file)
	{
	}

	void Exception::operator = (const Exception& rhs)
	{
		description = rhs.description;
		type = rhs.type;
		source = rhs.source;
		file = rhs.file;
		line = rhs.line;
		title = rhs.title;
	}

    const String& Exception::GetFullDescription() const
	{
		if (0 == fullDesc.Length())
		{	
			if( line > 0 )
			{
				fullDesc.Format("GENESIS EXCEPTION(%d:%s): \"%s\" in %s at %s(line, %d)", 
					type, title.AsCharPtr(), description.AsCharPtr(), source.AsCharPtr(), file.AsCharPtr(), line);
			}
			else
			{
				fullDesc.Format("GENESIS EXCEPTION(%d:%s): \"%s\" in %s", type, title.AsCharPtr(), description.AsCharPtr(), source.AsCharPtr());
			}
		}

		return fullDesc;
	}

    int Exception::GetType(void) const throw()
	{
		return type;
	}

    const String &Exception::GetSource() const 
	{ 
		return source;
	}

    const String &Exception::GetFile() const 
	{ 
		return file; 
	}

    long Exception::GetLine() const 
	{ 
		return line; 
	}

	const String &Exception::GetDescription(void) const 
	{ 
		return description; 
	}

	const char* Exception::what() const throw() 
	{ 
		return GetFullDescription().AsCharPtr(); 
	}
}