//
//  DTBAdNetworkInfo.h
//  DTBiOSSDK
//
//  Created by Jammula, Nimitha on 1/4/22.
//  Copyright © 2022 amazon.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum{
    DTBADNETWORK_GOOGLE_AD_MANAGER,
    DTBADNETWORK_MOPUB_AD_SERVER,
    DTBADNETWORK_ADMOB,
    DTBADNETWORK_AD_GENERATION,
    DTBADNETWORK_IRON_SOURCE,
    DTBADNETWORK_MAX,
    DTBADNETWORK_NIMBUS,
    DTBADNETWORK_OTHER
} DTBAdNetwork;

extern NSString * _Nonnull  const FormatType_toString[];

NS_ASSUME_NONNULL_BEGIN

@interface DTBAdNetworkInfo : NSObject

@property NSString *adNetworkName;
@property NSMutableDictionary *adNetworkProperties;

-(instancetype)initWithNetworkName:(DTBAdNetwork)adNetworkName;
-(NSString *) getAdNetworkName;
-(DTBAdNetworkInfo *) setAdNetworkProperties:(NSString *)adNetworkProperties
                              adNetworkValue:(NSString *) adNetworkValue;
-(NSString *) getAdNetworkProperties:(NSString *)adNetworkProperties;

@end

NS_ASSUME_NONNULL_END
