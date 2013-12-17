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
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif

#include "GraphicSystem.h"
#include "rendersystem/RenderMessageProtocol.h"
#include "Camera/RenderPipeline/RenderPipelineManager.h"
#include "vis/vissystems/visquadtree.h"
#include "base/RenderWindow.h"
#include "Renderable/RenderObject.h"
#include "Renderable/GraphicRenderer.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "resource/resourcemanager.h"
namespace Graphic
{

	struct CompareRenderOrder : public std::binary_function<const Camera*, const Camera*, std::size_t>
	{
		bool operator() (const Camera* lhs, const Camera* rhs) const
		{
			if (lhs->GetTargetWindow()==NULL&&rhs->GetTargetWindow()!=NULL)
			{
				return false;
			}
			else if(lhs->GetTargetWindow()!=NULL&&rhs->GetTargetWindow()==NULL)
			{
				return true;
			}

			if (lhs->GetTargetWindow() != rhs->GetTargetWindow())
			{
				return lhs->GetTargetWindow()->GetType() < rhs->GetTargetWindow()->GetType();
			}
			return lhs->GetCameraOrder() < rhs->GetCameraOrder();
		}
	};

	//__ImplementClass(ViewPortWindow,'VPWS',Core::RefCounted)

#if USE_RENDER_THREAD
	__ImplementClass(GraphicSystem,'GRSY',Interface::InterfaceBase)
#else
	__ImplementClass(GraphicSystem,'GRSY',Core::RefCounted);
#endif

	__ImplementImageSingleton(GraphicSystem);

	using namespace Threading;
	using namespace Interface;
	using namespace Messaging;
	using namespace FrameSync;
	using namespace RenderBase;

	static const GPtr<Camera> UnvalidCamera = NULL;
	static const GPtr<Light> UnvalidLight = NULL;
	static const GPtr<ViewPortWindow> ViewPortWindowNull = NULL;
	static const SizeT DefaultBlockSize = 1 << 23;
	static const SizeT AdditionBlockSize = 1 << 22;

	GraphicSystem::GraphicSystem()
		:m_nViewPort(0)
		,m_ViewPortDirty(false)
		,m_uiDrawCallBack(NULL)
		,m_uiBeforeDrawCallBack(NULL)
		,m_fontCallBack(NULL)
	{
		__ConstructImageSingleton;
		m_graphicDisplay = RenderDisplay::Create();
		m_RenderToTexturesManager = RenderToTextureManager::Create();
	}

	GraphicSystem::~GraphicSystem()
	{
		m_graphicDisplay = 0;
		m_RenderToTexturesManager = 0;
		m_renderingCameraStack.Clear();
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	void GraphicSystem::OpenRenderSystem(WindHandle hWnd)
	{
#if USE_RENDER_THREAD
		m_mainThreadId = Thread::GetMyThreadId();

		// setup asynchronous graphics subsystem
		//m_renderSystem = RenderSystem::RenderSystem::Create();
		m_renderThreadHandler = RenderBase::RenderSystemThreadHandler::Create();

#ifdef __WIN32__
		m_renderThreadHandler->SetMainWindowHandle((WindHandle)hWnd);
#endif //__WIN32__

		m_frameSyncHandlerThread = FrameSyncHandlerThread::Create();
		m_frameSyncHandlerThread->SetName("RenderSystem Thread");
		m_frameSyncHandlerThread->SetCoreId(System::Cpu::RenderThreadCore);
		m_frameSyncHandlerThread->AttachHandler(m_renderThreadHandler.cast<Handler>());
		SetHandlerThread(m_frameSyncHandlerThread.cast<HandlerThreadBase>());

		m_batchMessage = BatchMessage::Create();
#else
		mRenderSystem = RenderBase::RenderSystem::Create();
#ifdef __WIN32__
		mRenderSystem->SetMainWindowHandle(hWnd);
#endif

		//mRenderSystem->SetMainWindowHandle(hWnd);


		//mRenderSystem->SetOnDeviceResetFunc(OnDeviceReset);
		//mRenderSystem->SetOnDeviceLostFunc(OnDeviceLost);


#endif

	}
	//------------------------------------------------------------------------
	void GraphicSystem::Open(WindHandle hWnd, int width, int height, RenderBase::PixelFormat::Code format)
	{
		OpenRenderSystem(hWnd);

#if USE_RENDER_THREAD
		Super::Open();
#endif


		_SetupDefaultObjects();

		StartRenderSystem(width, height);

		CreateMainViewPortWindow((WindHandle)hWnd);


		m_streamBufferPool = StreamBufferPool::Create();
		m_streamBufferPool->Setup(DefaultBlockSize, AdditionBlockSize);

		m_ViewPortLists[MainViewPort]->SetDisplayMode(RenderBase::DisplayMode(0, 0, width, height, RenderBase::PixelFormat::X8R8G8B8));
	}
	//------------------------------------------------------------------------
	void GraphicSystem::StartRenderSystem(int width, int height)
	{
#if USE_RENDER_THREAD
		GPtr<StartRenderSystemMSG> srsmsg = StartRenderSystemMSG::Create();
		SendWait(srsmsg.upcast<Messaging::Message>());
#else
		mRenderSystem->Open(width, height);
#endif
	}

	void GraphicSystem::_SetupDefaultObjects()
	{
		//empty
	}

	void GraphicSystem::OnUpateFrame()
	{
		PROFILER_RESETDEVICESTATS();
		PROFILER_ADDDTICKBEGIN(drawTime);
		RenderAll();
		Material::GetGlobalMaterialParams()->ResetTextureCache();
		PROFILER_ADDDTICKEND(drawTime);
	}

	//--------------------------------------------------------------------------------
	void GraphicSystem::_BeginRender(ViewPortWindow* target)
	{
		target->GetRenderWindow()->BeginRender();
	}

	void GraphicSystem::_EndRender(ViewPortWindow* target)
	{
		target->GetRenderWindow()->EndRender();
	}

	const Camera* GraphicSystem::GetRenderingCamera()
	{
		if ( m_renderingCameraStack.Size() > 0 )
		{
			return m_renderingCameraStack.Peek();
		}
		return NULL;
	}
	void GraphicSystem::_RenderCamera(Camera* camera)
	{
		m_renderingCameraStack.Push(camera);

		bool bEvent = camera->IsUseBeforeDrawEvent();
		if (bEvent)
		{
			m_BeforeDrawEvent(camera);
		}

		camera->RenderBegin();

		RenderPipelineManager::OnRenderPipeline(camera);

		camera->RenderEnd();
		m_renderingCameraStack.Pop();
	}

	void GraphicSystem::RenderAll()
	{
		if (m_uiBeforeDrawCallBack) // [2012.3.27 zhongdaohuan]
		{
			m_uiBeforeDrawCallBack();
		}

		//m_cameraList里的camera是有序的，主窗口下的camera总是在后边。
		CameraList::Iterator it = m_cameraList.Begin();
		CameraList::Iterator end = m_cameraList.End();

		ViewPortWindow* winTarget = NULL;

		while(it != end && NULL != (*it)->GetTargetWindow() && VPT_MAIN != (*it)->GetTargetWindow()->GetType())//其他窗口渲染
		{
			if ((*it)->GetTargetWindow() != winTarget)
			{
				if (NULL != winTarget)
				{
					_EndRender(winTarget);
				}
				winTarget = (*it)->GetTargetWindow();
				_BeginRender(winTarget);
			}
			_RenderCamera((*it));
			++it;
		}
		if (NULL != winTarget)
		{
			_EndRender(winTarget);
		}

		winTarget = GetMainViewPortWindow().get();
		_BeginRender(winTarget);

		if (it != end)//主窗口渲染
		{
			n_assert(NULL == (*it)->GetTargetWindow());
			while(it != end)
			{
				_RenderCamera((*it));
				++it;
			}
		}
		else
		{
			SetRenderTarget(RenderBase::RenderTargetHandle());
		}

		if (m_uiDrawCallBack) // [2012.3.27 zhongdaohuan]
		{
			m_uiDrawCallBack();
		}

		if ( m_fontCallBack )
		{
			m_fontCallBack();
		}
		_EndRender(winTarget);

	}

	//--------------------------------------------------------------------------------
	void GraphicSystem::OnBeginFrame()
	{
		if (m_ViewPortDirty)
		{
			ViewPorts::Iterator it = m_ViewPortLists.Begin();
			ViewPorts::Iterator end = m_ViewPortLists.End();
			if ((*it)->_IsDirty())
			{
				(*it)->_OnChangeSize();
				const RenderBase::DisplayMode& mode = (*it)->GetDisplayMode();
				mRenderSystem->ChangeSize(mode.GetWidth(), mode.GetHeight());
			}
			++it;

			while(it != end)
			{
				if ((*it)->_IsDirty())
				{
					(*it)->_OnChangeSize();
				}
				++it;
			}
			m_ViewPortDirty = false;
		}
	}
	//--------------------------------------------------------------------------------
	void GraphicSystem::OnEndFrame()
	{
		//int nIdx = m_nViewPort+1;
		//m_nViewPort = nIdx%m_ViewPortLists.Size();
	}
	//------------------------------------------------------------------------
	void GraphicSystem::CloseRenderSystem()
	{
#if USE_RENDER_THREAD
		m_mainThreadId = 0;
#else
		mRenderSystem->Close();
		mRenderSystem = 0;
#endif
	}

	void GraphicSystem::Close()
	{
		//m_renderObjects.Clear();
		m_cameraList.Clear();


		m_ViewPortLists.Clear();
		m_streamBufferPool->Destory();
		m_streamBufferPool = NULL;

		Material::RemoveGlobalMaterialParams();

		CloseRenderSystem();
#if USE_RENDER_THREAD
		Super::Close();
#endif
	}
	//------------------------------------------------------------------------
	void GraphicSystem::SetViewPort(const Camera::ViewPort& vp)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetViewPortMSG> svpmsg = RenderBase::SetViewPortMSG::Create();
		svpmsg->SetX(vp.x);
		svpmsg->SetY(vp.y);
		svpmsg->SetWidth(vp.width);
		//svpmsg->SetHeight(vp.height);
		svpmsg->SetHeight(vp.height);
		svpmsg->SetMinZ(vp.minZ);
		svpmsg->SetMaxZ(vp.maxZ);
		SendWait(svpmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_SetViewPort(vp.x,vp.y,vp.width,vp.height,vp.minZ,vp.maxZ);
#endif

	}

	void GraphicSystem::SetVertexShaderConstantVectorF(const int& reg, const float4* val, const int& vec4count)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetVertexShaderConstantVectorFMSG> svscmsg = RenderBase::SetVertexShaderConstantFMSG::Create();
		svscmsg->SetReg(regIndex);
		svscmsg->SetValueRef(val);
		svscmsg->SetVec4count(vec4count);
		SendWait(svscmsg.cast<Messaging::Message>());
#else

		mRenderSystem->SetVertexShaderConstantVectorF(reg, (float*)val, vec4count);

#endif
	}

	void GraphicSystem::SetPixelShaderConstantVectorF(const int& reg, const float4* val, const int& vec4count)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetPixelShaderConstantVectorFMSG> spscmsg = RenderBase::SetPixelShaderConstantFMSG::Create();
		spscmsg->SetReg(regIndex);
		spscmsg->SetValueRef(val);
		spscmsg->SetVec4count(vec4count);
		SendWait(spscmsg.cast<Messaging::Message>());
#else

		mRenderSystem->SetPixelShaderConstantVectorF(reg, (float*)val, vec4count);
#endif
	}

	void GraphicSystem::SetVertexShaderConstantFloat(const int& reg, const float& val)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetVertexShaderConstantFloatMSG> svscmsg = RenderBase::SetVertexShaderConstantFMSG::Create();
		svscmsg->SetReg(regIndex);
		svscmsg->SetValueRef(val);
		SendWait(svscmsg.cast<Messaging::Message>());
#else
		mRenderSystem->SetVertexShaderConstantFloat(reg, (float*)&val);
#endif
	}

	void GraphicSystem::SetPixelShaderConstantFloat(const int& reg, const float& val)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetPixelShaderConstantFloatMSG> svscmsg = RenderBase::SetVertexShaderConstantFMSG::Create();
		svscmsg->SetReg(regIndex);
		svscmsg->SetValueRef(val);
		SendWait(svscmsg.cast<Messaging::Message>());
#else
		mRenderSystem->SetPixelShaderConstantFloat(reg, (float*)&val);
#endif
	}

	void GraphicSystem::SetVertexShaderConstantMatrixF(const int& reg, const matrix44* val, const int& matrixCount)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetVertexShaderConstantMatrixFMSG> svscmsg = RenderBase::SetVertexShaderConstantFMSG::Create();
		svscmsg->SetReg(regIndex);
		svscmsg->SetValueRef(val);
		svscmsg->SetmatrixCount(matrixCount);
		SendWait(svscmsg.cast<Messaging::Message>());
#else
		mRenderSystem->SetVertexShaderConstantMatrixF(reg, (float*)val, matrixCount);
#endif	
	}

	void GraphicSystem::SetPixelShaderConstantMatrixF(const int& reg, const matrix44* val, const int& matrixCount)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetPixelShaderConstantMatrixFMSG> svscmsg = RenderBase::SetVertexShaderConstantFMSG::Create();
		svscmsg->SetReg(regIndex);
		svscmsg->SetValueRef(val);
		svscmsg->SetmatrixCount(matrixCount);
		SendWait(svscmsg.cast<Messaging::Message>());
#else
		mRenderSystem->SetPixelShaderConstantMatrixF(reg, (float*)val, matrixCount);
#endif	
	}

	GPUProgramHandle GraphicSystem::CreateShaderProgram(GPtr<GPUProgram> program)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::CreateShaderProgramMSG> createShaderProgramMSG = RenderBase::CreateShaderProgramMSG::Create();
		createShaderProgramMSG->SetGPUProgram(program);
		SendWait(createShaderProgramMSG.cast<Messaging::Message>());
		n_assert(createShaderProgramMSG->Handled())
			return createShaderProgramMSG->GetHandle();
#else
		return mRenderSystem->CreateShaderProgram(program);
#endif
	}

	void GraphicSystem::SetShaderProgram(GPUProgramHandle handle)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetGPUProgramMSG> ssmsg = RenderBase::SetGPUProgramMSG::Create();
		ssmsg->SetHandle(handle);
		SendWait(ssmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_SetShaderProgram(handle);
#endif

	}

	void GraphicSystem::RemoveShaderProgram(RenderBase::GPUProgramHandle handle)
	{
		//TODO
	}

	//RenderBase::PrimitiveGroup* GraphicSystem::GetPrimitiveGroup(const RenderBase::PrimitiveHandle& handle) const
	//{
	//	return mRenderSystem->GetPrimitiveGroup(handle);
	//}

	PrimitiveHandle GraphicSystem::CreatePrimitiveHandle(const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd /* = NULL */)
	{
#if USE_RENDER_THREAD
		n_error("no suport.");
		return PrimitiveHandle();
#else
		return mRenderSystem->CreatePrimitiveHandle(vbd, ibd);
#endif
	}

	PrimitiveHandle GraphicSystem::CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
	{
		n_assert(NULL != vbd2);
		vbd2->_Bind();

		const RenderBase::VertexBufferData* vbd = &vbd2->_GetVertexBufferData();
		const RenderBase::IndexBufferData* ibd = NULL;

		if (ibd2)
		{
			ibd2->_Bind();
			ibd = &ibd2->_GetIndexBufferData();
		}

#if USE_RENDER_THREAD
		n_error("no suport.");
		return PrimitiveHandle();
#else
		PrimitiveHandle handle = mRenderSystem->CreatePrimitiveHandle(vbd, ibd);
		//[zhongdaohuan]
		//在设计中，VertexBufferData2 （或IndexBufferData2或DynamicBuffer）同时只能有一个对象处于激活状态，
		//必须立即声明，立即使用。否则不保证正确性。所谓使用就是调用
		//CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
		//或UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
		//所以下面的逻辑没有问题。
		MemoryPool* pool = vbd2->_getBlock()._getPool();
		if (pool)
		{
			pool->Clear();
			vbd2->_reset();
		}
		if (ibd2)
		{
			pool = ibd2->_getBlock()._getPool();
			if (pool)
			{
				pool->Clear();
				ibd2->_reset();
			}
		}
		return handle;
#endif
	}
	void GraphicSystem::ChangePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd /* = NULL */)
	{
#if USE_RENDER_THREAD
		n_error("no suport.");
		return PrimitiveHandle();
#else
		return mRenderSystem->ChangePrimitiveHandle(handle, vbd, ibd);
#endif
	}

	void GraphicSystem::ChangePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
	{
		n_assert(NULL != vbd2);
		vbd2->_Bind();

		const RenderBase::VertexBufferData* vbd = &vbd2->_GetVertexBufferData();
		const RenderBase::IndexBufferData* ibd = NULL;

		if (ibd2)
		{
			ibd2->_Bind();
			ibd = &ibd2->_GetIndexBufferData();
		}

#if USE_RENDER_THREAD
		n_error("no suport.");
		return PrimitiveHandle();
#else
		mRenderSystem->ChangePrimitiveHandle(handle, vbd, ibd);
		//[zhongdaohuan]
		//在设计中，VertexBufferData2 （或IndexBufferData2或DynamicBuffer）同时只能有一个对象处于激活状态，
		//必须立即声明，立即使用。否则不保证正确性。所谓使用就是调用
		//CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
		//或UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
		//所以下面的逻辑没有问题。
		MemoryPool* pool = vbd2->_getBlock()._getPool();
		if (pool)
		{
			pool->Clear();
			vbd2->_reset();
		}
		if (ibd2)
		{
			pool = ibd2->_getBlock()._getPool();
			if (pool)
			{
				pool->Clear();
				ibd2->_reset();
			}
		}
#endif
	}

	void GraphicSystem::UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
	{
#if USE_RENDER_THREAD
		n_error("[zhongdaohuan]");
		return PrimitiveHandle();
#else
		n_assert(vertices);
		RenderBase::DataStream ds;
		ds.data = vertices->GetPtr();
		ds.sizeInByte = vertices->_getBlock().size();
		mRenderSystem->UpdateVertexBuffer(handle, ds);
		if (indices)
		{
			RenderBase::DataStream ds2;
			ds2.data = indices->GetPtr();
			ds2.sizeInByte = indices->_getBlock().size();
			mRenderSystem->UpdateIndexBuffer(handle, ds2);
		}
		//[zhongdaohuan]
		//在设计中，VertexBufferData2 （或IndexBufferData2或DynamicBuffer）同时只能有一个对象处于激活状态，
		//必须立即声明，立即使用。否则不保证正确性。所谓使用就是调用
		//CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
		//或UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
		//所以下面的逻辑没有问题。
		MemoryPool* pool = vertices->_getBlock()._getPool();
		pool->Clear();
		vertices->_reset();

		if (indices)
		{
			pool = indices->_getBlock()._getPool();
			pool->Clear();
			indices->_reset();
		}
#endif
	}

	void GraphicSystem::GetVertexComponents(const RenderBase::PrimitiveHandle& handle, RenderBase::VertexComponents& vcs)
	{
		PrimitiveGroup* pg = mRenderSystem->GetPrimitiveGroup(handle);
		vcs = pg->GetVertexBuffer()->GetVertexLayout()->GetVertexComponents();
	}

	void GraphicSystem::GetVertexDesc(const RenderBase::PrimitiveHandle& handle, RenderBase::VERTEX_DESC& desc)
	{
		PrimitiveGroup* pg = mRenderSystem->GetPrimitiveGroup(handle);
		desc.topology = pg->GetPrimitiveTopology();
		desc.usage = pg->GetVertexBuffer()->GetUsage();
		desc.vertexCount = pg->GetVertexBuffer()->GetNumVertices();
		desc.vertexSizeInbyte = pg->GetVertexBuffer()->GetVertexDataSize() / desc.vertexCount;
	}

	void GraphicSystem::GetIndexDesc(const RenderBase::PrimitiveHandle& handle, RenderBase::INDEX_DESC& desc)
	{
		PrimitiveGroup* pg = mRenderSystem->GetPrimitiveGroup(handle);
		desc.usage = pg->GetVertexBuffer()->GetUsage();
		desc.indexCount = pg->GetIndexBuffer()->GetNumIndices();
		desc.indexType = pg->GetIndexBuffer()->GetIndexType();
	}

	void GraphicSystem::GetTextureDesc(const RenderBase::TextureHandle& handle, RenderBase::TEXTURE_DESC& desc)
	{
		Texture* texture = mRenderSystem->GetTexture(handle);
		desc.width = texture->GetWidth();
		desc.height = texture->GetHeight();
		desc.depth = texture->GetDepth();
		desc.numMipLevels = texture->GetNumMipLevels();
		desc.pixelFormat = texture->GetPixelFormat();
	}

	void GraphicSystem::DrawPrimitive(RenderBase::PrimitiveHandle handle,SizeT startVertice,SizeT numVertice,SizeT startIndice,SizeT numIndice)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::DrawMSG> drawmsg = RenderBase::DrawMSG::Create();
		drawmsg->SetHandle(handle);
		drawmsg->SetStartVertice(startVertice);
		drawmsg->SetEndVertice(numVertice);
		drawmsg->SetStartIndice(startIndice);
		drawmsg->SetEndIndice(numIndice);
		SendWait(drawmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_DrawPrimitive(handle,
			startVertice,
			numVertice,
			startIndice,
			numIndice);
#endif

	}

	void GraphicSystem::DrawPrimitive(RenderBase::PrimitiveHandle handle)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::DrawMSG> drawmsg = RenderBase::DrawMSG::Create();
		drawmsg->SetHandle(handle);
		drawmsg->SetStartVertice(-1);
		drawmsg->SetEndVertice(-1);
		drawmsg->SetStartIndice(-1);
		drawmsg->SetEndIndice(-1);
		SendWait(drawmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_DrawPrimitive(handle);
#endif

	}
	void GraphicSystem::RemovePrimitive(const RenderBase::PrimitiveHandle &handle)
	{
		_RemoveRenderResource(handle);
	}

	void GraphicSystem::SetRenderState( GPtr<RenderStateDesc> rsObject)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetRenderStateMSG> srsmsg = RenderBase::SetRenderStateMSG::Create();
		srsmsg->SetObject(rsObject);
		SendWait(srsmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_SetRenderState(rsObject);
#endif

	}

	RenderTargetHandle GraphicSystem::CreateRenderTarget( GPtr<RenderTarget> rt, TextureHandle& texhandle )
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::CreateRenderTargetMSG> createRTMSG = RenderBase::CreateRenderTargetMSG::Create();
		createRTMSG->SetRenderTarget(rt);
		SendWait(createRTMSG.cast<Messaging::Message>());
		n_assert(createRTMSG->Handled())
			texhandle = createRTMSG->GetTextureHandle();
		return createRTMSG->GetHandle();
#else
		return mRenderSystem->CreateRenderTarget(rt,texhandle);
#endif

	}

	MultipleRenderTargetHandle GraphicSystem::CreateMultipleRenderTarget(GPtr<RenderBase::MultipleRenderTarget> mrt, Util::Array< RenderBase::RenderTargetHandle >& handles)
	{
		return mRenderSystem->CreateMultipleRenderTarget(mrt, handles);	
	}

	void GraphicSystem::SetMultipleRenderTarget(GPtr<MultipleRenderToTexture> mrt, bool resume)
	{
		n_assert(mrt.isvalid());
		SetMultipleRenderTarget(mrt->GetMultipleTargetHandle(), resume);
	}

	void GraphicSystem::SetMultipleRenderTarget(RenderBase::MultipleRenderTargetHandle handle, bool resume)
	{
		mRenderSystem->_SetMultipleRenderTarget(handle, resume);
	}

	void GraphicSystem::ReSizeMultipleRenderTarget(RenderBase::MultipleRenderTargetHandle handle, int width, int height)
	{
		mRenderSystem->_ReSizeMultipleRenderTarget(handle,width,height);
	}

	void GraphicSystem::ReSizeMultipleRenderTarget(GPtr<MultipleRenderToTexture> mrt, int width, int height)
	{
		n_assert(mrt.isvalid());
		ReSizeMultipleRenderTarget(mrt->GetMultipleTargetHandle(),width,height);
	}

	void GraphicSystem::SetRenderTarget(RenderBase::RenderTargetHandle handle,SizeT index,uint clearflag)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetRenderTargetMSG> srtmsg = RenderBase::SetRenderTargetMSG::Create();
		srtmsg->SetHandle(handle);
		srtmsg->SetIndex(index);
		srtmsg->SetClearFlag(clearflag);
		SendWait(srtmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_SetRenderTarget(handle,index,clearflag);
#endif

	}

	void GraphicSystem::SetRenderTarget(const GPtr<RenderToTexture>& rt,SizeT index,uint clearflag)
	{
		n_assert(rt.isvalid())
			SetRenderTarget(rt->GetTargetHandle(),index,clearflag);
	}

	void GraphicSystem::SetRenderTargetClearColor(const GPtr<RenderToTexture>& rt,const Math::float4& clearColor)
	{
#if USE_RENDER_THREAD
		n_error(" GraphicSystem::SetRenderTargetClearColor(const GPtr<RenderToTexture>& rt,Math::float4& clearColor) has not implemented now!");
#endif
		n_assert(rt.isvalid())
			mRenderSystem->_SetRenderTargetClearColor(rt->GetTargetHandle(), clearColor);
	}

	void GraphicSystem::ReSizeRenderTarget(RenderBase::RenderTargetHandle handle, int width, int height)
	{
#if USE_RENDER_THREAD
		n_error(" GraphicSystem::ReSizeRenderTarget(RenderBase::RenderTargetHandle handle, int width, int height) has not implemented now!");
#endif
		mRenderSystem->_ReSizeRenderTarget(handle,width,height);
	}

	void GraphicSystem::ReSizeRenderTarget(GPtr<RenderToTexture> rt, int width, int height)
	{
		n_assert(rt.isvalid())
			ReSizeRenderTarget(rt->GetTargetHandle(),width,height);
	}

	void GraphicSystem::RemoveRenderTarget(const RenderBase::RenderTargetHandle& handle)
	{
		_RemoveRenderResource(handle);
	}

	void GraphicSystem::RemoveMultipleRenderTarget(const RenderBase::MultipleRenderTargetHandle& handle)
	{
		_RemoveRenderResource(handle);
	}

	void GraphicSystem::CopyRenderTarget(RenderBase::RenderTargetHandle srcHandle, const float4& srcRect,RenderBase::RenderTargetHandle desHandle, const float4& desRect)
	{
		mRenderSystem->CopyRenderTarget(srcHandle,srcRect,desHandle,desRect);
	}

	TextureHandle GraphicSystem::CreateTexture( GPtr<Texture> tex)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::CreateTextureMSG> ctmsg = RenderBase::CreateTextureMSG::Create();
		ctmsg->SetTexture(tex);
		SendWait(ctmsg.cast<Messaging::Message>());
		n_assert(ctmsg->Handled())
			return ctmsg->GetHandle();
#else
		return mRenderSystem->CreateTexture(tex);
#endif

	}

	void GraphicSystem::SetTexture(SizeT index,TextureHandle handle)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::SetTextureMSG> stmsg = RenderBase::SetTextureMSG::Create();
		stmsg->SetTexUnit(index);
		stmsg->SetHandle(handle);
		SendWait(stmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_SetTexture(handle,index);
#endif

	}

	void GraphicSystem::SetTexture(SizeT index,const GPtr<RenderToTexture>& rtt)
	{
		n_assert(rtt.isvalid())
			SetTexture(index,rtt->GetTextureHandle());
	}

	void GraphicSystem::UpdateTexture(RenderBase::TextureHandle texHandle, RenderBase::Texture::UpdateFunction texUpdateFunc, void* tag)
	{
#if USE_RENDER_THREAD
		//TODO: Add Update texture message
#else
		mRenderSystem->UpdateTexture(texHandle,texUpdateFunc, tag);
#endif

	}

	void GraphicSystem::UpdateTexture(RenderBase::TextureHandle texHandle, GPtr<RenderBase::Texture> texture)
	{
#if USE_RENDER_THREAD
		//TODO: Add Update texture message
#else
		mRenderSystem->UpdateTexture( texHandle, texture );
#endif

	}

	void GraphicSystem::ChangeTexture(RenderBase::TextureHandle texHandle, GPtr<Texture> texture)
	{
#if USE_RENDER_THREAD
		//TODO: Add Update texture message
#else
		mRenderSystem->ChangeTexture( texHandle, texture );
#endif
	}

	void GraphicSystem::RemoveTexture(const RenderBase::TextureHandle& handle)
	{
		_RemoveRenderResource(handle);
	}

	Camera* GraphicSystem::GetCameraByType(CameraOrder co) const
	{
		for (CameraList::Iterator it = m_cameraList.Begin(); it != m_cameraList.End(); ++it)
		{
			if ((*it)->GetCameraOrder() == co)
			{
				return (*it);
			}
		}
		return NULL;
	}


	void GraphicSystem::AddCamera(Camera* camera)
	{
		n_assert(camera);
		n_assert(camera->GetCameraOrder() != eCO_InvalidCamera);

		m_cameraList.Append(camera);
		Util::CustomSortArray<Camera*, CompareRenderOrder>(m_cameraList);
	}

	void GraphicSystem::RemoveCamera(const Camera* camera)
	{
		for (int i = 0; i < m_cameraList.Size(); ++i)
		{
			if (camera == m_cameraList[i])
			{
				m_cameraList.EraseIndex(i);
			}
		}

	}
	//------------------------------------------------------------------------
	void 
		GraphicSystem::_RemoveRenderResource(const RenderBase::RenderResourceHandle &handle)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::RemoveRenderResourceMSG> rmvmsg = RenderBase::RemoveRenderResourceMSG::Create();
		rmvmsg->SetHandle(handle);
		SendWait(rmvmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_RemoveResouce(handle);
#endif

	}

	//////////////////////////////////////////////////////////////////////////
	//Fixed Pipeline Functions
	void GraphicSystem::SetClipPlane(SizeT index, const Math::float4& cplane)
	{
#if USE_RENDER_THREAD
		GPtr<RenderBase::FXSetClipPlaneMSG> fxscpmsg = RenderBase::FXSetClipPlaneMSG::Create();
		fxscpmsg->SetIndex(index);
		fxscpmsg->SetPlane(cplane);
		SendWait(fxscpmsg.cast<Messaging::Message>());
#else
		mRenderSystem->_FXSetClipPlane(index,cplane);
#endif

	}

#if USE_RENDER_THREAD
	//------------------------------------------------------------------------------
	/**
	*/
	void
		GraphicSystem::EnterLockStepMode()
	{
		n_assert(Thread::GetMyThreadId() == m_mainThreadId);
		m_frameSyncHandlerThread->EnterLockStepMode();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		GraphicSystem::LeaveLockStepMode()
	{
		n_assert(Thread::GetMyThreadId() == m_mainThreadId);
		m_frameSyncHandlerThread->LeaveLockStepMode();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		GraphicSystem::GameThreadWaitForFrameSync()
	{
		n_assert(Thread::GetMyThreadId() == m_mainThreadId);
		m_frameSyncHandlerThread->ArriveAtSyncPoint(false);
	}
	//------------------------------------------------------------------------
	void GraphicSystem::AddBatchMessage(const GPtr<Message>& msg)
	{
#if NEBULA3_DEBUG
		n_assert(Thread::GetMyThreadId() == m_mainThreadId);
#endif
		m_batchMessage->AddMessage(msg);

	}
#endif
	//--------------------------------------------------------------------------------
	GPtr<ViewPortWindow> GraphicSystem::CreateMainViewPortWindow(WindHandle hWnd)
	{
		n_assert(m_ViewPortLists.Size() == 0);

		GPtr<ViewPortWindow> pVPWnd = ViewPortWindow::Create();
		pVPWnd->SetDeviceWindow(mRenderSystem->CreateViewPortWnd( hWnd ));	
		pVPWnd->_SetType(VPT_MAIN);
		m_ViewPortLists.Append( pVPWnd );
		return m_ViewPortLists.Back();
	}

	GPtr<ViewPortWindow> GraphicSystem::CreateAssistantViewPortWindow(WindHandle hWnd)
	{
		n_assert(m_ViewPortLists.Size() != 0);

		GPtr<ViewPortWindow> pVPWnd = ViewPortWindow::Create();
		pVPWnd->SetDeviceWindow(mRenderSystem->CreateViewPortWnd( hWnd ));	
		pVPWnd->_SetType(VPT_CustomBegin);
		m_ViewPortLists.Append( pVPWnd );
		return m_ViewPortLists.Back();

	}
	void GraphicSystem::DestroyViewPortWindow(GPtr<ViewPortWindow>& view)
	{
		IndexT index = m_ViewPortLists.FindIndex(view);
		n_assert(InvalidIndex != index);
		mRenderSystem->DestroyViewPortWnd(view->GetRenderWindow());
		view->SetDeviceWindow(NULL);
		m_ViewPortLists.EraseIndex(index);
	}
	//--------------------------------------------------------------------------------
	const GPtr<ViewPortWindow>& GraphicSystem::FindViewPortWindow( WindHandle hWnd ) const
	{
		for (IndexT nIdx = 0; nIdx < m_ViewPortLists.Size(); ++nIdx)
		{
			if ( m_ViewPortLists[nIdx]->GetRenderWindow() &&
				m_ViewPortLists[nIdx]->GetRenderWindow()->GetHandle() == hWnd )
			{
				return m_ViewPortLists[nIdx];
			}
		}
		return ViewPortWindowNull;
	}
	const GPtr<ViewPortWindow>& GraphicSystem::GetMainViewPortWindow() const
	{
		return m_ViewPortLists[MainViewPort];
	}

	MemoryBlock GraphicSystem::_GetBlock(SizeT sizeInByte)
	{
		return m_streamBufferPool->GetBlock(sizeInByte);
	}


	void GraphicSystem::OnDeviceLost()
	{
		mRenderSystem->OnDeviceLost();
		_OnDeviceLost();
	}
	bool GraphicSystem::CheckReset()
	{
		return mRenderSystem->CheckReset();
	}

	void GraphicSystem::OnDeviceReset()
	{
		mRenderSystem->OnDeviceReset();
		_OnDeviceReset();
	}

	void GraphicSystem::_OnDeviceLost()
	{

	}

	void GraphicSystem::_OnDeviceReset()
	{
#if RENDERDEVICE_D3D9

		CameraList::Iterator end = m_cameraList.End();
		for( CameraList::Iterator iter = m_cameraList.Begin(); iter != end; ++iter )
		{	
			ViewPortWindow* win = (NULL == (*iter)->GetTargetWindow())? m_ViewPortLists[MainViewPort] : (*iter)->GetTargetWindow();
			if (eCO_Main == (*iter)->GetCameraOrder())
			{
				(*iter)->OnDeviceReset(win->GetDisplayMode());
			}

		}
#elif RENDERDEVICE_OPENGLES
		Resources::ResourceManager::Instance()->ReloadAllVideoMemResource();
		ResetAllQuadRenderable();
#endif

	}


	void GraphicSystem::ResetAllQuadRenderable() const
	{
		SizeT nCount = m_AllQuadRenderable.Size();

		for (IndexT i = 0; i < nCount; ++i)
		{
			QuadRenderable* pQuad = m_AllQuadRenderable[i];
			SizeT width  = pQuad->GetWidth();
			SizeT height = pQuad->GetHeight();
			m_AllQuadRenderable[i]->Setup(width, height);
		}
	}

}
