//
//  SFDragSprite.m
//  SpriteForest2
//
//  Created by Moky on 12-10-3.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFDragSprite.h"


@implementation SFDragSprite

@synthesize dragRange = dragRange_;
@synthesize dragTied = dragTied_;

- (id) init
{
	if ((self = [super init]))
	{
		self.dragRange = CGRectZero;
		self.dragTied = NO;
	}
	return self;
}

- (void) onEnter
{
	controller_.dragEnabled = YES;
	[super onEnter];
}

- (void) setAttributes:(NSDictionary *)dict
{
	[super setAttributes:dict];
	
	// whether limit the draging in a range
	NSString * range = [dict objectForKey:@"DragRange"];
	if ([range isKindOfClass:[NSString class]])
	{
		CNLog(@"drag range = %@", range);
		self.dragRange = CGRectFromString(range);
	}
	
	// whether fly back to began point after drag end
	self.dragTied = [[dict objectForKey:@"DragTied"] boolValue];
}

@end


@implementation SFTouchHandler (drag)

- (BOOL) onDragStart:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onDragStart" node:node];
	[pool release];
	return YES;
}

- (BOOL) onDrag:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onDrag" node:node];
	[pool release];
	
	// check range
	if ([node isKindOfClass:[SFDragSprite class]])
	{
		CGRect range = ((SFDragSprite *)node).dragRange;
		if (!CGRectEqualToRect(range, CGRectZero))
		{
			CGSize size = node.contentSize;
			CGPoint anchor = ccpCompMult(ccpFromSize(size), node.anchorPoint);
			CGPoint point = ccpSub(node.position, anchor);
			// x
			if (point.x < range.origin.x)
			{
				point.x = range.origin.x;
			}
			else if (point.x + size.width > range.origin.x + range.size.width)
			{
				point.x = range.origin.x + range.size.width - size.width;
			}
			// y
			if (point.y < range.origin.y)
			{
				point.y = range.origin.y;
			}
			else if (point.y + size.height > range.origin.y + range.size.height)
			{
				point.y = range.origin.y + range.size.height - size.height;
			}
			// limit position
			point = ccpAdd(point, anchor);
			if (!CGPointEqualToPoint(point, node.position))
			{
				node.position = point;
			}
		}
	}
	
	return YES;
}

- (BOOL) onDragEnd:(CCNode *)node
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[self doEvent:@"onDragEnd" node:node];
	[pool release];
	
	if ([node isKindOfClass:[SFDragSprite class]])
	{
		return !((SFDragSprite *)node).dragTied;
	}
	
	return YES;
}

@end
