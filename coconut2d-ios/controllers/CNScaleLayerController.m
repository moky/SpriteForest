//
//  CNScaleLayerController.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScaleLayerController.h"

#import "cnMacros.h"
#import "CNFiniteLayer.h"

@implementation CNScaleLayerController

@synthesize layer = layer_;

- (id) init
{
	if ((self = [super init]))
	{
		[layer_ release];
		layer_ = nil;
		
		[[CCTouchDispatcher sharedDispatcher] addStandardDelegate:self priority:0];
	}
	return self;
}

- (void) dealloc
{
	[[CCTouchDispatcher sharedDispatcher] removeDelegate:self];
	
	[layer_ release];
	
	[super dealloc];
}


#pragma mark -


- (void) setLayer:(CCLayer *)layer
{
	if (layer_ != layer)
	{
		[layer_ release];
		layer_ = [layer retain];
		
		int priority = 0;
		for (CCNode * node = layer; [node isKindOfClass:[CCNode class]]; node = node.parent)
		{
			priority -= node.zOrder;
		}
		[[CCTouchDispatcher sharedDispatcher] setPriority:priority forDelegate:self];
	}
}

- (void) handlePinchGesture:(NSSet *)touches
{
	CCDirector * director = [CCDirector sharedDirector];
	UIView * view = [director openGLView];
	
	NSArray * array = [touches allObjects];
	if ([array count] < 2)
	{
		CNLog(@"ERROR, touches count=%d", [array count]);
		return ;
	}
	UITouch * touch1 = [array objectAtIndex:0];
	UITouch * touch2 = [array objectAtIndex:1];
	
	CGPoint point1, point2;
	// previous distance
	point1 = [director convertToGL:[touch1 previousLocationInView:view]];
	point2 = [director convertToGL:[touch2 previousLocationInView:view]];
	CGFloat previousDistance = ccpDistance(point1, point2);
	// distance
	point1 = [director convertToGL:[touch1 locationInView:view]];
	point2 = [director convertToGL:[touch2 locationInView:view]];
	CGFloat distance = ccpDistance(point1, point2);
	
	// scale
	CGFloat delta = DIV(distance, previousDistance);
	CGFloat newScale = layer_.scale * delta;
	
	// focus
	CGPoint focus = ccpMult(ccpAdd(point1, point2), 0.5f);
	CGPoint deltaPos = ccpSub(focus, layer_.position);
	deltaPos = ccpMult(deltaPos, 1.0f - delta);
	focus = ccpAdd(layer_.position, deltaPos);
	
	layer_.scale = newScale;
	layer_.position = focus;
}


- (void) handleDoubleTapGesture:(UITouch*)touch
{
	CCDirector * director = [CCDirector sharedDirector];
	UIView * view = [director openGLView];
	
	CGPoint location = [touch locationInView:view];
	location = [director convertToGL: location];
	
	// scale
	CGFloat newScale = (layer_.scale < 0.75f) ? 1.0f : ((layer_.scale > 1.25f) ? 0.5f : 1.5f);
	CGFloat delta = DIV(newScale, layer_.scale);
	
	// focus
	CGPoint deltaPos = ccpSub(location, layer_.position);
	deltaPos = ccpMult(deltaPos, 1.0f - delta);
	CGPoint focus = ccpAdd(layer_.position, deltaPos);
	
	layer_.scale = newScale;
	layer_.position = focus;
}


#pragma mark CCStandardTouchDelegate


- (void) ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	NSSet * allTouches = [event allTouches];
	NSUInteger touchesCount = [allTouches count];
	
	if (touchesCount >= 2)
	{
		[self handlePinchGesture:allTouches];
	}
}

- (void) ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch * touch = (UITouch *)[touches anyObject];
	if (touch.tapCount == 2)
	{
		[self handleDoubleTapGesture:touch];
	}
	if ([layer_ isKindOfClass:[CNFiniteLayer class]])
	{
		[(CNFiniteLayer *)layer_ correctPositionAndScale];
	}
}

- (void) ccTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	if ([layer_ isKindOfClass:[CNFiniteLayer class]])
	{
		[(CNFiniteLayer *)layer_ correctPositionAndScale];
	}
}

@end
