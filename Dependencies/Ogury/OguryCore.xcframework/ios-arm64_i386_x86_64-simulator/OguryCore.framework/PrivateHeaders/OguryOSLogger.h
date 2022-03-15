//
//  Copyright © 2021 Ogury. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OguryLogger.h"

@class OguryLogMessage;

NS_ASSUME_NONNULL_BEGIN

@interface OguryOSLogger : NSObject <OguryLogger>

#pragma mark - Properties

@property (nonatomic, strong, nullable) id<OguryLogFormatter> logFormatter;

#pragma mark - Initialization

- (instancetype)initWithSubSystem:(nullable NSString *)subSystem category:(nullable NSString *)category NS_DESIGNATED_INITIALIZER;

- (void)logMessage:(OguryLogMessage *)message;

@end

NS_ASSUME_NONNULL_END
