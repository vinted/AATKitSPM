//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>
#import "FAGender.h"


NS_ASSUME_NONNULL_BEGIN

/// Collects parameters for configuration of the FeedAd SDK
@interface FAConfig : NSObject <NSCopying>

/// Your client token as received from FeedAd after registration
@property (nonatomic, copy, nullable) NSString *clientToken;

/// Additional parameters for ad requests (optional)
@property (nonatomic, copy, nullable) NSDictionary<NSString *, NSString *> *customParameters;

/// Enable debug logging to console (defaults to NO)
@property (nonatomic, assign) BOOL isLoggingEnabled;

/// An user's age (optional)
@property (nonatomic, assign) NSInteger userAge;

/// An user's gender (optional)
@property (nonatomic, assign) FAGender userGender;

/// An user's ID (optional)
@property (nonatomic, copy, nullable) NSString *userId;

/// Delays the SDK init until consent from a TCF 2.0 CMP is available (defaults to NO)
@property (nonatomic, assign) BOOL waitForConsent;


/// Validates the configuration parameters
- (NSError * _Nullable)validate;
    
@end

NS_ASSUME_NONNULL_END
