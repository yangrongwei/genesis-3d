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
#ifndef __script_IAP_instance_H__
#define __script_IAP_instance_H__

#include "foundation/core/refcounted.h"
#include "foundation/util/scriptbind.h"
#include "foundation/util/monoapi.h"
#include "app/scriptfeature/inc/script_fwd_decl.h"
#include "appframework/app_fwd_decl.h"
#include "foundation/core/singleton.h"
#include "addons/ALSystem/ALSystem.h"

namespace App
{
	class ScriptIAPInstance : public Core::RefCounted
	{
		__DeclareSubClass( App::ScriptIAPInstance, Core::RefCounted );
		/// this is a singleton class
		__DeclareImageSingleton( App::ScriptIAPInstance );
	public:
		virtual ~ScriptIAPInstance();

		static void CreateSingleton();
		static void DestorySingleton();
		
		void Init();

		void onStoreKitValidateProductIDFailed(   const Util::String &   invalidProductIdentifiers  );
		void onStoreKitPurchaseFailedWithError(const Util::String & productIdentifier,
			const Util::String & transactionIdentifier,
			NALSystem::ALSystem::SK_ERROR errorType,
			const Util::String & error);
		void onStoreKitPurchaseSucceed(const Util::String & productIdentifier,
			const Util::String & transactionIdentifier,
			const Util::String & transactionReceipt);

		void onStoreKitGetProductPrice(Util::Dictionary<Util::String, Util::String> & idAndPrice);

		MonoObject* GetMonoObj();

		static const Util::String& s_csDerivedClassName;
		static const Util::String& s_csBaseClassName;
	private:
		ScriptIAPInstance();
		void GetEntryMethods();

		MonoClass*			m_pRootClass;				///< - mono class
		MonoObject*			m_pRootObj;					///< - mono object on script side
		uint32				m_uiRootRefID;				///< - mono ref id
		TMonoScriptPtr		m_pMonoScript;				///< - mono script which init this class
		TMonoMethodArray	m_ArrEntryMethods;			///< - methods which will be call by engine
		bool                m_bInit;					///< - to check if this class had already be inited
	};

	inline MonoObject* ScriptIAPInstance::GetMonoObj()
	{
		return m_pRootObj;
	}
}

#endif // - __SCRIPT_ROOT_INSTANCE_H__
