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
#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "appframework/component.h"
#include "graphicsystem/Material/materialinstance.h"
#include "graphicsystem/RenderUnit.h"
#include "foundation/delegates/delegatetype.h"
namespace Graphic
{
	class Material;
	class Camera;
}
namespace App
{

	typedef Graphic::ShaderParamString ShaderParamString;
	/*
	Management of renderstate, it contains materialarray. 
	*/
	class RenderComponent: public App::Component
	{
		__DeclareSubClass(RenderComponent, App::Component);
	public:
		typedef RenderComponent* OnWillRenderObjectSender;
		typedef Delegates::delegates::CDelegate1<OnWillRenderObjectSender> EventHandle_OnWillRenderObject;//CDelegate1
		RenderComponent();
		virtual ~RenderComponent();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );
		void CopyFrom_1( const GPtr<Component>& pComponent );
		void CopyFrom_2( const GPtr<Component>& pComponent );

		/// Render a component stand alone. the "customMat" could be null.
		virtual void StandaloneRender(const GPtr<Graphic::Material>& customMat);

		virtual void OnWillRenderObject(Graphic::Camera* sender);

		virtual void SetupAllResource();
		virtual bool IsAllResourceLoaded();

		/// Get Shader Count
		SizeT GetShaderCount(void) const;

		/// get Shader ID,return maybe null.
		const Resources::ResourceId& GetShaderID(IndexT iSubMesh ); 

		const Resources::ResourceId& GetMaterialID(IndexT iSubMesh ); 

		/// get texture param count refrence by submesh's shader 
		SizeT GetTextureParamCount(IndexT iSubMesh) const;

		SizeT GetMaterialCount(void) const;

		GPtr<Graphic::MaterialInstance>& GetMaterial(IndexT index );

		const GPtr<Graphic::MaterialInstance>& GetMaterial(IndexT index ) const;
		bool HaveMaterial(Resources::ResourceId& matID ) const;

		/**
		* SetMaterialID  
		* @param: IndexT iSubMesh						
		* @param: const Resources::ResourceId& matID,	
		* @param: const bool bCopy = false				when true the material will be a copy.
		* @return: void  
		* @see: 
		* @remark:  
		*/
		virtual void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );

		/**
		* SetMaterialByShaderID  
		* @param: IndexT iSubMesh						index
		* @param: const Resources::ResourceId& shaderID	shaderid
		* @param: const bool bSave = false				material will be save or not.
		* @return: void  
		* @see: 
		* @remark:  
		*/
		virtual void SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave = true );

		/**
		* ModifyMaterialShaderID  
		* @param: const Resources::ResourceID& shaderID  
		* @return: void  
		* @see: 
		* @remark: 
		*/
		virtual void ModifyMaterialShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID);

		// delete material
		void DelMaterial(IndexT iSubMesh);

		/// enum texture param name referenced by submesh's shader
		const ShaderParamString& EnumTextureParam(IndexT iSubMesh, IndexT iParam) const;

		/// if has texture param referenced by submesh's shader
		bool HasTextureParam(IndexT iSubMesh, const ShaderParamString& shaderparam ) const;

		/// set texture ID 
		void SetTexture( IndexT iSubMesh, const ShaderParamString& paramName, const Resources::ResourceId& texID, const Resources::Priority priority = Resources::ResourcePriority::TextureDefault );

		/// set texture handle
		void SetTexture(IndexT iSubMesh, const ShaderParamString& paramName, const RenderBase::TextureHandle& handle);

		/// get texture ID
		const Resources::ResourceId& GetTexture(IndexT iSubMesh, const ShaderParamString& paramName ) const;

		/// get shader constant param count refrence by submesh's shader 
		SizeT GetShaderConstantParamCount(IndexT iSubMesh) const;

		/// enum shader constant param name referenced by submesh's shader
		const ShaderParamString& EnumShaderConstantParam(IndexT iSubMesh, IndexT iParam) const;

		/*
		 *param in: iSubMesh,paramName
		 *param out: paramValue
		 *
		*/
		Graphic::MaterialParameterType GetShaderConstantParamValue( ShaderParamString& paramValue, const IndexT& iSubMesh, const ShaderParamString& paramName);
		/// 
		virtual void SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::float4& val);
		virtual void SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::scalar& val );
		virtual void SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::matrix44& val);

		virtual void SetVisible( bool bVisible);
		virtual bool GetVisible();

		
		virtual void SetCastShadow( bool bCastShadow );
		virtual bool GetCastShadow();

		virtual void SetReceiveShadow( bool bReceiveShadow );
		virtual bool GetReceiveShadow();

		void ClearShaderConstantParams( IndexT iSubMesh );

		Graphic::RenderbleResUnit& GetRenderbleRes( IndexT index);

		const Graphic::RenderableResUnitArray& GetRenderResource();

		bool IsAllTexLoaded();

		template<typename T>
		void OnWillRenderObjectEvent_Bind(T* object, void (T::*method)(OnWillRenderObjectSender));

		void OnWillRenderObjectEvent_Unbind();

		/// modify shader parameters
		void _AddTextureParam( IndexT iSubMesh, const ShaderParamString& paramName, const Resources::ResourceId& _texID, Resources::Priority priority = Resources::ResourcePriority::TextureDefault);
		void _ClearTextureParam( IndexT iSubMesh );
	protected:
	friend class RenderComponentSerialization;
		/// get shader constant param value,used for serialization
		void _SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Util::String& val);
		/// get shader constant param value,used for serialization
		const Util::String& _GetShaderConstantParamValue(IndexT iSubMesh, const ShaderParamString& paramName ) const;

		/// @Component::_OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::_OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		// @Component::_OnDestroy called only form Actor::Destroy
		virtual void OnDestroy();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

		/// @Component::_OnBeginFrame called after movement has happened. 
		virtual void _OnBeginFrame();

		/// Set actor, this is attached to, to `v'.
		virtual void _SetActor(Actor* v);

		virtual void _OnWillRenderObjectEvent_Change(bool bind){};

		virtual void _UpdateShadow();



		void _DirtyMaterial(IndexT iSubMesh );

		void _ClearRenderResUnits();



	protected:

		EventHandle_OnWillRenderObject eventWillRenderObject;
		Graphic::RenderableResUnitArray mRenderableResUnitList;
		bool mMatDirty;
		bool mCanCreateMaterial;
		//bool mRenderQueueDirty;
		
		bool m_bAllTexLoaded;

		//bool mSetAllRenderable;


		//0 means synchronization, 1 means asynchronization.
		int  mResourcePrior;

		bool mbCastShadow;
		bool mbReceiveShadow;

		bool mVisible;
	};
	//---------------------------------------------------------------------------
	inline bool RenderComponent::IsAllTexLoaded()
	{
		return m_bAllTexLoaded;
	}
	//--------------------------------------------------------------------------------
	inline Graphic::RenderbleResUnit& RenderComponent::GetRenderbleRes( IndexT index)
	{
		return mRenderableResUnitList[index];
	}
	//--------------------------------------------------------------------------------
	inline SizeT RenderComponent::GetMaterialCount() const 
	{ 
		return mRenderableResUnitList.Size() ; 
	}

	inline const Graphic::RenderableResUnitArray& RenderComponent::GetRenderResource()
	{
		return mRenderableResUnitList;
	}
	//--------------------------------------------------------------------------------
	template<typename T>
	inline void RenderComponent::OnWillRenderObjectEvent_Bind(T* object, void (T::*method)(OnWillRenderObjectSender))
	{
		eventWillRenderObject = Delegates::newDelegate(object, method);
		_OnWillRenderObjectEvent_Change(true);
	}
	//--------------------------------------------------------------------------------
	inline void RenderComponent::OnWillRenderObjectEvent_Unbind()
	{
		eventWillRenderObject = NULL;
		_OnWillRenderObjectEvent_Change(false);
	}

}



#endif // RENDERCOMPONENT_H_
