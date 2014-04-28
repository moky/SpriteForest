//
//  CNScrollLayer.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScrollLayer.h"

@implementation CNScrollLayer

- (id) init
{
	if ((self = [super init]))
	{
		[scrollController_ release];
		scrollController_ = nil;
	}
	return self;
}

- (void) dealloc
{
	[scrollController_ release];
	
	[super dealloc];
}

- (void) onEnter
{
	[super onEnter];
	
	[scrollController_ release];
	scrollController_ = [[CNScrollLayerController alloc] init];
	scrollController_.node = self;
	scrollController_.dragEnabled = YES;
}

- (void) onExit
{
	scrollController_.node = nil;
	[scrollController_ release];
	scrollController_ = nil;
	
	[super onExit];
}

@end
