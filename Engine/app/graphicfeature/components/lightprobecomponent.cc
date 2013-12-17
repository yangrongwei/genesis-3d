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
#include "lightprobecomponent.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "graphicfeature/graphicsfeature.h"
#include "rendersystem/RenderSystem.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/Camera/Camera.h"
#include "math/float4.h"
#include "app/basegamefeature/managers/timesource.h"
#include "addons/resource/imageoperations.h"

namespace App
{
	__ImplementClass(App::LightprobeComponent, 'LPOM', App::RenderComponent)

LightprobeComponent::LightprobeComponent():
	 rendertime(0)
    ,m_RenderTime(-1)
{

}
LightprobeComponent::~LightprobeComponent()
{

	
}
void LightprobeComponent::_UpdateRenderQueue()
{

}
void LightprobeComponent::SetupCallbacks()
{
	mActor->RegisterComponentCallback(this, BeginFrame);
	mActor->RegisterComponentCallback(this, OnFrame);
}

void LightprobeComponent::SetupAcceptedMessages()
{
	Super::SetupAcceptedMessages();
}

void LightprobeComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
{
	Super::HandleMessage(msg);
}

void LightprobeComponent::OnActivate()
{
	CreateCameraAndRT();
}

void LightprobeComponent::OnDeactivate()
{

}


void LightprobeComponent::_OnBeginFrame()
{
	Super::_OnBeginFrame();

	
	
}

void LightprobeComponent::_OnFrame()
{
	if(m_RenderTime==0)
	{
		m_RenderTime++;
	}
	else if(m_RenderTime>=1)
	{
		SaveRenderResult(m_TexturePath);
		m_RenderTime = -1;
		RemoveCamera();
		mActor->DestroyComponent(this);
	}
	else
	{

	}
	
}

void LightprobeComponent::CopyFrom( const GPtr<Component>& pComponent )
{
	n_error("light probe component can't be copied");
}

void LightprobeComponent::CreateCameraAndRT()
{
	__CreateCamAndRT(m_pXPosTexture,m_pXPosCam,X_POS);
	__CreateCamAndRT(m_pXNegTexture,m_pXNegCam,X_NEG);

	__CreateCamAndRT(m_pYPosTexture,m_pYPosCam,Y_POS);
	__CreateCamAndRT(m_pYNegTexture,m_pYNegCam,Y_NEG);

	__CreateCamAndRT(m_pZPosTexture,m_pZPosCam,Z_POS);
	__CreateCamAndRT(m_pZNegTexture,m_pZNegCam,Z_NEG);
}

void LightprobeComponent::_OnEndFrame()
{

}

App::Version LightprobeComponent::GetVersion() const
{
	return 1;
}

void LightprobeComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
{

}

void LightprobeComponent::Save( AppWriter* pWriter ) const
{

}

void LightprobeComponent::SaveRenderResult( const Util::String& path )
{
#ifdef	__WIN32__
	m_pExportCubeTex = D3D9::TextureD3D9::Create();
	
	const D3D9::TextureD3D9& front = m_pXPosTexture->GetD3DTexture9();
	const D3D9::TextureD3D9& back = m_pXNegTexture->GetD3DTexture9();

	const D3D9::TextureD3D9& top = m_pYPosTexture->GetD3DTexture9();
	const D3D9::TextureD3D9& under = m_pYNegTexture->GetD3DTexture9();

	const D3D9::TextureD3D9& right = m_pZPosTexture->GetD3DTexture9();
	const D3D9::TextureD3D9&  left = m_pZNegTexture->GetD3DTexture9();
	
	ubyte* CubeData = NULL;
	CubeData = n_new_array(ubyte,front.GetTextureSize()*6);  
	n_assert(CubeData!=NULL);

//front
	SizeT levelPixelSize =front.GetTextureSize();
	ubyte* dataFront = new ubyte[levelPixelSize];
	n_assert(dataFront!=NULL);
	front.GetTextureData(dataFront);

	Resources::ImageOperations::HorizontalFlipImage(dataFront,levelPixelSize,front.GetHeight(),front.GetWidth());
//back
	levelPixelSize =back.GetTextureSize();
	ubyte* dataBack = new ubyte[levelPixelSize];
	n_assert(dataBack!=NULL);
	back.GetTextureData(dataBack);

	Resources::ImageOperations::HorizontalFlipImage(dataBack,levelPixelSize,front.GetHeight(),front.GetWidth());
//left
	levelPixelSize =left.GetTextureSize();
	ubyte* dataLeft = new ubyte[levelPixelSize];
	n_assert(dataLeft!=NULL);
	left.GetTextureData(dataLeft);

	Resources::ImageOperations::HorizontalFlipImage(dataLeft,levelPixelSize,front.GetHeight(),front.GetWidth());
//right
	levelPixelSize =front.GetTextureSize();
	ubyte* dataRight = new ubyte[levelPixelSize];
	n_assert(dataRight!=NULL);
	right.GetTextureData(dataRight);

	Resources::ImageOperations::HorizontalFlipImage(dataRight,levelPixelSize,front.GetHeight(),front.GetWidth());

//up
	levelPixelSize =front.GetTextureSize();
	ubyte* dataUp = new ubyte[levelPixelSize];
	n_assert(dataUp!=NULL);
	top.GetTextureData(dataUp);

	Resources::ImageOperations::HorizontalFlipImage(dataUp,levelPixelSize,front.GetHeight(),front.GetWidth());

//down
	levelPixelSize =front.GetTextureSize();
	ubyte* dataDown = new ubyte[levelPixelSize];
	n_assert(dataDown!=NULL);
	under.GetTextureData(dataDown);

	Resources::ImageOperations::HorizontalFlipImage(dataDown,levelPixelSize,front.GetHeight(),front.GetWidth());

//data generate
	ubyte* srcDataOffset = NULL;
	srcDataOffset = CubeData;
	Memory::CopyToGraphicsMemory(dataFront,srcDataOffset,levelPixelSize);

	srcDataOffset += front.GetTextureSize();
	Memory::CopyToGraphicsMemory(dataBack,srcDataOffset,levelPixelSize);

	srcDataOffset += front.GetTextureSize();
	Memory::CopyToGraphicsMemory(dataUp,srcDataOffset,levelPixelSize);

	srcDataOffset += front.GetTextureSize();
	Memory::CopyToGraphicsMemory(dataDown,srcDataOffset,levelPixelSize);

	srcDataOffset += front.GetTextureSize();
	Memory::CopyToGraphicsMemory(dataRight,srcDataOffset,levelPixelSize);

	srcDataOffset += front.GetTextureSize();
	Memory::CopyToGraphicsMemory(dataLeft,srcDataOffset,levelPixelSize);

	
	Resources::ImageOperations::SaveDDSCubeImage(front.GetHeight(),front.GetWidth(),path,CubeData,front.GetTextureSize()*6);

	n_delete_array(CubeData);

	n_delete_array(dataFront);
	n_delete_array(dataBack);
	n_delete_array(dataLeft);
	n_delete_array(dataRight);
	n_delete_array(dataUp);
	n_delete_array(dataDown);
#endif
}



void LightprobeComponent::__CreateCamAndRT( GPtr<Graphic::RenderToTexture>& rt,GPtr<Graphic::Camera>& cam ,CameraFacingDirection direction)
{
	//zhongdaohuan 无用的component，无用的逻辑。
	//const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();

	//rt = Graphic::RenderToTexture::Create();
	//n_assert(rt.isvalid());

	//rt->Setup(512, 512, RenderBase::PixelFormat::A8R8G8B8, RenderBase::RenderTarget::ClearAll,
	//	Math::float4(0.f, 0.f, 0.f, 1.0f),true,1.f);

	//cam = Graphic::Camera::Create();

	//Graphic::CameraSetting cs = cam->GetCameraSetting();
	//cs.SetupPerspectiveFovRH(Math::n_deg2rad(90.0f), 1.f, 0.1f, 2500.0f);

	//Math::float4 _Pos = mActor->GetPosition();
	//Math::matrix44 viewMat;
	//
	//if ( direction==X_POS )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.x()			= facing.x()+10;
	//	Math::float4 up		= Math::float4(0,1,0,0);
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else if ( direction==X_NEG )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.x()			= facing.x()-10;
	//	Math::float4 up		= Math::float4(0,1,0,0);		
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else if ( direction==Y_POS )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.y()			= facing.y()+10;
	//	Math::float4 up		= Math::float4(0,0,-1,0);
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else if ( direction==Y_NEG )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.y()			= facing.y()-10;
	//	Math::float4 up		= Math::float4(0,0,1,0);
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else if ( direction==Z_POS )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.z()			= facing.z()+10;
	//	Math::float4 up		= Math::float4(0,1,0,0);
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else if ( direction==Z_NEG )
	//{
	//	Math::float4 facing = _Pos;
	//	facing.z()			= facing.z()-10;
	//	Math::float4 up		= Math::float4(0,1,0,0);
	//	viewMat = Math::matrix44::lookatrh(_Pos,facing,up);
	//}
	//else
	//{
	//	n_error("unexpected camera facing direction");
	//}
	//viewMat = Math::matrix44::inverse(viewMat);
	//cs.UpdateViewMatrix(viewMat);
	//cam->SetTransform(viewMat);
	//cam->SetCameraSetting(cs);

	//cam->SetCameraOrder(Graphic::eCO_CustomBeforeMain);
	//cam->SetCullMask( static_cast<Graphic::RenderLayer>(Graphic::eRLNone) );
	//cam->SetRenderToTexture(rt);

	//cam->SetRenderDepth(false);
	//cam->SetRenderNormal(true);
	//cam->SetUseCustomMaterial(false);
}

void LightprobeComponent::TakePhoto()
{
	m_RenderTime = 0;
	AddCamera();
}

void LightprobeComponent::RemoveCamera()
{
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pXPosCam);
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pXNegCam);
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pYPosCam);
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pYNegCam);
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pZPosCam);
	Graphic::GraphicSystem::Instance()->RemoveCamera(m_pZNegCam);
}

void LightprobeComponent::AddCamera()
{
	Graphic::GraphicSystem::Instance()->AddCamera(m_pXPosCam);
	Graphic::GraphicSystem::Instance()->AddCamera(m_pXNegCam);
	Graphic::GraphicSystem::Instance()->AddCamera(m_pYPosCam);
	Graphic::GraphicSystem::Instance()->AddCamera(m_pYNegCam);
	Graphic::GraphicSystem::Instance()->AddCamera(m_pZPosCam);
	Graphic::GraphicSystem::Instance()->AddCamera(m_pZNegCam);
}

}
