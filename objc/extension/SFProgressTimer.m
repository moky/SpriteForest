//
//  SFProgressTimer.m
//  SpriteForest2
//
//  Created by Moky on 12-10-8.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFProgressTimer.h"


@implementation SFProgressTimer

@synthesize snapshot = snapshot_;
@synthesize mask = mask_;
@synthesize type = type_;
@synthesize target = target_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		[self setTypeByString:[dict objectForKey:@"Type"]];
		self.target = [dict objectForKey:@"Snapshot"];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.snapshot = nil;
		self.mask = nil;
		type_ = kCCProgressTimerTypeRadialCCW;
		self.target = nil;
	}
	return self;
}

- (void) dealloc
{
	[snapshot_ release];
	[mask_ release];
	[target_ release];
	[super dealloc];
}

#pragma mark -

- (void) setTypeByString:(NSString *)type
{
	if ([type isKindOfClass:[NSString class]])
	{
		if ([type caseInsensitiveCompare:@"RadialCCW"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeRadialCW;
		}
		else if ([type caseInsensitiveCompare:@"RadialCW"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeRadialCCW;
		}
		else if ([type caseInsensitiveCompare:@"HorizontalBarLR"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeHorizontalBarRL;
		}
		else if ([type caseInsensitiveCompare:@"HorizontalBarRL"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeHorizontalBarLR;
		}
		else if ([type caseInsensitiveCompare:@"VerticalBarBT"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeVerticalBarTB;
		}
		else if ([type caseInsensitiveCompare:@"VerticalBarTB"] == NSOrderedSame)
		{
			type_ = kCCProgressTimerTypeVerticalBarBT;
		}
	}
}

- (void) setSnapshot:(CCSprite *)snapshot
{
	if (snapshot_ != snapshot)
	{
		[snapshot_ removeFromParentAndCleanup:YES];
		[snapshot_ release];
		snapshot_ = [snapshot retain];
	}
}

- (void) setMask:(CCProgressTimer *)mask
{
	if (mask_ != mask)
	{
		[mask_ removeFromParentAndCleanup:YES];
		[mask_ release];
		mask_ = [mask retain];
	}
}

- (void) showProgress
{
	if (![target_ isKindOfClass:[NSString class]])
	{
		return ;
	}
	CCNode * target = [self getTarget:target_];
	if (![target isKindOfClass:[CCNode class]])
	{
		return;
	}
	if (target == self)
	{
		return;
	}
	if (CGSizeEqualToSize(target.contentSize, CGSizeZero))
	{
		return;
	}
	
	CGSize size = target.contentSize;
	CGPoint anchor = ccp(size.width * target.anchorPoint.x, size.height * target.anchorPoint.y);
	CGPoint center = ccp(size.width / 2, size.height / 2);
	CGPoint point = ccpAdd(target.position, ccpSub(center, anchor));
	point = [target.parent convertToWorldSpace:point];
	point = [self convertToNodeSpace:point];
	
	if (![mask_ isKindOfClass:[CCProgressTimer class]])
	{
		if ([target respondsToSelector:@selector(getUIImage)])
		{
			UIImage * image = [target getUIImage];
			if ([image isKindOfClass:[UIImage class]])
			{
				CCTexture2D * texture = [[CCTexture2D alloc] initWithImage:image];
				if ([texture isKindOfClass:[CCTexture2D class]])
				{
					// snapshot
					self.snapshot = [CCSprite spriteWithTexture:texture];
					snapshot_.anchorPoint = ccp(0.5f, 0.5f);
					snapshot_.position = point;
					[self addChild:snapshot_];
					// mask
					self.mask = [CCProgressTimer progressWithTexture:texture];
					mask_.anchorPoint = ccp(0.5f, 0.5f);
					mask_.position = point;
					mask_.type = type_;
					mask_.sprite.opacity = 0x40;
					[self addChild:mask_];
				}
				[texture release];
			}
		}
	}
	target.visible = NO;
	self.visible = YES;
}

- (void) hideProgress
{
	if (![target_ isKindOfClass:[NSString class]])
	{
		return ;
	}
	CCNode * target = [self getTarget:target_];
	if (target == self)
	{
		return;
	}
	target.visible = YES;
	self.visible = NO;
}

- (void) setPercentage:(float)percentage
{
	if (percentage < 0)
	{
		percentage = 0;
	}
	if (percentage < 100)
	{
		[self showProgress];
	}
	else
	{
		percentage = 100;
		[self hideProgress];
	}
	mask_.percentage = 100 - percentage;
}

@end


#pragma mark - avoid crash caused by 'ProgressTo/FromTo' action


@implementation CCNode (ProgressTimer)

- (void) setPercentage:(float)percentage
{
	CNLog(@"percentage = %f, node = %@", percentage, self);
}

@end
