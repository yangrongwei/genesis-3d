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

#ifndef RENDERTARGETGLES_H_
#define RENDERTARGETGLES_H_

#include "base/RenderTarget.h"
#include "TextureGLES.h"


namespace GLES
{
	using namespace RenderBase;

	struct GLESFrameBuf
	{
		GLuint FrameBuf;
		GLuint FrameTexAttached;
		GLuint FrameDepthTexAttached;
		GLuint FrameDepthRBAttached;
		GLuint FrameStencilAttached;

		GLESFrameBuf()
			: FrameBuf(0),
			  FrameTexAttached(0),
			  FrameDepthTexAttached(0),
			  FrameDepthRBAttached(0),
			  FrameStencilAttached(0)
		{

		}

		void Clear()
		{
			FrameBuf			  = 0;
			FrameTexAttached	  = 0;
			FrameDepthTexAttached = 0;
			FrameDepthRBAttached  = 0;
			FrameStencilAttached  = 0;
		}
	};

class RenderTargetGLES : public RenderTarget
{
	__DeclareSubClass(RenderTargetGLES, RenderTarget);

public:

	/// constructor
	RenderTargetGLES();
	/// destructor
	virtual ~RenderTargetGLES();
	/// discard the render target object
	virtual void Discard();

	/// setup the render target object
	void LoadBuffers(SizeT _width, SizeT _height);


	void AssignGLESTextures();

	const GLESFrameBuf& GetRenderTargetGLES() const;

	virtual void OnDeviceLost();

	virtual void OnDeviceReset();

protected:

	GLESFrameBuf    m_GLESRenderTarget;

	friend class RenderDeviceGLES;
};

inline const GLESFrameBuf& RenderTargetGLES::GetRenderTargetGLES() const
{
	return m_GLESRenderTarget;		
}

}

#endif