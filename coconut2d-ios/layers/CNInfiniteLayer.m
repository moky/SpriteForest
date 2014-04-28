//
//  CNInfiniteLayer.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNInfiniteLayer.h"

#import "CNDirector.h"

#define INFINITE_TILE_TAG 0x95270101

@implementation CNInfiniteLayer

- (void) moveTile:(CCNode *)tile frame:(CGRect)frame
{
	CGSize winSize = [[CNDirector sharedDirector] winSize];
	CGPoint anchor = ccpCompMult(ccpFromSize(tile.contentSize), tile.anchorPoint);
	
	CGRect tileFrame = CGRectZero;
	tileFrame.size = tile.contentSize;
	tileFrame.origin = ccpSub(tile.position, anchor);
	
	//
	while (tileFrame.origin.x + tileFrame.size.width < frame.origin.x) {
		tileFrame.origin.x += frame.size.width;
	}
	while (tileFrame.origin.y + tileFrame.size.height < frame.origin.y) {
		tileFrame.origin.y += frame.size.height;
	}
	//
	while (tileFrame.origin.x > frame.origin.x + winSize.width) {
		tileFrame.origin.x -= frame.size.width;
	}
	while (tileFrame.origin.y > frame.origin.y + winSize.height) {
		tileFrame.origin.y -= frame.size.height;
	}
	
	tile.position = ccpAdd(tileFrame.origin, anchor);
}

- (void) setPosition:(CGPoint)position
{
	CGRect frame = CGRectZero;
	frame.size = self.contentSize;
	frame.origin = ccpSub(ccpSub(CGPointZero, position), ccpCompMult(ccpFromSize(self.contentSize), self.anchorPoint));
	
	NSArray * tiles = [children_ getNSArray];
	for (CCNode * tile in tiles)
	{
		if (tile.tag == INFINITE_TILE_TAG)
		{
			[self moveTile:tile frame:frame];
		}
	}
	
	[super setPosition:position];
}

- (void) addTile:(CCNode *)tile
{
	if (tile.parent)
	{
		[tile removeFromParentAndCleanup:NO];
	}
	tile.tag = INFINITE_TILE_TAG;
	[self addChild:tile];
}

- (void) addTiles:(NSArray *)tiles
{
	for (CCNode * tile in tiles)
	{
		[self addTile:tile];
	}
}

@end
