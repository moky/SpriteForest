//
//  SFActionInstant.m
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionInstant.h"

#import "coconut2d.h"


@implementation SFActionInstant

- (CCAction *) ccAction
{
	CNLog(@"override me");
	return nil;
//	return [CCActionInstant action];
}

@end


@implementation SFShow

- (CCAction *) ccAction
{
	return [CCShow action];
}

@end


@implementation SFHide

- (CCAction *) ccAction
{
	return [CCHide action];
}

@end


@implementation SFToggleVisibility

- (CCAction *) ccAction
{
	return [CCToggleVisibility action];
}

@end


@implementation SFFlipX

- (CCAction *) ccAction
{
	return [CCFlipX actionWithFlipX:YES];
}

@end


@implementation SFFlipY

- (CCAction *) ccAction
{
	return [CCFlipY actionWithFlipY:YES];
}

@end


@implementation SFPlace

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
	return [CCPlace actionWithPosition:position_];
}

@end


#pragma mark - Action Call Function


@implementation SFCallFunc

@synthesize targetCallback = targetCallback_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		self.targetCallback = [dict objectForKey:@"Target"];
		
		NSString * selector = [dict objectForKey:@"Selector"];
		if ([selector isKindOfClass:[NSString class]])
		{
			selector_ = NSSelectorFromString(selector);
		}
		else
		{
			CNLog(@"ERROR: invalid selector, dict = %@", dict);
		}
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.targetCallback = nil;
		selector_ = nil;
	}
	return self;
}

- (void) dealloc
{
	[targetCallback_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (!selector_ || ![targetCallback_ respondsToSelector:selector_])
	{
		CNLog(@"Error: invalid selector for this target.");
		return [super ccAction];
	}
	return [CCCallFunc actionWithTarget:targetCallback_ selector:selector_];
}

@end


//@implementation SFCallFuncN
//
//<#methods#>
//
//@end
//
//
//@implementation SFCallFuncND
//
//<#methods#>
//
//@end


@implementation SFCallFuncO

@synthesize object = object_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		self.object = [dict objectForKey:@"Object"];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.object = nil;
	}
	return self;
}

- (void) dealloc
{
	[object_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (!selector_ || ![targetCallback_ respondsToSelector:selector_])
	{
		CNLog(@"Error: invalid selector for this target: %@", targetCallback_);
		return [super ccAction];
	}
	return [CCCallFuncO actionWithTarget:targetCallback_ selector:selector_ object:object_];
}

@end


//@implementation SFCallBlock
//
//<#methods#>
//
//@end
//
//
//@implementation SFCallBlockN
//
//<#methods#>
//
//@end
