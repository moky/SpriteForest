//
//  SFAction.m
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFAction.h"

#import "SFActionInterval.h"
#import "SFActionMagic.h"
#import "SFNode.h"


@implementation SFAction

+ (id) getInstance:(NSDictionary *)dict
{
	NSString * name = [dict objectForKey:@"Name"];
	if (![name isKindOfClass:[NSString class]])
	{
		CNLog(@"ERROR: dict = %@", dict);
		return nil;
	}
	Class class = NSClassFromString([@"SF" stringByAppendingString:name]);
	if (![class isSubclassOfClass:[SFAction class]])
	{
		class = [SFActionMagic class];
	}
	return [[[class alloc] initWithDictionary:dict] autorelease];
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [self init]))
	{
		//CNLog(@"class = %@, dict = %@", [self class], dict);
	}
	return self;
}

- (CCAction *) ccAction
{
	CNLog(@"override me");
	return nil;
//	return [CCAction action];
}

+ (CCAction *) actionByReplaceTarget:(CCNode *)node dictionary:(NSDictionary *)dict
{
	id target = nil;
	if ([node isKindOfClass:[CCNode class]])
	{
		target = [node getTarget:[dict objectForKey:@"Target"]];
	}
	
	if ([target isKindOfClass:[CCNode class]])
	{
		dict = [NSMutableDictionary dictionaryWithDictionary:dict];
		[(NSMutableDictionary *)dict setObject:target forKey:@"Target"];
	}
	
	return [[self getInstance:dict] ccAction];
}

+ (CCAction *) subActionFromDictionary:(NSDictionary *)dict
{
	id target = [dict objectForKey:@"Target"];
	id action = [dict objectForKey:@"Action"];
	if ([action isKindOfClass:[NSDictionary class]])
	{
		action = [self actionByReplaceTarget:target dictionary:action];
	}
	
	if ([action isKindOfClass:[CCAction class]])
	{
		return action;
	}
	else
	{
		CNLog(@"ERROR!");
		return nil;
	}
}

+ (NSArray *) subActionsFromDictionary:(NSDictionary *)dict
{
	id target = [dict objectForKey:@"Target"];
	NSArray * actions = [dict objectForKey:@"Actions"];
	if (![actions isKindOfClass:[NSArray class]])
	{
		return nil;
	}
	
	NSMutableArray * mArray = [NSMutableArray arrayWithCapacity:[actions count]];
	for (id action in actions)
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		if ([action isKindOfClass:[NSDictionary class]])
		{
			action = [self actionByReplaceTarget:target dictionary:action];
		}
		
		if ([action isKindOfClass:[CCAction class]])
		{
			[mArray addObject:action];
		}
		else
		{
			CNLog(@"ERROR!");
		}
		[pool release];
	}
	
	return mArray;
}

@end


#pragma mark -


@implementation SFFiniteTimeAction

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		duration_ = [[dict objectForKey:@"Duration"] floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	CNLog(@"override me");
	return nil;
//	return [CCFiniteTimeAction action];
}

@end


@implementation SFRepeatForever

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
		CNLog(@"Error: actioin = %@", action_);
		return [super ccAction];
	}
	return [CCRepeatForever actionWithAction:action_];
}

@end


@implementation SFSpeed

@synthesize action = action_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		// drived action
		id action = [[self class] subActionFromDictionary:dict];
		if ([action isKindOfClass:[CCActionInterval class]])
		{
			self.action = action;
		}
		
		// speed rate
		rate_ = [[dict objectForKey:@"Rate"] intValue];
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
		CNLog(@"Error: actioin = %@", action_);
		return [super ccAction];
	}
	return [CCSpeed actionWithAction:action_ speed:rate_];
}

@end


@implementation SFFollow

@synthesize target = target_;
@synthesize followedNode = followedNode_;
@synthesize rect = rect_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		self.target = [dict objectForKey:@"Target"];
		self.followedNode = [dict objectForKey:@"FollowedNode"];
		
		NSString * rect = [dict objectForKey:@"Rect"];
		if (rect)
		{
			self.rect = CGRectFromString(rect);
		}
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.target = nil;
		self.followedNode = nil;
		self.rect = CGRectZero;
	}
	return self;
}

- (void) dealloc
{
	[target_ release];
	[followedNode_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![target_ isKindOfClass:[CCNode class]])
	{
		CNLog(@"invalid target: %@", target_);
		return [super ccAction];
	}
	if ([followedNode_ isKindOfClass:[NSString class]])
	{
		followedNode_ = [target_ getTarget:followedNode_];
	}
	if (![followedNode_ isKindOfClass:[CCNode class]])
	{
		CNLog(@"Error: followedNode = %@", followedNode_);
		return [super ccAction];
	}
	
	if (CGRectEqualToRect(rect_, CGRectZero))
	{
		return [CCFollow actionWithTarget:followedNode_];
	}
	else
	{
		return [CCFollow actionWithTarget:followedNode_ worldBoundary:rect_];
	}
}

@end