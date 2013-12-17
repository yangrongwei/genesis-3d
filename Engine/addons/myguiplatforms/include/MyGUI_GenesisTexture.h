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
#ifndef __MYGUI_GENESIS_TEXTURE_H__
#define __MYGUI_GENESIS_TEXTURE_H__

#include "MyGUI_ITexture.h"

#include "rendersystem/base/RenderDeviceTypes.h"
#include "rendersystem/base/RenderResource.h"
#include "foundation/io/memorystream.h"
#include "foundation/util/string.h"
#include "core/singleton.h"
#include "util/array.h"

namespace MyGUI
{

	class GenesisTexture :
		public ITexture//,
		//public Ogre::ManualResourceLoader
	{
	public:
		GenesisTexture(const std::string& _name, const std::string& _group);
		virtual ~GenesisTexture();

		virtual const std::string& getName() const;

		virtual void createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format);
		virtual void loadFromFile(const std::string& _filename);
		virtual void saveToFile(const std::string& _filename);

		virtual void createFromRenderTarget(IRenderTarget* rt);

		virtual void setInvalidateListener(ITextureInvalidateListener* _listener);

		virtual void destroy();

		virtual void* lock(TextureUsage _access);
		virtual void unlock();
		virtual bool isLocked();

		virtual int getWidth();
		virtual int getHeight();

		virtual PixelFormat getFormat();
		virtual TextureUsage getUsage();
		virtual size_t getNumElemBytes();

		virtual IRenderTarget* getRenderTarget();

		typedef GPtr<IO::MemoryStream> TextureBuffer;

		TextureBuffer& GetBuffer();
		RenderBase::TextureHandle GetTextureHandle() const;
		static PixelFormat FormatWjToMyGui(RenderBase::PixelFormat::Code format);
		static RenderBase::PixelFormat::Code FormatMyGuiToWj(PixelFormat format);
		static RenderBase::RenderResource::Usage UsageMyGuiToWj(TextureUsage usage);

		static void SetResourcePath(const Util::String& path);

	private:

		void setFormat(PixelFormat format);
		std::string mName;
		std::string mGroup;
		IRenderTarget* mRenderTarget;

		TextureUsage mOriginalUsage;
		PixelFormat mOriginalFormat;
		size_t mNumElemBytes;
		ITextureInvalidateListener* mListener;


		typedef unsigned char Byte;	
		size_t m_width;
		size_t m_height;
		TextureBuffer m_texStream;
		RenderBase::TextureHandle m_texHandle;
		static Util::String s_resourcePath;
		bool m_bManualCreate;

	};

	inline GenesisTexture::TextureBuffer& GenesisTexture::GetBuffer()
	{
		return m_texStream;
	}

	inline RenderBase::TextureHandle GenesisTexture::GetTextureHandle() const
	{
		return m_texHandle;
	}


	class GenesisTextureMgr : public Core::RefCounted
	{
		__DeclareSubClass(GenesisTextureMgr,Core::RefCounted);
		__DeclareImageSingleton(GenesisTextureMgr);

	public:

		GenesisTextureMgr();

		~GenesisTextureMgr();

	public:

		void AddManualTexture(GenesisTexture* const& pTex);
		void RemoveManualTexture(GenesisTexture* const& pTex);

		void ReLoadManualTextures() const;

	private:

		Util::Array< GenesisTexture* > m_ManualTextures;
	};


} // namespace MyGUI

#endif // __MYGUI_GENESIS_TEXTURE_H__
