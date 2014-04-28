//
//  CNTile.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNTileLayer.h"

#import "CNSprite.h"

@implementation CNTileLayer

+ (CNLayer *) landscapeLayerFromFiles:(NSArray *)filenames
{
	return [self landscapeLayer:[CNSprite createSprites:filenames]];
}

+ (CNLayer *) portraitLayerFromFiles:(NSArray *)filenames
{
	return [self portraitLayer:[CNSprite createSprites:filenames]];
}

+ (CNLayer *) landscapeLayer:(NSArray *)nodes
{
	CNLayer * tray = [[CNLayer alloc] init];
	tray.anchorPoint = CGPointZero;
	tray.position = CGPointZero;
	tray.contentSize = CGSizeZero;
	
	for (CCNode * node in nodes)
	{
		node.anchorPoint = CGPointZero;
		node.position = ccp(tray.contentSize.width, 0);
		tray.contentSize = CGSizeMake(tray.contentSize.width + node.contentSize.width,
									  MAX(tray.contentSize.height, node.contentSize.height));
		[tray addChild:node];
	}
	
	return [tray autorelease];
}

+ (CNLayer *) portraitLayer:(NSArray *)nodes
{
	CNLayer * tray = [[CNLayer alloc] init];
	tray.anchorPoint = CGPointZero;
	tray.position = CGPointZero;
	tray.contentSize = CGSizeZero;
	
	for (CCNode * node in nodes)
	{
		node.anchorPoint = CGPointZero;
		node.position = ccp(0, tray.contentSize.height);
		tray.contentSize = CGSizeMake(MAX(tray.contentSize.width, node.contentSize.width),
									  tray.contentSize.height + node.contentSize.height);
		[tray addChild:node];
	}
	
	return [tray autorelease];
}

@end
