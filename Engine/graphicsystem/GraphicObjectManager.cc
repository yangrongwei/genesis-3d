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
#include "GraphicObjectManager.h"
#include "rendersystem/RenderSystem.h"
#include "graphicsystem/GraphicSystem.h"

#include "resource/resourceserver.h"

#include "io/ioserver.h"
#include "io/textreader.h"
#include "io/memorystream.h"

#include "materialmaker/GenesisMaterial.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "resource/resourcemanager.h"
//#include "Material/MaterialManager.h"

namespace App
{
	__ImplementClass( App::GraphicObjectManager, 'AGOM',Core::RefCounted);
	__ImplementImageSingleton( App::GraphicObjectManager );

	__ImplementClass( App::RenderMeshNotifier, 'RMNR', Resources::ResourceNotifier);
	__ImplementClass( App::RenderTextureNotifier, 'RTNR', Resources::ResourceNotifier);

	using namespace RenderBase;
	using namespace Resources;
	using namespace Graphic;
	using namespace Threading;

	//------------------------------------------------------------------------
	void RenderMeshNotifier::Notify(Resources::Resource* res, Resources::Resource::State preState )
	{
		n_assert( GraphicObjectManager::HasInstance() );
		n_assert( res && res->GetRtti() == &MeshRes::RTTI );
		GPtr<Resource> pRes(res);
		GPtr<MeshRes> pMesh = pRes.downcast<MeshRes>();

		uint32 updateThreadID = uint32(Thread::GetMyThreadId());
		if ( GraphicObjectManager::Instance()->m_MainThreadID == updateThreadID )
		{
			GraphicObjectManager::Instance()->UpdataPrimitiveHandle( pMesh );
		}
	}
	//------------------------------------------------------------------------
	void RenderTextureNotifier::Notify(Resources::Resource* res, Resources::Resource::State preState)
	{
		n_assert( GraphicObjectManager::HasInstance() );
		n_assert( res && res->GetRtti() == &ImageRes::RTTI );
		GPtr<Resource> pRes(res);
		GPtr<ImageRes> pImage = pRes.downcast<ImageRes>();

		uint32 updateThreadID = uint32(Thread::GetMyThreadId());

		if ( GraphicObjectManager::Instance()->m_MainThreadID == updateThreadID )
		{
			GraphicObjectManager::Instance()->UpdataTextureHandle( pImage );
		}
	}

	//------------------------------------------------------------------------
	GraphicObjectManager::GraphicObjectManager()
	{
		m_MainThreadID = uint32(Thread::GetMyThreadId());

		__ConstructImageSingleton;
	}
	//------------------------------------------------------------------------
	GraphicObjectManager::~GraphicObjectManager()
	{
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::OnActivate()
	{
		n_assert( !mMeshNotifier.isvalid() );
		mMeshNotifier = RenderMeshNotifier::Create();

		n_assert( !mTexNotifier.isvalid() );
		mTexNotifier = RenderTextureNotifier::Create();

		Resources::ResourceServer* resServer = Resources::ResourceServer::Instance();
#if __WIN32__ && RENDERDEVICE_D3D9
		GPtr<Resource> pRes = resServer->CreateOrGetResource( "sys:white.dds", &ImageRes::RTTI );
#elif __ANDROID__ || RENDERDEVICE_OPENGLES
		GPtr<Resource> pRes = resServer->CreateOrGetResource( "sys:white.jpg", &ImageRes::RTTI );
#endif

		n_assert( pRes.isvalid() );

		if ( pRes->GetState() != Resource::Loaded )
		{
			bool bOK = resServer->LoadResource(pRes,false);
			n_assert( bOK );
		}

		GPtr<ImageRes> pImage = pRes.downcast<ImageRes>();
		n_assert( pImage.isvalid() );

		pImage->SetManuLoad(true);	//	避免被卸载

		//LoadAllMaterialInstance();	
		if ( !mMaterialInstanceManager.isvalid() )
		{
			mMaterialInstanceManager = Graphic::MaterialInstanceManager::Create();			
		}

	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::OnDeactivate()
	{
		// check if all object discard
		if ( !mReversePrimitives.IsEmpty() )
		{
			for ( IndexT index = 0; index < mReversePrimitives.Size(); ++index )
			{
				n_warning("GraphicObjectManager::OnDeactivate() %s Primitive Not Discard/n", mReversePrimitives.KeyAtIndex(index).AsString().AsCharPtr() );
			}
		}
		else
		{
			n_assert( !mMeshNotifier->IsAttached() );
		}

		if ( !mReverseTextures.IsEmpty() )
		{
			for ( IndexT index = 0; index < mReverseTextures.Size(); ++index )
			{
				n_warning("GraphicObjectManager::OnDeactivate() %s texture Not Discard/n", mReverseTextures.KeyAtIndex(index).AsString().AsCharPtr() );
			}
		}
		else
		{
			n_assert( !mTexNotifier->IsAttached() );
		}

		mMeshNotifier = NULL;
		mTexNotifier = NULL;
	}

	//------------------------------------------------------------------------
	RenderBase::PrimitiveHandle
		GraphicObjectManager::CreatePrimitiveHandle(const GPtr<Resources::MeshRes>& mesh)
	{
		if ( !mesh.isvalid() || !mesh->GetResourceId().IsValid() )
		{
			return RenderBase::PrimitiveHandle();
		}

		IndexT findIndex = mReversePrimitives.FindIndex( mesh->GetResourceId() );
		if ( findIndex != InvalidIndex )
		{
			const PrimitiveHandle& handle = mReversePrimitives.ValueAtIndex( findIndex );

			IndexT priIndex = mPrimitives.FindIndex( handle );
			if ( priIndex == InvalidIndex )
			{
				n_warning(" GraphicObjectManager::CreatePrimitiveHandle: some error. test reverse /n");
				mPrimitives.Add( handle, MeshRef(mesh) );
			}
			else
			{
				MeshRef& meshRef = mPrimitives.ValueAtIndex(priIndex);
				++(meshRef.refCount);
			}
			return handle;
		}
		else
		{
			PrimitiveHandle handle = _BuildPrimitive( mesh );
			if ( handle.IsValid() )
			{	
				n_assert( mMeshNotifier.isvalid() );
				mesh->AttachNotifier( mMeshNotifier.upcast<ResourceNotifier>() );
				mPrimitives.Add( handle, MeshRef(mesh) );
				mReversePrimitives.Add( mesh->GetResourceId(), handle );
			}
			return handle;
		}
	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::UpdataPrimitiveHandle( const GPtr<Resources::MeshRes>& mesh)
	{
		if ( !mesh.isvalid() || !mesh->GetResourceId().IsValid() )
		{
			return;
		}

		IndexT findIndex = mReversePrimitives.FindIndex( mesh->GetResourceId() );
		if ( findIndex != InvalidIndex )
		{
			PrimitiveHandle& handle = mReversePrimitives.ValueAtIndex( findIndex );
			n_assert( handle.IsValid() );

			VertexBufferData vbd;
			IndexBufferData ibd;

			if(_BuildBufferData(vbd, ibd, mesh))
			{
				GraphicSystem* gs = GraphicSystem::Instance();
				gs->ChangePrimitiveHandle(handle, &vbd, &ibd);
			}
			else
			{
				n_assert( "GraphicObjectManager::UpdataPrimitiveHandle Not Impl Now\n");
			}
		}

	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::DiscardPrimitiveHandle( const RenderBase::PrimitiveHandle& handle )
	{
		IndexT findIndex =  mPrimitives.FindIndex( handle );
		if ( findIndex == InvalidIndex )
		{
			return;
		}

		MeshRef& meshRef = mPrimitives.ValueAtIndex( findIndex ); 
		--meshRef.refCount;
		n_assert( meshRef.refCount >= 0 );

		if ( meshRef.refCount == 0 )
		{
			_ErasePrimitive(handle);

			n_assert( meshRef.res.isvalid() );

			n_assert( mMeshNotifier.isvalid() );
			meshRef.res->DeattachNotifier( mMeshNotifier.upcast<ResourceNotifier>() );
			mReversePrimitives.Erase( meshRef.res->GetResourceId() );

			mPrimitives.EraseAtIndex( findIndex );
		}
	}
	//------------------------------------------------------------------------
	RenderBase::TextureHandle 
		GraphicObjectManager::CreateTextureHandle( const GPtr<Resources::ImageRes>& image )
	{
		if ( !image.isvalid() || !image->GetResourceId().IsValid() )
		{
			return RenderBase::PrimitiveHandle();
		}

		IndexT findIndex = mReverseTextures.FindIndex( image->GetResourceId() );
		if ( findIndex != InvalidIndex )
		{
			TextureHandle handle = mReverseTextures.ValueAtIndex( findIndex );

			IndexT priIndex = mTextures.FindIndex( handle );
			if ( priIndex == InvalidIndex )
			{
				n_warning(" GraphicObjectManager::CreateTextureHandle: some error. test reverse /n");
				mTextures.Add( handle, ImageRef(image) );
			}
			else
			{
				ImageRef& imageRef = mTextures.ValueAtIndex(priIndex);
				++(imageRef.refCount);
			}
			return handle;
		}
		else
		{
			TextureHandle handle = _BuildTexture( image );
			if ( handle.IsValid() )
			{	
				n_assert( mTexNotifier.isvalid() );
				image->AttachNotifier( mTexNotifier.upcast<ResourceNotifier>() );
				mTextures.Add( handle, ImageRef(image) );
				mReverseTextures.Add( image->GetResourceId(), handle );
			}
			return handle;
		}
	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::UpdataTextureHandle( const GPtr<Resources::ImageRes>& image )
	{
		if ( !image.isvalid() || !image->GetResourceId().IsValid() )
		{
			return;
		}

		IndexT findIndex = mReverseTextures.FindIndex( image->GetResourceId() );
		if ( findIndex != InvalidIndex )
		{
			const TextureHandle& handle = mReverseTextures.ValueAtIndex( findIndex );
			n_assert( handle.IsValid() );

			const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();

			GPtr<RenderBase::Texture> tex = _BuildTextureData( image );

			if ( tex.isvalid() )
			{
				gs->ChangeTexture( handle, tex );
			}
			else
			{
				n_assert( "GraphicObjectManager::UpdataTextureHandle Not Impl Now\n");
			}
		}
	}

	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::DiscardTextureHandle( const RenderBase::TextureHandle& handle )
	{
		IndexT findIndex =  mTextures.FindIndex( handle );
		if ( findIndex == InvalidIndex )
		{
			return;
		}

		ImageRef& imageRef = mTextures.ValueAtIndex( findIndex ); 
		--imageRef.refCount;
		n_assert( imageRef.refCount >= 0 );

		if ( imageRef.refCount == 0 )
		{
			_EraseTexture(handle);

			n_assert( imageRef.res.isvalid() );
			n_assert( mTexNotifier.isvalid() );
			imageRef.res->DeattachNotifier( mTexNotifier.upcast<ResourceNotifier>() );
			mReverseTextures.Erase( imageRef.res->GetResourceId() );
			mTextures.EraseAtIndex( findIndex );
		}
	}	

	bool BuildVertexComponent(const GPtr<Resources::MeshRes>& mesh, Util::Array<RenderBase::VertexComponent>& verDeclare)
	{
		n_assert(mesh);

		if( mesh->GetVertexData<PositionData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Position,0, VertexComponent::Float3) );
		}

		if ( mesh->GetVertexData<NormalData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Normal,0, VertexComponent::Float3) );
		}

		if ( mesh->GetVertexData<ColorData>() )
		{
			//if ( RenderSystem::Instance()->GetRendererType() == eRendererD3D9 )
			if(true)
			{
				verDeclare.Append( VertexComponent(VertexComponent::Color,0, VertexComponent::ColorBGRA) );
			}
			else
			{
				n_error(" should decide device use bgra or rgba");
			}
		}

		const SizeT deviceSupportTexCount = 8;	// 这个数字应该是渲染系统定义的
		for ( IndexT iTex = 0; iTex < deviceSupportTexCount; ++iTex )
		{
			if ( mesh->GetVertexData<TexCoordData>(iTex) )
			{
				verDeclare.Append( VertexComponent(VertexComponent::TexCoord, iTex, VertexComponent::Float2) );
			}
			else
			{
				break;
			}
		}

		if( mesh->GetVertexData<TangentData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Tangent,0, VertexComponent::Float4) );
		}

		if ( mesh->GetVertexData<BiNormalData>() )
		{
			verDeclare.Append( VertexComponent(VertexComponent::Binormal,0, VertexComponent::Float4) );
		}

		if ( mesh->GetVertexData<BoneInfoData>() )
		{
			// SkinJIndices和SkinWeights一定同时存在，后面会一次性拷贝
			verDeclare.Append( VertexComponent(VertexComponent::SkinJIndices,0, VertexComponent::Short4) );
			verDeclare.Append( VertexComponent(VertexComponent::SkinWeights,0, VertexComponent::Float4) );
		}

		return !verDeclare.IsEmpty();
	}
	//------------------------------------------------------------------------
	template<typename T, SizeT elemSize >
	void StripeCopy( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			Memory::Copy( from, to, elemSize );
			++from;
			to += toElemsSize;
		}
	}
	template<typename T , SizeT elemSize >
	void StripeSwapCopyColor( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );	// color is 4 byte

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			*((int*)to) = ((Color32*)from)->HexARGB();

			++from;
			to += toElemsSize;
		}
	}
	//------------------------------------------------------------------------
	void buildVertexStreams( const GPtr<MeshRes>& mesh, const VertexComponent& vcdef, RenderBase::VertexStreams& streams)
	{
		RenderBase::VertexStream stream;
		switch( vcdef.GetSemanticName() )
		{
		case VertexComponent::Position:
			{
				PositionData::Elem* elem = mesh->GetVertexData<PositionData>();
				n_assert( vcdef.GetByteSize() == 12 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();	
			}
			break;
		case VertexComponent::Normal:
			{
				NormalData::Elem* elem = mesh->GetVertexData<NormalData>();
				n_assert( vcdef.GetByteSize() == 12 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();
			}
			break;
		case VertexComponent::Tangent:
			{
				TangentData::Elem* elem = mesh->GetVertexData<TangentData>();
				n_assert( vcdef.GetByteSize() == 16 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();
			}
			break;
		case VertexComponent::Binormal:
			{
				BiNormalData::Elem* elem = mesh->GetVertexData<BiNormalData>();
				n_assert( vcdef.GetByteSize() == 16 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();
			}
			break;
		case VertexComponent::TexCoord:
			{
				TexCoordData::Elem* elem = mesh->GetVertexData<TexCoordData>( vcdef.GetSemanticIndex() );
				n_assert( vcdef.GetByteSize() == 8 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();
			}
			break;
		case VertexComponent::Color:
			{
				ColorData::Elem* elem = mesh->GetVertexData<ColorData>( vcdef.GetSemanticIndex() );

				n_assert( vcdef.GetByteSize() == 4 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize();
			}
			break;
		case VertexComponent::SkinJIndices:
			{
				BoneInfoData::Elem* elem = mesh->GetVertexData<BoneInfoData>( vcdef.GetSemanticIndex() );

				// 有SkinJIndices的时候，一定紧跟着SkinWeights。一次性将两个数据都拷贝了
				n_assert( vcdef.GetByteSize() == 8 );
				stream.data = elem;
				stream.offsetInByte = vcdef.GetByteOffset();
				stream.elemSizeInByte = vcdef.GetByteSize() + VertexComponent::GetByteSize(VertexComponent::Float4);
			}
			break;
		case VertexComponent::SkinWeights:
			{
				n_assert( vcdef.GetByteSize() == 16 );
			}
			return;
		default:
			n_error("GraphicObjectManager|copyVBOComponent: invalid VertexComponent::SemanticName.\n");
			break;
		}
		streams.Append(stream);
	}
	void copyVBOComponent( const GPtr<MeshRes>& mesh, const VertexComponent& vcdef, uchar* vertexDataPtr, SizeT VertexSize, SizeT numVertices)
	{
		switch( vcdef.GetSemanticName() )
		{
		case VertexComponent::Position:
			{
				PositionData::Elem* elem = mesh->GetVertexData<PositionData>();
				n_assert( vcdef.GetByteSize() == 12 );
				StripeCopy<PositionData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Normal:
			{
				NormalData::Elem* elem = mesh->GetVertexData<NormalData>();
				n_assert( vcdef.GetByteSize() == 12 );
				StripeCopy<NormalData::Elem,12>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Tangent:
			{
				TangentData::Elem* elem = mesh->GetVertexData<TangentData>();
				n_assert( vcdef.GetByteSize() == 16 );
				StripeCopy<TangentData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Binormal:
			{
				BiNormalData::Elem* elem = mesh->GetVertexData<BiNormalData>();
				n_assert( vcdef.GetByteSize() == 16 );
				StripeCopy<BiNormalData::Elem,16>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::TexCoord:
			{
				TexCoordData::Elem* elem = mesh->GetVertexData<TexCoordData>( vcdef.GetSemanticIndex() );
				n_assert( vcdef.GetByteSize() == 8 );
				StripeCopy<TexCoordData::Elem,8>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::Color:
			{
				ColorData::Elem* elem = mesh->GetVertexData<ColorData>( vcdef.GetSemanticIndex() );

				n_assert( vcdef.GetByteSize() == 4 );
				if ( vcdef.GetFormat() == VertexComponent::ColorRGBA )
				{
					StripeCopy<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				}
				else if(  vcdef.GetFormat() == VertexComponent::ColorBGRA )
				{
					StripeSwapCopyColor<ColorData::Elem,4>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
				}
				else
				{
					n_assert(" GraphicObjectManager|copyVBOComponent: unknown color format" );
				}

			}
			break;
		case VertexComponent::SkinJIndices:
			{
				BoneInfoData::Elem* elem = mesh->GetVertexData<BoneInfoData>( vcdef.GetSemanticIndex() );

				// 有SkinJIndices的时候，一定紧跟着SkinWeights。一次性将两个数据都拷贝了
				n_assert( vcdef.GetByteSize() == 8 );
				StripeCopy<BoneInfoData::Elem,24>(elem, vertexDataPtr, VertexSize, vcdef.GetByteOffset(), numVertices );
			}
			break;
		case VertexComponent::SkinWeights:
			{
				n_assert( vcdef.GetByteSize() == 16 );
			}
			break;
		default:
			n_error("GraphicObjectManager|copyVBOComponent: invalid VertexComponent::SemanticName/n");
		}
		return;
	}

	void GraphicObjectManager::CopyVBOData(const GPtr<Resources::MeshRes>& mesh, const Util::Array<RenderBase::VertexComponent>& verDeclare, SizeT& vertexSize, SizeT& numVertices, uchar* out)
	{
		n_assert( out );

		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			copyVBOComponent(mesh, verDeclare[index], out, vertexSize, numVertices);
		}
	}

	void GraphicObjectManager::BuildVBData(const GPtr<Resources::MeshRes>& mesh, const RenderBase::VertexComponents& verDeclare, RenderBase::VertexStreams& streams)
	{
		for ( IndexT index = 0; index < verDeclare.Size(); ++index )
		{
			buildVertexStreams(mesh, verDeclare[index], streams);
		}
	}

	bool GraphicObjectManager::_BuildBufferData(RenderBase::VertexBufferData& vbd, RenderBase::IndexBufferData& ibd,const GPtr<Resources::MeshRes>& mesh)
	{
		n_assert(mesh.isvalid());

		// 必须有顶点和索引
		if ( mesh->GetIndexCount() == 0 
			|| mesh->GetVertexCount() == 0 
			|| mesh->GetTopologyType() == RenderBase::PrimitiveTopology::InvalidPrimitiveTopology )
		{
			return false;
		}

		// 解析需要拷贝的顶点分量。
		// @todo:　这里应该加上选择。哪些顶点分量是当前硬件或者shader可以用的
		if( !BuildVertexComponent(mesh, vbd.vertex.vertexComponents) )
		{
			return false;
		}
		VertexComponent::BuildComponentsOffsetAndSize(vbd.vertex.vertexComponents);
		vbd.topology = mesh->GetTopologyType();
		vbd.vertexCount = mesh->GetVertexCount();
		BuildVBData(mesh, vbd.vertex.vertexComponents, vbd.vertex.vertexComponentStreams);

		// 索引数据
		ibd.indexCount = mesh->GetIndexCount();
		if ( mesh->IsUseIndex16() )
		{
			ibd.indexType = IndexBufferData::Int16;
			n_static_assert( 2 == sizeof( Index16Container::value_type ) );
			ibd.stream = (IndexStream)mesh->GetIndex16();
		}
		else
		{
			ibd.indexType  = IndexBufferData::Int32;
			n_static_assert( 4 == sizeof( Index32Container::value_type ) );
			ibd.stream = (IndexStream)mesh->GetIndex32();
		}
		n_assert( ibd.indexType != IndexBufferData::Unknown );
		n_assert( ibd.indexCount > 0 );
		n_assert( ibd.stream );
		return true;
	}
	//------------------------------------------------------------------------
	RenderBase::PrimitiveHandle
		GraphicObjectManager::_BuildPrimitive(const GPtr<Resources::MeshRes>& mesh)
	{

		VertexBufferData vbd;
		IndexBufferData ibd;

		if(_BuildBufferData(vbd, ibd, mesh))
		{
			GraphicSystem* gs = GraphicSystem::Instance();
			return gs->CreatePrimitiveHandle(&vbd, &ibd);
		}
		else
		{
			return RenderBase::PrimitiveHandle();
		}

	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::_ErasePrimitive(const RenderBase::PrimitiveHandle& handle )
	{
		if ( handle.IsValid() )
		{
			const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
			n_assert(gs.isvalid());
			gs->RemovePrimitive( handle );
		}
	}
	//------------------------------------------------------------------------
	GPtr<RenderBase::Texture>
		GraphicObjectManager::_BuildTextureData(const GPtr<Resources::ImageRes>& image)
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

		GPtr<IO::MemoryStream> memStream = IO::MemoryStream::Create();
		memStream->SetAccessMode( IO::Stream::WriteAccess );
		if( memStream->Open() )
		{
			memStream->Write( imageData->Ptr(), imageData->Size() );
			tex->SetStream( memStream.upcast<IO::Stream>() );
			memStream->Close();
			memStream->SetAccessMode( IO::Stream::ReadAccess );
			return tex;
		}

		return GPtr<RenderBase::Texture>();
	}
	//------------------------------------------------------------------------
	RenderBase::TextureHandle 
		GraphicObjectManager::_BuildTexture(const GPtr<Resources::ImageRes>& image )
	{
		n_assert(image.isvalid());
		const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
		n_assert(gs.isvalid());

		GPtr<RenderBase::Texture> tex = _BuildTextureData(image);

		if ( tex.isvalid() )
		{
			return gs->CreateTexture( tex );
		}
		else
		{
			return RenderBase::TextureHandle();		
		}
	}
	//------------------------------------------------------------------------
	void 
		GraphicObjectManager::_EraseTexture(const RenderBase::TextureHandle& handle)
	{
		n_assert(handle.IsValid());
		const GPtr<GraphicSystem>& gs = GraphicSystem::Instance();
		n_assert(gs.isvalid());

		gs->RemoveTexture( handle );
	}


}

