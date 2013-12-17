/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
//#include <cstring>
#include "MyGUI_GenesisTexture.h"
//#include "MyGUI_DataManager.h"
//#include "MyGUI_GenesisRenderManager.h"
//#include "MyGUI_GenesisDiagnostic.h"
#include "MyGUI_GenesisRTTexture.h"

#include "resource/imageres.h"
#include "resource/resourceserver.h"
#include "graphicsystem/GraphicSystem.h"
#include "foundation/threading/criticalsection.h"
#include "foundation/util/queue.h"
#include "resource/resourcemanager.h"

namespace MyGUI
{

	using namespace Resources;
	using namespace Graphic;

	Util::String GenesisTexture::s_resourcePath = "";
	class TexUpdate
	{	
	public:

		static void Update(GenesisTexture* texture);

		static void updateTexture(RenderBase::Texture::MapInfo& texMap,int width,int height, int depth, RenderBase::PixelFormat::Code format, int mipLevel, void* tag);
	};

	void TexUpdate::Update(GenesisTexture* texture)
	{
		GraphicSystem::Instance()->UpdateTexture(texture->GetTextureHandle(), updateTexture, texture);

	}
	void TexUpdate::updateTexture(RenderBase::Texture::MapInfo& texMap,int width,int height, int depth, RenderBase::PixelFormat::Code format, int mipLevel, void* tag)
	{
		GenesisTexture* texture = static_cast<GenesisTexture*>(tag);
		if (texture->GetTextureHandle().IsValid() && texture->GetBuffer().isvalid())
		{
			size_t dst = (size_t)texMap.data;
			size_t pitch = texMap.rowPitch;
			size_t row_size = texture->getWidth() * texture->getNumElemBytes();

			if (!texture->GetBuffer()->IsOpen())
			{
				texture->GetBuffer()->Open();
			}
			if (texture->GetBuffer()->IsOpen())
			{
				for (int i = 0; i < texture->getHeight(); ++i)
				{
					texture->GetBuffer()->Seek(i * row_size, IO::Stream::Begin);
					texture->GetBuffer()->Read((void*)(dst + i * row_size), row_size);
				}
				texture->GetBuffer()->Close();
			}
		}

	}

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------
	GenesisTexture::GenesisTexture(const std::string& _name, const std::string& _group)
		: mName(_name)
		, mGroup(_group)
		, mRenderTarget(nullptr)
		, m_texHandle(NULL)
		, m_width(0)
		, m_height(0)
		, mNumElemBytes(0)
		, mOriginalFormat(PixelFormat::Unknow)
		, mOriginalUsage(TextureUsage::Default)
		, m_texStream(NULL)
		, m_bManualCreate(false)
	{
	}

	GenesisTexture::~GenesisTexture()
	{
		destroy();
	}

	void GenesisTexture::SetResourcePath(const Util::String& path)
	{
		s_resourcePath = path;
	}
	const std::string& GenesisTexture::getName() const
	{
		return mName;
	}

	void GenesisTexture::saveToFile(const std::string& _filename)		//[2012/4/20 zhongdaohuan] 暂缓实现
	{
		//... empty.
	}

	void GenesisTexture::setInvalidateListener(ITextureInvalidateListener* _listener)
	{
		mListener = _listener;
	}

	void GenesisTexture::destroy()
	{

		//[zhongdaohuan 2012/12/12] 如果这个texture是由render target创建的，那么，这个texture的句柄应该由render target类来管理。
		//现在的terender target还不能由mygui自己创建，所以所有render target都是源于mygui外部，
		//所以现在不会因mygui而引发内存泄漏问题，如果以后mygui内部自己也可以创建render target，那么，这里的逻辑应该重新评估。
		if (nullptr == mRenderTarget)
		{
			if (m_bManualCreate)
			{
				if (m_texHandle.IsValid())
				{
					GraphicSystem::Instance()->RemoveTexture(m_texHandle);
					m_texHandle = NULL;
				}
			}
			GenesisTextureMgr::Instance()->RemoveManualTexture(this);
		}

		m_texStream = NULL;
		mRenderTarget = nullptr;
		mNumElemBytes = 0;
		mOriginalFormat = PixelFormat::Unknow;
		mOriginalUsage = TextureUsage::Default;
		m_width = 0;
		m_height = 0;
	}

	int GenesisTexture::getWidth()
	{
		return m_width;//(int)mTexture->getWidth();
	}

	int GenesisTexture::getHeight()
	{
		return m_height;//(int)mTexture->getHeight();
	}
	PixelFormat GenesisTexture::getFormat()
	{
		return mOriginalFormat;
	}
	TextureUsage GenesisTexture::getUsage()
	{
		return mOriginalUsage;
	}
	size_t GenesisTexture::getNumElemBytes()
	{
		return mNumElemBytes;
	}
	void* GenesisTexture::lock(TextureUsage _access)
	{
		//[2012/4/12 zhongdaohuan]先不分TextureUsage::Write 和TextureUsage::Read的情况。so,_access暂时没用
		n_assert(NULL != m_texStream);
		m_texStream->SetAccessMode(IO::Stream::ReadWriteAccess);	//	王兴博。stream的类型在Open的时候可能导致数据清空
		if (!m_texStream->IsOpen())
		{
			m_texStream->Open();
		}
		return m_texStream->Map();
	}

	void GenesisTexture::unlock()
	{
		m_texStream->Unmap();
		if (m_texStream->IsOpen())
		{
			m_texStream->Close();
		}
		TexUpdate::Update(this);
	}

	bool GenesisTexture::isLocked()
	{
		return m_texStream->IsMapped();
	}

	PixelFormat GenesisTexture::FormatWjToMyGui(RenderBase::PixelFormat::Code format)
	{
		PixelFormat myFormat = PixelFormat::Unknow;
		switch (format)
		{
		case RenderBase::PixelFormat::L8:
			{
				myFormat = PixelFormat::L8;
			}
			break;
		case RenderBase::PixelFormat::L8A8:
			{
				myFormat = PixelFormat::L8A8;
			}
			break;
		case RenderBase::PixelFormat::R8G8B8:
			{
				myFormat = PixelFormat::R8G8B8;
			}
			break;
		case RenderBase::PixelFormat::R8G8B8A8:
			{
				myFormat = PixelFormat::R8G8B8A8;
			}
			break;
		default:
			{
				myFormat = PixelFormat::Unknow;
			}
			break;
		}
		return myFormat; 

	}

	RenderBase::PixelFormat::Code GenesisTexture::FormatMyGuiToWj(PixelFormat format)
	{
		RenderBase::PixelFormat::Code wjFormat = RenderBase::PixelFormat::InvalidPixelFormat;
		if(format == PixelFormat::L8)
		{
			wjFormat = RenderBase::PixelFormat::L8;
		}
		if (format == PixelFormat::L8A8)
		{
			wjFormat = RenderBase::PixelFormat::L8A8;
		}
		else if(format == PixelFormat::R8G8B8)
		{
			wjFormat = RenderBase::PixelFormat::R8G8B8;
		}

		else if(format == PixelFormat::R8G8B8A8)
		{
			wjFormat = RenderBase::PixelFormat::R8G8B8A8;
		}
		else 
		{
			wjFormat = RenderBase::PixelFormat::InvalidPixelFormat;
		}

		return wjFormat; 
	}

	RenderBase::RenderResource::Usage GenesisTexture::UsageMyGuiToWj(TextureUsage usage)
	{
		if (usage == TextureUsage::Default)
		{
			return RenderBase::RenderResource::UsageImmutable;//Ogre::TU_STATIC_WRITE_ONLY;
		}
		else if (usage == TextureUsage::RenderTarget)
		{
			return RenderBase::RenderResource::UsageDynamic;//Ogre::TU_RENDERTARGET;
		}
		else if (usage.isValue(TextureUsage::Static))
		{
			if (usage.isValue(TextureUsage::Write))
			{
				return RenderBase::RenderResource::UsageDynamic;//Ogre::TU_STATIC_WRITE_ONLY;
			}
			else
			{
				return RenderBase::RenderResource::UsageImmutable;//Ogre::TU_STATIC;
			}
		}
		else if (usage.isValue(TextureUsage::Dynamic))
		{
			if (usage.isValue(TextureUsage::Write))
			{
				return RenderBase::RenderResource::UsageDynamic;//Ogre::TU_DYNAMIC_WRITE_ONLY;
			}
			else
			{
				return RenderBase::RenderResource::UsageImmutable;//Ogre::TU_DYNAMIC;
			}
		}
		else if (usage.isValue(TextureUsage::Stream))
		{
			if (usage.isValue(TextureUsage::Write))
			{
				return RenderBase::RenderResource::UsageCpu;//Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE;
			}
			else
			{
				return RenderBase::RenderResource::UsageCpu;//Ogre::TU_DYNAMIC;
			}
		}
		return RenderBase::RenderResource::UsageImmutable;//Ogre::TU_DEFAULT;
	}

	void GenesisTexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format)
	{
		m_width = _width;
		m_height = _height;
		mOriginalUsage = _usage;
		setFormat(_format);
		RenderBase::PixelFormat::Code wj_format = FormatMyGuiToWj(_format);

		GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
		tex->Setup();

		// set type
		RenderBase::Texture::Type texType = RenderBase::Texture::Texture2D;

		tex->SetType( texType );

		tex->SetWidth( _width );
		tex->SetHeight( _height );
		tex->SetDepth( 1);
		tex->SetNumMipLevels( 1 );
		tex->SetPixelFormat( wj_format );

		tex->SetUsage(UsageMyGuiToWj(_usage));
		//tex->SetUsage(RenderBase::RenderResource::UsageDynamic);
		tex->SetAccess(RenderBase::RenderResource::AccessWrite);


		// dummy
		tex->SetSkippedMips( 0 );
		tex->SetUnitIndex( 0 );

		//tex->SetTexturePath();

		if (m_texStream)
		{
			m_texStream = NULL;
		}
		m_texStream = IO::MemoryStream::Create();
		m_texStream->SetAccessMode( IO::Stream::WriteAccess );
		if( m_texStream->Open() )
		{
			m_texStream->SetSize(m_width * m_height * mNumElemBytes);
			tex->SetStream( m_texStream.upcast<IO::Stream>() );
			m_texStream->Close();
			//m_texStream->SetAccessMode( IO::Stream::ReadAccess );
			m_texHandle = Graphic::GraphicSystem::Instance()->CreateTexture(tex);

			GenesisTextureMgr::Instance()->AddManualTexture(this);
			m_bManualCreate = true;
		}
		else
		{
			m_texHandle = NULL;
			m_width = 0;
			m_height = 0;
			mOriginalUsage = TextureUsage::Default;
			mOriginalFormat = PixelFormat::Unknow;
		}
	}
	GPtr<RenderBase::Texture> _BuildTextureData(const GPtr<Resources::ImageRes>& image, GPtr<IO::MemoryStream>& memStream)
	{
		n_assert(image.isvalid());

		if ( !image.isvalid() )
		{
			return GPtr<RenderBase::Texture>();
		}

		if ( !image->Validata() )
		{
			return GPtr<RenderBase::Texture>();
		}

		GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
		tex->Setup();

		// set type
		RenderBase::Texture::Type texType = RenderBase::Texture::InvalidType;

		if ( image->GetNumFace() == 1 )
		{
			if ( image->GetDepth() == 1)
			{
				texType = RenderBase::Texture::Texture2D; 
			}
			else
			{
				n_assert( image->GetDepth() > 1);
				texType = RenderBase::Texture::Texture3D; 
			}
		}
		else 
		{
			n_assert( image->GetNumFace() > 1);
			texType = RenderBase::Texture::TextureCube;
		}
		n_assert( texType != RenderBase::Texture::InvalidType)
			tex->SetType( texType );

		tex->SetWidth( image->GetWidth() );
		tex->SetHeight( image->GetHeight() );
		tex->SetDepth( image->GetDepth() );
		tex->SetNumMipLevels( image->GetMipMapLevel() + 1 );
		tex->SetPixelFormat( image->GetPixelFormat() );

		// dummy
		tex->SetSkippedMips( 0 );
		tex->SetUnitIndex( 0 );

		n_assert( image->GetResourceId().IsValid() );
		tex->SetTexturePath(image->GetResourceId());

		const GPtr<ImageData>& imageData = image->GetImageData();
		n_assert( imageData.isvalid() );
		if (memStream)
		{	
			memStream = NULL;
		}
		memStream = IO::MemoryStream::Create();

		memStream->SetAccessMode( IO::Stream::ReadWriteAccess );
		if( memStream->Open() )
		{
			memStream->Write( imageData->Ptr(), imageData->Size() );
			tex->SetStream( memStream.upcast<IO::Stream>() );
			memStream->Close();
			return tex;
		}

		return GPtr<RenderBase::Texture>();
	}
	void GenesisTexture::loadFromFile(const std::string& _filename)
	{

		Util::String filename = _filename.c_str();
		Util::String url = s_resourcePath + filename;

		/*Resources::ResourceServer* resServer = Resources::ResourceServer::Instance();
		GPtr<Resource> pRes = resServer->CreateOrGetResource(url, &ImageRes::RTTI );
		n_assert( pRes.isvalid() );

		if ( pRes->GetState() != Resource::Loaded )
		{
		bool bOK = resServer->LoadResource(pRes,false);
		if (!bOK)
		{			
		m_texHandle = RenderBase::PrimitiveHandle();
		return;
		}

		}

		GPtr<ImageRes> pImage = pRes.downcast<ImageRes>();
		n_assert( pImage.isvalid() );

		//pImage->SetManuLoad(true);	//	避免被卸载

		if ( !pRes.isvalid() || !pRes->GetResourceId().IsValid() )
		{
		m_texHandle = RenderBase::PrimitiveHandle();
		return;
		}

		m_width = pImage->GetWidth();
		m_height = pImage->GetHeight();
		mOriginalUsage = TextureUsage::Default;
		setFormat(FormatWjToMyGui(pImage->GetPixelFormat()));//mOriginalFormat =

		const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
		n_assert(gs.isvalid());

		GPtr<RenderBase::Texture> tex = _BuildTextureData(pImage, m_texStream);

		if ( tex.isvalid() )
		{
		m_texHandle = gs->CreateTexture( tex );
		}
		else
		{
		m_texHandle = RenderBase::TextureHandle();		
		}

		pRes->UnLoad();

		m_texStream = NULL;*/

		GPtr<TextureResInfo> tri = Resources::ResourceManager::Instance()->CreateTextureInfo(url, 0);
		m_texHandle = tri->GetHandle();
		RenderBase::TEXTURE_DESC texDesc;
		GraphicSystem::Instance()->GetTextureDesc(m_texHandle, texDesc);

		m_width = texDesc.width;
		m_height = texDesc.height;
		mOriginalUsage = TextureUsage::Default;
		setFormat(FormatWjToMyGui(texDesc.pixelFormat));//mOriginalFormat =


	}

	void GenesisTexture::createFromRenderTarget(IRenderTarget* rt)
	{
		mRenderTarget = rt;
		GenesisRTTexture* wjRt = static_cast<GenesisRTTexture*>(mRenderTarget);
		const GPtr<Graphic::RenderToTexture>& rendetToTexture = wjRt->getRenderToTexture();
		const GPtr<RenderBase::RenderTarget>& renderTarget = rendetToTexture->GetRenderTarget();


		m_width = renderTarget->GetWidth();
		m_height = renderTarget->GetHeight();
		mOriginalUsage = TextureUsage::RenderTarget;
		setFormat(FormatWjToMyGui(renderTarget->GetColorBufferFormat()));
		m_texHandle = rendetToTexture->GetTextureHandle();
	}

	void GenesisTexture::setFormat(PixelFormat format)
	{
		mOriginalFormat = format;
		mNumElemBytes = 0;

		if (format == PixelFormat::L8) 
			mNumElemBytes = 1;
		else if (format == PixelFormat::L8A8) 
			mNumElemBytes = 2;
		else if (format == PixelFormat::R8G8B8) 
			mNumElemBytes = 3;
		else if (format == PixelFormat::R8G8B8A8) 
			mNumElemBytes = 4;
	}


	IRenderTarget* GenesisTexture::getRenderTarget()
	{
		//if (mRenderTarget == nullptr)
		//	mRenderTarget = new OgreRTTexture(mTexture);

		return mRenderTarget;	
	}

	//IRenderTarget* OgreTexture::getRenderTarget()
	//{
	//	if (mRenderTarget == nullptr)
	//		mRenderTarget = new OgreRTTexture(mTexture);

	//	return mRenderTarget;
	//}

	__ImplementClass(GenesisTextureMgr,'WTMR',Core::RefCounted);
	__ImplementImageSingleton(GenesisTextureMgr);

	GenesisTextureMgr::GenesisTextureMgr()
	{
		__ConstructImageSingleton;
	}

	GenesisTextureMgr::~GenesisTextureMgr()
	{
		__DestructImageSingleton;
	}

	void GenesisTextureMgr::AddManualTexture(GenesisTexture* const& pTex)
	{
		IndexT res = m_ManualTextures.FindIndex(pTex);

		if (res == InvalidIndex)
		{
			m_ManualTextures.Append(pTex);
		}
	}

	void GenesisTextureMgr::RemoveManualTexture(GenesisTexture* const& pTex)
	{
		IndexT res = m_ManualTextures.FindIndex(pTex);
		if (res != InvalidIndex)
		{
			m_ManualTextures.EraseIndex(res);
		}
	}

	void GenesisTextureMgr::ReLoadManualTextures() const
	{
		SizeT nCount = m_ManualTextures.Size();

		for (IndexT i = 0; i < nCount; ++i)
		{

			GenesisTexture* pTex = m_ManualTextures[i];

			SizeT width  = pTex->getWidth();
			SizeT height = pTex->getHeight();

			RenderBase::PixelFormat::Code wj_format = GenesisTexture::FormatMyGuiToWj(pTex->getFormat());

			GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
			tex->Setup();

			// set type
			RenderBase::Texture::Type texType = RenderBase::Texture::Texture2D;

			tex->SetType( texType );

			tex->SetWidth( width );
			tex->SetHeight( height );
			tex->SetDepth( 1);
			tex->SetNumMipLevels( 1 );
			tex->SetPixelFormat( wj_format );

			tex->SetAccess(RenderBase::RenderResource::AccessWrite);

			// dummy
			tex->SetSkippedMips( 0 );
			tex->SetUnitIndex( 0 );

			tex->SetStream( pTex->GetBuffer().upcast<IO::Stream>() );

			Graphic::GraphicSystem::Instance()->UpdateTexture(pTex->GetTextureHandle(), tex);
		}
	}

} // namespace MyGUI
