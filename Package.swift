// swift-tools-version:5.4
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "AATKitSPM",
    defaultLocalization: "en",
    platforms: [.iOS(.v10)],
    products: [

        .library(name: "AATKit-Core", targets: ["AATKit-Core"]),
        .library(name: "AATKit-M1-Core", targets: ["AATKit-M1-Core"]),

        // Dependencies
        .library(name: "AATKit-GoogleMobileAds", targets: ["AATKit-GoogleMobileAds"]),
        .library(name: "AATKit-AppLovin", targets: ["AATKit-AppLovin"]),
        .library(name: "AATKit-Amazon", targets: ["AATKit-Amazon"]),
        .library(name: "AATKit-Smaato", targets: ["AATKit-Smaato"]),
        .library(name: "AATKit-SmartAd", targets: ["AATKit-SmartAd"]),
        .library(name: "AATKit-AdColony", targets: ["AATKit-AdColony"]),
        .library(name: "AATKit-YOC", targets: ["AATKit-YOC"]),
        .library(name: "AATKit-InMobi", targets: ["AATKit-InMobi"]),
        .library(name: "AATKit-AppNexus", targets: ["AATKit-AppNexus"]),
        .library(name: "AATKit-MoPub", targets: ["AATKit-MoPub"]),
        .library(name: "AATKit-PubNative", targets: ["AATKit-PubNative"]),
        .library(name: "AATKit-Unity", targets: ["AATKit-Unity"]),
        .library(name: "AATKit-Vungle", targets: ["AATKit-Vungle"]),
        .library(name: "AATKit-AATAdMobMediationAdapter", targets: ["AATAdMobMediationAdapter"]),

        // CMPs
        .library(name: "AATKit-OguryCMP", targets: ["AATKit-OguryCMP"]),
        .library(name: "AATKit-GoogleCMP", targets: ["AATKit-GoogleCMP"]),

        // Default Dependencies
        .library(name: "AATKit-Default", targets: ["AATKit-GoogleMobileAds",
                                                   "AATKit-AppLovin",
                                                   "AATKit-Amazon",
                                                   "AATKit-OguryCMP",
                                                   "AATKit-GoogleCMP",
                                                   "AATKit-Smaato",
                                                   "AATKit-SmartAd",
                                                   "AATKit-AdColony",
                                                   "AATKit-YOC",
                                                   "AATKit-InMobi",
                                                   "AATKit-AppNexus",
                                                   "AATKit-MoPub",
                                                   "AATKit-PubNative",
                                                   "AATKit-Unity",
                                                   "AATKit-Vungle"
                                                  ]),
        // M1 Default dependencies
        .library(name: "AATKit-M1-Default", targets: ["AATKit-GoogleMobileAds",
                                                      "AATKit-AppLovin",
                                                      "AATKit-Amazon",
                                                      "AATKit-OguryCMP",
                                                      "AATKit-GoogleCMP",
                                                      "AATKit-Smaato",
                                                      "AATKit-SmartAd",
                                                      "AATKit-AdColony",
                                                      "AATKit-InMobi",
                                                      "AATKit-AppNexus",
                                                      "AATKit-MoPub",
                                                      "AATKit-PubNative"
                                                     ]),

    ],
    dependencies: [
        // AdNetworks supporting SPM
        .package(name: "AppNexusSDK", url: "https://github.com/appnexus/mobile-sdk-ios", .exact("7.18.0")),
        .package(name: "GoogleAppMeasurement", url: "https://github.com/google/GoogleAppMeasurement.git", .exact("8.9.1")),
        .package(name: "AppLovinSDK", url: "https://github.com/AppLovin/AppLovin-MAX-Swift-Package.git", .exact("10.3.7"))
    ],
    targets: [
        // AATKit target
        .target(name:"AATKit-Core",
                dependencies: ["AATKit"],
                path: "./Sources/AATKit"),
        
        // AATKit M1 target
        .target(name:"AATKit-M1-Core",
                dependencies: ["AATKit-M1"],
                path: "./Sources/AATKit-M1"),

        // AATAdMobMediationAdapter target
        .target(name:"AATAdMobMediationAdapter",
                dependencies: [ "AATKit-GoogleMobileAds",
                                "AATDependencyHelper",
                                "AATKit"
                              ],
                path: "./Sources/AATAdMobMediationAdapter"),

        // MARK - Dependencies Targets
        .target(name: "AATKit-GoogleMobileAds",
                dependencies: [ "GoogleMobileAds",
                                "AATDependencyHelper",
                                .product(name: "GoogleAppMeasurement", package: "GoogleAppMeasurement")
                              ],
                path: "./Sources/GoogleMobileAdsSources"),
        .target(name:"AATKit-AdColony",
                dependencies: ["AATAdColonyAdapter","AdColony"],
                path: "./Sources/AdColonySources"),
        .target(name: "AATKit-AppLovin",
                dependencies: ["AppLovinSDK"],
                path: "./Sources/AppLovinSources"
               ),
        .target(name:"AATKit-AppNexus",
                dependencies: ["AppNexusSDK"],
                path: "./Sources/AppNexusSources"),
        .target(name:"AATKit-Amazon",
                dependencies: ["DTBiOSSDK"],
                path: "./Sources/AmazonSources"),
        .target(name:"AATKit-OguryCMP",
                dependencies: ["OguryChoiceManager"],
                path: "./Sources/OguryCMPSources"),
        .target(name:"AATKit-GoogleCMP",
                dependencies: ["UserMessagingPlatform"],
                path: "./Sources/GoogleCMPSources"),
        .target(name:"AATKit-Smaato",
                dependencies: ["OMSDK_Smaato",
                               "SmaatoSDKBanner",
                               "SmaatoSDKCore",
                               "SmaatoSDKInterstitial",
                               "SmaatoSDKNative",
                               "SmaatoSDKOpenMeasurement",
                               "SmaatoSDKOutstream",
                               "SmaatoSDKRewardedAds",
                               "SmaatoSDKRichMedia",
                               "SmaatoSDKVideo"],
                path: "./Sources/SmaatoSources"),
        .target(name:"AATKit-SmartAd",
                dependencies: ["SASDisplayKit","SCSCoreKit"],
                path: "./Sources/SmartAdSources"),
        .target(name:"AATKit-YOC",
               dependencies: ["VisxSDK"],
               path: "./Sources/YOCSources"),
        .target(name:"AATKit-InMobi",
                dependencies: ["InMobiSDK"],
                path: "./Sources/InMobiSources"),
        .target(name:"AATKit-MoPub",
                dependencies: ["MoPubSDK", "OMSDK_Mopub"],
                path: "./Sources/MoPubSources"),
        .target(name:"AATKit-PubNative",
                dependencies: ["HyBid", "OMSDK_Pubnativenet"],
                path: "./Sources/PubnativeSources"),
        .target(name:"AATKit-Unity",
                dependencies: ["UnityAds"],
                path: "./Sources/UnitySources"),
        .target(name:"AATKit-Vungle",
                dependencies: ["VungleSDK"],
                path: "./Sources/VungleSources"),

        // Mark: Binary Targets
        .binaryTarget(name: "AATKit", path: "./Dependencies/AATKit/AATKit.xcframework"),
        .binaryTarget(name: "AATKit-M1", path: "./Dependencies/AATKit-M1/AATKit-M1.xcframework"),

        // Google
        .binaryTarget(name: "GoogleMobileAds", path: "./Dependencies/Google/GoogleMobileAds.xcframework"),
        .binaryTarget(name: "AATDependencyHelper", path: "./Dependencies/Google/AATDependencyHelper.xcframework"),

        // Amazon
        .binaryTarget(name: "DTBiOSSDK", path: "./Dependencies/Amazon/DTBiOSSDK.xcframework"),

        // Ogury CMP
        .binaryTarget(name: "OguryChoiceManager", path: "./Dependencies/Ogury/OguryChoiceManager.xcframework"),

        // Google CMP
        .binaryTarget(name: "UserMessagingPlatform", path: "./Dependencies/Google/UserMessagingPlatform.xcframework"),

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
        .binaryTarget(name: "HyBid", path: "./Dependencies/Pubnative/HyBid.xcframework"),
        .binaryTarget(name: "OMSDK_Pubnativenet", path: "./Dependencies/Pubnative/OMSDK_Pubnativenet.xcframework"),

        // Unity
        .binaryTarget(name: "UnityAds", path: "./Dependencies/Unity/UnityAds.xcframework"),

        // Vungle
        .binaryTarget(name: "VungleSDK", path: "./Dependencies/Vungle/VungleSDK.xcframework"),
    ]
)


