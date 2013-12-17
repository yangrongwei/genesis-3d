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
#ifndef __graphicobjectmanager_H__
#define __graphicobjectmanager_H__
#include "graphicsystem/GraphicSystem.h"
#include "resource/meshres.h"
#include "resource/imageres.h"
#include "util/dictionary.h"
#include "graphicsystem/Material/materialinstance.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "rendersystem/base/Texture.h"
#include "rendersystem/base/BufferData.h"
#include "Material/MaterialManager.h"


namespace App
{
	class GraphicObjectManager;

	/*
	for mesh resource.
	*/
	class RenderMeshNotifier: public Resources::ResourceNotifier
	{
		__DeclareSubClass(RenderMeshNotifier,  Resources::ResourceNotifier );
	public:
		RenderMeshNotifier() { }
		virtual ~RenderMeshNotifier() { }
	protected:
		virtual void Notify(Resources::Resource* res, Resources::Resource::State preState );

	};

	/*
	for texture resource.
	*/
	class RenderTextureNotifier: public Resources::ResourceNotifier
	{
		__DeclareSubClass(RenderTextureNotifier,  Resources::ResourceNotifier );
	public:
		RenderTextureNotifier() { }
		virtual ~RenderTextureNotifier() { }
	protected:
		virtual void Notify(Resources::Resource* res, Resources::Resource::State preState );
	};


	class GraphicObjectManager : public Core::RefCounted
	{
		__DeclareClass(GraphicObjectManager);
		__DeclareImageSingleton(GraphicObjectManager);
	public:
		GraphicObjectManager();
		virtual ~GraphicObjectManager();

		// @ App::Manager::OnActivate
		virtual void OnActivate();

		/// @ App::Manager::OnDeactivate();
		virtual void OnDeactivate();    

		RenderBase::PrimitiveHandle CreatePrimitiveHandle(const GPtr<Resources::MeshRes>& mesh);
		void UpdataPrimitiveHandle( const GPtr<Resources::MeshRes>& mesh);
		void DiscardPrimitiveHandle( const RenderBase::PrimitiveHandle& handle );

		RenderBase::TextureHandle CreateTextureHandle( const GPtr<Resources::ImageRes>& image );
		void UpdataTextureHandle( const GPtr<Resources::ImageRes>& image );
		void DiscardTextureHandle( const RenderBase::TextureHandle& handle );

		GPtr<Graphic::MaterialInstanceManager>& GetMaterialInstanceManager();

		static void CopyVBOData(const GPtr<Resources::MeshRes>& mesh, const Util::Array<RenderBase::VertexComponent>& verDeclare, SizeT& vertexSize, SizeT& numVertices, uchar* out);
		static void BuildVBData(const GPtr<Resources::MeshRes>& mesh, const RenderBase::VertexComponents& verDeclare, RenderBase::VertexStreams& streams);
	protected:

		RenderBase::PrimitiveHandle _BuildPrimitive(const GPtr<Resources::MeshRes>& mesh);
		void _ErasePrimitive(const RenderBase::PrimitiveHandle& handle );

		GPtr<RenderBase::Texture> _BuildTextureData(const GPtr<Resources::ImageRes>& image);
		RenderBase::TextureHandle _BuildTexture(const GPtr<Resources::ImageRes>& image );
		void _EraseTexture(const RenderBase::TextureHandle& handle);

		static bool _BuildBufferData(RenderBase::VertexBufferData& vbd, RenderBase::IndexBufferData& ibd,const GPtr<Resources::MeshRes>& mesh);


	protected:
		template<typename T>
		struct ResourceRef 
		{
			ResourceRef(): refCount(0) { }
			ResourceRef(const GPtr<T>& t): res(t), refCount(1) { }
			GPtr<T> res;
			IndexT refCount;
		};

		typedef ResourceRef<Resources::MeshRes>  MeshRef;
		typedef ResourceRef<Resources::ImageRes> ImageRef;
		typedef ResourceRef<Graphic::Material> Material;

		typedef Util::Dictionary<RenderBase::PrimitiveHandle, MeshRef> PrimitiveMap;
		typedef Util::Dictionary<Resources::ResourceId, RenderBase::PrimitiveHandle> ReversePrimitiveMap;

		typedef Util::Dictionary<RenderBase::TextureHandle, ImageRef> TextureMap;
		typedef Util::Dictionary<Resources::ResourceId, RenderBase::TextureHandle> ReverseTextureMap;



		PrimitiveMap mPrimitives;
		ReversePrimitiveMap mReversePrimitives;

		TextureMap mTextures;
		ReverseTextureMap mReverseTextures;



		GPtr<RenderMeshNotifier> mMeshNotifier;
		GPtr<RenderTextureNotifier> mTexNotifier;
		GPtr<Graphic::MaterialInstanceManager> mMaterialInstanceManager;

	public:
		uint32 m_MainThreadID;
	};
	inline GPtr<Graphic::MaterialInstanceManager>& GraphicObjectManager::GetMaterialInstanceManager()
	{
		return mMaterialInstanceManager;
	}

}









#endif // __graphicobjectmanager_H__
