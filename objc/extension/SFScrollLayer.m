//
//  SFScrollLayer.m
//  SpriteForest2
//
//  Created by Moky on 12-10-24.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFScrollLayer.h"

#import "CNNode.h"
#import "CNSprite.h"
#import "SFNode.h"

@implementation SFScrollLayer

- (id) initWithDictionary:(NSDictionary *)dict
{
	NSString * filename = [dict objectForKey:@"File"];
	if ([filename isKindOfClass:[NSString class]])
	{
		CNSprite * sprite = [CNSprite spriteWithFile:filename];
		if ((self = [self initWithNode:sprite]))
		{
			[self setAttributes:dict];
		}
	}
	else if ((self = [super initWithDictionary:dict]))
	{
		NSString * size = [dict objectForKey:@"Size"];
		if (size != nil)
		{
			self.contentSize = CCSizeFromString(size);
		}
		else
		{
			NSString * width = [dict objectForKey:@"Width"];
			NSString * height = [dict objectForKey:@"Height"];
			if (width != nil && height != nil)
			{
				self.contentSize = CGSizeMake([width floatValue], [height floatValue]);
			}
		}
	}
	if (self)
	{
		// create sub layers
		// WARNING: For simplify reason, I hope you should never use it! -- Moky @ 2012.10.08
		NSArray * layers = [dict objectForKey:@"Layers"];
		[self addLayers:layers];
		
		// create sub sprites
		NSArray * sprites = [dict objectForKey:@"Sprites"];
		[self addSprites:sprites];
	}
	return self;
}

@end
