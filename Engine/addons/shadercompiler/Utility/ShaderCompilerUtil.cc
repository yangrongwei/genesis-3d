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
#include "util/hashtable.h"
#include "io/memorystream.h"
#include "io/textreader.h"
#include "io/ioserver.h"
#include "io/uri.h"
#include "ShaderCompilerUtil.h"

namespace ShaderProgramCompiler
{

bool ShaderUtil::HaveStringAtEnd(const Util::String& src, const Util::String& cmp)
{
	if (src.Length() < cmp.Length())
	{
		return false;
	}
	IndexT ind  = src.FindStringIndex(cmp,src.Length()-cmp.Length());
	IndexT cmpInd = src.Length() - cmp.Length();
	return (ind == cmpInd ? true : false);
}

bool ShaderUtil::ReadText(const Util::String& pathName, Util::String& output)
{
	GPtr<IO::Stream> stream         = IO::IoServer::Instance()->ReadFile(pathName);
	GPtr<IO::TextReader> textReader = IO::TextReader::Create();
	textReader->SetStream(stream);
	if (textReader->Open())
	{
		output = textReader->ReadAll();
		textReader->Close();
		stream     = 0;
		textReader = 0;

		return true;
	}
	else
	{
		return false;
	}
}

IndexT ShaderUtil::TokenizeWithoutCRLF(const Util::String& str, Util::String& out )
{
	Util::Array<Util::String> temps;
	str.Tokenize(" ", temps);
	out = temps[0];

	if (out[0] == 13 || out[0] == 10)
	{
		return InvalidIndex;
	}
	
	IndexT pos = out.Length() - 1;

	while (out[pos] < 14)
	{
		pos--;
	}

	if (pos != out.Length() - 1)
	{
		out.TerminateAtIndex(pos + 1);
	}
	

	return temps.Size();
}

void ShaderUtil::TokenizeWithoutCRLF(const Util::String& str, Util::Array<Util::String>& outs )
{
	Util::Array<Util::String> temps;
	str.Tokenize(" ", temps);

	SizeT nCount = temps.Size();

	for (IndexT i = 0; i < nCount; ++i)
	{
		Util::String temp = temps[i];

		if (temp[0] == 13 || temp[0] == 10)
		{
			continue;
		}
		

		IndexT pos = temp.Length() - 1;

		while (temp[pos] < 14)
		{
			pos--;
		}

		if (pos != temp.Length() - 1)
		{
			temp.TerminateAtIndex(pos + 1);
		}

		outs.Append(temp);
	}
}

}