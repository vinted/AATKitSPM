// swift-tools-version:5.5
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
                                                   "AATKit-Unity"]),
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
        .package(name: "AppNexusSDK", url: "https://github.com/appnexus/mobile-sdk-ios", .exact("7.16.0")),
        .package(name: "GoogleAppMeasurement", url: "https://github.com/google/GoogleAppMeasurement.git", .exact("8.8.0")),
    ],
    targets: [
        .target(name:"AATKit-Core",
                dependencies: ["AATKitFramework"],
                path: "./Sources/AATKit"),
        
            .target(name:"AATKit-M1-Core",
                    dependencies: ["AATKitFramework-M1"],
                    path: "./Sources/AATKit-M1"),
        
        // MARK - Dependencies Targets
        .target(name: "AATKit-GoogleMobileAds",
                dependencies: [ "GoogleMobileAds",
                                "AATDependencyHelper",
                                .product(name: "GoogleAppMeasurement", package: "GoogleAppMeasurement")
                              ],
                path: "./Sources/GoogleMobileAdsSources"),
        
            .target(name: "AATKit-AppLovin",
                    dependencies: ["AppLovin"],
                    path: "./Sources/AppLovinSources",
                    resources: [
                        .process("../../Dependencies/AppLovin/Bundle/AppLovinSDKResources.bundle")
                    ]
                   ),
        
            .target(name:"AATKit-Amazon",
                    dependencies: ["DTBiOSSDK"],
                    path: "./Sources/AmazonSources"),
        
            .target(name:"AATKit-OguryCMP",
                    dependencies: ["OguryCMP"],
                    path: "./Sources/OguryCMPSources"),

            .target(name:"AATKit-GoogleCMP",
                    dependencies: ["GoogleCMP"],
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
        
            .target(name:"AATKit-AdColony",
                    dependencies: ["AATAdColonyAdapter","AdColony"],
                    path: "./Sources/AdColonySources"),
        
            .target(name:"AATKit-YOC",
                    dependencies: ["VisxSDK"],
                    path: "./Sources/YOCSources"),
        
            .target(name:"AATKit-InMobi",
                    dependencies: ["InMobiSDK"],
                    path: "./Sources/InMobiSources"),
        
            .target(name:"AATKit-AppNexus",
                    dependencies: ["AppNexusSDK"],
                    path: "./Sources/AppNexusSources"),
        
            .target(name:"AATKit-MoPub",
                    dependencies: ["MoPubSDK", "OMSDK_Mopub"],
                    path: "./Sources/MoPubSources"),
        
            .target(name:"AATKit-PubNative",
                    dependencies: ["Pubnative"],
                    path: "./Sources/PubnativeSources"),
        
            .target(name:"AATKit-Unity",
                    dependencies: ["Unity"],
                    path: "./Sources/UnitySources"),
        
        // Mark: Binary Targets
        .binaryTarget(name: "AATKitFramework", path: "./Dependencies/AATKit/AATKit.xcframework"),
        .binaryTarget(name: "AATKitFramework-M1", path: "./Dependencies/AATKit-M1/AATKit.xcframework"),
        
        // Google
        .binaryTarget(name: "GoogleMobileAds", path: "./Dependencies/Google/GoogleMobileAds.xcframework"),
        .binaryTarget(name: "AATDependencyHelper", path: "./Dependencies/Google/AATDependencyHelper.xcframework"),
        
        // Amazon
        .binaryTarget(name: "DTBiOSSDK", path: "./Dependencies/Amazon/DTBiOSSDK.xcframework"),
        
        // Ogury CMP
        .binaryTarget(name: "OguryCMP", path: "./Dependencies/Ogury/OguryChoiceManager.xcframework"),

        // Google CMP
        .binaryTarget(name: "GoogleCMP", path: "./Dependencies/Google/UserMessagingPlatform.xcframework"),
        
        // AppLovin
        .binaryTarget(name: "AppLovin", path: "./Dependencies/AppLovin/AppLovinSDK.xcframework"),
        
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


