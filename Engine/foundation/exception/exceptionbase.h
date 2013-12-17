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

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include <exception>
#include "Util/string.h"

namespace Exceptions
{
	#define BASE_EXCEPT(desc, src) throw Exception(desc, src, __FILE__, __LINE__)

	typedef Util::String String;
	class Exception : public std::exception
	{
	public:
		enum ExceptionType
		{
			EXT_UNDEF_TYPE = 0,
			EXT_SERIALIZE_ERROR = 1,
			EXT_FORMAT_ERROR = 2,
			EXT_SHADER_ERROR = 3,
			//EXT_FILE_READ_FALSE,
			//EXT_FILE_WRITE_FALSE,
			//EXT_FILE_NOT_FOUND,
			//EXT_ITEM_NOT_FOUND,
			//EXT_SYSTEM_ERROR,
			EXT_CUSTOM_BEGIN = 1000,
		};

		/** Default constructor.
        */

        Exception(const String& description_, const String& source_);
		Exception(const String& description_, const String& source_, const char* file_, long line_);

        /** Copy constructor.
        */
        Exception(const Exception& rhs);

		/// Needed for  compatibility with std::exception
		virtual ~Exception() throw();

        /** Assignment operator.
        */
        void operator = (const Exception& rhs);

        virtual const String& GetFullDescription() const;

        /** Gets the error code.
        */
        virtual int GetType(void) const throw();

        /** Gets the source function.
        */
        virtual const String &GetSource() const;

        /** Gets source file name.
        */
        virtual const String &GetFile() const;

        /** Gets line number.
        */
        virtual long GetLine() const;

		/** Returns a string with only the 'description' field of this exception. Use 
			GetFullDescriptionto get a full description of the error including line number,
			error number and what function threw the exception.
        */
		virtual const String &GetDescription(void) const;

		/// Override std::exception::what
		const char* what() const throw();

	protected:

		/** Advanced constructor.
        */
        Exception(int type_, const String& description_, const String& source_, const char* tile_, const char* file_, long line_);

		long line;
		int type;
		String title;
		String description;
		String source;
		String file;
		mutable String fullDesc;
	};
}

#endif