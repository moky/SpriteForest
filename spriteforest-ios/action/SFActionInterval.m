//
//  SFActionInterval.m
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionInterval.h"

#import "coconut2d.h"
#import "CCMask.h"
#import "SFAnimation.h"


@implementation SFActionInterval

- (CCAction *) ccAction
{
	CNLog(@"override me");
	return nil;
//	return [CCActionInterval actionWithDuration:duration_];
}

@end


@implementation SFSequence

@synthesize actions = actions_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		NSArray * actions = [[self class] subActionsFromDictionary:dict];
		if ([actions isKindOfClass:[NSArray class]])
		{
			NSMutableArray * mArray = [NSMutableArray arrayWithCapacity:[actions count]];
			for (id action in actions)
			{
				if ([action isKindOfClass:[CCFiniteTimeAction class]])
				{
					[mArray addObject:action];
				}
			}
			if ([mArray count] > 0)
			{
				self.actions = mArray;
			}
		}// EOF if ([actions isKindOfClass:[NSArray class]])
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.actions = nil;
	}
	return self;
}

- (void) dealloc
{
	[actions_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![actions_ isKindOfClass:[NSArray class]])
	{
		CNLog(@"Error: actions = %@", actions_);
		return [super ccAction];
	}
	return [CCSequence actionsWithArray:actions_];
}

@end


@implementation SFRepeat

@synthesize action = action_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		// drived action
		id action = [[self class] subActionFromDictionary:dict];
		if ([action isKindOfClass:[CCFiniteTimeAction class]])
		{
			self.action = action;
		}
		
		// times
		times_ = [[dict objectForKey:@"Times"] intValue];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.action = nil;
	}
	return self;
}

- (void) dealloc
{
	[action_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCFiniteTimeAction class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCRepeat actionWithAction:action_ times:times_];
}

@end


@implementation SFSpawn

@synthesize actions = actions_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		NSArray * actions = [[self class] subActionsFromDictionary:dict];
		if ([actions isKindOfClass:[NSArray class]])
		{
			NSMutableArray * mArray = [NSMutableArray arrayWithCapacity:[actions count]];
			for (id action in actions)
			{
				if ([action isKindOfClass:[CCFiniteTimeAction class]])
				{
					[mArray addObject:action];
				}
			}
			if ([mArray count] > 0)
			{
				self.actions = mArray;
			}
		}// EOF if ([actions isKindOfClass:[NSArray class]])
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.actions = nil;
	}
	return self;
}

- (void) dealloc
{
	[actions_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![actions_ isKindOfClass:[NSArray class]])
	{
		CNLog(@"Error: actions = %@", actions_);
		return [super ccAction];
	}
	return [CCSpawn actionsWithArray:actions_];
}

@end


@implementation SFRotateTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		id val = [dict objectForKey:@"Angle"] ? [dict objectForKey:@"Angle"] : [dict objectForKey:@"Rotation"];
		angle_ = [val floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCRotateTo actionWithDuration:duration_ angle:angle_];
}

@end


@implementation SFRotateBy

- (CCAction *) ccAction
{
	return [CCRotateBy actionWithDuration:duration_ angle:angle_];
}

@end


@implementation SFMoveTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		position_ = [dict objectForKey:@"Position"] ? CCPointFromString([dict objectForKey:@"Position"]) : CGPointZero;
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCMoveTo actionWithDuration:duration_ position:position_];
}

@end


@implementation SFMoveBy

- (CCAction *) ccAction
{
	return [CCMoveBy actionWithDuration:duration_ position:position_];
}

@end


@implementation SFSkewTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		skewX_ = [[dict objectForKey:@"SkewX"] floatValue];
		skewY_ = [[dict objectForKey:@"SkewY"] floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCSkewTo actionWithDuration:duration_ skewX:skewX_ skewY:skewY_];
}

@end


@implementation SFSkewBy

- (CCAction *) ccAction
{
	return [CCSkewBy actionWithDuration:duration_ skewX:skewX_ skewY:skewY_];
}

@end


@implementation SFJumpTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		position_ = [dict objectForKey:@"Position"] ? CCPointFromString([dict objectForKey:@"Position"]) : CGPointZero;
		height_ = [[dict objectForKey:@"Height"] floatValue];
		jumps_ = [[dict objectForKey:@"Jumps"] intValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCJumpTo actionWithDuration:duration_ position:position_ height:height_ jumps:jumps_];
}

@end


@implementation SFJumpBy

- (CCAction *) ccAction
{
	return [CCJumpBy actionWithDuration:duration_ position:position_ height:height_ jumps:jumps_];
}

@end


@implementation SFBezierTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		bezierConfig_.endPosition = [dict objectForKey:@"EndPosition"] ? CCPointFromString([dict objectForKey:@"EndPosition"]) : CGPointZero;
		bezierConfig_.controlPoint_1 = [dict objectForKey:@"ControlPoint1"] ? CCPointFromString([dict objectForKey:@"ControlPoint1"]) : CGPointZero;
		bezierConfig_.controlPoint_2 = [dict objectForKey:@"ControlPoint2"] ? CCPointFromString([dict objectForKey:@"ControlPoint2"]) : CGPointZero;
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCBezierTo actionWithDuration:duration_ bezier:bezierConfig_];
}

@end


@implementation SFBezierBy

- (CCAction *) ccAction
{
	return [CCBezierBy actionWithDuration:duration_ bezier:bezierConfig_];
}

@end


@implementation SFScaleTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		id scale = [dict objectForKey:@"Scale"];
		if (scale)
		{
			scaleX_ = [scale floatValue];
			scaleY_ = [scale floatValue];
		}
		else
		{
			scaleX_ = [[dict objectForKey:@"ScaleX"] floatValue];
			scaleY_ = [[dict objectForKey:@"ScaleY"] floatValue];
		}
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCScaleTo actionWithDuration:duration_ scaleX:scaleX_ scaleY:scaleY_];
}

@end


@implementation SFScaleBy

- (CCAction *) ccAction
{
	return [CCScaleBy actionWithDuration:duration_ scaleX:scaleX_ scaleY:scaleY_];
}

@end


@implementation SFBlink

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		times_ = [[dict objectForKey:@"Times"] intValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCBlink actionWithDuration:duration_ blinks:times_];
}

@end


@implementation SFFadeIn

- (CCAction *) ccAction
{
	return [CCFadeIn actionWithDuration:duration_];
}

@end


@implementation SFFadeOut

- (CCAction *) ccAction
{
	return [CCFadeOut actionWithDuration:duration_];
}

@end


@implementation SFFadeTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		opacity_ = [[dict objectForKey:@"Opacity"] intValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCFadeTo actionWithDuration:duration_ opacity:opacity_];
}

@end


@implementation SFTintTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		red_ = [[dict objectForKey:@"Red"] intValue];
		green_ = [[dict objectForKey:@"Green"] intValue];
		blue_ = [[dict objectForKey:@"Blue"] intValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCTintTo actionWithDuration:duration_ red:red_ green:green_ blue:blue_];
}

@end


@implementation SFTintBy

- (CCAction *) ccAction
{
	return [CCTintBy actionWithDuration:duration_ red:red_ green:green_ blue:blue_];
}

@end


@implementation SFDelayTime

- (CCAction *) ccAction
{
	return [CCDelayTime actionWithDuration:duration_];
}

@end


@implementation SFReverseTime

@synthesize action = action_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		id action = [[self class] subActionFromDictionary:dict];
		if ([action isKindOfClass:[CCActionInterval class]])
		{
			self.action = action;
		}
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.action = nil;
	}
	return self;
}

- (void) dealloc
{
	[action_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCFiniteTimeAction class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCReverseTime actionWithAction:action_];
}

@end


@implementation SFMaskTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		rect_ = [dict objectForKey:@"Rect"] ? CCRectFromString([dict objectForKey:@"Rect"]) : CGRectZero;
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCMaskTo actionWithDuration:duration_ rect:rect_];
}

@end


@implementation SFMaskBy

- (CCAction *) ccAction
{
	return [CCMaskBy actionWithDuration:duration_ rect:rect_];
}

@end


@implementation SFAnimate

@synthesize frames = frames_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		id frames = [dict objectForKey:@"Frames"];
		if ([frames isKindOfClass:[NSArray class]])
		{
			self.frames = frames;
		}
		delay_ = [[dict objectForKey:@"Delay"] floatValue];
		restoreOriginalFrame_ = [[dict objectForKey:@"RestoreOriginalFrame"] boolValue];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.frames = nil;
	}
	return self;
}

- (void) dealloc
{
	[frames_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	CGFloat delaytime = (duration_ * [frames_ count]) ? duration_ / [frames_ count] : delay_;
	CCAnimation * animation = [SFAnimation animationWithFrames:frames_ delay:delaytime];
	if (![animation isKindOfClass:[CCAnimation class]])
	{
		CNLog(@"Error: frames = %@, delay = %.2f, restoreOriginalFrame = %d", frames_, delay_, restoreOriginalFrame_);
		return [super ccAction];
	}
	return [CCAnimate actionWithDuration:duration_ animation:animation restoreOriginalFrame:restoreOriginalFrame_];
}

@end
