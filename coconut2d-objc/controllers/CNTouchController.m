//
//  CNTouchController.m
//  Coconut2D
//
//  Created by Moky on 12-11-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNTouchController.h"

#import "cnMacros.h"
#import "CNNode.h"
#import "CNScene+Touch.h"

@implementation CNTouchController

@synthesize node = node_;
@synthesize delegate = delegate_;

@synthesize touchBeganPoint = touchBeganPoint_;
@synthesize touchPoint = touchPoint_;
@synthesize touchEndedPoint = touchEndedPoint_;

@synthesize dragEnabled = dragEnabled_;

- (id) init
{
	if ((self = [super init]))
	{
		self.node = nil;
		self.delegate = nil;
		
		touchBeganPoint_ = CGPointZero;
		touchPoint_ = CGPointZero;
		touchEndedPoint_ = CGPointZero;
		
		status_ = kTouchNodeNormal;
		
		dragEnabled_ = NO;
		originalPosition_ = CGPointZero;
	}
	return self;
}

- (void) dealloc
{
	[delegate_ release];
	[node_ release];
	[super dealloc];
}


#pragma mark -


- (void) setNode:(CCNode *)node
{
	if (node_ != node)
	{
		if ([node_ isKindOfClass:[CCNode class]])
		{
			CCScene * scene = [node_ scene];
			if ([scene isKindOfClass:[CNScene class]])
			{
				[(CNScene *)scene removeTouchNode:node_];
			}
		}
		
		[node_ release];
		node_ = [node retain];
		
		if ([node_ isKindOfClass:[CCNode class]])
		{
			CCScene * scene = [node_ scene];
			if ([scene isKindOfClass:[CNScene class]])
			{
				int maxTouches = dragEnabled_ ? 1 : -1;
				[(CNScene *)scene addTouchNode:node_ withDelegate:self maxTouches:maxTouches];
			}
		}
	}
}

- (void) doEvent:(SEL)s
{
	if ([delegate_ respondsToSelector:s])
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		[delegate_ performSelector:s withObject:node_];
		[pool release];
	}
}

#pragma mark CCTargetedTouchDelegate

- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
	if (![node_ containsTouchLocation:touch])
	{
		return NO;
	}
	
	// touch points
	CGPoint point = [node_ convertsTouchToNodeSpace:touch];
	touchBeganPoint_ = point;
	touchPoint_ = point;
	touchEndedPoint_ = point;
	
	if (dragEnabled_)
	{
		touchBeganPoint_ = [node_ convertToWorldSpace:touchBeganPoint_];
		touchPoint_ = touchBeganPoint_;
		touchEndedPoint_ = touchBeganPoint_;
		
		originalPosition_ = node_.position;
		
		BOOL flag = YES;
		if ([delegate_ respondsToSelector:@selector(onDragStart:)])
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			flag = [delegate_ onDragStart:node_];
			[pool release];
		}
		return flag;
	} // EOF if (dragEnabled_)
	
	// button delegate
	status_ = kTouchNodeActive;
	[self doEvent:@selector(onFingerDown:)];
	[self doEvent:@selector(onFingerOver:)];
	
	return YES;
}

- (void) ccTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event
{
	// touch points
	CGPoint point = [node_ convertsTouchToNodeSpace:touch];
	touchPoint_ = point;
	
	if (dragEnabled_)
	{
		touchPoint_ = [node_ convertToWorldSpace:touchPoint_];
		
		point = [node_ convertToWorldSpace:point];
		CGPoint delta = ccpSub(point, touchBeganPoint_);
		
		CGPoint oldPosition = node_.position;
		CGPoint newPosition = [node_.parent convertToWorldSpace:originalPosition_];
		newPosition = ccpAdd(newPosition, delta);
		newPosition = [node_.parent convertToNodeSpace:newPosition];
		// try to move to new position
		node_.position = newPosition;
		
		// check
		if ([delegate_ respondsToSelector:@selector(onDrag:)])
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			if (![delegate_ onDrag:node_])
			{
				node_.position = oldPosition;
			}
			[pool release];
		}
		return;
	} // EOF if (dragEnabled_)
	
	if (![node_ containsTouchLocation:touch])
	{
		if (status_ == kTouchNodeActive)
		{
			status_ = kTouchNodeNormal;
			[self doEvent:@selector(onFingerOut:)];
		}
		return;
	}
	
	// button delegate
	if (status_ != kTouchNodeActive)
	{
		status_ = kTouchNodeActive;
		[self doEvent:@selector(onFingerOver:)];
	}
	else
	{
		[self doEvent:@selector(onFingerMove:)];
	}
}

- (void) ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event
{
	// touch points
	CGPoint point = [node_ convertsTouchToNodeSpace:touch];
	touchPoint_ = point;
	touchEndedPoint_ = point;
	
	if (dragEnabled_)
	{
		touchPoint_ = [node_ convertToWorldSpace:touchPoint_];
		touchEndedPoint_ = touchPoint_;
		
		if ([delegate_ respondsToSelector:@selector(onDragEnd:)])
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			if (![delegate_ onDragEnd:node_])
			{
				[self ccTouchCancelled:touch withEvent:event];
			}
			[pool release];
		}
		return ;
	} // EOF if (dragEnabled_)
	
	if (![node_ containsTouchLocation:touch])
	{
		return ;
	}
	
	// button delegate
	status_ = kTouchNodeNormal;
	[self doEvent:@selector(onFingerUp:)];
	[self doEvent:@selector(onFingerOut:)];
	
	// guestures delegate
	CGFloat dx = touchEndedPoint_.x - touchBeganPoint_.x;
	CGFloat dy = touchEndedPoint_.y - touchBeganPoint_.y;
	if (dx > - 100 && dx < 100)
	{
		if (dy > 100)
		{
			[self doEvent:@selector(onSwipeUp:)];
			return;
		}
		else if (dy < -100)
		{
			[self doEvent:@selector(onSwipeDown:)];
			return;
		}
	}
	else if (dy > -100 && dy < 100)
	{
		if (dx > 100)
		{
			[self doEvent:@selector(onSwipeRight:)];
			return;
		}
		else if (dx < -100)
		{
			[self doEvent:@selector(onSwipeLeft:)];
			return;
		}
	}
	
	// click delegate
	switch ([touch tapCount])
	{
		case 0:
		case 1:
			[self doEvent:@selector(onClick:)];
			//[self performSelector:@selector(singleTap) withObject:nil afterDelay:0.2f];
			break;
		case 2:
			[self doEvent:@selector(onDoubleClick:)];
			//[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(singleTap) object:nil];
			//[self performSelector:@selector(doubleTap) withObject:nil afterDelay:0.2f];
			break;
		//case 3:
			//[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(doubleTap) object:nil];
			//[self performSelector:@selector(tripleTap) withObject:nil afterDelay:0.2f];
			//break;
		//case 4:
			//[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(tripleTap) object:nil];
			//break;
		default:
			CNLog(@"tapCount=%d", [touch tapCount]);
			break;
	}
}

- (void) ccTouchCancelled:(UITouch *)touch withEvent:(UIEvent *)event
{
	if (dragEnabled_)
	{
		CCActionInterval * moveTo = [CCMoveTo actionWithDuration:0.2f position:originalPosition_];
		moveTo = [CCEaseInOut actionWithAction:moveTo rate:2.0f];
		[node_ runAction:moveTo];
		return ;
	}
	[self doEvent:@selector(onFingerUp:)];
}

//- (void) singleTap
//{
//	CNLog(@"---------------------------- singleTap");
//	[self doEvent:@selector(onClick:)];
//}
//
//- (void) doubleTap
//{
//	CNLog(@"---------------------------- doubleTap");
//	[self doEvent:@selector(onDoubleClick:)];
//}
//
//- (void) tripleTap
//{
//	CNLog(@"---------------------------- tripleTap");
//}

@end
