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
#ifndef __APP_SCRIPT_COMPONENT_H__
#define __APP_SCRIPT_COMPONENT_H__

#include "foundation/util/array.h"
#include "foundation/util/string.h"
#include "appframework/component.h"
#include "appframework/serialization.h"
#include "scriptfeature/inc/script_fwd_decl.h"
#include "scriptfeature/editable_field_value.h"
#include "scriptfeature/inc/script_utility.h"
#include "graphicfeature/components/rendercomponent.h"


namespace Graphic
{
	class RenderToTexture;
}
namespace App
{
	class CameraComponent;
	/*
	 *  Basically, it is a belt connecting mono script system and actor.
	 *	This is actual an instance of script which will be attached to an actor.
 	 *	It contains script instances.
	 */
	class ScriptComponent : public App::Component
	{
		__DeclareSubClass( ScriptComponent , App::Component );
	public:
		ScriptComponent() ;
		virtual ~ScriptComponent();

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();
		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();
		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();
		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();
		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage( const GPtr<Messaging::Message>& msg );
		/// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;
		/// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );
		/// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;
		/// copy this component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		virtual void SetupAllResource();

		virtual bool IsAllResourceLoaded();

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;
		/// get method
		const Util::TStringArray& GetClassNames() const;
		/// get method
		const Util::TStringArray& GetNameSpaces() const	;
		/// get method
		const Util::TStringArray& GetAssemblyNames() const ;
		/// get method
		int GetScriptCount();
		/// get a script instance by name
		TScriptInstancePtr& GetScriptByName( const Util::String& name );
		/// get a script instance by classname
		TScriptInstancePtr& GetScriptByClassName(const Util::String& name);
		/// get a ScriptInstance by index,a null pointer is return if the idx is invalid
		TScriptInstancePtr& GetScriptInstance( int idx );

		TScriptInstancePtr& FindScriptWithEntryMethod(EEntryMethodIndex emIndex);

		bool OnRenderPostEffect(int index, CameraComponent* camera, Graphic::RenderToTexture* source, Graphic::RenderToTexture* destination);

		void BindOnWillRenderObject(const GPtr<RenderComponent>& renderComponent);

		void BindOnRenderPostEffect(const GPtr<CameraComponent>& cameraComponent);

		void UnbindOnRenderPostEffect(const GPtr<CameraComponent>& cameraComponent);

		/// get the write read access for the feild value;
		EditableFeilValue& GetEditableFeildValue();

		void ResetFeildValue();
		void AssignFeildValue();
#ifdef __GENESIS_EDITOR__
		/// add a script to this component;
		void AddCSharpScript( const Util::String& className);
        /// remove a script to this component;
		void RemoveCSharpScript( const Util::String& className );
		/// remove a script to this component;
		void RemoveCSharpScriptByIndex( int index );
		/// add a script to this component
		void AddCSharpScriptByIndex(const Util::String& className,int index ,EditableFeilValue evalue);

		void AddCSharpScriptByIndex( const Util::String& className, int index );
		/// change the order of scripts in the array;
		void ChangeExeOrder( int source, int target );
		/// change the order of scripts in the array;
		void MoveExeOrder( int source, int target );
		/// change name of a script;
		void ChangeScriptName( int source , Util::String& className );
		/// change name of a script;
		void ChangeScriptName( int source , Util::String& className, const EditableFeilValue& evalue);
		/// ReCreateScriptInsctances;
		void CreateAllScriptInstances();
		/// Destory ScriptInstances;
		void DestoryAllScriptInstances();
		/// get a script's class name by index;
		const Util::String& FindClassName( int index );
		/// call script's OnLoad method only on editor side;
		void OnLoad_Editor();
		/// Get intance's info which creation failed
		bool GetInstanceCreationError( Util::String& error );
#endif
	private:  
		/// call script's OnLoad method
		void OnLoad();
		/// call script's OnExit method
		void OnExit();
		/// rewrite the set actor fun to set the owner of script instances
		virtual void _SetActor(Actor* v);

		/// set method
		void SetProperties( const Util::TStringArray& arrClassNames,
						const Util::TStringArray& arrNameSpaces,
						const Util::TStringArray& arrAssemblyNames );
		/// save version 1 scene data
		void SaveVer1( AppWriter* pWriter )const;
		/// save version 2 scene data
		void SaveVer2( AppWriter* pWriter )const;
		/// load version 1 scene data
		void LoadVer1( AppReader* pReader );
		/// load version 2 scene data
		void LoadVer2( AppReader* pReader );

		void _CreateAllScriptInstances();

		void _DestoryAllScriptInstances();

		void _Check_OnRenderPostEffect_Bind();

		void _Check_OnRenderPostEffect_Unbind();

		void _Check_OnRenderPostEffect_Rebind();

		void _OnWillRenderObject(RenderComponent* renderComponent);

		void _Check_OnWillRenderObject_Bind();

		void _Check_OnWillRenderObject_Unbind();

		void _Check_OnWillRenderObject_Rebind();



		// - private member
		Util::TStringArray m_arrClassNames;
		Util::TStringArray m_arrNameSpaces;
		Util::TStringArray m_arrAssemblyNames;
		typedef Util::Array<TScriptInstancePtr> ScriptInstanceContainer;
		ScriptInstanceContainer m_arrScriptInstances;
		
		EditableFeilValue m_fieldValue;
#ifdef __GENESIS_EDITOR__
		bool m_bOnLoaded;
#endif
	};

	//------------------------------------------------------------------------
	inline const Util::TStringArray& ScriptComponent::GetClassNames() const 
	{
		return m_arrClassNames;
	}
	//------------------------------------------------------------------------
	inline const Util::TStringArray& ScriptComponent::GetNameSpaces() const	
	{
		return m_arrNameSpaces;
	}
	//------------------------------------------------------------------------
	inline const Util::TStringArray& ScriptComponent::GetAssemblyNames() const 	
	{
		return m_arrAssemblyNames;
	}
	//------------------------------------------------------------------------
	inline int ScriptComponent::GetScriptCount() 
	{
		return m_arrClassNames.Size();
	}
	//------------------------------------------------------------------------
	inline TScriptInstancePtr& ScriptComponent::GetScriptInstance( int idx )
	{
		return m_arrScriptInstances[idx];
	}
	//------------------------------------------------------------------------
	inline EditableFeilValue& ScriptComponent::GetEditableFeildValue()
	{
		return m_fieldValue;
	}


}

#endif // - __SCRIPT_COMPONENT_H__
