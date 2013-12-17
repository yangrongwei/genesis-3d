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
#include "VertexBufferObjectGLES.h"
#include "GLESTypes.h"
#include "GPUProgramGLES.h"

namespace GLES
{
	using namespace RenderBase;

	__ImplementClass(GLES::VertexBufferObjectGLES,'VOGE',RenderBase::VertexBuffer );

VertexBufferObjectGLES::VertexBufferObjectGLES()
: m_VBObejectGLES(0)
{

}

VertexBufferObjectGLES::~VertexBufferObjectGLES()
{
	Discard();
}

void VertexBufferObjectGLES::Discard()
{
	if (m_VBObejectGLES)
	{
		GLESImpl::Instance()->ActiveVertexBufferObject(0);
		glDeleteBuffers(1, &m_VBObejectGLES);
		m_VBObejectGLES = 0;
		PROFILER_ADDDEVICESTATEVAL(videoRam, -GetVertexDataSize());
		PROFILER_ADDDEVICESTATEVAL(vboRam, -GetVertexDataSize());
	}
}

void VertexBufferObjectGLES::BindingVertexLayout(const GPUProgramGLES* pGlesProgram)
{
	GLESImpl::Instance()->ActiveVertexBufferObject(m_VBObejectGLES);

	void* pVertex = NULL;
	uint  offset  = 0;

	const RenderBase::VertexComponents& vertexComponents = this->vertexLayout->GetVertexComponents();

	const SizeT vSize = vertexComponents.Size();

	const Util::Dictionary<Util::String, Attribute>& activeAttributes = pGlesProgram->GetActiveAttributes();

	for (IndexT compIndex = 0; compIndex < vSize; ++compIndex)
	{
		const VertexComponent& component  = vertexComponents[compIndex];
		VertexComponent::SemanticName sem = component.GetSemanticName();
		VertexComponent::Format format    = component.GetFormat();

		Util::String attributeName;

		if (sem == VertexComponent::Position || sem == VertexComponent::Normal ||
			sem == VertexComponent::Color || sem == VertexComponent::Tangent ||
			sem == VertexComponent::SkinWeights || sem == VertexComponent::SkinJIndices)
		{
			attributeName              = GLESTypes::AsGlesAttributeName(sem);
			IndexT ret = activeAttributes.FindIndex(attributeName);
			if (ret != InvalidIndex)
			{
				const Attribute& attribute = activeAttributes[attributeName];
				const IndexT loc           = attribute.location;
				glEnableVertexAttribArray(loc);
				glVertexAttribPointer(loc, VertexComponent::GetTypeCount(format), GLESTypes::AsGLESBasicType(format), 
					GL_FALSE, static_cast<GLsizei>(this->vertexLayout->GetVertexByteSize()), pVertex);
			}
			
		}
		else if (sem == VertexComponent::TexCoord)
		{
			Util::String s_MulTexIndex;
			attributeName              = GLESTypes::AsGlesAttributeName(sem);
			IndexT nMulTex             = component.GetSemanticIndex();
			s_MulTexIndex.SetInt(nMulTex);
			attributeName             += s_MulTexIndex;
			IndexT ret = activeAttributes.FindIndex(attributeName);
			if (ret != InvalidIndex)
			{
				const Attribute& attribute = activeAttributes[attributeName];
				const IndexT loc           = attribute.location;
				glEnableVertexAttribArray(loc);
				glVertexAttribPointer(loc, VertexComponent::GetTypeCount(format), GLESTypes::AsGLESBasicType(format), 
					GL_FALSE, static_cast<GLsizei>(this->vertexLayout->GetVertexByteSize()), pVertex);
			}
			
		}
		else
		{
			n_error("No matched VertexComponent!");
		}

		GLESImpl::Instance()->CheckError();

		offset += component.GetByteSize();
		pVertex = (char *)NULL + offset;
	}
}

void VertexBufferObjectGLES::UpdateData(const RenderBase::DataStream& stream)
{
	n_assert(stream.data);
	n_assert(vertexDataSize >= stream.sizeInByte);
	GLenum usagegl = GLESTypes::AsGLESUsage(usage);
	if (!m_VBObejectGLES)
	{
		glGenBuffers(1,&m_VBObejectGLES);
	}
	GLESImpl::Instance()->ActiveVertexBufferObject(m_VBObejectGLES);

	glBufferData(GL_ARRAY_BUFFER,
		stream.sizeInByte,
		stream.data,
		usagegl
		);
	GLESImpl::Instance()->CheckError();
}

void VertexBufferObjectGLES::CreateVertexBuffer(const RenderBase::VertexBufferData* vbd, GPtr<VertexBufferObjectGLES>& out)
{
	out = VertexBufferObjectGLES::Create();

	GPtr<VertexLayout> layout = VertexLayout::Create();
	layout->Setup(vbd->vertex.vertexComponents);
	int vertexBufferSize = vbd->vertexCount * layout->GetVertexByteSize();
	out->_SetVertexDataSize(vertexBufferSize);
	out->_SetNumVertices(vbd->vertexCount);
	out->_SetUsage(vbd->usage);
	out->_SetVertexLayout(layout);

	GLenum usagegl = GLESTypes::AsGLESUsage(vbd->usage);

	GLuint bufferObj = 0;

	// create buffer
	glGenBuffers(1,&bufferObj);

	GLESImpl::Instance()->CheckError();
	out->_SetGLESVertexBuffer(bufferObj);
	if (vbd->vertex.vertexComponentStreams.Size())
	{
		uchar* dstPtr = n_new_array(uchar, vertexBufferSize);
		DirectCopyVertexDataToGraphicBuffer(*vbd, dstPtr, layout->GetVertexByteSize());
		GLESImpl::Instance()->ActiveVertexBufferObject(bufferObj);

		glBufferData(GL_ARRAY_BUFFER,
			vertexBufferSize,
			dstPtr,
			usagegl
			);
		GLESImpl::Instance()->CheckError();
		n_delete_array(dstPtr);


		PROFILER_ADDDEVICESTATEVAL(videoRam, vertexBufferSize);
		PROFILER_ADDDEVICESTATEVAL(vboRam, vertexBufferSize);

		GLESImpl::Instance()->ActiveVertexBufferObject(0);
	}
}

void VertexBufferObjectGLES::OnDeviceLost()
{
	m_VBObejectGLES = 0;
}

void VertexBufferObjectGLES::OnDeviceReset()
{
	if (this->usage == RenderBase::BufferData::Dynamic)
	{
		glGenBuffers(1, &m_VBObejectGLES);
	}
}

}