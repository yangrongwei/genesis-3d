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
#include "RenderDeviceGLES.h"
#include "RenderSystem.h"

#include "PrimitiveGroupObjectGLES.h"
#include "GPUProgramGLES.h"
#include "TextureGLES.h"
#include "GLESTypes.h"
#include "RenderTargetGLES.h"

#define USE_NATIVE_WINDOW 1

namespace GLES
{
	using namespace RenderBase;

	__ImplementClass(GLES::RenderDeviceGLES,'GRDE',RenderBase::RenderDevice);

RenderDeviceGLES::RenderDeviceGLES()
: m_glesImpl(NULL)
{
#if USE_NATIVE_WINDOW && __WIN32__

	m_activeContext = GLESContext::Create();
	n_assert(m_activeContext);
#endif


	for (IndexT i = 0; i < GLES::MaxTextureUnits; ++i)
	{
		m_Textures.Add(i, NULL);
	}
#if __OSX__
    m_mainFBOnum = 1;
#else
    m_mainFBOnum = 0;
#endif
}

RenderDeviceGLES::~RenderDeviceGLES()
{
	m_Textures.Clear();

	if (m_glesImpl != NULL)
	{
		n_delete(m_glesImpl);
	}

	if (m_activeContext.isvalid())
	{
		m_activeContext = NULL;
	}
}

bool RenderDeviceGLES::InitDevice()
{
#if USE_NATIVE_WINDOW && __WIN32__
	if (m_activeContext.isvalid())
	{
		SizeT inMulsample  = 0;
		m_activeContext->InitContext(inMulsample);
	} 
	else
	{
		return false;
	}
#endif
	m_glesImpl = GLESImpl::Create();

	if (m_glesImpl != NULL)
	{
		m_glesImpl->Init();
	} 
	else
	{
		return false;
	}

	for (int i = 0; i< GLES::MaxTextureUnits; ++i)
	{
		m_texturesTypes[i] = 0;
	}

	return true;
}
//------------------------------------------------------------------------
void RenderDeviceGLES::DetectGraphicCardCaps()
{
#if RENDERDEVICE_OPENGLES
	m_graphicCardCaps.DetectGraphicCardCapsGLES20();
#endif
}
//------------------------------------------------------------------------
const GraphicCardCapability& 
RenderDeviceGLES::GetGraphicCardCapability()
{
	return m_graphicCardCaps;
}
//------------------------------------------------------------------------
float RenderDeviceGLES::GetHorizontalTexelOffset(void)
{
	// No offset in GL
	return 0.0f;
}

float RenderDeviceGLES::GetVerticalTexelOffset(void)
{
	// No offset in GL
	return 0.0f;
}

float RenderDeviceGLES::GetMinimumDepthInputValue()
{
	// Range [-1.0f, 1.0f]
	return -1.0f;
}

float RenderDeviceGLES::GetMaximumDepthInputValue()
{
	// Range [-1.0f, 1.0f]
	return 1.0f;
}

GPtr<PrimitiveGroup> RenderDeviceGLES::CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd)
{
	n_assert(NULL != vbd);
	GPtr<PrimitiveGroupObjectGLES> prim = PrimitiveGroupObjectGLES::Create();
	prim->LoadBuffers(vbd, ibd);
	return prim.upcast<PrimitiveGroup>();
}

void RenderDeviceGLES::UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data)
{
	n_assert(vb);
	VertexBufferObjectGLES* vbgl = _Convert<VertexBuffer, VertexBufferObjectGLES>(vb);
	vbgl->UpdateData(data);
}

void RenderDeviceGLES::UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data)
{
	n_assert(ib);
	IndexBufferObjectGLES* ibgl = _Convert<IndexBuffer, IndexBufferObjectGLES>(ib);
	ibgl->UpdateData(data);
}
const GPtr<GPUProgram> RenderDeviceGLES::CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram)
{
	GPtr<GPUProgramGLES> pGPUProgramGLES = GPUProgramGLES::Create();
	pGPUProgramGLES->SetCodePath(srcGPUProgram->GetCodePath());
	pGPUProgramGLES->SetVertexCode(srcGPUProgram->GetVertexCode());
	pGPUProgramGLES->SetPixelCode(srcGPUProgram->GetPixelCode());

	pGPUProgramGLES->LoadBuffers();

	m_pGPUProgramGLES = pGPUProgramGLES;
	return pGPUProgramGLES.upcast<GPUProgram>();

}

const GPtr<RenderStateDesc> RenderDeviceGLES::CreateRenderState(const GPtr<RenderStateDesc>& state)
{
	GPtr<RenderStateDesc> rsObject = RenderStateDesc::Create();
	rsObject->Setup();
	rsObject->SetBlendState(state->GetBlendState());
	rsObject->SetSamplerState(state->GetSamplerState());
	rsObject->SetDepthAndStencilState(state->GetDepthAndStencilState());
	rsObject->SetRasterizerState(state->GetRasterizerState());
	rsObject->SetUpdateFlag(state->GetUpdateFlag());
	return rsObject;
}

void RenderDeviceGLES::ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd /* = NULL */)
{
	PrimitiveGroupObjectGLES* pggl = static_cast<PrimitiveGroupObjectGLES*>(group);
	if (vbd)
	{
		pggl->DiscardVertexBuffer();
	}
	if (ibd)
	{
		pggl->DiscardIndexBuffer();
	}
	pggl->LoadBuffers(vbd, ibd);
}
const GPtr<Texture> RenderDeviceGLES::CreateRenderSideTexture( GPtr<Texture> tex)
{
	GPtr<TextureGLES> texture = TextureGLES::Create();
	texture->Setup(tex);
	texture->LoadBuffers();
	texture->SetStream(NULL);
	return texture.upcast<Texture>();
}

void RenderDeviceGLES::SetBlendState(const DeviceBlendState& state)
{

	int i = 0;

	m_glesImpl->SetColorMask( state.m_colorWriteMask[i] );

	const GraphicCardCapability& caps = GetGraphicCardCapability();

#if RENDERDEVICE_OPENGLES
	if (caps.mSeparateAplhaBlend)
	{
		if( state.m_alphaBlendEnable[i] )
		{
			m_glesImpl->ActiveAlphaBlend(true);

			m_glesImpl->SetBlendFuncSeparate( GLESTypes::AsGLESBlendFactor( state.m_srcBlend[i] ), GLESTypes::AsGLESBlendFactor( state.m_destBlend[i] ),
				GLESTypes::AsGLESBlendFactor( state.m_srcBlendAlpha[i] ), GLESTypes::AsGLESBlendFactor( state.m_destBlendAlpha[i] ) );

			m_glesImpl->SetBlendEquationSeparate( GLESTypes::AsGLESBlendOperation( state.m_blendOP[i] ) ,
				GLESTypes::AsGLESBlendOperation( state.m_blendOPAlpha[i] ) );
		}
		else
		{
			m_glesImpl->ActiveAlphaBlend(false);
		}
	} 
	else
	{
		if(true == state.m_alphaBlendEnable[i])
		{
			m_glesImpl->ActiveAlphaBlend(true);
			m_glesImpl->SetBlendFunc(GLESTypes::AsGLESBlendFactor( state.m_srcBlend[i] ), GLESTypes::AsGLESBlendFactor( state.m_destBlend[i] ));
			m_glesImpl->SetBlendEquation( GLESTypes::AsGLESBlendOperation( state.m_blendOP[i] ) );
		}
		else
		{
			m_glesImpl->ActiveAlphaBlend(false);
		}
	}
#endif

}

void RenderDeviceGLES::SetRasterState(const DeviceRasterizerState& state)
{

	m_glesImpl->SetCullMode( state.m_cullMode );
	m_glesImpl->SetPolyOffset(state.m_slopScaleDepthBias, state.m_depthBias );
	m_glesImpl->ActiveScissorTest( state.m_scissorTestEnable  );
}

void RenderDeviceGLES::SetDepthAndStencilState(const DeviceDepthAndStencilState& state)
{

	//depth
	if (state.m_depthEnable)
	{
		m_glesImpl->ActiveDepthTest(true);
		m_glesImpl->SetDepthFunc( GLESTypes::AsGLESCompareFunction(state.m_zFunc) );
	}
	else
	{
		m_glesImpl->ActiveDepthTest(false);
	}
	m_glesImpl->SetDepthWrite( state.m_depthWriteMask );

#if RENDERDEVICE_OPENGLES
	const GraphicCardCapability& caps = GetGraphicCardCapability();
	bool stencilSeparate = caps.mStencilTwoSize && state.m_stencilTwoEnable;

	if ( state.m_stencilEnable )
	{
		m_glesImpl->ActiveStencilTest(true);
		if ( stencilSeparate )
		{
			m_glesImpl->SetStencilFuncSeparate( GLESTypes::AsGLESCompareFunction( state.m_stencilFunc), 
				state.m_stencilRef, state.m_stencilReadMask,
				GLESTypes::AsGLESCompareFunction( state.m_StencilTwoFunc),
				state.m_stencilRef, state.m_stencilTwoReadMask  );

			m_glesImpl->SetStencilOpSeparate( GLESTypes::AsGLESStencilOperation(state.m_stencilFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilZFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilPass), 
				GLESTypes::AsGLESStencilOperation(state.m_stencilTwoFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilTwoZFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilTwoPass) );
		}
		else
		{
			m_glesImpl->SetStencilFunc( GLESTypes::AsGLESCompareFunction( state.m_stencilFunc), 
				state.m_stencilRef, state.m_stencilReadMask );

			m_glesImpl->SetStencilOp( GLESTypes::AsGLESStencilOperation(state.m_stencilFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilZFail),
				GLESTypes::AsGLESStencilOperation(state.m_stencilPass) );
		}
	}
	else
	{
		m_glesImpl->ActiveStencilTest(false);
	}

	if (  caps.mStencilTwoSize )
	{
		m_glesImpl->SetStencilMaskSeparate(  state.m_stencilWriteMask,  state.m_stencilTwoWriteMask);
	}
	else
	{
		m_glesImpl->SetStencilMask(  state.m_stencilWriteMask );
	}
#endif
}

void RenderDeviceGLES::SetTextureSamplerState(const DeviceSamplerState& state)
{

	for (SizeT i = 0; i < 8; ++i)
	{
		if (state.m_textureIndexEnable[i])
		{
			m_glesImpl->ActiveTextureUnit(i);

			const Util::String& type = state.m_textureType[i];

			GLenum textueType = GLESTypes::AsGLESTextureType(type);


			IndexT addresU, addresV, texOp;
			bool bMipMap = false;
			if (m_Textures[i])
			{
				addresU = m_Textures[i]->GetTexAddresingModeU();
				addresV = m_Textures[i]->GetTexAddresingModeV();
				texOp   = m_Textures[i]->GetTexFilterOp();

				if (addresU != state.m_addressU[i])
				{
					m_glesImpl->SetTextureWrapMode(textueType, GL_TEXTURE_WRAP_S, state.m_addressU[i]);
					m_Textures[i]->SetTexAddresingModeU((IndexT)(state.m_addressU[i]));
				}

				if (addresV != state.m_addressV[i])
				{
					m_glesImpl->SetTextureWrapMode(textueType, GL_TEXTURE_WRAP_T, state.m_addressV[i]);
					m_Textures[i]->SetTexAddresingModeV((IndexT)(state.m_addressV[i]));
				}

				bMipMap = m_Textures[i]->IsUseMipMap();
				if (texOp != state.m_Filter[i])
				{
					m_glesImpl->SetTextureFilter(textueType, state.m_Filter[i], bMipMap);
					m_Textures[i]->SetTexFilterOp((IndexT)(state.m_Filter[i]));
				}
			}

		
			m_glesImpl->CheckError();

		}
	}

	m_glesImpl->ActiveTextureUnit(0);
}

void RenderDeviceGLES::SetVertexLayout(const VertexLayout* vl)
{

}

void RenderDeviceGLES::SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex)
{

}

void RenderDeviceGLES::SetIndexBuffer(const IndexBuffer* ib)
{
	n_assert (ib)
	
	const IndexBufferObjectGLES* pIB = _Convert<IndexBuffer, IndexBufferObjectGLES>(ib);
	GLuint bufferID = pIB->GetGLESIndexBuffer();
	m_glesImpl->ActiveIndexBufferObject(bufferID);
}

void RenderDeviceGLES::SetPrimitiveGroup(const PrimitiveGroup* pg)
{
	m_primitiveGroupGLES = _Convert<PrimitiveGroup, PrimitiveGroupObjectGLES>(pg);

	const GPtr<VertexBuffer>& pVB = m_primitiveGroupGLES->GetVertexBuffer();
	const GPtr<IndexBuffer>&  pIB = m_primitiveGroupGLES->GetIndexBuffer();

	const GPtr<VertexBufferObjectGLES>& pVBGLES = pVB.downcast<VertexBufferObjectGLES>();

	if (pVBGLES.isvalid())
	{
		pVBGLES->BindingVertexLayout(m_pGPUProgramGLES);

		if (pIB.isvalid())
		{
			SetIndexBuffer(pIB);
		}
	}
	
}

void RenderDeviceGLES::SetTexture(const Texture* tex)
{
	n_assert(tex)
	
	const TextureGLES* texture = _Convert<Texture, TextureGLES>(tex);

	int texUnit = texture->GetUnitIndex();
	if (texUnit < GLES::MaxTextureUnits)
	{

		GLenum lastTextureType = m_texturesTypes[texUnit];

		m_glesImpl->ActiveTextureUnit(texUnit);

		Texture::Type texType = tex->GetType();
		GLenum target = GLESTypes::AsGLESTextureType(texType);

		GLuint texGLES = texture->GetGLESTexture();

		m_glesImpl->ActiveTextureObject(target, texGLES);

		const IndexT texLoc = m_pGPUProgramGLES->GetTextureUniformLocation(texUnit);
		glUniform1i(texLoc, texUnit);

		m_glesImpl->CheckError();
		m_glesImpl->ActiveTextureUnit(0);

		m_Textures[texUnit] = const_cast<TextureGLES*>(texture);
	}
		

	
}

void RenderDeviceGLES::ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
{
	GPtr<TextureGLES> destTexGL = destTex.downcast<TextureGLES>();
	n_assert(destTexGL.isvalid());
	destTexGL->Unload();
	destTexGL->Setup(srcTex);
	destTexGL->LoadBuffers();
	destTexGL->SetStream(NULL);
}

void RenderDeviceGLES::UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc, GPtr<Texture> destTex, void* tag)
{
	const GPtr<TextureGLES>& destTexGles = destTex.downcast<TextureGLES>();
	n_assert(destTexGles.isvalid());
	destTexGles->UpdateTexture(texUpdateFunc, tag);
}

void RenderDeviceGLES::UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
{
	const GPtr<TextureGLES>& destTexGles = destTex.downcast<TextureGLES>();
	n_assert(destTexGles.isvalid())

    //GLES目前这里只处理设备丢失后重新创建纹理的情况
	destTexGles->SetStream( srcTex->GetStream() );
	destTexGles->LoadBuffers();
	destTexGles->SetStream( NULL );
}

void RenderDeviceGLES::SetViewPort(const int &x, const int &y, const int &width, const int &height, const float &minZ, const float &maxZ)
{
	glViewport(x, y, width, height);
	m_glesImpl->CheckError();
}

void RenderDeviceGLES::SetGPUProgram(const GPUProgram* program)
{
	n_assert(program);

	const GPUProgramGLES* pFragmentGLES = _Convert<GPUProgram, GPUProgramGLES>(program);

	if (m_pGPUProgramGLES != pFragmentGLES)
	{
		if (m_pGPUProgramGLES)
		{
			m_pGPUProgramGLES->UnbindProgram();
		}

		m_pGPUProgramGLES = pFragmentGLES;
	}
	m_pGPUProgramGLES->BindProgram();	
}

void RenderDeviceGLES::Draw(SizeT startVertice,SizeT numVertice,SizeT startIndice,SizeT numIndice)
{
#if RENDERDEVICE_OPENGLES
	GLenum glPrimType = GLESTypes::AsGLESPrimitiveType(m_primitiveGroupGLES->GetPrimitiveTopology());
	n_assert(m_primitiveGroupGLES->GetNumVertices() >= numVertice && m_primitiveGroupGLES->GetNumVertices() >= startVertice)
	n_assert(m_primitiveGroupGLES->GetNumIndices() >= numIndice && m_primitiveGroupGLES->GetNumIndices() >= startIndice)

	SizeT numTris = 0;

	if (m_primitiveGroupGLES->GetNumIndices() > 0)
	{
		numTris = m_primitiveGroupGLES->NumberOfPrimitives( m_primitiveGroupGLES->GetPrimitiveTopology(), numIndice );

		const GPtr<IndexBuffer>& pIB = m_primitiveGroupGLES->GetIndexBuffer();

		IndexBufferData::IndexType indexType = pIB->GetIndexType();

		const RenderBase::GraphicCardCapability& caps = RenderBase::RenderSystem::Instance()->GetGraphicCardCapability();
		if (indexType == IndexBufferData::Int32 && !caps.mIndexUint)
		{
			n_warning("The Device Can Not Support GL_UNSIGNED_INT Index Type! \n");
			return;
		}

		GLenum indexTypeGLES = GLESTypes::IndexTypeAsGLESFormat( indexType );
		SizeT  indexSize     = IndexBufferData::SizeOf(indexType);

		glDrawElements(glPrimType,
			numIndice,
			indexTypeGLES,
			(char *)NULL + startIndice * indexSize
			);
		m_glesImpl->CheckError();
	} 
	else
	{
		glDrawArrays(glPrimType, startVertice, numVertice);
		m_glesImpl->CheckError();
	}

	const GPtr<VertexBuffer>& pVB = m_primitiveGroupGLES->GetVertexBuffer();


	const Util::Dictionary<Util::String, Attribute>& attributes = m_pGPUProgramGLES->GetActiveAttributes();

	for (IndexT i = 0; i < attributes.Size(); ++i)
	{
		glDisableVertexAttribArray(attributes.ValueAtIndex(i).location);
	}

    m_glesImpl->ActiveVertexBufferObject(0);
	m_glesImpl->ActiveIndexBufferObject(0);

    
	PROFILER_ADDDEVICESTATEVAL( tris, numTris );
	PROFILER_ADDDEVICESTATEVAL( calls, 1 );
	PROFILER_ADDDEVICESTATEVAL( verts, numVertice );
#endif
}

bool RenderDeviceGLES::BeginFrame()
{
#if USE_NATIVE_WINDOW && __WIN32__

	if (m_activeContext.isvalid())
	{
		m_activeContext->BeginFrame();
	}
	else
	{
		return false;
	}
#endif

	m_glesImpl->ActiveVertexBufferObject(0);
	m_glesImpl->ActiveIndexBufferObject(0);

	return true;
}

void RenderDeviceGLES::EndFrame()
{
	m_glesImpl->ActiveShaderProgram(0);
	m_glesImpl->ActiveFrameBuffer(m_mainFBOnum);
	m_glesImpl->ActiveTextureUnit(0);

	m_bDeviceLost = false;

}

void RenderDeviceGLES::Present(WindHandle hwnd)
{
#if USE_NATIVE_WINDOW && __WIN32__
	if (m_activeContext.isvalid())
	{
		m_activeContext->EndFrame();
	}
	else
	{
		return;
	}

#endif
}

void RenderDeviceGLES::SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
{
	glUniform4fv(reg, vec4count, val);
	m_glesImpl->CheckError();
}

void RenderDeviceGLES::SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
{
	
}

void RenderDeviceGLES::SetVertexShaderConstantFloat(const int& reg, float* val)
{
	glUniform1f(reg, *val);
	m_glesImpl->CheckError();
}

void RenderDeviceGLES::SetPixelShaderConstantFloat(const int& reg, float* val)
{

}

void RenderDeviceGLES::SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
{
	if (matrixCount == 1)
	{
		Math::matrix44* mat       =  (Math::matrix44*)val;
		Math::matrix44 transposed = Math::matrix44::transpose(*mat);

		glUniformMatrix4fv(reg, matrixCount, GL_FALSE, (float*)&transposed);
		m_glesImpl->CheckError();
	} 
	else
	{
		glUniformMatrix4fv(reg, matrixCount, GL_FALSE, val);
		m_glesImpl->CheckError();
	}
	
}

void RenderDeviceGLES::SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
{

}

bool RenderDeviceGLES::OnDeviceLost()
{
	m_glesImpl->ActiveFrameBuffer(0);

	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_glesImpl->ResetGLState();

	return true;
}

bool RenderDeviceGLES::CheckReset()
{
	return true;
}

bool RenderDeviceGLES::OnDeviceReset()
{
	return true;
}

void RenderDeviceGLES::SetRenderTarget(RenderTarget* rt)
{
	n_assert (rt)
	
	const RenderTargetGLES* pRTGLES = _Convert<RenderTarget, RenderTargetGLES>(rt);

	GLbitfield mask = 0;

	const GLESFrameBuf& fbo = pRTGLES->GetRenderTargetGLES();

	if (!pRTGLES->IsDefaultRenderTarget())
	{
		_UnbindBuffer();

		m_glesImpl->ActiveFrameBuffer(fbo.FrameBuf);
	} 
	else
	{
		m_glesImpl->ActiveFrameBuffer(m_mainFBOnum);

		mask |= GL_DEPTH_BUFFER_BIT;
		mask |= GL_STENCIL_BUFFER_BIT;
	}

	uint clearFlags = pRTGLES->GetClearFlags();

	if (clearFlags & RenderTarget::ClearColor)
	{
		mask |= GL_COLOR_BUFFER_BIT;
	}

	if (pRTGLES->HasDepthStencilBuffer())
	{
		if (clearFlags & RenderTarget::ClearDepth)
		{
			mask |= GL_DEPTH_BUFFER_BIT;
		}

		if (clearFlags & RenderTarget::ClearStencil)
		{
			mask |= GL_STENCIL_BUFFER_BIT;
		}
	}

	if (mask != 0)
	{
		const Math::float4& color = pRTGLES->GetClearColor();
		glClearColor(color.x(), color.y(), color.z(), color.w());	
		m_glesImpl->CheckError();
		GLboolean bDepthMask = GL_FALSE;

		glGetBooleanv(GL_DEPTH_WRITEMASK, &bDepthMask);
		glDepthMask(GL_TRUE);
		m_glesImpl->CheckError();
		glClear(mask);
		m_glesImpl->CheckError();
		glDepthMask(bDepthMask);
		m_glesImpl->CheckError();
	}
}

void RenderDeviceGLES::SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume /* = false */)
{

}

const GPtr<RenderTarget> RenderDeviceGLES::CreateRenderTarget(const GPtr<RenderTarget>& rt)
{
	GPtr<RenderTargetGLES> rtGLES = RenderTargetGLES::Create();
	n_assert(rtGLES.isvalid());

	rtGLES->SetWidth(rt->GetWidth());
	rtGLES->SetHeight(rt->GetHeight());
	rtGLES->SetAntiAliasQuality(rt->GetAntiAliasQuality());
	rtGLES->SetColorBufferFormat(rt->GetColorBufferFormat());
	rtGLES->SetMipMapsEnabled(rt->AreMipMapsEnabled());
	rtGLES->SetClearFlags(rt->GetClearFlags());
	rtGLES->SetClearColor(rt->GetClearColor());
	rtGLES->SetClearStencil(rt->GetClearStencil());
	rtGLES->SetClearDepth(rt->GetClearDepth());
	rtGLES->SetMRTIndex(rt->GetMRTIndex());
	if (rt->HasDepthStencilBuffer())
	{
		rtGLES->AddDepthStencilBuffer();
	}

	rtGLES->SetScreenSizeRatio(rt->GetScreenSizeRatio());
	rtGLES->SetDefaultRenderTarget(rt->IsDefaultRenderTarget());

	if (rt->IsAttachedToMRT())
	{
		rtGLES->AttachToMRT();
	}

	rtGLES->LoadBuffers(rt->GetWidth(), rt->GetHeight());
	rtGLES->AssignGLESTextures();

	return rtGLES.upcast<RenderTarget>();
}

const GPtr<MultipleRenderTarget> RenderDeviceGLES::CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget> &mrt)
{
	return NULL;
}

void RenderDeviceGLES::DrawIndexedInstanced(SizeT numInstances)
{

}

void RenderDeviceGLES::FXSetClipPlane(const int &index, const Math::float4 &plane)
{

}

void RenderDeviceGLES::DisableRenderTarget(int index)
{

}

void RenderDeviceGLES::_UnbindBuffer()
{
	m_glesImpl->ActiveFrameBuffer(m_mainFBOnum);

	for (IndexT i = 0; i < GLES::MaxTextureUnits; ++i)
	{
		m_glesImpl->ActiveTextureUnit(i);
		m_glesImpl->ActiveTextureObject(GL_TEXTURE_2D, 0);
	}

	m_glesImpl->ActiveTextureUnit(0);

}

GLESWindow* RenderDeviceGLES::CreateViewPortWnd( void* hWnd )
{
	return new GLESWindow(this, hWnd );
}

void RenderDeviceGLES::DestroyViewPortWnd( GLESWindow* view )
{
	delete view;
}

}