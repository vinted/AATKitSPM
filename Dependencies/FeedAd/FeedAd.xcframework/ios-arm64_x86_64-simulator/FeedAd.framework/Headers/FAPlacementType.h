//
// Copyright 2020 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

/// Defines context in which an InterstitialAd or StandaloneAd is displayed
typedef NS_ENUM(NSInteger, FAPlacementType) {
    /// Unknown
    FAPlacementTypeUnknown,
    
    /// Non-player context / Standalone ad
    FAPlacementTypeStandalone,
    
    /// Player context / Ad before actual content
    FAPlacementTypePreRoll,
    
    /// Player context / Ad break in-between actual content
    FAPlacementTypeMidRoll,
    
    /// Player context / Ad after actual content
    FAPlacementTypePostRoll
};

NS_ASSUME_NONNULL_END
