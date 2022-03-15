//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FAStandaloneAdConfig.h"
#import "FAStandaloneAdDelegate.h"


NS_ASSUME_NONNULL_BEGIN

/// Loads and displays an ad for injection into your view hirarchy
@interface FAStandaloneAd : NSObject

/// UI for displaying the ad
@property (nonatomic, readonly) UIView *adView;

/// Delegate for getting notified about ad events
@property (nonatomic, weak, nullable) id <FAStandaloneAdDelegate> delegate;

/// Is the ad ready for display?
@property (nonatomic, readonly) BOOL isLoaded;


/// Checks if an ad is available for a given placemend id
+ (BOOL)isAvailableForPlacementId:(NSString *)placementId;


/// Cancels the stand-alone ad
- (void)cancel;

/// Initializes a FAStandaloneAd with a FAStandaloneAdConfig
- (instancetype)initWithConfig:(FAStandaloneAdConfig *)config;

/// Loads a new ad
- (void)load;

/// Calculates the desired size for the ad view
/// given the size of your container view
///
/// If your container view is flexible in one dimension
/// of size, either height or width, set it to CGFLOAT_MAX.
- (CGSize)sizeForSuperviewSize:(CGSize)superviewSize;

@end

NS_ASSUME_NONNULL_END
