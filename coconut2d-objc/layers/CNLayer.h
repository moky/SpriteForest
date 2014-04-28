//
//  CNLayer.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNLayer : CCLayer

+ (id) layerWithFile:(NSString *)filename;
+ (id) layerWithNode:(CCNode *)background;
+ (id) layerWithFrame:(CGRect)frame;
+ (id) layerWithDictionary:(NSDictionary *)dict;

- (id) initWithFile:(NSString *)filename;
- (id) initWithNode:(CCNode *)background;
- (id) initWithFrame:(CGRect)frame;
- (id) initWithDictionary:(NSDictionary *)dict;


- (void) focus:(CGPoint)point;
- (CGPoint) focus;

@end
