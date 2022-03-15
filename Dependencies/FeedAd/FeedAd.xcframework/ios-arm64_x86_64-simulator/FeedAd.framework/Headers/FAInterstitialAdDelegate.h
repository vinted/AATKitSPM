//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class FAInterstitialAd;

/// Make your delegate conform to this protocol
/// to get notified about events from FAInterstitialAd
/// and to customize its appearance
@protocol FAInterstitialAdDelegate <NSObject>

/// An ad failed to load or play
///
/// Request another ad or move on in your ad mediation
- (void)interstitialAd:(FAInterstitialAd *)interstitialAd didFailWithError:(NSError *)error;

/// An ad has finished loading and is ready for display through the show method
///
/// As soon as the SDK detects the view to be fully visible,
/// ad playback will start
- (void)interstitialAdDidFinishLoading:(FAInterstitialAd *)interstitialAd;

/// An ad has finished playing through successfully
///
/// Request another ad or move on in your ad mediation
- (void)interstitialAdDidFinishPlaying:(FAInterstitialAd *)interstitialAd;


@optional

/// Specify a view to show in the background
///
/// Implement this method and return a view that should be shown in the
/// background of the interstitial. It will be visible especially while
/// the ad is loading. Your view will be resized to match the expected
/// size of the ad.
- (UIView *)backgroundViewForInterstitialAd:(FAInterstitialAd *)interstitialAd;

/// An ad logged an impression
- (void)interstitialAdDidLogImpression:(FAInterstitialAd *)interstitialAd;

/// Should a loading indicator be displayed for this interstitial ad?
///
/// By default, a loading indicator will be displayed, when an ad is loading.
/// Implement this method and return NO, to disable it.
- (BOOL)interstitialAdShouldDisplayLoadingIndicator:(FAInterstitialAd *)interstitialAd;

/// An ad has been clicked
- (void)interstitialAdWasClicked:(FAInterstitialAd *)interstitialAd;

/// An ad has been skipped
- (void)interstitialAdWasSkipped:(FAInterstitialAd *)interstitialAd;

/// An ad will leave the application to show its
/// landing page after the user has clicked the ad
- (void)interstitialAdWillLeaveApplication:(FAInterstitialAd *)interstitialAd;

@end

NS_ASSUME_NONNULL_END
