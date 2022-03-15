//
//  Copyright © 2021 Ogury. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol OguryLogger;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, OguryLogLevel) {
    OguryLogLevelOff = -1,
    OguryLogLevelError,
    OguryLogLevelWarning,
    OguryLogLevelInfo,
    OguryLogLevelDebug,
    OguryLogLevelAll = NSIntegerMax
};

@interface OguryLog : NSObject

#pragma mark - Properties

@property (class, nonatomic, strong, readonly) OguryLog *sharedInstance;

@property (nonatomic, strong, readonly) NSMutableArray<id<OguryLogger>> *loggers;

#pragma mark - Methods

- (void)addLogger:(id<OguryLogger>)logger;

- (void)clearLoggers;

- (void)logMessage:(NSString *)message level:(OguryLogLevel)level;

- (void)log:(OguryLogLevel)level format:(NSString *)format, ...;

@end

NS_ASSUME_NONNULL_END
