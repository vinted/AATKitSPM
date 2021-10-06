// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "AATKitSPM",
    defaultLocalization: "en",
    platforms: [.iOS(.v10)],
    products: [
        .library(
            name: "AATKitSPM",
            targets: ["AATKitSPM"]
        ),
        .library(
            name: "AATKitSPM-M1",
            targets: ["AATKitSPM-M1"]
        )
    ],
    dependencies: [
        // AdNetworks supporting SPM
        .package(name: "AppNexusSDK", url: "https://github.com/appnexus/mobile-sdk-ios", .exact("7.16.0")),
        .package(name: "TeadsSDK", url: "https://github.com/teads/TeadsSDK-iOS", .exact("4.8.7")),
        .package(name: "GoogleAppMeasurement", url: "https://github.com/google/GoogleAppMeasurement.git", .exact("8.8.0")),
    ],
    targets: [
        .target(name: "AATKitSPM",
                dependencies: [
                    "AATKitFramework", "DTBiOSSDK", "OguryCMP", "AppLovin",
                    "OMSDK_Smaato","SmaatoSDKBanner", "SmaatoSDKCore", "SmaatoSDKInterstitial", "SmaatoSDKNative", "SmaatoSDKOpenMeasurement", "SmaatoSDKOutstream", "SmaatoSDKRewardedAds", "SmaatoSDKRichMedia", "SmaatoSDKVideo",
                    "SASDisplayKit","SCSCoreKit","AATAdColonyAdapter","AdColony", "VisxSDK", "InMobiSDK",
                    "AppNexusSDK", "TeadsSDK", "MoPubSDK", "OMSDK_Mopub", "Pubnative",
                    "GoogleMobileAds", "GoogleCMP", "AATDependencyHelper", "Unity",
                    .product(name: "GoogleAppMeasurement", package: "GoogleAppMeasurement")
                ],
                path: "./Sources/AATKitSPM",
                resources: [
                    .process("../../Dependencies/AppLovin/Bundle/AppLovinSDKResources.bundle")
                ]
               ),
        
        .target(name: "AATKitSPM-M1",
                dependencies: [
                    "AATKitFramework-M1", "DTBiOSSDK", "OguryCMP", "AppLovin",
                    "OMSDK_Smaato","SmaatoSDKBanner", "SmaatoSDKCore", "SmaatoSDKInterstitial", "SmaatoSDKNative", "SmaatoSDKOpenMeasurement", "SmaatoSDKOutstream", "SmaatoSDKRewardedAds", "SmaatoSDKRichMedia", "SmaatoSDKVideo",
                    "SASDisplayKit","SCSCoreKit","AATAdColonyAdapter","AdColony", "VisxSDK", "InMobiSDK",
                    "AppNexusSDK", "TeadsSDK", "MoPubSDK", "OMSDK_Mopub", "Pubnative",
                    "GoogleMobileAds", "GoogleCMP", "AATDependencyHelper",
                    .product(name: "GoogleAppMeasurement", package: "GoogleAppMeasurement")
                ],
                path: "./Sources/AATKitSPM-M1",
                resources: [
                    .process("../../Dependencies/AppLovin/Bundle/AppLovinSDKResources.bundle")
                ]
               ),
        
        .binaryTarget(name: "AATKitFramework", path: "./Dependencies/AATKit/AATKit.xcframework"),
        .binaryTarget(name: "AATKitFramework-M1", path: "./Dependencies/AATKit-M1/AATKit.xcframework"),
        
        // Google
        .binaryTarget(name: "GoogleMobileAds", path: "./Dependencies/Google/GoogleMobileAds.xcframework"),
        .binaryTarget(name: "GoogleCMP", path: "./Dependencies/Google/UserMessagingPlatform.xcframework"),
        .binaryTarget(name: "AATDependencyHelper", path: "./Dependencies/Google/AATDependencyHelper.xcframework"),

        // Amazon
        .binaryTarget(name: "DTBiOSSDK", path: "./Dependencies/Amazon/DTBiOSSDK.xcframework"),

        // Ogury
        .binaryTarget(name: "OguryCMP", path: "./Dependencies/Ogury/OguryChoiceManager.xcframework"),

        // AppLovin
        .binaryTarget(name: "AppLovin", path: "./Dependencies/AppLovin/AppLovinSDK.xcframework"),
//        .target(name: "ApplovinResources", path: "./Sources/AppLovin", resources: [.process("Bundle")]),

        // Smaato
        .binaryTarget(name: "OMSDK_Smaato", path: "./Dependencies/Smaato/OMSDK_Smaato.xcframework"),
        .binaryTarget(name: "SmaatoSDKBanner", path: "./Dependencies/Smaato/SmaatoSDKBanner.xcframework"),
        .binaryTarget(name: "SmaatoSDKCore", path: "./Dependencies/Smaato/SmaatoSDKCore.xcframework"),
        .binaryTarget(name: "SmaatoSDKInterstitial", path: "./Dependencies/Smaato/SmaatoSDKInterstitial.xcframework"),
        .binaryTarget(name: "SmaatoSDKNative", path: "./Dependencies/Smaato/SmaatoSDKNative.xcframework"),
        .binaryTarget(name: "SmaatoSDKOpenMeasurement", path: "./Dependencies/Smaato/SmaatoSDKOpenMeasurement.xcframework"),
        .binaryTarget(name: "SmaatoSDKOutstream", path: "./Dependencies/Smaato/SmaatoSDKOutstream.xcframework"),
        .binaryTarget(name: "SmaatoSDKRewardedAds", path: "./Dependencies/Smaato/SmaatoSDKRewardedAds.xcframework"),
        .binaryTarget(name: "SmaatoSDKRichMedia", path: "./Dependencies/Smaato/SmaatoSDKRichMedia.xcframework"),
        .binaryTarget(name: "SmaatoSDKVideo", path: "./Dependencies/Smaato/SmaatoSDKVideo.xcframework"),

        //SmartAd
        .binaryTarget(name: "SASDisplayKit", path: "./Dependencies/SmartAd/SASDisplayKit.xcframework"),
        .binaryTarget(name: "SCSCoreKit", path: "./Dependencies/SmartAd/SCSCoreKit.xcframework"),

        //AdColony
        .binaryTarget(name: "AATAdColonyAdapter", path: "./Dependencies/AdColony/AATAdColonyAdapter.xcframework"),
        .binaryTarget(name: "AdColony", path: "./Dependencies/AdColony/AdColony.xcframework"),

        // YOC
        .binaryTarget(name: "VisxSDK", path: "./Dependencies/YOC/VisxSDK.xcframework"),

        // InMobi
        .binaryTarget(name: "InMobiSDK", path: "./Dependencies/InMobi/InMobiSDK.xcframework"),

        // MoPub
        .binaryTarget(name: "MoPubSDK", path: "./Dependencies/MoPub/MoPubSDK.xcframework"),
        .binaryTarget(name: "OMSDK_Mopub", path: "./Dependencies/MoPub/OMSDK_Mopub.xcframework"),

        // PubNative
        .binaryTarget(name: "Pubnative", path: "./Dependencies/Pubnative/HyBid.xcframework"),

        // Unity
        .binaryTarget(name: "Unity", path: "./Dependencies/Unity/UnityAds.xcframework"),
    ]
)


