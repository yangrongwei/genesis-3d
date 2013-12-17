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
#include "EGLContext.h"


namespace GLES
{
	__ImplementClass(GLESContext,'ESCT',Core::RefCounted);

GLESContext::GLESContext()
: m_EglConfig(NULL),
  m_EglDisplay(NULL),
  m_EglSurface(NULL),
  m_Context(NULL),
  m_bCreated(false),
  m_bIsActive(false)
{

}

GLESContext::~GLESContext()
{

}

bool GLESContext::InitContext(int inMultisample)
{
	if (m_bCreated)
	{
		DestroyContex();
	}

	if ( !m_hwnd )
	{
		return false;
	}

	_GetGLESDisplay();

	//IndexT multisampleChosen = 0;
	//_InitMSAAConfig(inMultisample, multisampleChosen);

	if (!eglBindAPI(EGL_OPENGL_ES_API))
	{
		n_error("Failed to bind OpenGL ES API!");
	}

	int minAttribs[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_LEVEL, 0,
		EGL_DEPTH_SIZE, 16,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	int maxAttribs[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		//EGL_BUFFER_SIZE, 32,
		EGL_RED_SIZE, 4,
		EGL_GREEN_SIZE, 4,
		EGL_BLUE_SIZE, 4,
		EGL_ALPHA_SIZE, 4,
		EGL_DEPTH_SIZE, 16,
		EGL_STENCIL_SIZE, 8,
		//EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};
	
	m_EglConfig  = _SelectGLESConfig(minAttribs, maxAttribs);
	_CheckError();
	
	EGLint ContextAttributes[] = {
		EGL_CONTEXT_CLIENT_VERSION,
		2, // selects OpenGL ES 2.0, set to 1 to select OpenGL ES 1.1
		EGL_NONE
	};

	m_Context = eglCreateContext(m_EglDisplay, m_EglConfig, EGL_NO_CONTEXT, ContextAttributes);
	_CheckError();	 

	EGLint AttribList[] = {EGL_NONE};
	m_EglSurface = eglCreateWindowSurface(m_EglDisplay, m_EglConfig, (EGLNativeWindowType)m_hwnd, AttribList);
	_CheckError();
	if (m_EglSurface == EGL_NO_SURFACE)
	{
		n_error("Failed to create EGL surface!");
	}

	if (m_Context == EGL_NO_CONTEXT)
	{
		n_error("Failed to create EGL context!");
	}

	_SetCurrentContext();

	m_bCreated = true;

	return true;
}

void GLESContext::DestroyContex()
{
	eglMakeCurrent(m_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(m_EglSurface, m_EglSurface);
	eglDestroyContext(m_EglDisplay, m_Context);
	eglTerminate(m_EglDisplay);

	m_bCreated = false;
}

bool GLESContext::ActiveContext()
{
	if ( _IsValid() )
	{
		_SetCurrentContext();

		m_bIsActive = true;
	}

	return m_bIsActive;
}

void GLESContext::DeactiveContext()
{
	eglMakeCurrent(m_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	m_bIsActive = false;
}

bool GLESContext::BeginFrame()
{
	if (!_IsActive())
	{
		return ActiveContext();
	}

	return true;
}

bool GLESContext::EndFrame()
{
	if ( _IsActive() )
	{
		return eglSwapBuffers(m_EglDisplay, m_EglSurface) > 0;
	}

	return false;
}

EGLConfig GLESContext::_SelectGLESConfig(const EGLint* minAttribs, const EGLint *maxAttribs)
{
	//EGLConfig *glConfigs;
	EGLConfig glConfig = 0;
	EGLint    nConfigs = 0;

	/*glConfigs = _ChooseGLESConfig(minAttribs, &nConfigs);

	if (!nConfigs)
	{
		return NULL;
	}

	glConfig = glConfigs[0];

	if (maxAttribs != NULL)
	{
		GLESConfigAttribs maximum(maxAttribs);
		GLESConfigAttribs best(maxAttribs);
		GLESConfigAttribs candidate(maxAttribs);

		best.load(this, glConfig);

		for (IndexT config = 1; config < nConfigs; config++)
		{
			candidate.load(this, glConfigs[config]);

			if (candidate > maximum)
			{
				continue;
			}

			if (candidate > best)
			{
				glConfig = glConfigs[config];

				best.load(this, glConfig);
			}
		}

	}

	n_delete_array(glConfigs);*/

	eglChooseConfig(m_EglDisplay, maxAttribs, &glConfig, 1, &nConfigs);

	return glConfig;
}

EGLConfig* GLESContext::_ChooseGLESConfig(const EGLint *attribList, EGLint *nElements)
{
	EGLConfig *configs;

	if (eglChooseConfig(m_EglDisplay, attribList, NULL, 0, nElements) == EGL_FALSE)
	{
		n_error("Fail to choose config!");

		return NULL;
	}


	configs = n_new_array(EGLConfig, *nElements * sizeof(EGLConfig));

	if (eglChooseConfig(m_EglDisplay, attribList, configs, *nElements, nElements) == EGL_FALSE)
	{
		n_error("Fail to choose config!");

		return NULL;
	}

	return configs;
}

EGLBoolean GLESContext::GetGLESConfigAttrib(EGLConfig glConfig, EGLint attribute, EGLint *value)
{
	EGLBoolean status;

	status = eglGetConfigAttrib(m_EglDisplay, glConfig, attribute, value);

	return status;
}

void GLESContext::_GetGLESDisplay()
{
	EGLint majorVersion;
	EGLint minorVersion;

	m_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if (m_EglDisplay == EGL_NO_DISPLAY)
	{
		n_error("Couldn't open EGLDisplay !");
	}

	if (eglInitialize(m_EglDisplay, &majorVersion, &minorVersion) == EGL_FALSE)
	{
		n_error("Couldn't initialize EGLDisplay!");
	}
}

void GLESContext::_InitMSAAConfig(int inMultisample, int& multisampleChosen)
{
	EGLConfig *glConfigs;
	IndexT config, nConfigs = 0;

	glConfigs = _ChooseGLESConfig(NULL, &nConfigs);

	for (config = 0; config < nConfigs; ++config)
	{
		IndexT caveat, samples;

		GetGLESConfigAttrib(glConfigs[config], EGL_CONFIG_CAVEAT, &caveat);

		if (caveat != EGL_SLOW_CONFIG)
		{
			GetGLESConfigAttrib(glConfigs[config], EGL_SAMPLES, &samples);
			
			IndexT found = m_FSAALevels.FindIndex(samples);

			if (found == InvalidIndex)
			{
				m_FSAALevels.Append(samples);
			}
		}
	}

	IndexT ret = m_FSAALevels.FindIndex(inMultisample);
	
	if (ret == InvalidIndex)
	{
		if (m_FSAALevels.Back() < inMultisample)
		{
			multisampleChosen = m_FSAALevels.Back();
		}
		else
		{
			for (IndexT i = 0; i < m_FSAALevels.Size(); ++i)
			{
				if (m_FSAALevels[i] > inMultisample)
				{
					if ( i > 0)
					{
						multisampleChosen = m_FSAALevels[i - 1];
					}
					else
					{
						multisampleChosen = m_FSAALevels[0];
					}

					break;
				}

			}
		}


	} 
	else
	{
		multisampleChosen = inMultisample;
	}

	n_delete_array(glConfigs);
}

void GLESContext::_SetCurrentContext()
{
	EGLBoolean ret = eglMakeCurrent(m_EglDisplay, m_EglSurface, m_EglSurface, m_Context);

	if (!ret)
	{
		n_error("Fail to make context current!");
	}
}

}
