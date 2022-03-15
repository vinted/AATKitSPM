//
// Copyright 2017 - present FeedAd GmbH. All rights reserved.
//
// By using the FeedAd SDK, you agree to our Terms of Service:
// https://feedad.com/tos
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

/// Defines the gender of an user for use with FAConfig
typedef NS_ENUM(NSInteger, FAGender) {
    /// Gender of user is not known (default)
    FAGenderUnknown,
    
    /// User is female
    FAGenderFemale,
    
    /// User is male
    FAGenderMale
};

NS_ASSUME_NONNULL_END
