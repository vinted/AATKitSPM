//
//  Copyright © 2020-present Ogury. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface OGCInternal : NSObject

+ (instancetype)shared;
+ (NSString *)getVersion;
- (NSString *)getAdIdentifier;
- (NSString *)getInstanceToken;
- (NSString *)getConsentToken;
- (void)updateInstanceToken;
- (BOOL)isAdOptin;

@end

NS_ASSUME_NONNULL_END
