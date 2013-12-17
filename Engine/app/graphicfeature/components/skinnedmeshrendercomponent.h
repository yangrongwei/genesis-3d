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

#pragma once

#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicfeature/components/skinnedrenderobject.h"
#include "resource/meshres.h"
#include "foundation/math/matrix44.h"

namespace App
{
	class SkeletonComponent;
	class AnimationComponent;
	class SkinnedRenderObject;

	class SkinnedMeshRenderComponent : public App::MeshRenderComponent
	{
		__DeclareSubClass(SkinnedMeshRenderComponent, App::MeshRenderComponent);

	public:

		enum UpdateState
		{
			US_Lack,
			US_Stop,
			US_Update,
			US_HadUpdated,		
		};

		typedef SkinnedRenderObject RenderObjectType;
		SkinnedMeshRenderComponent();
		~SkinnedMeshRenderComponent();
		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		void SetSkeleton(SkeletonComponent* skeleton);

		void SetAnimation(AnimationComponent* animation);

		void _NeedUpdate();

		static const Math::matrix44 m_IndentityMatrix;

	protected:

		virtual void _OnFrame();

		virtual void _BuildRenderRes();

		virtual void _BuildRenderObject();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

		void _SetRenderable(const GPtr<Resources::MeshRes>& meshRes, IndexT index, RenderObjectType::RenderableType* renderable);

		void _BuildOriginalVertices(const GPtr<Resources::MeshRes>& mesh);//Only used in software skinning

	private:

		void _CheckState();

		void _ResetSkinnedMatrices();

		void _Update();

		void _ForceUpdate();

		bool _BuildVertexComponent(const GPtr<Resources::MeshRes>& mesh, Util::Array<RenderBase::VertexComponent>& verDeclare); 

		uchar* _BuildOriginalVertices(const GPtr<Resources::MeshRes>& mesh, const Util::Array<RenderBase::VertexComponent> &verDeclare, SizeT& numVertices, SizeT& vertexDataSize);

		void _AnalysisVBOComponent( const GPtr<Resources::MeshRes>& mesh, const RenderBase::VertexComponent& vcdef, SizeT VertexSize);

		bool _BuildToRootXForms();

		bool _BuildDefaultToRootXFroms();

		void _Skinning();

		void _Destroy();

		Util::Dictionary<IndexT, Math::matrix44>   m_FinalTrans;
		Util::Dictionary<IndexT, Math::matrix44>   m_DefaultFinalTrans;
		Util::Array<int> m_VertsRecord;

		Util::String m_LostedSkelton;

		GPtr<SkeletonComponent> m_SkeletonCom;
		GPtr<AnimationComponent> m_AniamtionCom;

		uchar*  m_pVertexDataPtr;
		SizeT  m_VertexPosSize;
		IndexT m_VertexPosByteOffset;
		SizeT  m_VertexNormalSize;
		IndexT m_VertexNormalByteOffset;
		SizeT  m_VertexDataSize;
		IndexT m_BoneInfoIndex;

		SizeT m_nVerticeCount;

		UpdateState m_UpdateState;

		bool m_bReserveFinalTrans;

		//Record vertex count when software skinning
		bool m_bHasRecorded;

	};
}