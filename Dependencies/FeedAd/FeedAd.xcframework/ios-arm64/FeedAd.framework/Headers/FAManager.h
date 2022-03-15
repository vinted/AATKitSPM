//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import "FACustomEvent.h"
#import "FAConfig.h"


NS_ASSUME_NONNULL_BEGIN

/// Manages SDK configuration and provides methods for sending
/// additional targeting parameters and tracking events
@interface FAManager : NSObject

/// Returns the SDK version
+ (NSString *)sdkVersion;

/// Gets the FAManager singleton instance
+ (instancetype)sharedManager;

/// Cancels all instances of FAFeedAd currently active
- (void)cancelAllFeedAds;

/// Updates the configuration of the SDK
- (void)configure:(FAConfig *)config;

/// Sends a custom event
///
/// If `FAConfig.waitForConsent` is enabled, calling `sendCustomEvent:`
/// with missing or insufficient TCF 2.0 consent will cause events to be
/// dropped.
///
/// Adapt your integration to send custom events at a point in time,
/// when you can ensure consent is actually available.
- (void)sendCustomEvent:(FACustomEvent *)customEvent;

/// Updates the current geo location
- (NSError * _Nullable)setGeoLocation:(CLLocation *)geoLocation;

@end

NS_ASSUME_NONNULL_END
