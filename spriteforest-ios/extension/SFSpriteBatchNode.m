//
//  SFSpriteBatchNode.m
//  SpriteForest2
//
//  Created by Moky on 12-10-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFSpriteBatchNode.h"

@implementation SFSpriteBatchNode

- (id) initWithDictionary:(NSDictionary *)dict
{
	NSString * filename = [dict objectForKey:@"File"];
	if ((self = [super initWithFile:filename]))
	{
		// create sub sprites
		NSArray * sprites = [dict objectForKey:@"Sprites"];
		[self addSprites:sprites];
		
		// set attributes
		[self setAttributes:dict];
	}
	return self;
}

@end
