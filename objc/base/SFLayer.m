//
//  SFLayer.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFLayer.h"

#import "SFScene.h"
#import "SFSprite.h"

@implementation SFLayer

@synthesize textures = textures_;

+ (id) nodeWithDictionary:(NSDictionary *)dict
{
	NSString * className = [dict objectForKey:@"Class"];
	if (![className isKindOfClass:[NSString class]])
	{
		dict = [NSMutableDictionary dictionaryWithDictionary:dict];
		// extend scroll layer
		if ([[dict objectForKey:@"ScrollEnabled"] boolValue])
		{
			[(NSMutableDictionary *)dict setObject:@"SFScrollLayer" forKey:@"Class"];
		}
		// extend scale layer
		else if ([[dict objectForKey:@"ScaleEnabled"] boolValue])
		{
			[(NSMutableDictionary *)dict setObject:@"SFScaleLayer" forKey:@"Class"];
		}
	}
	return [super nodeWithDictionary:dict];
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		// load textures
		NSArray * textures = [dict objectForKey:@"Textures"];
		if ([textures isKindOfClass:[NSArray class]])
		{
			self.textures = [SFScene loadTextures:textures];
		}
		
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

- (id) init
{
	if ((self = [super init]))
	{
		self.textures = nil;
	}
	return self;
}

- (void) dealloc
{
	self.textures = nil;
	[super dealloc];
}

- (void) setTextures:(NSArray *)textures
{
	if (textures != textures_)
	{
		CNLog(@"cleaning textures: %@", textures_);
		[SFScene cleanTextures:textures_];
		[textures_ release];
		textures_ = [textures retain];
	}
}

#pragma mark -

- (void) setAttributes:(NSDictionary *)dict
{
	// init layer frame
	[self setAnchorPoint:CGPointZero];
	[self setPosition:CGPointZero];
	
	[super setAttributes:dict];
}

@end
