#if __OSX__

#include "../../../foundation/stdneb.h"
#include "iOSSystem.h"
#import "ALStoreKit.h"
#include "string.h"

using namespace NALSystem;

__ImplementClass(iOSSystem, 'IOSI', NALSystem::ALSystem);
__ImplementImageSingleton(iOSSystem);

iOSSystem::iOSSystem()
{
	__ConstructImageSingleton;
    m_pStoreKit = NULL;
   
}

iOSSystem::~iOSSystem()
{
    __DestructImageSingleton;
}

void ALSystemFactory::createALSystem()
{
    
    if (!ALSystem::m_spALSystem.isvalid()) {
		ALSystem::m_spALSystem  = iOSSystem::Create();
    }
    
}
void ALSystemFactory::releaseALSystem()
{
	ALSystem::m_spALSystem = NULL;
}


#pragma mark -
#pragma mark StoreKit

void iOSSystem::storeKitAddTransactionObserver(ALStoreKitListener* storeKitListener)
{
    if (!m_pStoreKit) {
        m_pStoreKit = [[ALStoreKit alloc] init];
        m_pStoreKit.m_pStoreKitDelegate = storeKitListener;
    }
}

void iOSSystem::storeKitStartPurchaseProducts(Util::Array<Util::String> & productIdentifiers)
{
    if (!m_pStoreKit) {
        m_pStoreKit = [[ALStoreKit alloc] init];
    }
    NSMutableArray* identifiers = [[NSMutableArray alloc] init];
    if (productIdentifiers.Size() == 0) {
        n_error("productIdentifiers is null, cancel purchase! ");
    }
    else {
        for (Util::Array<Util::String>::Iterator iter = productIdentifiers.Begin();
             iter != productIdentifiers.End(); iter++) {
            if (iter->Get() != NULL) {
                [identifiers addObject:[NSString stringWithCString:iter->Get() encoding:[NSString defaultCStringEncoding]]];//??????????????????
            }
        }
    }
    [m_pStoreKit startWithProductIdentifiers:identifiers];
    //[identifiers autorelease];
}
void iOSSystem::storeKitFinishTransaction(const Util::String & transactionIdentifier)
{
    if (!m_pStoreKit) {
        NSLog(@"m_pStoreKit does not exist! No transaction to be finished.");
        return;
    }
    if (transactionIdentifier.IsEmpty()) {
        return;
    }
    [m_pStoreKit finishTransaction:[NSString stringWithCString:transactionIdentifier.Get() encoding:[NSString defaultCStringEncoding]]];
}

void iOSSystem::storeKitRequestPrice(Util::Array<Util::String> & productIdentifiers)
{
    if (!m_pStoreKit) {
        m_pStoreKit = [[ALStoreKit alloc] init];
    }
    NSMutableArray* identifiers = [[NSMutableArray alloc] init];
    if (productIdentifiers.Size() == 0) {
        n_error("productIdentifiers is null, cancel purchase! ");
    }
    else {
        for (Util::Array<Util::String>::Iterator iter = productIdentifiers.Begin();
             iter != productIdentifiers.End(); iter++) {
            if (iter->Get() != NULL) {
                [identifiers addObject:[NSString stringWithCString:iter->Get() encoding:[NSString defaultCStringEncoding]]];//??????????????????
            }
        }
    }
    [m_pStoreKit requestPrice:identifiers];
    //[identifiers autorelease];
}


#endif