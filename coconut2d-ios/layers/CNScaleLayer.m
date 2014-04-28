//
//  CNScaleLayer.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScaleLayer.h"

@implementation CNScaleLayer

- (id) init
{
	if ((self = [super init]))
	{
		[scaleController_ release];
		scaleController_ = nil;
	}
	return self;
}

- (void) dealloc
{
	[scaleController_ release];
	
	[super dealloc];
}

- (void) onEnter
{
	[super onEnter];
	
	[scaleController_ release];
	scaleController_ = [[CNScaleLayerController alloc] init];
	scaleController_.layer = self;
}

- (void) onExit
{
	scaleController_.layer = nil;
	[scaleController_ release];
	scaleController_ = nil;
	
	[super onExit];
}

@end
