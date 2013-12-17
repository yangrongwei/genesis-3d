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
#ifndef __SCRIPT_INSTANCE_H__
#define __SCRIPT_INSTANCE_H__

#include "foundation/core/refcounted.h"
#include "foundation/util/scriptbind.h"
#include "foundation/util/monoapi.h"
#include "app/scriptfeature/inc/script_fwd_decl.h"
#include "appframework/app_fwd_decl.h"
//#include "app/physXfeature/PhysicsShapeComponent.h"
#include "app/scriptfeature/inc/script_message.h"

namespace Graphic
{
	class RenderToTexture;
}

namespace App
{
	class RenderComponent;
	class CameraComponent;
	/*
	* instantiate a mono script,use this class to run a script
	*/
	class ScriptInstance : public Core::RefCounted
	{
		__DeclareSubClass( App::ScriptInstance, Core::RefCounted );
		__ScriptBind
	public:
		/// constructor
		ScriptInstance()
			: m_pOwner( NULL )
			, m_pArrEntryMethods( NULL )
			, m_pMonoObj( NULL )
			, m_pDicMethods( NULL )
			, m_pMonoScript()
			, m_sName()
			, m_pDicRegistedMessageHandler( NULL )
			, m_Ref(0)
		{}
		/// destructor
		virtual ~ScriptInstance();
		/// if this class has been init
		bool IsInit( void );
		/// Discard this obj
		void Discard();
		/// if a method had been writed in user's class.
		bool IsScriptMethodExist(EEntryMethodIndex methodIndex);
		/// get owner actor
		Actor* GetOwner( void );
		/// initialize this class from a script
		bool Init( const TMonoScriptPtr& pMonoScript );
		/// set owner actor of this instance
		void SetOwner( Actor* pOwner );
		/// get mono script
		MonoScript* GetMonoScript( void );
		/// Call mono method , use mono_runtime_invoke internally.
		MonoObject* CallMethod( const char* methodName, void** params );
		/// call script function "OnBeginFrame"
		void OnBeginFrame( void );
		/// call script function "OnFrame"
		void OnFrame( void );
		/// call script function "OnEndFrame"
		void OnEndFrame( void );
		/// call script function "OnLoad"
		void OnLoad( void );
		/// call script function "OnExit"
		void OnExit( void );
		/// call script function "OnStopped"
		void OnStopped( void );
		/// call script function "OnResumed"
		void OnResumed( void );
		/// call script function "OnWillRenderObject"
		void OnWillRenderObject( RenderComponent* renderComponent );
		/// call script function "OnRenderPostEffect"
		bool OnRenderPostEffect(CameraComponent* camera, Graphic::RenderToTexture* source, Graphic::RenderToTexture* destination);
		/// get name
		const Util::String& GetName() const; 
		/// set name
		void SetName( const Util::String& name ); 
		/// get c# instance
		MonoObject* GetMonoInstance();
		/// throw the msg to the script side
		void HandleMessage( const TScriptMessagePtr& msg );
	private:
		MonoObject* invokeScript(EEntryMethodIndex methodIndex, void** params = NULL);

		Actor*				m_pOwner;					///< - owner of this script					
		TMonoMethodArray*	m_pArrEntryMethods;			///< - methods which will be call by engine
		TMonoMethodMap*	    m_pDicMethods;				///< - all method of a script, get from mono script,temp code
		MonoObject*			m_pMonoObj;					///< - script instance on Mono side	
		TMonoScriptPtr		m_pMonoScript;				///< - mono script which init this class
		Util::String        m_sName;					///< - name of the script on script side
		ScriptMessageHandlerMap*   m_pDicRegistedMessageHandler;  ///< - pointer to a recored registered message handler map

		int m_Ref;
	};

	// - implement of inline function
	inline bool ScriptInstance::IsInit( void )
	{
		return ( (NULL!=m_pOwner) && (NULL!=m_pMonoObj) );
	}
	//------------------------------------------------------------------------
	inline Actor* ScriptInstance::GetOwner( void )
	{
		return m_pOwner;
	}
	//------------------------------------------------------------------------
	inline MonoScript* ScriptInstance::GetMonoScript( void )
	{
		return m_pMonoScript.get();
	}
	//------------------------------------------------------------------------
	inline const Util::String& ScriptInstance::GetName() const 
	{
		return m_sName; 
	}
	//------------------------------------------------------------------------
	inline void ScriptInstance::SetName( const Util::String& name )
	{ 
		m_sName = name; 
	}
	//------------------------------------------------------------------------
	inline MonoObject* ScriptInstance::GetMonoInstance()
	{
		return m_pMonoObj;
	}
	//------------------------------------------------------------------------
	inline bool ScriptInstance::IsScriptMethodExist(EEntryMethodIndex methodIndex)
	{
		if ( IsInit() )
		{		
			MonoMethod* pMethod = m_pArrEntryMethods->operator[]( methodIndex );
			return NULL != pMethod;
		}
		return false;
	}
	//------------------------------------------------------------------------
	inline MonoObject* ScriptInstance::invokeScript(EEntryMethodIndex methodIndex, void** params /* = NULL */)
	{
		if ( IsInit() )
		{		
			MonoMethod* pMethod = m_pArrEntryMethods->operator[]( methodIndex );
			if ( pMethod )
			{
				return Utility_MonoRuntimeInvoke( pMethod, m_pMonoObj, params );
			}
		}
		return NULL;
	}
}

#endif // - __SCRIPT_INSTANCE_H__
