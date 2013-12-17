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
#ifndef __GameIap_H__
#define __GameIap_H__

#include "core/singleton.h"
#include "../addons/ALSystem/ALSystem.h"
#include "../addons/ALSystem/InAppPurchase.h"

namespace App
{
	struct Transcation
	{
		Util::String m_pid;
		Util::String m_tid;
		Util::String m_recipt;
		Transcation(Util::String pid,Util::String tid,Util::String recipt)
		{
			m_pid = pid;
			m_tid = tid;
			m_recipt = recipt;
		}
	};

	typedef Util::Dictionary<Util::String,Transcation*> sussTranscationMap;

	class GameIap : public NALSystem::InAppPurchase, NALSystem::ALSystem::ALStoreKitListener
	{
		__DeclareClass(GameIap);
		__DeclareImageSingleton(GameIap);
	public:

		GameIap();
		virtual ~GameIap();

		bool Init();

		//导出接口////////////////////////////////////////////////////////////////////////

		virtual void onStoreKitValidateProductIDFailed(   const Util::String &   invalidProductIdentifiers  );

		virtual void onStoreKitPurchaseFailedWithError(const Util::String & productIdentifier,
			const Util::String & transactionIdentifier,
			NALSystem::ALSystem::SK_ERROR errorType,
			const Util::String & error);
		virtual void onStoreKitPurchaseSucceed(const Util::String & productIdentifier,
			const Util::String & transactionIdentifier,
			const Util::String & transactionReceipt);

		virtual void onStoreKitGetProductPrice(Util::Dictionary<Util::String, Util::String> & idAndPrice);


		virtual void RequestProductInfo(const Util::String& productID );
		virtual void BuyProduct(const Util::String& productID );

		//server-base的预留接口////////////////////////////////////////////////////////////////////////	

		void test(Util::String productId);	
		void RemoveIAPId(Util::String productId);
		bool IsHasIAPId(Util::String productId);
		void EndPayment(Util::String strTranscation);
		sussTranscationMap mSussMap;
		void onTick();


	private:
		float mTime;

	};
}

#endif
