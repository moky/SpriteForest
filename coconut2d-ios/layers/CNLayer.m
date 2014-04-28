//
//  CNLayer.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNLayer.h"

#import "cnMacros.h"
#import "CNDirector.h"
#import "CNNode.h"
#import "CNSprite.h"


@implementation CNLayer

+ (id) layerWithFile:(NSString *)filename
{
	return [[[self alloc] initWithFile:filename] autorelease];
}

+ (id) layerWithNode:(CCNode *)background
{
	return [[[self alloc] initWithNode:background] autorelease];
}

+ (id) layerWithFrame:(CGRect)frame
{
	return [[[self alloc] initWithFrame:frame] autorelease];
}

+ (id) layerWithDictionary:(NSDictionary *)dict
{
	return [[[self alloc] initWithDictionary:dict] autorelease];
}

- (id) init
{
	if ((self = [super init]))
	{
		self.contentSize = [[CNDirector sharedDirector] winSize];
	}
	return self;
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [self init]))
	{
		[self setAttributes:dict];
	}
	return self;
}

- (id) initWithFrame:(CGRect)frame
{
	if ((self = [self init]))
	{
		self.isRelativeAnchorPoint = YES;
		self.contentSize = frame.size;
		self.position = frame.origin;
	}
	return self;
}

- (id) initWithNode:(CCNode *)background
{
	CGSize size = background.contentSize;
	CGPoint anchor = ccpCompMult(ccpFromSize(size), background.anchorPoint);
	CGPoint origin = ccpSub(background.position, anchor);
	
	CGRect frame = CGRectZero;
	frame.size = size;
	frame.origin = origin;
	
	if ((self = [self initWithFrame:frame]))
	{
		background.anchorPoint = CGPointZero;
		background.position = CGPointZero;
		
		[self addChild:background];
	}
	return self;
}

- (id) initWithFile:(NSString *)filename
{
	CCNode * background = [[CNSprite alloc] initWithFile:filename];
	background.anchorPoint = CGPointZero;
	background.position = CGPointZero;
	self = [self initWithNode:background];
	[background release];
	return self;
}

- (void) dealloc
{
	CNLog(@"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ %@ dealloc", [self class]);
	[super dealloc];
}


#pragma mark -


- (void) addChild:(CCNode *)child
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child z:z];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z tag:(NSInteger)tag
{
	if (child == nil || child.parent != nil)
	{
		return ;
	}
	[super addChild:child z:z tag:tag];
}

#pragma mark -

- (void) focus:(CGPoint)point
{
	CGSize winSize = [[CNDirector sharedDirector] winSize];
	CGPoint center = ccpMult(ccpFromSize(winSize), 0.5f);
	CGPoint anchor = ccpCompMult(ccpFromSize(self.contentSize), self.anchorPoint);
	CGPoint distance = ccpSub(anchor, point);
	CGPoint newPosition = ccpAdd(center, distance);
	self.position = newPosition;
}

- (CGPoint) focus
{
	CGSize winSize = [[CNDirector sharedDirector] winSize];
	CGPoint center = ccpMult(ccpFromSize(winSize), 0.5f);
	return ccpSub(center, self.position);
}

@end
