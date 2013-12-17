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
    @class IO::BinaryWriter
    
    A friendly interface for writing binary data to a stream. Optionally
    the writer can use memory mapping for optimal write performance.
    
    @todo convert endianess!    

*/
#include "io/streamwriter.h"
#include "util/blob.h"
#include "util/guid.h"
#include "system/byteorder.h"

#include "math/float2.h"
#include "math/point.h"
#include "math/vector.h"


//------------------------------------------------------------------------------
namespace IO
{
class BinaryWriter : public StreamWriter
{
    __DeclareClass(BinaryWriter);
public:
    /// constructor
    BinaryWriter();
    /// destructor
    virtual ~BinaryWriter();
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
    /// write an 8-bit char to the stream
    void WriteChar(char c);
    /// write an 8-bit unsigned char to the stream
    void WriteUChar(unsigned char c);
    /// write an 16-bit short to the stream
    void WriteShort(short s);
    /// write an 16-bit unsigned short to the stream
    void WriteUShort(unsigned short s);
    /// write an 32-bit int to the stream
    void WriteInt(int i);
    /// write an 32-bit unsigned int to the stream
    void WriteUInt(unsigned int i);
    /// write a float value to the stream    
    void WriteFloat(float f);
    /// write a compressed float value to the stream, lossy and needed to be in the range of -1.0 and +1.0
    void WriteFloatAsNormalizedUByte2(float f);
    /// write a compressed float value to the stream, lossy and needed to be in the range of 0.0 and +1.0
    void WriteFloatAsUnsignedNormalizedUByte2(float f);
    /// write a double value to the stream
    void WriteDouble(double d);
    /// write a boolean value to the stream
    void WriteBool(bool b);
    /// write a string to the stream
    void WriteString(const Util::String& s);
 
    /// write a float value to the stream    
    void WriteFloat2(Math::float2 f);
    /// write a float4 to the stream
    void WriteFloat4(const Math::float4& v);
    /// write a float4 to the stream
    void WritePoint(const Math::point& v);
    /// write a float4 to the stream
    void WriteVector(const Math::vector& v);
    /// write a matrix44 to the stream
    void WriteMatrix44(const Math::matrix44& m);

    /// write a guid
    void WriteGuid(const Util::Guid& guid);
    /// write a blob of data
    void WriteBlob(const Util::Blob& blob);
    /// write raw data
    void WriteRawData(const void* ptr, SizeT numBytes);

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
inline
void
BinaryWriter::SetMemoryMappingEnabled(bool b)
{
    this->enableMapping = b;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
BinaryWriter::IsMemoryMappingEnabled() const
{
    return this->enableMapping;
}

//------------------------------------------------------------------------------
/**
*/
inline void
BinaryWriter::SetStreamByteOrder(System::ByteOrder::Type order)
{
    this->byteOrder.SetToByteOrder(order);
}

//------------------------------------------------------------------------------
/**
*/
inline System::ByteOrder::Type
BinaryWriter::GetStreamByteOrder() const
{
    return this->byteOrder.GetToByteOrder();
}

} // namespace IO
//------------------------------------------------------------------------------
