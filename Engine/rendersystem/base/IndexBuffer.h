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

#pragma once

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_
#include "RenderDeviceTypes.h"
#include "core/types.h"
#ifdef __OSX__
#include "../rendersystem/config/RenderDeviceConfig.h"
#else
#include "config/RenderDeviceConfig.h"
#endif
#include "util/string.h"
#include "BufferData.h"

namespace RenderBase
{

class IndexBuffer : public Core::RefCounted
{
	__DeclareSubClass(IndexBuffer,Core::RefCounted)
public:

	virtual ~IndexBuffer();

	IndexBufferData::IndexType GetIndexType() const;
	SizeT GetIndexDataSize() const;
	SizeT GetNumIndices() const;
	BufferData::Usage GetUsage() const;

	void _SetNumIndices(SizeT num);
	void _SetIndexDataSize(SizeT size);
	void _SetIndexType(IndexBufferData::IndexType type);
	void _SetUsage(BufferData::Usage usage);

	/// on device lost
	virtual void OnDeviceLost();
	/// on device reset
	virtual void OnDeviceReset();

protected:	
	IndexBuffer();
	SizeT numIndices;
	SizeT indexDataSize;
	IndexBufferData::IndexType indexType;
	BufferData::Usage usage;

};

//------------------------------------------------------------------------------
/**
*/
inline void
IndexBuffer::_SetIndexType(IndexBufferData::IndexType type)
{
	this->indexType = type;
}

//------------------------------------------------------------------------------
/**
*/
inline IndexBufferData::IndexType
IndexBuffer::GetIndexType() const
{
	return this->indexType;
}
//------------------------------------------------------------------------------
/**
*/
inline BufferData::Usage
IndexBuffer::GetUsage() const
{
	return this->usage;
}
//------------------------------------------------------------------------------
/**
*/
inline void
IndexBuffer::_SetNumIndices(SizeT num)
{
	n_assert(num > 0);
	this->numIndices = num;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
IndexBuffer::GetNumIndices() const
{
	return this->numIndices;
}
//------------------------------------------------------------------------------
/**
*/
inline void
IndexBuffer::_SetIndexDataSize(SizeT size)
{
	this->indexDataSize = size;
}

inline SizeT
IndexBuffer::GetIndexDataSize() const
{
	return this->indexDataSize;
}
inline void 
IndexBuffer::_SetUsage(BufferData::Usage usage)
{
	this->usage = usage;
}
}
#endif