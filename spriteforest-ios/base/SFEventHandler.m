//
//  SFEventHandler.m
//  SpriteForest2
//
//  Created by Moky on 12-9-30.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFEventHandler.h"

#import "SFSprite.h"
#import "SFAction.h"

@implementation SFEventHandler

@synthesize eventTree = eventTree_;
@synthesize actionTree = actionTree_;

+ (id) handlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree
{
	return [[[self alloc] initWithEventTree:eTree actionTree:aTree] autorelease];
}

- (id) initWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree
{
	if ((self = [self init]))
	{
		if ([eTree isKindOfClass:[NSDictionary class]])
		{
			self.eventTree = eTree;
		}
		if ([aTree isKindOfClass:[NSDictionary class]])
		{
			self.actionTree = aTree;
		}
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.eventTree = nil;
		self.actionTree = nil;
	}
	return self;
}

- (void) dealloc
{
	[eventTree_ release];
	[actionTree_ release];
	
	[super dealloc];
}

#pragma mark -

- (BOOL) doAction:(NSString *)action node:(CCNode *)node
{
	if (![action isKindOfClass:[NSString class]])
	{
		CNLog(@"invalid action name: %@", action);
		return NO;
	}
	if (![node isKindOfClass:[CCNode class]])
	{
		CNLog(@"invalid node: %@", node);
		return NO;
	}
	
	NSDictionary * dict = [actionTree_ objectForKey:action];
	if (![dict isKindOfClass:[NSDictionary class]])
	{
		CNLog(@"no such action: %@", action);
		return NO;
	}
	
	// replace 'Target'
	CCNode * target = [node getTarget:[dict objectForKey:@"Target"]];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"cannot find target, dict = %@", dict);
		return NO;
	}
	
	BOOL flag = NO;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	dict = [NSMutableDictionary dictionaryWithDictionary:dict];
	[(NSMutableDictionary *)dict setObject:target forKey:@"Target"];
	CCAction * act = [[SFAction getInstance:dict] ccAction];
	if ([act isKindOfClass:[CCAction class]])
	{
		// run it
		[target runAction:act];
		flag = YES;
	}
	else
	{
		CNLog(@"failed to create action, dict = %@, act = %@", dict, act);
	}
	
	[pool release];
	return flag;
}

- (BOOL) doEvent:(NSString *)event node:(CCNode *)node
{
	NSArray * tasks = [eventTree_ objectForKey:event];
	if (![tasks isKindOfClass:[NSArray class]])
	{
		//CNLog(@"no such event: %@", event);
		return NO;
	}
	
	BOOL flag = NO;
	
	for (NSDictionary * task in tasks)
	{
		if (![task isKindOfClass:[NSDictionary class]])
		{
			CNLog(@"invalid task (%@) in this event (%@)", task, event);
			continue;
		}
		CCNode * target = [node getTarget:[task objectForKey:@"Target"]];
		if (![target isKindOfClass:[CCNode class]])
		{
			CNLog(@"cannot find target, task = %@", task);
			continue;
		}
		
		id<SFEventDelegate> worker = self;
		if ([target isKindOfClass:[SFSprite class]])
		{
			worker = [(SFSprite *)target eventHandler];
		}
		
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		
		NSString * name = [task objectForKey:@"Name"];
		if (![name isKindOfClass:[NSString class]])
		{
			CNLog(@"ERROR: invalid name = %@", name);
		}
		else if ([worker doEvent:name node:target])
		{
			flag = YES;
		}
		else if ([worker doAction:name node:target])
		{
			// combined action
			flag = YES;
		}
		else
		{
			// cc action
			task = [NSMutableDictionary dictionaryWithDictionary:task];
			[(NSMutableDictionary *)task setObject:target forKey:@"Target"];
			CCAction * act = [[SFAction getInstance:task] ccAction];
			if ([act isKindOfClass:[CCAction class]])
			{
				[target runAction:act];
				flag = YES;
			}
			else
			{
				CNLog(@"failed to create action, task = %@, act = %@", task, act);
			}
		}
		
		[pool release];
	} // EOF 'for (NSDictionary * task in tasks)'
	
	return flag;
}

@end
