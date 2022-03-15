//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FAConfig.h"
#import "FAFeedAdConfig.h"
#import "FAFeedAdDelegate.h"


NS_ASSUME_NONNULL_BEGIN

/// Loads and displays an ad for injection into content feeds
@interface FAFeedAd : NSObject

/// UI for displaying the ad
@property (nonatomic, readonly) UIView *adView;

/// Delegate for getting notified about ad events
@property (nonatomic, weak, nullable) id <FAFeedAdDelegate> delegate;

/// Is this ad ready for display?
@property (nonatomic, readonly) BOOL isLoaded;


/// Cancels the feed ad
///
/// Make sure to call this method when cleaning up an feed ad
/// that is currently loading or playing to prevent memory leaks
- (void)cancel;

/// Initializes a FAFeedAd with a FAFeedAdConfig
- (instancetype)initWithConfig:(FAFeedAdConfig *)config;

/// Loads a new ad
///
/// If `FAConfig.waitForConsent` is enabled, calling `load` with missing or
/// insufficient TCF 2.0 consent will delay SDK init and running ads infinitely,
/// until it is available.
///
/// As a result, you should expect `FAFeedAdDelegate` not to receive any
/// calls until sufficient consent for FeedAd has actually been provided.
- (void)load;

/// Calculates the desired size for the ad view
/// given the size of your container view
///
/// If your container view is flexible in one dimension
/// of size, either height or width, set it to CGFLOAT_MAX.
- (CGSize)sizeForSuperviewSize:(CGSize)superviewSize;

@end

NS_ASSUME_NONNULL_END
