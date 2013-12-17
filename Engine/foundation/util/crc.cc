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
#include "util/crc.h"

namespace Util
{
unsigned int Crc::Table[NumByteValues] = { 0 };
bool Crc::TableInitialized = false;

//------------------------------------------------------------------------------
/**
*/
Crc::Crc() :
    inBegin(false),
    resultValid(false),
    checksum(0)
{
    // first-time byte table initialization
    if (!TableInitialized)
    {
        unsigned int i;
        for (i = 0; i < NumByteValues; ++i)
        {
            unsigned int reg = i << 24;
            int j;
            for (j = 0; j < 8; ++j)
            {
                bool topBit = (reg & 0x80000000) != 0;
                reg <<= 1;
                if (topBit)
                {
                    reg ^= Key;
                }
            }
            Table[i] = reg;
        }
        TableInitialized = true;
    }
}

//------------------------------------------------------------------------------
/**
    Begin computing a CRC checksum over several chunks of data. This can be
    done in multiple runs, which is the only useful way to compute
    checksum for large files.
*/
void
Crc::Begin()
{
    n_assert(!this->inBegin);    
    this->resultValid = false;
    this->inBegin = true;
    this->checksum = 0;
}

//------------------------------------------------------------------------------
/**
    Do one run of checksum computation for a chunk of data. Must be 
    executed inside Begin()/End().
*/
void
Crc::Compute(unsigned char* buf, unsigned int numBytes)
{
    n_assert(this->inBegin);
    unsigned int i;
    for (i = 0; i < numBytes; i++)
    {
        uint top = this->checksum >> 24;
        top ^= buf[i];
        this->checksum = (this->checksum << 8) ^ Table[top];
    }
}

//------------------------------------------------------------------------------
/**
    End checksum computation. This validates the result, so that
    it can be accessed with GetResult().
*/
void
Crc::End()
{
    n_assert(this->inBegin);
    this->inBegin = false;
    this->resultValid = true;
}

//------------------------------------------------------------------------------
/**
    Get the result of the checksum computation. Must be executed
    after End().
*/
unsigned int
Crc::GetResult() const
{
    n_assert(!this->inBegin);
    n_assert(this->resultValid);
    return this->checksum;
}

} // namespace Util
