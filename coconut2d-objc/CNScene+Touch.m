//
//  CNScene+Touch.m
//  Coconut2D
//
//  Created by Moky on 12-11-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScene+Touch.h"

#import "cnMacros.h"
#import "CNNode.h"

@implementation CNTouchObject

@synthesize count = count_;
@synthesize maxTouches = maxTouches_;
@synthesize claimedTouches = claimedTouches_;
@synthesize delegate = delegate_;

- (id) init
{
	if ((self = [super init]))
	{
		count_ = 0;
		maxTouches_ = -1; // unlimited
		self.claimedTouches = [NSMutableSet setWithCapacity:1];
		self.delegate = nil;
	}
	return self;
}

- (void) dealloc
{
	[claimedTouches_ release];
	[delegate_ release];
	[super dealloc];
}

- (NSString *) description
{
	NSString * desc = [super description];
	return [NSString stringWithFormat:@"%@ count = %d, delegate = %@", desc, count_, delegate_];
}

@end

@implementation CNScene (Touch)

- (void) onEnter
{
	[super onEnter];
	[[CCTouchDispatcher sharedDispatcher] addStandardDelegate:self priority:-1];
}

- (void) onExit
{
	[[CCTouchDispatcher sharedDispatcher] removeDelegate:self];
	[super onExit];
}

- (NSString *) keyByNode:(CCNode *)node
{
	return [NSString stringWithFormat:@"%@", node];
}

- (void) addTouchNode:(CCNode *)node withDelegate:(id<CCTargetedTouchDelegate>)delegate
{
	[self addTouchNode:node withDelegate:delegate maxTouches:-1];
}

- (void) addTouchNode:(CCNode *)node withDelegate:(id<CCTargetedTouchDelegate>)delegate maxTouches:(int)count
{
	for (CCNode * p = node; [p isKindOfClass:[CCNode class]]; p = p.parent)
	{
		NSString * key = [self keyByNode:p];
		
		CNTouchObject * obj = [touchNodes_ objectForKey:key];
		if (![obj isKindOfClass:[CNTouchObject class]])
		{
			obj = [[[CNTouchObject alloc] init] autorelease];
			[touchNodes_ setObject:obj forKey:key];
		}
		obj.count++;
		if (p == node && delegate)
		{
			obj.delegate = delegate;
			obj.maxTouches = count;
		}
	}
}

- (void) removeTouchNode:(CCNode *)node
{
	for (CCNode * p = node; [p isKindOfClass:[CCNode class]]; p = p.parent)
	{
		NSString * key = [self keyByNode:p];
		
		CNTouchObject * obj = [touchNodes_ objectForKey:key];
		if ([obj isKindOfClass:[CNTouchObject class]])
		{
			obj.count--;
			if (obj.count <= 0)
			{
				[touchNodes_ removeObjectForKey:key];
			}
		}
	}
}

- (CNTouchObject *) objectByNode:(CCNode *)node
{
	NSString * key = [self keyByNode:node];
	return [touchNodes_ objectForKey:key];
}

- (NSString *) keyByTouch:(UITouch *)touch
{
	NSString * touchKey = [NSString stringWithFormat:@"%@", touch];
	if ([touchKey length] < 20)
	{
		return NO;
	}
	return [touchKey substringToIndex:19];
}

#pragma mark -

- (BOOL) cnTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event delegate:(id<CCTargetedTouchDelegate>)delegate
{
	BOOL flag = NO;
	if ([delegate respondsToSelector:@selector(ccTouchBegan:withEvent:)])
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		flag = [delegate ccTouchBegan:touch withEvent:event];
		[pool release];
	}
	return flag;
}
- (void) cnTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event delegate:(id<CCTargetedTouchDelegate>)delegate
{
	if ([delegate respondsToSelector:@selector(ccTouchMoved:withEvent:)])
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		[delegate ccTouchMoved:touch withEvent:event];
		[pool release];
	}
}
- (void) cnTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event delegate:(id<CCTargetedTouchDelegate>)delegate
{
	if ([delegate respondsToSelector:@selector(ccTouchEnded:withEvent:)])
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		[delegate ccTouchEnded:touch withEvent:event];
		[pool release];
	}
}
- (void) cnTouchCancelled:(UITouch *)touch withEvent:(UIEvent *)event delegate:(id<CCTargetedTouchDelegate>)delegate
{
	if ([delegate respondsToSelector:@selector(ccTouchCancelled:withEvent:)])
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		[delegate ccTouchCancelled:touch withEvent:event];
		[pool release];
	}
}

- (BOOL) cnTouch:(UITouch *)touch withEvent:(UIEvent *)event withTouchType:(unsigned int)idx withTouchObject:(CNTouchObject *)obj
{
	NSString * touchKey = [self keyByTouch:touch];
	
	if (idx == kCCTouchBegan)
	{
		for (UITouch * t in obj.claimedTouches)
		{
			NSString * k = [self keyByTouch:t];
			[allClaimedKeys_ removeObject:k];
		}
		[obj.claimedTouches removeAllObjects];
	}
	
	BOOL claimed = NO;
	// dispatch
	if ([obj.claimedTouches containsObject:touch])
	{
		claimed = YES;
		if (idx == kCCTouchMoved)
		{
			[self cnTouchMoved:touch withEvent:event delegate:obj.delegate];
		}
		else if (idx == kCCTouchEnded)
		{
			[allClaimedKeys_ removeObject:touchKey];
			[obj.claimedTouches removeObject:touch];
			[self cnTouchEnded:touch withEvent:event delegate:obj.delegate];
		}
		else if (idx == kCCTouchCancelled)
		{
			[allClaimedKeys_ removeObject:touchKey];
			[obj.claimedTouches removeObject:touch];
			[self cnTouchCancelled:touch withEvent:event delegate:obj.delegate];
		}
		else
		{
			CNLog(@"ERROR: could not happen!");
		}
	}
	else if ([allClaimedKeys_ containsObject:touchKey])
	{
		// already claimed by other obj
	}
	else if (obj.maxTouches > 0 && [obj.claimedTouches count] >= obj.maxTouches)
	{
		CNLog(@"the touch node has already claimed %d touch(es)", [obj.claimedTouches count]);
	}
	else if (idx == kCCTouchBegan || idx == kCCTouchMoved)
	{
		claimed = [self cnTouchBegan:touch withEvent:event delegate:obj.delegate];
		if (claimed)
		{
			[obj.claimedTouches addObject:touch];
			[allClaimedKeys_ addObject:touchKey];
		}
	}
	
	return claimed;
}

- (BOOL) cnTouch:(UITouch *)touch withEvent:(UIEvent *)event withTouchType:(unsigned int)idx withNode:(CCNode *)node
{
	int touchableCount = 0;
	CNTouchObject * obj = [self objectByNode:node];
	if ([obj isKindOfClass:[CNTouchObject class]])
	{
		touchableCount = obj.count;
	}
	if (touchableCount <= 0)
	{
		CNLog(@"could not happen!");
		return NO;
	}
	
	CCArray * children = node.children;
	int pos = [children isKindOfClass:[CCArray class]] ? children.count - 1 : -1;
	
	// check children which zOrder >= 0
	for (; pos >= 0 && (touchableCount > 1 || obj.delegate == nil); pos--)
	{
		CCNode * child = [children objectAtIndex:pos];
		if (child.zOrder < 0)
		{
			break;
		}
		
		CNTouchObject * childObj = [self objectByNode:child];
		if (![childObj isKindOfClass:[CNTouchObject class]])
		{
			// not a touchable node
			continue;
		}
		touchableCount -= childObj.count;
		
		if ([self cnTouch:touch withEvent:event withTouchType:idx withNode:child])
		{
			return YES;
		}
	}
	
	if (touchableCount == 0)
	{
		return NO;
	}
	else if (touchableCount < 0)
	{
		CNLog(@"could not happen!");
		return NO;
	}
	
	if (obj.delegate)
	{
		touchableCount--;
		
		if ([self cnTouch:touch withEvent:event withTouchType:idx withTouchObject:obj])
		{
			return YES;
		}
	}
	
	if (touchableCount == 0)
	{
		return NO;
	}
	else if (touchableCount < 0)
	{
		CNLog(@"could not happen!");
		return NO;
	}
	
	// check children which zOrder < 0
	for (; pos >= 0 && (touchableCount > 1 || obj.delegate == nil); pos--)
	{
		CCNode * child = [children objectAtIndex:pos];
		if (child.zOrder >= 0)
		{
			CNLog(@"could not happen!");
			break;
		}
		
		CNTouchObject * childObj = [self objectByNode:child];
		if (![childObj isKindOfClass:[CNTouchObject class]])
		{
			// not a touchable node
			continue;
		}
		touchableCount -= childObj.count;
		
		if ([self cnTouch:touch withEvent:event withTouchType:idx withNode:child])
		{
			return YES;
		}
	}
	
	if (touchableCount != 0)
	{
		CNLog(@"could not happen!");
	}
	
	return NO;
}

- (void) cnTouches:(NSSet *)touches withEvent:(UIEvent *)event withTouchType:(unsigned int)idx
{
	NSSet * allTouches = [event allTouches];
	for (UITouch * touch in allTouches)
	{
		BOOL processed = [self cnTouch:touch withEvent:event withTouchType:idx withNode:self];
		if (!processed)
		{
			CNLog(@"nothing hit.");
		}
	}
}

#pragma mark CCStandardTouchDelegate

- (void) ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self cnTouches:touches withEvent:event withTouchType:kCCTouchBegan];
}

- (void) ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self cnTouches:touches withEvent:event withTouchType:kCCTouchMoved];
}

- (void) ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self cnTouches:touches withEvent:event withTouchType:kCCTouchEnded];
}

- (void) ccTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self cnTouches:touches withEvent:event withTouchType:kCCTouchCancelled];
}

@end
