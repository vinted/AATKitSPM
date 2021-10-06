//
//  SMAAdMarkup.h
//  SmaatoSDKNative
//
//  Created by Stefan Meyer on 23.04.21.
//  Copyright © 2021 Smaato Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SMAAdMarkup : NSObject
@property (nonatomic, copy, readonly, nullable) NSString *markup;
@property (nonatomic, copy, readonly, nullable) NSString *type;

- (instancetype)initWithMarkup:(NSString *)markup andType:(NSString *)type;

@end

NS_ASSUME_NONNULL_END
