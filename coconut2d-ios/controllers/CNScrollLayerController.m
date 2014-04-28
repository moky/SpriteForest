//
//  CNScrollLayerController.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScrollLayerController.h"

#import "cnMacros.h"
#import "CNScene+Touch.h"

@implementation CNScrollLayerController

- (id) init
{
	if ((self = [super init]))
	{
		[currentAction_ release];
		currentAction_ = nil;
	}
	return self;
}

- (void) dealloc
{
	[currentAction_ release];
	
	[super dealloc];
}


#pragma mark -


- (void) handleSwingGesture:(UITouch *)touch
{
	CGPoint location = [touch locationInView:[touch view]];
	location = [[CCDirector sharedDirector] convertToGL: location];
	
	CGPoint deltaDistance = ccpSub(location, swingBeganPoint_);
	deltaDistance = ccpMult(deltaDistance, 10);
	CGFloat len = ccpLength(deltaDistance);
	len = MAX(1, len);
	
	clock_t now = clock();
	long deltaTime = (now - swingBeganTime_) / 1000;
	
	CGFloat v = DIV(len, deltaTime);
	
	ccTime duration = DIV(1000, v);
	if (duration > 10) {
		return;
	} else if (duration < 0.1) {
		duration = 0.1;
	}
	
	CGPoint newPosition = ccpAdd(node_.position, deltaDistance);
	
	
	CCActionInterval * action = [CCMoveTo actionWithDuration:duration position:newPosition];
	action = [CCEaseExponentialOut actionWithAction:action];
	[node_ runAction:action];
	
	if (currentAction_ != action)
	{
		[currentAction_ release];
		currentAction_ = [action retain];
	}
}


#pragma mark CCTargetedTouchDelegate


- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
	CGPoint location = [touch locationInView:[touch view]];
	swingBeganPoint_ = [[CCDirector sharedDirector] convertToGL: location];
	swingBeganTime_ = clock();
	
	[currentAction_ stop];
	return [super ccTouchBegan:touch withEvent:event];
}

- (void) ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event
{
	[super ccTouchEnded:touch withEvent:event];
	
	if (touch.tapCount <= 1)
	{
		[self handleSwingGesture:touch];
	}
}

@end
