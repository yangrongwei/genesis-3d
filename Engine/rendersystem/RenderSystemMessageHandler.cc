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
#include "RenderMessageProtocol.h"
#include "RenderSystem.h"
#include "messaging/staticmessagehandler.h"

namespace Messaging
{
	__StaticHandler(RenderBase::StartRenderSystemMSG)
	{
		//RenderBase::RenderSystem::Instance()->Open();
	}

	__StaticHandler(RenderBase::BeginFrameMSG)
	{
		RenderBase::RenderSystem::Instance()->BeginFrame();
	}

	__StaticHandler(RenderBase::EndFrameMSG)
	{
		RenderBase::RenderSystem::Instance()->EndFrame();
	}

	__StaticHandler(RenderBase::SetViewPortMSG)
	{
		//RenderBase::RenderSystem::Instance()->_SetViewPort(msg->GetX(),msg->GetY(),msg->GetWidth(),msg->GetHeight(),msg->GetMinZ(),msg->GetMaxZ());
		n_error("SetViewPortMSG changed,being not implemented now");
	}

	__StaticHandler(RenderBase::CreateTextureMSG)
	{
		RenderBase::TextureHandle handle = RenderBase::RenderSystem::Instance()->CreateTexture(msg->GetTexture());
		msg->SetHandle(handle);
	}

	__StaticHandler(RenderBase::CreatePrimitiveGroupMSG)
	{
		//RenderBase::PrimitiveHandle handle = RenderBase::RenderSystem::Instance()->CreatePrimitiveGroup(msg->GetPrimitiveGroup());
		//msg->SetHandle(handle);
	}

	__StaticHandler(RenderBase::CreateShaderProgramMSG)
	{
		RenderBase::GPUProgramHandle handle = RenderBase::RenderSystem::Instance()->CreateShaderProgram(msg->GetProgram());
		msg->SetHandle(handle);
	}

	__StaticHandler(RenderBase::CreateRenderTargetMSG)
	{
		RenderBase::TextureHandle texhandle; 
		RenderBase::RenderTargetHandle handle = RenderBase::RenderSystem::Instance()->CreateRenderTarget(msg->GetRenderTarget(),texhandle);
		msg->SetHandle(handle);
		msg->SetTextureHandle(texhandle);
	}

	__StaticHandler(RenderBase::SetTextureMSG)
	{
		RenderBase::RenderSystem::Instance()->_SetTexture(msg->GetHandle(),msg->GetTexUnit());
	}

	__StaticHandler(RenderBase::SetRenderStateMSG)
	{
		RenderBase::RenderSystem::Instance()->_SetRenderState(msg->GetObject());
	}

	__StaticHandler(RenderBase::SetVertexShaderConstantVectorFMSG)
	{
		RenderBase::RenderSystem::Instance()->SetVertexShaderConstantVectorF(msg->GetReg(),msg->GetValueRef(),msg->GetVec4count());
	}

	__StaticHandler(RenderBase::SetPixelShaderConstantVectorFMSG)
	{
		RenderBase::RenderSystem::Instance()->SetPixelShaderConstantVectorF(msg->GetReg(),msg->GetValueRef(),msg->GetVec4count());
	}

	__StaticHandler(RenderBase::SetVertexShaderConstantFloatMSG)
	{
		RenderBase::RenderSystem::Instance()->SetVertexShaderConstantFloat(msg->GetReg(), msg->GetValueRef());
	}

	__StaticHandler(RenderBase::SetPixelShaderConstantFloatMSG)
	{
		RenderBase::RenderSystem::Instance()->SetPixelShaderConstantFloat(msg->GetReg(), msg->GetValueRef());
	}

	__StaticHandler(RenderBase::SetVertexShaderConstantMatrixFMSG)
	{
		RenderBase::RenderSystem::Instance()->SetVertexShaderConstantMatrixF(msg->GetReg(),msg->GetValueRef(), msg->GetmatrixCount());
	}

	__StaticHandler(RenderBase::SetPixelShaderConstantMatrixFMSG)
	{
		RenderBase::RenderSystem::Instance()->SetPixelShaderConstantMatrixF(msg->GetReg(),msg->GetValueRef(), msg->GetmatrixCount());
	}

	__StaticHandler(RenderBase::SetGPUProgramMSG)
	{
		RenderBase::RenderSystem::Instance()->_SetShaderProgram(msg->GetHandle());
	}

	__StaticHandler(RenderBase::SetRenderTargetMSG)
	{
		RenderBase::RenderSystem::Instance()->_SetRenderTarget(msg->GetHandle(),msg->GetIndex(),msg->GetClearFlag());
	}

	__StaticHandler(RenderBase::DrawMSG)
	{
		RenderBase::RenderSystem::Instance()->_DrawPrimitive(msg->GetHandle(),
															msg->GetStartVertice(),
															msg->GetEndVertice(),
															msg->GetStartIndice(),
															msg->GetEndIndice());
	}

	__StaticHandler(RenderBase::UpdatePrimitiveGroupMSG)
	{
		//RenderBase::RenderSystem::Instance()->UpdatePrimitiveGroup(msg->GetHandle(),msg->GetPrimitiveGroup());
	}

	__StaticHandler(RenderBase::RemoveRenderResourceMSG)
	{
		RenderBase::RenderSystem::Instance()->_RemoveResouce(msg->GetHandle());
	}

	//////////////////////////////////////////////////////////////////////////
	//Fixed Pipeline Functions
	__StaticHandler(RenderBase::FXSetClipPlaneMSG)
	{
		RenderBase::RenderSystem::Instance()->_FXSetClipPlane(msg->GetIndex(),msg->GetPlane());
	}
}