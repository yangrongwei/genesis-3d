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
#include "RenderSystemThreadHandler.h"
#include "RenderMessageProtocol.h"
#include "messaging/staticmessagehandler.h"

namespace RenderBase
{
	__ImplementClass(RenderSystemThreadHandler,'MHRS',Interface::InterfaceHandlerBase)
	using namespace Interface;

	RenderSystemThreadHandler::RenderSystemThreadHandler()
	{
#ifdef __WIN32__
		m_mainHWND = NULL;
#endif
	}

	RenderSystemThreadHandler::~RenderSystemThreadHandler()
	{
		///empty
	}

	void RenderSystemThreadHandler::Open()
	{
		Super::Open();
		m_renderSystem = RenderSystem::Create();
#ifdef __WIN32__
		m_renderSystem->SetMainWindowHandle(m_mainHWND);
#endif// __WIN32__
	}

	void RenderSystemThreadHandler::Close()
	{
		Super::Close();
		n_assert(m_renderSystem.isvalid())
		m_renderSystem->Close();
		m_renderSystem = 0;
	}

	bool RenderSystemThreadHandler::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		n_assert(msg.isvalid());

		__StaticHandle(StartRenderSystemMSG);
		__StaticHandle(BeginFrameMSG);
		__StaticHandle(EndFrameMSG);
		__StaticHandle(SetViewPortMSG);
		__StaticHandle(CreateTextureMSG);
		__StaticHandle(CreateShaderProgramMSG);
		__StaticHandle(CreateRenderTargetMSG);
		__StaticHandle(CreatePrimitiveGroupMSG);
		__StaticHandle(UpdatePrimitiveGroupMSG);
		__StaticHandle(SetTextureMSG);
		__StaticHandle(SetRenderStateMSG);
		__StaticHandle(SetVertexShaderConstantVectorFMSG);
		__StaticHandle(SetPixelShaderConstantVectorFMSG);
		__StaticHandle(SetVertexShaderConstantFloatMSG);
		__StaticHandle(SetPixelShaderConstantFloatMSG);
		__StaticHandle(SetVertexShaderConstantMatrixFMSG);
		__StaticHandle(SetPixelShaderConstantMatrixFMSG);
		__StaticHandle(SetGPUProgramMSG);
		__StaticHandle(SetRenderTargetMSG);
		__StaticHandle(DrawMSG);
		__StaticHandle(RemoveRenderResourceMSG);

		return false;

	}

	void RenderSystemThreadHandler::DoWork()
	{

	}
	
};