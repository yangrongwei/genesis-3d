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
#ifndef __MYGUI_GENESIS_DATA_STREAM_H__
#define __MYGUI_GENESIS_DATA_STREAM_H__

#include "MyGUI_IDataStream.h"
#include "foundation/io/textreader.h"


namespace MyGUI
{
	class GenesisDataStream :
		public IDataStream
	{
	public:
		GenesisDataStream(GPtr<IO::TextReader>& _stream);
		virtual ~GenesisDataStream();

		virtual bool eof();
		virtual size_t size();
		virtual void readline(std::string& _source, Char _delim);
		virtual size_t read(void* _buf, size_t _count);

	private:
		void _checkOpen();
		GPtr<IO::TextReader> mStream;
	};
	inline void GenesisDataStream::_checkOpen()
	{
		if (mStream && !mStream->IsOpen())
		{
			mStream->Open();
		}
	}

} // namespace MyGUI

#endif // __MYGUI_GENESIS_DATA_STREAM_H__
