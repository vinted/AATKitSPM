//
// Copyright 2020 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>
#import "FAPlacementType.h"


NS_ASSUME_NONNULL_BEGIN

/// Configuration for FAStandaloneAd
@interface FAStandaloneAdConfig : NSObject

/// URL of content for the current screen (optional)
///
/// iOS Universal Link for the current screen where the ad is displayed.
@property (nonatomic, strong, nullable) NSURL *contentURL;

/// Custom tracking parameters (optional)
///
/// Specify custom parameters to pass additional tracking data about
/// the context of your placement. For example, this could be the
/// category of a certain item an user viewed in your app.
@property (nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *customParameters;

/// Type of the placement
///
/// See FAPlacementType for available options.
@property (nonatomic, assign) FAPlacementType placementType;

/// The ID of the placement (required)
///
/// Valid placement IDs are words of lowercase letters from a to z
/// and numbers from 0 to 9. The words can be separated by hyphens
/// or underscores. Multiple separators must not follow each other.
@property (nonatomic, copy, nullable) NSString *placementId;

@end

NS_ASSUME_NONNULL_END
