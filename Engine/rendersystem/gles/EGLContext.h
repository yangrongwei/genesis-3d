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

#ifndef __glescontext_H__
#define __glescontext_H__

#include "core/refcounted.h"
#include "util/array.h"
#include "OpenGLES.h"


namespace GLES
{
	class GLESContext: public Core::RefCounted
{
	__DeclareClass(GLESContext);

public:

	GLESContext();
	virtual ~GLESContext();
public:

	bool InitContext(int inMultisample);

	void DestroyContex();

	bool ActiveContext();
	void DeactiveContext();

	bool BeginFrame();
	bool EndFrame();


	void SetWindow(void* hWnd);

	
#ifdef __OSX__
    
#else
	EGLBoolean GetGLESConfigAttrib(EGLConfig glConfig, EGLint attribute, EGLint *value);

protected:

	EGLConfig _SelectGLESConfig(const EGLint* minAttribs, const EGLint *maxAttribs);

	EGLConfig* _ChooseGLESConfig(const EGLint *attribList, EGLint *nElements);
#endif
    
	void       _SetCurrentContext();
	
	void       _GetGLESDisplay();

	void       _InitMSAAConfig(int inMultisample, int& multisampleChosen);

	bool       _IsValid();

	bool       _IsActive();

	void       _CheckError();

private:


	void*				 m_hwnd;

#ifndef __OSX__
	EGLDisplay			 m_EglDisplay;
	EGLSurface			 m_EglSurface;
	EGLConfig			 m_EglConfig;
	EGLContext			 m_Context;
#endif
	bool				 m_bCreated;
	bool                 m_bIsActive;

	Util::Array<int>	 m_FSAALevels;
};


inline void GLESContext::SetWindow(void* hWnd)
{
	m_hwnd = hWnd;
}


inline bool GLESContext::_IsValid()
{
    return true;
	//return m_EglDisplay != NULL;
}

inline bool GLESContext::_IsActive()
{
	return m_bIsActive;
}

inline void GLESContext::_CheckError()
{
#ifdef __OSX__
    GLint error = glGetError();
#else
	EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
#endif
	//
	{
		n_error("EGL ERROR!");
	}
}

}

#endif