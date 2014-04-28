//
//  CNInfiniteLayer.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNLayer.h"

@interface CNInfiniteLayer : CNLayer

/**
 *  添加一个瓦片
 *  瓦片会随着 layer 的每一次移动而改变位置（以 layer.frame 为单元格），以达到循环出现的目的
 */
- (void) addTile:(CCNode *)tile;
- (void) addTiles:(NSArray *)tiles;

@end
