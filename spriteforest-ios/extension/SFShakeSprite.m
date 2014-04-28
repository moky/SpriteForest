//
//  SFShakeSprite.m
//  SpriteForest2
//
//  Created by Moky on 12-10-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFShakeSprite.h"

@implementation SFShakeSprite

@synthesize shakeController = shakeController_;

- (id) init
{
	if ((self = [super init]))
	{
		self.shakeController = nil;
	}
	return self;
}

- (void) dealloc
{
	[shakeController_ release];
	[super dealloc];
}

- (void) appointHandlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree
{
	SFShakeHandler * handler = [SFShakeHandler handlerWithEventTree:eTree actionTree:aTree];
	self.eventHandler = handler;
}

- (void) onEnter
{
	[super onEnter];
	
	((SFShakeHandler *)eventHandler_).sprite = self;
	
	self.shakeController = [[[SFShakeController alloc] init] autorelease];
	shakeController_.delegate = (SFShakeHandler *)eventHandler_;
}

- (void) onExit
{
	shakeController_.delegate = nil;
	self.shakeController = nil;
	
	((SFShakeHandler *)eventHandler_).sprite = nil;
	
	[super onExit];
}

@end


@implementation SFShakeHandler

@synthesize sprite = sprite_;

- (id) init
{
	if ((self = [super init]))
	{
		self.sprite = nil;
	}
	return self;
}

- (void) dealloc
{
	[sprite_ release];
	[super dealloc];
}

- (void) onShakeStart:(UIAcceleration *)acceleration
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	CNLog(@"onShakeStart");
	[self doEvent:@"onShakeStart" node:sprite_];
	[pool release];
}

- (void) onShake:(UIAcceleration *)acceleration
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onShake" node:sprite_];
	[pool release];
}

- (void) onShakeEnd:(UIAcceleration *)acceleration
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onShakeEnd" node:sprite_];
	CNLog(@"onShakeEnd");
	[pool release];
}

@end