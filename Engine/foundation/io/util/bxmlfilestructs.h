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
    @file io/util/bxmlfilestructs.h
    
    Structures used by the BXML file format.
*/
#include "core/types.h"

//------------------------------------------------------------------------------
namespace IO
{
#pragma pack(push,1)
struct BXMLFileHeader
{
    uint magic;
    uint numAttrs;          // number of attributes in attribute array
    uint numNodes;          // number of nodes in node array
    uint numStrings;        // number of strings in string table
};
struct BXMLFileAttr
{
    ushort nameIndex;       // index into string table
    ushort valueIndex;      // index into string table
};
struct BXMLFileNode
{
    ushort nameIndex;           // index into string table
    ushort firstChildIndex;     // index to first child node
    ushort nextSiblingIndex;    // index of next sibling
    ushort parentIndex;         // index of parent
    uint attrIndex;             // index to first attr
    uint numAttrs;              // number of attributes
};
#pragma pack(pop)
}
//------------------------------------------------------------------------------
    