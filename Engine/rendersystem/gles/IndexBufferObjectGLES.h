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

#ifndef __IndexBufferObjectGLES_H__
#define __IndexBufferObjectGLES_H__

#include "base/IndexBuffer.h"
#include "OpenGLES.h"

namespace GLES
{
	class IndexBufferObjectGLES : public RenderBase::IndexBuffer
{
	__DeclareSubClass(IndexBufferObjectGLES, RenderBase::IndexBuffer)

public:
	/// constructor
	IndexBufferObjectGLES();
	/// destructor
	virtual ~IndexBufferObjectGLES();

	void Discard();

	GLuint GetGLESIndexBuffer() const;
	
	GLenum GetGLESIndexType() const;

	void UpdateData(const RenderBase::DataStream& stream);

	/// on device lost
	virtual void OnDeviceLost();
	/// on device reset
	virtual void OnDeviceReset();

	static void CreateIndexBuffer(const RenderBase::IndexBufferData* ibd, GPtr<IndexBufferObjectGLES>& out);

private:
	void _SetGLESIndexBuffer(GLuint obj);
	void _SetGLESIndexType(GLenum t);
	GLuint m_IBObejectGLES;
	GLenum m_IndexTypeGLES;
};

inline void IndexBufferObjectGLES::_SetGLESIndexBuffer(GLuint obj)
{
	n_assert(0 != obj);
	n_assert(0 == m_IBObejectGLES);
	this->m_IBObejectGLES = obj;
}

inline GLuint IndexBufferObjectGLES::GetGLESIndexBuffer() const
{
	return this->m_IBObejectGLES;
}

inline void IndexBufferObjectGLES::_SetGLESIndexType(GLenum t)
{
	m_IndexTypeGLES = t;
}

inline GLenum IndexBufferObjectGLES::GetGLESIndexType() const
{
	return m_IndexTypeGLES;
}

}

#endif