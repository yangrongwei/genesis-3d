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
#ifndef _script_message_
#define _script_message_
#include "script_fwd_decl.h"
#include "script_utility.h"
#include "foundation/core/singleton.h"
#include "foundation/util/string.h"
#include "foundation/util/assetpath.h"
#include "foundation/util/dictionary.h"
#include "messaging/message.h"
#include "app/physXfeature/UserReport.h"

namespace App
{
	class ScriptMessage: public Messaging::Message
	{
		__DeclareClass(ScriptMessage);
		__DeclareMsgId;
		public:
			ScriptMessage()
			{}
			~ScriptMessage()
			{
				m_param = NULL;
			}
			
			GPtr<UserReportPair> GetParam()
			{
				return m_param;
			}
			
			Util::String& GetName()
			{
				return m_name;
			}

			MonoObject* GetMonoParam();
							
		protected:
			void SetParam(UserReportPair& pair)
			{	
				m_param = &pair;
			}

			void SetName(const Util::String& name)
			{
				m_name = name;
			}
			
			GPtr<UserReportPair> m_param;//to store this smartptr in order to avoid the release of the param ; 
			Util::String    m_name;
			
			friend class ScriptMessageCreator;
			
		private:

	};

	struct SigAndRtti
	{
		Util::String	mSig;
		Core::Rtti*		mParamRtti;
	};

	class ScriptMessageCreator:public Core::RefCounted
	{
		__DeclareSubClass( App::ScriptMessageCreator, Core::RefCounted );
		__DeclareImageSingleton( App::ScriptMessageCreator );   
	public:
		ScriptMessageCreator():
			m_diNameToSig()
		   ,m_dicNameToParamRtti()
		{ __ConstructImageSingleton; }

		~ScriptMessageCreator()
		{
			m_diNameToSig.Clear();
			m_dicNameToParamRtti.Clear();
			__DestructImageSingleton;
		}

		template<typename T> 
		TScriptMessagePtr CreateMessage(const Util::String& event,T& pair);

		void RegistMsg(Util::String& sEventName,Util::String& sSig,Core::Rtti* rpParam);

		const Util::String& GetNameByIndex(int index);
		Util::String& GetSigByName(const Util::String& name);
		Core::Rtti*  GetRttiByName(const Util::String& name);
		/// how many messages we have
		int GetMessageCount();
		// - static functions
		/// create singleton 
		static void CreateSingleton( void );
		/// destroy singleton 
		static void DestorySingleton( void );
	private:
		Util::Dictionary<Util::String, Util::String> m_diNameToSig;
		Util::Dictionary<Util::String, Core::Rtti*>   m_dicNameToParamRtti;
	};

	template<typename T>
	TScriptMessagePtr ScriptMessageCreator::CreateMessage(const Util::String& name,T& pair )
	{
		TScriptMessagePtr ptrSMI= ScriptMessage::Create();
		Core::Rtti* rtti = ScriptMessageCreator::Instance()->GetRttiByName(name);
		
		if ( rtti != &(T::RTTI) )
		{
			n_error("this event's param' type is not what you give");
		}
#ifndef __APP_BUILD_COMMIT__
		ptrSMI->SetParam(pair);
#endif
	
		ptrSMI->SetName(name);

		return ptrSMI;
	}

	inline int ScriptMessageCreator::GetMessageCount()
	{
		return m_diNameToSig.Size();
	}
}
#endif // _script_message_
