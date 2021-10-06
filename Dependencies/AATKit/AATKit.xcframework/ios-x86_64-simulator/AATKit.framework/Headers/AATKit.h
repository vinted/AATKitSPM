//
//  AATKit.h
//
//  Created by Daniel Brockhaus on 04.04.12.
//  Copyright (c) 2012-2013 AddApptr. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//! Project version number for M1AATKit.
FOUNDATION_EXPORT double AATKitVersionNumber;

//! Project version string for M1AATKit.
FOUNDATION_EXPORT const unsigned char AATKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <M1AATKit/PublicHeader.h>
#import "AATKit/AATKit.h"
/**
 * Ad Networks
 *
 * You can use these enum values to enable or disable ad networks.
 *
 * @see +[AATKit reenableAdNetwork:]
 * @see +[AATKit disableAdNetwork:]
 */
typedef NS_ENUM(NSInteger, AATKitAdNetwork) {
    AATAdColony,
    AATAdMob,
    AATAdX,
    AATAmazonHB,
    AATApplovin,
    AATAppnexus,
    AATBluestack,
    AATCriteoSDK,
    AATDFP,
    AATFacebook,
    AATInmobi,
    AATMoPub,
    AATOgury,
    AATRubicon,
    AATSmaato,
    AATSmartAd,
    AATSmartAdDirect,
    AATUnity,
    AATYandex,
    AATTeads,
    AATPubNative,
    AATYOC,
    AATUnknownNetwork,
};

typedef NS_ENUM(NSInteger, AATConsent) {
    AATConsentUnknown,
    AATConsentObtained,
    AATConsentWithheld
};

typedef NS_ENUM(NSInteger, AATManagedConsentState) {
    AATManagedConsentStateUnknown,
    AATManagedConsentStateWithheld,
    AATManagedConsentStateCustom,
    AATManagedConsentStateObtained
};

NS_ASSUME_NONNULL_BEGIN

@protocol AATAdRequestDelegate;

/// Ad Request
///
/// In the new request/response based banner API, you can instantiate one
/// AATAdRequest for each ad you like to display.
///
/// Just instantiate, configure and execute an ad request like this:
///
///     let request = AATAdRequest(yourViewController)
///     request.targetingKeywords = [
///         "news-category": "technology"
///     ]
///     bannerPlacement.execute(request) { bannerView, error in
///         guard let bannerView = bannerView {
///             /// Handle load errors here by using `error!`.
///             handleAdLoadingError(error!)
///             return
///         }
///
///         // Integrate the banner view into your view hierarchy.
///         integrateBannerView(bannerView)
///     }
@interface AATAdRequest: NSObject <NSCopying>

/// NSNumbers representing banner sizes.
/// The default value is `nil`, allowing all possible banner sizes.
/// Banner sizes are found in the enum AATKitAdType
/// You can use the following code snippet to provide specific **banner** sizes:
/// NSMutableSet<NSNumber*>* bannerSizes = [NSMutableSet set];
/// [bannerSizes addObject:[NSNumber numberWithInteger:AATKitBannerMultiSize]];
/// [bannerSizes addObject:[NSNumber numberWithInteger:AATKitBanner375x53]];
/// self.adRequest.bannerSizes = bannerSizes;
/// Default: `nil` => All banner sizes supported by AATKit
@property (null_resettable) NSSet<NSNumber*>* bannerSizes;

/// An optional delegate to customize the load-time behavior for this request.
@property (nullable, readonly, weak) NSObject<AATAdRequestDelegate>* delegate;

/// Targeting Keywords you might want to send to your ad server.
@property NSDictionary<NSString*,NSObject*>* targetingKeywords;

@property (nullable) NSString* contentTargetingURL;

- (instancetype)init NS_UNAVAILABLE;

/// Initialize an Ad Request
///
/// This method initializes an ad request so you can use it to load ads.
///
/// @param viewController The view controller that will be associated to the
///                       ad request. Most of the ad networks need you to provide
///                       a view controller when loading an ad. So does AATKit.
- (instancetype)initWithViewController:(UIViewController*)viewController;

/// Initialize an Ad Request with an Optional Delegate
///
/// This method initializes an ad request so you can use it to load ads using
/// an optional request delegate.
///
/// @param delegate An optional delegate that can be used to fine-tune the
///                 loading process for this request.
/// @param viewController The view controller that will be associated to the
///                       ad request. Most of the ad networks need you to provide
///                       a view controller when loading an ad. So does AATKit.
- (instancetype)initWithDelegate:(nullable NSObject<AATAdRequestDelegate>*)delegate
                  viewController:(UIViewController*)viewController;
@end

/// Ad Request Delegate
///
/// This protocol provides a way for apps to customize process for loading
/// ads for a certain ad request.
@protocol AATAdRequestDelegate
@optional
/// Fine-Tune Keyword Targeting
///
/// You can use this method to indicate whether or not the specified keywords
/// should be sent to a specific ad network/ad server. This is useful if you
/// want to send the keywords only to your ad server but not to other sources
/// of ads.
- (BOOL)adRequest:(AATAdRequest*)request shouldUseTargetingKeywordsForNetwork:(AATKitAdNetwork)network;
@end

/// Banner Placement Configuration
///
/// Using this type, you can configure the way a banner placement should
/// work.
@interface AATBannerConfiguration: NSObject <NSCopying>

/// The Default Configuration
///
/// Use this method to access the default configuration suggested by AddApptr.
+ (instancetype)defaultConfiguration;

/// The Number of Workers
///
/// The request/response based banner placement can request multiple banner
/// ads in parallel. Using this property, you can specify the upper limit
/// of ads that might be processed in parallel. If you try to execute more
/// than this number of ads, any excess ads will be queued immediately and
/// scheduled for processing once one of the pending requests is completed
/// or cancelled.
@property NSInteger defaultNumberOfWorkers;

/// Enable Manual Ad Space Counting
///
/// If you don't want to rely on AATKit's ad space counting, you can set this
/// property to `true` and use `AATBannerPlacementProtocol.countAdSpace()`
/// to count ad spaces manually.
///
/// Default: `false`
@property BOOL manualAdSpaceCounting;
@end

/// Banner Loading Completion Handler
///
/// This type is used as a callback when loading banner ads. It will be invoked
/// after an ad request loaded an ad, failed to load any ad or after the application
/// cancelled the ad request.
///
/// @param bannerView `nil` if there was an error. Otherwise it's the UIView
///                   representing the loaded banner ad. Integrate it into
///                   your view hierarchy.
///                   The AATKit doesn't keep ownership, as the UIView instance is autoreleased.
/// @param error `nil` if an ad was loaded. Otherwise an `NSError` instance
///              that will indicate there was an error loading the ad.
typedef void (^AATBannerCompletionHandler) (UIView* __nullable bannerView, NSError* __nullable error);

/// A Request/Response-based Banner Placement
///
/// Using this type, you can request ads using the familiar request/response
/// mechanism, which allows you to request multiple ads in parallel.
///
/// @see +[AATKit createBannerPlacementWithName:]
/// @see +[AATKit createBannerPlacementWithName:configuration:]
@protocol AATBannerPlacementProtocol

/// Execute an Ad Request
///
/// This method will queue an ad request for processing. If a worker is
/// available, processing will start immediately.
///
/// @param request The ad request to be executed.
/// @param completionHandler A completion handler to be invoked after
///                          processing the ad request.  The completion
///                          handler will be called after an ad was loaded,
///                          after the SDK failed to load an ad or after the
///                          application cancelled the ad request. This
///                          completion handler will be called on the main
///                          queue.
- (void)executeRequest:(AATAdRequest*)request
     completionHandler:(AATBannerCompletionHandler)completionHandler
    NS_SWIFT_NAME(execute(_:completionHandler:));

/// Execute an Ad Request
///
/// This method will queue an ad request for processing. If a worker is
/// available, processing will start immediately.
///
/// @param request The ad request to be executed.
/// @param queue The `DispatchQueue` used to execute `completionHandler`.
/// @param completionHandler A completion handler to be invoked after
///                          processing the ad request.  The completion
///                          handler will be called after an ad was loaded,
///                          after the SDK failed to load an ad or after the
///                          application cancelled the ad request.
- (void)executeRequest:(AATAdRequest*)request
       completionQueue:(dispatch_queue_t)queue
     completionHandler:(AATBannerCompletionHandler)completionHandler
    NS_SWIFT_NAME(execute(_:queue:completionHandler:));

/// Cancel a schedule ad request.
///
/// Call this method to cancel an ad request. As ad requests have to keep
/// strong references to the view controller, you need to cancel pending
/// ad requests to avoid building a retain cycle. Cancelling a request will
/// clear the view controller reference on the ad request and thus, break
/// the retain cycle.
- (void)cancelRequest:(AATAdRequest*)request;

/// Manually Count an Ad Space
///
/// Manually count an ad space. You can use this method of you keep a backlog
/// of cached ads, so you can use them immediately instead of using them
/// when they get loaded. This will prevent unused ad results to count as
/// (unfilled) ad spaces already.
///
/// **NOTE:** You only need to use this method, if you enabled manual ad
/// space counting using the AATBannerConfiguration.
///
/// @see -[AATBannerConfiguration manualAdSpaceCounting]
- (void)countAdSpace;

/// Call this method to clean the placement data
/// This would clean placement data
/// **NOTE:** Call this method only when you are completely done with this placement

- (void)cleanPlacementData;

@end

@protocol AATKitDelegate;

@protocol AATConsentProtocol

/// NSNumbers representing networks that will not be requested if they do not have the TCF2 consent. Only works if TCF2 compliant CMP is used.
/// The default value is `nil`, using a default set of networks.
/// Networks are found in the enum AATKitAdNetwork
/// You can use the following code snippet to set specific networks:
/// NSMutableSet<NSNumber*>* stopSet = [NSMutableSet set];
/// [stopSet addObject:[NSNumber numberWithInteger:AATAdMob]];
/// [stopSet addObject:[NSNumber numberWithInteger:AATAdX]];
/// self.consent.noConsentNetworkStopSet = stopSet;
/// Default: `nil` => The default stopset provided by AATKit will be used
@property (nullable) NSSet<NSNumber*>* noConsentNetworkStopSet;
@end

@protocol AATManagedConsentDelegate;

@protocol AATCMPDelegate

/// onConsentUpdated is being called whenever the consent has been updated by CMPs.
/// AATKit TO Publisher.
- (void)onConsentUpdatedWithState:(AATManagedConsentState)state;

/// onCMPFailedToShow is being called whenever the CMP fails to show the form.
/// AATKit TO Publisher.
/// @param error the error string.
- (void)onCMPFailedToShow:(NSString *)error;

/// onCMPFailedToLoad is being called whenever the CMP fails to load the form (Only google fails to load).
/// AATKit TO Publisher.
/// @param error the error string.
- (void)onCMPFailedToLoad:(NSString *)error;

/// CMPNeedsUI is being called when the CMP form is ready to be shown.
/// AATKit TO Publisher.
- (void)CMPNeedsUI;

/// showCMP presents the consent screen ONLY if it is required by the used CMP (i.e. no user consent has been set yet)..
/// Publisher TO AATKit.
- (void)showIfNeeded:(UIViewController *)viewController;

/// editConsent presents the consent screen, allowing the user to change consent settings.
/// Publisher TO AATKit.
- (void)editConsent:(UIViewController *)viewController;

/// reload tells the CMP to reload. Tells the CMP to reload.
/// Does not need to be used unless some error occurs.
/// Publisher TO AATKit.
- (void)reload;

@end

/// AATCMP protocol should be conformed by any new CMP provider.
@protocol AATCMP <NSObject>
@end

/// AATCMPProviderObj should be inherited by any CMP provider.
@interface AATCMPProviderObj : NSObject <AATCMP>
@end

/// AATCMPGoogle should be used when you use Google CMP.
/// AATKit/GoogleCMP dependency should be added to your Podfile.
@interface AATCMPGoogle: AATCMPProviderObj <AATCMP>
- (instancetype)init;
@end

/// AATCMPOgury should be used when you use Ogury CMP.
/// AATKit/OguryCMP dependency should be added to your Podfile.
@interface AATCMPOgury: AATCMPProviderObj <AATCMP>
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithAssetKey:(NSString *)assetKey;
@end

@interface AATManagedConsent : NSObject <AATConsentProtocol, AATCMPDelegate>
- (instancetype)init NS_UNAVAILABLE;

/// @param delegate must not be (null/nil) it would be called with CMP different events
/// @param cmp the CMP provider used. Could be AATCMPGoogle or AATCMPOgury
- (instancetype)initWithDelegate:(nullable NSObject<AATManagedConsentDelegate>*)delegate cmp:(AATCMPProviderObj <AATCMP>*)cmp;

@end

@protocol AATManagedConsentDelegate
- (void)CMPNeedsUI:(AATManagedConsent*)managedConsent;
- (void)managedConsentCMPFinishedWithState:(AATManagedConsentState)state;
- (void)managedConsentCMPFailedToLoad:(AATManagedConsent*)managedConsent error:(NSString *)string;
- (void)managedConsentCMPFailedToShow:(AATManagedConsent*)managedConsent error:(NSString *)string;
@end

/** The simple type of consent to allow publishers who are not using our CMP (AATManagedConsent) to pass non-IAB consent
 information. */
@interface AATSimpleConsent : NSObject <AATConsentProtocol>
@property AATConsent nonIABConsent;

- (instancetype)init NS_UNAVAILABLE;
/**
 @param nonIABConsent Must be one of the following: AATConsentUnknown, AATConsentObtained or AATConsentWithheld
 @return AATSimpleConsent object to be passed to AATKit configurations
 */
- (instancetype)initWithNonIABConsent:(AATConsent)nonIABConsent;
@end

/**
* The AATVendorConsentDelegate delegate protocol.
*
* The `AATVendorConsentDelegate` protocol defines methods that should be implemented by
* Conformers to AATVendorConsentDelegate
*/
@protocol AATVendorConsentDelegate
// get consent for a specific ad network
- (AATConsent)getConsentForNetwork:(AATKitAdNetwork)network;
// return AATKit consent
- (AATConsent)getConsentForAddApptr;
@end

/** To support 3rd parties CMPs, we need to make sure that AATKit works well with 3rd party CMPs
 3rd party CMPs offer the management of “more partners”  for each of them separately
 The vendor type of consent is similar to AATSimpleConsent, the only difference is that: it manages the consent for each network separately */
@interface AATVendorConsent : NSObject <AATConsentProtocol>
- (instancetype)init NS_UNAVAILABLE;
/**
@param delegate Must conform to AATVendorConsentDelegate that is implementing consent for each ad network
@return AATVendorConsent object to be passed to AATKit configurations
*/
- (instancetype)initWithVendorConsentDelegate:(nonnull NSObject<AATVendorConsentDelegate>*)delegate;
@end

/**
 AATKitStatisticsDelegate notify you with all placements reporting events Like: - countAdSpace - countImpression ... etc
 */
@protocol AATKitStatisticsDelegate <NSObject>

@optional

/**
Will notify the AATKitStatisticsDelegate with every ad space counting event
 */
- (void)AATKitCountedAdSpace;

/**
 Will notify the AATKitStatisticsDelegate with every ad request event
@param network the Ad Network that performed the reported request
 */
- (void)AATKitCountedRequestForNetwork:(AATKitAdNetwork)network;

/**
 Will notify the AATKitStatisticsDelegate with every ad response event
@param network the Ad Network that returned the reported response
 */
- (void)AATKitCountedResponseForNetwork:(AATKitAdNetwork)network;

/**
 Will notify the AATKitStatisticsDelegate with every impression counting event
@param network the Ad Network that returned the adv for this impression
 */
- (void)AATKitCountedImpressionForNetwork:(AATKitAdNetwork)network;

/**
 Will notify the AATKitStatisticsDelegate with every viewable impression counting event
@param network the Ad Network that returned the adv for this viewable impression
 */
- (void)AATKitCountedVImpressionForNetwork:(AATKitAdNetwork)network;

/**
 Will notify the AATKitStatisticsDelegate with every click event
@param network the Ad Network that returned the adv for this click
 */
- (void)AATKitCountedClickForNetwork:(AATKitAdNetwork)network;

@end

/**
 AATReportsDelegate notify you with reporting request parameters
 */
@protocol AATReportsDelegate <NSObject>

- (void)onReportSent:(NSString *)report;

@end

/**
 * The AATBannerCache delegate protocol.
 *
 * The `AATBannerCacheDelegate` protocol defines methods that should be implemented by
 * Conformers to AATBannerCacheDelegate
 */
@protocol AATBannerCacheDelegate<NSObject>
/// Method used to notify the delegate when ads (at least 1) are ready to consume
- (void)firstBannerLoaded;
@end


@interface AATBannerCacheConfiguration: NSObject <NSCopying>
@property NSString* placementName;
@property (nullable, weak) id<AATBannerCacheDelegate> delegate;
@property int cacheSize;
@property BOOL shouldCacheAdditionalAdAtStart;
@property AATAdRequest* adRequest;
@property NSTimeInterval minimumDelay;

- (instancetype)init NS_UNAVAILABLE;


- (instancetype)initWithPlacementName:(NSString *)placementName
                            cacheSize:(int)cacheSize
                       viewController:(UIViewController *) viewController;

/// @brief Init AATBannerCacheConfiguration
/// @param placementName placement name
/// @param delegate the delegate that would be notified when first ad is ready default value is null
/// @param cacheSize maximum number of banner ads to be cached
/// @param shouldCacheAdditionalAdAtStart should load extra ad default value is false
/// @param adRequest AATAdRequest with configurations
/// @param minimumDelay minimum delay in seconds between consuming ads default value is 1 sec
/// @return AATBannerCacheConfiguration object
- (instancetype)initWithPlacementName:(NSString *)placementName
                             delegate:(nullable id<AATBannerCacheDelegate>)delegate
                            cacheSize:(int)cacheSize
       shouldCacheAdditionalAdAtStart:(BOOL)shouldCacheAdditionalAdAtStart
                            adRequest:(AATAdRequest *)adRequest
                         minimumDelay:(NSTimeInterval) minimumDelay;
@end

@interface AATBannerCache: NSObject
@property (weak) id<AATBannerCacheDelegate> delegate;
- (instancetype)init NS_UNAVAILABLE;

/// @brief Init AATBannerCache will automatically start loading ads
/// @param configuration configuration required to intialize AATBannerCache, once the AATBannerCache intialiazed with AATBannerCacheConfiguration object, this configuration cannot be changed
/// @return AATBannerCache object
- (instancetype)initWithConfiguration:(AATBannerCacheConfiguration *)configuration
NS_SWIFT_NAME(init(configuration:));

- (instancetype)initWithConfiguration:(AATBannerCacheConfiguration *)configuration
                andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate
NS_SWIFT_NAME(init(configuration:statisticsDelegate:));

/// Change the BannerCache delegate
/// Set a new delegate to receive  firstBannerLoaded notification
- (void)setCacheDelegate:(nullable id<AATBannerCacheDelegate>)delegate;
/// @brief Returns  banner ad view,
/// This method respects the frequency capping, set by AATBannerCacheConfiguration.minimumDelay
/// @return UIView
- (nullable UIView *)consume;

/// @brief Method to return banner ad view
/// @param forceConsume  true if cache should try to return banner ignoring the frequency capping set by AATBannerCacheConfiguration.minimumDelay
/// @return UIView
- (nullable UIView *)consume:(BOOL) forceConsume;
/// Method to update the used AATAdRequest
/// No need to call startLoadBanners method after this method
/// It will automatically call startLoadBanners
/// @param request the new ad request
/// @param shouldRefresh if this boolean set to true:
/// - Cancel current requests
/// - Empty the cached ads
/// - Start loading new ads
/// - When the first banner ad is ready, firstBannerLoaded delegate method will be called
- (void)updateRequestConfiguration:(AATAdRequest *)request shouldRefresh:(BOOL)shouldRefresh;

/// Cancel all loading requests
- (void)destroy;
@end

@interface AATRuntimeConfiguration : NSObject

/// Specify whether or not the user's consent is required to display
/// personalized ads.
///
/// Set this to `YES` if your user is subject to privacy regulations like
/// the GDPR. Set to `NO` otherwise.
///
/// Default: `YES`
@property BOOL consentRequired;

/// Specify whether or not to allow AddApptr, and ad networks used in its SDK,
/// the tracking of geo data.
///
/// Default: `NO`
@property (nonatomic) BOOL shouldUseGeoLocation;

/// Default: nil, never read/write the consent string from NSUserDefaults.
@property (nullable) NSObject<AATConsentProtocol>* consent;

@property (nullable) NSString *userLogChoice;

@end


@interface AATConfiguration: AATRuntimeConfiguration

/// Specify another Bundle ID to use for Rules
///
/// Use this, if your beta version has a different bundle ID than your app
/// store release. In that case, specify the bundle ID of your app store
/// release here.
///
/// Default: `nil`
@property (nullable) NSString* alternativeBundleID;

/// Specify whether or not the alternative bundle ID should be used for reporting.
///
/// If `alternativeBundleID` is `nil`, this field has no effect.
///
/// If this flag is `YES`, AATKit will report impressions etc. using the
/// alternative bundle ID. This is good to prevent skewed statistics.
///
/// If this flag is `NO`, AATKit will report impressions etc. using the
/// actual bundle ID. This is good to see separate statistics for your beta
/// versions.
///
/// Default: `YES`
@property BOOL shouldReportMetricsUsingAlternativeBundleID;

/// A View Controller for the Ad Networks
///
/// Several ad networks require a valid view controller to load ads. You
/// can specify a default view controller here.
///
/// Default: `nil`
@property (nullable) UIViewController* defaultViewController;

/// A Delegate for AATKit
///
/// Use this property, to specify a delegate that will be notified by AATKit
/// for any ad-related events.
///
/// Default: `nil`
@property (nullable, weak) NSObject<AATKitDelegate>* delegate;

/// The rules to use before receiving fresh rules from the AATKit servers.
///
/// **NOTE:** Please contact the AddApptr support team in case you want to
/// use this property.
///
/// Default: `nil`
@property (nullable) NSArray<NSString*>* initialRules;

/// Specify whether rules downloaded from the AATKit servers should be
/// cached on the device.
///
/// Default: `YES`
@property BOOL shouldCacheRules;

/// The account ID to use for testing.
///
/// **NOTE:** The argument is an `NSNumber`. Pass literal values like `@797`.
///
/// Default: `nil`
@property (nullable) NSNumber* testModeAccountID;

/// Specify whether the skip-load feature (if no consent given for this network) is enabled or not
///
/// @NOTE To enable/disable this feature, please call `- (void)enableShouldSkipRules:(BOOL)shouldSkipRules;`
///
/// Default: `NO`
@property (readonly) BOOL shouldSkipRules;

/// The reports delegate that would be notified with the report request parameters.
///
/// Default: `nil`
@property (nullable, weak) id<AATReportsDelegate> reportsDelegate;

/// Specify whether the skip-load feature (if no consent given for this network) is enabled or not
/// @param shouldSkipRules a BOOL that would be applied on (skip-rules if no consent) feature
- (void)enableShouldSkipRules:(BOOL)shouldSkipRules;
@property (readonly) BOOL shouldDeactivateViewability;

@end
NS_ASSUME_NONNULL_END

/**
 * A placement.
 *
 * In AATKit, a placement represents a logical position of an ad in your app.
 * You might want to use a fullscreen placement to show interstitials or a
 * banner placement to display a banner in your app.
 *
 * You can also use different banner placements with different sizes or use
 * different banner placements for different view controllers in your app.
 *
 * **NOTE:** We strongly advise against creating too many placements. Most
 * of the time you won't need to use more than half a dozen placements.
 *
 * @see +[AATKit createPlacementWithName:andType:]
 * @see +[AATKit showPlacement:]
 * @see +[AATKit reloadPlacement:]
 * @see +[AATKit startPlacementAutoReload:]
 * @see +[AATKit getNativeAdForPlacement:]
 */
@protocol AATKitPlacement <NSObject>
@property (copy) NSString * _Nonnull name;
@end

/**
 * A native ad.
 *
 * A native ad contains meta information that can be used by an application
 * to integrate native ads into their layout, providing a seamless user
 * experience.
 *
 * @see +[AATKit getNativeAdForPlacement:]
 * @see +[AATKit setViewController:forNativeAd:]
 * @see +[AATKit setTrackingView:forNativeAd:]
 * @see +[AATKit removeTrackingViewForNativeAd:]
 * @see +[AATKit getNativeAdTitle:]
 * @see +[AATKit getNativeAdDescription:]
 * @see +[AATKit getNativeAdImageURL:]
 * @see +[AATKit getNativeAdIconURL:]
 * @see +[AATKit getNativeAdCallToAction:]
 * @see +[AATKit getNativeAdBrandingLogoView:]
 * @see +[AATKit getNativeAdAdvertizer:]
 * @see +[AATKit getNativeAdType:]
 * @see +[AATKit getNativeAdRating:]
 * @see +[AATKit getNativeAdNetwork:]
 * @see +[AATKit isNativeAdExpired:]
 * @see +[AATKit isNativeAdReady:]
 * @see +[AATKit isNativeAdVideo:]
 */
@protocol AATKitNativeAd <NSObject>
@end

NS_ASSUME_NONNULL_BEGIN

@interface AATKitReward: NSObject
@property (readonly) NSString* name;
@property (readonly) NSString* value;

- (instancetype)init NS_UNAVAILABLE;
@end
NS_ASSUME_NONNULL_END

/**
 * The AATKit delegate protocol.
 *
 * The `AATKitDelegate` protocol defines methods that are called by the
 * AATKit framework in response to important events.
 */
@protocol AATKitDelegate<NSObject>

@optional

/// @name All Placement Types

/**
 * A placement is ready to display an ad.
 *
 * This method will be called for banner, full screen, and native
 * placements.
 * - Banner placements will automatically display the new ad.
 * - Full screen placements can now invoke +[AATKit showPlacement:].
 * - Native placements can now invoke +[AATKit getNativeAdForPlacement:].
 *
 * Because of the delayed and asynchronous nature of the ad networks'
 * responses, it is possible to get multiple notifications for a single call
 * to +[AATKit reloadPlacement:]. Use +[AATKit haveAdForPlacement:] to check
 * for these cached responses before calling +[AATKit reloadPlacement:]
 * again.
 *
 * **NOTE:** This method will not be called when displaying a banner from
 * the internal EMPTY network. Use -[AATKitDelegate AATKitShowingEmpty:]
 * to receive notifications for these banners.
 *
 * @see +[AATKit showPlacement:]
 * @see +[AATKit getNativeAdForPlacement:]
 * @see -[id\<AATKitDelegate> AATKitShowingEmpty:]
 */
- (void) AATKitHaveAd:(nonnull NSObject<AATKitPlacement>*) placement;


/**
 * Multi-Size placement specific callback.
 * When a placement of type AATKitBannerMultiSize is ready to display an ad.
 * Since multi-size banner views vary in size, the reference to a new UIView
 * instance is provided in the callback as well.
 *
 * *NOTE* The reference to the multi-size banner view (placementView) is autoreleased.
 * Hence the receiver has to make sure to retain the the UIView instance himself,
 * as well as dispose the old UIView instance if present.
 *
 * The callback AATKitHaveAd will not be called for multi-size banner placements.
 */
- (void) AATKitHaveAdOnMultiSizeBanner:(nonnull NSObject<AATKitPlacement>*) placement withView:(nonnull UIView*) placementView;

/**
 * A placement could not get ready to display an ad.
 *
 * For fullscreen and native placements: This method will be called when
 * AATKit failed to load an ad within a predefined time interval.
 *
 * For banner placements with auto-reload: This method will be called when
 * AATKit failed to load a new ad to replace the current one within a
 * reasonable amount of time. You can use this signal to hide the banner
 * view. However, we recommend against doing so, as this might have a negative
 * impact on your click-rate.
 *
 * For banner placements with manual loading: This method will be called when
 * a banner ad has been visible for the required minimal duration. Use this
 * signal to trigger a manual loading again once you like to.
 */
- (void) AATKitNoAds:(nonnull NSObject<AATKitPlacement>*) placement;

/// @name Banner Placements

/**
 * An empty banner is ready to be displayed.
 *
 * This method will be called for banner placements when it will display a
 * banner ad from the internal EMPTY network. The EMPTY network displays a
 * transparent banner.
 *
 * If a banner from a different network will be loaded, -[AATKitDelegate
 * AATKitHaveAd:] will be called.
 *
 * @see -[id\<AATKitDelegate> AATKitHaveAd:]
 */
- (void) AATKitShowingEmpty:(nonnull NSObject<AATKitPlacement>*) placement;

/// @name Full Screen Placements

/**
 * A full screen ad will be displayed.
 *
 * In this callback, you can e.g. suspend a game while the user is watching
 * a full screen ad.
 *
 * *NOTE:* This callback is unreliable due to inconsistent use of callbacks
 * in different ad network SDKs.
 *
 * @see -[id\<AATKitDelegate> AATKitResumeAfterAd]
 */
- (void) AATKitPauseForAd __deprecated_msg("This method is deprecated. Use - (void) AATKitPauseForAd:(nullable NSObject<AATKitPlacement>*)placement; instead.");

/**
 * A full screen ad will be displayed.
 *
 * In this callback, you can e.g. suspend a game while the user is watching
 * a full screen ad.
 *
 * *NOTE:* This callback is unreliable due to inconsistent use of callbacks
 * in different ad network SDKs.
 * @param placement The AATKit placement that caused the app to pause
 *
 * @see -[id\<AATKitDelegate> AATKitResumeAfterAd]
 */
- (void) AATKitPauseForAd:(nullable NSObject<AATKitPlacement>*)placement;

/**
 * A full screen ad was displayed.
 *
 * In this callback, you can e.g. resume a game after the user was watching
 * a full screen ad.
 *
 * *NOTE:* This callback is unreliable due to inconsistent use of callbacks
 * in different ad network SDKs.
 *
 * @see -[id\<AATKitDelegate> AATKitPauseForAd]
 */
- (void) AATKitResumeAfterAd __deprecated_msg("This method is deprecated. Use - (void) AATKitResumeAfterAd:(nullable NSObject<AATKitPlacement>*)placement; instead.");

/**
 * A full screen ad was displayed.
 *
 * In this callback, you can e.g. resume a game after the user was watching
 * a full screen ad.
 *
 * *NOTE:* This callback is unreliable due to inconsistent use of callbacks
 * in different ad network SDKs.
 *
 * @param placement The AATKit placement that paused the app
 *
 * @see -[id\<AATKitDelegate> AATKitPauseForAd]
 */
- (void) AATKitResumeAfterAd:(nullable NSObject<AATKitPlacement>*)placement;

/// @name Other Methods

/**
 * Please ignore unless told otherwise by AddApptr support.
 */
- (BOOL) AATKitAppWillHandleURL:(nonnull NSURLRequest*) url;

/**
 * Please ignore unless told otherwise by AddApptr support.
 */
- (void) AATKitUserEarnedIncentive:(nullable AATKitReward *) reward;

- (void) AATKitUserEarnedIncentiveOnPlacement: (nonnull NSObject<AATKitPlacement>*) placement withReward: (nullable AATKitReward *) reward;
- (void) AATKitObtainedAdRules: (BOOL) fromTheServer;
@end

/**
 * Banner Alignment Constants
 *
 * Sometimes different ad networks have very similar ad sizes. When this
 * happens, the banner container will get a size allocation fitting the
 * largest of these banner types.
 *
 * To make sure smaller banners will get properly aligned, use these
 * constants for `+[AATKit setPlacementAlign:forPlacement:]` to provide a
 * hint about the desired banner alignment.
 *
 * @see +[AATKit setPlacementAlign:forPlacement:]
 */
typedef NS_ENUM(NSInteger, AATKitBannerAlign) {
    /**
     * Banners should be aligned to the top edge of the container view.
     * This alignment is recommended for banner ads at the top of the
     * screen.
     */
    AATKitBannerTop,
    /**
     * Banners should be aligned to the bottom edge of the container view.
     * This alignment is recommended for banner ads at the bottom of the
     * screen.
     */
    AATKitBannerBottom,
    /**
     * Banners should be vertically centered in the container view. This
     * Alignment is recommended for banner ads embedded in scrollable
     * content, such as instances of `UITableViewCell`.
     */
    AATKitBannerCenter
};

/**
 * Ad Placement Types.
 *
 * *NOTE:* Not all types are supported by all ad networks.
 */
typedef NS_ENUM(NSInteger, AATKitAdType) {
    /// Default small banner.
    AATKitBanner320x53,
    /// An iPhone 6 wrapper for the 320x53 banner size.
    AATKitBanner375x53,
    /// An iPhone 6 Plus wrapper for the 320x53 banner size.
    AATKitBanner414x53,
    /// A banner size for iPad devices.
    AATKitBanner768x90,
    /// The standard “medium rectangle”.
    AATKitBanner300x250,
    /// A banner size fitting a landscape iPhone.
    AATKitBanner468x60,
    /// A multi size banner comprising banner of different sizes.
    AATKitBannerMultiSize,
    /// Full Screen Ads.
    AATKitFullscreen,
    /// Native Ads
    AATKitNativeAd,
    /// Banner with a size up to 480x32.
    AATKitBanner480x32,
    /// Banner with a size up to 1024x66.
    AATKitBanner1024x66,
    /// 300x200
    AATKitBanner300x200,
    /// 90x80
    AATKitBanner90x80,
    /// 200x200
    AATKitBanner200x200,
    // specific DFP size
    AATKitBanner320x75,
    // specific DFP size
    AATKitBanner320x100,
    // specific DFP size
    AATKitBanner320x150,
    // specific One by AOL size
    AATKitBanner320x160,
    // specific One by AOL size
    AATKitBanner320x480,
    // specific Amazon tablet size
    AATKitBanner728x90,
    // specific Vungle size
    AATKitBanner300x50
};

/**
 * Native Ad Content Types
 *
 * This type is used to indicate the content type of a native ad.
 */
typedef NS_ENUM(NSInteger, AATKitNativeAdType) {
    /// The user will be prompted to install an application.
    AATKitNativeAppInstall,
    /// Undocumented
    AATKitNativeContent,
    AATKitNativeVideo,
    AATKitNativeOther,
    AATKitNativeTypeUnknown
} __deprecated_msg("If you are using this method for implementing Google app install or content native ads, please use Google unified native ads instead. For more information, please have a look at our documentation.");

typedef NS_ENUM(NSInteger, AdChoicesIconPosition) {
    defaultPosition, // default value
    top_left,
    top_right,
    bottom_right,
    bottom_left
};

/**
 * AATKit Public Interface
 *
 * The `AATKit` class is used to communicate with the framework. It is the
 * main interface for you to configure and display ads.
 *
 * Using AATKit requires four steps in general:
 *
 * 1. Initialize AATKit:
 *   * `+[AATKit initWithViewController:andDelegate:]`
 * 2. Create a placement:
 *   * `+[AATKit createPlacementWithName:andType:]`
 * 3. Load ads for the placement:
 *   * `+[AATKit reloadPlacement:]`
 *   * `+[AATKit startPlacementAutoReload:]`
 * 4. Display the ad:
 *   * `+[AATKit getPlacementView:]` (for banner ads)
 *   * `+[AATKit showPlacement:]` (for full screen ads)
 *   * `+[AATKit getNativeAdForPlacement:]` (for native ads)
 */
// FIXME: Provide some example snippets for the different kinds of ads.
@interface AATKit : NSObject

/// @name Initialization and Configuration

/// Initialize AATKit
///
/// This method call must be the first call into AATKit. It will initialize
/// the framework and trigger the initial download of rules from the server.
///
/// @param configuration The AATKit configuration for this app instance. May
///                      be `nil` to use default values.
+(void)initializeWithConfiguration:(nullable AATConfiguration*)configuration
    NS_SWIFT_NAME(initialize(with:));

/**
 * Initialize AATKit with Initial Rules.
 *
 * This method allows to specify the rules defining the way AATKit works.
 * Using this method, you can avoid contacting the AddApptr servers. This
 * can improve the speed of loading the first ads.
 *
 * Please contact the support team for help when defining the initial rule
 * set.
 *
 * @param rulesCaching Specify whether the initial rule set should be
 * cached.
 *
 * **NOTE:** Please contact the AddApptr support team in case you want to
 * use this method.
 *
 * **NOTE:** This method is deprecated, replace it with this code to preserve
 * the current behavior:
 *
 *     AATConfiguration* configuration = [[AATConfiguration alloc] init];
 *     configuration.defaultViewController = viewController;
 *     configuration.delegate = delegate;
 *     configuration.shouldCacheRules = rulesCaching;
 *     configuration.initialRules = initialRules;
 *     [AATKit initializeWithConfiguration:configuration];
 */
+ (void) initWithViewController: (nullable UIViewController*)viewcon
                       delegate: (nullable id<AATKitDelegate>) delegate
             enableRulesCaching: (BOOL) rulesCaching
                andInitialRules: (nullable NSString*) initialRules
    __deprecated_msg("This method is deprecated. Use +[AATKit initializeWithConfiguration:] instead.");


/**
 * Update AATKit consent arguments via AATRuntimeConfiguration object after
 * the AATKit is already initialized.
 *
 */
+ (void)reconfigureUsingConfiguration:(nonnull AATRuntimeConfiguration*)configuration
        NS_SWIFT_NAME(reconfigure(using:));


/**
 * Set Targeting Information.
 *
 * Some networks support providing additional information to improve the
 * ads for the current context.
 *
 * You can set a dictionary like this: `@{@"interests": @[@"sports", @"stocks"], @"gender": @"female"}`.
 *
 * Supported types for the keys: NSString.
 *
 * Supported types for the values: NSString, NSNumber, and NSArray containing NSString and/or NSNumber.
 *
 * Please contact the support team for help when defining targeting information.
 */
+ (void) setTargetingInfo:(nullable NSDictionary*)targetingInfo;

/**
 * Specify the presenting view controller.
 *
 * Update the view controller that will be used by the framework to present
 * full screen view controllers. Full screen view controllers can be
 * presented by full screen ads (while they are being displayed) or even
 * banner ads (after the user tapped an ad).
 *
 * See +[AATKit setPlacementViewController:forPlacement:] fo details about
 * using this API.
 */
+ (void) setViewController:(nullable UIViewController*)con;

/**
 * Specify the delegate for AATKit.
 *
 * You can use this method to update the delegate object for AATKit.
 *
 * *NOTE:* Be careful when updating the delegate. You might still receive
 * notifications for previously used placements.
 */
+ (void) setDelegate:(nullable id<AATKitDelegate>)delegate;

/// @name Debugging Information

/**
 * Get the AATKit version number.
 *
 * Get the string representation of the AATKit version number.
 */
+ (nonnull NSString *) getVersion;

/**
 * Check if the device is a type of iPad
*/
+ (BOOL) isTablet;

/**
 * Returns the AATKitAdType with maximum width that will fit on a given device in portrait screen orientation.
*/
+ (AATKitAdType) maximumBannerSizePortrait;

/**
 * Returns the AATKitAdType with maximum width that will fit on a given device in landscape screen orientation.
*/
+ (AATKitAdType) maximumBannerSizeLandscape;

/**
 * Enable debugging.
 *
 * When debugging is enabled (`YES`), there will be more information printed
 * to the console.
 *
 * *Default:* `NO`.
 */
+ (void) debug:(BOOL) flag;

/**
 * Enable extended debugging.
 *
 * Enable extended debugging for +[AATKit setPlacementPos:forPlacement:].
 * Extended debugging checks whether the placement is manipulated from
 * -[UIViewController viewWillAppear:]. Updating the placement before
 * presenting the view controller's view can render an application unstable.
 *
 * **NOTE:** Only disable when you know what you're doing.
 *
 * *Default:* `YES`.
 *
 * @see +[AATKit setPlacementPos:forPlacement:]
 */
+ (void) extendedDebug:(BOOL)yesOrNo;

/**
 * Enable Shake-to-Debug.
 *
 * By default, AATKit will display a popup box with information about the
 * framework version and the currently visible ads. Use `[AATKit debugShake:NO]`
 * to disable this behavior.
 *
 * *Default:* `YES`.
 */
+ (void) debugShake:(BOOL) flag;

/**
 * Collect debug information about AATKit.
 */
+ (nonnull NSString*) getDebugInfo;

/// Create a Request/Response Banner Placement
///
/// Use this method to create a banner placement with the default configuration.
///
/// @param name The name of the new placement.
+ (nullable NSObject<AATBannerPlacementProtocol>*)createBannerPlacementWithName:(nonnull NSString*)name
    NS_SWIFT_NAME(createBannerPlacement(name:));

/// Create a Request/Response Banner Placement
///
/// Use this method to create a banner placement with the default configuration.
///
/// @param name The name of the new placement.
/// @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
+ (nullable NSObject<AATBannerPlacementProtocol>*)createBannerPlacementWithName:(nonnull NSString*)name
                                                          andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate
    NS_SWIFT_NAME(createBannerPlacement(name:statisticsDelegate:));

/// Create a Request/Response Banner Placement
///
/// Use this method to create a banner placement with the default configuration.
///
/// @param name The name of the new placement.
/// @param configuration The configuration for this placement.
///
/// **NOTE:** The configuration will be copied into the new placement. The
/// placement will not be affected by modifications to `configuration` after
/// it has been created.
+ (nullable NSObject<AATBannerPlacementProtocol>*)createBannerPlacementWithName:(nonnull NSString*)name
                                                                 configuration:(nullable AATBannerConfiguration*)configuration
    NS_SWIFT_NAME(createBannerPlacement(name:configuration:));

/// Create a Request/Response Banner Placement
///
/// Use this method to create a banner placement with the default configuration.
///
/// @param name The name of the new placement.
/// @param configuration The configuration for this placement.
/// @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
///
/// **NOTE:** The configuration will be copied into the new placement. The
/// placement will not be affected by modifications to `configuration` after
/// it has been created.configuration:(nullable AATBannerConfiguration*)configuration
+ (nullable NSObject<AATBannerPlacementProtocol>*)createBannerPlacementWithName:(nonnull NSString*)name
                                                                 configuration:(nullable AATBannerConfiguration*)configuration
                                                          andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate
    NS_SWIFT_NAME(createBannerPlacement(name:configuration:statisticsDelegate:));

/**
 * Create a new Placement.
 *
 * @param type Specifies the type of the placement. Banner placements are
 * treated differently from full screen placements.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules. You must not use the
 * names `"banner"`, `"fullscreen"`, and `"promo"`.
 */
+ (nullable NSObject<AATKitPlacement>*) createPlacementWithName:(nonnull NSString *) placementName andType:(AATKitAdType)type NS_RETURNS_RETAINED;

/**
 * Create a new Placement.
 *
 * @param type Specifies the type of the placement. Banner placements are
 * treated differently from full screen placements.
 *
 * @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules. You must not use the
 * names `"banner"`, `"fullscreen"`, and `"promo"`.
 */

+ (nullable NSObject<AATKitPlacement>*) createPlacementWithName:(nonnull NSString *) placementName
                                                        andType:(AATKitAdType)type
                                          andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate NS_RETURNS_RETAINED;

/**
 * Create a new placement for rewarded video.
 *
 * *NOTE:* It is only possible to create one rewarded video placement. When
 * trying to create a second rewarded video placement, your app will crash.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules.
 */
+ (nullable NSObject<AATKitPlacement>*)createRewardedVideoPlacement:(nonnull NSString*)placementName;

/**
 * Create a new placement for rewarded video.
 *
 * @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
 * *NOTE:* It is only possible to create one rewarded video placement. When
 * trying to create a second rewarded video placement, your app will crash.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules.
 */
+ (nullable NSObject<AATKitPlacement>*)createRewardedVideoPlacement:(nonnull NSString*)placementName
                                              andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate;

/**
* Create a new placement for AppOpen Ad.
*
* *NOTE:* You should register your `placementName` on the AddApptr website
* if you intend to target it with specific rules.
*/
+ (nullable NSObject<AATKitPlacement>*)createAppOpenAdPlacement:(nonnull NSString*)placementName;

/**
* Create a new placement for AppOpen Ad
*
* @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
*/
+ (nullable NSObject<AATKitPlacement>*)createAppOpenAdPlacement:(nonnull NSString*)placementName
                                             andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate;

/**
 * Create a new placement for native ads.
 *
 * @param supportsMainImage Specifies if the native ads returned should have the main image asset. Keep in mind that if main image is used, it has to be displayed.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules.
 */
+ (nullable NSObject<AATKitPlacement>*)createNativeAdPlacement:(nonnull NSString*)placementName
                                             supportsMainImage:(BOOL)supportsMainImage;

/**
 * Create a new placement for native ads.
 *
 * @param supportsMainImage Specifies if the native ads returned should have the main image asset. Keep in mind that if main image is used, it has to be displayed.
 * @param statisticsDelegate The statistics delegate of the new placement. It would be notified with the statistics events.
 *
 * *NOTE:* You should register your `placementName` on the AddApptr website
 * if you intend to target it with specific rules.
 */
+ (nullable NSObject<AATKitPlacement>*)createNativeAdPlacement:(nonnull NSString*)placementName
                                             supportsMainImage:(BOOL)supportsMainImage
                                         andStatisticsDelegate:(nullable NSObject <AATKitStatisticsDelegate>*)statisticsDelegate;

/**
 * Obtain a reference to a previously created placement.
 *
 * This method can be used to obtain a reference to a previously defined
 * placement.
 */
+ (nullable NSObject<AATKitPlacement>*) getPlacementWithName:(nonnull NSString *)placementName;

/**
 * Start automatic (re)loading of ads for a certain placement.
 *
 * Use `+[AATKit stopPlacementAutoReload:]` to restore the manual reload
 * mode.
 *
 * **For Banner Placements:**
 *
 * Use this method if you don't want to manually reload the ad of a banner
 * placement. This method will automatically reload banners every 30
 * seconds.
 *
 * *NOTE:* You must not use auto reload on more than one banner placement at
 * any time.
 *
 * Use `+[AATKit startPlacementAutoReloadWithSeconds:forPlacement:]` to
 * specify a custom time interval.
 *
 * **For Full Screen Placements:**
 *
 * Use this method to automatically load a new full screen ad while the
 * current one is being displayed.
 *
 * *NOTE:* You should not use both this method and `+[AATKit
 * reloadPlacement:]`.
 *
 * @see +[AATKit startPlacementAutoReloadWithSeconds:forPlacement:]
 * @see +[AATKit stopPlacementAutoReload:]
 * @see +[AATKit reloadPlacement:]
 */
+ (void) startPlacementAutoReload:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Disable automatic reloading for a placement.
 */
+ (void) stopPlacementAutoReload:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Set the parent view controller for a specific placement.
 *
 * This setting (if used) will override the global view controller. To
 * restore the global behavior, pass `nil` as an argument.
 *
 * When you implement a custom `UIViewController` which is supposed to
 * present any kind of ad, follow these rules to avoid unintended behavior:
 *
 * - Override the implementation of `-viewWillAppear:` and set the current
 *   view controller (`self`) with this method.
 * - Override the implementation of `-viewWillDisappear:` and reset the
 *   view controller by passing `nil` to this method.
 */
+ (void) setPlacementViewController:(nullable UIViewController*)con forPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Load/reload the content of a placement.
 *
 * After a banner placement was created, no ad was downloaded to be
 * displayed. Use this method to download the initial content for a
 * placement.
 *
 * Banner placements can reload their content by calling this method again.
 * The delegate will be notified about the reload result.
 *
 * Full screen placements need this method to download the full screen ad
 * before it is supposed to be displayed. The delegate will be notified
 * about the reload result.
 *
 * After using this method of these three delegate methods will be invoked:
 * - -[AATKitDelegate AATKitHaveAd:]
 * - -[AATKitDelegate AATKitNoAds:]
 * - -[AATKitDelegate AATKitShowEmpty:]
 */
+ (BOOL) reloadPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Load/reload the content of a placement.
 *
 * After a banner placement was created, no ad was downloaded to be
 * displayed. Use this method to download the initial content for a
 * placement.
 *
 * Banner placements can reload their content by calling this method again.
 * The delegate will be notified about the reload result.
 *
 * Full screen placements need this method to download the full screen ad
 * before it is supposed to be displayed. The delegate will be notified
 * about the reload result.
 *
 * After using this method of these three delegate methods will be invoked:
 * - -[AATKitDelegate AATKitHaveAd:]
 * - -[AATKitDelegate AATKitNoAds:]
 * - -[AATKitDelegate AATKitShowEmpty:]
 *
 * @param forceLoad If `YES`, the placement will be reloaded even if other
 * requirements like the minimum display time are not met.
 */
+ (BOOL) reloadPlacement:(nonnull NSObject<AATKitPlacement>*) placement forceLoad:(BOOL) forceLoad;


/**
 * Set Targeting Information.
 *
 * Some networks support providing additional information to improve the
 * ads for the current context. Overrides the global information set with
 * `+setTargetingInfo:`.
 *
 * You can set a dictionary like this: `@{@"interests": @[@"sports", @"stocks"], @"gender": @"female"}`.
 *
 * Supported types for the keys: NSString.
 *
 * Supported types for the values: NSString, NSNumber, and NSArray containing NSString and/or NSNumber.
 *
 * Please contact the support team for help when defining targeting information.
 */
+ (void) setTargetingInfo:(nonnull NSDictionary*)targetingInfo forPlacement:(nonnull NSObject<AATKitPlacement>*)placement;


/**
 * adds an ad network to the list of ad networks that receive targeting keywords (if any set).
 * if no ad networks are added, any set keywords will be delivered to all ad networks supporting keyword targeting.
 * if you try to add an ad network that was already added before, nothing will happen, i.e. no error will be thrown.
 */
+ (void)addAdNetworkForKeywordTargeting:(enum AATKitAdNetwork)adNetwork;

/**
 * removes an ad network to the list of ad networks that receive targeting keywords (if any set).
 * if no ad networks are added, any set keywords will be delivered to all ad networks supporting keyword targeting.
 * if you try to remove an ad network that wasn't added before, nothing will happen, i.e. no error will be thrown.
 */
+ (void)removeAdNetworkForKeywordTargeting:(enum AATKitAdNetwork)adNetwork;

/**
 * Sets the content URL of ad requests.
 * By now only the ad requests for Google with the GADRequest class support adding a content URL.
 */
+ (void)setContentTargetingURL:(nullable NSString*)targetingURL;

/**
 * Sets the content URL of ad requests for a specific placement.
 * If you use "+ (void)setContentTargetingUrl:(nullable NSString*)targetingURL;" after executing this method,
 * the content URL for the specific placement will not be overwritten.
 * By now only the ad requests for Google with the GADRequest class support adding a content URL.
 */
+ (void)setContentTargetingURL:(nullable NSString*)targetingURL forPlacement:(nonnull NSObject<AATKitPlacement>*)placement;

/**
 * Query the current status of a placement.
 *
 * Use this call to find out whether a placement has an ad ready.
 *
 * *NOTE:* It is recommended to use the AATKitDelegate protocol to receive
 * updates for the placement status.
 */
+ (BOOL) haveAdForPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/// @name Banner Advertisements

/**
 * Start reloading placements automatically with a customized time interval.
 *
 * If you do not want to manually reload banner ads, you can use this method
 * to specify an interval for automatic reloading of banner ads.
 *
 *
 * *NOTE:* You should not mix this call with `+[AATKit reloadPlacement:]`.
 *
 * @see +[AATKit stopPlacementAutoReload:]
 */
+ (void) startPlacementAutoReloadWithSeconds:(int) seconds forPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Get the banner container view.
 *
 * Returns the UIView containing the banner placement's content.
 *
 * *NOTE:* This view will be transparent (ans thus: invisible) until either
 * `+[AATKit reloadPlacement:]` or `+[AATKit startPlacementAutoReload:]`
 * have been called.
 *
 * To show the banner, you will have to add this view to your view
 * hierarchy. You might also need to bring the view to the foreground.
 */
+ (nullable UIView*) getPlacementView:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Get the required size of the content.
 *
 * You can use this size to manually calculate the position of the view or
 * to set up auto-layout constraints.
 */
+ (CGSize) getPlacementContentSize:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Specify the vertical alignment of the banner within the container view.
 *
 * Some of the “standard” banner ad formats are actually not the same for
 * all ad networks. E.g. some networks provide 320x48 sized banners for the
 * 320x50 category, some provide 320x53. AATKit allows for these differences
 * by creating a view that will fit the largest banner size (in this case,
 * 320x53). Smaller ads can be aligned to the top, the bottom or the middle
 * of the container view.
 */
+ (void) setPlacementAlign:(AATKitBannerAlign) align forPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Define the top-left position of the banner container.
 */
+ (void) setPlacementPos:(CGPoint) pos forPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Provide a default image for banner ads.
 *
 * Using this call, a banner placement can display a static image when no
 * ad could be loaded. The image will be scaled to fill the container view.
 * Use `nil` to revert to the default behavior.
 */
+ (void) setPlacementDefaultImage:(nullable UIImage *) image forPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/// @name Full Screen Advertizements

/**
 * Display a full screen placement.
 */
+ (BOOL) showPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/// @name Native Advertizements

/**
 * Describe the Rating of the Advertized Product.
 *
 * This can be used for native ads that are advertizing for other apps. Your
 * app can use this e.g. to display a star rating.
 */
struct AATKitNativeAdRating {
    /// The rating of the app, e.g. `3.5`.
    float value;
    /// The Scale for the rating, usually something like `5.0`
    float scale;
    /**
     * Indicates whether the ad network supports rating at all.
     *
     * *NOTE:* Just because this value is `YES`, does not mean that there is
     * useful data here.
     */
    BOOL hasRating;
};

// native placement lifecycle methods

/**
 * Query the number of ad requests that are pending on a placement.
 */
+ (NSUInteger) currentlyLoadingNativeAdsOnPlacement:(nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Get the native ad object for a placement.
 *
 * This method is usually called in implementations of
 * `-[id\<AATKitDelegate> AATKitHaveAd:]`.
 */
+ (nullable NSObject<AATKitNativeAd>*) getNativeAdForPlacement: (nonnull NSObject<AATKitPlacement>*) placement;

/**
 * Call this method when a native ad gets displayed for the first time.
 * This will make sure that the ad space will be correctly reported in the
 * AddApptr dashboard.
 */
+ (void) appHasAdSpaceForNativePlacement:(nonnull NSObject<AATKitPlacement>*)placement;

/**
 * Call this method before trying to call `+[AATKit reloadPlacement:]` to
 * avoid requesting ads when such a request will fail anyway.
 * This method can be used for native and fullscreen placements.
 */
+ (BOOL) isFrequencyCapReachedForPlacement:(nonnull NSObject<AATKitPlacement>*)placement;

/**
 * Specify the view controller for a native ad.
 *
 * The view controller can be used to display full screen ads after the user
 * selected a view.
 */
+ (void) setViewController: (nullable UIViewController*) con forNativeAd: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Specify the tracking view for a native ad.
 *
 * The tracking view will be used by the SDK to determine the duration of
 * an ad's visibility.
 *
 * @param mainImageView View used to show the main image of the ad. Can be nil.
 *
 * @param iconView View used to show the icon of the native ad.
 */
+ (void) setTrackingView: (null_unspecified UIView*) trackingView forNativeAd: (nonnull NSObject<AATKitNativeAd>*) nativeAd mainImageView: (nullable UIView*) mainImageView iconView:(nullable UIView*) iconView __deprecated_msg("This method is deprecated. Use + (void) setTrackingView: (null_unspecified UIView*) trackingView forNativeAd: (nonnull NSObject<AATKitNativeAd>*) nativeAd mainImageView: (nullable UIView*) mainImageView iconView:(nullable UIView*) iconView CTAView:(nullable UIView*) ctaView; instead.");

/**
 * Specify the tracking view for a native ad.
 *
 * The tracking view will be used by the SDK to determine the duration of
 * an ad's visibility.
 *
 * @param mainImageView View used to show the main image of the ad. Can be nil.
 *
 * @param iconView View used to show the icon of the native ad.
 *
 * @param ctaView CTA view of the native ad.
 */
+ (void) setTrackingView: (null_unspecified UIView*) trackingView forNativeAd: (nonnull NSObject<AATKitNativeAd>*) nativeAd mainImageView: (nullable UIView*) mainImageView iconView:(nullable UIView*) iconView CTAView:(nullable UIView*) ctaView;

/**
 * Remove the tracking view for from native ad.
 *
 * Use this method to remove the tracking view from an ad before configuring
 * it as the tracking view of a different ad.
 */
+ (void) removeTrackingViewForNativeAd: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the title for the native ad.
 */
+ (nullable NSString*)   getNativeAdTitle: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the description for the native ad.
 */
+ (nullable NSString*)   getNativeAdDescription: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the URL string for the native ad image.
 */
+ (nullable NSString*)   getNativeAdImageURL: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the URL string for the native ad icon.
 */
+ (nullable NSString*)   getNativeAdIconURL: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the title for the call to action item.
 */
+ (nullable NSString*)   getNativeAdCallToAction: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the UIImageView instance for the native ad branding logo.
 */
+ (nullable UIImageView*) getNativeAdBrandingLogoView:(nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the name of the advertizer for a native ad.
 */
+ (nullable NSString*)   getNativeAdAdvertiser: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the rating of the product being advertized.
 */
+ (struct AATKitNativeAdRating) getNativeAdRating: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Get the network providing this native ad.
 */
+ (enum AATKitAdNetwork) getNativeAdNetwork: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Check if a native ad is expired.
 *
 * If you implement pre-fetching of native ads, you can use this method
 * (periodically) to check for stale content.
 */
+ (BOOL) isNativeAdExpired: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Check if a native ad is ready to be displayed.
 */
+ (BOOL) isNativeAdReady: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Check if a native ad is a video ad.
 */
+ (BOOL) isNativeAdVideo: (nonnull NSObject<AATKitNativeAd>*) nativeAd;

/**
 * Set NativeAd icon position.
 * @param position ad choices icon position
 */
+ (void) setAdChoicesIconPosition: (AdChoicesIconPosition) position;

/**
 * Prepare promotional full screen ads.
 *
 * Prepares promotional fullscreen ads (i.e. load and cache) for display but
 * does not display the ads yet.
 *
 * Calling +[AATKit enablePromo] does this automatically. Usually, there is
 * no reason to call this method.
 *
 * @see +[AATKit enablePromo]
 */
+ (void) preparePromo;

/**
 * Show a promotional full screen ad (if available).
 *
 *
 * *NOTE:* Make sure you have called +[AATKit enablePromo] or +[AATKit
 * preparePromo] before calling this.
 *
 * @param force `YES` to enable the promo to be shown more often than every
 * hour. `NO` to display the promo is every per hour.
 */
+ (BOOL) showPromo:(BOOL)force;

/**
 * …
 *
 * Use this only if you are using per-placement view controllers.
 */
+ (void) setPromoViewController:(nullable UIViewController*)viewcon;

// @name Choosing Ad Networks

/**
 * Disable ad networks programmatically.
 *
 * @see +[AATKit reenableAdNetwork:]
 */
+ (void) disableAdNetwork:(enum AATKitAdNetwork)adNetwork;

/**
 * Enable ad networks programmatically.
 *
 * Usually, you don't have to enable ad networks. You can use this method
 * and `+[AATKit disableAdNetwork:]` to implement your own switches for
 * ad networks.
 *
 * @see +[AATKit disableAdNetwork:]
 */
+ (void) reenableAdNetwork:(enum AATKitAdNetwork)adNetwork;

/**
* Gets NSSet of all banner sizes that fit the screen with portrait orientation
* The returned sizes correspond to the correct AATAdType enum value
* @return NSSet<NSNumber*> of available sizes
*/
+ (NSSet<NSNumber*>*_Nonnull)fittingBannerSizesPortrait;

/**
* Gets NSSet of all banner sizes that fit the screen with landscape orientation
* The returned sizes correspond to the correct AATAdType enum value
* @return NSSet<NSNumber*> of available sizes
*/
+ (NSSet<NSNumber*>*_Nonnull)fittingBannerSizesLandscape;

/**
 * Mute/Unmute video ads across all ads
 * Currently available with GoogleMobileAds
 * @param muted BOOL
 */
+ (void) setVideoAdsMuted:(BOOL)muted;
@end
