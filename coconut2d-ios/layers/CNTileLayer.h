//
//  CNTileLayer.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNLayer.h"

@interface CNTileLayer : CNLayer

+ (CNLayer *) landscapeLayerFromFiles:(NSArray *)filenames;
+ (CNLayer *) portraitLayerFromFiles:(NSArray *)filenames;

+ (CNLayer *) landscapeLayer:(NSArray *)nodes;
+ (CNLayer *) portraitLayer:(NSArray *)nodes;

@end
