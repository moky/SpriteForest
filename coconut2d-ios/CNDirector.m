//
//  CNDirector.m
//  Coconut2D
//
//  Created by Moky on 12-10-27.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNDirector.h"

@implementation CNDirector

@synthesize winSize = winSize_;

static CNDirector *_sharedDirector = nil;

+ (CNDirector *) sharedDirector
{
	if (!_sharedDirector)
	{
		_sharedDirector = [[self alloc] init];
	}
	return _sharedDirector;
}

+ (id) alloc
{
	NSAssert(_sharedDirector == nil, @"It's illegal to have more than ONE lord!");
	return [super alloc];
}

- (id) init
{
	if ((self = [super init]))
	{
		winSize_ = [[CCDirector sharedDirector] winSize];
	}
	return self;
}

@end
