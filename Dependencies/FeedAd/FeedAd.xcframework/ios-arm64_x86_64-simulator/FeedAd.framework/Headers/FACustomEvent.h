//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

/// Records a custom event for sending with FAManager
///
/// Allows you to track events inside your app,
/// including an optional revenue amount
/// (e.g. an in-app purchase being bought or
/// a certain game level being reached).
@interface FACustomEvent : NSObject

/// Give your event a label to distinguish it from other events
/// e.g. "iap" or "level-1-completed"
@property (nonatomic, copy, nullable) NSString *label;

/// Record an amount of revenue with this event (optional)
@property (nonatomic, copy, nullable) NSDecimalNumber *revenue;

/// Currency for the amount of revenue (optional)
///
/// Must be a 3-character currency code as of ISO 4217
/// e.g. "EUR", "USD", ...
@property (nonatomic, copy, nullable) NSString *revenueCurrency;


/// Initializes a custom event with a label
- (instancetype)initWithLabel:(NSString *)label;

/// Initializes a custom event with a label, revenue and revenue currency
- (instancetype)initWithLabel:(NSString *)label revenue:(NSDecimalNumber *)revenue revenueCurrency:(NSString *)revenueCurrency;

/// Validates a custom event
- (NSError * _Nullable)validate;

@end

NS_ASSUME_NONNULL_END
