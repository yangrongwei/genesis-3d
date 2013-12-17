#if __OSX__ 
#include "../../../foundation/stdneb.h"
#include  "ALStoreKit.h"
//#import "GTMBase64.h"

#include <iostream>

#include "../../../foundation/util/array.h"
#include "../../../foundation/util/string.h"
#include "../../../foundation/util/dictionary.h"
using namespace NALSystem;

@implementation ALStoreKit
@synthesize m_pStoreKitDelegate;
@synthesize transactionResults;

- (id) init
{
    self = [super init];
    if (self) {
        m_pStoreKitDelegate = NULL;
        transactionResults = [[NSMutableArray alloc] init];
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        priceRequest = NULL;
        buyRequest = NULL;
        
        NSLog(@"Transaction Observer added !");
    }
    return self;
}
- (void) startWithProductIdentifiers:(NSArray *)productIdentifiers
{
    NSLog(@"Send product request to App Store, Product Identifiers:\n %@",productIdentifiers);
    
    if ([SKPaymentQueue canMakePayments]) {
        if ([productIdentifiers count] > 0) {
            buyRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithArray:productIdentifiers]];
            buyRequest.delegate = self;
            [buyRequest start];
            //[buyRequest release];
        }
    }
    else {
        std::string error("This device is not able or allowed to make payments");
        std::cout<<error<<std::endl;
        if (self.m_pStoreKitDelegate) {
            self.m_pStoreKitDelegate->onStoreKitPurchaseFailedWithError("","",ALSystem::SKErrorPaymentNotAllowed,error.c_str());
        }
    }
}
- (void)requestPrice:(NSArray *)productIdentifiers
{
    NSLog(@"Reques price for Product Identifiers:\n %@",productIdentifiers);
    
    if ([productIdentifiers count] > 0) {
        priceRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithArray:productIdentifiers]];
        priceRequest.delegate = self;
        [priceRequest start];
        //[priceRequest release];
    }

}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *myProduct = response.products;  
    
    NSLog(@"Receive product response:");
    for(SKProduct *product in myProduct){ 
        NSLog(@"Product Identifier: %@" , product.productIdentifier);
        NSLog(@"Product Title: %@" , product.localizedTitle);    
        NSLog(@"Product Description: %@" , product.localizedDescription);    
        NSLog(@"Product Price: %@%@" , [product.priceLocale objectForKey:NSLocaleCurrencySymbol],product.price);
    }
    NSLog(@"Total Product Quantity: %d", [myProduct count]);
    
    //request
    if (request == priceRequest) {
        Util::Dictionary<Util::String, Util::String> priceMap;
        for (SKProduct *product in myProduct) {
            NSString* price = [NSString stringWithFormat:@"%@%@",[product.priceLocale objectForKey:NSLocaleCurrencySymbol],product.price];
            std::string priceStd = price.UTF8String;
             
            priceMap.Add(product.productIdentifier.UTF8String, priceStd.c_str());
        }
        
        for (NSString* invalidID in response.invalidProductIdentifiers) {
            NSLog(@"Product Identifier: %@ is invalid, price = 0",invalidID);
            priceMap.Add(invalidID.UTF8String, "0");
        }
        if (priceMap.Size() > 0) {
            m_pStoreKitDelegate->onStoreKitGetProductPrice(priceMap);
        }
    }
    else if (request == buyRequest) {    //buy
        if ([response.invalidProductIdentifiers count] > 0) {
            NSArray* invalidProductIdentifiers = response.invalidProductIdentifiers;
           // std::vector<std::string>invalidIDVector;
            for (NSString* invalidID in invalidProductIdentifiers) {
                NSLog(@"Invalid Product Identifier: %@",invalidID);
               // invalidIDVector.push_back([invalidID UTF8String]);
                if (self.m_pStoreKitDelegate) {
                    self.m_pStoreKitDelegate->onStoreKitValidateProductIDFailed([invalidID UTF8String]);
                }
            }
        }
        
        NSArray *products = response.products;
        for (SKProduct *product in products) {
            NSLog(@"Add product %@ to payment queue", product.productIdentifier);
            [[SKPaymentQueue defaultQueue] addPayment:[SKPayment paymentWithProduct:product]];
        }
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{    
    NSString* errorStr = [NSString stringWithFormat:@"Product request failed. error description: %@",[error localizedDescription]];
    NSLog(@"%@", errorStr);
    std::string stdError([errorStr UTF8String]);
    if (self.m_pStoreKitDelegate) {
        self.m_pStoreKitDelegate->onStoreKitPurchaseFailedWithError("","",ALSystem::SKErrorRequestFailed,stdError.c_str());
    }
}

- (void)requestDidFinish:(SKRequest *)request
{
    if (priceRequest == request) {
        NSLog(@"price request finished");
        priceRequest = NULL;
    }
    if (buyRequest == request) {
        NSLog(@"buy request finished");
        buyRequest = NULL;
    }
}

#pragma mark payments

- (NSString*)base64forData:(NSData*)theData {
    const uint8_t* input = (const uint8_t*)[theData bytes];
    NSInteger length = [theData length];
    
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData* data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t* output = (uint8_t*)data.mutableBytes;
    
    NSInteger i;
    for (i=0; i < length; i += 3) {
        NSInteger value = 0;
        NSInteger j;
        for (j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger theIndex = (i / 3) * 4;
        output[theIndex + 0] =                    table[(value >> 18) & 0x3F];
        output[theIndex + 1] =                    table[(value >> 12) & 0x3F];
        output[theIndex + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[theIndex + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    //return [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
}

- (void) completedPurchaseTransaction: (SKPaymentTransaction *) transaction
{    
   // NSString* orgTransactionReceipt = [[[NSString alloc] initWithData:transaction.transactionReceipt encoding:[NSString defaultCStringEncoding]] autorelease];
    NSString* orgTransactionReceipt = [[NSString alloc] initWithData:transaction.transactionReceipt encoding:[NSString defaultCStringEncoding]];
    NSLog(@"Transaction succeed! productIdentifier: %@. transactionIdentifier: %@.",transaction.payment.productIdentifier, transaction.transactionIdentifier);
    NSLog(@"transactionReceipt: %@",orgTransactionReceipt);
    
    NSString* transactionReceiptStr = [NSString stringWithFormat:@"%@",[self base64forData:transaction.transactionReceipt]];
    
    [transactionResults addObject:transaction];
    
    const std::string productIdentifier([transaction.payment.productIdentifier UTF8String]);
    const std::string transactionIdentifier([transaction.transactionIdentifier UTF8String]);
    const std::string transactionReceipt([transactionReceiptStr UTF8String]);
    
    if (m_pStoreKitDelegate != NULL) {
        m_pStoreKitDelegate->onStoreKitPurchaseSucceed(productIdentifier.c_str(), transactionIdentifier.c_str(), transactionReceipt.c_str());
    }
}


- (void) handleFailedTransaction: (SKPaymentTransaction *) transaction
{   
    std::string error([[transaction.error description] UTF8String]);
    
    ALSystem::SK_ERROR errorType;
    switch (transaction.error.code) {
        case SKErrorUnknown:
            errorType = ALSystem::SKErrorUnknown;
            break;
        case SKErrorClientInvalid:
            errorType = ALSystem::SKErrorClientInvalid;
            break;        
        case SKErrorPaymentCancelled:
            errorType = ALSystem::SKErrorPaymentCancelled;
            break;        
        case SKErrorPaymentNotAllowed:
            errorType = ALSystem::SKErrorPaymentNotAllowed;
            break;        
        default:
            errorType = ALSystem::SKErrorUnknown;
            break;
    }
    
    NSLog(@"Transaction failed : %@, %@, %d, %@",transaction.transactionIdentifier,transaction.payment.productIdentifier, transaction.error.code, [transaction.error description]);

    [self.transactionResults addObject:transaction];

    if (self.m_pStoreKitDelegate != NULL) {
        self.m_pStoreKitDelegate->onStoreKitPurchaseFailedWithError([transaction.payment.productIdentifier UTF8String],[transaction.transactionIdentifier UTF8String], errorType, error.c_str());
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions 
{
    NSLog(@"Payment queue updated, a transaction state changed.");
	for (SKPaymentTransaction *transaction in transactions) {
		switch (transaction.transactionState) {
			case SKPaymentTransactionStatePurchased:            //交易完成
                NSLog(@"Handle a purchased transaction...");
                [self completedPurchaseTransaction:transaction];
				break;
			case SKPaymentTransactionStateRestored:             //Transaction was restored from user's purchase history
                NSLog(@"Handle a restored transaction...");
				[self completedPurchaseTransaction:transaction];
				break;
			case SKPaymentTransactionStateFailed: 
                NSLog(@"Handle a failed transaction...");
				[self handleFailedTransaction:transaction]; //交易失败
				break;
			case SKPaymentTransactionStatePurchasing:     //商品添加进列表 
                NSLog(@"Product %@ added to payment queue!",transaction.payment.productIdentifier);
				break;
			default: 
			    NSLog(@"Unknown transaction state.");
				break;
		}
	}
}

- (void) repurchase
{
    NSLog(@"repurchase");
    
	[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    
}
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    
}
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
    
}


- (void)finishTransaction:(NSString *)aTransactionID
{
    for (SKPaymentTransaction *transaction in transactionResults) {
        if ([transaction.transactionIdentifier isEqualToString:aTransactionID]) {
            [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
            NSLog(@"Finish transaction: transaction ID: %@, product ID: %@",transaction.transactionIdentifier,transaction.payment.productIdentifier);
            [transactionResults removeObject:transaction];
            break;
        }
    }
}


- (void)dealloc
{
    //[transactionResults release];
    transactionResults = nil;
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    //[super dealloc];
}

@end
#endif