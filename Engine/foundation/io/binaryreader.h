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

#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::BinaryReader
    
    A friendly interface to read binary data from a stream. Optionally the
    reader can use memory mapping for optimal read performance. Performs
    automatic byte order conversion if necessary.

    @todo convert endianess!
*/
#include "io/streamreader.h"
#if !__OSX__
#include "math/float2.h"
#include "math/float4.h"
#include "math/point.h"
#include "math/vector.h"
#include "math/matrix44.h"
#endif
#include "util/guid.h"
#include "util/blob.h"
#include "system/byteorder.h"

//------------------------------------------------------------------------------
namespace IO
{
class BinaryReader : public StreamReader
{
    __DeclareClass(BinaryReader);
public:        
    /// constructor
    BinaryReader();
    /// destructor
    virtual ~BinaryReader();
    /// call before Open() to enable memory mapping (if stream supports mapping)
    void SetMemoryMappingEnabled(bool b);
    /// return true if memory mapping is enabled
    bool IsMemoryMappingEnabled() const;
    /// set the stream byte order (default is host byte order)
    void SetStreamByteOrder(System::ByteOrder::Type byteOrder);
    /// get the stream byte order
    System::ByteOrder::Type GetStreamByteOrder() const;
    /// begin reading from the stream
    virtual bool Open();
    /// end reading from the stream
    virtual void Close();
    /// read an 8-bit char from the stream
    char ReadChar();
    /// read an 8-bit unsigned character from the stream
    unsigned char ReadUChar();
    /// read a 16-bit short from the stream
    short ReadShort();
    /// read a 16-bit unsigned short from the stream
    unsigned short ReadUShort();
    /// read a 32-bit int from the stream
    int ReadInt();
    /// read a 32-bit unsigned int from the stream
    unsigned int ReadUInt();
    /// read a float value from the stream
    float ReadFloat();
    /// read a compressed float value from the stream, lossy and needed to be in the range of -1.0 and +1.0
    float ReadFloatFromNormalizedUByte2();
    /// read a compressed float value from the stream, lossy and needed to be in the range of 0.0 and +1.0
    float ReadFloatFromUnsignedNormalizedUByte2();
    /// read a double value from the stream
    double ReadDouble();
    /// read a bool value from the stream
    bool ReadBool();
    /// read a string from the stream
    Util::String ReadString();
 
    /// read a float2 from the stream
    Math::float2 ReadFloat2();
    /// read a float4 from the stream
    Math::float4 ReadFloat4();
    /// read a point from the stream, (x,y,z,1.0)
    Math::point ReadPoint();
    /// read a vector from the stream, (x,y,z,0.0)
    Math::vector ReadVector();
    /// read a matrix44 from the stream
    Math::matrix44 ReadMatrix44();

    /// read a guid
    Util::Guid ReadGuid();
    /// read a blob of data
    Util::Blob ReadBlob();
    /// read raw data
    void ReadRawData(void* ptr, SizeT numBytes);

public:
    bool enableMapping;
    bool isMapped;
    System::ByteOrder byteOrder;
    unsigned char* mapCursor;
    unsigned char* mapEnd;
};

//------------------------------------------------------------------------------
/**
*/
inline void
BinaryReader::SetMemoryMappingEnabled(bool b)
{
    this->enableMapping = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
BinaryReader::IsMemoryMappingEnabled() const
{
    return this->enableMapping;
}

//------------------------------------------------------------------------------
/**
*/
inline void
BinaryReader::SetStreamByteOrder(System::ByteOrder::Type order)
{
    this->byteOrder.SetFromByteOrder(order);
}

//------------------------------------------------------------------------------
/**
*/
inline System::ByteOrder::Type
BinaryReader::GetStreamByteOrder() const
{
    return this->byteOrder.GetFromByteOrder();
}

} // namespace IO
//------------------------------------------------------------------------------
