//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FAInterstitialAdConfig.h"
#import "FAInterstitialAdDelegate.h"


NS_ASSUME_NONNULL_BEGIN

/// Loads and displays an interstitial ad
@interface FAInterstitialAd : NSObject

/// Delegate for getting notified about ad events
@property (nonatomic, weak, nullable) id <FAInterstitialAdDelegate> delegate;

/// Is this ad ready for display?
@property (nonatomic, readonly) BOOL isLoaded;


/// Checks if an ad is available for a given placemend id
+ (BOOL)isAvailableForPlacementId:(NSString *)placementId;


/// Cancels the interstitial ad
- (void)cancel;

/// Initializes a FAInterstitialAd with a FAInterstitialAdConfig
- (instancetype)initWithConfig:(FAInterstitialAdConfig *)config;

/// Loads a new ad
- (void)load;

/// Shows the interstitial ad
- (void)show;

@end

NS_ASSUME_NONNULL_END
