//
//  SFActionEase.m
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionEase.h"

#import "cnMacros.h"


@implementation SFActionEase

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
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCActionEase actionWithAction:action_];
}

@end


#pragma mark - Action Ease Rate


@implementation SFEaseRateAction

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		rate_ = [[dict objectForKey:@"Rate"] floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseRateAction actionWithAction:action_ rate:rate_];
}

@end


@implementation SFEaseIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseIn actionWithAction:action_ rate:rate_];
}

@end


@implementation SFEaseOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseOut actionWithAction:action_ rate:rate_];
}

@end


@implementation SFEaseInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseInOut actionWithAction:action_ rate:rate_];
}

@end


#pragma mark - Action Ease Exponential


@implementation SFEaseExponentialIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseExponentialIn actionWithAction:action_];
}

@end


@implementation SFEaseExponentialOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseExponentialOut actionWithAction:action_];
}

@end


@implementation SFEaseExponentialInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseExponentialInOut actionWithAction:action_];
}

@end


#pragma mark - Action Ease Sine


@implementation SFEaseSineIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseSineIn actionWithAction:action_];
}

@end


@implementation SFEaseSineOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseSineOut actionWithAction:action_];
}

@end


@implementation SFEaseSineInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseSineInOut actionWithAction:action_];
}

@end


#pragma mark - Action Ease Elastic


@implementation SFEaseElastic

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseElastic actionWithAction:action_ period:duration_];
}

@end


@implementation SFEaseElasticIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseElasticIn actionWithAction:action_ period:duration_];
}

@end


@implementation SFEaseElasticOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseElasticOut actionWithAction:action_ period:duration_];
}

@end


@implementation SFEaseElasticInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseElasticInOut actionWithAction:action_ period:duration_];
}

@end


#pragma mark - Action Ease Bounce


@implementation SFEaseBounce

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBounce actionWithAction:action_];
}

@end


@implementation SFEaseBounceIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBounceIn actionWithAction:action_];
}

@end


@implementation SFEaseBounceOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBounceOut actionWithAction:action_];
}

@end


@implementation SFEaseBounceInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBounceInOut actionWithAction:action_];
}

@end


#pragma mark - Action Ease Back


@implementation SFEaseBackIn

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBackIn actionWithAction:action_];
}

@end


@implementation SFEaseBackOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBackOut actionWithAction:action_];
}

@end


@implementation SFEaseBackInOut

- (CCAction *) ccAction
{
	if (![action_ isKindOfClass:[CCActionInterval class]])
	{
		CNLog(@"Error: action = %@", action_);
		return [super ccAction];
	}
	return [CCEaseBackInOut actionWithAction:action_];
}

@end
