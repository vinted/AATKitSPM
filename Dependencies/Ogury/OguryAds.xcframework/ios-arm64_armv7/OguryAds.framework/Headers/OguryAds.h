#import <Foundation/Foundation.h>

#import "OguryInterstitialAd.h"
#import "OguryOptinVideoAd.h"
#import "OguryBannerAd.h"
#import "OguryThumbnailAd.h"

#import "OguryAdsDelegate.h"
#import "OguryAdsInterstitial.h"
#import "OguryAdsOptinVideo.h"
#import "OguryAdsThumbnailAd.h"
#import "OguryAdsBanner.h"
#import "OGARewardItem.h"
#import "OguryTokenService.h"

typedef void (^SetupCompletionBlock)(NSError *error);
typedef void (^LoadCompletionBlock)(void);

__deprecated_msg("Use 'Ogury.startWithConfiguration' to start Ogury SDK instead.")
@interface OguryAds : NSObject

@property (nonatomic, strong) NSString *sdkVersion __deprecated_msg("Use 'Ogury.getSdkVersion' method instead");

+ (instancetype)shared;

- (void)setupWithAssetKey:(NSString *)assetKey;

- (void)setupWithAssetKey:(NSString *)assetKey andCompletionHandler:(SetupCompletionBlock)completionHandler;

- (void)setupWithAssetKey:(NSString *)assetKey andMediationName:(NSString *)mediationName;

- (void)setupWithAssetKey:(NSString *)assetKey mediationName:(NSString *)mediationName andCompletionHandler:(SetupCompletionBlock)completionHandler;

- (void)defineSDKType:(NSUInteger)sdkType;

- (void)defineMediationName:(NSString *)mediationName;

@end
