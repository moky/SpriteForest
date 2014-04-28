//
//  SFParticleSystem.m
//  SpriteForest
//
//  Created by Moky on 11-12-26.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "SFParticleSystem.h"

#import "SFTouchSprite.h"


@implementation SFParticleSystem
{
	NSString * positionString_;
}

+ (id) particle:(NSDictionary *)dict
{
	return [[[self alloc] init:dict] autorelease];
}

- (id) init:(NSDictionary *)dict
{
	NSString * filename = (NSString *)[dict objectForKey:@"File"];
	if (!filename || ![[NSFileManager defaultManager] fileExistsAtPath:filename])
	{
		return [super init];
	}
	NSMutableDictionary * mDict = [NSMutableDictionary dictionaryWithContentsOfFile:filename];
	NSString * textureFileName = [mDict objectForKey:@"textureFileName"];
	if ([textureFileName isKindOfClass:[NSString class]])
	{
		NSString * path = [filename stringByDeletingLastPathComponent];
		textureFileName = [path stringByAppendingPathComponent:textureFileName];
		[mDict setObject:textureFileName forKey:@"textureFileName"];
	}
	if ((self = [super initWithDictionary:mDict]))
	{
		// Position
		[positionString_ release];
		positionString_ = [dict objectForKey:@"Position"];
		[positionString_ retain];
		
		// ZOrder
		zOrder_ = [[dict objectForKey:@"ZOrder"] integerValue];
		
		// PositionType
		NSString * positionType = [dict objectForKey:@"PositionType"];
		if ([positionType caseInsensitiveCompare:@"Free"] == NSOrderedSame)
		{
			self.positionType = kCCPositionTypeFree;
		}
		else if ([positionType caseInsensitiveCompare:@"Relative"] == NSOrderedSame)
		{
			self.positionType = kCCPositionTypeRelative;
		}
		else if ([positionType caseInsensitiveCompare:@"Grouped"] == NSOrderedSame)
		{
			self.positionType = kCCPositionTypeGrouped;
		}
		
		self.autoRemoveOnFinish = YES;
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		[positionString_ release];
		positionString_ = nil;
	}
	return self;
}

- (void) dealloc
{
	[positionString_ release];
	[super dealloc];
}

- (void) runWithNode:(CCNode *)node
{
	// get position
	if ([node isKindOfClass:[SFTouchSprite class]])
	{
		CNTouchController * controller = [(SFTouchSprite *)node controller];
		if ([positionString_ caseInsensitiveCompare:@"TouchBeganPoint"] == NSOrderedSame)
		{
			self.position = controller.touchBeganPoint;
		}
		else if ([positionString_ caseInsensitiveCompare:@"TouchPoint"] == NSOrderedSame)
		{
			self.position = controller.touchPoint;
		}
		else if ([positionString_ caseInsensitiveCompare:@"TouchEndedPoint"] == NSOrderedSame)
		{
			self.position = controller.touchEndedPoint;
		}
		else
		{
			self.position = CGPointFromString(positionString_);
		}
	}
	// show
	[node addChild:self];
}


@end
