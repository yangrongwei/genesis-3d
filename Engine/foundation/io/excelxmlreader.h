/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::ExcelXmlReader
    
    A stream reader class which reads Excel XML files.
    NOTE: the strings returned by this class will be in UTF-8 format!

*/
#include "io/streamreader.h"
#include "io/xmlreader.h"
#include "util/string.h"
#include "util/array.h"
#include "util/fixedtable.h"

//------------------------------------------------------------------------------
namespace IO
{
class ExcelXmlReader : public StreamReader
{
    __DeclareClass(ExcelXmlReader);
public:
    /// constructor
    ExcelXmlReader();
    /// destructor
    virtual ~ExcelXmlReader();

    /// begin reading from the stream
    virtual bool Open();
    /// end reading from the stream
    virtual void Close();

    /// get the number of tables in the file
    SizeT GetNumTables() const;
    /// get the name of the table at given table index
    const Util::String& GetTableName(IndexT tableIndex = 0) const;
    /// get index of table by name
    IndexT GetTableIndex(const Util::String& tableName);
    /// get number of rows in table
    SizeT GetNumRows(IndexT tableIndex = 0) const;
    /// get number of columns in table
    SizeT GetNumColumns(IndexT tableIndex = 0) const;
    /// return true if table has named column
    bool HasColumn(const Util::String& columnName, IndexT tableIndex = 0) const;
    /// get column index by name, returns InvalidIndex if column doesn't exist
    IndexT FindColumnIndex(const Util::String& columnName, IndexT tableIndex = 0) const;
    /// get cell content by row index and column index
    const Util::String& GetElement(IndexT rowIndex, IndexT columnIndex, IndexT tableIndex = 0) const;
    /// get cell content by row index and column name (SLOW!)
    const Util::String& GetElement(IndexT rowIndex, const Util::String& columnName, IndexT tableIndex = 0) const;

private:
    /// parse the Excel-XML-stream
    bool ParseExcelXmlStream();
    /// parse table contents
    bool ParseTables(const GPtr<IO::XmlReader>& xmlReader);

    Util::Array<Util::String> tableNames;
    Util::Array<Util::FixedTable<Util::String> > tables;
};

} // namespace IO
//------------------------------------------------------------------------------
