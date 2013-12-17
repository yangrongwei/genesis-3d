/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#include "MyGUI_GenesisDataStream.h"

namespace MyGUI
{

	GenesisDataStream::GenesisDataStream(GPtr<IO::TextReader>& _stream) :
mStream(_stream)
{
}

GenesisDataStream::~GenesisDataStream()
{
	mStream = NULL;
}

bool GenesisDataStream::eof()
{
	_checkOpen();
	return (NULL == mStream) ? true : mStream->Eof();
}

size_t GenesisDataStream::size()
{
	_checkOpen();
	return (NULL == mStream) ? 0 : mStream->GetStream()->GetSize();
}

void GenesisDataStream::readline(std::string& _source, Char _delim)
{
	if (NULL == mStream)
	{
		_source.clear();
		return;
	}
	_checkOpen();
	Util::String str = mStream->ReadLine();
	_source = str.AsCharPtr();
}

size_t GenesisDataStream::read(void* _buf, size_t _count)
{
	if (NULL == mStream) 
	{
		return 0;
	}
	_checkOpen();
	return mStream->GetStream()->Read(_buf, _count);
	//return mStream->read(_buf, _count);
}

} // namespace MyGUI
