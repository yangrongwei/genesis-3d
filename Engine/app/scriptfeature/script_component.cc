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

#include "io/assignregistry.h"
#include "appframework/actor.h"
#include "scriptfeature/mono_icall_registration.h"
#include "scriptfeature/inc/script_component.h"
#include "scriptfeature/script_general_manager.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/inc/script_feature.h"
#include "foundation/util/array.h"
#include "foundation/util/dictionary.h"
#include "foundation/util/string.h"
//#include "app/physXfeature/PhysicsShapeComponent.h"
#include "app/scriptfeature/inc/script_message.h"
#include "app/graphicfeature/components/rendercomponent.h"
#include "app/graphicfeature/components/cameracomponent.h"
#include "app/scriptfeature/script_render_buffer_filter.h"
namespace App
{
	const Util::String s_csScriptSerialize_ClassName     = "ClassName";
	const Util::String s_csScriptSerialize_NameSpace     = "NameSpace";
	const Util::String s_csScriptSerialize_AssemblyName  = "AssemblyName"; 
	const Util::String s_csScriptSerialize_InstanceCount = "InstanceCount";
	const Util::String s_csScriptSerialize_FieldCount    = "FieldCount";
	const Util::String s_csScriptSerialize_FieldName     = "FieldName";
	const Util::String s_csScriptSerialize_FieldType     = "FieldType";
	const Util::String s_csScriptSerialize_FieldValue	 = "FieldValue";
    const Util::String s_csUserDefClassName				 = "UserDefClass";		

	//- ScriptComponent implement ------------------------------------------------------------------------------
	
	__ImplementClass( ScriptComponent , 'SCRC' , App::Component );
	//------------------------------------------------------------------------
	ScriptComponent::ScriptComponent()
		 : m_arrClassNames()
		 , m_arrNameSpaces()
		 , m_arrAssemblyNames()
		 , m_arrScriptInstances()
#ifdef __GENESIS_EDITOR__
		 , m_bOnLoaded( false )
#endif
	{}
	//------------------------------------------------------------------------
	ScriptComponent::~ScriptComponent()
	{
		if( m_arrScriptInstances.Size()>0 )
		{
			n_error("Deadly Error:ScriptComponent is Released before calling function OnDeactivate()\n");
		}	
		
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			if (m_arrScriptInstances[ii].isvalid())
			{
				m_arrScriptInstances[ii]->Discard();
				m_arrScriptInstances[ii] = NULL;
			}
		}	
		m_arrScriptInstances.Clear();
	}
	//------------------------------------------------------------------------
	void ScriptComponent::OnActivate()
	{
		Super::OnActivate();
		_CreateAllScriptInstances();
		OnLoad();
		_Check_OnWillRenderObject_Bind();
		_Check_OnRenderPostEffect_Bind();
	}
	//------------------------------------------------------------------------
	void ScriptComponent::OnDeactivate()
	{
		_Check_OnWillRenderObject_Unbind();
		_Check_OnRenderPostEffect_Unbind();
		if( m_arrScriptInstances.Size()>0 )
		{
			ScriptFeature::Instance()->RemoveScript( this,m_arrScriptInstances );
		}
		
		//--TODO: CHECK IT LATER,NOW DI IT LIKE THIS FOR 7.10'S DEMO,
		//SCRIPTINSTANCE'S DESTROY WILL BE DOWN LATER.
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			if (m_arrScriptInstances[ii].isvalid())
			{
				m_arrScriptInstances[ii]->Discard();
				m_arrScriptInstances[ii] = NULL;
			}
		}		
		m_arrScriptInstances.Clear();
		Super::OnDeactivate();
	}

	//------------------------------------------------------------------------
	void ScriptComponent::SetupCallbacks()
	{
		this->mActor->RegisterComponentCallback( this, MoveBefore );
		this->mActor->RegisterComponentCallback( this, MoveAfter );
		this->mActor->RegisterComponentCallback( this, RenderDebug );

	}
	//------------------------------------------------------------------------
	void ScriptComponent::SetupAcceptedMessages()
	{
		this->RegisterMessage( App::ScriptMessage::Id );
	}
	//------------------------------------------------------------------------
	void ScriptComponent::HandleMessage( const GPtr<Messaging::Message>& msg )
	{
		n_assert( msg );

		if ( msg->CheckId(ScriptMessage::Id) )
		{
  			TScriptMessagePtr smi = msg.downcast<ScriptMessage>();
  			for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
  			{
  				if ( m_arrScriptInstances[ii].isvalid() )
  				{
  					m_arrScriptInstances[ii]->HandleMessage( smi );
  				}
  			} 
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::BindOnWillRenderObject(const GPtr<RenderComponent>& renderComponent)
	{
		renderComponent->OnWillRenderObjectEvent_Bind(this, &ScriptComponent::_OnWillRenderObject);
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_OnWillRenderObject(RenderComponent* renderComponent )
	{
		ScriptInstanceContainer::Iterator begin = m_arrScriptInstances.Begin();
		const ScriptInstanceContainer::Iterator end = m_arrScriptInstances.End();
		while(begin != end)
		{
			if ((*begin).isvalid())
			{
				if ( (*begin)->IsScriptMethodExist(EEntryMethodIndex_OnWillRenderObject) )
				{
					(*begin)->OnWillRenderObject(renderComponent);
				}
			}
			++begin;
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnWillRenderObject_Bind()
	{
		ScriptInstanceContainer::Iterator begin = m_arrScriptInstances.Begin();
		const ScriptInstanceContainer::Iterator end = m_arrScriptInstances.End();
		while(begin != end)
		{
			if ((*begin).isvalid())
			{
				if ( (*begin)->IsScriptMethodExist(EEntryMethodIndex_OnWillRenderObject) )
				{
					mActor->OpenComponentsCommSign(eCCS_OnWillRenderObject);
#ifndef __SCRIPT_COMMIT__
					mActor->Check_OnWillRenderObject_Bind();
#endif
                    return;
				}
			}
			++begin;
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnWillRenderObject_Rebind()
	{
		if (mActor->IsComponentsCommSignOpen(eCCS_OnWillRenderObject))
		{
			ScriptInstanceContainer::Iterator begin = m_arrScriptInstances.Begin();
			const ScriptInstanceContainer::Iterator end = m_arrScriptInstances.End();
			while(begin != end)
			{
				if ((*begin).isvalid())
				{
					if ( (*begin)->IsScriptMethodExist(EEntryMethodIndex_OnWillRenderObject) )
					{
						return;
					}
				}
				++begin;
			}
			_Check_OnWillRenderObject_Unbind();
		}
		else
		{
			_Check_OnWillRenderObject_Bind();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnWillRenderObject_Unbind()
	{
#ifndef __SCRIPT_COMMIT__
		mActor->Check_OnWillRenderObject_Unbind();
#endif
		mActor->CloseComponentsCommSign(eCCS_OnWillRenderObject);
	}

	//------------------------------------------------------------------------
	void ScriptComponent::BindOnRenderPostEffect(const GPtr<CameraComponent>& cameraComponent)
	{
		Graphic::ImageFilterManager& filters = cameraComponent->GetCameraObject()->GetPostEffectFilters();

		int count = m_arrScriptInstances.Size();
		for (int index = 0; index < count; ++ index)
		{	
			GPtr<ScriptInstance>& si = m_arrScriptInstances[index];
			if(!si.isvalid())
			{
				continue;
			}
			if (si->IsScriptMethodExist(EEntryMethodIndex_OnRenderPostEffect))
			{
				n_assert(!filters.Contain(this, ScriptRenderBufferFilter::ScriptIndexToSortIndex(index)));
				ScriptRenderBufferFilter* filter = filters.InsertFilter<ScriptRenderBufferFilter>(this, ScriptRenderBufferFilter::ScriptIndexToSortIndex(index));
				filter->Setup(cameraComponent.get());
			}
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::UnbindOnRenderPostEffect(const GPtr<CameraComponent>& cameraComponent)
	{
		Graphic::ImageFilterManager& filters = cameraComponent->GetCameraObject()->GetPostEffectFilters();
		filters.RemoveFiltersByOwner(this);
	}
	//------------------------------------------------------------------------
	bool ScriptComponent::OnRenderPostEffect(int index, CameraComponent* camera, Graphic::RenderToTexture* source, Graphic::RenderToTexture* destination)
	{
		n_assert(index < m_arrScriptInstances.Size());
		return m_arrScriptInstances[index]->OnRenderPostEffect(camera, source, destination);
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnRenderPostEffect_Bind()
	{
		ScriptInstanceContainer::Iterator begin = m_arrScriptInstances.Begin();
		const ScriptInstanceContainer::Iterator end = m_arrScriptInstances.End();
		while(begin != end)
		{
			if ((*begin).isvalid())
			{
				if ( (*begin)->IsScriptMethodExist(EEntryMethodIndex_OnRenderPostEffect) )
				{
					mActor->OpenComponentsCommSign(eCCS_OnRenderPostEffect);
#ifndef __SCRIPT_COMMIT__
					mActor->Check_OnRenderPostEffect_Bind();
#endif
					return;
				}
			}
			++begin;
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnRenderPostEffect_Rebind()
	{
		_Check_OnRenderPostEffect_Unbind();
		_Check_OnRenderPostEffect_Bind();
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_Check_OnRenderPostEffect_Unbind()
	{
#ifndef __SCRIPT_COMMIT__
		mActor->Check_OnRenderPostEffect_Unbind();
#endif
		mActor->CloseComponentsCommSign(eCCS_OnRenderPostEffect);
	}
	//------------------------------------------------------------------------
	Version ScriptComponent::GetVersion() const
	{
		return 2;
	}
	//------------------------------------------------------------------------
	void ScriptComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		switch ( ver )
		{
		case 1: { LoadVer1( pReader ); break; }
		case 2: { LoadVer2( pReader ); break; }
		default: { n_assert( "Error version tag appear in script component!" ); }
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::Save( AppWriter* pWriter ) const
	{
		Version ver = GetVersion();
		switch ( ver )
		{
		case 1: { SaveVer1( pWriter ); break; }
		case 2: { SaveVer2( pWriter ); break; }
		default: { n_assert( "Can't find save function!" ); }
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::OnLoad()
	{	
		#ifdef __GENESIS_EDITOR__
		return;
		#endif
		for ( IndexT i=0; i < m_arrScriptInstances.Size(); ++i)
		{
			m_arrScriptInstances[i]->OnLoad();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::OnExit()
	{
		for ( IndexT i=0; i < m_arrScriptInstances.Size(); ++i)
		{
			m_arrScriptInstances[i]->OnExit();
		}
	}
	//------------------------------------------------------------------------
	TScriptInstancePtr& ScriptComponent::GetScriptByName(const Util::String& name)
	{
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			if ( m_arrScriptInstances[ii]->GetName()!=name )
			{
				continue;
			}
			return m_arrScriptInstances[ii];
		}

		static TScriptInstancePtr nullPtr;
		return nullPtr;
	}
	//------------------------------------------------------------------------
	TScriptInstancePtr& ScriptComponent::FindScriptWithEntryMethod(EEntryMethodIndex emIndex)
	{
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			if ( m_arrScriptInstances[ii]->IsScriptMethodExist(emIndex) )
			{
				return m_arrScriptInstances[ii];
			}
		}
		static TScriptInstancePtr nullPtr;
		return nullPtr;
	}
	//------------------------------------------------------------------------

	TScriptInstancePtr& ScriptComponent::GetScriptByClassName( const Util::String& name )
	{
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			if ( m_arrClassNames[ii]!=name )
			{
				continue;
			}
			return m_arrScriptInstances[ii];
		}

		static TScriptInstancePtr nullPtr;
		return nullPtr;
	}

	//------------------------------------------------------------------------
	void ScriptComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
		{
			return;
		}

		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
		{
			return;
		}

		GPtr<ScriptComponent> pSource = pComponent.downcast<ScriptComponent>();

		SetProperties( pSource->GetClassNames(), 
					pSource->GetNameSpaces(), 
					pSource->GetAssemblyNames() );

		m_fieldValue = pSource->m_fieldValue;
	}
	void ScriptComponent::SetupAllResource()
	{
		//TODO:
		return;
	}
	bool ScriptComponent::IsAllResourceLoaded()
	{
		return true;
	}
	//------------------------------------------------------------------------
#ifdef __GENESIS_EDITOR__
	void ScriptComponent::OnLoad_Editor()
	{	
		if ( !m_bOnLoaded )
		{
			m_bOnLoaded = true;
			for ( IndexT i=0; i < m_arrScriptInstances.Size(); ++i)
			{
				m_arrScriptInstances[i]->OnLoad();
			}
		}
	}

	template <typename T>
	void MoveArrElement(Util::Array<T>& arr,int source,int target)
	{
		n_assert(source>=0&&source<arr.Size());
		n_assert(target>=0&&target<=arr.Size())
			T sourceElement = arr[source];
		arr.EraseIndex(source);
		arr.Insert(target,sourceElement);
	}
	//------------------------------------------------------------------------
	void ScriptComponent::AddCSharpScript( const Util::String& className )
	{
		TScriptInstancePtr _pScriptInstance;
		if (IsActive())
		{
			_pScriptInstance = Utility_CreateScriptInstance(className,s_csScriptRuntimeNamespace,s_csUserDefCSharpLibName );
			if ( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure that the file name is the same with the class name,and there is no compile errors!\n  ");
			}
			else
			{
				_pScriptInstance->SetOwner( mActor );
			}
			ScriptFeature::Instance()->RemoveScript(this,m_arrScriptInstances);
		}

		m_arrClassNames.Append( className );
		m_arrNameSpaces.Append( s_csScriptRuntimeNamespace );
		m_arrAssemblyNames.Append( s_csUserDefCSharpLibName );

		if (IsActive())
		{
			m_arrScriptInstances.Append( _pScriptInstance );

			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			ResetFeildValue();
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::ChangeExeOrder(int source, int target)
	{
		if (IsActive())
		{
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}
		Util::String sourceString = m_arrClassNames[source];
		m_arrClassNames[source] = m_arrClassNames[target];
		m_arrClassNames[target] = sourceString;

		if (IsActive())
		{
			TScriptInstancePtr scriptInstance = m_arrScriptInstances[source];
			m_arrScriptInstances[source] = m_arrScriptInstances[target];
			m_arrScriptInstances[target] = scriptInstance;
			ResetFeildValue();
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::MoveExeOrder( int source, int target )
	{
		if (IsActive())
		{
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}

		MoveArrElement<Util::String>(m_arrClassNames,source,target);
		MoveArrElement<Util::String>(m_arrNameSpaces,source,target);
		MoveArrElement<Util::String>(m_arrAssemblyNames,source,target);

		if (IsActive())
		{
			MoveArrElement<TScriptInstancePtr>(m_arrScriptInstances,source,target);
			ResetFeildValue();
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::ChangeScriptName( int source , Util::String& className )
	{
		if (IsActive())
		{
			TScriptInstancePtr _pScriptInstance =Utility_CreateScriptInstance(className,s_csScriptRuntimeNamespace,s_csUserDefCSharpLibName );

			if( m_arrClassNames.Size()==0 )
			{
				return;
			}

			if( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure thar the file name is the same with the class name,and there is no compile errors!\n  ");
			}
			else
			{
				_pScriptInstance->SetOwner( mActor );
			}

			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );

			m_arrScriptInstances[source] = _pScriptInstance;
		}
		m_arrClassNames[source] = className;
		if (IsActive())
		{
			ResetFeildValue();
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}

	void ScriptComponent::ChangeScriptName( int source , Util::String& className, const EditableFeilValue& evalue )
	{
		if (IsActive())
		{
			TScriptInstancePtr _pScriptInstance =Utility_CreateScriptInstance(className,s_csScriptRuntimeNamespace,s_csUserDefCSharpLibName );

			if( m_arrClassNames.Size()==0 )
			{
				return;
			}

			if( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure thar the file name is the same with the class name,and there is no compile errors!\n  ");
			}
			else
			{
				_pScriptInstance->SetOwner( mActor );
			}

			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );

			m_arrScriptInstances[source] = _pScriptInstance;
		}

		for (int jj=0;jj<evalue.GetArrInt()[0].Size();jj++ )
		{
			Utility_SetFieldValue(m_arrScriptInstances[source], evalue.GetArrInt()[0].KeyAtIndex(jj), MONO_TYPE_I4, & evalue.GetArrInt()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj< evalue.GetArrFloat()[0].Size();jj++ )
		{
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrFloat()[0].KeyAtIndex(jj), MONO_TYPE_R4, & evalue.GetArrFloat()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrFloat2()[0].Size();jj++ )
		{
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrFloat2()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat2()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrFloat3()[0].Size();jj++ )
		{
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrFloat3()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat3()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrFloat4()[0].Size();jj++ )
		{
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrFloat4()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat4()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrString()[0].Size();jj++ )
		{
			MonoString* monoString = Utility_CppStringToMonoString( evalue.GetArrString()[0].ValueAtIndex(jj).AsCharPtr() );
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrString()[0].KeyAtIndex(jj), MONO_TYPE_STRING,monoString);
		}

		for (int jj=0; jj < evalue.GetArrColor()[0].Size();jj++ )
		{
			Utility_SetFieldValue( m_arrScriptInstances[source], evalue.GetArrColor()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrColor()[0].ValueAtIndex(jj));
		}

		for (int jj=0; jj < evalue.GetArrImagePath()[0].Size();jj++ )
		{
			Utility_SetImagePathFieldValue( m_arrScriptInstances[source], evalue.GetArrImagePath()[0].KeyAtIndex(jj),  evalue.GetArrImagePath()[0].ValueAtIndex(jj),MONO_TYPE_CLASS);
		}

		for (int jj=0; jj < evalue.GetArrAssetPath()[0].Size();jj++ )
		{
			Utility_SetAssetPathFieldValue( m_arrScriptInstances[source], evalue.GetArrAssetPath()[0].KeyAtIndex(jj),  evalue.GetArrAssetPath()[0].ValueAtIndex(jj),MONO_TYPE_CLASS);
		}

		m_arrClassNames[source] = className;
		if (IsActive())
		{
			ResetFeildValue();
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}

	//------------------------------------------------------------------------
	void ScriptComponent::RemoveCSharpScript(const Util::String& className)
	{
		if (IsActive())
		{
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}
		int index = m_arrClassNames.FindIndex(className);

		m_arrClassNames.Erase(m_arrClassNames.Find(className));
		m_arrAssemblyNames.EraseIndex(index);
		m_arrNameSpaces.EraseIndex(index); 
		if (IsActive())
		{
			m_arrScriptInstances.EraseIndex(index);
			if (m_arrScriptInstances.Size()>0)
			{
				ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			}
			ResetFeildValue();
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}

	//------------------------------------------------------------------------
	void ScriptComponent::RemoveCSharpScriptByIndex( int index)
	{
		n_assert( index<=m_arrClassNames.Size());
		
		if (m_arrClassNames.Size()<=0)
		{
			return;
		}
		if (IsActive())
		{
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}

		m_arrClassNames.EraseIndex(index);
		m_arrNameSpaces.EraseIndex(index);
		m_arrAssemblyNames.EraseIndex(index);
		if (IsActive())
		{
			m_arrScriptInstances.EraseIndex(index);
			ResetFeildValue();
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::AddCSharpScriptByIndex(const Util::String& className,int index ,EditableFeilValue evalue)
	{
		TScriptInstancePtr _pScriptInstance;
		if (IsActive())
		{
			_pScriptInstance =Utility_CreateScriptInstance(className,s_csScriptRuntimeNamespace,s_csUserDefCSharpLibName );
			if ( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure thar the file name is the same with the class name,and there is no compile errors!\n  ");
			}
			else
			{
				_pScriptInstance->SetOwner( mActor );

			}
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}
		m_fieldValue.InsertValueAt(evalue,index);

			
		for (int jj=0;jj<evalue.GetArrInt()[0].Size();jj++ )
		{
			Utility_SetFieldValue(_pScriptInstance, evalue.GetArrInt()[0].KeyAtIndex(jj), MONO_TYPE_I4, & evalue.GetArrInt()[0].ValueAtIndex(jj));
		}
			
		for (int jj=0;jj< evalue.GetArrFloat()[0].Size();jj++ )
		{
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrFloat()[0].KeyAtIndex(jj), MONO_TYPE_R4, & evalue.GetArrFloat()[0].ValueAtIndex(jj));
		}
	
		for (int jj=0;jj<evalue.GetArrFloat2()[0].Size();jj++ )
		{
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrFloat2()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat2()[0].ValueAtIndex(jj));
		}
			
		for (int jj=0;jj<evalue.GetArrFloat3()[0].Size();jj++ )
		{
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrFloat3()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat3()[0].ValueAtIndex(jj));
		}
				
		for (int jj=0;jj<evalue.GetArrFloat4()[0].Size();jj++ )
		{
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrFloat4()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrFloat4()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrString()[0].Size();jj++ )
		{
			MonoString* monoString = Utility_CppStringToMonoString( evalue.GetArrString()[0].ValueAtIndex(jj).AsCharPtr() );
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrString()[0].KeyAtIndex(jj), MONO_TYPE_STRING,monoString);
		}

		for (int jj=0;jj<evalue.GetArrColor()[0].Size();jj++ )
		{
			Utility_SetFieldValue( _pScriptInstance, evalue.GetArrColor()[0].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & evalue.GetArrColor()[0].ValueAtIndex(jj));
		}

		for (int jj=0;jj<evalue.GetArrImagePath()[0].Size();jj++ )
		{
			Utility_SetImagePathFieldValue( _pScriptInstance, evalue.GetArrImagePath()[0].KeyAtIndex(jj), evalue.GetArrImagePath()[0].ValueAtIndex(jj), MONO_TYPE_CLASS);
		}

		for (int jj=0;jj<evalue.GetArrAssetPath()[0].Size();jj++ )
		{
			Utility_SetAssetPathFieldValue( _pScriptInstance, evalue.GetArrAssetPath()[0].KeyAtIndex(jj), evalue.GetArrAssetPath()[0].ValueAtIndex(jj), MONO_TYPE_CLASS);
		}

			
		m_arrClassNames.Insert(index, className);
		m_arrNameSpaces.Insert(index, s_csScriptRuntimeNamespace );
		m_arrAssemblyNames.Insert(index, s_csUserDefCSharpLibName );
		if (IsActive())
		{
			m_arrScriptInstances.Insert( index, _pScriptInstance );
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//------------------------------------------------------------------------------------------
	void ScriptComponent::AddCSharpScriptByIndex(const Util::String& className,int index)
	{
		TScriptInstancePtr _pScriptInstance;
		if (IsActive())
		{
			_pScriptInstance =Utility_CreateScriptInstance(className,s_csScriptRuntimeNamespace,s_csUserDefCSharpLibName );
			if ( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure thar the file name is the same with the class name,and there is no compile errors!\n  ");
			}
			else
			{
				_pScriptInstance->SetOwner( mActor );

			}
			ScriptFeature::Instance()->RemoveScript( this, m_arrScriptInstances );
		}

		m_arrClassNames.Insert(index, className);
		m_arrNameSpaces.Insert(index, s_csScriptRuntimeNamespace );
		m_arrAssemblyNames.Insert(index, s_csUserDefCSharpLibName );
		if (IsActive())
		{
			m_arrScriptInstances.Insert( index, _pScriptInstance );
			ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );
			ResetFeildValue();
			_Check_OnWillRenderObject_Rebind();
			_Check_OnRenderPostEffect_Rebind();
		}
	}
	//-------------------------------------------------------------------------
	void ScriptComponent::DestoryAllScriptInstances()
	{
		_DestoryAllScriptInstances();
		_Check_OnWillRenderObject_Rebind();
		_Check_OnRenderPostEffect_Rebind();
	}
	//------------------------------------------------------------------------
	void ScriptComponent::CreateAllScriptInstances()
	{
		_CreateAllScriptInstances();
		_Check_OnRenderPostEffect_Rebind();
		_Check_OnWillRenderObject_Rebind();
	}
	//-------------------------------------------------------------------------
	void ScriptComponent::_DestoryAllScriptInstances()
	{
		ResetFeildValue();
		if ( m_arrScriptInstances.Size()>0 )
		{
			ScriptFeature::Instance()->RemoveScript( this,m_arrScriptInstances );
			for (int i = 0;i<m_arrScriptInstances.Size();i++)
			{
				if(m_arrScriptInstances[i].isvalid())
				{
					m_arrScriptInstances[i]->Discard();
				}
				
			}
			m_arrScriptInstances.Clear();	
		}
		m_bOnLoaded = false;
	}

	//------------------------------------------------------------------------

	const Util::String& ScriptComponent::FindClassName( int index )
	{
		n_assert( index>=0 &&
			index<m_arrClassNames.Size() );

		return m_arrClassNames[index];
	}

	//------------------------------------------------------------------------
	bool ScriptComponent::GetInstanceCreationError(  Util::String& error )
	{
		bool ret = false;
		for ( int ii=0; ii<m_arrClassNames.Size(); ii++ )
		{
			TMonoScriptPtr pMonoScript = ScriptGeneralManager::Instance()->GetMonoScript( m_arrClassNames[ii], m_arrNameSpaces[ii], m_arrAssemblyNames[ii] );
			if ( !pMonoScript->IsValid() )
			{
				if (error.Length()==0||error.FindStringIndex(m_arrClassNames[ii])==-1)
				{
					error.Append(m_arrClassNames[ii]+"; ");
				}
				ret = true;
			}
		}
		return ret;
	}

#endif // #ifdef __EDITOR__
	//------------------------------------------------------------------------
	void ScriptComponent::SetProperties( const Util::TStringArray& arrClassNames,
		const Util::TStringArray& arrNameSpaces,
		const Util::TStringArray& arrAssemblyNames )
	{
		m_arrClassNames = arrClassNames;
		m_arrNameSpaces = arrNameSpaces;
		m_arrAssemblyNames = arrAssemblyNames;
	}
	//------------------------------------------------------------------------
	void ScriptComponent::SaveVer1( AppWriter* pWriter )const
	{
		// - serialize loading params
		Util::String _sClassName;
		Util::String _sNameSpace;
		Util::String _sAssemblyName;
		for ( int ii=0; ii<m_arrClassNames.Size(); ii++ )
		{
			_sClassName    += m_arrClassNames[ii]    + " ";
			_sNameSpace    += m_arrNameSpaces[ii]    + " ";
			_sAssemblyName += m_arrAssemblyNames[ii] + " ";
		}

		pWriter->SerializeString( s_csScriptSerialize_ClassName.AsCharPtr() , _sClassName );
		pWriter->SerializeString( s_csScriptSerialize_NameSpace.AsCharPtr() , _sNameSpace );
		pWriter->SerializeString( s_csScriptSerialize_AssemblyName.AsCharPtr() , _sAssemblyName );
	}
	//------------------------------------------------------------------------
	void ScriptComponent::SaveVer2( AppWriter* pWriter )const
	{
		// - serialize loading params
		SaveVer1( pWriter );

		// - serialize instance count
		int iInsSize = m_arrClassNames.Size();
		pWriter->SerializeInt( s_csScriptSerialize_InstanceCount.AsCharPtr(), iInsSize );

		// - begin serialize!
		for ( int ii=0; ii<iInsSize; ii++ )
		{			
			int iFieldCount	= 0;
				
			if (m_fieldValue.GetArrFloat().Size()==0)
			{
				iFieldCount = 0;
				pWriter->SerializeInt( s_csScriptSerialize_FieldCount.AsCharPtr(), iFieldCount );
				return;
			}
			else
			{
				iFieldCount = m_fieldValue.GetArrFloat()[ii].Size()+m_fieldValue.GetArrInt()[ii].Size()+
					m_fieldValue.GetArrString()[ii].Size()+m_fieldValue.GetArrFloat2()[ii].Size()+
					m_fieldValue.GetArrFloat3()[ii].Size()+m_fieldValue.GetArrFloat4()[ii].Size()+
					m_fieldValue.GetArrColor()[ii].Size() + m_fieldValue.GetArrImagePath()[ii].Size() + 
					m_fieldValue.GetArrAssetPath()[ii].Size();

				pWriter->SerializeInt( s_csScriptSerialize_FieldCount.AsCharPtr(), iFieldCount );
			}

			

			for ( int jj=0; jj<m_fieldValue.GetArrInt()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrInt()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_I4 );
				pWriter->SerializeInt( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrInt()[ii].ValueAtIndex(jj) );
			}

			for ( int jj=0; jj<m_fieldValue.GetArrFloat()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrFloat()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_R4 );
				pWriter->SerializeFloat( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrFloat()[ii].ValueAtIndex(jj) );
				
			}

			for ( int jj=0; jj<m_fieldValue.GetArrString()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrString()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_STRING );
				pWriter->SerializeString( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrString()[ii].ValueAtIndex(jj) );	
			}

			for ( int jj=0; jj<m_fieldValue.GetArrFloat2()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrFloat2()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_VALUETYPE );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csFloat2ClassName );
				pWriter->SerializeFloat2( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrFloat2()[ii].ValueAtIndex(jj) );			
			}

			for ( int jj=0; jj<m_fieldValue.GetArrFloat3()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrFloat3()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_VALUETYPE );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csFloat3ClassName );
				pWriter->SerializeFloat3( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrFloat3()[ii].ValueAtIndex(jj) );	
			}

			for ( int jj=0; jj<m_fieldValue.GetArrFloat4()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrFloat4()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_VALUETYPE );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csFloat4ClassName );
				pWriter->SerializeFloat4( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrFloat4()[ii].ValueAtIndex(jj) );
			}

			for ( int jj=0; jj<m_fieldValue.GetArrColor()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrColor()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_VALUETYPE );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csColor32ClassName );
				pWriter->SerializeColor32( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrColor()[ii].ValueAtIndex(jj) );
			}

			for ( int jj=0; jj<m_fieldValue.GetArrImagePath()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrImagePath()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_CLASS );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csImagePathClassName );
				pWriter->SerializeString( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrImagePath()[ii].ValueAtIndex(jj) );
			}

			for ( int jj=0; jj<m_fieldValue.GetArrAssetPath()[ii].Size(); jj++ )
			{					
				pWriter->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), m_fieldValue.GetArrAssetPath()[ii].KeyAtIndex(jj) );
				pWriter->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), MONO_TYPE_CLASS );
				pWriter->SerializeString( s_csUserDefClassName.AsCharPtr(), s_csAssetPathClassName );
				pWriter->SerializeAssetPath( s_csScriptSerialize_FieldValue.AsCharPtr(), m_fieldValue.GetArrAssetPath()[ii].ValueAtIndex(jj) );
			}
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::LoadVer1( AppReader* pReader )
	{
		Util::String _sClassName;
		pReader->SerializeString( s_csScriptSerialize_ClassName.AsCharPtr(), _sClassName );
		int iScriptCount = _sClassName.Tokenize( " ",m_arrClassNames );

		Util::String _sNameSpace;
		pReader->SerializeString( s_csScriptSerialize_NameSpace.AsCharPtr(), _sNameSpace );
		int iNameSpaceCount = _sNameSpace.Tokenize( " ",m_arrNameSpaces );
		script_fatal_error(iNameSpaceCount == iScriptCount);

		Util::String _sAssemblyName;
		pReader->SerializeString( s_csScriptSerialize_AssemblyName.AsCharPtr(), _sAssemblyName );
		int iAssemblyCount = _sAssemblyName.Tokenize( " ", m_arrAssemblyNames );	
		script_fatal_error(iAssemblyCount == iScriptCount);

		m_fieldValue.Clear();
		for ( int ii=0; ii<iScriptCount; ii++ )
		{
			m_fieldValue.GrowAllArray();
		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::LoadVer2( AppReader* pReader )
	{
		// - load ver 1 data
		LoadVer1( pReader );

		// - serialize instance params
		int iInstanceSize = 0;
		pReader->SerializeInt( s_csScriptSerialize_InstanceCount.AsCharPtr(), iInstanceSize );

		for ( int ii=0; ii<iInstanceSize; ii++ )
		{
			int iFieldCount = 0;
			pReader->SerializeInt( s_csScriptSerialize_FieldCount.AsCharPtr(), iFieldCount );

			
			for ( int jj=0; jj<iFieldCount; jj++ )
			{
				Util::String sFieldName;
				int type = 0;
				pReader->SerializeString( s_csScriptSerialize_FieldName.AsCharPtr(), sFieldName );
				pReader->SerializeInt( s_csScriptSerialize_FieldType.AsCharPtr(), type );
							
				switch ( type )
				{
				case MONO_TYPE_I4:
					{
						int value = 0;
						pReader->SerializeInt( s_csScriptSerialize_FieldValue.AsCharPtr(), value );
						m_fieldValue.AddInt(ii,sFieldName,value);						
						break;
					}
				case MONO_TYPE_STRING:
					{
						Util::String value;
						pReader->SerializeString( s_csScriptSerialize_FieldValue.AsCharPtr(), value );
						m_fieldValue.AddString(ii,sFieldName,value);						
						break;
					}
				case MONO_TYPE_R4:
					{
						float value = 0;
						pReader->SerializeFloat( s_csScriptSerialize_FieldValue.AsCharPtr(), value );
						m_fieldValue.AddFloat(ii,sFieldName,value);					
						break;
					}
				case MONO_TYPE_VALUETYPE:
					{

						Util::String className; 						
						pReader->SerializeString(s_csUserDefClassName.AsCharPtr(), className );

						if( className==s_csFloat2ClassName)
						{
							Math::float2 f2;
							pReader->SerializeFloat2(s_csScriptSerialize_FieldValue.AsCharPtr(),f2);
							m_fieldValue.AddFloat2(ii,sFieldName,f2);
 							
						}
						else if( className==s_csFloat3ClassName)
						{
							Math::float3 f3;
							pReader->SerializeFloat3(s_csScriptSerialize_FieldValue.AsCharPtr(),f3);
							m_fieldValue.AddFloat3(ii,sFieldName,f3);

						}
						else if (className==s_csFloat4ClassName)
						{
							Math::float4 f4;
							pReader->SerializeFloat4(s_csScriptSerialize_FieldValue.AsCharPtr(),f4);
							m_fieldValue.AddFloat4(ii,sFieldName,f4);
						}
						else if( className == s_csColor32ClassName)
						{
							Math::Color32 color32;
							pReader->SerializeColor32(s_csScriptSerialize_FieldValue.AsCharPtr(),color32);
							m_fieldValue.AddColor32(ii,sFieldName, color32);
						}
						break;
					}
				case MONO_TYPE_CLASS:
					{
						Util::String className; 						
						pReader->SerializeString(s_csUserDefClassName.AsCharPtr(), className );

						if( className == s_csImagePathClassName )
						{
							Util::String str;
							pReader->SerializeString( s_csScriptSerialize_FieldValue.AsCharPtr(),str);
							m_fieldValue.AddImagePath( ii, sFieldName, str);
						}
						else if( className == s_csAssetPathClassName )
						{
							Util::AssetPath assetPath;
							pReader->SerializeAssetPath( s_csScriptSerialize_FieldValue.AsCharPtr(), assetPath);
							m_fieldValue.AddAssetPath( ii, sFieldName, assetPath);
						}
						break;
					}
				default:
					continue;

				}
			}

		}
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_CreateAllScriptInstances()
	{
		if (!m_arrScriptInstances.IsEmpty())
		{
			n_printf("instances already exits!");
			return;
		}
		for ( int ii=0; ii<m_arrClassNames.Size(); ii++ )
		{
			TScriptInstancePtr _pScriptInstance = Utility_CreateScriptInstance( m_arrClassNames[ii], m_arrNameSpaces[ii], m_arrAssemblyNames[ii] );

			m_arrScriptInstances.Append( _pScriptInstance );
			
#ifdef __GENESIS_EDITOR__
			if ( !_pScriptInstance.isvalid() )
			{
				n_warning("Script instance creation failed! Please make sure thar the file name is the same with the class name,and there is no compile errors!\n");
				continue;
			}
#endif
			if ( m_fieldValue.GetArrInt().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrInt()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrInt()[ii].KeyAtIndex(jj), MONO_TYPE_I4, & m_fieldValue.GetArrInt()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrFloat().Size()>ii )
			{
				for (int jj=0;jj< m_fieldValue.GetArrFloat()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrFloat()[ii].KeyAtIndex(jj), MONO_TYPE_R4, & m_fieldValue.GetArrFloat()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrFloat2().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrFloat2()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrFloat2()[ii].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & m_fieldValue.GetArrFloat2()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrFloat3().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrFloat3()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrFloat3()[ii].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & m_fieldValue.GetArrFloat3()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrFloat4().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrFloat4()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrFloat4()[ii].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & m_fieldValue.GetArrFloat4()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrColor().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrColor()[ii].Size();jj++ )
				{
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrColor()[ii].KeyAtIndex(jj), MONO_TYPE_VALUETYPE, & m_fieldValue.GetArrColor()[ii].ValueAtIndex(jj));
				}
			}

			if ( m_fieldValue.GetArrString().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrString()[ii].Size();jj++ )
				{
					MonoString* monoString = Utility_CppStringToMonoString( m_fieldValue.GetArrString()[ii].ValueAtIndex(jj).AsCharPtr() );
					Utility_SetFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrString()[ii].KeyAtIndex(jj), MONO_TYPE_STRING,monoString);
				}
			}

			if ( m_fieldValue.GetArrImagePath().Size()>ii )
			{
				for (int jj=0;jj<m_fieldValue.GetArrImagePath()[ii].Size();jj++ )
				{
					Utility_SetImagePathFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrImagePath()[ii].KeyAtIndex(jj),
						m_fieldValue.GetArrImagePath()[ii].ValueAtIndex(jj), MONO_TYPE_CLASS);
				}
			}

			if ( m_fieldValue.GetArrAssetPath().Size()>ii )
			{

				for (int jj=0;jj<m_fieldValue.GetArrAssetPath()[ii].Size();jj++ )
				{
					Utility_SetAssetPathFieldValue( m_arrScriptInstances[ii], m_fieldValue.GetArrAssetPath()[ii].KeyAtIndex(jj),
						m_fieldValue.GetArrAssetPath()[ii].ValueAtIndex(jj), MONO_TYPE_CLASS);
				}
			}
		}

		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			TScriptInstancePtr& instancePtr = m_arrScriptInstances[ii];
			if (instancePtr.isvalid())
			{
				instancePtr->SetOwner( mActor );
			}
			
		}
		
		ScriptFeature::Instance()->AttachScript( this, m_arrScriptInstances );

		AssignFeildValue();
	}
	//------------------------------------------------------------------------
	void ScriptComponent::_SetActor( Actor* v )
	{
		Super::_SetActor(v);
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			m_arrScriptInstances[ii]->SetOwner( mActor );
		}
	}

	void ScriptComponent::ResetFeildValue()
	{
		m_fieldValue.Clear();

		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			m_fieldValue.GrowAllArray();

			int iFieldCount = 0;
			if ( m_arrScriptInstances[ii].isvalid())
			{
				iFieldCount = Utility_GetEditableFieldCount( m_arrScriptInstances[ii] );
			}
		
			for ( int jj=0; jj<iFieldCount; jj++ )
			{
				MonoObject* pMonoObj		= m_arrScriptInstances[ii]->GetMonoInstance();
				MonoClassField* pClassField = Utility_GetEditableField( m_arrScriptInstances[ii], jj );
				const char* pFieldName		= Utility_GetFieldName( pClassField );
				int iType					= Utility_GetFieldType( pClassField );
				Util::String sFieldName( pFieldName );

				switch ( iType )
				{
				case MONO_TYPE_I4:
					{
						int32 value = Utility_GetFieldBuiltInTypeValue<int32>( pMonoObj, pClassField );								
						m_fieldValue.AddInt(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_STRING:
					{
						Util::String value = Utility_GetFieldStringValue( pMonoObj, pClassField );
						m_fieldValue.AddString(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_R4:
					{
						float32 value = Utility_GetFieldBuiltInTypeValue<float32>( pMonoObj, pClassField );								
						m_fieldValue.AddFloat(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_VALUETYPE:
					{
						Util::String className = Utility_GetTypeClassName(pClassField);
						if( className==s_csFloat2ClassName)
						{
							Math::float2 value = Utility_GetFieldBuiltInTypeValue<Math::float2>( pMonoObj, pClassField );
							m_fieldValue.AddFloat2(ii,sFieldName,value);
						}
						else if( className==s_csFloat3ClassName)
						{
							Math::float3 value = Utility_GetFieldBuiltInTypeValue<Math::float3>( pMonoObj, pClassField );
							m_fieldValue.AddFloat3(ii,sFieldName,value);
						}
						else if (className==s_csFloat4ClassName)
						{
							Math::float4 value = Utility_GetFieldBuiltInTypeValue<Math::float4>( pMonoObj, pClassField );
							m_fieldValue.AddFloat4(ii,sFieldName,value);
						}
						else if( className == s_csColor32ClassName )
						{
							Math::Color32 value = Utility_GetFieldBuiltInTypeValue<Math::Color32>( pMonoObj, pClassField);
							m_fieldValue.AddColor32(ii,sFieldName,value);
						}
						break;
					}
				case MONO_TYPE_CLASS:
					{
						Util::String className = Utility_GetTypeClassName(pClassField);
						if( className == s_csImagePathClassName )
						{
							Util::String value = Utility_GetFieldImagePathValue( pMonoObj, pClassField);
							m_fieldValue.AddImagePath( ii, sFieldName, value);
						}
						else if( className == s_csAssetPathClassName )
						{
							Util::AssetPath assetPath = Utility_GetFieldAssetPathValue( pMonoObj, pClassField);
							m_fieldValue.AddAssetPath( ii, sFieldName, assetPath);
						}
						break;
					}
				default:
					continue;
				}
			}

		}
	}

	void ScriptComponent::AssignFeildValue()
	{
		for ( int ii=0; ii<m_arrScriptInstances.Size(); ii++ )
		{
			int iFieldCount = 0;
			if ( m_arrScriptInstances[ii].isvalid())
			{
				iFieldCount = Utility_GetEditableFieldCount( m_arrScriptInstances[ii] );
			}
			m_fieldValue.AssignAll(ii);
			for ( int jj=0; jj<iFieldCount; jj++ )
			{
				MonoObject* pMonoObj		= m_arrScriptInstances[ii]->GetMonoInstance();
				MonoClassField* pClassField = Utility_GetEditableField( m_arrScriptInstances[ii], jj );
				const char* pFieldName		= Utility_GetFieldName( pClassField );
				int iType					= Utility_GetFieldType( pClassField );
				Util::String sFieldName( pFieldName );
				
				switch ( iType )
				{
				case MONO_TYPE_I4:
					{
						int32 value = Utility_GetFieldBuiltInTypeValue<int32>( pMonoObj, pClassField );								
						m_fieldValue.AssignInt(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_STRING:
					{
						Util::String value = Utility_GetFieldStringValue( pMonoObj, pClassField );
						m_fieldValue.AssignString(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_R4:
					{
						float32 value = Utility_GetFieldBuiltInTypeValue<float32>( pMonoObj, pClassField );								
						m_fieldValue.AssignFloat(ii,sFieldName,value);
						break;
					}
				case MONO_TYPE_VALUETYPE:
					{
						Util::String className = Utility_GetTypeClassName(pClassField);
						if( className==s_csFloat2ClassName)
						{
							Math::float2 value = Utility_GetFieldBuiltInTypeValue<Math::float2>( pMonoObj, pClassField );
							m_fieldValue.AssignFloat2(ii,sFieldName,value);
						}
						else if( className==s_csFloat3ClassName)
						{
							Math::float3 value = Utility_GetFieldBuiltInTypeValue<Math::float3>( pMonoObj, pClassField );
							m_fieldValue.AssignFloat3(ii,sFieldName,value);
						}
						else if (className==s_csFloat4ClassName)
						{
							Math::float4 value = Utility_GetFieldBuiltInTypeValue<Math::float4>( pMonoObj, pClassField );
							m_fieldValue.AssignFloat4(ii,sFieldName,value);
						}
						else if( className == s_csColor32ClassName )
						{
							Math::Color32 value = Utility_GetFieldBuiltInTypeValue<Math::Color32>( pMonoObj, pClassField );
							m_fieldValue.AssignColor32(ii,sFieldName,value);
						}
						break;
					}
				case MONO_TYPE_CLASS:
					{
						Util::String className = Utility_GetTypeClassName(pClassField);
						if( className == s_csImagePathClassName )
						{
							Util::String value = Utility_GetFieldImagePathValue( pMonoObj, pClassField);
							m_fieldValue.AssignImagePath( ii, sFieldName, value);
						}
						else if( className == s_csAssetPathClassName )
						{
							Util::AssetPath value = Utility_GetFieldAssetPathValue( pMonoObj, pClassField);
							m_fieldValue.AssignAssetPath( ii, sFieldName, value);
						}
						break;
					}
				default:
					continue;
				}
			}

		}
	}

	void ScriptComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		Super::GetReferenceResourceId(list);
	}
}
