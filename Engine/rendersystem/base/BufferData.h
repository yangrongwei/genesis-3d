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

#ifndef __BUFFERDATA_H__
#define __BUFFERDATA_H__
#ifdef __OSX__
#include "../rendersystem/base/VertexComponent.h"
#include "../rendersystem/base/RenderDeviceTypes.h"
#else
#include "rendersystem/base/VertexComponent.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#endif
namespace RenderBase
{
	const int MaxNumVertexStreams = 2;

	struct BufferData
	{
		enum Usage
		{
			Static,
			Dynamic,
		};
		Usage usage;
	protected:
		inline BufferData(Usage _usage)
			:usage(_usage)
		{

		}
	};
	struct DataStream
	{
		void* data;
		int sizeInByte;
		inline DataStream()
			:data(NULL)
			,sizeInByte(0)
		{

		}
	};

	typedef Util::Array<VertexComponent> VertexComponents;
	struct VertexStream
	{
		void* data;
		int offsetInByte;
		int elemSizeInByte;
		inline VertexStream()
			:data(NULL)
			,offsetInByte(0)
			,elemSizeInByte(0)
		{

		}
	};

	typedef Util::Array<VertexStream> VertexStreams;

	struct VertexBufferData : public BufferData
	{
		struct Vertex
		{
			VertexComponents vertexComponents;
			VertexStreams vertexComponentStreams;
		};
		Vertex vertex;
		//VertexStream uniqueStream;
		RenderBase::PrimitiveTopology::Code topology;
		int vertexCount;
		inline VertexBufferData()
			: BufferData(Static)
			, topology(RenderBase::PrimitiveTopology::InvalidPrimitiveTopology)
		{

		}
	};

	typedef void* IndexStream;
	struct IndexBufferData : public BufferData
	{
		enum IndexType
		{
			Unknown,
			Int16,
			Int32,
		};
		int indexCount;
		IndexType indexType;
		IndexStream stream;
		inline IndexBufferData()
			: BufferData(Static)
			, indexCount(0)
			, stream(NULL)
			, indexType(Unknown)
		{

		}

		static int SizeOf(IndexType type);
	};

	struct VERTEX_DESC
	{
		BufferData::Usage usage;
		RenderBase::PrimitiveTopology::Code topology;
		int vertexCount;
		int vertexSizeInbyte;
	};
	struct INDEX_DESC
	{
		BufferData::Usage usage;
		IndexBufferData::IndexType indexType;
		int indexCount;
	};

	struct TEXTURE_DESC
	{
		SizeT width;
		SizeT height;
		SizeT depth;
		SizeT numMipLevels;
		PixelFormat::Code pixelFormat;
	};

	void DirectCopyVertexDataToGraphicBuffer(const VertexBufferData& source, void* to, int vertexByteSize);
}


#endif	//__BUFFERDATA_H__