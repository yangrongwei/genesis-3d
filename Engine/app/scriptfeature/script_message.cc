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
#include "scriptfeature/mono_script.h"
#include "inc/script_message.h"
#include "../physXfeature/PhysicsBodyComponent.h"

//------------------------------------------------------------------------------
namespace App
{
//------------------------------------------------------------------------------
	__ImplementClass(App::ScriptMessage, 'SMID', Messaging::Message);
	__ImplementMsgId(ScriptMessage);

	
	__ImplementClass( App::ScriptMessageCreator, 'SMCT', Core::RefCounted );
	__ImplementImageSingleton( App::ScriptMessageCreator );

	//------------------------------------------------------------------------
	void ScriptMessageCreator::RegistMsg(Util::String& sEventName,Util::String& sSig,Core::Rtti* rpParam)
	{
		m_diNameToSig.Add(sEventName,sSig);
		m_dicNameToParamRtti.Add(sEventName,rpParam);
	}
	//------------------------------------------------------------------------
	Util::String& ScriptMessageCreator::GetSigByName(const Util::String& name )
	{
		return m_diNameToSig[name];
	}
	//------------------------------------------------------------------------
	Core::Rtti* ScriptMessageCreator::GetRttiByName(const Util::String& name )
	{	
		return m_dicNameToParamRtti[name];
	}
	//------------------------------------------------------------------------
	const Util::String& ScriptMessageCreator::GetNameByIndex( int index )
	{
		return m_diNameToSig.KeyAtIndex(index);
	}
	//------------------------------------------------------------------------
	void ScriptMessageCreator::CreateSingleton( void )
	{
		ScriptMessageCreator::Create();
		ScriptMessageCreator::Instance()->AddRef();
	}
	//------------------------------------------------------------------------
	void ScriptMessageCreator::DestorySingleton( void )
	{
		ScriptMessageCreator::Instance()->Release();
	}
	//------------------------------------------------------------------------
	MonoObject* ScriptMessage::GetMonoParam()
	{
		Core::Rtti* rtti = ScriptMessageCreator::Instance()->GetRttiByName(m_name);
		MonoObject* pObj = NULL ;
		pObj = CppObjectToScriptObj<UserReportPair>(*m_param);
		Util::String strClassName = m_param->GetRtti()->GetName();
		MonoMethod* pMethod = MonoScript::GetMethodByName("*:SetValue(PhysicsBodyComponent,PhysicsBodyComponent)",Utility_GetRuntimeMonoClass(strClassName));
		MonoObject* pFirstBodyCom = NULL,*pSecondBodyCom = NULL;
		if(m_param->first)
		{
			App::PhysicsBodyComponent* pBody = (App::PhysicsBodyComponent*)m_param->first;
			pFirstBodyCom = CppObjectToScriptObj<App::PhysicsBodyComponent>(*pBody);
		}
		if(m_param->second)
		{
			App::PhysicsBodyComponent* pBody = (App::PhysicsBodyComponent*)m_param->first;
			pSecondBodyCom = CppObjectToScriptObj<App::PhysicsBodyComponent>(*pBody);
		}
		void *Param[2]={pFirstBodyCom,pSecondBodyCom};
		Utility_MonoRuntimeInvoke(pMethod,pObj,Param);
		return pObj;
	}
}
namespace Commands
{
} // namespace Commands
//------------------------------------------------------------------------------
