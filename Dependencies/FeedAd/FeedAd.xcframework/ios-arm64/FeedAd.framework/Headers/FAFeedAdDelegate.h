//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class FAFeedAd;


/// Make your delegate conform to this protocol
/// to get notified about events from FAFeedAd
/// and to customize its appearance
@protocol FAFeedAdDelegate <NSObject>

/// An ad failed to load or play
///
/// Request another ad or move on in your ad mediation
- (void)feedAd:(FAFeedAd *)feedAd didFailWithError:(NSError *)error;

/// An ad has finished loading and is ready for display
///
/// Add FAFeedAd.adView to the view hiearachy of your
/// view controller
///
/// As soon as the SDK detects the view to be fully visible,
/// ad playback will start
- (void)feedAdDidFinishLoading:(FAFeedAd *)feedAd;

/// An ad has finished playing through successfully
///
/// Request another ad or move on in your ad mediation
- (void)feedAdDidFinishPlaying:(FAFeedAd *)feedAd;


@optional

/// An ad has changed its size
///
/// Resize your container view in your UI
- (void)feedAdDidChangeSize:(FAFeedAd *)feedAd;

/// An ad logged an impression
- (void)feedAdDidLogImpression:(FAFeedAd *)feedAd;

/// Should a loading indicator be displayed for an ad in the current context?
///
/// By default, a loading indicator will be displayed, when an ad is loading.
/// Implement this method and return NO, to disable it. This method might
/// be called multiple times.
- (BOOL)feedAdShouldDisplayLoadingIndicator:(FAFeedAd *)feedAd;

/// An ad has been clicked
- (void)feedAdWasClicked:(FAFeedAd *)feedAd;

/// An ad will leave the application to show its
/// landing page after the user has clicked the ad
- (void)feedAdWillLeaveApplication:(FAFeedAd *)feedAd;

@end

NS_ASSUME_NONNULL_END
