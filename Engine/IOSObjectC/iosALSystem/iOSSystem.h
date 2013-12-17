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

#if __OSX__
#ifndef TestGame_iOSSystem_h
#define TestGame_iOSSystem_h
#include "../../../addons/ALSystem/ALSystem.h"
#include "../../../foundation/core/singleton.h"

@class ALStoreKit;

class iOSSystem: public NALSystem::ALSystem
{
	__DeclareClass(iOSSystem);
	__DeclareImageSingleton(iOSSystem);
public:
    iOSSystem();
    iOSSystem(float precision, std::string ID);
    virtual ~iOSSystem();
    

#pragma mark -
#pragma mark StoreKit
    
    virtual void storeKitAddTransactionObserver(ALStoreKitListener* storeKitListener);
    virtual void storeKitStartPurchaseProducts(Util::Array<Util::String>  & productIdentifiers);
    virtual void storeKitFinishTransaction(const Util::String  & transactionIdentifier);
    virtual void storeKitRequestPrice(Util::Array<Util::String> & productIdentifiers);   




private:
    ALStoreKit* m_pStoreKit;

};


#endif
#endif //__osx__
