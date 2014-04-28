//
//  SFTouchSprite.m
//  SpriteForest2
//
//  Created by Moky on 12-10-3.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFTouchSprite.h"

@implementation SFTouchSprite

@synthesize controller = controller_;
@synthesize irregular = irregular_;
@synthesize touchBounds = touchBounds_;

- (id) init
{
	if ((self = [super init]))
	{
		self.controller = [[[CNTouchController alloc] init] autorelease];
		irregular_ = NO;
		touchBounds_ = CGRectZero;
	}
	return self;
}

- (void) dealloc
{
	[controller_ release];
	
	[super dealloc];
}

- (void) appointHandlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree
{
	SFTouchHandler * handler = [SFTouchHandler handlerWithEventTree:eTree actionTree:aTree];
	self.eventHandler = handler;
}

- (void) onEnter
{
	[super onEnter];
	
	controller_.node = self;
	controller_.delegate = (SFTouchHandler *)eventHandler_;
}

- (void) onExit
{
	controller_.delegate = nil;
	controller_.node = nil;
	
	[super onExit];
}

- (BOOL) containsNodeSpacePoint:(CGPoint)point
{
	if (![super containsNodeSpacePoint:point])
	{
		return NO;
	}
	return CGRectEqualToRect(touchBounds_, CGRectZero) || CGRectContainsPoint(touchBounds_, point);
}

- (BOOL) containsTouchLocation:(UITouch *)touch
{
	return [self containsTouchLocation:touch checkPixel:irregular_];
}

- (void) setAttributes:(NSDictionary *)dict
{
	// irregular
	NSString * irregular = [dict objectForKeyCaseInsensitive:@"Irregular"];
	if (irregular != nil)
	{
		self.irregular = [irregular boolValue];
	}
	
	// touch bounds
	NSString * touchBounds = [dict objectForKeyCaseInsensitive:@"TouchBounds"];
	if (touchBounds != nil)
	{
		self.touchBounds = CGRectFromString(touchBounds);
	}
	
	[super setAttributes:dict];
}

@end


@implementation SFTouchHandler

- (void) onFingerDown:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onFingerDown" node:node];
	[self doEvent:@"onMouseDown" node:node]; // deprecated
	[pool release];
}

- (void) onFingerUp:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onFingerUp" node:node];
	[self doEvent:@"onMouseUp" node:node]; // deprecated
	[pool release];
}

- (void) onFingerOver:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onFingerOver" node:node];
	[self doEvent:@"onMouseOver" node:node]; // deprecated
	[pool release];
}

- (void) onFingerOut:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onFingerOut" node:node];
	[self doEvent:@"onMouseOut" node:node]; // deprecated
	[pool release];
}

- (void) onFingerMove:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onFingerMove" node:node];
	[self doEvent:@"onMouseMove" node:node]; // deprecated
	[pool release];
}

// click
- (void) onClick:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onClick" node:node];
	[pool release];
}

- (void) onDoubleClick:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onDoubleClick" node:node]; // deprecated
	[pool release];
}

// guestures
- (void) onSwipeLeft:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onSwipeLeft" node:node];
	[pool release];
}

- (void) onSwipeRight:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onSwipeRight" node:node];
	[pool release];
}

- (void) onSwipeUp:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onSwipeUp" node:node];
	[pool release];
}

- (void) onSwipeDown:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onSwipeDown" node:node];
	[pool release];
}

@end

