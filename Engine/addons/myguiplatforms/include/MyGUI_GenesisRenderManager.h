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
#ifndef __MYGUI_GENESIS_RENDER_MANAGER_H__
#define __MYGUI_GENESIS_RENDER_MANAGER_H__

#include "MyGUI_RenderFormat.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_RenderManager.h"

#include "graphicsystem/GraphicSystem.h"
#include "RenderSystem.h"

namespace MyGUI
{
	class GenesisVertexBufferMgr;
	class GenesisTextureMgr;

	class GenesisRenderManager :
		public RenderManager,
		public IRenderTarget
	{
	public:
		GenesisRenderManager();
		virtual ~GenesisRenderManager();
		void initialise();
		void shutdown();

		static GenesisRenderManager& getInstance();
		static GenesisRenderManager* getInstancePtr();

		/** @see RenderManager::getViewSize */
		virtual const IntSize& getViewSize() const;

		/** @see RenderManager::getVertexFormat */
		virtual VertexColourType getVertexFormat();

		/** @see RenderManager::createVertexBuffer */
		virtual IVertexBuffer* createVertexBuffer();
		/** @see RenderManager::destroyVertexBuffer */
		virtual void destroyVertexBuffer(IVertexBuffer* _buffer);

		/** @see RenderManager::createTexture */
		virtual ITexture* createTexture(const std::string& _name);
		/** @see RenderManager::destroyTexture */
		virtual void destroyTexture(ITexture* _texture);
		/** @see RenderManager::getTexture */
		virtual ITexture* getTexture(const std::string& _name);

		/** @see RenderManager::isFormatSupported */
		virtual bool isFormatSupported(PixelFormat _format, TextureUsage _usage);

		/** @see IRenderTarget::begin */
		virtual void begin();
		/** @see IRenderTarget::end */
		virtual void end();

		/** @see IRenderTarget::doRender */
		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

		/** @see IRenderTarget::getInfo */
		virtual const RenderTargetInfo& getInfo();
#if MYGUI_DEBUG_MODE == 1
		virtual bool checkTexture(ITexture* _texture);
#endif

		void setResolution(int width, int height);//0 means auto.

		void setResolution(const IntSize& size);//0 means auto.

		const IntSize& getResolution() const;

		bool autoResolutionWidth() const;
		bool autoResolutionHeight() const;

		void windowResized();

		void deviceReseted();

		void renderGUI();

		bool getManualRender();

		void setManualRender(bool _value);		

		size_t getBatchCount() const;

		static void SetResourcePath(const Util::String& path);

		void  outofDate();

	private:

		void resetViewSize();
		void destroyAllResources();
		void updateRenderInfo();

		bool mUpdate;
		IntSize mCurrentResolution;
		IntSize mResolutionConfig;
		VertexColourType mVertexFormat;
		RenderTargetInfo mInfo;
		typedef std::map<std::string, ITexture*> MapTexture;
		MapTexture mTextures;

		bool mIsInitialise;
		bool mManualRender;
		size_t mCountBatch;

		//[2012/4/12 zhondaohuan] 以下是移植过程中额外添加的

	private:
		friend class GenesisRTTexture;
		void _loadShader();					
		void _checkShader();
		void _beforeDraw();
		GPtr<Graphic::Material> m_shader;
		//GPtr<RenderBase::RenderStateObject> m_renderState;
		RenderBase::GPUProgramHandle* m_shaderHandle;
		static Util::String s_resourcePath;

		GenesisVertexBufferMgr* m_VertexMgr;
		GenesisTextureMgr*      m_TextureMgr;
	};

	inline void GenesisRenderManager::_checkShader()
	{
		if (NULL == m_shader)
		{
			_loadShader();
		}
	}

	inline const IntSize& GenesisRenderManager::getResolution() const
	{
		return mCurrentResolution;
	}

	inline bool GenesisRenderManager::autoResolutionWidth() const
	{
		return (0 == mResolutionConfig.width);
	}

	inline bool GenesisRenderManager::autoResolutionHeight() const
	{
		return (0 == mResolutionConfig.height);
	}

	inline void GenesisRenderManager::outofDate() 
	{
		mUpdate = true;
	}

} // namespace MyGUI

#endif // __MYGUI_GENESIS_RENDER_MANAGER_H__
