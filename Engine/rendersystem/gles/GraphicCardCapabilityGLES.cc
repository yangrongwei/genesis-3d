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
#include "rendersystem//base/GraphicCardCapability.h"
#include "RenderSystem.h"
#include "OpenGLES.h"

namespace RenderBase
{
	using namespace GLES;

#if RENDERDEVICE_OPENGLES
void GraphicCardCapability::DetectGraphicCardCapsGLES20()
{
	mDriverName = "OpenGL ES";
	mApiVersion = "2.0";

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mMaxTextureWidth);
	mMaxTextureHeight = mMaxTextureWidth;

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &mMaxUniformVectors); 

	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, mHighFloatRange, &mHighFloatPrecision);

	mFragmentHightPrecision = GLESImpl::Instance()->CheckExtension("OES_fragment_precision_high");
	mIndexUint        = GLESImpl::Instance()->CheckExtension("OES_element_index_uint");

	mDepthFormat = GLESImpl::Instance()->CheckExtension("GL_OES_depth_texture") || GLESImpl::Instance()->CheckExtension("GL_GOOGLE_depth_texture");
	mSeparateAplhaBlend = true;
	mStencilTwoSize =  GLESImpl::Instance()->CheckExtension("GL_OES_packed_depth_stencil");

}
#endif
}