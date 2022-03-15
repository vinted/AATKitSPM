//
//  AATAdMobMediationAdapter.h
//  AATAdMobMediationAdapter
//
//  Created by Mahmoud Amer on 01.12.21.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//! Project version number for AATAdMobMediationAdapter.
FOUNDATION_EXPORT double AATAdMobMediationAdapterVersionNumber;

//! Project version string for AATAdMobMediationAdapter.
FOUNDATION_EXPORT const unsigned char AATAdMobMediationAdapterVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AATAdMobMediationAdapter/PublicHeader.h>
#import <AATAdMobMediationAdapter/AATAdMobMediationAdapter.h>

NS_ASSUME_NONNULL_BEGIN

@interface AATAdMobMediationAdapter: NSObject

@property (nullable, readonly) UIViewController *viewController;
@property (nullable, readonly) UIView *nativeAdMainImageView;
@property (nullable, readonly) UIView *nativeAdIconImg;
@property (nullable, readonly) UIView *nativeAdCTAView;

+ (nonnull instancetype)sharedInstance;

/// Sets the viewController that displays ads
///
/// This method should be called with the viewController's viewWillAppear() method
///
/// @param controller The view controller that will display the ad
- (void)viewControllerWillAppear:(nullable UIViewController *)controller;

/// Clears the viewController instance of AATAdMobMediationAdapter
///
/// This method should be called with the viewController's viewWillDisappear() method
///
/// @param controller The view controller that will released
- (void)viewControllerWillDisAppear:(nullable UIViewController *)controller;

/// initialize AATKit with default configuration
///
/// If you don't use the [AATKit initializeWithConfiguration:configuration];
/// 
/// Then at lease call this method to let AATKit starts earlier
- (void)initializeAATKitWithDefaultConfiguration;

- (void)checkAATKitInitStatus:(nullable NSNumber *)testModeAccId;

@end

NS_ASSUME_NONNULL_END
