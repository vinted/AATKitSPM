//
//  DTBAdCallback.h
//  DTBiOSSDK
//
//  Copyright (c) 2021 Amazon Publisher Services. All rights reserved.


#import <Foundation/Foundation.h>
#import "DTBAdResponse.h"

@protocol DTBAdCallback

- (void)onFailure:(DTBAdError)error;

- (void)onSuccess:(DTBAdResponse *)adResponse;

@end
