//
//  CNSprite.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNSprite : CCSprite

+ (id) spriteWithFile:(NSString *)filename;
+ (id) spriteWithDictionary:(NSDictionary *)dict;

- (id) initWithFile:(NSString *)filename;
- (id) initWithDictionary:(NSDictionary *)dict;


+ (NSArray *) createSprites:(NSArray *)filenames;

/**
 *  change the sprite's image
 */
- (void) replaceImageWithFile:(NSString *)filename;

+ (UIImage *) getUIImageWithPath:(NSString *)imagePath;

@end
