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
#include "GenesisMakeMaterial.h"
#include "graphicsystem/GraphicSystem.h"
#include "io/memorystream.h"
#include "io/iointerfaceprotocol.h"
#include "io/iointerface.h"
namespace GenesisMaterialMaker
{
	GenesisMakeMaterial::GenesisMakeMaterial()
	{
		//empty
	}

	GenesisMakeMaterial::~GenesisMakeMaterial()
	{
		//empty
	}

	const Util::String GenesisMakeMaterial::GetMatParamValueByName(const Util::String& name) const
	{
		for (SizeT i = 0; i < m_matParamList.Size(); ++i)
		{
			if (m_matParamList[i]->GetName() == name)
			{
				return m_matParamList[i]->GetStringValue();
			}
		}
		return "";
	}

	RenderBase::GPUProgramHandle GenesisMakeMaterial::CreateGPUProgram()
	{
		for (SizeT i = 0; i < m_TechniqueList.Size(); ++i)
		{
			return m_TechniqueList[i].CreateGPUProgram();
		}
		return RenderBase::GPUProgramHandle();
	}

	void GenesisMakeMaterial::MakeMaterial(GPtr<Graphic::Material>& mat)
	{
		mat = Graphic::Material::Create();
		mat->SetRenderQueue(m_renderQueue);
		mat->AddParams(m_matParamList);
		for (SizeT i = 0; i < m_TechniqueList.Size(); ++i)
		{
			GPtr<Graphic::MaterialTech> tech;
			m_TechniqueList[i].CreateTech(tech);
			mat->AddTech(tech);
			
		}
	}

	void GenesisMakeMaterial::AssignDefaultMatParamBindings()
	{
		//textures
		{
			static RenderBase::TextureHandle tex2DHandle,tex3DHandle,texCubeHandle;
			if (!tex2DHandle.IsValid())
			{
				GPtr<RenderBase::Texture> tex2d = RenderBase::Texture::Create();
				tex2d->Setup();
#if __WIN32__ && RENDERDEVICE_D3D9
				tex2d->SetTexturePath("sys:white.dds");
#elif __ANDROID__ || RENDERDEVICE_OPENGLES
				tex2d->SetTexturePath("sys:white.jpg");
				tex2d->SetPixelFormat(RenderBase::PixelFormat::A8R8G8B8);
#endif
				GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
				n_assert( pStream );
				GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
				n_assert( readStreamMsg );
				readStreamMsg->SetFileName( tex2d->GetTexturePath() );
				readStreamMsg->SetStream( pStream );
				IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

				if ( !readStreamMsg->GetResult() )
				{
					n_warning( "GenesisMakeMaterial::AssignDefaultMatParamBindings::AssignDefaultMatParamBindings: can not open %s", tex2d->GetTexturePath().AsString().AsCharPtr() );
				}
				tex2d->SetStream(pStream);
				tex2d->SetType(RenderBase::Texture::Texture2D);
				tex2DHandle = Graphic::GraphicSystem::Instance()->CreateTexture(tex2d);
			}
#if __WIN32__ && RENDERDEVICE_D3D9
			if (!tex3DHandle.IsValid())
			{
				GPtr<RenderBase::Texture> tex3d = RenderBase::Texture::Create();
				tex3d->Setup();
				tex3d->SetTexturePath("sys:Random3D.dds");
				GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
				n_assert( pStream );
				GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
				n_assert( readStreamMsg );
				readStreamMsg->SetFileName( tex3d->GetTexturePath().Value() );
				readStreamMsg->SetStream( pStream );
				IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

				if ( !readStreamMsg->GetResult() )
				{
					n_warning( "GenesisMakeMaterial::AssignDefaultMatParamBindings::AssignDefaultMatParamBindings: can not open %s", tex3d->GetTexturePath().AsString().AsCharPtr() );
				}
				tex3d->SetStream(pStream);
				tex3DHandle = Graphic::GraphicSystem::Instance()->CreateTexture(tex3d);
			}

			if (!texCubeHandle.IsValid())
			{
				GPtr<RenderBase::Texture> texcube = RenderBase::Texture::Create();
				texcube->Setup();
				texcube->SetTexturePath("sys:whitecube.dds");
				GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
				n_assert( pStream );
				GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
				n_assert( readStreamMsg );
				readStreamMsg->SetFileName( texcube->GetTexturePath() );
				readStreamMsg->SetStream( pStream );
				IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

				if ( !readStreamMsg->GetResult() )
				{
					n_warning( "GenesisMakeMaterial::AssignDefaultMatParamBindings::AssignDefaultMatParamBindings: can not open %s", texcube->GetTexturePath().AsString().AsCharPtr() );
				}
				texcube->SetStream(pStream);
				texCubeHandle = Graphic::GraphicSystem::Instance()->CreateTexture(texcube);
			}
#endif
			for (SizeT i = 0; i < m_matParamList.Size(); ++i)
			{
				if(m_matParamList[i]->GetType() == Graphic::eMaterialParamTexture2D)
				{
					static_cast<Graphic::MaterialParamTex2D*>(m_matParamList[i])->SetHandle(tex2DHandle);
				}
#if __WIN32__ && RENDERDEVICE_D3D9
				else if (m_matParamList[i]->GetType() == Graphic::eMaterialParamTexture3D)
				{
					static_cast<Graphic::MaterialParamTex3D*>(m_matParamList[i])->SetHandle(tex3DHandle);
				}
				else if(m_matParamList[i]->GetType() == Graphic::eMaterialParamTextureCUBE)
				{
					static_cast<Graphic::MaterialParamTexCube*>(m_matParamList[i])->SetHandle(texCubeHandle);
				}
#endif
			}

			//_SetTextureSamplers();
		}
		//variables
		{
			for (SizeT i = 0; i < m_matParamList.Size(); ++i)
			{
				switch(m_matParamList[i]->GetType())
				{
				case Graphic::eMaterialParamFloat:
					{
						Graphic::MaterialParamFloat* pMpf = static_cast<Graphic::MaterialParamFloat*>(m_matParamList[i]);
						pMpf->SetValue(pMpf->GetStringValue().AsFloat());
						break;
					}
					

				case Graphic::eMaterialParamVector:
					{
						Graphic::MaterialParamVector* pMpv = static_cast<Graphic::MaterialParamVector*>(m_matParamList[i]);
						pMpv->SetValue(pMpv->GetStringValue().AsFloat4());
						break;
					}

				case Graphic::eMaterialParamMatrix:
					{
						Graphic::MaterialParamMatrix* pMpm = static_cast<Graphic::MaterialParamMatrix*>(m_matParamList[i]);
						pMpm->SetValue(pMpm->GetStringValue().AsMatrix44());
						break;
					}
					
				}
				
			}
		}
		

	}

	void GenesisMakeMaterial::_SetTextureSamplers()
	{
		for(SizeT i = 0; i < m_TechniqueList.Size(); ++i)
		{
			m_TechniqueList[i].AssignSamplerStates(m_TexSamplerStateList);
		}
	}
}