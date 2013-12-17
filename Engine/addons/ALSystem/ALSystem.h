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

#ifndef __ALSystem_H__
#define __ALSystem_H__

#include "core/refcounted.h"
#include "util/string.h"
#include "util/dictionary.h"
#include "util/array.h"
namespace NALSystem
{



class ALSystem : public Core::RefCounted
{
	__DeclareAbstractClass(ALSystem);
private:
	static GPtr<ALSystem> m_spALSystem;
	friend class ALSystemFactory;
    
public:
    ALSystem();
    virtual ~ALSystem();
    
	static ALSystem* getInstance(){return m_spALSystem.get();}
    

    /***************************************** StoreKit ************************************/
    
    enum SK_ERROR
    {
        SKErrorUnknown = 0,
        SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
        SKErrorPaymentCancelled,    // user cancelled the request, etc.
        SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
        SKErrorPaymentNotAllowed,    // this device is not allowed to make the payment
        SKErrorRequestFailed
    };
    
    class ALStoreKitListener
    {
    public:
        //step5 用户输入的pid是无效的id
        virtual void onStoreKitValidateProductIDFailed( const Util::String &   invalidProductIdentifiers ){};
        //step5
        virtual void onStoreKitPurchaseFailedWithError(const Util::String & productIdentifier, 
                                                       const Util::String & transactionIdentifier, 
                                                       SK_ERROR errorType, 
                                                       const Util::String & error){};
       //step5
        virtual void onStoreKitPurchaseSucceed(const Util::String & productIdentifier,
                                               const Util::String & transactionIdentifier,
                                               const Util::String & transactionReceipt){};

        //step3
        virtual void onStoreKitGetProductPrice(Util::Dictionary<Util::String, Util::String> & idAndPrice){};

    };
    /** 功  能：添加应用内支付的交易观察者， IAPKit对象建立后调用 
     *  注  意：一定要在IAPKit对象建立后立即调用    step1
     */
    virtual void storeKitAddTransactionObserver(ALStoreKitListener* storeKitListener)=0;
    
    /**  step2
     */
    virtual void storeKitRequestPrice(Util::Array<Util::String> & productIdentifiers)=0;

    //step4
    virtual void storeKitStartPurchaseProducts(Util::Array<Util::String> & productIdentifiers)=0;
    //step6
    virtual void storeKitFinishTransaction(const Util::String & transactionIdentifier)=0;       
  
};

class ALSystemFactory
{
public:
	static void createALSystem();
	static void releaseALSystem();
};
}
#endif
