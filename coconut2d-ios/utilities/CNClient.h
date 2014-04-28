//
//  CNClient.h
//  Coconut2D
//
//  Created by Moky on 12-10-29.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CNClient : NSObject

+ (CGSize) getScreenSize;
+ (CGFloat) getScreenScale;
+ (CGSize) getWindowSize;

+ (NSString *) getHardware;
+ (NSString *) getDeviceIdentifier;
+ (NSString *) getDeviceModel;
+ (NSString *) getSystemName;
+ (NSString *) getSystemVersion;

+ (NSString *) getBundleVersion;

+ (void) disableIdleTimer;

// HTTP Request
+ (NSString *) getClientParameters; // for stat

+ (BOOL) openURL:(NSString *)urlString;

@end
