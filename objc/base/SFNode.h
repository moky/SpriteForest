//
//  SFNode.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "coconut2d.h"

#define SF_DEFAULT_WINDOW_WIDTH 1024
#define SF_DEFAULT_WINDOW_HEIGHT 768

@interface CCNode (SpriteForest)

+ (id) nodeWithString:(NSString *)string;
+ (id) nodeWithDictionary:(NSDictionary *)dict;

- (void) addSprites:(NSArray *)array;
- (void) addLayers:(NSArray *)array;

- (id) getTarget:(NSString *)target;

@end
