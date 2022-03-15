//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class FAStandaloneAd;

/// Make your delegate conform to this protocol
/// to get notified about events from FAStandaloneAd
/// and to customize its appearance
@protocol FAStandaloneAdDelegate <NSObject>

/// An ad failed to load or play
///
/// Request another ad or move on in your ad mediation
- (void)standaloneAd:(FAStandaloneAd *)standaloneAd didFailWithError:(NSError *)error;

/// An ad has finished loading and is ready for display
///
/// Add FAStandaloneAd.adView to the view hiearachy of your
/// view controller
///
/// As soon as the SDK detects the view to be fully visible,
/// ad playback will start
- (void)standaloneAdDidFinishLoading:(FAStandaloneAd *)standaloneAd;

/// An ad has finished playing through successfully
///
/// Request another ad or move on in your ad mediation
- (void)standaloneAdDidFinishPlaying:(FAStandaloneAd *)standaloneAd;


@optional

/// An ad has changed its size
///
/// Resize your container view in your UI
- (void)standaloneAdDidChangeSize:(FAStandaloneAd *)standaloneAd;

/// An ad logged an impression
- (void)standaloneAdDidLogImpression:(FAStandaloneAd *)standaloneAdAd;

/// Should a loading indicator be displayed for this standalone ad?
///
/// By default, a loading indicator will be displayed, when an ad is loading.
/// Implement this method and return NO, to disable it.
- (BOOL)standaloneAdShouldDisplayLoadingIndicator:(FAStandaloneAd *)standaloneAd;

/// An ad has been clicked
- (void)standaloneAdWasClicked:(FAStandaloneAd *)standaloneAd;

/// An ad has been skipped
- (void)standaloneAdWasSkipped:(FAStandaloneAd *)standaloneAd;

/// An ad will leave the application to show its
/// landing page after the user has clicked the ad
- (void)standaloneAdWillLeaveApplication:(FAStandaloneAd *)standaloneAd;

@end

NS_ASSUME_NONNULL_END
