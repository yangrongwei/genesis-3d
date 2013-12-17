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
#include "ALSystemFeature/GameIap.h"
#include "scriptfeature/script_IAP_instance.h"
namespace App
{

__ImplementClass(App::GameIap, 'GIAP', NALSystem::InAppPurchase);
__ImplementImageSingleton(App::GameIap);
GameIap::GameIap()
{
	__ConstructImageSingleton;
    mTime = 0;
    
};

GameIap::~GameIap()
{
    __DestructImageSingleton;
};

bool GameIap::Init()
{
    NALSystem::ALSystem::getInstance()->storeKitAddTransactionObserver(this);
	mSussMap.Clear();
    return true;
};

void GameIap::onStoreKitGetProductPrice(Util::Dictionary<Util::String, Util::String> & idAndPrice)
{
	// 返回数据给脚本
	ScriptIAPInstance::Instance()->onStoreKitGetProductPrice(idAndPrice);
    
};

void GameIap::onStoreKitValidateProductIDFailed(  const Util::String &   invalidProductIdentifiers)
{
	ScriptIAPInstance::Instance()->onStoreKitValidateProductIDFailed(invalidProductIdentifiers);
	
	// ALStoreKit had print log about invalidProductIdentifiers
	NALSystem::ALSystem::getInstance()->storeKitFinishTransaction(invalidProductIdentifiers);
};

void GameIap::onStoreKitPurchaseFailedWithError(const Util::String & productIdentifier,
                                       const Util::String & transactionIdentifier,
                                       NALSystem::ALSystem::SK_ERROR errorType,
                                       const Util::String & error)
{
	ScriptIAPInstance::Instance()->onStoreKitPurchaseFailedWithError(productIdentifier,transactionIdentifier,errorType,error);

   // ALStoreKit had print log about this case
    NALSystem::ALSystem::getInstance()->storeKitFinishTransaction(transactionIdentifier);
};

void GameIap::onStoreKitPurchaseSucceed(const Util::String & productIdentifier,
                               const Util::String & transactionIdentifier,
                               const Util::String & transactionReceipt)
{
	/*receipt verify to be coninue....
	//流程：
	//		拿着sk返回的receipt再去appStore做验证，但我们的iap是build-in，而不是server-base，因此没必要这样做
	*/

	
};





void GameIap::RemoveIAPId(Util::String transactionId)
{

}

void GameIap::EndPayment(Util::String strTranscation)
{

	NALSystem::ALSystem::getInstance()->storeKitFinishTransaction(strTranscation);

}

bool GameIap::IsHasIAPId(Util::String productId)
{
	return false;
}

void GameIap::test(Util::String productId)
{
    Util::Array<Util::String> priceMap;
    priceMap.Append(productId);  
    NALSystem::ALSystem::getInstance()->storeKitStartPurchaseProducts(priceMap);    

}

void GameIap::onTick()
{
	//对已交易成功的receipt 进行验证  
}

void GameIap::RequestProductInfo(const Util::String& productID )
{
	n_printf("[IAP] RequestProductInfo pid:%s",productID.Get());
	 Util::Array<Util::String> priceMap;
	 priceMap.Append(productID);
	 NALSystem::ALSystem::getInstance()->storeKitRequestPrice(priceMap);
}
void GameIap::BuyProduct(const Util::String& productID )
{
	n_printf("[IAP] BuyProduct pid:%s",productID.Get());
	Util::Array<Util::String> priceMap;
	priceMap.Append(productID);
	NALSystem::ALSystem::getInstance()->storeKitStartPurchaseProducts(priceMap);
}


}