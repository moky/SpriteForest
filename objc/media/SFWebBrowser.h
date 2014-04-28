//
//  WebBrowser.h
//  SpriteForest2
//
//  Created by Moky on 12-10-7.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SF_WEB_BROWSER_CLOSE_BUTTON @"web_close.png"

@interface SFWebBrowser : NSObject

+ (void) openURL:(NSString *)urlString;
+ (void) openURL:(NSString *)urlString inFrame:(CGRect)frame;
+ (void) openURL:(NSString *)urlString inFrame:(CGRect)frame closeButton:(NSString *)imageFile;

@end
