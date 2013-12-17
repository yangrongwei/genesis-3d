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
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif
#include "IndexBufferObjectGLES.h"
#include "GLESTypes.h"

namespace GLES
{
	__ImplementClass(GLES::IndexBufferObjectGLES,'IOGE',RenderBase::IndexBuffer);

IndexBufferObjectGLES::IndexBufferObjectGLES()
: m_IBObejectGLES(0),
  m_IndexTypeGLES(GL_UNSIGNED_SHORT)
{

}

IndexBufferObjectGLES::~IndexBufferObjectGLES()
{
	Discard();
}

void IndexBufferObjectGLES::Discard()
{
	if (m_IBObejectGLES)
	{
		GLESImpl::Instance()->ActiveIndexBufferObject(0);
		glDeleteBuffers(1, &m_IBObejectGLES);
		m_IBObejectGLES = 0;
  
		PROFILER_ADDDEVICESTATEVAL(videoRam, -GetIndexDataSize());
		PROFILER_ADDDEVICESTATEVAL(vboRam, -GetIndexDataSize());
	}
}

void IndexBufferObjectGLES::UpdateData(const RenderBase::DataStream& stream)
{
	n_assert(stream.data);
	n_assert(indexDataSize >= stream.sizeInByte);
	GLenum usagegl = GLESTypes::AsGLESUsage(usage);

	if (!m_IBObejectGLES)
	{
		glGenBuffers(1,&m_IBObejectGLES);
	}

	GLESImpl::Instance()->ActiveIndexBufferObject(m_IBObejectGLES);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		stream.sizeInByte,
		stream.data,
		usagegl
		);
	GLESImpl::Instance()->CheckError();
}

void IndexBufferObjectGLES::CreateIndexBuffer(const RenderBase::IndexBufferData* ibd, GPtr<IndexBufferObjectGLES>& out)
{
	out = IndexBufferObjectGLES::Create();

	n_assert(ibd);
	int indexBufferSize = RenderBase::IndexBufferData::SizeOf(ibd->indexType) * ibd->indexCount;

	out->_SetIndexDataSize(indexBufferSize);
	out->_SetNumIndices(ibd->indexCount);
	out->_SetIndexType(ibd->indexType);
	out->_SetUsage(ibd->usage);

	GLenum indexUsage = GLESTypes::AsGLESUsage(ibd->usage);

	GLenum indexType =  GLESTypes::IndexTypeAsGLESFormat(ibd->indexType);

	out->_SetGLESIndexType(indexType);

	// create buffer
	GLuint bufferObj = 0;

	glGenBuffers(1,&bufferObj);
	GLESImpl::Instance()->CheckError();
	out->_SetGLESIndexBuffer(bufferObj);

	n_assert(bufferObj);

	// setup initial data if provided
	if (NULL != ibd->stream)
	{
		GLESImpl::Instance()->ActiveIndexBufferObject(bufferObj);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
			indexBufferSize,
			ibd->stream,
			indexUsage);
		GLESImpl::Instance()->CheckError();


		PROFILER_ADDDEVICESTATEVAL(videoRam, indexBufferSize);
		PROFILER_ADDDEVICESTATEVAL(vboRam, indexBufferSize);

		GLESImpl::Instance()->ActiveIndexBufferObject(0);
	}

}

void IndexBufferObjectGLES::OnDeviceLost()
{
	m_IBObejectGLES = 0;
}

void IndexBufferObjectGLES::OnDeviceReset()
{
	if (this->usage == RenderBase::BufferData::Dynamic)
	{
		glGenBuffers(1, &m_IBObejectGLES);
	}
}

}